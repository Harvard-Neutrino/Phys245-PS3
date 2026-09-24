# Phys245-PS3 — GEANT4 examples for Physics 245 Problem Set 3

Two independent GEANT4 applications:

- **`B1/`** — the standard GEANT4 basic example B1, unmodified (from GEANT4
  v11.4.2). Build and run this first to verify your GEANT4 installation.
- **repository root** — `examplePS3`, a toy calorimeter (5 m x 5 m x 10 m of
  liquid argon by default) based on example B1. Originally by Brendon Bullard;
  adapted by Laura Bruce for Fall 2025. This is the simulation used in the
  problem set.

## Prerequisites

A conda environment with GEANT4 (Qt build) and the development packages needed
to compile against it:

```bash
conda config --add channels conda-forge
conda config --set channel_priority strict
conda install "geant4=*=qt_*" cmake zlib freetype
```

Set these before configuring (in every new shell):

```bash
export CMAKE_PREFIX_PATH=$CONDA_PREFIX
export CMAKE_INCLUDE_PATH=$CONDA_PREFIX/include
export CMAKE_LIBRARY_PATH=$CONDA_PREFIX/lib
export HDF5_ROOT=$CONDA_PREFIX
```

## Build and run

Example B1 (installation check):

```bash
cd B1
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=$CONDA_PREFIX
make
./exampleB1
```

Toy calorimeter:

```bash
cd ../..           # back to the repository root
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=$CONDA_PREFIX
make
./examplePS3       # interactive (GUI); or ./examplePS3 run.mac for batch
```

Each run writes `output_default.root` containing two ntuples: `edep`
(per-event total energy deposit, GeV) and `showerEDep` (per-step deposits with
positions: E in GeV, z/r/x/y in cm, z measured from the front face where the
particle gun sits). Rename the output file between runs so it is not
overwritten.

See the Physics 245 Problem Set 3 handout for full installation instructions
(including Windows/WSL) and the assignment itself.
