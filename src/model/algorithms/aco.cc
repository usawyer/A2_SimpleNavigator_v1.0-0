#include "aco.h"

ACO::ACO(Graph& graph) : distance_(graph.GetGraph()) {
  num_cities_ = num_ants_ = graph.GetSize();
}

void ACO::InitPheromones() {
  pheromones_ = Matrix(distance_.GetSize());
  const int pheromones_size = pheromones_.GetSize();
  const double initial_pheromones = 0.5;
  for (int i = 0; i < pheromones_size; ++i) {
    for (int j = 0; j < pheromones_size; ++j) {
      if (i != j) pheromones_(i, j) = initial_pheromones;
    }
  }
}

void ACO::InitColony() {
  for (int i = 0; i < num_ants_; i++) {
    ants_.push_back(new Ant(i, &distance_, &pheromones_));
  }
}

void ACO::UpdatePheromones() {
  pheromones_ *= kRemainigPheromone;
  for (std::vector<Ant*>::size_type i = 0; i < ants_.size(); i++) {
    pheromones_ += ants_[i]->GetAdditive();
  }
}

void ACO::UpdateResult(int& lapcounter) {
  for (auto& ant : ants_) {
    if (ant->GetCost() < res_.distance) {
      res_.distance = ant->GetCost();
      res_.vertices = ant->GetPath();
      lapcounter = 0;
    }
    ant->CleanAnt();
  }
}

TsmResult& ACO::InitAlgorithm() {
  InitPheromones();
  InitColony();
  for (int i = 0; i < kLapCounter; i++) {
    for (auto& ant : ants_) {
      ant->StartCircle();
    }
    UpdatePheromones();
    UpdateResult(i);
  }
  DeleteColony();
  return res_;
}

void ACO::DeleteColony() {
  for (auto& ant : ants_) {
    delete ant;
    ant = nullptr;
  }
  ants_.clear();
}
