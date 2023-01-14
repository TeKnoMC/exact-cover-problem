/**
 * Exact cover solver in C++.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <cinttypes>
#include <limits>


template <typename T>
struct MatrixNode {
    MatrixNode<T>* left;
    MatrixNode<T>* right;
    MatrixNode<T>* up;
    MatrixNode<T>* down;
    MatrixNode<T>* controlHeader;
    T value;

    // Control header fields
    size_t size;
    char name;
};


template <typename T>
class IncidenceMatrix {
    private:

    public:
        IncidenceMatrix(std::vector<std::vector<T>> initVals) {
            std::vector<MatrixNode<T>*> columnHeaders;
            MatrixNode<T>* h = new MatrixNode<T>();
            h->name = 'h';
            columnHeaders.push_back(h);

            MatrixNode<T>** currentHeader

            for (size_t i = 0; i < initVals.size(); i++) {
                MatrixNode<T>* columnHeader = new MatrixNode<T>();
                columnHeader->name = 'A' + i;
                columnHeader->size = initVals[i].size();
                columnHeaders.push_back(columnHeader);

                std::cout << columnHeaders[i]->name << "(" << columnHeaders[i]->size << "), ";
            }

            std::cout << std::endl;
        }

        size_t chooseSmallestColumn() {}

        void coverColumn() {

        }
};





void algorithmX(IncidenceMatrix<uint8_t> A) {
    // If A has no columns, soluition is valid - return

    // Choose a column c that has the fewest 1s in

    // Choose a row r that abides by constraints
    // Add row to partial solution
    // For each column with a 1 in the selected row
    //   For each row with a 1 in the column
    //      Remove row
    //   Remove column
    // Recurse on new matrix

    int minCol = 0;
}

int main() {
    std::vector<std::vector<uint8_t>> initVals {
        {1, 1},
        {1, 1, 1},
        {1}
    };
    IncidenceMatrix<uint8_t> m(initVals);

    return 0;
}