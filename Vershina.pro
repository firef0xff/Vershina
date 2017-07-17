TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES +=__fastcall\
          DEMO



INCLUDEPATH += OPC\
               communication/owen\

HEADERS +=\
   src/*.h\
   src/login/*.h\
   src/opc/*.h\
   src/sert/*.h\
   SQL/*.h\

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

HEADERS +=\
   src/cpu/cpu_memory.h\
   src/cpu/data_block_base.h\
   src/cpu/data/gr1.h\
   src/cpu/data/gr2.h\
   src/cpu/data/gr3.h\
   src/cpu/data/gr4.h\
   src/cpu/data/gr5.h\
   src/cpu/data/gr6.h\
   src/cpu/data/gr8.h\
   src/cpu/data/gr9.h\
   src/cpu/data/gr10.h\
   src/cpu/data/gr12.h\
   src/cpu/data/gr13.h\
   src/login/dialogs/*.h\
   src/splash_screen/*.h\
   src/support_functions/*.h\
   MD5/MD5.h\
   OPC/opc.h\
   OPC/miniOPC.h\
   OPC/impl/demo_mode.h\
   OPC/impl/sync_thread.h\
   OPC/impl/types.h\
   OPC/impl/win_ole_mode.h\
   OPC/impl/cache/cache.h\
   OPC/impl/cache/def_opc.h\
   OPC/impl/cache/memory.h\
   COMPort/ComPort.h\
   communication/owen/owen_command.h\
   communication/owen/owen_data_element.h\
   communication/owen/owen_paskage.h\
   communication/owen/types/owen_time.h\
   communication/owen/types/owen_float.h\
   communication/owen/types/owen_int_types.h\
   communication/owen/types/owen_string.h\
   communication/owen/funcs/owen_read.h\
   communication/owen/funcs/owen_write.h\
   communication/buffer_tools.h
   communication/swap_endian.h

SOURCES +=\
   src/cpu/cpu_memory.cpp\
   src/cpu/data/gr1.cpp\
   src/cpu/data/gr2.cpp\
   src/cpu/data/gr3.cpp\
   src/cpu/data/gr4.cpp\
   src/cpu/data/gr5.cpp\
   src/cpu/data/gr6.cpp\
   src/cpu/data/gr8.cpp\
   src/cpu/data/gr9.cpp\
   src/cpu/data/gr10.cpp\
   src/cpu/data/gr12.cpp\
   src/cpu/data/gr13.cpp\
   MD5/MD5.cpp\
   OPC/opc_i.c\
   OPC/impl/demo_mode.cpp\
   OPC/impl/sync_thread.cpp\
   OPC/impl/win_ole_mode.cpp\
   OPC/impl/cache/memory.cpp\
   COMPort/ComPort.cpp\
   communication/owen/owen_command.cpp\
   communication/owen/owen_paskage.cpp\
   communication/owen/types/owen_time.cpp\
   communication/owen/types/owen_float.cpp\
   communication/owen/types/owen_int_types.cpp\
   communication/owen/types/owen_string.cpp\
   communication/owen/funcs/owen_read.cpp\
   communication/owen/funcs/owen_write.cpp\


OTHER_FILES +=\
   src/*.dfm\
   src/login/*.dfm\
   src/login/dialogs/*.dfm\
   src/splash_screen/*.dfm\
