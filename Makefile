CC = gcc
CXX = g++
CFLAGS = -I./include -I/usr/include -Wall -O2
CXXFLAGS = -I./include -I/usr/include -I/usr/include/opencv `pkg-config --cflags opencv` -Wall -O2
LDFLAGS = -L./lib -lm -ldxl `pkg-config --libs opencv`
AR = ar
OBJECTS = obj/Dimitri.o obj/Joint.o obj/ElasticJoint.o \
	  obj/JointChain.o obj/Util.o obj/PidController.o \
	  obj/dynamixel.o obj/dxl_hal.o obj/Object.o \
	  obj/Camera.o

all: lib/libdxl.a bin/dynamixel_test bin/dynamixel_test_id \
  bin/dimitri_print bin/dimitri_print_normalized \
  bin/dimitri_stance bin/dimitri_relax \
  bin/dimitri_off bin/dimitri_on \
  bin/dimitri_zero bin/dimitri_teach bin/dimitri_poses \
  bin/camera_test bin/dimitri_vision
	@echo $(COLOR)All done! $(NOCOLOR)

COLOR = '\033[0;32m'
NOCOLOR='\033[0m'

lib/libdxl.a: obj/dxl_hal.o obj/dynamixel.o
	@echo -e -n $(COLOR)Linking with\ 
	@$(AR) rs $@ $^

bin/dynamixel_test: obj/dynamixel_test.o lib/libdxl.a
	@echo -e $(COLOR)Linking $@ $(NOCOLOR)
	@$(CXX) $< -o $@ $(LDFLAGS)

bin/dynamixel_test_id: obj/dynamixel_test_id.o lib/libdxl.a
	@echo -e $(COLOR)Linking $@ $(NOCOLOR)
	@$(CXX) $< -o $@ $(LDFLAGS)

bin/dimitri_print: obj/dimitri_print.o $(OBJECTS) lib/libdxl.a
	@echo -e $(COLOR)Linking $@ $(NOCOLOR)
	@$(CXX) $^ -o $@ $(LDFLAGS)

bin/dimitri_print_normalized: obj/dimitri_print_normalized.o $(OBJECTS) lib/libdxl.a
	@echo -e $(COLOR)Linking $@ $(NOCOLOR)
	@$(CXX) $^ -o $@ $(LDFLAGS)

bin/dimitri_off: obj/dimitri_off.o $(OBJECTS) lib/libdxl.a
	@echo -e $(COLOR)Linking $@ $(NOCOLOR)
	@$(CXX) $^ -o $@ $(LDFLAGS)

bin/dimitri_on: obj/dimitri_on.o $(OBJECTS) lib/libdxl.a
	@echo -e $(COLOR)Linking $@ $(NOCOLOR)
	@$(CXX) $^ -o $@ $(LDFLAGS)

bin/dimitri_stance: obj/dimitri_stance.o $(OBJECTS) lib/libdxl.a
	@echo -e $(COLOR)Linking $@ $(NOCOLOR)
	@$(CXX) $^ -o $@ $(LDFLAGS)

bin/dimitri_relax: obj/dimitri_relax.o $(OBJECTS) lib/libdxl.a
	@echo -e $(COLOR)Linking $@ $(NOCOLOR)
	@$(CXX) $^ -o $@ $(LDFLAGS)

bin/dimitri_zero: obj/dimitri_zero.o $(OBJECTS) lib/libdxl.a
	@echo -e $(COLOR)Linking $@ $(NOCOLOR)
	@$(CXX) $^ -o $@ $(LDFLAGS)

bin/dimitri_teach: obj/dimitri_teach.o $(OBJECTS) lib/libdxl.a
	@echo -e $(COLOR)Linking $@ $(NOCOLOR)
	@$(CXX) $^ -o $@ $(LDFLAGS)

bin/dimitri_poses: obj/dimitri_poses.o $(OBJECTS) lib/libdxl.a
	@echo -e $(COLOR)Linking $@ $(NOCOLOR)
	@$(CXX) $^ -o $@ $(LDFLAGS)

bin/camera_test: obj/camera_test.o $(OBJECTS) lib/libdxl.a
	@echo -e $(COLOR)Linking $@ $(NOCOLOR)
	@$(CXX) $^ -o $@ $(LDFLAGS)

bin/dimitri_vision: obj/dimitri_vision.o $(OBJECTS) lib/libdxl.a
	@echo -e $(COLOR)Linking $@ $(NOCOLOR)
	@$(CXX) $^ -o $@ $(LDFLAGS)

obj/%.o: src/%.cpp
	@echo -e $(COLOR)Compiling $@ $(NOCOLOR)
	@$(CXX) -c $< -o $@ $(CXXFLAGS)

obj/%.o: src/%.c
	@echo -e $(COLOR)Compiling $@ $(NOCOLOR)
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@echo -e $(COLOR)Cleaning all binaries $(NOCOLOR)
	@rm -f obj/*.o lib/*.a bin/*

