//---------------------------------------------------------------------------

#ifndef SellingH
#define SellingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TSellingTickets : public TForm
{
__published:	// IDE-managed Components
	TDataSource *SaleDataSource;
	TPanel *SalePanel;
	TPanel *PricePanel;
	TDBGrid *SaleGrid;
	TADOCommand *SellADOCommand;
	TButton *SellBtn;
	TADODataSet *PriceADODataSet;
	TDBGrid *PriceGrid;
	TDataSource *PriceDataSource;
	TLabel *PriceLabel;
	TADODataSet *SaleADODataSet;
	void __fastcall SaleGridDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
	void __fastcall SellBtnClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TSellingTickets(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSellingTickets *SellingTickets;
//---------------------------------------------------------------------------
#endif
