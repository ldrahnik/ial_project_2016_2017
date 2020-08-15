#!/usr/bin/env bash

BIN_DIR=$1

# program
TASK_NAME=shreya
TASK=$BIN_DIR/$TASK_NAME

# tests
LOG_PATH=$2/
REF_PATH=$3/

# graphiz
GRAPHVIZ_TASK_SCRIPT=$4
GRAPHVIZ_TASK_INTERPRET=python3.6
GRAPHVIZ_TASK="$GRAPHVIZ_TASK_INTERPRET $GRAPHVIZ_TASK_SCRIPT"

# test01: cesta v orientovaném grafu
$TASK -i ${REF_PATH}test01.in A F -o > ${LOG_PATH}test01.out 2> ${LOG_PATH}test01.err
echo -n $? > ${LOG_PATH}test01.rc
$GRAPHVIZ_TASK --input ${REF_PATH}test01.in --output ${REF_PATH}test01.png -o

# test02: 2 srovnatelně krátké cesty, jedna se zápornou hranou)
$TASK -i ${REF_PATH}test02.in A B -o > ${LOG_PATH}test02.out 2> ${LOG_PATH}test02.err
echo -n $? > ${LOG_PATH}test02.rc
$GRAPHVIZ_TASK --input ${REF_PATH}test02.in --output ${REF_PATH}test02.png -o

# test03: cesta v orientovaném grafu
$TASK -i ${REF_PATH}test03.in F A -o > ${LOG_PATH}test03.out 2> ${LOG_PATH}test03.err
echo -n $? > ${LOG_PATH}test03.rc
$GRAPHVIZ_TASK --input ${REF_PATH}test03.in --output ${REF_PATH}test03.png -o

# Expected:
#
# -> F -> D -> B -> C -> A
#

# test04: diamant, 2 cesty v neorientovaném grafu (Dijkstra)
$TASK -i ${REF_PATH}test04.in A D > ${LOG_PATH}test04.out 2> ${LOG_PATH}test04.err
echo -n $? > ${LOG_PATH}test04.rc
$GRAPHVIZ_TASK --input ${REF_PATH}test04.in --output ${REF_PATH}test04.png

# Expected:
#
# -> A -> B -> D 
# -> A -> C -> D 
#

# test05: cesta v orientovaném grafu
$TASK -i ${REF_PATH}test05.in A E -o > ${LOG_PATH}test05.out 2> ${LOG_PATH}test05.err
echo -n $? > ${LOG_PATH}test05.rc
$GRAPHVIZ_TASK --input ${REF_PATH}test05.in --output ${REF_PATH}test05.png -o

# Expected:
#
# -> A -> C -> F -> E 
# -> A -> C -> E 
# -> A -> D -> F -> E
#

# test06: dvojitý diamant, 4 nejkratší cesty v neorientovaném grafu (Dijkstra)
$TASK -i ${REF_PATH}test06.in A G > ${LOG_PATH}test06.out 2> ${LOG_PATH}test06.err
echo -n $? > ${LOG_PATH}test06.rc
$GRAPHVIZ_TASK --input ${REF_PATH}test06.in --output ${REF_PATH}test06.png

# Expected:
#
# -> A -> B -> D -> E -> G
# -> A -> B -> D -> F -> G
# -> A -> C -> D -> F -> G
# -> A -> C -> D -> E -> G
#
