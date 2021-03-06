TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG -= no-pkg-config

# Define DEBUG flags
QMAKE_CXXFLAGS_DEBUG += -DDEBUG 
QMAKE_CXXFLAGS_RELEASE -= -DDEBUG 

SOURCES += \
    main.cpp \
    block.cpp \
    walker.cpp \
    history.cpp \
    Wlk_Resources.cpp \

HEADERS += \
    adjustidsOut.h \
    block.h \
    history.h \
    resources.h \
    walker.h \
    Wlk_Resources.h

DISTFILES += \
    CMakeLists.txt

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libconfig++
