CC = gcc
CXX = g++
CFLAGS = -I./include -Wall -O2
CXXFLAGS = -I./include -Wall -O2
LDFLAGS = -L./lib -lm -ldxl
AR = ar
OBJECTS = obj/Dimitri.o obj/Joint.o obj/ElasticJoint.o obj/JointChain.o obj/PidController.o obj/dynamixel.o obj/dxl_hal.o

all: lib/libdxl.a bin/dynamixel_test bin/dimitri_print bin/dimitri_stance bin/dimitri_off bin/dimitri_on

lib/libdxl.a: obj/dxl_hal.o obj/dynamixel.o
	$(AR) rs $@ $^

bin/dynamixel_test: obj/dynamixel_test.o lib/libdxl.a
	$(CXX) $< -o $@ $(LDFLAGS)

bin/dimitri_print: obj/dimitri_print.o $(OBJECTS) lib/libdxl.a
	$(CXX) $^ -o $@ $(LDFLAGS)

bin/dimitri_off: obj/dimitri_off.o $(OBJECTS) lib/libdxl.a
	$(CXX) $^ -o $@ $(LDFLAGS)

bin/dimitri_on: obj/dimitri_on.o $(OBJECTS) lib/libdxl.a
	$(CXX) $^ -o $@ $(LDFLAGS)

bin/dimitri_stance: obj/dimitri_stance.o $(OBJECTS) lib/libdxl.a
	$(CXX) $^ -o $@ $(LDFLAGS)

obj/%.o: src/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f obj/*.o lib/*.a bin/*

