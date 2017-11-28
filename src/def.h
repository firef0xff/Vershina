#define STAND_NO "ОКА-6" //номер стенда для выовда в отчет и интерфейс


#define MAXNUMOFSTEPS   100    // максимальное количество шагов программы испытаний
#define MAXNUMOFPOLLS   250    // максимальное количество опросов


// размеры таблиц для аттестации
#define LOWTLIM      -50
#define UPPERTLIM    150

// настройки стенда
#define MIN_SPEED 0
#define MAX_SPEED 300
#define MIN_LOAD  0
#define MAX_LOAD  30
// дебаг
#ifdef _DEBUG
// #define  _mDEBUG
// #define    _NO_Write
#endif

#define DELAY_TIME 5000  //5 сек
#define USEPROCESSDELAY /*Включает задержку по времени для нормализации
// давления при аттестации и калибровке тензодатчика*/

// ограничители температуры
#define LOWTEMP   37
#define HIGHTTEMP 55

#ifndef SI8_PORT
#define SI8_PORT "COM3"
#endif
