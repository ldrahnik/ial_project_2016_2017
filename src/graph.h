/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 * File:              Soubor zabývající se implementací konverze vstupu z terminálu nebo ze souboru do grafových struktur obsahujících vše důležité pro funkci programu.
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
#include <limits.h>
#include <math.h>

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
  TEdge** edge;
  TVertice** vertice;
  int ecode;
  int debug;
} TGraph;

TGraph stepByStepGraphRoute(char** graph_route, int debug);
TParams parseInputToGraphRoute(TParams params);
TGraph getGraph(TParams params);
int isNumber(char number[]);
int isNonRatedEdge(char* c);
int isEdge(char* c);
int isNumberEdge(char* c);
int getPositionOfVertice(TGraph graph, char* vertice);
int isVerticeValid(TGraph graph, char* vertice);
void cleanGraph(TGraph graph);
void cleanGraphVertex(TGraph graph, int id);
void cleanGraphEdge(TGraph graph, int id);
int getEdgeValue(TGraph graph, int start_vertice_id, int end_vertice_id);
TGraph addVertex(TGraph graph, const char* new_vertex_name);
TGraph addEdge(TGraph graph, char* start_vertice, char* end_vertice, int weight);
TGraph removeTopVertice(TGraph graph);
TGraph changeEdgeWeight(TGraph graph, int start_vertice_id, int end_vertice_id, int new_weight);
int isExistsEdge(TGraph graph, int start_vertice_id, int end_vertice_id);
int getEdgeValueNDigits(int edge_value);

#endif
