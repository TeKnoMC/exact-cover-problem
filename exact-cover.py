"""A module to solve the exact cover problem for a given constraint.

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
"""

from typing import Dict, Set


DancingLinksMatrix = Dict[int, Set[str]]


def algorithm_x(matrix: DancingLinksMatrix, partial_solution: Set[str] = set(), discarded_rows: Set[str] = set()):
    """Solve the exact cover problem using Knuth's algorithm X."""

    #print(f"Matrix: {matrix}")
    #print(f"Part sol: {partial_solution}")

    # Recursion exit clause
    if len(matrix) == 0:
        return partial_solution

    

    # Get c with fewest elements
    smallestC, _ = min(matrix.items(), key=lambda t: len(t[1]))

    #print(f"  chosen column = {smallestC} - {matrix[smallestC]}")

    # Choose r - add to partial solution (for every possibly choice r)
    for r in matrix[smallestC]:
        removed_cols = {}
        removed_rows = set()

        # Ignore discarded rows
        #print(f"Trying {r}")
        if r in discarded_rows:
            #print("scratch that; discarded")
            continue

        rowsToRemove = matrix[smallestC]

        # Delete every column that shares the selected row
        for i in list(matrix.keys()):
            if r in matrix[i]:
                removed_cols[i] = matrix.pop(i)
                removed_rows |= removed_cols[i]
        
        #print(f"  all discarded rows={discarded_rows | removed_rows}")

        # Recurse - add row to partial solution
        potential_solution = algorithm_x(matrix, partial_solution | {r}, discarded_rows | removed_rows)
        if potential_solution is not None:
            return potential_solution

        # Undo column deletion
        for i in list(removed_cols.keys()):
            matrix[i] = removed_cols.pop(i)
    
    #print("nope - backtrack")
    return None


def main():
    # This works for performing dancing links operations (in a sense).
    # Columns (1, 2, ...) can be removed and inserted back easily (order
    # can be interpreted from idx easily).
    # Rows (elements with the same name are in the same row - 'A', 'B', ...)
    # can be discarded by having a discard list, which can be used to tell if
    # a row should be considered by the algorithm.

    matrix = {
        1: {'A', 'B'},
        2: {'E', 'F'},
        3: {'D', 'E'},
        4: {'A', 'B', 'C'},
        5: {'C', 'D'},
        6: {'D', 'E'},
        7: {'A', 'C', 'E', 'F'}
    }

    print(algorithm_x(matrix))

    matrix = {
        1: {'A', 'B'},
        2: {'B', 'F'},
        3: {'D', 'E'},
        4: {'A', 'B', 'C'},
        5: {'C', 'D'},
        6: {'D', 'E'},
        7: {'A', 'C', 'E'}
    }

    print(algorithm_x(matrix))


if __name__ == "__main__":
    main()