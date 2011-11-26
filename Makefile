CC 	= g++
CFLAGS	= -Wall
LD	= $(CC)
LDFLAGS =
RM	= rm

EXE 	= Tetris
SRCS 	= Piece.cpp Board.cpp TetrisGame.cpp main.cpp
OBJS	= ${SRCS:.cpp=.o}

WXFLAGS = `wx-config --cppflags`
WXLINK 	= `wx-config --libs`

.SUFFIXES: #clear them just in case
.SUFFIXES: .o .cpp

all : $(EXE)

depend : .depend

.depend : $(SRCS)
	$(CC) $(CFLAGS) -MM $^ > .depend

include .depend

.cpp.o :
	$(CC) $(WXFLAGS) $(CFLAGS) -c $<

$(EXE) : $(OBJS)
	$(LD) $(WXLINK) -o $@ $(OBJS)

.PHONY : clean
clean :
	-$(RM) $(EXE) $(OBJS)