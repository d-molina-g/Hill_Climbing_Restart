EXE = main
CFLAGS = -Wall -O2 -std=c++11 -g
C = g++
OBJ = obj/main.o obj/Functions.o obj/Class.o obj/Read_write.o obj/HcRestart_MM.o

$(EXE): $(OBJ)
	$(C) $(CFLAGS) -o $@ $^

obj/main.o: main.cpp
	$(C) -c -o obj/main.o main.cpp

obj/Functions.o: src/Functions.cpp header/Functions.h
	$(C) -c -o obj/Functions.o src/Functions.cpp

obj/Class.o: src/Class.cpp header/Class.h
	$(C) -c -o obj/Class.o src/Class.cpp

obj/Read_write.o: src/Read_write.cpp header/Read_write.h
	$(C) -c -o obj/Read_write.o src/Read_write.cpp

obj/HcRestart_MM.o: src/HcRestart_MM.cpp header/HcRestart_MM.h 
	$(C) -c -o obj/HcRestart_MM.o src/HcRestart_MM.cpp

clean:
	rm -fr $(EXE)
	rm -fr obj/*
	rm -fr Salida/*

run:
	./$(EXE) a36.mcwb 5