LINK_TARGET = ResourceMonitor
OBJS = main.c memory.c cpu.c
CFLAG = -Wall -g
CC = gcc
INCLUDE =
LIBS = -lncurses
REBUILDABLES = ${LINK_TARGET}

%.o:%.c
	${CC} ${CFLAGS} $@ -c $<

${LINK_TARGET}:${OBJ}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ ${OBJS} ${LIBS}

clean:
	rm -f ${REBUILDABLES}
	echo Clean done
