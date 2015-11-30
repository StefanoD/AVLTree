#include "avltree.h"
#include <iostream>

int main()
{
    AVLTree<int> tree;

    for (int i = 6; i > 0; --i) {
        tree.insert(i);
    }

    for (int elem : tree) {
        std::cout << elem << ",";
    }

    std::cout << std::endl;

    return 0;
}
