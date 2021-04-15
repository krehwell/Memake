# Memake
the tighter it is the nicer it will

## Run
1. `git clone https://github.com/krehwell/PSM-2.git`
2. `cd PSM-2`
3. `make`

## Dependencies
1. SDL2: `pacman -S sdl2` || `apt-get install libsdl2-dev`
2. Glew (Optional) _(so far there is no implementation of this)_: `pacman -S glew` || `apt-get install glew-utils`

**np** remove `-lGL -lGLEW` from makefile if Glew is not installed on system.
- Since I am using Arch, I just copy the `apt` command from internet without testing. So, I am not sure it will work on Ubuntu or not.
