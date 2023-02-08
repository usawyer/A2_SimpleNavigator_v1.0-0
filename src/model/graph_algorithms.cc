#include "graph_algorithms.h"

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                   int startVertex) {
  std::vector<int> result;
  Stack<int> dfs;
  unsigned int size = graph.GetSize();
  std::vector<bool> visited(size);
  dfs.Push(startVertex - 1);
  visited[startVertex - 1] = 1;

  while (!dfs.Empty()) {
    int i = dfs.Peek();
    dfs.Pop();
    for (unsigned int j = 0; j < size; j++) {
      if (graph.GetGraph()(i, j) != 0 && visited[j] == 0) {
        dfs.Push(j);
        visited[j] = 1;
      }
    }
    result.push_back(i + 1);
  }
  return result;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                     int startVertex) {
  std::vector<int> result;
  Queue<int> bfs;
  unsigned int size = graph.GetSize();
  std::vector<bool> used(size);
  bfs.Push(startVertex - 1);
  used[startVertex - 1] = 1;

  while (!bfs.Empty()) {
    int i = bfs.Front();
    bfs.Pop();
    for (unsigned int j = 0; j < size; j++) {
      if (graph.GetGraph()(i, j) != 0 && used[j] == 0) {
        bfs.Push(j);
        used[j] = 1;
      }
    }
    result.push_back(i + 1);
  }
  return result;
}

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  if (graph.GetNegativeType()) {
    throw std::invalid_argument("This graph is negative!");
  }
  unsigned int v1 = vertex1 - 1, v2 = vertex2 - 1;
  Queue<int> sort_point;
  Matrix buf_mtrx = graph.GetGraph();
  unsigned int size = graph.GetSize();
  std::vector<int> way(size, INT32_MAX);
  std::vector<bool> used(size, 0);

  sort_point.Push(v1);
  way.at(v1) = 0;

  while (!sort_point.Empty()) {
    int i = sort_point.Front();
    sort_point.Pop();
    if (used[i] == 1) {
      continue;
    }
    used[i] = 1;
    for (unsigned int j = 0; j < size; ++j) {
      int t_way = way[i] + buf_mtrx(i, j);
      if (buf_mtrx(i, j) != 0 && used[j] == 0 && way[j] > t_way) {
        way[j] = t_way;
        if (j != v2) {
          sort_point.Push(j);
        }
      }
    }
  }
  return way[v2] == INT32_MAX ? 0 : way[v2];
}

Matrix GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  Matrix result_m(graph.GetGraph());
  unsigned int size = graph.GetSize();
  for (unsigned int k = 0; k < size; ++k) {
    for (unsigned int i = 0; i < size; ++i) {
      for (unsigned int j = 0; j < size; ++j) {
        if (result_m(i, k) && result_m(k, j) &&
            result_m(i, j) > result_m(i, k) + result_m(k, j) && i != j) {
          result_m(i, j) = result_m(i, k) + result_m(k, j);
        }
      }
    }
  }
  return result_m;
}

Matrix GraphAlgorithms::GetLeastSpanningTree(Graph &graph) {
  if (graph.GetDirectType()) {
    throw std::invalid_argument("This graph is directed!");
  }
  Matrix buf_mtrx = graph.GetGraph();
  unsigned int size = graph.GetSize();
  Matrix result(size);
  std::set<int> used;
  std::vector<std::pair<int, int>> way;
  used.insert(0);
  while (used.size() < size) {
    int min_weight = INT32_MAX, to = 0, from = 0;
    for (auto i : used)
      for (size_t j = 0; j < size; j++)
        if (GetMinWay(buf_mtrx(j, i), min_weight) && !used.count(j)) {
          min_weight = buf_mtrx(j, i);
          from = i;
          to = j;
        }
    way.push_back(std::make_pair(from, to));
    used.insert(to);
  }
  for (auto &i : way)
    result(i.first, i.second) = result(i.second, i.first) =
        buf_mtrx(i.first, i.second);
  return result;
}

bool GraphAlgorithms::GetMinWay(int way, int min_way) {
  return way != 0 && way < min_way;
}

TsmResult GraphAlgorithms::TSPAntColonyOptimization(Graph &graph) {
  if (graph.GetNegativeType()) {
    throw std::invalid_argument("Wrong graph");
  }
  ACO ant_colony_optimization(graph);
  TsmResult res = ant_colony_optimization.InitAlgorithm();
  return res;
}

TsmResult GraphAlgorithms::TSPSimulatedAnnealing(Graph &graph) {
  if (graph.GetNegativeType() || graph.GetDirectType()) {
    throw std::invalid_argument("Wrong graph");
  }
  SimulatedAnnealing simulated_annealing(graph);
  TsmResult res = simulated_annealing.InitAlgorithm();
  return res;
}

TsmResult GraphAlgorithms::TSPBruteForce(Graph &graph) {
  if (graph.GetNegativeType() || graph.GetDirectType()) {
    throw std::invalid_argument("Wrong graph");
  }
  TsmResult res;
  std::vector<int> freetovisit;
  std::vector<int> path;
  int source = 0;
  for (int i = 1; i < graph.GetSize(); i++) {
    freetovisit.push_back(i);
  }
  while (next_permutation(freetovisit.begin(), freetovisit.end())) {
    double cost = 0.0;
    int j = source;
    path.clear();
    path.push_back(j + 1);
    for (size_t i = 0; i < freetovisit.size(); i++) {
      cost += CalcBruteForceCount(graph.GetGraph()(j, freetovisit[i]));
      j = freetovisit[i];
      path.push_back(j + 1);
    }
    path.push_back(path[0]);
    cost += CalcBruteForceCount(graph.GetGraph()(j, source));
    if (cost < res.distance) {
      res.distance = cost;
      res.vertices = path;
    }
  }

  return res;
}

double GraphAlgorithms::CalcBruteForceCount(double cost) {
  return cost != 0.0 ? cost : INFINITY;
}

std::vector<std::tuple<std::string, double, std::vector<int>, double>>
GraphAlgorithms::TSPComparison(Graph &graph, int N) {
  std::vector<std::tuple<std::string, double, std::vector<int>, double>> res;
  TsmResult result;

  clock_t time_start = clock();
  for (int i = 0; i < N; i++) {
    result = TSPAntColonyOptimization(graph);
  }
  clock_t time_end = clock() - time_start;
  double duration = static_cast<double>(time_end) / CLOCKS_PER_SEC;
  res.push_back(std::make_tuple("Ant Colony Optimization", result.distance,
                                result.vertices, duration));

  time_start = clock();
  for (int i = 0; i < N; i++) {
    result = TSPSimulatedAnnealing(graph);
  }
  time_end = clock() - time_start;
  duration = static_cast<double>(time_end) / CLOCKS_PER_SEC;
  res.push_back(std::make_tuple("Simulated Annealing", result.distance,
                                result.vertices, duration));

  time_start = clock();
  for (int i = 0; i < N; i++) {
    result = TSPBruteForce(graph);
  }
  time_end = clock() - time_start;
  duration = static_cast<double>(time_end) / CLOCKS_PER_SEC;
  res.push_back(std::make_tuple("Brute Force", result.distance, result.vertices,
                                duration));

  return res;
}
