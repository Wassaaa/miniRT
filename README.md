 # miniRT

 miniRT is a simple ray tracing renderer implemented in C. It uses the MLX42 library for graphics rendering.

 ## Installation

 ### Prerequisites

 Before installing miniRT, make sure you have the following dependencies installed:

 - CMake (version 3.18.0 or higher)
 - GLFW (version 3.3.6 or higher)

 #### Installing dependencies

 For macOS (using Homebrew):
 ```bash
 brew install cmake glfw
 ```

 For Ubuntu/Debian:
 ```bash
 sudo apt-get update
 sudo apt-get install cmake libglfw3-dev
 ```

 For Fedora:
 ```bash
 sudo dnf install cmake glfw-devel
 ```

 For more detailed instructions on installing these dependencies, please refer to the [MLX42 README](lib/MLX42/README.md).

 ### Building miniRT

 1. Clone this repository:
    ```bash
    git clone https:github.com/LeonorTu/miniRT.git
    cd miniRT
    ```

 2. Build the project:
    ```bash
    make
    ```

 ## Usage

 To run miniRT:

 ```bash
 ./miniRT scenes/rt_sample.rt
 ```

 This command will run miniRT with the scene file "rt_sample.rt" located in the "scenes" directory.

 ### Scene File Format

 Scene files use a specific format to describe the elements in the scene. Here's a basic example:

 ```
 A 0.2 255,255,255
 C 0,0,-10 0,0,1 60
 L 5,5,0 0.5 255,255,255
 sp 0,0,15 5 255,0,0
 ```

 For more details on the scene file format, please refer to "scenes/rt_sample.rt" file

 ### Controls

 - WASD keys: Move the camera horizontally
 - SPACE: Move the camera up
 - C: Move the camera down
 - Arrow keys: Pan the camera
 - TAB: Change targeted object (shown in the top left of the screen)
 - R: Rotate the targeted object 30 degrees right
 - T: Rotate the targeted object 30 degrees left
 - . (dot): Scale the targeted object bigger
 - , (comma): Scale the targeted object smaller
 - UHJK OL keys: Move targeted objects

 ## Features

 - Ray tracing with support for multiple shapes (spheres, planes, cylinders, cones)
 - Multiple light sources
 - Shadows and reflections
 - Texture mapping and bump mapping
 - Multi-threaded rendering for improved performance

 ## Compatibility

 This program has been tested and confirmed to work on Linux and macOS systems.

 ## Contributing

 Contributions are welcome! Please feel free to submit a Pull Request.

 ## License

 This project is licensed under the [Your License] License - see the LICENSE file for details.

 ## Acknowledgments

 - [MLX42 Library](https:github.com/codam-coding-college/MLX42)

  ## Co-Authors
 - [jtu](https://github.com/LeonorTu)
 - [aklein](https://github.com/Wassaaa)