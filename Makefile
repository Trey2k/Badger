CC = gcc
CFLAGS = -c -std=c99 -g
LDFLAGS = -g
SRC = ${wildcard src/*.c}
HDR = ${wildcard src/*.h}
OBJ = ${SRC:.c=.o}
EXEC = Badger.exe

all: ${SRC} ${OBJ} ${EXEC}

${EXEC}: ${OBJ}
	${CC} ${LDFLAGS} $^ -o $@

%.o: %.c ${HDR}
	${CC} ${CFLAGS} $< -o $@

clean:
	rm src/*.o ${EXEC}
