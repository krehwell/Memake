#define SDL_MAIN_HANDLED

#include "Memake/Memake.h"

Memake mmk(800, 800, "memake");

using namespace std;

void draw()
{
    static int width = 50;

    /// Drawing Primitives
    mmk.drawCircle(400, 200, 90, Colmake.darkslategray);
    mmk.drawLine(550, 590, 590, 600, Colmake.azure);
    mmk.drawEllipse(100, 500, 90, 20, Colmake.purple);
    mmk.drawDot(400, 60, Colmake.yellowgreen);
    mmk.drawTriangle(50, 80, 60, 50, 90, 100, Colmake.yellow);
    mmk.drawTrapezoid(700, 695, 720, 650, 780, 644, 740, 740, Colmake.aquamarine);
    mmk.drawEllipseBorder(300, 400, 20, 60, Colmake.burlywood);
    mmk.drawRect(300, 600, width, 70, Colmake.red);

    /// Drawing Customs
    Vector2 polygon[] = {{140, 140}, {150, 130}, {120, 120}, {180, 120}, {200, 180}, {130, 240}};
    mmk.drawPolygon(polygon, 6, mmk.generateColor(204, 252, 203));
    mmk.drawPolkadot(400, 500, 450, 590);
    mmk.drawFlower(150, 650, 50, 50, Colmake.coral, Colmake.cornsilk);
    mmk.drawPaddle(200, 40, 50, 30, Colmake.darkcyan, Colmake.burlywood);
    mmk.drawRadar(700, 50, 20, 8, Colmake.darkred);
    mmk.drawFractalTree(700, 600, 70, 8, 90, 15, Colmake.cadetblue);

    /// Keyboard input
    switch(mmk.readKeyInput()) {
        case 'a':
            width--;
            break;
        case 'd':
            width++;
            break;
        case 's':
            mmk.setScreenBackgroundColor(Colmake.darkred);
            break;
    }
}

int main()
{
    /// Vector Utils
    Vector2 a = {2, 4};
    Vector2 b = {5, 2};
    Vector2 c = a + b;

    float length = c.getLength();
    Vector2 normalize = c.getNormalized();

    // std::cout << c.x << std::endl;
    // std::cout << c.y << std::endl;

    // std::cout << length << std::endl;

    // std::cout << normalize.x << std::endl;
    // std::cout << normalize.y << std::endl;

    /// Memake Game Event
    mmk.update(draw);

    return 0;
}
