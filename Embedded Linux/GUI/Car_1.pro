QT += quick qml #Qt config using the Qt Quick and QML modules.
QT += svg

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        radialbar.cpp

RESOURCES += qml.qrc  #QRC files are used to specify external resources such as QML files, images, etc., to be included in the application

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
#QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin    #for the QNX platform. It sets the target path for the binary files.
else: unix:!android: target.path = /opt/$${TARGET}/bin   #deployment rules for Unix platforms other than Android. It sets the target path for the binary files.
!isEmpty(target.path): INSTALLS += target   #specifies the installation process. If the target path is not empty, it installs the target.

HEADERS += \
        radialbar.h
