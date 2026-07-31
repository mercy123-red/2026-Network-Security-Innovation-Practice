cmake_minimum_required(VERSION 3.13)

project(openfhe_conv_homework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenFHE CONFIG REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenFHE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenFHE_EXE_LINKER_FLAGS}")

if(NOT EXISTS "${OpenFHE_INCLUDE}/pke/openfhe.h" AND
   NOT EXISTS "${OpenFHE_INCLUDE}/openfhe.h")
    message(FATAL_ERROR
        "OpenFHE was found, but openfhe.h was not found under OpenFHE_INCLUDE='${OpenFHE_INCLUDE}'. "
        "This usually means OpenFHE was built but not installed. Run 'make install' in the OpenFHE "
        "build directory, or configure OpenFHE with -DCMAKE_INSTALL_PREFIX=$HOME/openfhe-install "
        "and then build this project with -DCMAKE_PREFIX_PATH=$HOME/openfhe-install.")
endif()

include_directories(${OPENMP_INCLUDES})
include_directories(${OpenFHE_INCLUDE})
include_directories(${OpenFHE_INCLUDE}/third-party/include)
include_directories(${OpenFHE_INCLUDE}/core)
include_directories(${OpenFHE_INCLUDE}/pke)
include_directories(${OpenFHE_INCLUDE}/binfhe)

link_directories(${OpenFHE_LIBDIR})
link_directories(${OPENMP_LIBRARIES})

add_executable(openfhe_conv_homework src/main.cpp)

if(DEFINED OpenFHE_SHARED_LIBRARIES AND OpenFHE_SHARED_LIBRARIES)
    target_link_libraries(openfhe_conv_homework PRIVATE ${OpenFHE_SHARED_LIBRARIES})
elseif(DEFINED OpenFHE_STATIC_LIBRARIES AND OpenFHE_STATIC_LIBRARIES)
    target_link_libraries(openfhe_conv_homework PRIVATE ${OpenFHE_STATIC_LIBRARIES})
else()
    message(FATAL_ERROR "OpenFHE was found, but no OpenFHE library target/list was exported.")
endif()
