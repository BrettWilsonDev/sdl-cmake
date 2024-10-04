cmake_minimum_required(VERSION 3.22)
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 20)

##########################################################################################
# Project libs
##########################################################################################

# toggle libs to be used with ON and OFF

# sdl3 - wasm unknown
set(useSdl3 ON)

# sdl2 - wasm unknown
set(useSdl2 OFF)

# glad - wasm unknown
set(useGlad OFF)

# imgui files - wasm supported
set(useImGui OFF)

# ldtk loader used with LDtk
set(useLDtkLoader OFF)

# fmt library - wasm supported
set(useFmt OFF)

# box2d physics 2d - wasm untested
set(useBox2d OFF)

# bullet physics 3d - wasm supported
set(useBullet3 OFF)

# note: wont play nice with gcc use msvc/clang instead
# reactphysics 3d - wasm unsupported
set(useReactPhysics3D OFF)

# Jolt Physics 3d - wasm supported
set(useJoltPhysics OFF)

##########################################################################################
# pre lib include settings
##########################################################################################

# this is here to ensure the runtime is linked staticly for msvc
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
    else()
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    endif()
endif()

if (NOT DEFINED PLATFORM)
    set(PLATFORM "default")
endif()

##########################################################################################
# Add dependencies with FetchContent
##########################################################################################

# libraries array to be linked
set(LIBRARIES ${PROJECT_NAME})

include(FetchContent)
function(add_git_dependency libName gitURL gitTag)

        FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG        ${gitTag}
            GIT_SHALLOW    TRUE
            GIT_PROGRESS   TRUE
        )

        if(NOT ("${libName}" STREQUAL "libname"))
            FetchContent_MakeAvailable(${libName})
        endif()

endfunction()

# sld3
if(useSdl3)
    set(SDL3IMAGE_INSTALL OFF)
    set(BUILD_SHARED_LIBS FALSE)

    set(dep SDL3)
    add_git_dependency(
        ${dep}
        https://github.com/libsdl-org/SDL.git
        head
    )
    
    FetchContent_GetProperties(${dep})
    if(NOT ${dep}_POPULATED)
    endif()

    list(APPEND LIBRARIES SDL3::SDL3-static)

endif()

if(useSdl3)
    set(SDL3IMAGE_INSTALL OFF)
    set(BUILD_SHARED_LIBS FALSE)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(SDLIMAGE_AVIF OFF CACHE BOOL "Support loading AVIF images" FORCE)
    endif()
    
    
    set(dep SDL3_image)
    add_git_dependency(
        ${dep}
        https://github.com/libsdl-org/SDL_image.git
        head
    )
    
    FetchContent_GetProperties(${dep})
    if(NOT ${dep}_POPULATED)
    endif()

    include_directories(RECURSE build/_deps/sdl3-src/include/SDL3/)
        
    list(APPEND LIBRARIES SDL3_image::SDL3_image-static)

endif()

#add new dependencies here
# sld2
if(useSdl2)
    set(SDL2IMAGE_INSTALL OFF)
    set(BUILD_SHARED_LIBS FALSE)

    set(dep SDL2)
    add_git_dependency(
        ${dep}
        https://github.com/libsdl-org/SDL.git
        SDL2
    )
    
    FetchContent_GetProperties(${dep})
    if(NOT ${dep}_POPULATED)
    endif()

    list(APPEND LIBRARIES SDL2main SDL2-static)

endif()

if(useSdl2)
    set(SDL2IMAGE_INSTALL OFF)
    set(BUILD_SHARED_LIBS FALSE)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(SDL2IMAGE_AVIF OFF CACHE BOOL "Support loading AVIF images" FORCE)
    endif()
    
    
    set(dep SDL2_image)
    add_git_dependency(
        ${dep}
        https://github.com/libsdl-org/SDL_image.git
        SDL2
    )
    
    FetchContent_GetProperties(${dep})
    if(NOT ${dep}_POPULATED)
    endif()

    include_directories(RECURSE build/_deps/sdl2-src/include/SDL2/)
        
    list(APPEND LIBRARIES SDL2_image)

endif()

if(useGlad)
    set(dep glad)
    add_git_dependency(
        ${dep}
        https://github.com/Dav1dde/glad.git
        master
    )
    
    FetchContent_GetProperties(${dep})
    if(NOT ${dep}_POPULATED)
        FetchContent_Populate(${dep})

        set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
        set(GLAD_API "gl=" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
        set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")

        find_package(OpenGL REQUIRED)
        
        add_subdirectory(${${dep}_SOURCE_DIR} ${${dep}_BINARY_DIR})
    endif()

    # add the dependency here to be linked
    list(APPEND LIBRARIES ${dep})
endif()


# imgui files
if(useImGui)
endif()

# part of imgui files
if(useImGui)
endif()

# ldtk loader
if(useLDtkLoader)
    set(dep LDtkLoader)
    add_git_dependency(
        ${dep}
        https://github.com/Madour/LDtkLoader.git
        head
    )

    FetchContent_GetProperties(${dep})

    # add the dependency here to be linked
    list(APPEND LIBRARIES ${dep})
endif()

# fmt
if(useFmt)
    set(dep fmt)
    add_git_dependency(
        ${dep}
        https://github.com/fmtlib/fmt.git
        head
    )

    FetchContent_GetProperties(${dep})
        
    # add the dependency here to be linked
    list(APPEND LIBRARIES ${dep})
endif()

# box2d
if(useBox2d)
    set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE) # don't build the supplied examples

    set(dep box2d)
    add_git_dependency(
        ${dep}
        https://github.com/erincatto/box2d.git
        head
    )

    # add the dependency here to be linked
    list(APPEND LIBRARIES ${dep})
endif()

# bullet physics 3d
if(useBullet3)
    set(BUILD_EXTRAS OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BUILD_CPU_DEMOS OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "" FORCE) # don't build the supplied examples

    set(dep BULLET_PHYSICS3)
    add_git_dependency(
        ${dep}
        https://github.com/bulletphysics/bullet3.git
        head
    )

    FetchContent_GetProperties(${dep})
    if(NOT ${dep}_POPULATED)
        
    endif()

    include_directories(RECURSE build/_deps/bullet_physics3-src/src)
        
    # add the dependency here to be linked BulletDynamics BulletCollision LinearMath BulletSoftBody
    list(APPEND LIBRARIES BulletDynamics)
    list(APPEND LIBRARIES BulletCollision)
    list(APPEND LIBRARIES LinearMath)
    list(APPEND LIBRARIES BulletSoftBody)
endif()

# react physics
if(useReactPhysics3D)
    set(dep reactphysics3d)
    add_git_dependency(
        ${dep}
        https://github.com/DanielChappuis/ReactPhysics3D.git
        head
    )
    FetchContent_GetProperties(${dep})

    include_directories(RECURSE build/_deps/reactphysics3d-src/include)
        
    # add the dependency here to be linked
    list(APPEND LIBRARIES ${dep})
endif()

# jolt physics
if(useJoltPhysics)
    set(DOUBLE_PRECISION OFF)
    set(GENERATE_DEBUG_SYMBOLS ON)
    set(CROSS_PLATFORM_DETERMINISTIC OFF)
    set(INTERPROCEDURAL_OPTIMIZATION ON)
    set(FLOATING_POINT_EXCEPTIONS_ENABLED OFF)
    set(OBJECT_LAYER_BITS 16)
    set(USE_SSE4_1 ON)
    set(USE_SSE4_2 ON)
    set(USE_AVX ON)
    set(USE_AVX2 ON)
    set(USE_AVX512 OFF)
    set(USE_LZCNT ON)
    set(USE_TZCNT ON)
    set(USE_F16C ON)
    set(USE_FMADD ON)

    if (${PLATFORM} STREQUAL "Web")
        option(ENABLE_MEMORY_PROFILER "Enable emscriptens memory profiler to help find leaks" OFF)
        option(DOUBLE_PRECISION "Compile the library in double precision mode" OFF)
        option(ENABLE_SIMD "Enable SIMD instructions (warning: last major browser to support this was Safari 16.4 in March 2023)" OFF)
        option(ENABLE_MULTI_THREADING "Compile the library in multi threading mode (warning: doesn't work in Safari nor with any JS callbacks currently)'" OFF) # SharedArrayBuffer is not defined when ON
        option(BUILD_WASM_COMPAT_ONLY "Compile online the WASM compat version of the library (speeds up compilation)" ON)

        set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Distribution")
        set(FLOATING_POINT_EXCEPTIONS_ENABLED OFF)
        set(INTERPROCEDURAL_OPTIMIZATION OFF)
        set(GENERATE_DEBUG_SYMBOLS ON)
        set(DISABLE_CUSTOM_ALLOCATOR ON)
        set(OBJECT_LAYER_BITS 32)

        # Enable multi threading
        if (ENABLE_MULTI_THREADING)
            set(MULTI_THREADED_FLAG 
                -pthread 
                -s SHARED_MEMORY)
            set(ENVIRONMENT_FLAG
                -s ENVIRONMENT='web,node,worker' 
                -s PTHREAD_POOL_SIZE=16)
            set(CMAKE_CXX_FLAGS "-pthread -s SHARED_MEMORY")
        else()
            set(MULTI_THREADED_FLAG "")
            set(ENVIRONMENT_FLAG "-s ENVIRONMENT='web,node'")
        endif()
    endif()

    FetchContent_Declare(
        JoltPhysics
        GIT_REPOSITORY "https://github.com/jrouwe/JoltPhysics"
        GIT_TAG "v5.0.0"
        SOURCE_SUBDIR "Build"
    )
    FetchContent_MakeAvailable(JoltPhysics)

    set(CMAKE_EXE_LINKER_FLAGS_DISTRIBUTION "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
    
    # add the dependency here to be linked
    list(APPEND LIBRARIES Jolt)
endif()


##########################################################################################
# Project executable setup
##########################################################################################

# Adding our source files
# Define PROJECT_SOURCES as a list of all source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

# Define PROJECT_INCLUDE to be the path to the include directory of the project
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})

# Includes imgui source
if(useImGui)
    make_directory(../src/imgui)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src/imgui)
endif()


##########################################################################################
# compiler settings
##########################################################################################

if(NOT ${PLATFORM} STREQUAL "Web")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -pthread")
        target_link_libraries(${LIBRARIES} -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)
        # dont forget to set  "cmake.configureSettings": { "CMAKE_BUILD_TYPE": "${buildType}" } in settings.json for vs code
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
        endif()
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${LIBRARIES} -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
        target_link_libraries(${LIBRARIES} -static-intel -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_link_libraries(${LIBRARIES})

        if(OFF)
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")  
        endif()

        # dont forget to set  "cmake.configureSettings": { "CMAKE_BUILD_TYPE": "${buildType}" } in settings.json for vs code
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            message("-- console enabled")
            set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
        else()
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")  
        endif()
    else()
        target_link_libraries(${LIBRARIES})
    endif()
else()
    target_link_libraries(${LIBRARIES})
endif()


##########################################################################################
# custom commands
##########################################################################################

add_definitions( -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} )

# for web build when using emscripten
if(ASYNCIFY)
endif()


##########################################################################################
# Project build settings
##########################################################################################

if (useReactPhysics3D)
    set(CMAKE_CXX_FLAGS "-m64")
endif()

# Setting ASSETS_PATH
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O0 -DDEBUG")
    message("-- console enabled")
    if(NOT noAssets AND NOT ${PLATFORM} STREQUAL "Web")
        # Set the asset path macro to the absolute path on the dev machine
        target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")   
    endif()
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    if(NOT noAssets AND NOT ${PLATFORM} STREQUAL "Web")
        # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable
        target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets/")
    endif()
    if(WIN32)
      if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows") 
      endif()    
      add_compile_definitions(NDEBUG)
    endif()
endif()

# Set common compiler flags
# SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wswitch")
# Set common compiler flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# if (NOT DEFINED PLATFORM)
#     set(PLATFORM "default")
# endif()

if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an .html file.
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Os")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    if(NOT noAssets)
        # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -Os -Wall -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 --preload-file assets/ --shell-file ../src/minshell.html")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -Os -Wall -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 --preload-file assets/ --shell-file ../vendor/minshell.html")
        target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="/assets/") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable
    else()
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -Os -Wall -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 --shell-file ../vendor/minshell.html")
    endif()
endif()

# Ensure that hot-reload is enabled for VS
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
endif()
