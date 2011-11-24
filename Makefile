CC 	= g++
CFLAGS	= -Wall
LD	= $(CC)
LDFLAGS =
RM	= rm

EXE 	= Tetris
SRCS 	= Pieces.cpp Board.cpp TetrisGame.cpp main.cpp
HEADERS = Pieces.h Board.h TetrisGame.h
OBJS	= ${SRCS:.c=.o}

.SUFFIXES: #clear them just in case
.SUFFIXES: .o .c

.c.o :
	$(CC) $(CFLAGS) -c $<

all : $(EXE)

$(EXE) : $(OBJS)
	$(LD) -o $@ $(OBJS)

$(OBJS) : $(HEADERS)

clean :
	-$(RM) $(EXE) $(OBJS)