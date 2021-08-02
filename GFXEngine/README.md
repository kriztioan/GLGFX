# GXEngine

`GXEngine` demonstrates the use of a  [projection matrix](https://en.wikipedia.org/wiki/Projection_matrix) to display 3D graphics. It is inspired by a One Lone Coder [YouTube video](https://youtu.be/nBzCS-Y0FcY) ([GitHub](https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_olcEngine3D_Part4.cpp)).

`GXEngine` is written using [`GL GFX`](../README.md).

## Usage

`GFXEngine` is compiled with:

```shell
cmake .
make
```

This results in a binary executable called `GFXEngine`, which is invoked as:

```shell
./GFXEngine models/Mountain.obj
```

The first command line parameter points to a file defining a mesh object. These are simple text files containing the vertices. [Blender](https://www.blender.org) is capable of exporting to this file format. The [models](models/)-directory holds the files of a few objects.

`GFXEngine` relies on the keyboard for input. The table below lists the keys that are recognized and their associated action.

|key|action|
----|-----
|`left arrow`|move camera left|
|`up arrow`|move camera up|
|`right arrow`|move camera right|
|`down arrow`|move camera down|
|`a`|turn left|
|`w`|move forward|
|`d`|turn right|
|`s`|move backward|
|`q`|quit|

## Notes

1. `GXEngine` can use a significant amount of computer resources.

## BSD-3 License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
