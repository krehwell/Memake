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
![keyboard animation](https://i.imgur.com/TFwBkr5.gif)  
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
![keyboard animation](https://i.imgur.com/MTdYxTl.gif)
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
