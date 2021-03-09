# pixmap-ops

Image manipulation demos based on the PPM image format.


![collageV](https://user-images.githubusercontent.com/55757317/110420202-db5a1480-8068-11eb-8058-cfb70792f3da.jpg)


## How to build

*Windows*

Open git bash to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake -G "Visual Studio 16 2019" ..
pixmap-ops/build $ start Pixmap-Ops.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell, 

```
pixmap-ops/build $ ../bin/Debug/pixmap_test
pixmap-ops/build $ ../bin/Debug/pixmap_art
```

*macOS*

Open terminal to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake ..
pixmap-ops/build $ make
```

To run each program from build, you would type

```
pixmap-ops/build $ ../bin/pixmap_test
pixmap-ops/build $ ../bin/pixmap_art
```

## Image operators
Unfortunately, I could not include ppm files here. However, all of them are available in the art folder.
resize(int w, int h)
flip_horizontal()
subimage(int startx, int starty, int w, int h)
replace(const ppm_image& image, int startx, int starty)
alpha_blend(const ppm_image& other, float alpha)
gammaCorrect(float gamma)
grayscale()

invert()
swirl()
border(ppm_oixel bord)
collageVertical(ppm_image img)
collageHorizontal(ppm_image img)
sum(ppm_image img)

attempts:
difference(ppm_image img)
lightest(ppm_image)


## Results

My original idea was to make a collage of my cat, however, for some reason, my photos were not readible by a file so I used the photos provided. The artwork that I created in the pixmap_art.ppm was a file collageV.ppm. I combined grayscale, invert and collage filters to make earth look like two completely different planets.

