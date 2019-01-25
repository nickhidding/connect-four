# Connect Four

Connect Four build with C++ using CMake

## Build on Ubuntu 18.04 LTS

Required packages:
* libgtk-3-dev
* cmake

```
g++ *.cpp -o build -I`pkg-config --cflags --libs gtk+-3.0` && ./build
```

```
cmake . && make && ./Main
```

### Run tests

```
cd test
cmake . && make && ./runTests
```

## Build on Windows 10 (incomplete)

1. Install [MSYS2](https://www.msys2.org/)
2. Update with `pacman -Syuu`
3. Install Git, nano, etc. `pacman -S git nano cmake`
4. Install GTK3 `pacman -S mingw-w64-x86_64-gtk3`
5. Clone Git repository & unpack
6. Enter directory `cd /c/path/to/unpacked/files/connect-four/`
7. Run Cmake `cmake . -G "MSYS Makefiles"`
8. Build & Run `make && ConnectFour.exe`
