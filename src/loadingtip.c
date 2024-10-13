#include "loadingtip.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char FORTUNE_FILE_DELIM = '%';

// simple demo function
void show_demo_tip_stderr() {
  fprintf(stderr, "This is using libloadingtip!\n");
}

// select a random tip from a list of tips loaded into memory
size_t select_random_tip_from_str_array(const char **tip_list,
                                        const size_t tip_list_size,
                                        const char *tip_out,
                                        const size_t tip_out_buf_size);

void print_index_info(FortuneIndex *index) {
  printf("Version: %u\n", index->version);
  printf("Number of fortunes: %u\n", index->num_fortunes);
  printf("First 5 fortunes (or fewer if less than 5 total):\n");
  for (uint32_t i = 0; i < index->num_fortunes && i < 5; i++) {
    printf("Fortune %u: offset = %u, length = %u\n", i, index->offsets[i],
           index->lengths[i]);
  }
}

// load a database of loading tips and its strfile index and then select a
// random fortune. Returns number of bytes written to *tip out
size_t select_random_tip_from_fortune_files(const char *fortune_file_path,
                                            const char *fortune_index_path,
                                            const char *tip_out,
                                            const size_t tip_out_buf_size) {
  FortuneIndex index = {0, 0, NULL, NULL};

  FILE *file = fopen(fortune_index_path, "rb");
  if (!file) {
    perror("Error opening file");
    return -1;
  }

  // Read header
  if (fread(&index.version, sizeof(uint32_t), 1, file) != 1 ||
      fread(&index.num_fortunes, sizeof(uint32_t), 1, file) != 1) {
    perror("Error reading header");
    fclose(file);
    return -1;
  }

  // allocate arrays for offsets
  index.offsets = malloc(sizeof(uint32_t) * index.num_fortunes);
  index.lengths = malloc(sizeof(uint32_t) * index.num_fortunes);
  if (!(index.offsets || index.offsets)) {
    perror("Error allocating memory for file index");
    free(index.offsets);
    free(index.lengths);
  }
  // Read offsets
  if (fread(index.offsets, sizeof(uint32_t), index.num_fortunes, file) !=
      index.num_fortunes) {
    perror("Error reading offsets");
    free(index.offsets);
    free(index.lengths);
    fclose(file);
    return -1;
  }

  // Read lengths
  if (fread(index.lengths, sizeof(uint32_t), index.num_fortunes, file) !=
      index.num_fortunes) {
    perror("Error reading lengths");
    free(index.offsets);
    fclose(file);
    return -1;
  }

  print_index_info(&index);
  return 0;
}
