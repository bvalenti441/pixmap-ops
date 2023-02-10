#include <iostream>
#include "image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
   // todo: make at least one artwork!
    Image image;
    image.load("../images/soup.png");
    image = image.grayscale();
    image = image.invert();
    image = image.gammaCorrect(0.1);
    image = image.flipVertical();
    image = image.flipHorizontal();
    image.save("boup.png");
}

