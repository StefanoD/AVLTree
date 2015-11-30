#ifndef AVLTREE_H
#define AVLTREE_H

#include <memory>
#include <algorithm>
#include <assert.h>
#include <iterator>

template <typename T>
class AVLTree
{
private:
  class Node
  {
  public:
    int height = 0;
    T value;

    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    Node(T v)
      : value(v)
    {
    }

    // Kleiner-Ordnung
    bool operator<(const T& _value) const { return value < _value; }

    ~Node() {
        delete left;
        delete right;
    }
  };

  Node* root = nullptr;

  int getHeight(Node* p)
  {
    if (p == nullptr)
      return -1;
    else
      return p->height;
  }

  int getBalance(Node* p)
  {
    if (p == nullptr)
      return 0;
    else
      return getHeight(p->right) - getHeight(p->left);
  }

  Node* insertR(T value, Node* p)
  {
    if (p == nullptr) {
      p = new Node(value);
    } else if (value < p->value) {
      Node* temp = insertR(value, p->left);
      p->left = temp;
      temp->parent = p;
    } else if (value > p->value) {
      Node* temp = insertR(value, p->right);
      p->right = temp;
      temp->parent = p;
    }

    p = balance(p);

    return p;
  }

  Node* balance(Node* p)
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

  Node* rotateRight(Node* p)
  {
    assert(p->left != nullptr);

    Node* q = p->left;
    p->left = q->right;
    q->right = p;

    p->height = std::max(getHeight(p->left), getHeight(p->right)) + 1;
    q->height = std::max(getHeight(q->left), getHeight(q->right)) + 1;

    q->parent = p->parent;

    if (p->left != nullptr) {
      p->left->parent = p;
    }

    p->parent = q;

    return q;
  }

  Node* rotateLeft(Node* p)
  {
    assert(p->right != nullptr);

    Node* q = p->right;
    p->right = q->left;
    q->left = p;

    p->height = std::max(getHeight(p->left), getHeight(p->right)) + 1;
    q->height = std::max(getHeight(q->left), getHeight(q->right)) + 1;

    q->parent = p->parent;

    if (p->right != nullptr) {
      p->right->parent = p;
    }

    p->parent = q;

    return q;
  }

  Node* rotateLeftRight(Node* p)
  {
    assert(p->left != nullptr);

    p->left = rotateLeft(p->left);
    return rotateRight(p);
  }

  Node* rotateRightLeft(Node* p)
  {
    assert(p->right != nullptr);

    p->right = rotateRight(p->right);
    return rotateLeft(p);
  }

  bool contains(T value, Node* p)
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

  Node* findMax(Node* p)
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

  Node* findMin(Node* p)
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
    Node* node;

  private:
    Node* inOrderSuccessor(Node* n)
    {
      if (n->right != nullptr) {
        return tree->findMin(n->right);
      }

      Node* p = n->parent;

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
  ~AVLTree() {
      delete root;
  }

  iterator begin() { return iterator(this); }
  iterator end() { return iterator(); }

  void insert(T value)
  {
    if (root == nullptr) {
      root = new Node(value);
    } else {
      root = insertR(value, root);
    }
  }

  bool contains(T value) { return contains(value, root); }

  T findMax() { findMax(root)->value; }
};

#endif // AVLTREE_H
