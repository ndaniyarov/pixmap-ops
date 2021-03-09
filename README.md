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
resize(int w, int h)

![earth-200-300](https://user-images.githubusercontent.com/55757317/110421454-8cfa4500-806b-11eb-957f-bef2d802d800.jpg)

flip_horizontal()

![earth-flip](https://user-images.githubusercontent.com/55757317/110421470-95528000-806b-11eb-8493-0d057d42a4fa.jpg)

subimage(int startx, int starty, int w, int h)

![earth-subimage](https://user-images.githubusercontent.com/55757317/110421585-cb8fff80-806b-11eb-9b7b-ca13d90c364f.jpg)

replace(const ppm_image& image, int startx, int starty)
alpha_blend(const ppm_image& other, float alpha)
gammaCorrect(float gamma)

![earth-gamma-0 6](https://user-images.githubusercontent.com/55757317/110421498-a0a5ab80-806b-11eb-99e3-2a040b477f7b.jpg)![earth-gamma-2 2](https://user-images.githubusercontent.com/55757317/110421537-b3b87b80-806b-11eb-87df-3ddb222ba712.jpg)

grayscale()

![earth-grayscale](https://user-images.githubusercontent.com/55757317/110421562-be731080-806b-11eb-8528-a61b9e2a8901.jpg)

invert()

![invert](https://user-images.githubusercontent.com/55757317/110421604-d6e32b00-806b-11eb-8339-bd557e049cfe.jpg)

swirl()

![swirl](https://user-images.githubusercontent.com/55757317/110421613-dea2cf80-806b-11eb-86ef-bc75cc5dba68.jpg)

border(ppm_oixel bord)

![border](https://user-images.githubusercontent.com/55757317/110421398-6fc57680-806b-11eb-90e3-7163a17b66be.jpg)

collageVertical(ppm_image img)

![collageWithASwirl](https://user-images.githubusercontent.com/55757317/110421437-84097380-806b-11eb-8fdd-e5e3719e126e.jpg)

collageHorizontal(ppm_image img)

![sum](https://user-images.githubusercontent.com/55757317/110421971-7c969a00-806c-11eb-92b9-6a37c028dda8.jpg)

sum(ppm_image img)

![collageH](https://user-images.githubusercontent.com/55757317/110421959-77394f80-806c-11eb-9191-045dc19be76d.jpg)

attempts:
difference(ppm_image img)

![lightest](https://user-images.githubusercontent.com/55757317/110422176-d4350580-806c-11eb-8f4b-379fd824a029.jpg)

lightest(ppm_image)

![difference](https://user-images.githubusercontent.com/55757317/110422150-c8e1da00-806c-11eb-82cc-d865c72247f2.jpg)

## Results
![collageV](https://user-images.githubusercontent.com/55757317/110420202-db5a1480-8068-11eb-8058-cfb70792f3da.jpg)

My original idea was to make a collage of my cat, however, for some reason, my photos were not readible by a file so I used the photos provided. The artwork that I created in the pixmap_art.ppm was a file collageV.ppm. I combined grayscale, invert and collage filters to make earth look like two completely different planets.

