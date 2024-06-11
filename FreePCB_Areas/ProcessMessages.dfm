object Form3: TForm3
  Left = 814
  Top = 347
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  ClientHeight = 138
  ClientWidth = 436
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = [fsBold, fsItalic]
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 16
  object GroupBox1: TGroupBox
    Left = 10
    Top = 8
    Width = 415
    Height = 65
    Caption = 'Process Messages'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 32
      Top = 32
      Width = 47
      Height = 16
      Caption = 'Begin...'
    end
    object Label3: TLabel
      Left = 273
      Top = 32
      Width = 8
      Height = 16
      Caption = '0'
    end
    object Label2: TLabel
      Left = 323
      Top = 32
      Width = 30
      Height = 16
      Caption = 'from'
    end
    object Label4: TLabel
      Left = 361
      Top = 32
      Width = 8
      Height = 16
      Caption = '0'
    end
  end
  object Area: TListBox
    Left = 162
    Top = 104
    Width = 31
    Height = 25
    ItemHeight = 16
    TabOrder = 1
    Visible = False
  end
  object ProgressBar1: TProgressBar
    Left = 10
    Top = 80
    Width = 415
    Height = 16
    Min = 0
    Max = 100
    Step = 1
    TabOrder = 2
  end
  object Button1: TButton
    Left = 352
    Top = 104
    Width = 75
    Height = 25
    Caption = 'Abort'
    TabOrder = 3
    OnClick = Button1Click
  end
end
