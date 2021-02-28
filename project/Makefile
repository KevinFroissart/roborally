.DEFAULT_GOAL := all

CXX       = g++
CXXFLAGS += -g -Wall -pedantic
LDFLAGS  +=

TARGET = bin/
CPATH  = src/
HPATH  = header/

HEADERS     = $(wildcard $(HPATH)*.hpp)
ALL_SOURCES = $(wildcard $(CPATH)*.cpp)

FILE    += board.cpp
SOURCES += $(CPATH)$(FILE)
OBJECTS  = $(foreach source, $(SOURCES), obj/$(patsubst src/%.cpp,%.o,$(source)))

board : $(OBJECTS) $(HEADERS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

CLEAN_OBJECTS = $(OBJECTS)
TARGETS       = 

########## test_board ##########

TEST_BOARD_FILE    += test_board.cpp
TEST_BOARD_SOURCES += $(CPATH)$(TEST_BOARD_FILE)
TEST_BOARD_OBJECTS  = $(foreach source, $(TEST_BOARD_SOURCES), obj/$(patsubst src/%.cpp,%.o,$(source)))

bin/test_board : $(TEST_BOARD_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(TEST_BOARD_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)


all            : $(TARGET)test_board
TARGETS       += $(TARGET)test_board
CLEAN_OBJECTS += $(TEST_BOARD_OBJECTS)

########## app ##########

APP_FILE    += app.cpp
APP_SOURCES += $(CPATH)$(APP_FILE)
APP_OBJECTS  = $(foreach source, $(APP_SOURCES), obj/$(patsubst src/%.cpp,%.o,$(source)))

bin/app : $(APP_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) -pthread $(APP_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)

all            : $(TARGET)app
TARGETS       += $(TARGET)app
CLEAN_OBJECTS += $(APP_OBJECTS)

########## run ##########

run : all
	./$(TARGET)app board.txt

########## cleanup ##########

clean:
	@rm -f $(TARGETS) $(CLEAN_OBJECTS)
	@rm -f obj/*.d
	@rm makefile.dep

makefile.dep: $(ALL_SOURCES) $(HEADERS)
	@echo "Calculating dependencies..."
	@$(RM) makefile.dep
	@for file in $(ALL_SOURCES); do echo "obj/`g++ $(CXXFLAGS) -MM $$file`" >> makefile.dep; done

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

include makefile.dep