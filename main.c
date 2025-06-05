#include <argtable3.h>
#include <stdlib.h>

#include <math.h>
#include "config.h"
#include "logger.h"
#include "macros.h"
#include "memory.h"
#include "version.h"

static struct arg_lit *help, *version;
static struct arg_int *verbose, *mem_limit;
static config_t       *config;
static meminfo_t      *meminfo;

void freeup_and_exit(void *arg_tbl, void *config, const int exitcode) {
  arg_freetable(arg_tbl, sizeof(*arg_tbl));
  free(config);
  free(meminfo);
  exit(exitcode);
}

int main(const int argc, char **argv) {
  config  = malloc(sizeof(config_t));
  meminfo = malloc(sizeof(meminfo_t));

  initialize_config(config);
  initialize_mem_info(meminfo);

  void *arg_tbl[] = {
    help      = arg_litn("h", "help", 0, 1, "Display this help and exit."),
    version   = arg_litn("v", "version", 0, 1, "Display version and exit."),
    verbose   = arg_int0(NULLPTR, "verbose", "<level>", "Set verbosity level. Default: 0."),
    mem_limit = arg_int0("M", "memory-limit", "<kB>", "Set memory limit of child process (in kB)."),

    arg_end(20),
  };
  const int n_errors = arg_parse(argc, argv, arg_tbl);

  if (n_errors) {
    freeup_and_exit(arg_tbl, config, EXIT_FAILURE);
  }

  if (help->count) {
    printf("Usage: %s", APPLICATION_NAME);
    arg_print_syntax(stdout, arg_tbl, "\n\n");
    arg_print_glossary(stdout, arg_tbl, "  %-25s %s\n");
    freeup_and_exit(arg_tbl, config, EXIT_NORMAL);
  }

  if (version->count) {
    printf("%s v%d.%d.%d %d\n", APPLICATION_NAME, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_BUILD);
    printf("%s\n\n", APPLICATION_LICENSE);
    freeup_and_exit(arg_tbl, config, EXIT_NORMAL);
  }

  if (verbose->count)
    config->verbosity = (short)*verbose->ival;

  if (config->verbosity > VERBOSE_INFO) {
    char buf_freemem[1024]  = "\0";
    char buf_totalmem[1024] = "\0";
    get_readable_mem_blocks(buf_freemem, calculate_free_mem_blocks(meminfo));
    get_readable_mem_blocks(buf_totalmem, meminfo->total_mem);
    verbose_msg(VERBOSE_INFO, config->verbosity, "Free page sizes: %s / %s\n", buf_freemem, buf_totalmem);
  }

  freeup_and_exit(arg_tbl, config, EXIT_NORMAL);
}
