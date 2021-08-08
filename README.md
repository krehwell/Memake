# Memake
Yeet, yeet, yeet!.

```c++
#include "Memake.h"
Memake mmk(800, 800, "memake window");

void draw() {
    mmk.drawRect(300, 300, 100, 100, Colmake.red); // draw a rectangle with red color
}

int main() {
    mmk.update(draw);
    return 0;
}
```

## Dependencies
- [SDL2](https://www.libsdl.org/)

## Download
Download project based on tools you use to run C++:
- Manual Compile (for chad): `git clone https://github.com/krehwell/Memake.git`
- Visual Studio Code: [GDrive](https://drive.google.com/uc?id=1miBk4zrwGcTGMf8Lj65ge2YUiKuP8WUz&export=download)
- Visual Studio: [GDrive](https://drive.google.com/uc?id=1CSqh1opYfNVwt_4Vw8hDVYIA1FBPTcxu&export=download)
- Dev-C++: [GDrive](https://drive.google.com/u/1/uc?id=1ztK2zg4faMglrwNrvJa429BcZ2al5PK-&export=download)


## Installation
<details>
<summary>Visual Studio Code (VsCode) Installation: (<a href="https://imgur.com/gallery/Xa16Wzh">Simple installation page</a>) </summary>  

1. Download the project and extract
2. Inside the extracted folder go to `__install__` folder  
    ![vscode1](https://i.imgur.com/zAySyOA.png)  
3. Move `MinGW` folder to `C:`  
    ![vscode2](https://i.imgur.com/ev9vPj2.png) 
4. Right click "Add MinGW to env.bat" and Run as administrator
    ![vscode3](https://i.imgur.com/7X5sBvA.png) 
5. Open the extracted project with vscode
    ![vscode4](https://i.imgur.com/7X5sBvA.png) 
6. Install C++ extension for VsCode
    ![vscode5](https://i.imgur.com/dkXNRWW.png) 
7. Run project by pressing F5
    ![vscode6](https://i.imgur.com/4ESu7QX.png) 
</details>

<details>
<summary>Visual Studio Installation: (<a href="https://imgur.com/gallery/B6VY4PZ">Simple installation page</a>)</summary>  
<b>note</b> : This example is run on Visual Studio 2019, it should run just fine on 2017 too.  
  
1. Download the project and extract
2. Inside the extracted folder open the "Memake_VisualStudio.sln"  
    ![vs1](https://i.imgur.com/zAySyOA.png)  
3. Press "Local Windows Debugger" to compile and run project   
    ![vs2](https://i.imgur.com/kIdD6zO.png) 
4. See result  
    ![vs3](https://i.imgur.com/i44HiFl.png)
</details>

<details>
<summary>Dev-C++ Installation: (<a href="https://imgur.com/a/9dTH38w">Simple installation page</a>) </summary>
 
    
1. Download the project and extract
2. Inside the extracted folder click "project.dev" to open the project in Dev-C++  
    ![devc++1](https://i.imgur.com/H7ocRax.png)  
3. Press "Compile and Run (F11)" to compile and run project   
    ![devc++2](https://i.imgur.com/SO7AwoU.png) 
4. See result  
    ![devc++3](https://i.imgur.com/Htd0B13.png)
</details>


## Example Codes

### Animation with Keyboard 
<img src="https://i.imgur.com/TFwBkr5.gif" width="35%">
<details>
<summary>Code snippet</summary>  
    
```c++
#include "Memake/Memake.h"
using namespace std;

Memake mmk(800, 800, "memake");

int x = 350;
int y = 350;

void draw() {
    mmk.drawRect(x, y, 100, 100, Colmake.red);  // draw rectangle with a red color
    
    // get keyboard's key pressed  
    switch(mmk.readKeyInput()) {
        case 'd':
            x++;
            break;
        case 'a':
            x--;
            break;
        case 's':
            y++;
            break;
    	case 'w':
            y--;
            break;
	}
}

int main()
{
    mmk.update(draw);

    return 0;
}
```  
	
</details>
  
### Animation with Mouse 
<img src="https://i.imgur.com/MTdYxTl.gif" width="35%">
<details>
<summary>Code snippet</summary>  
    
```c++
#include "Memake/Memake.h"
using namespace std;

Memake mmk(800, 800, "memake");

int x = 350;
int y = 350;

void draw() {
    mmk.drawCircle(x, y, 40, Colmake.yellow);  // draw circle with a yellow color
    
    // get mouse position
    x = mmk.getMousePosX();
    y = mmk.getMousePosY();
}

int main()
{
    mmk.update(draw);

    return 0;
}

```  
	
</details>

### Randomize Screen Background Every X Second 
<img src="https://i.imgur.com/lCdFArn.gif" width="35%">
<details>
<summary>Code snippet</summary>  
    
```c++
#include "Memake/Memake.h"
using namespace std;

Memake mmk(800, 800, "memake");

int x = 350;
int y = 350;

void draw() {
    mmk.drawFractalTree(400, 750, 150, 22, 90, 20, Colmake.cornsilk);
    
    // set new background color 
    Color newColor = mmk.generateColor(random(0,255), random(0,255), random(0,255));
    mmk.setScreenBackgroundColor(newColor);
    
    mmk.delay(200);  // delay to slow re-rendering 
}

int main()
{
    mmk.update(draw);

    return 0;
}

```  
</details>

### Clamping Ball Animation 
<img src="https://i.imgur.com/dEMaNvI.gif" width="35%">
<details>
<summary>Code snippet</summary>  
    
```c++
#include "Memake/Memake.h"
using namespace std;

Memake mmk(800, 800, "memake");

class Ball {
    public:
        int x, y, r;
        int xdirection = 1, ydirection = 1;
        
        Ball(int _x, int _y, int _r) {
            x = _x;
            y = _y;
            r = _r;
        }
        
        void update() {
            draw();
            move();
            checkScreenClamp();
        }
        
        void draw() {
            mmk.drawCircle(x, y, r, Colmake.beige);
        }
        
        void move() {
            x += xdirection;
            y += ydirection;
        }
        
        void checkScreenClamp() {  // check screen's edge to change ball's direction
            if (x <= 0 || x >= mmk.getScreenW()) {
                xdirection *= -1;
            }
        	
            if (y <= 0 || y >= mmk.getScreenH()) {
                ydirection *= -1;
            }
        }
};

int main()
{
    Ball ball(230, 520, 40);
	
    // use lambda to utilize local scope instead of define everything as global variable
    mmk.update([&](){
        ball.update();
        
        mmk.delay(1);
    });

    return 0;
}


```  
</details>
	
### Generate Custom Polygon 
<img src="https://i.imgur.com/ZsuLCKI.png" width="35%">
<details>
<summary>Code snippet</summary>  
    
```c++
#include "Memake/Memake.h"
using namespace std;

Memake mmk(800, 800, "memake");

void draw() {
    Vector2 polygon[] = {{117, 173}, {200, 300}, {364, 351}, {528, 144}, {414, 203}, {355, 63}, {277, 172}, {217, 51}, {203, 195}};
    mmk.drawPolygon(polygon, 9, mmk.generateColor(255,102,0));  // 9 is the number of edges desired to be drawn
}

int main()
{
    mmk.update(draw);

    return 0;
}
```  
</details>
	
### Polygon Generator Randomizer  
<img src="https://i.imgur.com/HVtGYwv.gif" width="35%">
<details>
<summary>Code snippet</summary>  
    
```c++
#include "Memake/Memake.h"
using namespace std;

Memake mmk(800, 800, "memake");

void draw() {
    Vector2 polygon[] = {
        {random(400, 500), random(300, 800)}, 
        {random(200, 300), random(200, 300)}, 
        {random(400, 500), random(300, 800)}, 
        {random(200, 300), random(200, 300)}, 
        {random(200, 300), random(200, 300)}, 
        {random(200, 300), random(200, 300)}, 
        {random(200, 300), random(200, 300)}, 
        {random(200, 300), random(200, 300)}, 
        {random(200, 300), random(200, 300)},
        {random(600, 700), random(400, 600)},
        {random(500, 700), random(400, 500)},
        {random(600, 600), random(400, 700)}
    };
		
    mmk.drawPolygon(polygon, random(7,12), Colmake.khaki); 
    
    mmk.delay(600);
}

int main()
{
    mmk.update(draw);

    return 0;
}

```  
</details>
	
### Bouncing Balls Screensaver 
<img src="https://i.imgur.com/TsoSPBT.gif" width="35%">
<details>
<summary>Code snippet</summary>  
    
```c++
#include "Memake/Memake.h"
#include <math.h>

Memake mmk(800, 800, "memake");

using namespace std;

class Ball {
    public:
        int x, y, r;
        int dx = 1, dy = 1;

        Ball(int _x, int _y, int _r) {
            x = _x;
            y = _y;
            r = _r;
        }

        void update() {
            draw();
            checkClamp();
            move();
        }

        void draw() {
            mmk.drawCircle(x, y, r, Colmake.beige);
        }

        void checkCollision(Ball &b) {
            int distX = x - b.x;
            int distY = y - b.y;

            float distance = sqrt((distX * distX) + (distY * distY));

            if (distance < r + b.r) {
                dx *= -1;
                dy *= -1;
            }
        }

        void move() {
            x += dx;
            y += dy;
        }

        void checkClamp() {
            if (x <= 0 || x >= mmk.getScreenW()) {
                dx *= -1;
            }
            if (y <= 0 || y >= mmk.getScreenH()) {
                dy *= -1;
            }
        }

};

int main()
{
    int numOfBall = 24;
    Ball b[] = {
        Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10),
        Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10),
        Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10),
        Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10),
	Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10), 
	Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10),
        Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10),
        Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10), Ball(random(0, 800), random(0, 800), 10),
        Ball(random(0, 800), random(0, 800), 10)
    };

    mmk.update([&](){
        for (int i = 0; i < numOfBall; i++) {
            for (int j = 0; j < numOfBall; j++) {
                // check collision between one ball to others, but don't check collision to itself
                if (j != i) {
                    b[i].checkCollision(b[j]);
                }
            }
            b[i].update();  // update/move every ball
        }

        mmk.delay(2);
    });

    return 0;
}
```  
</details>	

