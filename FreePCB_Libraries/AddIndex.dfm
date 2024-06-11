object Form2: TForm2
  Left = 260
  Top = 301
  BorderIcons = [biSystemMenu, biHelp]
  BorderStyle = bsDialog
  Caption = 'FreePcb - Add string'
  ClientHeight = 304
  ClientWidth = 322
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Arial'
  Font.Style = [fsBold]
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 16
  object OK_ADD_STR: TButton
    Left = 8
    Top = 272
    Width = 105
    Height = 25
    Caption = 'OK'
    TabOrder = 0
    OnClick = OK_ADD_STRClick
  end
  object GroupBox1: TGroupBox
    Left = 2
    Top = 1
    Width = 319
    Height = 57
    TabOrder = 1
    object RadioButtonRef: TCheckBox
      Left = 32
      Top = 24
      Width = 97
      Height = 17
      Caption = 'Reference'
      TabOrder = 0
    end
    object RadioButtonShape: TCheckBox
      Left = 192
      Top = 24
      Width = 97
      Height = 17
      Caption = 'Shape'
      TabOrder = 1
    end
  end
  object GroupBox2: TGroupBox
    Left = 2
    Top = 64
    Width = 319
    Height = 201
    TabOrder = 2
    object AddStr: TRadioButton
      Left = 16
      Top = 24
      Width = 105
      Height = 17
      Caption = 'Add string'
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = AddStrClick
    end
    object DelStr: TRadioButton
      Left = 16
      Top = 48
      Width = 113
      Height = 17
      Caption = 'Delete string'
      TabOrder = 1
      OnClick = AddStrClick
    end
    object GroupBox3: TGroupBox
      Left = 152
      Top = 8
      Width = 153
      Height = 105
      TabOrder = 2
      object Label1: TLabel
        Left = 11
        Top = 67
        Width = 38
        Height = 16
        Caption = 'String'
      end
      object RadioButtonBegin: TRadioButton
        Left = 8
        Top = 16
        Width = 113
        Height = 17
        Caption = 'String to begin'
        Checked = True
        TabOrder = 0
        TabStop = True
      end
      object RadioButtonEnd: TRadioButton
        Left = 8
        Top = 40
        Width = 113
        Height = 17
        Caption = 'String to end'
        TabOrder = 1
      end
      object Edit1: TEdit
        Left = 56
        Top = 65
        Width = 81
        Height = 24
        TabOrder = 2
      end
    end
    object GroupBox4: TGroupBox
      Left = 152
      Top = 112
      Width = 153
      Height = 81
      TabOrder = 3
      object Label2: TLabel
        Left = 15
        Top = 20
        Width = 22
        Height = 16
        Caption = 'Old'
      end
      object Label3: TLabel
        Left = 13
        Top = 52
        Width = 28
        Height = 16
        Caption = 'New'
      end
      object Edit2: TEdit
        Left = 56
        Top = 17
        Width = 81
        Height = 24
        TabOrder = 0
      end
      object Edit3: TEdit
        Left = 56
        Top = 49
        Width = 81
        Height = 24
        TabOrder = 1
      end
    end
    object ReplaceStr: TRadioButton
      Left = 16
      Top = 122
      Width = 113
      Height = 17
      Caption = 'Replace string'
      TabOrder = 4
      OnClick = ReplaceStrClick
    end
    object InEnd: TCheckBox
      Left = 33
      Top = 146
      Width = 116
      Height = 17
      Caption = 'In end only'
      TabOrder = 5
    end
    object InBegin: TCheckBox
      Left = 33
      Top = 170
      Width = 117
      Height = 17
      Caption = 'In begin only'
      TabOrder = 6
    end
  end
  object ReplaceOrigFile: TCheckBox
    Left = 152
    Top = 275
    Width = 161
    Height = 17
    Caption = 'Replace original file'
    TabOrder = 3
  end
end
