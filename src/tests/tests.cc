#include <gtest/gtest.h>

#include "../model/graph_algorithms.h"

TEST(graph, Load) {
  Graph graph;
  graph.LoadGraphFromFile("tests/graphs/1.txt");
  EXPECT_EQ(graph.GetSize(), 11);
}

// TEST(graph, LoadThrow) {
//   Graph graph;
//   EXPECT_ANY_THROW(graph.LoadGraphFromFile("tests/graphs/666.txt"));
// }

TEST(graph, GraphType) {
  Graph graph;
  graph.LoadGraphFromFile("tests/graphs/1.txt");
  EXPECT_EQ(graph.GetDirectType(), 0);
  EXPECT_EQ(graph.GetWeightType(), 1);
}

TEST(graph, GraphType2) {
  Graph graph;
  graph.LoadGraphFromFile("tests/graphs/4.txt");
  EXPECT_EQ(graph.GetDirectType(), 1);
  EXPECT_EQ(graph.GetWeightType(), 1);
}

TEST(graph, ExportGraphToDot) {
  Graph graph;
  graph.LoadGraphFromFile("tests/graphs/1.txt");
  graph.ExportGraphToDot("test_graph.dot");
  SUCCEED();
}
TEST(graph, ExportGraphToDot2) {
  Graph graph;
  graph.LoadGraphFromFile("tests/graphs/5.txt");
  graph.ExportGraphToDot("test_graph2.dot");
  SUCCEED();
}

TEST(graph_algorithms, DepthFirstSearch) {
  Graph graph;
  graph.LoadGraphFromFile("tests/graphs/1.txt");
  GraphAlgorithms algorithm;
  std::vector<int> res = algorithm.DepthFirstSearch(graph, 1);
  std::vector<int> vec{1, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2};
  EXPECT_EQ(res, vec);
}

TEST(graph_algorithms, BreadthFirstSearch) {
  Graph graph;
  graph.LoadGraphFromFile("tests/graphs/1.txt");
  GraphAlgorithms algorithm;
  std::vector<int> res = algorithm.BreadthFirstSearch(graph, 1);
  std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  EXPECT_EQ(res, vec);
}

TEST(graph_algorithms, GetShortestPathBetweenVertices) {
  Graph graph;
  graph.LoadGraphFromFile("tests/graphs/1.txt");
  GraphAlgorithms algorithm;
  int res = algorithm.GetShortestPathBetweenVertices(graph, 1, 11);
  EXPECT_EQ(res, 18);
}

TEST(graph_algorithms, GetShortestPathsBetweenAllVertices) {
  Graph graph;
  graph.LoadGraphFromFile("tests/graphs/3.txt");
  GraphAlgorithms algorithm;
  Matrix res = algorithm.GetShortestPathsBetweenAllVertices(graph);
  Matrix result(
      4, {{0, 10, 17, 10}, {10, 0, 10, 10}, {17, 10, 0, 10}, {10, 10, 10, 0}});
  EXPECT_TRUE(res.EqMatrix(result));
}

TEST(graph_algorithms, GetLeastSpanningTree) {
  Graph graph;
  graph.LoadGraphFromFile("tests/graphs/3.txt");
  GraphAlgorithms algorithm;
  Matrix res = algorithm.GetLeastSpanningTree(graph);
  Matrix result(4,
                {{0, 10, 0, 10}, {10, 0, 10, 0}, {0, 10, 0, 0}, {10, 0, 0, 0}});
  EXPECT_TRUE(res.EqMatrix(result));
}

TEST(graph_algorithms, AntColonyOptimization) {
  Graph graph;
  graph.LoadGraphFromFile("tests/graphs/3.txt");
  GraphAlgorithms algorithm;
  TsmResult res = algorithm.TSPAntColonyOptimization(graph);
  EXPECT_EQ(res.distance, 40);
}

TEST(graph_algorithms, ComparisonTSP) {
  Graph graph;
  graph.LoadGraphFromFile("tests/graphs/3.txt");
  GraphAlgorithms algorithm;
  std::vector<std::tuple<std::string, double, std::vector<int>, double>> res =
      algorithm.TSPComparison(graph, 1);
  for (auto [A, B, C, D] : res) {
    EXPECT_EQ(B, 40);
  }
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
