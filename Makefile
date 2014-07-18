all: select.c
	@gcc -o select select.c
	@exec ./select

s2: select2.c
	gcc -o s2 select2.c
	exec ./s2
