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
CMAKE_SOURCE_DIR = /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms

# Utility rule file for gen1.

# Include the progress variables for this target.
include lib/clingo/libgringo/CMakeFiles/gen1.dir/progress.make

lib/clingo/libgringo/CMakeFiles/gen1: lib/clingo/libgringo/src/input/groundtermgrammar/grammar.cc


lib/clingo/libgringo/src/input/groundtermgrammar/grammar.cc: lib/clingo/libgringo/src/input/groundtermgrammar.yy
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "[BISON][groundtermgrammar] Building parser with bison 3.5.1"
	cd /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libgringo && /usr/bin/bison -d -o /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libgringo/src/input/groundtermgrammar/grammar.cc /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libgringo/src/input/groundtermgrammar.yy

lib/clingo/libgringo/src/input/groundtermgrammar/grammar.hh: lib/clingo/libgringo/src/input/groundtermgrammar/grammar.cc
	@$(CMAKE_COMMAND) -E touch_nocreate lib/clingo/libgringo/src/input/groundtermgrammar/grammar.hh

gen1: lib/clingo/libgringo/CMakeFiles/gen1
gen1: lib/clingo/libgringo/src/input/groundtermgrammar/grammar.cc
gen1: lib/clingo/libgringo/src/input/groundtermgrammar/grammar.hh
gen1: lib/clingo/libgringo/CMakeFiles/gen1.dir/build.make

.PHONY : gen1

# Rule to build all files generated by this target.
lib/clingo/libgringo/CMakeFiles/gen1.dir/build: gen1

.PHONY : lib/clingo/libgringo/CMakeFiles/gen1.dir/build

lib/clingo/libgringo/CMakeFiles/gen1.dir/clean:
	cd /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libgringo && $(CMAKE_COMMAND) -P CMakeFiles/gen1.dir/cmake_clean.cmake
.PHONY : lib/clingo/libgringo/CMakeFiles/gen1.dir/clean

lib/clingo/libgringo/CMakeFiles/gen1.dir/depend:
	cd /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libgringo /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libgringo /home/isabelle/Schreibtisch/Uni/AIM/InconsistencyMeasureAlgorithms/lib/clingo/libgringo/CMakeFiles/gen1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/clingo/libgringo/CMakeFiles/gen1.dir/depend
