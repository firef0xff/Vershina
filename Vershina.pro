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
   SQL/*.h\
   src/login/dialogs/*.h\
   src/splash_screen/*.h\
   src/support_functions/functoins.h\
   src/support_functions/print_support.h\

SOURCES +=\
   src/*.cpp\
   src/login/*.cpp\
   src/login/dialogs/*.cpp\
   src/splash_screen/*.cpp\
   src/support_functions/*.cpp\
   src/support_functions/print_support.cpp\
   SQL/*.cpp \

HEADERS +=\
   src/cpu/cpu_memory.h\
   src/cpu/data_block_base.h\
   src/cpu/data/gr1.h\
   src/cpu/data/gr2.h\
   src/cpu/data/gr3.h\
   src/cpu/data/gr4.h\
   src/cpu/data/gr5.h\
   src/cpu/data/gr6.h\
   src/cpu/data/gr7.h\
   src/cpu/data/gr8.h\
   src/cpu/data/gr9.h\
   src/cpu/data/gr10.h\
   src/cpu/data/gr11.h\
   src/cpu/data/gr12.h\
   src/cpu/data/gr13.h\
   src/cpu/data/common_params.h\
   src/cpu/si8/si8.h\
   src/support_functions/str_convert.h\
   src/support_functions/serialize.h\
   src/log/log.h\
   src/log/log_impl.h\
   src/sert/l_calibr.h\
   src/sert/l_sert.h \
   src/sert/v_sert.h \
   src/sert/t_sert.h \
   src/sert/r_sert.h \
   src/sert/TyreProt.h\
   src/pos/ui_pos.h \
   src/prg/time_programm.h\
   src/prg/path_programm.h \
   src/data_updater/data_updater.h\
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
   communication/buffer_tools.h\
   communication/swap_endian.h\
   date/date.h \
   src/support_functions/date_time.h \

SOURCES +=\
   src/cpu/cpu_memory.cpp\
   src/cpu/data/gr1.cpp\
   src/cpu/data/gr2.cpp\
   src/cpu/data/gr3.cpp\
   src/cpu/data/gr4.cpp\
   src/cpu/data/gr5.cpp\
   src/cpu/data/gr6.cpp\
   src/cpu/data/gr7.cpp\
   src/cpu/data/gr8.cpp\
   src/cpu/data/gr9.cpp\
   src/cpu/data/gr10.cpp\
   src/cpu/data/gr11.cpp\
   src/cpu/data/gr12.cpp\
   src/cpu/data/gr13.cpp\
   src/cpu/data/common_params.cpp\
   src/cpu/si8/si8.cpp\
   src/pos/ui_pos.cpp \
   src/support_functions/str_convert.cpp\
   src/support_functions/serialize.cpp\
   src/log/log.cpp\
   src/log/log_impl.cpp\
   src/sert/l_calibr.cpp\
   src/sert/l_sert.cpp\
   src/sert/v_sert.cpp\
   src/sert/t_sert.cpp\
   src/sert/r_sert.cpp\
   src/sert/TyreProt.cpp\
   src/prg/time_programm.cpp\
   src/prg/path_programm.cpp \
   src/data_updater/data_updater.cpp\
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
   src/support_functions/date_time.cpp \



OTHER_FILES +=\
   src/*.dfm\
   src/login/*.dfm\
   src/login/dialogs/*.dfm\
   src/splash_screen/*.dfm\
