CC = g++
CFLAGS = -I. -I./headers -std=c++17 -lstdc++ -lstdc++fs
DEPS = Converters.hpp PsvParser.hpp Record.hpp RecordsManager.hpp
OBJ = src/Converters.o src/PsvParser.o src/Record.o src/RecordsManager.o
COMPILEAPP = $(OBJ) src/main.o
TESTOBJ = test/MainTest.o test/Converters_Test.o test/Record_Test.o test/PsvParser_Test.o test/RecordsManager_Test.o
COMPILETEST = $(TESTOBJ) $(OBJ)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: build/AudienceExerciseTest build/AudienceExercise

build/AudienceExerciseTest: $(COMPILETEST)
	$(CC) -o $@ $^ $(CFLAGS) /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a -lpthread
	
build/AudienceExercise: $(COMPILEAPP)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	@rm -r -f $(COMPILETEST)
	@rm -r -f $(COMPILEAPP)
	@rm -r -f build/AudienceExerciseTest build/AudienceExercise
