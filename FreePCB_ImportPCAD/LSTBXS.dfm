object Form2: TForm2
  Left = 759
  Top = 296
  BorderStyle = bsDialog
  Caption = 'Pins'
  ClientHeight = 509
  ClientWidth = 767
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 16
  object Label1: TLabel
    Left = 32
    Top = 264
    Width = 90
    Height = 13
    Caption = 'FootPrintsName'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object ListBox1_FootPrintsName: TListBox
    Left = 32
    Top = 288
    Width = 353
    Height = 193
    ItemHeight = 16
    TabOrder = 0
  end
  object StringGrid1: TStringGrid
    Left = 32
    Top = 64
    Width = 713
    Height = 177
    TabOrder = 1
    RowHeights = (
      24
      24
      24
      24
      24)
  end
  object Button1: TButton
    Left = 168
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Find Pin'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Edit1: TEdit
    Left = 32
    Top = 24
    Width = 121
    Height = 24
    TabOrder = 3
  end
  object GroupBox1: TGroupBox
    Left = 400
    Top = 280
    Width = 345
    Height = 201
    Caption = 'Memory'
    TabOrder = 4
    object Label2: TLabel
      Left = 16
      Top = 48
      Width = 147
      Height = 16
      Caption = 'Memory for one trace:'
    end
    object Label3: TLabel
      Left = 16
      Top = 88
      Width = 144
      Height = 16
      Caption = 'Memory for all traces:'
    end
    object Edit2: TEdit
      Left = 200
      Top = 45
      Width = 121
      Height = 24
      TabOrder = 0
      Text = '9999'
    end
    object Edit3: TEdit
      Left = 200
      Top = 82
      Width = 121
      Height = 24
      TabOrder = 1
      Text = '199999'
    end
  end
end