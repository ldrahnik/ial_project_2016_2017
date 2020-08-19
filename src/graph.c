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
    cleanGraphEdge(graph, i);
  }
  for (i = 0; i < graph.vertices_count; i++) {
    cleanGraphVertex(graph, i);
  }
  free(graph.edge);
  free(graph.vertice);
}

void cleanGraphEdge(TGraph graph, int id) {
  if(graph.edge[id] != NULL) {
    free(graph.edge[id]->src);
    free(graph.edge[id]->dest);
    free(graph.edge[id]);
  }
}

void cleanGraphVertex(TGraph graph, int id) {
  if(graph.vertice[id] != NULL) {
    free(graph.vertice[id]->name);
    free(graph.vertice[id]);
  }
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
TParams parseInputToGraphRoute(TParams params) {

  // replace new line etc. with space
  for (char* p = params.input; (p = strchr(p, '\r')); ++p) {
    *p = ' ';
  }
  for (char* p = params.input; (p = strchr(p, '\n')); ++p) {
    *p = ' ';
  }

  char *  p = strtok(params.input, " ");
  int n_spaces = 0, i = 0;

  // split string and append tokens to 'res'
  while(p) {
    params.graph_route = realloc(params.graph_route, sizeof (char*)* ++n_spaces);

    // memory allocation failed
    if(params.graph_route == NULL) {
      fprintf(stderr, "Memory allocation failed.");
      params.graph_route = params.graph_route;
      return params;
    }

    params.graph_route[n_spaces-1] = p;

    p = strtok (NULL, " ");
  }

  // realloc one extra element for the last NULL
  params.graph_route = realloc(params.graph_route, sizeof(char*) * (n_spaces + 1));
  params.graph_route[n_spaces] = NULL;

  // DEBUG:
  if(params.debug) {
    for(i = 0; i < (n_spaces+1); ++i)
      fprintf(stderr, "DEBUG: parseInputToGraphRoute[%d] = %s\n", i, params.graph_route[i]);
    fprintf(stderr, "\n");
  }

  return params;
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

        graph = addVertex(graph, graph_route[i]);
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

        graph = addVertex(graph, graph_route[i]);
      }

      graph = addEdge(graph, graph_route[i - 2], graph_route[i], atoi(graph_route[i - 1]));

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

          graph = addVertex(graph, graph_route[i]);
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

  TGraph graph;
  graph.ecode = EOK;

  params = parseInputToGraphRoute(params);
  if(params.ecode != EOK) {
    graph.ecode = params.ecode;
    return graph;
  }
  graph = stepByStepGraphRoute(params.graph_route, params.debug);
  if(graph.ecode != EOK) {
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

int isExistsEdge(TGraph graph, int start_vertice_id, int end_vertice_id) {
  for(int i = 0; i < graph.edges_count; i++)
    if(graph.edge[i]->src_id == start_vertice_id && graph.edge[i]->dest_id == end_vertice_id)
      return 1;
  return 0;
}

int getEdgeValue(TGraph graph, int start_vertice_id, int end_vertice_id) {
  for(int i = 0; i < graph.edges_count; i++)
    if(graph.edge[i]->src_id == start_vertice_id && graph.edge[i]->dest_id == end_vertice_id)
      return graph.edge[i]->weight;
  return INT_MAX;
}

TGraph addVertex(TGraph graph, const char* new_vertex_name) {

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
  graph.vertice[graph.vertices_count]->name = malloc(strlen(new_vertex_name) + 1);
  if(graph.vertice[graph.vertices_count]->name == NULL) {
    graph.ecode = EALLOC;
    return graph;
  }
  strcpy(graph.vertice[graph.vertices_count]->name, new_vertex_name);
  graph.vertice[graph.vertices_count]->name[strlen(new_vertex_name)] = '\0';

  graph.vertices_count++;

  return graph;
}

TGraph addEdge(TGraph graph, char* start_vertice, char* end_vertice, int weight) {

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
   graph.edge[graph.edges_count]->src = malloc(strlen(start_vertice) + 1);
   if(graph.edge[graph.edges_count]->src == NULL) {
     graph.ecode = EALLOC;
     return graph;
   }
   graph.edge[graph.edges_count]->dest = malloc(strlen(end_vertice) + 1);
   if(graph.edge[graph.edges_count]->dest == NULL) {
     graph.ecode = EALLOC;
     return graph;
   }

   strcpy(graph.edge[graph.edges_count]->src, start_vertice);
   graph.edge[graph.edges_count]->src_id = getPositionOfVertice(graph, start_vertice);
   graph.edge[graph.edges_count]->weight = weight;
   graph.edge[graph.edges_count]->src[strlen(start_vertice)] = '\0';
   strcpy(graph.edge[graph.edges_count]->dest, end_vertice);
   graph.edge[graph.edges_count]->dest[strlen(end_vertice)] = '\0';
   graph.edge[graph.edges_count]->dest_id = getPositionOfVertice(graph, end_vertice);

   graph.edges_count++;

   return graph;
}

/** remove last added edge's associated with last added vertice too */
TGraph removeTopVertice(TGraph graph) {
  int i;

  int last_vertice_id = graph.vertices_count - 1;
  int last_edge_id = graph.edges_count - 1;

  // edges
  for(i = last_edge_id; i >= 0; i--) {
    if(graph.edge[i]->src_id == last_vertice_id || graph.edge[i]->dest_id == last_vertice_id) {
      cleanGraphEdge(graph, i);
      graph.edges_count--;
    } else {
      break;
    }
  }

  // vertex
  cleanGraphVertex(graph, last_vertice_id);
  graph.vertices_count--;

  return graph;
}

TGraph changeEdgeWeight(TGraph graph, int start_vertice_id, int end_vertice_id, int new_weight) {
  int i;

  for(i = 0; i < graph.edges_count; i++) {
    if(graph.edge[i]->src_id == start_vertice_id && graph.edge[i]->dest_id == end_vertice_id) {
      graph.edge[i]->weight = new_weight;
    }
  }
  return graph;
}
