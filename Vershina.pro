TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES +=__fastcall


INCLUDEPATH +=\
    ../../win_includes/vcl\
    ../../win_includes/rtl\
    ../../win_includes/crtl\
    ../../win_includes/sdk\
    classes\
    classes/COMPort\
    classes/net\
    RB001\
    RB001/login\
    RB001/login/dialogs\
    RB001/myOPC\
    RB001/CD9904/interface\
    RB001/CD9904/keypad\
    RB001/CD9904/protocol\
    RB001/CD9904/search_devices\
    RB001/CD9904/sensor_options\
    RB001/CD9904/support_functions\


HEADERS +=\
    classes/*.h\
    classes/COMPort/*.h\
    classes/net/*.h\
    RB001/*.h\
    RB001/login/*.h\
    RB001/login/dialogs/*.h\
    RB001/myOPC/*.h\
    RB001/CD9904/interface/*.h\
    RB001/CD9904/keypad/*.h\
    RB001/CD9904/protocol/*.h\
    RB001/CD9904/search_devices/*.h\
    RB001/CD9904/sensor_options/*.h\
    RB001/CD9904/support_functions/*.h\

SOURCES +=\
    classes/*.cpp\
    classes/COMPort/*.cpp\
    classes/net/*.cpp\
    RB001/*.cpp\
    RB001/*.c\
    RB001/login/*.cpp\
    RB001/login/dialogs/*.cpp\
    RB001/myOPC/*.cpp\
    RB001/CD9904/interface/*.cpp\
    RB001/CD9904/keypad/*.cpp\
    RB001/CD9904/protocol/*.cpp\
    RB001/CD9904/search_devices/*.cpp\
    RB001/CD9904/sensor_options/*.cpp\
    RB001/CD9904/support_functions/*.cpp\
