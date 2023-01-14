/**
 * Doubly-linked list with circular links.
 */

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H


#include <iostream>
#include <cstdio>
#include <memory>
#include <cinttypes>
#include <vector>
#include <cassert>


/**
 * Node element for the linked list
 */
template <typename T>
struct DoublyLinkedNode {
    DoublyLinkedNode<T>* left;
    DoublyLinkedNode<T>* right;
    T value;
};

template <typename T>
class DoublyLinkedList {
    private:
        DoublyLinkedNode<T>* start;
        DoublyLinkedNode<T>* end;

        size_t _size;

    public:
        DoublyLinkedList(std::vector<T> initValues) {
            assert(initValues.size() > 0);

            DoublyLinkedNode<T>** currentNode = &start;
            DoublyLinkedNode<T>* previousNode = nullptr;

            for (auto value : initValues) {
                *currentNode = new DoublyLinkedNode<T>();
                std::cout << "New node at " << *currentNode << std::endl;
                (*currentNode)->value = value;

                // Set left to previous node (nullptr at start)
                (*currentNode)->left = previousNode;

                previousNode = *currentNode;

                end = *currentNode;

                // Set current node to the ->next pointer
                // so it will be populated with next new operator.
                currentNode = &((*currentNode)->right);
            }

            start->left = end;
            end->right = start;

            _size = initValues.size();
        }

        size_t size() {
            return _size;
        }

        void print() {
            DoublyLinkedNode<T>* node = start;
            while (1) {
                printf("%p", node->value);
                if (node->right == start) {
                    std::cout << std::endl;
                    return;
                }
                printf(" <-> ");
                node = node->right;
            }
        }

        DoublyLinkedNode<T>* get(size_t idx) {
            DoublyLinkedNode<T>* node = start;
            for (size_t i = 0; i < idx; i++) {
                node = node->right;
            }
            return node;
        }

        DoublyLinkedNode<T>* cover(size_t idxToCover) {
            DoublyLinkedNode<T>* node = get(idxToCover);

            // Perform dancing links cover operation
            node->left->right = node->right;
            node->right->left = node->left;

            size--;

            return node;
        }

        void uncover(DoublyLinkedNode<T>* node) {
            node->left->right = node;
            node->right->left = node;

            size++;
        }
};

#endif // DOUBLY_LINKED_LIST_H