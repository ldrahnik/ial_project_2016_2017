/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 */

#include "bellman_ford.h"

TResults bellmanFord(TGraph graph, int vertice_id) {
  int i, a, v, negative_cycle = 0;

  TResults results = {
    .distances = malloc(graph.vertices_count * sizeof(int *)),
    .predecessors = malloc(graph.vertices_count * sizeof(int *)),
    .ecode = EOK,
  };
  if(results.distances == NULL) {
    results.ecode = EALLOC;
    return results;
  }
  if(results.predecessors == NULL) {
    results.ecode = EALLOC;
    return results;
  }

  // all distances start infinite
  for(i = 0; i < graph.vertices_count; i++) {
    results.distances[i] = malloc(graph.vertices_count * sizeof(int));
    results.predecessors[i] = malloc(graph.vertices_count * sizeof(int));
    results.distances[0][i] = INT_MAX;

    for(v = 0; v < graph.vertices_count; v++) {
      results.predecessors[i][v] = 0;
    }
  }

  // distance to starting vertice is 0
  results.distances[0][vertice_id] = 0;

  // relax edges repeatedly
  for(v = 0; v < graph.vertices_count; v++) {
    for (a = 0; a < graph.edges_count; a++) {

      int src_id = graph.edge[a].src_id;
      int dest_id = graph.edge[a].dest_id;
      int weight = graph.edge[a].weight;

      if (results.distances[0][src_id] != INT_MAX && results.distances[0][src_id] + weight < results.distances[0][dest_id]) {
        results.distances[0][dest_id] = results.distances[0][src_id] + weight;
      }

      if (results.distances[0][src_id] != INT_MAX && results.distances[0][src_id] + weight <= results.distances[0][dest_id]) {
        results.predecessors[dest_id][src_id] = 1;
      }
    }
  }

  // check for negative weight cycle
  for(a = 0; a < graph.edges_count && !negative_cycle; a++) {

    int src_id = graph.edge[a].src_id;
    int dest_id = graph.edge[a].dest_id;
    int weight = graph.edge[a].weight;

    negative_cycle = results.distances[0][src_id] + weight < results.distances[0][dest_id];
  }

  // negative cycle
  if(negative_cycle) {
    results.ecode = ENEGATIVE_CYCLE;
  }

  return results;
}

void printBellmanFordPredecessors(TGraph graph, TResults results) {
  int v, a;
  for(v = 0; v < graph.vertices_count; v++) {
    for(a = 0; a < graph.vertices_count; a++) {
      int isEdgeValid = results.predecessors[v][a];
      if(isEdgeValid) {
        printf("dest_id: %i [ dest: %s ] -> src_id %i [ src: %s ]\n", v, graph.vertice[v].name, a, graph.vertice[a].name);
      }
    }
  }
}

void printBellmanFordPath(TGraph graph, TResults results, int end_vertice, int start_vertice, char* path) {
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
        printBellmanFordPath(graph, results, end_vertice, a, pathNew);
      }
    }
    free(pathNew);
  }
}


void printBellmanFordDistances(TGraph graph, TResults results) {
  int i;
  for(i = 0; i < graph.vertices_count; i++) {
    fprintf(stderr, "%u: %d\n", i, results.distances[0][i]);
  }
}
