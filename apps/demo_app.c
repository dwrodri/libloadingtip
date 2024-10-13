#include "loadingtip.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv) {
  if (argc < 3) {
    perror("./demo_app fortune_text_file fortune_dat_file\n");
  } else {
    show_demo_tip_stderr();
  }
  char *buf = malloc(sizeof(char) * 128);
  if (!buf) {
    free(buf);
  }
  select_random_tip_from_fortune_files(argv[1], argv[2], buf, 128);
}
