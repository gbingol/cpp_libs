# Generate new cpp project

### Inspired by Rust's cargo tool, this is a simple command-line tool to quickly generate a C++ project directory.

&nbsp;

```sh
cppmngr --new myproject
```

Generates *myproject* folder with:
- .git folder and  .gitignore file, 
- CMakeLists.txt 
- main.cpp.  

If *vcpkg* is already installed on the system, also runs `vcpkg new --application`



&nbsp;

## Requirements
 Requires C++17 or higher.