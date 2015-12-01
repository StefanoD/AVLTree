#include <QtTest/QtTest>
#include <map>
#include <iostream>
#include "avltree.h"

class AVLTest : public QObject
{
  Q_OBJECT
private slots:
  void testOrderSuccIsBigger();
  void testOrderSuccIsSmaller();
  void testOrder();
  void testDoubleKeys();
};

/**
 *  AVLTree<int> tree;

    for (int i = 0; i < 100; ++i) {
        tree.insert(i);
    }

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
    std::cout << "====findBiggerEqualThan====" << std::endl;

    auto it = tree.findBiggerEqualThan(0);

    for (; it != tree.end(); ++it) {
        int i = *it;
        std::cout << i << ",";
    }

 */

/**
 * @brief AVLTest::testOrderSuccIsBigger
 * Test order when every successor is bigger.
 */
void
AVLTest::testOrderSuccIsBigger()
{
    AVLTree<int> tree;

    for (int i = 0; i < 100; ++i) {
      tree.insert(i);
    }

    int i = 0;

    for (int elem : tree) {
      QCOMPARE(elem, i);
      ++i;
    }
}

/**
 * @brief AVLTest::testOrderSuccIsSmaller
 * Test order when every successor is smaller.
 */
void AVLTest::testOrderSuccIsSmaller()
{
    AVLTree<int> tree;

    for (int i = 0; i > -100; --i) {
      tree.insert(i);
    }

    int i = -99;

    for (int elem : tree) {
      QCOMPARE(elem, i);
      ++i;
    }
}

/**
 * @brief AVLTest::testOrder
 * Test order with mixed insertions
 */
void AVLTest::testOrder()
{
    AVLTree<int> tree;

    for (int i = 0; i > -100; --i) {
      tree.insert(i);
    }

    for (int i = 1; i < 100; ++i) {
      tree.insert(i);
    }

    for (int i = -100; i > -200; --i) {
      tree.insert(i);
    }

    for (int i = 100; i < 200; ++i) {
      tree.insert(i);
    }

    int prevElement = -100000;

    for (int elem : tree) {
      QVERIFY(prevElement < elem);
      prevElement = elem;
    }
}

/**
 * @brief AVLTest::testDoubleKeys
 * We insert two identical elements and test if every element is inserted
 * correctly.
 */
void
AVLTest::testDoubleKeys()
{
  AVLTree<int> tree;
  std::map<int, int> map;

  for (int i = 0; i < 100; ++i) {
    tree.insert(i);
  }

  for (int i = 0; i < 100; ++i) {
    tree.insert(i);
  }

  int expectedValue = 0;
  int i = 0;

  for (int elem : tree) {
    QCOMPARE(elem, expectedValue);

    map[expectedValue] += 1;

    // Value changes only every second element.
    if (i % 2 != 0) {
      ++expectedValue;
    }

    ++i;
  }

  // Every element should have been inserted twice in avl tree.
  for (const auto& kv : map) {
    QCOMPARE(kv.second, 2);
  }
}

QTEST_MAIN(AVLTest)
#include "avltest.moc"
