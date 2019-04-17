TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

# Define DEBUG flags
QMAKE_CXXFLAGS_DEBUG += -DDEBUG
QMAKE_CXXFLAGS_RELEASE -= -DDEBUG

SOURCES += \
    main.cpp \
    block.cpp \
    walker.cpp

HEADERS += \
    block.h \
    history.h \
    resources.h \
    walker.h

DISTFILES += \
    CMakeLists.txt
