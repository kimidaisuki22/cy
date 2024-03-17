#include <cy/experiment/coroutine/scheduler_pack.h>
namespace cy::experiment::coroutine {

Scheduler_pack::Scheduler_pack(size_t io_count, size_t compute_count)
    : io_balance_{io_count}, compute_balance_{compute_count} {

  io_threads_.resize(io_count);
  compute_threads_.resize(compute_count);
  for (auto &p : io_threads_) {
    p = std::make_unique<Scheduler>();
  }
  for (auto &p : compute_threads_) {
    p = std::make_unique<Scheduler>();
  }
}
} // namespace cy::experiment::coroutine
