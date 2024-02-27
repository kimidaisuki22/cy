#include "cy/experiment/coroutine/simple_generator.h"
#include "cy/experiment/coroutine/simple_task.h"

#include <coroutine>
#include <functional>
#include <gtest/gtest.h>
#include <numeric>
#include <vector>

cy::experiment::coroutine::Simple_generator<int> one_to_ten() {
  for (int i = 0; i <= 10; i++) {
    co_yield i;
  }
}

cy::experiment::coroutine::Simple_task<int> count_n(int n) {
  int sum{};
  for (int i = 0; i <= n; i++) {
    co_await std::suspend_always{};
    std::cout << "Count " << i << "\n";
    sum += i;
  }
  co_return sum;
}

cy::experiment::coroutine::Simple_task<int> count_up() {
  auto gen = one_to_ten();
  int result{};
  for (auto i : gen) {
    std::cout << "suspend 1\n";
    co_await std::suspend_always{};
    std::cout << "add 1\n";
    result += i;
    std::cout << "suspend 2\n";
    co_await std::suspend_always{};
  }
  std::cout << "await sub task\n";
  int to_10 = co_await count_n(10);
  std::cout << "await sub task done\n";
  EXPECT_EQ(result, to_10);
  co_return result;
}

TEST(Coroutine, simple_coroutine) {
  std::vector<int> a, b;
  for (int i = 0; i <= 10; i++) {
    a.push_back(i);
  }
  for (auto i : one_to_ten()) {
    b.push_back(i);
  }
  EXPECT_EQ(a, b);

  auto task = count_up();
  task.execute_to_done();
  int sum{};
  for (auto e : a) {
    sum += e;
  }
  EXPECT_EQ(task.getValue().value(), sum);
}