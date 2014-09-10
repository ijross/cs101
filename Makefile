CC=gcc 
CFLAGSS =  -Wall 
DEPS = list.h hash.h hashlist.h bookcountlist.h 
OBJ = hash.o hashdr.o list.o hashlist.o bookcountlist.o 
OBJ2 = hash.o list.o hashlist.o bookcountlist.o store.o
OBJ3 = booklistdr.o bookcountlist.o

all: hashDriver store countlistdriver

clean :
	- rm ${OBJ} booklistdr.o store.o hashDriver store countlistdriver

%.o : %.c ${DEPS}
	$(CC) -c -o  $@ $< $(CFLAGS)

countlistdriver : ${OBJ3}
	gcc -o $@ $^ ${CFLAGS}

store : ${OBJ2}
	gcc -o $@ $^ ${CFLAGS}

hashDriver : ${OBJ}
	gcc -o $@ $^ ${CFLAGS}
