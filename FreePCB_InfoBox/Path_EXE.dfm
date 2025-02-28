object Form2: TForm2
  Left = 458
  Top = 164
  BorderStyle = bsDialog
  Caption = 'Settings'
  ClientHeight = 465
  ClientWidth = 768
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  FormStyle = fsStayOnTop
  Icon.Data = {
    0000010001001010100000000000280100001600000028000000100000002000
    0000010004000000000080000000000000000000000000000000000000000000
    0000000080000080000000808000800000008000800080800000C0C0C0008080
    80000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF002222
    992222992222222299222299222222229922229922222222992222992222AAAA
    AAAAAAAAAAAAAAAAAAAAAAAAAAAA222299222299222222229922229922222222
    992222EE2222222299222EEEE222AAAAAAAAEE00EE22AAAAAAAAEE00EE222222
    99222EEEE2222222992222EE2222222299222222222222229922222222220000
    2222000022220000229900002992000022220000222200002299000029920000
    222200002222000022990000299200002222000022220000229900002992}
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 16
  object Label1: TLabel
    Left = 660
    Top = 439
    Width = 57
    Height = 13
    Cursor = crHandPoint
    Caption = 'Freepcb-2'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
    OnClick = Label1Click
  end
  object GroupBoxPath: TGroupBox
    Left = 8
    Top = 8
    Width = 457
    Height = 145
    TabOrder = 0
    object GroupBox2: TGroupBox
      Left = 16
      Top = 16
      Width = 153
      Height = 105
      Caption = 'Embed'
      TabOrder = 0
      object OnTop: TRadioButton
        Left = 16
        Top = 24
        Width = 113
        Height = 17
        Caption = 'on top'
        TabOrder = 0
      end
      object OnTheRight: TRadioButton
        Left = 16
        Top = 40
        Width = 113
        Height = 17
        Caption = 'on the right'
        TabOrder = 1
      end
      object FreePos: TRadioButton
        Left = 16
        Top = 72
        Width = 113
        Height = 17
        Caption = 'free position'
        Checked = True
        TabOrder = 2
        TabStop = True
      end
      object FromBelow: TRadioButton
        Left = 16
        Top = 56
        Width = 113
        Height = 17
        Caption = 'from below'
        TabOrder = 3
      end
    end
    object GroupBox3: TGroupBox
      Left = 184
      Top = 16
      Width = 257
      Height = 105
      Caption = 'Options'
      TabOrder = 1
      object IgnoreCase: TCheckBox
        Left = 19
        Top = 56
        Width = 230
        Height = 17
        Caption = 'Ignore case in the filter'
        TabOrder = 0
      end
      object Language: TCheckBox
        Left = 19
        Top = 40
        Width = 230
        Height = 17
        Caption = #1056#1091#1089#1089#1082#1080#1081' '#1080#1085#1090#1077#1088#1092#1077#1081#1089
        TabOrder = 1
        OnClick = LanguageClick
      end
      object OnlyLatin: TCheckBox
        Left = 19
        Top = 24
        Width = 230
        Height = 17
        Caption = 'Only Latin symbols'
        TabOrder = 2
      end
    end
  end
  object GroupBox1: TGroupBox
    Left = 472
    Top = 8
    Width = 289
    Height = 425
    Caption = 'Control'
    TabOrder = 1
    object Memo1: TMemo
      Left = 8
      Top = 16
      Width = 273
      Height = 401
      Color = clBtnFace
      Lines.Strings = (
        'For quick editing, some FREEPCB function '
        'keys work in INFOBOX. From the REF '
        'search string or after clicking the mouse '
        'on the selected part, you can run:'
        'F1 - Open part properties'
        'F4 - Move part to center of screen')
      TabOrder = 0
    end
  end
  object mem_pos_wnd: TCheckBox
    Left = 259
    Top = 439
    Width = 369
    Height = 17
    Caption = 'Remember size and position of the InfoBox window'
    TabOrder = 2
  end
  object GroupBox4: TGroupBox
    Left = 8
    Top = 160
    Width = 241
    Height = 297
    Caption = 'Part columns'
    TabOrder = 3
    object check_refs: TCheckBox
      Left = 16
      Top = 24
      Width = 150
      Height = 17
      Caption = 'Part References'
      TabOrder = 0
    end
    object check_ref_index: TCheckBox
      Left = 16
      Top = 40
      Width = 150
      Height = 17
      Caption = 'Part Ref Indexes'
      TabOrder = 1
    end
    object check_values: TCheckBox
      Left = 16
      Top = 56
      Width = 150
      Height = 17
      Caption = 'Part Values'
      TabOrder = 2
    end
    object check_valuesNL: TCheckBox
      Left = 16
      Top = 72
      Width = 209
      Height = 17
      Caption = 'Values in external netlist'
      TabOrder = 3
    end
    object check_package: TCheckBox
      Left = 16
      Top = 120
      Width = 145
      Height = 17
      Caption = 'Part Packages'
      TabOrder = 4
    end
    object check_foot: TCheckBox
      Left = 16
      Top = 88
      Width = 150
      Height = 17
      Caption = 'Part Footprints'
      TabOrder = 5
    end
    object check_packageNL: TCheckBox
      Left = 16
      Top = 104
      Width = 209
      Height = 17
      Caption = 'Footprints in external netlist'
      TabOrder = 6
    end
    object check_merge: TCheckBox
      Left = 16
      Top = 136
      Width = 150
      Height = 17
      Caption = 'Part Merges'
      TabOrder = 7
    end
    object check_parts_pins: TCheckBox
      Left = 16
      Top = 152
      Width = 150
      Height = 17
      Caption = 'Part Pin Count'
      TabOrder = 8
    end
    object check_parts_holes: TCheckBox
      Left = 16
      Top = 168
      Width = 150
      Height = 17
      Caption = 'Part Holes'
      TabOrder = 9
    end
    object check_glueds: TCheckBox
      Left = 16
      Top = 184
      Width = 150
      Height = 17
      Caption = 'Part Glueds'
      TabOrder = 10
    end
    object check_sides: TCheckBox
      Left = 16
      Top = 200
      Width = 150
      Height = 17
      Caption = 'Part Sides'
      TabOrder = 11
    end
    object check_angles: TCheckBox
      Left = 16
      Top = 216
      Width = 150
      Height = 17
      Caption = 'Part angles'
      TabOrder = 12
    end
    object check_partx: TCheckBox
      Left = 16
      Top = 232
      Width = 150
      Height = 17
      Caption = 'Part X'
      TabOrder = 13
    end
    object check_party: TCheckBox
      Left = 16
      Top = 248
      Width = 150
      Height = 17
      Caption = 'Part Y'
      TabOrder = 14
    end
    object check_comp_nlist: TCheckBox
      Left = 16
      Top = 264
      Width = 150
      Height = 17
      Caption = 'Compare Netlist'
      TabOrder = 15
    end
  end
  object GroupBox5: TGroupBox
    Left = 256
    Top = 160
    Width = 209
    Height = 273
    Caption = 'Pin columns'
    TabOrder = 4
    object check_pinname: TCheckBox
      Left = 19
      Top = 24
      Width = 150
      Height = 17
      Caption = 'Pin names'
      TabOrder = 0
    end
    object check_netpcb: TCheckBox
      Left = 19
      Top = 40
      Width = 150
      Height = 17
      Caption = 'Pin nets of PCB'
      TabOrder = 1
    end
    object check_pins_cnt: TCheckBox
      Left = 19
      Top = 56
      Width = 150
      Height = 17
      Caption = 'Pin net count'
      TabOrder = 2
    end
    object check_ext_netlist: TCheckBox
      Left = 19
      Top = 72
      Width = 182
      Height = 17
      Caption = 'Nets of external netlist'
      TabOrder = 3
    end
    object check_pins_type: TCheckBox
      Left = 19
      Top = 88
      Width = 150
      Height = 17
      Caption = 'Pin Types'
      TabOrder = 4
    end
    object check_pins_w: TCheckBox
      Left = 19
      Top = 104
      Width = 150
      Height = 17
      Caption = 'Pin Widths'
      TabOrder = 5
    end
    object check_pins_l: TCheckBox
      Left = 19
      Top = 120
      Width = 150
      Height = 17
      Caption = 'Pin Lengths'
      TabOrder = 6
    end
    object check_thrml: TCheckBox
      Left = 19
      Top = 136
      Width = 150
      Height = 17
      Caption = 'Pin Thermal Types'
      TabOrder = 7
    end
    object check_holes_diam: TCheckBox
      Left = 19
      Top = 152
      Width = 185
      Height = 17
      Caption = 'Pin Hole Diameters'
      TabOrder = 8
    end
    object check_paste: TCheckBox
      Left = 19
      Top = 168
      Width = 174
      Height = 17
      Caption = 'Pin Paste mask Checks'
      TabOrder = 9
    end
    object check_pinsx: TCheckBox
      Left = 19
      Top = 184
      Width = 150
      Height = 17
      Caption = 'Pin X'
      TabOrder = 10
    end
    object check_pinsy: TCheckBox
      Left = 19
      Top = 200
      Width = 150
      Height = 17
      Caption = 'Pin Y'
      TabOrder = 11
    end
    object check_vias: TCheckBox
      Left = 19
      Top = 216
      Width = 150
      Height = 17
      Caption = 'Show Vias'
      TabOrder = 12
      OnClick = check_viasClick
    end
  end
end
