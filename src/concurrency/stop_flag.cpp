#include <cy/concurrency/stop_flag.h>
namespace cy::concurrency {

Stop_flag::Stop_flag() { stopped_.clear(std::memory_order::release); }
bool Stop_flag::is_stopped() const {
  return stopped_.test(std::memory_order::acquire);
}
void Stop_flag::stop() { stopped_.test_and_set(std::memory_order::release); }
} // namespace cy::concurrency