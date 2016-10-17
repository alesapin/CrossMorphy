project(CrossMorphy)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
find_package(Boost COMPONENTS locale program_options regex REQUIRED)
find_package(ICU REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set (EXECUTABLE_OUTPUT_PATH bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set (SOURCE_FILES
  main.cpp
  analyze/SufProcessor.cpp analyze/SufProcessor.h
  base/MorphChars.h base/MorphChars.cpp
  base/MorphClass.cpp base/MorphClass.cpp
  base/MorphClassContainer.h base/MorphClassContainer.cpp
  build/AutomationBuilder.h build/AutomationBuilder.cpp
  analyze/DictAnalyzer.cpp analyze/DictAnalyzer.cpp
  base/TagConverter.h base/TagConverter.cpp
  tag_printer/CrossLexTagPrinter.h tag_printer/CrossLexTagPrinter.cpp
  analyze/NounPairs.h analyze/NounPairs.cpp
  Config.cpp
  MorphAnalyzer.cpp
)
add_executable(CrossMorphy ${SOURCE_FILES})
target_link_libraries(CrossMorphy ${Boost_LIBRARIES} ${ICU_LIBRARIES})
