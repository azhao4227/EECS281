struct BinaryTreeNode {
  BinaryTreeNode* left;
  BinaryTreeNode* right;
  int value;
  BinaryTreeNode(int n) : left{nullptr}, right{nullptr}, value{n} {}
};

int max(int a, int b);
int height(const BinaryTreeNode* tree);
int diameter(const BinaryTreeNode* tree);
