QT += testlib
QT += gui
QT += widgets

TARGET = tst_statisticsunittest

CONFIG += qt console
CONFIG -= app_bundle
CONFIG += c++14
CONFIG += depend_includepath

TEMPLATE = app

SOURCES +=  tst_statisticsunittest.cpp \
    ../Game/statistics.cpp

HEADERS += \
    ../Game/statistics.hh


INCLUDEPATH += \
    $$PWD/../Game


DEPENDPATH += \
    $$PWD/../Game


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += $$PWD/../Course/CourseLib
DEPENDPATH += $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Course/CourseLib/libCourseLib.a
