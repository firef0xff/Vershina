#define ADDRLEN         100    // Максимальная длина строки для адреса одного элемента

#define GR1BOOLITEMSNUM  39    // количество булевых переменных в группе 1
#define GR1INTITEMSNUM   11    // количество целых переменных в группе 1
#define GR1FLTITEMSNUM   13     // количество вещественных переменных в группе 1
#define GR1ITEMSNUM      GR1BOOLITEMSNUM+GR1INTITEMSNUM+GR1FLTITEMSNUM    // количество переменных в группе 1

#define GR2FLOATITEMSNUM 23    //количество вещественных переменных группе 2
#define GR2INTITEMSNUM	 2     // количество целых переменных в группе 2
#define GR2ITEMSNUM      GR2FLOATITEMSNUM+GR2INTITEMSNUM    // количество переменных в группе 2

#define GR3INTITEMSNUM    8    // количество целых переменных в группе 3
#define GR3FLTITEMSNUM   23    // количество вещественных переменных в группе 3
#define GR3ITEMSNUM      GR3INTITEMSNUM+GR3FLTITEMSNUM    // количество переменных в группе 3


#define GR41ITEMSNUM    250    // количество переменных в массиве 1 группы 4
#define GR42ITEMSNUM    100    // количество переменных в массиве 2 группы 4
#define GR4ITEMSNUM     GR41ITEMSNUM+GR42ITEMSNUM    // количество переменных в группе 4


#define GR51ITEMSNUM    250    // количество переменных в массиве 1 группы 5
#define GR52ITEMSNUM    100    // количество переменных в массиве 2 группы 5
#define GR5ITEMSNUM     GR51ITEMSNUM+GR52ITEMSNUM    // количество переменных в группе 5


#define GR6ITEMSNUM     200    // количество переменных в группе 6
#define GR7ARRAYSNUM      6    // количество массивов в группе 7
#define GR7ARRAYSIZE    250    // размер массивов в группе 7

#define GR81ITEMSNUM    250    // количество переменных в массиве 1 группы 8
#define GR82ITEMSNUM    100    // количество переменных в массиве 2 группы 8
#define GR8ITEMSNUM     GR81ITEMSNUM+GR82ITEMSNUM    // количество переменных в группе 8

#define GR91ITEMSNUM    250    // количество переменных в массиве 1 группы 9
#define GR92ITEMSNUM    100    // количество переменных в массиве 2 группы 9
#define GR9ITEMSNUM     GR91ITEMSNUM+GR92ITEMSNUM    // количество переменных в группе 9

#define GR10ITEMSNUM    200    // количество переменных в группе 10

#define GR11ARRAYSNUM     6    // количество массивов в группе 11
#define GR11ARRAYSIZE   250    // размер массивов в группе 11

#define GR12ITEMSNUM     80    // количество переменных в группе 12
#define GR12ARRAYSIZE    40    // количество переменных в массиве группы 12
#define GR13ITEMSNUM     80    // количество переменных в группе 13
#define GR13ARRAYSIZE    40    // количество переменных в массиве группы 13

#define MAXNUMOFSTEPS   100    // максимальное количество шагов программы испытаний
#define MAXNUMOFPOLLS   250    // максимальное количество опросов
// определение собственных сообщений
#define WM_LogPrint  WM_USER
#define WM_DataShow  WM_USER+1
#define WM_OPCCmd    WM_USER+2
// метки управления по переменной OPCCtrlStat
#define IDDLESTAT      0
#define READGR1        1
#define WRITEGR1ITEM   2
// метки управления для функции OnDataShow
#define COMMONPRMSHOW  0
// размеры таблиц для аттестации
#define VQTY          33
#define LDQTY         7
#define TQTY          20
#define RQTY          20
#define LDCQTY		  20
#define LOWTLIM      -50
#define UPPERTLIM    150

//настройки стенда
#define MIN_SPEED 0
#define MAX_SPEED 170
#define MIN_LOAD  0
#define MAX_LOAD  115
//дебаг
#ifdef _DEBUG
	  //#define  _mDEBUG
	  //#define    _NO_Write
#endif

//настройки
#define _NOS_SHOW_SEK   //заказчик решил что секунды ему ненужны во времени

#define DELAY_TIME 5000  //5 сек
#define USEPROCESSDELAY /*Включает задержку по времени для нормализации
						  //давления при аттестации и калибровке тензодатчика*/

// ограничители температуры
#define LOWTEMP   37
#define HIGHTTEMP 55
