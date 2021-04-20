# Memake
The tighter the nicer.

## Run
1. `git clone https://github.com/krehwell/PSM-2.git`
2. `cd PSM-2`
3. `make`
4. `./main`

## Dependencies
1. SDL2: `pacman -S sdl2` || `apt-get install libsdl2-dev`
2. Glew (Optional) _(so far there is no implementation of this)_: `pacman -S glew` || `apt-get install glew-utils`

**np:** remove `-lGL -lGLEW` from makefile if Glew is not installed on system.
- Since I am using Arch-btw, I just copy the `apt` command from internet without testing. So, I am not sure it will work on Ubuntu or not.

## Why This Exists?
Well by default SDL never provides you function like to Draw Circle nor Ellipse or even to Draw Triangle/Polygon. What SDL provides is 
just Draw Rectangle and Draw Dot on screen. This Library can draw those 2D which SDL not provides by default. The more playground the more
imagination can be expressed. Also hey, there is a premade colors too with `Colmk`.
  
That's all the words I made up so that it seems a perfect project like everyone's make, but what I actually want is just to graduate. Who knows that someday, somebody use this library
to hack Elon Musk's Rocket.
