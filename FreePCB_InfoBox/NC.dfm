object Form3: TForm3
  Left = 976
  Top = 196
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'NC'
  ClientHeight = 502
  ClientWidth = 259
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
  object NC: TListBox
    Left = 8
    Top = 13
    Width = 145
    Height = 476
    ItemHeight = 13
    TabOrder = 0
  end
  object Button1: TButton
    Left = 168
    Top = 16
    Width = 75
    Height = 25
    Caption = 'TXT'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 168
    Top = 48
    Width = 75
    Height = 25
    Caption = 'Show'
    TabOrder = 2
    OnClick = Button2Click
  end
end
