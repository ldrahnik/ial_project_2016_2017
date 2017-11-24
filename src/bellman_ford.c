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
    .distances = malloc(graph.vertices_count * sizeof(int)),
    .predecessors = malloc(graph.vertices_count * sizeof(int)),
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
    results.distances[i] = INT_MAX;
    results.predecessors[i] = -1;
  }

  // distance to starting vertice is 0
  results.distances[vertice_id] = 0;

  // relax edges repeatedly
  for(v = 0; v < graph.vertices_count; v++) {
    for (a = 0; a < graph.edges_count; a++) {

      int src_id = graph.edge[a].src_id;
      int dest_id = graph.edge[a].dest_id;
      int weight = graph.edge[a].weight;

      printf("\nweight: %i\n", weight);
      printf("\nsrc_id [ %i ] : %i\n", src_id, results.distances[src_id]);
      if (results.distances[src_id] != INT_MAX && results.distances[src_id] + weight < results.distances[dest_id]) {
        results.distances[dest_id] = results.distances[src_id] + weight;
        results.predecessors[dest_id] = src_id;
        printf("\ndistances[dest_id: %i]: %i\n", dest_id, results.distances[dest_id]);
      }
    }
  }

  // check for negative weight cycle
  for(a = 0; a < graph.edges_count && !negative_cycle; a++) {

    int src_id = graph.edge[a].src_id;
    int dest_id = graph.edge[a].dest_id;
    int weight = graph.edge[a].weight;

    negative_cycle = results.distances[src_id] + weight < results.distances[dest_id];
  }

  // negative cycle
  if(negative_cycle) {
    free(results.distances);
    free(results.predecessors);
    results.distances = NULL;
  }

  return results;
}
