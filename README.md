odyssey

```sh
cd build
cmake ..
make
./odyssey
```

---

- use the current folder as the src dir, and generate the build files in the build folder

```sh
cmake -S . -B build && cmake --build build
```

**Class diagram generation**

```sh
clang-uml
plantuml -tsvg docs/diagrams/odyssey.puml
```
