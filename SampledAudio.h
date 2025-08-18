/**
 *  @file   SampledAudio.h
 *  @brief  Play Audio Samples
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-07-30
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CBGLGFX_SAMPLEDAUDIO_H_
#define CBGLGFX_SAMPLEDAUDIO_H_

#include "Audio.h"

#include <fstream>
#include <vector>

extern "C" {
#include <zlib.h>
}

namespace cb {
class SampledAudio;
}

typedef struct _AudioSample {
  _AudioSample() = default;

  _AudioSample(char *d, size_t s) : data(d), size(s) {};
  char *data;
  size_t size;
} AudioSample;

typedef struct {
  size_t pos;
  size_t sample;
  bool loop;
} AudioChannel;

class cb::SampledAudio : public cb::Audio {
public:
  SampledAudio() noexcept = default;

  [[maybe_unused]] void Start() {

    Audio::Start();

    SetCallback([&](double fFrameTime, void *mData, size_t mDataByteSize) {
      size_t bytes_to_copy;
      char *buf = (char *)mData, *p, *pp;
      bzero(buf, mDataByteSize);

      if (!mixer || samples.empty())
        return;

      for (unsigned int i = 0; i < channels; i++) {
        if (mixer[i].pos == 0)
          continue;
        if (mixer[i].pos > samples.at(mixer[i].sample).size) {

          if (mixer[i].loop) {
            mixer[i].pos = 1;
          } else {
            mixer[i].pos = 0;
            continue;
          }
        }

        p = samples.at(mixer[i].sample).data + mixer[i].pos - 1;

        if ((mixer[i].pos + mDataByteSize) <=
            samples.at(mixer[i].sample).size) {
          bytes_to_copy = mDataByteSize;
        } else {
          bytes_to_copy = samples.at(mixer[i].sample).size - mixer[i].pos + 1;
        }

        mixer[i].pos += bytes_to_copy;
        pp = buf;
        float b;
        while (bytes_to_copy--) {
          b = static_cast<float>(*pp) + static_cast<float>(*p++);
          *pp++ = std::max(-127.0f, std::min(127.0f, b));
        }
      }
    });

    mixer = new AudioChannel[channels]{};
  }

  [[maybe_unused]] void Stop() {
    Audio::Stop();
    Reset();
    delete mixer;
    mixer = nullptr;
  };

  [[maybe_unused]] size_t LoadFromFile(const char *filename) {

    std::ifstream ifstr;

    ifstr.open(filename, std::ios::in | std::ios::binary);
    if (ifstr.fail())
      return -1;

    AudioSample s;

    ifstr.seekg(0, std::ios::end);
    size_t size = s.size = ifstr.tellg();
    ifstr.seekg(0, std::ios::beg);
    s.data = new char[s.size];
    ifstr.read(s.data, s.size);
    ifstr.close();
    samples.emplace_back(s);

    return samples.size() - 1;
  }

  [[maybe_unused]] size_t Load(const char *sample, size_t size) {

    AudioSample s;
    s.size = size;
    s.data = new char[s.size];
    std::memcpy(s.data, sample, s.size);
    samples.emplace_back(s);

    return samples.size() - 1;
  }

  [[maybe_unused]] int z_Load(const char *z, size_t s_z, uLongf s) {

    char *d = new char[s];

    uncompress(reinterpret_cast<Bytef *>(d), &s,
               reinterpret_cast<const Bytef *>(z), s_z);

    int id = Load(d, s);

    delete[] d;

    return id;
  }

  [[maybe_unused]] void Play(unsigned int sample, bool loop = false) {

    if (mixer != nullptr && sample < samples.size() &&
        samples.at(sample).data != nullptr) {

      for (unsigned int i = 0; i < channels; i++) {

        if (mixer[i].pos == 0 && !mixer[i].loop) {

          mixer[i].pos = 1;
          mixer[i].sample = sample;
          mixer[i].loop = loop;
          break;
        }
      }
    }
  }

  [[maybe_unused]] size_t PlaySample(char *data, size_t size,
                                     bool loop = false) {

    samples.emplace_back(data, size);
    size_t id = samples.size() - 1;
    Play(id, loop);
    return id;
  }

  [[maybe_unused]] void Reset() {
    if (mixer != nullptr)
      bzero(mixer, channels * sizeof(AudioChannel));
    for (auto &s : samples)
      delete s.data;
    samples.clear();
  };

  [[maybe_unused]] inline void SetAudioChannels(unsigned int chan) {
    channels = chan;
  }

protected:
  std::vector<AudioSample> samples;
  unsigned int channels = 16;
  AudioChannel *mixer = nullptr;
};

#endif // CBGLGFX_SAMPLEDAUDIO_H_
