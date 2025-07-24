# Makefile for the project
# This Makefile compiles C source files into object files and links them into an executable
# It is a recursive tree structure with source files in src/, object files in obj/, and the final executable in bin/
# $() is used to reference variables
TARGET = bin/final.out						# Name of the final executable
SRC = $(wildcard src/*.c)					# wildcard is used to get all .c files in src/
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))	# patsubst (Pattern Substitution) is used to replace the src/ prefix with obj/ for object files

$(shell mkdir -p obj bin) 					# Create obj and bin directories if they do not exist

# Makefile for building the project
# 1st rule is the default target
default: $(TARGET)

# 2nd rule is for building the final executable
# $? is used to get all prerequisites that are newer than the target
$(TARGET): $(OBJ)
	gcc -o $@ $?

# 3rd rule is for compiling source files to object files
# $< is the first prerequisite (the source file), $@ is the target (the object file)
# -Iinclude is used to include header files from the include directory
obj/%.o : src/%.c
	gcc -c $< -o $@ -Iinclude

# 4th rule is for cleaning up the build
clean:
	rm -f obj/*.o
	rm -f bin/*
