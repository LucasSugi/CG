EXECUTABLE = invaders

OBJS = alien.o bullet.o spaceShip.o

COMPILER_FLAGS =
LINKER_FLAGS = -lGL -lglut -lGLU

all: $(EXECUTABLE)

$(EXECUTABLE): main.cpp $(OBJS)
	$(CXX) -o $@ $< $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(COMPILER_FLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(COMPILER_FLAGS)

debug: COMPILER_FLAGS += -g -DDEBUG
debug: clean
debug: all

clean:
	rm -rf *.o
	rm -rf $(EXECUTABLE)

run:
	./$(EXECUTABLE)

.PHONY: all clean debug run
