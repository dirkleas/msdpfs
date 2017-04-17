# msdpfs

Max/MSP external for [Music_SDP](http://musicsdp.com/) w/ basic file services 
(e.g. exists, cp, mkdir, and rm). The Quickstart section provides detailed 
walkthroughs for both MacOS and Windows for compiling and linking this repo with the 
[Cycling74 max-devkit](https://github.com/Cycling74/max-devkit) for C++ (this is 
replacement legacy [Max SDK](https://github.com/Cycling74/max-api) for C), 
[Boost](http://www.boost.org/) C++ libraries, and this repo's Max/MSP external 
**msdpfs** code for your specific platform. Recent binaries are available in 
the **externals** folder for your convenience.

Low level file I/O is provided by **Boost** via it's **filesystem** library. 
**Quickstart** only builds dependent **Boost** libaries to minimize build time.


## Quickstart:

Complete the following steps for your preferred platform.


## MacOS:

Build **Boost** static libraries as **MacOS** universal binary format. This isn't 
documented by either **Cycling74** or the **Boost** guides. Changes from their
provided documentation incudes 1) BASH scripting for compiling universal binaries, 
and 2) an enhanced [CMake](https://cmake.org/download/) script integrating the two 
SDKs.

* download and install the latest version of **Xcode** along with the CLI tools from 
the **Apple App Store**
* download and install [CMake](https://cmake.org/download/) binaries for your MacOS
* download [Boost](http://www.boost.org/) and untar
* define environment variable for boost installation: **export BOOST_ROOT=[MY-BOOST-INSTALL-DIR]**
* change directory to resulting directory
* invoke the [following](https://tinyurl.com/mzhsghp) (thanks bruth) to generate 
the universal binaries for static linking with resulting binaries under 
**stage/lib**

```
    rm -rf i386 x86_64 universal &&  ./bootstrap.sh --with-toolset=clang --with-libraries=filesystem && ./b2 toolset=darwin -j8 address-model=32 architecture=x86 -a && mkdir -p i386 && cp stage/lib/*.dylib i386 && ./b2 toolset=clang -j8 cxxflags="-arch i386 -arch x86_64" -a && mkdir x86_64 && cp stage/lib/*.dylib x86_64 && mkdir universal && for dylib in i386/*; do lipo -create -arch i386 $dylib -arch x86_64 x86_64/$(basename $dylib) -output universal/$(basename $dylib); done
```

* download [Cycling74 max-devkit](https://github.com/Cycling74/max-devkit) and untar
* change directory to resulting directory
* create build directory: **mkdir build; cd build**
* add this repo to the demos projects directory: **cd ../source/projects**, clone 
[clone/download](https://github.com/dirkleas/msdpfs.git) project, ensure name is 
**msdpfs**
* return to the build direoctory and build the external binary: **cd ../../build; BOOST_ROOT=$BOOST_ROOT cmake ..; BOOST_ROOT=$BOOST_ROOT cmake --build .**
* add **max-devkit** folder to your Max/MSP path via Options, File Preferences... menu
* test the external with the included **msdpfs** help patcher **msdpfs.maxhelp**


## Windows:

Build **max-devkit** with **Boost** static libraries as 64-bit **Windows** binary
using a known, legacy version of [Visual Studio 12, 2013](https://tinyurl.com/qenh4bq)
and apply Update 5 patch from within IDE.
[CMake](https://cmake.org/download/) is used for compiling/linking the external.

* download install, and patch [Visual Studio 12, 2013](https://tinyurl.com/qenh4bq)
* download and install [CMake](https://cmake.org/download/) binaries for your MacOS
* download [Boost](http://www.boost.org/) and untar
* change directory to resulting directory
* **BOOST** complile/link: **.\b2 --prefix="c:/h4x/boost_1_63_0" --with-filesystem --build-type=complete**
* download [Cycling74 max-devkit](https://github.com/Cycling74/max-devkit) and untar
* change directory to resulting directory
* create build directory: **mkdir build; cd build**
* add this repo to the demos projects directory: **cd ../source/projects**, clone 
[clone/download](https://github.com/dirkleas/msdpfs.git) project, ensure name is 
**msdpfs**
* return to the build direoctory and build the external binary *** WARNING: STILL FAILS ***

```
     cd ../../build
     cmake -G "Visual Studio 12 Win64" -DWIN64:Bool=True  ..
     cmake --build . --config Release
```

* if build fails, try alernative cmake definition via this [gist](https://tinyurl.com/mb4to2j)
with additional logging/debugging enabled, edit any hard-coded **BOOST** directories 
based on your download directory -- replace existing **source/projects/msdpfs/CMakeLists.txt** 
and repeat **cmake** build steps above
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
