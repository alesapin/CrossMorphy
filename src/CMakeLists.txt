include_directories(${PROJECT_SOURCE_DIR}/include)
set (SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Analyze/SufProcessor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Base/MorphChars.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Base/MorphClass.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Base/MorphClassContainer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Build/AutomationBuilder.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Analyze/DictAnalyzer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Base/TagConverter.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/TagPrinter/CrossLexTagPrinter.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Analyze/NounPairs.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MorphAnalyzer.cpp

  PARENT_SCOPE
)
