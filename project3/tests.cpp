#include <iostream>
#include <sstream>
#include "BinarySearchTree.h"
#include "unit_test_framework.h"

using namespace std;


TEST(test_empty) {
    // Add your tests here
	BinarySearchTree<int> tree;
	ASSERT_TRUE(tree.empty());
	tree.insert(5);
	ASSERT_FALSE(tree.empty());
	tree.insert(1);
	ASSERT_FALSE(tree.empty());
	tree.insert(19);
	ASSERT_FALSE(tree.empty());	
	tree.insert(100);
	ASSERT_FALSE(tree.empty());	
	tree.insert(0);
	ASSERT_FALSE(tree.empty());	
	tree.insert(-2);
	ASSERT_FALSE(tree.empty());
	
}

TEST(test_height){
	
	BinarySearchTree<int> tree;
	ASSERT_EQUAL(tree.height(), 0);
	tree.insert(15);
	ASSERT_EQUAL(tree.height(), 1);
	tree.insert(30);
	ASSERT_EQUAL(tree.height(), 2);
	tree.insert(1);
	ASSERT_EQUAL(tree.height(), 2);
	tree.insert(-5);
	ASSERT_EQUAL(tree.height(), 3);

	BinarySearchTree<int> stick;
	ASSERT_EQUAL(stick.height(), 0);
	stick.insert(1);
	ASSERT_EQUAL(stick.height(), 1);
	stick.insert(10);
	ASSERT_EQUAL(stick.height(), 2);
	stick.insert(100);
	ASSERT_EQUAL(stick.height(), 3);
	stick.insert(1000);
	ASSERT_EQUAL(stick.height(), 4);
	stick.insert(10000);
    ASSERT_EQUAL(stick.height(), 5);

}

TEST(test_size){

	BinarySearchTree<int> tree;
	ASSERT_EQUAL(tree.size(), 0);
	tree.insert(15);
	ASSERT_EQUAL(tree.size(), 1);
	tree.insert(30);
	ASSERT_EQUAL(tree.size(), 2);
	tree.insert(1);
	ASSERT_EQUAL(tree.size(), 3);
	tree.insert(1);
	ASSERT_EQUAL(tree.size(), 4);

	BinarySearchTree<int> stick;
	ASSERT_EQUAL(stick.size(), 0);
	stick.insert(1);
	ASSERT_EQUAL(stick.size(), 1);
	stick.insert(10);
	ASSERT_EQUAL(stick.size(), 2);
	stick.insert(100);
	ASSERT_EQUAL(stick.size(), 3);
	stick.insert(1000);
	ASSERT_EQUAL(stick.size(), 4);
	stick.insert(10000);
    ASSERT_EQUAL(stick.size(), 5);
	
}

TEST(test_copy_constructor){
	BinarySearchTree<int> tree;
	BinarySearchTree<int> copy = tree;
	ASSERT_TRUE(tree.empty());
	ASSERT_TRUE(copy.empty());
	
	tree.insert(8);
	tree.insert(5);
	tree.insert(4);
	BinarySearchTree<int> copy = tree;
	BinarySearchTree<int>::Iterator start = tree.begin();
	BinarySearchTree<int>::Iterator copystart = copy.begin();
	ASSERT_EQUAL(*start, copystart);
	
}

TEST(test_assignment_operator){
	BinarySearchTree<int> tree;
	tree.insert(5);
	tree.insert(15);
	
	BinarySearchTree<int> copy;
	copy.insert(4);
	copy.insert(5);
	
	BinarySearchTree<int>::Iterator start = tree.begin();
	BinarySearchTree<int>::Iterator copystart = copy.begin();
	ASSERT_NOT_EQUAL(*start, *copystart);
	
	
}

TEST(test_check_sorting_invariant){
	BinarySearchTree<int> tree;
	ASSERT_TRUE(tree.check_sorting_invariant());	
	tree.insert(5);
	ASSERT_TRUE(tree.check_sorting_invariant());
	tree.insert(3);
	ASSERT_TRUE(tree.check_sorting_invariant());
	tree.insert(100);
	ASSERT_TRUE(tree.check_sorting_invariant());
	tree.insert(-2000);
    ASSERT_TRUE(tree.check_sorting_invariant());

	
	BinarySearchTree<int>::Iterator insert = tree.find(5);
	*insert = 200000;
	ASSERT_FALSE(tree.check_sorting_invariant());
	
}


TEST(test_find){
	BinarySearchTree<int> tree;
	BinarySearchTree<int>::Iterator num = tree.find(2);
	BinarySearchTree<int>::Iterator end = tree.end();
	ASSERT_EQUAL(num, end);
	
	tree.insert(10);
	num = tree.find(10);
	ASSERT_EQUAL(*num, 10);
	
	tree.insert(-100);
	num = tree.find(-100);
	ASSERT_EQUAL(*num, -100);
	
	tree.insert(0);
	num = tree.find(0);
	ASSERT_EQUAL(*num, 0);
	
}

TEST(test_min_element){
	
	BinarySearchTree<int> tree;
	BinarySearchTree<int>::Iterator min = tree.min_element();
	tree.insert(1000);
	min = tree.min_element();
	ASSERT_EQUAL(*min, 1000);
	
	tree.insert(150000);
	min = tree.min_element();
	ASSERT_EQUAL(*min, 1000);
	
	tree.insert(6);
	min = tree.min_element();
	ASSERT_EQUAL(*min, 6);
	
	
	
}

TEST(test_max_element){
	
	BinarySearchTree<int> tree;
	BinarySearchTree<int>::Iterator max = tree.max_element();
	BinarySearchTree<int>::Iterator end = tree.end();
	
	tree.insert(1000);
	max = tree.max_element();
	ASSERT_EQUAL(*min, 1000);
	
	tree.insert(15);
	max = tree.max_element();
	ASSERT_EQUAL(*max, 1000);
	
	tree.insert(6);
	max = tree.max_element();
	ASSERT_EQUAL(*max, 6);
	
	
}


TEST_MAIN()