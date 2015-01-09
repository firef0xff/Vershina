//---------------------------------------------------------------------------


#pragma hdrstop

#include "CD_9904_interface.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
					CD_9904_interface::CD_9904_interface	(TComponent* Owner):settings(0)
{
	if (!count)
	{
		count++;
		settings=new TSettings(Owner);
	}else
	{
		throw Exception("Можно подключить только одно устройство");
	}
}
					CD_9904_interface::~CD_9904_interface	(void)
{
	delete settings;
	count--;
}
CD_9904::Sensor * 	CD_9904_interface::Sensor			(void)
{
	if (settings)
	{
		return settings->Get_Sensor();
	}else
	{
    	return 0;
	}
}
void				CD_9904_interface::Set_Settings		(void)
{
	if (settings)
	{
		settings->ShowModal();
	}
}
void				CD_9904_interface::Set_def_settings	(void)
{
	if (settings)
	{
		settings->Set_DefaultSettings();
	}
}
void				CD_9904_interface::Connect			(void)
{
	if (settings)
	{
		settings->Connect();
	}
}
void				CD_9904_interface::ResetBus_1 		(void)
{
	if (settings)
	{
		settings->ResetBus_1();
	}
}
void				CD_9904_interface::ResetBus_2 		(void)
{
	if (settings)
	{
		settings->ResetBus_2();
	}
}
