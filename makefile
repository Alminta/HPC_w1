TARGET	= libmatmult.so
LIBSRCS	= matmult.c
LIBOBJS	= $(LIBSRCS:.c=.o)
OPT	= -g -O3 -mfpmath=sse -march=core-avx2 -DUSE_RESTRICT -funroll-loops
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