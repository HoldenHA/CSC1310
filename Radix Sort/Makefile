AutomatedMakefile = am
CC = g++
CXXFLAGS = -Wno-deprecated-declarations -g -O0

PROJECT_PATH = $(CURRENT_DIR)
GUI_PATH = $(DRIVE_LETTER)/TDM-GCC-64/wxWidgets-3.1.0

INC_DIRS = -I./1310/CSC1310 -I./1310/GUI -I$(GUI_PATH)/include -I$(GUI_PATH)/lib/gcc510TDM_x64_dll/mswu
LIB_DIRS = -L./1310/CSC1310 -L./1310/GUI -L$(GUI_PATH)/lib/gcc510TDM_x64_dll
LDFLAGS = -Wl,-Bstatic
LIBS = $(LDFLAGS) -lCSC1310 -lrandom -lGUI -lwxmsw31u_core -lwxbase31u -lgdi32

COMPILE = $(CC) $(CXXFLAGS) $(INC_DIRS) -c
LINK = $(CC) $(CXXFLAGS) $(LIB_DIRS)

FILES = RadixSortDriver.o
EXECUTABLE = Radix.exe

all: Project

Project: $(FILES)
	 $(LINK) $(FILES) $(LIBS) -o $(EXECUTABLE)

RadixSortDriver.o: RadixSortDriver.cpp RadixSort.h
	$(COMPILE) RadixSortDriver.cpp
