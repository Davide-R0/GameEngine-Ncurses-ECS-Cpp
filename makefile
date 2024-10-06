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
#	echo $(BUILD_DIR)/$(EXEC)

run: $(BUILD_DIR)/$(EXEC)
	${BUILD_DIR}/${EXEC}
#if the program exit with an error make will tell something like: "make: *** [makefile:--: run] Error 1"

# The final build step.
$(BUILD_DIR)/$(EXEC): $(OBJS)
	$(CPP) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -r $(BUILD_DIR)

rebuild: clean $(BUILD_DIR)/$(EXEC)


