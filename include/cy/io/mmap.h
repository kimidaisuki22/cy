#pragma once
#include <string>

namespace cy::io {

class Mmap_file_reader {
public:
  Mmap_file_reader(const std::string &file_name);
  ~Mmap_file_reader();

  const void *data() const;
  template <typename T> const T *data() const {
    return reinterpret_cast<const T *>(data());
  }
  size_t size() const;

private:
#ifdef _WIN32
  using HANDLE = void *;
  HANDLE file_handle_;
  HANDLE map_handle_;
#elif __APPLE__ || __linux__
  int file_descriptor_;
#endif
  void *data_;
  size_t size_;
};
} // namespace cy::io
