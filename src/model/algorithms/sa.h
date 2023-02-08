#ifndef SRC_MODEL_ALGORITHMS_SA_H_
#define SRC_MODEL_ALGORITHMS_SA_H_

#include <iostream>
#include <random>
#include <set>

#include "../TsmResult.h"
#include "../graph.h"
#include "../matrix/matrix.h"

const double T = 0.01;
const double y = 0.99;

class SimulatedAnnealing {
 public:
  explicit SimulatedAnnealing(Graph &graph);
  SimulatedAnnealing(const SimulatedAnnealing &other) = delete;
  SimulatedAnnealing(const SimulatedAnnealing &&other) = delete;
  SimulatedAnnealing &operator=(const SimulatedAnnealing &other) = delete;
  SimulatedAnnealing &operator=(const SimulatedAnnealing &&other) = delete;
  ~SimulatedAnnealing() {}

  TsmResult &InitAlgorithm();

 private:
  TsmResult res_;
  unsigned int num_cities_;
  Matrix distance_;
  std::set<int> freetovisit_;

  void GenerateBase();
  void InitFreeToVisit();
  int RandomGenerate(int max);
  void PushAndErase(int value);
  std::vector<int> FillFreeToVisit();
  double CountCost(std::vector<int> &v);
  TsmResult ChangeBase();
  double CalcProbability(double new_distance, double Ti);
};

#endif  // SRC_MODEL_ALGORITHMS_SA_H_
