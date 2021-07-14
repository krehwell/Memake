#include "Memake/Memake.h"

Memake mmk(800, 800, "memake");

void draw()
{
    // mmk.DrawCircle(40, 50, 50, Colmake.azure);
    mmk.drawRect(300, 600, 20, 70, Colmake.red);
    mmk.drawCircle(500, 300, 90, Colmake.darkslategray);
    mmk.drawLine(550, 590, 590, 600, Colmake.azure);
    mmk.drawEllipse(100, 500, 90, 20, Colmake.purple);
    mmk.drawDot(600, 60, Colmake.yellowgreen);
    mmk.drawTriangle(50, 80, 60, 50, 90, 100, Colmake.yellow);
    mmk.drawTrapezoid(700, 695, 720, 650, 780, 644, 740, 740, Colmake.aquamarine);

    Vec2 a[] = {{140, 140}, {150, 130}, {120, 120}, {180, 120}, {200, 180}, {130, 240}};
    Color newColorTest = mmk.generateColor(204, 252, 203);
    mmk.drawPolygon(a, 6, newColorTest);

    // cout << mmk.GetMousePosX() << " , " << mmk.GetMousePosY() << endl;
}

int main()
{
    // vector utils testing
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

    mmk.Update(draw);

    return 0;
}
