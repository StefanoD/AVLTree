#include "avltree.h"
#include <iostream>

int main()
{

    AVLTree<int> tree;

    for (int i = 0; i < 100; ++i) {
        tree.insert(i);
    }

    for (int i = -200; i < 0; ++i) {
        tree.insert(i);
    }

    for (int i = 100; i < 400; ++i) {
        tree.insert(i);
    }

    for (int elem : tree) {
        std::cout << elem << ",";
    }

    std::cout << std::endl;

    return 0;
}
