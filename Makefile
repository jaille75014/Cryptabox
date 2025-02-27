CC = gcc
CFLAGS = -O2 -Wall -Wextra
CLIBS = -lm -lmysqlclient -lssl -lcrypto
EXE = bin/cryptabox
OBJ = obj/
SRC = src/
INCL = include/

FILEC := $(wildcard $(SRC)cli/*.c $(SRC)network/*.c $(SRC)security/*.c $(SRC)user_management/*.c $(SRC)main.c)
FILEH := $(wildcard $(SRC)cli/*.h $(SRC)network/*.h $(SRC)security/*.h $(SRC)user_management/*.h include/global.h)
FILEO := $(patsubst $(SRC)%.c,$(OBJ)%.o,$(FILEC))



$(OBJ):
	mkdir -p $(OBJ)cli $(OBJ)network $(OBJ)security $(OBJ)user_management

$(EXE) : $(FILEO)
	mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

$(OBJ)main.o : $(SRC)main.c $(FILEH)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)%.o : $(SRC)%.c $(FILEH)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

install: $(EXE)
	sudo mkdir -p $(DESTDIR)/usr/bin/
	sudo cp $(EXE) $(DESTDIR)/usr/bin/cryptabox
	sudo chmod +x $(DESTDIR)/usr/bin/cryptabox

clean:
	rm -rf $(OBJ)/*.o $(OBJ)cli/*.o $(OBJ)network/*.o $(OBJ)security/*.o $(OBJ)user_management/*.o
	rm -rf $(EXE)