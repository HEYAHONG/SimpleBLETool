

cmake_minimum_required(VERSION 3.13)

#程序名称
Set(PROJECT_NAME SimpleBLETool)
#主版本
set(PROJECT_MAJOR_VERSION_STR 1)
#次版本号
set(PROJECT_MINOR_VERSION_STR 0)
#修订号
set(PROJECT_REVISION_VERSION_STR 0)
#构建版本（以时间戳天数作为构建版本）
string(TIMESTAMP PROJECT_BUILD_TIME_SECOND "%s" UTC)
math(EXPR  PROJECT_BUILD_VERSION_STR "${PROJECT_BUILD_TIME_SECOND}/60/60/24"  OUTPUT_FORMAT DECIMAL)
#程序版本
set(PROJECT_VERSION_STR "${PROJECT_MAJOR_VERSION_STR}.${PROJECT_MINOR_VERSION_STR}.${PROJECT_REVISION_VERSION_STR}.${PROJECT_BUILD_VERSION_STR}")
message(STATUS "Version:${PROJECT_VERSION_STR}")
configure_file(Version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Version.h)
if(WIN32)
configure_file(Version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/win32/Version.h)
endif()

Project(${PROJECT_NAME} C CXX ASM)
Project(${PROJECT_NAME}	VERSION "${PROJECT_VERSION_STR}")

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

#设置MSVC编译选项
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set_property(TARGET ${PROJECT_NAME}
		     PROPERTY WIN32_EXECUTABLE TRUE )
	target_compile_options(${PROJECT_NAME}
				PUBLIC /utf-8)
	
endif()

if(MSVC)
    # Use the static C library for all build types
    foreach(var
        CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
      )
      if(${var} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${var} "${${var}}")
      endif()
    endforeach()
endif(MSVC)

#添加wxWidgets库
if(WIN32)
	find_package(wxWidgets REQUIRED core base adv aui webview html gl richtext )
else()
	find_package(wxWidgets REQUIRED all)
endif()
include(${wxWidgets_USE_FILE})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

#添加simpleble库
add_subdirectory(SimpleBLE/simpleble/  EXCLUDE_FROM_ALL SYSTEM)
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

#软件包相关
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
	#安装桌面快捷方式
	install(FILES SimpleBLETool.desktop DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
	#安装桌面快捷方式图标
	install(FILES SimpleBLETool.png DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/32x32/apps)
	if(EXISTS "/etc/issue")
		file(READ "/etc/issue" ETC_ISSUE)
		if(ETC_ISSUE MATCHES "Debian|Ubuntu")

#打包deb软件包
message(STATUS "this is a debian(ubuntu) system")
set(CPACK_PACKAGE_NAME  "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION_STR}")
set(CPACK_PACKAGE_VENDOR "HEYAHONG")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SimpleBLETool By HYH")
set(CPACK_PACKAGE_DESCRIPTION "SimpleBLETool By HYH")
set(CPACK_PACKAGE_CONTACT    "2229388563@qq.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER    "HEYAHONG")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libwxgtk3.0-gtk3-0v5 (>=3.0.5.0),libdbus-1-3  (>=1.12.20)")
set(CPACK_DEBIAN_PACKAGE_SECTION "System;X11")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "Optional")
set(CPACK_GENERATOR "DEB")
include(CPack)

		endif()
	endif()
endif()



if(CMAKE_SYSTEM_NAME MATCHES "Windows")

#打包NSIS安装包
message(STATUS "this is a windows system")
set(CPACK_PACKAGE_NAME  "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION_STR}")
set(CPACK_PACKAGE_VENDOR "HEYAHONG")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SimpleBLETool By HYH")
set(CPACK_PACKAGE_DESCRIPTION "SimpleBLETool By HYH")
set(CPACK_PACKAGE_CONTACT    "2229388563@qq.com")
#设置安装程序图标
set(CPACK_PACKAGE_ICON_PATH_STRING "${CMAKE_CURRENT_SOURCE_DIR}/win32/window_resources.ico")
string(REPLACE "/" "\\\\" CPACK_PACKAGE_ICON ${CPACK_PACKAGE_ICON_PATH_STRING})
set(CPACK_NSIS_MUI_ICON ${CPACK_PACKAGE_ICON})
set(CPACK_NSIS_MUI_UNIICON ${CPACK_PACKAGE_ICON})
#安装前卸载
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
#设置在控制面板的名称
set(CPACK_NSIS_DISPLAY_NAME ${CPACK_PACKAGE_NAME})
#设置需要创建快捷方式的程序
set(CPACK_PACKAGE_EXECUTABLES ${PROJECT_NAME};${PROJECT_NAME} )
#设置LICENSE
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/win32/nsis/LICENSE.txt)
#设置Welcome
set(CPACK_RESOURCE_FILE_WELCOME ${CMAKE_CURRENT_SOURCE_DIR}/win32/nsis/WELCOME.txt)
#设置readme
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/win32/nsis/README.txt)
set(CPACK_GENERATOR "NSIS")
include(CPack)

endif()

