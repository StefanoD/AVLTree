#include "avltree.h"
#include <iostream>

int main()
{

    AVLTree<int> tree;

    for (int i = 0; i < 1000; ++i) {
        tree.insert(i);
    }

    for (int elem : tree) {
        std::cout << elem << ",";
    }

    std::cout << std::endl;

    return 0;
}
