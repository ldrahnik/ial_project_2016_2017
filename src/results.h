/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 * File:              Soubor zabývající prací s návratovými hodnotami algoritmů, jejich naplněním do struktury používané v dalších částech projektu při vyhodnocování na standartní výstup. Také se stará o dealokaci.
 */

#ifndef _results_H_
#define _results_H_

#include "graph.h"

typedef struct results {
  int** distances;
  int** predecessors;
  TGraph graph; // if was modified graph inside algorithm - required for correct free after results printing
  int ecode;
} TResults;

void cleanResults(TGraph graph, TResults results);
char* addEdgeToPath(char* path, char* src_vertex_name, int edge_value,  int copy_before);

#endif
