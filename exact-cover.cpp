/**
 * Exact cover solver in C++.
 */

#include <iostream>
#include <memory>
#include <cinttypes>

#include "doubly_linked_list.hpp"

void algorithmX() {
    
}

int main() {
    std::vector<uint8_t> values{1, 2, 5, 0, 7, 4, 12};
    DoublyLinkedList<uint8_t> ddl(values);

    ddl.print();
    DoublyLinkedNode<uint8_t>* node = ddl.cover(2);
    ddl.print();
    ddl.uncover(node);
    ddl.print();

    return 0;
}