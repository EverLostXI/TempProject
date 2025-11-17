cmake_minimum_required(VERSION 3.16)

project(qt_chat_client VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)
qt_standard_project_setup()

# Add source files
set(SOURCES
    main.cpp
    src/loginwindow.cpp
    src/chatwindow.cpp
    src/user.cpp
    src/message.cpp
    src/contactlistmodel.cpp
)

# Add header files
set(HEADERS
    include/loginwindow.h
    include/chatwindow.h
    include/user.h
    include/message.h
    include/contactlistmodel.h
)

# Add UI files
set(UIS
    ui/loginwindow.ui
    ui/chatwindow.ui
)

# Create Qt resources
set(RESOURCES
    resources.qrc
)

# Process UI files
qt6_wrap_ui(UI_HEADERS ${UIS})

# Process resource files
qt6_add_resources(RESOURCE_FILES ${RESOURCES})

# Create executable
qt6_add_executable(qt_chat_client
    ${SOURCES}
    ${HEADERS}
    ${UI_HEADERS}
    ${RESOURCE_FILES}
)

# Link Qt libraries
target_link_libraries(qt_chat_client PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
)

# Include directories
target_include_directories(qt_chat_client PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}  # For UI headers
)

# Set properties
set_target_properties(qt_chat_client PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
