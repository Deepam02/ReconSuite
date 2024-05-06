# Project configuration
QT += core gui concurrent network widgets # Add necessary Qt modules
CONFIG += c++17

# Uncomment the following line if you want to disable deprecated APIs
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Source files
SOURCES += \
    src/dig/dig.cpp \
    src/dnsenum/dnsenum.cpp \
    src/ffuf/ffuf.cpp \
    src/gui/gui.cpp \
    src/main.cpp \
    src/nmap/nmap.cpp \
    src/ping/ping.cpp \
    src/subfinder/subfinder.cpp \
    src/traceroute/traceroute.cpp \
    src/whois/whois.cpp \
    src/widget/widget.cpp

# Header files
HEADERS += \
    src/dig/dig.h \
    src/dnsenum/dnsenum.h \
    src/ffuf/ffuf.h \
    src/gui/gui.h \
    src/nmap/nmap.h \
    src/ping/ping.h \
    src/subfinder/subfinder.h \
    src/traceroute/traceroute.h \
    src/whois/whois.h \
    src/widget/widget.h

# UI files
FORMS += \
    src/dig/dig.ui \
    src/dnsenum/dnsenum.ui \
    src/ffuf/ffuf.ui \
    src/nmap/nmap.ui \
    src/ping/ping.ui \
    src/subfinder/subfinder.ui \
    src/traceroute/traceroute.ui \
    src/whois/whois.ui \
    src/widget/widget.ui

# Deployment rules
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Resource files
RESOURCES += \
    src/images/img.qrc
