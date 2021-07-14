#include "Memake/Memake.h"
// use winuser.h with GetAsyncKeyState on windows

Memake mmk(800, 800, "memake");

int i = 50;

void draw()
{
    /// Drawing Method
    mmk.drawRect(300, 600, i, 70, Colmake.red);
    mmk.drawCircle(500, 300, 90, Colmake.darkslategray);
    mmk.drawLine(550, 590, 590, 600, Colmake.azure);
    mmk.drawEllipse(100, 500, 90, 20, Colmake.purple);
    mmk.drawDot(600, 60, Colmake.yellowgreen);
    mmk.drawTriangle(50, 80, 60, 50, 90, 100, Colmake.yellow);
    mmk.drawTrapezoid(700, 695, 720, 650, 780, 644, 740, 740, Colmake.aquamarine);

    Vec2 a[] = {{140, 140}, {150, 130}, {120, 120}, {180, 120}, {200, 180}, {130, 240}};
    Color newColorTest = mmk.generateColor(204, 252, 203);
    mmk.drawPolygon(a, 6, newColorTest);

    /// Keyboard Input
    if (mmk.getKeyboardInput('a')) {
        std::cout << "Yuza is cool" << std::endl;
    } if (mmk.getKeyboardInput('e')) {
        mmk.close();
    }

    /// Mouse Input
    cout << mmk.getMousePosX() << " , " << mmk.getMousePosY() << endl;

    /// GET DELTA TIME
    std::cout << "deltatime: " << mmk.getDeltaTime() << std::endl;

    /// DELAY
    mmk.delay(1);
}

int main()
{
    /// Vector Utils
    Vec2 a = {2, 4};
    Vec2 b = {5, 2};
    Vec2 c = a + b;

    float length = c.GetLength();
    Vec2 normalize = c.GetNormalized();

    std::cout << c.x << std::endl;
    std::cout << c.y << std::endl;

    std::cout << length << std::endl;

    std::cout << normalize.x << std::endl;
    std::cout << normalize.y << std::endl;

    /// Memake Game Event
    mmk.update(draw);

    return 0;
}
