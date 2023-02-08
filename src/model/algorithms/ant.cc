#include "ant.h"

Ant::Ant(int index, Matrix* distance, Matrix* pheromones)
    : position_(index), distance_(distance), pheromones_(pheromones) {
  additive_ = Matrix(distance_->GetSize());
  cost_ = std::numeric_limits<double>::infinity();
}

void Ant::InitRemainToVisit() {
  for (unsigned int i = 0; i < (*distance_).GetSize(); i++) {
    remain_to_visit_.insert(i);
  }
}

void Ant::PushAndErase(int value) {
  path_.push_back(value + 1);
  remain_to_visit_.erase(value);
}

void Ant::StartCircle() {
  InitRemainToVisit();
  PushAndErase(position_);
  FillFreeToVisit();
  while (!freetovisit_.empty()) {
    ChosePath();
    PushAndErase(position_);
    FillFreeToVisit();
  }
  if (path_.size() == (*distance_).GetSize() &&
      (*distance_)(position_, path_[0] - 1 != 0)) {
    position_ = path_[0] - 1;
    path_.push_back(path_[0]);
    CalcPath();
    CalcPheromones();
  } else {
    cost_ = std::numeric_limits<double>::infinity();
  }
}

void Ant::FillFreeToVisit() {
  freetovisit_.clear();
  for (auto it = remain_to_visit_.begin(); it != remain_to_visit_.end(); ++it) {
    if ((*distance_)(path_.back() - 1, *it) != 0) freetovisit_.push_back(*it);
  }
}

void Ant::ChosePath() {
  std::vector<double> choice;
  for (std::vector<int>::size_type i = 0; i < freetovisit_.size(); i++) {
    choice.push_back(TauMulEta(position_, freetovisit_[i]));
  }
  double desire = std::accumulate(choice.begin(), choice.end(), 0.0);
  for (size_t i = 0; i < choice.size(); i++) {
    choice[i] /= desire;
  }
  const int index = WhichCoordinate(choice);
  position_ = freetovisit_[index];
}

int Ant::WhichCoordinate(std::vector<double>& choice) {
  double nextpoint = RandomChoice();

  auto it = choice.begin();
  double sum = *it;
  int count = 0;
  while (nextpoint > sum) {
    sum += *(++it);
    count++;
  }
  return count;
}

double Ant::TauMulEta(int point, int it) {
  double tau = pow((*pheromones_)(point, it), kAlpha);
  double eta = pow(1 / (*distance_)(point, it), kBeta);
  return tau * eta;
}

double Ant::RandomChoice() {
  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_real_distribution<> choise(0.0, 1.0);
  return choise(generator);
}

void Ant::CalcPath() {
  cost_ = 0;
  for (auto it = path_.begin(); it != path_.end() - 1; ++it) {
    cost_ += (*distance_)(*it - 1, *(it + 1) - 1);
  }
}

void Ant::CalcPheromones() {
  for (auto it = path_.begin(); it != path_.end() - 1; ++it) {
    additive_(*it - 1, *(it + 1) - 1) = kQ / cost_;
  }
}

void Ant::CleanAnt() {
  freetovisit_.clear();
  remain_to_visit_.clear();
  path_.clear();
  additive_.SetToZero();
}
