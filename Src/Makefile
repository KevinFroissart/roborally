CXX      = g++

.DEFAULT_GOAL := all

SOURCES = 
SOURCES += src/board.cpp src/sommet.cpp src/graphe.cpp

OBJECTS = $(foreach source, $(SOURCES), obj/$(patsubst src/%.cpp,%.o,$(source)))

CXXFLAGS += -g -Wall -pedantic
LDFLAGS +=

obj/%.o: src/%.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

CLEAN_OBJECTS = $(OBJECTS)
TARGETS = 

########## test_board ##########

TEST_BOARD_SOURCES = src/test_board.cpp
TEST_BOARD_OBJECTS = $(foreach source, $(TEST_BOARD_SOURCES), obj/$(patsubst src/%.cpp,%.o,$(source)))

bin/test_board : $(TEST_BOARD_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(TEST_BOARD_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(TEST_BOARD_OBJECTS): $(TEST_BOARD_SOURCES)
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

all : bin/test_board
TARGETS += bin/test_board
CLEAN_OBJECTS += $(TEST_BOARD_OBJECTS)

########## app ##########

APP_SOURCES = src/app.cpp
APP_OBJECTS = $(foreach source, $(APP_SOURCES), obj/$(patsubst src/%.cpp,%.o,$(source)))

bin/app : $(APP_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) -pthread $(APP_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(APP_OBJECTS): $(APP_SOURCES)
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

all : bin/app
TARGETS += bin/app
CLEAN_OBJECTS += $(APP_OBJECTS)

########## cleanup ##########
DEPS = $(CLEAN_OBJECTS:.o=.d)

clean:
	@rm -f $(DEPS) $(TARGETS) $(CLEAN_OBJECTS)

-include $(DEPS)
