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
  for(i = 0; i < graph.vertices_count; i++) {
    results.distances[i] = malloc(graph.vertices_count * sizeof(int));
    results.predecessors[i] = malloc(graph.vertices_count * sizeof(int));
    results.distances[0][i] = INT_MAX;
    unvisited[i] = 1;

    for(v = 0; v <graph.vertices_count; v++) {
      results.predecessors[i][v] = 0;
    }
  }

  // Distance to starting vertex is 0
  results.distances[0][vertice_id] = 0;

  while (unvisited_count > 0) {

    // Update the distances to all neighbours
    for (e = 0; e < graph.edges_count; e++) {
      if (graph.edge[e].src_id == current || graph.edge[e].dest_id == current) {
        int neighbour = graph.edge[e].src_id == current ? graph.edge[e].dest_id : graph.edge[e].src_id;
        int distance = results.distances[0][current] + graph.edge[e].weight;
        if (distance < results.distances[0][neighbour]) {
          results.distances[0][neighbour] = distance;
        }
        if (distance <= results.distances[0][neighbour]) {
          results.predecessors[neighbour][current] = 1;
        }
        // TODO: cycle removing already not shortest ways
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
        fprintf(stderr, "DEBUG: dest_id: %i [ dest: %s ] -> src_id %i [ src: %s ]\n", v, graph.vertice[v].name, a, graph.vertice[a].name);
      }
    }
  }
}

void printDijkstraPath(TGraph graph, TResults results, int end_vertice, int start_vertice, char* path) {
  if(start_vertice != INT_MIN) {
    char* pathNew = (char *)malloc(100 * sizeof(char));
    strcpy(pathNew, path);
    strcat(pathNew, "-> ");
    strcat(pathNew, graph.vertice[start_vertice].name);
    strcat(pathNew, " ");
    if(end_vertice == start_vertice) {
      fprintf(stdout, "%s\n", pathNew);
    }
    int a;
    for(a = 0; a < graph.vertices_count; a++) {
      int isEdgeValid = results.predecessors[a][start_vertice];
      if(isEdgeValid) {
        printDijkstraPath(graph, results, end_vertice, a, pathNew);
      }
    }
    free(pathNew);
  }
}

void printDijkstraDistances(TGraph graph, TResults results) {
  fprintf(stderr, "\n");
  int i;
  for (i = 0; i < graph.vertices_count; i++) {
    fprintf(stderr, "DEBUG: %u: %u\n", i, results.distances[0][i]);
  }
}
