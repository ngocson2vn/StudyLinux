all: select.c
	@gcc -o select select.c
	@exec ./select

s2: FORCE
	@gcc -o s2 select2.c
	@./s2

FORCE:
