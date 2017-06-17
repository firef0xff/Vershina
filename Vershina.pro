TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES +=__fastcall


INCLUDEPATH +=\

HEADERS +=\
   src/*.h\
   src/login/*.h\
   src/login/dialogs/*.h\
   src/opc/*.h\
   src/sert/*.h\
   src/splash_screen/*.h\
   src/support_functions/*.h\
   SQL/*.h\
   MD5/*.h\

SOURCES +=\
   src/*.cpp\
   src/login/*.cpp\
   src/login/dialogs/*.cpp\
   src/opc/*.c\
   src/opc/*.cpp\
   src/sert/*.cpp\
   src/splash_screen/*.cpp\
   src/support_functions/*.cpp\
   SQL/*.cpp\
   MD5/*.cpp\


OTHER_FILES +=\
   src/*.dfm\
   src/login/*.dfm\
   src/login/dialogs/*.dfm\
   src/splash_screen/*.dfm\
