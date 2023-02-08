#ifndef SRC_MODEL_ALGORITHMS_ACO_H_
#define SRC_MODEL_ALGORITHMS_ACO_H_

#include "../TsmResult.h"
#include "../graph.h"
#include "ant.h"

class ACO {
 public:
  explicit ACO(Graph &graph);
  ACO(const ACO &other) = delete;
  ACO(const ACO &&other) = delete;
  ACO &operator=(const ACO &other) = delete;
  ACO &operator=(const ACO &&other) = delete;
  ~ACO() {}

  TsmResult &InitAlgorithm();

 private:
  TsmResult res_;
  int num_ants_;
  int num_cities_;
  std::vector<Ant *> ants_;

  Matrix distance_;
  Matrix pheromones_;

  void InitPheromones();
  void InitColony();
  void UpdatePheromones();
  void UpdateResult(int &lapcounter);
  void DeleteColony();
};

#endif  // SRC_MODEL_ALGORITHMS_ACO_H_
