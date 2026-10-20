# Vector Calculator
Vector Calculator is an interactive command line calculator for simple vector calculations. It has a dynamic internal storage to store any number of vectors, as well as save and load them from csv files.

# Build
Build the program using the provided Makefile.

```
$make
```

# Run
To start Vector Calculator, simply run the created executable.

### Optional Arguments
```
--help
    Displays the help screen for running and interacting with Vector Calcultor
```

# Usage
Initializing a vector
```
> a = 1 2 3
> b = 2 2 2
```
Adding vectors
```
> a + b
3 4 5
```
Subtracting vectors
```
> a - b
-1 0 1
```
Multiplying vector with a scalar
```
> a * 2
2 4 6
```
All operations can be assigned to a new vector
```
> c = a + b
3 4 5
> c
3 4 5
```
Listing stored vectors
```
> list
a: 1 2 3
b: 2 2 2
c: 3 4 5
```
Clearing stored vectors
```
> clear
```
Loading vectors from csv
```
> load src/file.csv
loaded n vectors
```
Saving vectors to `vectors.csv`
```
> save
```
Quitting program
```
> quit
```

# Dynamic Memory
This program uses dynamically allocated memory to store a practically unlimited numbers of vectors. This is implemented through a linked list struct that stores vector information and points to the next and previous vector links. When a vector is added, we crawl to the end of list (`next == NULL`) and assign next to the pointer for the new link struct.