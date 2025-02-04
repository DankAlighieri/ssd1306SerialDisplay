# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Tarefa03.02 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

file (GLOB LIBSOURCES "lib/*.c")
file (GLOB ASSETSOURCERS "assets/*.c")

add_executable(Tarefa03.02 Tarefa03.02.c ${LIBSOURCES} ${ASSETSOURCERS})

pico_set_program_name(Tarefa03.02 "Tarefa03.02")
pico_set_program_version(Tarefa03.02 "0.1")

pico_generate_pio_header(${CMAKE_PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/lib/pio_matrix.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Tarefa03.02 1)
pico_enable_stdio_usb(Tarefa03.02 1)

# Add the standard library to the build
target_link_libraries(Tarefa03.02
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(Tarefa03.02 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(Tarefa03.02 
        hardware_i2c
        hardware_uart
        hardware_pio
        )

pico_add_extra_outputs(Tarefa03.02)

