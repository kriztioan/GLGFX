# Flappy Bird

[`Flappy Bird`](https://en.wikipedia.org/wiki/Flappy_Bird) is a side-scrolling avoidance game. It is inspired by a One Lone Coder [YouTube video](https://youtu.be/b6A4XHkTjs8) ([GitHub](https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_FlappyBird.cpp)).

`Flappy Bird` is written using [`GL GFX`](../README.md).

![Flappy Bird in Action](FlappyBird.png "Plappy Bird in Action")

## Usage

`Flappy Bird` is compiled with:

```shell
cmake .
make
```

This results in a binary executable called `FlappyBird`, which is invoked as:

```shell
./FlappyBird
```

`Flappy Bird` relies on the keyboard for input. The table below lists the keys that are recognized and their associated action.

|key|action|
----|-----
|`q`|quit|
|`space`|flap|

## Notes

1. `Flappy Bird` saves its high score to `.flappybird` in the running directory.
2. Graphics and sound assets are located in the `gfx`- and `sfx`-directory, respectively.

## BSD-3 License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
