/* 
 * sort012.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 5 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convience.
// No need to use them. 
// Remove any of them if you want.
#include <unordered_map>
#include <vector>
#include <iostream>


using namespace std;


void two_pair_sums(const vector <int> &input_vec , ostream& out){  

  unordered_map<int, pair<int,int>> sums;
  //int counter = 0;

  for(auto it = input_vec.begin(); it != input_vec.end(); it++){
    for(auto it2 = it; it2 != input_vec.end(); it2++){

      if(*it2 != *it){
        pair<int,int> combo = make_pair(*it, *it2);
        int sum = *it + *it2;
        auto got = sums.find(sum);

        if(got != sums.end()){
          out << "(" << sums[sum].first << "," << sums[sum].second << ")" << " and " << "(" << *it << "," << *it2 << ")" << endl;
        } else {
          sums[sum] = combo;
        }
      }

    }
  }
}

int main(int argc, char *argv[]) {
    // This should be in all of your projects, speeds up I/O
    ios_base::sync_with_stdio(false);

    vector<int> vec = {3,4,7,1,2,8};
    two_pair_sums(vec,cout);

    return 0;
} 