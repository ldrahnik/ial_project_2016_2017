ASSESSMENT 
==========

8.9/15b ([assessment report](https://github.com/ldrahnik/ial_project_2017_2018/issues/2))

SHREYA - Nejkratší cesta v grafu
============

Program hledá nejkratší cestu v grafu mezi dvěma zadanými vrcholy. Pokud není explicitně uvedeno zda se jedná o ohodnocený (`-r`) nebo neohodnocený (`-u`) graf, nastaví se automaticky ohodnocený v případě nalezení alespoň 1 ohodnocené hrany. Orientovanost (`-o`) je nutné vždy explicitně vyžádat argumentem.

## Příklad spuštění:

```
./shreya -h
The shorted path in graph between two vertices. If the type of graph would be not explicitly defined by options are automatically defined from graph.

Example of usage:

./shreya [-h ] [-r] [-o] [-i <graph_path as string>] <vertice_start> <vertice_end>

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

```
make test
bash ./tests/_run-tests.sh /home/ldrahnik/projects/ial_project_2017_2018 /home/ldrahnik/projects/ial_project_2017_2018/tests/log /home/ldrahnik/projects/ial_project_2017_2018/tests/ /home/ldrahnik/projects/ial_project_2017_2018/graphviz/convert_script.py
bash ./tests/_run-tests-diff.sh /home/ldrahnik/projects/ial_project_2017_2018 /home/ldrahnik/projects/ial_project_2017_2018/tests/log /home/ldrahnik/projects/ial_project_2017_2018/tests/
*******TEST test01 PASSED
*******TEST test02 PASSED
*******TEST test03 PASSED
*******TEST test04 PASSED
*******TEST test05 PASSED
*******TEST test06 PASSED
rm -rf /home/ldrahnik/projects/ial_project_2017_2018/tests/log/*
```

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
