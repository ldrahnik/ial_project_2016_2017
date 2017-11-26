/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 */

#include "bellman_ford.h"

TResults bellmanFord(TGraph graph, int vertice_id) {
  int i;

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

  int a, v, negative_cycle = 0;

  // all distances start infinite
  for(i = 0; i < graph.vertices_count; i++) {
    results.distances[i] = malloc(graph.vertices_count * sizeof(int));
    results.predecessors[i] = malloc(graph.vertices_count * sizeof(int));
    results.distances[0][i] = INT_MAX;
    results.predecessors[0][i] = INT_MIN;
  }

  // distance to starting vertice is 0
  results.distances[0][vertice_id] = 0;

  // relax edges repeatedly
  for(v = 0; v < graph.vertices_count; v++) {
    for (a = 0; a < graph.edges_count; a++) {

      int src_id = graph.edge[a].src_id;
      int dest_id = graph.edge[a].dest_id;
      int weight = graph.edge[a].weight;

      //printf("\nweight: %i\n", weight);
      //printf("\nsrc_id [ %i ] : %i\n", src_id, results.distances[0][src_id]);
      if (results.distances[0][src_id] != INT_MAX && results.distances[0][src_id] + weight < results.distances[0][dest_id]) {
        results.distances[0][dest_id] = results.distances[0][src_id] + weight;
        results.predecessors[0][dest_id] = src_id;
        //printf("\ndistances[dest_id: %i]: %i\n", dest_id, results.distances[0][dest_id]);
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
    cleanResults(graph, results);
    results.distances = NULL;
  }

  return results;
}

void printBellmanFordPath(TGraph graph, TResults results, int end_vertice) {
  if(end_vertice != INT_MIN) {
    int positionId = results.predecessors[0][end_vertice];
    printBellmanFordPath(graph, results, positionId);
    fprintf(stdout, "-> %s ", graph.vertice[end_vertice].name);
  }
}

void printBellmanFordDistances(TGraph graph, TResults results) {
  int i;
  for(i = 0; i < graph.vertices_count; i++) {
    fprintf(stderr, "%u: %d\n", i, results.distances[0][i]);
  }
}
