# Random Graph Generators

A collection of graph generators.

## Dependencies:

For `C++`:

- `CMake` and `Boost` Libraries. `g++` compiler is recommended. `C++ Standard` >=11

For `Python`:

- `Pandas`, `Numpy` and `Matplotlib`.
- `Python >= 3.8.0`

# Usage

### Single Phase Execution

You can use the script for generating inputs, compiling the source code and executing the inputs with benchmarks via
single script on `Unix` or `Mac`

On the project folder, change your directory to scripts.

```
python3 run.py n --generate --cleanup
```

where `n` is the number of inputs you want it to generate. It automatically handles the rest.

### Multiple Phase Manual Execution

In this setup, every phase executed manually and no plots will be generated.

Generate the inputs by using `scripts/auto_generate.py`.

```
python3 scripts/auto_generate.py n 
```

where `n` is the number of degree sequences to be generated.

On the project folder, make a new directory called `build` and go into it. After that run the command:

```
cmake ../. && cmake --build .
```

Then execute the program on the `build` folder by feeding the inputs:

```
./rgg "./feeds/in"
```

The project is fully `CLion` compatible. It's suggested for users to open the project with it in order to navigate and
execute easier.

## TODO

- [x] Havel-Hakimi Generator.
- [x] Documentation
- [x] Code Commenting
- [ ] ***URGENT*** Sequential Algorithm Implementation
- [x] Benchmark CSV Exporter
- [x] Better CLI Scripts
- [x] Easy builder and runner scripts
- [x] Pairing Model Generator
- [x] Havel-Hakimi Generator
- [x] Graphviz Generator(Built-in Boost Libraries)
- [x] Input Generator
- [x] Input Reader
- [x] Output Writer
- [x] CMake Config
