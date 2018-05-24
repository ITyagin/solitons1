QT += widgets
QT += gui
QT += charts
QT += printsupport

QMAKE_EXTRA_TARGETS += before_build makefilehook

makefilehook.target = $(MAKEFILE)
makefilehook.depends = .beforebuild

PRE_TARGETDEPS += .beforebuild

before_build.target = .beforebuild
before_build.depends = FORCE
before_build.commands = chcp 1251

HEADERS += \
    graphwindow.h \
    advqchart.h \
    left_plotter.h \
    new_func.h

SOURCES += \
    main.cpp \
    graphwindow.cpp \
    advqchart.cpp \
    left_plotter.cpp
