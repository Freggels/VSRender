# VSRender
A simple project of mine to learn about the vulkan api and 3d graphics in general

![](https://raw.githubusercontent.com/SHGuy1/VSRender/master/screenshots/lights_upgradable.png "Lights are not working yet")
## Deps and Compilation
### Linux
#### Dependedncies
  - libglfw
  - vulkan headers (vulkan/vulkan.h)
  - \> Please check first, weather your gpu (or apu) supports vulkan
  - a c++17-enabled compiler
#### Compiling
I have a little script for quick compilation.
Just execute in the root dir of the project the following:
```
./scripts/build.sh -b
```

## Running
Now you can run either the ```./main``` file directly or use the script with the ```-r``` arg
