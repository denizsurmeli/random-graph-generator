# Random Graph Generators

A collection of graph generators.

## TODO

- [ ] Documentation
- [x] Code Commenting
- [x] Sequential Algorithm Implementation
- [x] Benchmark CSV Exporter
- [ ] Recursive version of the Havel-Hakimi Generator
- [x] Better CLI Scripts
- [x] Easy builder and runner scripts
- [x] Pairing Model Generator
- [x] Havel-Hakimi Generator
- [x] Graphviz Generator(Built-in Boost Libraries)
- [x] Input Generator
- [x] Input Reader
- [x] Output Writer(Partial Implemented, need better version)
- [x] CMake Config

## Dependencies:

For C++:

- CMake and Boost Libraries. C++ Standard >=11

For Python:

- Pandas and Matplotlib.

## Usage

### On Unix/Mac:

On the project folder, change your directory to scripts.

```
python3 run.py n
```

where n is the number of inputs you want it to generate. It automatically handles the rest.

# On Windows, Manual Build

Generate the inputs by using `scripts/auto_generate.py`. On the project folder, make a new directory called `build` and
go into it. After that run the command:

```
cmake ../. && cmake --build ."
```

Then execute the program on the `build` folder by running:

```
./rgg "./feeds/in"
```

The project is fully `CLion` compatible.