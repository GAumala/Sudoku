# Proposal

A clock puzzle is game in which a clock has random numbers as the face value.
The goal is to find a path across every face value only once. From any position,
the only valid movements are n positions clockwise, or n positions counter
clockwise where n is the face value of the current position.

The clock puzzle is essentially a Hamiltonian path problem where every node has
at most 2 links away from it. This feature reduces the complexity of the problem
significantly.

The proposed solution consists in modeling the problem with binary search tree
and searching with a depth first algorithm. This approach is complete, it will find
every solution to any given puzzle, but it will be slow, because it is a blind
search without heuristics. this algorithm is estimated to be O(2^n).

# Dependencies

On a UNIX-like system you need to have installed:

- gcc (GNU Collection Compiler)
- glib 2.0 (Utility library from GNOME)

# Build

Clone this repo and then use `make` to build. The executable file is `main`.

```
make
./main
```

# Testing

You can build a program that tests our functions using assert.h like this:

```
make test
./test
```
