#include "stdio.h"
#include "stdlib.h"

#ifndef OPT_LEVEL
#define OPT_LEVEL "Opt level not specified."
#endif

int main(int argc, char** argv) {
  if (argc >= 2) {
    fprintf(stderr,
            "mul_loop running with optimization level: %s, argv[0]: %s\n",
            OPT_LEVEL, argv[1]);
  }
  return 0;
}