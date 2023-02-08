#ifndef SRC_MODEL_GRAPH_ALGORITHMS_H_
#define SRC_MODEL_GRAPH_ALGORITHMS_H_

#include <limits.h>

#include <algorithm>
#include <set>
#include <tuple>

#include "algorithms/aco.h"
#include "algorithms/sa.h"
#include "containers/queue.h"
#include "containers/stack.h"

class GraphAlgorithms {
 public:
  std::vector<int> DepthFirstSearch(Graph &graph, int startVertex);
  std::vector<int> BreadthFirstSearch(Graph &graph, int startVertex);
  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  Matrix GetShortestPathsBetweenAllVertices(Graph &graph);
  Matrix GetLeastSpanningTree(Graph &graph);
  TsmResult TSPAntColonyOptimization(Graph &graph);
  std::vector<std::tuple<std::string, double, std::vector<int>, double>>
  TSPComparison(Graph &graph, int N);

 private:
  bool GetMinWay(int way, int min_way);
  TsmResult TSPSimulatedAnnealing(Graph &graph);
  TsmResult TSPBruteForce(Graph &graph);
  double CalcBruteForceCount(double cost);
};

#endif  // SRC_MODEL_GRAPH_ALGORITHMS_H_
