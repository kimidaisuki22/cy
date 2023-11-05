#pragma once
#include <cstddef>
#include <cstring>

// TODO: add concept to check copy pod type only.
namespace tpl {
template <typename T, typename U>
constexpr void pod_copy(const T &from, U &to) noexcept {
  static_assert(sizeof(from) == sizeof(to),
                "pod copy should only copy on file that has same size.");
  memcpy(&to, &from, sizeof(from));
}
template <size_t size, size_t offset = 0, typename T, typename U>
constexpr void pod_copy_slice(const T &from, U &to) noexcept {
  static_assert(size + offset <= sizeof(from),
                "copy has out of range for source.");
  static_assert(size + offset <= sizeof(to), "copy has out of range for destination.");
  memcpy(reinterpret_cast<char *>(&to) + offset,
         reinterpret_cast<const char *>(&from) + offset, size);
}
} // namespace tpl