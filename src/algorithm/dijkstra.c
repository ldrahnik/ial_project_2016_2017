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

      if (graph.edge[e]->src_id == current || (!graph.is_graph_oriented && graph.edge[e]->dest_id == current)) {
        int neighbour_id = graph.edge[e]->src_id == current ? graph.edge[e]->dest_id : graph.edge[e]->src_id;
        int distance = results.distances[0][current] + graph.edge[e]->weight;
        if (distance < results.distances[0][neighbour_id]) {
          results.distances[0][neighbour_id] = distance;
        }
      }
    }

    // Finished with this vertex
    unvisited[current] = 0;
    unvisited_count--;

    // Find the nearest unvisited vertex
    min_distance = INT_MAX;
    for (v = 0; v < graph.vertices_count; v++) {
      if (unvisited[v] == 1 && results.distances[0][v] < min_distance) {
        min_distance = results.distances[0][v];
        current = v;
      }
    }
  }
  free(unvisited);
  return results;
}

void printDijkstraPath(TGraph graph, TResults results, int end_vertice, int start_vertice, char* path, const char* algorithm_prefix_name) {
  int e;

  if(end_vertice == start_vertice) {
    fprintf(stdout, "%s: %s\n", algorithm_prefix_name, path);
    return;
  }

  // looking for all neighbour (exists edge) vertices with minimum distance value (can be multiple)
  int minimum_neighbor_distance_width_edge_value = INT_MAX;
  for(e = 0; e < graph.edges_count; e++) {

    int src_id = graph.edge[e]->src_id;
    int dest_id = graph.edge[e]->dest_id;

    if (dest_id == end_vertice && results.distances[0][src_id] != INT_MAX && results.distances[0][src_id] + graph.edge[e]->weight < minimum_neighbor_distance_width_edge_value) {
      minimum_neighbor_distance_width_edge_value = results.distances[0][src_id] + graph.edge[e]->weight;
    }
  }

  // for all shortest paths, is it reverted path print
  if(minimum_neighbor_distance_width_edge_value != INT_MAX) {
    for(e = 0; e < graph.edges_count; e++) {

      int src_id = graph.edge[e]->src_id;
      int dest_id = graph.edge[e]->dest_id;

      if (dest_id == end_vertice && results.distances[0][src_id] != INT_MAX && results.distances[0][src_id] + graph.edge[e]->weight == minimum_neighbor_distance_width_edge_value) {

        int edge_value = results.distances[0][end_vertice] - results.distances[0][src_id];

        char* path_new = addEdgeToPath(path, graph.vertice[src_id]->name, edge_value);

        printDijkstraPath(graph, results, src_id, start_vertice, path_new, algorithm_prefix_name);
        free(path_new);
      }
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
