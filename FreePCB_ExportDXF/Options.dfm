object Form3: TForm3
  Left = 906
  Top = 392
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Options'
  ClientHeight = 286
  ClientWidth = 184
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 54
    Height = 13
    Caption = 'Board thick'
  end
  object Label2: TLabel
    Left = 152
    Top = 16
    Width = 16
    Height = 13
    Caption = 'mm'
  end
  object Label3: TLabel
    Left = 16
    Top = 65
    Width = 72
    Height = 13
    Caption = 'Filling with lines'
  end
  object Edit1: TEdit
    Left = 96
    Top = 12
    Width = 49
    Height = 21
    TabOrder = 0
    Text = '1.5'
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 92
    Width = 153
    Height = 89
    Caption = 'Lines style'
    TabOrder = 1
    object RadioButton1: TRadioButton
      Left = 32
      Top = 19
      Width = 113
      Height = 17
      Caption = 'PolyFace'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object RadioButton2: TRadioButton
      Left = 32
      Top = 65
      Width = 113
      Height = 17
      Caption = 'Unpoured'
      TabOrder = 1
    end
    object RadioButton5: TRadioButton
      Left = 32
      Top = 42
      Width = 113
      Height = 17
      Caption = 'PolyLine'
      TabOrder = 2
    end
  end
  object ComboBox1: TComboBox
    Left = 96
    Top = 62
    Width = 49
    Height = 21
    ItemHeight = 13
    TabOrder = 2
    Items.Strings = (
      '1'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7')
  end
  object GroupBox2: TGroupBox
    Left = 16
    Top = 186
    Width = 153
    Height = 65
    Caption = 'Object style'
    TabOrder = 3
    object RadioButton3: TRadioButton
      Left = 32
      Top = 19
      Width = 113
      Height = 17
      Caption = '3dFace'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object RadioButton4: TRadioButton
      Left = 32
      Top = 41
      Width = 113
      Height = 17
      Caption = 'Unpoured'
      TabOrder = 1
    end
  end
  object CheckBox1: TCheckBox
    Left = 48
    Top = 259
    Width = 97
    Height = 17
    Caption = 'Total rect'
    TabOrder = 4
  end
  object BPoured: TCheckBox
    Left = 48
    Top = 40
    Width = 97
    Height = 17
    Caption = 'Board poured'
    TabOrder = 5
  end
end