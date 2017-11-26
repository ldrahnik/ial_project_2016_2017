/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 */

#include "params.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

/**
 * Get TParams structure from terminal options, option arguments and vertices.
 *
 * @return TParams
 */
TParams getParams(int argc, char *argv[]) {

  TParams params = {
  	.show_help_message = 0,
    .ecode = EOK,
    .is_graph_rated = 0,
    .contains_negative_edge = 0,
    .is_graph_oriented = 0,
  };

  // don't want getopt() writing to stderr
  opterr = 0;

  // file
  FILE *file;
  long length;

  // getopt
  int c;
  while ((c = getopt(argc, argv, "orhi:")) != -1) {
    switch (c) {
      case 'h':
        params.show_help_message = 1;
        break;
      case 'r':
        params.is_graph_rated = 1;
        break;
      case 'o':
        params.is_graph_oriented = 1;
        break;
      case 'i':
        file = fopen(optarg,"rb");
        if(file != NULL) {
          fseek(file, 0, SEEK_END);  // TODO: error check
          length = ftell(file); // TODO: error check
          fseek(file, 0, SEEK_SET); // TODO: error check
          params.input = malloc(length);
          if(params.input  == NULL) {
            params.ecode = EALLOC;
            return params;
          }
          if(params.input ) {
            fread(params.input, 1, length, file);  // TODO: error check
          }
          fclose(file);
        } else {
          params.input  = malloc(strlen(optarg));
          if(params.input  == NULL) {
            params.ecode = EALLOC;
            return params;
          }
          strcpy(params.input, optarg);
        }
        break;
      case '?':
        if(optopt == 'i') {
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        } else if(isprint (optopt)) {
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        } else {
          fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
        }
        params.ecode = EOPT;
      default:
        fprintf (stderr, "At least one vertice is required.\n");
        params.ecode = EOPT;
    }
  }

  // default vertices [count of non option args = argc - optind]
  int non_option_count = argc - optind;

  // there can be only 2 vertices: <vertice_start> <vertice_end>
  if(non_option_count > 2) {
    fprintf(stderr, "Too match vertices. Can be there only vertice_start and vertice_end.\n");
    params.ecode = EOPT;
    return params;
  }
  if(non_option_count < 1) {
    fprintf(stderr, "vertice_start and vertice_end is missing.\n");
    params.ecode = EOPT;
    return params;
  }
  if(non_option_count < 2) {
    fprintf(stderr, "vertice_end is missing.\n");
    params.ecode = EOPT;
    return params;
  }

  params.vertice_start = argv[optind];
  params.vertice_end = argv[optind + 1];

  return params;
}

/**
 * Clean the mess.
 */
void cleanParams(TParams params) {
  free(params.input);
  free(params.graph_route);
}
