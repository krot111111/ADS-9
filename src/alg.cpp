// Copyright 2022 NNTU-CS
#include <algorithm>
#include <vector>
#include "tree.h"

PMTree::PMTree(const std::vector<char> &src) : base(src) {
  top = new Node(0);

  std::vector<char> subset = src;
  std::sort(subset.begin(), subset.end());

  for (char token : subset) {
    std::vector<char> unselected = subset;
    unselected.erase(std::find(unselected.begin(), unselected.end(), token));
    Node *child = generate(unselected);
    child->sym = token;
    top->links.push_back(child);
  }
}

PMTree::~PMTree() { destroy(top); }

PMTree::Node *PMTree::generate(const std::vector<char> &available) {
  if (available.empty())
    return new Node(0);
  Node *activeNode = new Node(0);
  std::vector<char> sortedQueue = available;
  std::sort(sortedQueue.begin(), sortedQueue.end());
  for (char token : sortedQueue) {
    std::vector<char> unselected = sortedQueue;
    unselected.erase(std::find(unselected.begin(), unselected.end(), token));
    Node *child = generate(unselected);
    child->sym = token;
    activeNode->links.push_back(child);
  }
  return activeNode;
}

void PMTree::destroy(Node *nodePtr) {
  if (!nodePtr)
    return;
  for (auto child : nodePtr->links) {
    destroy(child);
  }
  delete nodePtr;
}

void collectPaths(PMTree::Node *rootNode, std::vector<char> &sequence,
                  std::vector<std::vector<char>> &collection, int level,
                  int limit) {
  if (level == limit) {
    collection.push_back(sequence);
    return;
  }
  for (auto branch : rootNode->links) {
    sequence.push_back(branch->sym);
    collectPaths(branch, sequence, collection, level + 1, limit);
    sequence.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(PMTree &treeObj) {
  std::vector<std::vector<char>> finalSet;
  std::vector<char> track;
  int sizeCount = treeObj.base.size();
  for (auto firstBranch : treeObj.top->links) {
    track.push_back(firstBranch->sym);
    collectPaths(firstBranch, track, finalSet, 1, sizeCount);
    track.pop_back();
  }
  return finalSet;
}

std::vector<char> getPerm1(PMTree &treeObj, int num) {
  auto storage = getAllPerms(treeObj);
  if (num <= 0 || num > static_cast<int>(storage.size()))
    return {};
  return storage[num - 1];
}

size_t fact(int n) {
  size_t totalFact = 1;
  for (int idx = 2; idx <= n; ++idx)
    totalFact *= idx;
  return totalFact;
}

std::vector<char> getPerm2(PMTree &treeObj, int num) {
  int sizeCount = treeObj.base.size();
  if (num <= 0 || static_cast<size_t>(num) > fact(sizeCount))
    return {};

  std::vector<char> finalPath;
  int indexTrack = num - 1;
  PMTree::Node *currentPos = treeObj.top;

  for (int iteration = 0; iteration < sizeCount; ++iteration) {
    size_t clusterSize = fact(sizeCount - iteration - 1);
    int targetBranch = indexTrack / clusterSize;
    indexTrack %= clusterSize;
    if (targetBranch >= static_cast<int>(currentPos->links.size())) {
      return {};
    }
    currentPos = currentPos->links[targetBranch];
    finalPath.push_back(currentPos->sym);
  }
  return finalPath;
}
