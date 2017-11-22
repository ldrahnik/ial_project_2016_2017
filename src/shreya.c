/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

/**
 * Help message.
 */
const char *HELP_MSG = {
  "The shorted path in graph between two vertices.\n\n"
  "Example of usage:\n\n"
  "./shreya [-h ] [-r ] [-i <graph_path as string>] <vertice_start> <vertice_end>\n\n"
  "Options:\n"
  "-r -- rated graph\n"
  "-o -- oriented graph\n"
  "-h -- show help message\n"
  "-i -- string contains graph_path (for example rated graph vertice0 -> 4 -> vertice1)\n"
  "<vertice> -- name of valid vertice (first is start, second is end)\n"
};

const char *plus = "+";
const char *minus = "-";

/**
 * Terminal params.
 */
typedef struct params {
  int show_help_message;                // option i
  int ecode;                            // error code
  char** graph_route;                   // format rated: vertice0 -> number (positive or negative) -> vertice1
                                        // format unrated: vertice0 -> vertice1 -> vertice2 -> vertice3
  int contains_negative_edge;           // some algorithm does not support negative edge
  int is_graph_rated;                   // program take care about numbers
  int is_graph_oriented;                // program take care about +/-
  char* vertice_start;
  char* vertice_end;
} TParams;

/**
 * Error codes.
 */
enum ecodes {
  EOK = 0,               // ok
  EOPT = 1,              // invalid option (option argument is missing,
                         // unknown option, unknown option character)
  EVERTICE_START = 2,    // vertice_start is not valid
  EVERTICE_END = 3,      // vertice_end is not valid
  ERATED_GRAPH = 4,      // spec. rated graph: min length, error like edge is not digit number
  EUNRATED_GRAPH = 5,    // spec. unrated graph: min length
  EGRAPH = 6,            // graph common
  EALLOC = 7,
};

/**
 * Parse for example -i 'A 1 B 2 C' to  [0] = A, [1] = 1 ... [5] = (null)
 */
char** parseInputToGraphRoute(char* input) {
  char ** res = NULL;
  char *  p = strtok(input, " ");
  int n_spaces = 0, i = 0;

  // split string and append tokens to 'res'
  while(p) {
    res = realloc(res, sizeof (char*)* ++n_spaces);

    // memory allocation failed
    if(res == NULL) {
      fprintf(stderr, "Memory allocation failed.");
      return res;
    }

    res[n_spaces-1] = p;

    p = strtok (NULL, " ");
  }

  // realloc one extra element for the last NULL
  res = realloc(res, sizeof(char*) * (n_spaces+1));
  res[n_spaces] = 0;

  // DEBUG:
  for(i = 0; i < (n_spaces+1); ++i)
    printf("DEBUG: res[%d] = %s\n", i, res[i]);
  printf("\n");

  return res;
}


int isNumber(char number[]) {
  int i = 0;
  if (number[0] == '-')
    i = 1;
  for (; number[i] != 0; i++)
    if (!isdigit(number[i]))
      return 0;
  return 1;
}

int isNonRatedEdge(char* c) {
  return strcmp(c, plus) == 0 || strcmp(c, minus) == 0;
}

int isEdge(char* c) {
  return isNumber(c) || isNonRatedEdge(c);
}

int isNumberEdge(char* c) {
  return isNumber(c) && !isNonRatedEdge(c);
}

int stepByStepGraphRoute(char** graph_route, int is_graph_rated, int contains_negative_edge, int validate_vertice, char* vertice) {
  int i = 0;

  // <start_vertice> <edge> <end_vertice> ...
  // <start_vertice> <edge> <end_vertice> <edge> <end_vertice> ...
  int start_vertice = 0;
  int edge = 0;
  int end_vertice = 0;

  while(graph_route[i]) {
    if(start_vertice == 0) { // start_vertice
      fprintf(stderr, "DEBUG: start_vertice at index: %i\n", i);
      start_vertice = 1;

      // validate vertice
      if(validate_vertice == 1 && strcmp(graph_route[i], vertice) == 0) {
        return 1;
      }
    } else if(start_vertice == 1 && edge == 0) { // edge
      if(isNumberEdge(graph_route[i])) {
        fprintf(stderr, "DEBUG: edge as number at index: %i\n", i);

        edge = 1;

        // check if is rated_graph
        if(is_graph_rated == 1) {
          return 1;
        }

        // negative check
        if(contains_negative_edge == 1) {
          if(atoi(graph_route[i]) < 0) {
            return 1;
          }
        }
      } else if (strcmp(graph_route[i], plus) != 0 || strcmp(graph_route[i], minus) != 0) {
        fprintf(stderr, "DEBUG: edge +/- at index: %i\n", i);
        edge = 1;
      }
    } else if (start_vertice == 1 && edge == 1 && end_vertice == 0) {  // end_vertice
      fprintf(stderr, "DEBUG: end_vertice at index: %i\n", i);
      end_vertice = 1;

      // validate vertice
      if(validate_vertice == 1 && strcmp(graph_route[i], vertice) == 0) {
        return 1;
      }
    } else if(start_vertice == 1 && edge == 1 && end_vertice == 1) {
      if(isNumber(graph_route[i]) && strcmp(graph_route[i], plus) != 0 && strcmp(graph_route[i], minus) != 0) {
        fprintf(stderr, "DEBUG: edge-e-e as number at index: %i\n", i);

        edge = 1;
        start_vertice = 1;
        end_vertice = 0;

        // check if is rated_graph
        if(is_graph_rated == 1) {
          return 1;
        }

        // negative check
        if(contains_negative_edge == 1) {
          if(atoi(graph_route[i]) < 0) {
            return 1;
          }
        }
      } else {
        fprintf(stderr, "DEBUG: start_vertice at index: %i\n", i);
        start_vertice = 1;
        end_vertice = 0;
        edge = 0;

        // validate vertice
        if(validate_vertice == 1 && strcmp(graph_route[i], vertice) == 0) {
          return 1;
        }
      }
    } else {
      fprintf(stderr, "Error at index: %i, vertice_start: %i, vertice_end: %i, edge: %i\n", i, start_vertice, end_vertice, edge);
      return -1;
    }
    i++;
  }
  if(start_vertice == 1 && edge == 0) {
    fprintf(stderr, "There is missing edge at index %i.\n", i);
    return -1;
  }
  if(start_vertice == 1 && edge == 1 && end_vertice == 0) {
    fprintf(stderr, "There is missing end_vertice at index %i.\n", i);
    return -1;
  }
  return 0;
}

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

  // for debug prints only
  char* input;

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
        input = (char*)malloc(sizeof(strlen(optarg)));
        if(input == NULL) {
          params.ecode = EALLOC;
          return params;
        }
        strcpy(input, optarg);
        params.graph_route = parseInputToGraphRoute(optarg);
        if(params.graph_route == NULL) {
          params.ecode = EALLOC;

          // clean
          free(input);

          return params;
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

  if(stepByStepGraphRoute(params.graph_route, 0, 0, 0, 0) == -1) {
    params.ecode = EGRAPH;
    return params;
  }

  // is graph oriented
  printf("\nDEBUG: graph is oriented: %i\n\n", params.is_graph_oriented);

  // is graph rated
  params.is_graph_rated = params.is_graph_rated ? stepByStepGraphRoute(params.graph_route, 1, 0, 0, 0) : 0;
  printf("\nDEBUG: graph is rated: %i\n\n", params.is_graph_rated);

  // is there negative edge?
  params.contains_negative_edge = params.is_graph_oriented ? stepByStepGraphRoute(params.graph_route, 0, 1, 0, 0) : 0;
  printf("\nDEBUG: graph contains negative edge: %i\n\n", params.contains_negative_edge);

  // check correct minimum of graph length
  int length_of_graph_route = 0;
  while(params.graph_route[length_of_graph_route])
    length_of_graph_route++;

  if(params.is_graph_rated && length_of_graph_route < 3) { // atleast 'A +/-1 B'
    fprintf(stderr, "Minimum skeleton of rated graph is 'A 12 B', that means 2 vertices and 1 rated edge. Given: %s.\n", input);
    params.ecode = ERATED_GRAPH;
  } else if(length_of_graph_route < 3) { // atleast 'A +/- B'
    fprintf(stderr, "Minimum skeleton of unrated graph is 'A B', that means 2 vertices and one unvision unrated edge. Given: %s.\n", input);
    params.ecode = EUNRATED_GRAPH;
  }

  // default vertices [count of non option args = argc - optind]
  int non_option_count = argc - optind;

  // there can be only 2 vertices: <vertice_start> <vertice_end>
  if(non_option_count > 2) {
    fprintf(stderr, "Too match vertices. Can be there only vertice_start and vertice_end.\n");
    params.ecode = EOPT;

    // clean
    free(input);

    return params;
  }
  if(non_option_count < 1) {
    fprintf(stderr, "vertice_start and vertice_end is missing.\n");
    params.ecode = EOPT;

    // clean
    free(input);

    return params;
  }
  if(non_option_count < 2) {
    fprintf(stderr, "vertice_end is missing.\n");
    params.ecode = EOPT;
    return params;
  }

  // is vertice_start valid?
  if(stepByStepGraphRoute(params.graph_route, 0, 0, 1, argv[optind])) {
    params.vertice_start = argv[optind];
  } else {
    fprintf(stderr, "vertice_start is not valid, vertice: '%s' does not exist.\n", argv[optind]);
    params.ecode = EVERTICE_START;
  }

  // is vertice_end valid?
  if(stepByStepGraphRoute(params.graph_route, 0, 0, 1, argv[optind + 1])) {
    params.vertice_end = argv[optind + 1];
  } else {
    fprintf(stderr, "vertice_end is not valid, vertice: '%s' does not exist.\n", argv[optind + 1]);
    params.ecode = EVERTICE_END;
  }

  // clean
  free(input);

  return params;
}

/**
 * Clean the mess.
 */
void clean(TParams params) {
  free(params.graph_route);
}

/**
 * Entry point of application.
 *
 * @param int argc
 * @param char *argv[]
 *
 * @return int
 */
int main(int argc, char *argv[]) {
  int ecode = EOK;

  // get params
  TParams params = getParams(argc, argv);
  if(params.ecode != EOK) {
    return params.ecode;
  }

  fprintf(stderr, "\nDEBUG: getParams() successfuly ended.\n");

  // help message
  if(params.show_help_message) {
    printf("%s", HELP_MSG);
    return ecode;
  }

  // clean
  clean(params);

  return ecode;
}
