Givt-toekenning
===============

This application can generate a csv formatted file to be used to upload assignment of income to a purpose in the Givt dashboard.

usage
-----

First create the application, start by installing [mcfp](https://github.com/mhekkel/mcfp.git) and [date](https://github.com/HowardHinnant/date.git). You also need of course [CMake](https://cmake.org/) and a recent C++ compiler.

Once these requirements are met, building the application is as simple as:

```console
git clone https://github.com/mhekkel/givt-toekenning.git
cd givt-toekenning
cmake -S . -B build
cmake --build build
```

The result is an application called givt-toekenning in the folder build. Using the --help option will give you:

```console
build/givt-toekenning --help
Gebruik: givt-toekenning [option]

  -h [ --help ]                Toon deze help tekst
  --jaar arg (=2024)           Het jaar voor de toekenning
  --aantal-collectes arg (=3)  Het aantal collectes per weer
```

So, the options are --jaar that takes a year and --aantal-collectes that takes a number with a practical maximum of 3.

Output is to stdout, so you have to redirect output to get a file:

```console
build/givt-toekenning --jaar 2024 > givt-2024.csv
```