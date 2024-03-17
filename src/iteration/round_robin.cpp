#include <cy/iteration/round_robin.h>
size_t cy::iteration::Round_robin::next() {
  auto v = current_;
  current_++;
  if (current_ >= max_) {
    current_ = 0;
  }
  return v;
}
void cy::iteration::Round_robin::change_work_set_size(size_t size) {
  max_ = size;
  if (max_ > current_) {
    current_ = 0;
  }
}
