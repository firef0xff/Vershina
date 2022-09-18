object Plotter: TPlotter
  Left = 0
  Top = 0
  Width = 952
  Height = 559
  TabOrder = 0
  OnResize = FrameResize
  object GraphArea: TImage
    Left = 0
    Top = 0
    Width = 952
    Height = 526
    Align = alClient
    ExplicitLeft = 456
    ExplicitTop = 160
    ExplicitWidth = 105
    ExplicitHeight = 105
  end
  object Panel1: TPanel
    Left = 0
    Top = 526
    Width = 952
    Height = 33
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      952
      33)
    object ScaleDownX: TSpeedButton
      Left = 834
      Top = 6
      Width = 23
      Height = 22
      Anchors = [akRight, akBottom]
      ExplicitLeft = 526
    end
    object ScaleDownY: TSpeedButton
      Left = 892
      Top = 6
      Width = 23
      Height = 22
      Anchors = [akRight, akBottom]
      ExplicitLeft = 584
    end
    object ScaleReset: TSpeedButton
      Left = 805
      Top = 6
      Width = 23
      Height = 22
      Anchors = [akRight, akBottom]
      ExplicitLeft = 497
    end
    object ScaleUpX: TSpeedButton
      Left = 863
      Top = 6
      Width = 23
      Height = 22
      Anchors = [akRight, akBottom]
      ExplicitLeft = 555
    end
    object ScaleUpY: TSpeedButton
      Left = 921
      Top = 6
      Width = 23
      Height = 22
      Anchors = [akRight, akBottom]
      ExplicitLeft = 613
    end
    object Label1: TLabel
      Left = 8
      Top = 9
      Width = 10
      Height = 13
      Caption = 'X:'
    end
    object Label2: TLabel
      Left = 177
      Top = 9
      Width = 10
      Height = 13
      Caption = 'Y:'
    end
    object ValuesX: TComboBox
      Left = 26
      Top = 6
      Width = 145
      Height = 21
      TabOrder = 0
      Text = 'ValuesX'
    end
    object ValuesY: TComboBox
      Left = 191
      Top = 6
      Width = 145
      Height = 21
      TabOrder = 1
      Text = 'ComboBox1'
    end
  end
end
