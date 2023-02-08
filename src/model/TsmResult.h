#ifndef SRC_MODEL_TSMRESULT_H_
#define SRC_MODEL_TSMRESULT_H_

#include <limits>
#include <vector>

struct TsmResult {
  std::vector<int> vertices{};
  double distance = std::numeric_limits<double>::infinity();
};

#endif  // SRC_MODEL_TSMRESULT_H_
