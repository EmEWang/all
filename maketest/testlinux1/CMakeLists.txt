cmake_minimum_required(VERSION 3.10)
project(test)
file(GLOB objfiles  *.c)
foreach(obj IN LISTS objfiles)     # 对每个文件生成一个可执行程序
    # Get file name without directory
    get_filename_component(mainname ${obj} NAME_WE)
    message("origin:${obj} to:${mainname}")
    add_executable(${mainname} ${obj})
    if(${mainname} MATCHES "draw")
        target_link_libraries(${mainname} PRIVATE -pthread -lrt -lm)
    elseif(${mainname} MATCHES "sched")
        target_compile_definitions(${mainname} PRIVATE _GNU_SOURCE)#gcc需要特殊宏 gcc不需要
    else()
        target_link_libraries(${mainname} PRIVATE -pthread -lrt) # draw需要-lm
    endif()
endforeach()



