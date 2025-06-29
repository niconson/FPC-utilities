object Form1: TForm1
  Left = 926
  Top = 94
  BorderStyle = bsDialog
  Caption = 'BMP to FreePCB file translator '
  ClientHeight = 644
  ClientWidth = 424
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 16
  object Link: TLabel
    Left = 304
    Top = 336
    Width = 97
    Height = 13
    Cursor = crHandPoint
    Caption = 'www.freepcb.dev'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
    Transparent = True
    OnClick = LinkClick
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 360
    Width = 409
    Height = 273
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 37
      Top = 117
      Width = 22
      Height = 13
      Caption = 'RED'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 103
      Top = 117
      Width = 35
      Height = 13
      Caption = 'GREEN'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 180
      Top = 117
      Width = 27
      Height = 13
      Caption = 'BLUE'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label6: TLabel
      Left = 20
      Top = 225
      Width = 103
      Height = 13
      Caption = 'Process Messages'
    end
    object Button1: TButton
      Left = 240
      Top = 100
      Width = 153
      Height = 27
      Caption = 'Update Canvas'
      TabOrder = 0
      OnClick = Button1Click
    end
    object TrackBar1: TTrackBar
      Left = 8
      Top = 85
      Width = 81
      Height = 33
      Max = 255
      Orientation = trHorizontal
      Frequency = 15
      Position = 128
      SelEnd = 0
      SelStart = 0
      TabOrder = 1
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = TrackBar1Change
    end
    object TrackBar2: TTrackBar
      Left = 80
      Top = 85
      Width = 81
      Height = 33
      Max = 255
      Orientation = trHorizontal
      Frequency = 15
      Position = 128
      SelEnd = 0
      SelStart = 0
      TabOrder = 2
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = TrackBar2Change
    end
    object TrackBar3: TTrackBar
      Left = 152
      Top = 85
      Width = 81
      Height = 33
      Max = 255
      Orientation = trHorizontal
      Frequency = 15
      Position = 128
      SelEnd = 0
      SelStart = 0
      TabOrder = 3
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = TrackBar3Change
    end
    object Button2: TButton
      Left = 324
      Top = 141
      Width = 69
      Height = 74
      Caption = 'OK'
      TabOrder = 4
      OnClick = Button2Click
    end
    object GroupBox2: TGroupBox
      Left = 15
      Top = 18
      Width = 209
      Height = 57
      Caption = 'Size of the finished picture (mm)'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      object Label4: TLabel
        Left = 16
        Top = 27
        Width = 16
        Height = 13
        Caption = 'X='
      end
      object Label5: TLabel
        Left = 104
        Top = 27
        Width = 16
        Height = 13
        Caption = 'Y='
      end
      object Edit1: TEdit
        Left = 40
        Top = 23
        Width = 49
        Height = 21
        TabOrder = 0
        Text = '10,0'
        OnChange = Edit1Change
      end
      object Edit2: TEdit
        Left = 128
        Top = 23
        Width = 49
        Height = 21
        TabOrder = 1
        Text = '10,0'
        OnChange = Edit2Change
      end
    end
    object GroupBox3: TGroupBox
      Left = 240
      Top = 18
      Width = 153
      Height = 73
      Caption = 'Pen width'
      TabOrder = 6
      object RadioButton1: TRadioButton
        Left = 8
        Top = 21
        Width = 121
        Height = 17
        Caption = 'Automatically'
        TabOrder = 0
        OnClick = RadioButton1Click
      end
      object RadioButton2: TRadioButton
        Left = 8
        Top = 44
        Width = 81
        Height = 17
        Caption = 'Set(mm)'
        TabOrder = 1
        OnClick = RadioButton2Click
      end
      object Edit3: TEdit
        Left = 100
        Top = 43
        Width = 41
        Height = 21
        TabOrder = 2
        OnChange = Edit3Change
      end
    end
    object GroupBox4: TGroupBox
      Left = 159
      Top = 136
      Width = 153
      Height = 81
      Caption = 'Options'
      TabOrder = 7
      object CheckBox1: TCheckBox
        Left = 8
        Top = 20
        Width = 73
        Height = 17
        Caption = 'Contour'
        TabOrder = 0
        OnClick = CheckBox1Click
      end
      object CheckBox2: TCheckBox
        Left = 8
        Top = 56
        Width = 97
        Height = 17
        Caption = 'Poured:  1/'
        TabOrder = 1
        OnClick = CheckBox2Click
      end
      object CheckBox3: TCheckBox
        Left = 24
        Top = 38
        Width = 57
        Height = 17
        Caption = 'RND'
        TabOrder = 2
        OnClick = CheckBox3Click
      end
      object ComboBox1: TComboBox
        Left = 96
        Top = 52
        Width = 49
        Height = 21
        ItemHeight = 13
        TabOrder = 3
        OnChange = ComboBox1Change
      end
    end
    object GroupBox5: TGroupBox
      Left = 9
      Top = 136
      Width = 145
      Height = 81
      Caption = 'Layer'
      TabOrder = 8
      object RadioButton3: TRadioButton
        Left = 24
        Top = 20
        Width = 105
        Height = 17
        Caption = 'Copper Pads'
        TabOrder = 0
        OnClick = RadioButton3Click
      end
      object RadioButton4: TRadioButton
        Left = 24
        Top = 55
        Width = 105
        Height = 17
        Caption = 'Silkscreen'
        Checked = True
        TabOrder = 1
        TabStop = True
        OnClick = RadioButton4Click
      end
      object RadioButton5: TRadioButton
        Left = 24
        Top = 37
        Width = 105
        Height = 17
        Caption = 'Copper Lines'
        TabOrder = 2
        OnClick = RadioButton5Click
      end
    end
    object FPC: TRadioButton
      Left = 19
      Top = 251
      Width = 110
      Height = 17
      Caption = 'FreePcb-2.033'
      Checked = True
      TabOrder = 9
      TabStop = True
    end
    object FRS: TRadioButton
      Left = 171
      Top = 251
      Width = 184
      Height = 17
      Caption = 'Schematic Constructor v 1.0'
      TabOrder = 10
    end
  end
  object OpenPictureDialog1: TOpenPictureDialog
    Filter = 'Bitmaps (*.bmp)|*.bmp'
    Left = 280
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 500
    OnTimer = Timer1Timer
    Left = 248
  end
end
