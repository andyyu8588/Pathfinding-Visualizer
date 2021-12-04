CC = g++
EXCLUDE_FILES = ../src/Display.cpp ../src/main.cpp ../src/Bidirectional.cpp ../src/Runner.cpp
WARNINGS_FLAGS = -Wall -Wextra

SRC_FILES = $(filter-out $(EXCLUDE_FILES), $(wildcard ../src/*.cpp ./*.cpp)) 

main:
	$(CC) -g -o test -fopenmp $(SRC_FILES) $(WARNINGS_FLAGS) 

clean:
	rm ./test