A wireframe rasteriser written in C using MLX42 library. First graphics project in the 42 curriculum. It was left in a janky state but I'm still proud of it. Learned a lot about 3d graphics and built everything from the ground up.

Installation:

Install dependencies glfw and cmake.


```bash
git clone https://github.com/taoramo/fdf
cd fdf
git clone https://github.com/codam-coding-college/MLX42
```

Edit Makefile to link glfw from the correct directory, then run
```
make
```

Usage:
```
./fdf [map_file]
```

Implemented following the OpenGL matrix pipeline model. Supports orthographic and perspective views with camera lens like zoom. Translation and rotation of model and coloring according to map or height along y-axis.

Controls:

|key|function|
|---|---|
| arrow keys | rotation |
| i,j,k,l | translation|
|z,a|zoom|
|p|switch perspective|
|c|bonus color mode|

