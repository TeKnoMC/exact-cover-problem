# exact-cover-problem
Implementing Knuth's Algorithm X to solve polynomino/polycube tiling problems.

## Description
A module to solve the exact cover problem for a given constraint.

Given a collection S containing subsets of a set X, find a
subcollection S* such that the elements of S* include all
elements of X only once.

E.g.:
```
X = {1, 2, 3, 4, 5}

S = {A, B, C, D, E}
A = {1, 3}
B = {2, 4}
C = {2, 3}
D = {5}
E = {1, 5}
```

With these constraints, `S* = {A, B, D}`
(`{1, 3} + {2, 4} + {5} = {1, 2, 3, 4, 5} = X`)

Donald Knuth proposed an algorithm for solving this problem - Algorithm X.

To prepare for Algorithm X, the problem is converted into an incidence matrix:

|   | 1 | 2 | 3 | 4 | 5 |
| - | - | - | - | - | - |
| A | 1 | 0 | 1 | 0 | 0 |
| B | 0 | 1 | 0 | 1 | 0 |
| C | 0 | 1 | 1 | 0 | 0 |
| D | 0 | 0 | 0 | 0 | 1 |
| E | 1 | 0 | 0 | 0 | 1 |

Algorithm X works by performing a depth-first search on a solution tree,
where each walk down a branch of the tree chooses a row (selecting a subset
for part of the solution) and removes the columns where that row has a 1
in, as well as other rows that have 1s in the columns to be removed.

E.g., by selecting A, the matrix can be reduced by removing rows A, C, and
E, as well as columns 1 and 5:

|   | 2 | 4 | 5 |
| - | - | - | - |
| B | 1 | 1 | 0 |
| D | 0 | 0 | 1 |

The algorithm repeats, selecting row B and finally row D, finding the
solution S* = {A, B, D}

If the chosen subsets don't result in a solution, the algorithm rewinds back
up the solution tree and selects any other available subsets, recursing
until a solution is found.
