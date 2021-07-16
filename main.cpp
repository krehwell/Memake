#include "Memake/Memake.h"

Memake mmk(800, 800, "memake");

using namespace std;

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

    Vector2 a[] = {{140, 140}, {150, 130}, {120, 120}, {180, 120}, {200, 180}, {130, 240}};
    Color newColorTest = mmk.generateColor(204, 252, 203);
    mmk.drawPolygon(a, 6, newColorTest);

    mmk.drawPolkadot(200, 500, 250, 590);
    mmk.drawFlower(80, 700, 50, 30, Colmake.coral, Colmake.cornsilk);

    /// Keyboard Input
    /// for win user: use winuser.h with GetAsyncKeyState on windows is better in my opinion
    if (mmk.getKeyboardInput('a')) {
        i++;
    } if (mmk.getKeyboardInput('e')) {
        i--;
    }

    /// Mouse Input
    // cout << mmk.getMousePosX() << " , " << mmk.getMousePosY() << endl;

    /// Get Delta Time
    // std::cout << "deltatime: " << mmk.getDeltaTime() << std::endl;

    /// Delay
    mmk.delay(60);
}

int main()
{
    /// Vector Utils
    Vector2 a = {2, 4};
    Vector2 b = {5, 2};
    Vector2 c = a + b;

    float length = c.GetLength();
    Vector2 normalize = c.GetNormalized();

    std::cout << c.x << std::endl;
    std::cout << c.y << std::endl;

    std::cout << length << std::endl;

    std::cout << normalize.x << std::endl;
    std::cout << normalize.y << std::endl;

    /// Memake Game Event
    mmk.update(draw);

    return 0;
}
