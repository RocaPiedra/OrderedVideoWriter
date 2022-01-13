# OrderedVideoWriter
Simple C++ code to create video from a folder of images. The images are ordered using the std::sort function, it is perfect for common names as XXX_0001.jpg. The video is created using OpenCV's function VideoWriter. Tested for C++ >= 14.

Requirements: 
* OpenCV <br />
* C++ compiler <br />
* [Optional] CMake (you can compile it however you want but CMakeLists is provided to make it easy) <br />

# Steps to use code:
Git clone the repo in the folder of your choice. <br />
Go to the folder path and follow this steps to create an executable: <br />
`mkdir build` <br />
`cd build` <br /> 
`cmake ..` <br />
`make` <br />
Now, the executable is ready in the build folder to launch under the name defined in the CMakeLists, launch it in Linux using: <br />
`./orderedWriter` <br />
