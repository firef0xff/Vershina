#ifndef ui_posH
#define ui_posH
#pragma once
#include <string>
#include "src/sert/l_calibr.h"
#include "src/sert/l_sert.h"
#include "src/sert/r_sert.h"
#include "src/sert/t_sert.h"
#include "src/sert/v_sert.h"
#include "src/sert/TyreProt.h"

class UICommonData
{
public:
   std::string strDistProg = "";
   std::string strTimeProg = "";
   std::string strTitleProt = "";
   std::string strSpdCalibr = "";
   bool AutoSave = false;
};

class UIPosData
{
public:
   UIPosData( std::string const& tyre_type, std::string const& run_prog_name );
   ~UIPosData();

   // предидущий и текущий режим ручной/авто поз
   int OldMode = 0;
   int CurrMode = 0;

   // предидущий и текущий режим старт/стоп поз
   int OldSMode = 0;
   int CurrSMode = 0;

   int old_step = 0; // предидущий номер шага по поз
   int cur_step = 0; // текущий номер шага по поз

   float old_speed = 0.0; // предидущая скорость по поз
   float cur_speed = 0.0; // текущая скорость по поз

   int old_time = 0; // продолжительность предидущего шага поз
   int cur_time = 0; // продолжительность текущего шага поз


   float old_dist = 0.0; // путь на предидущем шаге поз
   float cur_dist = 0.0; // путь на текущем шаге поз
   float old_load = 0.0; // нагрузка на предидущем шаге поз
   float cur_load = 0.0; // нагрузка на текущем шаге поз
   float old_temp = 0.0; // температура на предидущем шаге поз
   float cur_temp = 0.0; // температура на текущем шаге поз
   float old_radius = 0.0; // радиус на предидущем шаге поз
   float cur_radius = 0.0; // радиус на текущем шаге поз

   bool CurrentStart = false; // Текущее состояние поз НА!!!!!!!!!!!!!!!!!!!
   bool switch_Carriage = false;

   std::string TyreType = "";
   std::string RunProgName = "";

   // настройки сохранения
   std::string strProt = "";
   std::string strLoadCalibr = "";
   std::string strTCalibr = "";
   std::string strRCalibr = "";
   std::string strSertPrintProt = "";

   //автосохранение
   bool needSave = false;
   bool in_save = false;

   Tyre mTyre;
   sert::LSert mLdS;
   sert::TSert mTS;
   sert::RSert mRS;
   sert::LCalibr mLdC;
};

#endif // UI_POS_H
