#ifndef ROOTSYS
#	$(error *** Please set up Root)
#endif

NAME     := Train
INC_DIR  := include
SRC_DIR  := src
OBJ_DIR  := obj

# create obj directory if one does not exist
$(shell mkdir -p obj)

#SRCS := $(SRC_DIR)/*.cxx
#OBJS := $(SRCS:.cxx=.o)
SRC_FILES := $(wildcard $(SRC_DIR)/*.cxx)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cxx,$(OBJ_DIR)/%.o,$(SRC_FILES))

$(info OBJ_FILES is $(OBJ_FILES))

# compilers
CXX := g++
#CXXFLAGS := -O -Wall -fPIC -g -ansi -Wshadow -Wextra $(shell root-config --cflags)
LDFLAGS  := $(shell root-config --cflags)
LDLIBS   := $(shell root-config --libs)
CXXFLAGS :=  -c -o $(shell root-config --cflags) -std=c++11
CPPFLAGS := -I. -I$(INC_DIR)

# do stuff
train: $(OBJ_FILES)
	g++ $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cxx
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
#	g++ $(CPPFLAGS) $(CXXFLAGS) $@ $<

clean: 
	rm train obj/*