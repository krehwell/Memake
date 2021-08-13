#define SDL_MAIN_HANDLED

#include "Memake/Memake.h"
#include <math.h>

// RAII - Testing
#include "Memake/Timer.h"

Memake mmk(1500, 1000, "memake");

using namespace std;

class Ball {
    public:
        Ball(){}
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
                if (random(0,1)) {
                    dy *= -1;
                } else {
                    dx *= -1;
                }
            }
        }

        void move() {
            x += dx;
            y += dy;
        }

        void checkClamp() {
            if (x <= 0 || x >= mmk.getScreenW()) {
                if (random(0,1)) {
                    dy *= -1;
                } else {
                    dx *= -1;
                }
            }

            if (y <= 0 || y >= mmk.getScreenH()) {
                if (random(0,1)) {
                    dy *= -1;
                } else {
                    dx *= -1;
                }
            }
        }

};

int main()
{
    int numOfBall = 2000;
    Ball b[numOfBall];

    // generate ball to total X numOfBall
    for (int i = 0; i < numOfBall; i++) {
        b[i] = Ball(random(0, mmk.getScreenW()), random(0, mmk.getScreenH()), 2);
    }

    // animate ball
    mmk.update([&](){
        {
            Timer timer;

            for (int i = 0; i < numOfBall; i++) {
                for (int j = 0; j < numOfBall; j++) {
                    // check collision, but don't check collision to itself
                    if (j != i) {
                        b[i].checkCollision(b[j]);
                    }
                }
                b[i].update();
            }
        }

        cout << "one frame has ended" << endl << endl;
    });

    return 0;
}
