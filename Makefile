executable: main.o encrypt.o decrypt.o
	gcc -o prog main.o encrypt.o decrypt.o -lssl -lcrypto

main.o: main.c 
	gcc -c main.c

encrypt.o: src/security/encrypt.c 
	gcc -c src/security/encrypt.c

decrypt.o: src/security/decrypt.c 
	gcc -c src/security/decrypt.c


clean:
	rm -rf *.o prog
