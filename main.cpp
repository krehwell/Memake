#include "Memake.h"

Memake mmk(800, 800, "memake");

void draw()
{
    // mmk.DrawCircle(40, 50, 50, Colmake.azure);
    mmk.DrawRect(sexposx, sexposy, 20, 70, Colmake.red);
    mmk.DrawCircle(500, 300, 90, Colmake.blue);
    mmk.DrawLine(550, 590, 590, 600, Colmake.azure);
    mmk.DrawEllipse(100, 500, 90, 20, Colmake.purple);
    mmk.DrawDot(600, 60, Colmake.yellowgreen);
    mmk.DrawTriangle(50, 80, 60, 50, 90, 100, Colmake.yellow);
    mmk.DrawTrapezoid(700, 695, 720, 650, 780, 644, 740, 740, Colmake.aquamarine);

    Vec2 a[] = {{140, 140}, {150, 130}, {120, 120}, {180, 120}, {200, 180}, {130, 240}};
    Color newColorTest = mmk.GenerateColor(204, 252, 203);
    mmk.DrawPolygon(a, 6, newColorTest);
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
