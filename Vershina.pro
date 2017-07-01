TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES +=__fastcall\
          DEMO


INCLUDEPATH += OPC\

HEADERS +=\
   src/*.h\
   src/cpu/cpu_memory.h\
   src/cpu/data_block_base.h\
   src/cpu/data/gr1.h\
   src/cpu/data/gr2.h\
   src/login/*.h\
   src/login/dialogs/*.h\
   src/opc/*.h\
   src/sert/*.h\
   src/splash_screen/*.h\
   src/support_functions/*.h\
   SQL/*.h\
   MD5/*.h\
   OPC/opc.h\
   OPC/miniOPC.h\
   OPC/impl/*.h\
   OPC/impl/cache/*.h\
   COMPort/*.h\

SOURCES +=\
   src/*.cpp\
   src/login/*.cpp\
   src/login/dialogs/*.cpp\
   src/cpu/cpu_memory.cpp\
   src/cpu/data/gr1.cpp\
   src/cpu/data/gr2.cpp\
   src/opc/*.c\
   src/opc/*.cpp\
   src/sert/*.cpp\
   src/splash_screen/*.cpp\
   src/support_functions/*.cpp\
   SQL/*.cpp\
   MD5/*.cpp\
   OPC/opc_i.c\
   OPC/impl/*.cpp\
   OPC/impl/cache/*.cpp\
   COMPort/*.cpp\


OTHER_FILES +=\
   src/*.dfm\
   src/login/*.dfm\
   src/login/dialogs/*.dfm\
   src/splash_screen/*.dfm\
