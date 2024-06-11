object Form3: TForm3
  Left = 665
  Top = 133
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Editing mode'
  ClientHeight = 513
  ClientWidth = 411
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Arial'
  Font.Style = [fsBold]
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 16
  object Label1: TLabel
    Left = 16
    Top = 8
    Width = 46
    Height = 16
    Caption = 'Old net'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 224
    Top = 8
    Width = 52
    Height = 16
    Caption = 'New net'
  end
  object OLD: TListBox
    Left = 16
    Top = 24
    Width = 169
    Height = 409
    ItemHeight = 16
    MultiSelect = True
    TabOrder = 0
  end
  object NEW: TListBox
    Left = 224
    Top = 24
    Width = 169
    Height = 409
    ItemHeight = 16
    MultiSelect = True
    TabOrder = 1
  end
  object Button1: TButton
    Left = 192
    Top = 32
    Width = 25
    Height = 25
    Caption = '>>'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 192
    Top = 80
    Width = 25
    Height = 25
    Caption = '<<'
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 168
    Top = 448
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 4
    OnClick = Button3Click
  end
  object Indexes: TListBox
    Left = 16
    Top = 448
    Width = 25
    Height = 25
    ItemHeight = 16
    TabOrder = 5
    Visible = False
  end
  object CheckBox1: TCheckBox
    Left = 16
    Top = 485
    Width = 225
    Height = 17
    Caption = 'Copy file to the project folder'
    Checked = True
    State = cbChecked
    TabOrder = 6
  end
end
