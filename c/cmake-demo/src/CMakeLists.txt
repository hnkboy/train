# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(demo_test ${DIR_SRCS})

# 将项目目录下的cmake文件夹加入到CMAKE_MODULE_PATH中，让find_pakcage能够找到我们自定义的函数库
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
find_package(CURL)
find_package(ADD)
if(ADD_FOUND)
    #message("1.ADD_INCLUDE_DIR = ${ADD_INCLUDE_DIR}")
    target_include_directories(demo_test PRIVATE ${ADD_INCLUDE_DIR})
    target_link_libraries(demo_test  ${ADD_LIBRARY})
else(ADD_FOUND)
    message(FATAL_ERROR "ADD library not found")
endif(ADD_FOUND)
