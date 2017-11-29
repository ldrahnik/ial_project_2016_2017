/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 * File:              Soubor zabývající prací s návratovými hodnotami algoritmů, jejich naplněním do struktury používané v dalších částech projektu při vyhodnocování na standartní výstup. Také se stará o dealokaci.
 */

#include "results.h"

#include <stdlib.h>

/**
 * Clean the mess.
 */
void cleanResults(TGraph graph, TResults results) {
  int i;
  for (i = 0; i < graph.vertices_count; i++) {
    if(results.distances[i] != NULL)
      free(results.distances[i]);
    if(results.predecessors[i] != NULL)
      free(results.predecessors[i]);
  }
  if(results.distances != NULL)
    free(results.distances);
  if(results.predecessors != NULL) {
    free(results.predecessors);
  }
}
