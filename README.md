# msdpfs

**msdpfs** is a Max/MSP external used by [Music_SDP](http://musicsdp.com/) for 
basic file services (e.g. exists, cp, mkdir, and rm). The Quickstart section 
provides detailed walkthroughs for both **MacOS** and **Windows** for compiling and 
linking this repo with the 
[Cycling74 max-devkit](https://github.com/Cycling74/max-devkit) for C++ (this is 
replacement legacy [Max SDK](https://github.com/Cycling74/max-api) for C), and 
this repo's Max/MSP external **msdpfs** code for your specific platform. Recent 
binaries are available in the **externals** folder for your convenience. 
**max-devkit** uses [CMake](https://cmake.org/download/) for building externals.


## Quickstart:

Complete the following steps for your preferred **MacOS** or **Windows** platform.


## MacOS:

Build the **MacOS** external via the following:

* download and install the latest version of **Xcode** along with the CLI tools from 
the **Apple App Store**
* download and install [CMake](https://cmake.org/download/) binaries for MacOS
* clone/download [Cycling74 max-devkit](https://github.com/Cycling74/max-devkit) and untar
* change directory to resulting directory
* create build directory: **mkdir build; cd build**
* add this repo to the demos projects directory: **cd ../source/projects**, 
[clone/download](https://github.com/dirkleas/msdpfs.git) this project, rename if necessary 
to **msdpfs**
* return to the build directory and build the external binary:
**cd ../../build; cmake ..; cmake --build .**
* add **max-devkit** folder to your Max/MSP path via Options, File Preferences... menu
* test the external with the included **msdpfs** help patcher **msdpfs.maxhelp**


## Windows:

Build the **MacOS** external via the following:

* download and install the latest free version of 
[Visual Studio Community](https://www.visualstudio.com/downloads/)
* download and install [CMake](https://cmake.org/download/) binaries for MacOS
* clone/download [Cycling74 max-devkit](https://github.com/Cycling74/max-devkit) and untar
* change directory to resulting directory
* create build directory: **mkdir build; cd build**
* add this repo to the demos projects directory: **cd ../source/projects**, 
[clone/download](https://github.com/dirkleas/msdpfs.git) this project, rename if necessary 
to **msdpfs**
* return to the build directory and build the external binary:
```
     cd ../../build
     cmake -G "Visual Studio 15 2017 Win64" -DWIN64:Bool=True  ..
     cmake --build . --config Release
```
* add **max-devkit** folder to your Max/MSP path via Options, File Preferences... menu
* test the external with the included **msdpfs** help patcher **msdpfs.maxhelp**


## ToDo:

Unprioritized toDo items:

* complete Windows walkthrough (e.g. compile/link details)
* security/vulnerability/reliability peer review
* verify general/edge file I/O behaviors
* implement cross-platform CI
* enhance Max/MSP help file and consider reference, refactor other UX aspects 
based on feedback
* automate builds for both platforms

--

Feel free to submit pull requests, or submit feedback/suggestions 
[here](http://musicsdp.com/contact-the-team/). Enjoy!
