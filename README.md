# Random Graph Generators

A collection of graph generators.

## Dependencies:

For `C++`:

- `CMake` and `Boost` Libraries. `g++` compiler is recommended. `C++ Standard` >=11

For `Python`:

- `Pandas`, `Numpy` and `Matplotlib`.
- `Python >= 3.8.0`

For `Docker`:

- You need `Docker`.

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
python3 scripts/auto_generate.py n k 
```

where `n` and `k` are the numbers of valid degree sequences and invalid degree sequences respectively,to be generated.

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

## Docker(Easiest Way)

There is a `dockerfile` for containerized version of the program with all necessary dependencies.

Change your directory to the project folder and run

```asm
docker build . --build-arg valid_inputs=N --build-arg invalid_inputs=K -t rgg:latest
```

Where `N` is the number of valid inputs and `K` is the number of invalid inputs. After you build the image, start the
image and attach to it by running

```asm
docker run -it rgg:latest
```

After that you will be greeted in a containerized environment. You can find the inputs and outputs under `./feeds/in`
and`./feeds/out` respectively.

## TODO

- [x] Havel-Hakimi Generator.
- [x] Documentation
- [x] Code Commenting
- [x] Sequential Algorithm Implementation
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
