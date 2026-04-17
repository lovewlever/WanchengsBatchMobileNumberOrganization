cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(WanchengsBatchMobileNumberOrganization VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)

include_directories(include)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appWanchengsBatchMobileNumberOrganization
    main.cpp
)

qt_add_qml_module(appWanchengsBatchMobileNumberOrganization
    URI WanchengsBatchMobileNumberOrganization
    QML_FILES
        Main.qml
        QML_FILES UnionButton.qml
        SOURCES include/theme.h src/theme.cpp
        RESOURCES sources.qrc
        SOURCES include/InstanceTheme.h src/InstanceTheme.cpp
        SOURCES include/PhoneNumberImportrer.h src/PhoneNumberImportrer.cpp
        SOURCES include/PhoneNumberListModel.h src/PhoneNumberListModel.cpp
        SOURCES include/CSVPhoneLocationLoader.h src/CSVPhoneLocationLoader.cpp
        SOURCES include/Structs.h src/Structs.cpp
        SOURCES include/TextFileLoader.h src/TextFileLoader.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appWanchengsBatchMobileNumberOrganization PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appWanchengsBatchMobileNumberOrganization
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appWanchengsBatchMobileNumberOrganization
    PRIVATE Qt6::Quick Qt6::QuickControls2
)

install(TARGETS appWanchengsBatchMobileNumberOrganization
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
