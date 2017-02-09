CXX := c++

# Find all the names of CPP files in the src directory.
CPP_FILES := $(wildcard src/*.cpp)
H_FILES := $(wildcard src/*.h)

TEST_FILES := $(wildcard tests/*.cpp)
TEST_EXECUTABLES := $(TEST_FILES:.cpp=.out)

# Get the corresponding obj/FILE.o paths for the CPP files.
OBJ_FILES := $(addprefix obj/, $(notdir $(CPP_FILES:.cpp=.o)))

# The directories to search for includes from.
### Sometimes, header files are in other directories.
### This is where one might place those directory paths.
TESTINCLUDEDIR = -Idep/googletest/googletest -Idep/googletest/googletest/include
INCLUDEDIR = -Isrc/

# These are for including the libraries you want to use.
### Ignore these for now; we have not covered libraries yet.
LIBSDIR = 
LIBS = 
TESTLIBSDIR = -Ldep/googletest/build/googlemock/gtest
TESTLIBS = -lgtest -lpthread

# Flags for the linker step.
LD_FLAGS  := $(INCLUDEDIR) $(LIBSDIR) $(LIBS)

# Flags for the C++ compilation step.
CXX_FLAGS := -Wall -Wextra -pedantic --std=c++11 -g \
			 $(INCLUDEDIR) $(LIBSDIR) $(LIBS) 

TEST_FLAGS := -Wall -Wextra -pedantic --std=c++11 -g \
			  $(INCLUDEDIR) $(TESTINCLUDEDIR) \
			  $(LIBSDIR) $(TESTLIBSDIR) \
			  $(LIBS) $(TESTLIBS)

# The default rule to be build when just `make` is run.
all: bin/main

# Build the main executable and place inside the (bin)ary directory..
bin/main: $(OBJ_FILES)
	$(CXX) -o $@ $^ $(CXX_FLAGS)

# A rule to build all the object files from the source files.
obj/%.o: src/%.cpp
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

# A POSIX-compliant clean command
clean: 
	rm obj/*.o
	rm bin/main

clean-all: clean clean-tests clean-docs clean-tests-docs

clean-docs:
	rm -rf docs/*

clean-tests-docs:
	rm -rf tests-docs/*

clean-tests:
	rm -rf tests/*.out

run:
	cd bin; ./main; cd ../

docs: $(CPP_FILES)
	cd docs; doxygen ../doxygen_config_file; cd ../

tests: $(TEST_EXECUTABLES)

tests/%.out: tests/%.cpp
	$(CXX) -o $@ $^ $(TEST_FLAGS)
