//---------------------------------------------------------------------------

#ifndef GraphBuilderH
#define GraphBuilderH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <memory>
//---------------------------------------------------------------------------
class TPlotter : public TFrame
{
__published:	// IDE-managed Components
   TSpeedButton *ScaleUpY;
   TSpeedButton *ScaleDownY;
   TSpeedButton *ScaleUpX;
   TSpeedButton *ScaleDownX;
   TSpeedButton *ScaleReset;
   TPanel *Panel1;
   TComboBox *ValuesX;
   TComboBox *ValuesY;
   TLabel *Label1;
   TLabel *Label2;
   TImage *GraphArea;
   void __fastcall FrameResize(TObject *Sender);

   void __fastcall Repaint(void);
private:	// User declarations
   void Draw();
   std::unique_ptr<TBitmap> DrawStandartGraph( int w, int h );
public:		// User declarations
   __fastcall TPlotter(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPlotter *Plotter;
//---------------------------------------------------------------------------
#endif
