# Bitcmp

This program is a simple linux application I made for one of my classes.

It compares two files and gives you the answer of how many bits are different between them.

# Build

To build the program just use `make` in your terminal. It's important to know that this program uses `getopt.h`, so it will not work on windows without additional tinkering.

# Usage

To execute the program type the following:
```
./bitcmp -f first_file -s second_file
```

The program will print how many bits of difference are there.
