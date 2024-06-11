object Form1: TForm1
  Left = 503
  Top = 126
  BorderStyle = bsDialog
  Caption = 'FreePcb footprints library'
  ClientHeight = 472
  ClientWidth = 625
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  OldCreateOrder = False
  Position = poScreenCenter
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  OnMouseWheelDown = FormMouseWheelDown
  OnMouseWheelUp = FormMouseWheelUp
  PixelsPerInch = 96
  TextHeight = 16
  object Label3: TLabel
    Left = 326
    Top = 443
    Width = 58
    Height = 16
    Cursor = crHandPoint
    Caption = 'FreePcb-2'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlue
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = Label3Click
  end
  object Image1: TImage
    Left = 5
    Top = 200
    Width = 311
    Height = 265
    OnMouseMove = Image1MouseMove
  end
  object Button8: TLabel
    Left = 517
    Top = 339
    Width = 74
    Height = 16
    Cursor = crHandPoint
    Caption = 'Load FPC file'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    OnClick = Button8Click
  end
  object Label10: TLabel
    Left = 327
    Top = 421
    Width = 44
    Height = 16
    Caption = 'Label10'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Edit1: TEdit
    Left = 4
    Top = 3
    Width = 283
    Height = 24
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnChange = Edit1Change
  end
  object GroupBox1: TGroupBox
    Left = 324
    Top = 275
    Width = 168
    Height = 118
    Caption = 'Sorting style'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object Sort_ABC: TRadioButton
      Left = 5
      Top = 21
      Width = 130
      Height = 17
      Caption = 'Alphabetically'
      TabOrder = 0
      OnClick = Sort_ABCClick
    end
    object Sort_n_pins: TRadioButton
      Left = 5
      Top = 40
      Width = 154
      Height = 17
      Caption = 'The number of pins'
      TabOrder = 1
      OnClick = Sort_n_pinsClick
    end
    object Sort_n_holes: TRadioButton
      Left = 5
      Top = 61
      Width = 154
      Height = 11
      Caption = 'The number of holes'
      TabOrder = 2
      OnClick = Sort_n_holesClick
    end
    object Sort_author: TRadioButton
      Left = 5
      Top = 76
      Width = 113
      Height = 17
      Caption = 'Author'
      TabOrder = 3
      OnClick = Sort_authorClick
    end
    object Sort_desc: TRadioButton
      Left = 5
      Top = 97
      Width = 122
      Height = 11
      Caption = 'Description'
      TabOrder = 4
      OnClick = Sort_descClick
    end
    object R: TButton
      Left = 143
      Top = 91
      Width = 17
      Height = 17
      Caption = 'R'
      TabOrder = 5
      OnClick = RClick
    end
  end
  object Button1: TButton
    Left = 292
    Top = 2
    Width = 23
    Height = 25
    Caption = '...'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = Button1Click
  end
  object GroupBox3: TGroupBox
    Left = 6
    Top = 31
    Width = 311
    Height = 165
    Caption = 'Filter'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    object Label7: TLabel
      Left = 8
      Top = 16
      Width = 38
      Height = 16
      Caption = 'Name:'
    end
    object Label8: TLabel
      Left = 147
      Top = 17
      Width = 35
      Height = 16
      Caption = 'nPins:'
    end
    object Label9: TLabel
      Left = 225
      Top = 16
      Width = 43
      Height = 16
      Caption = 'nHoles:'
    end
    object SpeedButton3: TSpeedButton
      Left = 229
      Top = 142
      Width = 74
      Height = 18
      Caption = 'Delete'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      OnClick = SpeedButton3Click
    end
    object ListBox1: TListBox
      Left = 7
      Top = 38
      Width = 297
      Height = 103
      ItemHeight = 16
      Sorted = True
      TabOrder = 0
      OnClick = ListBox1Click
      OnDblClick = ListBox1DblClick
    end
    object Edit2: TEdit
      Left = 53
      Top = 14
      Width = 91
      Height = 20
      AutoSize = False
      TabOrder = 1
      OnChange = Edit2Change
    end
    object Edit3: TEdit
      Left = 184
      Top = 14
      Width = 35
      Height = 20
      AutoSize = False
      TabOrder = 2
      OnChange = Edit3Change
    end
    object Edit4: TEdit
      Left = 269
      Top = 14
      Width = 35
      Height = 20
      AutoSize = False
      TabOrder = 3
      OnChange = Edit4Change
    end
    object bOpenPDF: TButton
      Left = 81
      Top = 142
      Width = 74
      Height = 18
      Caption = 'Open PDF'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = bOpenPDFClick
    end
    object bOpenLib: TButton
      Left = 155
      Top = 142
      Width = 74
      Height = 18
      Caption = 'Open Lib'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = bOpenLibClick
    end
    object bEditFoot: TButton
      Left = 7
      Top = 142
      Width = 74
      Height = 18
      Caption = 'Edit'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      OnClick = bEditFootClick
    end
  end
  object Sname: TListBox
    Left = 291
    Top = 322
    Width = 25
    Height = 25
    ItemHeight = 16
    TabOrder = 4
  end
  object Spins: TListBox
    Left = 267
    Top = 322
    Width = 25
    Height = 25
    ItemHeight = 16
    TabOrder = 5
  end
  object Sholes: TListBox
    Left = 243
    Top = 322
    Width = 25
    Height = 25
    ItemHeight = 16
    TabOrder = 6
  end
  object ListBox5: TListBox
    Left = 171
    Top = 322
    Width = 25
    Height = 25
    ItemHeight = 16
    TabOrder = 7
  end
  object ListBox6: TListBox
    Left = 11
    Top = 320
    Width = 86
    Height = 33
    ItemHeight = 16
    TabOrder = 8
    Visible = False
  end
  object Sauthor: TListBox
    Left = 219
    Top = 322
    Width = 25
    Height = 25
    ItemHeight = 16
    TabOrder = 9
  end
  object Sdescript: TListBox
    Left = 195
    Top = 322
    Width = 25
    Height = 25
    ItemHeight = 16
    TabOrder = 10
  end
  object GroupBox2: TGroupBox
    Left = 499
    Top = 275
    Width = 119
    Height = 51
    Caption = 'Sorting'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 11
    object Button2: TButton
      Left = 5
      Top = 18
      Width = 108
      Height = 25
      Caption = 'Rewrite all lib'
      TabOrder = 0
      OnClick = Button2Click
    end
  end
  object GroupBox4: TGroupBox
    Left = 321
    Top = 216
    Width = 297
    Height = 57
    Caption = '      Pad style Filter'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 12
    object RadioButton6: TRadioButton
      Left = 7
      Top = 17
      Width = 56
      Height = 17
      Caption = 'none'
      Checked = True
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      TabStop = True
      OnClick = RadioButton6Click
    end
    object RadioButton7: TRadioButton
      Left = 83
      Top = 18
      Width = 58
      Height = 17
      Caption = 'round'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = RadioButton7Click
    end
    object RadioButton8: TRadioButton
      Left = 7
      Top = 32
      Width = 74
      Height = 17
      Caption = 'square'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = RadioButton8Click
    end
    object RadioButton9: TRadioButton
      Left = 151
      Top = 19
      Width = 53
      Height = 17
      Caption = 'rect'
      TabOrder = 3
      OnClick = RadioButton9Click
    end
    object RadioButton10: TRadioButton
      Left = 213
      Top = 19
      Width = 66
      Height = 17
      Caption = 'rndrect'
      TabOrder = 4
      OnClick = RadioButton10Click
    end
    object RadioButton11: TRadioButton
      Left = 83
      Top = 33
      Width = 57
      Height = 17
      Caption = 'oval'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = RadioButton11Click
    end
    object RadioButton12: TRadioButton
      Left = 151
      Top = 34
      Width = 84
      Height = 17
      Caption = 'octagon'
      TabOrder = 6
      OnClick = RadioButton12Click
    end
    object CheckBox2: TCheckBox
      Left = 8
      Top = -2
      Width = 15
      Height = 17
      TabOrder = 7
      OnClick = CheckBox2Click
    end
  end
  object bCombFoot: TButton
    Left = 321
    Top = 135
    Width = 136
    Height = 18
    Caption = 'Combine footprints'
    Enabled = False
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 13
    OnClick = bCombFootClick
  end
  object bAddRefStr: TButton
    Left = 460
    Top = 135
    Width = 157
    Height = 18
    Caption = 'Add String to References'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 14
    OnClick = bAddRefStrClick
  end
  object bAddShapeStr: TButton
    Left = 321
    Top = 155
    Width = 296
    Height = 18
    Caption = 'Add String to Footprint name for panelization'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 15
    OnClick = bAddShapeStrClick
  end
  object Button6: TButton
    Left = 321
    Top = 173
    Width = 296
    Height = 18
    Caption = 'Replace selected Footprint in current File'
    Enabled = False
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 16
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 321
    Top = 191
    Width = 296
    Height = 18
    Caption = 'Replace all footprints in current File'
    Enabled = False
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 17
    OnClick = Button7Click
  end
  object GroupBox5: TGroupBox
    Left = 322
    Top = 4
    Width = 297
    Height = 121
    Caption = 'Selected'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 18
    object Label5: TLabel
      Left = 8
      Top = 21
      Width = 56
      Height = 16
      Caption = 'FootPrint:'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 8
      Top = 68
      Width = 43
      Height = 16
      Caption = 'Author:'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label12: TLabel
      Left = 6
      Top = 91
      Width = 68
      Height = 16
      Caption = 'Description:'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 8
      Top = 44
      Width = 52
      Height = 16
      Caption = 'Package:'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object NameEdit: TEdit
      Left = 83
      Top = 16
      Width = 153
      Height = 24
      TabOrder = 0
    end
    object Mod: TButton
      Left = 240
      Top = 16
      Width = 47
      Height = 97
      Caption = 'Mod'
      TabOrder = 1
      OnClick = ModClick
    end
    object PackageEdit: TEdit
      Left = 83
      Top = 40
      Width = 153
      Height = 24
      TabOrder = 2
    end
    object AuthorEdit: TComboBox
      Left = 83
      Top = 64
      Width = 153
      Height = 24
      ItemHeight = 16
      Sorted = True
      TabOrder = 3
    end
    object DescEdit: TComboBox
      Left = 83
      Top = 88
      Width = 153
      Height = 24
      ItemHeight = 16
      Sorted = True
      TabOrder = 4
    end
  end
  object CheckBox1: TCheckBox
    Left = 327
    Top = 398
    Width = 130
    Height = 17
    Caption = 'Show duplicates'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 19
    OnClick = CheckBox1Click
  end
  object Button3: TButton
    Left = 279
    Top = 432
    Width = 25
    Height = 25
    Caption = '>>'
    TabOrder = 20
    OnClick = Button3Click
  end
  object bPaste: TButton
    Left = 15
    Top = 432
    Width = 58
    Height = 25
    Caption = 'Paste'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 21
    Visible = False
    OnClick = bPasteClick
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 200
    OnTimer = Timer2Timer
    Left = 135
    Top = 320
  end
  object OpenDialog1: TOpenDialog
    Filter = 'Print Cirquit  Board (FPC)|*.fpc'
    Left = 103
    Top = 320
  end
end
