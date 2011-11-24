CC 	= g++
CFLAGS	= -Wall
LD	= $(CC)
LDFLAGS =
RM	= rm

EXE 	= Tetris
SRCS 	= Piece.cpp Board.cpp TetrisGame.cpp main.cpp
HEADERS = Piece.hpp Board.hpp TetrisGame.hpp
OBJS	= ${SRCS:.cpp=.o}

WXFLAGS = `wx-config --cppflags`
WXLINK 	= `wx-config --libs`

.SUFFIXES: #clear them just in case
.SUFFIXES: .o .cpp

.cpp.o :
	$(CC) $(WXFLAGS) $(CFLAGS) -c $<

all : $(HEADERS) $(EXE)

$(EXE) : $(OBJS)
	$(LD) $(WXLINK) -o $@ $(OBJS)

clean :
	-$(RM) $(EXE) $(OBJS)