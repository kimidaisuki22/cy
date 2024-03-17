#include "cy/experiment/coroutine/await_event_board_cast.h"
#include "cy/experiment/coroutine/scheduler_executor.h"
#include "cy/experiment/coroutine/scheduler_pack.h"
#include "cy/experiment/coroutine/simple_generator.h"
#include "cy/experiment/coroutine/simple_task.h"
#include "cy/experiment/coroutine/stream_generator.h"

#include <atomic>
#include <chrono>
#include <gtest/gtest.h>
#include <thread>
#include <vector>

cy::experiment::coroutine::Simple_generator<int> one_to_ten() {
  for (int i = 0; i <= 10; i++) {
    co_yield i;
  }
}

cy::experiment::coroutine::Simple_task<int>
f_sleep(cy::experiment::coroutine::Scheduler_pack &schedulers, int second) {
  co_await schedulers.await_io();
  std::this_thread::sleep_for(std::chrono::seconds{second});
  co_return second;
}

cy::experiment::coroutine::Simple_task<int>
f_task(cy::experiment::coroutine::Scheduler_pack &schedulers, int index,
       int &output, int &count_down) {

  co_await schedulers.await_io();

  co_await schedulers.await_main();

  std::cout << "IO : " << index << "\n";
  co_await schedulers.await_compute();

  for (int i = 0; i < 10; i++) {
    std::vector<char> ch;
    ch.resize(1024);
    memset(ch.data(), 0, ch.size());
  }

  int time = co_await f_sleep(schedulers, index / 10);

  co_await schedulers.await_main();
  std::cout << "Done " << index << " for " << time << " seconds\n";
  output += 1;
  count_down--;
  co_return 0;
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
}

TEST(Coroutine, simple_task) {
  cy::experiment::coroutine::Scheduler_pack schedulers{10, 10};
  cy::experiment::coroutine::Scheduler_executor exe{schedulers};
  const int task_count = 20;
  std::atomic_int count_down{task_count};
  int running = task_count;
  int output = 0;
  for (int i = 0; i < task_count; i++) {
    f_task(schedulers, i, output, running);
  }
  // when there is no remain task, there may have some tasks is running.
  for (int i = 0; running; i++) {
    std::this_thread::sleep_for(std::chrono::seconds{1});
    std::cout << "Tick " << i << "\n";
    exe.main_task();
  }

  exe.stop();
  exe.wait_all();
  EXPECT_EQ(output, 20);
}

TEST(Coroutine, board_cast) {
  const int task_count = 20;
  int running = task_count;
  int output = 0;

  cy::experiment::coroutine::Awaitable_event_board_cast<int> number_provider;

  auto f =
      [](cy::experiment::coroutine::Awaitable_event_board_cast<int> &number,
         int &output,
         int &count_down) -> cy::experiment::coroutine::Simple_task<int> {
    auto n = co_await number.await();
    output += n * 2;

    count_down--;
    co_return 0;
  };
  for (int i = 0; i < task_count; i++) {
    f(number_provider, output, running);
  }
  const int input = 42;
  const int target_output = input * task_count * 2;
  EXPECT_EQ(number_provider.send_event(input), task_count);

  EXPECT_EQ(running, 0);
  EXPECT_EQ(output, target_output);
}

TEST(Coroutine, stream) {
  const int task_count = 20;

  auto f =
      [](int mux) -> cy::experiment::coroutine::Stream_generator<int, int> {
    int input = 0;
    int output = 0;
    while ((input = co_yield output)) {
      output = input * mux;
    }
  };
  int mux_value = 42;
  auto mux = f(mux_value);
  for (int i = 1; i < task_count; i++) {
    EXPECT_EQ(i * mux_value, mux(i));
  }
}