/**
 * Name: Drahník Lukáš
 * Project: IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date: 12.18.2020
 * Email: <xdrahn00@stud.fit.vutbr.cz>
 * File: Soubor zabývající se implementací algoritmu Johnson.
 */

#ifndef _johnson_H_
#define _johnson_H_

#include "../graph.h"
#include "../results.h"
#include "bellman_ford.h"
#include "dijkstra.h"
#include "../params.h"

#include <stdlib.h>
#include <limits.h>

TResults johnson(TParams params, TGraph graph);
void printJohnsonPath(TGraph graph, TResults results, int start_vertice, int end_vertice);
void printJohnsonDistances(TGraph graph, TResults results);

#endif
