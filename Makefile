CC = gcc
CFLAGS = -O2 -Wall -Wextra -Werror
CLIBS = -lm
EXE = Cryptabox
OBJ = obj/
SRC = src/
INCL = include/

FILEC := $(wildcard $(SRC)cli/*.c $(SRC)network/*.c $(SRC)security/*.c $(SRC)user_management/*.c $(SRC)main.c)
FILEH := $(wildcard $(SRC)cli/*.h $(SRC)network/*.h $(SRC)security/*.h $(SRC)user_management/*.h $(SRC)global.h)
FILEO := $(patsubst $(SRC)%.c,$(OBJ)%.o,$(FILEC))



$(OBJ):
	mkdir -p $(OBJ)cli $(OBJ)network $(OBJ)security $(OBJ)user_management

$(EXE) : $(FILEO)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

$(OBJ)main.o : $(SRC)main.c $(FILEH)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)%.o : $(SRC)%.c $(FILEH)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -rf $(OBJ)*.o
	rm -rf $(EXE)