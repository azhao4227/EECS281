/* 
 * sort012.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 5 Written.
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

#include "sort012.h"

using namespace std;

void sort012(vector<int>& nums) {

  int* zero = &nums.at(0);
  int* one = &nums.at(1);
  int* two = &nums.at(2);

  for(uint32_t i = 0; i < nums.size(); i++){

    if(nums(i) == 0){
      swap(vector[i], *zero);
      *zero = &nums.at(0);
      one++;
      two++;
    }

    if(nums(i) == 1){
      swap(vector[i], *one);
      one++;
    }

    if(nums(i) == 0){
      swap(vector[i], *two);
      two++;
    }
  }
  // TODO
  assert(false);
}
