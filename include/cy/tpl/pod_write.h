#pragma once

namespace tpl {
template <typename Stream, typename Pod>
constexpr decltype(auto) pod_write(Stream &stream, const Pod &pod) noexcept {
  return stream.write(reinterpret_cast<const char *>(&pod), sizeof(pod));
}
} // namespace tpl