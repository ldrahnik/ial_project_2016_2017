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
    if(results.distances != NULL && results.distances[i] != NULL)
      free(results.distances[i]);
    if(results.predecessors != NULL && results.predecessors[i] != NULL)
      free(results.predecessors[i]);
  }
  if(results.distances != NULL)
    free(results.distances);
  if(results.predecessors != NULL) {
    free(results.predecessors);
  }
}

char* addEdgeToPath(char* path, char* src_vertex_name, int edge_value, int copy_before) {
  const char* before_edge = " -(";
  const char* after_edge = ")> ";

  int edge_value_n_digits = getEdgeValueNDigits(edge_value);

  int path_new_length = strlen(path) + strlen(src_vertex_name) + 1 + strlen(before_edge) + strlen(after_edge) + edge_value_n_digits + 2;
  char* path_new = (char*)malloc(path_new_length * sizeof(char));

  path_new[0] = '\0';

  if(copy_before) {
    strcpy(path_new, path);
  } else {
    strcat(path_new, src_vertex_name);
  }

  strcat(path_new, before_edge);

  char* edge_value_string = (char*)malloc((edge_value_n_digits + 2) * sizeof(char));
  sprintf(edge_value_string, "%d", edge_value);
  strcat(path_new, edge_value_string);
  free(edge_value_string);

  strcat(path_new, after_edge);

  if(!copy_before) {
    strcat(path_new, path);
  } else {
    strcat(path_new, src_vertex_name);
  }

  return path_new;
}
