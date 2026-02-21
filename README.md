*This project has been created as part of the 42 curriculum by jiyawang, mhnatovs.*

# miniRT

## Description
miniRT is a basic Raytracer implementation written in C. The goal of this project is to generate computer-generated images using the Ray Tracing technique. It simulates the physics of light to render 3D scenes containing basic geometric shapes (Spheres, Planes, and Cylinders) with realistic lighting and shadows.

This project utilizes the **MLX42** library for window management and pixel manipulation.

**Key Features:**
-   **Shapes:** Sphere, Plane, Cylinder.
-   **Lighting:** Ambient and diffuse lighting implementation.
-   **Shadows:** Hard shadows casting.
-   **Interactive Camera:** Move and rotate the view inside the scene using WASD and mouse.
-   **Object Manipulation:** Select objects with the mouse to move or scale them interactively.
-   **Scene Parsing:** Reads scene configuration from `.rt` files.

## Instructions

### Compilation
To compile the project, simply run `make` in the root directory:
```bash
make
```

### Execution
Run the program by providing a path to a scene file (`.rt`):
```bash
./miniRT scenes/scene.rt
```

### Controls
-   **Camera Movement:**
    -   `W`, `A`, `S`, `D`: Move camera position.
    -   `Arrow Keys`: Rotate camera view.
    -   `Q` / `E`: Move Up / Down.
-   **Object Interaction:**
    -   **Left Click:** Select an object.
    -   **Drag (Left Click):** Move the selected object.
    -   **Scroll Wheel:**
        -   If no object is selected: Adjust Camera FOV (Zoom).
        -   If an object is selected: Scale the object (Radius/Height).
    -   **Right Click:** Deselect object / Stop dragging.
-   **General:**
    -   `ESC`: Exit the program.

## Resources

### References
-   [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) - The standard guide for understanding ray tracing concepts.
-   [MLX42 Documentation](https://github.com/codam-coding-college/MLX42) - Documentation for the graphical library used.
-   [Scratchapixel](https://www.scratchapixel.com/) - Great resources for computer graphics math.
-   [42 miniRT Subject](https://cdn.intra.42.fr/pdf/pdf/145453/en.subject.pdf) - Project requirements.

### AI Usage
AI assistants (GitHub Copilot) were used in this project to enhance development efficiency and code quality. Specifically:

-   **Code Optimization:** AI suggested compiler flags (`-O3`, `-ffast-math`) and architectural changes in the ray tracing loop (deferring normal calculation) to significantly improve rendering performance.
-   **Debugging:** AI assisted in analyzing Valgrind reports to differentiate between project-specific memory leaks and external library (MLX42/GLFW) allocations.
-   **Refactoring:** AI helped split large functions and files (e.g., `move_object.c`, `if_colliding.c`) to comply with the 42 "Norminette" coding standard (max 25 lines per function, max 5 functions per file).
-   **Boilerplate:** AI generated standard boilerplate code for headers and Makefiles.
-   **Learning:** Explaining complex mathematical concepts like vector projections and intersection formulas.
