// ---------------------------------------------------------------------------

#ifndef LoginH
#define LoginH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>

#include "SQL.h"
#include <memory>

#ifndef nullptr
#define nullptr 0
#endif

// ---------------------------------------------------------------------------
class TLogInwnd : public TForm
{
__published: // IDE-managed Components
   TComboBox *cbGroups;
   TEdit *eLog;
   TEdit *ePass;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TBitBtn *BitBtn2;
   TBitBtn *BitBtn1;

   void __fastcall BitBtn1Click(TObject *Sender);

private: // User declarations
      std::unique_ptr<cSQL>&DB;

   int opr_ind;
   bool Managment, // доступы
      Adjust, Work;

public: // User declarations
   __fastcall TLogInwnd(TComponent* Owner, std::unique_ptr<cSQL>& db);

   bool get_Managment(void) const
   {
      return Managment;
   }

   bool get_Adjust(void) const
   {
      return Adjust;
   }

   bool get_Work(void) const
   {
      return Work;
   }
};
#endif
