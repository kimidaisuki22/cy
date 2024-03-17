#pragma once
#include <cstddef>
namespace cy::iteration {
class Round_robin {
public:
  Round_robin(size_t work_set_size) : max_{work_set_size} {}
  size_t next();
  void change_work_set_size(size_t size);

private:
  size_t current_{};
  size_t max_{};
};
} // namespace cy::iteration