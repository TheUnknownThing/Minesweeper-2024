# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/Code/Projects/Minesweeper-2024

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/Code/Projects/Minesweeper-2024/build

# Include any dependencies generated for this target.
include src/CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/server.dir/flags.make

src/CMakeFiles/server.dir/basic.cpp.o: src/CMakeFiles/server.dir/flags.make
src/CMakeFiles/server.dir/basic.cpp.o: ../src/basic.cpp
src/CMakeFiles/server.dir/basic.cpp.o: src/CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Code/Projects/Minesweeper-2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/server.dir/basic.cpp.o"
	cd /root/Code/Projects/Minesweeper-2024/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/server.dir/basic.cpp.o -MF CMakeFiles/server.dir/basic.cpp.o.d -o CMakeFiles/server.dir/basic.cpp.o -c /root/Code/Projects/Minesweeper-2024/src/basic.cpp

src/CMakeFiles/server.dir/basic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/basic.cpp.i"
	cd /root/Code/Projects/Minesweeper-2024/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/Code/Projects/Minesweeper-2024/src/basic.cpp > CMakeFiles/server.dir/basic.cpp.i

src/CMakeFiles/server.dir/basic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/basic.cpp.s"
	cd /root/Code/Projects/Minesweeper-2024/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/Code/Projects/Minesweeper-2024/src/basic.cpp -o CMakeFiles/server.dir/basic.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/basic.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

src/server: src/CMakeFiles/server.dir/basic.cpp.o
src/server: src/CMakeFiles/server.dir/build.make
src/server: src/CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/Code/Projects/Minesweeper-2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable server"
	cd /root/Code/Projects/Minesweeper-2024/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/server.dir/build: src/server
.PHONY : src/CMakeFiles/server.dir/build

src/CMakeFiles/server.dir/clean:
	cd /root/Code/Projects/Minesweeper-2024/build/src && $(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/server.dir/clean

src/CMakeFiles/server.dir/depend:
	cd /root/Code/Projects/Minesweeper-2024/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/Code/Projects/Minesweeper-2024 /root/Code/Projects/Minesweeper-2024/src /root/Code/Projects/Minesweeper-2024/build /root/Code/Projects/Minesweeper-2024/build/src /root/Code/Projects/Minesweeper-2024/build/src/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/server.dir/depend

