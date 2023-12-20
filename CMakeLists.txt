cmake_minimum_required(VERSION 3.5)

project(imageReadWithC LANGUAGES C)

add_executable(imageReadWithC main.c)

include(GNUInstallDirs)
install(TARGETS imageReadWithC
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
