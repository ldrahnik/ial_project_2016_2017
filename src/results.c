/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 */

#include "results.h"

#include <stdlib.h>

/**
 * Clean the mess.
 */
void cleanResults(TGraph graph, TResults results) {
  int i;
  for (i = 0; i < graph.vertices_count; i++) {
    free(results.distances[i]);
    free(results.predecessors[i]);
  }
  free(results.distances);
  free(results.predecessors);
}
