
#include "cy/text/time.h"
#include <iostream>
int main(int argc, char **argv) {
  std::cout << cy::text::local_date_str() << "\n";
  std::cout << cy::text::local_hour_minute_seconds_str() << "\n";
}