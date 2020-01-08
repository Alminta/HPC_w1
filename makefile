TARGET	= libmatmult.so
LIBSRCS	= matmult.c
LIBOBJS	= $(LIBSRCS:.c=.o)
# -O3 -ffast-math -funroll-loops -floop-nest-optimize -floop-unroll-and-jam
OPT	= -g -O3 -funroll-loops
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