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
  "The shorted path in graph between two nodes.\n\n"
  "Example of usage:\n\n"
  "./shreya [-h ] [-r ] [-i <graph_path as string>] <node_start> <node_end>\n\n"
  "Options:\n"
  "-r -- rated graph\n"
  "-h -- show help message\n"
  "-i -- string contains graph_path (for example rated graph node0 -> 4 -> node1)\n"
  "<node> -- name of valid node (first is start, second is end)\n"
};

/**
 * Terminal params.
 */
typedef struct params {
  int show_help_message;                // option i
  int ecode;                            // error code
  char** graph_route;                   // format rated: node0 -> number (positive or negative) -> node1
                                        // format unrated: node0 -> node1 -> node2 -> node3
  int contains_negative_edge;           // some algorithm does not support negative edge
  int is_graph_rated;
  char* node_start;
  char* node_end;
} TParams;

/**
 * Error codes.
 */
enum ecodes {
  EOK = 0,               // ok
  EOPT = 1,              // invalid option (option argument is missing,
                         // unknown option, unknown option character)
  ENODE_START = 2,       // node_start is not valid
  ENODE_END = 3,         // node_start is not valid
  ERATED_GRAPH = 4,      // min length, error like edge is not digit number
  EUNRATED_GRAPH = 5,    // min length
  EALLOC = 6,
};

/**
 * Wrapper of isdigit.
 */
int isNumber(char number[]) {
    int i = 0;
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
      if (!isdigit(number[i]))
        return 0;
    return 1;
}

/**
 * Validation of node.
 */
int isValidNode(char** graph_route, TParams params, char* node) {
  int i = 0;
  while(graph_route[i]) {
    if(params.is_graph_rated == 1) {
      if(i % 2 == 0) // odd number of index (take care only about nodes, not edge's)
        if(strcmp(graph_route[i], node) == 0)
          return 1;
    } else {
      if(strcmp(graph_route[i], node) == 0)
        return 1;
    }
    i++;
  }
  return 0;
}

/**
 * Contains any negative edge? 1|0
 */
int containsGraphNegativeEdge(char** graph_route) {
  int i = 0;
  while(graph_route[i]) {
    if(i % 2 && !isNumber(graph_route[i])) {
      fprintf(stderr, "Rating of edge needs to be digit. Given: %s.\n", graph_route[i]);
      return -1;
    } else if(i % 2 && isNumber(graph_route[i]) && atoi(graph_route[i]) < 0) {
      return 1;
    }
    i++;
  }
  return 0;
}

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

/**
 * Get TParams structure from terminal options, option arguments and nodes.
 *
 * @return TParams
 */
TParams getParams(int argc, char *argv[]) {

  TParams params = {
  	.show_help_message = 0,
    .ecode = EOK,
    .is_graph_rated = 0,
    .contains_negative_edge = 0,
  };

  // don't want getopt() writing to stderr
  opterr = 0;

  // for debug prints only
  char* input;

  // getopt
  int c;
  while ((c = getopt(argc, argv, "rhi:")) != -1) {
    switch (c) {
      case 'h':
        params.show_help_message = 1;
        break;
      case 'r':
        params.is_graph_rated = 1;
        break;
      case 'i':
        input = (char*)malloc(sizeof(strlen(optarg)));
        strcpy(input, optarg);
        params.graph_route = parseInputToGraphRoute(optarg);
        if(params.graph_route == NULL) {
          params.ecode = EALLOC;
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
        fprintf (stderr, "At least one node is required.\n");
        params.ecode = EOPT;
    }
  }

  // is there negative edge?
  if(params.is_graph_rated) {
    int res = containsGraphNegativeEdge(params.graph_route);
    if(res == -1) {
      params.ecode = ERATED_GRAPH;
    }
    params.contains_negative_edge = res;
  }

  // check correct minimum of graph length
  int length_of_graph_route = 0;
  while(params.graph_route[length_of_graph_route])
    length_of_graph_route++;

  if(params.is_graph_rated && length_of_graph_route < 3) { // atleast 'A 1 B'
    fprintf(stderr, "Minimum skeleton of rated graph is 'A 12 B', that means 2 nodes and 1 rated edge. Given: %s.\n", input);
    params.ecode = ERATED_GRAPH;
  } else if(length_of_graph_route < 2) { // atleast 'A B'
    fprintf(stderr, "Minimum skeleton of unrated graph is 'A B', that means 2 nodes and one unvision unrated edge. Given: %s.\n", input);
    params.ecode = EUNRATED_GRAPH;
  }

  // default nodes [count of non option args = argc - optind]
  int non_option_count = argc - optind;

  // there can be only 2 nodes: <node_start> <node_end>
  if(non_option_count > 2) {
    fprintf(stderr, "Too match nodes. Can be there only node_start and node_end.\n");
    params.ecode = EOPT;
    return params;
  }
  if(non_option_count < 1) {
    fprintf(stderr, "node_start and node_end is missing.\n");
    params.ecode = EOPT;
    return params;
  }
  if(non_option_count < 2) {
    fprintf(stderr, "node_end is missing.\n");
    params.ecode = EOPT;
    return params;
  }

  // is node_start valid?
  if(isValidNode(params.graph_route, params, argv[optind])) {
    params.node_start = argv[optind];
  } else {
    fprintf(stderr, "node_start is not valid, node: '%s' does not exist.\n", argv[optind]);
    params.ecode = ENODE_START;
  }

  // is node_end valid?
  if(isValidNode(params.graph_route, params, argv[optind + 1])) {
    params.node_end = argv[optind + 1];
  } else {
    fprintf(stderr, "node_end is not valid, node: '%s' does not exist.\n", argv[optind + 1]);
    params.ecode = ENODE_END;
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

  // help message
  if(params.show_help_message) {
    printf("%s", HELP_MSG);
    return ecode;
  }

  // clean
  clean(params);

  return ecode;
}
