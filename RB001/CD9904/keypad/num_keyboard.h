//---------------------------------------------------------------------------

#ifndef num_keyboardH
#define num_keyboardH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "functions.h"
class TNum_Pannel : public TForm
{
__published:	// IDE-managed Components
	TEdit *Displ;
	TPanel *Buttons;
	TButton *BT7;
	TPanel *Panel1;
	TPanel *Panel2;
	TButton *BT4;
	TButton *BT1;
	TButton *BT0;
	TButton *BT2;
	TButton *BT3;
	TButton *BT5;
	TButton *BT8;
	TButton *BT9;
	TButton *BT6;
	TButton *BTD;
	TButton *BS;
	TButton *C;
	TBitBtn *OK;
	TBitBtn *Cancel;
	void __fastcall BTClick(TObject *Sender);
	void __fastcall BSClick(TObject *Sender);
	void __fastcall CClick(TObject *Sender);
	void __fastcall OKClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	size_t  decimals, //знаков после запятой
			length;   //длина целой части
	double 	max_val,      //максимальное значение
			min_val;      //минимальное значение
	String 	Decimal_Separator;//разделитль разрядов числа
	bool 	check_value;      //необходимость проверки	данных по диапазону
public:		// User declarations
	String Value;
	__fastcall TNum_Pannel(TComponent* Owner,
							size_t _decimals,
							size_t _length,
							double _min_val,
							double _max_val,
							double init_val,
							bool _check_value=false,
							String separator=""
							);
};

#endif
