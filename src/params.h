/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 * File:              Soubor zabývající prací s parametry a argumenty programu, jejich naplněním do struktury používané v dalších částech projektu i dealokování.
 */

#ifndef _params_H_
#define _params_H_

#include "error.h"

typedef struct params {
  int show_help_message;                // option i
  int ecode;                            // error code
  char* input;
  char** graph_route;                   // format rated: vertice0 -> number (positive or negative) -> vertice1
  int graph_route_length;
                                        // format unrated: vertice0 -> +/- -> vertice1 -> +/- -> vertice2 -> +/- -> vertice3
  int contains_negative_edge;           // some algorithm does not support negative edge
  int is_graph_rated;                   // program take care about numbers
  int is_graph_oriented;                // program take care about direction
  char* vertice_start;
  char* vertice_end;
  int debug;
} TParams;

TParams getParams(int argc, char *argv[]);
void cleanParams(TParams params);

#endif
