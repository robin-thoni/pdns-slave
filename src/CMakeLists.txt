include_directories(.)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES
  main.cpp
  Interface/MainClass.cpp
  Interface/MainClass.h
  Interface/CommandLineParser.cpp
  Interface/CommandLineParser.h
  DBO/CommandLineOption.cpp
  DBO/CommandLineOption.h
  Business/PdnsSlave.cpp
  Business/PdnsSlave.h
  DBO/SqlConfiguration.cpp
  DBO/SqlConfiguration.h
  DataAccess/PdnsSlaveConfig.cpp
  DataAccess/PdnsSlaveConfig.h
  DataAccess/HostsConfig.cpp
  DataAccess/HostsConfig.h
  DBO/Actions/Action.cpp
  DBO/Actions/Action.h
  DBO/Result.hxx
  DBO/Result.h
  )
set(LIBS ${LIBS} jsoncpp)
add_executable(pdns-slave ${SOURCE_FILES} DBO/Actions/ActionDelHost.cpp DBO/Actions/ActionDelHost.h DBO/Actions/ActionAddHost.cpp DBO/Actions/ActionAddHost.h)
target_link_libraries(pdns-slave ${LIBS})
