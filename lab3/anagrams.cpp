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

using namespace std;

bool isAnagram(const string &s1, const string &s2){
	map<char,int> stringOne;
	map<char,int> stringTwo;


	for(int i = 0; i < s1.length(); i++){
		stringOne[s1[i]]++;
	}

	for(int i = 0; i < s2.length(); i++){
		stringTwo[s1[i]]++;
	}

	if(stringOne.size() != stringTwo.size()){
		return false;
	}

	iterator s2i = s2.begin();

	for (iterator it = s1.begin(); it != s1.end(); ++it){
		if(it -> second != s2i -> second){
			return false;
		}
		++s2i;
	}

	return true;


}
