#include "diameter.h"

int height(const const BinaryTreeNode* tree){
  if(tree == nullptr){
    return 0;
  }

  return 1+max(height(tree->left),height(tree->left));
}

int max(int a, int b) { 
  if(a > b){
    return a;
  }else{
    return b;
  }
}

int diameter(const BinaryTreeNode* tree) {
  // TODO

  int currDiameter = 1 + height(tree->left) + height(tree->right);;
  int leftDiameter = diameter(tree->left);
  int rightDiameter = diameter(tree->right);

  int largerDiameter = max(leftDiameter, rightDiameter);

  return max(largerDiameter, currDiameter);
}
