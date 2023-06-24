# GL GFX

`GL GFX` is a `C++`-(mostly)header-only library for developing games. It relies on [OpenGL](https://www.opengl.org) as a backend.

It is an evolution of the [NCurses Game
Engine](https://github.com/kriztioan/NCursesGameEngine) and inspired by the One
Lone Coder's
[olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine). A
number of projects are based off [YouTube
videos](https://www.youtube.com/channel/UC-yuWVUplUJZvieEligKBkA) of his.

The library has `MacOS` in mind, as for Audio it relies on `CoreAudio` and it expects a [GLUT that supports Retina](http://iihm.imag.fr/blanch/software/glut-macosx/).

## Usage

The library consists of six header files, which are listed in the table below together with their usage.

| header           | usage                        |
| ---------------- | ---------------------------- |
| `Audio.h`        | main SFX library             |
| `GFX3D.h`        | 2D and 3D vector/matrix math |
| `GLGFX.h`        | main GFX library             |
| `SampledAudio.h` | play sampled audio           |
| `Sprite.h`       | draw/manipulate sprites      |
| `Widgets.h`      | widget library               |

Note that the library is set in the`namespace` `cb::`.

`nesfonts8x8.c` holds the font used to draw text.

A number of projects are available in subdirectories. See each of them for examples and details on how to use `GL GFX`.

## Create Asset

A tool called `Create Asset` is included that can convert a binary asset into a format that can be directly included in `C`/`C++`-code, e.g., graphics and sound. It attempts to optimize space by compressing the data using `zlib`. This can increase binary portability.

The tool is compiled with:

```shell
make
```

This results in a binary executable called `CreateAsset`, which is invoked as:

```shell
./CreateAsset nesfont8x8.bin
```

The above will result in a file called `nesfont8x8.c`. The data can be included in a `C`/`C++` project by using the variables listed in the table below and prepending the `extern`-keyword. The table also gives the usage of each variable.

| type         | name          | usage                        |
| ------------ | ------------- | ---------------------------- |
| size_t       | nesfont8x8_s  | number of uncompressed bytes |
| size_t       | nesfont8x8_sz | number of compressed bytes   |
| const char[] | nesfont8x8_z  | byte data                    |

## Notes

1. `GL GFX` is an evolution of the [`NCurses Game Engine`](https://github.com/kriztioan/NCursesGameEngine).

## BSD-3 License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
