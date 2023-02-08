#include "console_interface.h"

void ConsoleInterface::Init() {
  Welcome();
  LoadGraph();
}

void ConsoleInterface::Welcome() {
  std::cout << font_ << "\t---------------------------------------------"
            << color_off_ << std::endl;
  std::cout << back_ << "\t                                             "
            << color_off_ << std::endl;
  std::cout << back_ << "\t       WELCOME TO SIMPLE NAVIGATOR V1.0      "
            << color_off_ << std::endl;
  std::cout << back_ << "\t                                             "
            << color_off_ << std::endl;
  std::cout << font_ << "\t---------------------------------------------"
            << color_off_ << std::endl;
}

void ConsoleInterface::Menu() {
  std::cout << font_ << "\t---------------------------------------------"
            << color_off_ << std::endl;
  std::cout << back_ << "\t                     MENU                    "
            << color_off_ << std::endl;
  std::cout << font_ << "\t---------------------------------------------"
            << std::endl;
  std::cout << "\t1. Load graph from a file" << std::endl;
  std::cout << "\t2. Breadth-first search" << std::endl;
  std::cout << "\t3. Depth-first search" << std::endl;
  std::cout << "\t4. Dijkstra's algorithm" << std::endl;
  std::cout << "\t5. Floyd-Warshall algorithm" << std::endl;
  std::cout << "\t6. Prim's algorithm" << std::endl;
  std::cout << "\t7. Ant colony algorithm" << std::endl;
  std::cout << "\t8. Comparison of methods for solving the TSP" << std::endl;
  std::cout << "\t9. Save to .dot" << std::endl;
  std::cout << "\t0. Exit" << std::endl;
  std::cout << "\t---------------------------------------------" << color_off_
            << std::endl;
}

void ConsoleInterface::ChooseMenu() {
  Menu();
  std::cout << font_ << "\n\tEnter menu number..." << std::endl;
  int num = CheckInput();
  if (num != -1 && num < 10) {
    DoAlgorithm(num);
  } else {
    std::cout << font_ << "\n\tError: incorrect input, try again\n"
              << color_off_ << std::endl;
    ChooseMenu();
  }
}

bool ConsoleInterface::IsNumber(std::string choice) {
  bool result = true;
  for (std::string::size_type i = 0; i < choice.size(); i++) {
    if (!std::isdigit(choice[i])) {
      result = false;
      break;
    }
  }
  return result;
}

void ConsoleInterface::DoAlgorithm(int num) {
  if (num == 1) {
    LoadGraph();
  } else if (num == 2 || num == 3) {
    BreadthDepthFirstSearch(num);
  } else if (num == 4) {
    DijkstrasAlgorithm();
  } else if (num == 5 || num == 6) {
    FloydWarshallPrimsAlgorithm(num);
  } else if (num == 7) {
    AntColonyAlgorithm();
  } else if (num == 8) {
    ComparisonTSP();
  } else if (num == 9) {
    Save();
  } else if (num == 0) {
    return;
  }
}

void ConsoleInterface::WhatIsNext() {
  std::cout << font_ << "\n\tTo return to the menu enter 1" << std::endl;
  std::cout << "\tTo exit the program enter 0" << std::endl;

  int num = CheckInput();
  if (num != -1 && num < 2) {
    if (num == 1) {
      ChooseMenu();
    } else if (num == 0) {
      exit(EXIT_SUCCESS);
    }
  } else {
    std::cout << font_ << "\n\tError: incorrect input, try again" << color_off_
              << std::endl;
    WhatIsNext();
  }
}

void ConsoleInterface::LoadGraph() {
  while (true) {
    std::string filename;
    std::cout << font_ << "\n\tEnter file name..." << std::endl;
    std::cout << "\t";
    std::cin >> filename;
    try {
      graph_.GraphClear();
      graph_.LoadGraphFromFile("tests/graphs/" + filename);
      break;
    } catch (std::exception &e) {
      std::cerr << "\n\tError: " << e.what() << std::endl;
    }
  }
  std::cout << color_off_ << std::endl;
  ChooseMenu();
}

void ConsoleInterface::BreadthDepthFirstSearch(int choice) {
  try {
    std::cout << font_ << "\n\tEnter starting vertex from 1 to "
              << graph_.GetSize() << std::endl;
    int num = CheckInput();
    if (num != -1 && num < (graph_.GetSize() + 1) && num > 0) {
      std::vector<int> path;
      if (choice == 2) {
        path = algorithm_.BreadthFirstSearch(graph_, num);
      } else {
        path = algorithm_.DepthFirstSearch(graph_, num);
      }
      std::cout << font_ << "\n\t";
      PrintVector(path);
      std::cout << color_off_;
      WhatIsNext();
    } else {
      std::cout << font_ << "\n\tError: incorrect input, try again"
                << color_off_ << std::endl;
      BreadthDepthFirstSearch(choice);
    }
  } catch (std::exception &e) {
    std::cerr << font_ << "\nError: " << e.what() << color_off_ << "\n";
    WhatIsNext();
  }
}

void ConsoleInterface::DijkstrasAlgorithm() {
  try {
    std::cout << font_ << "\n\tEnter starting vertex from 1 to "
              << graph_.GetSize() << std::endl;
    int start = CheckInput();
    std::cout << font_ << "\n\tEnter finishing vertex from 1 to "
              << graph_.GetSize() << std::endl;
    int finish = CheckInput();
    if (start != -1 && finish != -1 && start < (graph_.GetSize() + 1) &&
        finish < (graph_.GetSize() + 1) && start > 0 && finish > 0) {
      int distance =
          algorithm_.GetShortestPathBetweenVertices(graph_, start, finish);
      std::cout << font_ << "\n\tDistance: " << distance << color_off_
                << std::endl;
      WhatIsNext();
    } else {
      std::cout << font_ << "\n\tError: incorrect input, try again"
                << color_off_ << std::endl;
      DijkstrasAlgorithm();
    }
  } catch (std::exception &e) {
    std::cerr << font_ << "\n\tError: " << e.what() << color_off_ << "\n";
    WhatIsNext();
  }
}

void ConsoleInterface::FloydWarshallPrimsAlgorithm(int choice) {
  try {
    Matrix res;
    if (choice == 5) {
      res = algorithm_.GetShortestPathsBetweenAllVertices(graph_);
    } else {
      res = algorithm_.GetLeastSpanningTree(graph_);
    }
    std::cout << font_ << "\n\t";
    PrintMatrix(res);
    std::cout << color_off_;
    WhatIsNext();
  } catch (std::exception &e) {
    std::cerr << font_ << "\n\tError: " << e.what() << color_off_ << "\n";
    WhatIsNext();
  }
}

void ConsoleInterface::AntColonyAlgorithm() {
  try {
    TsmResult res;
    res = algorithm_.TSPAntColonyOptimization(graph_);
    if (!std::isinf(res.distance)) {
      std::cout << font_ << "\n\tRoute length: " << res.distance;
      std::cout << "\n\tSequence of traversing vertices: ";
      PrintVector(res.vertices);
      std::cout << color_off_;
    } else {
      std::cout << font_ << "\n\tNo path found!\n" << color_off_;
    }
    WhatIsNext();
  } catch (std::exception &e) {
    std::cerr << font_ << "\n\tError: " << e.what() << color_off_ << "\n";
    WhatIsNext();
  }
}

void ConsoleInterface::ComparisonTSP() {
  try {
    std::vector<std::tuple<std::string, double, std::vector<int>, double>> res;
    std::cout << font_ << "\n\tEnter how many times to execute each algorithm"
              << std::endl;

    int num = CheckInput();
    if (num != -1 && num < 1001 && num > 0) {
      res = algorithm_.TSPComparison(graph_, num);
      ComparisonOutput(res);
    } else {
      std::cout << font_ << "\n\tError: incorrect input, try again"
                << color_off_ << std::endl;
      ComparisonTSP();
    }
    WhatIsNext();
  } catch (std::exception &e) {
    std::cerr << font_ << "\n\tError: " << e.what() << color_off_ << "\n";
    WhatIsNext();
  }
}

void ConsoleInterface::Save() {
  std::cout << font_ << "\n\tEnter file name to save graph with .dot extension"
            << std::endl;
  std::string filename;
  std::cout << "\t";
  std::cin >> filename;
  graph_.ExportGraphToDot(filename);
  std::cout << "\tFile is saved" << color_off_ << std::endl;
  WhatIsNext();
}

void ConsoleInterface::ComparisonOutput(
    const std::vector<std::tuple<std::string, double, std::vector<int>, double>>
        &v) {
  for (auto [A, B, C, D] : v) {
    if (!std::isinf(B)) {
      std::cout << font_ << "\n\tUsing algorithm: " << A;
      std::cout << "\n\tRoute length: " << B;
      std::cout << "\n\tSequence of traversing vertices: ";
      auto &vec = C;
      for (auto &it : vec) {
        std::cout << it << " ";
      }
      std::cout << "\n\tExecution time: " << D << " sec" << std::endl;
    } else {
      std::cout << font_ << "\n\tUsing algorithm: " << A;
      std::cout << "\n\tNo path found!\n" << color_off_;
    }
  }
}

int ConsoleInterface::CheckInput() {
  std::string choice;
  int num;
  std::cout << "\t";
  std::cin >> choice;
  std::cout << color_off_;

  return IsNumber(choice) == 1 ? num = std::stoi(choice) : -1;
}

template <typename T>
void ConsoleInterface::PrintVector(std::vector<T> &v) {
  for (auto &elem : v) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

void ConsoleInterface::PrintMatrix(Matrix &m) {
  for (unsigned int i = 0; i < m.GetSize(); i++) {
    for (unsigned int j = 0; j < m.GetSize(); j++) {
      std::cout << m(i, j) << ' ';
    }
    std::cout << "\n\t";
  }
}
