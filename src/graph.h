/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 */

#ifndef _graph_H_
#define _graph_H_

#include "error.h"
#include "params.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

typedef struct edge {
  char* src;
  int src_id;
  char* dest;
  int dest_id;
  int weight;
} TEdge;

typedef struct vertice {
  char* name;
} TVertice;

typedef struct graph {
  int edges_count;
  int vertices_count;
  int contains_negative_edge;
  int is_graph_rated;
  int is_graph_oriented;
  TEdge* edge;
  TVertice* vertice;
  int ecode;
} TGraph;

TGraph stepByStepGraphRoute(char** graph_route);
char** parseInputToGraphRoute(char* input);
TGraph getGraph(TParams params);
int isNumber(char number[]);
int isNonRatedEdge(char* c);
int isEdge(char* c);
int isNumberEdge(char* c);
int getPositionOfVertice(TGraph graph, char* vertice);
int isVerticeValid(TGraph graph, char* vertice);

#endif
