#!/usr/bin/env bash

BIN_DIR=$1

# tests
LOG_PATH=$2/
REF_PATH=$3/

for TEST_FILE_NAME in $(find $REF_PATH -maxdepth 1 -type f -name "*.out" -printf "%f\n" | sort); do
    TEST_NAME=${TEST_FILE_NAME%.out}
    SUCCESS=true

    # prochází všechna očekávaná řešení
    while read SOLUTION_LINE; do

        # kontroluje zda každé z očekávaných řešení existuje ve výstupu programu
        if !(grep -Fxq "$SOLUTION_LINE" $LOG_PATH$TEST_FILE_NAME); then
            SUCCESS=false
            echo "TEST $TEST_NAME SOLUTION '$SOLUTION_LINE' NOT FOUND";
        fi
    done <$REF_PATH$TEST_FILE_NAME

    # pokud byly všechny hledaná řešení nalezeny, test byl úspěšně dokončen
    if $SUCCESS; then
        echo "*******TEST $TEST_NAME PASSED";
    else
        echo "TEST $TEST_NAME FAILED";
    fi

done
