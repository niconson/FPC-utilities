object ObjMan: TObjMan
  Left = 237
  Top = 647
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Object Manger'
  ClientHeight = 246
  ClientWidth = 153
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Find: TComboBox
    Left = 0
    Top = 0
    Width = 153
    Height = 21
    ItemHeight = 13
    TabOrder = 0
    Text = 'Find'
  end
  object TextFind: TEdit
    Left = 0
    Top = 24
    Width = 153
    Height = 21
    TabOrder = 1
  end
  object ListBoxObjMan: TListBox
    Left = 0
    Top = 48
    Width = 153
    Height = 193
    ItemHeight = 13
    TabOrder = 2
  end
end