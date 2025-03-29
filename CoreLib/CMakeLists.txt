#GameCore library - By Daniel Sutton 2025




#gather source files
file(GLOB_RECURSE gc_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE gc_headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE gc_inlines ${CMAKE_CURRENT_SOURCE_DIR}/include/*.inl)
add_library(GCore STATIC ${gc_sources} ${gc_headers} ${gc_inlines})

target_include_directories(GCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(GCore PRIVATE SFML::System SFML::Graphics)
