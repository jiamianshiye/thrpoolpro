OBJ=thrMain

sources = *.c
CC=gcc
#CC=aarch64-linux-gnu-gcc

LDFLAGS+=-lpthread


all:$(OBJ)
	

$(OBJ): main.o thrpoolPriv.o
	$(CC) $^ -o $@ $(LDFLAGS) -g

clean:
	rm *.o
	rm ./$(OBJ)

