CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -fPIE -fPIC -ggdb -g3 -lportaudio

BIN := bin
SOURCE := source
INCLUDE := include

# UI
UIC := uic
UI_FORMS := ui_mainwindow.h

MOC := moc
MOCS := moc_mainwindow.cpp 
MOCS_OBJS := moc_mainwindow.o

BIN_MOCS_OBJS := $(patsubst %.o, $(BIN)/%.o, $(MOCS_OBJS))

UI_PATH := ui
# END UI


LIBS := -L/usr/lib/qt/QtWidgets -L/usr/lib/qt -lQt5Widgets -lQt5Test -lQt5Gui -lQt5Core
INCLUDE_PATHS := -I/usr/include/qt/QtWidgets -I/usr/include/qt -I/usr/include/qt/QtGui -I/usr/include/qt/QtCore -I$(INCLUDE) -I$(INCLUDE)/sound -I$(UI_PATH)/include

SRC := $(wildcard $(SOURCE)/*.cpp) $(wildcard $(SOURCE)/sound/*.cpp)  # FIND ALL FILES IN $(SOURCE) FOLDER THAT END WITH .cpp (example output: source/main.cpp source/car.cpp)
OBJ := $(patsubst $(SOURCE)%.cpp, $(BIN)%.o, $(SRC)) # REPLACE SOURCE PATH AND .cpp EXTENSION WITH BIN PATH .o EXTENSION (example output: bin/main.o bin/car.o)

NAME := main # NAME OF OUTPUT FILE

all: 
	#$(warning $(OBJ)) 
	$(warning $(BIN_MOCS_OBJS)) 
	make ui
	make main 

ui: $(UI_FORMS) $(MOCS) $(MOCS_OBJS)
	

run:
	./bin/main

$(NAME): $(OBJ)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $(OBJ) $(BIN_MOCS_OBJS) -o $(BIN)/$@ $(INCLUDE_PATHS) $(LIBS) -ldl



ui_%.h: $(SOURCE)/%.ui
	@mkdir -p $(UI_PATH)/include
	$(UIC) $< -o $(UI_PATH)/include/$@

moc_%.cpp: $(INCLUDE)/%.h
	@mkdir -p $(UI_PATH)/source 
	$(MOC) $< -o $(UI_PATH)/source/$@

moc_mainwindow.o: $(UI_PATH)/source/moc_mainwindow.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATHS) -c $< -o $(BIN)/$@



$(BIN)/%.o: $(SOURCE)/%.cpp
	@mkdir -p $(BIN)
	@mkdir -p $(BIN)/sound
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATHS) -c $< -o $@



clean:
	@rm -fr $(BIN)
	@rm -fr $(UI_PATH)

cleanbin:
	@rm -fr $(OBJ)
	@rm -fr $(BIN)/$(NAME)

cleanui:
	@rm -fr $(BIN)/$(MOCS_OBJS)
	@rm -fr $(UI_PATH)