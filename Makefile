octdump: octdump.o
	gcc -s -o octdump octdump.o

octdump.o: octdump.c
	gcc -O2 -c octdump.c

install:
	sudo cp octdump /usr/local/bin/octdump
	sudo chown root:root /usr/local/bin/octdump

clean:
	rm *.o && rm octdump
