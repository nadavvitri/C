# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = "/cygdrive/c/Users/nadav vitri/.CLion2017.2/system/cygwin_cmake/bin/cmake.exe"

# The command to remove a file.
RM = "/cygdrive/c/Users/nadav vitri/.CLion2017.2/system/cygwin_cmake/bin/cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/c/Users/nadav vitri/CLionProjects/ex2.2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/c/Users/nadav vitri/CLionProjects/ex2.2/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/ex2_2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ex2_2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex2_2.dir/flags.make

CMakeFiles/ex2_2.dir/LineSeparator.c.o: CMakeFiles/ex2_2.dir/flags.make
CMakeFiles/ex2_2.dir/LineSeparator.c.o: ../LineSeparator.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/nadav vitri/CLionProjects/ex2.2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ex2_2.dir/LineSeparator.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ex2_2.dir/LineSeparator.c.o   -c "/cygdrive/c/Users/nadav vitri/CLionProjects/ex2.2/LineSeparator.c"

CMakeFiles/ex2_2.dir/LineSeparator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex2_2.dir/LineSeparator.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/c/Users/nadav vitri/CLionProjects/ex2.2/LineSeparator.c" > CMakeFiles/ex2_2.dir/LineSeparator.c.i

CMakeFiles/ex2_2.dir/LineSeparator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex2_2.dir/LineSeparator.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/c/Users/nadav vitri/CLionProjects/ex2.2/LineSeparator.c" -o CMakeFiles/ex2_2.dir/LineSeparator.c.s

CMakeFiles/ex2_2.dir/LineSeparator.c.o.requires:

.PHONY : CMakeFiles/ex2_2.dir/LineSeparator.c.o.requires

CMakeFiles/ex2_2.dir/LineSeparator.c.o.provides: CMakeFiles/ex2_2.dir/LineSeparator.c.o.requires
	$(MAKE) -f CMakeFiles/ex2_2.dir/build.make CMakeFiles/ex2_2.dir/LineSeparator.c.o.provides.build
.PHONY : CMakeFiles/ex2_2.dir/LineSeparator.c.o.provides

CMakeFiles/ex2_2.dir/LineSeparator.c.o.provides.build: CMakeFiles/ex2_2.dir/LineSeparator.c.o


# Object files for target ex2_2
ex2_2_OBJECTS = \
"CMakeFiles/ex2_2.dir/LineSeparator.c.o"

# External object files for target ex2_2
ex2_2_EXTERNAL_OBJECTS =

ex2_2.exe: CMakeFiles/ex2_2.dir/LineSeparator.c.o
ex2_2.exe: CMakeFiles/ex2_2.dir/build.make
ex2_2.exe: CMakeFiles/ex2_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/c/Users/nadav vitri/CLionProjects/ex2.2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ex2_2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex2_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex2_2.dir/build: ex2_2.exe

.PHONY : CMakeFiles/ex2_2.dir/build

CMakeFiles/ex2_2.dir/requires: CMakeFiles/ex2_2.dir/LineSeparator.c.o.requires

.PHONY : CMakeFiles/ex2_2.dir/requires

CMakeFiles/ex2_2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex2_2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex2_2.dir/clean

CMakeFiles/ex2_2.dir/depend:
	cd "/cygdrive/c/Users/nadav vitri/CLionProjects/ex2.2/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/Users/nadav vitri/CLionProjects/ex2.2" "/cygdrive/c/Users/nadav vitri/CLionProjects/ex2.2" "/cygdrive/c/Users/nadav vitri/CLionProjects/ex2.2/cmake-build-debug" "/cygdrive/c/Users/nadav vitri/CLionProjects/ex2.2/cmake-build-debug" "/cygdrive/c/Users/nadav vitri/CLionProjects/ex2.2/cmake-build-debug/CMakeFiles/ex2_2.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/ex2_2.dir/depend

