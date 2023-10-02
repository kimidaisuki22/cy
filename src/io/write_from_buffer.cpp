#include <cy/io/write_from_buffer.h>
namespace cy::io {
bool write_from_buffer(std::span<const char> buffer, std::ostream &out_stream) {
  out_stream.write(buffer.data(), buffer.size());
  return out_stream.good();
}
bool write_from_buffer(std::span<const uint8_t> buffer,
                       std::ostream &out_stream) {
  return write_from_buffer(
      std::span<const char>(reinterpret_cast<const char *>(buffer.data()),
                            buffer.size()),
      out_stream);
}
} // namespace cy::io