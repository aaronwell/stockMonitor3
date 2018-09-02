QT += qml quick network

win32|unix|macx {
    QT += widgets
    SOURCES +=
    HEADERS +=
}
# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    stockModel.cpp \
    stockProvider.cpp \
    stock.cpp


# Installation path
# target.path =

RESOURCES += \
    stockMonitor.qrc

android-g++ {
    LIBS += -lgnustl_shared
    QT += androidextras
    SOURCES +=
    HEADERS +=
}

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml \
    android/src/an/qt/stockMonitor/StockMonitorActivity.java

TRANSLATIONS = stockMonitor_zh.ts

HEADERS += \
    stockModel.h \
    stockProvider.h \
    stock.h

DISTFILES += \
    Debug/debug/getData.py



#针对无法打开corecrt.h的bug
INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.10240.0/ucrt"

win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64/' -lucrt
else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64/' -lucrtd
else:unix: LIBS += -L'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64/' -lucrt

INCLUDEPATH += 'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64'
DEPENDPATH += 'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64'

#加入python库
 INCLUDEPATH +=C:/Python27/include
 LIBS +=C:/Python27/libs/python27.lib

