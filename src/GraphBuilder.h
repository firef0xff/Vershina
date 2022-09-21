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
#include <mutex>
#include <map>
#include <vector>
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
   TLabel *xLabel;
   TImage *GraphArea;
   TComboBox *LinesList;
   void __fastcall FrameResize(TObject *Sender);

   void __fastcall Repaint(void);
   void __fastcall LinesListChange(TObject *Sender);
   void __fastcall GraphAreaMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
   void __fastcall Panel1MouseLeave(TObject *Sender);
   void __fastcall Panel1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
   void __fastcall Panel1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
   void __fastcall ScaleResetClick(TObject *Sender);
   void __fastcall ScaleDownXClick(TObject *Sender);
   void __fastcall ScaleUpXClick(TObject *Sender);


public:  // User declarations
   struct AxisLimits
   {
      double mMin = 0.0;
      double mMax = 0.0;
   };
   struct LinePoint
   {
      double mX;
      double mY;
   };


   void AddLine( UnicodeString const& name, TColor color, UnicodeString y_name, UnicodeString x_name );
   void AddLinePoint( UnicodeString const& name, LinePoint point );

   __fastcall TPlotter(TComponent* Owner);

   //устанавливают границы на отображаемые данные
   void SetLimits( AxisLimits x, AxisLimits y );
   void SetLimitsX( AxisLimits x );
   void SetLimitsY( AxisLimits y );

   //убирают ограничения на отображаемые данные
   //ограничения в этом случае берутся по данным
   void ClearLimits();
   void ClearLimitsX();
   void ClearLimitsY();

private:// User declarations
   struct Line
   {
      TColor mColor;
      AxisLimits mSelfLimitsX;
      AxisLimits mSelfLimitsY;
      AxisLimits mDrawingLimitsX;
      AxisLimits mDrawingLimitsY;

      double mMoveX = 0.0;
      double mMoveY = 0.0;

      std::unique_ptr< AxisLimits > mLimitsX;
      std::unique_ptr< AxisLimits > mLimitsY;
      UnicodeString mYname;
      UnicodeString mXname;
      double mLimitScale = 0.0;
      double x_scale = 0.0;
      double y_scale = 0.0;
      TRect mHolst;
      std::vector< LinePoint > mPoints;
   };

   void Draw();
   std::unique_ptr<TBitmap> DrawStandartGraph( int w, int h );

   void SetLimitsImpl( AxisLimits x, AxisLimits y );
   void SetLimitsXImpl( AxisLimits x );
   AxisLimits GetLimitsX();
   AxisLimits GetLimitsY();
   void ClearLimitsImpl();

   void DrawGrid( TCanvas* cnv, double x_center, double y_center );
   void DrawLine( TCanvas* cnv );
   void DrawSelection( TCanvas* cnv );

   double ScaleX( AxisLimits& x );
   double ScaleY( AxisLimits& y );
   TPoint HolstPoint( double x, double y );
   LinePoint RealPoint(double x, double y);
   double AxisValue( AxisLimits const& a, double scale );

   UnicodeString StringValue( double v );

   std::mutex mDataMutex;
   int mBorder; //отсутп от краев поля до начала графика (пикс)
   int mDistGrid; //расстояние между линиями сетки в пикселях
   int mMarkOfset; //расстояние от линии до текста подписи

   std::map< UnicodeString, Line > mLines;
   Line* mCurrentLine;

   struct SeletionState
   {
      TPoint mStartPoint;
      TPoint mEndPoint;
   };
   std::unique_ptr<SeletionState> mSelection;

   std::unique_ptr<TPoint> mMoveState;
};
//---------------------------------------------------------------------------
extern PACKAGE TPlotter *Plotter;
//---------------------------------------------------------------------------
#endif
