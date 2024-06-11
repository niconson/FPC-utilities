object Form4: TForm4
  Left = 728
  Top = 372
  BorderStyle = bsDialog
  Caption = 'Enter new name'
  ClientHeight = 32
  ClientWidth = 289
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Edit1: TEdit
    Left = 8
    Top = 4
    Width = 185
    Height = 21
    TabOrder = 0
  end
  object Button1: TButton
    Left = 205
    Top = 3
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = Button1Click
  end
end
