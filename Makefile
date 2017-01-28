# Find all the names of CPP files in the src directory.
CPP_FILES := $(wildcard src/*.cpp)

# Get the corresponding obj/FILE.o paths for the CPP files.
OBJ_FILES := $(addprefix obj/, $(notdir $(CPP_FILES:.cpp=.o)))

# The directories to search for includes from.
### Sometimes, header files are in other directories.
### This is where one might place those directory paths.
INCLUDEDIR = -Idep/googletest/googletest -Idep/googletest/googletest/include

# These are for including the libraries you want to use.
### Ignore these for now; we have not covered libraries yet.
LIBSDIR = -Ldep/googletest/build/googlemock/gtest
LIBS = -lgtest

# Flags for the linker step.
LD_FLAGS  := $(INCLUDEDIR) $(LIBSDIR) $(LIBS)

# Flags for the C++ compilation step.
CXX_FLAGS := -Wall -Wextra -pedantic --std=c++11 -g \
			 $(INCLUDEDIR) $(LIBSDIR) $(LIBS) 

# The default rule to be build when just `make` is run.
all: bin/main

# Build the main executable and place inside the (bin)ary directory..
bin/main: $(OBJ_FILES)
	g++ -o $@ $^ $(CXX_FLAGS)

# A rule to build all the object files from the source files.
obj/%.o: src/%.cpp
	g++ $(CXX_FLAGS) -c -o $@ $<

# A POSIX-compliant clean command
clean: 
	rm obj/*.o
	rm bin/main

clean-all: clean
	rm -rf docs/*

run:
	cd bin; ./main; cd ../

docs:
	cd docs; doxygen ../doxygen_config_file; cd ../
