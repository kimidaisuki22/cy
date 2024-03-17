#include "cy/experiment/coroutine/scheduler_check.h"
#include "cy/experiment/coroutine/scheduler_executor.h"
#include "cy/experiment/coroutine/scheduler_pack.h"
#include "cy/experiment/coroutine/simple_generator.h"
#include "cy/experiment/coroutine/simple_task.h"

#include <gtest/gtest.h>
#include <vector>

cy::experiment::coroutine::Simple_generator<int> one_to_ten() {
  for (int i = 0; i <= 10; i++) {
    co_yield i;
  }
}
cy::experiment::coroutine::Simple_task<int>
f_task(cy::experiment::coroutine::Scheduler_pack &schedulers, int index,
       int &output) {

  co_await schedulers.await_io();

  co_await schedulers.await_main();

  std::cout << "IO : " << index << "\n";
  co_await schedulers.await_compute();

  for (int i = 0; i < 10; i++) {
    std::vector<char> ch;
    ch.resize(1024);
    memset(ch.data(), 0, ch.size());
  }
  co_await schedulers.await_main();
  std::cout << "Done " << index << " \n";
  output += 1;
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
  int output = 0;
  for (int i = 0; i < 20; i++) {
    f_task(schedulers, i, output);
  }

  for (int i = 0; !cy::experiment::coroutine::is_no_task(schedulers); i++) {
    std::this_thread::sleep_for(std::chrono::seconds{1});
    std::cout << "Tick " << i << "\n";
    exe.main_task();
  }

  exe.stop();
  exe.wait_all();
  EXPECT_EQ(output, 20);
}