/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 */

#include "dijkstra.h"

TResults dijkstra(TGraph graph, int vertice_id) {
  int i, current = vertice_id;
  int unvisited_count = graph.vertices_count;

  TResults results = {
    .distances = malloc(graph.vertices_count * sizeof(int *)),
    .predecessors = malloc(graph.vertices_count * sizeof(int *)),
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
  results.distances[0] = malloc(graph.vertices_count * sizeof(int));
  results.predecessors[0] = malloc(graph.vertices_count * sizeof(int));
  for (i = 0; i < graph.vertices_count; i++) {
    results.distances[0][i] = INT_MAX;
    results.predecessors[0][i] = INT_MIN;
    unvisited[i] = 1;
  }

  // Distance to starting vertex is 0
  results.distances[0][vertice_id] = 0;

  while (unvisited_count > 0) {

    // Update the distances to all neighbours
    int e, v;
    int min_distance;
    for (e = 0; e < graph.edges_count; e++) {
      if (graph.edge[e].src_id == current || graph.edge[e].dest_id == current) {
        int neighbour = graph.edge[e].src_id == current ? graph.edge[e].dest_id : graph.edge[e].src_id;
        int distance = results.distances[0][current] + graph.edge[e].weight;
        if (distance < results.distances[0][neighbour]) {
          results.distances[0][neighbour] = distance;
          results.predecessors[0][neighbour] = current;
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

void printDijkstraPath(TGraph graph, TResults results, int end_vertice) {
  if(end_vertice != INT_MIN) {
    int positionId = results.predecessors[0][end_vertice];
    printDijkstraPath(graph, results, positionId);
    fprintf(stdout, "-> %s ", graph.vertice[end_vertice].name);
  }
}

void printDijkstraDistances(TGraph graph, TResults results) {
  int i;
  for (i = 0; i < graph.vertices_count; i++) {
    printf("%u: %u\n", i, results.distances[0][i]);
  }
}
