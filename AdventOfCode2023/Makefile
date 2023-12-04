ifeq ($(OS),Windows_NT)
	EXEC = exe
else
	EXEC = bin
endif

ifeq ($(RELEASE),TRUE)
	CFLAGS = -O2 -DNDEBUG
else
	CFLAGS = -g -Wall
endif

CC = gcc
EXT = c
IFLAGS = -Iinclude
SRC = src
OBJ = obj
DATA = data
BINDIR = bin
PROJNAME = AoC23
BINNAME = $(PROJNAME).$(EXEC)
CONTAINER = $(OBJ)/container.o
BIN = $(BINDIR)/$(BINNAME)
NUM = n

$(NUM)%: $(OBJ)/challenge_%.o $(CONTAINER)
	$(CC) $(CFLAGS) $(IFLAGS) $^ -o $(BIN)
	$(BIN) $(DATA)/$@.txt

$(OBJ)/%.o: $(SRC)/%.$(EXT) $(BINDIR)
	$(CC) -c $(CFLAGS) $(IFLAGS) $< -o $@

$(BINDIR):
	@mkdir -p $(BINDIR) $(OBJ)

clean:
	rm -r $(BINDIR) $(OBJ)