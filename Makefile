ifdef env
	ifeq ($(env), mac)
		LIBS := -lncurses
	else
		LIBS := -lncursesw
	endif
else
	LIBS := -lncursesw
endif

CC := gcc
SHELL := /bin/bash
OBJS := typing.o main.o logging.o display.o
PROGRAM := typing

${PROGRAM}: ${OBJS}
#	#${SHELL} -c 'if [ "$$(uname)" == "Darwin" ] ; then LIBS=-lncurses ; fi'
#	${SHELL} -c 'if [ "$$(uname)" == "Linux" ] ; then LIBS="-lncurses" ; fi'
#	${SHELL} -c 'echo ${LIBS}'
	${CC} -o ${PROGRAM} typing.o main.o logging.o display.o ${LIBS}
typing.o: typing.h display.h typing.c
	${CC} -c typing.c ${LIBS}
main.o: main.c
	${CC} -c main.c ${LIBS}
logging.o: logging.h logging.c
	${CC} -c logging.c ${LIBS}
display.o: display.c display.h
	${CC} -c display.c ${LIBS}
${OBJS}: typing.h
${OBJS}: logging.h
${OBJS}: display.h

clean:
	$(RM) *.o *~
	$(RM) ${PROGRAM}
