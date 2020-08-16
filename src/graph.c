/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 * File:              Soubor zabývající se implementací konverze vstupu z terminálu nebo ze souboru do grafových struktur obsahujících vše důležité pro funkci programu.
 */

#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

const char *plus = "+";
const char *minus = "-";

void cleanGraph(TGraph graph) {
  int i;
  for (i = 0; i < graph.edges_count; i++) {
    free(graph.edge[i]);
  }
  for (i = 0; i < graph.vertices_count; i++) {
    free(graph.vertice[i]->name);
    free(graph.vertice[i]);
  }
  free(graph.edge);
  free(graph.vertice);
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

int isVerticeValid(TGraph graph, char* vertice) {
  for(int i = 0; i < graph.vertices_count; i++)
    if(strcmp(graph.vertice[i]->name, vertice) == 0)
      return 1;
  return 0;
}

int getPositionOfVertice(TGraph graph, char* vertice) {
  for(int i = 0; i < graph.vertices_count; i++)
    if(strcmp(graph.vertice[i]->name, vertice) == 0)
      return i;
  return 0;
}

/**
 * Parse for example -i 'A 1 B 2 C' to  [0] = A, [1] = 1 ... [5] = (null)
 */
char** parseInputToGraphRoute(char* input, int debug) {
  char ** res = NULL;

  // replace new line etc. with space
  for (char* p = input; (p = strchr(p, '\r')); ++p) {
    *p = ' ';
  }
  for (char* p = input; (p = strchr(p, '\n')); ++p) {
    *p = ' ';
  }

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
  if(debug) {
    for(i = 0; i < (n_spaces+1); ++i)
      fprintf(stderr, "DEBUG: parseInputToGraphRoute[%d] = %s\n", i, res[i]);
    fprintf(stderr, "\n");
  }

  return res;
}

TGraph stepByStepGraphRoute(char** graph_route, int debug) {
  int i = 0;

  TGraph graph = {
  	.is_graph_rated = 0,
    .ecode = EOK,
    .contains_negative_edge = 0,
    .vertices_count = 0,
    .edges_count = 0,
    .edge = NULL,
    .vertice = NULL,
    .debug = debug,
  };

  // <start_vertice> <edge> <end_vertice> ...
  // <start_vertice> <edge> <end_vertice> <edge> <end_vertice> ...
  int start_vertice = 0;
  int edge = 0;
  int end_vertice = 0;
  int previous_edge_weight = INT_MAX;

  while(graph_route[i]) {

    if(start_vertice == 0) { // start_vertice
      if(debug) {
        fprintf(stderr, "DEBUG: start_vertice at index: %i\n", i);
      }
      start_vertice = 1;

      if(!isVerticeValid(graph, graph_route[i])) {
        if(debug)
          fprintf(stderr, "DEBUG: add new vertice at index: %i, %s\n", i, graph_route[i]);
        graph.vertice = (TVertice**)realloc(graph.vertice, (graph.vertices_count + 1) * sizeof(TVertice));
        if(graph.vertice == NULL) {
            graph.ecode = EALLOC;
            return graph;
        }
        graph.vertice[graph.vertices_count] = malloc(sizeof(TVertice));
        if(graph.vertice[graph.vertices_count] == NULL) {
            graph.ecode = EALLOC;
            return graph;
        }
        graph.vertice[graph.vertices_count]->name = malloc(strlen(graph_route[i]) + 1);
        if(graph.vertice[graph.vertices_count]->name == NULL) {
            graph.ecode = EALLOC;
            return graph;
        }
        strcpy(graph.vertice[graph.vertices_count]->name, graph_route[i]);
        graph.vertice[graph.vertices_count]->name[strlen(graph_route[i])] = '\0';
        graph.vertices_count++;
      }
    } else if(start_vertice == 1 && edge == 0) { // edge
      edge = 1;
      if(isNumberEdge(graph_route[i])) {
        if(debug)
          fprintf(stderr, "DEBUG: edge as number at index: %i\n", i);

        // negative check
        if(atoi(graph_route[i]) < 0) {
          graph.contains_negative_edge = 1;
        }

        // check if is rated_graph
        if(previous_edge_weight == INT_MAX) {
          previous_edge_weight = atoi(graph_route[i]);
        } else if(previous_edge_weight != atoi(graph_route[i])) {
          graph.is_graph_rated = 1;
        }
      } else if (isNonRatedEdge(graph_route[i])) {
        if(debug)
          fprintf(stderr, "DEBUG: edge +/- at index: %i\n", i);
      }
    } else if (start_vertice == 1 && edge == 1 && end_vertice == 0) {  // end_vertice
      if(debug)
        fprintf(stderr, "DEBUG: end_vertice at index: %i\n", i);
      end_vertice = 1;

      if(!isVerticeValid(graph, graph_route[i])) {
        if(debug)
          fprintf(stderr, "DEBUG: add new vertice at index: %i, %s\n", i, graph_route[i]);
        graph.vertice = (TVertice**)realloc(graph.vertice, (graph.vertices_count + 1) * sizeof(TVertice));
        if(graph.vertice == NULL) {
            graph.ecode = EALLOC;
            return graph;
        }
        graph.vertice[graph.vertices_count] = malloc(sizeof(TVertice));
        if(graph.vertice[graph.vertices_count] == NULL) {
            graph.ecode = EALLOC;
            return graph;
        }
        graph.vertice[graph.vertices_count]->name = malloc(strlen(graph_route[i]) + 1);
        if(graph.vertice[graph.vertices_count]->name == NULL) {
            graph.ecode = EALLOC;
            return graph;
        }
        strcpy(graph.vertice[graph.vertices_count]->name, graph_route[i]);
        graph.vertice[graph.vertices_count]->name[strlen(graph_route[i])] = '\0';
        graph.vertices_count++;
      }

      graph.edge = (TEdge**)realloc(graph.edge, (graph.edges_count + 1) * sizeof(TEdge));
      if(graph.edge == NULL) {
        graph.ecode = EALLOC;
        return graph;
      }
      graph.edge[graph.edges_count] = malloc(sizeof(TEdge));
      if(graph.edge[graph.edges_count] == NULL) {
        graph.ecode = EALLOC;
        return graph;
      }

      graph.edge[graph.edges_count]->src = graph_route[i - 2];
      graph.edge[graph.edges_count]->src_id = getPositionOfVertice(graph, graph_route[i - 2]);
      graph.edge[graph.edges_count]->weight = atoi(graph_route[i - 1]);
      graph.edge[graph.edges_count]->dest = graph_route[i];
      graph.edge[graph.edges_count]->dest_id = getPositionOfVertice(graph, graph_route[i]);

      graph.edges_count++;
    } else if(start_vertice == 1 && edge == 1 && end_vertice == 1) {
      if(isNumberEdge(graph_route[i])) {
        if(debug)
          fprintf(stderr, "DEBUG: edge-e-e as number at index: %i\n", i);

        edge = 1;
        start_vertice = 1;
        end_vertice = 0;

        // check if is rated_graph
        if(previous_edge_weight == INT_MAX) {
          previous_edge_weight = atoi(graph_route[i]);
        } else if(previous_edge_weight != atoi(graph_route[i])) {
          graph.is_graph_rated = 1;
        }

        // negative check
        if(atoi(graph_route[i]) < 0) {
          graph.contains_negative_edge = 1;
        }
      } else {
        if(debug)
          fprintf(stderr, "DEBUG: start_vertice at index: %i\n", i);
        start_vertice = 1;
        end_vertice = 0;
        edge = 0;

        if(!isVerticeValid(graph, graph_route[i])) {
          if(debug)
            fprintf(stderr, "DEBUG: add new vertice at index: %i, %s\n", i, graph_route[i]);
          graph.vertice = (TVertice**)realloc(graph.vertice, (graph.vertices_count + 1) * sizeof(TVertice));
          graph.vertice[graph.vertices_count]->name = graph_route[i];
          graph.vertices_count++;
        }
      }
    } else {
      fprintf(stderr, "Error at index: %i, vertice_start: %i, vertice_end: %i, edge: %i\n", i, start_vertice, end_vertice, edge);
      graph.ecode = EGRAPH;
    }
    i++;
  }
  int y;

  if(debug) {
    for(y = 0; y < graph.vertices_count; y++) {
      fprintf(stderr, "\nDEBUG: %i %s\n", y, graph.vertice[y]->name);
    }
    for(y = 0; y < graph.edges_count; y++) {
      fprintf(stderr, "\nDEBUG: %i src: %s\n", y, graph.edge[y]->src);
      fprintf(stderr, "\nDEBUG: %i dest: %s\n", y, graph.edge[y]->dest);
      fprintf(stderr, "\nDEBUG: %i src_id: %i\n", y, graph.edge[y]->src_id);
      fprintf(stderr, "\nDEBUG: %i dest_id: %i\n", y, graph.edge[y]->dest_id);
      fprintf(stderr, "\nDEBUG: %i weight: %i\n", y, graph.edge[y]->weight);
    }
  }
  if(start_vertice == 1 && edge == 0) {
    fprintf(stderr, "There is missing edge at index %i.\n", i);
    graph.ecode = EGRAPH;
  }
  if(start_vertice == 1 && edge == 1 && end_vertice == 0) {
    fprintf(stderr, "There is missing end_vertice at index %i.\n", i);
    graph.ecode = EGRAPH;
  }
  return graph;
}

/**
 * Get TGraph structure from graph_route and params.
 *
 * @return TParams
 */
TGraph getGraph(TParams params) {
  params.graph_route = parseInputToGraphRoute(params.input, params.debug);
  if(params.graph_route == NULL) {
    TGraph graph;
    graph.ecode = EALLOC;
    return graph;
  }
  TGraph graph = stepByStepGraphRoute(params.graph_route, params.debug);

  if(graph.ecode != EOK) {
    graph.ecode = EGRAPH;
    return graph;
  }

  // is graph oriented
  graph.is_graph_oriented = params.is_graph_oriented;
  if(params.debug)
    fprintf(stderr, "\nDEBUG: graph is oriented: %i\n\n", graph.is_graph_oriented);

  // is graph rated
  graph.is_graph_rated = params.is_graph_rated != -1 ? params.is_graph_rated : graph.is_graph_rated;
  if(params.debug)
    fprintf(stderr, "\nDEBUG: graph is rated: %i\n\n", graph.is_graph_rated);

  // if is graph not rated (or we want to be non rated, set up all edges as 1)
  if(!graph.is_graph_rated) {
    int i;
    for(i = 0; i < graph.edges_count; i++) {
      graph.edge[i]->weight = 1;
    }
    graph.contains_negative_edge = 0;
  }

  // is there negative edge?
  if(params.debug)
    fprintf(stderr, "\nDEBUG: graph contains negative edge: %i\n\n", graph.contains_negative_edge);

  // check correct minimum of graph length
  int length_of_graph_route = 0;
  while(params.graph_route[length_of_graph_route])
    length_of_graph_route++;

  if(params.is_graph_rated && length_of_graph_route < 3) { // atleast 'A +/-1 B'
    fprintf(stderr, "Minimum skeleton of rated graph is 'A 12 B', that means 2 vertices and 1 rated edge. Given: %s.\n", params.input);
    graph.ecode = ERATED_GRAPH;
    return graph;
  } else if(length_of_graph_route < 3) { // atleast 'A +/- B'
    fprintf(stderr, "Minimum skeleton of unrated graph is 'A B', that means 2 vertices and one unvision unrated edge. Given: %s.\n", params.input);
    graph.ecode = EUNRATED_GRAPH;
    return graph;
  }

  // is vertice_start valid?
  if(!isVerticeValid(graph, params.vertice_start)) {
    fprintf(stderr, "vertice_start is not valid, vertice: '%s' does not exist.\n", params.vertice_start);
    graph.ecode = EVERTICE_START;
    return graph;
  }

  // is vertice_end valid?
  if(!isVerticeValid(graph, params.vertice_end)) {
    fprintf(stderr, "vertice_end is not valid, vertice: '%s' does not exist.\n", params.vertice_end);
    graph.ecode = EVERTICE_END;
    return graph;
  }

  return graph;
}

int getEdgeValue(TGraph graph, int start_vertice_id, int end_vertice_id) {
  for(int i = 0; i < graph.edges_count; i++)
    if(graph.edge[i]->src_id == start_vertice_id && graph.edge[i]->dest_id == end_vertice_id)
      return graph.edge[i]->weight;
  return INT_MAX;
}
