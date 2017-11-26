/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 */

#ifndef _floyd_warshall_H_
#define _floyd_warshall_H_

#include "graph.h"
#include "results.h"

#include <stdlib.h>
#include <limits.h>

TResults floydWarshall(TGraph graph);
void printPath(TGraph graph, TResults results, int i, int j);
void printDistances(TGraph graph, TResults results);

#endif
