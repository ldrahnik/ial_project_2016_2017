ASSESSMENT 
==========

8.9/15b ([assessment report](https://github.com/ldrahnik/ial_project_2017_2018/issues/2))

SHREYA - Nejkratší cesta v grafu
============

Program hledá nejkratší cestu v grafu mezi dvěma vrcholy. Pokud není typ grafu explicitně zadaný argumentem (ohodnocený `-r`, neohodnocený `-u` a orientovaný `-o`) je typ automaticky rozpoznaný ze zadaného grafu.

## Příklad spuštění:

```
./shreya -h
The shorted path in graph between two vertices. If the type of graph would be not explicitly defined by options are automatically defined from graph.

Example of usage:

./shreya [-h ] [-r|-nr] [-o|-no] [-i <graph_path as string>] <vertice_start> <vertice_end>

Options:
-r -- rated graph
-u -- non-rated graph
-o -- oriented graph
-h -- show help message
-i -- string contains graph_path (for example rated graph vertice0 -> 4 -> vertice1)
<vertice> -- name of valid vertice (first is start, second is end)
```

## Omezení programu:

## Rozšíření programu:

Přidaný volitelný debugovací parametr `[-d]`.

## Testování programu:

## Odevzdané soubory:

```
xdrahn00
├── Makefile
├── manual.pdf
└── src
    ├── algorithm
    │   ├── bellman_ford.c
    │   ├── bellman_ford.h
    │   ├── dijkstra.c
    │   ├── dijkstra.h
    │   ├── floyd_warshall.c
    │   └── floyd_warshall.h
    ├── error.h
    ├── graph.c
    ├── graph.h
    ├── params.c
    ├── params.h
    ├── results.c
    ├── results.h
    ├── shreya.c
    └── shreya.h
```
