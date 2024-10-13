#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint32_t version;
  uint32_t num_fortunes;
  uint32_t *offsets;
  uint32_t *lengths;
} FortuneIndex;

void show_demo_tip_stderr();

void print_index_info(FortuneIndex *index);

size_t select_random_tip_from_fortune_files(const char *fortune_file_path,
                                            const char *fortune_index_path,
                                            const char *tip_out,
                                            const size_t tip_out_buf_size);