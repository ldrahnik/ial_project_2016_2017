/**
 * Name:							Tučková Martina, Tussupová Kymbat, Lázňovský David, Drahník Lukáš
 * Project: 					IAL: náhradní projekt: 4. Nejkratší cesta v grafu
 * Date:							21.10.2017
 * Email:						  <xtucko00@stud.fit.vutbr.cz>, <xtussu00@stud.fit.vutbr.cz>, <xlazno00@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
 * File:              Hlavní entry point programu.
 */


/**
 * Posloupnost vrcholů a hran grafu, kde každá hrana má za koncové vrcholy předchozí a následující vrchol této posloupnosti (pro orientované
 * grafy musí souhlasit i orientace hrany od předchozího k následujícímu vrcholu posloupnosti) a kde se každá hrana vyskytuje nejvýše jednou,
 * se nazývá (orientovaná) cesta.
 *
 * Vytvořte program pro hledání nejkratší cesty v grafu mezi dvěma zadanými vrcholy. Úlohu řešte pro neorientované i orientované grafy a pro
 * neohodnocené i ohodnocené grafy. V případě ohodnocených grafů považujte za vzdálenost vrcholů ohodnocení hrany mezi nimi.
 *
 * Pokud existuje více řešení, nalezněte všechna. Výsledky prezentujte vhodným způsobem. Součástí projektu bude načítání grafů ze souboru a
 * vhodné testovací grafy. V dokumentaci uveďte teoretickou složitost úlohy a porovnejte ji s experimentálními výsledky.
 */

#include "shreya.h"

const char *HELP_MSG = {
  "The shorted path in graph between two vertices. If the type of graph would be not explicitly defined by options are automatically defined from graph.\n\n"
  "Example of usage:\n\n"
  "./shreya [-h ] [-r] [-o] [-i <graph_path as string>] <vertice_start> <vertice_end>\n\n"
  "Options:\n"
  "-r -- rated graph\n"
  "-u -- non-rated graph\n"
  "-o -- oriented graph\n"
  "-h -- show help message\n"
  "-i -- string contains graph_path (for example rated graph vertice0 -> 4 -> vertice1)\n"
  "<vertice> -- name of valid vertice (first is start, second is end)\n"
};

/**
 * Entry point of application.
 *
 * @param int argc
 * @param char *argv[]
 *
 * @return int
 */
int main(int argc, char *argv[]) {
  int ecode = EOK;

  // get params
  TParams params = getParams(argc, argv);
  if(params.ecode != EOK) {
    return params.ecode;
  }

  if(params.debug)
    fprintf(stderr, "DEBUG: getParams() successfuly ended.\n\n");

  // help message
  if(params.show_help_message) {
    printf("%s", HELP_MSG);
    cleanParams(params);
    return ecode;
  }

  // get graph
  TGraph graph = getGraph(params);
  if(graph.ecode != EOK) {
    cleanParams(params);
    return params.ecode;
  }

  if(params.debug) {
    fprintf(stderr, "DEBUG: vertices count: %i\n\n", graph.vertices_count);
    fprintf(stderr, "DEBUG: edges count: %i\n\n", graph.edges_count);
    fprintf(stderr, "\nDEBUG: getGraph() successfuly ended.\n\n");
  }

  int start_position = getPositionOfVertice(graph, params.vertice_start);
  int end_position = getPositionOfVertice(graph, params.vertice_end);

  // Floyd Warshall and Bellman Ford only rated graph
  if(graph.is_graph_oriented) {
    fprintf(stdout, "Floyd Warshall:\n");

    TResults results = floydWarshall(graph);

    if(results.ecode != EOK) {
      fprintf(stderr, "Alloc problem.\n");
      cleanResults(graph, results);
      return results.ecode;
    }

    if (params.debug) {
      printFloydWarshallDistances(graph, results);
      fprintf(stdout, "\n");
    }

    // TODO: more ways
    fprintf(stdout, "FloydWarshall: ");
    printFloydWarshallPath(params, graph, results, start_position, end_position);

    fprintf(stdout, "\n\n");

    cleanResults(graph, results);
  }

  // Floyd Warshall and Bellman Ford only rated graph
  if(graph.is_graph_oriented) {
    fprintf(stdout, "Bellman Ford:\n");

    TResults results = bellmanFord(graph, start_position);

    if(results.ecode != EOK) {
      if(results.ecode == ENEGATIVE_CYCLE) {
        fprintf(stderr, "Negative cycle detection which bellman ford can not handle.\n");
      } else if(results.ecode == EALLOC) {
        fprintf(stderr, "Alloc problem.\n");
        cleanResults(graph, results);
        return results.ecode;
      } else {
        cleanResults(graph, results);
        return results.ecode;
      }
    }

    if(params.debug) {
      printBellmanFordDistances(graph, results);
      fprintf(stdout, "\n");
    }

    if(params.debug) {
      printBellmanFordPredecessors(graph, results);
      fprintf(stdout, "\n");
    }

    char* path = (char *)malloc(100 * sizeof(char));
    path[0] = '\0';
    printBellmanFordPath(graph, results, end_position, start_position, 0, path);
    free(path);

    fprintf(stdout, "\n");

    cleanResults(graph, results);
  }

  // Dijkstra does not handle negative edge
  if(!graph.contains_negative_edge) {
    fprintf(stdout, "Dijkstra:\n");

    TResults results = dijkstra(graph, start_position);

    if(results.ecode != EOK) {
      fprintf(stderr, "Alloc problem.\n");
      cleanResults(graph, results);
      return results.ecode;
    }

    if(params.debug) {
      printDijkstraDistances(graph, results);
      fprintf(stdout, "\n");
    }

    char* path = (char *)malloc((strlen(params.vertice_end) + 1) * sizeof(char));
    strcpy(path, params.vertice_end);
    path[strlen(params.vertice_end)] = '\0';
    const char* algorithm_prefix_name = "Dijkstra";
    printDijkstraPath(graph, results, end_position, start_position, path, algorithm_prefix_name);
    free(path);

    fprintf(stdout, "\n");

    cleanResults(graph, results);
  }

  // Johnson algorithm
  if(graph.is_graph_oriented) {
    fprintf(stdout, "Johnson:\n");

    TResults results = johnson(params, graph);
    // TODO: graph is modified for next algorithms!!!
    graph = results.graph; // johnson method change graph (add vertex and edges, than remove but realloc was called)

    if(results.ecode != EOK) {
      fprintf(stderr, "Alloc problem.\n");
      cleanResults(graph, results);
      return results.ecode;
    }

    if(params.debug) {
      printJohnsonDistances(graph, results);
      fprintf(stdout, "\n");
    }

    printJohnsonPath(graph, results, start_position, end_position);

    cleanResults(graph, results);
  }

  cleanParams(params);
  cleanGraph(graph);

  return ecode;
}
