#include <benchmark/benchmark.h>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <cy/memory/raw_arena.h>
#include <vector>
namespace {
void raw_set(void *pt, size_t size) { memset(pt, 0xfa, size); }
const int block_size = 64;
} // namespace
static void BM_malloc(benchmark::State &state) {
  auto count = state.range(0);
  std::vector<void *> buffer;
  for (auto _ : state) {

    for (int i = 0; i < count; i++) {
      auto pt = malloc(block_size);
      raw_set(pt, block_size);
      buffer.push_back(pt);
    }
    for (auto p : buffer) {
      free(p);
    }
    buffer.clear();
  }
}
// Register the function as a benchmark
BENCHMARK(BM_malloc)->RangeMultiplier(2)->Range(1, 1 << 16);

// Define another benchmark
static void BM_arena(benchmark::State &state) {
  cy::memory::Raw_arena arena(block_size * 512);
  auto count = state.range();
  for (auto _ : state) {

    for (int i = 0; i < count; i++) {
      auto pt = arena.alloc(block_size);
      raw_set(pt, block_size);
    }
    arena.rewind();
  }
}
BENCHMARK(BM_arena)->RangeMultiplier(2)->Range(1, 1 << 16);
