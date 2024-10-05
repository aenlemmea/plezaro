# CPP-Template

Begin by install clang, python3-dev, python3-pip, libc++-dev, cmake, ninja-build.

Edit the CMakeLists EXEC\_NAME to set the default executable name. Also set project() in CMakeLists.
Generate the makefiles (default, Unix Makefiles) with `./build.sh`

The script generates a `out` directory and copies the compile\_commands.json to the root directory for editor use. 
`cd out` then you can call `make` to generate the executable.

To quickly clean the generated cmake files, run `./build.sh clean` 


