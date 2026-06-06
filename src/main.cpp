// Copyright 2022 NNTU-CS
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <random>
#include <vector>
#include "tree.h"

int main() {
  std::vector<char> inputDataset = { '1', '2', '3' };
  PMTree sampleTree(inputDataset);

  auto generatedVariants = getAllPerms(sampleTree);
  for (auto& variantItem : generatedVariants) {
    for (char unitSymbol : variantItem) std::cout << unitSymbol;
    std::cout << "  ";
  }
  std::cout << "\n\n";

  std::cout << "getPerm1(1): ";
  auto singleMatch1 = getPerm1(sampleTree, 1);
  for (char unitSymbol : singleMatch1) std::cout << unitSymbol;
  std::cout << std::endl;

  std::cout << "getPerm2(2): ";
  auto singleMatch2 = getPerm2(sampleTree, 2);
  for (char unitSymbol : singleMatch2) std::cout << unitSymbol;
  std::cout << "\n\n";

  std::cout << "n;getAllPerms(s);getPerm1(s);getPerm2(s)" << std::endl;

  for (int currentN = 3; currentN <= 8; ++currentN) {
    std::vector<char> nodeElements;
    for (int counter = 0; counter < currentN; ++counter) {
      nodeElements.push_back('a' + counter);
    }
    PMTree benchTree(nodeElements);

    std::mt19937 generatorEngine(42);
    std::uniform_int_distribution<> distributionRange(
        1, static_cast<int>(fact(currentN)));
    int randomTarget = distributionRange(generatorEngine);

    auto timestamp0 = std::chrono::high_resolution_clock::now();
    getAllPerms(benchTree);
    auto timestamp1 = std::chrono::high_resolution_clock::now();
    getPerm1(benchTree, randomTarget);
    auto timestamp2 = std::chrono::high_resolution_clock::now();
    getPerm2(benchTree, randomTarget);
    auto timestamp3 = std::chrono::high_resolution_clock::now();

    double runTimeAll = std::chrono::duration<double>(
        timestamp1 - timestamp0).count();
    double runTimeP1  = std::chrono::duration<double>(
        timestamp2 - timestamp1).count();
    double runTimeP2  = std::chrono::duration<double>(
        timestamp3 - timestamp2).count();

    std::cout << currentN << ";"
        << std::fixed << std::setprecision(6) << runTimeAll << ";"
        << runTimeP1 << ";"
        << runTimeP2 << std::endl;
  }

  return 0;
}
