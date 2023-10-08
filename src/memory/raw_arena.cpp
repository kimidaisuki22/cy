#include <cstddef>
#include <cy/memory/raw_arena.h>
#include <malloc/_malloc.h>
#include <span>
namespace {
constexpr size_t calculate_padded_size(size_t raw, size_t alignment) noexcept {
  auto dif = raw % alignment;
  return dif ? raw + alignment - dif : raw;
}
} // namespace
namespace cy::memory {
Raw_arena::~Raw_arena() {
  for (auto buffer : buffers_to_free_) {
    free(buffer);
  }
}
void Raw_arena::create_new_buffer() {
  auto pt = malloc(block_size_);
  buffers_to_free_.push_back(pt);
  ready_buffer_.push_back(
      std::span<char>{reinterpret_cast<char *>(pt), block_size_});
}
void *Raw_arena::handle_small_buffer(size_t buffer_size) {
  size_t buffer_index = ready_buffer_.size();
  auto task_buffer = [buffer_size, this](size_t idx) -> void * {
    auto &buffer = ready_buffer_[idx - 1];
    if (buffer_size <= buffer.size()) {
      auto pt = buffer.data();
      buffer = buffer.subspan(buffer_size);

      if (buffer.size() == 0) {
        std::swap(ready_buffer_.back(), ready_buffer_[idx]);
      }
      ready_buffer_.pop_back();

      return pt;
    }
    return nullptr;
  };
  for (; buffer_index != 0; buffer_index--) {
    auto buffer = task_buffer(buffer_index);
    if (buffer) {
      return buffer;
    }
  }
  create_new_buffer();
  return task_buffer(ready_buffer_.size() - 1);
}

void *Raw_arena::handle_large_buffer(size_t buffer_size) {
  auto buffer = malloc(buffer_size);
  buffers_to_free_.push_back(buffer);
  return buffer;
}
void *Raw_arena::alloc(size_t buffer_size) {
  buffer_size = calculate_padded_size(buffer_size, minimize_alloc_size_);
  if (buffer_size >= this->minimize_alloc_size_) {
    return handle_large_buffer(buffer_size);
  } else {
    return handle_small_buffer(buffer_size);
  }
}
} // namespace cy::memory