# C++ code I used in different projects

This library contains some things I found myself implementing repeatedly while working at ACRO.

![CMake](https://github.com/JeroenDM/acrolib_cpp/workflows/CMake/badge.svg)

## Installation (tested on Ubuntu 18.04 LTS)

Clone this repository in a folder where you like to keep applications.
```bash
git clone https://github.com/JeroenDM/acrolib_cpp.git
cd acrolib_cpp
```

Create a build directory and do the standard cmake stuff.
```
mkdir build
cd build
cmake ..
make
```

Now you can uses the build version, or install the library on system level:
```bash
make install
```

You can find the specific files that where installed in `install_manifest.txt`. This same file can be used to [uninstall](https://stackoverflow.com/questions/41471620/cmake-support-make-uninstall) the library.
```bash
xargs rm < install_manifest.txt
```
It is possible that you need to run the install and uninstall commands with `sudo`.
