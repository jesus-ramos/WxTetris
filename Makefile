CC 	= g++
CFLAGS	= -Wall
LD	= $(CC)
LDFLAGS =
RM	= rm

EXE 	= Tetris
SRCS 	= Piece.cpp Board.cpp TetrisGame.cpp main.cpp
HEADERS = Piece.h Board.h TetrisGame.h
OBJS	= ${SRCS:.cpp=.o}

.SUFFIXES: #clear them just in case
.SUFFIXES: .o .cpp

.cpp.o :
	$(CC) $(CFLAGS) -c $<

all : $(EXE)

$(EXE) : $(OBJS) $(HEADERS)
	$(LD) -o $@ $(OBJS)

clean :
	-$(RM) $(EXE) $(OBJS)