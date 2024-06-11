object Form2: TForm2
  Left = 910
  Top = 296
  Width = 1019
  Height = 440
  Caption = 'DXF library'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  WindowState = wsMaximized
  OnClose = FormClose
  OnContextPopup = FormContextPopup
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  OnMouseUp = FormMouseUp
  OnMouseWheelDown = FormMouseWheelDown
  OnMouseWheelUp = FormMouseWheelUp
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object pDC: TImage
    Left = 400
    Top = 8
    Width = 105
    Height = 105
  end
  object CheckBox1: TCheckBox
    Left = 400
    Top = 212
    Width = 73
    Height = 17
    Caption = 'Swap'
    TabOrder = 0
    Visible = False
  end
  object Select: TListBox
    Left = 400
    Top = 168
    Width = 33
    Height = 33
    ItemHeight = 13
    TabOrder = 1
  end
  object v2d: TGroupBox
    Left = 447
    Top = 320
    Width = 198
    Height = 49
    Caption = 'View 2D'
    TabOrder = 2
    object Button3: TButton
      Left = 76
      Top = 18
      Width = 43
      Height = 19
      Caption = 'Behind'
      TabOrder = 0
      OnClick = Button3Click
      OnKeyUp = Button3KeyUp
    end
    object Button2: TButton
      Left = 41
      Top = 18
      Width = 35
      Height = 19
      Caption = 'Front'
      TabOrder = 1
      OnClick = Button2Click
      OnKeyUp = Button2KeyUp
    end
    object vTop: TButton
      Left = 6
      Top = 18
      Width = 35
      Height = 19
      Caption = 'Top'
      TabOrder = 2
      OnClick = vTopClick
      OnKeyDown = StringGrid1KeyDown
      OnKeyUp = StringGrid1KeyUp
    end
    object Button4: TButton
      Left = 119
      Top = 18
      Width = 35
      Height = 19
      Caption = 'Left'
      TabOrder = 3
      OnClick = Button4Click
      OnKeyUp = Button4KeyUp
    end
    object Button5: TButton
      Left = 154
      Top = 18
      Width = 35
      Height = 19
      Caption = 'Right'
      TabOrder = 4
      OnClick = Button5Click
      OnKeyUp = Button5KeyUp
    end
  end
  object v3d: TGroupBox
    Left = 645
    Top = 320
    Width = 102
    Height = 49
    Caption = 'View 3D'
    TabOrder = 3
    object Button6: TButton
      Left = 50
      Top = 18
      Width = 21
      Height = 19
      Caption = '3'
      TabOrder = 0
      OnClick = Button6Click
    end
    object Button7: TButton
      Left = 28
      Top = 18
      Width = 21
      Height = 19
      Caption = '2'
      TabOrder = 1
      OnClick = Button7Click
    end
    object Button8: TButton
      Left = 8
      Top = 18
      Width = 19
      Height = 19
      Caption = '1'
      TabOrder = 2
      OnClick = Button8Click
    end
    object Button9: TButton
      Left = 72
      Top = 18
      Width = 21
      Height = 19
      Caption = '4'
      TabOrder = 3
      OnClick = Button9Click
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 8
    Width = 385
    Height = 273
    ActivePage = Editor
    TabIndex = 1
    TabOrder = 4
    TabPosition = tpBottom
    OnChanging = PageControl1Changing
    object Viewer: TTabSheet
      Caption = 'Viewer'
      object GroupBox1: TGroupBox
        Left = 184
        Top = 4
        Width = 185
        Height = 185
        Caption = 'Where else is this part used...'
        TabOrder = 0
        object Used: TListBox
          Left = 8
          Top = 16
          Width = 169
          Height = 161
          ItemHeight = 13
          TabOrder = 0
          OnClick = UsedClick
        end
      end
      object FootPrints: TListBox
        Left = 8
        Top = 8
        Width = 169
        Height = 233
        ItemHeight = 13
        Sorted = True
        TabOrder = 1
        OnClick = FootPrintsClick
      end
      object DelSel: TButton
        Left = 264
        Top = 216
        Width = 105
        Height = 25
        Caption = 'Delete selection'
        TabOrder = 2
        OnClick = DelSelClick
      end
      object SelAll: TButton
        Left = 184
        Top = 216
        Width = 73
        Height = 25
        Caption = 'Select all'
        TabOrder = 3
        OnClick = SelAllClick
      end
    end
    object Editor: TTabSheet
      Caption = 'Editor'
      ImageIndex = 1
      object StringGrid1: TStringGrid
        Left = 2
        Top = 0
        Width = 231
        Height = 111
        Color = clBtnFace
        Ctl3D = True
        DefaultColWidth = 40
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing]
        ParentCtl3D = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnContextPopup = StringGrid1ContextPopup
        OnDrawCell = StringGrid1DrawCell
        OnGetEditText = StringGrid1GetEditText
        OnKeyDown = StringGrid1KeyDown
        OnKeyUp = StringGrid1KeyUp
        OnMouseDown = StringGrid1MouseDown
        OnMouseUp = StringGrid1MouseUp
        OnMouseWheelDown = StringGrid1MouseWheelDown
        OnMouseWheelUp = StringGrid1MouseWheelUp
        OnSetEditText = StringGrid1SetEditText
        ColWidths = (
          40
          40
          40
          40
          40)
      end
      object Shapes: TListBox
        Left = 176
        Top = 152
        Width = 185
        Height = 49
        ItemHeight = 13
        MultiSelect = True
        TabOrder = 1
        Visible = False
        OnKeyUp = ShapesKeyUp
        OnMouseUp = ShapesMouseUp
      end
    end
  end
  object ProgressBar1: TProgressBar
    Left = 853
    Top = 345
    Width = 118
    Height = 16
    Min = 0
    Max = 100
    TabOrder = 5
  end
  object DrawGpoupObjects: TGroupBox
    Left = 214
    Top = 320
    Width = 233
    Height = 49
    Caption = 'Draw Gpoup Objects'
    TabOrder = 6
    object DrawGroupList: TComboBox
      Left = 8
      Top = 18
      Width = 169
      Height = 22
      Style = csOwnerDrawFixed
      ItemHeight = 16
      TabOrder = 0
    end
    object Draw: TButton
      Left = 184
      Top = 17
      Width = 41
      Height = 21
      Caption = 'Draw'
      TabOrder = 1
      OnClick = DrawClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 88
    Top = 320
    Width = 126
    Height = 49
    Caption = 'Library Path'
    TabOrder = 7
    object SvLib: TCheckBox
      Left = 8
      Top = 21
      Width = 113
      Height = 17
      Caption = 'Create local library'
      TabOrder = 0
      OnClick = SvLibClick
    end
  end
  object GroupBox3: TGroupBox
    Left = 747
    Top = 320
    Width = 97
    Height = 49
    Caption = 'Grid Lines'
    TabOrder = 8
    object GridValues: TComboBox
      Left = 8
      Top = 19
      Width = 81
      Height = 21
      ItemHeight = 13
      TabOrder = 0
      OnChange = GridValuesChange
    end
  end
  object GroupBox4: TGroupBox
    Left = 6
    Top = 320
    Width = 81
    Height = 49
    Caption = 'Find'
    TabOrder = 9
    object Edit1: TEdit
      Left = 8
      Top = 18
      Width = 65
      Height = 21
      TabOrder = 0
      OnChange = Edit1Change
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 400
    Top = 128
    object CopyObject1: TMenuItem
      Caption = 'Copy Current Object'
      OnClick = CopyObject1Click
    end
    object Copy1: TMenuItem
      Caption = 'Copy Current String'
      OnClick = Copy1Click
    end
    object DeleteString1: TMenuItem
      Caption = 'Delete Current String'
      OnClick = DeleteString1Click
    end
    object InsertEmptyString1: TMenuItem
      Caption = 'Insert Empty String'
      OnClick = InsertEmptyString1Click
    end
    object SwapCells1: TMenuItem
      Caption = 'Swap Cells'
      OnClick = SwapCells1Click
    end
    object Complex1: TMenuItem
      Caption = 'Complex Editing Mode'
      OnClick = Complex1Click
    end
    object BuildDXF1: TMenuItem
      Caption = 'Build DXF Model'
      OnClick = BuildDXF1Click
    end
    object ShowLengthofSides1: TMenuItem
      Caption = 'Show Length of Sides'
      OnClick = ShowLengthofSides1Click
    end
  end
end
