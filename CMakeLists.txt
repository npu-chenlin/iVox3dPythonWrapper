
cmake_minimum_required(VERSION 3.7)

project(ivox3d)

include(cmake/PICMake.cmake)
set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message("-- Build type: " ${CMAKE_BUILD_TYPE})
add_definitions(-DIVOX_NODE_TYPE_PHC)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DWIN32_LEAN_AND_MEAN /DNOMINMAX ")
    # for compile complex Eigen templates
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
    
    # about /MT and /MD
    #   http://www.cnblogs.com/cswuyg/archive/2012/02/03/2336424.html
    #   https://docs.microsoft.com/en-us/cpp/build/reference/md-mt-ld-use-run-time-library?view=vs-2019
    set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS_RELWITHDEBINFO
        CMAKE_C_FLAGS_MINSIZEREL
        CMAKE_CXX_FLAGS_MINSIZEREL
        CXX_FLAGS
        C_FLAGS
        )
    foreach(CompilerFlag ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
        message(STATUS "    CompilerFlag: ${${CompilerFlag}}")
    endforeach() 
    
    if(BUILD_WITH_DEBUG_INFO)
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DEBUG /OPT:REF /OPT:ICF")
        set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    /DEBUG /OPT:REF /OPT:ICF")
        set(CMAKE_CXX_FLAGS           "${CMAKE_CXX_FLAGS}           /Zi")
        set(CMAKE_C_FLAGS             "${CMAKE_C_FLAGS}             /Zi")
    endif()
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-rpath,.:lib:../lib -fpermissive")
endif()

include_directories(include)



pi_add_target(ivox3d SHARED src REQUIRED System Eigen3 PCL LTO)

target_link_libraries(ivox3d pcl_common)
pi_report_targets()