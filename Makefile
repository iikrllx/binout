src/binout: src/binout.c
	gcc -Wall -Wextra src/binout.c -o src/binout -lm

install: src/binout
	install -D src/binout $(DESTDIR)/usr/bin/binout
