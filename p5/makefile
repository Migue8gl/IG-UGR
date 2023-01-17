.PHONY: x clean tar

EJECUTABLE= practica_objetos_B5

MODULOS:= practica_objetos_B5.o\
         objetos_B5.o\
         file_ply_stl.o\
      
LIBS:= -lglut -lGLU -lGL -lsupc++ -lm -lc -lstdc++ -lpthread -L/usr/X11R6/lib/ -lX11 


CPPFLAGS:= -Wall -fmax-errors=2 -g

CC= g++

x: $(EJECUTABLE) 
	./$(EJECUTABLE) beethoven.ply

$(EJECUTABLE): $(MODULOS)
	$(CC) -o $(EJECUTABLE) $(LDFLAGS) $(MODULOS) $(LIBS)

objetos_B5.o : objetos_B5.cc CImg.h
	$(CC) -c objetos_B5.cc

clean:
	rm -rf *.o $(EJECUTABLE)

