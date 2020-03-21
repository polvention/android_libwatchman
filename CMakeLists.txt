set(src libusb.cpp)

add_library(libwatchman ${src})

#target_include_directories(libwatchman
#    PUBLIC
#    /usr/include/linux/
#    /usr/lib/llvm-9/lib/clang/9.0.0/include/
#    )

target_link_libraries(libwatchman
    libusb
    )

target_compile_options(libwatchamn PRIVATE ${COMPILE_FLAGS})

set_target_properties(
    libwatchman PROPERTIES
    CXX_CLANG_TIDY ${CLANG_TIDY_FLAGS}
)
