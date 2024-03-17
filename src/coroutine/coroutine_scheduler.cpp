#include <cy/coroutine/coroutine_scheduler.h>
namespace cy::coroutine {
void Coroutine_scheduler::notify() { wait_wake_up_.notify_one(); }
Coroutine_scheduler::Handle Coroutine_scheduler::pop() {
  Handle h;
  {
    std::unique_lock lock{mutex_};
    h = handles_.front();
    handles_.pop_front();
  }
  return h;
}
bool Coroutine_scheduler::empty() const { return handles_.empty(); }
void Coroutine_scheduler::add(Handle handle) {
  {
    std::unique_lock lock{mutex_};
    handles_.push_back(handle);
  }
  wait_wake_up_.notify_one();
}
} // namespace cy::coroutine
