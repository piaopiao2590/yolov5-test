QT       += core gui
QT += serialbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    modbus.cpp \
    widget.cpp \
    yolo_test.cpp \
    yolothread.cpp \
    yolov5.cpp

HEADERS += \
    modbus.h \
    widget.h \
    yolo_test.h \
    yolothread.h \
    yolov5.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L$$PWD/opencv/include/x64/vc16/lib/ -lopencv_world4100d

INCLUDEPATH += $$PWD/opencv/include/opencv2 \
                $$PWD/opencv/include

DEPENDPATH += $$PWD/opencv/include/opencv2 \
                $$PWD/opencv/include

g++: PRE_TARGETDEPS += $$PWD/opencv/include/x64/vc16/lib/opencv_world4100d.lib
