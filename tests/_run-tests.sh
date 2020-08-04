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

# test01: orientovaný
$TASK -i ${REF_PATH}test01.in A F -o > ${LOG_PATH}test01.out 2> ${LOG_PATH}test01.err
echo -n $? > ${LOG_PATH}test01.rc
$GRAPHVIZ_TASK --input ${REF_PATH}test01.in --output ${REF_PATH}test01.png -o
