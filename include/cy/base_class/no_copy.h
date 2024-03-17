#pragma once

namespace cy::base_class {
struct No_copy {
  No_copy() = default;
  No_copy(const No_copy &) = delete;
  No_copy &operator=(const No_copy &) = delete;
  No_copy(No_copy &&) = default;
  No_copy &operator=(No_copy &&) = default;
};
} // namespace cy::base_class