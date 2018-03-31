CC		:= g++
C_FLAGS := -std=c++17 -Wall -Wextra 
LDFLAGS :=

BIN		:= bin
SRC		:= src
INCLUDE	:= -I/usr/include/boost
LIB		:=  -lboost_regex  \
		    -lboost_filesystem \
			-lboost_system \
			-lboost_random \
			-lboost_date_time \
			-lboost_program_options
			
LIBRARIES	:= 


ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
else
EXECUTABLE	:= main
endif

all: $(BIN)/$(EXECUTABLE)

clean:
	$(RM) $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*
	$(CC) $(C_FLAGS) $^ -o $@ $(shell pkg-config --cflags --libs gtkmm-3.0)  $(LIB) $(INCLUDE)