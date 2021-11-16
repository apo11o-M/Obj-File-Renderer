project(main)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

SET(CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY(SFML)
ADD_EXECUTABLE(main Fps.cpp Vec2d.cpp Vec3d.cpp util.cpp ObjFileParser.cpp 3DModels/ObjModel.cpp main.cpp)

TARGET_LINK_LIBRARIES(main sfml-graphics sfml-window sfml-system)
