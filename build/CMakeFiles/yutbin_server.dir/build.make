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
CMAKE_SOURCE_DIR = /home/zhaozeyu/Desktop/study/yutbin_server/build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhaozeyu/Desktop/study/yutbin_server/build

# Include any dependencies generated for this target.
include CMakeFiles/yutbin_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/yutbin_server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/yutbin_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/yutbin_server.dir/flags.make

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.o: CMakeFiles/yutbin_server.dir/flags.make
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.o: /home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.cpp
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.o: CMakeFiles/yutbin_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhaozeyu/Desktop/study/yutbin_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.o -MF CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.o.d -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.o -c /home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.cpp

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.cpp > CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.i

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.cpp -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.s

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.o: CMakeFiles/yutbin_server.dir/flags.make
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.o: /home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.cpp
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.o: CMakeFiles/yutbin_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhaozeyu/Desktop/study/yutbin_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.o -MF CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.o.d -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.o -c /home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.cpp

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.cpp > CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.i

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.cpp -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.s

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.o: CMakeFiles/yutbin_server.dir/flags.make
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.o: /home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.cpp
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.o: CMakeFiles/yutbin_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhaozeyu/Desktop/study/yutbin_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.o -MF CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.o.d -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.o -c /home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.cpp

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.cpp > CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.i

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.cpp -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.s

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.o: CMakeFiles/yutbin_server.dir/flags.make
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.o: /home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.cpp
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.o: CMakeFiles/yutbin_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhaozeyu/Desktop/study/yutbin_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.o -MF CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.o.d -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.o -c /home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.cpp

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.cpp > CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.i

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.cpp -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.s

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.o: CMakeFiles/yutbin_server.dir/flags.make
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.o: /home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.cpp
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.o: CMakeFiles/yutbin_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhaozeyu/Desktop/study/yutbin_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.o -MF CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.o.d -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.o -c /home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.cpp

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.cpp > CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.i

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.cpp -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.s

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.o: CMakeFiles/yutbin_server.dir/flags.make
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.o: /home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.cpp
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.o: CMakeFiles/yutbin_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhaozeyu/Desktop/study/yutbin_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.o -MF CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.o.d -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.o -c /home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.cpp

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.cpp > CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.i

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.cpp -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.s

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.o: CMakeFiles/yutbin_server.dir/flags.make
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.o: /home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.cpp
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.o: CMakeFiles/yutbin_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhaozeyu/Desktop/study/yutbin_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.o -MF CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.o.d -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.o -c /home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.cpp

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.cpp > CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.i

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.cpp -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.s

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logging.o: CMakeFiles/yutbin_server.dir/flags.make
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logging.o: /home/zhaozeyu/Desktop/study/yutbin_server/base/logging.cpp
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logging.o: CMakeFiles/yutbin_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhaozeyu/Desktop/study/yutbin_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logging.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logging.o -MF CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logging.o.d -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logging.o -c /home/zhaozeyu/Desktop/study/yutbin_server/base/logging.cpp

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logging.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logging.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhaozeyu/Desktop/study/yutbin_server/base/logging.cpp > CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logging.i

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logging.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logging.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhaozeyu/Desktop/study/yutbin_server/base/logging.cpp -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logging.s

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.o: CMakeFiles/yutbin_server.dir/flags.make
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.o: /home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.cpp
CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.o: CMakeFiles/yutbin_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhaozeyu/Desktop/study/yutbin_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.o -MF CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.o.d -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.o -c /home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.cpp

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.cpp > CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.i

CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.cpp -o CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.s

# Object files for target yutbin_server
yutbin_server_OBJECTS = \
"CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.o" \
"CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.o" \
"CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.o" \
"CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.o" \
"CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.o" \
"CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.o" \
"CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.o" \
"CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logging.o" \
"CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.o"

# External object files for target yutbin_server
yutbin_server_EXTERNAL_OBJECTS =

yutbin_server: CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/test/testlog.o
yutbin_server: CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Coroutines.o
yutbin_server: CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Thread.o
yutbin_server: CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/Timestamp.o
yutbin_server: CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/asyclogging.o
yutbin_server: CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/fileutil.o
yutbin_server: CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logfile.o
yutbin_server: CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logging.o
yutbin_server: CMakeFiles/yutbin_server.dir/home/zhaozeyu/Desktop/study/yutbin_server/base/logstream.o
yutbin_server: CMakeFiles/yutbin_server.dir/build.make
yutbin_server: CMakeFiles/yutbin_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhaozeyu/Desktop/study/yutbin_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable yutbin_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yutbin_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/yutbin_server.dir/build: yutbin_server
.PHONY : CMakeFiles/yutbin_server.dir/build

CMakeFiles/yutbin_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/yutbin_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/yutbin_server.dir/clean

CMakeFiles/yutbin_server.dir/depend:
	cd /home/zhaozeyu/Desktop/study/yutbin_server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhaozeyu/Desktop/study/yutbin_server/build /home/zhaozeyu/Desktop/study/yutbin_server/build /home/zhaozeyu/Desktop/study/yutbin_server/build /home/zhaozeyu/Desktop/study/yutbin_server/build /home/zhaozeyu/Desktop/study/yutbin_server/build/CMakeFiles/yutbin_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/yutbin_server.dir/depend

