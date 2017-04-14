
cmake_minimum_required(VERSION 3.0)

# boost handler (https://tinyurl.com/olotkwr, https://tinyurl.com/gmxfspp, assumes $BOOST_ROOT)
set(BOOST_ROOT "/Users/dirkleas/Downloads/boost_1_63_0")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
set(Boost_LIBRARIES "/Users/dirkleas/Downloads/boost_1_63_0/stage/lib")
find_package(Boost 1.63.0 COMPONENTS filesystem)
if(Boost_FOUND)
    #include_directories(${Boost_INCLUDE_DIRS}) 
    #add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp) 
    #target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

    # from max-devkit boilerplate
    include(${CMAKE_CURRENT_SOURCE_DIR}/../../max-api/script/max-pretarget.cmake)
    include_directories("${C74_INCLUDES}" "${Boost_INCLUDE_DIRS}")
    add_library(${PROJECT_NAME} MODULE ${PROJECT_NAME}.cpp)
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    include(${CMAKE_CURRENT_SOURCE_DIR}/../../max-api/script/max-posttarget.cmake)
endif()
