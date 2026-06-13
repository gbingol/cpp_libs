project(macrolandframework)


SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/macroland_app/64Bit)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/macroland_app/64Bit)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/macroland_app/64Bit)


set(CMAKE_DEBUG_POSTFIX "_d")


set(VARPY Python310)
#set(VARPY Python311)
#set(VARPY Python312)

if(${VARPY} STREQUAL "Python310")
	set(PYLIB "python310")
	set(PYHOME "C:/Python/Python3106/")

elseif(${VARPY} STREQUAL "Python311")
	set(PYLIB "python311")
	set(PYHOME "C:/Python/Python311/")

elseif(${VARPY} STREQUAL "Python312")
	set(PYLIB "python312")
	set(PYHOME "C:/Python/Python312/")
endif()



add_subdirectory(macroland)
