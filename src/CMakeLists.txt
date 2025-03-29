set(SOURCES Aircraft.cpp Command.cpp CommandQueue.cpp Entity.cpp Game.cpp main.cpp SceneNode.cpp SpriteNode.cpp World.cpp)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})



# Use FILE_SET for headers located in DanGame/include/
target_sources(DanGame PRIVATE
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_SOURCE_DIR}/include
    FILES ${CMAKE_SOURCE_DIR}/include/Aircraft.h
          ${CMAKE_SOURCE_DIR}/include/Command.h
)