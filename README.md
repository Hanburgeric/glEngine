# glEngine
A personal, ongoing attempt at an OpenGL based graphics engine. Currently, the main focus of the project is to encapsulate and display [all of the specifications of 2.0 glTF files](https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html), which should serve as an adequate initial guideline for what features the engine should implement and how they should be implemented. While certain individual features have already been implemented separately (model loading, texture wrapping, animation, etc.), they have yet to be combined into a single, cohesive codebase.

<br>

## Features
### `master` branch
The main version of the project. Currently quite minimal and somewhat buggy due to a recent refactoring of code in order to accomodate a change in JSON libraries (RapidJSON → nlohmann/json). Only capable of reading basic vertex information at the moment, but features a more robust error handling and shader system.

<br>

### `deprecated-animation` branch
A soon-to-be deprecated version of the project, built quite crudely for the express purpose of implementing an animation system.

<p align="center">
  Basic Animation + Interpolation (Linear, Step, Cubic Spline)
</p>
<p align=center>
  <img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExa2xqYWEyOHExZW93cXEzMGg3eThtdHl1MTF0dm03d2ljczZ1NzVucyZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/wHNvPAclzAmAndXHMr/giphy.gif"/
</p><br>

<br><p align="center">
  Morphing Animation
</p>
<p align=center>
  <img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExamxqdHZkMjhsdDI1c3oybTZpMGlpeW9xZHIycThhN2o3dHB4NjdlMiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/rWqTkMx7c0kAQedKba/giphy.gif"/>
</p><br>

### `deprecated-pbr` branch
A soon-to-be deprecated version of the project, built quite crudely for the express purpose of implementing and testing a physically based rendering (PBR) system.

<p align="center">
  PBR with Image Based Lighting (IBL)
</p>
<p align=center>
  <img width=720 src="https://imgur.com/KouT5Da.png"/>
</p><br>

## Controls
Camera
> Currently only a feature of the `deprecated` branches
 - `RMB` + Drag : move camera.
 - `LAlt` + `RMB` + Drag : rotate camera.
 - `Scroll` : zoom camera.
<br>

## To-Do
 - Refactor and merge the two `deprecated` branches into the `master` branch.
 - Implement a more flexible and dynamic shader system that automatically accounts for the needs and layout of the model.
   - Naturally, as the code expands, there will also eventually be a need for shader and overall resource management (e.g. shader caching, batch rendering, etc.).
 - Implement a GUI that allows runtime manipulation of the scene for better functionality testing.

<br>

## Development Environment
 - IDE : CLion
 - Compiler : MinGW
 - Libraries :
   - [Dear ImGui](https://github.com/ocornut/imgui)
   - [glad](https://glad.dav1d.de/)
   - [GLFW](https://www.glfw.org/)
   - [GLM](http://glm.g-truc.net)
   - [nlohmann/json](https://json.nlohmann.me/)
   - [stb](https://github.com/nothings/stb)
