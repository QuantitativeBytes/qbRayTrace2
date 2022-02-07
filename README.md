# qbRayTrace2

Welcome to my series on building a ray tracer from scratch in C++ with the SDL2 library! Follow me in this 'code with me' style series as I build a simple but functional ray tracer from scratch in C++. As far as possible, I use only the standard libraries, with the addition of SDL2 to allow the display of the final image in a window.

**Note that the SDL2 library is not included here, you will have to obtain and install that yourself from the SDL2 website in order to use the qbRayTrace code.

The code for the first 10 episodes is in a separate repository "qbRayTrace", where the code for each episode is in a different sub-folder. I did it this way to make it easier for people to follow the series. The code for episodes 11 and onwards will be here, in the "qbRayTrace2" repository and I will not be using seperate sub-folders for each episode. As the project gets more complex, I thought that duplicating the code over and over again in each sub-folder would be too inefficient.

This code is intended to be primarily for educational purposes and to be studied alongside the corresponding videos on the QuantitativeBytes YouTube channel.

As the code corresponds to specific episodes of the series, pull requests will not be accepted.

The QuantitativeBytes YouTube channel can be found here: www.youtube.com/c/QuantitativeBytes

The repository for the first 10 episodes can be found here: https://github.com/QuantitativeBytes/qbRayTrace

## Episode 11
### Fixing the normals
Made some changes to the way normals are handled when geometric transforms are applied. Previously this was not implemented correctly, leading to minor errors with reflections.
https://youtu.be/5lDRXL5zQDo

## Episode 12
### Boxes
A basic implementation of a box primative. Creates a unit cube at the origin that can then be transformed at will using the standard geometric transforms.
https://youtu.be/Fg-_f1L-6dI

## Episode 13
### Ray Tracing vs. Ray Marching
A comparison of ray marching and ray tracing techniques, with a simple implementation of ray marching.
https://youtu.be/4408vlE_60Y
