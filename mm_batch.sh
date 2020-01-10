#!/bin/bash
#BSUB -J 8_monitors_blk_many_optim
#BSUB -o 8_monitors_blk_many_optim%J.out
#BSUB -q hpcintro
#BSUB -n 1
#BSUB -R "rusage[mem=512]"
#BSUB -W 60

EXECUTABLE=matmult_c.gcc

# "32 64 128 256 512 1024 2048"
SIZES="2048"

PERM="blk"

# "4 8 16 32 64 128 256 512"
BLKSIZE=128

export MFLOPS_MAX_IT=10
export MATMULT_COMPARE=0

# ./$EXECUTABLE $PERM $SIZES $SIZES $SIZES $BLKSIZE

# for B in $BLKSIZE
# do
#     ./$EXECUTABLE $PERM $SIZES $SIZES $SIZES $B
# done

for B in {2..400..2}
do
    ./$EXECUTABLE $PERM $SIZES $SIZES $SIZES $B
done

# for S in $SIZES
# do
#     ./$EXECUTABLE $PERM $S $S $S $BLKSIZE
# done

# PERMS="mnk mkn kmn knm nkm nmk"

# for P in $PERMS
# do
#     for S in $SIZES
#     do
#         ./$EXECUTABLE $P $S $S $S $BLKSIZE
#     done
# done