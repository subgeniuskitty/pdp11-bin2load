all:
	gcc -std=c99 -o bin2load bin2load.c

install: all
	mkdir -p /home/ataylor/bin/pdp/bin
	cp bin2load /home/ataylor/bin/pdp/bin/bin2load

uninstall:
	rm /home/ataylor/bin/pdp/bin/bin2load

clean:
	rm bin2load
