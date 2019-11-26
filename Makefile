OBJ=main

sources = *.c
CC=gcc

LDFLAGS+=-lpthread


all: $(OBJ)
$(OBJ): main.o thrpoolPriv.o
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm *.o
	rm ./$(OBJ)
	rm *.d




include $(sources:.c=.d)
%.d:%.c
	set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
	rm *.d
