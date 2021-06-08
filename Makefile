CC = g++
CFLAGS = -I. -I./headers -std=c++17 -lstdc++ -lstdc++fs
DEPS = Converters.hpp PsvParser.hpp Record.hpp RecordsManager.hpp
OBJ = src/Converters.o src/PsvParser.o src/Record.o src/RecordsManager.o src/main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
AudienceExercise: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	@rm -r -f $(OBJ)
