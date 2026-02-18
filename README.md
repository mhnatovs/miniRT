*This project has been created as part of the 42 curriculum by jiyawang, mhnatovs.*

# miniRT

## Description
miniRT is a simple Raytracer developed in C. The goal of the project is to implement the fundamentals of ray tracing to render 3D scenes. It supports the rendering of basic geometric primitives (spheres, planes, and cylinders) with ambient and point light sources. The program handles camera positioning and orientation, providing a windowed display of the rendered scene using the MLX42 library.

## Instructions

### Prerequisites
- Linux/macOS
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
./miniRT scenes/scene.rt
```
- **Controls**: Press `ESC` to close the window and exit the program.

### Scene Format
The project uses `.rt` files to define scenes. Each line represents a scene element:
- `A`: Ambient lighting (ratio, RGB)
- `C`: Camera (position, direction, FOV)
- `L`: Light source (position, brightness, RGB)
- `sp`: Sphere (center, diameter, RGB)
- `pl`: Plane (point, normal, RGB)
- `cy`: Cylinder (center, axis, diameter, height, RGB)

Example `.rt` file:
```
A 0.2 255,255,255
C -50,0,20 1,0,0 70
L -40,0,30 0.7 255,255,255
pl 0,0,0 0,1,0 255,0,225
sp 0,0,20 20 255,0,0
cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255
```

## Resources
- [Scratchapixel](https://www.scratchapixel.com/): Comprehensive guides on computer graphics and ray tracing.
- [Ray Tracing in One Weekend](https://raytracing.github.io/): A popular tutorial series for building a ray tracer from scratch.

### Mathematical Background
- Linear algebra: vectors, dot product, cross product
- Analytic geometry: ray-sphere, ray-plane, ray-cylinder intersection
- Lighting models: ambient, diffuse (Lambertian)

### AI Usage

AI was used during development for:

**Learning support:**
- Explaining mathematical concepts (quadratic equation for ray-sphere intersection, vector projections)
- Breaking down complex algorithms into understandable steps
- Providing visual analogies and examples

**Debugging assistance:**
- Identifying logic errors in intersection calculations
- Reviewing code structure

**Code review:**
- Suggesting better variable names for clarity

**What we did NOT use AI for:**
- Writing complete functions (we wrote all code ourselves)
- Copy-pasting solutions without understanding
- Bypassing the learning process

All mathematical formulas were derived step-by-step with explanations.
Every function was written by hand after understanding the underlying logic.
The project represents genuine learning and comprehension of ray tracing principles.

## Team

- **mhnatovs** - Ray tracing engine, mathematics, lighting
- **jiyawang** - Parser, MLX integration, memory management
```