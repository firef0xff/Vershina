object mfRB: TmfRB
  Left = 0
  Top = 0
  Anchors = [akTop, akRight]
  Caption = 'Run-in bench'
  ClientHeight = 713
  ClientWidth = 1016
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  WindowState = wsMaximized
  OnCloseQuery = OnCloseQuery
  OnResize = OnMFResize
  PixelsPerInch = 96
  TextHeight = 14
  object lTPollingTblNme: TLabel
    Left = 342
    Top = 150
    Width = 86
    Height = 14
    Caption = 'lTPollingTblNme'
  end
  object sbRB: TStatusBar
    Left = 0
    Top = 694
    Width = 1016
    Height = 19
    Panels = <
      item
        Text = #1057#1086#1077#1076#1080#1085#1077#1085#1080#1077' '#1089#1086' '#1089#1090#1077#1085#1076#1086#1084' '#1091#1089#1090#1072#1085#1086#1074#1083#1077#1085#1086
        Width = 255
      end
      item
        Text = 'CycleCnt='
        Width = 95
      end
      item
        Text = 'empty'
        Width = 525
      end
      item
        Text = '00/00/2010 00:00'
        Width = 141
      end>
  end
  object pcRB: TPageControl
    Left = 0
    Top = 66
    Width = 816
    Height = 628
    ActivePage = tsCalibration
    Align = alClient
    TabOrder = 1
    object tsCurrentStatus: TTabSheet
      Caption = #1058#1077#1082#1091#1097#1077#1077' '#1089#1086#1089#1090#1086#1103#1085#1080#1077
      object Splitter1: TSplitter
        Left = 0
        Top = 306
        Width = 808
        Height = 3
        Cursor = crVSplit
        Align = alTop
        ExplicitTop = 269
        ExplicitWidth = 858
      end
      object pParam1: TPanel
        Left = 0
        Top = 0
        Width = 808
        Height = 306
        Align = alTop
        TabOrder = 0
        object stP1TL0C1: TStaticText
          Left = 137
          Top = 0
          Width = 234
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BorderStyle = sbsSingle
          Caption = #1056#1045#1046#1048#1052' '#1055#1054#1047#1048#1062#1048#1071' '#1040
          TabOrder = 0
        end
        object stP1CurDate: TStaticText
          Left = 0
          Top = 0
          Width = 138
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BorderStyle = sbsSingle
          Caption = #1058#1045#1050#1059#1065#1040#1071' '#1044#1040#1058#1040
          TabOrder = 1
        end
        object stP1TTyreType: TStaticText
          Left = 0
          Top = 15
          Width = 138
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BorderStyle = sbsSingle
          Caption = #1052#1040#1056#1050#1040' '#1055#1054#1050#1056#1067#1064#1050#1048
          Color = clGray
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clLime
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentColor = False
          ParentFont = False
          TabOrder = 2
        end
        object stP1L1TyreTypeA: TStaticText
          Left = 137
          Top = 15
          Width = 234
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 3
        end
        object stP1TProgName: TStaticText
          Left = 0
          Top = 30
          Width = 138
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BorderStyle = sbsSingle
          Caption = #1055#1056#1054#1043#1056#1040#1052#1052#1040' '#1054#1041#1050#1040#1058#1050#1048
          Color = clGray
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clLime
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentColor = False
          ParentFont = False
          TabOrder = 4
        end
        object stP1L2ProgNameA: TStaticText
          Left = 137
          Top = 30
          Width = 234
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 5
        end
        object pP1PT2: TPanel
          Left = 0
          Top = 45
          Width = 371
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1047#1053#1040#1063#1045#1053#1048#1071':'
          Color = clMedGray
          ParentBackground = False
          TabOrder = 6
        end
        object pP1PL1Ttl: TPanel
          Left = 0
          Top = 60
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1055#1040#1056#1040#1052#1045#1058#1056#1067' '#1054#1041#1050#1040#1058#1050#1048
          Color = clMedGray
          ParentBackground = False
          TabOrder = 7
        end
        object pP1L1C1Ttl: TPanel
          Left = 138
          Top = 60
          Width = 78
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1047#1040#1044#1040#1053#1053#1054#1045
          Color = clMedGray
          ParentBackground = False
          TabOrder = 8
        end
        object pP1L1C2Ttl: TPanel
          Left = 216
          Top = 60
          Width = 78
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1058#1045#1050#1059#1065#1045#1045
          Color = clMedGray
          ParentBackground = False
          TabOrder = 9
        end
        object pP1L1C3Ttl: TPanel
          Left = 294
          Top = 60
          Width = 78
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1053#1040' '#1057#1051#1045#1044'. '#1064#1040#1043#1045
          Color = clMedGray
          ParentBackground = False
          TabOrder = 10
        end
        object pP1PL2Ttl: TPanel
          Left = 0
          Top = 75
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1054#1041#1065#1045#1045' '#1042#1056#1045#1052#1071' '#1048#1057#1055#1067#1058#1040#1053#1048#1071
          Color = clMedGray
          ParentBackground = False
          TabOrder = 11
        end
        object pP1PL3Ttl: TPanel
          Left = 0
          Top = 90
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1054#1041#1065#1048#1049' '#1055#1059#1058#1068', '#1050#1052
          Color = clMedGray
          ParentBackground = False
          TabOrder = 12
        end
        object pP1PL4Ttl: TPanel
          Left = 0
          Top = 105
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1057#1050#1054#1056#1054#1057#1058#1068' '#1054#1041#1050#1040#1058#1050#1048', '#1050#1052'/'#1063#1040#1057
          Color = clMedGray
          ParentBackground = False
          TabOrder = 13
        end
        object pP1PL5Ttl: TPanel
          Left = 0
          Top = 120
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1053#1040#1043#1056#1059#1047#1050#1040', '#1082#1053
          Color = clMedGray
          ParentBackground = False
          TabOrder = 14
        end
        object pP1PL6Ttl: TPanel
          Left = 0
          Top = 135
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1044#1040#1042#1051#1045#1053#1048#1045' '#1042' '#1064#1048#1053#1045', '#1082#1055#1072
          Color = clMedGray
          ParentBackground = False
          TabOrder = 15
        end
        object pP1PL7Ttl: TPanel
          Left = 0
          Top = 150
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1058#1045#1052#1055#1045#1056#1040#1058#1059#1056#1040' '#1042#1054#1047#1044#1059#1061#1040', '#1057
          Color = clMedGray
          ParentBackground = False
          TabOrder = 16
        end
        object pP1PL8Ttl: TPanel
          Left = 0
          Top = 165
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1056#1040#1044#1048#1059#1057' '#1064#1048#1053#1067', '#1084#1084
          Color = clMedGray
          ParentBackground = False
          TabOrder = 17
        end
        object pP1PL9Ttl: TPanel
          Left = 0
          Top = 180
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #8470' '#1056#1040#1041#1054#1063#1045#1043#1054' '#1064#1040#1043#1040
          Color = clMedGray
          ParentBackground = False
          TabOrder = 18
        end
        object stP1CParL1C1: TStaticText
          Left = 138
          Top = 75
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 19
        end
        object stP1CParL1C2: TStaticText
          Left = 216
          Top = 75
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          Color = clBtnFace
          ParentColor = False
          TabOrder = 20
        end
        object stP1CParL1C3: TStaticText
          Left = 294
          Top = 75
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 21
        end
        object stP1CParL2C1: TStaticText
          Left = 138
          Top = 90
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 22
        end
        object stP1CParL2C2: TStaticText
          Left = 216
          Top = 90
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 23
        end
        object stP1CParL2C3: TStaticText
          Left = 294
          Top = 90
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 24
        end
        object stP1CParL3C1: TStaticText
          Left = 138
          Top = 105
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 25
        end
        object stP1CParL3C2: TStaticText
          Left = 216
          Top = 105
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 26
        end
        object stP1CParL3C3: TStaticText
          Left = 294
          Top = 105
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 27
        end
        object stP1CParL4C3: TStaticText
          Left = 294
          Top = 120
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 28
          Transparent = False
        end
        object stP1CParL4C2: TStaticText
          Left = 216
          Top = 120
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 29
          Transparent = False
        end
        object stP1CParL4C1: TStaticText
          Left = 138
          Top = 120
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 30
          Transparent = False
        end
        object stP1CParL5C1: TStaticText
          Left = 138
          Top = 135
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 31
        end
        object stP1CParL5C2: TStaticText
          Left = 216
          Top = 135
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 32
        end
        object stP1CParL5C3: TStaticText
          Left = 294
          Top = 135
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 33
        end
        object stP1CParL6C1: TStaticText
          Left = 138
          Top = 150
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 34
        end
        object stP1CParL6C2: TStaticText
          Left = 216
          Top = 150
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 35
        end
        object stP1CParL6C3: TStaticText
          Left = 294
          Top = 150
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 36
        end
        object stP1CParL7C1: TStaticText
          Left = 138
          Top = 165
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 37
        end
        object stP1CParL7C2: TStaticText
          Left = 216
          Top = 165
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 38
        end
        object stP1CParL7C3: TStaticText
          Left = 294
          Top = 165
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 39
        end
        object stP1CParL8C1: TStaticText
          Left = 138
          Top = 180
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 40
          Transparent = False
        end
        object stP1CParL8C2: TStaticText
          Left = 216
          Top = 180
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 41
          Transparent = False
        end
        object stP1CParL8C3: TStaticText
          Left = 294
          Top = 180
          Width = 78
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 42
          Transparent = False
        end
      end
      object pParam2: TPanel
        Left = 0
        Top = 309
        Width = 808
        Height = 290
        Align = alClient
        TabOrder = 1
        object pP2TtlL0C1: TPanel
          Left = 138
          Top = 2
          Width = 233
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1054#1055#1056#1054#1057
          Color = clMedGray
          ParentBackground = False
          TabOrder = 0
        end
        object pP2TtlL1C1: TPanel
          Left = 138
          Top = 15
          Width = 117
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1055#1054' '#1042#1056#1045#1052#1045#1053#1048
          Color = clMedGray
          ParentBackground = False
          TabOrder = 1
        end
        object pP2TtlL1C2: TPanel
          Left = 255
          Top = 15
          Width = 117
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1055#1054' '#1055#1056#1054#1041#1045#1043#1059
          Color = clMedGray
          ParentBackground = False
          TabOrder = 2
        end
        object pP2TtlL1C0: TPanel
          Left = 0
          Top = 30
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1042#1056#1045#1052#1071
          Color = clMedGray
          ParentBackground = False
          TabOrder = 3
        end
        object pP2TtlL2C0: TPanel
          Left = 0
          Top = 45
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1055#1059#1058#1068', '#1050#1052
          Color = clMedGray
          ParentBackground = False
          TabOrder = 4
        end
        object pP2TtlL3C0: TPanel
          Left = 0
          Top = 60
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1057#1050#1054#1056#1054#1057#1058#1068', '#1050#1052'/'#1063#1040#1057
          Color = clMedGray
          ParentBackground = False
          TabOrder = 5
        end
        object pP2TtlL4C0: TPanel
          Left = 0
          Top = 75
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1053#1040#1043#1056#1059#1047#1050#1040', '#1082#1053
          Color = clMedGray
          ParentBackground = False
          TabOrder = 6
        end
        object pP2TtlL7C0: TPanel
          Left = 0
          Top = 120
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1057#1051#1045#1044#1059#1070#1065#1048#1049' '#1054#1055#1056#1054#1057' ('#1095#1072#1089'/'#1082#1084')'
          Color = clMedGray
          ParentBackground = False
          TabOrder = 7
        end
        object pP2TtlL5C0: TPanel
          Left = 0
          Top = 90
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1058#1045#1052#1055#1045#1056#1040#1058#1059#1056#1040' '#1042#1054#1047#1044#1059#1061#1040', '#1057
          Color = clMedGray
          ParentBackground = False
          TabOrder = 8
        end
        object pP2TtlL6C0: TPanel
          Left = 0
          Top = 105
          Width = 138
          Height = 15
          BevelOuter = bvSpace
          BorderStyle = bsSingle
          Caption = #1056#1040#1044#1048#1059#1057', '#1084#1084
          Color = clMedGray
          ParentBackground = False
          TabOrder = 9
        end
        object stP2CParL1C1: TStaticText
          Left = 138
          Top = 30
          Width = 117
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 10
        end
        object stP2CParL2C1: TStaticText
          Left = 138
          Top = 45
          Width = 117
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 11
        end
        object stP2CParL3C1: TStaticText
          Left = 138
          Top = 60
          Width = 117
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 12
        end
        object stP2CParL4C1: TStaticText
          Left = 138
          Top = 75
          Width = 117
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 13
          Transparent = False
        end
        object stP2CParL5C1: TStaticText
          Left = 138
          Top = 90
          Width = 117
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 14
        end
        object stP2CParL6C1: TStaticText
          Left = 138
          Top = 105
          Width = 117
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 15
        end
        object stP2CParL7C1: TStaticText
          Left = 138
          Top = 120
          Width = 117
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 16
        end
        object stP2CParL7C2: TStaticText
          Left = 255
          Top = 120
          Width = 117
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 17
        end
        object stP2CParL6C2: TStaticText
          Left = 255
          Top = 105
          Width = 117
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 18
        end
        object stP2CParL5C2: TStaticText
          Left = 255
          Top = 90
          Width = 117
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 19
        end
        object stP2CParL4C2: TStaticText
          Left = 255
          Top = 75
          Width = 117
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 20
          Transparent = False
        end
        object stP2CParL3C2: TStaticText
          Left = 255
          Top = 60
          Width = 117
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 21
        end
        object stP2CParL2C2: TStaticText
          Left = 255
          Top = 45
          Width = 117
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 22
        end
        object stP2CParL1C2: TStaticText
          Left = 255
          Top = 30
          Width = 117
          Height = 15
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          BevelOuter = bvRaised
          BorderStyle = sbsSunken
          TabOrder = 23
        end
      end
    end
    object tsManual: TTabSheet
      Caption = #1056#1091#1095#1085#1086#1081' '#1088#1077#1078#1080#1084
      ImageIndex = 6
      object gbDrum: TGroupBox
        Left = 225
        Top = 10
        Width = 158
        Height = 438
        BiDiMode = bdLeftToRight
        Caption = #1041#1040#1056#1040#1041#1040#1053
        Color = clBtnHighlight
        ParentBackground = False
        ParentBiDiMode = False
        ParentColor = False
        TabOrder = 0
        object lSpeed0: TLabel
          Left = 111
          Top = 286
          Width = 22
          Height = 15
          Alignment = taRightJustify
          AutoSize = False
          Caption = '0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = 13
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object lSpeed25: TLabel
          Left = 111
          Top = 267
          Width = 22
          Height = 15
          Alignment = taRightJustify
          AutoSize = False
          Caption = '25'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = 13
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object sbDrumOn: TSpeedButton
          Left = 14
          Top = 284
          Width = 19
          Height = 19
          AllowAllUp = True
          GroupIndex = 1
          Glyph.Data = {
            360C0000424D360C000000000000360000002800000040000000100000000100
            180000000000000C000000000000000000000000000000000000008080008080
            0080800080800080800080800080800080800080800080800080800080800080
            8000808000808000808000808000808000808000808000808000808000808000
            8080008080008080008080008080008080008080008080008080008080008080
            0080800080800080800080800080800080800080800080800080800080800080
            8000808000808000808000808000808000808000808000808000808000808000
            8080008080008080008080008080008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080008080008080
            008080000000000000BFBFBFBFBFBF7F7F7F7F7F7F7F7F7F0000000000000080
            80008080008080008080008080008080008080000000000000BFBFBFBFBFBF7F
            7F7F7F7F7F7F7F7F000000000000008080008080008080008080008080008080
            008080000000000000BFBFBFBFBFBF7F7F7F7F7F7F7F7F7F0000000000000080
            80008080008080008080008080008080008080000000000000BFBFBFBFBFBF7F
            7F7F7F7F7F7F7F7F000000000000008080008080008080008080008080008080
            000000BFBFBFBFBFBF7F7F7F0000000000000000007F7F7F7F7F7F7F7F7F0000
            00008080008080008080008080008080000000BFBFBFBFBFBF7F7F7F00000000
            00000000007F7F7F7F7F7F7F7F7F000000008080008080008080008080008080
            000000BFBFBFBFBFBF7F7F7F0000000000000000007F7F7F7F7F7F7F7F7F0000
            00008080008080008080008080008080000000BFBFBFBFBFBF7F7F7F00000000
            00000000007F7F7F7F7F7F7F7F7F000000008080008080008080008080000000
            BFBFBFBFBFBF000000FFFFFF0000FFFFFFFF0000FFFFFFFF0000007F7F7F7F7F
            7F000000008080008080008080000000BFBFBFBFBFBF000000FFFFFF0000FFFF
            FFFF0000FFFFFFFF0000007F7F7F7F7F7F000000008080008080008080000000
            BFBFBFBFBFBF000000FFFFFF00FF00FFFFFF00FF00FFFFFF0000007F7F7F7F7F
            7F000000008080008080008080000000BFBFBFBFBFBF000000FFFFFF00FF00FF
            FFFF00FF00FFFFFF0000007F7F7F7F7F7F000000008080008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF0000007F7F
            7F000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF0000007F7F7F000000008080008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF0000007F7F
            7F000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF0000007F7F7F000000008080008080000000BFBFBF
            7F7F7FFFFFFF0000000000000000FF000080000080000000000000FFFFFF7F7F
            7F7F7F7F000000008080000000BFBFBF7F7F7FFFFFFF0000000000000000FF00
            0080000080000000000000FFFFFF7F7F7F7F7F7F000000008080000000BFBFBF
            7F7F7FFFFFFF00000000000000FF00008000008000000000000000FFFFFF7F7F
            7F7F7F7F000000008080000000BFBFBF7F7F7FFFFFFF00000000000000FF0000
            8000008000000000000000FFFFFF7F7F7F7F7F7F000000008080000000BFBFBF
            0000000000FF0000000000FF0000800000FF0000800000800000000000FF0000
            007F7F7F000000008080000000BFBFBF0000000000FF0000000000FF00008000
            00FF0000800000800000000000FF0000007F7F7F000000008080000000BFBFBF
            00000000FF0000000000FF0000800000FF0000800000800000000000FF000000
            007F7F7F000000008080000000BFBFBF00000000FF0000000000FF0000800000
            FF0000800000800000000000FF000000007F7F7F000000008080000000FFFFFF
            000000FFFFFF0000000000FF0000FF0000FF0000FF000080000000FFFFFF0000
            007F7F7F000000008080000000FFFFFF000000FFFFFF0000000000FF0000FF00
            00FF0000FF000080000000FFFFFF0000007F7F7F000000008080000000FFFFFF
            000000FFFFFF00000000FF0000FF0000FF0000FF00008000000000FFFFFF0000
            007F7F7F000000008080000000FFFFFF000000FFFFFF00000000FF0000FF0000
            FF0000FF00008000000000FFFFFF0000007F7F7F000000008080000000FFFFFF
            0000000000FF000000FFFFFF0000FF0000FF0000800000FF0000000000FF0000
            00BFBFBF000000008080000000FFFFFF0000000000FF000000FFFFFF0000FF00
            00FF0000800000FF0000000000FF000000BFBFBF000000008080000000FFFFFF
            00000000FF00000000FFFFFF00FF0000FF0000800000FF0000000000FF000000
            00BFBFBF000000008080000000FFFFFF00000000FF00000000FFFFFF00FF0000
            FF0000800000FF0000000000FF00000000BFBFBF000000008080000000FFFFFF
            7F7F7FFFFFFF000000000000FFFFFFFFFFFF0000FF000000000000FFFFFF7F7F
            7FBFBFBF000000008080000000FFFFFF7F7F7FFFFFFF000000000000FFFFFFFF
            FFFF0000FF000000000000FFFFFF7F7F7FBFBFBF000000008080000000FFFFFF
            7F7F7FFFFFFF000000000000FFFFFFFFFFFF00FF00000000000000FFFFFF7F7F
            7FBFBFBF000000008080000000FFFFFF7F7F7FFFFFFF000000000000FFFFFFFF
            FFFF00FF00000000000000FFFFFF7F7F7FBFBFBF000000008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF000000BFBF
            BF000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF000000BFBFBF000000008080008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF000000BFBF
            BF000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF000000BFBFBF000000008080008080008080000000
            FFFFFFBFBFBF000000FFFFFF0000FFFFFFFF0000FFFFFFFF000000BFBFBFBFBF
            BF000000008080008080008080000000FFFFFFBFBFBF000000FFFFFF0000FFFF
            FFFF0000FFFFFFFF000000BFBFBFBFBFBF000000008080008080008080000000
            FFFFFFBFBFBF000000FFFFFF00FF00FFFFFF00FF00FFFFFF000000BFBFBFBFBF
            BF000000008080008080008080000000FFFFFFBFBFBF000000FFFFFF00FF00FF
            FFFF00FF00FFFFFF000000BFBFBFBFBFBF000000008080008080008080008080
            000000FFFFFFBFBFBF7F7F7F0000000000000000007F7F7FBFBFBFBFBFBF0000
            00008080008080008080008080008080000000FFFFFFBFBFBF7F7F7F00000000
            00000000007F7F7FBFBFBFBFBFBF000000008080008080008080008080008080
            000000FFFFFFBFBFBF7F7F7F0000000000000000007F7F7FBFBFBFBFBFBF0000
            00008080008080008080008080008080000000FFFFFFBFBFBF7F7F7F00000000
            00000000007F7F7FBFBFBFBFBFBF000000008080008080008080008080008080
            008080000000000000FFFFFFFFFFFFFFFFFFBFBFBFBFBFBF0000000000000080
            80008080008080008080008080008080008080000000000000FFFFFFFFFFFFFF
            FFFFBFBFBFBFBFBF000000000000008080008080008080008080008080008080
            008080000000000000FFFFFFFFFFFFFFFFFFBFBFBFBFBFBF0000000000000080
            80008080008080008080008080008080008080000000000000FFFFFFFFFFFFFF
            FFFFBFBFBFBFBFBF000000000000008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080}
          NumGlyphs = 4
        end
        object lSpeed75: TLabel
          Left = 111
          Top = 227
          Width = 22
          Height = 15
          Alignment = taRightJustify
          AutoSize = False
          Caption = '75'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = 13
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object lSpeed50: TLabel
          Left = 111
          Top = 246
          Width = 22
          Height = 15
          Alignment = taRightJustify
          AutoSize = False
          Caption = '50'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = 13
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object lSpeed100: TLabel
          Left = 111
          Top = 211
          Width = 22
          Height = 15
          Alignment = taRightJustify
          AutoSize = False
          Caption = '100'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = 13
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object lSpeed125: TLabel
          Left = 111
          Top = 194
          Width = 22
          Height = 15
          Alignment = taRightJustify
          AutoSize = False
          Caption = '125'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = 13
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object lSpeed150: TLabel
          Left = 111
          Top = 173
          Width = 22
          Height = 15
          Alignment = taRightJustify
          AutoSize = False
          Caption = '150'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = 13
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object lSpeed175: TLabel
          Left = 111
          Top = 152
          Width = 22
          Height = 15
          Alignment = taRightJustify
          AutoSize = False
          Caption = '175'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = 13
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object lSpeed200: TLabel
          Left = 111
          Top = 131
          Width = 22
          Height = 15
          Alignment = taRightJustify
          AutoSize = False
          Caption = '200'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = 13
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object lSpeed225: TLabel
          Left = 111
          Top = 122
          Width = 22
          Height = 15
          Alignment = taRightJustify
          AutoSize = False
          Caption = '225'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = 13
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object lSpeed250: TLabel
          Left = 111
          Top = 101
          Width = 22
          Height = 15
          Alignment = taRightJustify
          AutoSize = False
          Caption = '250'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = 13
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object lSpeed300: TLabel
          Left = 111
          Top = 59
          Width = 22
          Height = 15
          Alignment = taRightJustify
          AutoSize = False
          Caption = '300'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = 13
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object lSpeed275: TLabel
          Left = 111
          Top = 80
          Width = 22
          Height = 15
          Alignment = taRightJustify
          AutoSize = False
          Caption = '275'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = 13
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object leSetDrumSpeed: TLabeledEdit
          Left = 15
          Top = 113
          Width = 48
          Height = 22
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 57
          EditLabel.Height = 14
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = #1047#1040#1044#1040#1053#1048#1045':'
          EditLabel.ParentBiDiMode = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clOlive
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentBiDiMode = False
          ParentFont = False
          TabOrder = 0
          Text = '40'
          OnKeyPress = leSetDrumSpeedKeyPress
        end
        object pDrumTtl: TPanel
          Left = 8
          Top = 326
          Width = 142
          Height = 19
          BevelInner = bvLowered
          BorderWidth = 1
          BorderStyle = bsSingle
          Caption = #1059#1055#1056#1040#1042#1051#1045#1053#1048#1045' '#1041#1040#1056#1040#1041#1040#1053#1054#1052
          Color = clBackground
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindow
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentBackground = False
          ParentFont = False
          TabOrder = 1
        end
        object btnDrumOn: TButton
          Left = 23
          Top = 353
          Width = 112
          Height = 30
          Caption = #1042#1050#1051#1070#1063#1048#1058#1068', F6'
          TabOrder = 2
          OnClick = OnDrumOn
        end
        object btnDrumOff: TButton
          Left = 23
          Top = 393
          Width = 112
          Height = 30
          Caption = #1042#1067#1050#1051#1070#1063#1048#1058#1068', F7'
          TabOrder = 3
          OnClick = OnDrumOff
        end
        object tbCurrentDrumSpeed: TTrackBar
          Left = 68
          Top = 53
          Width = 37
          Height = 255
          Ctl3D = True
          DragMode = dmAutomatic
          Max = 300
          Orientation = trVertical
          ParentCtl3D = False
          Frequency = 25
          Position = 300
          PositionToolTip = ptRight
          SelEnd = 300
          SelStart = 300
          TabOrder = 4
          ThumbLength = 30
          TickMarks = tmBoth
        end
        object pDrumSpeed: TPanel
          Left = 8
          Top = 15
          Width = 142
          Height = 20
          BevelInner = bvLowered
          BorderWidth = 1
          BorderStyle = bsSingle
          Caption = #1057#1050#1054#1056#1054#1057#1058#1068', '#1050#1052'/'#1063#1072#1089
          Color = clBackground
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindow
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentBackground = False
          ParentFont = False
          TabOrder = 5
        end
        object leCurrentDrumSpeed: TLabeledEdit
          Left = 15
          Top = 69
          Width = 48
          Height = 23
          AutoSize = False
          EditLabel.Width = 59
          EditLabel.Height = 14
          EditLabel.Caption = #1058#1045#1050#1059#1065#1040#1071':'
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          ReadOnly = True
          TabOrder = 6
          Text = '10'
        end
      end
      object gbCarriage1: TGroupBox
        Left = 3
        Top = 10
        Width = 219
        Height = 438
        Caption = #1055#1054#1047#1048#1062#1048#1071' '#1040
        TabOrder = 1
        object sbCarriage1Off: TSpeedButton
          Left = 2
          Top = 416
          Width = 19
          Height = 19
          AllowAllUp = True
          GroupIndex = 1
          Down = True
          Glyph.Data = {
            360C0000424D360C000000000000360000002800000040000000100000000100
            180000000000000C000000000000000000000000000000000000008080008080
            0080800080800080800080800080800080800080800080800080800080800080
            8000808000808000808000808000808000808000808000808000808000808000
            8080008080008080008080008080008080008080008080008080008080008080
            0080800080800080800080800080800080800080800080800080800080800080
            8000808000808000808000808000808000808000808000808000808000808000
            8080008080008080008080008080008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080008080008080
            008080000000000000BFBFBFBFBFBF7F7F7F7F7F7F7F7F7F0000000000000080
            80008080008080008080008080008080008080000000000000BFBFBFBFBFBF7F
            7F7F7F7F7F7F7F7F000000000000008080008080008080008080008080008080
            008080000000000000BFBFBFBFBFBF7F7F7F7F7F7F7F7F7F0000000000000080
            80008080008080008080008080008080008080000000000000BFBFBFBFBFBF7F
            7F7F7F7F7F7F7F7F000000000000008080008080008080008080008080008080
            000000BFBFBFBFBFBF7F7F7F0000000000000000007F7F7F7F7F7F7F7F7F0000
            00008080008080008080008080008080000000BFBFBFBFBFBF7F7F7F00000000
            00000000007F7F7F7F7F7F7F7F7F000000008080008080008080008080008080
            000000BFBFBFBFBFBF7F7F7F0000000000000000007F7F7F7F7F7F7F7F7F0000
            00008080008080008080008080008080000000BFBFBFBFBFBF7F7F7F00000000
            00000000007F7F7F7F7F7F7F7F7F000000008080008080008080008080000000
            BFBFBFBFBFBF000000FFFFFF0000FFFFFFFF0000FFFFFFFF0000007F7F7F7F7F
            7F000000008080008080008080000000BFBFBFBFBFBF000000FFFFFF0000FFFF
            FFFF0000FFFFFFFF0000007F7F7F7F7F7F000000008080008080008080000000
            BFBFBFBFBFBF000000FFFFFF00FF00FFFFFF00FF00FFFFFF0000007F7F7F7F7F
            7F000000008080008080008080000000BFBFBFBFBFBF000000FFFFFF00FF00FF
            FFFF00FF00FFFFFF0000007F7F7F7F7F7F000000008080008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF0000007F7F
            7F000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF0000007F7F7F000000008080008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF0000007F7F
            7F000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF0000007F7F7F000000008080008080000000BFBFBF
            7F7F7FFFFFFF0000000000000000FF000080000080000000000000FFFFFF7F7F
            7F7F7F7F000000008080000000BFBFBF7F7F7FFFFFFF0000000000000000FF00
            0080000080000000000000FFFFFF7F7F7F7F7F7F000000008080000000BFBFBF
            7F7F7FFFFFFF00000000000000FF00008000008000000000000000FFFFFF7F7F
            7F7F7F7F000000008080000000BFBFBF7F7F7FFFFFFF00000000000000FF0000
            8000008000000000000000FFFFFF7F7F7F7F7F7F000000008080000000BFBFBF
            0000000000FF0000000000FF0000800000FF0000800000800000000000FF0000
            007F7F7F000000008080000000BFBFBF0000000000FF0000000000FF00008000
            00FF0000800000800000000000FF0000007F7F7F000000008080000000BFBFBF
            00000000FF0000000000FF0000800000FF0000800000800000000000FF000000
            007F7F7F000000008080000000BFBFBF00000000FF0000000000FF0000800000
            FF0000800000800000000000FF000000007F7F7F000000008080000000FFFFFF
            000000FFFFFF0000000000FF0000FF0000FF0000FF000080000000FFFFFF0000
            007F7F7F000000008080000000FFFFFF000000FFFFFF0000000000FF0000FF00
            00FF0000FF000080000000FFFFFF0000007F7F7F000000008080000000FFFFFF
            000000FFFFFF00000000FF0000FF0000FF0000FF00008000000000FFFFFF0000
            007F7F7F000000008080000000FFFFFF000000FFFFFF00000000FF0000FF0000
            FF0000FF00008000000000FFFFFF0000007F7F7F000000008080000000FFFFFF
            0000000000FF000000FFFFFF0000FF0000FF0000800000FF0000000000FF0000
            00BFBFBF000000008080000000FFFFFF0000000000FF000000FFFFFF0000FF00
            00FF0000800000FF0000000000FF000000BFBFBF000000008080000000FFFFFF
            00000000FF00000000FFFFFF00FF0000FF0000800000FF0000000000FF000000
            00BFBFBF000000008080000000FFFFFF00000000FF00000000FFFFFF00FF0000
            FF0000800000FF0000000000FF00000000BFBFBF000000008080000000FFFFFF
            7F7F7FFFFFFF000000000000FFFFFFFFFFFF0000FF000000000000FFFFFF7F7F
            7FBFBFBF000000008080000000FFFFFF7F7F7FFFFFFF000000000000FFFFFFFF
            FFFF0000FF000000000000FFFFFF7F7F7FBFBFBF000000008080000000FFFFFF
            7F7F7FFFFFFF000000000000FFFFFFFFFFFF00FF00000000000000FFFFFF7F7F
            7FBFBFBF000000008080000000FFFFFF7F7F7FFFFFFF000000000000FFFFFFFF
            FFFF00FF00000000000000FFFFFF7F7F7FBFBFBF000000008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF000000BFBF
            BF000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF000000BFBFBF000000008080008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF000000BFBF
            BF000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF000000BFBFBF000000008080008080008080000000
            FFFFFFBFBFBF000000FFFFFF0000FFFFFFFF0000FFFFFFFF000000BFBFBFBFBF
            BF000000008080008080008080000000FFFFFFBFBFBF000000FFFFFF0000FFFF
            FFFF0000FFFFFFFF000000BFBFBFBFBFBF000000008080008080008080000000
            FFFFFFBFBFBF000000FFFFFF00FF00FFFFFF00FF00FFFFFF000000BFBFBFBFBF
            BF000000008080008080008080000000FFFFFFBFBFBF000000FFFFFF00FF00FF
            FFFF00FF00FFFFFF000000BFBFBFBFBFBF000000008080008080008080008080
            000000FFFFFFBFBFBF7F7F7F0000000000000000007F7F7FBFBFBFBFBFBF0000
            00008080008080008080008080008080000000FFFFFFBFBFBF7F7F7F00000000
            00000000007F7F7FBFBFBFBFBFBF000000008080008080008080008080008080
            000000FFFFFFBFBFBF7F7F7F0000000000000000007F7F7FBFBFBFBFBFBF0000
            00008080008080008080008080008080000000FFFFFFBFBFBF7F7F7F00000000
            00000000007F7F7FBFBFBFBFBFBF000000008080008080008080008080008080
            008080000000000000FFFFFFFFFFFFFFFFFFBFBFBFBFBFBF0000000000000080
            80008080008080008080008080008080008080000000000000FFFFFFFFFFFFFF
            FFFFBFBFBFBFBFBF000000000000008080008080008080008080008080008080
            008080000000000000FFFFFFFFFFFFFFFFFFBFBFBFBFBFBF0000000000000080
            80008080008080008080008080008080008080000000000000FFFFFFFFFFFFFF
            FFFFBFBFBFBFBFBF000000000000008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080}
          NumGlyphs = 4
        end
        object lCarriage1Off: TLabel
          Left = 25
          Top = 416
          Width = 124
          Height = 20
          AutoSize = False
          Caption = ' - '#1050#1040#1056#1045#1058#1050#1040' '#1042' '#1048#1057#1061#1054#1044#1053#1054#1052
          Layout = tlCenter
        end
        object lLoad15: TLabel
          Left = 173
          Top = 128
          Width = 23
          Height = 12
          Alignment = taRightJustify
          AutoSize = False
          Caption = '15'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object lLoad10: TLabel
          Left = 172
          Top = 158
          Width = 23
          Height = 12
          Alignment = taRightJustify
          AutoSize = False
          Caption = '10'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object lLoad5: TLabel
          Left = 173
          Top = 194
          Width = 23
          Height = 12
          Alignment = taRightJustify
          AutoSize = False
          Caption = '5'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object lLoad0: TLabel
          Left = 172
          Top = 227
          Width = 23
          Height = 12
          Alignment = taRightJustify
          AutoSize = False
          Caption = '0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object sbCarr1Fm: TSpeedButton
          Left = 2
          Top = 387
          Width = 19
          Height = 20
          AllowAllUp = True
          GroupIndex = 1
          Glyph.Data = {
            360C0000424D360C000000000000360000002800000040000000100000000100
            180000000000000C000000000000000000000000000000000000008080008080
            0080800080800080800080800080800080800080800080800080800080800080
            8000808000808000808000808000808000808000808000808000808000808000
            8080008080008080008080008080008080008080008080008080008080008080
            0080800080800080800080800080800080800080800080800080800080800080
            8000808000808000808000808000808000808000808000808000808000808000
            8080008080008080008080008080008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080008080008080
            008080000000000000BFBFBFBFBFBF7F7F7F7F7F7F7F7F7F0000000000000080
            80008080008080008080008080008080008080000000000000BFBFBFBFBFBF7F
            7F7F7F7F7F7F7F7F000000000000008080008080008080008080008080008080
            008080000000000000BFBFBFBFBFBF7F7F7F7F7F7F7F7F7F0000000000000080
            80008080008080008080008080008080008080000000000000BFBFBFBFBFBF7F
            7F7F7F7F7F7F7F7F000000000000008080008080008080008080008080008080
            000000BFBFBFBFBFBF7F7F7F0000000000000000007F7F7F7F7F7F7F7F7F0000
            00008080008080008080008080008080000000BFBFBFBFBFBF7F7F7F00000000
            00000000007F7F7F7F7F7F7F7F7F000000008080008080008080008080008080
            000000BFBFBFBFBFBF7F7F7F0000000000000000007F7F7F7F7F7F7F7F7F0000
            00008080008080008080008080008080000000BFBFBFBFBFBF7F7F7F00000000
            00000000007F7F7F7F7F7F7F7F7F000000008080008080008080008080000000
            BFBFBFBFBFBF000000FFFFFF0000FFFFFFFF0000FFFFFFFF0000007F7F7F7F7F
            7F000000008080008080008080000000BFBFBFBFBFBF000000FFFFFF0000FFFF
            FFFF0000FFFFFFFF0000007F7F7F7F7F7F000000008080008080008080000000
            BFBFBFBFBFBF000000FFFFFF00FF00FFFFFF00FF00FFFFFF0000007F7F7F7F7F
            7F000000008080008080008080000000BFBFBFBFBFBF000000FFFFFF00FF00FF
            FFFF00FF00FFFFFF0000007F7F7F7F7F7F000000008080008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF0000007F7F
            7F000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF0000007F7F7F000000008080008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF0000007F7F
            7F000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF0000007F7F7F000000008080008080000000BFBFBF
            7F7F7FFFFFFF0000000000000000FF000080000080000000000000FFFFFF7F7F
            7F7F7F7F000000008080000000BFBFBF7F7F7FFFFFFF0000000000000000FF00
            0080000080000000000000FFFFFF7F7F7F7F7F7F000000008080000000BFBFBF
            7F7F7FFFFFFF00000000000000FF00008000008000000000000000FFFFFF7F7F
            7F7F7F7F000000008080000000BFBFBF7F7F7FFFFFFF00000000000000FF0000
            8000008000000000000000FFFFFF7F7F7F7F7F7F000000008080000000BFBFBF
            0000000000FF0000000000FF0000800000FF0000800000800000000000FF0000
            007F7F7F000000008080000000BFBFBF0000000000FF0000000000FF00008000
            00FF0000800000800000000000FF0000007F7F7F000000008080000000BFBFBF
            00000000FF0000000000FF0000800000FF0000800000800000000000FF000000
            007F7F7F000000008080000000BFBFBF00000000FF0000000000FF0000800000
            FF0000800000800000000000FF000000007F7F7F000000008080000000FFFFFF
            000000FFFFFF0000000000FF0000FF0000FF0000FF000080000000FFFFFF0000
            007F7F7F000000008080000000FFFFFF000000FFFFFF0000000000FF0000FF00
            00FF0000FF000080000000FFFFFF0000007F7F7F000000008080000000FFFFFF
            000000FFFFFF00000000FF0000FF0000FF0000FF00008000000000FFFFFF0000
            007F7F7F000000008080000000FFFFFF000000FFFFFF00000000FF0000FF0000
            FF0000FF00008000000000FFFFFF0000007F7F7F000000008080000000FFFFFF
            0000000000FF000000FFFFFF0000FF0000FF0000800000FF0000000000FF0000
            00BFBFBF000000008080000000FFFFFF0000000000FF000000FFFFFF0000FF00
            00FF0000800000FF0000000000FF000000BFBFBF000000008080000000FFFFFF
            00000000FF00000000FFFFFF00FF0000FF0000800000FF0000000000FF000000
            00BFBFBF000000008080000000FFFFFF00000000FF00000000FFFFFF00FF0000
            FF0000800000FF0000000000FF00000000BFBFBF000000008080000000FFFFFF
            7F7F7FFFFFFF000000000000FFFFFFFFFFFF0000FF000000000000FFFFFF7F7F
            7FBFBFBF000000008080000000FFFFFF7F7F7FFFFFFF000000000000FFFFFFFF
            FFFF0000FF000000000000FFFFFF7F7F7FBFBFBF000000008080000000FFFFFF
            7F7F7FFFFFFF000000000000FFFFFFFFFFFF00FF00000000000000FFFFFF7F7F
            7FBFBFBF000000008080000000FFFFFF7F7F7FFFFFFF000000000000FFFFFFFF
            FFFF00FF00000000000000FFFFFF7F7F7FBFBFBF000000008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF000000BFBF
            BF000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF000000BFBFBF000000008080008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF000000BFBF
            BF000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF000000BFBFBF000000008080008080008080000000
            FFFFFFBFBFBF000000FFFFFF0000FFFFFFFF0000FFFFFFFF000000BFBFBFBFBF
            BF000000008080008080008080000000FFFFFFBFBFBF000000FFFFFF0000FFFF
            FFFF0000FFFFFFFF000000BFBFBFBFBFBF000000008080008080008080000000
            FFFFFFBFBFBF000000FFFFFF00FF00FFFFFF00FF00FFFFFF000000BFBFBFBFBF
            BF000000008080008080008080000000FFFFFFBFBFBF000000FFFFFF00FF00FF
            FFFF00FF00FFFFFF000000BFBFBFBFBFBF000000008080008080008080008080
            000000FFFFFFBFBFBF7F7F7F0000000000000000007F7F7FBFBFBFBFBFBF0000
            00008080008080008080008080008080000000FFFFFFBFBFBF7F7F7F00000000
            00000000007F7F7FBFBFBFBFBFBF000000008080008080008080008080008080
            000000FFFFFFBFBFBF7F7F7F0000000000000000007F7F7FBFBFBFBFBFBF0000
            00008080008080008080008080008080000000FFFFFFBFBFBF7F7F7F00000000
            00000000007F7F7FBFBFBFBFBFBF000000008080008080008080008080008080
            008080000000000000FFFFFFFFFFFFFFFFFFBFBFBFBFBFBF0000000000000080
            80008080008080008080008080008080008080000000000000FFFFFFFFFFFFFF
            FFFFBFBFBFBFBFBF000000000000008080008080008080008080008080008080
            008080000000000000FFFFFFFFFFFFFFFFFFBFBFBFBFBFBF0000000000000080
            80008080008080008080008080008080008080000000000000FFFFFFFFFFFFFF
            FFFFBFBFBFBFBFBF000000000000008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080}
          NumGlyphs = 4
        end
        object sbCarr1To: TSpeedButton
          Left = 190
          Top = 387
          Width = 19
          Height = 20
          AllowAllUp = True
          GroupIndex = 1
          Glyph.Data = {
            360C0000424D360C000000000000360000002800000040000000100000000100
            180000000000000C000000000000000000000000000000000000008080008080
            0080800080800080800080800080800080800080800080800080800080800080
            8000808000808000808000808000808000808000808000808000808000808000
            8080008080008080008080008080008080008080008080008080008080008080
            0080800080800080800080800080800080800080800080800080800080800080
            8000808000808000808000808000808000808000808000808000808000808000
            8080008080008080008080008080008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080008080008080
            008080000000000000BFBFBFBFBFBF7F7F7F7F7F7F7F7F7F0000000000000080
            80008080008080008080008080008080008080000000000000BFBFBFBFBFBF7F
            7F7F7F7F7F7F7F7F000000000000008080008080008080008080008080008080
            008080000000000000BFBFBFBFBFBF7F7F7F7F7F7F7F7F7F0000000000000080
            80008080008080008080008080008080008080000000000000BFBFBFBFBFBF7F
            7F7F7F7F7F7F7F7F000000000000008080008080008080008080008080008080
            000000BFBFBFBFBFBF7F7F7F0000000000000000007F7F7F7F7F7F7F7F7F0000
            00008080008080008080008080008080000000BFBFBFBFBFBF7F7F7F00000000
            00000000007F7F7F7F7F7F7F7F7F000000008080008080008080008080008080
            000000BFBFBFBFBFBF7F7F7F0000000000000000007F7F7F7F7F7F7F7F7F0000
            00008080008080008080008080008080000000BFBFBFBFBFBF7F7F7F00000000
            00000000007F7F7F7F7F7F7F7F7F000000008080008080008080008080000000
            BFBFBFBFBFBF000000FFFFFF0000FFFFFFFF0000FFFFFFFF0000007F7F7F7F7F
            7F000000008080008080008080000000BFBFBFBFBFBF000000FFFFFF0000FFFF
            FFFF0000FFFFFFFF0000007F7F7F7F7F7F000000008080008080008080000000
            BFBFBFBFBFBF000000FFFFFF00FF00FFFFFF00FF00FFFFFF0000007F7F7F7F7F
            7F000000008080008080008080000000BFBFBFBFBFBF000000FFFFFF00FF00FF
            FFFF00FF00FFFFFF0000007F7F7F7F7F7F000000008080008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF0000007F7F
            7F000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF0000007F7F7F000000008080008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF0000007F7F
            7F000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF0000007F7F7F000000008080008080000000BFBFBF
            7F7F7FFFFFFF0000000000000000FF000080000080000000000000FFFFFF7F7F
            7F7F7F7F000000008080000000BFBFBF7F7F7FFFFFFF0000000000000000FF00
            0080000080000000000000FFFFFF7F7F7F7F7F7F000000008080000000BFBFBF
            7F7F7FFFFFFF00000000000000FF00008000008000000000000000FFFFFF7F7F
            7F7F7F7F000000008080000000BFBFBF7F7F7FFFFFFF00000000000000FF0000
            8000008000000000000000FFFFFF7F7F7F7F7F7F000000008080000000BFBFBF
            0000000000FF0000000000FF0000800000FF0000800000800000000000FF0000
            007F7F7F000000008080000000BFBFBF0000000000FF0000000000FF00008000
            00FF0000800000800000000000FF0000007F7F7F000000008080000000BFBFBF
            00000000FF0000000000FF0000800000FF0000800000800000000000FF000000
            007F7F7F000000008080000000BFBFBF00000000FF0000000000FF0000800000
            FF0000800000800000000000FF000000007F7F7F000000008080000000FFFFFF
            000000FFFFFF0000000000FF0000FF0000FF0000FF000080000000FFFFFF0000
            007F7F7F000000008080000000FFFFFF000000FFFFFF0000000000FF0000FF00
            00FF0000FF000080000000FFFFFF0000007F7F7F000000008080000000FFFFFF
            000000FFFFFF00000000FF0000FF0000FF0000FF00008000000000FFFFFF0000
            007F7F7F000000008080000000FFFFFF000000FFFFFF00000000FF0000FF0000
            FF0000FF00008000000000FFFFFF0000007F7F7F000000008080000000FFFFFF
            0000000000FF000000FFFFFF0000FF0000FF0000800000FF0000000000FF0000
            00BFBFBF000000008080000000FFFFFF0000000000FF000000FFFFFF0000FF00
            00FF0000800000FF0000000000FF000000BFBFBF000000008080000000FFFFFF
            00000000FF00000000FFFFFF00FF0000FF0000800000FF0000000000FF000000
            00BFBFBF000000008080000000FFFFFF00000000FF00000000FFFFFF00FF0000
            FF0000800000FF0000000000FF00000000BFBFBF000000008080000000FFFFFF
            7F7F7FFFFFFF000000000000FFFFFFFFFFFF0000FF000000000000FFFFFF7F7F
            7FBFBFBF000000008080000000FFFFFF7F7F7FFFFFFF000000000000FFFFFFFF
            FFFF0000FF000000000000FFFFFF7F7F7FBFBFBF000000008080000000FFFFFF
            7F7F7FFFFFFF000000000000FFFFFFFFFFFF00FF00000000000000FFFFFF7F7F
            7FBFBFBF000000008080000000FFFFFF7F7F7FFFFFFF000000000000FFFFFFFF
            FFFF00FF00000000000000FFFFFF7F7F7FBFBFBF000000008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF000000BFBF
            BF000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF000000BFBFBF000000008080008080008080000000
            BFBFBF000000FFFFFF000000000000000000000000000000FFFFFF000000BFBF
            BF000000008080008080008080000000BFBFBF000000FFFFFF00000000000000
            0000000000000000FFFFFF000000BFBFBF000000008080008080008080000000
            FFFFFFBFBFBF000000FFFFFF0000FFFFFFFF0000FFFFFFFF000000BFBFBFBFBF
            BF000000008080008080008080000000FFFFFFBFBFBF000000FFFFFF0000FFFF
            FFFF0000FFFFFFFF000000BFBFBFBFBFBF000000008080008080008080000000
            FFFFFFBFBFBF000000FFFFFF00FF00FFFFFF00FF00FFFFFF000000BFBFBFBFBF
            BF000000008080008080008080000000FFFFFFBFBFBF000000FFFFFF00FF00FF
            FFFF00FF00FFFFFF000000BFBFBFBFBFBF000000008080008080008080008080
            000000FFFFFFBFBFBF7F7F7F0000000000000000007F7F7FBFBFBFBFBFBF0000
            00008080008080008080008080008080000000FFFFFFBFBFBF7F7F7F00000000
            00000000007F7F7FBFBFBFBFBFBF000000008080008080008080008080008080
            000000FFFFFFBFBFBF7F7F7F0000000000000000007F7F7FBFBFBFBFBFBF0000
            00008080008080008080008080008080000000FFFFFFBFBFBF7F7F7F00000000
            00000000007F7F7FBFBFBFBFBFBF000000008080008080008080008080008080
            008080000000000000FFFFFFFFFFFFFFFFFFBFBFBFBFBFBF0000000000000080
            80008080008080008080008080008080008080000000000000FFFFFFFFFFFFFF
            FFFFBFBFBFBFBFBF000000000000008080008080008080008080008080008080
            008080000000000000FFFFFFFFFFFFFFFFFFBFBFBFBFBFBF0000000000000080
            80008080008080008080008080008080008080000000000000FFFFFFFFFFFFFF
            FFFFBFBFBFBFBFBF000000000000008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080008080008080
            0080800080800080800000000000000000000000000000000080800080800080
            8000808000808000808000808000808000808000808000808000000000000000
            0000000000000000008080008080008080008080008080008080}
          NumGlyphs = 4
        end
        object lLoad20: TLabel
          Left = 174
          Top = 93
          Width = 23
          Height = 12
          Alignment = taRightJustify
          AutoSize = False
          Caption = '20'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object lLoad25: TLabel
          Left = 173
          Top = 58
          Width = 23
          Height = 12
          Alignment = taRightJustify
          AutoSize = False
          Caption = '25'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object pCarr1Ttl: TPanel
          Left = 11
          Top = 326
          Width = 198
          Height = 19
          BevelInner = bvLowered
          BorderWidth = 1
          BorderStyle = bsSingle
          Caption = #1059#1055#1056#1040#1042#1051#1045#1053#1048#1045' '#1055#1045#1056#1045#1052#1045#1065#1045#1053#1048#1045#1052' '#1050#1040#1056#1045#1058#1050#1048
          Color = clBackground
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindow
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentBackground = False
          ParentFont = False
          TabOrder = 0
        end
        object btnCarriage1From: TButton
          Left = -3
          Top = 351
          Width = 84
          Height = 30
          Caption = #1054#1058' '#1041#1040#1056#1040#1041#1040#1053#1040', F3'
          TabOrder = 1
          OnClick = OnCarriage1From
        end
        object btnCarriage1To: TButton
          Left = 140
          Top = 353
          Width = 76
          Height = 30
          Caption = #1050' '#1041#1040#1056#1040#1041#1040#1053#1059', F5'
          TabOrder = 2
          OnClick = OnCarriage1To
        end
        object btnCarriage1Stop: TButton
          Left = 87
          Top = 351
          Width = 47
          Height = 30
          Caption = #1057#1058#1054#1055', F4'
          TabOrder = 3
          OnClick = OnCarriage1Stop
        end
        object pCarr1Load: TPanel
          Left = 11
          Top = 15
          Width = 198
          Height = 20
          BevelInner = bvLowered
          BorderWidth = 1
          BorderStyle = bsSingle
          Caption = #1053#1040#1043#1056#1059#1047#1050#1040' '#1053#1040' '#1064#1048#1053#1059', '#1082#1053
          Color = clBackground
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindow
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentBackground = False
          ParentFont = False
          TabOrder = 4
        end
        object leCurrentLoad1: TLabeledEdit
          Left = 38
          Top = 72
          Width = 48
          Height = 23
          AutoSize = False
          EditLabel.Width = 59
          EditLabel.Height = 14
          EditLabel.Caption = #1058#1045#1050#1059#1065#1040#1071':'
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          ReadOnly = True
          TabOrder = 5
          Text = '10'
        end
        object leSetLoad1: TLabeledEdit
          Left = 38
          Top = 113
          Width = 48
          Height = 22
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 57
          EditLabel.Height = 14
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = #1047#1040#1044#1040#1053#1048#1045':'
          EditLabel.ParentBiDiMode = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clOlive
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentBiDiMode = False
          ParentFont = False
          TabOrder = 6
          Text = '20'
          OnKeyPress = leSetLoad1KeyPress
        end
        object tbCurrentLoad1: TTrackBar
          Left = 129
          Top = 53
          Width = 38
          Height = 195
          Ctl3D = True
          DragMode = dmAutomatic
          Max = 25
          Orientation = trVertical
          ParentCtl3D = False
          Frequency = 5
          Position = 25
          PositionToolTip = ptRight
          SelEnd = 60
          SelStart = 60
          TabOrder = 7
          ThumbLength = 30
          TickMarks = tmBoth
        end
        object leCurrentT1: TLabeledEdit
          Left = 135
          Top = 258
          Width = 38
          Height = 23
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 99
          EditLabel.Height = 18
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = 'T '#1074#1086#1079#1076#1091#1093#1072', C: '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'Tahoma'
          EditLabel.Font.Style = []
          EditLabel.ParentBiDiMode = False
          EditLabel.ParentFont = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          LabelPosition = lpLeft
          ParentBiDiMode = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 8
          Text = '10'
        end
        object leCurrentR1: TLabeledEdit
          Left = 135
          Top = 288
          Width = 38
          Height = 23
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 87
          EditLabel.Height = 18
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = #1056#1072#1076#1080#1091#1089', '#1084#1084': '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'Tahoma'
          EditLabel.Font.Style = []
          EditLabel.ParentBiDiMode = False
          EditLabel.ParentFont = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          LabelPosition = lpLeft
          ParentBiDiMode = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 9
          Text = '10'
        end
      end
    end
    object tsTestProgramSetting: TTabSheet
      Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1072' '#1080#1089#1087#1099#1090#1072#1085#1080#1081
      ImageIndex = 2
      object pcTestProg: TPageControl
        Left = 0
        Top = 0
        Width = 808
        Height = 599
        ActivePage = tsTimeProg
        Align = alClient
        TabOrder = 0
        object tsTimeProg: TTabSheet
          Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1072' '#1080#1089#1087#1099#1090#1072#1085#1080#1081' '#1087#1086' '#1074#1088#1077#1084#1077#1085#1080
          object lTProgTblNme: TLabel
            Left = 90
            Top = 66
            Width = 147
            Height = 14
            Caption = #1055#1056#1054#1043#1056#1040#1052#1052#1040' '#1048#1057#1055#1067#1058#1040#1053#1048#1049
          end
          object lTPollingTblNme1: TLabel
            Left = 336
            Top = 67
            Width = 49
            Height = 14
            Caption = #1054#1055#1056#1054#1057#1067
          end
          object leTProgName: TLabeledEdit
            Left = 134
            Top = 20
            Width = 166
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 84
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1048#1084#1103' '#1087#1088#1086#1075#1088#1072#1084#1084#1099': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 0
            Text = #1071'-'
            OnKeyDown = OnLEKeyDown
          end
          object leTTyrePressure: TLabeledEdit
            Left = 134
            Top = 43
            Width = 29
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 121
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1044#1072#1074#1083#1077#1085#1080#1077' '#1074' '#1096#1080#1085#1077', '#1082#1055#1072': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 1
            Text = '0'
            OnKeyDown = OnLEKeyDown
            OnKeyPress = OnSGKeyPress
          end
          object leTTotalStepsQty: TLabeledEdit
            Left = 272
            Top = 43
            Width = 28
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 101
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1096#1072#1075#1086#1074': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 4
            Text = '0'
          end
          object leTotalTestTime: TLabeledEdit
            Left = 452
            Top = 20
            Width = 50
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 133
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1054#1073#1097#1077#1077' '#1074#1088#1077#1084#1103' '#1080#1089#1087#1099#1090#1072#1085#1080#1081': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 5
            Text = '00:00:00'
          end
          object leTPollingTotalQty: TLabeledEdit
            Left = 452
            Top = 43
            Width = 29
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 111
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1086#1087#1088#1086#1089#1086#1074': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 6
            Text = '0'
          end
          object sgTProgram: TStringGrid
            Left = 30
            Top = 83
            Width = 262
            Height = 336
            RowCount = 101
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goTabs]
            ParentFont = False
            ScrollBars = ssVertical
            TabOrder = 2
            OnEnter = OnSGTEnter
            OnExit = OnStringGridExit
            OnKeyDown = OnSGKeyDown
            OnKeyPress = OnSGKeyPress
            ColWidths = (
              64
              64
              64
              64
              64)
            RowHeights = (
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24)
          end
          object sgTPolling: TStringGrid
            Left = 324
            Top = 83
            Width = 169
            Height = 337
            ColCount = 3
            RowCount = 251
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goTabs]
            ParentFont = False
            ScrollBars = ssVertical
            TabOrder = 3
            OnEnter = OnSGTEnter
            OnExit = OnStringGridExit
            OnKeyDown = OnSGKeyDown
            OnKeyPress = OnSGKeyPress
            ColWidths = (
              64
              64
              64)
            RowHeights = (
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24)
          end
          object btnSaveTProgToFile: TButton
            Left = 504
            Top = 197
            Width = 94
            Height = 43
            Action = acTProgFileSaveAs
            TabOrder = 7
            WordWrap = True
          end
          object btnOpenTProgFmFile: TButton
            Left = 504
            Top = 251
            Width = 94
            Height = 42
            Action = acTProgFileOpen
            TabOrder = 8
            WordWrap = True
          end
          object btnLoadTProgToPosA: TButton
            Left = 504
            Top = 307
            Width = 94
            Height = 43
            Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1087#1088#1086#1075#1088#1072#1084#1084#1091' '#1074' '#1087#1086#1079'. '#1040
            Enabled = False
            TabOrder = 9
            WordWrap = True
            OnClick = OnLoadTProgToPosA
          end
          object btnCheckTProg: TButton
            Left = 504
            Top = 143
            Width = 94
            Height = 43
            Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100' '#1087#1088#1086#1075#1088#1072#1084#1084#1091
            Enabled = False
            TabOrder = 10
            WordWrap = True
            OnClick = OnTProgCheck
          end
          object btnNewTProg: TButton
            Left = 504
            Top = 83
            Width = 94
            Height = 42
            Caption = #1057#1073#1088#1086#1089#1080#1090#1100' '#1087#1088#1086#1075#1088#1072#1084#1084#1091
            TabOrder = 11
            WordWrap = True
            OnClick = OnNewTProg
          end
          object pTProgTtl: TPanel
            Left = 0
            Top = 0
            Width = 600
            Height = 20
            BevelInner = bvLowered
            BorderWidth = 1
            BorderStyle = bsSingle
            Caption = #1057#1054#1047#1044#1040#1053#1048#1045' '#1048' '#1056#1045#1044#1040#1050#1058#1048#1056#1054#1042#1040#1053#1048#1045' '#1055#1056#1054#1043#1056#1040#1052#1052#1067' '#1048#1057#1055#1067#1058#1040#1053#1048#1049' '#1055#1054' '#1042#1056#1045#1052#1045#1053#1048
            Color = clBackground
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindow
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentBackground = False
            ParentFont = False
            TabOrder = 12
          end
        end
        object tsSProg: TTabSheet
          Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1072' '#1080#1089#1087#1099#1090#1072#1085#1080#1081' '#1087#1086' '#1087#1091#1090#1080
          ImageIndex = 1
          object lSPollingTblNme1: TLabel
            Left = 336
            Top = 67
            Width = 49
            Height = 14
            Caption = #1054#1055#1056#1054#1057#1067
          end
          object lSProgTblNme: TLabel
            Left = 90
            Top = 66
            Width = 147
            Height = 14
            Caption = #1055#1056#1054#1043#1056#1040#1052#1052#1040' '#1048#1057#1055#1067#1058#1040#1053#1048#1049
          end
          object pSProgTtl: TPanel
            Left = 0
            Top = 0
            Width = 600
            Height = 20
            BevelInner = bvLowered
            BorderWidth = 1
            BorderStyle = bsSingle
            Caption = #1057#1054#1047#1044#1040#1053#1048#1045' '#1048' '#1056#1045#1044#1040#1050#1058#1048#1056#1054#1042#1040#1053#1048#1045' '#1055#1056#1054#1043#1056#1040#1052#1052#1067' '#1048#1057#1055#1067#1058#1040#1053#1048#1049' '#1055#1054' '#1055#1059#1058#1048
            Color = clBackground
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindow
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentBackground = False
            ParentFont = False
            TabOrder = 0
          end
          object leSProgName: TLabeledEdit
            Left = 132
            Top = 20
            Width = 149
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 84
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1048#1084#1103' '#1087#1088#1086#1075#1088#1072#1084#1084#1099': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 1
            Text = #1071'-'
            OnKeyDown = OnLEKeyDown
          end
          object leSTyrePressure: TLabeledEdit
            Left = 132
            Top = 43
            Width = 29
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 121
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1044#1072#1074#1083#1077#1085#1080#1077' '#1074' '#1096#1080#1085#1077', '#1082#1055#1072': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 2
            Text = '0'
            OnKeyDown = OnLEKeyDown
            OnKeyPress = OnSGKeyPress
          end
          object leSTotalStepsQty: TLabeledEdit
            Left = 271
            Top = 43
            Width = 28
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 101
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1096#1072#1075#1086#1074': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 3
            Text = '0'
          end
          object leTotalTestS: TLabeledEdit
            Left = 453
            Top = 20
            Width = 41
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 151
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1054#1073#1097#1080#1081' '#1087#1091#1090#1100' '#1087#1088#1080'  '#1080#1089#1087#1099#1090#1072#1085#1080#1080': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 4
            Text = '0'
          end
          object leSPollingTotalQty: TLabeledEdit
            Left = 453
            Top = 43
            Width = 29
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 111
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1086#1087#1088#1086#1089#1086#1074': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 5
            Text = '0'
          end
          object sgSProgram: TStringGrid
            Left = 30
            Top = 83
            Width = 262
            Height = 336
            ColCount = 4
            RowCount = 101
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goTabs]
            ParentFont = False
            ScrollBars = ssVertical
            TabOrder = 6
            OnEnter = OnSGSEnter
            OnExit = OnStringGridExit
            OnKeyDown = OnSGKeyDown
            OnKeyPress = OnSGKeyPress
            ColWidths = (
              64
              64
              64
              64)
            RowHeights = (
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24)
          end
          object sgSPolling: TStringGrid
            Left = 324
            Top = 83
            Width = 169
            Height = 337
            ColCount = 2
            RowCount = 251
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goTabs]
            ParentFont = False
            ScrollBars = ssVertical
            TabOrder = 7
            OnEnter = OnSGSEnter
            OnExit = OnStringGridExit
            OnKeyDown = OnSGKeyDown
            OnKeyPress = OnSGKeyPress
            ColWidths = (
              64
              64)
            RowHeights = (
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24)
          end
          object btnNewSProg: TButton
            Left = 504
            Top = 83
            Width = 94
            Height = 42
            Caption = #1057#1073#1088#1086#1089#1080#1090#1100' '#1087#1088#1086#1075#1088#1072#1084#1084#1091
            TabOrder = 8
            WordWrap = True
            OnClick = OnNewSProg
          end
          object btnCheckSProg: TButton
            Left = 504
            Top = 143
            Width = 94
            Height = 43
            Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100' '#1087#1088#1086#1075#1088#1072#1084#1084#1091
            Enabled = False
            TabOrder = 9
            WordWrap = True
            OnClick = OnSProgCheck
          end
          object btnSaveSProgToFile: TButton
            Left = 504
            Top = 202
            Width = 94
            Height = 43
            Action = acSProgFileSaveAs
            TabOrder = 10
            WordWrap = True
          end
          object btnOpenSProgFmFile: TButton
            Left = 504
            Top = 251
            Width = 94
            Height = 42
            Action = acSProgFileOpen
            TabOrder = 11
            WordWrap = True
          end
          object btnLoadSProgToPosA: TButton
            Left = 506
            Top = 312
            Width = 94
            Height = 43
            Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1087#1088#1086#1075#1088#1072#1084#1084#1091' '#1074' '#1087#1086#1079'. '#1040
            Enabled = False
            TabOrder = 12
            WordWrap = True
            OnClick = OnLoadSProgToPosA
          end
        end
      end
    end
    object tsProtocol: TTabSheet
      Caption = #1055#1088#1086#1090#1086#1082#1086#1083
      ImageIndex = 1
      object pcProtTitle: TPageControl
        Left = 0
        Top = 0
        Width = 808
        Height = 599
        ActivePage = tsNewProtocol
        Align = alClient
        TabOrder = 0
        object tsProtocolA: TTabSheet
          Caption = #1058#1077#1082#1091#1097#1080#1081' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1087#1086#1079'. '#1040
          object pCurrentProtATtl: TPanel
            Left = 2
            Top = 0
            Width = 596
            Height = 20
            BorderStyle = bsSingle
            Caption = #1055#1056#1054#1058#1054#1050#1054#1051' '#1048#1057#1055#1067#1058#1040#1053#1048#1049'  '#1053#1040' '#1057#1058#1045#1053#1044#1045' '#8470'13 ('#1055#1054#1047'. '#1040')'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
          end
          object leTyreModelA: TLabeledEdit
            Left = 98
            Top = 20
            Width = 61
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 46
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1052#1086#1076#1077#1083#1100': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 1
          end
          object leTyreSyzeA: TLabeledEdit
            Left = 224
            Top = 20
            Width = 62
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 42
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1056#1072#1079#1084#1077#1088': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 2
            Text = '185/70R14'
          end
          object leManDateA: TLabeledEdit
            Left = 401
            Top = 20
            Width = 72
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 106
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1044#1072#1090#1072' '#1080#1079#1075#1086#1090#1086#1074#1083#1077#1085#1080#1103': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 3
          end
          object leSerialNoA: TLabeledEdit
            Left = 571
            Top = 20
            Width = 39
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 87
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1055#1086#1088#1103#1076#1082#1086#1074#1099#1081' '#8470': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 4
            Text = '200'
          end
          object leManufacturerA: TLabeledEdit
            Left = 98
            Top = 38
            Width = 61
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 78
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1048#1079#1075#1086#1090#1086#1074#1080#1090#1077#1083#1100': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 5
            Text = 'Nokia'
          end
          object leTestCustomerA: TLabeledEdit
            Left = 224
            Top = 38
            Width = 249
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 54
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1047#1072#1082#1072#1079#1095#1080#1082': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 6
            Text = #1071#1064#1047
          end
          object leFormNoA: TLabeledEdit
            Left = 571
            Top = 56
            Width = 39
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 55
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1060#1086#1088#1084#1072' '#8470': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 7
            Text = '1'
          end
          object leTestProcA: TLabeledEdit
            Left = 224
            Top = 56
            Width = 62
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 58
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1052#1077#1090#1086#1076#1080#1082#1072': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 8
            Text = '32-2006'#1052
          end
          object leDrumD_A: TLabeledEdit
            Left = 412
            Top = 56
            Width = 61
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 121
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1044#1080#1072#1084#1077#1090#1088' '#1073#1072#1088#1072#1073#1072#1085#1072', '#1084#1084': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 9
            Text = '1700'
          end
          object lePerfSpecNoA: TLabeledEdit
            Left = 98
            Top = 56
            Width = 61
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 90
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1058#1077#1093'. '#1079#1072#1076#1072#1085#1080#1077' '#8470': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 10
            Text = '1'
          end
          object leOrderNoA: TLabeledEdit
            Left = 571
            Top = 38
            Width = 39
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 52
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1047#1072#1082#1072#1079' '#8470': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 11
            Text = '1'
          end
          object pTyreParamATtl: TPanel
            Left = 2
            Top = 78
            Width = 596
            Height = 19
            BorderStyle = bsSingle
            Caption = #1061#1040#1056#1040#1050#1058#1045#1056#1048#1057#1058#1048#1050#1040' '#1064#1048#1053#1067':'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsUnderline]
            ParentFont = False
            TabOrder = 12
          end
          object leLoadIndA: TLabeledEdit
            Left = 139
            Top = 100
            Width = 43
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 93
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1048#1085#1076#1077#1082#1089' '#1085#1072#1075#1088#1091#1079#1082#1080': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 13
            Text = '1'
          end
          object leMaxLoadA: TLabeledEdit
            Left = 350
            Top = 101
            Width = 43
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 149
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1072#1103' '#1085#1072#1075#1088#1091#1079#1082#1072', '#1082#1053': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 14
            Text = '50'
          end
          object leSpeedIndA: TLabeledEdit
            Left = 139
            Top = 119
            Width = 43
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 110
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1050#1072#1090#1077#1075#1086#1088#1080#1103' '#1089#1082#1086#1088#1086#1089#1090#1080': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 15
            Text = 'T'
          end
          object leMaxSpeedA: TLabeledEdit
            Left = 350
            Top = 119
            Width = 43
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 158
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1072#1103' '#1089#1082#1086#1088#1086#1089#1090#1100', '#1082#1084'/'#1095': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 16
            Text = '180'
          end
          object leStaticR_A: TLabeledEdit
            Left = 541
            Top = 101
            Width = 47
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 131
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1057#1090#1072#1090#1080#1095#1077#1089#1082#1080#1081' '#1088#1072#1076#1080#1091#1089', '#1084#1084': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 17
            Text = '14'
          end
          object leTyreWideA: TLabeledEdit
            Left = 541
            Top = 119
            Width = 47
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 113
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1064#1080#1088#1080#1085#1072' '#1087#1088#1086#1092#1080#1083#1103', '#1084#1084': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 18
            Text = '70'
          end
          object leOuterD_A: TLabeledEdit
            Left = 139
            Top = 137
            Width = 43
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 106
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1053#1072#1088#1091#1078#1085#1099#1081' '#1076#1080#1072#1084#1077#1090#1088': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 19
            Text = '28'
          end
          object leRimA: TLabeledEdit
            Left = 541
            Top = 137
            Width = 47
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 34
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1054#1073#1086#1076': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 20
            Text = #1089#1090#1072#1083#1100
          end
          object leQMaxPressureA: TLabeledEdit
            Left = 350
            Top = 137
            Width = 43
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 153
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1044#1072#1074#1083#1077#1085#1080#1077' '#1087#1088#1080' Qmax, '#1082#1075#1089'/'#1089#1084'2: '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 21
            Text = '2'
          end
          object pTestResTtlA: TPanel
            Left = 2
            Top = 161
            Width = 596
            Height = 18
            BorderStyle = bsSingle
            Caption = #1056#1045#1047#1059#1051#1068#1058#1040#1058#1067' '#1048#1057#1055#1067#1058#1040#1053#1048#1049':'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsUnderline]
            ParentFont = False
            TabOrder = 22
          end
          object leTestDurationA: TLabeledEdit
            Left = 512
            Top = 182
            Width = 60
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 95
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1042#1088#1077#1084#1103' '#1086#1073#1082#1072#1090#1082#1080', '#1095': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 23
            Text = '10'
          end
          object leTestModeA: TLabeledEdit
            Left = 315
            Top = 182
            Width = 66
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 84
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1056#1077#1078#1080#1084' '#1086#1073#1082#1072#1090#1082#1080': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 24
            Text = #1087#1086' '#1074#1088#1077#1084#1077#1085#1080
          end
          object leTyrePressureA: TLabeledEdit
            Left = 139
            Top = 182
            Width = 43
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 121
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1044#1072#1074#1083#1077#1085#1080#1077' '#1074' '#1096#1080#1085#1077', '#1082#1055#1072': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 25
            Text = '0'
            OnKeyDown = OnLEKeyDown
            OnKeyPress = OnSGKeyPress
          end
          object leStepQtyA: TLabeledEdit
            Left = 315
            Top = 200
            Width = 66
            Height = 20
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 105
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1064#1072#1075#1086#1074' '#1074' '#1087#1088#1086#1075#1088#1072#1084#1084#1077': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 26
            Text = '0'
          end
          object lePollsQtyA: TLabeledEdit
            Left = 512
            Top = 200
            Width = 60
            Height = 20
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 111
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1086#1087#1088#1086#1089#1086#1074': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 27
            Text = '0'
          end
          object sgTestResultA: TStringGrid
            Left = 14
            Top = 234
            Width = 360
            Height = 190
            ColCount = 7
            RowCount = 251
            ScrollBars = ssVertical
            TabOrder = 28
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64)
            RowHeights = (
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24)
          end
          object btnLoadTestResPosA: TButton
            Left = 450
            Top = 234
            Width = 148
            Height = 34
            Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1099' '#1080#1089#1087#1099#1090#1072#1085#1080#1081' '#1080#1079' '#1082#1086#1085#1090#1088#1086#1083#1083#1077#1088#1072
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 29
            WordWrap = True
            OnClick = OnLoadTestResFmPosA
          end
          object btnSaveTestResPosAToFile: TButton
            Left = 450
            Top = 275
            Width = 148
            Height = 33
            Action = acPrintProtPosAToFile
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 30
            WordWrap = True
          end
          object btnPrintTestResPosA: TButton
            Left = 450
            Top = 316
            Width = 148
            Height = 34
            Hint = 'Save As|Saves the active file with a new name'
            Caption = #1056#1072#1089#1087#1077#1095#1072#1090#1072#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1080#1089#1087#1099#1090#1072#1085#1080#1081' '#1080#1079' '#1087#1086#1079'. '#1040
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 31
            WordWrap = True
            OnClick = OnPrintProtocol
          end
          object btnResetResPosA: TButton
            Left = 450
            Top = 356
            Width = 148
            Height = 34
            Caption = #1057#1073#1088#1086#1089' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1086#1074' '#1080#1089#1087#1099#1090#1072#1085#1080#1081' '#1080#1079' '#1087#1086#1079'. '#1040
            TabOrder = 32
            WordWrap = True
            OnClick = btnResetResPosAClick
          end
        end
        object tsNewProtocol: TTabSheet
          Caption = #1053#1086#1074#1099#1081' '#1087#1088#1086#1090#1086#1082#1086#1083
          ImageIndex = 2
          object lblTestMode: TLabel
            Left = 233
            Top = 293
            Width = 84
            Height = 13
            Caption = #1056#1077#1078#1080#1084' '#1086#1073#1082#1072#1090#1082#1080': '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            Visible = False
          end
          object lblManDate: TLabel
            Left = 345
            Top = 58
            Width = 106
            Height = 13
            Caption = #1044#1072#1090#1072' '#1080#1079#1075#1086#1090#1086#1074#1083#1077#1085#1080#1103': '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
          end
          object leProtocolNo: TLabeledEdit
            Left = 75
            Top = 33
            Width = 62
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 72
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1055#1088#1086#1090#1086#1082#1086#1083' '#8470': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 0
            Text = '30038'
            Visible = False
            OnKeyDown = OnLEKeyDown
          end
          object leTyreSize: TLabeledEdit
            Left = 75
            Top = 56
            Width = 62
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 42
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1056#1072#1079#1084#1077#1088': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 1
            Text = '185/70R14'
            OnKeyDown = OnLEKeyDown
          end
          object leTyreType: TLabeledEdit
            Left = 75
            Top = 80
            Width = 62
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 46
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1052#1086#1076#1077#1083#1100': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 2
            Text = #1071'-607'
            OnKeyDown = OnLEKeyDown
          end
          object leTestProc: TLabeledEdit
            Left = 75
            Top = 104
            Width = 62
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 58
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1052#1077#1090#1086#1076#1080#1082#1072': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 3
            Text = '32-2006'#1052
            OnKeyDown = OnLEKeyDown
          end
          object leStandNo: TLabeledEdit
            Left = 268
            Top = 56
            Width = 63
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 55
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1057#1090#1077#1085#1076' '#8470': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 5
            Text = #1054#1050#1040'-6'
            OnKeyDown = OnLEKeyDown
          end
          object leManufacturer: TLabeledEdit
            Left = 268
            Top = 80
            Width = 63
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 78
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1048#1079#1075#1086#1090#1086#1074#1080#1090#1077#1083#1100': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 6
            Text = 'Nokia'
            OnKeyDown = OnLEKeyDown
          end
          object leDrumD: TLabeledEdit
            Left = 268
            Top = 104
            Width = 63
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 121
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1044#1080#1072#1084#1077#1090#1088' '#1073#1072#1088#1072#1073#1072#1085#1072', '#1084#1084': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 7
            Text = '1700'
            OnKeyDown = OnLEKeyDown
          end
          object leCustomer: TLabeledEdit
            Left = 268
            Top = 32
            Width = 250
            Height = 20
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 54
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1047#1072#1082#1072#1079#1095#1080#1082': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 4
            Text = #1071#1064#1047
            OnKeyDown = OnLEKeyDown
          end
          object leSeralNo: TLabeledEdit
            Left = 454
            Top = 81
            Width = 64
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 87
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1055#1086#1088#1103#1076#1082#1086#1074#1099#1081' '#8470': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 9
            Text = '200'
            OnKeyDown = OnLEKeyDown
          end
          object leFormNo: TLabeledEdit
            Left = 583
            Top = 80
            Width = 33
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 55
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1060#1086#1088#1084#1072' '#8470': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 12
            Text = '1'
            OnKeyDown = OnLEKeyDown
          end
          object leOrderNo: TLabeledEdit
            Left = 583
            Top = 57
            Width = 33
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 52
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1047#1072#1082#1072#1079' '#8470': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 11
            Text = '1'
            OnKeyDown = OnLEKeyDown
          end
          object lePerfSpecNo: TLabeledEdit
            Left = 454
            Top = 104
            Width = 64
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 90
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1058#1077#1093'. '#1079#1072#1076#1072#1085#1080#1077' '#8470': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 10
            Text = '1'
            OnKeyDown = OnLEKeyDown
          end
          object pCommonProtData: TPanel
            Left = 2
            Top = 10
            Width = 596
            Height = 19
            BorderStyle = bsSingle
            Caption = #1054#1041#1065#1048#1045' '#1044#1040#1053#1053#1067#1045':'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 33
          end
          object pTyreParam: TPanel
            Left = 2
            Top = 138
            Width = 596
            Height = 19
            BorderStyle = bsSingle
            Caption = #1061#1040#1056#1040#1050#1058#1045#1056#1048#1057#1058#1048#1050#1040' '#1064#1048#1053#1067':'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsUnderline]
            ParentFont = False
            TabOrder = 34
          end
          object leLoadIndex: TLabeledEdit
            Left = 165
            Top = 164
            Width = 52
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 93
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1048#1085#1076#1077#1082#1089' '#1085#1072#1075#1088#1091#1079#1082#1080': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 13
            Text = '448/446Y'
            OnKeyDown = OnLEKeyDown
          end
          object leMaxLoad: TLabeledEdit
            Left = 165
            Top = 187
            Width = 52
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 149
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1072#1103' '#1085#1072#1075#1088#1091#1079#1082#1072', '#1082#1053': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 14
            Text = '50'
            OnKeyDown = OnLEKeyDown
          end
          object leSpeedIndex: TLabeledEdit
            Left = 165
            Top = 210
            Width = 52
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 110
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1050#1072#1090#1077#1075#1086#1088#1080#1103' '#1089#1082#1086#1088#1086#1089#1090#1080': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 15
            Text = 'T'
            OnKeyDown = OnLEKeyDown
          end
          object leMaxSpeed: TLabeledEdit
            Left = 165
            Top = 235
            Width = 52
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 158
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1072#1103' '#1089#1082#1086#1088#1086#1089#1090#1100', '#1082#1084'/'#1095': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 16
            Text = '180'
            OnKeyDown = OnLEKeyDown
          end
          object leStaticR: TLabeledEdit
            Left = 384
            Top = 164
            Width = 53
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 131
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1057#1090#1072#1090#1080#1095#1077#1089#1082#1080#1081' '#1088#1072#1076#1080#1091#1089', '#1084#1084': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 17
            Text = '300'
            OnKeyDown = OnLEKeyDown
          end
          object leOuterD: TLabeledEdit
            Left = 384
            Top = 187
            Width = 53
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 125
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1053#1072#1088#1091#1078#1085#1099#1081' '#1076#1080#1072#1084#1077#1090#1088', '#1084#1084': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 18
            Text = '560'
            OnKeyDown = OnLEKeyDown
          end
          object leRim: TLabeledEdit
            Left = 384
            Top = 210
            Width = 53
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 34
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1054#1073#1086#1076': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 19
            Text = '5.5J'
            OnKeyDown = OnLEKeyDown
          end
          object leQMaxPressure: TLabeledEdit
            Left = 384
            Top = 235
            Width = 53
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 153
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1044#1072#1074#1083#1077#1085#1080#1077' '#1087#1088#1080' Qmax, '#1082#1075#1089'/'#1089#1084'2: '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 20
            Text = '1000'
            OnKeyDown = OnLEKeyDown
          end
          object leTyreWide: TLabeledEdit
            Left = 563
            Top = 164
            Width = 69
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 113
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1064#1080#1088#1080#1085#1072' '#1087#1088#1086#1092#1080#1083#1103', '#1084#1084': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 21
            Text = '70'
            OnKeyDown = OnLEKeyDown
          end
          object rgTyreType: TRadioGroup
            Left = 481
            Top = 189
            Width = 108
            Height = 52
            BiDiMode = bdLeftToRight
            Caption = #1058#1080#1087' '#1087#1086#1082#1088#1099#1096#1082#1080
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ItemIndex = 0
            Items.Strings = (
              #1088#1072#1076#1080#1072#1083#1100#1085#1072#1103
              #1076#1080#1072#1075#1086#1085#1072#1083#1100#1085#1072#1103)
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 22
            Visible = False
          end
          object pTestMode: TPanel
            Left = 2
            Top = 270
            Width = 596
            Height = 19
            BorderStyle = bsSingle
            Caption = #1056#1045#1046#1048#1052' '#1048#1057#1055#1067#1058#1040#1053#1048#1049':'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsUnderline]
            ParentFont = False
            TabOrder = 35
            Visible = False
          end
          object leTestLoad: TLabeledEdit
            Left = 158
            Top = 293
            Width = 52
            Height = 20
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 74
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1053#1072#1075#1088#1091#1079#1082#1072', '#1082#1053': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 27
            Text = '1'
            Visible = False
          end
          object leInitPressure: TLabeledEdit
            Left = 158
            Top = 317
            Width = 52
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 142
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1053#1072#1095#1072#1083#1100#1085#1086#1077' '#1076#1072#1074#1083#1077#1085#1080#1077', '#1052#1055#1072': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 28
            Text = '50'
            Visible = False
          end
          object leTestSpeed: TLabeledEdit
            Left = 158
            Top = 340
            Width = 52
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 55
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1057#1082#1086#1088#1086#1089#1090#1100': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 29
            Text = '100'
            Visible = False
          end
          object cmbTestMode: TComboBox
            Left = 324
            Top = 293
            Width = 84
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 30
            Text = #1087#1086' '#1074#1088#1077#1084#1077#1085#1080
            Visible = False
            OnChange = OnTestModeChange
            Items.Strings = (
              #1087#1086' '#1074#1088#1077#1084#1077#1085#1080
              #1087#1086' '#1087#1091#1090#1080)
          end
          object leTestTimePath: TLabeledEdit
            Left = 324
            Top = 317
            Width = 77
            Height = 18
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 95
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1042#1088#1077#1084#1103' '#1086#1073#1082#1072#1090#1082#1080', '#1095': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 31
            Text = '10'
            Visible = False
          end
          object leAsks: TLabeledEdit
            Left = 324
            Top = 340
            Width = 77
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 46
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1054#1087#1088#1086#1089#1099': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 32
            Text = '10'
            Visible = False
          end
          object btnLoadProtToPosA: TButton
            Left = 324
            Top = 371
            Width = 90
            Height = 37
            Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1074' '#1087#1086#1079'. '#1040
            TabOrder = 26
            WordWrap = True
            OnClick = OnLoadProtToPosA
          end
          object meManDate: TMaskEdit
            Left = 457
            Top = 57
            Width = 59
            Height = 21
            EditMask = '!99/0000;1;_'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            MaxLength = 7
            ParentFont = False
            TabOrder = 8
            Text = '  .    '
            OnKeyDown = OnLEKeyDown
          end
          object btnClearProt: TButton
            Left = 9
            Top = 371
            Width = 90
            Height = 37
            Caption = #1047#1072#1087#1086#1083#1085#1080#1090#1100' '#1085#1086#1074#1099#1081' '#1087#1088#1086#1090#1086#1082#1086#1083
            TabOrder = 23
            WordWrap = True
            OnClick = OnClearProt
          end
          object btnSaveProtTtlToFile: TButton
            Left = 104
            Top = 371
            Width = 90
            Height = 37
            Action = acProtTitleFileSaveAs
            TabOrder = 24
            WordWrap = True
          end
          object btnLoadProtTtlFmFile: TButton
            Left = 206
            Top = 371
            Width = 90
            Height = 37
            Action = acProtTitleFileOpen
            TabOrder = 25
            WordWrap = True
          end
        end
      end
    end
    object tsEmSettings: TTabSheet
      Caption = #1059#1089#1090#1072#1085#1086#1074#1082#1080
      ImageIndex = 8
      object GroupBox1: TGroupBox
        Left = 0
        Top = 3
        Width = 625
        Height = 158
        Caption = #1058#1077#1082#1091#1097#1080#1077' '#1091#1089#1090#1072#1085#1086#1074#1082#1080
        TabOrder = 0
        object leEmMaxSpeed: TLabeledEdit
          Left = 290
          Top = 87
          Width = 70
          Height = 29
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 270
          EditLabel.Height = 18
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1072#1103' '#1089#1082#1086#1088#1086#1089#1090#1100' '#1074' '#1094#1080#1082#1083#1077', '#1082#1084'/'#1095':'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'Tahoma'
          EditLabel.Font.Style = []
          EditLabel.ParentBiDiMode = False
          EditLabel.ParentFont = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          LabelPosition = lpLeft
          ParentBiDiMode = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 0
          Text = '10'
        end
        object leEmMaxLoad_1: TLabeledEdit
          Left = 556
          Top = 17
          Width = 57
          Height = 29
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 213
          EditLabel.Height = 18
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = #1052#1072#1082#1089'. '#1085#1072#1075#1088#1091#1079#1082#1072' '#1074' '#1094#1080#1082#1083#1077' '#1040', '#1082#1053': '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'Tahoma'
          EditLabel.Font.Style = []
          EditLabel.ParentBiDiMode = False
          EditLabel.ParentFont = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          LabelPosition = lpLeft
          ParentBiDiMode = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 1
          Text = '10'
        end
        object leEmMinLoad_1: TLabeledEdit
          Left = 250
          Top = 17
          Width = 56
          Height = 29
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 202
          EditLabel.Height = 18
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = #1052#1080#1085'. '#1085#1072#1075#1088#1091#1079#1082#1072' '#1074' '#1094#1080#1082#1083#1077' '#1040', '#1082#1053':'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'Tahoma'
          EditLabel.Font.Style = []
          EditLabel.ParentBiDiMode = False
          EditLabel.ParentFont = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          LabelPosition = lpLeft
          ParentBiDiMode = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 2
          Text = '10'
        end
        object leEmMinSpeed: TLabeledEdit
          Left = 290
          Top = 122
          Width = 70
          Height = 29
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 269
          EditLabel.Height = 18
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = #1052#1080#1085#1080#1084#1072#1083#1100#1085#1072#1103' '#1089#1082#1086#1088#1086#1089#1090#1100' '#1074' '#1094#1080#1082#1083#1077', '#1082#1084'/'#1095': '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'Tahoma'
          EditLabel.Font.Style = []
          EditLabel.ParentBiDiMode = False
          EditLabel.ParentFont = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          LabelPosition = lpLeft
          ParentBiDiMode = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 3
          Text = '10'
        end
        object leEmMinTemp_1: TLabeledEdit
          Left = 250
          Top = 52
          Width = 56
          Height = 29
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 218
          EditLabel.Height = 18
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = #1052#1080#1085'. '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1072' '#1087#1086#1079'. '#1040', '#1075#1088' '#1057':'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'Tahoma'
          EditLabel.Font.Style = []
          EditLabel.ParentBiDiMode = False
          EditLabel.ParentFont = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          LabelPosition = lpLeft
          ParentBiDiMode = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 4
          Text = '10'
        end
        object leEmMaxTemp_1: TLabeledEdit
          Left = 556
          Top = 52
          Width = 57
          Height = 29
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 219
          EditLabel.Height = 18
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = #1052#1072#1082#1089'. '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1072' '#1087#1086#1079'. '#1040', '#1075#1088' '#1057
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'Tahoma'
          EditLabel.Font.Style = []
          EditLabel.ParentBiDiMode = False
          EditLabel.ParentFont = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          LabelPosition = lpLeft
          ParentBiDiMode = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 5
          Text = '10'
        end
      end
      object GroupBox2: TGroupBox
        Left = 3
        Top = 167
        Width = 622
        Height = 170
        Caption = #1053#1086#1074#1099#1077' '#1091#1089#1090#1072#1085#1086#1074#1082#1080
        TabOrder = 1
        object leEmMaxSpeedR: TLabeledEdit
          Left = 287
          Top = 95
          Width = 70
          Height = 29
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 270
          EditLabel.Height = 18
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1072#1103' '#1089#1082#1086#1088#1086#1089#1090#1100' '#1074' '#1094#1080#1082#1083#1077', '#1082#1084'/'#1095':'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'Tahoma'
          EditLabel.Font.Style = []
          EditLabel.ParentBiDiMode = False
          EditLabel.ParentFont = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          LabelPosition = lpLeft
          ParentBiDiMode = False
          ParentFont = False
          TabOrder = 0
          OnKeyPress = leEmMinLoad_1RKeyPress
        end
        object leEmMaxLoad_1R: TLabeledEdit
          Left = 553
          Top = 19
          Width = 57
          Height = 29
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 213
          EditLabel.Height = 18
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = #1052#1072#1082#1089'. '#1085#1072#1075#1088#1091#1079#1082#1072' '#1074' '#1094#1080#1082#1083#1077' '#1040', '#1082#1053': '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'Tahoma'
          EditLabel.Font.Style = []
          EditLabel.ParentBiDiMode = False
          EditLabel.ParentFont = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          LabelPosition = lpLeft
          ParentBiDiMode = False
          ParentFont = False
          TabOrder = 1
          OnKeyPress = leEmMinLoad_1RKeyPress
        end
        object leEmMinLoad_1R: TLabeledEdit
          Left = 247
          Top = 25
          Width = 56
          Height = 29
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 202
          EditLabel.Height = 18
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = #1052#1080#1085'. '#1085#1072#1075#1088#1091#1079#1082#1072' '#1074' '#1094#1080#1082#1083#1077' '#1040', '#1082#1053':'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'Tahoma'
          EditLabel.Font.Style = []
          EditLabel.ParentBiDiMode = False
          EditLabel.ParentFont = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          LabelPosition = lpLeft
          ParentBiDiMode = False
          ParentFont = False
          TabOrder = 2
          OnKeyPress = leEmMinLoad_1RKeyPress
        end
        object btEmSettings: TButton
          Left = 472
          Top = 132
          Width = 138
          Height = 29
          Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
          TabOrder = 3
          OnClick = btEmSettingsClick
        end
        object leEmMinSpeedR: TLabeledEdit
          Left = 287
          Top = 130
          Width = 70
          Height = 29
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 269
          EditLabel.Height = 18
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = #1052#1080#1085#1080#1084#1072#1083#1100#1085#1072#1103' '#1089#1082#1086#1088#1086#1089#1090#1100' '#1074' '#1094#1080#1082#1083#1077', '#1082#1084'/'#1095': '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'Tahoma'
          EditLabel.Font.Style = []
          EditLabel.ParentBiDiMode = False
          EditLabel.ParentFont = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          LabelPosition = lpLeft
          ParentBiDiMode = False
          ParentFont = False
          TabOrder = 4
          OnKeyPress = leEmMinLoad_1RKeyPress
        end
        object leEmMinTemp_1R: TLabeledEdit
          Left = 247
          Top = 60
          Width = 56
          Height = 29
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 218
          EditLabel.Height = 18
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = #1052#1080#1085'. '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1072' '#1087#1086#1079'. '#1040', '#1075#1088' '#1057':'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'Tahoma'
          EditLabel.Font.Style = []
          EditLabel.ParentBiDiMode = False
          EditLabel.ParentFont = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          LabelPosition = lpLeft
          ParentBiDiMode = False
          ParentFont = False
          TabOrder = 5
        end
        object leEmMaxTemp_1R: TLabeledEdit
          Left = 551
          Top = 54
          Width = 59
          Height = 29
          AutoSize = False
          BiDiMode = bdLeftToRight
          EditLabel.Width = 219
          EditLabel.Height = 18
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = #1052#1072#1082#1089'. '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1072' '#1087#1086#1079'. '#1040', '#1075#1088' '#1057
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'Tahoma'
          EditLabel.Font.Style = []
          EditLabel.ParentBiDiMode = False
          EditLabel.ParentFont = False
          EditLabel.Layout = tlCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -17
          Font.Name = 'Tahoma'
          Font.Style = []
          LabelPosition = lpLeft
          ParentBiDiMode = False
          ParentFont = False
          TabOrder = 6
        end
      end
    end
    object tsCalibration: TTabSheet
      Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103
      ImageIndex = 4
      object pcCalibration: TPageControl
        Left = 0
        Top = 0
        Width = 808
        Height = 599
        ActivePage = tsSpeedCalibr
        Align = alClient
        TabOrder = 0
        object tsLoadCalibr: TTabSheet
          Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103' '#1087#1086' '#1085#1072#1075#1088#1091#1079#1082#1077
          object pcLoadCalibr: TPageControl
            Left = 0
            Top = 0
            Width = 800
            Height = 570
            ActivePage = tsLoadCalibrA
            Align = alClient
            TabOrder = 0
            object tsLoadCalibrA: TTabSheet
              Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103' '#1087#1086' '#1085#1072#1075#1088#1091#1079#1082#1077' '#1087#1086#1079'. '#1040
              object pLoadCalibrBTtl: TPanel
                Left = 0
                Top = 0
                Width = 792
                Height = 20
                Align = alTop
                BevelKind = bkFlat
                BorderStyle = bsSingle
                Caption = 
                  #1054#1087#1088#1077#1076#1077#1083#1077#1085#1080#1077' '#1086#1090#1085#1086#1089#1080#1090#1077#1083#1100#1085#1086#1081' '#1087#1086#1075#1088#1077#1096#1085#1086#1089#1090#1080' (%) '#1079#1072#1076#1072#1085#1080#1103' '#1080' '#1087#1086#1076#1076#1077#1088#1078#1072#1085#1080#1103' ' +
                  #1089#1080#1083#1099' '#1087#1088#1080#1078#1080#1084#1072' '#1096#1080#1085#1099' '#1082' '#1073#1072#1088#1072#1073#1072#1085#1091' ('#1082#1053')'
                Color = clMedGray
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindow
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentBackground = False
                ParentFont = False
                TabOrder = 0
              end
              object sgLoadCalibrA: TStringGrid
                Left = 0
                Top = 20
                Width = 280
                Height = 521
                Align = alLeft
                RowCount = 14
                ScrollBars = ssVertical
                TabOrder = 1
                OnDrawCell = OnCalibrDrawCell
                OnExit = OnStringGridExit
                OnKeyPress = OnSGKeyPress
                ColWidths = (
                  64
                  64
                  64
                  64
                  64)
                RowHeights = (
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24)
              end
              object btnPrevCalibrLoadA: TButton
                Left = 290
                Top = 39
                Width = 192
                Height = 38
                Caption = #1055#1088#1077#1076#1099#1076#1091#1097#1077#1077' '#1079#1072#1076#1072#1085#1080#1077
                TabOrder = 2
                WordWrap = True
                OnClick = OnPrevCalibrLoadBtn
              end
              object leCurrentLoadSetA: TLabeledEdit
                Left = 286
                Top = 100
                Width = 64
                Height = 19
                AutoSize = False
                BiDiMode = bdLeftToRight
                EditLabel.Width = 47
                EditLabel.Height = 13
                EditLabel.BiDiMode = bdLeftToRight
                EditLabel.Caption = #1047#1072#1076#1072#1085#1080#1077':'
                EditLabel.Font.Charset = DEFAULT_CHARSET
                EditLabel.Font.Color = clWindowText
                EditLabel.Font.Height = -11
                EditLabel.Font.Name = 'Tahoma'
                EditLabel.Font.Style = []
                EditLabel.ParentBiDiMode = False
                EditLabel.ParentFont = False
                EditLabel.Layout = tlCenter
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentBiDiMode = False
                ParentFont = False
                ReadOnly = True
                TabOrder = 3
                Text = '150.00'
              end
              object leReadLoadA: TLabeledEdit
                Left = 354
                Top = 100
                Width = 64
                Height = 19
                AutoSize = False
                BiDiMode = bdLeftToRight
                EditLabel.Width = 58
                EditLabel.Height = 13
                EditLabel.BiDiMode = bdLeftToRight
                EditLabel.Caption = #1055#1086#1082#1072#1079#1072#1085#1080#1077':'
                EditLabel.Font.Charset = DEFAULT_CHARSET
                EditLabel.Font.Color = clWindowText
                EditLabel.Font.Height = -11
                EditLabel.Font.Name = 'Tahoma'
                EditLabel.Font.Style = []
                EditLabel.ParentBiDiMode = False
                EditLabel.ParentFont = False
                EditLabel.Layout = tlCenter
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentBiDiMode = False
                ParentFont = False
                ReadOnly = True
                TabOrder = 4
                Text = '150.00'
              end
              object leMeasuredLoadA: TLabeledEdit
                Left = 418
                Top = 100
                Width = 64
                Height = 19
                AutoSize = False
                BiDiMode = bdLeftToRight
                EditLabel.Width = 58
                EditLabel.Height = 13
                EditLabel.BiDiMode = bdLeftToRight
                EditLabel.Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077':'
                EditLabel.Font.Charset = DEFAULT_CHARSET
                EditLabel.Font.Color = clWindowText
                EditLabel.Font.Height = -11
                EditLabel.Font.Name = 'Tahoma'
                EditLabel.Font.Style = []
                EditLabel.ParentBiDiMode = False
                EditLabel.ParentFont = False
                EditLabel.Layout = tlCenter
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentBiDiMode = False
                ParentFont = False
                TabOrder = 5
                Text = '150.00'
                OnKeyPress = OnSGKeyPress
              end
              object btnNextCalibrLoadA: TButton
                Left = 290
                Top = 124
                Width = 192
                Height = 28
                Caption = #1057#1083#1077#1076#1091#1102#1097#1077#1077' '#1079#1072#1076#1072#1085#1080#1077
                TabOrder = 6
                WordWrap = True
                OnClick = OnNextCalibrLoadBtn
              end
              object btnClearLoadCalibreTableA: TButton
                Left = 503
                Top = 35
                Width = 80
                Height = 37
                Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
                TabOrder = 7
                WordWrap = True
                OnClick = OnLoadCalibrTableClear
              end
              object btnLoadCalibrCalcA: TButton
                Left = 503
                Top = 77
                Width = 80
                Height = 36
                Caption = #1056#1072#1089#1089#1095#1080#1090#1072#1090#1100' '#1087#1086#1075#1088#1077#1096#1085#1086#1089#1090#1100
                TabOrder = 8
                WordWrap = True
                OnClick = OnLoadCalibrCalc
              end
              object btnLoadCalibrTableAPrint: TButton
                Left = 503
                Top = 131
                Width = 80
                Height = 36
                Action = acPrintLoadCalibrProtA
                Caption = #1056#1072#1089#1087#1077#1095#1072#1090#1072#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083
                TabOrder = 9
                WordWrap = True
              end
              object btnPumpOnA: TButton
                Left = 311
                Top = 236
                Width = 155
                Height = 24
                Caption = #1042#1050#1051#1070#1063#1048#1058#1068' '#1053#1040#1057#1054#1057' '#1040', Ctrl+F1'
                TabOrder = 10
                OnClick = OnPump1On
              end
              object btnPumpOffA: TButton
                Left = 311
                Top = 273
                Width = 155
                Height = 24
                Caption = #1042#1067#1050#1051#1070#1063#1048#1058#1068' '#1053#1040#1057#1054#1057' '#1040', Ctrl+F2'
                TabOrder = 11
                OnClick = OnPump1Off
              end
            end
          end
        end
        object tsRadiusCalibr: TTabSheet
          Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103' '#1087#1086' '#1088#1072#1076#1080#1091#1089#1091
          ImageIndex = 1
          object pcRadiusCalibr: TPageControl
            Left = 0
            Top = 0
            Width = 800
            Height = 570
            ActivePage = tsRCalibrA
            Align = alClient
            TabOrder = 0
            object tsRCalibrA: TTabSheet
              Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103' '#1087#1086' '#1088#1072#1076#1080#1091#1089#1091' '#1087#1086#1079'. '#1040
              object pRCalibrATtl: TPanel
                Left = 0
                Top = 0
                Width = 792
                Height = 26
                Align = alTop
                BevelKind = bkFlat
                BorderStyle = bsSingle
                Caption = #1054#1087#1088#1077#1076#1077#1083#1077#1085#1080#1077' '#1072#1073#1089#1086#1083#1102#1090#1085#1086#1081' '#1087#1086#1075#1088#1077#1096#1085#1086#1089#1090#1080' '#1080#1079#1084#1077#1088#1077#1085#1080#1103' '#1088#1072#1076#1080#1091#1089#1072' ('#1084#1084')'
                Color = clMedGray
                ParentBackground = False
                TabOrder = 0
              end
              object sgRCalibrA: TStringGrid
                Left = 0
                Top = 26
                Width = 263
                Height = 515
                Align = alLeft
                ColCount = 4
                RowCount = 21
                ScrollBars = ssNone
                TabOrder = 1
                OnDrawCell = OnCalibrDrawCell
                OnExit = OnStringGridExit
                ColWidths = (
                  64
                  64
                  64
                  64)
                RowHeights = (
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24)
              end
              object btnPrevRCalibrA: TButton
                Left = 290
                Top = 33
                Width = 192
                Height = 38
                Caption = #1055#1088#1077#1076#1099#1076#1091#1097#1077#1077' '#1079#1085#1072#1095#1077#1085#1080#1077
                TabOrder = 2
                WordWrap = True
                OnClick = OnPrevCalibrRBtn
              end
              object leReadRA: TLabeledEdit
                Left = 294
                Top = 100
                Width = 88
                Height = 19
                AutoSize = False
                BiDiMode = bdLeftToRight
                EditLabel.Width = 58
                EditLabel.Height = 13
                EditLabel.BiDiMode = bdLeftToRight
                EditLabel.Caption = #1055#1086#1082#1072#1079#1072#1085#1080#1077':'
                EditLabel.Font.Charset = DEFAULT_CHARSET
                EditLabel.Font.Color = clWindowText
                EditLabel.Font.Height = -11
                EditLabel.Font.Name = 'Tahoma'
                EditLabel.Font.Style = []
                EditLabel.ParentBiDiMode = False
                EditLabel.ParentFont = False
                EditLabel.Layout = tlCenter
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentBiDiMode = False
                ParentFont = False
                ReadOnly = True
                TabOrder = 3
                Text = '150.00'
              end
              object leMeasRA: TLabeledEdit
                Left = 382
                Top = 100
                Width = 100
                Height = 19
                AutoSize = False
                BiDiMode = bdLeftToRight
                EditLabel.Width = 58
                EditLabel.Height = 13
                EditLabel.BiDiMode = bdLeftToRight
                EditLabel.Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077':'
                EditLabel.Font.Charset = DEFAULT_CHARSET
                EditLabel.Font.Color = clWindowText
                EditLabel.Font.Height = -11
                EditLabel.Font.Name = 'Tahoma'
                EditLabel.Font.Style = []
                EditLabel.ParentBiDiMode = False
                EditLabel.ParentFont = False
                EditLabel.Layout = tlCenter
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentBiDiMode = False
                ParentFont = False
                TabOrder = 4
                Text = '150.00'
                OnKeyPress = OnSGKeyPress
              end
              object btnNextRCalibrA: TButton
                Left = 290
                Top = 124
                Width = 192
                Height = 28
                Caption = #1057#1083#1077#1076#1091#1102#1097#1077#1077' '#1079#1085#1072#1095#1077#1085#1080#1077
                TabOrder = 5
                WordWrap = True
                OnClick = OnNextCalibrRBtn
              end
              object btnClearRCalibrTableA: TButton
                Left = 503
                Top = 35
                Width = 80
                Height = 37
                Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
                TabOrder = 6
                WordWrap = True
                OnClick = OnRCalibrTableClear
              end
              object btnRCalibrCalcA: TButton
                Left = 503
                Top = 77
                Width = 80
                Height = 36
                Caption = #1056#1072#1089#1089#1095#1080#1090#1072#1090#1100' '#1087#1086#1075#1088#1077#1096#1085#1086#1089#1090#1100
                TabOrder = 7
                WordWrap = True
                OnClick = OnRCalibrCalc
              end
              object btnRCalibrTableAPrint: TButton
                Left = 503
                Top = 131
                Width = 80
                Height = 36
                Action = acPrintRCalibrProtA
                Caption = #1056#1072#1089#1087#1077#1095#1072#1090#1072#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083
                TabOrder = 8
                WordWrap = True
              end
              object btnCalibrCarr1Fm: TButton
                Left = 290
                Top = 215
                Width = 84
                Height = 30
                Caption = #1054#1058' '#1041#1040#1056#1040#1041#1040#1053#1040', F3'
                TabOrder = 9
                OnClick = OnCarriage1From
              end
              object btnCalibrCarr1Stop: TButton
                Left = 378
                Top = 215
                Width = 47
                Height = 30
                Caption = #1057#1058#1054#1055', F4'
                TabOrder = 10
                OnClick = OnCarriage1Stop
              end
              object btnCalibrCarr1To: TButton
                Left = 428
                Top = 215
                Width = 76
                Height = 30
                Caption = #1050' '#1041#1040#1056#1040#1041#1040#1053#1059', F5'
                TabOrder = 11
                OnClick = OnCarriage1To
              end
            end
          end
        end
        object tsTempCalibr: TTabSheet
          Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103' '#1087#1086' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1077
          ImageIndex = 2
          object pcTempCalibr: TPageControl
            Left = 0
            Top = 0
            Width = 800
            Height = 570
            ActivePage = tsTCalibrA
            Align = alClient
            TabOrder = 0
            object tsTCalibrA: TTabSheet
              Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103' '#1087#1086' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1077' '#1087#1086#1079'. '#1040
              object pTCalibrATtl: TPanel
                Left = 0
                Top = 0
                Width = 792
                Height = 26
                Align = alTop
                BevelKind = bkFlat
                BorderStyle = bsSingle
                Caption = #1054#1087#1088#1077#1076#1077#1083#1077#1085#1080#1077' '#1072#1073#1089#1086#1083#1102#1090#1085#1086#1081' '#1087#1086#1075#1088#1077#1096#1085#1086#1089#1090#1080' '#1080#1079#1084#1077#1088#1077#1085#1080#1103' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099' (C)'
                Color = clMedGray
                ParentBackground = False
                TabOrder = 0
              end
              object sgTCalibrA: TStringGrid
                Left = 0
                Top = 26
                Width = 263
                Height = 515
                Align = alLeft
                ColCount = 4
                RowCount = 21
                ScrollBars = ssNone
                TabOrder = 1
                OnDrawCell = OnCalibrDrawCell
                OnExit = OnStringGridExit
                ColWidths = (
                  64
                  64
                  64
                  64)
                RowHeights = (
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24)
              end
              object btnPrevTCalibrA: TButton
                Left = 290
                Top = 39
                Width = 192
                Height = 38
                Caption = #1055#1088#1077#1076#1099#1076#1091#1097#1077#1077' '#1079#1085#1072#1095#1077#1085#1080#1077
                TabOrder = 2
                WordWrap = True
                OnClick = OnPrevCalibrTBtn
              end
              object leReadTA: TLabeledEdit
                Left = 294
                Top = 100
                Width = 88
                Height = 19
                AutoSize = False
                BiDiMode = bdLeftToRight
                EditLabel.Width = 58
                EditLabel.Height = 13
                EditLabel.BiDiMode = bdLeftToRight
                EditLabel.Caption = #1055#1086#1082#1072#1079#1072#1085#1080#1077':'
                EditLabel.Font.Charset = DEFAULT_CHARSET
                EditLabel.Font.Color = clWindowText
                EditLabel.Font.Height = -11
                EditLabel.Font.Name = 'Tahoma'
                EditLabel.Font.Style = []
                EditLabel.ParentBiDiMode = False
                EditLabel.ParentFont = False
                EditLabel.Layout = tlCenter
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentBiDiMode = False
                ParentFont = False
                ReadOnly = True
                TabOrder = 3
                Text = '150.00'
              end
              object leMeasTA: TLabeledEdit
                Left = 382
                Top = 100
                Width = 100
                Height = 19
                AutoSize = False
                BiDiMode = bdLeftToRight
                EditLabel.Width = 58
                EditLabel.Height = 13
                EditLabel.BiDiMode = bdLeftToRight
                EditLabel.Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077':'
                EditLabel.Font.Charset = DEFAULT_CHARSET
                EditLabel.Font.Color = clWindowText
                EditLabel.Font.Height = -11
                EditLabel.Font.Name = 'Tahoma'
                EditLabel.Font.Style = []
                EditLabel.ParentBiDiMode = False
                EditLabel.ParentFont = False
                EditLabel.Layout = tlCenter
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentBiDiMode = False
                ParentFont = False
                TabOrder = 4
                Text = '150.00'
                OnKeyPress = OnSGKeyPress
              end
              object btnNextTCalibrA: TButton
                Left = 290
                Top = 124
                Width = 192
                Height = 28
                Caption = #1057#1083#1077#1076#1091#1102#1097#1077#1077' '#1079#1085#1072#1095#1077#1085#1080#1077
                TabOrder = 5
                WordWrap = True
                OnClick = OnNextCalibrTBtn
              end
              object btnClearTCalibrTableA: TButton
                Left = 503
                Top = 35
                Width = 125
                Height = 37
                Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
                TabOrder = 6
                WordWrap = True
                OnClick = OnTCalibrTableClear
              end
              object btnTCalibrCalcA: TButton
                Left = 503
                Top = 77
                Width = 125
                Height = 36
                Caption = #1056#1072#1089#1089#1095#1080#1090#1072#1090#1100' '#1087#1086#1075#1088#1077#1096#1085#1086#1089#1090#1100
                TabOrder = 7
                WordWrap = True
                OnClick = OnTCalibrCalc
              end
              object btnTCalibrTableAPrint: TButton
                Left = 503
                Top = 131
                Width = 125
                Height = 36
                Action = acPrintTCalibrProtA
                Caption = #1056#1072#1089#1087#1077#1095#1072#1090#1072#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083
                TabOrder = 8
                WordWrap = True
              end
              object btnTLimitsCalcA: TButton
                Left = 503
                Top = 187
                Width = 125
                Height = 46
                Hint = 'Save As|Saves the active file with a new name'
                Caption = #1056#1072#1089#1089#1095#1080#1090#1072#1090#1100' '#1087#1086#1087#1088#1072#1074#1082#1080' '#1076#1083#1103' '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1080
                TabOrder = 9
                WordWrap = True
                OnClick = OnTLimitsCalc
              end
            end
          end
        end
        object tsSpeedCalibr: TTabSheet
          Caption = #1040#1090#1090#1077#1089#1090#1072#1094#1080#1103' '#1073#1072#1088#1072#1073#1072#1085#1072
          ImageIndex = 3
          object pSpeedCalibrTtl: TPanel
            Left = 0
            Top = 0
            Width = 800
            Height = 20
            Align = alTop
            BevelKind = bkFlat
            BorderStyle = bsSingle
            Caption = 
              #1054#1087#1088#1077#1076#1077#1083#1077#1085#1080#1077' '#1086#1090#1085#1086#1089#1080#1090#1077#1083#1100#1085#1086#1081' '#1087#1086#1075#1088#1077#1096#1085#1086#1089#1090#1080' (%) '#1079#1072#1076#1072#1085#1080#1103' '#1080' '#1087#1086#1076#1076#1077#1088#1078#1072#1085#1080#1103' ' +
              #1083#1080#1085#1077#1081#1085#1086#1081' '#1089#1082#1086#1088#1086#1089#1090#1080' '#1073#1072#1088#1072#1073#1072#1085#1072' ('#1082#1084'/'#1095')'
            Color = clMedGray
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindow
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentBackground = False
            ParentFont = False
            TabOrder = 0
          end
          object sgSpeedCalibr: TStringGrid
            Left = 0
            Top = 20
            Width = 263
            Height = 550
            Align = alLeft
            RowCount = 18
            ScrollBars = ssVertical
            TabOrder = 1
            OnDrawCell = OnCalibrDrawCell
            OnExit = OnStringGridExit
            ColWidths = (
              64
              64
              64
              64
              64)
            RowHeights = (
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24
              24)
          end
          object leCurrentVSet: TLabeledEdit
            Left = 290
            Top = 100
            Width = 64
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 47
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1047#1072#1076#1072#1085#1080#1077':'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 2
            Text = '150.00'
          end
          object leReadV: TLabeledEdit
            Left = 354
            Top = 100
            Width = 64
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 58
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1055#1086#1082#1072#1079#1072#1085#1080#1077':'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 3
            Text = '150.00'
          end
          object leMeasuredV: TLabeledEdit
            Left = 418
            Top = 100
            Width = 64
            Height = 19
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 58
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077':'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 4
            Text = '150.00'
            OnKeyPress = OnSGKeyPress
          end
          object btnPrevCalibrV: TButton
            Left = 290
            Top = 39
            Width = 192
            Height = 38
            Caption = #1055#1088#1077#1076#1099#1076#1091#1097#1077#1077' '#1079#1072#1076#1072#1085#1080#1077
            TabOrder = 5
            WordWrap = True
            OnClick = OnPrevCalibrVBtn
          end
          object btnNextCalibrV: TButton
            Left = 290
            Top = 131
            Width = 192
            Height = 28
            Caption = #1057#1083#1077#1076#1091#1102#1097#1077#1077' '#1079#1072#1076#1072#1085#1080#1077
            TabOrder = 6
            WordWrap = True
            OnClick = OnNextCalibrVBtn
          end
          object btnCalibrVCalc: TButton
            Left = 503
            Top = 83
            Width = 80
            Height = 36
            Caption = #1056#1072#1089#1089#1095#1080#1090#1072#1090#1100' '#1087#1086#1075#1088#1077#1096#1085#1086#1089#1090#1100
            TabOrder = 7
            WordWrap = True
            OnClick = OnVCalibrCalc
          end
          object btnVCalibrDrumOn: TButton
            Left = 336
            Top = 233
            Width = 137
            Height = 24
            Caption = #1042#1050#1051#1070#1063#1048#1058#1068' '#1041#1040#1056#1040#1041#1040#1053', F6'
            TabOrder = 8
            OnClick = OnDrumOn
          end
          object btnVCalibrDrumOff: TButton
            Left = 336
            Top = 273
            Width = 137
            Height = 24
            Caption = #1042#1067#1050#1051#1070#1063#1048#1058#1068' '#1041#1040#1056#1040#1041#1040#1053', F7'
            TabOrder = 9
            OnClick = OnDrumOff
          end
          object btnClearVCalibreTable: TButton
            Left = 503
            Top = 35
            Width = 80
            Height = 37
            Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
            TabOrder = 10
            WordWrap = True
            OnClick = OnVCalibrClear
          end
          object btnSpdCalibrTablePrint: TButton
            Left = 503
            Top = 131
            Width = 80
            Height = 36
            Action = acPrintSpdCalibrProt
            Caption = #1056#1072#1089#1087#1077#1095#1072#1090#1072#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083
            TabOrder = 11
            WordWrap = True
          end
        end
      end
    end
    object tsSert: TTabSheet
      Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072
      ImageIndex = 7
      object pcSert: TPageControl
        Left = 0
        Top = 0
        Width = 808
        Height = 599
        ActivePage = tsDrumSpeedSert
        Align = alClient
        TabOrder = 0
        object tsDrumSpeedSert: TTabSheet
          Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072' '#1089#1082#1086#1088#1086#1089#1090#1080
          object pDrumSpeedSertTtl: TPanel
            Left = 0
            Top = 0
            Width = 800
            Height = 33
            Align = alTop
            BevelKind = bkFlat
            BorderStyle = bsSingle
            Caption = #1042#1074#1086#1076' '#1087#1086#1087#1088#1072#1074#1086#1095#1085#1099#1093' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090#1086#1074' '#1087#1086' '#1079#1072#1076#1072#1085#1080#1102' '#1080' '#1080#1079#1084#1077#1088#1077#1085#1080#1102' '#1089#1082#1086#1088#1086#1089#1090#1080
            Color = clMedGray
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindow
            Font.Height = -13
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentBackground = False
            ParentFont = False
            TabOrder = 0
          end
          object leSetSpeedCoef: TLabeledEdit
            Left = 267
            Top = 54
            Width = 66
            Height = 20
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 242
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1055#1086#1087#1088#1072#1074#1086#1095#1085#1099#1081' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090' '#1079#1072#1076#1072#1085#1080#1103' '#1089#1082#1086#1088#1086#1089#1090#1080': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 1
            Text = '1.00'
          end
          object leMeasSpeedCoef: TLabeledEdit
            Left = 267
            Top = 104
            Width = 66
            Height = 20
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 253
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1055#1086#1087#1088#1072#1074#1086#1095#1085#1099#1081' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090' '#1080#1079#1084#1077#1088#1077#1085#1080#1103' '#1089#1082#1086#1088#1086#1089#1090#1080': '
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            LabelPosition = lpLeft
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 2
            Text = '1.00'
          end
          object btnLoadSpeedCoefToPLC: TButton
            Left = 426
            Top = 54
            Width = 121
            Height = 67
            Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090#1099' '#1074' '#1082#1086#1085#1090#1088#1086#1083#1083#1077#1088
            TabOrder = 3
            WordWrap = True
            OnClick = OnLoadSpeedCoefToPLC
          end
          object leSetSpeedCoefReal: TLabeledEdit
            Left = 339
            Top = 54
            Width = 81
            Height = 20
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 79
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1042' '#1082#1086#1085#1090#1088#1086#1083#1083#1077#1088#1077':'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 4
            Text = '0.00'
          end
          object leMeasSpeedCoefReal: TLabeledEdit
            Left = 339
            Top = 104
            Width = 81
            Height = 20
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 79
            EditLabel.Height = 13
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1042' '#1082#1086#1085#1090#1088#1086#1083#1083#1077#1088#1077':'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'Tahoma'
            EditLabel.Font.Style = []
            EditLabel.ParentBiDiMode = False
            EditLabel.ParentFont = False
            EditLabel.Layout = tlCenter
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentBiDiMode = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 5
            Text = '0.00'
          end
        end
        object tsTemSert: TTabSheet
          Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072' '#1076#1072#1090#1095#1080#1082#1086#1074' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099
          ImageIndex = 1
          object pTSertTtl: TPanel
            Left = 0
            Top = 0
            Width = 800
            Height = 26
            Align = alTop
            BevelKind = bkFlat
            BorderStyle = bsSingle
            Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072' '#1076#1072#1090#1095#1080#1082#1086#1074' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099' '#1087#1086' '#1087#1086#1079'. '#1040
            Color = clMedGray
            ParentBackground = False
            TabOrder = 0
          end
          object gbTSertA: TGroupBox
            Left = 0
            Top = 26
            Width = 800
            Height = 544
            Align = alClient
            Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072' '#1087#1086#1079'. '#1040
            TabOrder = 1
            object lblCalcLimitsA: TLabel
              Left = 30
              Top = 44
              Width = 142
              Height = 14
              Caption = #1056#1072#1089#1089#1095#1080#1090#1072#1085#1085#1099#1077' '#1087#1088#1077#1076#1077#1083#1099': '
            end
            object lblLowA: TLabel
              Left = 178
              Top = 21
              Width = 54
              Height = 14
              Caption = #1053#1080#1078#1085#1080#1081': '
            end
            object lblHighA: TLabel
              Left = 258
              Top = 21
              Width = 56
              Height = 14
              Caption = #1042#1077#1088#1093#1085#1080#1081': '
            end
            object lblTLoadedLimitsA: TLabel
              Left = 34
              Top = 72
              Width = 138
              Height = 14
              Caption = #1047#1072#1075#1088#1091#1078#1072#1077#1084#1099#1077' '#1087#1088#1077#1076#1077#1083#1099': '
            end
            object edCalcLowLimitA: TEdit
              Left = 178
              Top = 41
              Width = 54
              Height = 22
              ReadOnly = True
              TabOrder = 0
              Text = '0.0'
            end
            object edCalcUpLimitA: TEdit
              Left = 258
              Top = 41
              Width = 56
              Height = 22
              ReadOnly = True
              TabOrder = 1
              Text = '0.0'
            end
            object edLoadedLowLimitA: TEdit
              Left = 178
              Top = 69
              Width = 54
              Height = 22
              TabOrder = 2
              Text = '-50.00'
            end
            object edLoadedUpLimitA: TEdit
              Left = 258
              Top = 69
              Width = 56
              Height = 22
              TabOrder = 3
              Text = '150.00'
            end
            object btnLoadTLimitsA: TButton
              Left = 320
              Top = 28
              Width = 153
              Height = 65
              Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1091#1089#1090#1072#1085#1086#1074#1083#1077#1085#1085#1099#1077' '#1087#1088#1077#1076#1077#1083#1099' '#1074' '#1082#1086#1085#1090#1088#1086#1083#1083#1077#1088
              TabOrder = 4
              WordWrap = True
              OnClick = OnTLimitsLoadToPLC
            end
          end
        end
        object tsLoadSert: TTabSheet
          Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072' '#1090#1077#1085#1079#1086#1076#1072#1090#1095#1080#1082#1086#1074
          ImageIndex = 2
          object pcLoadSert: TPageControl
            Left = 0
            Top = 0
            Width = 800
            Height = 570
            ActivePage = tsLoadSertA
            Align = alClient
            TabOrder = 0
            object tsLoadSertA: TTabSheet
              Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072' '#1090#1077#1085#1079#1086#1076#1072#1090#1095#1080#1082#1072' '#1087#1086#1079'. '#1040
              object pLoadSertATtl: TPanel
                Left = 0
                Top = 0
                Width = 792
                Height = 20
                Align = alTop
                BevelKind = bkFlat
                BorderStyle = bsSingle
                Caption = #1054#1087#1088#1077#1076#1077#1083#1077#1085#1080#1077' '#1087#1086#1087#1088#1072#1074#1086#1095#1085#1099#1093' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090#1086#1074' '#1090#1077#1085#1079#1086#1076#1072#1090#1095#1080#1082#1086#1074' '#1089#1090#1086#1088#1086#1085#1072' '#1040
                Color = clMedGray
                ParentBackground = False
                TabOrder = 0
              end
              object sgLoadSertA: TStringGrid
                Left = 0
                Top = 20
                Width = 328
                Height = 521
                Align = alLeft
                RowCount = 40
                ScrollBars = ssVertical
                TabOrder = 1
                OnDrawCell = OnCalibrDrawCell
                OnExit = OnStringGridExit
                OnKeyPress = OnSGKeyPress
                OnSelectCell = OnSGSelectCell
                ColWidths = (
                  64
                  64
                  64
                  64
                  64)
                RowHeights = (
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24
                  24)
              end
              object btnPrevSertLoadA: TButton
                Left = 466
                Top = 44
                Width = 192
                Height = 38
                Caption = #1055#1088#1077#1076#1099#1076#1091#1097#1077#1077' '#1079#1072#1076#1072#1085#1080#1077
                TabOrder = 2
                WordWrap = True
                OnClick = OnPrevSertLoadBtn
              end
              object leCurrentLoadSertSetA: TLabeledEdit
                Left = 462
                Top = 105
                Width = 64
                Height = 19
                AutoSize = False
                EditLabel.Width = 47
                EditLabel.Height = 13
                EditLabel.BiDiMode = bdLeftToRight
                EditLabel.Caption = #1047#1072#1076#1072#1085#1080#1077':'
                EditLabel.Font.Charset = DEFAULT_CHARSET
                EditLabel.Font.Color = clWindowText
                EditLabel.Font.Height = -11
                EditLabel.Font.Name = 'Tahoma'
                EditLabel.Font.Style = []
                EditLabel.ParentBiDiMode = False
                EditLabel.ParentFont = False
                EditLabel.Layout = tlCenter
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
                ReadOnly = True
                TabOrder = 3
                Text = '150.00'
              end
              object leReadLoadSertA: TLabeledEdit
                Left = 530
                Top = 105
                Width = 64
                Height = 19
                AutoSize = False
                BiDiMode = bdLeftToRight
                EditLabel.Width = 58
                EditLabel.Height = 13
                EditLabel.BiDiMode = bdLeftToRight
                EditLabel.Caption = #1055#1086#1082#1072#1079#1072#1085#1080#1077':'
                EditLabel.Font.Charset = DEFAULT_CHARSET
                EditLabel.Font.Color = clWindowText
                EditLabel.Font.Height = -11
                EditLabel.Font.Name = 'Tahoma'
                EditLabel.Font.Style = []
                EditLabel.ParentBiDiMode = False
                EditLabel.ParentFont = False
                EditLabel.Layout = tlCenter
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentBiDiMode = False
                ParentFont = False
                ReadOnly = True
                TabOrder = 4
                Text = '150.00'
              end
              object leMeasLoadSertA: TLabeledEdit
                Left = 594
                Top = 105
                Width = 64
                Height = 19
                AutoSize = False
                BiDiMode = bdLeftToRight
                EditLabel.Width = 58
                EditLabel.Height = 13
                EditLabel.BiDiMode = bdLeftToRight
                EditLabel.Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077':'
                EditLabel.Font.Charset = DEFAULT_CHARSET
                EditLabel.Font.Color = clWindowText
                EditLabel.Font.Height = -11
                EditLabel.Font.Name = 'Tahoma'
                EditLabel.Font.Style = []
                EditLabel.ParentBiDiMode = False
                EditLabel.ParentFont = False
                EditLabel.Layout = tlCenter
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentBiDiMode = False
                ParentFont = False
                TabOrder = 5
                Text = '150.00'
                OnKeyPress = OnSGKeyPress
              end
              object btnNextSertLoadA: TButton
                Left = 466
                Top = 130
                Width = 192
                Height = 28
                Caption = #1057#1083#1077#1076#1091#1102#1097#1077#1077' '#1079#1072#1076#1072#1085#1080#1077
                TabOrder = 6
                WordWrap = True
                OnClick = OnNextSertLoadBtn
              end
              object btnSertPumpOnA: TButton
                Left = 487
                Top = 241
                Width = 155
                Height = 24
                Caption = #1042#1050#1051#1070#1063#1048#1058#1068' '#1053#1040#1057#1054#1057' '#1040', Ctrl+F1'
                TabOrder = 7
                OnClick = OnPump1On
              end
              object btnSertPumpOffA: TButton
                Left = 487
                Top = 271
                Width = 155
                Height = 24
                Caption = #1042#1067#1050#1051#1070#1063#1048#1058#1068' '#1053#1040#1057#1054#1057' '#1040', Ctrl+F2'
                TabOrder = 8
                OnClick = OnPump1Off
              end
              object btnLoadSertClearTableA: TButton
                Left = 679
                Top = 44
                Width = 122
                Height = 46
                Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
                TabOrder = 9
                WordWrap = True
                OnClick = OnLoadSertTableClear
              end
              object btnLoadSertCalcA: TButton
                Left = 679
                Top = 102
                Width = 122
                Height = 48
                Caption = #1056#1072#1089#1089#1095#1080#1090#1072#1090#1100' '#1087#1086#1087#1088#1072#1074#1086#1095#1085#1099#1081' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090
                TabOrder = 10
                WordWrap = True
                OnClick = OnLoadSertCalc
              end
              object btnLoadSertPrintProtA: TButton
                Left = 679
                Top = 156
                Width = 122
                Height = 45
                Action = acLoadSertPrintProtA
                Caption = #1056#1072#1089#1087#1077#1095#1072#1090#1072#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083
                TabOrder = 11
                WordWrap = True
              end
              object btnLoadSertAToPLC: TButton
                Left = 679
                Top = 208
                Width = 122
                Height = 45
                Hint = 'Save As|Saves the active file with a new name'
                Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090#1099' '#1074' '#1082#1086#1085#1090#1088#1086#1083#1083#1077#1088
                TabOrder = 12
                WordWrap = True
                OnClick = OnLoadSertToPLC
              end
              object btnResetCalibrCoeffA: TButton
                Left = 679
                Top = 333
                Width = 122
                Height = 45
                Hint = 'Save As|Saves the active file with a new name'
                Caption = #1057#1073#1088#1086#1089#1080#1090#1100' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090#1099' '#1074' '#1082#1086#1085#1090#1088#1086#1083#1083#1077#1088#1077
                TabOrder = 13
                WordWrap = True
                OnClick = OnLSertCoefReset
              end
              object btnUploadSertAFmPLC: TButton
                Left = 679
                Top = 269
                Width = 122
                Height = 45
                Hint = 'Save As|Saves the active file with a new name'
                Caption = #1055#1088#1086#1095#1080#1090#1072#1090#1100' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090#1099' '#1080#1079' '#1082#1086#1085#1090#1088#1086#1083#1083#1077#1088#1072
                TabOrder = 14
                WordWrap = True
                OnClick = OnUploadLSertFmPLC
              end
            end
          end
        end
        object tsRadSert: TTabSheet
          Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072' '#1076#1072#1090#1095#1080#1082#1072' '#1088#1072#1076#1080#1091#1089#1072
          ImageIndex = 3
          object leRShiftA: TLabeledEdit
            Left = 426
            Top = 32
            Width = 57
            Height = 20
            AutoSize = False
            BiDiMode = bdLeftToRight
            EditLabel.Width = 406
            EditLabel.Height = 14
            EditLabel.BiDiMode = bdLeftToRight
            EditLabel.Caption = #1057#1084#1077#1097#1077#1085#1080#1077' '#1087#1086#1082#1072#1079#1072#1085#1080#1081' '#1076#1072#1090#1095#1080#1082#1072' '#1080#1079#1084#1077#1088#1077#1085#1080#1103' '#1088#1072#1076#1080#1091#1089#1072' '#1076#1083#1103' '#1089#1090#1086#1088#1086#1085#1099' '#1040', '#1084#1084': '
            EditLabel.ParentBiDiMode = False
            EditLabel.Layout = tlCenter
            LabelPosition = lpLeft
            ParentBiDiMode = False
            TabOrder = 0
            Text = '0.00'
          end
          object btnRShiftALoadToPLC: TButton
            Left = 489
            Top = 32
            Width = 153
            Height = 41
            Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1089#1084#1077#1097#1077#1085#1080#1077' '#1087#1086' '#1089#1090#1086#1088#1086#1085#1077' '#1040' '#1074' '#1082#1086#1085#1090#1088#1086#1083#1083#1077#1088
            TabOrder = 1
            WordWrap = True
            OnClick = OnRShiftLoadToPLC
          end
          object pRSertTtl: TPanel
            Left = 0
            Top = 0
            Width = 800
            Height = 26
            Align = alTop
            BevelKind = bkFlat
            BorderStyle = bsSingle
            Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072' '#1076#1072#1090#1095#1080#1082#1086#1074' '#1080#1079#1084#1077#1088#1077#1085#1080#1103' '#1088#1072#1076#1080#1091#1089#1072' '#1087#1086' '#1087#1086#1079'. '#1040
            Color = clMedGray
            ParentBackground = False
            TabOrder = 2
          end
        end
      end
    end
    object tsLog: TTabSheet
      Caption = #1046#1091#1088#1085#1072#1083
      ImageIndex = 5
      object reLog: TRichEdit
        Left = 0
        Top = 0
        Width = 808
        Height = 599
        Align = alClient
        Color = clNone
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWhite
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Lines.Strings = (
          'reLog')
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
        Zoom = 100
      end
    end
  end
  object pnlCPU: TPanel
    Left = 816
    Top = 66
    Width = 200
    Height = 628
    Align = alRight
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 2
    object gbPosition1ControlBox: TGroupBox
      Left = 11
      Top = 10
      Width = 180
      Height = 279
      Caption = #1055#1086#1079#1080#1094#1080#1103' '#1040
      TabOrder = 0
      object gbSensors1: TGroupBox
        Left = 11
        Top = 144
        Width = 160
        Height = 125
        Caption = #1044#1072#1090#1095#1080#1082#1080
        TabOrder = 0
        object IndBlowout1: TEdit
          Left = 8
          Top = 47
          Width = 143
          Height = 22
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          ReadOnly = True
          TabOrder = 0
          Text = #1056#1040#1047#1056#1067#1042
        end
        object IndGuardrail1: TEdit
          Left = 8
          Top = 23
          Width = 143
          Height = 22
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          ReadOnly = True
          TabOrder = 1
          Text = #1054#1043#1056#1040#1046#1044#1045#1053#1048#1045
        end
        object IndDestroyLateral1: TEdit
          Left = 8
          Top = 71
          Width = 143
          Height = 22
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          ReadOnly = True
          TabOrder = 2
          Text = #1056#1040#1047#1056#1067#1042' '#1041#1054#1050#1054#1042#1054#1049
        end
        object IndDestroyRunning1: TEdit
          Left = 8
          Top = 95
          Width = 143
          Height = 22
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          ReadOnly = True
          TabOrder = 3
          Text = #1056#1040#1047#1056#1067#1042' '#1041#1045#1043#1054#1042#1054#1049
        end
      end
      object rgPos1Mode: TGroupBox
        Left = 10
        Top = 20
        Width = 160
        Height = 50
        Hint = #1056#1077#1078#1080#1084' '#1088#1072#1073#1086#1090#1099' '#1087#1086#1079#1080#1094#1080#1080' '#1040
        Caption = #1056#1077#1078#1080#1084
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        object sbAutomatA: TSpeedButton
          Left = 80
          Top = 19
          Width = 26
          Height = 26
          AllowAllUp = True
          GroupIndex = 1
          Glyph.Data = {
            36080000424D3608000000000000360400002800000040000000100000000100
            08000000000000040000C40E0000C40E00000001000000000000000000000000
            80000080000000808000800000008000800080800000C0C0C000C0DCC000F0CA
            A6000020400000206000002080000020A0000020C0000020E000004000000040
            20000040400000406000004080000040A0000040C0000040E000006000000060
            20000060400000606000006080000060A0000060C0000060E000008000000080
            20000080400000806000008080000080A0000080C0000080E00000A0000000A0
            200000A0400000A0600000A0800000A0A00000A0C00000A0E00000C0000000C0
            200000C0400000C0600000C0800000C0A00000C0C00000C0E00000E0000000E0
            200000E0400000E0600000E0800000E0A00000E0C00000E0E000400000004000
            20004000400040006000400080004000A0004000C0004000E000402000004020
            20004020400040206000402080004020A0004020C0004020E000404000004040
            20004040400040406000404080004040A0004040C0004040E000406000004060
            20004060400040606000406080004060A0004060C0004060E000408000004080
            20004080400040806000408080004080A0004080C0004080E00040A0000040A0
            200040A0400040A0600040A0800040A0A00040A0C00040A0E00040C0000040C0
            200040C0400040C0600040C0800040C0A00040C0C00040C0E00040E0000040E0
            200040E0400040E0600040E0800040E0A00040E0C00040E0E000800000008000
            20008000400080006000800080008000A0008000C0008000E000802000008020
            20008020400080206000802080008020A0008020C0008020E000804000008040
            20008040400080406000804080008040A0008040C0008040E000806000008060
            20008060400080606000806080008060A0008060C0008060E000808000008080
            20008080400080806000808080008080A0008080C0008080E00080A0000080A0
            200080A0400080A0600080A0800080A0A00080A0C00080A0E00080C0000080C0
            200080C0400080C0600080C0800080C0A00080C0C00080C0E00080E0000080E0
            200080E0400080E0600080E0800080E0A00080E0C00080E0E000C0000000C000
            2000C0004000C0006000C0008000C000A000C000C000C000E000C0200000C020
            2000C0204000C0206000C0208000C020A000C020C000C020E000C0400000C040
            2000C0404000C0406000C0408000C040A000C040C000C040E000C0600000C060
            2000C0604000C0606000C0608000C060A000C060C000C060E000C0800000C080
            2000C0804000C0806000C0808000C080A000C080C000C080E000C0A00000C0A0
            2000C0A04000C0A06000C0A08000C0A0A000C0A0C000C0A0E000C0C00000C0C0
            2000C0C04000C0C06000C0C08000C0C0A000F0FBFF00A4A0A000808080000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00030303030303
            0303030303030303030303030303030303030303030303030303030303030303
            0303030303030303030303030303030303030303030303030303030303030300
            0000000003030303030303030303039B9B9B9B9B030303030303030303030300
            0000000003030303030303030303030000000000030303030303030303000007
            07A4A4A40000030303030303039B9BFFFF0707079B9B03030303030303000007
            07A4A4A400000303030303030300000707A4A4A40000030303030303000707A4
            000000A4A4A40003030303039BFFFF079B9B9B0707079B0303030303000707A4
            000000A4A4A4000303030303000707A4000000A4A4A4000303030300070700A7
            A7A7A7A700A4A4000303039BFFFF9BFFFFFFFFFF9B07079B03030300070700BC
            BCBCBCBC00A4A40003030300070700BCBCBCBCBC00A4A400030303000700A700
            00000000A700A4000303039BFF9BFF9B9B9B9B9BFF9B079B030303000700BC00
            00000000BC00A400030303000700BC0000000000BC00A40003030007A4A70000
            F901010000A7A4A400039BFF07FF9B9B07F7F79B9BFF07079B030007A4BC0000
            FA02020000BCA4A400030007A4BC0000FA02020000BCA4A40003000700A700F9
            01F9010100A700A400039BFF9BFF9B07F707F7F79BFF9B079B03000700BC00FA
            02FA020200BC00A40003000700BC00FA02FA020200BC00A4000300FF00A700F9
            F9F9F90100A700A400039BFF9BFF9B07070707F79BFF9B079B0300FF00BC00FA
            FAFAFA0200BC00A4000300FF00BC00FAFAFAFA0200BC00A4000300FF00A700FF
            F9F901F900A7000700039BFF9BFF9BFF0707F7079BFF9BFF9B0300FF00BC00FF
            FAFA02FA00BC0007000300FF00BC00FFFAFA02FA00BC0007000300FFA4A70000
            FFFFF90000A7A40700039BFF07FF9B9BFFFF079B9BFF07FF9B0300FFA4BC0000
            FFFFFA0000BCA407000300FFA4BC0000FFFFFA0000BCA407000303000700A700
            00000000A70007000303039BFF9BFF9B9B9B9B9BFF9BFF9B030303000700BC00
            00000000BC000700030303000700BC0000000000BC00070003030300FF0700A7
            A7A7A7A7000707000303039BFFFF9BFFFFFFFFFF9BFFFF9B03030300FF0700BC
            BCBCBCBC0007070003030300FF0700BCBCBCBCBC000707000303030300FF07A4
            000000A407070003030303039BFFFF079B9B9B07FFFF9B030303030300FF07A4
            000000A4070700030303030300FF07A4000000A40707000303030303030000FF
            FFFF07070000030303030303039B9BFFFFFFFFFF9B9B030303030303030000FF
            FFFF07070000030303030303030000FFFFFF0707000003030303030303030300
            0000000003030303030303030303039B9B9B9B9B030303030303030303030300
            0000000003030303030303030303030000000000030303030303}
          NumGlyphs = 4
          OnClick = OnRGPos1ModeClick
        end
        object sbManualA: TSpeedButton
          Left = 3
          Top = 19
          Width = 26
          Height = 26
          AllowAllUp = True
          GroupIndex = 1
          Down = True
          Glyph.Data = {
            36080000424D3608000000000000360400002800000040000000100000000100
            08000000000000040000C40E0000C40E00000001000000000000000000000000
            80000080000000808000800000008000800080800000C0C0C000C0DCC000F0CA
            A6000020400000206000002080000020A0000020C0000020E000004000000040
            20000040400000406000004080000040A0000040C0000040E000006000000060
            20000060400000606000006080000060A0000060C0000060E000008000000080
            20000080400000806000008080000080A0000080C0000080E00000A0000000A0
            200000A0400000A0600000A0800000A0A00000A0C00000A0E00000C0000000C0
            200000C0400000C0600000C0800000C0A00000C0C00000C0E00000E0000000E0
            200000E0400000E0600000E0800000E0A00000E0C00000E0E000400000004000
            20004000400040006000400080004000A0004000C0004000E000402000004020
            20004020400040206000402080004020A0004020C0004020E000404000004040
            20004040400040406000404080004040A0004040C0004040E000406000004060
            20004060400040606000406080004060A0004060C0004060E000408000004080
            20004080400040806000408080004080A0004080C0004080E00040A0000040A0
            200040A0400040A0600040A0800040A0A00040A0C00040A0E00040C0000040C0
            200040C0400040C0600040C0800040C0A00040C0C00040C0E00040E0000040E0
            200040E0400040E0600040E0800040E0A00040E0C00040E0E000800000008000
            20008000400080006000800080008000A0008000C0008000E000802000008020
            20008020400080206000802080008020A0008020C0008020E000804000008040
            20008040400080406000804080008040A0008040C0008040E000806000008060
            20008060400080606000806080008060A0008060C0008060E000808000008080
            20008080400080806000808080008080A0008080C0008080E00080A0000080A0
            200080A0400080A0600080A0800080A0A00080A0C00080A0E00080C0000080C0
            200080C0400080C0600080C0800080C0A00080C0C00080C0E00080E0000080E0
            200080E0400080E0600080E0800080E0A00080E0C00080E0E000C0000000C000
            2000C0004000C0006000C0008000C000A000C000C000C000E000C0200000C020
            2000C0204000C0206000C0208000C020A000C020C000C020E000C0400000C040
            2000C0404000C0406000C0408000C040A000C040C000C040E000C0600000C060
            2000C0604000C0606000C0608000C060A000C060C000C060E000C0800000C080
            2000C0804000C0806000C0808000C080A000C080C000C080E000C0A00000C0A0
            2000C0A04000C0A06000C0A08000C0A0A000C0A0C000C0A0E000C0C00000C0C0
            2000C0C04000C0C06000C0C08000C0C0A000F0FBFF00A4A0A000808080000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00030303030303
            0303030303030303030303030303030303030303030303030303030303030303
            0303030303030303030303030303030303030303030303030303030303030300
            0000000003030303030303030303039B9B9B9B9B030303030303030303030300
            0000000003030303030303030303030000000000030303030303030303000007
            07A4A4A40000030303030303039B9BFFFF0707079B9B03030303030303000007
            07A4A4A400000303030303030300000707A4A4A40000030303030303000707A4
            000000A4A4A40003030303039BFFFF079B9B9B0707079B0303030303000707A4
            000000A4A4A4000303030303000707A4000000A4A4A4000303030300070700A7
            A7A7A7A700A4A4000303039BFFFF9BFFFFFFFFFF9B07079B03030300070700BC
            BCBCBCBC00A4A40003030300070700BCBCBCBCBC00A4A400030303000700A700
            00000000A700A4000303039BFF9BFF9B9B9B9B9BFF9B079B030303000700BC00
            00000000BC00A400030303000700BC0000000000BC00A40003030007A4A70000
            F901010000A7A4A400039BFF07FF9B9B07F7F79B9BFF07079B030007A4BC0000
            FA02020000BCA4A400030007A4BC0000FA02020000BCA4A40003000700A700F9
            01F9010100A700A400039BFF9BFF9B07F707F7F79BFF9B079B03000700BC00FA
            02FA020200BC00A40003000700BC00FA02FA020200BC00A4000300FF00A700F9
            F9F9F90100A700A400039BFF9BFF9B07070707F79BFF9B079B0300FF00BC00FA
            FAFAFA0200BC00A4000300FF00BC00FAFAFAFA0200BC00A4000300FF00A700FF
            F9F901F900A7000700039BFF9BFF9BFF0707F7079BFF9BFF9B0300FF00BC00FF
            FAFA02FA00BC0007000300FF00BC00FFFAFA02FA00BC0007000300FFA4A70000
            FFFFF90000A7A40700039BFF07FF9B9BFFFF079B9BFF07FF9B0300FFA4BC0000
            FFFFFA0000BCA407000300FFA4BC0000FFFFFA0000BCA407000303000700A700
            00000000A70007000303039BFF9BFF9B9B9B9B9BFF9BFF9B030303000700BC00
            00000000BC000700030303000700BC0000000000BC00070003030300FF0700A7
            A7A7A7A7000707000303039BFFFF9BFFFFFFFFFF9BFFFF9B03030300FF0700BC
            BCBCBCBC0007070003030300FF0700BCBCBCBCBC000707000303030300FF07A4
            000000A407070003030303039BFFFF079B9B9B07FFFF9B030303030300FF07A4
            000000A4070700030303030300FF07A4000000A40707000303030303030000FF
            FFFF07070000030303030303039B9BFFFFFFFFFF9B9B030303030303030000FF
            FFFF07070000030303030303030000FFFFFF0707000003030303030303030300
            0000000003030303030303030303039B9B9B9B9B030303030303030303030300
            0000000003030303030303030303030000000000030303030303}
          NumGlyphs = 4
          OnClick = OnRGPos1ModeClick
        end
        object Label3: TLabel
          Left = 34
          Top = 24
          Width = 41
          Height = 14
          Caption = #1056#1091#1095#1085#1086#1081
        end
        object Label4: TLabel
          Left = 110
          Top = 23
          Width = 47
          Height = 14
          Caption = #1040#1074#1090#1086#1084#1072#1090
        end
      end
      object rgPos1StartStop: TGroupBox
        Left = 10
        Top = 73
        Width = 160
        Height = 54
        Hint = #1047#1072#1087#1091#1089#1082' '#1089#1090#1077#1085#1076#1072' '#1087#1086#1079#1080#1094#1080#1103' '#1040
        Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        object sbStartA: TSpeedButton
          Left = 80
          Top = 19
          Width = 26
          Height = 26
          AllowAllUp = True
          GroupIndex = 1
          Glyph.Data = {
            36080000424D3608000000000000360400002800000040000000100000000100
            08000000000000040000C40E0000C40E00000001000000000000000000000000
            80000080000000808000800000008000800080800000C0C0C000C0DCC000F0CA
            A6000020400000206000002080000020A0000020C0000020E000004000000040
            20000040400000406000004080000040A0000040C0000040E000006000000060
            20000060400000606000006080000060A0000060C0000060E000008000000080
            20000080400000806000008080000080A0000080C0000080E00000A0000000A0
            200000A0400000A0600000A0800000A0A00000A0C00000A0E00000C0000000C0
            200000C0400000C0600000C0800000C0A00000C0C00000C0E00000E0000000E0
            200000E0400000E0600000E0800000E0A00000E0C00000E0E000400000004000
            20004000400040006000400080004000A0004000C0004000E000402000004020
            20004020400040206000402080004020A0004020C0004020E000404000004040
            20004040400040406000404080004040A0004040C0004040E000406000004060
            20004060400040606000406080004060A0004060C0004060E000408000004080
            20004080400040806000408080004080A0004080C0004080E00040A0000040A0
            200040A0400040A0600040A0800040A0A00040A0C00040A0E00040C0000040C0
            200040C0400040C0600040C0800040C0A00040C0C00040C0E00040E0000040E0
            200040E0400040E0600040E0800040E0A00040E0C00040E0E000800000008000
            20008000400080006000800080008000A0008000C0008000E000802000008020
            20008020400080206000802080008020A0008020C0008020E000804000008040
            20008040400080406000804080008040A0008040C0008040E000806000008060
            20008060400080606000806080008060A0008060C0008060E000808000008080
            20008080400080806000808080008080A0008080C0008080E00080A0000080A0
            200080A0400080A0600080A0800080A0A00080A0C00080A0E00080C0000080C0
            200080C0400080C0600080C0800080C0A00080C0C00080C0E00080E0000080E0
            200080E0400080E0600080E0800080E0A00080E0C00080E0E000C0000000C000
            2000C0004000C0006000C0008000C000A000C000C000C000E000C0200000C020
            2000C0204000C0206000C0208000C020A000C020C000C020E000C0400000C040
            2000C0404000C0406000C0408000C040A000C040C000C040E000C0600000C060
            2000C0604000C0606000C0608000C060A000C060C000C060E000C0800000C080
            2000C0804000C0806000C0808000C080A000C080C000C080E000C0A00000C0A0
            2000C0A04000C0A06000C0A08000C0A0A000C0A0C000C0A0E000C0C00000C0C0
            2000C0C04000C0C06000C0C08000C0C0A000F0FBFF00A4A0A000808080000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00030303030303
            0303030303030303030303030303030303030303030303030303030303030303
            0303030303030303030303030303030303030303030303030303030303030300
            0000000003030303030303030303039B9B9B9B9B030303030303030303030300
            0000000003030303030303030303030000000000030303030303030303000007
            07A4A4A40000030303030303039B9BFFFF0707079B9B03030303030303000007
            07A4A4A400000303030303030300000707A4A4A40000030303030303000707A4
            000000A4A4A40003030303039BFFFF079B9B9B0707079B0303030303000707A4
            000000A4A4A4000303030303000707A4000000A4A4A4000303030300070700A7
            A7A7A7A700A4A4000303039BFFFF9BFFFFFFFFFF9B07079B03030300070700BC
            BCBCBCBC00A4A40003030300070700BCBCBCBCBC00A4A400030303000700A700
            00000000A700A4000303039BFF9BFF9B9B9B9B9BFF9B079B030303000700BC00
            00000000BC00A400030303000700BC0000000000BC00A40003030007A4A70000
            F901010000A7A4A400039BFF07FF9B9B07F7F79B9BFF07079B030007A4BC0000
            FA02020000BCA4A400030007A4BC0000FA02020000BCA4A40003000700A700F9
            01F9010100A700A400039BFF9BFF9B07F707F7F79BFF9B079B03000700BC00FA
            02FA020200BC00A40003000700BC00FA02FA020200BC00A4000300FF00A700F9
            F9F9F90100A700A400039BFF9BFF9B07070707F79BFF9B079B0300FF00BC00FA
            FAFAFA0200BC00A4000300FF00BC00FAFAFAFA0200BC00A4000300FF00A700FF
            F9F901F900A7000700039BFF9BFF9BFF0707F7079BFF9BFF9B0300FF00BC00FF
            FAFA02FA00BC0007000300FF00BC00FFFAFA02FA00BC0007000300FFA4A70000
            FFFFF90000A7A40700039BFF07FF9B9BFFFF079B9BFF07FF9B0300FFA4BC0000
            FFFFFA0000BCA407000300FFA4BC0000FFFFFA0000BCA407000303000700A700
            00000000A70007000303039BFF9BFF9B9B9B9B9BFF9BFF9B030303000700BC00
            00000000BC000700030303000700BC0000000000BC00070003030300FF0700A7
            A7A7A7A7000707000303039BFFFF9BFFFFFFFFFF9BFFFF9B03030300FF0700BC
            BCBCBCBC0007070003030300FF0700BCBCBCBCBC000707000303030300FF07A4
            000000A407070003030303039BFFFF079B9B9B07FFFF9B030303030300FF07A4
            000000A4070700030303030300FF07A4000000A40707000303030303030000FF
            FFFF07070000030303030303039B9BFFFFFFFFFF9B9B030303030303030000FF
            FFFF07070000030303030303030000FFFFFF0707000003030303030303030300
            0000000003030303030303030303039B9B9B9B9B030303030303030303030300
            0000000003030303030303030303030000000000030303030303}
          NumGlyphs = 4
          OnClick = OnRGPos1StartStopClick
        end
        object sbStopA: TSpeedButton
          Left = 3
          Top = 19
          Width = 26
          Height = 26
          AllowAllUp = True
          GroupIndex = 1
          Down = True
          Glyph.Data = {
            36080000424D3608000000000000360400002800000040000000100000000100
            08000000000000040000C40E0000C40E00000001000000000000000000000000
            80000080000000808000800000008000800080800000C0C0C000C0DCC000F0CA
            A6000020400000206000002080000020A0000020C0000020E000004000000040
            20000040400000406000004080000040A0000040C0000040E000006000000060
            20000060400000606000006080000060A0000060C0000060E000008000000080
            20000080400000806000008080000080A0000080C0000080E00000A0000000A0
            200000A0400000A0600000A0800000A0A00000A0C00000A0E00000C0000000C0
            200000C0400000C0600000C0800000C0A00000C0C00000C0E00000E0000000E0
            200000E0400000E0600000E0800000E0A00000E0C00000E0E000400000004000
            20004000400040006000400080004000A0004000C0004000E000402000004020
            20004020400040206000402080004020A0004020C0004020E000404000004040
            20004040400040406000404080004040A0004040C0004040E000406000004060
            20004060400040606000406080004060A0004060C0004060E000408000004080
            20004080400040806000408080004080A0004080C0004080E00040A0000040A0
            200040A0400040A0600040A0800040A0A00040A0C00040A0E00040C0000040C0
            200040C0400040C0600040C0800040C0A00040C0C00040C0E00040E0000040E0
            200040E0400040E0600040E0800040E0A00040E0C00040E0E000800000008000
            20008000400080006000800080008000A0008000C0008000E000802000008020
            20008020400080206000802080008020A0008020C0008020E000804000008040
            20008040400080406000804080008040A0008040C0008040E000806000008060
            20008060400080606000806080008060A0008060C0008060E000808000008080
            20008080400080806000808080008080A0008080C0008080E00080A0000080A0
            200080A0400080A0600080A0800080A0A00080A0C00080A0E00080C0000080C0
            200080C0400080C0600080C0800080C0A00080C0C00080C0E00080E0000080E0
            200080E0400080E0600080E0800080E0A00080E0C00080E0E000C0000000C000
            2000C0004000C0006000C0008000C000A000C000C000C000E000C0200000C020
            2000C0204000C0206000C0208000C020A000C020C000C020E000C0400000C040
            2000C0404000C0406000C0408000C040A000C040C000C040E000C0600000C060
            2000C0604000C0606000C0608000C060A000C060C000C060E000C0800000C080
            2000C0804000C0806000C0808000C080A000C080C000C080E000C0A00000C0A0
            2000C0A04000C0A06000C0A08000C0A0A000C0A0C000C0A0E000C0C00000C0C0
            2000C0C04000C0C06000C0C08000C0C0A000F0FBFF00A4A0A000808080000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00030303030303
            0303030303030303030303030303030303030303030303030303030303030303
            0303030303030303030303030303030303030303030303030303030303030300
            0000000003030303030303030303039B9B9B9B9B030303030303030303030300
            0000000003030303030303030303030000000000030303030303030303000007
            07A4A4A40000030303030303039B9BFFFF0707079B9B03030303030303000007
            07A4A4A400000303030303030300000707A4A4A40000030303030303000707A4
            000000A4A4A40003030303039BFFFF079B9B9B0707079B0303030303000707A4
            000000A4A4A4000303030303000707A4000000A4A4A4000303030300070700A7
            A7A7A7A700A4A4000303039BFFFF9BFFFFFFFFFF9B07079B03030300070700BC
            BCBCBCBC00A4A40003030300070700BCBCBCBCBC00A4A400030303000700A700
            00000000A700A4000303039BFF9BFF9B9B9B9B9BFF9B079B030303000700BC00
            00000000BC00A400030303000700BC0000000000BC00A40003030007A4A70000
            F901010000A7A4A400039BFF07FF9B9B07F7F79B9BFF07079B030007A4BC0000
            FA02020000BCA4A400030007A4BC0000FA02020000BCA4A40003000700A700F9
            01F9010100A700A400039BFF9BFF9B07F707F7F79BFF9B079B03000700BC00FA
            02FA020200BC00A40003000700BC00FA02FA020200BC00A4000300FF00A700F9
            F9F9F90100A700A400039BFF9BFF9B07070707F79BFF9B079B0300FF00BC00FA
            FAFAFA0200BC00A4000300FF00BC00FAFAFAFA0200BC00A4000300FF00A700FF
            F9F901F900A7000700039BFF9BFF9BFF0707F7079BFF9BFF9B0300FF00BC00FF
            FAFA02FA00BC0007000300FF00BC00FFFAFA02FA00BC0007000300FFA4A70000
            FFFFF90000A7A40700039BFF07FF9B9BFFFF079B9BFF07FF9B0300FFA4BC0000
            FFFFFA0000BCA407000300FFA4BC0000FFFFFA0000BCA407000303000700A700
            00000000A70007000303039BFF9BFF9B9B9B9B9BFF9BFF9B030303000700BC00
            00000000BC000700030303000700BC0000000000BC00070003030300FF0700A7
            A7A7A7A7000707000303039BFFFF9BFFFFFFFFFF9BFFFF9B03030300FF0700BC
            BCBCBCBC0007070003030300FF0700BCBCBCBCBC000707000303030300FF07A4
            000000A407070003030303039BFFFF079B9B9B07FFFF9B030303030300FF07A4
            000000A4070700030303030300FF07A4000000A40707000303030303030000FF
            FFFF07070000030303030303039B9BFFFFFFFFFF9B9B030303030303030000FF
            FFFF07070000030303030303030000FFFFFF0707000003030303030303030300
            0000000003030303030303030303039B9B9B9B9B030303030303030303030300
            0000000003030303030303030303030000000000030303030303}
          NumGlyphs = 4
          OnClick = OnRGPos1StartStopClick
        end
        object Label5: TLabel
          Left = 35
          Top = 25
          Width = 27
          Height = 14
          Caption = #1057#1090#1086#1087
        end
        object Label6: TLabel
          Left = 110
          Top = 25
          Width = 32
          Height = 14
          Caption = #1057#1090#1072#1088#1090
        end
      end
      object cbControlLateralA: TCheckBox
        Left = 18
        Top = 128
        Width = 143
        Height = 17
        Caption = #1050#1086#1085#1090#1088#1086#1083#1100' '#1073#1086#1082#1086#1074#1086#1081
        TabOrder = 3
        OnClick = cbControlLateralAClick
      end
    end
    object btnGeneralStop: TButton
      Left = 6
      Top = 295
      Width = 180
      Height = 22
      Caption = #1054#1041#1065#1048#1049' '#1057#1058#1054#1055', CTRL + F12'
      TabOrder = 1
      OnClick = OnGeneralStop
    end
  end
  object ammbRB: TActionMainMenuBar
    Left = 0
    Top = 0
    Width = 1016
    Height = 25
    UseSystemFont = False
    ActionManager = amRB
    Caption = 'ActionMainMenuBar'
    ColorMap.HighlightColor = clWhite
    ColorMap.BtnSelectedColor = clBtnFace
    ColorMap.UnusedColor = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    Spacing = 0
  end
  object gbOil: TGroupBox
    Left = 0
    Top = 25
    Width = 1016
    Height = 41
    Align = alTop
    Caption = #1044#1072#1090#1095#1080#1082#1080' '#1084#1072#1089#1083#1072
    TabOrder = 4
    DesignSize = (
      1016
      41)
    object Label1: TLabel
      Left = 10
      Top = 21
      Width = 75
      Height = 14
      Caption = #1058#1077#1084#1087#1077#1088#1072#1090#1091#1088#1072
    end
    object Label2: TLabel
      Left = 140
      Top = 21
      Width = 27
      Height = 14
      Caption = #1075#1088'. '#1057
    end
    object TreadCounter: TLabel
      Left = 532
      Top = 21
      Width = 4
      Height = 14
    end
    object IndOilLvl: TEdit
      Left = 173
      Top = 17
      Width = 121
      Height = 22
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      Text = #1059#1056#1054#1042#1045#1053#1068' '#1052#1040#1057#1051#1040
    end
    object IndlOilFilter: TEdit
      Left = 300
      Top = 17
      Width = 61
      Height = 22
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
      Text = #1060#1048#1051#1068#1058#1056
    end
    object IndDriveDrum: TEdit
      Left = 367
      Top = 17
      Width = 154
      Height = 22
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
      Text = #1044#1042#1048#1043#1040#1058#1045#1051#1068' '#1041#1040#1056#1040#1041#1040#1053#1040
    end
    object eOilTemp: TEdit
      Left = 91
      Top = 17
      Width = 43
      Height = 22
      CharCase = ecUpperCase
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      NumbersOnly = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 3
    end
    object eStendConnection: TEdit
      Left = 880
      Top = 17
      Width = 133
      Height = 22
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 4
      Text = #1057#1042#1071#1047#1068' '#1057#1054' '#1057#1058#1045#1053#1044#1054#1052
    end
  end
  object amRB: TActionManager
    ActionBars = <
      item
        Items = <
          item
            Items = <
              item
                Action = acTProgFileOpen
                ImageIndex = 7
              end
              item
                Action = acTProgFileSaveAs
                ImageIndex = 30
              end
              item
                Action = acSProgFileOpen
                ImageIndex = 7
              end
              item
                Action = acSProgFileSaveAs
                ImageIndex = 30
              end
              item
                Action = acProtTitleFileOpen
                ImageIndex = 7
                ShortCut = 16463
              end
              item
                Action = acProtTitleFileSaveAs
                ImageIndex = 30
              end
              item
                Action = Action1
              end
              item
                Action = acPrintSetup
              end
              item
                Action = acSettingsManagment
              end
              item
                Action = RBExit
                ImageIndex = 43
                ShortCut = 49240
              end>
            Caption = #1060#1072#1081#1083
          end
          item
            Items = <
              item
                Action = acOPCControlStart
                ShortCut = 16504
              end
              item
                Action = acOPCControlStop
                ShortCut = 16505
              end>
            Caption = #1057#1090#1077#1085#1076
          end
          item
            Items = <
              item
                Action = AboutProg
              end>
            Caption = #1055#1086#1084#1086#1097#1100
          end>
        ActionBar = ammbRB
      end>
    Left = 672
    StyleName = 'XP Style'
    object acTProgFileOpen: TFileOpen
      Category = #1060#1072#1081#1083
      Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1080#1079' '#1092#1072#1081#1083#1072' '#1087#1088#1086#1075#1088#1072#1084#1084#1091' '#1087#1086' '#1074#1088#1077#1084#1077#1085#1080
      Dialog.DefaultExt = 'tprg'
      Dialog.FileName = 'TProg1'
      Dialog.Filter = #1092#1072#1081#1083#1099' '#1087#1088#1086#1075#1088#1072#1084#1084' (*.tprg)|*.tprg|'#1074#1089#1077' '#1092#1072#1081#1083#1099'|*.*'
      Dialog.Title = #1059#1082#1072#1078#1080#1090#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1076#1083#1103' '#1079#1072#1075#1088#1091#1079#1082#1080' '#1087#1088#1086#1075#1088#1072#1084#1084#1091' '#1087#1086' '#1074#1088#1077#1084#1077#1085#1080':'
      Hint = 'Open|Opens an existing file'
      ImageIndex = 7
      OnAccept = OnTProgFileOpen
    end
    object acTProgFileSaveAs: TFileSaveAs
      Category = #1060#1072#1081#1083
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1092#1072#1081#1083#1077' '#1087#1088#1086#1075#1088#1072#1084#1084#1091' '#1087#1086' '#1074#1088#1077#1084#1077#1085#1080
      Dialog.DefaultExt = 'tprg'
      Dialog.FileName = 'TProg'
      Dialog.Filter = #1092#1072#1081#1083#1099' '#1087#1088#1086#1075#1088#1072#1084#1084' (*.tprg)|*.tprg|'#1074#1089#1077' '#1092#1072#1081#1083#1099'|*.*'
      Dialog.Title = #1059#1082#1072#1078#1080#1090#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1076#1083#1103' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1087#1088#1086#1075#1088#1072#1084#1084#1099' '#1087#1086' '#1074#1088#1077#1084#1077#1085#1080':'
      Hint = 'Save As|Saves the active file with a new name'
      ImageIndex = 30
      OnAccept = OnTProgFileSaveAs
    end
    object acSProgFileOpen: TFileOpen
      Category = #1060#1072#1081#1083
      Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1080#1079' '#1092#1072#1081#1083#1072' '#1087#1088#1086#1075#1088#1072#1084#1084#1091' '#1087#1086' '#1087#1091#1090#1080
      Dialog.DefaultExt = 'sprg'
      Dialog.FileName = 'SProg1'
      Dialog.Filter = #1092#1072#1081#1083#1099' '#1087#1088#1086#1075#1088#1072#1084#1084' (*.sprg)|*.sprg|'#1074#1089#1077' '#1092#1072#1081#1083#1099'|*.*'
      Dialog.Title = #1059#1082#1072#1078#1080#1090#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1076#1083#1103' '#1079#1072#1075#1088#1091#1079#1082#1080' '#1087#1088#1086#1075#1088#1072#1084#1084#1091' '#1087#1086' '#1087#1091#1090#1080':'
      Hint = 'Open|Opens an existing file'
      ImageIndex = 7
      OnAccept = OnSProgFileOpen
    end
    object acSProgFileSaveAs: TFileSaveAs
      Category = #1060#1072#1081#1083
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1092#1072#1081#1083#1077' '#1087#1088#1086#1075#1088#1072#1084#1084#1091' '#1087#1086' '#1087#1091#1090#1080
      Dialog.DefaultExt = 'sprg'
      Dialog.Filter = #1092#1072#1081#1083#1099' '#1087#1088#1086#1075#1088#1072#1084#1084' (*.sprg)|*.sprg|'#1074#1089#1077' '#1092#1072#1081#1083#1099'|*.*'
      Dialog.Title = #1059#1082#1072#1078#1080#1090#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1076#1083#1103' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1087#1088#1086#1075#1088#1072#1084#1084#1099' '#1087#1086' '#1087#1091#1090#1080':'
      Hint = 'Save As|Saves the active file with a new name'
      ImageIndex = 30
      OnAccept = OnSProgFileSaveAs
    end
    object acProtTitleFileOpen: TFileOpen
      Category = #1060#1072#1081#1083
      Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1080#1079' '#1092#1072#1081#1083#1072' '#1079#1072#1075#1086#1083#1086#1074#1086#1082' '#1087#1088#1086#1090#1086#1082#1086#1083#1072
      Dialog.DefaultExt = 'prottitle'
      Dialog.Filter = 
        #1092#1072#1081#1083#1099' '#1079#1072#1075#1086#1083#1086#1074#1082#1086#1074' '#1087#1088#1086#1090#1086#1082#1086#1083#1086#1074' (*.prottitle)|*.prottitle|'#1074#1089#1077' '#1092#1072#1081#1083#1099' ' +
        '(*.*)|*.*'
      Dialog.Title = #1059#1082#1072#1078#1080#1090#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1076#1083#1103' '#1079#1072#1075#1088#1091#1079#1082#1080' '#1079#1072#1075#1086#1083#1086#1074#1082#1072' '#1087#1088#1086#1090#1086#1082#1086#1083#1072
      Hint = 'Open|Opens an existing file'
      ImageIndex = 7
      ShortCut = 16463
      OnAccept = OnProtTtlFileOpen
    end
    object acProtTitleFileSaveAs: TFileSaveAs
      Category = #1060#1072#1081#1083
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1092#1072#1081#1083#1077' '#1079#1072#1075#1086#1083#1086#1074#1086#1082' '#1087#1088#1086#1090#1086#1082#1086#1083#1072
      Dialog.DefaultExt = 'prottitle'
      Dialog.FileName = 'Prot'
      Dialog.Filter = 
        #1092#1072#1081#1083#1099' '#1079#1072#1075#1086#1083#1086#1074#1082#1086#1074' '#1087#1088#1086#1090#1086#1082#1086#1083#1086#1074' (*.prottitle)|*.prottitle|'#1074#1089#1077' '#1092#1072#1081#1083#1099' ' +
        '(*.*)|*.*'
      Dialog.Title = #1059#1082#1072#1078#1080#1090#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1076#1083#1103' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1079#1072#1075#1086#1083#1086#1074#1082#1072' '#1087#1088#1086#1090#1086#1082#1086#1083#1072
      Hint = 'Save As|Saves the active file with a new name'
      ImageIndex = 30
      OnAccept = OnProtTtlFileSaveAs
    end
    object Action1: TAction
      Category = #1060#1072#1081#1083
      Caption = #1059#1089#1090#1072#1085#1086#1074#1082#1072' '#1092#1086#1085#1090#1072
      OnExecute = OnPrinterFontSelect
    end
    object acPrintSetup: TFilePrintSetup
      Category = #1060#1072#1081#1083
      Caption = #1059#1089#1090#1072#1085#1086#1074#1082#1072' '#1087#1088#1080#1085#1090#1077#1088#1072'...'
      Hint = #1059#1089#1090#1072#1085#1086#1074#1082#1072' '#1087#1088#1080#1085#1090#1077#1088#1072
    end
    object acSettingsManagment: TAction
      Category = #1060#1072#1081#1083
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
      OnExecute = acSettingsManagmentExecute
    end
    object RBExit: TFileExit
      Category = #1060#1072#1081#1083
      Caption = #1042#1099#1093#1086#1076
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
      ShortCut = 49240
    end
    object acOPCControlStart: TAction
      Category = #1057#1090#1077#1085#1076
      Caption = #1057#1090#1072#1088#1090' '#1091#1087#1088#1072#1074#1083#1077#1085#1080#1103
      ShortCut = 16504
      OnExecute = onOPCControlStartExec
    end
    object acOPCControlStop: TAction
      Category = #1057#1090#1077#1085#1076
      Caption = #1057#1090#1086#1087' '#1091#1087#1088#1072#1074#1083#1077#1085#1080#1103
      ShortCut = 16505
      OnExecute = OnOPCControlStopExec
    end
    object AboutProg: TAction
      Category = #1055#1086#1084#1086#1097#1100
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
    end
    object CommonParamRead: TAction
      Category = #1057#1090#1077#1085#1076
      Caption = #1063#1090#1077#1085#1080#1077' '#1086#1073#1097#1080#1093' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074
      OnExecute = OnCommonParamReadExec
    end
    object acPumpOnA: TAction
      Category = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
      Caption = #1042#1082#1083#1102#1095#1080#1090#1100' '#1085#1072#1089#1086#1089' '#1087#1086#1079'. '#1040
      ShortCut = 16496
      OnExecute = OnPump1On
    end
    object acPumpOffA: TAction
      Category = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
      Caption = #1042#1099#1082#1083#1102#1095#1080#1090#1100' '#1085#1072#1089#1086#1089' '#1087#1086#1079'. '#1040
      ShortCut = 16497
      OnExecute = OnPump1Off
    end
    object acCarriage1From: TAction
      Category = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
      Caption = #1050#1072#1088#1077#1090#1082#1072' '#1040' '#1086#1090' '#1073#1072#1088#1072#1073#1072#1085#1072
      ShortCut = 114
      OnExecute = OnCarriage1From
    end
    object acCarriage1Stop: TAction
      Category = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
      Caption = #1050#1072#1088#1077#1090#1082#1072' '#1040' '#1057#1090#1086#1087
      ShortCut = 115
      OnExecute = OnCarriage1Stop
    end
    object acCarriage1To: TAction
      Category = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
      Caption = #1050#1072#1088#1077#1090#1082#1072' '#1040' '#1082' '#1073#1072#1088#1072#1073#1072#1085#1091
      ShortCut = 116
      OnExecute = OnCarriage1To
    end
    object acDrumOn: TAction
      Category = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
      Caption = #1042#1082#1083#1102#1095#1080#1090#1100' '#1073#1072#1088#1072#1073#1072#1085
      ShortCut = 117
      OnExecute = OnDrumOn
    end
    object acDrumOff: TAction
      Category = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
      Caption = #1042#1099#1082#1083#1102#1095#1080#1090#1100' '#1073#1072#1088#1072#1073#1072#1085
      ShortCut = 118
      OnExecute = OnDrumOff
    end
    object acGeneralStop: TAction
      Category = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
      Caption = #1054#1073#1097#1080#1081' '#1089#1090#1086#1087
      ShortCut = 16507
      OnExecute = OnGeneralStop
    end
    object acLoadTestResFmPosA: TAction
      Category = #1057#1090#1077#1085#1076
      Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1099' '#1080#1089#1087#1099#1090#1072#1085#1080#1081' '#1087#1086' '#1087#1086#1079'. '#1040
      OnExecute = OnLoadTestResFmPosA
    end
    object acPrintProtPosAToFile: TFileSaveAs
      Category = #1055#1088#1086#1090#1086#1082#1086#1083#1099
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1080#1089#1087#1099#1090#1072#1085#1080#1081' '#1080#1079' '#1087#1086#1079'. '#1040
      Dialog.DefaultExt = 'prtprot'
      Dialog.FileName = 'Protocol'
      Dialog.Filter = #1092#1072#1081#1083#1099' '#1087#1088#1086#1090#1086#1082#1086#1083#1086#1074' (*.prtprot)|*.prtprot|'#1074#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
      Dialog.Title = #1042#1074#1077#1076#1080#1090#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1076#1083#1103' '#1087#1077#1095#1072#1090#1080' '#1087#1088#1086#1090#1086#1082#1086#1083#1072' '#1080#1089#1087#1099#1090#1072#1085#1080#1081':'
      Hint = 'Save As|Saves the active file with a new name'
      ImageIndex = 30
      OnAccept = OnPrintProtPosAToFile
    end
    object acPrintLoadCalibrProtA: TFileSaveAs
      Category = #1055#1088#1086#1090#1086#1082#1086#1083#1099
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1072#1090#1090#1077#1089#1090#1072#1094#1080#1080' '#1085#1072#1075#1088#1091#1079#1082#1080' '#1087#1086#1079'. '#1040
      Dialog.DefaultExt = 'lcprt'
      Dialog.FileName = 'LoadCalibrA'
      Dialog.Filter = 
        #1092#1072#1081#1083#1099' '#1087#1088#1086#1090#1086#1082#1086#1083#1086#1074' '#1072#1090#1090#1077#1089#1090#1072#1094#1080#1080' '#1085#1072#1075#1088#1091#1079#1082#1080' (*.lcprt)|*.lcprt|'#1074#1089#1077' '#1092#1072#1081#1083#1099 +
        ' (*.*)|*.*'
      Dialog.Title = 
        #1042#1074#1077#1076#1080#1090#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1076#1083#1103' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1087#1088#1086#1090#1086#1082#1086#1083#1072' '#1072#1090#1090#1077#1089#1090#1072#1094#1080#1080' '#1085#1072#1075#1088#1091#1079#1082#1080' '#1087 +
        #1086#1079'. '#1040':'
      Hint = 'Save As|Saves the active file with a new name'
      ImageIndex = 30
      OnAccept = OnPrintLoadCalibrProtA
    end
    object acLoadSertPrintProtA: TFileSaveAs
      Category = #1055#1088#1086#1090#1086#1082#1086#1083#1099
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1080' '#1090#1077#1085#1079#1086#1076#1072#1090#1095#1080#1082#1072' '#1087#1086#1079'. '#1040
      Dialog.DefaultExt = 'tcprt'
      Dialog.FileName = 'TensCalibrA'
      Dialog.Filter = 
        #1092#1072#1081#1083#1099' '#1087#1088#1086#1090#1086#1082#1086#1083#1086#1074' '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1080' '#1090#1077#1085#1079#1086#1076#1072#1090#1095#1080#1082#1086#1074'  (*.tcprt)|*.tcprt|'#1074#1089#1077 +
        ' '#1092#1072#1081#1083#1099' (*.*)|*.*'
      Dialog.Title = #1042#1074#1077#1076#1080#1090#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1080' '#1090#1077#1085#1079#1086#1076#1072#1090#1095#1080#1082#1072' '#1087#1086#1079'. '#1040':'
      Hint = 'Save As|Saves the active file with a new name'
      ImageIndex = 30
      OnAccept = OnPrintLoadSertProtA
    end
    object acPrintRCalibrProtA: TFileSaveAs
      Category = #1055#1088#1086#1090#1086#1082#1086#1083#1099
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1072#1090#1090#1077#1089#1090#1072#1094#1080#1080' '#1076#1072#1090#1095#1080#1082#1072' '#1087#1086#1083#1086#1078#1077#1085#1080#1103' '#1087#1086#1079'. '#1040
      Dialog.DefaultExt = 'rcprt'
      Dialog.FileName = 'RadiusCalibrA'
      Dialog.Filter = 
        #1092#1072#1081#1083#1099' '#1087#1088#1086#1090#1086#1082#1086#1083#1086#1074' '#1072#1090#1090#1077#1089#1090#1072#1094#1080#1080' '#1088#1072#1076#1080#1091#1089#1072' (*.rcprt)|*.rcprt|'#1074#1089#1077' '#1092#1072#1081#1083#1099' ' +
        '(*.*)|*.*'
      Dialog.Title = 
        #1042#1074#1077#1076#1080#1090#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1076#1083#1103' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1087#1088#1086#1090#1086#1082#1086#1083#1072' '#1072#1090#1090#1077#1089#1090#1072#1094#1080#1080' '#1076#1072#1090#1095#1080#1082#1072' '#1087#1086 +
        #1083#1086#1078#1077#1085#1080#1103' '#1087#1086#1079'. '#1040':'
      Hint = 'Save As|Saves the active file with a new name'
      ImageIndex = 30
      OnAccept = OnPrintRCalibrProtA
    end
    object acPrintTCalibrProtA: TFileSaveAs
      Category = #1055#1088#1086#1090#1086#1082#1086#1083#1099
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1072#1090#1090#1077#1089#1090#1072#1094#1080#1080' '#1076#1072#1090#1095#1080#1082#1072' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099' '#1087#1086#1079'. '#1040
      Dialog.DefaultExt = 'tcprt'
      Dialog.FileName = 'TempCalibrA'
      Dialog.Filter = 
        #1092#1072#1081#1083#1099' '#1087#1088#1086#1090#1086#1082#1086#1083#1086#1074' '#1072#1090#1090#1077#1089#1090#1072#1094#1080#1080' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099' (*.tcprt)|*.tcprt|'#1074#1089#1077' '#1092#1072 +
        #1081#1083#1099' (*.*)|*.*'
      Dialog.Title = 
        #1042#1074#1077#1076#1080#1090#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1076#1083#1103' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1087#1088#1086#1090#1086#1082#1086#1083#1072' '#1072#1090#1090#1077#1089#1090#1072#1094#1080#1080' '#1076#1072#1090#1095#1080#1082#1072' '#1090#1077 +
        #1084#1087#1077#1088#1072#1090#1091#1088#1099' '#1087#1086#1079'. '#1040':'
      Hint = 'Save As|Saves the active file with a new name'
      ImageIndex = 30
      OnAccept = OnPrintTCalibrProtA
    end
    object acPrintSpdCalibrProt: TFileSaveAs
      Category = #1055#1088#1086#1090#1086#1082#1086#1083#1099
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1072#1090#1090#1077#1089#1090#1072#1094#1080#1080' '#1073#1072#1088#1072#1073#1072#1085#1072
      Dialog.DefaultExt = 'scprt'
      Dialog.FileName = 'SpeedCalibr'
      Dialog.Filter = 
        #1092#1072#1081#1083#1099' '#1087#1088#1086#1090#1086#1082#1086#1083#1086#1074' '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1080' (*.scprt)|*.scprt|'#1074#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.' +
        '*'
      Dialog.Title = #1042#1074#1077#1076#1080#1090#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1076#1083#1103' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1087#1088#1086#1090#1086#1082#1086#1083#1072' '#1072#1090#1090#1077#1089#1090#1072#1094#1080#1080' '#1073#1072#1088#1072#1073#1072#1085#1072':'
      Hint = 'Save As|Saves the active file with a new name'
      ImageIndex = 30
      OnAccept = OnPrintSpdCalibrProtocol
    end
    object _acTProgFileSaveAs: TAction
      Category = #1060#1072#1081#1083
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1092#1072#1081#1083#1077' '#1087#1088#1086#1075#1088#1072#1084#1084#1091' '#1087#1086' '#1074#1088#1077#1084#1077#1085#1080
      OnExecute = OnTProgFileSaveAs
    end
    object _acSProgFileSaveAs: TAction
      Category = #1060#1072#1081#1083
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1092#1072#1081#1083#1077' '#1087#1088#1086#1075#1088#1072#1084#1084#1091' '#1087#1086' '#1087#1091#1090#1080
      OnExecute = OnSProgFileSaveAs
    end
    object _acProtTitleFileSaveAs: TAction
      Category = #1060#1072#1081#1083
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1092#1072#1081#1083#1077' '#1079#1072#1075#1086#1083#1086#1074#1086#1082' '#1087#1088#1086#1090#1086#1082#1086#1083#1072
      OnExecute = OnProtTtlFileSaveAs
    end
    object _acPrintProtPosAToFile: TAction
      Category = #1055#1088#1086#1090#1086#1082#1086#1083#1099
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1080#1089#1087#1099#1090#1072#1085#1080#1081' '#1080#1079' '#1087#1086#1079'. '#1040
      OnExecute = OnPrintProtPosAToFile
    end
    object _acPrintLoadCalibrProtA: TAction
      Category = #1055#1088#1086#1090#1086#1082#1086#1083#1099
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1072#1090#1090#1077#1089#1090#1072#1094#1080#1080' '#1085#1072#1075#1088#1091#1079#1082#1080' '#1087#1086#1079'. '#1040
      OnExecute = OnPrintLoadCalibrProtA
    end
    object _acLoadSertPrintProtA: TAction
      Category = #1055#1088#1086#1090#1086#1082#1086#1083#1099
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1080' '#1090#1077#1085#1079#1086#1076#1072#1090#1095#1080#1082#1072' '#1087#1086#1079'. '#1040
      OnExecute = OnPrintLoadSertProtA
    end
    object _acPrintRCalibrProtA: TAction
      Category = #1055#1088#1086#1090#1086#1082#1086#1083#1099
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1072#1090#1090#1077#1089#1090#1072#1094#1080#1080' '#1076#1072#1090#1095#1080#1082#1072' '#1087#1086#1083#1086#1078#1077#1085#1080#1103' '#1087#1086#1079'. '#1040
      OnExecute = OnPrintRCalibrProtA
    end
    object _acPrintTCalibrProtA: TAction
      Category = #1055#1088#1086#1090#1086#1082#1086#1083#1099
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1072#1090#1090#1077#1089#1090#1072#1094#1080#1080' '#1076#1072#1090#1095#1080#1082#1072' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099' '#1087#1086#1079'. '#1040
      OnExecute = OnPrintTCalibrProtA
    end
    object _acPrintSpdCalibrProt: TAction
      Category = #1055#1088#1086#1090#1086#1082#1086#1083#1099
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083' '#1072#1090#1090#1077#1089#1090#1072#1094#1080#1080' '#1073#1072#1088#1072#1073#1072#1085#1072
      OnExecute = OnPrintSpdCalibrProtocol
    end
  end
  object PrinterFontDialog: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Device = fdPrinter
    Left = 736
  end
  object ADC: TADOConnection
    ConnectionString = 
      'Provider=MSDASQL.1;Persist Security Info=False;Data Source=Versh' +
      'ina'
    Provider = 'MSDASQL.1'
    Left = 576
    Top = 8
  end
  object ShowTimer: TTimer
    Enabled = False
    OnTimer = OnReadCycleTimer
    Left = 472
    Top = 8
  end
end
