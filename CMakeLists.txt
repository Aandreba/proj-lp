project (proj-lp)

set(SOURCES
    src/main.cpp
    src/Util.cpp
    src/XML4OSMUtilModificat.cpp
    src/PuntDeInteresBase.cpp
    src/BallTree.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CXX_STANDARD 14)
add_executable(proj-lp ${SOURCES})
