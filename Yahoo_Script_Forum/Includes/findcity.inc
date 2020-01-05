use os;
use uo;

Function FindCity(me)
  If ( me.x>=1244 and me.y>=1530 and me.x<=1704 and me.y<=1758)
    Return "Britain";

  Elseif( me.x>=5272 and me.x<=5310 and me.y>=1160 and me.y<=1190)
    Return "Jail";

  Elseif( me.x>=1385 and me.x<=1414 and me.y>=3729 and me.y<=3758)
    Return "Fighting Arena";

  Elseif( me.x>=4094 and me.y>=3073 and me.x<=4868 and me.y<=3993)
    Return "Isle of the Avatar";

  Elseif( me.x>=3839 and me.x<=4309 and me.y>=167 and me.y<=773)
    Return "Ice Isle";

    Elseif ( me.x>=4228 and me.y>=774 and me.x<=4829 and me.y<=1546)
      Return "Moonglow Isle";
    Elseif ( me.x>=4379 and me.y>=1045 and me.x<=4487 and me.y<=1178)
      Return "Moonglow";

    Elseif ( me.x>=5137 and me.y>=3948 and me.x<=5196 and me.y<=4082)
      Return "Delucia";
    Elseif ( me.x>=5196 and me.y>=3923 and me.x<=5322 and me.y<=4085)
      Return "Delucia";

    Elseif ( me.x>=5374 and me.y>=1079 and me.x<=5635 and me.y<=1283)
      Return "Green Acres";
    Elseif ( me.x>=5627 and me.y>=1021 and me.x<=6144 and me.y<=1283)
      Return "Green Acres";
    Elseif ( me.x>=5887 and me.y>=510 and me.x<=6144 and me.y<=1022)
      Return "Green Acres";

    Elseif ( me.x>=5638 and me.y>=3083 and me.x<=5799 and me.y<=3328)
      Return "Papua";
    Elseif ( me.x>=5799 and me.y>=3121 and me.x<=5822 and me.y<=3327)
      Return "Papua";

    Elseif ( me.x>=5132 and me.y>=1754 and me.x<=5161 and me.y<=1782)
      Return "Star Chamber";

    Elseif ( me.x>=1294 and me.y>=3664 and me.x<=1506 and me.y<=3886)
      Return "Jhelom";
      
    Elseif ( me.x>=494 and me.y>=926 and me.x<=600 and me.y<=1034)
      Return "Yew";

    Elseif ( me.x>=590 and me.y>=796 and me.x<=670 and me.y<=886)
      Return "Empath Abbey";

    Elseif ( me.x>=2394 and me.y>=370 and me.x<=2624 and me.y<=632)
      Return "Minoc";

    Elseif ( me.x>=1794 and me.y>=2638 and me.x<=2136 and me.y<=2902)
      Return "Trinsic";

    Elseif ( me.x>=538 and me.y>=2106 and me.x<=686 and me.y<=2274)
      Return "Skara Brae";

    Elseif ( me.x>=3646 and me.y>=2040 and me.x<=3814 and me.y<=2280)
      Return "Magincia";

    Elseif ( me.x>=3588 and me.y>=2446 and me.x<=3762 and me.y<=2690)
      Return "Occlo";

    Elseif ( me.x>=2612 and me.y>=2082 and me.x<=2772 and me.y<=2256)
      Return "Buccaneers Den";

    Elseif ( me.x>=3496 and me.y>=1062 and me.x<=3808 and me.y<=1400)
      Return "Nujelm";

    Elseif ( me.x>=2794 and me.y>=634 and me.x<=3026 and me.y<=1000)
      Return "Vesper";

    Elseif ( me.x>=2206 and me.y>=1116 and me.x<=2290 and me.y<=1236)
      Return "Cove";

    Elseif ( me.x>=5120 and me.y>=0 and me.x<=6128 and me.y<=1992)
      Return "Dungeons";

    Elseif ( me.x>=5120 and me.y>=0 and me.x<=5374 and me.y<=254)
      Return "Wind";
Endif

Return "Sosaria";
EndFunction
