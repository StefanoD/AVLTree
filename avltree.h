#ifndef AVLTREE_H
#define AVLTREE_H

#include <memory>
#include <algorithm>
#include <assert.h>
#include <iterator>
#include <iostream>

template <typename T>
class AVLTree
{
private:
  class Node
  {
  public:
    int height = 0;
    T value;

    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
    std::shared_ptr<Node> parent = nullptr;

    Node(T v)
      : value(v)
    {
    }

    // Kleiner-Ordnung
    bool operator<(const T& _value) const { return value < _value; }
  };

  std::shared_ptr<Node> root = nullptr;

  int getHeight(std::shared_ptr<Node> p)
  {
    if (p == nullptr)
      return -1;
    else
      return p->height;
  }

  int getBalance(std::shared_ptr<Node> p)
  {
    if (p == nullptr)
      return 0;
    else
      return getHeight(p->right) - getHeight(p->left);
  }

  std::shared_ptr<Node> insertR(T value, std::shared_ptr<Node> p)
  {
    if (p == nullptr) {
      p = std::make_shared<Node>(value);
    } else if (value < p->value) {
      std::shared_ptr<Node> temp = insertR(value, p->left);
      p->left = temp;
      temp->parent = p;
    } else if (value > p->value) {
      std::shared_ptr<Node> temp = insertR(value, p->right);
      p->right = temp;
      temp->parent = p;
    }

    p = balance(p);

    return p;
  }

  std::shared_ptr<Node> balance(std::shared_ptr<Node> p)
  {
    if (p == nullptr)
      return nullptr;

    p->height = std::max(getHeight(p->left), getHeight(p->right)) + 1;

    if (getBalance(p) == -2) {
      if (getBalance(p->left) <= 0)
        p = rotateRight(p);
      else
        p = rotateLeftRight(p);
    } else if (getBalance(p) == 2) {
      if (getBalance(p->right) >= 0)
        p = rotateLeft(p);
      else
        p = rotateRightLeft(p);
    }

    return p;
  }

  std::shared_ptr<Node> rotateRight(std::shared_ptr<Node> p)
  {
    assert(p->left != nullptr);

    std::shared_ptr<Node> q = p->left;
    p->left = q->right;
    q->right = p;

    p->height = std::max(getHeight(p->left), getHeight(p->right)) + 1;
    q->height = std::max(getHeight(q->left), getHeight(q->right)) + 1;

    q->parent = p->parent;
    q->right->parent = p;
    p->parent = q;

    return q;
  }

  std::shared_ptr<Node> rotateLeft(std::shared_ptr<Node> p)
  {
    assert(p->right != nullptr);

    std::shared_ptr<Node> q = p->right;
    p->right = q->left;
    q->left = p;

    p->height = std::max(getHeight(p->left), getHeight(p->right)) + 1;
    q->height = std::max(getHeight(q->left), getHeight(q->right)) + 1;

    q->parent = p->parent;
    q->left->parent = p;
    p->parent = q;

    return q;
  }

  std::shared_ptr<Node> rotateLeftRight(std::shared_ptr<Node> p)
  {
    assert(p->left != nullptr);

    p->left = rotateLeft(p->left);
    return rotateRight(p);
  }

  std::shared_ptr<Node> rotateRightLeft(std::shared_ptr<Node> p)
  {
    assert(p->right != nullptr);

    p->right = rotateRight(p->right);
    return rotateLeft(p);
  }

  bool contains(T value, std::shared_ptr<Node> p)
  {
    if (p == nullptr) {
      return false;
    } else {
      if (value < *p) {
        contains(value, p->left);
      } else {
        if (value > *p) {
          contains(value, p->right);
        } else {
          return true;
        }
      }
    }
  }

  std::shared_ptr<Node> findMax(std::shared_ptr<Node> p)
  {
    if (p == nullptr) {
      return p;
    } else {
      while (p->right != nullptr) {
        p = p->right;
      }
      return p;
    }
  }

  std::shared_ptr<Node> findMin(std::shared_ptr<Node> p)
  {
    if (p == nullptr) {
      return p;
    } else {
      while (p->left != nullptr) {
        p = p->left;
      }
      return p;
    }
  }

  class iterator : std::iterator<std::forward_iterator_tag, T>
  {
    AVLTree* tree;
    std::shared_ptr<Node> node;

  private:
    std::shared_ptr<Node> inOrderSuccessor(std::shared_ptr<Node> n)
    {
      // step 1 of the above algorithm
      if (n->right != nullptr)
        return tree->findMin(n->right);

      // step 2 of the above algorithm
      std::shared_ptr<Node> p = n->parent;
      while (p != nullptr && n == p->right) {
        n = p;
        p = p->parent;
      }
      return p;
    }

  public:
    explicit iterator()
      : tree(nullptr)
      , node(nullptr)
    {
    }

    explicit iterator(AVLTree* tree)
      : tree(tree)
    {
      node = tree->findMin(tree->root);
    }

    T& operator*() { return node->value; }

    iterator& operator++()
    {
      if (node != nullptr) {
        node = inOrderSuccessor(node);
      }

      return *this;
    }

    iterator operator++(int)
    {
      iterator tmp = *this;
      ++*this;
      return tmp;
    }

    bool operator==(const iterator& other) const { return node == other.node; }
    bool operator!=(const iterator& other) const { return node != other.node; }
  };

public:
  iterator begin() { return iterator(this); }
  iterator end() { return iterator(); }

  void insert(T value)
  {
    if (root == nullptr) {
      root = std::make_shared<Node>(value);
    } else {
      root = insertR(value, root);
    }
  }

  bool contains(T value) { return contains(value, root); }

  T findMax() { findMax(root)->value; }
};

#endif // AVLTREE_H
