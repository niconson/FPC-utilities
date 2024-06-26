object Form1: TForm1
  Left = 423
  Top = 269
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'FreePcb 2 DXF converter'
  ClientHeight = 302
  ClientWidth = 736
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 567
    Top = 283
    Width = 32
    Height = 13
    Caption = 'Label1'
    Visible = False
  end
  object Label2: TLabel
    Left = 634
    Top = 264
    Width = 48
    Height = 13
    Cursor = crHandPoint
    Caption = 'Freepcb-2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = Label2Click
  end
  object CheckBox1: TCheckBox
    Left = 448
    Top = 6
    Width = 89
    Height = 17
    Caption = 'Board layer'
    Checked = True
    State = cbChecked
    TabOrder = 0
  end
  object CheckBox2: TCheckBox
    Left = 448
    Top = 22
    Width = 97
    Height = 17
    Caption = 'Top pads'
    Checked = True
    State = cbChecked
    TabOrder = 1
  end
  object CheckBox3: TCheckBox
    Left = 448
    Top = 38
    Width = 81
    Height = 17
    Caption = 'Top lines'
    TabOrder = 2
  end
  object CheckBox4: TCheckBox
    Left = 448
    Top = 54
    Width = 97
    Height = 17
    Caption = 'Top areas'
    TabOrder = 3
  end
  object CheckBox5: TCheckBox
    Left = 448
    Top = 70
    Width = 97
    Height = 17
    Caption = 'Top mask'
    TabOrder = 4
  end
  object CheckBox6: TCheckBox
    Left = 448
    Top = 86
    Width = 97
    Height = 17
    Caption = 'Top paste'
    TabOrder = 5
  end
  object CheckBox8: TCheckBox
    Left = 448
    Top = 118
    Width = 97
    Height = 17
    Caption = 'Bottom pads'
    Checked = True
    State = cbChecked
    TabOrder = 6
  end
  object CheckBox9: TCheckBox
    Left = 448
    Top = 134
    Width = 81
    Height = 17
    Caption = 'Bottom lines'
    TabOrder = 7
  end
  object CheckBox10: TCheckBox
    Left = 448
    Top = 150
    Width = 97
    Height = 17
    Caption = 'Bottom areas'
    TabOrder = 8
  end
  object CheckBox11: TCheckBox
    Left = 448
    Top = 166
    Width = 97
    Height = 17
    Caption = 'Bottom mask'
    TabOrder = 9
  end
  object CheckBox12: TCheckBox
    Left = 448
    Top = 182
    Width = 97
    Height = 17
    Caption = 'Bottom paste'
    TabOrder = 10
  end
  object CheckBox14: TCheckBox
    Left = 448
    Top = 214
    Width = 73
    Height = 17
    Caption = '3d top'
    Checked = True
    State = cbChecked
    TabOrder = 11
  end
  object CheckBox15: TCheckBox
    Left = 448
    Top = 230
    Width = 73
    Height = 17
    Caption = '3d bottom'
    Checked = True
    State = cbChecked
    TabOrder = 12
  end
  object Button1: TButton
    Left = 606
    Top = 32
    Width = 105
    Height = 25
    Caption = 'Edit DXF library'
    TabOrder = 13
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 606
    Top = 232
    Width = 105
    Height = 25
    Caption = 'OK'
    TabOrder = 14
    OnClick = Button2Click
  end
  object OutputBox: TListBox
    Left = 608
    Top = 16
    Width = 25
    Height = 25
    ItemHeight = 13
    TabOrder = 15
    Visible = False
  end
  object CheckBox16: TCheckBox
    Left = 448
    Top = 246
    Width = 81
    Height = 17
    Caption = 'Via Pads'
    TabOrder = 16
  end
  object CheckBox17: TCheckBox
    Left = 448
    Top = 278
    Width = 97
    Height = 17
    Caption = 'Pad holes'
    Checked = True
    State = cbChecked
    TabOrder = 17
  end
  object Button3: TButton
    Left = 606
    Top = 64
    Width = 105
    Height = 25
    Caption = 'Options'
    TabOrder = 18
    OnClick = Button3Click
  end
  object File: TListBox
    Left = 640
    Top = 16
    Width = 25
    Height = 25
    ItemHeight = 13
    TabOrder = 19
    Visible = False
  end
  object CheckBox7: TCheckBox
    Left = 448
    Top = 102
    Width = 97
    Height = 17
    Caption = 'Top silk'
    TabOrder = 20
  end
  object CheckBox13: TCheckBox
    Left = 448
    Top = 198
    Width = 97
    Height = 17
    Caption = 'Bottom silk'
    TabOrder = 21
  end
  object Button4: TButton
    Left = 606
    Top = 96
    Width = 105
    Height = 25
    Caption = 'Select/Unselect'
    TabOrder = 22
    OnClick = Button4Click
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 12
    Width = 201
    Height = 275
    Caption = 'Parts'
    TabOrder = 23
    object Parts: TListBox
      Left = 15
      Top = 24
      Width = 170
      Height = 217
      Enabled = False
      ItemHeight = 13
      MultiSelect = True
      Sorted = True
      TabOrder = 0
    end
    object AllP: TCheckBox
      Left = 16
      Top = 248
      Width = 65
      Height = 17
      Caption = 'All parts'
      Checked = True
      State = cbChecked
      TabOrder = 1
      OnClick = AllPClick
    end
  end
  object Blocks: TListBox
    Left = 672
    Top = 16
    Width = 25
    Height = 25
    ItemHeight = 13
    TabOrder = 24
    Visible = False
  end
  object NamesOfBlocks: TListBox
    Left = 704
    Top = 16
    Width = 25
    Height = 25
    ItemHeight = 13
    TabOrder = 25
    Visible = False
  end
  object GroupBox2: TGroupBox
    Left = 224
    Top = 12
    Width = 201
    Height = 275
    Caption = 'Nets'
    TabOrder = 26
    object Nets: TListBox
      Left = 15
      Top = 24
      Width = 170
      Height = 217
      Enabled = False
      ItemHeight = 13
      MultiSelect = True
      Sorted = True
      TabOrder = 0
    end
    object CheckBox19: TCheckBox
      Left = 16
      Top = 248
      Width = 97
      Height = 17
      Caption = 'All nets'
      Checked = True
      State = cbChecked
      TabOrder = 1
      OnClick = CheckBox19Click
    end
  end
  object GroupBox3: TGroupBox
    Left = 608
    Top = 128
    Width = 105
    Height = 57
    TabOrder = 27
    object RadioButton1: TRadioButton
      Left = 16
      Top = 14
      Width = 81
      Height = 17
      Caption = 'Play'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object RadioButton2: TRadioButton
      Left = 16
      Top = 30
      Width = 81
      Height = 17
      Caption = 'Import'
      TabOrder = 1
    end
  end
  object InsideBRD: TCheckBox
    Left = 608
    Top = 200
    Width = 113
    Height = 17
    Caption = 'Inside BoardRect'
    TabOrder = 28
  end
  object CheckBox18: TCheckBox
    Left = 448
    Top = 262
    Width = 89
    Height = 17
    Caption = 'Via Holes'
    TabOrder = 29
  end
  object OpenDialog1: TOpenDialog
    Filter = 'FreePCB project file|*.fpc|All files|*.*'
    Left = 568
    Top = 94
  end
end
