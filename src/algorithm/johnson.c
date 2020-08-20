/**
 * Name: Drahník Lukáš
 * Project: IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date: 12.18.2020
 * Email: <xdrahn00@stud.fit.vutbr.cz>
 * File: Soubor zabývající se implementací algoritmu Johnson.
 */

#include "johnson.h"

TResults johnson(TParams params, TGraph graph) {
    int i, j;

    TResults results = {
      .distances = NULL,
      .predecessors = malloc((graph.vertices_count + 1) * sizeof(int * )),
      .ecode = EOK,
    };

    if(results.predecessors == NULL) {
      results.ecode = EALLOC;
      return results;
    }

    // initialize predecessors
    for(i = 0; i < graph.vertices_count + 1; i++) {
      results.predecessors[i] = malloc((graph.vertices_count + 1) * sizeof(int *));
      if(results.predecessors[i] == NULL) {
        results.ecode = EALLOC;
        return results;
      }
      for(j = 0; j < graph.vertices_count + 1; j++) {
        results.predecessors[i][j] = INT_MAX;
      }
    }

    // add tmp vertice
    const char *tmpVertexName = "TMP";
    graph = addVertex(graph, tmpVertexName);
    if(graph.ecode != EOK) {
      results.ecode = graph.ecode;
      return results;
    }

    // add edge with weight 0 from added vertice to each other vertice 
    for(i = 0; i < graph.vertices_count ; i++) {
      if(strcmp(graph.vertice[i]->name, graph.vertice[graph.vertices_count - 1]->name) != 0) {
        graph = addEdge(graph, graph.vertice[graph.vertices_count - 1]->name, graph.vertice[i]->name, 0);
        if(graph.ecode != 0) {
          results.ecode = graph.ecode;
          return results;
        }
      }
    }

    // run Bellman Ford algorithm with newly added vertice as source
    TResults bellman_ford_results = bellmanFord(graph, 0);
    if(bellman_ford_results.ecode != EOK && bellman_ford_results.ecode != ENEGATIVE_CYCLE) {
      results.ecode = bellman_ford_results.ecode;
      return results;
    }

    // reweight
    TGraph modified_graph;
    for(i = 0; i < graph.vertices_count; i++) {
      for(j = 0; j < graph.vertices_count; j++) {
        if(isExistsEdge(graph, i, j)) {
          int new_weight = getEdgeValue(graph, i, j) + bellman_ford_results.distances[0][i] - bellman_ford_results.distances[0][j];
          results.predecessors[j][i] = new_weight;
          modified_graph = changeEdgeWeight(graph, i, j, new_weight);
        }
      }
    }

    // clean Bellman Ford results (used for reweight)
    cleanResults(modified_graph, bellman_ford_results);

    // results.predecessors serve only for printing reweighted edges while debugging (with newly added vertex and edge's) 
    if(params.debug) {
      printBellmanFordPredecessors(modified_graph, results);
      fprintf(stdout, "\n");
    }

    free(results.predecessors[graph.vertices_count - 1]);

    // remove tmp vertice and edge's in graph (in results still stored)
    modified_graph = removeTopVertice(modified_graph);

    // results.predecessors serve only for printing reweighted edges while debugging 
    if(params.debug) {
      printBellmanFordPredecessors(modified_graph, results);
      fprintf(stdout, "\n");
    }

    cleanResults(modified_graph, results);

    // run Dijkstra
    TResults djiskra_results = dijkstra(modified_graph, getPositionOfVertice(modified_graph, params.vertice_start));

    djiskra_results.graph = modified_graph;

    return djiskra_results;
}

void printJohnsonPath(TGraph graph, TResults results, int start_vertice, int end_vertice) {
  char* path = (char *)malloc((strlen(graph.vertice[end_vertice]->name) + 1) * sizeof(char));
  strcpy(path, graph.vertice[end_vertice]->name);
  path[strlen(graph.vertice[end_vertice]->name)] = '\0';

  const char* algorithm_prefix_name = "Johnson";

  printDijkstraPath(graph, results, end_vertice, start_vertice, path, algorithm_prefix_name);

  free(path);
}

void printJohnsonDistances(TGraph graph, TResults results) {
  printDijkstraDistances(graph, results);
}
