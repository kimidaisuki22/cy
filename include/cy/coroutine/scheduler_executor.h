#pragma once
#include <cy/concurrency/stop_flag.h>
#include <cy/coroutine/coroutine_scheduler.h>
#include <cy/coroutine/scheduler_pack.h>
#include <cy/coroutine/switch_scheduler.h>
#include <vector>
#include <thread>

namespace cy::coroutine {
class Scheduler_executor {
public:
  Scheduler_executor(Scheduler_pack &pack);
  // process all coroutine in need execute in main thread.
  // call in the main loop.
  void main_task();

  void stop();
  void wait_all();

  void spawn_scheduler_to_thread(Coroutine_scheduler &scheduler);
  int get_working_count() const;

private:
  static void scheduler_thread_task(Coroutine_scheduler &scheduler,
                                    concurrency::Stop_flag &stop_flag,
                                    std::atomic_int &working_count);
  Scheduler_pack *pack_{};
  std::vector<std::thread> working_threads_;
  concurrency::Stop_flag stop_flag_{};
  std::atomic_int working_count_{};
};

} // namespace cy::coroutine
