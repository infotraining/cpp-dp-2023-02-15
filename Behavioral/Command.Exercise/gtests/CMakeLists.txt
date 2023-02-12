set(PROJECT_GTESTS ${TARGET_MAIN}_google_tests)
message(STATUS "PROJECT_GTESTS is: " ${PROJECT_GTESTS})

project(${PROJECT_GTESTS} CXX)

find_package(GTest CONFIG REQUIRED)

file(GLOB TEST_SOURCES *_tests.cpp *_test.cpp)

add_executable(${PROJECT_GTESTS} ${TEST_SOURCES})
target_compile_features(${PROJECT_GTESTS} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_GTESTS} PRIVATE ${PROJECT_LIB} GTest::gtest GTest::gmock)

enable_testing()        
add_test(AllTestsInMain ${PROJECT_GTESTS})
