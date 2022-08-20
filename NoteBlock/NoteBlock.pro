QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_folder_dialog.cpp \
    color_picker_dialog.cpp \
    main.cpp \
    main_dialog.cpp \
    options.cpp \
    options_dialog.cpp \
    options_dialog_utilities.cpp \
    options_menu_dialog.cpp \
    save_as_dialog.cpp

HEADERS += \
    add_folder_dialog.h \
    color_picker_dialog.h \
    main_dialog.h \
    options.h \
    options_dialog.h \
    options_dialog_utilities.h \
    options_menu_dialog.h \
    save_as_dialog.h

FORMS += \
    add_folder_dialog.ui \
    color_picker_dialog.ui \
    main_dialog.ui \
    options_dialog.ui \
    options_menu_dialog.ui \
    save_as_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
