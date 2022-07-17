# Install script for directory: /Users/jordanevans/Documents/ASPIK/ALL_SDK/myprojects/JExciter/cmake/vst_cmake

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

set(CMAKE_BINARY_DIR "/Users/jordanevans/Documents/ASPIK/ALL_SDK/myprojects/JExciter/mac_build")

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/jordanevans/Documents/ASPIK/ALL_SDK/myprojects/JExciter/mac_build/cmake/vst_cmake/pluginterfaces/cmake_install.cmake")
  include("/Users/jordanevans/Documents/ASPIK/ALL_SDK/myprojects/JExciter/mac_build/cmake/vst_cmake/base/cmake_install.cmake")
  include("/Users/jordanevans/Documents/ASPIK/ALL_SDK/myprojects/JExciter/mac_build/cmake/vst_cmake/public.sdk/cmake_install.cmake")
  include("/Users/jordanevans/Documents/ASPIK/ALL_SDK/myprojects/JExciter/mac_build/cmake/vst_cmake/public.sdk/samples/vst-hosting/cmake_install.cmake")
  include("/Users/jordanevans/Documents/ASPIK/ALL_SDK/myprojects/JExciter/mac_build/project_source/cmake/vst_cmake/cmake_install.cmake")
  include("/Users/jordanevans/Documents/ASPIK/ALL_SDK/myprojects/JExciter/mac_build/cmake/vst_cmake/vstgui4/vstgui/cmake_install.cmake")

endif()

