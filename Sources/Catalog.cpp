// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <Menus.hpp>
#include "Catalog.h"
#include "Connection.h"
#include "Editor.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDirectory *Directory;

// ---------------------------------------------------------------------------
static const String GenSelectSQL(const TTable &aTable) {
	String res = "SELECT ";
	for (size_t i = 0; i < aTable.size(); i++) {
		if (i > 0)
			res += ", ";

		res += aTable.NameTable + "." + aTable[i].DataField;
		if (aTable[i].Primary)
			res += ", " + aTable[i].KeyTable + "." + aTable[i].ListField;
	}
	return res;
}

// ---------------------------------------------------------------------------
static const String GenJoinSQL(const TTable &aTable) {
	String res = "";
	for (size_t i = 0; i < aTable.size(); i++)
		if (aTable[i].Primary)
			res += "(";

	res += aTable.NameTable;
	for (size_t i = 0; i < aTable.size(); i++)
		if (aTable[i].Primary)
			res += " INNER JOIN " + aTable[i].KeyTable + " ON " +
				aTable.NameTable + "." + aTable[i].DataField + " = " +
				aTable[i].KeyTable + "." + aTable[i].KeyField + ")";

	return res;
}

// ---------------------------------------------------------------------------
static const String GenFromSQL(const TTable &aTable) {
	return "FROM " + GenJoinSQL(aTable);
}

// ---------------------------------------------------------------------------
static const String GetOrderFields(const TTable &aTable) {
	String res = "";
	for (size_t i = 0; i < aTable.size(); i++) {
		if (!aTable[i].Visible)
			continue;

		res += aTable[i].DataField + "|ORDER BY ";
		if (aTable[i].Primary)
			res += aTable[i].KeyTable + "." + aTable[i].ListField;
		else
			res += aTable.NameTable + "." + aTable[i].DataField;
		res += "|";
	}
	return res.SubString(1, res.Length() - 1);
}

// ---------------------------------------------------------------------------
static const String GetFilterFields(const TTable &aTable) {
	String res = "";
	for (size_t i = 0; i < aTable.size(); i++) {
		if (!aTable[i].Visible)
			continue;

		res += aTable[i].DataField + "|CStr(";
		if (aTable[i].Primary)
			res += aTable[i].KeyTable + "." + aTable[i].ListField;
		else
			res += aTable.NameTable + "." + aTable[i].DataField;
		res += ")|";
	}
	return res.SubString(1, res.Length() - 1);
}

// ---------------------------------------------------------------------------
__fastcall TDirectory::TDirectory(TComponent* Owner, const TTable &aTable)
	: TForm(Owner), fTable(aTable) {
	Caption = fTable.NameTable;

	if (fTable.ReadOnly) {
		AddBtn->Enabled = false;
		DelBtn->Enabled = false;
		EditBtn->Enabled = false;
	}

	for (size_t i = 0; i < fTable.size(); i++) {
		TColumn *fCol = DBGrid->Columns->Add();
		if (fTable[i].Primary)
			fCol->FieldName = fTable[i].ListField;
		else
			fCol->FieldName = fTable[i].DataField;

		fCol->Title->Caption = fTable[i].DataField;
		fCol->Width = 10 + Canvas->TextWidth(fCol->Title->Caption);
		fCol->Visible = fTable[i].Visible;
	}

	FilterField->Filter = GetFilterFields(fTable);
	OrderField->Filter = GetOrderFields(fTable);
	ADOQuery->SQL->Append(GenSelectSQL(fTable));
	ADOQuery->SQL->Append(GenFromSQL(fTable));
	fQuery = ADOQuery->SQL->Text;
	ADOQuery->Open();
}

// ---------------------------------------------------------------------------
void __fastcall TDirectory::AddBtnClick(TObject *Sender) {
	TCellEditor(this, ADD, fTable, ADOQuery).ShowModal();
}

// ---------------------------------------------------------------------------
void __fastcall TDirectory::FormClose(TObject *Sender, TCloseAction &Action) {
	dynamic_cast<TMenuItem*>(Owner)->Checked = false;
	Action = caFree;
}

// ---------------------------------------------------------------------------
void __fastcall TDirectory::SearchBtnClick(TObject *Sender) {
	ADOQuery->Close();
	ADOQuery->SQL->Text = fQuery;
	ADOQuery->SQL->Append("WHERE " + FilterField->Mask + FilterWay->Mask + "'" +
		FilterEdit->Text + "'");
	ADOQuery->SQL->Append(OrderField->Mask + OrderWay->Mask);
	ADOQuery->Open();
}

// ---------------------------------------------------------------------------
void __fastcall TDirectory::RefreshBtnClick(TObject *Sender) {
	ADOQuery->Close();
	ADOQuery->SQL->Text = fQuery;
	ADOQuery->Open();
}
// ---------------------------------------------------------------------------

void __fastcall TDirectory::DBGridDrawColumnCell(TObject *Sender,
	const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State) {
	int MaxWidth = 10 + Canvas->TextWidth(Column->Field->Text);
	if (MaxWidth > Column->Width)
		Column->Width = MaxWidth;
}
// ---------------------------------------------------------------------------

void __fastcall TDirectory::EditBtnClick(TObject *Sender) {
	TCellEditor(this, EDIT, fTable, ADOQuery).ShowModal();
}
// ---------------------------------------------------------------------------

void __fastcall TDirectory::DelBtnClick(TObject *Sender) {
	if (MessageDlg("�� �������, ��� ������ ������� ��������� ������?",
		mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
		TCellEditor(this, REMOVE, fTable, ADOQuery);
}
// ---------------------------------------------------------------------------
