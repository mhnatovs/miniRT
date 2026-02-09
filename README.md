*This project has been created as part of the 42 curriculum by jiyawang, mhnatovs.*

# miniRT

## Description
miniRT is a simple Raytracer developed in C. The goal of the project is to implement the fundamentals of ray tracing to render 3D scenes. It supports the rendering of basic geometric primitives (spheres, planes, and cylinders) with ambient and point light sources. The program handles camera positioning and orientation, providing a windowed display of the rendered scene using the MLX42 library.

## Instructions

### Prerequisites
- `cc` compiler
- `cmake` (required for MLX42)
- `glfw` (dependency for MLX42)
- `make`

### Compilation
To compile the project, run the following command in the root of the repository:
```bash
make
```
This will build the `MLX42` library and the `miniRT` executable.

### Execution
To run the Raytracer with a scene description file:
```bash
./miniRT scene.rt
```
- **Controls**: Press `ESC` to close the window and exit the program.

### Scene Format
The project uses `.rt` files to define scenes. Each line represents a scene element:
- `A`: Ambient lighting
- `C`: Camera
- `L`: Light source
- `sp`: Sphere
- `pl`: Plane
- `cy`: Cylinder

## Resources
- [Scratchapixel](https://www.scratchapixel.com/): Comprehensive guides on computer graphics and ray tracing.
- [Ray Tracing in One Weekend](https://raytracing.github.io/): A popular tutorial series for building a ray tracer from scratch.

### AI Usage


## Features
