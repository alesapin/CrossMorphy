include_directories(${PROJECT_SOURCE_DIR}/include)
set (SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Analyze/SufProcessor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Base/MorphChars.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Base/MorphClass.cpp

  PARENT_SCOPE
)
