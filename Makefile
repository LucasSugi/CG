EXECUTABLE = invaders

OBJS =

COMPILER_FLAGS =
LINKER_FLAGS = -lGL -lglut -lGLU

all: $(EXECUTABLE)

$(EXECUTABLE): main.c $(OBJS)
	$(CC) -o $@ main.c $(COMPILER_FLAGS) $(LINKER_FLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(COMPILER_FLAGS)

debug: COMPILER_FLAGS += -g -DDEBUG
debug: clean
debug: all

clean:
	rm -rf *.o
	rm -rf $(EXECUTABLE)

run:
	./$(EXECUTABLE)

.PHONY: all clean debug run
