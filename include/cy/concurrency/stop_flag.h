#pragma once
#include <atomic>
namespace cy::concurrency {
class Stop_flag {
public:
  Stop_flag();
  bool is_stopped() const;
  void stop();

private:
  std::atomic_flag stopped_;
};
} // namespace cy::concurrency