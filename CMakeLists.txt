project (proij-lp)

set(SOURCES
    main.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(CXX_STANDARD 14)
add_executable(proij-lp ${SOURCES})
