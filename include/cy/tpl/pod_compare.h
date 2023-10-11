#pragma once
// TODO: add concept to check copy pod type only.
#include <cstring>
namespace tpl {
template <typename T, typename U>
constexpr bool pod_is_same(const T &lhs, const U &rhs) noexcept {
  static_assert(sizeof(lhs) == sizeof(rhs),
                "pod is same should only call on file that has same size.");
  return std::memcmp(&lhs,&rhs,sizeof(lhs)) == 0;
}
} // namespace tpl