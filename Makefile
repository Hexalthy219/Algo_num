### 
## Makefile
## INFO2050: Projet 2
## RANDAXHE Martin && RUSSE Cyril
## 
### 

## Variables

# Tools & flags
CC = gcc
CFLAGS = --std=c99 --pedantic -Wall -Wextra -Wmissing-prototypes -DNDEBUG 
LD = gcc
LDFLAGS =

# Files
EXEC = test

MODULES_MATRICECREUSE = main.c matriceCreuse.c
OBJECTS_MATRICECREUSE = main.o matriceCreuse.o



## Rules

#compilation

make: $(OBJECTS_MATRICECREUSE)
	$(LD) -o $(EXEC) $(OBJECTS_MATRICECREUSE) $(LDFLAGS) -lm


main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

matriceCreuse.o: matriceCreuse.c
	$(CC) -c matriceCreuse.c -o matriceCreuse.o $(CFLAGS)




#rapport
rapport:all_rapport clean_log_aux

all_rapport:
	cd ../rapport && pdflatex tad-RusseCyril.tex

clean_log_aux:
	cd ../rapport && rm -f tad-RusseCyril.aux tad-RusseCyril.log tad-RusseCyril.toc

clean_rapport: clean_log_aux
	cd ../rapport && rm -f tad-RusseCyril.pdf

#création archive
archive:
	cd .. && tar -zcvf demineur_01.tar.gz source rapport doc

#supp fichiers objets + executable
clean:
	rm -f *.o $(EXEC)