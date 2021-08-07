# Game of Life

`Game of Life` is an implementation of [`Conway's Game of Life`](https://en.wikipedia.org/wiki/Conway's_Game_of_Life) [cellular automaton](https://en.wikipedia.org/wiki/Cellular_automaton).

It is inspired by a One Lone Coder [YouTube video](https://youtu.be/E7CxMHsYzSs) ([GitHub](https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_GameOfLife.cpp)).

`Game of Life` is written using [`GL GFX`](../README.md).

![Game of Life in Action](GameOfLife.png "Game of Life in Action")

## Usage

`Game of Life` is compiled with:

```shell
cmake .
make
```

This results in a binary executable called `GameOfLife`, which is invoked as:

```shell
./GameOfLife
```

`Game of Life` relies on the keyboard for input. The table below lists the keys that are recognized and their associated action.

|key|action|
----|-----
|`n`|evolve 1 step (when stopped)|
|`q`|quit|
|`r`|reset|
|`s`|stop/resume evolving|

## Notes

1. `Game of Life` is a *zero*-player game.

## BSD-3 License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
