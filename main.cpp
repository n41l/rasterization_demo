#include <iostream>
#include "math.h"
#include "line.h"

int main() {

    const int imageWidth = 512, imageHeight = 512;
    Color image[imageWidth][imageHeight];


    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j) {
        for (int i = 0; i < imageWidth; ++i) {
            image[i][j] = Color(0, 0, 0);
        }
    }
    Line l = Line(Vec2<int>(40, 40), Vec2<int>(200, 120));
    Line l2 = Line(Vec2<int>(40, 40), Vec2<int>(120, 200));
    Line l3 = Line(Vec2<int>(40, 40), Vec2<int>(120, 0));
    Line l4 = Line(Vec2<int>(40, 40), Vec2<int>(0, 120));
    l.draw<imageWidth, imageHeight>(image);
    l2.draw<imageWidth, imageHeight>(image);
    l3.draw<imageWidth, imageHeight>(image);
    l4.draw<imageWidth, imageHeight>(image);

    for (int j = imageHeight - 1; j >= 0; --j) {
        for (int i = 0; i < imageWidth; ++i) {
            std::cout << static_cast<int>(255.999 * image[i][j].x()) << ' '
                << static_cast<int>(255.999 * image[i][j].y()) << ' '
                << static_cast<int>(255.999 * image[i][j].z()) << '\n';
        }
    }

    std::cerr << "\nDone.\n";
    return 0;
}
