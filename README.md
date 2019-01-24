# Connect Four

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

## Run tests

```
cd test
cmake . && make && ./runTests
```
