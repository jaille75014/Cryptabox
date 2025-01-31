executable: main.o crypto.o
	gcc -o prog main.o crypto.o -lssl -lcrypto

main.o: main.c 
	gcc -c main.c

crypto.o: src/security/crypto.c 
	gcc -c src/security/crypto.c

clean:
	rm -rf *.o prog
