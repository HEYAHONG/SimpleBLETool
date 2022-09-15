

cmake_minimum_required(VERSION 3.13)

Set(PROJECT_NAME SimpleBLETool)

Project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)


file(GLOB MAIN_CXX_C_FILES *.cpp *.hpp *.c *.h bluetooth/*.c bluetooth/*.cpp bluetooth/*.h )
list(APPEND  MAIN_SRCS ${MAIN_CXX_C_FILES})

if(WIN32)
	file(GLOB_RECURSE MAIN_RC_FILES win32/*.rc)
	list(APPEND  MAIN_SRCS ${MAIN_RC_FILES})
endif()


add_executable(${PROJECT_NAME} ${MAIN_SRCS})
target_link_libraries(${PROJECT_NAME} ${MAIN_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC bluetooth )

#添加线程库
FIND_PACKAGE(Threads REQUIRED)
TARGET_LINK_LIBRARIES(${PROJECT_NAME}  ${CMAKE_THREAD_LIBS_INIT})

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set_property(TARGET ${PROJECT_NAME}
		     PROPERTY WIN32_EXECUTABLE TRUE )
	target_compile_options(${PROJECT_NAME}
				PUBLIC /utf-8)
endif()


#添加wxWidgets库
if(WIN32)
	find_package(wxWidgets REQUIRED core base adv aui webview html gl richtext )
else()
	find_package(wxWidgets REQUIRED all)
endif()
include(${wxWidgets_USE_FILE})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

#添加simpleble库
add_subdirectory(SimpleBLE/simpleble/)
target_link_libraries(${PROJECT_NAME} simpleble::simpleble)
file(GLOB_RECURSE SIMPLEBLE_HEADER_FILES SimpleBLE/simpleble/*.h )
target_sources(${PROJECT_NAME} PUBLIC  ${SIMPLEBLE_HEADER_FILES})

include(GNUInstallDirs)
#安装
INSTALL(TARGETS ${PROJECT_NAME}
       RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
       LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
       ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
