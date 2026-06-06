// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
public:
  struct Node {
    char sym;
    std::vector<Node*> links;
    explicit Node(char s) : sym(s) {}
  };

  Node* top;
  std::vector<char> base;

  explicit PMTree(const std::vector<char>& src);
  ~PMTree();

private:
  Node* generate(const std::vector<char>& available);
  void destroy(Node* nodePtr);
};

std::vector<std::vector<char>> getAllPerms(PMTree& treeObj);
std::vector<char> getPerm1(PMTree& treeObj, int num);
std::vector<char> getPerm2(PMTree& treeObj, int num);

size_t fact(int n);

#endif

