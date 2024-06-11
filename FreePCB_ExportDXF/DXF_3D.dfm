object Form1: TForm1
  Left = 437
  Top = 118
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1054#1087#1094#1080#1080
  ClientHeight = 687
  ClientWidth = 872
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
  object Label11: TLabel
    Left = 208
    Top = 659
    Width = 425
    Height = 16
    AutoSize = False
    Caption = 'process process process process process process process'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    Visible = False
    OnMouseMove = Label11MouseMove
  end
  object Label16: TLabel
    Left = 16
    Top = 8
    Width = 59
    Height = 16
    Caption = 'MaxLines'
    Visible = False
  end
  object Label17: TLabel
    Left = 144
    Top = 8
    Width = 52
    Height = 16
    Caption = 'MaxPins'
    Visible = False
  end
  object CheckBox1: TCheckBox
    Left = 16
    Top = 633
    Width = 217
    Height = 17
    Caption = 'Print grid to output file'
    TabOrder = 0
    OnClick = CheckBox1Click
  end
  object Button1: TButton
    Left = 776
    Top = 651
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = Button1Click
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 48
    Width = 305
    Height = 105
    TabOrder = 2
    object Label1: TLabel
      Left = 16
      Top = 51
      Width = 68
      Height = 16
      Caption = 'Line Width'
    end
    object Label2: TLabel
      Left = 120
      Top = 76
      Width = 39
      Height = 16
      Caption = 'Space'
    end
    object Label7: TLabel
      Left = 16
      Top = 25
      Width = 80
      Height = 16
      Caption = 'Board Width'
    end
    object CheckBox2: TCheckBox
      Left = 16
      Top = 76
      Width = 57
      Height = 17
      Caption = 'Fill'
      TabOrder = 0
    end
    object CSpinEdit1: TCSpinEdit
      Left = 168
      Top = 71
      Width = 121
      Height = 26
      TabOrder = 1
    end
    object CSpinEdit2: TCSpinEdit
      Left = 168
      Top = 45
      Width = 121
      Height = 26
      TabOrder = 2
    end
    object CSpinEdit3: TCSpinEdit
      Left = 168
      Top = 19
      Width = 121
      Height = 26
      TabOrder = 3
    end
  end
  object GroupBox2: TGroupBox
    Left = 16
    Top = 176
    Width = 305
    Height = 225
    TabOrder = 3
    object Label8: TLabel
      Left = 16
      Top = 25
      Width = 125
      Height = 16
      Caption = 'Copper layer Width'
    end
    object Label3: TLabel
      Left = 192
      Top = 199
      Width = 39
      Height = 16
      Caption = 'Space'
    end
    object Label4: TLabel
      Left = 192
      Top = 79
      Width = 39
      Height = 16
      Caption = 'Space'
    end
    object Label5: TLabel
      Left = 192
      Top = 103
      Width = 39
      Height = 16
      Caption = 'Space'
    end
    object Label6: TLabel
      Left = 192
      Top = 127
      Width = 39
      Height = 16
      Caption = 'Space'
    end
    object Label9: TLabel
      Left = 192
      Top = 151
      Width = 39
      Height = 16
      Caption = 'Space'
    end
    object Label10: TLabel
      Left = 192
      Top = 175
      Width = 39
      Height = 16
      Caption = 'Space'
    end
    object Label12: TLabel
      Left = 16
      Top = 51
      Width = 68
      Height = 16
      Caption = 'Line Width'
    end
    object CSpinEdit4: TCSpinEdit
      Left = 168
      Top = 19
      Width = 121
      Height = 26
      TabOrder = 0
    end
    object CheckBox3: TCheckBox
      Left = 16
      Top = 80
      Width = 97
      Height = 17
      Caption = 'Top Pads'
      TabOrder = 1
    end
    object CheckBox4: TCheckBox
      Left = 128
      Top = 79
      Width = 49
      Height = 17
      Caption = 'Fill'
      TabOrder = 2
    end
    object CSpinEdit5: TCSpinEdit
      Left = 240
      Top = 74
      Width = 49
      Height = 26
      TabOrder = 3
    end
    object CheckBox5: TCheckBox
      Left = 16
      Top = 104
      Width = 97
      Height = 17
      Caption = 'Top Lines'
      TabOrder = 4
    end
    object CheckBox6: TCheckBox
      Left = 16
      Top = 128
      Width = 97
      Height = 17
      Caption = 'Top Areas'
      TabOrder = 5
    end
    object CheckBox7: TCheckBox
      Left = 128
      Top = 103
      Width = 49
      Height = 17
      Caption = 'Fill'
      TabOrder = 6
    end
    object CSpinEdit6: TCSpinEdit
      Left = 240
      Top = 98
      Width = 49
      Height = 26
      TabOrder = 7
    end
    object CheckBox8: TCheckBox
      Left = 128
      Top = 127
      Width = 49
      Height = 17
      Caption = 'Fill'
      TabOrder = 8
    end
    object CSpinEdit7: TCSpinEdit
      Left = 240
      Top = 122
      Width = 49
      Height = 26
      TabOrder = 9
    end
    object CheckBox9: TCheckBox
      Left = 128
      Top = 151
      Width = 49
      Height = 17
      Caption = 'Fill'
      TabOrder = 10
    end
    object CSpinEdit8: TCSpinEdit
      Left = 240
      Top = 146
      Width = 49
      Height = 26
      TabOrder = 11
    end
    object CheckBox10: TCheckBox
      Left = 128
      Top = 175
      Width = 49
      Height = 17
      Caption = 'Fill'
      TabOrder = 12
    end
    object CSpinEdit9: TCSpinEdit
      Left = 240
      Top = 170
      Width = 49
      Height = 26
      TabOrder = 13
    end
    object CheckBox11: TCheckBox
      Left = 128
      Top = 199
      Width = 49
      Height = 17
      Caption = 'Fill'
      TabOrder = 14
    end
    object CSpinEdit10: TCSpinEdit
      Left = 240
      Top = 194
      Width = 49
      Height = 26
      TabOrder = 15
    end
    object CheckBox12: TCheckBox
      Left = 16
      Top = 152
      Width = 97
      Height = 17
      Caption = 'Top Pads'
      TabOrder = 16
    end
    object CheckBox13: TCheckBox
      Left = 16
      Top = 176
      Width = 97
      Height = 17
      Caption = 'Top Lines'
      TabOrder = 17
    end
    object CheckBox14: TCheckBox
      Left = 16
      Top = 200
      Width = 97
      Height = 17
      Caption = 'Top Areas'
      TabOrder = 18
    end
    object CSpinEdit11: TCSpinEdit
      Left = 168
      Top = 45
      Width = 121
      Height = 26
      TabOrder = 19
    end
  end
  object GroupBox3: TGroupBox
    Left = 16
    Top = 424
    Width = 305
    Height = 73
    TabOrder = 4
    object Label13: TLabel
      Left = 16
      Top = 19
      Width = 68
      Height = 16
      Caption = 'Line Width'
    end
    object CSpinEdit12: TCSpinEdit
      Left = 168
      Top = 13
      Width = 121
      Height = 26
      TabOrder = 0
    end
    object CheckBox19: TCheckBox
      Left = 16
      Top = 48
      Width = 57
      Height = 17
      Caption = 'Top'
      TabOrder = 1
    end
    object CheckBox20: TCheckBox
      Left = 80
      Top = 48
      Width = 97
      Height = 17
      Caption = 'Bottom'
      TabOrder = 2
    end
  end
  object CheckBox15: TCheckBox
    Left = 16
    Top = 32
    Width = 129
    Height = 17
    Caption = 'Board layer'
    TabOrder = 5
  end
  object CheckBox16: TCheckBox
    Left = 16
    Top = 160
    Width = 145
    Height = 17
    Caption = 'Copper layers'
    TabOrder = 6
  end
  object CheckBox17: TCheckBox
    Left = 16
    Top = 408
    Width = 161
    Height = 17
    Caption = 'Silcscreen layers'
    TabOrder = 7
  end
  object GroupBox4: TGroupBox
    Left = 16
    Top = 520
    Width = 305
    Height = 105
    TabOrder = 8
    object Label14: TLabel
      Left = 16
      Top = 25
      Width = 68
      Height = 16
      Caption = 'Line Width'
    end
    object Label15: TLabel
      Left = 120
      Top = 52
      Width = 39
      Height = 16
      Caption = 'Space'
    end
    object CSpinEdit13: TCSpinEdit
      Left = 168
      Top = 19
      Width = 121
      Height = 26
      TabOrder = 0
    end
    object CheckBox21: TCheckBox
      Left = 80
      Top = 80
      Width = 97
      Height = 17
      Caption = 'Bottom'
      TabOrder = 1
    end
    object CheckBox22: TCheckBox
      Left = 16
      Top = 80
      Width = 57
      Height = 17
      Caption = 'Top'
      TabOrder = 2
    end
    object CheckBox23: TCheckBox
      Left = 16
      Top = 52
      Width = 57
      Height = 17
      Caption = 'Fill'
      TabOrder = 3
    end
    object CSpinEdit14: TCSpinEdit
      Left = 168
      Top = 47
      Width = 121
      Height = 26
      TabOrder = 4
    end
  end
  object CheckBox18: TCheckBox
    Left = 16
    Top = 504
    Width = 177
    Height = 17
    Caption = 'Solder mask cutouts'
    TabOrder = 9
  end
  object StringGrid1: TStringGrid
    Left = 328
    Top = 8
    Width = 529
    Height = 145
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    TabOrder = 10
    RowHeights = (
      24
      24
      24
      24
      24)
  end
  object OpenDialog1: TOpenDialog
    Filter = 'FreePcb MFC Application|*.fpc||*.FPC'
    Left = 288
    Top = 8
  end
end
