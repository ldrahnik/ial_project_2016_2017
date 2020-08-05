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

# Expected:
#
# -> A -> D -> B -> C -> F
#

# test02: 2 srovnatelně krátké cesty, jedna se zápornou hranou)
$TASK -i ${REF_PATH}test02.in A B -o > ${LOG_PATH}test02.out 2> ${LOG_PATH}test02.err
echo -n $? > ${LOG_PATH}test02.rc
$GRAPHVIZ_TASK --input ${REF_PATH}test02.in --output ${REF_PATH}test02.png -o

# Expected:
#
# -> A -> C -> B 
# -> A -> B 
#

# test03: cesta v orientovaném grafu
$TASK -i ${REF_PATH}test03.in F A -o > ${LOG_PATH}test03.out 2> ${LOG_PATH}test03.err
echo -n $? > ${LOG_PATH}test03.rc
$GRAPHVIZ_TASK --input ${REF_PATH}test03.in --output ${REF_PATH}test03.png -o

# Expected:
#
# -> F -> D -> B -> C -> A
#

# test04: cesta v neorientovaném grafu (Dijkstra)
$TASK -i ${REF_PATH}test04.in A D -o > ${LOG_PATH}test04.out 2> ${LOG_PATH}test04.err
echo -n $? > ${LOG_PATH}test04.rc
$GRAPHVIZ_TASK --input ${REF_PATH}test04.in --output ${REF_PATH}test04.png

# Expected:
#
# -> A -> B -> D 
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
