
#include "cy/text/time.h"
#include <iostream>
int main(int argc, char **argv) {
  std::cout << cy::text::local_date_str() << "\n";
}