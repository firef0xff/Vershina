//---------------------------------------------------------------------------

#ifndef CD_9904_interfaceH
#define CD_9904_interfaceH

#include "Set_settings.h"
#include <thread>
#include <memory>
class CD_9904_interface
{
public:
						CD_9904_interface	(TComponent* Owner);
						~CD_9904_interface	(void);
	CD_9904::Sensor * 	Sensor				(void);
	void				Set_Settings		(void);
	void				Set_def_settings	(void);
	void				Connect				(void);
	void				ResetBus_1 			(void);
	void				ResetBus_2 			(void);
private:
	std::shared_ptr<TSettings> settings;
	static size_t count;
};
size_t CD_9904_interface::count=0;
#endif
