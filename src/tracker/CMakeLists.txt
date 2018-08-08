project(truckTracker)

cmake_minimum_required(VERSION 2.6)

set(SOURCES main.cpp)

if(WIN32)
  include_directories(../common/msinttypes)
endif(WIN32)

add_executable(truckTracker ${SOURCES})

if(WIN32)
  add_definitions(-DNOMINMAX -D_WIN32_WINNT=0x0501)
  set_target_properties(truckTracker PROPERTIES 
                        COMPILE_FLAGS "-D_SCL_SECURE_NO_WARNINGS")
  target_link_libraries(truckTracker setupapi)

else(WIN32)
  if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")

    if (NOT CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
      set_target_properties(truckTracker PROPERTIES LINK_FLAGS "-s")

    endif()
  endif()

  target_link_libraries(truckTracker)

endif(WIN32)

