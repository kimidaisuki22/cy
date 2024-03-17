#include <cy/experiment/coroutine/scheduler_executor.h>
namespace cy::experiment::coroutine {

Scheduler_executor::Scheduler_executor(Scheduler_pack &pack) : pack_{&pack} {
  for (auto &io : pack.io_threads_) {
    spawn_scheduler_to_thread(*io);
  }
  for (auto &compute : pack.compute_threads_) {
    spawn_scheduler_to_thread(*compute);
  }
}
void Scheduler_executor::main_task() {
  while (!pack_->main_thread_.empty()) {
    pack_->main_thread_.pop().resume();
  }
}
void Scheduler_executor::stop() {
  stop_flag_.stop();
  for (auto &io : pack_->io_threads_) {
    io->notify();
  }
  for (auto &compute : pack_->compute_threads_) {
    compute->notify();
  }
}
void Scheduler_executor::wait_all() {
  for (auto &t : working_threads_) {
    t.join();
  }
}
void Scheduler_executor::spawn_scheduler_to_thread(
    Coroutine_scheduler &scheduler) {
  std::thread t([&] { scheduler_thread_task(scheduler, stop_flag_); });
  working_threads_.push_back(std::move(t));
}
void Scheduler_executor::scheduler_thread_task(
    Coroutine_scheduler &scheduler, concurrency::Stop_flag &stop_flag) {
  while (true) {
    scheduler.wait([&stop_flag] { return stop_flag.is_stopped(); });
    if (stop_flag.is_stopped()) {
      break;
    }

    while (!scheduler.empty()) {
      scheduler.pop().resume();
      if (stop_flag.is_stopped()) {
        break;
      }
    }
  }
}
} // namespace cy::experiment::coroutine
