/**
 *  @file   CreateAsset.cpp
 *  @brief  Create Asset
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <zlib.h>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "need one input file\n";
    return 1;
  }

  std::string path(argv[1]);

  std::ifstream ifstr;

  ifstr.open(path, std::ios::in | std::ios::binary);

  if (ifstr.fail())
    return 2;

  std::streampos beg = ifstr.tellg();

  ifstr.seekg(0, std::ios::end);

  std::streampos end = ifstr.tellg();

  size_t size = end - beg;

  ifstr.seekg(0, std::ios::beg);

  unsigned char *buff = new unsigned char[size];

  ifstr.read(reinterpret_cast<char *>(buff), size);

  ifstr.close();

  uLong z_size = compressBound(size);

  Bytef *z_buff = new Bytef[z_size];

  if (Z_OK != compress2(z_buff, &z_size, static_cast<Bytef *>(buff), size,
                        Z_BEST_COMPRESSION)) {

    delete[] buff;

    return 3;
  }

  delete[] buff;

  std::string dir, file;

  std::size_t pos = path.find_last_of('/');

  if (pos != std::string::npos) {
    dir = path.substr(0, pos);
    if (pos < path.length())
      file = path.substr(pos + 1);
  } else
    file = path;

  pos = file.find_last_of('.');

  std::string base = (pos == std::string::npos) ? file : file.substr(0, pos);

  if (base.empty()) {
    delete[] z_buff;
    return 4;
  }

  std::ofstream ofstr;

  ofstr.open(base + ".c", std::ios::out);

  if (ofstr.fail()) {
    delete[] z_buff;
    return 5;
  }

  ofstr << "#include<stdlib.h>\nsize_t " << base << "_s = " << size
        << ";\nsize_t " << base << "_sz = " << z_size << ";\nconst char "
        << base << "_z[] = {";

  for (int i = 0; i < (z_size - 1); i++) {
    if (0 == (i % 16))
      ofstr << "\n";
    ofstr << std::showbase << std::setw(2) << std::setfill('0') << std::hex
          << static_cast<int>(z_buff[i]) << ",";
  }
  ofstr << std::showbase << std::setw(2) << std::setfill('0') << std::hex
        << static_cast<int>(z_buff[z_size - 1]) << "};" << std::endl;

  delete[] z_buff;

  return 0;
}
