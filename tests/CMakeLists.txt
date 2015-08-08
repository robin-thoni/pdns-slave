enable_testing()
include_directories(${CHECK_INCLUDE_DIRS})
include_directories(. ../src)
find_package (Threads)
set(LIBS ${LIBS} gtest pthread)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(test-pdns-slave
  test-pdns-slave.cpp
  )
target_link_libraries(test-pdns-slave ${LIBS})
add_test(test-pdns-slave ${CMAKE_CURRENT_BINARY_DIR}/test-pdns-slave)
