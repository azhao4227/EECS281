/* 
 * join_ropes.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 4 Written.
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

#include "join_ropes.h"

using namespace std;

int join_ropes(const vector<int>& rope_lengths) {


  priority_queue<int, vector<int>, greater<int>> ropes;
  for(int i = 0; i < rope_lengths.size(); i++){
    ropes.push(rope_lengths.at(i));
  }

  int total = 0;

  while(!ropes.empty()){
    int sum = ropes.top();
    ropes.pop();
    if(!ropes.empty()){
      sum += ropes.top();
      ropes.pop();
    }

    total += sum;
    ropes.push(sum);

  }

  return total;

}
