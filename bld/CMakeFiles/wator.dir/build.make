# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_SOURCE_DIR = /home/kitty/git/wator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kitty/git/wator/bld

# Include any dependencies generated for this target.
include CMakeFiles/wator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wator.dir/flags.make

CMakeFiles/wator.dir/src/draw.c.o: CMakeFiles/wator.dir/flags.make
CMakeFiles/wator.dir/src/draw.c.o: ../src/draw.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kitty/git/wator/bld/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/wator.dir/src/draw.c.o"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wator.dir/src/draw.c.o   -c /home/kitty/git/wator/src/draw.c

CMakeFiles/wator.dir/src/draw.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wator.dir/src/draw.c.i"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kitty/git/wator/src/draw.c > CMakeFiles/wator.dir/src/draw.c.i

CMakeFiles/wator.dir/src/draw.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wator.dir/src/draw.c.s"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kitty/git/wator/src/draw.c -o CMakeFiles/wator.dir/src/draw.c.s

CMakeFiles/wator.dir/src/game.c.o: CMakeFiles/wator.dir/flags.make
CMakeFiles/wator.dir/src/game.c.o: ../src/game.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kitty/git/wator/bld/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/wator.dir/src/game.c.o"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wator.dir/src/game.c.o   -c /home/kitty/git/wator/src/game.c

CMakeFiles/wator.dir/src/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wator.dir/src/game.c.i"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kitty/git/wator/src/game.c > CMakeFiles/wator.dir/src/game.c.i

CMakeFiles/wator.dir/src/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wator.dir/src/game.c.s"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kitty/git/wator/src/game.c -o CMakeFiles/wator.dir/src/game.c.s

CMakeFiles/wator.dir/src/main.c.o: CMakeFiles/wator.dir/flags.make
CMakeFiles/wator.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kitty/git/wator/bld/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/wator.dir/src/main.c.o"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wator.dir/src/main.c.o   -c /home/kitty/git/wator/src/main.c

CMakeFiles/wator.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wator.dir/src/main.c.i"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kitty/git/wator/src/main.c > CMakeFiles/wator.dir/src/main.c.i

CMakeFiles/wator.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wator.dir/src/main.c.s"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kitty/git/wator/src/main.c -o CMakeFiles/wator.dir/src/main.c.s

CMakeFiles/wator.dir/src/ptrmap.c.o: CMakeFiles/wator.dir/flags.make
CMakeFiles/wator.dir/src/ptrmap.c.o: ../src/ptrmap.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kitty/git/wator/bld/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/wator.dir/src/ptrmap.c.o"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wator.dir/src/ptrmap.c.o   -c /home/kitty/git/wator/src/ptrmap.c

CMakeFiles/wator.dir/src/ptrmap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wator.dir/src/ptrmap.c.i"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kitty/git/wator/src/ptrmap.c > CMakeFiles/wator.dir/src/ptrmap.c.i

CMakeFiles/wator.dir/src/ptrmap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wator.dir/src/ptrmap.c.s"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kitty/git/wator/src/ptrmap.c -o CMakeFiles/wator.dir/src/ptrmap.c.s

CMakeFiles/wator.dir/src/simulation.c.o: CMakeFiles/wator.dir/flags.make
CMakeFiles/wator.dir/src/simulation.c.o: ../src/simulation.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kitty/git/wator/bld/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/wator.dir/src/simulation.c.o"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wator.dir/src/simulation.c.o   -c /home/kitty/git/wator/src/simulation.c

CMakeFiles/wator.dir/src/simulation.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wator.dir/src/simulation.c.i"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kitty/git/wator/src/simulation.c > CMakeFiles/wator.dir/src/simulation.c.i

CMakeFiles/wator.dir/src/simulation.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wator.dir/src/simulation.c.s"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kitty/git/wator/src/simulation.c -o CMakeFiles/wator.dir/src/simulation.c.s

# Object files for target wator
wator_OBJECTS = \
"CMakeFiles/wator.dir/src/draw.c.o" \
"CMakeFiles/wator.dir/src/game.c.o" \
"CMakeFiles/wator.dir/src/main.c.o" \
"CMakeFiles/wator.dir/src/ptrmap.c.o" \
"CMakeFiles/wator.dir/src/simulation.c.o"

# External object files for target wator
wator_EXTERNAL_OBJECTS =

wator: CMakeFiles/wator.dir/src/draw.c.o
wator: CMakeFiles/wator.dir/src/game.c.o
wator: CMakeFiles/wator.dir/src/main.c.o
wator: CMakeFiles/wator.dir/src/ptrmap.c.o
wator: CMakeFiles/wator.dir/src/simulation.c.o
wator: CMakeFiles/wator.dir/build.make
wator: /usr/lib/libSDL2main.a
wator: /usr/lib/libSDL2.so
wator: /usr/lib/libSDL2_image.so
wator: btt/libbtt.a
wator: CMakeFiles/wator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kitty/git/wator/bld/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable wator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wator.dir/build: wator

.PHONY : CMakeFiles/wator.dir/build

CMakeFiles/wator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wator.dir/clean

CMakeFiles/wator.dir/depend:
	cd /home/kitty/git/wator/bld && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kitty/git/wator /home/kitty/git/wator /home/kitty/git/wator/bld /home/kitty/git/wator/bld /home/kitty/git/wator/bld/CMakeFiles/wator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/wator.dir/depend
