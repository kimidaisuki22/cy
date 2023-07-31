#include <algorithm>
#include <cy/proc/executable.h>
#include <stdio.h>
#include <string>

#include <cstdio>
#include <string>
namespace {
class Tiny_buffer {
public:
  std::string pop_buffer() noexcept {
    impl_.resize(real_size_);
    real_size_ = 0;
    return std::move(impl_);
  }
  char *get_write_point() {
    realloc_buffer();
    return impl_.data() + real_size_;
  }
  size_t get_writeable_size() const noexcept {
    return impl_.size() - real_size_;
  }
  void update_write_count(size_t write_delta) noexcept {
    real_size_ += write_delta;
  }

private:
  void realloc_buffer() {
    if (impl_.size() < preserve_size_ + real_size_) {
      impl_.resize(std::max(preserve_size_ + real_size_, impl_.size() * 2));
    }
  }

  std::string impl_;
  size_t preserve_size_ = 1024;
  size_t real_size_ = 0;
};
void append_zero(Tiny_buffer &buffer) {
  *buffer.get_write_point() = 0;
  buffer.update_write_count(1);
}
#ifdef _WIN32
const auto popen = _popen;
const auto pclose = _pclose;
#endif
} // namespace

namespace cy::proc {
std::string execute_command(std::string command) {
  FILE *pipe = popen(command.c_str(), "r");
  if (pipe == NULL) {
    return {};
  }
  Tiny_buffer buffer;

  while (true) {
    auto start = buffer.get_write_point();
    auto result = fgets(start, buffer.get_writeable_size(), pipe);
    if (!result) {
      break;
    }
    auto end = std::find(start, start + buffer.get_writeable_size(), '\0');
    auto readed_count = end - start;

    buffer.update_write_count(readed_count);
  }

  if (pclose(pipe) != 0) {
  }
  append_zero(buffer);

  return buffer.pop_buffer();
}
} // namespace cy::proc