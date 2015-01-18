object AppManagment: TAppManagment
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
  ClientHeight = 472
  ClientWidth = 536
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object pcSettings: TPageControl
    Left = 0
    Top = 0
    Width = 536
    Height = 433
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #1044#1080#1088#1077#1082#1090#1086#1088#1080#1080' '#1076#1083#1103' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object cbMode: TCheckBox
        Left = 3
        Top = 383
        Width = 222
        Height = 17
        Caption = #1042#1082#1083#1102#1095#1080#1090#1100' '#1072#1074#1090#1086#1084#1072#1090#1080#1095#1077#1089#1082#1086#1077' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1077
        TabOrder = 0
      end
      object gbCalibration: TGroupBox
        Left = 0
        Top = 319
        Width = 521
        Height = 58
        Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072
        TabOrder = 1
        object bFind14: TButton
          Tag = 13
          Left = 491
          Top = 26
          Width = 26
          Height = 23
          Caption = '...'
          TabOrder = 0
          OnClick = bFindClick
        end
        object bFind13: TButton
          Tag = 12
          Left = 231
          Top = 27
          Width = 26
          Height = 23
          Caption = '...'
          TabOrder = 1
          OnClick = bFindClick
        end
        object leSertPrintProtB: TLabeledEdit
          Left = 263
          Top = 28
          Width = 222
          Height = 21
          EditLabel.Width = 195
          EditLabel.Height = 13
          EditLabel.Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072' '#1090#1077#1085#1079#1086#1076#1072#1090#1095#1080#1082#1086#1074' '#1087#1086#1079#1080#1094#1080#1080' '#1041
          TabOrder = 2
        end
        object leSertPrintProtA: TLabeledEdit
          Left = 3
          Top = 28
          Width = 222
          Height = 21
          EditLabel.Width = 196
          EditLabel.Height = 13
          EditLabel.Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072' '#1090#1077#1085#1079#1086#1076#1072#1090#1095#1080#1082#1086#1074' '#1087#1086#1079#1080#1094#1080#1080' '#1040
          TabOrder = 3
        end
      end
      object gbAttestation: TGroupBox
        Left = 0
        Top = 143
        Width = 521
        Height = 170
        Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103
        TabOrder = 2
        object bFind12: TButton
          Tag = 11
          Left = 231
          Top = 144
          Width = 26
          Height = 23
          Caption = '...'
          TabOrder = 0
          OnClick = bFindClick
        end
        object bFind11: TButton
          Tag = 10
          Left = 491
          Top = 106
          Width = 26
          Height = 23
          Caption = '...'
          TabOrder = 1
          OnClick = bFindClick
        end
        object bFind10: TButton
          Tag = 9
          Left = 231
          Top = 106
          Width = 26
          Height = 23
          Caption = '...'
          TabOrder = 2
          OnClick = bFindClick
        end
        object bFind9: TButton
          Tag = 8
          Left = 491
          Top = 68
          Width = 26
          Height = 23
          Caption = '...'
          TabOrder = 3
          OnClick = bFindClick
        end
        object bFind8: TButton
          Tag = 7
          Left = 231
          Top = 68
          Width = 26
          Height = 23
          Caption = '...'
          TabOrder = 4
          OnClick = bFindClick
        end
        object bFind7: TButton
          Tag = 6
          Left = 491
          Top = 28
          Width = 26
          Height = 23
          Caption = '...'
          TabOrder = 5
          OnClick = bFindClick
        end
        object bFind6: TButton
          Tag = 5
          Left = 231
          Top = 29
          Width = 26
          Height = 23
          Caption = '...'
          TabOrder = 6
          OnClick = bFindClick
        end
        object leSpdCalibr: TLabeledEdit
          Left = 3
          Top = 145
          Width = 222
          Height = 21
          EditLabel.Width = 111
          EditLabel.Height = 13
          EditLabel.Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103' '#1073#1072#1088#1072#1073#1072#1085#1072
          TabOrder = 7
        end
        object leRCalibrB: TLabeledEdit
          Left = 263
          Top = 107
          Width = 222
          Height = 21
          EditLabel.Width = 176
          EditLabel.Height = 13
          EditLabel.Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103' '#1087#1086' '#1088#1072#1076#1080#1091#1089#1091' '#1087#1086#1079#1080#1094#1080#1080' '#1041' '
          TabOrder = 8
        end
        object leRCalibrA: TLabeledEdit
          Left = 3
          Top = 107
          Width = 222
          Height = 21
          EditLabel.Width = 177
          EditLabel.Height = 13
          EditLabel.Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103' '#1087#1086' '#1088#1072#1076#1080#1091#1089#1091' '#1087#1086#1079#1080#1094#1080#1080' '#1040' '
          TabOrder = 9
        end
        object leTCalibrB: TLabeledEdit
          Left = 263
          Top = 69
          Width = 222
          Height = 21
          EditLabel.Width = 197
          EditLabel.Height = 13
          EditLabel.Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103' '#1087#1086' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1077' '#1087#1086#1079#1080#1094#1080#1080' '#1041
          TabOrder = 10
        end
        object leTCalibrA: TLabeledEdit
          Left = 3
          Top = 69
          Width = 222
          Height = 21
          EditLabel.Width = 201
          EditLabel.Height = 13
          EditLabel.Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103' '#1087#1086' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1077' '#1087#1086#1079#1080#1094#1080#1080' '#1040' '
          TabOrder = 11
        end
        object leLoadCalibrB: TLabeledEdit
          Left = 263
          Top = 30
          Width = 222
          Height = 21
          EditLabel.Width = 177
          EditLabel.Height = 13
          EditLabel.Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103' '#1087#1086' '#1085#1072#1075#1088#1091#1079#1082#1077' '#1087#1086#1079#1080#1094#1080#1080' '#1041
          TabOrder = 12
        end
        object leLoadCalibrA: TLabeledEdit
          Left = 3
          Top = 30
          Width = 222
          Height = 21
          EditLabel.Width = 181
          EditLabel.Height = 13
          EditLabel.Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103' '#1087#1086' '#1085#1072#1075#1088#1091#1079#1082#1077' '#1087#1086#1079#1080#1094#1080#1080' '#1040' '
          TabOrder = 13
        end
      end
      object gbTest: TGroupBox
        Left = 0
        Top = 3
        Width = 521
        Height = 134
        Caption = #1048#1089#1087#1099#1090#1072#1085#1080#1103
        TabOrder = 3
        object bFind3: TButton
          Tag = 2
          Left = 231
          Top = 70
          Width = 26
          Height = 23
          Caption = '...'
          TabOrder = 0
          OnClick = bFindClick
        end
        object leProtA: TLabeledEdit
          Left = 3
          Top = 71
          Width = 222
          Height = 21
          EditLabel.Width = 105
          EditLabel.Height = 13
          EditLabel.Caption = #1055#1088#1086#1090#1086#1082#1083#1099' '#1087#1086#1079#1080#1094#1080#1080' '#1040
          TabOrder = 1
        end
        object leDistProg: TLabeledEdit
          Left = 3
          Top = 31
          Width = 222
          Height = 21
          EditLabel.Width = 122
          EditLabel.Height = 13
          EditLabel.Caption = #1055#1088#1086#1075#1088#1072#1084#1099' '#1087#1086' '#1076#1080#1089#1090#1072#1085#1094#1080#1080
          TabOrder = 2
        end
        object bFind4: TButton
          Tag = 3
          Left = 491
          Top = 70
          Width = 26
          Height = 23
          Caption = '...'
          TabOrder = 3
          OnClick = bFindClick
        end
        object bFind1: TButton
          Left = 231
          Top = 30
          Width = 26
          Height = 23
          Caption = '...'
          TabOrder = 4
          OnClick = bFindClick
        end
        object leTimeProg: TLabeledEdit
          Left = 263
          Top = 31
          Width = 222
          Height = 21
          EditLabel.Width = 116
          EditLabel.Height = 13
          EditLabel.Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1099' '#1087#1086' '#1074#1088#1077#1084#1077#1085#1080
          TabOrder = 5
        end
        object bFind2: TButton
          Tag = 1
          Left = 491
          Top = 30
          Width = 26
          Height = 23
          Caption = '...'
          TabOrder = 6
          OnClick = bFindClick
        end
        object leTitleProt: TLabeledEdit
          Left = 3
          Top = 108
          Width = 222
          Height = 21
          EditLabel.Width = 116
          EditLabel.Height = 13
          EditLabel.Caption = #1047#1072#1075#1086#1090#1086#1074#1082#1080' '#1087#1088#1086#1090#1086#1082#1086#1083#1086#1074
          TabOrder = 7
        end
        object leProtB: TLabeledEdit
          Left = 263
          Top = 71
          Width = 222
          Height = 21
          EditLabel.Width = 104
          EditLabel.Height = 13
          EditLabel.Caption = #1055#1088#1086#1090#1086#1082#1083#1099' '#1087#1086#1079#1080#1094#1080#1080' '#1041
          TabOrder = 8
        end
        object bFind5: TButton
          Tag = 4
          Left = 231
          Top = 107
          Width = 26
          Height = 23
          Caption = '...'
          TabOrder = 9
          OnClick = bFindClick
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103#1084#1080
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object Panel2: TPanel
        Left = 397
        Top = 0
        Width = 131
        Height = 405
        Align = alClient
        BevelKind = bkTile
        BevelOuter = bvNone
        TabOrder = 0
        object Panel3: TPanel
          Left = 0
          Top = 0
          Width = 127
          Height = 17
          Align = alTop
          Caption = #1043#1088#1091#1087#1087#1099
          TabOrder = 0
        end
        object sgGroups: TStringGrid
          Left = 0
          Top = 17
          Width = 127
          Height = 384
          Align = alClient
          BorderStyle = bsNone
          ColCount = 1
          DefaultColWidth = 120
          DefaultRowHeight = 16
          FixedCols = 0
          RowCount = 1
          FixedRows = 0
          PopupMenu = pabGroups
          TabOrder = 1
        end
      end
      object Panel4: TPanel
        Left = 0
        Top = 0
        Width = 397
        Height = 405
        Align = alLeft
        BevelKind = bkTile
        BevelOuter = bvNone
        BiDiMode = bdLeftToRight
        Caption = 'Panel4'
        ParentBiDiMode = False
        TabOrder = 1
        object sgUsers: TStringGrid
          Left = 0
          Top = 17
          Width = 393
          Height = 384
          Align = alClient
          BorderStyle = bsNone
          ColCount = 4
          DefaultColWidth = 16
          DefaultRowHeight = 16
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect, goFixedRowClick]
          PopupMenu = pabUsers
          TabOrder = 0
          OnFixedCellClick = sgUsersFixedCellClick
          OnSelectCell = sgUsersSelectCell
        end
        object Panel5: TPanel
          Left = 0
          Top = 0
          Width = 393
          Height = 17
          Align = alTop
          Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1080
          TabOrder = 1
        end
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 433
    Width = 536
    Height = 39
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      536
      39)
    object BitBtn2: TBitBtn
      Left = 376
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1054#1090#1084#1077#1085#1072
      DoubleBuffered = True
      Kind = bkCancel
      NumGlyphs = 2
      ParentDoubleBuffered = False
      TabOrder = 0
    end
    object BitBtn1: TBitBtn
      Left = 457
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1055#1088#1080#1085#1103#1090#1100
      Default = True
      DoubleBuffered = True
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        3333333333333333333333330000333333333333333333333333F33333333333
        00003333344333333333333333388F3333333333000033334224333333333333
        338338F3333333330000333422224333333333333833338F3333333300003342
        222224333333333383333338F3333333000034222A22224333333338F338F333
        8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
        33333338F83338F338F33333000033A33333A222433333338333338F338F3333
        0000333333333A222433333333333338F338F33300003333333333A222433333
        333333338F338F33000033333333333A222433333333333338F338F300003333
        33333333A222433333333333338F338F00003333333333333A22433333333333
        3338F38F000033333333333333A223333333333333338F830000333333333333
        333A333333333333333338330000333333333333333333333333333333333333
        0000}
      ModalResult = 1
      NumGlyphs = 2
      ParentDoubleBuffered = False
      TabOrder = 1
      OnClick = BitBtn1Click
    end
  end
  object pabUsers: TPopupActionBar
    Left = 224
    Top = 80
    object UserAdd: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      OnClick = UserAddClick
    end
    object UserUpdate: TMenuItem
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100
      OnClick = UserUpdateClick
    end
    object UserDel: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100
      OnClick = UserDelClick
    end
    object N4: TMenuItem
      Caption = #1043#1088#1091#1087#1087#1072
      object AddGroup1: TMenuItem
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        OnClick = AddGroupClick
      end
      object GroupDel1: TMenuItem
        Caption = #1059#1076#1072#1083#1080#1090#1100
        OnClick = GroupDel1Click
      end
    end
  end
  object pabGroups: TPopupActionBar
    Left = 312
    Top = 80
    object AddGroup2: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      OnClick = AddGroupClick
    end
    object GroupDel2: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100
      OnClick = GroupDel2Click
    end
  end
  object sdPath: TSaveDialog
    FileName = 'file'
    FilterIndex = 0
    Options = [ofHideReadOnly, ofShareAware, ofEnableSizing, ofDontAddToRecent]
    Left = 400
  end
end
