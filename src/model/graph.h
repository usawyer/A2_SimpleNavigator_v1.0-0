#ifndef SRC_MODEL_GRAPH_H_
#define SRC_MODEL_GRAPH_H_

#include <fstream>
#include <string>
#include <vector>

#include "matrix/matrix.h"

class Graph {
 public:
  void LoadGraphFromFile(std::string filename);
  void ExportGraphToDot(const std::string& filename);
  Matrix& GetGraph() { return matrix_; }
  int GetSize() { return rows_; }
  bool GetDirectType() { return directed_; }
  bool GetWeightType() { return weighted_; }
  bool GetNegativeType() { return negative_; }
  void GraphClear();

 private:
  Matrix matrix_;
  int rows_ = 0, cols_ = 0;
  bool directed_ = 0, weighted_ = 0, negative_ = 0;

  void Size(const std::string& line);
  void ParsingFile(std::ifstream& file);
  void CreateMatrix();
  void FillingInTheMatrix(std::string& line, int row);
  void GraphType();
  void AddDataToFile(std::ofstream& file, std::vector<bool>& used);
  void AddDataWToFile(std::ofstream& file, std::vector<bool>& used);
};

#endif  // SRC_MODEL_GRAPH_H_
