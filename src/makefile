#usefull make flags:
#- `-k` continue to compile even if it encounters error

#BUILD_DIR := ./build
#SRC_DIRS := ./src

CPP = g++
CPPFLAGS = -Wall -g 
LDFLAGS = -lncurses -ltinfo 

info: 
	# Outputs the target name
	echo $@
	# Outputs all prerequisites
	echo $^

main: main.cpp app.o gameEng.o
	$(CPP) $(CPPFLAGS) $(LDFLAGS) main.cpp app.o gameEng.o -o $@  
	#$@= the name of the function

app.o: app.cpp
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -c app.cpp 

gameEng.o: gameEng.cpp
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -c gameEng.cpp

clean: 
	rm main *.o

rebuild: clean main


