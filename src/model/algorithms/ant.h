#ifndef SRC_MODEL_ALGORITHMS_ANT_H_
#define SRC_MODEL_ALGORITHMS_ANT_H_

#include <random>
#include <set>
#include <vector>

#include "../matrix/matrix.h"

const int kLapCounter = 30;
const double kAlpha = 1.0;
const double kBeta = 1.0;
const double kQ = 1.0;
const double kRemainigPheromone = 0.75;

class Ant {
 public:
  Ant(int index, Matrix* distance, Matrix* pheromones);
  Ant(const Ant& other) = delete;
  Ant(const Ant&& other) = delete;
  Ant& operator=(const Ant& other) = delete;
  Ant& operator=(const Ant&& other) = delete;
  ~Ant() {}

  void StartCircle();
  void CleanAnt();
  double& GetCost() { return cost_; }
  std::vector<int>& GetPath() { return path_; }
  Matrix& GetAdditive() { return additive_; }

 private:
  int position_;
  std::vector<int> freetovisit_;
  std::set<int> remain_to_visit_;
  std::vector<int> path_;
  double cost_;
  Matrix additive_;

  Matrix* distance_ = nullptr;
  Matrix* pheromones_ = nullptr;

  void InitRemainToVisit();
  void PushAndErase(int value);
  void FillFreeToVisit();
  void ChosePath();
  double TauMulEta(int point, int i);
  int WhichCoordinate(std::vector<double>& choice);
  double RandomChoice();
  void CalcPath();
  void CalcPheromones();
};

#endif  // SRC_MODEL_ALGORITHMS_ANT_H_
