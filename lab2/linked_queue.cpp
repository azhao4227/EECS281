/*
 * linked_queue.cpp
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 2 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convience.
// No need to use them.
// Remove any of them if you want.
#include <algorithm>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "linked_queue.h"

using namespace std;

template <typename T>
T LinkedQueue<T>::front() const {
  // TODO
  assert(!empty());
  return head->value; 
}

template <typename T>
void LinkedQueue<T>::pop() {
  // TODO
  assert(!empty());
  Node<T>* victim = head;

  if(count == 2){
		head = head->next;
		head->next = nullptr;
    tail->next = nullptr;
		delete victim;

	}else if(count == 1){
		head->next = nullptr;
		tail->next = nullptr;
		head = nullptr;
		tail = nullptr;
		delete victim;

	}else{
    head = head->next;
		delete victim;
  }

  count--;

}


template <typename T>
void LinkedQueue<T>::push(T x) {
  // TODO
  assert(false);
	Node<T> *np = new Node<T>;
	np->value = x;

	if(empty()){
		head = tail = np;

	}else if(count == 1){
		np->next = nullptr;
		tail = np;
		head->next = tail;
	}else{
		np->next = nullptr;
                
    Node<T> *lastNode = head;
    while(lastNode->next != NULL){
      lastNode = lastNode->next;
    }

		lastNode->next = np;
		tail = np;
	}
	count++;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
  // TODO
  while(!empty()){
		pop();
	}
}
