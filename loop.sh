#!/bin/bash
EXECUTABLE=matmult_c.gcc
PERM="kmn"
BLKSIZE=32
MKN = "1000 1000 1000"
counter = 20
while [ $counter -le 30 ]
do
    ./$EXECUTABLE $PERM $MKN $counter $BLKSIZE
    ((counter++))
done