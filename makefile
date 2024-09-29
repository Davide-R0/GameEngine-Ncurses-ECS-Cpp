#usefull make flags:
#- `-k` continue to compile even if it encounters error

#BUILD_DIR := ./build
#SRC_DIRS := ./src

CPP := g++
CPPFLAGS := -Wall -g 
LDFLAGS := -lncurses -ltinfo 
CXXFLAGS :=

EXEC := main 
BUILD_DIR := ./build
SRC_DIR := ./src

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)

#info: 
# Outputs the target name
#	echo $@
# Outputs all prerequisites
#	echo $^

# The final build step.
$(BUILD_DIR)/$(EXEC): $(OBJS)
	$(CPP) $(OBJS) -o $@ $(LDFLAGS)

.PHONY: build
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
#-include $(DEPS)





ifeq (0,1)
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

endif

