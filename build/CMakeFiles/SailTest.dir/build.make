# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/marinph/PG/Sailtest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marinph/PG/Sailtest/build

# Include any dependencies generated for this target.
include CMakeFiles/SailTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SailTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SailTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SailTest.dir/flags.make

CMakeFiles/SailTest.dir/main.cpp.o: CMakeFiles/SailTest.dir/flags.make
CMakeFiles/SailTest.dir/main.cpp.o: /home/marinph/PG/Sailtest/main.cpp
CMakeFiles/SailTest.dir/main.cpp.o: CMakeFiles/SailTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marinph/PG/Sailtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SailTest.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SailTest.dir/main.cpp.o -MF CMakeFiles/SailTest.dir/main.cpp.o.d -o CMakeFiles/SailTest.dir/main.cpp.o -c /home/marinph/PG/Sailtest/main.cpp

CMakeFiles/SailTest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SailTest.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marinph/PG/Sailtest/main.cpp > CMakeFiles/SailTest.dir/main.cpp.i

CMakeFiles/SailTest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SailTest.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marinph/PG/Sailtest/main.cpp -o CMakeFiles/SailTest.dir/main.cpp.s

CMakeFiles/SailTest.dir/src/navigation/boat.cpp.o: CMakeFiles/SailTest.dir/flags.make
CMakeFiles/SailTest.dir/src/navigation/boat.cpp.o: /home/marinph/PG/Sailtest/src/navigation/boat.cpp
CMakeFiles/SailTest.dir/src/navigation/boat.cpp.o: CMakeFiles/SailTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marinph/PG/Sailtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SailTest.dir/src/navigation/boat.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SailTest.dir/src/navigation/boat.cpp.o -MF CMakeFiles/SailTest.dir/src/navigation/boat.cpp.o.d -o CMakeFiles/SailTest.dir/src/navigation/boat.cpp.o -c /home/marinph/PG/Sailtest/src/navigation/boat.cpp

CMakeFiles/SailTest.dir/src/navigation/boat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SailTest.dir/src/navigation/boat.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marinph/PG/Sailtest/src/navigation/boat.cpp > CMakeFiles/SailTest.dir/src/navigation/boat.cpp.i

CMakeFiles/SailTest.dir/src/navigation/boat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SailTest.dir/src/navigation/boat.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marinph/PG/Sailtest/src/navigation/boat.cpp -o CMakeFiles/SailTest.dir/src/navigation/boat.cpp.s

CMakeFiles/SailTest.dir/src/navigation/rudder.cpp.o: CMakeFiles/SailTest.dir/flags.make
CMakeFiles/SailTest.dir/src/navigation/rudder.cpp.o: /home/marinph/PG/Sailtest/src/navigation/rudder.cpp
CMakeFiles/SailTest.dir/src/navigation/rudder.cpp.o: CMakeFiles/SailTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marinph/PG/Sailtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SailTest.dir/src/navigation/rudder.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SailTest.dir/src/navigation/rudder.cpp.o -MF CMakeFiles/SailTest.dir/src/navigation/rudder.cpp.o.d -o CMakeFiles/SailTest.dir/src/navigation/rudder.cpp.o -c /home/marinph/PG/Sailtest/src/navigation/rudder.cpp

CMakeFiles/SailTest.dir/src/navigation/rudder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SailTest.dir/src/navigation/rudder.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marinph/PG/Sailtest/src/navigation/rudder.cpp > CMakeFiles/SailTest.dir/src/navigation/rudder.cpp.i

CMakeFiles/SailTest.dir/src/navigation/rudder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SailTest.dir/src/navigation/rudder.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marinph/PG/Sailtest/src/navigation/rudder.cpp -o CMakeFiles/SailTest.dir/src/navigation/rudder.cpp.s

CMakeFiles/SailTest.dir/src/navigation/keel.cpp.o: CMakeFiles/SailTest.dir/flags.make
CMakeFiles/SailTest.dir/src/navigation/keel.cpp.o: /home/marinph/PG/Sailtest/src/navigation/keel.cpp
CMakeFiles/SailTest.dir/src/navigation/keel.cpp.o: CMakeFiles/SailTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marinph/PG/Sailtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SailTest.dir/src/navigation/keel.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SailTest.dir/src/navigation/keel.cpp.o -MF CMakeFiles/SailTest.dir/src/navigation/keel.cpp.o.d -o CMakeFiles/SailTest.dir/src/navigation/keel.cpp.o -c /home/marinph/PG/Sailtest/src/navigation/keel.cpp

CMakeFiles/SailTest.dir/src/navigation/keel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SailTest.dir/src/navigation/keel.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marinph/PG/Sailtest/src/navigation/keel.cpp > CMakeFiles/SailTest.dir/src/navigation/keel.cpp.i

CMakeFiles/SailTest.dir/src/navigation/keel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SailTest.dir/src/navigation/keel.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marinph/PG/Sailtest/src/navigation/keel.cpp -o CMakeFiles/SailTest.dir/src/navigation/keel.cpp.s

CMakeFiles/SailTest.dir/src/navigation/hull.cpp.o: CMakeFiles/SailTest.dir/flags.make
CMakeFiles/SailTest.dir/src/navigation/hull.cpp.o: /home/marinph/PG/Sailtest/src/navigation/hull.cpp
CMakeFiles/SailTest.dir/src/navigation/hull.cpp.o: CMakeFiles/SailTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marinph/PG/Sailtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/SailTest.dir/src/navigation/hull.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SailTest.dir/src/navigation/hull.cpp.o -MF CMakeFiles/SailTest.dir/src/navigation/hull.cpp.o.d -o CMakeFiles/SailTest.dir/src/navigation/hull.cpp.o -c /home/marinph/PG/Sailtest/src/navigation/hull.cpp

CMakeFiles/SailTest.dir/src/navigation/hull.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SailTest.dir/src/navigation/hull.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marinph/PG/Sailtest/src/navigation/hull.cpp > CMakeFiles/SailTest.dir/src/navigation/hull.cpp.i

CMakeFiles/SailTest.dir/src/navigation/hull.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SailTest.dir/src/navigation/hull.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marinph/PG/Sailtest/src/navigation/hull.cpp -o CMakeFiles/SailTest.dir/src/navigation/hull.cpp.s

CMakeFiles/SailTest.dir/src/navigation/sail.cpp.o: CMakeFiles/SailTest.dir/flags.make
CMakeFiles/SailTest.dir/src/navigation/sail.cpp.o: /home/marinph/PG/Sailtest/src/navigation/sail.cpp
CMakeFiles/SailTest.dir/src/navigation/sail.cpp.o: CMakeFiles/SailTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marinph/PG/Sailtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/SailTest.dir/src/navigation/sail.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SailTest.dir/src/navigation/sail.cpp.o -MF CMakeFiles/SailTest.dir/src/navigation/sail.cpp.o.d -o CMakeFiles/SailTest.dir/src/navigation/sail.cpp.o -c /home/marinph/PG/Sailtest/src/navigation/sail.cpp

CMakeFiles/SailTest.dir/src/navigation/sail.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SailTest.dir/src/navigation/sail.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marinph/PG/Sailtest/src/navigation/sail.cpp > CMakeFiles/SailTest.dir/src/navigation/sail.cpp.i

CMakeFiles/SailTest.dir/src/navigation/sail.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SailTest.dir/src/navigation/sail.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marinph/PG/Sailtest/src/navigation/sail.cpp -o CMakeFiles/SailTest.dir/src/navigation/sail.cpp.s

# Object files for target SailTest
SailTest_OBJECTS = \
"CMakeFiles/SailTest.dir/main.cpp.o" \
"CMakeFiles/SailTest.dir/src/navigation/boat.cpp.o" \
"CMakeFiles/SailTest.dir/src/navigation/rudder.cpp.o" \
"CMakeFiles/SailTest.dir/src/navigation/keel.cpp.o" \
"CMakeFiles/SailTest.dir/src/navigation/hull.cpp.o" \
"CMakeFiles/SailTest.dir/src/navigation/sail.cpp.o"

# External object files for target SailTest
SailTest_EXTERNAL_OBJECTS =

SailTest: CMakeFiles/SailTest.dir/main.cpp.o
SailTest: CMakeFiles/SailTest.dir/src/navigation/boat.cpp.o
SailTest: CMakeFiles/SailTest.dir/src/navigation/rudder.cpp.o
SailTest: CMakeFiles/SailTest.dir/src/navigation/keel.cpp.o
SailTest: CMakeFiles/SailTest.dir/src/navigation/hull.cpp.o
SailTest: CMakeFiles/SailTest.dir/src/navigation/sail.cpp.o
SailTest: CMakeFiles/SailTest.dir/build.make
SailTest: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.6.1
SailTest: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.6.1
SailTest: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.6.1
SailTest: CMakeFiles/SailTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/marinph/PG/Sailtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable SailTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SailTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SailTest.dir/build: SailTest
.PHONY : CMakeFiles/SailTest.dir/build

CMakeFiles/SailTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SailTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SailTest.dir/clean

CMakeFiles/SailTest.dir/depend:
	cd /home/marinph/PG/Sailtest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marinph/PG/Sailtest /home/marinph/PG/Sailtest /home/marinph/PG/Sailtest/build /home/marinph/PG/Sailtest/build /home/marinph/PG/Sailtest/build/CMakeFiles/SailTest.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/SailTest.dir/depend

