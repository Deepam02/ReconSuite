QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dig.cpp \
    dnsenum.cpp \
    main.cpp \
    nmap.cpp \
    nslookup.cpp \
    ping.cpp \
    subfinder.cpp \
    traceroute.cpp \
    whois.cpp \
    widget.cpp

HEADERS += \
    dig.h \
    dnsenum.h \
    nmap.h \
    nslookup.h \
    ping.h \
    subfinder.h \
    traceroute.h \
    whois.h \
    widget.h

FORMS += \
    dig.ui \
    dnsenum.ui \
    nmap.ui \
    nslookup.ui \
    ping.ui \
    subfinder.ui \
    traceroute.ui \
    whois.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
