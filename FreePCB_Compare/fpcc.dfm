object Form1: TForm1
  Left = 651
  Top = 209
  BorderStyle = bsDialog
  Caption = 'FreePcb - Compare'
  ClientHeight = 559
  ClientWidth = 586
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Courier New'
  Font.Style = [fsBold]
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 16
  object Label5: TLabel
    Left = 21
    Top = 523
    Width = 120
    Height = 16
    Cursor = crHandPoint
    Caption = 'www.freepcb.dev'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlue
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
    OnClick = Label5Click
  end
  object Mess: TLabel
    Left = 24
    Top = 501
    Width = 96
    Height = 16
    Caption = 'Progress Bar'
  end
  object MicroStrings: TListBox
    Left = 520
    Top = 504
    Width = 33
    Height = 33
    ItemHeight = 16
    TabOrder = 0
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 585
    Height = 481
    ActivePage = Step_3
    TabIndex = 1
    TabOrder = 1
    object Step_2: TTabSheet
      Caption = 'Feeders'
      ImageIndex = 1
      object Label3: TLabel
        Left = 5
        Top = 309
        Width = 128
        Height = 16
        Caption = 'Hint (First row)'
      end
      object Label2: TLabel
        Left = 8
        Top = 8
        Width = 400
        Height = 16
        Caption = 'Select Storage Folder (BOM, TXT, CSV or VPL files)'
      end
      object Label6: TLabel
        Left = 5
        Top = 334
        Width = 120
        Height = 16
        Caption = 'Storage of item'
        Visible = False
      end
      object ButtonFeeders: TButton
        Left = 535
        Top = 31
        Width = 33
        Height = 24
        Caption = 'Add'
        TabOrder = 0
        OnClick = ButtonFeedersClick
      end
      object Btn_Feed_Sort_V: TButton
        Left = 168
        Top = 61
        Width = 188
        Height = 17
        Caption = 'sort'
        TabOrder = 1
        OnClick = Btn_Feed_Sort_VClick
      end
      object Btn_Feed_Sort_P: TButton
        Left = 357
        Top = 61
        Width = 188
        Height = 17
        Caption = 'sort'
        TabOrder = 2
        OnClick = Btn_Feed_Sort_PClick
      end
      object GridFeeders: TStringGrid
        Left = 1
        Top = 80
        Width = 576
        Height = 225
        ColCount = 3
        FixedCols = 0
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
        TabOrder = 3
        OnClick = GridFeedersClick
        OnDrawCell = GridFeedersDrawCell
      end
      object ComboHelp: TComboBox
        Left = 136
        Top = 307
        Width = 440
        Height = 22
        Style = csOwnerDrawFixed
        ItemHeight = 16
        TabOrder = 4
      end
      object Button1: TButton
        Left = 3
        Top = 62
        Width = 164
        Height = 16
        Caption = 'sort'
        TabOrder = 5
        OnClick = Button1Click
      end
      object StorageLine: TComboBox
        Left = 7
        Top = 32
        Width = 521
        Height = 22
        Style = csOwnerDrawFixed
        ItemHeight = 16
        TabOrder = 6
        OnChange = StorageLineChange
        OnKeyUp = StorageLineKeyUp
      end
      object ColMem: TComboBox
        Left = 279
        Top = 376
        Width = 26
        Height = 22
        Style = csOwnerDrawFixed
        ItemHeight = 16
        TabOrder = 7
        Visible = False
      end
      object Button2: TButton
        Left = 313
        Top = 380
        Width = 249
        Height = 20
        Caption = 'Feeder Table as Text File'
        TabOrder = 8
        OnClick = Button2Click
      end
      object Button3: TButton
        Left = 313
        Top = 401
        Width = 249
        Height = 20
        Caption = 'Save as storage'
        TabOrder = 9
        OnClick = Button3Click
      end
      object Button4: TButton
        Left = 313
        Top = 359
        Width = 249
        Height = 20
        Caption = 'Open current storage folder'
        TabOrder = 10
        OnClick = Button4Click
      end
      object Button5: TButton
        Left = 313
        Top = 422
        Width = 249
        Height = 20
        Caption = 'Part Report'
        Enabled = False
        TabOrder = 11
      end
      object GroupBox1: TGroupBox
        Left = 8
        Top = 358
        Width = 265
        Height = 80
        Caption = 'Column number of attribute'
        TabOrder = 12
        object Label16: TLabel
          Left = 52
          Top = 27
          Width = 40
          Height = 16
          Caption = 'value'
        end
        object Label19: TLabel
          Left = 52
          Top = 50
          Width = 56
          Height = 16
          Caption = 'package'
        end
        object fdr_col_V: TEdit
          Left = 142
          Top = 23
          Width = 65
          Height = 24
          TabOrder = 0
          OnChange = fdr_col_VChange
        end
        object fdr_col_P: TEdit
          Left = 142
          Top = 47
          Width = 65
          Height = 24
          TabOrder = 1
          OnChange = fdr_col_PChange
        end
      end
      object FileBox: TComboBox
        Left = 136
        Top = 332
        Width = 440
        Height = 22
        Style = csOwnerDrawFixed
        ItemHeight = 16
        TabOrder = 13
        Visible = False
      end
    end
    object Step_3: TTabSheet
      Caption = 'Projects'
      ImageIndex = 2
      object Label7: TLabel
        Left = 20
        Top = 343
        Width = 136
        Height = 16
        Caption = 'Values from files'
      end
      object Label15: TLabel
        Left = 20
        Top = 392
        Width = 152
        Height = 16
        Caption = 'Packages from files'
      end
      object PACKAGES: TComboBox
        Left = 19
        Top = 412
        Width = 262
        Height = 22
        Style = csOwnerDrawFixed
        ItemHeight = 16
        TabOrder = 7
      end
      object ProjectsList: TListBox
        Left = 0
        Top = 80
        Width = 577
        Height = 257
        ItemHeight = 16
        TabOrder = 0
        OnDblClick = ProjectsListDblClick
      end
      object ButtonProjects: TButton
        Left = 48
        Top = 27
        Width = 225
        Height = 27
        Caption = 'Select Project Folder'
        TabOrder = 1
        OnClick = ButtonProjectsClick
      end
      object ch_txt: TCheckBox
        Left = 320
        Top = 38
        Width = 161
        Height = 17
        Caption = 'TXT Tabular Files'
        TabOrder = 2
        OnClick = ch_csvClick
      end
      object ch_csv: TCheckBox
        Left = 320
        Top = 21
        Width = 97
        Height = 17
        Caption = 'CSV Files'
        TabOrder = 3
        OnClick = ch_csvClick
      end
      object ch_cmpr: TCheckBox
        Left = 320
        Top = 55
        Width = 201
        Height = 17
        Caption = 'FreePcb-2 VPL Files'
        Checked = True
        State = cbChecked
        TabOrder = 4
        OnClick = ch_csvClick
      end
      object BOM: TCheckBox
        Left = 320
        Top = 4
        Width = 105
        Height = 17
        Caption = 'BOM files'
        TabOrder = 5
        OnClick = ch_csvClick
      end
      object VALUES: TComboBox
        Left = 19
        Top = 365
        Width = 262
        Height = 22
        Style = csOwnerDrawFixed
        ItemHeight = 16
        TabOrder = 6
      end
      object FileNumbers: TComboBox
        Left = 272
        Top = 340
        Width = 25
        Height = 24
        ItemHeight = 16
        TabOrder = 8
        Visible = False
      end
      object GroupBox2: TGroupBox
        Left = 304
        Top = 354
        Width = 265
        Height = 81
        Caption = 'Column number of attribute'
        TabOrder = 9
        object Label1: TLabel
          Left = 52
          Top = 26
          Width = 40
          Height = 16
          Caption = 'value'
        end
        object Label8: TLabel
          Left = 52
          Top = 49
          Width = 56
          Height = 16
          Caption = 'package'
        end
        object Vcol: TEdit
          Left = 142
          Top = 22
          Width = 65
          Height = 24
          TabOrder = 0
          OnChange = fdr_col_VChange
        end
        object Pcol: TEdit
          Left = 142
          Top = 46
          Width = 65
          Height = 24
          TabOrder = 1
          OnChange = fdr_col_PChange
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Excluding'
      ImageIndex = 6
      object Label12: TLabel
        Left = 72
        Top = 32
        Width = 48
        Height = 16
        Caption = 'values'
      end
      object Label13: TLabel
        Left = 320
        Top = 32
        Width = 64
        Height = 16
        Caption = 'packages'
      end
      object ExclV: TMemo
        Left = 72
        Top = 56
        Width = 185
        Height = 281
        TabOrder = 0
      end
      object ExclP: TMemo
        Left = 320
        Top = 56
        Width = 185
        Height = 281
        TabOrder = 1
      end
      object ExcludingGroup: TGroupBox
        Left = 104
        Top = 369
        Width = 369
        Height = 57
        Caption = 'Exclude string from comparing '
        TabOrder = 2
        object ExcludeAsterisk: TCheckBox
          Left = 16
          Top = 24
          Width = 41
          Height = 17
          Caption = '*'
          TabOrder = 0
          OnClick = ExcludeAsteriskClick
        end
        object ExcludeDash: TCheckBox
          Left = 64
          Top = 24
          Width = 41
          Height = 17
          Caption = '-'
          TabOrder = 1
          OnClick = ExcludeAsteriskClick
        end
        object ExcludeUnderscore: TCheckBox
          Left = 112
          Top = 24
          Width = 41
          Height = 17
          Caption = '_'
          TabOrder = 2
          OnClick = ExcludeAsteriskClick
        end
        object ExcludeParentheses: TCheckBox
          Left = 160
          Top = 24
          Width = 41
          Height = 17
          Caption = '()'
          TabOrder = 3
          OnClick = ExcludeAsteriskClick
        end
        object ExcludeSlash: TCheckBox
          Left = 208
          Top = 24
          Width = 41
          Height = 17
          Caption = '/'
          TabOrder = 4
          OnClick = ExcludeAsteriskClick
        end
        object ExcludeComma: TCheckBox
          Left = 256
          Top = 24
          Width = 105
          Height = 17
          Caption = 'comma=dot'
          TabOrder = 5
          OnClick = ExcludeAsteriskClick
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Equating'
      ImageIndex = 5
      object Label14: TLabel
        Left = 272
        Top = 431
        Width = 128
        Height = 16
        Caption = 'Equating disable'
        Visible = False
      end
      object lbNoReplace: TMemo
        Left = 288
        Top = 426
        Width = 49
        Height = 31
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Style = [fsBold]
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 0
        Visible = False
      end
      object bnTest: TButton
        Left = 480
        Top = 416
        Width = 81
        Height = 20
        Caption = 'Test'
        TabOrder = 1
        Visible = False
        OnMouseDown = bnTestMouseDown
        OnMouseUp = ButtonScanMouseUp
      end
      object lbReplace: TStringGrid
        Left = 16
        Top = 32
        Width = 545
        Height = 361
        ColCount = 3
        FixedCols = 0
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
        TabOrder = 2
        OnClick = lbReplaceClick
        OnDrawCell = GridFeedersDrawCell
      end
      object DSL: TCheckBox
        Left = 16
        Top = 416
        Width = 233
        Height = 17
        Caption = 'Download Saved List'
        Checked = True
        State = cbChecked
        TabOrder = 3
        OnMouseUp = DSLMouseUp
      end
      object Memo1: TMemo
        Left = 343
        Top = 426
        Width = 50
        Height = 31
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Style = [fsBold]
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 4
        Visible = False
      end
    end
    object Step_5: TTabSheet
      Caption = 'Compare'
      ImageIndex = 4
      object Label4: TLabel
        Left = 8
        Top = 20
        Width = 48
        Height = 16
        Caption = 'Result'
      end
      object Btn_Sort_Match_V: TButton
        Left = 252
        Top = 21
        Width = 149
        Height = 17
        Caption = 'sort'
        TabOrder = 0
        OnClick = Btn_Sort_Match_VClick
      end
      object Btn_Sort_Match_P: TButton
        Left = 400
        Top = 21
        Width = 145
        Height = 17
        Caption = 'sort'
        TabOrder = 1
        OnClick = Btn_Sort_Match_PClick
      end
      object GridResult: TStringGrid
        Left = 0
        Top = 40
        Width = 576
        Height = 353
        ColCount = 3
        FixedCols = 0
        TabOrder = 2
      end
      object ButtonScan: TButton
        Left = 138
        Top = 416
        Width = 89
        Height = 20
        Caption = 'Scan'
        TabOrder = 3
        OnMouseUp = ButtonScanMouseUp
      end
      object Reset: TButton
        Left = 358
        Top = 416
        Width = 89
        Height = 20
        Caption = 'Reset'
        Enabled = False
        TabOrder = 4
        OnMouseUp = ResetMouseUp
      end
    end
    object TabSheet1: TTabSheet
      Caption = 'Report'
      ImageIndex = 5
      object TreeReport: TTreeView
        Left = 8
        Top = 8
        Width = 561
        Height = 393
        Indent = 19
        MultiSelect = True
        MultiSelectStyle = [msControlSelect, msShiftSelect, msVisibleOnly, msSiblingOnly]
        TabOrder = 0
        OnCustomDrawItem = TreeReportCustomDrawItem
        OnExpanding = TreeReportExpanding
        OnExpanded = TreeReportExpanded
        OnKeyUp = TreeReportKeyUp
        OnMouseDown = TreeReportMouseDown
        OnMouseMove = TreeReportMouseMove
        OnMouseUp = TreeReportMouseUp
      end
      object bnR: TButton
        Left = 11
        Top = 416
        Width = 89
        Height = 20
        Caption = 'As Text'
        TabOrder = 1
        OnClick = bnRClick
      end
      object StrikeThrough: TCheckBox
        Left = 128
        Top = 407
        Width = 425
        Height = 17
        Caption = 'Add strikethrough attributes to the exclusion list'
        TabOrder = 2
      end
      object AddSelSimilar: TCheckBox
        Left = 128
        Top = 429
        Width = 425
        Height = 17
        Caption = 'Add replaced component to the eguating list'
        TabOrder = 3
      end
    end
  end
  object ProgressBar1: TProgressBar
    Left = 154
    Top = 523
    Width = 417
    Height = 17
    Min = 0
    Max = 100
    TabOrder = 2
  end
  object lbReport: TListBox
    Left = 528
    Top = 512
    Width = 33
    Height = 33
    ItemHeight = 16
    TabOrder = 3
  end
  object CmdPlay: TTimer
    Enabled = False
    Interval = 500
    OnTimer = CmdPlayTimer
    Left = 488
    Top = 504
  end
  object SaveDialog: TSaveDialog
    Filter = 'Value-Package List (VPL)|*.vpl|All files|*.*'
    Options = [ofHideReadOnly, ofOldStyleDialog, ofForceShowHidden]
    Left = 448
    Top = 504
  end
end