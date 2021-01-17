# diffusion-image-segmentation
Build and run for Windows 10:

0. [Download](https://sourceforge.net/projects/opencvlibrary/files/opencv-win/) prebuild opencv library  
1. In the root folder run ```mkdir build && cd build```
2. Move **opencv\build** to **build** folder in project
3. run ```cmake ..```
4. run ```cmake --build . --config Release```
5. Move **opencv\build\x64\vc15\bin\opencv_world451.dll** to **build\Release**
