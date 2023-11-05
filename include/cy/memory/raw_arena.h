#pragma once

#include <cstddef>
#include <span>
#include <vector>
namespace cy::memory {
class Raw_arena {
public:
  Raw_arena(size_t block_size, size_t minimize_alloc_size = 8);
  ~Raw_arena();
  void *alloc(size_t buffer_size);
  void rewind();

private:
  void *handle_large_buffer(size_t buffer_size);
  void *handle_small_buffer(size_t buffer_size);
  void create_new_buffer();

  std::vector<std::span<char>> ready_buffer_;
  std::vector<void *> buffers_to_free_;
  size_t block_size_;
  size_t minimize_alloc_size_;
};
} // namespace cy::memory