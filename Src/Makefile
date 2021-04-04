CXX      = g++

.DEFAULT_GOAL := all

SRC = src/
OBJ = obj/
BIN = bin/

SOURCES = 
SOURCES += $(SRC)board.cpp $(SRC)sommet.cpp $(SRC)graphe.cpp $(SRC)joueurArtificiel.cpp

OBJECTS = $(foreach source, $(SOURCES), $(OBJ)$(patsubst $(SRC)%.cpp,%.o,$(source)))

CXXFLAGS += -g -Wall -pedantic
LDFLAGS +=

$(OBJ)%.o: $(SRC)%.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

CLEAN_OBJECTS = $(OBJECTS)
TARGETS = 

########## test_board ##########

TEST_BOARD_SOURCES = $(SRC)test_board.cpp
TEST_BOARD_OBJECTS = $(foreach source, $(TEST_BOARD_SOURCES), $(OBJ)$(patsubst $(SRC)%.cpp,%.o,$(source)))

$(BIN)test_board : $(TEST_BOARD_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(TEST_BOARD_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(TEST_BOARD_OBJECTS): $(TEST_BOARD_SOURCES)
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

all : $(BIN)test_board
TARGETS += $(BIN)test_board
CLEAN_OBJECTS += $(TEST_BOARD_OBJECTS)

########## app ##########

APP_SOURCES = $(SRC)app.cpp
APP_OBJECTS = $(foreach source, $(APP_SOURCES), $(OBJ)$(patsubst $(SRC)%.cpp,%.o,$(source)))

$(BIN)app : $(APP_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) -pthread $(APP_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(APP_OBJECTS): $(APP_SOURCES)
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

all : $(BIN)app
TARGETS += $(BIN)app
CLEAN_OBJECTS += $(APP_OBJECTS)

########## cleanup ##########
DEPS = $(CLEAN_OBJECTS:.o=.d)

clean:
	@rm -f $(DEPS) $(TARGETS) $(CLEAN_OBJECTS)

-include $(DEPS)
