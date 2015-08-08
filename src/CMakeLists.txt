include_directories(.)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES
  main.cpp
  Interface/MainClass.cpp
  Interface/MainClass.h
  Interface/CommandLineParser.cpp
  Interface/CommandLineParser.h
  Interface/CommandLineOption.cpp
  Interface/CommandLineOption.h
  )
add_executable(pdns-slave ${SOURCE_FILES})
