object Form1: TForm1
  Left = 765
  Top = 247
  BorderStyle = bsDialog
  Caption = 'Insert Nets'
  ClientHeight = 415
  ClientWidth = 422
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Courier New'
  Font.Style = [fsBold]
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 16
  object Label3: TLabel
    Left = 32
    Top = 80
    Width = 40
    Height = 16
    Caption = 'Width'
  end
  object Label4: TLabel
    Left = 32
    Top = 104
    Width = 48
    Height = 16
    Caption = 'Heigth'
  end
  object Label5: TLabel
    Left = 304
    Top = 393
    Width = 63
    Height = 14
    Cursor = crHandPoint
    Caption = 'Freepcb-2'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
    OnClick = Label5Click
  end
  object Label6: TLabel
    Left = 216
    Top = 80
    Width = 88
    Height = 16
    Caption = 'nano-Meters'
  end
  object Label7: TLabel
    Left = 216
    Top = 104
    Width = 88
    Height = 16
    Caption = 'nano-Meters'
  end
  object Edit3: TEdit
    Left = 136
    Top = 75
    Width = 73
    Height = 24
    TabOrder = 0
    Text = '300000'
  end
  object Edit4: TEdit
    Left = 136
    Top = 99
    Width = 73
    Height = 24
    TabOrder = 1
    Text = '2000000'
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 128
    Width = 393
    Height = 265
    Caption = 'Please select nets and layer Info'
    TabOrder = 2
    object ListBox1: TListBox
      Left = 200
      Top = 24
      Width = 177
      Height = 225
      ItemHeight = 16
      TabOrder = 0
    end
    object ListBox3: TListBox
      Left = 16
      Top = 24
      Width = 177
      Height = 161
      ItemHeight = 16
      TabOrder = 1
    end
    object Button2: TButton
      Left = 16
      Top = 224
      Width = 177
      Height = 25
      Caption = 'Unselect Nxxxxx'
      TabOrder = 2
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 16
      Top = 192
      Width = 177
      Height = 25
      Caption = 'Select All'
      TabOrder = 3
      OnClick = Button3Click
    end
  end
  object Button1: TButton
    Left = 328
    Top = 88
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 3
    OnClick = Button1Click
  end
  object ListBox2: TListBox
    Left = 312
    Top = 96
    Width = 25
    Height = 25
    ItemHeight = 16
    TabOrder = 4
    Visible = False
  end
  object ToRight: TCheckBox
    Left = 32
    Top = 8
    Width = 369
    Height = 17
    Caption = 'Insert texts to the right of board outline'
    Checked = True
    State = cbChecked
    TabOrder = 5
    OnMouseUp = ToRightMouseUp
  end
  object Below: TCheckBox
    Left = 32
    Top = 32
    Width = 377
    Height = 17
    Caption = 'Insert texts below board outline'
    TabOrder = 6
    OnMouseUp = BelowMouseUp
  end
  object OpenDialog1: TOpenDialog
    Filter = 'FreePCB file FPC|*.fpc'
    Left = 384
    Top = 96
  end
end
