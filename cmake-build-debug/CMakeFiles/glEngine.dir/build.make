# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.3.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.3.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\hanwe\OneDrive\CLionProjects\glEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/glEngine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/glEngine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/glEngine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/glEngine.dir/flags.make

CMakeFiles/glEngine.dir/vendor/glad/src/gl.c.obj: CMakeFiles/glEngine.dir/flags.make
CMakeFiles/glEngine.dir/vendor/glad/src/gl.c.obj: CMakeFiles/glEngine.dir/includes_C.rsp
CMakeFiles/glEngine.dir/vendor/glad/src/gl.c.obj: C:/Users/hanwe/OneDrive/CLionProjects/glEngine/vendor/glad/src/gl.c
CMakeFiles/glEngine.dir/vendor/glad/src/gl.c.obj: CMakeFiles/glEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/glEngine.dir/vendor/glad/src/gl.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/glEngine.dir/vendor/glad/src/gl.c.obj -MF CMakeFiles\glEngine.dir\vendor\glad\src\gl.c.obj.d -o CMakeFiles\glEngine.dir\vendor\glad\src\gl.c.obj -c C:\Users\hanwe\OneDrive\CLionProjects\glEngine\vendor\glad\src\gl.c

CMakeFiles/glEngine.dir/vendor/glad/src/gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/glEngine.dir/vendor/glad/src/gl.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\hanwe\OneDrive\CLionProjects\glEngine\vendor\glad\src\gl.c > CMakeFiles\glEngine.dir\vendor\glad\src\gl.c.i

CMakeFiles/glEngine.dir/vendor/glad/src/gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/glEngine.dir/vendor/glad/src/gl.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\hanwe\OneDrive\CLionProjects\glEngine\vendor\glad\src\gl.c -o CMakeFiles\glEngine.dir\vendor\glad\src\gl.c.s

CMakeFiles/glEngine.dir/src/engine/camera.cc.obj: CMakeFiles/glEngine.dir/flags.make
CMakeFiles/glEngine.dir/src/engine/camera.cc.obj: CMakeFiles/glEngine.dir/includes_CXX.rsp
CMakeFiles/glEngine.dir/src/engine/camera.cc.obj: C:/Users/hanwe/OneDrive/CLionProjects/glEngine/src/engine/camera.cc
CMakeFiles/glEngine.dir/src/engine/camera.cc.obj: CMakeFiles/glEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/glEngine.dir/src/engine/camera.cc.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/glEngine.dir/src/engine/camera.cc.obj -MF CMakeFiles\glEngine.dir\src\engine\camera.cc.obj.d -o CMakeFiles\glEngine.dir\src\engine\camera.cc.obj -c C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\camera.cc

CMakeFiles/glEngine.dir/src/engine/camera.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glEngine.dir/src/engine/camera.cc.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\camera.cc > CMakeFiles\glEngine.dir\src\engine\camera.cc.i

CMakeFiles/glEngine.dir/src/engine/camera.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glEngine.dir/src/engine/camera.cc.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\camera.cc -o CMakeFiles\glEngine.dir\src\engine\camera.cc.s

CMakeFiles/glEngine.dir/src/engine/cube.cc.obj: CMakeFiles/glEngine.dir/flags.make
CMakeFiles/glEngine.dir/src/engine/cube.cc.obj: CMakeFiles/glEngine.dir/includes_CXX.rsp
CMakeFiles/glEngine.dir/src/engine/cube.cc.obj: C:/Users/hanwe/OneDrive/CLionProjects/glEngine/src/engine/cube.cc
CMakeFiles/glEngine.dir/src/engine/cube.cc.obj: CMakeFiles/glEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/glEngine.dir/src/engine/cube.cc.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/glEngine.dir/src/engine/cube.cc.obj -MF CMakeFiles\glEngine.dir\src\engine\cube.cc.obj.d -o CMakeFiles\glEngine.dir\src\engine\cube.cc.obj -c C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\cube.cc

CMakeFiles/glEngine.dir/src/engine/cube.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glEngine.dir/src/engine/cube.cc.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\cube.cc > CMakeFiles\glEngine.dir\src\engine\cube.cc.i

CMakeFiles/glEngine.dir/src/engine/cube.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glEngine.dir/src/engine/cube.cc.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\cube.cc -o CMakeFiles\glEngine.dir\src\engine\cube.cc.s

CMakeFiles/glEngine.dir/src/engine/engine.cc.obj: CMakeFiles/glEngine.dir/flags.make
CMakeFiles/glEngine.dir/src/engine/engine.cc.obj: CMakeFiles/glEngine.dir/includes_CXX.rsp
CMakeFiles/glEngine.dir/src/engine/engine.cc.obj: C:/Users/hanwe/OneDrive/CLionProjects/glEngine/src/engine/engine.cc
CMakeFiles/glEngine.dir/src/engine/engine.cc.obj: CMakeFiles/glEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/glEngine.dir/src/engine/engine.cc.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/glEngine.dir/src/engine/engine.cc.obj -MF CMakeFiles\glEngine.dir\src\engine\engine.cc.obj.d -o CMakeFiles\glEngine.dir\src\engine\engine.cc.obj -c C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\engine.cc

CMakeFiles/glEngine.dir/src/engine/engine.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glEngine.dir/src/engine/engine.cc.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\engine.cc > CMakeFiles\glEngine.dir\src\engine\engine.cc.i

CMakeFiles/glEngine.dir/src/engine/engine.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glEngine.dir/src/engine/engine.cc.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\engine.cc -o CMakeFiles\glEngine.dir\src\engine\engine.cc.s

CMakeFiles/glEngine.dir/src/engine/importer.cc.obj: CMakeFiles/glEngine.dir/flags.make
CMakeFiles/glEngine.dir/src/engine/importer.cc.obj: CMakeFiles/glEngine.dir/includes_CXX.rsp
CMakeFiles/glEngine.dir/src/engine/importer.cc.obj: C:/Users/hanwe/OneDrive/CLionProjects/glEngine/src/engine/importer.cc
CMakeFiles/glEngine.dir/src/engine/importer.cc.obj: CMakeFiles/glEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/glEngine.dir/src/engine/importer.cc.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/glEngine.dir/src/engine/importer.cc.obj -MF CMakeFiles\glEngine.dir\src\engine\importer.cc.obj.d -o CMakeFiles\glEngine.dir\src\engine\importer.cc.obj -c C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\importer.cc

CMakeFiles/glEngine.dir/src/engine/importer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glEngine.dir/src/engine/importer.cc.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\importer.cc > CMakeFiles\glEngine.dir\src\engine\importer.cc.i

CMakeFiles/glEngine.dir/src/engine/importer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glEngine.dir/src/engine/importer.cc.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\importer.cc -o CMakeFiles\glEngine.dir\src\engine\importer.cc.s

CMakeFiles/glEngine.dir/src/engine/input_manager.cc.obj: CMakeFiles/glEngine.dir/flags.make
CMakeFiles/glEngine.dir/src/engine/input_manager.cc.obj: CMakeFiles/glEngine.dir/includes_CXX.rsp
CMakeFiles/glEngine.dir/src/engine/input_manager.cc.obj: C:/Users/hanwe/OneDrive/CLionProjects/glEngine/src/engine/input_manager.cc
CMakeFiles/glEngine.dir/src/engine/input_manager.cc.obj: CMakeFiles/glEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/glEngine.dir/src/engine/input_manager.cc.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/glEngine.dir/src/engine/input_manager.cc.obj -MF CMakeFiles\glEngine.dir\src\engine\input_manager.cc.obj.d -o CMakeFiles\glEngine.dir\src\engine\input_manager.cc.obj -c C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\input_manager.cc

CMakeFiles/glEngine.dir/src/engine/input_manager.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glEngine.dir/src/engine/input_manager.cc.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\input_manager.cc > CMakeFiles\glEngine.dir\src\engine\input_manager.cc.i

CMakeFiles/glEngine.dir/src/engine/input_manager.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glEngine.dir/src/engine/input_manager.cc.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\input_manager.cc -o CMakeFiles\glEngine.dir\src\engine\input_manager.cc.s

CMakeFiles/glEngine.dir/src/engine/mesh.cc.obj: CMakeFiles/glEngine.dir/flags.make
CMakeFiles/glEngine.dir/src/engine/mesh.cc.obj: CMakeFiles/glEngine.dir/includes_CXX.rsp
CMakeFiles/glEngine.dir/src/engine/mesh.cc.obj: C:/Users/hanwe/OneDrive/CLionProjects/glEngine/src/engine/mesh.cc
CMakeFiles/glEngine.dir/src/engine/mesh.cc.obj: CMakeFiles/glEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/glEngine.dir/src/engine/mesh.cc.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/glEngine.dir/src/engine/mesh.cc.obj -MF CMakeFiles\glEngine.dir\src\engine\mesh.cc.obj.d -o CMakeFiles\glEngine.dir\src\engine\mesh.cc.obj -c C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\mesh.cc

CMakeFiles/glEngine.dir/src/engine/mesh.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glEngine.dir/src/engine/mesh.cc.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\mesh.cc > CMakeFiles\glEngine.dir\src\engine\mesh.cc.i

CMakeFiles/glEngine.dir/src/engine/mesh.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glEngine.dir/src/engine/mesh.cc.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\mesh.cc -o CMakeFiles\glEngine.dir\src\engine\mesh.cc.s

CMakeFiles/glEngine.dir/src/engine/model.cc.obj: CMakeFiles/glEngine.dir/flags.make
CMakeFiles/glEngine.dir/src/engine/model.cc.obj: CMakeFiles/glEngine.dir/includes_CXX.rsp
CMakeFiles/glEngine.dir/src/engine/model.cc.obj: C:/Users/hanwe/OneDrive/CLionProjects/glEngine/src/engine/model.cc
CMakeFiles/glEngine.dir/src/engine/model.cc.obj: CMakeFiles/glEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/glEngine.dir/src/engine/model.cc.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/glEngine.dir/src/engine/model.cc.obj -MF CMakeFiles\glEngine.dir\src\engine\model.cc.obj.d -o CMakeFiles\glEngine.dir\src\engine\model.cc.obj -c C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\model.cc

CMakeFiles/glEngine.dir/src/engine/model.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glEngine.dir/src/engine/model.cc.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\model.cc > CMakeFiles\glEngine.dir\src\engine\model.cc.i

CMakeFiles/glEngine.dir/src/engine/model.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glEngine.dir/src/engine/model.cc.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\model.cc -o CMakeFiles\glEngine.dir\src\engine\model.cc.s

CMakeFiles/glEngine.dir/src/engine/primitive.cc.obj: CMakeFiles/glEngine.dir/flags.make
CMakeFiles/glEngine.dir/src/engine/primitive.cc.obj: CMakeFiles/glEngine.dir/includes_CXX.rsp
CMakeFiles/glEngine.dir/src/engine/primitive.cc.obj: C:/Users/hanwe/OneDrive/CLionProjects/glEngine/src/engine/primitive.cc
CMakeFiles/glEngine.dir/src/engine/primitive.cc.obj: CMakeFiles/glEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/glEngine.dir/src/engine/primitive.cc.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/glEngine.dir/src/engine/primitive.cc.obj -MF CMakeFiles\glEngine.dir\src\engine\primitive.cc.obj.d -o CMakeFiles\glEngine.dir\src\engine\primitive.cc.obj -c C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\primitive.cc

CMakeFiles/glEngine.dir/src/engine/primitive.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glEngine.dir/src/engine/primitive.cc.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\primitive.cc > CMakeFiles\glEngine.dir\src\engine\primitive.cc.i

CMakeFiles/glEngine.dir/src/engine/primitive.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glEngine.dir/src/engine/primitive.cc.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\primitive.cc -o CMakeFiles\glEngine.dir\src\engine\primitive.cc.s

CMakeFiles/glEngine.dir/src/engine/program.cc.obj: CMakeFiles/glEngine.dir/flags.make
CMakeFiles/glEngine.dir/src/engine/program.cc.obj: CMakeFiles/glEngine.dir/includes_CXX.rsp
CMakeFiles/glEngine.dir/src/engine/program.cc.obj: C:/Users/hanwe/OneDrive/CLionProjects/glEngine/src/engine/program.cc
CMakeFiles/glEngine.dir/src/engine/program.cc.obj: CMakeFiles/glEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/glEngine.dir/src/engine/program.cc.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/glEngine.dir/src/engine/program.cc.obj -MF CMakeFiles\glEngine.dir\src\engine\program.cc.obj.d -o CMakeFiles\glEngine.dir\src\engine\program.cc.obj -c C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\program.cc

CMakeFiles/glEngine.dir/src/engine/program.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glEngine.dir/src/engine/program.cc.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\program.cc > CMakeFiles\glEngine.dir\src\engine\program.cc.i

CMakeFiles/glEngine.dir/src/engine/program.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glEngine.dir/src/engine/program.cc.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\program.cc -o CMakeFiles\glEngine.dir\src\engine\program.cc.s

CMakeFiles/glEngine.dir/src/engine/shader.cc.obj: CMakeFiles/glEngine.dir/flags.make
CMakeFiles/glEngine.dir/src/engine/shader.cc.obj: CMakeFiles/glEngine.dir/includes_CXX.rsp
CMakeFiles/glEngine.dir/src/engine/shader.cc.obj: C:/Users/hanwe/OneDrive/CLionProjects/glEngine/src/engine/shader.cc
CMakeFiles/glEngine.dir/src/engine/shader.cc.obj: CMakeFiles/glEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/glEngine.dir/src/engine/shader.cc.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/glEngine.dir/src/engine/shader.cc.obj -MF CMakeFiles\glEngine.dir\src\engine\shader.cc.obj.d -o CMakeFiles\glEngine.dir\src\engine\shader.cc.obj -c C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\shader.cc

CMakeFiles/glEngine.dir/src/engine/shader.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glEngine.dir/src/engine/shader.cc.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\shader.cc > CMakeFiles\glEngine.dir\src\engine\shader.cc.i

CMakeFiles/glEngine.dir/src/engine/shader.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glEngine.dir/src/engine/shader.cc.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\shader.cc -o CMakeFiles\glEngine.dir\src\engine\shader.cc.s

CMakeFiles/glEngine.dir/src/engine/texture.cc.obj: CMakeFiles/glEngine.dir/flags.make
CMakeFiles/glEngine.dir/src/engine/texture.cc.obj: CMakeFiles/glEngine.dir/includes_CXX.rsp
CMakeFiles/glEngine.dir/src/engine/texture.cc.obj: C:/Users/hanwe/OneDrive/CLionProjects/glEngine/src/engine/texture.cc
CMakeFiles/glEngine.dir/src/engine/texture.cc.obj: CMakeFiles/glEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/glEngine.dir/src/engine/texture.cc.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/glEngine.dir/src/engine/texture.cc.obj -MF CMakeFiles\glEngine.dir\src\engine\texture.cc.obj.d -o CMakeFiles\glEngine.dir\src\engine\texture.cc.obj -c C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\texture.cc

CMakeFiles/glEngine.dir/src/engine/texture.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glEngine.dir/src/engine/texture.cc.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\texture.cc > CMakeFiles\glEngine.dir\src\engine\texture.cc.i

CMakeFiles/glEngine.dir/src/engine/texture.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glEngine.dir/src/engine/texture.cc.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\texture.cc -o CMakeFiles\glEngine.dir\src\engine\texture.cc.s

CMakeFiles/glEngine.dir/src/engine/utils.cc.obj: CMakeFiles/glEngine.dir/flags.make
CMakeFiles/glEngine.dir/src/engine/utils.cc.obj: CMakeFiles/glEngine.dir/includes_CXX.rsp
CMakeFiles/glEngine.dir/src/engine/utils.cc.obj: C:/Users/hanwe/OneDrive/CLionProjects/glEngine/src/engine/utils.cc
CMakeFiles/glEngine.dir/src/engine/utils.cc.obj: CMakeFiles/glEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/glEngine.dir/src/engine/utils.cc.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/glEngine.dir/src/engine/utils.cc.obj -MF CMakeFiles\glEngine.dir\src\engine\utils.cc.obj.d -o CMakeFiles\glEngine.dir\src\engine\utils.cc.obj -c C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\utils.cc

CMakeFiles/glEngine.dir/src/engine/utils.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glEngine.dir/src/engine/utils.cc.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\utils.cc > CMakeFiles\glEngine.dir\src\engine\utils.cc.i

CMakeFiles/glEngine.dir/src/engine/utils.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glEngine.dir/src/engine/utils.cc.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\utils.cc -o CMakeFiles\glEngine.dir\src\engine\utils.cc.s

CMakeFiles/glEngine.dir/src/engine/material.cc.obj: CMakeFiles/glEngine.dir/flags.make
CMakeFiles/glEngine.dir/src/engine/material.cc.obj: CMakeFiles/glEngine.dir/includes_CXX.rsp
CMakeFiles/glEngine.dir/src/engine/material.cc.obj: C:/Users/hanwe/OneDrive/CLionProjects/glEngine/src/engine/material.cc
CMakeFiles/glEngine.dir/src/engine/material.cc.obj: CMakeFiles/glEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/glEngine.dir/src/engine/material.cc.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/glEngine.dir/src/engine/material.cc.obj -MF CMakeFiles\glEngine.dir\src\engine\material.cc.obj.d -o CMakeFiles\glEngine.dir\src\engine\material.cc.obj -c C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\material.cc

CMakeFiles/glEngine.dir/src/engine/material.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glEngine.dir/src/engine/material.cc.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\material.cc > CMakeFiles\glEngine.dir\src\engine\material.cc.i

CMakeFiles/glEngine.dir/src/engine/material.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glEngine.dir/src/engine/material.cc.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\hanwe\OneDrive\CLionProjects\glEngine\src\engine\material.cc -o CMakeFiles\glEngine.dir\src\engine\material.cc.s

CMakeFiles/glEngine.dir/main.cc.obj: CMakeFiles/glEngine.dir/flags.make
CMakeFiles/glEngine.dir/main.cc.obj: CMakeFiles/glEngine.dir/includes_CXX.rsp
CMakeFiles/glEngine.dir/main.cc.obj: C:/Users/hanwe/OneDrive/CLionProjects/glEngine/main.cc
CMakeFiles/glEngine.dir/main.cc.obj: CMakeFiles/glEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/glEngine.dir/main.cc.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/glEngine.dir/main.cc.obj -MF CMakeFiles\glEngine.dir\main.cc.obj.d -o CMakeFiles\glEngine.dir\main.cc.obj -c C:\Users\hanwe\OneDrive\CLionProjects\glEngine\main.cc

CMakeFiles/glEngine.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glEngine.dir/main.cc.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\hanwe\OneDrive\CLionProjects\glEngine\main.cc > CMakeFiles\glEngine.dir\main.cc.i

CMakeFiles/glEngine.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glEngine.dir/main.cc.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\hanwe\OneDrive\CLionProjects\glEngine\main.cc -o CMakeFiles\glEngine.dir\main.cc.s

# Object files for target glEngine
glEngine_OBJECTS = \
"CMakeFiles/glEngine.dir/vendor/glad/src/gl.c.obj" \
"CMakeFiles/glEngine.dir/src/engine/camera.cc.obj" \
"CMakeFiles/glEngine.dir/src/engine/cube.cc.obj" \
"CMakeFiles/glEngine.dir/src/engine/engine.cc.obj" \
"CMakeFiles/glEngine.dir/src/engine/importer.cc.obj" \
"CMakeFiles/glEngine.dir/src/engine/input_manager.cc.obj" \
"CMakeFiles/glEngine.dir/src/engine/mesh.cc.obj" \
"CMakeFiles/glEngine.dir/src/engine/model.cc.obj" \
"CMakeFiles/glEngine.dir/src/engine/primitive.cc.obj" \
"CMakeFiles/glEngine.dir/src/engine/program.cc.obj" \
"CMakeFiles/glEngine.dir/src/engine/shader.cc.obj" \
"CMakeFiles/glEngine.dir/src/engine/texture.cc.obj" \
"CMakeFiles/glEngine.dir/src/engine/utils.cc.obj" \
"CMakeFiles/glEngine.dir/src/engine/material.cc.obj" \
"CMakeFiles/glEngine.dir/main.cc.obj"

# External object files for target glEngine
glEngine_EXTERNAL_OBJECTS =

glEngine.exe: CMakeFiles/glEngine.dir/vendor/glad/src/gl.c.obj
glEngine.exe: CMakeFiles/glEngine.dir/src/engine/camera.cc.obj
glEngine.exe: CMakeFiles/glEngine.dir/src/engine/cube.cc.obj
glEngine.exe: CMakeFiles/glEngine.dir/src/engine/engine.cc.obj
glEngine.exe: CMakeFiles/glEngine.dir/src/engine/importer.cc.obj
glEngine.exe: CMakeFiles/glEngine.dir/src/engine/input_manager.cc.obj
glEngine.exe: CMakeFiles/glEngine.dir/src/engine/mesh.cc.obj
glEngine.exe: CMakeFiles/glEngine.dir/src/engine/model.cc.obj
glEngine.exe: CMakeFiles/glEngine.dir/src/engine/primitive.cc.obj
glEngine.exe: CMakeFiles/glEngine.dir/src/engine/program.cc.obj
glEngine.exe: CMakeFiles/glEngine.dir/src/engine/shader.cc.obj
glEngine.exe: CMakeFiles/glEngine.dir/src/engine/texture.cc.obj
glEngine.exe: CMakeFiles/glEngine.dir/src/engine/utils.cc.obj
glEngine.exe: CMakeFiles/glEngine.dir/src/engine/material.cc.obj
glEngine.exe: CMakeFiles/glEngine.dir/main.cc.obj
glEngine.exe: CMakeFiles/glEngine.dir/build.make
glEngine.exe: vendor/glfw-3.4/src/libglfw3.a
glEngine.exe: vendor/glm-1.0.1/glm/libglm.a
glEngine.exe: CMakeFiles/glEngine.dir/linkLibs.rsp
glEngine.exe: CMakeFiles/glEngine.dir/objects1.rsp
glEngine.exe: CMakeFiles/glEngine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable glEngine.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\glEngine.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/glEngine.dir/build: glEngine.exe
.PHONY : CMakeFiles/glEngine.dir/build

CMakeFiles/glEngine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\glEngine.dir\cmake_clean.cmake
.PHONY : CMakeFiles/glEngine.dir/clean

CMakeFiles/glEngine.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\hanwe\OneDrive\CLionProjects\glEngine C:\Users\hanwe\OneDrive\CLionProjects\glEngine C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug C:\Users\hanwe\OneDrive\CLionProjects\glEngine\cmake-build-debug\CMakeFiles\glEngine.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/glEngine.dir/depend

