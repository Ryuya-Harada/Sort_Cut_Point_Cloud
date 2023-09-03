
# Point Cloud Sort and Cut Attribute
## Requirements

- g++ (tested 9.4)
- CMake 3.2 (tested 3.27)
- Boost (tested 1.82.0)

## Build
Linux
```bash
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make
```
or
```bash
$ ./build.sh
```

## Usage
Linux
```bash
~/build$ ./cpp_cmake -i path/to/input_file -s -c
```
Help
```bahs
~/build$ ./cpp_cmake -h
```