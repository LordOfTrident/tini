CFLAGS = -pedantic -Wpedantic -Wshadow -Wvla -Wuninitialized -Wundef -Wno-deprecated-declarations \
         -Wall -Wextra -std=c99 -Werror -g -Og -fsanitize=address

example: example.c tini.h
	cc example.c -o example $(CFLAGS)

clean: example
	rm -f example
