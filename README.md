# qbRayTrace2

Welcome to my series on building a ray tracer from scratch in C++ with the SDL2 library! Follow me in this 'code with me' style series as I build a simple but functional ray tracer from scratch in C++. As far as possible, I use only the standard libraries, with the addition of SDL2 to allow the display of the final image in a window.

**Note that the SDL2 library is not included here, you will have to obtain and install that yourself from the SDL2 website in order to use the qbRayTrace code.

You will also need to make sure that you clone this repository recursively to include the submodule containing the linear algebra library. This can be done using the --recurse-submodules command like this:

git clone --recurse-submodules https://www.github.com/QuantitativeBytes/qbRayTrace2.git

The code for the first 10 episodes is in a separate repository "qbRayTrace", where the code for each episode is in a different sub-folder. I did it this way to make it easier for people to follow the series. The code for episodes 11 and onwards will be here, in the "qbRayTrace2" repository and I will not be using separate sub-folders for each episode. As the project gets more complex, I thought that duplicating the code over and over again in each sub-folder would be too inefficient.

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
A basic implementation of a box primitive. Creates a unit cube at the origin that can then be transformed at will using the standard geometric transforms.
https://youtu.be/Fg-_f1L-6dI

## Episode 13
### Ray Tracing vs. Ray Marching
A comparison of ray marching and ray tracing techniques, with a simple implementation of ray marching.
https://youtu.be/4408vlE_60Y

## Episode 14
### Procedural textures - Part 1
A quick look at the basics of procedural textures.
https://youtu.be/5fuE4mTu8Cg

## Episode 15
### Value noise
A look at how procedural noise can be used to create more natural looking textures, starting with simple value noise.
https://youtu.be/iuJKrOtne_Y

## Episode 16
### Gradient noise
Extending the work we did in the last episode to implement gradient based procedural noise, allowing us to generate even more realistic and natural looking textures.
https://youtu.be/K-Tp8ucK3CU

## Episode 17
### Normal (bump) maps - Part 1
Part 1 of a mini-series looking at implementing normal maps. Normal maps, or bump maps as they are sometimes called, are a technique for adding surface detail without adding geometry.
https://youtu.be/22-8c0ow7XA

## Episode 18
### Texture based normal maps
Part 2 of the mini-series looking at normal maps. This episode looks at how we can compute a normal map directly from a procedural texture using numerical differentiation.
https://youtu.be/R-4QBaUvH84

## Episode 19
### Image based normal maps
Part 3 of the mini-series looking at normal maps. This episode focuses on how to implement and work with image based normal maps, such as those usually included with PBR textures. Note that you will have to use your own bitmap-format image files for the texture and normal map to make this code work, as these are not included with the repository. If you download from one of the common website that provide free textures, you may have to convert to a bitmap format first (it should work with either 3-bytes-per-pixel (RGB) or 4-bytes-per-pixel (RGBA) bitmap files).
https://youtu.be/4GGRx502-iY

## Episode 20
### Building a useful ray tracer
https://youtu.be/4gVQJWmMeSQ

## Episode 21
### UV Projection
A look at UV projection and how this differs from the UV mapping techniques that we have already implemented in Episode 9.
https://youtu.be/1nJwteZIOBI

## Episode 22
### Bounding boxes and composite shapes
Composite shapes offer us a way to combine multiple primitive shapes together and make it a lot easier to model complex geometries with multiple transforms.

Bounding boxes offer a simple and effective way to improve ray tracing performance by allowing us to test for intersections only with rays that are likely to intersect with a particular part of the scene, determined by which rays intersect with the bounding box.

Combined together, bounding boxes and composite shapes offer an effective way to model complex shapes and shorten the time required to render complex scenes.
https://youtu.be/1D9j60E27XI

## Episode 23
### Performance
The first of a three part mini-series looking at improving the performance of qbRAY.
https://youtu.be/-5kLk7_bs0U

## Episode 24
### Performance (Part 2)  - Profiling and Debugging
Using a profiler to investigate what is causing the code to be slow.
https://youtu.be/EQlXfCIBpdg

## Episode 25
### Performance (Part 3) - Faster linear algebra
Implementing a new matrix class to complete the work on making the linear algebra library faster for fixed size vectors and matrices.

https://youtu.be/sr1OA7NPwcI

## Episode 26
### Multi-threading (Part 1 of 2) - Tile based rendering
In the first of a 2 part mini-series on multi-threading, we take a look at implementing a tile based rendering system. On it's own, this isn't very useful, but it will form the foundation of the multi-threading implementation that we will look at in the next episode.

https://youtu.be/2bMUtPt3Ya0

