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
CMAKE_SOURCE_DIR = /home/mihal/projects/gosha_bot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mihal/projects/gosha_bot/build

# Include any dependencies generated for this target.
include CMakeFiles/bot.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bot.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bot.dir/flags.make

CMakeFiles/bot.dir/main.cpp.o: CMakeFiles/bot.dir/flags.make
CMakeFiles/bot.dir/main.cpp.o: ../main.cpp
CMakeFiles/bot.dir/main.cpp.o: CMakeFiles/bot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mihal/projects/gosha_bot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bot.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bot.dir/main.cpp.o -MF CMakeFiles/bot.dir/main.cpp.o.d -o CMakeFiles/bot.dir/main.cpp.o -c /home/mihal/projects/gosha_bot/main.cpp

CMakeFiles/bot.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bot.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mihal/projects/gosha_bot/main.cpp > CMakeFiles/bot.dir/main.cpp.i

CMakeFiles/bot.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bot.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mihal/projects/gosha_bot/main.cpp -o CMakeFiles/bot.dir/main.cpp.s

# Object files for target bot
bot_OBJECTS = \
"CMakeFiles/bot.dir/main.cpp.o"

# External object files for target bot
bot_EXTERNAL_OBJECTS =

bot: CMakeFiles/bot.dir/main.cpp.o
bot: CMakeFiles/bot.dir/build.make
bot: CMakeFiles/bot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mihal/projects/gosha_bot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bot"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bot.dir/build: bot
.PHONY : CMakeFiles/bot.dir/build

CMakeFiles/bot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bot.dir/clean

CMakeFiles/bot.dir/depend:
	cd /home/mihal/projects/gosha_bot/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mihal/projects/gosha_bot /home/mihal/projects/gosha_bot /home/mihal/projects/gosha_bot/build /home/mihal/projects/gosha_bot/build /home/mihal/projects/gosha_bot/build/CMakeFiles/bot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bot.dir/depend

