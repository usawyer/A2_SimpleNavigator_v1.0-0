#include "sa.h"

SimulatedAnnealing::SimulatedAnnealing(Graph& graph) {
  num_cities_ = graph.GetSize();
  distance_ = graph.GetGraph();
}

void SimulatedAnnealing::GenerateBase() {
  InitFreeToVisit();
  PushAndErase(RandomGenerate(num_cities_));
  std::vector<int> choice = FillFreeToVisit();
  while (!choice.empty()) {
    int value = RandomGenerate(choice.size());
    PushAndErase(choice[value - 1]);
    choice = FillFreeToVisit();
  }
  if (res_.vertices.size() == num_cities_ &&
      distance_(res_.vertices.back() - 1, res_.vertices[0] - 1) != 0) {
    res_.distance = CountCost(res_.vertices);
  } else {
    res_.vertices.clear();
  }
}

void SimulatedAnnealing::InitFreeToVisit() {
  for (unsigned int i = 1; i < num_cities_ + 1; i++) {
    freetovisit_.insert(i);
  }
}

void SimulatedAnnealing::PushAndErase(int value) {
  res_.vertices.push_back(value);
  freetovisit_.erase(value);
}

std::vector<int> SimulatedAnnealing::FillFreeToVisit() {
  std::vector<int> choice;
  for (auto it = freetovisit_.begin(); it != freetovisit_.end(); ++it) {
    if (distance_(res_.vertices.back() - 1, (*it) - 1) != 0)
      choice.push_back(*it);
  }
  return choice;
}

int SimulatedAnnealing::RandomGenerate(int max) {
  std::random_device random;
  std::mt19937 gen(random());
  std::uniform_int_distribution<> distrib(1, max);
  return distrib(gen);
}

double SimulatedAnnealing::CountCost(std::vector<int>& v) {
  double cost = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    double num;
    if (it == v.end() - 1) {
      num = v[0] - 1;
    } else {
      num = *(it + 1) - 1;
    }
    if ((distance_)(*it - 1, num) != 0) {
      cost += (distance_)(*it - 1, num);
    } else {
      return INFINITY;
    }
  }
  return cost;
}

TsmResult& SimulatedAnnealing::InitAlgorithm() {
  GenerateBase();
  if (res_.vertices.size() != 0) {
    double Ti = 100.0;
    while (Ti > T) {
      TsmResult new_base = ChangeBase();
      if (new_base.distance < res_.distance) {
        res_ = new_base;
      } else if (!std::isinf(new_base.distance) &&
                 new_base.distance > res_.distance) {
        if (CalcProbability(new_base.distance, Ti) > RandomGenerate(100)) {
          res_ = new_base;
        }
      }
      Ti *= y;
    }
    res_.vertices.push_back(res_.vertices[0]);
  }
  return res_;
}

TsmResult SimulatedAnnealing::ChangeBase() {
  int i = RandomGenerate(res_.vertices.size()) - 1;
  int j = RandomGenerate(res_.vertices.size()) - 1;
  TsmResult tmp = res_;
  std::swap(tmp.vertices[i], tmp.vertices[j]);
  tmp.distance = CountCost(tmp.vertices);
  return tmp;
}

double SimulatedAnnealing::CalcProbability(double new_distance, double Ti) {
  return 100.0 * exp(-(new_distance - res_.distance) / Ti);
}
