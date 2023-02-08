#include "graph.h"

void Graph::LoadGraphFromFile(std::string filename) {
  std::ifstream file(filename);
  ParsingFile(file);
}

void Graph::ParsingFile(std::ifstream& file) {
  if (file.is_open()) {
    std::string line;
    std::getline(file, line);
    Size(line);
    CreateMatrix();
    for (auto i = 0; i < rows_; i++) {
      std::getline(file, line);
      FillingInTheMatrix(line, i);
    }
    file.close();
    GraphType();
  } else {
    throw std::invalid_argument("No such file!");
  }
}

void Graph::Size(const std::string& line) { rows_ = cols_ = std::stoi(line); }

void Graph::CreateMatrix() { matrix_ = Matrix(rows_); }

void Graph::FillingInTheMatrix(std::string& line, int row) {
  std::string::size_type size = 0;
  for (auto j = 0; j < cols_; j++) {
    matrix_(row, j) = std::stoi(line, &size);
    line.erase(0, size + 1);
  }
}

void Graph::GraphType() {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      if (matrix_(i, j) != matrix_(j, i)) directed_ = 1;
      if (matrix_(i, j) > 1) weighted_ = 1;
      if (matrix_(i, j) < 0) negative_ = 1;
    }
  }
}

void Graph::GraphClear() {
  matrix_.SetToZero();
  rows_ = 0, cols_ = 0;
  directed_ = 0, weighted_ = 0, negative_ = 0;
}

void Graph::ExportGraphToDot(const std::string& filename) {
  std::vector<bool> used(matrix_.GetSize());
  std::ofstream save_file;
  save_file.open(filename);
  if (!directed_) {
    save_file << "graph graphname {" << '\n';
  } else {
    save_file << "digraph graphname {" << '\n';
  }
  for (auto i = 0; i < rows_; i++) {
    save_file << i + 1 << ";\n";
  }
  if (weighted_) {
    AddDataWToFile(save_file, used);

  } else {
    AddDataToFile(save_file, used);
  }
  used.clear();
  save_file << "}" << '\n';
  save_file.close();
  std::ifstream checkup(filename);
  if (checkup.peek() == std::ifstream::traits_type::eof()) {
    throw std::logic_error("File is empty!");
  }
}

void Graph::AddDataToFile(std::ofstream& file, std::vector<bool>& used) {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      if (directed_) {
        if (matrix_(i, j) != 0) {
          file << i + 1 << " -> " << j + 1 << ";\n";
        }
      } else if (matrix_(i, j) != 0 && used[j] == 0) {
        file << i + 1 << " -- " << j + 1 << ";\n";
      }
      used[i] = 1;
    }
  }
}

void Graph::AddDataWToFile(std::ofstream& file, std::vector<bool>& used) {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      if (directed_) {
        if (matrix_(i, j) != 0) {
          file << i + 1 << " -> " << j + 1 << " [label = " << matrix_(i, j)
               << ", weight = " << matrix_(i, j) << "];" << '\n';
        }
      } else if (matrix_(i, j) != 0 && used[j] == 0) {
        file << i + 1 << " -- " << j + 1 << " [label = " << matrix_(i, j)
             << ", weight = " << matrix_(i, j) << "];" << '\n';
      }
      used[i] = 1;
    }
  }
}
