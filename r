#!/bin/bash

NAME="solve"

if [ "$#" -eq 1 ]; then
  NAME="$1"
fi

echo "[+] Compiling..."
g++ -std=c++14 -O3 -Wall -Wextra "${NAME}.cpp" -o "${NAME}"

echo "[+] Running..."
TEMP=`mktemp`

for x in in*.txt; do
  y=$(echo $x | sed s/in/out/)
  echo -e "Case: $x\n"
  echo "Actual:"
  ./${NAME} < $x | tee $TEMP
  echo -e "\n"
  echo -e "Expected: "
  cat $y
  diff $y $TEMP
  echo -e "===\n"
done

rm $TEMP
