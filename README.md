# Luna Raytracer

Luna Raytracer is a simple multi-threaded C++ ray tracing library. It provides the basic building blocks for rendering simple scenes and hooks for extending its capabilites.

## Table of Contents

1. [Features](#features)
2. [Project structure](#project-structure)
3. [Build](#build)
4. [License](#license)

## Features

This is a list of the features currently provided by the library:

* General
  * Multiplatform.
  * Stochastic algorithm.
  * Designed for 64 bits platforms.
  * Multi-threaded core.
  * Listener-based progress notification.
* Rendering
  * 64 bits HDR color pipeline.
  * Quasi-Monte Carlo supersampling antialiasing.
  * Bucket rendering.
  * Gamma correction.
* Geometry
  * Mathematic entities: plane, disc, esphere.
  * Triangles and triangle meshes.
  * Model instancing.
* Lighting
  * Point light.
  * Area lights: sphere and disc.
  * Skylight.
  * Adaptive sampling using low-discrepancy sequences.
  * Light attenuation.
* Materials
  * Phong shading.
  * Glossy surfaces.
  * Reflection.
  * Refraction with light absorption.
* Cameras
  * Pinhole camera.
  * Real depth of field camera.
* Input/Output
  * PNG image saving.
  * ASC model loader.

## Project structure

The layout of the project is as follows:
* `bin`- Executable files after project building go here.
* `build`- Temporary files go here.
* `data`- Working folder during development/testing. Relative paths are solved to this folder.
* `dist`- Distributable binary packages are created in this folder.
* `doc`- Documentation folder.
* `prj`- Files needed for building the project.
* `src`- Source code.

The source code folder is divided into these additional folders:
- `app`- Simple application template for rapid prototyping.
- `core`- The core raytracer with the multi-thread task system is here, along the internal classes needed.
- `examples`- Usage examples using the `app` application template.
- `gui`- Progress dispaly window for the `app` application template.
- `io`- Model loading and image saving helper functions.
- `math`- Math-related code.
- `scene`- Scene abstractions such as light sources, cameras, objects, and so on.

## Build

The project uses a GNU Make based custom build system and some libraries for platform-independent operation.

#### Dependencies

The project has three library dependencies:
* Boost - Used for multi-threading and CPU count.
* libpng - Saving images using a helper fuction.
* SDL - Displaying progress in the sample application.

These libraries are all available for the most common platforms (Windows, Mac and Linux). On most Linux distributions they are easy to install using the package management tool.

#### Build system

The necessary files for building the project using GNU GCC and GNU Make can be found in the `prj/gcc` folder. The system uses two environment varaibles for choosing both the target architecture and the compilation profile. Creating more architecture configuration files adds support for building on more platforms and even cross-compiling.

As an example, this command will build the project for a x64 platform using the most optimized profile, without debugging symbols:
```
/home/user/raytracer/prj/gcc$ ARCH=x86_64 PROFILE=release make
```
While this command perform the same task, but for a x86 platform with debug symbols, lacking any optimization:
```
/home/user/raytracer/prj/gcc$ ARCH=x86 PROFILE=debug make
```
The complete list of available targets for the Make-based building system is:
* `make`- Executes the default target (`target`).
* `make all`- Same than the previous one, but executes additional Makefiles for subprojects. Not used.
* `make target`- This is the default target. Build the project and creates the executable file in the `bin` folder.
* `make deps`- Computes the dependencies using the `#include` directives in the source files.
* `make clean`- Deletes temporary and final build files from the `build` and `bin` folders.
* `make dist`- Packages in the `dist`folder the contents of the `bin` and `data` folders.
* `make distclean`- Cleans the content of the `dist` folder.
* `make doc`- Runs Doxygen.
* `make docclean`- Deletes the Doxygen-generated documentation.
* `make bin`- Runs the executable file from the `bin` folder using the `data` folder as working folder.

## License

Apache License Version 2.0 (see LICENSE in the repository).
