# PictureProgram
A console-based simple picture program that can edit a picture in varies ways. Uses Sean Barrett's stb single-file public domain file libraries for C/C++.

# Requirements
GCC c++ compiler,
Supported picture file - PNG or JPG,
Pictures in picture_reservoir folder for the mosaic functionality

# Usage
When first starting the program, a compatible picture file must be given to proceed. The name or directory is sufficent.
The program will then show different options to edit the picture - pick one.
The result of each option will be in "result.jpg" in the same directory as main.exe.
The mosaic function requires a "pictures_reservoir" folder inside which you should provide pictures to be used.
The "Make a lot of images of colors" option will create 25^3 number of 64x64 images of colors and will be places in the same folder as main.exe. Use at your own discretion.

# Examples

Original: 
![test](https://github.com/Crayfry/PictureProgram/assets/52294803/b430e9e4-4f5c-4eb7-8db0-cb7355dbb3aa)

Greyscale:
![result](https://github.com/Crayfry/PictureProgram/assets/52294803/0d111ba6-4c42-4412-ae52-0bbe48f4c8bd)

Reflection:
![result](https://github.com/Crayfry/PictureProgram/assets/52294803/8a795da9-d3b7-47f8-a018-d281bd5b26f0)

Mosaic (sampled down as resulting picture is too big to upload):
![image](https://github.com/Crayfry/PictureProgram/assets/52294803/8f4e5842-3b04-42e1-ae31-364b3770e336)
![image](https://github.com/Crayfry/PictureProgram/assets/52294803/b184a2de-032a-4f9d-8ebc-ecaa4e17dcc2)
![image](https://github.com/Crayfry/PictureProgram/assets/52294803/324dde1c-0591-4c0d-9376-194161195e40)
