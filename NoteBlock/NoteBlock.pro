QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    color_picker_dialog.cpp \
    crypt_system.cpp \
    file_helper.cpp \
    main.cpp \
    main_dialog.cpp \
    msg_box_handler.cpp \
    open_file_dialog.cpp \
    options.cpp \
    options_dialog.cpp \
    options_menu_dialog.cpp \
    save_as_dialog.cpp \
    save_as_utilities.cpp

HEADERS += \
    color_picker_dialog.h \
    crypt_system.h \
    file_helper.h \
    main_dialog.h \
    msg_box_handler.h \
    open_file_dialog.h \
    options.h \
    options_dialog.h \
    options_menu_dialog.h \
    save_as_dialog.h \
    save_as_utilities.h

FORMS += \
    color_picker_dialog.ui \
    main_dialog.ui \
    open_file_dialog.ui \
    options_dialog.ui \
    options_menu_dialog.ui \
    save_as_dialog.ui \
    save_as_utilities.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
