all: wuncur

wuncur: main.o controller.o api_handler.o json.o view.o
	gcc -g -lncurses -o wuncur main.o controller.o api_handler.o json.o view.o

main.o:
	gcc -g -c main.c

controller.o: controller.h
	gcc -g -DDEBUG -c controller.c

api_handler.o: api_handler.h
	gcc -g -c api_handler.c

view.o: view.h
	gcc -g -lncurses -c view.c

json.o: extlib/json.h
	gcc -g -c extlib/json.c

document:
	doxygen ../Doxyfile

clean:
	rm -f wuncur *.o
