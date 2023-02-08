#ifndef SRC_VIEW_CONSOLE_INTERFACE_H_
#define SRC_VIEW_CONSOLE_INTERFACE_H_

#include <iostream>

#include "../model/graph_algorithms.h"

class ConsoleInterface {
 public:
  void Init();

 private:
  Graph graph_;
  GraphAlgorithms algorithm_;

  std::string font_{"\033[1;32m"};
  std::string back_{"\033[1;42m"};
  std::string color_off_{"\033[0m"};

  void Menu();
  void WhatIsNext();
  void Welcome();
  void LoadGraph();
  void ChooseMenu();
  int CheckInput();
  bool IsNumber(std::string choice);
  void DoAlgorithm(int num);
  void BreadthDepthFirstSearch(int choice);
  void DijkstrasAlgorithm();
  void FloydWarshallPrimsAlgorithm(int choice);
  void AntColonyAlgorithm();
  void ComparisonTSP();
  void ComparisonOutput(
      const std::vector<
          std::tuple<std::string, double, std::vector<int>, double>>& v);
  void Save();

  template <typename T>
  void PrintVector(std::vector<T>& v);
  void PrintMatrix(Matrix& m);
};

#endif  // SRC_VIEW_CONSOLE_INTERFACE_H_
