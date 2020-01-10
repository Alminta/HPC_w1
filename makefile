TARGET	= libmatmult.so
LIBSRCS	= matmult.c
LIBOBJS	= $(LIBSRCS:.c=.o)
# -O3 -ffast-math -funroll-loops -floop-nest-optimize -floop-unroll-and-jam -msse -mavx -mfpmath=sse -march=core-avx2
#  -O3 -mfpmath=sse -march=core-avx2 -DUSE_RESTRICT
OPT	= -g -O3 -DUSE_RESTRICT -mfpmath=sse -march=core-avx2 -funroll-loops
PIC	= -fPIC

CC	= gcc
CFLAGS= $(OPT) $(PIC) $(XOPTS)

SOFLAGS = -shared 
XLIBS	= 

$(TARGET): $(LIBOBJS)
	$(CC) -o $@ $(SOFLAGS) $(LIBOBJS) $(XLIBS)

clean:
	@/bin/rm -f core core.* $(LIBOBJS) 


matmult.o: matmult.c matmult.h