# Install script for directory: D:/programming/MSYS2_SETUP/home/amrat/JUCE

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/HearMEout")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Custom")
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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/programming/MSYS2_SETUP/home/amrat/JUCE/projects/HearMEout/build/JUCE-build/tools/modules/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/programming/MSYS2_SETUP/home/amrat/JUCE/projects/HearMEout/build/JUCE-build/tools/extras/Build/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-8.0.10" TYPE FILE FILES
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/projects/HearMEout/build/JUCE-build/tools/JUCEConfigVersion.cmake"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/projects/HearMEout/build/JUCE-build/tools/JUCEConfig.cmake"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/JUCECheckAtomic.cmake"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/JUCEHelperTargets.cmake"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/JUCEModuleSupport.cmake"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/JUCEUtils.cmake"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/JuceLV2Defines.h.in"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/LaunchScreen.storyboard"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/PIPAudioProcessor.cpp.in"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/PIPAudioProcessorWithARA.cpp.in"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/PIPComponent.cpp.in"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/PIPConsole.cpp.in"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/RecentFilesMenuTemplate.nib"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/UnityPluginGUIScript.cs.in"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/checkBundleSigning.cmake"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/copyDir.cmake"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/juce_runtime_arch_detection.cpp"
    "D:/programming/MSYS2_SETUP/home/amrat/JUCE/extras/Build/CMake/juce_LinuxSubprocessHelper.cpp"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "D:/programming/MSYS2_SETUP/home/amrat/JUCE/projects/HearMEout/build/JUCE-build/tools/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "D:/programming/MSYS2_SETUP/home/amrat/JUCE/projects/HearMEout/build/JUCE-build/tools/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
