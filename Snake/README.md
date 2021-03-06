# Snake

[`Snake`](https://en.wikipedia.org/wiki/Snake_(video_game_genre)) is a classic obstacle avoidance game. This simple version of `Snake` gives the player 3 seconds to 'eat' the item before it disappears.

`Snake` is written using [`GL GFX`](../README.md).

![Snake in Action](Snake.png "Snake in Action")

## Usage

`Snake` is compiled with:

```shell
cmake .
make
```

This results in a binary executable called `Snake`, which is invoked as:

```shell
./Snake
```

`Snake` relies on the keyboard for input. The table below lists the keys that are recognized and their associated action.

|key|action|
----|-----
|`left arrow`|move left|
|`up arrow`|move up|
|`right arrow`|move right|
|`down arrow`|move down|
|`p`|toggle pause|
|`q`|quit|
|`space`|continue|

## Notes

1. `Snake` saves its high score to .snake in the running directory.

## BSD-3 License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
