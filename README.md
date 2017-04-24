# msdpfs

**msdpfs** is a **Max 7** (Cycling74) external used by 
[Music_SDP](http://musicsdp.com/) for basic file services (e.g. cp, exists, 
mkdir, and rm). The Quickstart section below provides step-by-step instructions
for **MacOS** and **Windows** to compile, link, and install this external for
**Max 7**. It uses Cycling74's [max-devkit](https://github.com/Cycling74/max-devkit) 
for C++ and [CMake](https://cmake.org/download/) for build automation.

For your convenience, pre-compiled binaries are also available in the project 
**Releases** menubar. Add them to your **Max 7** file path via the 
**Options**, **File Preferences...** menu.

Using the **msdpfs** external whether you install the pre-compiled binary or
build it via the **Quickstart** below is simple -- add a **[msdpfs]** object 
to your patcher, then connect message objects with the appropriate argument 
symbols for your desired result. Refer to the project help patcher for examples 
of each of the behaviors for **MacOS** and **Windows** -- here's a screenshot.

![msdpfs usage](https://cloud.githubusercontent.com/assets/52076/25161907/a90dbbf8-248c-11e7-9352-0367c25de4bd.png)

**msdpfs** Behaviors/Rules:

Everything supports standard **MacOS**/**Windows** and **Max 7** path-oriented naming
conventions.

* cp - copy a file from source to destination with override
* exists - check to see if a file or directory exists
* mkdir - create a new directory where it doesn't exist
* rm - delete file or directory if allowed and it exists

All **msdpfs** requests respond to message input, sending 1 for success, 
and 0 for failure as object output, with failure details sent to the **Max Console**.


## Quickstart:

Complete the following steps for your preferred **MacOS** or **Windows** platform.


## MacOS:

Build and install a **MacOS** compatible 64-bit external as follows:

* download and install the latest version of **Xcode** along with the CLI tools 
from the **Apple App Store**
* download and install [CMake](https://cmake.org/download/) binary for MacOS, 
then run it and click on the **Tools** menu, then click the 
**How to Install For Command Line Use** submenu and follow along to expose 
from the shell/teminal
* clone/download Cycling74 [max-devkit](https://github.com/Cycling74/max-devkit), 
untar if downloaded, rename resulting directory to "max-devkit"
* clone/download Cycling74 [max-api](https://github.com/Cycling74/max-api)
subproject, untar if downloaded, rename it as "max-api", and move it to 
the **max-devkit\source** directory
* change directory to **max-devkit**
* create build directory: **mkdir build**
* add this repo to the demos projects directory: **cd ../source/projects**, 
clone/download [this project](https://github.com/dirkleas/msdpfs.git), untar if 
downloaded, rename resulting directory to "msdpfs"
* return to the build directory and build the external binary:
**cd ../../build && cmake .. && cmake --build .**
* add **max-devkit** directory to your **Max 7** path via 
**Options**, **File Preferences...** menu
* test the external with the included **msdpfs** help patcher **msdpfs.maxhelp**


## Windows:

Build and install a **Windows** compatible 64-bit external as follows:

* download and install the latest free version of 
[Visual Studio Community](https://www.visualstudio.com/downloads/)
* download and install [CMake](https://cmake.org/download/) binary for Windows
* clone/download Cycling74 [max-devkit](https://github.com/Cycling74/max-devkit), 
untar if downloaded, rename resulting directory to "max-devkit"
* clone/download Cycling74 [max-api](https://github.com/Cycling74/max-api)
subproject, untar if downloaded, rename it as "max-api", and move it to 
the **max-devkit\source** directory
* change directory to **max-devkit**
* create build directory: **mkdir build**
* add this repo to the demos projects directory: **cd ../source/projects**, 
clone/download [this project](https://github.com/dirkleas/msdpfs.git), unzip if 
downloaded, rename resulting directory to "msdpfs"
* return to the build directory and build the external binary:
```
     cd ../../build
     cmake -G "Visual Studio 15 2017 Win64" -DWIN64:Bool=True  ..
     cmake --build . --config Release
```
* add **max-devkit** directory to your **Max 7** path via 
**Options**, **File Preferences...** menu
* test the external with the included **msdpfs** help patcher **msdpfs.maxhelp**


## ToDo:

Unprioritized toDo items:

* security/vulnerability/reliability peer review, and more peer review
* verify general/edge file I/O behaviors
* enhance **msdpfs** help patcher, refactor other UX aspects based on feedback

--

Feel free to submit issues or pull requests for this project through the 
associated tabs above. 
[Feedback/suggestions](http://musicsdp.com/contact-the-team/) is also greatly 
appreciated. 

[[[[Enjoy!]joy!]oy!]!]
