# **********************************************************
#      2024 : Arthur JEULIN
#      Copyright (c) 
#      Created by Arthur JEULIN on 03/10/2024.
# **********************************************************
cmake_minimum_required(VERSION 3.27.5)


# RTMaps Package Name
set(PCK Demo-System)

set(POSITION_INDEPENDENT_CODE ON)

if(UNIX)
    set(RTMAPS_SDKDIR "/opt/rtmaps")
endif()
if(WIN32)
    set(RTMAPS_SDKDIR "C:/Program Files/Intempora/RTMaps 4")
    set(CMAKE_GENERATOR_TOOLSET "v143")
endif()
    
    
project("${PCK}.u"
  VERSION 0.0.1
  DESCRIPTION "RTMaps Component RFID-System"
  LANGUAGES CXX
)
    
find_package (glog 0.6.0 CONFIG REQUIRED)  
find_package(tinyxml2 CONFIG REQUIRED)
find_package(OpenCV REQUIRED)

# If -D"RTMAPS_SDKDIR=<RTMaps Install Dir>" has NOT been passed to 
# the "cmake" command
if (NOT DEFINED RTMAPS_SDKDIR) 
# Try to use the default RTMaps installation
    if (DEFINED ENV{RTMAPS_SDKDIR})  
        set(RTMAPS_SDKDIR "$ENV{RTMAPS_SDKDIR}" 
        CACHE PATH "Path the RTMaps installation directory")
    else()
        message(FATAL_ERROR
        "RTMAPS_SDKDIR not defined. Either pass -D\"RTMAPS_SDKDIR=...\" 
        to CMake or define an RTMAPS_SDKDIR environment variable")
    endif()
endif()

# REQUIRED: Include the RTMaps CMake configuration file
include("${RTMAPS_SDKDIR}/templates.u/rtmaps.cmake")


add_rtmaps_package(${PCK} PCKINFO "${PCK}.pckinfo"
    # add sources, headers and/or directories
    "local_interfaces"                    
    "src"                              
)

#Include path change if we are on Windows or Linux
include_directories(${OpenCV_INCLUDE_DIRS})
target_include_directories(${PCK} PRIVATE 
  ${OpenCV_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/rtmaps/local_interfaces
)


# HIGHLY RECOMMENDED: Append useful compiler flags
if (MSVC)
    # Winmm.lib Needed in Windows to Gettime (API of Windows)
    # target_link_libraries(${PCK} Winmm.lib)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Options pour le mode Debug
    target_link_libraries(${PCK} 
    Winmm.lib
    glog::glog
    ${OpenCV_LIBS} 
    )
    # Ne peut pas utiliser se flag pour une raison que j'igonre /MPd
    # rtmaps_pck.lib est compiler en release donc on ne peut pas utliser
    # certains flags de debug car non compatible => rechercher a faire
    target_compile_options(${PCK} PRIVATE  /W3 /WX /MD )
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Options pour le mode Release
    target_link_libraries(${PCK}
    Winmm.lib 
    glog::glog
    ${OpenCV_LIBS} 
    )
    target_compile_options(${PCK} PRIVATE /MD /MP /W3 /WX -DNDEBUG)
endif()
else()
    target_link_libraries(${PCK}
    glog::glog
    ${OpenCV_LIBS} 
    )
    target_compile_options(${PCK} PRIVATE
    -Wall -Wextra -Wpedantic -finline-functions -fexceptions 
    -O3 -fdiagnostics-show-option -pedantic)

    install(TARGETS ${PCK}
            CONFIGURATIONS Release
            DESTINATION "${RTMAPS_SDKDIR}/user_sdk/package"
    )
endif()