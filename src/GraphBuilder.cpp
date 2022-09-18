//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GraphBuilder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPlotter *Plotter;
//---------------------------------------------------------------------------
__fastcall TPlotter::TPlotter(TComponent* Owner)
   : TFrame(Owner)
{
}
void __fastcall TPlotter::Repaint(void)
{
   TFrame::Repaint();
   Draw();
}
//---------------------------------------------------------------------------
void TPlotter::Draw()
{
   auto rect = GraphArea->ClientRect;
   auto w = rect.Width();
   auto h = rect.Height();
   std::unique_ptr<TBitmap> bmp;
   bmp = DrawStandartGraph( w, h );
   GraphArea->Picture->Bitmap->Width = bmp->Width;
   GraphArea->Picture->Bitmap->Height = bmp->Height;
   GraphArea->Canvas->Draw( 0, 0, bmp.get() );
}

std::unique_ptr<TBitmap> TPlotter::DrawStandartGraph( int w, int h )
{
   std::unique_ptr<TBitmap> res = std::make_unique<TBitmap>();
   TBitmap *bmp = res.get() ;
   bmp->Width = w;
   bmp->Height = h;
   auto cnv = bmp->Canvas;
      //����������� ����� ��� ������� ����
   cnv->Brush->Color=clWhite;
   cnv->Font->Color=clWindowText;
   //������ ����
   TRect rect(0,0,w,h);
   cnv->FillRect( rect );

//    QPixmap picture( mWidth, mHeight );
//    QPainter painter( &picture );
//    painter.setFont( mFont );
//    QFontMetrics metrix( painter.font() );
////    painter.setRenderHint(QPainter::Antialiasing);
//
//    int x_pos = mWidth/2 - 1;
//    int y_pos = mHeight/2 - 1;
//
//    if ( mMode == TopHalf || mMode == PlusPlus)
//        y_pos = mHeight - ( metrix.height() * 2 );
//    if ( mMode == BottomHalf )
//        y_pos = ( metrix.height() * 2 );
//    if ( mMode == PlusPlus )
//        x_pos = ( metrix.width("12345") * 2 );
//
//    int legend_y_ofset = 5;
//    int width = mWidth - 2;
//    int height = mHeight - 2;
//    int x_dist = width - x_pos;
//    int legend_start_point = -(height - ( height - y_pos ) - legend_y_ofset  ) ;
//    int y_dist = -legend_start_point - metrix.height() * data.size() ;
//
//    // ���������� �����
//    QRect border( 0, 0, mWidth - 1, mHeight - 1 );
//    painter.fillRect( border, Qt::white );
//    painter.drawRect( border );
//
//    // ����������� ����������� � ����� �����������
//    QPoint window_center ( x_pos, y_pos );
//    painter.setPen( Qt::black );
//    painter.setPen( Qt::SolidLine );
//    painter.translate ( window_center );
//
//
//    // ���������� ��� x � y
//    painter.drawLine( -x_dist, 0, width, 0 );
//    painter.drawLine( 0, -y_dist, 0, height );
//
//    qreal x_skale = x_dist / x_interval;
//    qreal y_skale = y_dist / y_interval;
//
//    //���������� �����/�����
//    {
//        painter.save();
//        painter.setPen( Qt::lightGray );
//        painter.setPen( draw_greed ? Qt::DotLine : Qt::SolidLine );
//
//        qreal dash_lehgth = std::min( y_dist, x_dist )/100;
//
//        // x
//        {
//            qreal st_y = 0;
//            qreal sp_y = 0;
//            if ( !draw_greed )
//            {
//                sp_y = dash_lehgth;
//                st_y = -dash_lehgth;
//            }
//            else
//            {
//                st_y = -y_dist;
//                sp_y = y_dist;
//                if ( mMode == PlusPlus )
//                {
//                    sp_y = 0;
//                }
//            }
//            // ������������� ��������
//            {
//                qreal pos = 0 + x_step;
//                QPointF start( pos * x_skale, st_y ), stop( start.x(), sp_y );
//                while ( start.x() < x_dist )
//                {
//                    painter.drawLine( start, stop );
//
//                    QString t = QString::number(pos);
//                    painter.drawText( stop.x() - metrix.width( t )/2 , dash_lehgth + metrix.height(), t );
//
//                    pos += x_step;
//                    start.setX( pos * x_skale );
//                    stop.setX( pos * x_skale );
//                }
//            }
//            // ������������� ��������
//            if ( mMode != PlusPlus )
//            {
//                qreal pos = 0 - x_step;
//                QPointF start( pos * x_skale, st_y ), stop( start.x(), sp_y );
//                while ( start.x() > -x_dist )
//                {
//                    painter.drawLine( start, stop );
//
//                    QString t = QString::number(pos);
//                    painter.drawText( stop.x() - metrix.width( t )/2 , dash_lehgth + metrix.height(), t );
//
//                    pos -= x_step;
//                    start.setX( pos * x_skale );
//                    stop.setX( pos * x_skale );
//                }
//            }
//        }
//
//        // y
//        {
//            qreal st_x = 0;
//            qreal sp_x = 0;
//            if ( !draw_greed )
//            {
//                sp_x = dash_lehgth;
//                st_x = -dash_lehgth;
//            }
//            else
//            {
//                st_x = -x_dist;
//                if ( mMode == TopHalf || mMode == PlusPlus )
//                {
//                    st_x = 0;
//                }
//                sp_x = x_dist;
//            }
//            // ������������� ��������
//            {
//                qreal pos = 0 - y_step;
//                QPointF start( st_x, pos * y_skale ), stop( sp_x, start.y() );
//                while ( start.y() > -y_dist )
//                {
//                    painter.drawLine( start, stop );
//
//                    QString t = QString::number( -1 * pos);
//                    painter.drawText( -dash_lehgth - metrix.width( t ), start.y() + metrix.height()/4, t );
//
//                    pos -= y_step;
//                    start.setY( pos * y_skale );
//                    stop.setY( pos * y_skale );
//                }
//            }
//            // ������������� ��������
//            if ( !(mMode == TopHalf || mMode == PlusPlus) )
//            {
//                qreal pos = 0 + y_step;
//                QPointF start( st_x, pos * y_skale ), stop( sp_x, start.y() );
//                while ( start.y() < y_dist )
//                {
//                    painter.drawLine( start, stop );
//
//                    QString t = QString::number( -1 * pos);
//                    painter.drawText( -dash_lehgth - metrix.width( t ), start.y() + metrix.height()/4 , t );
//
//                    pos += y_step;
//                    start.setY( pos * y_skale );
//                    stop.setY( pos * y_skale );
//                }
//            }
//        }
//
//        // �������� �� ��� ���� ����
//
//        painter.drawText( x_dist - metrix.width( x_label ), -4, x_label );
//        painter.drawText( 4 , -y_dist + metrix.height(), y_label );
//
//
//        painter.restore();
//    }
//
//    int legend_width = 0;
//    int leged_height = 0;
//    //���������� �����
//    foreach (Line const& line, data)
//    {
//        int l_width = metrix.width(line.second.mName);
//        QRect t( x_dist/100*25, legend_start_point + leged_height, l_width , metrix.height() );
//
//        painter.setPen( Qt::black );
//        painter.drawText( t, line.second.mName );
//        legend_width = std::max( legend_width, l_width );
//
//        leged_height += metrix.height();
//        painter.setPen( line.second.mColor );
//
//        painter.drawLine( 0, t.center().y(), x_dist/100*20, t.center().y() );
//
//        QPointF const* prevPoint = nullptr;
//        foreach (QPointF const& p, line.first)
//        {
//            if ( !prevPoint )
//                prevPoint = &p;
//
//            QPointF start = *prevPoint;
//            start.setX( start.x() * x_skale );
//            start.setY( start.y() * y_skale  *-1 );
//            if ( prevPoint != &p )
//            {
//                QPointF stop = p;
//                stop.setX( stop.x() * x_skale );
//                stop.setY( stop.y() * y_skale *-1 );
//
//                painter.drawLine( start, stop );
//            }
//            else if ( data.size() == 1 )
//            {
//                painter.drawPoint( start );
//            }
//
//            prevPoint = &p;
//        }
//    }
//
//    //���������� �������
//
//    return picture;
   return res;
}

void __fastcall TPlotter::FrameResize(TObject *Sender)
{
   Draw();
}
//---------------------------------------------------------------------------


