project (Rewriter)

enable_testing()

add_subdirectory(stream)
add_subdirectory(standalone)

add_executable(test_rewriteHTML test_rewriteHTML.cpp $<TARGET_OBJECTS:stream>)
add_test(test_rewriteHTML test_rewriteHTML)

add_executable(test_config test_config.cpp $<TARGET_OBJECTS:stream>)
set_property(TARGET test_config PROPERTY COMPILE_FLAGS -fno-access-control)
add_test(test_config test_config)
