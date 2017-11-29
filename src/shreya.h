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

#ifndef _shreya_H_
#define _shreya_H_

#include "error.h"
#include "graph.h"
#include "params.h"
#include "floyd_warshall.h"
#include "bellman_ford.h"
#include "dijkstra.h"
#include "results.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char *argv[]);

#endif
