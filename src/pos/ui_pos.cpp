#include "ui_pos.h"


UIPosData::UIPosData( std::string const& tyre_type, std::string const& run_prog_name ):
   TyreType( tyre_type ),
   RunProgName( run_prog_name ),
   mTyre(tyre_type),
   mLdS(tyre_type),
   mTS(tyre_type),
   mRS(tyre_type),
   mLdC(tyre_type)
{}
UIPosData::~UIPosData()
{}
