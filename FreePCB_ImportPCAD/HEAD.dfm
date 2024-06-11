object Form1: TForm1
  Left = 410
  Top = 190
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Accel Tango to FreePcb '
  ClientHeight = 370
  ClientWidth = 534
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
  object Label5: TLabel
    Left = 137
    Top = 342
    Width = 44
    Height = 13
    Caption = 'Strings: 0'
  end
  object Label3: TLabel
    Left = 10
    Top = 341
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
    OnClick = Label3Click
  end
  object Button1: TButton
    Left = 323
    Top = 336
    Width = 137
    Height = 25
    Caption = 'Start conversion'
    TabOrder = 0
    OnClick = Button1Click
  end
  object GroupBox1: TGroupBox
    Left = 2
    Top = 0
    Width = 530
    Height = 105
    Caption = 'Path'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    object Label1: TLabel
      Left = 16
      Top = 28
      Width = 41
      Height = 13
      Caption = 'PCB file'
    end
    object Label2: TLabel
      Left = 16
      Top = 68
      Width = 40
      Height = 13
      Caption = 'FPC file'
    end
    object Edit1: TEdit
      Left = 88
      Top = 24
      Width = 401
      Height = 21
      TabOrder = 0
      Text = 'P-CAD ASCII Input File'
      OnChange = Edit1Change
    end
    object Edit2: TEdit
      Left = 88
      Top = 64
      Width = 401
      Height = 21
      TabOrder = 1
      Text = 'FreePcb Output File'
      OnChange = Edit2Change
    end
    object Button2: TButton
      Left = 496
      Top = 24
      Width = 25
      Height = 25
      Caption = '...'
      TabOrder = 2
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 496
      Top = 64
      Width = 25
      Height = 25
      Caption = '...'
      TabOrder = 3
      OnClick = Button3Click
    end
  end
  object GroupBox3: TGroupBox
    Left = 2
    Top = 272
    Width = 530
    Height = 57
    Caption = 'Process'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    object Label4: TLabel
      Left = 24
      Top = 24
      Width = 56
      Height = 13
      Caption = 'Messages'
    end
  end
  object Button4: TButton
    Left = 467
    Top = 336
    Width = 57
    Height = 25
    Caption = 'Pins'
    TabOrder = 3
    OnClick = Button4Click
  end
  object ListBox1: TListBox
    Left = 8
    Top = 256
    Width = 33
    Height = 25
    ItemHeight = 13
    TabOrder = 4
    Visible = False
  end
  object ListBox2: TListBox
    Left = 48
    Top = 256
    Width = 33
    Height = 25
    ItemHeight = 13
    TabOrder = 5
    Visible = False
  end
  object ListBox3_TEXTS: TListBox
    Left = 88
    Top = 256
    Width = 33
    Height = 25
    ItemHeight = 13
    TabOrder = 6
    Visible = False
  end
  object ListBox4_Lines: TListBox
    Left = 128
    Top = 256
    Width = 33
    Height = 25
    ItemHeight = 13
    TabOrder = 7
    Visible = False
  end
  object Library: TListBox
    Left = 168
    Top = 256
    Width = 33
    Height = 25
    ItemHeight = 13
    TabOrder = 8
    Visible = False
  end
  object GroupBox4: TGroupBox
    Left = 2
    Top = 112
    Width = 530
    Height = 153
    Caption = 'Options'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 9
    object Label7: TLabel
      Left = 24
      Top = 20
      Width = 168
      Height = 13
      Caption = 'Increment for arcs (degrees):'
    end
    object Label6: TLabel
      Left = 24
      Top = 80
      Width = 281
      Height = 13
      Caption = 'Mask clearance for Pads specified by polygon:'
    end
    object ComboBox3: TComboBox
      Left = 24
      Top = 40
      Width = 73
      Height = 21
      ItemHeight = 13
      TabOrder = 0
    end
    object ComboBox2: TComboBox
      Left = 24
      Top = 100
      Width = 73
      Height = 21
      ItemHeight = 13
      TabOrder = 1
    end
    object GroupBox2: TGroupBox
      Left = 355
      Top = 17
      Width = 158
      Height = 121
      Caption = 'Move to board layer'
      TabOrder = 2
      object TopPaste_2_Board: TCheckBox
        Left = 10
        Top = 81
        Width = 113
        Height = 18
        Caption = 'Top Paste lines'
        TabOrder = 0
      end
      object BotPaste_2_Board: TCheckBox
        Left = 10
        Top = 97
        Width = 137
        Height = 17
        Caption = 'Bottom Paste lines'
        TabOrder = 1
      end
      object TopAssy_2_Board: TCheckBox
        Left = 10
        Top = 51
        Width = 121
        Height = 17
        Caption = 'Top Assy lines'
        TabOrder = 2
      end
      object BotAssy_2_Board: TCheckBox
        Left = 10
        Top = 67
        Width = 127
        Height = 16
        Caption = 'Bottom Assy lines '
        TabOrder = 3
      end
      object TopSilk_2_Board: TCheckBox
        Left = 10
        Top = 19
        Width = 121
        Height = 17
        Caption = 'Top Silk lines'
        TabOrder = 4
      end
      object BotSilk_2_Board: TCheckBox
        Left = 10
        Top = 35
        Width = 129
        Height = 17
        Caption = 'Bottom Silk lines'
        TabOrder = 5
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'P-cad ASCII|*.pcb'
    Left = 320
    Top = 312
  end
  object SaveDialog1: TSaveDialog
    Left = 352
    Top = 312
  end
end
