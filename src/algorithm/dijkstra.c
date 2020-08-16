/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 * File:              Soubor zabývající se implementací algoritmu Dijkstra.
 */

#include "dijkstra.h"

TResults dijkstra(TGraph graph, int vertice_id) {
  int e, v, min_distance, i, current = vertice_id;
  int unvisited_count = graph.vertices_count;

  TResults results = {
    .distances = malloc(graph.vertices_count * sizeof(int *)),
    .predecessors = NULL,
    .ecode = EOK,
  };

  int *unvisited = malloc(unvisited_count* sizeof(int));

  if(results.distances == NULL) {
    results.ecode = EALLOC;
    return results;
  }

  if(unvisited == NULL) {
    results.ecode = EALLOC;
    return results;
  }

  // All distances start infinite and all vertices start unvisited
  for(i = 0; i < graph.vertices_count; i++) {
    results.distances[i] = malloc(graph.vertices_count * sizeof(int));
    results.distances[0][i] = INT_MAX;
    unvisited[i] = 1;
  }

  // Distance to starting vertex is 0
  results.distances[0][vertice_id] = 0;

  while (unvisited_count > 0) {

    // Update the distances to all neighbours
    for (e = 0; e < graph.edges_count; e++) {
      if (graph.edge[e]->src_id == current || graph.edge[e]->dest_id == current) {
        int neighbour = graph.edge[e]->src_id == current ? graph.edge[e]->dest_id : graph.edge[e]->src_id;
        int distance = results.distances[0][current] + graph.edge[e]->weight;
        if (distance <= results.distances[0][neighbour]) {
          results.distances[0][neighbour] = distance;
        }
      }
    }

    // Finished with this vertex
    unvisited[current] = 0;
    unvisited_count--;

    // Find the nearest unvisited vertex
    min_distance = 0;
    for (v = 0; v < graph.vertices_count; v++) {
      if (unvisited[v] == 1 && (min_distance == 0 || results.distances[0][v] < min_distance)) {
        min_distance = results.distances[0][v];
        current = v;
      }
    }
  }
  free(unvisited);
  return results;
}

void printDijkstraPredecessors(TGraph graph, TResults results) {
  int v, a;
  for(v = 0; v < graph.vertices_count; v++) {
    for(a = 0; a < graph.vertices_count; a++) {
      int isEdgeValid = results.predecessors[v][a];
      if(isEdgeValid) {
        fprintf(stderr, "DEBUG: dest_id: %i [ dest: %s ] -> src_id %i [ src: %s ]\n", v, graph.vertice[v]->name, a, graph.vertice[a]->name);
      }
    }
  }
}

void printDijkstraPath(TGraph graph, TResults results, int end_vertice, int start_vertice, char* path) {
  int e, v;

  if(end_vertice == start_vertice) {
    fprintf(stdout, "Dijkstra: %s\n", path);
    return;
  }

  // for all neighbour vertices looking for shortest edge's (can be multiple with the same value)
  int minimum = INT_MAX;
  for(e = 0; e < graph.edges_count; e++) {

    int src_id = graph.edge[e]->src_id;
    int dest_id = graph.edge[e]->dest_id;

    if(src_id == end_vertice && results.distances[0][dest_id] < minimum) {
      minimum = results.distances[0][dest_id];
    } else if(dest_id == end_vertice && results.distances[0][src_id] < minimum) {
      minimum = results.distances[0][src_id];
    }
  }

  // for all shortest paths, is it reverted path print
  for(v = 0; v < graph.vertices_count; v++) {

    if(v != end_vertice && results.distances[0][v] == minimum) {
      char* path_new = (char *)malloc(100 * sizeof(char));
      path_new[0] = '\0';
      strcat(path_new, graph.vertice[v]->name);
      strcat(path_new, " -(");

      int edge_value = results.distances[0][end_vertice] - results.distances[0][v];
      char edgeValueLikeString[10];
      sprintf(edgeValueLikeString, "%d", edge_value);
      strcat(path_new, edgeValueLikeString);

      strcat(path_new, ")> ");
      strcat(path_new, path);

      printDijkstraPath(graph, results, v, start_vertice, path_new);
      free(path_new);
    }
  }
}

void printDijkstraDistances(TGraph graph, TResults results) {
  fprintf(stderr, "\n");
  int i;
  for (i = 0; i < graph.vertices_count; i++) {
    fprintf(stderr, "DEBUG: %s: %u: %u\n", graph.vertice[i]->name, i, results.distances[0][i]);
  }
}
