project (proj-lp)

set(SOURCES
    main.cpp
    Util.cpp
    XML4OSMUtilModificat.cpp
    PuntDeInteresBase.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(CXX_STANDARD 14)
add_executable(proj-lp src/${SOURCES})
