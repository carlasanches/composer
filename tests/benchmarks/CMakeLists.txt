#######################################################
### Google benchmark                                ###
#######################################################
CPMAddPackage(
        NAME benchmark
        GITHUB_REPOSITORY google/benchmark
        VERSION 1.5.1
        OPTIONS
        "BENCHMARK_ENABLE_TESTING Off"
        "LLVMAR_EXECUTABLE ON"
        "LLVMNM_EXECUTABLE ON"
        "LLVMRANLIB_EXECUTABLE ON"
        "GCC_AR ON"
        "GCC_RANLIB ON"
        "BENCHMARK_ENABLE_INSTALL OFF"
)

if (benchmark_ADDED)
    # patch google benchmark target
    set_target_properties(benchmark PROPERTIES CXX_STANDARD 17)
    target_compile_definitions(benchmark PUBLIC -DNDEBUG)
endif()

#######################################################
### Composer benchmarks                             ###
#######################################################
# run with "--benchmark_repetitions=30 --benchmark_display_aggregates_only=true --benchmark_out=melody_benchmark.csv --benchmark_out_format=csv"
add_executable(melody_benchmark melody_benchmark.cpp)
target_link_libraries(melody_benchmark PUBLIC composerlib benchmark)
if (BUILD_LONG_TESTS)
    target_compile_definitions(melody_benchmark PUBLIC BUILD_LONG_TESTS)
endif()
if (MSVC)
    # Allow MSVC to compile such a large code
    target_compile_options(melody_benchmark PRIVATE /bigobj)
    # MSVC requires this flag if the code uses C++ exception handling
    target_compile_options(melody_benchmark PRIVATE /EHsc)
endif()