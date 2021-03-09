#include <iostream>
#include "ppm_image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
    ppm_image image1;
    image1.load("../images/earth-ascii.ppm");

    ppm_image image2;
    image2.load("../images/earth-ascii.ppm");

    ppm_image grayscale = image1.grayscale();
    ppm_image inverted = image2.invert();

    grayscale.save("gs.ppm");
    inverted.save("invr.ppm");

    ppm_image collageH;
    collageH = grayscale.collageHorizontal(inverted);

    ppm_image collageV;
    collageV = grayscale.collageVertical(inverted);

    collageV.save("collageV.ppm");
    collageH.save("collageH.ppm");

}

