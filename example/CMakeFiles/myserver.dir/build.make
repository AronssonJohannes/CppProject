# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/johan/git/CppProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/johan/git/CppProject

# Include any dependencies generated for this target.
include example/CMakeFiles/myserver.dir/depend.make

# Include the progress variables for this target.
include example/CMakeFiles/myserver.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/myserver.dir/flags.make

example/CMakeFiles/myserver.dir/myserver.cc.o: example/CMakeFiles/myserver.dir/flags.make
example/CMakeFiles/myserver.dir/myserver.cc.o: example/myserver.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/johan/git/CppProject/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/myserver.dir/myserver.cc.o"
	cd /mnt/c/Users/johan/git/CppProject/example && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myserver.dir/myserver.cc.o -c /mnt/c/Users/johan/git/CppProject/example/myserver.cc

example/CMakeFiles/myserver.dir/myserver.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myserver.dir/myserver.cc.i"
	cd /mnt/c/Users/johan/git/CppProject/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/johan/git/CppProject/example/myserver.cc > CMakeFiles/myserver.dir/myserver.cc.i

example/CMakeFiles/myserver.dir/myserver.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myserver.dir/myserver.cc.s"
	cd /mnt/c/Users/johan/git/CppProject/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/johan/git/CppProject/example/myserver.cc -o CMakeFiles/myserver.dir/myserver.cc.s

# Object files for target myserver
myserver_OBJECTS = \
"CMakeFiles/myserver.dir/myserver.cc.o"

# External object files for target myserver
myserver_EXTERNAL_OBJECTS =

example/myserver: example/CMakeFiles/myserver.dir/myserver.cc.o
example/myserver: example/CMakeFiles/myserver.dir/build.make
example/myserver: libclientserver.a
example/myserver: example/CMakeFiles/myserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/johan/git/CppProject/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable myserver"
	cd /mnt/c/Users/johan/git/CppProject/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/myserver.dir/build: example/myserver

.PHONY : example/CMakeFiles/myserver.dir/build

example/CMakeFiles/myserver.dir/clean:
	cd /mnt/c/Users/johan/git/CppProject/example && $(CMAKE_COMMAND) -P CMakeFiles/myserver.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/myserver.dir/clean

example/CMakeFiles/myserver.dir/depend:
	cd /mnt/c/Users/johan/git/CppProject && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/johan/git/CppProject /mnt/c/Users/johan/git/CppProject/example /mnt/c/Users/johan/git/CppProject /mnt/c/Users/johan/git/CppProject/example /mnt/c/Users/johan/git/CppProject/example/CMakeFiles/myserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/myserver.dir/depend

