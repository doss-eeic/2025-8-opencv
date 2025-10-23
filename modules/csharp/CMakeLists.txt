# OpenCV C# Wrapper Module
set(the_description "C# Wrapper for OpenCV")

ocv_add_module(csharp opencv_core opencv_imgproc opencv_videoio opencv_highgui)

# Create the module
ocv_create_module()

# Add source files explicitly after module creation
target_sources(${the_module} PRIVATE csharp.cpp)

# Add include directories
target_include_directories(${the_module} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../imgproc/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../highgui/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../videoio/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../imgcodecs/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../calib3d/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../features2d/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../flann/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../dnn/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../ml/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../objdetect/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../photo/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../stitching/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../video/include
)

# Set module properties
set_target_properties(${the_module} PROPERTIES
    OUTPUT_NAME "opencv_csharp_wrapper${OPENCV_DLLVERSION}"
    DEBUG_POSTFIX "${OPENCV_DEBUG_POSTFIX}"
)

# Export symbols for DLL
if(WIN32 AND BUILD_SHARED_LIBS)
    set_target_properties(${the_module} PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
    )
endif()

# Export symbols for macOS
if(APPLE AND BUILD_SHARED_LIBS)
    # Override the global visibility settings
    target_compile_options(${the_module} PRIVATE "-fvisibility=default")
    # Use target_link_options for better compatibility
    target_link_options(${the_module} PRIVATE "-Wl,-exported_symbols_list,${CMAKE_CURRENT_SOURCE_DIR}/exported_symbols.txt")
    # Also set the property for compatibility
    set_target_properties(${the_module} PROPERTIES
        LINK_FLAGS "-Wl,-exported_symbols_list,${CMAKE_CURRENT_SOURCE_DIR}/exported_symbols.txt"
    )
endif()

# Install the module
install(TARGETS ${the_module}
    RUNTIME DESTINATION ${OPENCV_BIN_INSTALL_PATH} COMPONENT libs
    LIBRARY DESTINATION ${OPENCV_LIB_INSTALL_PATH} COMPONENT libs
    ARCHIVE DESTINATION ${OPENCV_LIB_INSTALL_PATH} COMPONENT libs
)

# Install headers
install(FILES csharp.hpp
    DESTINATION ${OPENCV_INCLUDE_INSTALL_PATH}/opencv2
    COMPONENT dev
)
