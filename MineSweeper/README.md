# Mine Sweeper

`Mine Sweeper` is a [classic](https://en.wikipedia.org/wiki/Minesweeper_(video_game)) single player puzzle game. It is inspired by a One Lone Coder [YouTube video](https://youtu.be/FOIbK4bJKS8).

`Mine Sweeper` is written using [`GL GFX`](../README.md).

![Mine Sweeper in Action](MineSweeper.png "Mine Sweeper in Action")

## Usage

`Mine Sweeper` is compiled with:

```shell
cmake .
make
```

This results in a binary executable called `MineSweeper`, which is invoked as:

```shell
./MineSweeper
```

`MineSweeper` relies on the mouse for input. The table below lists the mouse button and its associated action.

|mouse|action|
----|-----
|`left click`|reveal|
|`middle click`|place flag|

Lastly, `q` quits.

## Notes

1. `Mine Sweeper` saves its high score to `.minesweeper` in the running directory.
2. Graphics and sound assets are located in the `gfx`- and `sfx`-directory, respectively.

## BSD-3 License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
