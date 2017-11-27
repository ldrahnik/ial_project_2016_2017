/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 */

#include "floyd_warshall.h"

// TODO: algoritm do not find all paths
TResults floydWarshall(TGraph graph) {
    int i, j, k;

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

    // initialise the distance table */
    for (i = 0; i < graph.vertices_count; i++) {
      results.distances[i] = malloc(graph.vertices_count * sizeof(int));
      results.predecessors[i] = malloc(graph.vertices_count * sizeof(int));
      for (j = 0; j < graph.vertices_count; j++) {
        results.predecessors[i][j] = i;
        if (i == j) {
            results.distances[i][j] = 0;
        } else {
            results.distances[i][j] = INT_MAX;
        }
        results.predecessors[i][j] = i;
        if(i != j && results.distances[i][j] == 0) {
          results.predecessors[i][j] = INT_MIN;
        }
      }
    }

    // add the distance for each arc
    for (i = 0; i < graph.edges_count; i++) {
        results.distances[graph.edge[i].src_id][graph.edge[i].dest_id] = graph.edge[i].weight;
    }

    // calculate the rest of the distances
    for (i = 0; i < graph.vertices_count; i++) {
        for (j = 0; j < graph.vertices_count; j++) {
            for (k = 0; k < graph.vertices_count; k++) {
                int djk = results.distances[j][k];
                int dji = results.distances[j][i];
                int dik = results.distances[i][k];
                if (dji != INT_MAX && dik != INT_MAX && djk > dji + dik) {
                    results.distances[j][k] = dji + dik;
                    results.predecessors[j][k] = results.predecessors[i][k];
                }
            }
        }
    }
    return results;
}

void printFloydWarshallPath(TGraph graph, TResults results, int start_vertice, int end_vertice) {
  if (start_vertice == end_vertice) {
    fprintf(stdout, "-> %s ", graph.vertice[start_vertice].name);
  } else if (results.predecessors[start_vertice][end_vertice] == INT_MIN) {
    fprintf(stdout, "%s -> %s", graph.vertice[start_vertice].name, graph.vertice[end_vertice].name);
  } else {
    printFloydWarshallPath(graph, results, start_vertice, results.predecessors[start_vertice][end_vertice]);
    fprintf(stdout, "-> %s ", graph.vertice[end_vertice].name);
  }
}

void printFloydWarshallDistances(TGraph graph, TResults results) {
  printf("\n");
  int i, j;
  for (i = 0; i < graph.vertices_count; i++) {
    for (j = 0; j < graph.vertices_count; j++) {
      fprintf(stderr, "DEBUG: %d ", results.distances[i][j]);
    }
    putchar('\n');
  }
}
