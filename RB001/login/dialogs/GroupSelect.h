//---------------------------------------------------------------------------

#ifndef GroupSelectH
#define GroupSelectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "SQL.h"
#include <Buttons.hpp>

#ifndef nullptr
	#define nullptr 0
#endif
//---------------------------------------------------------------------------
class TfselGroup : public TForm
{
__published:	// IDE-managed Components
	TComboBox *cbGroups;
	TLabel *Label3;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn1;
private:	// User declarations
	cSQL *DB;
public:		// User declarations
	__fastcall TfselGroup(TComponent* Owner,cSQL *db);
};

#endif
