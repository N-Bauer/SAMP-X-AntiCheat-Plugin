project(plugin)

cmake_minimum_required(VERSION 2.8)

include(AmxConfig)
include(plugin)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_plugin(plugin
  plugin.cpp
  plugin.def
  ${SDK_INCLUDE_DIR}/amxplugin.cpp
)

target_link_libraries(plugin sampgdk)
