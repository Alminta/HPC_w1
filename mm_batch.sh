#!/bin/bash
#BSUB -J 93_monitors_blk=1024_3_sizes
#BSUB -o 93_monitors_blk=1024_3_sizes_%J.out
#BSUB -q hpcintro
#BSUB -n 1
#BSUB -R "rusage[mem=512]"
#BSUB -W 60

EXECUTABLE=matmult_c.gcc

# "32 64 128 256 512 1024 2048"
SIZES="1024 2048 4096"

PERM="blk"

# "4 8 16 32 64 128 256 512"
BLKSIZE=1024

export MFLOPS_MAX_IT=10
export MATMULT_COMPARE=0

./$EXECUTABLE $PERM $SIZES $SIZES $SIZES $BLKSIZE

# for B in $BLKSIZE
# do
#     ./$EXECUTABLE $PERM $SIZES $SIZES $SIZES $B
# done

# for B in {8..200..8}
# do
#     ./$EXECUTABLE $PERM $SIZES $SIZES $SIZES $B
# done

for S in $SIZES
do
    ./$EXECUTABLE $PERM $S $S $S $BLKSIZE
done

# PERMS="mnk mkn kmn knm nkm nmk"
# PERMS="mkn kmn"
# for P in $PERMS
# do
#     for S in $SIZES
#     do
#         ./$EXECUTABLE $P $S $S $S $BLKSIZE
#     done
# done