# pixmap-ops

Image manipulation demos based on the PPM image format.

TODO: Add a representative image for your project here

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake -G "Visual Studio 17 2022" ..
pixmap-ops/build $ start pixmap-ops.sln
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

Darkest:

![darkest](https://user-images.githubusercontent.com/60118290/217980704-cccf3b1a-99b0-46ee-a607-e82d75cf8916.png)

Extract:

![earth-no-blue](https://user-images.githubusercontent.com/60118290/217980810-55abbb40-2829-4da2-834b-9fd23fe0e7d5.png)

Multiply:

![earth-squared](https://user-images.githubusercontent.com/60118290/217980819-f85a8b2d-b8de-4179-85f6-7bb5c3c0cac3.png)

Lightest:

![lightest](https://user-images.githubusercontent.com/60118290/217980862-022e3d73-46f0-447b-99ce-18d100c94637.png)

Rotate90:

![rotate](https://user-images.githubusercontent.com/60118290/217980873-37c4755c-5a55-4106-b94c-9a34207f5aa4.png)

Invert:

![invert](https://user-images.githubusercontent.com/60118290/217980856-8e5ea2a1-05f8-4dff-ad94-63c3848104a7.png)
Swirl:
![earth-swirl](https://user-images.githubusercontent.com/60118290/217980830-824d3a37-9df7-4b64-8b85-260e0d24db47.png)

Flip-vertical:

![flip-vert](https://user-images.githubusercontent.com/60118290/217980850-7f622b07-0040-4ccc-b152-7e6fe72c54da.png)

## Results

Boup:

![boup](https://user-images.githubusercontent.com/60118290/217981918-85f74098-53c6-478c-8a67-82091688c8eb.png)
