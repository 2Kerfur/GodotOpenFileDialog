cmake_minimum_required(VERSION 2.6.0)

project(GodotNativeTools C)

add_executable(${PROJECT_NAME} 
    #core files
    src/main.c
    src/main.h

    #linux source
    src/linux/arduino/com_port.c
    src/linux/arduino/com_port.h
    src/linux/utils/dir.c
    src/linux/utils/dir.h
    src/linux/utils/native_dialog.c
    src/linux/utils/native_dialog.h


    #windows source
    src/windows/arduino/com_port.c
    src/windows/arduino/com_port.h
    src/windows/utils/dir.c
    src/windows/utils/dir.h
    src/windows/utils/native_dialog.c
    src/windows/utils/native_dialog.h

)

target_include_directories(${PROJECT_NAME}
    PUBLIC src
)