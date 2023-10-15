#include <cy/shell/shell.h>

int main(int argc, char **argv) {
  if (argc > 1) {
    cy::shell::open(argv[1]);
  } else {
    cy::shell::show(argv[0]);
  }
}