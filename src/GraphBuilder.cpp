// ---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "GraphBuilder.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPlotter *Plotter;

// ---------------------------------------------------------------------------
__fastcall TPlotter::TPlotter(TComponent* Owner) : TFrame(Owner), mBorder(5),
   mDistGrid(50), mMarkOfset(5),mCurrentLine(nullptr)
{
}

void TPlotter::AddLine( UnicodeString const& name, TColor color, UnicodeString y_name, UnicodeString x_name )
{
   std::unique_lock<std::mutex>lock(mDataMutex);
   auto& line = mLines[name];
   line.mColor = color;
   line.mYname = std::move(y_name);
   line.mXname = std::move(x_name);
   LinesList->Items->Clear();
   LinesList->Text = L"";
   for (auto it = mLines.begin(), end = mLines.end(); it != end; ++it)
   {
      LinesList->Items->Add(it->first);
   }
   LinesList->ItemIndex = 0;
   mCurrentLine = &mLines[LinesList->Text];
   ClearLimitsImpl();
   Draw();
}
void TPlotter::AddLinePoint( UnicodeString const& name, LinePoint point )
{
   std::unique_lock<std::mutex>lock(mDataMutex);
   auto& line = mLines[name];
   if( line.mPoints.empty() )
   {
      line.mSelfLimitsX.mMax = point.mX;
      line.mSelfLimitsX.mMin = point.mX;
      line.mSelfLimitsY.mMax = point.mY;
      line.mSelfLimitsY.mMin = point.mY;
   }
   line.mSelfLimitsX.mMax = point.mX > line.mSelfLimitsX.mMax ? point.mX : line.mSelfLimitsX.mMax;
   line.mSelfLimitsY.mMax = point.mY > line.mSelfLimitsY.mMax ? point.mY : line.mSelfLimitsY.mMax;
   line.mSelfLimitsX.mMin = point.mX < line.mSelfLimitsX.mMin ? point.mX : line.mSelfLimitsX.mMin;
   line.mSelfLimitsY.mMin = point.mY < line.mSelfLimitsY.mMin ? point.mY : line.mSelfLimitsY.mMin;

   line.mPoints.emplace_back( std::move(point) );

   if( mCurrentLine == &line && !mSelection && !mMoveState )
   {
      lock.unlock();
      Repaint();
   }
}

void TPlotter::SetLimits(AxisLimits x, AxisLimits y)
{
   std::unique_lock<std::mutex>lock(mDataMutex);
   SetLimitsImpl( x ,y );
}
void TPlotter::SetLimitsImpl( AxisLimits x, AxisLimits y )
{
   if(!mCurrentLine)
      return;
   mCurrentLine->mLimitsX = std::make_unique<AxisLimits>(std::move(x));
   mCurrentLine->mLimitsY = std::make_unique<AxisLimits>(std::move(y));
}
void TPlotter::SetLimitsX(AxisLimits x)
{
   std::unique_lock<std::mutex>lock(mDataMutex);
   SetLimitsXImpl( x );
}
void TPlotter::SetLimitsXImpl( AxisLimits x )
{
   if(!mCurrentLine)
      return;
   mCurrentLine->mLimitsX = std::make_unique<AxisLimits>(std::move(x));
}

void TPlotter::SetLimitsY(AxisLimits y)
{
   std::unique_lock<std::mutex>lock(mDataMutex);
   if(!mCurrentLine)
      return;
   mCurrentLine->mLimitsY = std::make_unique<AxisLimits>(std::move(y));
}

void TPlotter::ClearLimits()
{
   std::unique_lock<std::mutex>lock(mDataMutex);
   ClearLimitsImpl();
}
void TPlotter::ClearLimitsImpl()
{
   if(!mCurrentLine)
      return;
   mCurrentLine->mLimitsY.reset();
   mCurrentLine->mLimitsX.reset();
   mCurrentLine->mMoveX = 0;
   mCurrentLine->mMoveY = 0;
}

void TPlotter::ClearLimitsX()
{
   std::unique_lock<std::mutex>lock(mDataMutex);
   if(!mCurrentLine)
      return;
   mCurrentLine->mLimitsX.reset();
}
void TPlotter::ClearLimitsY()
{
   std::unique_lock<std::mutex>lock(mDataMutex);
   if(!mCurrentLine)
      return;
   mCurrentLine->mLimitsY.reset();
}

TPlotter::AxisLimits TPlotter::GetLimitsX()
{
   if ( mCurrentLine )
   {
      if (mCurrentLine->mLimitsX)
         return *mCurrentLine->mLimitsX;
      return mCurrentLine->mSelfLimitsX;
   }
   AxisLimits res;
   res.mMax = 10;
   res.mMin = -10;
   return res;
}
TPlotter::AxisLimits TPlotter::GetLimitsY()
{
   if (mCurrentLine)
   {
      if (mCurrentLine->mLimitsY)
         return *mCurrentLine->mLimitsY;
      return mCurrentLine->mSelfLimitsY;
   }
   AxisLimits res;
   res.mMax = 10;
   res.mMin = -10;
   return res;
}

void __fastcall TPlotter::Repaint(void)
{
   std::unique_lock<std::mutex>lock(mDataMutex);
   TFrame::Repaint();
   Draw();
}

void TPlotter::Draw()
{
   auto rect = GraphArea->ClientRect;
   auto w = rect.Width();
   auto h = rect.Height();
   std::unique_ptr<TBitmap>bmp;
   bmp = DrawStandartGraph(w, h);
   if( !bmp )
      return;
   GraphArea->Picture->Bitmap->Width = bmp->Width;
   GraphArea->Picture->Bitmap->Height = bmp->Height;
   GraphArea->Canvas->Draw(0, 0, bmp.get());
}

double Aproximate(double val)
{
   if (val == 0.0) {
      return val;
   }

   auto l = floor(log10(abs(val)));
   auto p = ceil(pow(10.0, -1 * l) * abs(val) ) * pow(10.0, l);

   return val > 0 ? p : -1 *p;
}

void TPlotter::DrawGrid( TCanvas* cnv, double x_center, double y_center )
{
   double x_step = mCurrentLine->x_scale * mDistGrid;
   double y_step = mCurrentLine->y_scale * mDistGrid;

   TPoint center = HolstPoint(x_center, y_center);

   auto x_label_rect = [&]( int x, int y, TSize const& text_size )
   {
      TRect r(x - text_size.Width / 2, y + mMarkOfset,
              x + text_size.Width / 2 + 1,
              y + mMarkOfset + text_size.Height);
      return r;
   };
   auto y_label_rect = [&]( int x, int y, TSize const& text_size )
   {
      TRect r(x - mMarkOfset - text_size.Width,
            y - text_size.Height / 2, x + text_size.Width,
            y + text_size.Height / 2 + 1);
      return r;
   };
   // Сетка по оси x
   // осевая линия
   {
      if( x_center == 0.0 )
      {
        cnv->Pen->Color = clBlack;
        cnv->Pen->Width = 2;
      }
      else
      {
         cnv->Pen->Color = clGray;
         cnv->Pen->Width = 1;
      }
      cnv->MoveTo(center.X, mCurrentLine->mHolst.top);
      cnv->LineTo(center.X, mCurrentLine->mHolst.bottom);
   }

   {
      // линии сетки
      cnv->Pen->Color = clGray;
      cnv->Pen->Width = 1;
      for (int pos = center.X + mDistGrid; pos < mCurrentLine->mHolst.right; pos += mDistGrid)
      {
         cnv->MoveTo(pos, mCurrentLine->mHolst.top);
         cnv->LineTo(pos, mCurrentLine->mHolst.bottom);
      }
      for (int pos = center.X - mDistGrid; pos > mCurrentLine->mHolst.left; pos -= mDistGrid)
      {
         cnv->MoveTo(pos, mCurrentLine->mHolst.top);
         cnv->LineTo(pos, mCurrentLine->mHolst.bottom);
      }
   }

   // Сетка по оси y
   {
      // осевая линия
      {
         if( y_center == 0.0 )
         {
           cnv->Pen->Color = clBlack;
           cnv->Pen->Width = 2;
         }
         else
         {
            cnv->Pen->Color = clGray;
            cnv->Pen->Width = 1;
         }
         cnv->MoveTo( mCurrentLine->mHolst.left, center.Y );
         cnv->LineTo( mCurrentLine->mHolst.right, center.Y );
      }
      // линии сетки
      {
         cnv->Pen->Color = clGray;
         cnv->Pen->Width = 1;
         for (int pos = center.Y + mDistGrid; pos < mCurrentLine->mHolst.bottom; pos += mDistGrid)
         {
            cnv->MoveTo(mCurrentLine->mHolst.left, pos);
            cnv->LineTo(mCurrentLine->mHolst.right, pos);
         }
         for (int pos = center.Y - mDistGrid; pos > mCurrentLine->mHolst.top; pos -= mDistGrid)
         {
            cnv->MoveTo(mCurrentLine->mHolst.left, pos);
            cnv->LineTo(mCurrentLine->mHolst.right, pos);
         }
      }
   }
   //легенда
   {
      //линии легенды
      cnv->Pen->Color = clBlack;
      cnv->Pen->Width = 1;
      cnv->MoveTo(mCurrentLine->mHolst.left, mCurrentLine->mHolst.bottom);
      cnv->LineTo(mCurrentLine->mHolst.left, mCurrentLine->mHolst.top);
      cnv->MoveTo(mCurrentLine->mHolst.left, mCurrentLine->mHolst.bottom);
      cnv->LineTo(mCurrentLine->mHolst.right, mCurrentLine->mHolst.bottom);
      //узел
      UnicodeString s = StringValue(x_center);
      auto text_size = cnv->TextExtent(s);
      TRect r = x_label_rect( center.X, mCurrentLine->mHolst.bottom, text_size );
      cnv->TextRect(r, s);

      //ось Х
      double x_val = x_center + x_step;
      for (int pos = center.X + mDistGrid; pos < mCurrentLine->mHolst.right; pos += mDistGrid)
      {
         UnicodeString s = StringValue(x_val);
         auto text_size = cnv->TextExtent(s);
         TRect r = x_label_rect( pos, mCurrentLine->mHolst.bottom, text_size );
         cnv->TextRect(r, s);
         x_val += x_step;
      }
      x_val = x_center - x_step;
      for (int pos = center.X - mDistGrid; pos > mCurrentLine->mHolst.left; pos -= mDistGrid)
      {
         UnicodeString s = StringValue(x_val);
         auto text_size = cnv->TextExtent(s);
         TRect r = x_label_rect( pos, mCurrentLine->mHolst.bottom, text_size );
         cnv->TextRect(r, s);
         x_val -= x_step;
      }
      //ось Y
      s = StringValue(y_center);
      text_size = cnv->TextExtent(s);
      r = y_label_rect( mCurrentLine->mHolst.left, center.Y, text_size );
      cnv->TextRect(r, s);
      double y_val = y_center - y_step;
      for (int pos = center.Y + mDistGrid; pos < mCurrentLine->mHolst.bottom; pos += mDistGrid)
      {
         UnicodeString s = StringValue(y_val);
         auto text_size = cnv->TextExtent(s);
         TRect r = y_label_rect( mCurrentLine->mHolst.left, pos, text_size );
         cnv->TextRect(r, s);
         y_val -= y_step;
      }
      y_val = y_center + y_step;
      for (int pos = center.Y - mDistGrid; pos > mCurrentLine->mHolst.top; pos -= mDistGrid)
      {
         UnicodeString s = StringValue(y_val);
         auto text_size = cnv->TextExtent(s);
         TRect r = y_label_rect( mCurrentLine->mHolst.left, pos, text_size );
         cnv->TextRect(r, s);
         y_val += y_step;
      }
   }
   //название осей
   {
      auto text_size = cnv->TextExtent(mCurrentLine->mYname);
      TRect r(
         mCurrentLine->mHolst.left + mMarkOfset, mCurrentLine->mHolst.top,
         mCurrentLine->mHolst.left + mMarkOfset +text_size.Width, mCurrentLine->mHolst.top + text_size.Height
         );

      cnv->TextRect(r, mCurrentLine->mYname);

      text_size = cnv->TextExtent(mCurrentLine->mXname);
      TRect r1(
         mCurrentLine->mHolst.right - text_size.Width, mCurrentLine->mHolst.bottom - mMarkOfset - text_size.Height,
         mCurrentLine->mHolst.right, mCurrentLine->mHolst.bottom - mMarkOfset
         );

      cnv->TextRect(r1, mCurrentLine->mXname);
   }
}

void TPlotter::DrawLine( TCanvas* cnv )
{
   if (!mCurrentLine)
      return;
   cnv->Pen->Color = mCurrentLine->mColor;
   cnv->Pen->Width = 2;
   int r = 3;
   bool first = true;
   for (auto it = mCurrentLine->mPoints.begin(), end = mCurrentLine->mPoints.end(); it != end; ++it)
   {
      if( mCurrentLine->mDrawingLimitsX.mMin > it->mX ||
          mCurrentLine->mDrawingLimitsX.mMax < it->mX ||
          mCurrentLine->mDrawingLimitsY.mMin > it->mY ||
          mCurrentLine->mDrawingLimitsY.mMax < it->mY )
      {
         first = true;
         continue;
      }
      TPoint point = HolstPoint(it->mX, it->mY);
      if (first)
      {
         cnv->MoveTo(point.X, point.Y);
         first = false;
      }
      else
      {
//         cnv->Pen->Width = 2;
         cnv->LineTo( point.X, point.Y );
      }
//      cnv->Pen->Width = 1;
//      cnv->Ellipse( point.X + r, point.Y + r , point.X - r, point.Y - r );
   }
}

void TPlotter::DrawSelection( TCanvas* cnv )
{
   if( !mSelection )
      return;
   cnv->Pen->Color = clBlue;
   cnv->Pen->Width = 1;
   cnv->Pen->Style = psDot;
   cnv->Brush->Style = bsClear;

   cnv->MoveTo( mSelection->mStartPoint.X, mSelection->mStartPoint.Y );
   cnv->Rectangle( mSelection->mStartPoint.X, mSelection->mStartPoint.Y, mSelection->mEndPoint.X, mSelection->mEndPoint.Y );
}

// Коэффициент масштабирования по X (количество длинны в одном пикселе)
double TPlotter::ScaleX(AxisLimits& x)
{
   if( !mCurrentLine )
      return 1;
   // масштаб в "лоб"
   double scale = (x.mMax - x.mMin) / (mCurrentLine->mHolst.Width());
   // смотрим какой получилась величина шага сетки
   double grid_step = scale * mDistGrid;
   // хотим чтобы шаг сетки был "красывым" кратным 10, округляем в большую сторону

   //нужно взять ближайшее значение из 2 5 10
   auto l = floor(log10(abs(grid_step)));
   int p = ceil(pow(10.0, -1 * l) * abs(grid_step) );
   p = p <= 2 ? 2 : p <= 5 ? 5 : 10;
   auto r = pow(10.0, l);
   grid_step = p * r;
   // пересчитываем scale
   scale = grid_step / mDistGrid;
   double delta = scale * mCurrentLine->mHolst.Width() - (x.mMax - x.mMin);
   x.mMax += delta / 2;
   x.mMin -= delta / 2;

   return scale;
}

// Коэффициент масштабирования по Y
double TPlotter::ScaleY(AxisLimits& y)
{
   if( !mCurrentLine )
      return 1;
   // масштаб в "лоб"
   double scale = (y.mMax - y.mMin) / (mCurrentLine->mHolst.Height());
   // смотрим какой получилась величина шага сетки
   double grid_step = scale * mDistGrid;
   // хотим чтобы шаг сетки был "красывым" кратным 10, округляем в большую сторону
   //нужно взять ближайшее значение из 2 5 10
   auto l = floor(log10(abs(grid_step)));
   int p = ceil(pow(10.0, -1 * l) * abs(grid_step) );
   p = p <= 2 ? 2 : p <= 5 ? 5 : 10;
   auto r = pow(10.0, l);
   grid_step = p * r;
   // пересчитываем scale
   scale = grid_step / mDistGrid;
   double delta = scale * mCurrentLine->mHolst.Height() - (y.mMax - y.mMin);
   y.mMax += delta / 2;
   y.mMin -= delta / 2;

   return scale;
}

TPoint TPlotter::HolstPoint(double x, double y)
{
   // Переводим координаты точки диапазона в координакты графика
   TPoint res;

   double dx = (x - mCurrentLine->mDrawingLimitsX.mMin) / mCurrentLine->x_scale;
   double dy = (y - mCurrentLine->mDrawingLimitsY.mMin) / mCurrentLine->y_scale;

   res.x = mCurrentLine->mHolst.Left + dx;
   res.y = mCurrentLine->mHolst.Bottom - dy;
   return res;
}

double TPlotter::AxisValue(AxisLimits const & a, double scale)
{
   double point = 0.0;
   // если в диапазоне есть 0, то он будет точкой построения оси
   if (a.mMin < point && a.mMax > point)
      return point;
   // нам не повезло, 0 нет

   double delta = mDistGrid*scale;
   if (abs(a.mMin) < abs(a.mMax))
   {
      point = ceil(a.mMin/delta)*delta;
   }
   else
   {
      point = floor(a.mMax/delta)*delta;
   }
   return point;
}

std::unique_ptr<TBitmap>TPlotter::DrawStandartGraph(int w, int h)
{
   std::unique_ptr<TBitmap>res = std::make_unique<TBitmap>();
   TBitmap *bmp = res.get();
   bmp->Width = w;
   bmp->Height = h;
   auto cnv = bmp->Canvas;
   // настраиваем цвета для очистки окна
   cnv->Brush->Color = clWhite;
   cnv->Font->Color = clWindowText;
   // чистим окно
   TRect holst(0, 0, w, h);
   cnv->FillRect(holst);

   if( !mCurrentLine )
      return res;

   cnv->Font->Color = clBlack;
   cnv->Font->Orientation = 0;
//   cnv->Font->Name = L"Comic Sans MS";
   cnv->Font->Name = L"Tahoma";
   cnv->Font->Size = 10;

   mCurrentLine->mDrawingLimitsX = GetLimitsX();
   mCurrentLine->mDrawingLimitsY = GetLimitsY();


   auto min_y = cnv->TextExtent( StringValue(-99999.999999) );

   int left_ofset = min_y.Width;
   int bottom_ofset = min_y.Height;

   //от холста нужно отрезать место для подписей с низу и с лева

   mCurrentLine->mHolst = TRect(mBorder+left_ofset, mBorder, w - (mBorder * 2), h - (mBorder * 2)-bottom_ofset);

   if( mCurrentLine->mDrawingLimitsX.mMax - mCurrentLine->mDrawingLimitsX.mMin == 0 )
      return res;
   mCurrentLine->x_scale = ScaleX(mCurrentLine->mDrawingLimitsX);
   mCurrentLine->y_scale = ScaleY(mCurrentLine->mDrawingLimitsY);

   mCurrentLine->mDrawingLimitsX.mMax += mCurrentLine->mMoveX;
   mCurrentLine->mDrawingLimitsX.mMin += mCurrentLine->mMoveX;
   mCurrentLine->mDrawingLimitsY.mMax += mCurrentLine->mMoveY;
   mCurrentLine->mDrawingLimitsY.mMin += mCurrentLine->mMoveY;

   double x_point = AxisValue(mCurrentLine->mDrawingLimitsX, mCurrentLine->x_scale);
   double y_point = AxisValue(mCurrentLine->mDrawingLimitsY, mCurrentLine->y_scale);

   // посчитаем количество линий сетки на осях
   DrawGrid( cnv, x_point, y_point );
   DrawLine( cnv );
   DrawSelection( cnv );
   return res;
}

void __fastcall TPlotter::FrameResize(TObject *Sender)
{
   Repaint();
}

void __fastcall TPlotter::LinesListChange(TObject *Sender)
{
   std::unique_lock<std::mutex>lock(mDataMutex);
   mCurrentLine = &mLines[LinesList->Text];
   ClearLimitsImpl();
   Draw();
}

TPlotter::LinePoint TPlotter::RealPoint(double x, double y)
{
   // Переводим координаты точки диапазона в координакты графика
   LinePoint res;

   double dx = abs(x - mCurrentLine->mHolst.Left) * mCurrentLine->x_scale;
   double dy = abs(y - mCurrentLine->mHolst.Bottom) * mCurrentLine->y_scale;

   res.mX = mCurrentLine->mDrawingLimitsX.mMin + dx;
   res.mY = mCurrentLine->mDrawingLimitsY.mMin + dy;
   return res;
}

UnicodeString TPlotter::StringValue( double v )
{
   //ffGeneral, ffExponent, ffFixed, ffNumber, ffCurrency
   return FloatToStrF(v, ffGeneral, 6, 4);
}

void __fastcall TPlotter::GraphAreaMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
   std::unique_lock<std::mutex>lock(mDataMutex);
   if( !mCurrentLine )
      return;

   LinePoint p = RealPoint( X, Y );
   xLabel->Caption = mCurrentLine->mXname + L": " + StringValue( p.mX ) + L" " + mCurrentLine->mYname + L": " + StringValue( p.mY );

   auto point = TPoint(X,Y);
   if( mSelection )
      mSelection->mEndPoint = point;
   if( mMoveState )
   {
      auto p2 = RealPoint( mMoveState->X, mMoveState->Y );
      *mMoveState = point;

      mCurrentLine->mMoveX += p2.mX - p.mX;
      mCurrentLine->mMoveY += p2.mY - p.mY;
   }

   Draw();
}
void __fastcall TPlotter::Panel1MouseLeave(TObject *Sender)
{
   xLabel->Caption = L"";
   std::unique_lock<std::mutex>lock(mDataMutex);
   mSelection.reset();
   mMoveState.reset();
   GraphArea->Cursor = crHandPoint;
}
void __fastcall TPlotter::Panel1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
   if ( Button == mbRight )
   {
      GraphArea->Cursor = crCross;
      std::unique_lock<std::mutex>lock(mDataMutex);
      if( !mCurrentLine )
         return;
      mSelection = std::make_unique< SeletionState >();
      mSelection->mStartPoint = TPoint(X,Y);
      mSelection->mEndPoint = TPoint(X,Y);
   }
   else if( Button == mbLeft )
   {
      GraphArea->Cursor = crHandPoint;
      std::unique_lock<std::mutex>lock(mDataMutex);
      if( !mCurrentLine )
         return;
      mMoveState = std::make_unique< TPoint >(X,Y);
      SetLimitsImpl( GetLimitsX(), GetLimitsY() );
   }

}
void __fastcall TPlotter::Panel1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
   if ( Button == mbRight )
   {
      std::unique_lock<std::mutex>lock(mDataMutex);
      if( !mSelection )
         return;
      mSelection->mEndPoint = TPoint(X,Y);
      if( !mCurrentLine )
         return;

      auto start_point = RealPoint( mSelection->mStartPoint.X, mSelection->mStartPoint.Y );
      auto end_point = RealPoint( mSelection->mEndPoint.X, mSelection->mEndPoint.Y );

      AxisLimits x_limit;
      x_limit.mMin = start_point.mX < end_point.mX ? start_point.mX : end_point.mX;
      x_limit.mMax = start_point.mX > end_point.mX ? start_point.mX : end_point.mX;

      AxisLimits y_limit;
      y_limit.mMin = start_point.mY < end_point.mY ? start_point.mY : end_point.mY;
      y_limit.mMax = start_point.mY > end_point.mY? start_point.mY : end_point.mY;

      SetLimitsImpl( x_limit, y_limit );
      mCurrentLine->mMoveX = 0;
      mCurrentLine->mMoveY = 0;
      mSelection.reset();
      Draw();
   }
   else if( Button == mbLeft )
   {
      std::unique_lock<std::mutex>lock(mDataMutex);
      mMoveState.reset();
   }
   GraphArea->Cursor = crHandPoint;
}

void __fastcall TPlotter::ScaleResetClick(TObject *Sender)
{
   ClearLimits();
   Repaint();
}
void __fastcall TPlotter::ScaleDownXClick(TObject *Sender)
{
   std::unique_lock<std::mutex>lock(mDataMutex);

   if( !mCurrentLine )
      return;
   auto limits_x = GetLimitsX();
   auto limits_y = GetLimitsY();
   auto dx = abs( limits_x.mMax - limits_x.mMin )*0.5;
   auto dy = abs( limits_y.mMax - limits_y.mMin )*0.5;
   limits_x.mMax += dx;
   limits_x.mMin -= dx;
   limits_y.mMax += dy;
   limits_y.mMin -= dy;

   SetLimitsImpl( limits_x, limits_y );
   Draw();
}
void __fastcall TPlotter::ScaleUpXClick(TObject *Sender)
{
   std::unique_lock<std::mutex>lock(mDataMutex);
   auto limits_x = GetLimitsX();
   auto limits_y = GetLimitsY();
   auto dx = abs( limits_x.mMax - limits_x.mMin )*0.25;
   auto dy = abs( limits_y.mMax - limits_y.mMin )*0.25;
   limits_x.mMax -= dx;
   limits_x.mMin += dx;
   limits_y.mMax -= dy;
   limits_y.mMin += dy;

   SetLimitsImpl( limits_x, limits_y );
   Draw();
}

