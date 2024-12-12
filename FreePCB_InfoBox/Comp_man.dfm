object Form1: TForm1
  Left = 313
  Top = 190
  Width = 896
  Height = 264
  BorderIcons = [biSystemMenu]
  BorderWidth = 1
  Caption = '*'
  Color = clSilver
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
  OnKeyUp = FormKeyUp
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 16
  object Label1: TLabel
    Left = 156
    Top = 178
    Width = 35
    Height = 16
    Caption = 'parts'
    Visible = False
  end
  object Label2: TLabel
    Left = 244
    Top = 179
    Width = 26
    Height = 16
    Caption = 'pins'
    Visible = False
  end
  object Label6: TLabel
    Left = 356
    Top = 177
    Width = 35
    Height = 16
    Caption = 'bufer'
    Visible = False
  end
  object Label7: TLabel
    Left = 440
    Top = 176
    Width = 66
    Height = 16
    Caption = 'sortedbox'
    Visible = False
  end
  object SortedBox: TListBox
    Left = 425
    Top = 121
    Width = 100
    Height = 40
    ItemHeight = 16
    TabOrder = 0
    Visible = False
  end
  object Bufer: TListBox
    Left = 321
    Top = 121
    Width = 100
    Height = 40
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ItemHeight = 13
    ParentFont = False
    TabOrder = 1
    Visible = False
  end
  object DataParts: TListBox
    Left = 113
    Top = 122
    Width = 100
    Height = 39
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ItemHeight = 13
    ParentFont = False
    TabOrder = 2
    Visible = False
  end
  object DataPins: TListBox
    Left = 217
    Top = 122
    Width = 100
    Height = 39
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ItemHeight = 13
    ParentFont = False
    TabOrder = 3
    Visible = False
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 873
    Height = 81
    ActivePage = Parts
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Century Gothic'
    Font.Style = []
    MultiLine = True
    ParentFont = False
    TabHeight = 24
    TabIndex = 0
    TabOrder = 4
    TabPosition = tpLeft
    OnChange = PageControl1Change
    object Parts: TTabSheet
      Caption = 'Parts'
      object n_el1: TLabel
        Left = 768
        Top = 49
        Width = 21
        Height = 16
        Caption = '000'
      end
      object R: TImage
        Left = 752
        Top = 33
        Width = 33
        Height = 32
        Cursor = crHandPoint
        AutoSize = True
        Picture.Data = {
          07544269746D6170B60C0000424DB60C00000000000036000000280000002100
          0000200000000100180000000000800C00000000000000000000000000000000
          0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF6F6F6FFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFADADAD6666663838382323232020202424241F1F1F28282848
          4848818181D3D3D3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFAFAFA7A7A7A2A2A2A3232323A3A3A414141434343424141414141454545
          4343433D3D3D3A3A3A2727273A3A3AACACACFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFA8A8A82C2C2C3B3B3B47474648484845454444443F36372D484B414F4F
          4442403A32332E4444414242424A4A4A414142333333414141EBEBEBFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFF6A69693637374B4B4B4D4D4D3F3E3D605E54AEADA2ABABC3BABAE299
          9FE3969DE4A5AADEBFC3DBBEC1BE98968B4747414847474E4E4E4848482E2D2D
          AAAAAAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFF5152524341414F4E4E4E4C4B57574FD5D5CA979ADF1E1EC70000D6
          0000D80100DE0000DB0001D90000D50401C54C51C4C4C7DAADAD9E4847415253
          534F51533B3A3A9B9B9BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFF626262494949565455504D4D959589BFBFD4080DAD0000DB0C0B
          DF0D0DDC0D0DDC0D0DDB0E0DDC0D0DDC0D0DDC0E0DE00505DE0000D23A40BFD3
          D6D96261585354585555553B3B3BBDBDBDFFFFFFFFFFFFFFFFFFFFFFFF00FFFF
          FFFFFFFFFFFFFF9B9B9B4544465D5A5B52534BADAC9C7375D80000CB0A0AE40E
          0DDC0E0DDC0D0EDB0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0D0DDB0E0EDB0D0DDD
          0505E20103BDBDC0DD6E695F5959595C5B5B414140EFEFF0FFFFFFFFFFFFFFFF
          FF00FFFFFFFFFFFFFFFFFF4444455D5D5C5C5A5A9796867073D60000D70E0DDF
          0D0DDD0D0DDB0D0EDB0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDB0D0EDC0E0D
          DC0E0EDB0D0DDC0A0BE00000C4B3B1DB67685B61616259595A6C6D6AFFFFFFFF
          FFFFFFFFFF00FFFFFFFFFFFF7E7E7E5A585A66656673736A9D9FD40000CC0E0D
          DE0D0DDB0E0EDB0D0EDC0E0EDB0D0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E
          0EDB0E0EDB0E0EDC0E0EDC0E0EDB0B0BDE0403D4A2A5C065635C6566664F4E4E
          D1D1D1FFFFFFFFFFFF00FFFFFFFFFFFF50504F666768626461B1B5B10D0AB80C
          0CE10D0DDC0E0EDC0E0EDC0E0EDB0D0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC
          0E0EDC0E0EDC0D0EDC0D0EDC0D0EDB0F0DDC0E0EDC0606DF2D2ED48D92816868
          6769686A777777FFFFFFFFFFFF00FFFFFFB1B1B16161616E6D6F8081766C6FA8
          0405DA0E0DDE0D0EDB0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0E
          DC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDB0D0EDC0D0DDB0D0DDD0201D78A
          8CB372726A717072585858F3F3F3FFFFFF00FFFFFF8484846F6F6F7373729D9E
          961E1EA00A0AE30E0DDD0D0DDC0D0DDD0D0DDC0D0DDD0D0CDE0C0CDD0D0DDC0C
          0CDD0A0ADC0D0DDD0E0EDC0D0DDD0D0DDE0C0CDD0D0DDC0D0DDC0D0CDD0E0DDC
          0907E04143CC86897577777A666666C7C7C7FFFFFF00FFFFFF6769677677767A
          7A779597970000BD0104D00407D60606DC0000C40C0DD90000C50205C30B0ECA
          0402D80203C80E0EDC0000C80908DE0000CA0100C20E0FCA090AD80E0DDE0302
          CB0909D80A0BDE1D1CCE9393907C7E7B737373A3A3A3FFFFFF00FFFFFF6B6C6B
          7F807D8989847071920000D600F2FF0E0EDC2B2DCB00F2FF0E0EDC00F2FF00F2
          FF00F2FF0E0EDC00F2FF00F2FF00F2FF0E0EDC00F2FF00F2FF00F2FF2024D20E
          0EDC00F2FF0E0EDC0A0AE10806D58D8D9A8887847C7C7C949494FFFFFF00FFFF
          FF73727387888490908B605E8E0000DA00F2FF0E0EDC00F2FF0E0EDC0E0EDC00
          F2FF0E0EDC0E0EDC070BD80E0EDC3736C300F2FF0E0EDC00F2FF191EB40000C0
          0B0BDD0E0EDC00F2FF1D1ED00909E00100D886879C908D888182828D8D8DFFFF
          FF00FFFFFF7878788A8B899494905C59850000DB00F2FF00F2FF00F2FF00F2FF
          0E0EDC00F2FF00F2FF00F2FF0E0EDC00F2FF00F2FF00F2FF0E0EDC00F2FF00F2
          FF00F2FF0E0EDC0E0EDC00F2FF0E0EDC0506DD0301D981819898979389898994
          9494FFFFFF00FFFFFF8080808F8F8F9F9F9862648D0000D900F2FF0E0EDC0E0E
          DC00F2FF0E0EDC00F2FF4548BD3B3BD21416CD00F2FF1516B40E0EDC120FCF00
          F2FF0E0EDC0E0EDC0E0EDC4546CD00F2FF6867CE2320DC0A09D58B8B909A9A9A
          8E8E8EA0A0A0FFFFFF00FFFFFF858585969695A4A49F7777910000D400F2FF00
          F2FF00F2FF00F2FF0404D500F2FF00F2FF00F2FF0806D500F2FF00F2FF00F2FF
          0805D100F2FF00F2FF00F2FF2D2FCA00F2FF00F2FF00F2FF3C3CDA0E0DCC9998
          93A1A09F939492B7B7B7FFFFFF00FFFFFFA2A3A2999B98A7A7A5999895120FCC
          0304DD0002DB0505E00E0BDA0D0EDC0304DB0304DD0302DC0E0FDE0B08DF0402
          DF0301DB0F0CE00204DB0003DC0004DF0A08DD0105DC0204DD0305DC0403E52F
          319BB6B3A5A7A6A4979896D2D2D2FFFFFF00FFFFFFCACBCA9B9D9AA9A9A9B7B7
          A83431A00707E60E0DDB0D0DDB0D0EDC0E0DDC0E0DDC0D0DDB0D0EDC0D0DDB0D
          0DDB0D0DDB0D0EDB0D0EDB0E0EDC0E0DDC0E0DDB0D0DDB0E0DDC0E0DDC0D0DDC
          0807DC686B81BBBBB6ABA9AA99999AF7F7F7FFFFFF00FFFFFFF4F4F39C9D9BAE
          AEAEC0BEBC81828D0509CF0E0EDF0E0DDB0D0EDB0E0EDC0E0EDB0D0EDC0E0EDC
          0D0EDB0E0EDC0E0EDB0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0D0EDC0E0DDC0D0F
          DA0A0AE41211A3BCBBADB5B4B5AEAEACAFAFAFFFFFFFFFFFFF00FFFFFFFFFFFF
          B4B4B4B1B0B0B7B8BACECEC03034820607E30E0DDD0E0EDC0D0EDB0D0EDC0F0E
          DC0E0EDC0D0EDC0E0EDB0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDB0D
          0EDB0D0BE00205D3737682D0D0C5BBBABDADAEADD9D9D9FFFFFFFFFFFF00FFFF
          FFFFFFFFEFEFEFA9A9A9C0BFC0C8C3CAC3C5B61718910708E70E0DDE0D0DDB0D
          0DDB0D0EDB0D0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDB0E0EDB0D0EDB
          0D0DDC0C0BE20405DC414375E3E2D9C4C4C5BFBFBFB5B5B5FFFFFFFFFFFFFFFF
          FF00FFFFFFFFFFFFFFFFFFCECECEC0C0BFCAC9C9D6D7D2BEC0AF11108D0808E0
          0C0DE10E0DDC0D0DDC0D0EDB0E0EDB0E0EDB0E0EDC0E0DDC0E0EDB0E0EDC0D0E
          DC0D0CDD0B0BE60907D5353A6BE8E8D8D0D0D1CCCBCDB8B8B7F2F2F2FFFFFFFF
          FFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFBCBCBCCBCCCCD4D4D5E5E4E3D3D5
          C12C305F0B0BC50A09E80B0CE20D0DDD0D0DDC0D0DDC0E0DDB0D0EDB0D0DDC0C
          0DE00B0BE60809E60B069961626EFDFBF0E3DEE0D7D7D7C9C8C8DBDBDCFFFFFF
          FFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC4C4C4DADADAE0
          E0DFEBECE8FDFDFA8F9186151564090AAF0C07DC0609E00A09E80809E8090AE8
          0D09E10807CB070A8D383858C5C6BBFFFFFFEAE9E8E1E0E0D8D8D8D5D5D5FFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          D1D1D1E7E7E8EAEAEBF2F3F2FFFFFFFFFFFDB6B7AD6D7078393C6623235C1E1C
          5C2221794B4D62888982D8DACDFFFFFFFFFFFFF3F3F5EEEEEFDFDFDFDEDEDEFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFDBDBDAE5E5E5FCFBFBFCFBFCFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF9F9F9DBDBDBE9E9E9
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFF4F4F4DDDDDDE9E9E9FFFFFFFFFFFFFFFFFF
          FEFEFFFFFFFFFDFDFEFFFFFFFFFFFFFEFEFEFFFFFFFDFDFDE0E0E0E8E8E8FFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF9F9F9E5E5E5E5E5
          E5E5E5E5ECECECF6F6F6F9F9F9F3F3F3E8E8E8E8E8E8E3E3E3E3E3E3FFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FF00}
        Transparent = True
        OnClick = RClick
      end
      object StringGridParts: TStringGrid
        Left = 1
        Top = 40
        Width = 744
        Height = 25
        Cursor = crArrow
        Color = clMenu
        ColCount = 99
        Ctl3D = True
        DefaultColWidth = 56
        DefaultRowHeight = 15
        DefaultDrawing = False
        FixedColor = clBlack
        FixedCols = 0
        RowCount = 1
        FixedRows = 0
        GridLineWidth = 0
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
        ParentCtl3D = False
        ParentShowHint = False
        PopupMenu = Popup
        ScrollBars = ssVertical
        ShowHint = True
        TabOrder = 0
        OnContextPopup = StringGridPartsContextPopup
        OnDrawCell = StringGridPartsDrawCell
        OnKeyUp = StringGridPartsKeyUp
        OnMouseDown = StringGridPartsMouseDown
        OnMouseUp = StringGridPartsMouseUp
        OnMouseWheelDown = StringGridPartsMouseWheelDown
        OnMouseWheelUp = StringGridPartsMouseWheelUp
      end
      object BRefDes: TButton
        Left = 4
        Top = 0
        Width = 46
        Height = 17
        Caption = 'RefDes'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Century Gothic'
        Font.Style = []
        ParentFont = False
        PopupMenu = SF
        TabOrder = 1
        OnClick = BRefDesClick
      end
      object BValue: TButton
        Left = 93
        Top = 0
        Width = 39
        Height = 17
        Caption = 'Value'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        PopupMenu = SF
        TabOrder = 2
        OnClick = BValueClick
      end
      object BPackage: TButton
        Left = 171
        Top = 0
        Width = 41
        Height = 17
        Caption = 'Package'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        PopupMenu = SF
        TabOrder = 3
        OnClick = BPackageClick
      end
      object BPins: TButton
        Left = 351
        Top = 0
        Width = 58
        Height = 17
        Caption = 'Pins'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 4
        OnClick = BPinsClick
      end
      object BHoles: TButton
        Left = 409
        Top = 0
        Width = 55
        Height = 17
        Caption = 'Holes'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 5
        OnClick = BHolesClick
      end
      object MinPin: TEdit
        Left = 351
        Top = 17
        Width = 28
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 6
        OnKeyUp = MinPinKeyUp
      end
      object MinHoles: TEdit
        Left = 408
        Top = 16
        Width = 27
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 7
        OnClick = MinHolesClick
        OnKeyUp = MinHolesKeyUp
      end
      object MaxPins: TEdit
        Left = 379
        Top = 16
        Width = 28
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 8
        OnKeyUp = MaxPinsKeyUp
      end
      object MaxHoles: TEdit
        Left = 436
        Top = 16
        Width = 27
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 9
        OnClick = MaxHolesClick
        OnKeyUp = MaxHolesKeyUp
      end
      object BSide: TButton
        Left = 496
        Top = 0
        Width = 28
        Height = 17
        Caption = 'S'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 10
        OnClick = BSideClick
      end
      object Side: TEdit
        Left = 494
        Top = 16
        Width = 29
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 11
        OnKeyDown = SideKeyDown
        OnKeyUp = SideKeyUp
      end
      object BCNetlist: TButton
        Left = 677
        Top = 0
        Width = 139
        Height = 16
        Caption = 'Compare Netlist'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 12
        OnClick = BCNetlistClick
        OnMouseMove = BCNetlistMouseMove
      end
      object BGlueds: TButton
        Left = 464
        Top = 0
        Width = 31
        Height = 17
        Caption = 'Gl'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 13
        OnClick = BGluedsClick
      end
      object Glueds: TEdit
        Left = 464
        Top = 16
        Width = 29
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 14
        OnKeyDown = GluedsKeyDown
        OnKeyUp = GluedsKeyUp
      end
      object BAng: TButton
        Left = 525
        Top = 0
        Width = 29
        Height = 17
        Caption = 'Ang'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 15
        OnClick = BAngClick
      end
      object Ang: TEdit
        Left = 524
        Top = 16
        Width = 29
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 16
        OnKeyUp = AngKeyUp
      end
      object BX: TButton
        Left = 555
        Top = 0
        Width = 60
        Height = 17
        Caption = 'X'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 17
        OnClick = BXClick
      end
      object EXmin: TEdit
        Left = 553
        Top = 16
        Width = 29
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 18
        OnKeyUp = EXminKeyUp
      end
      object BY: TButton
        Left = 616
        Top = 0
        Width = 60
        Height = 17
        Caption = 'Y'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 19
        OnClick = BYClick
      end
      object EYmin: TEdit
        Left = 614
        Top = 16
        Width = 31
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 20
        OnKeyUp = EYminKeyUp
      end
      object CCNetlist: TComboBox
        Left = 676
        Top = 16
        Width = 141
        Height = 21
        DropDownCount = 12
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ItemHeight = 13
        ParentFont = False
        TabOrder = 21
        OnChange = CCNetlistChange
        OnKeyUp = CCNetlistKeyUp
      end
      object EXmax: TEdit
        Left = 583
        Top = 16
        Width = 30
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 22
        OnKeyUp = EXmaxKeyUp
      end
      object EYmax: TEdit
        Left = 646
        Top = 16
        Width = 30
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 23
        OnKeyUp = EYmaxKeyUp
      end
      object BMerge: TButton
        Left = 296
        Top = 0
        Width = 54
        Height = 17
        Caption = 'Merge'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 24
        OnClick = BPackageClick
      end
      object CRefDes: TEdit
        Left = 3
        Top = 17
        Width = 47
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        PopupMenu = SF
        TabOrder = 25
        OnChange = CRefDeshange
        OnClick = CRefDesClick
        OnKeyUp = CRefDesKeyUp
        OnMouseDown = CRefDesMouseDown
      end
      object CValue: TEdit
        Left = 92
        Top = 17
        Width = 39
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        PopupMenu = SF
        TabOrder = 26
        OnChange = CRefDeshange
        OnClick = CValueClick
        OnKeyUp = CRefDesKeyUp
      end
      object CPackage: TEdit
        Left = 170
        Top = 17
        Width = 42
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        PopupMenu = SF
        TabOrder = 27
        OnChange = CRefDeshange
        OnClick = CPackageClick
        OnKeyUp = CRefDesKeyUp
      end
      object CMerge: TComboBox
        Left = 295
        Top = 17
        Width = 55
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ItemHeight = 13
        ParentFont = False
        TabOrder = 28
        OnChange = CRefDeshange
        OnKeyUp = CRefDesKeyUp
      end
      object CValueNL: TEdit
        Left = 131
        Top = 17
        Width = 40
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 29
        OnChange = CRefDeshange
        OnClick = CValueClick
        OnKeyUp = CRefDesKeyUp
      end
      object BValueNL: TButton
        Left = 133
        Top = 0
        Width = 37
        Height = 17
        Caption = 'Value nl'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 30
        OnClick = BValueNLClick
      end
      object BPackageNL: TButton
        Left = 213
        Top = 0
        Width = 40
        Height = 17
        Caption = 'Package'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 31
        OnClick = BPackageNLClick
      end
      object CPackageNL: TEdit
        Left = 212
        Top = 17
        Width = 42
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 32
        OnChange = CRefDeshange
        OnClick = CPackageClick
        OnKeyUp = CRefDesKeyUp
      end
      object BFootPrint: TButton
        Left = 255
        Top = 0
        Width = 39
        Height = 17
        Caption = 'Foot'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 33
        OnClick = BFootPrintClick
      end
      object CFootPrint: TEdit
        Left = 254
        Top = 17
        Width = 41
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        PopupMenu = SF
        TabOrder = 34
        OnChange = CRefDeshange
        OnClick = CPackageClick
        OnKeyUp = CRefDesKeyUp
      end
      object MaxRI: TEdit
        Left = 71
        Top = 17
        Width = 20
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 35
        OnKeyUp = MaxRIKeyUp
      end
      object MinRI: TEdit
        Left = 50
        Top = 17
        Width = 20
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 36
        OnKeyUp = MinRIKeyUp
      end
      object BRIRange: TButton
        Left = 52
        Top = 0
        Width = 39
        Height = 17
        Caption = 'Index'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        PopupMenu = SF
        TabOrder = 37
        OnClick = BRIRangeClick
      end
    end
    object Pins: TTabSheet
      Caption = 'Pins'
      ImageIndex = 1
      object n_el2: TLabel
        Left = 696
        Top = 49
        Width = 21
        Height = 16
        Caption = '000'
      end
      object R2: TImage
        Left = 680
        Top = 41
        Width = 33
        Height = 32
        Cursor = crHandPoint
        AutoSize = True
        Picture.Data = {
          07544269746D6170B60C0000424DB60C00000000000036000000280000002100
          0000200000000100180000000000800C00000000000000000000000000000000
          0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF6F6F6FFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFADADAD6666663838382323232020202424241F1F1F28282848
          4848818181D3D3D3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFAFAFA7A7A7A2A2A2A3232323A3A3A414141434343424141414141454545
          4343433D3D3D3A3A3A2727273A3A3AACACACFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFA8A8A82C2C2C3B3B3B47474648484845454444443F36372D484B414F4F
          4442403A32332E4444414242424A4A4A414142333333414141EBEBEBFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFF6A69693637374B4B4B4D4D4D3F3E3D605E54AEADA2ABABC3BABAE299
          9FE3969DE4A5AADEBFC3DBBEC1BE98968B4747414847474E4E4E4848482E2D2D
          AAAAAAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFF5152524341414F4E4E4E4C4B57574FD5D5CA979ADF1E1EC70000D6
          0000D80100DE0000DB0001D90000D50401C54C51C4C4C7DAADAD9E4847415253
          534F51533B3A3A9B9B9BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFF626262494949565455504D4D959589BFBFD4080DAD0000DB0C0B
          DF0D0DDC0D0DDC0D0DDB0E0DDC0D0DDC0D0DDC0E0DE00505DE0000D23A40BFD3
          D6D96261585354585555553B3B3BBDBDBDFFFFFFFFFFFFFFFFFFFFFFFF00FFFF
          FFFFFFFFFFFFFF9B9B9B4544465D5A5B52534BADAC9C7375D80000CB0A0AE40E
          0DDC0E0DDC0D0EDB0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0D0DDB0E0EDB0D0DDD
          0505E20103BDBDC0DD6E695F5959595C5B5B414140EFEFF0FFFFFFFFFFFFFFFF
          FF00FFFFFFFFFFFFFFFFFF4444455D5D5C5C5A5A9796867073D60000D70E0DDF
          0D0DDD0D0DDB0D0EDB0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDB0D0EDC0E0D
          DC0E0EDB0D0DDC0A0BE00000C4B3B1DB67685B61616259595A6C6D6AFFFFFFFF
          FFFFFFFFFF00FFFFFFFFFFFF7E7E7E5A585A66656673736A9D9FD40000CC0E0D
          DE0D0DDB0E0EDB0D0EDC0E0EDB0D0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E
          0EDB0E0EDB0E0EDC0E0EDC0E0EDB0B0BDE0403D4A2A5C065635C6566664F4E4E
          D1D1D1FFFFFFFFFFFF00FFFFFFFFFFFF50504F666768626461B1B5B10D0AB80C
          0CE10D0DDC0E0EDC0E0EDC0E0EDB0D0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC
          0E0EDC0E0EDC0D0EDC0D0EDC0D0EDB0F0DDC0E0EDC0606DF2D2ED48D92816868
          6769686A777777FFFFFFFFFFFF00FFFFFFB1B1B16161616E6D6F8081766C6FA8
          0405DA0E0DDE0D0EDB0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0E
          DC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDB0D0EDC0D0DDB0D0DDD0201D78A
          8CB372726A717072585858F3F3F3FFFFFF00FFFFFF8484846F6F6F7373729D9E
          961E1EA00A0AE30E0DDD0D0DDC0D0DDD0D0DDC0D0DDD0D0CDE0C0CDD0D0DDC0C
          0CDD0A0ADC0D0DDD0E0EDC0D0DDD0D0DDE0C0CDD0D0DDC0D0DDC0D0CDD0E0DDC
          0907E04143CC86897577777A666666C7C7C7FFFFFF00FFFFFF6769677677767A
          7A779597970000BD0104D00407D60606DC0000C40C0DD90000C50205C30B0ECA
          0402D80203C80E0EDC0000C80908DE0000CA0100C20E0FCA090AD80E0DDE0302
          CB0909D80A0BDE1D1CCE9393907C7E7B737373A3A3A3FFFFFF00FFFFFF6B6C6B
          7F807D8989847071920000D600F2FF0E0EDC2B2DCB00F2FF0E0EDC00F2FF00F2
          FF00F2FF0E0EDC00F2FF00F2FF00F2FF0E0EDC00F2FF00F2FF00F2FF2024D20E
          0EDC00F2FF0E0EDC0A0AE10806D58D8D9A8887847C7C7C949494FFFFFF00FFFF
          FF73727387888490908B605E8E0000DA00F2FF0E0EDC00F2FF0E0EDC0E0EDC00
          F2FF0E0EDC0E0EDC070BD80E0EDC3736C300F2FF0E0EDC00F2FF191EB40000C0
          0B0BDD0E0EDC00F2FF1D1ED00909E00100D886879C908D888182828D8D8DFFFF
          FF00FFFFFF7878788A8B899494905C59850000DB00F2FF00F2FF00F2FF00F2FF
          0E0EDC00F2FF00F2FF00F2FF0E0EDC00F2FF00F2FF00F2FF0E0EDC00F2FF00F2
          FF00F2FF0E0EDC0E0EDC00F2FF0E0EDC0506DD0301D981819898979389898994
          9494FFFFFF00FFFFFF8080808F8F8F9F9F9862648D0000D900F2FF0E0EDC0E0E
          DC00F2FF0E0EDC00F2FF4548BD3B3BD21416CD00F2FF1516B40E0EDC120FCF00
          F2FF0E0EDC0E0EDC0E0EDC4546CD00F2FF6867CE2320DC0A09D58B8B909A9A9A
          8E8E8EA0A0A0FFFFFF00FFFFFF858585969695A4A49F7777910000D400F2FF00
          F2FF00F2FF00F2FF0404D500F2FF00F2FF00F2FF0806D500F2FF00F2FF00F2FF
          0805D100F2FF00F2FF00F2FF2D2FCA00F2FF00F2FF00F2FF3C3CDA0E0DCC9998
          93A1A09F939492B7B7B7FFFFFF00FFFFFFA2A3A2999B98A7A7A5999895120FCC
          0304DD0002DB0505E00E0BDA0D0EDC0304DB0304DD0302DC0E0FDE0B08DF0402
          DF0301DB0F0CE00204DB0003DC0004DF0A08DD0105DC0204DD0305DC0403E52F
          319BB6B3A5A7A6A4979896D2D2D2FFFFFF00FFFFFFCACBCA9B9D9AA9A9A9B7B7
          A83431A00707E60E0DDB0D0DDB0D0EDC0E0DDC0E0DDC0D0DDB0D0EDC0D0DDB0D
          0DDB0D0DDB0D0EDB0D0EDB0E0EDC0E0DDC0E0DDB0D0DDB0E0DDC0E0DDC0D0DDC
          0807DC686B81BBBBB6ABA9AA99999AF7F7F7FFFFFF00FFFFFFF4F4F39C9D9BAE
          AEAEC0BEBC81828D0509CF0E0EDF0E0DDB0D0EDB0E0EDC0E0EDB0D0EDC0E0EDC
          0D0EDB0E0EDC0E0EDB0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0D0EDC0E0DDC0D0F
          DA0A0AE41211A3BCBBADB5B4B5AEAEACAFAFAFFFFFFFFFFFFF00FFFFFFFFFFFF
          B4B4B4B1B0B0B7B8BACECEC03034820607E30E0DDD0E0EDC0D0EDB0D0EDC0F0E
          DC0E0EDC0D0EDC0E0EDB0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDB0D
          0EDB0D0BE00205D3737682D0D0C5BBBABDADAEADD9D9D9FFFFFFFFFFFF00FFFF
          FFFFFFFFEFEFEFA9A9A9C0BFC0C8C3CAC3C5B61718910708E70E0DDE0D0DDB0D
          0DDB0D0EDB0D0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDC0E0EDB0E0EDB0D0EDB
          0D0DDC0C0BE20405DC414375E3E2D9C4C4C5BFBFBFB5B5B5FFFFFFFFFFFFFFFF
          FF00FFFFFFFFFFFFFFFFFFCECECEC0C0BFCAC9C9D6D7D2BEC0AF11108D0808E0
          0C0DE10E0DDC0D0DDC0D0EDB0E0EDB0E0EDB0E0EDC0E0DDC0E0EDB0E0EDC0D0E
          DC0D0CDD0B0BE60907D5353A6BE8E8D8D0D0D1CCCBCDB8B8B7F2F2F2FFFFFFFF
          FFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFBCBCBCCBCCCCD4D4D5E5E4E3D3D5
          C12C305F0B0BC50A09E80B0CE20D0DDD0D0DDC0D0DDC0E0DDB0D0EDB0D0DDC0C
          0DE00B0BE60809E60B069961626EFDFBF0E3DEE0D7D7D7C9C8C8DBDBDCFFFFFF
          FFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC4C4C4DADADAE0
          E0DFEBECE8FDFDFA8F9186151564090AAF0C07DC0609E00A09E80809E8090AE8
          0D09E10807CB070A8D383858C5C6BBFFFFFFEAE9E8E1E0E0D8D8D8D5D5D5FFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          D1D1D1E7E7E8EAEAEBF2F3F2FFFFFFFFFFFDB6B7AD6D7078393C6623235C1E1C
          5C2221794B4D62888982D8DACDFFFFFFFFFFFFF3F3F5EEEEEFDFDFDFDEDEDEFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFDBDBDAE5E5E5FCFBFBFCFBFCFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF9F9F9DBDBDBE9E9E9
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFF4F4F4DDDDDDE9E9E9FFFFFFFFFFFFFFFFFF
          FEFEFFFFFFFFFDFDFEFFFFFFFFFFFFFEFEFEFFFFFFFDFDFDE0E0E0E8E8E8FFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF9F9F9E5E5E5E5E5
          E5E5E5E5ECECECF6F6F6F9F9F9F3F3F3E8E8E8E8E8E8E3E3E3E3E3E3FFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FF00}
        Transparent = True
        OnClick = RClick
      end
      object StringGridPins: TStringGrid
        Left = 66
        Top = 38
        Width = 271
        Height = 27
        Cursor = crDrag
        Color = clCream
        ColCount = 99
        Ctl3D = True
        DefaultColWidth = 56
        DefaultRowHeight = 15
        DefaultDrawing = False
        FixedColor = clBlack
        FixedCols = 0
        RowCount = 1
        FixedRows = 0
        GridLineWidth = 0
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
        ParentCtl3D = False
        ParentShowHint = False
        PopupMenu = Popup
        ScrollBars = ssVertical
        ShowHint = False
        TabOrder = 0
        OnContextPopup = StringGridPinsContextPopup
        OnDrawCell = StringGridPinsDrawCell
        OnKeyUp = StringGridPinsKeyUp
        OnMouseDown = StringGridPinsMouseDown
        OnMouseUp = StringGridPinsMouseUp
        OnMouseWheelDown = StringGridPinsMouseWheelDown
        OnMouseWheelUp = StringGridPinsMouseWheelUp
      end
      object BPin: TButton
        Left = 2
        Top = 0
        Width = 71
        Height = 17
        Caption = 'Pin'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 1
        OnClick = BPinClick
      end
      object BPinNetPCB: TButton
        Left = 82
        Top = 0
        Width = 92
        Height = 17
        Caption = 'Net Pcb'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 2
        OnClick = BPinNetPCBClick
      end
      object BType: TButton
        Left = 314
        Top = 0
        Width = 59
        Height = 17
        Caption = 'Type'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 3
        OnClick = BTypeClick
      end
      object CType: TComboBox
        Left = 313
        Top = 17
        Width = 59
        Height = 21
        DropDownCount = 12
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ItemHeight = 0
        ParentFont = False
        TabOrder = 4
        OnChange = CTypeChange
      end
      object BPinNetList: TButton
        Left = 221
        Top = 0
        Width = 92
        Height = 17
        Caption = 'Net list'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 5
        OnClick = BPinNetListClick
      end
      object BW: TButton
        Left = 373
        Top = 0
        Width = 59
        Height = 17
        Caption = 'W'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 6
        OnClick = BWClick
      end
      object BL: TButton
        Left = 433
        Top = 0
        Width = 59
        Height = 17
        Caption = 'L'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 7
        OnClick = BLClick
      end
      object BTrml: TButton
        Left = 493
        Top = 0
        Width = 59
        Height = 17
        Caption = 'Thrml'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 8
        OnClick = BTrmlClick
      end
      object CTrml: TComboBox
        Left = 492
        Top = 17
        Width = 59
        Height = 22
        DropDownCount = 12
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = []
        ItemHeight = 0
        ParentFont = False
        TabOrder = 9
        OnChange = CTrmlChange
      end
      object BDHole: TButton
        Left = 553
        Top = 0
        Width = 88
        Height = 17
        Caption = 'DHole'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 10
        OnClick = BDHoleClick
      end
      object BXPin: TButton
        Left = 682
        Top = 0
        Width = 69
        Height = 17
        Caption = 'X'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 11
        OnClick = BXPinClick
      end
      object WPinMin: TEdit
        Left = 373
        Top = 17
        Width = 29
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 12
        OnKeyUp = WPinMinKeyUp
      end
      object WPinMax: TEdit
        Left = 402
        Top = 17
        Width = 29
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 13
        OnKeyUp = WPinMaxKeyUp
      end
      object LPinMin: TEdit
        Left = 433
        Top = 17
        Width = 29
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 14
        OnKeyUp = LPinMinKeyUp
      end
      object LPinMax: TEdit
        Left = 462
        Top = 17
        Width = 29
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 15
        OnKeyUp = LPinMaxKeyUp
      end
      object XPinMin: TEdit
        Left = 680
        Top = 17
        Width = 36
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 16
        OnKeyUp = XPinMinKeyUp
      end
      object XPinMax: TEdit
        Left = 716
        Top = 17
        Width = 34
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 17
        OnKeyUp = XPinMaxKeyUp
      end
      object BYPin: TButton
        Left = 752
        Top = 0
        Width = 65
        Height = 17
        Caption = 'Y'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 18
        OnClick = BYPinClick
      end
      object YPinMin: TEdit
        Left = 750
        Top = 17
        Width = 34
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 19
        OnKeyUp = YPinMinKeyUp
      end
      object YPinMax: TEdit
        Left = 784
        Top = 17
        Width = 34
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 20
        OnKeyUp = YPinMaxKeyUp
      end
      object CPin: TEdit
        Left = 2
        Top = 17
        Width = 71
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 21
        OnChange = CPinChange
        OnClick = CPinClick
        OnDblClick = CPinDblClick
        OnKeyUp = CPinKeyUp
      end
      object CNetNetlist: TEdit
        Left = 221
        Top = 17
        Width = 92
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 22
        OnChange = CNetNetlistChange
        OnClick = CNetNetlistClick
      end
      object DHoleMin: TComboBox
        Left = 550
        Top = 17
        Width = 46
        Height = 22
        DropDownCount = 12
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = []
        ItemHeight = 0
        ParentFont = False
        TabOrder = 23
        OnChange = DHoleMinChange
        OnKeyUp = DHoleMinKeyUp
      end
      object DHoleMax: TComboBox
        Left = 594
        Top = 17
        Width = 46
        Height = 22
        DropDownCount = 12
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = []
        ItemHeight = 0
        ParentFont = False
        TabOrder = 24
        OnChange = DHoleMaxChange
        OnKeyUp = DHoleMaxKeyUp
      end
      object BCnt: TButton
        Left = 175
        Top = 0
        Width = 45
        Height = 17
        Caption = 'Cnt'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 25
        OnClick = BCntClick
      end
      object CPinNetPCB: TComboBox
        Left = 81
        Top = 17
        Width = 94
        Height = 22
        AutoComplete = False
        DropDownCount = 30
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = []
        ItemHeight = 0
        ParentFont = False
        TabOrder = 26
        OnChange = CPinNetPCBChange
      end
      object CCnt: TComboBox
        Left = 175
        Top = 17
        Width = 45
        Height = 21
        DropDownCount = 30
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ItemHeight = 0
        ParentFont = False
        TabOrder = 27
        OnChange = CTypeChange
      end
      object BPas: TButton
        Left = 641
        Top = 0
        Width = 40
        Height = 17
        Caption = 'Pas'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
        TabOrder = 28
        OnClick = BPasClick
      end
      object Pas: TEdit
        Left = 640
        Top = 17
        Width = 39
        Height = 21
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 29
        OnChange = PasChange
      end
    end
  end
  object Values: TComboBox
    Left = 728
    Top = 120
    Width = 81
    Height = 24
    ItemHeight = 16
    TabOrder = 5
    Text = 'Values'
    Visible = False
  end
  object ProgressBar1: TProgressBar
    Left = 8
    Top = 80
    Width = 857
    Height = 17
    Min = 0
    Max = 100
    Smooth = True
    TabOrder = 6
  end
  object Deleted: TListBox
    Left = 529
    Top = 121
    Width = 100
    Height = 40
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ItemHeight = 13
    ParentFont = False
    TabOrder = 7
    Visible = False
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 300
    OnTimer = Timer1Timer
    Left = 5
    Top = 119
  end
  object OpenDialog1: TOpenDialog
    Filter = 
      'PADS-PCB netlist file(*.net)|*.net|PADS-PCB netlist file(*.txt)|' +
      '*.txt|all files(*.*)|*.*'
    Left = 5
    Top = 183
  end
  object Popup: TPopupMenu
    MenuAnimation = [maLeftToRight, maTopToBottom]
    OnPopup = PopupPopup
    Left = 656
    Top = 120
    object ST_popup: TMenuItem
      Caption = ' Settings...'
      OnClick = ST_popupClick
    end
    object RF_popup: TMenuItem
      Caption = ' Reset Filter'
      OnClick = RF_popupClick
    end
    object CSC_popup: TMenuItem
      Caption = ' Fix'
      OnClick = CSC_popupClick
    end
    object PF_popup: TMenuItem
      Caption = ' Open Project folder'
      OnClick = PF_popupClick
    end
    object HA_popup: TMenuItem
      Caption = ' Highlight all elements'
      OnClick = HA_popupClick
    end
    object VP_popup: TMenuItem
      Caption = ' Add to Values Storage'
      OnClick = VP_popupClick
    end
    object TXT_popup: TMenuItem
      Caption = ' Generate TXT list'
      OnClick = TXT_popupClick
    end
    object EX_popup: TMenuItem
      Caption = ' Generate CSV list'
      OnClick = EX_popupClick
    end
    object Utilities1: TMenuItem
      Caption = 'Utilities'
      object EP_popup: TMenuItem
        Caption = 'Multiple edit pins'
        OnClick = EP_popupClick
      end
      object CP_popup: TMenuItem
        Caption = 'Compare PCB assembly Kit'
        OnClick = CP_popupClick
      end
      object FA_popup: TMenuItem
        Caption = 'Copper area splitter'
        OnClick = FA_popupClick
      end
      object NE_popup: TMenuItem
        Caption = 'Show net'
        OnClick = NE_popupClick
      end
    end
    object LN_popup: TMenuItem
      Caption = 'Loading Nets from netlist'
      OnClick = LN_popupClick
    end
  end
  object SF: TPopupMenu
    Left = 688
    Top = 120
    object SaveFilter1: TMenuItem
      Caption = 'Save Ref List'
      OnClick = SaveFilter1Click
    end
    object SaveFilter2: TMenuItem
      Caption = 'Save Value List'
      OnClick = SaveFilter2Click
    end
    object SaveFilter3: TMenuItem
      Caption = 'Save Package List'
      OnClick = SaveFilter3Click
    end
    object RemoveCurrentList1: TMenuItem
      Caption = 'Remove Performed List'
      OnClick = RemoveCurrentList1Click
    end
  end
  object OpenDialog2: TOpenDialog
    Filter = 
      'TXT Table (Ref Value Package)(*.txt)|*.txt|TXT Table (Ref Packag' +
      'e Value)(*.txt)|*.txt|all files(*.*)|*.*'
    Left = 37
    Top = 183
  end
  object TFilterAll: TTimer
    Enabled = False
    Interval = 10
    OnTimer = TFilterAllTimer
    Left = 21
    Top = 143
  end
end
