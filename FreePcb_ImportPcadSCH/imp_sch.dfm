object Form1: TForm1
  Left = 206
  Top = 127
  Width = 487
  Height = 95
  BorderIcons = []
  Caption = 'Schematic Constructor 1.4'
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
  object Label1: TLabel
    Left = 16
    Top = 8
    Width = 140
    Height = 13
    Caption = 'P-cad schematic file selection'
  end
  object ProgressBar: TProgressBar
    Left = 8
    Top = 32
    Width = 457
    Height = 17
    Min = 0
    Max = 100
    TabOrder = 0
  end
  object LB1: TListBox
    Left = 208
    Top = 16
    Width = 89
    Height = 25
    ItemHeight = 13
    TabOrder = 1
    Visible = False
  end
  object OpenDialog1: TOpenDialog
    Filter = 'P-cad schematic file (ASCII)|*.sch'
    Left = 56
    Top = 8
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 152
    Top = 8
  end
end
