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
RM = echo "hello"

.SECONDARY: $(OBJECTS)

.PHONY: all
all: lib/libdxl.a bin/dynamixel_test bin/dynamixel_test_id \
  bin/dimitri_print bin/dimitri_print_normalized \
  bin/dimitri_stance bin/dimitri_relax bin/dimitri_zero\
  bin/dimitri_off bin/dimitri_on \
  bin/dimitri_teach bin/dimitri_poses \
  bin/camera_test bin/dimitri_vision bin/dimitri_record
	@echo $(COLOR)All done! $(NOCOLOR)

COLOR = '\033[0;32m'
NOCOLOR='\033[0m'

lib/libdxl.a: obj/dxl_hal.o obj/dynamixel.o
	@echo -e -n $(COLOR)Linking with\ 
	@$(AR) rs $@ $^

bin/%: obj/%.o $(OBJECTS) lib/libdxl.a
	@echo -e $(COLOR)Linking $@ $(NOCOLOR)
	@$(CXX) $^ -o $@ $(LDFLAGS)

obj/%.o: src/%.cpp
	@echo -e $(COLOR)Compiling $@ $(NOCOLOR)
	@$(CXX) -c $< -o $@ $(CXXFLAGS)

obj/%.o: src/%.c
	@echo -e $(COLOR)Compiling $@ $(NOCOLOR)
	@$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean
clean:
	@echo -e $(COLOR)Cleaning all binaries $(NOCOLOR)
	@rm -f obj/*.o lib/*.a bin/*

