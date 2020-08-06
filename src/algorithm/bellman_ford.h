/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 * File:              Soubor zabývající se implementací algoritmu Bellman Ford.
 */

#ifndef _bellman_ford_H_
#define _bellman_ford_H_

#include "../graph.h"
#include "../results.h"

#include <stdlib.h>
#include <limits.h>

TResults bellmanFord(TGraph graph, int vertice_id);
void printBellmanFordPath(TGraph graph, TResults results, int end_vertice, int start_vertice, int edge_value_to_start_vertice, char* path);
void printBellmanFordDistances(TGraph graph, TResults results);
void printBellmanFordPredecessors(TGraph graph, TResults results);

#endif
