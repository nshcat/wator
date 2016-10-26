#######################################################################################
## wator CMake Project File
##

# Version requirement and project info
cmake_minimum_required(VERSION 3.3.0)
project(wator)

# Include submodule libraries
add_subdirectory(btt)

# Source files
file(GLOB SOURCE_FILES src/*.c)

# Data files
file(GLOB DATA_FILES data/*.*)

foreach(DATA_FILE ${DATA_FILES})
	get_filename_component(DATA_FILE_NAME ${DATA_FILE} NAME)
	configure_file(${DATA_FILE} ${DATA_FILE_NAME} COPYONLY)
endforeach()
##

# Define target as executable
add_executable(wator ${SOURCE_FILES})

# Include own include files
target_include_directories(wator PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

# Use crude hack to get project to compile with MSYS.
if(MINGW OR MSYS)
	# Manually set paths
	set_target_properties(wator PROPERTIES COMPILE_FLAGS "-I/mingw64/include/SDL2")
		
	# Link to support libraries
	target_link_libraries(wator PUBLIC mingw32 sdl2main sdl2 sdl2_image)
	
# Use find_package to retrieve SDL2 paths
else()
	set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../cmake)
	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
	
	# Include SDL2 include directories
	target_include_directories(wator PUBLIC ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

	# Link to libraries
	target_link_libraries(wator PUBLIC ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
endif()


# Link to libraries
target_link_libraries(wator PUBLIC ${LIBBTT_LIBRARIES})


# Require support for at least C11.
set_property(TARGET wator PROPERTY C_STANDARD 11)
set_property(TARGET wator PROPERTY C_STANDARD_REQUIRED ON)




