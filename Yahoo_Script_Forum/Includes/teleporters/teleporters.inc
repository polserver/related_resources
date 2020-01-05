////////////////////////////////////////////////////////////////////////////
//  TELEPORTERS.INC - Places teleporters into the world.
//
//  This file is to be included into start.src and the function
//  CreateTeleporters() called from there.
//
//  Author: Ignatius 1999/05/27
//
//  TODO: walk thru all these and check em out.
//
//  Thanks to Raxxla for some tweaks/fixes!
//
//  Serious overhaul by Culland @ Hidden Shard 2000/06/06
//	- removed as many -255 as possible,
//      - walk throughs fluid in position
//	- teleporters and teleport to locations cleaned up
//      - organized teleporters into lists by locations rather then #
//	- cleaned up descriptions, some abbreviations are:
//	      - btw - between, dwn - down, # is generally the level
//            from top or inwards, N. NE E. W. S., etc are all compass
//            directions, in and out generally mean for the 'area' as
//            a whole.
////////////////////////////////////////////////////////////////////////////

use uo;
use os;
use cfgfile;
//
// System teleporters
//
// Teleporter locations were mainly taken from the UOX project.
// Credit is given where credit is due!
//
// Format:
// { startX, startY, startZ, toX, toY, ToZ },
//
// if startZ is -255 it should affect *all* Z coordinates on that spot,
// but for now the walkonscript gets the lowest walkable location.
//

var teleporters := {
    {2498,   916,     0, 5455,   1863,    0},  // covetous in
    {2499,   916,     0, 5456,   1863,    0},  // covetous in
    {2500,   916,     0, 5457,   1863,    0},  // covetous in
    {5455,  1864,     0, 2498,    917,    0},  // covetous out
    {5456,  1864,     0, 2499,    917,    0},  // covetous out
    {5457,  1864,     0, 2500,    917,    0},  // covetous out
    {5392,  1959,     0, 2420,    884,    0},  // covetous 1 to btw 1-2
    {5393,  1959,     0, 2421,    884,    0},  // covetous 1 to btw 1-2
    {5394,  1959,     0, 2422,    884,    0},  // covetous 1 to btw 1-2
    {2420,   883,     0, 5392,   1958,    0},  // covetous btw 1-2 to 1
    {2421,   883,     0, 5393,   1958,    0},  // covetous btw 1-2 to 1
    {2422,   883,     0, 5394,   1958,    0},  // covetous btw 1-2 to 1
    {2384,   836,     0, 5614,   1996,    0},  // covetous btw 1-2 to 2
    {2384,   837,     0, 5614,   1997,    0},  // covetous btw 1-2 to 2
    {2384,   838,     0, 5614,   1998,    0},  // covetous btw 1-2 to 2	
    {5615,  1996,     0, 2385,    836,    0},  // covetous 2 to btw 1-2
    {5615,  1997,     0, 2385,    837,    0},  // covetous 2 to btw 1-2
    {5615,  1998,     0, 2385,    838,    0},  // covetous 2 to btw 1-2	
    {5388,  2027,     0, 2455,    859,    0},  // covetous 2 to btw 2-3 
    {5389,  2027,     0, 2456,    859,    0},  // covetous 2 to btw 2-3
    {5390,  2027,     0, 2457,    859,    0},  // covetous 2 to btw 2-3
    {2455,   858,     0, 5388,   2026,    0},  // covetous btw 2-3 to 2
    {2456,   858,     0, 5389,   2026,    0},  // covetous btw 2-3 to 2
    {2457,   858,     0, 5390,   2026,    0},  // covetous btw 2-3 to 2
    {2544,   849,     0, 5578,   1926,    0},  // covetous btw 2-3 to 3
    {2545,   849,     0, 5579,   1926,    0},  // covetous btw 2-3 to 3
    {2546,   849,     0, 5580,   1926,    0},  // covetous btw 2-3 to 3
    {5578,  1927,     0, 2544,   850,     0},  // covetous 3 to btw 2-3 
    {5579,  1927,     0, 2545,   850,     0},  // covetous 3 to btw 2-3
    {5580,  1927,     0, 2546,   850,     0},  // covetous 3 to btw 2-3
    {5551,  1803,    20, 5556,   1827,    0},  // covetous torture to 3
    {5552,  1803,    20, 5557,   1827,    0},  // covetous torture to 3
    {5553,  1803,    20, 5558,   1827,    0},  // covetous torture to 3
    {5556,  1828,   -20, 5551,   1804,   17},  // covetous 3 to torture
    {5557,  1828,   -20, 5552,   1804,   17},  // covetous 3 to torture
    {5596,  1840,   -20, 5465,   1805,   15},  // covetous 3 to lake
    {5596,  1841,   -20, 5465,   1806,   15},  // covetous 3 to lake
    {5464,  1804,   20,  5595,   1840,  -14},  // covetous lake to 3
    {5464,  1805,   20,  5595,   1840,  -14},  // covetous lake to 3
    {5464,  1806,   20,  5595,   1841,  -14},  // covetous lake to 3
    {1296,  1080,    0,  5587,    630,   30},  // despise in 
    {1296,  1081,    0,  5587,    631,   30},  // despise in 
    {1296,  1082,    0,  5587,    632,   30},  // despise in
    {5588,   630,   30,  1297,   1080,    0},  // despise out 
    {5588,   631,   30,  1297,   1081,    0},  // despise out 
    {5588,   632,   30,  1297,   1082,    0},  // despise out
    {5571,   628,   50,  5505,    569,   41},  // despise entrance up
    {5571,   629,   50,  5505,    570,   41},  // despise entrance up
    {5571,   630,   50,  5505,    571,   41},  // despise entrance up
    {5571,   632,   12,  5523,    672,   37},  // despise entrance dwn 
    {5571,   633,   12,  5523,    673,   37},  // despise entrance dwn
    {5571,   634,   12,  5523,    674,   37},  // despise entrance dwn
    {5506,   569,   39,  5572,    628,   47},  // despise 1 to entrance
    {5506,   570,   39,  5572,    629,   47},  // despise 1 to entrance
    {5506,   571,   39,  5572,    630,   47},  // despise 1 to entrance*
    {5524,   672,   40,  5572,    632,   17},  // despise 2 to entrance
    {5524,   673,   40,  5572,    633,   17},  // despise 2 to entrance
    {5524,   674,   40,  5572,    634,   17},  // despise 2 to entrance	
    {5385,   755,  -13,  5410,    858,   57},  // despise 2 to 3 
    {5385,   756,  -13,  5410,    859,   57},  // despise 2 to 3
    {5385,   757,  -13,  5410,    860,   57},  // despise 2 to 3
    {5411,   858,   62,  5386,    755,   -8},  // despise 3 to 2 
    {5411,   859,   62,  5386,    756,   -8},  // despise 3 to 2
    {5411,   860,   62,  5386,    757,   -8},  // despise 3 to 2
    {4721,  3813,    0,  5904,     17,   59},  // hythloth in
    {4722,  3813,    0,  5905,     17,   59},  // hythloth in
    {4723,  3813,    0,  5906,     17,   59},  // hythloth in		 
    {5904,    16,   59,  4721,   3814,    0},  // hythloth out
    {5905,    16,   59,  4722,   3814,    0},  // hythloth out
    {5906,    16,   59,  4723,   3814,    0},  // hythloth out	
    {5904,    96,    0,  5974,    169,    0},  // hythloth 1 to 2
    {5974,   168,    0,  5904,     97,    0},  // hythloth 2 to 1
    {5923,   168,    2,  6081,    144,  -10},  // hythloth 2 to 3
    {5923,   169,    1,  6081,    145,  -10},  // hythloth 2 to 3
    {5923,   170,    2,  6081,    146,  -10},  // hythloth 2 to 3
    {6080,   144,   -7,  5922,    168,    7},  // hythloth 3 to 2
    {6080,   145,   -7,  5922,    169,    7},  // hythloth 3 to 2
    {6080,   146,   -7,  5922,    170,    7},  // hythloth 3 to 2
    {6042,   192,    2,  6057,     88,   34},  // hythloth 3 to 4
    {6042,   193,    2,  6057,     89,   34},  // hythloth 3 to 4
    {6042,   194,    2,  6057,     90,   34},  // hythloth 3 to 4
    {6056,    88,   37,  6041,    192,    7},  // hythloth 4 to 3
    {6056,    89,   37,  6041,    193,    7},  // hythloth 4 to 3
    {6056,    90,   37,  6041,    194,    7},  // hythloth 4 to 3
    {4110,   430,    5,  5187,    638,    0},  // deceit in
    {4111,   430,    5,  5188,    638,    0},  // deceit in
    {4112,   430,    5,  5189,    638,    0},  // deceit in
    {5187,   639,    0,  4110,    431,    5},  // deceit out
    {5188,   639,    0,  4111,    431,    5},  // deceit out
    {5189,   639,    0,  4112,    431,    5},  // deceit out
    {5216,   588,  -20,  5304,    530,   17},  // deceit 1 to 2 
    {5217,   588,  -20,  5305,    530,   17},  // deceit 1 to 2
    {5218,   588,  -20,  5306,    530,   17},  // deceit 1 to 2 
    {5304,   529,   20,  5216,    587,  -18},  // deceit 2 to 1 
    {5305,   529,   20,  5217,    587,  -18},  // deceit 2 to 1 
    {5306,   529,   20,  5218,    587,  -18},  // deceit 2 to 1 
    {5346,   578,    5,  5137,    650,    5},  // deceit 2 to 3
    {5137,   649,    5,  5346,    579,    5},  // deceit 3 to 2		
    {5218,   763,  -38,  5305,    649,   17},  // deceit 3 to 4
    {5219,   763,  -40,  5306,    649,   17},  // deceit 3 to 4	
    {5305,   648,   20,  5218,    762,  -33},  // deceit 4 to 3
    {5306,   648,   20,  5219,    762,  -28},  // deceit 4 to 3
    {1175,  2635,    0,  5242,   1006,    0},  // destard in
    {1176,  2635,    0,  5243,   1006,    0},  // destard in
    {1177,  2635,    0,  5244,   1006,    0},  // destard in	
    {5242,  1007,    0,  1175,   2636,    0},  // destard out
    {5243,  1007,    0,  1176,   2636,    0},  // destard out
    {5244,  1007,    0,  1177,   2636,    0},  // destard out
    {5129,   909,  -27,  5142,    798,   17},  // destard 1 to 2
    {5130,   909,  -27,  5143,    798,   17},  // destard 1 to 2
    {5131,   909,  -27,  5144,    798,   17},  // destard 1 to 2
    {5132,   909,  -27,  5145,    798,   17},  // destard 1 to 2
    {5142,   797,   22,  5129,    908,  -22},  // destard 2 to 1
    {5143,   797,   22,  5130,    908,  -22},  // destard 2 to 1
    {5144,   797,   22,  5131,    908,  -22},  // destard 2 to 1
    {5145,   797,   22,  5132,    908,  -22},  // destard 2 to 1
    {5153,   808,  -25,  5135,    984,   12},  // destard 2 to 3
    {5153,   809,  -25,  5135,    985,   12},  // destard 2 to 3
    {5153,   810,  -25,  5135,    986,   12},  // destard 2 to 3		
    {5153,   811,  -25,  5135,    987,   12},  // destard 2 to 3
    {5134,   984,   17,  5152,    808,  -19},  // destard 3 to 2
    {5134,   985,   17,  5152,    809,  -19},  // destard 3 to 2
    {5134,   986,   17,  5152,    810,  -19},  // destard 3 to 2
    {5134,   987,   17,  5152,    811,  -19},  // destard 3 to 2	
    {512,   1559,    0,  5394,    126,    0},  // shame in
    {513,   1559,    0,  5395,    126,    0},  // shame in
    {514,   1559,    0,  5396,    126,    0},  // shame in	
    {5394,   127,    0,   512,   1560,    0},  // shame out
    {5395,   127,    0,   513,   1560,    0},  // shame out
    {5396,   127,    0,   514,   1560,    0},  // shame out
    {5490,    19,  -25,  5515,     11,    5},  // shame 1 to 2
    {5514,    10,    5,  5489,     19,  -25},  // shame 2 to 1	
    {5604,   102,    5,  5515,    147,   25},  // shame 2 to 3	
    {5514,   147,   25,  5604,    101,    5},  // shame 3 to 2	
    {5538,   170,    5,  5514,    175,    5},  // shame 3 to 3 centre
    {5513,   176,    5,  5539,    171,    5},  // shame 3 centre to 3
    {5507,   162,    5,  5874,     20,   -5},  // shame 3 to 4			
    {5875,    19,   -5,  5508,    163,    5},  // shame 4 to 3
    {2041,   215,   14,  5824,    630,    0},  // wrong in
    {2042,   215,   14,  5825,    630,    0},  // wrong in
    {2043,   215,   14,  5826,    630,    0},  // wrong in
    {5824,   631,    0,  2041,   216,    14},  // wrong out
    {5825,   631,    0,  2042,   216,    14},  // wrong out
    {5826,   631,    0,  2043,   216,    14},  // wrong out
    {5867,   537,   15,  5690,   569,    25},  // wrong 1 to 2
    {5732,   554,   20,  5825,   594,     0},  // wrong 2 to 1	
    {5862,   527,   15,  5703,   639,     0},  // wrong 1 to 3
    {5698,   662,    0,  5792,   527,    10},  // wrong 3 to 1
    {5757,  2907,   15,  5791,  1415,    38},  // lava in N. Papua
    {5757,  2908,   14,  5791,  1416,    38},  // lave in N. Papua
    {5757,  2909,   15,  5791,  1417,    40},  // lava in N. Papua
    {5792,  1415,   41,  5758,   2907,   15},  // lava out N. Papua
    {5792,  1416,   41,  5758,   2908,   15},  // lava out N. Papua
    {5792,  1417,   41,  5758,   2909,   15},  // lava out N. Papua	
    {2922,  3405,    7,  5686,   1423,   37},  // lava in Serp. Hold.
    {2923,  3405,    6,  5687,   1423,   39},  // lava in Serp. Hold.
    {2924,  3405,    7,  5688,   1423,   40},  // lava in Serp. Hold.
    {5686,  1424,   38,  2922,   3406,    8},  // lava out Serp. Hold. 
    {5687,  1424,   38,  2923,   3406,    8},  // lava out Serp. Hold.
    {5688,  1424,   38,  2924,   3406,    7},  // lava out Serp. Hold.	
    {5786,  1335,  -13,  5701,   1319,   13},  // lava 1 to 2
    {5787,  1335,  -13,  5702,   1319,   13},  // lava 1 to 2
    {5788,  1335,  -13,  5703,   1319,   13},  // lava 1 to 2
    {5701,  1320,   16,  5786,   1336,   -8},  // lava 2 to 1
    {5702,  1320,   16,  5787,   1336,   -8},  // lava 2 to 1
    {5703,  1320,   16,  5788,   1336,   -8},  // lava 2 to 1
    {5203,  2327,   27,  5875,    147,   25},  // ice in Icelands
    {5207,  2322,   27,  5875,    147,   25},  // ice in Icelands
    {5207,  2323,   26,  5875,    147,   25},  // ice in Icelands
    {5873,   145,   30,  5208,   2322,   32},  // ice out Icelands
    {5874,   145,   30,  5208,   2322,   32},  // ice out Icelands
    {5875,   145,   30,  5208,   2322,   32},  // ice out Icelands
    {5876,   145,   30,  5208,   2323,   31},  // ice out Icelands
    {5877,   145,   30,  5208,   2323,   31},  // ice out Icelands
    {5878,   145,   30,  5208,   2323,   31},  // ice out Icelands	
    {1997,    80,    7,  5881,    241,    0},  // ice in N. Wrong
    {1997,    81,    7,  5881,    242,    0},  // ice in N. Wrong
    {1997,    82,    6,  5881,    243,    0},  // ice in N. Wrong
    {5882,   241,    0,  1998,     80,    6},  // ice out N. Wrong
    {5882,   242,    0,  1998,     81,    5},  // ice out N. Wrong
    {5882,   243,    0,  1998,     82,    5},  // ice out N. Wrong
    {5849,   238,  -25,  5831,    324,   27},  // ice 1 to 2 (orcs)
    {5850,   238,  -25,  5832,    324,   26},  // ice 1 to 2 (orcs)
    {5851,   238,  -25,  5833,    324,   28},  // ice 1 to 2 (orcs)
    {5852,   238,  -25,  5834,    324,   27},  // ice 1 to 2 (orcs)
    {5853,   238,  -22,  5835,    324,   27},  // ice 1 to 2 (orcs)	
    {5831,   323,   34,  5849,    237,  -24},  // ice 2 (orcs) to 1	
    {5832,   323,   34,  5850,    237,  -24},  // ice 2 (orcs) to 1
    {5833,   323,   33,  5851,    237,  -24},  // ice 2 (orcs) to 1
    {5834,   323,   33,  5852,    237,  -25},  // ice 2 (orcs) to 1
    {5835,   323,   33,  5853,    237,  -22},  // ice 2 (orcs) to 1	
    {5704,   146,  -45,  5704,    305,    2},  // ice 1 to 3
    {5704,   147,  -45,  5704,    306,    2},  // ice 1 to 3
    {5705,   304,    7,  5705,    146,  -45},  // ice 3 to 1
    {5705,   305,    7,  5705,    146,  -45},  // ice 3 to 1
    {5705,   306,    7,  5705,    147,  -45},  // ice 3 to 1
    {5705,   307,    7,  5705,    147,  -45},  // ice 3 to 1
    {1628,  3320,    0,   5890,   1410,  42},  // SW Trinsic to t2a cave
    {1629,  3320,    0,   5900,   1410,  42},  // SW Trinsic to t2a cave
    {5898,  1411,   38,   1628,   3321,   0},  // t2a cave to SW Trinsic
    {5899,  1411,   43,   1629,   3321,   0},  // t2a cave to SW Trinsic	
    {5900,  1411,   42,   1629,   3321,   0},  // t2a cave to SW Trinsic
    {5918,  1410,  -29,   5962,   1407,  57},  // t2a cave to t2a newbie
    {5918,  1411,  -29,   5962,   1408,  56},  // t2a cave to t2a newbie
    {5918,  1412,  -29,   5962,   1409,  56},  // t2a cave to t2a newbie
    {5961,  1407,   59,   5917,   1410, -27},  // t2a newbie to t2a cave
    {5961,  1408,   59,   5917,   1411, -27},  // t2a newbie to t2a cave
    {5961,  1409,   59,   5917,   1412, -27},  // t2a newbie to t2a cave
    {6005,  1378,    0,   5151,   4062,  37},  // t2a newbie to Delucia
    {6005,  1379,    2,   5151,   4063,  37},  // t2a newbie to Delucia
    {5150,  4062,   38,   6004,   1378,   1},  // Delucia to t2a newbie
    {5150,  4063,   38,   6004,   1379,  -1},  // Delucia to t2a newbie
    {6025,  1344,  -26,   5138,   3664,  31},  // t2a newbie to W. t2a
    {6025,  1345,  -26,   5138,   3665,  32},  // t2a newbie to W. t2a
    {6025,  1346,  -26,   5138,   3666,  32},  // t2a newbie to W. t2a
    {5137,  3664,   27,   6024,   1344, -26},  // W. t2a to newbie
    {5137,  3665,   31,   6024,   1345, -25},  // W. t2a to newbie
    {5426,  3122,  -74,   5340,   1599,  40},  // terathan in
    {5340,  1598,   47,   5426,   3121, -65},  // terathan out
    {5341,  1598,   47,   5426,   3121, -65},  // terathan out	
    {312,    786,  -24,  5748,    361,    2},  // yew jail to cave
    {313,    786,  -24,  5749,    361,    2},  // yew jail to cave
    {314,    786,  -24,  5750,    361,    4},  // yew jail to cave
    {5748,   362,    2,   312,    787,  -24},  // yew cave to yew jail
    {5749,   362,    0,   313,    787,  -24},  // yew cave to yew jail
    {5750,   362,    3,   314,    787,  -24},  // yew cave to yew jail
    {5753,   325,   10,  5672,   2390,   60},  // yew cave to lighthouse		
    {5671,  2391,   46,  5753,    326,    4},  // lighthouse to yew cave
    {1491,  1640,   24,  6032,   1499,   27},  // Britain sewer down
    {1491,  1642,   24,  6032,   1501,   27},  // Britain sewer down
    {6031,  1499,   35,  1490,   1640,   24},  // Britain sewer up 
    {6031,  1501,   35,  1490,   1642,   24},  // Britain sewer up
    {6140,  1431,    4,  6137,   1408,    2},  // sewer to t2a cave
    {6141,  1431,    4,  6138,   1408,    2},  // sewer to t2a cave
    {6137,  1409,    2,  6140,   1432,    4},  // t2a cave to sewer
    {6138,  1409,    2,  6141,   1432,    4},  // t2a cave to sewer
    {6125,  1411,   15,  6074,   3333,    2},  // t2a cave to t2a bog
    {6126,  1411,   15,  6075,   3333,    2},  // t2a cave to t2a bog			
    {6074,  3332,    4,  6126,   1410,   15},  // t2a bog to t2a cave
    {6075,  3332,    4,  6127,   1410,   15},  // t2a bog to t2a cave
    {1409,  3824,    5,  1124,   3623,    5},  // jhelom main to NW isle	
    {1142,  3621,    5,  1414,   3828,    5},  // jhelom NW isle to main
    {1419,  3832,    5,  1466,   4015,    5},  // jhelom main to S. isle		
    {1406,  3996,    5,  1414,   3828,    5},  // jhelom S. isle to main
    {4436,  1107,    5,   4300,   992,    5},  // moonglow town to NW	
    {4300,   968,    5,   4442,  1122,    5},  // moonglow NW to town
    {4449,  1115,    5,   4671,  1135,   10},  // moonglow town to E.	
    {4663,  1134,   13,   4442,  1122,    5},  // moonglow E. to town 		
    {4449,  1107,    5,   4539,   890,   28},  // moonglow town to N.
    {4540,   898,   32,   4442,  1122,    5},  // moonglow N. to town	
    {4443,  1137,    5,   4487,   1475,   5},  // moonglow town to S.
    {4496,  1475,   15,   4442,   1122,   5},  // moonglow S. to town
    {4545,   851,   30,   5735,   3196,  10},  // moonglow to papua	
    {5736,  3196,   10,   4545,    852,  30},  // papua to moonglow	
    {1361,   883,    0,   5166,	   245,  15},  // wind in
    {5191,   152,    0,   1361,    884,   0},  // wind out
    {5200,    71,   17,   5211,     22,  15},  // wind town to park
    {5217,    18,   15,   5204,     74,  17},  // wind park to town	
    {2776,   894,  -23,   5685,    386,   1},  // vesper grave to cave
    {2776,   895,  -23,   5685,    387,   2},  // vesper grave to cave
    {5686,   385,    2,   2777,    893, -23},  // cave to vesper grave
    {5686,   386,    2,   2777,    894, -23},  // cave to vesper grave
    {5686,   387,    2,   2777,    895, -23},  // cave to vesper grave		
    {5658,   423,    8,   5697,   3659,   2},  // cave to S. of Papua
    {5697,  3660,   -5,   5658,    424,   0},  // S. of Papua to cave
    {2398,   198,    0,   6087,   3675,  17},  // N. Minoc to east t2a	
    {2399,   198,    0,   6087,   3675,  17},  // N. Minoc to east t2a
    {2400,   198,    0,   6087,   3676,  18},  // N. Minoc to east t2a
    {6086,  3675,   15,   2399,    199,   0},  // east t2a to N. Minoc
    {6086,  3676,   16,   2400,    199,   0},  // east t2a to N. Minoc
    {2494,  3576,    5,   5907,   4069,  26},  // S. Isle to S. t2a
    {5906,  4069,   26,   2494,   3577,   5},  // S. t2a to S. Isle
    {1163,  2208,   60,   1171,   2202,   0},  // maze NE roof to ground
    {1165,  2204,   40,   1163,   2210,  60},  // maze NE bldg to roof
    {1133,  2230,   20,   1163,   2208,   0},  // maze main bldg to NE
    {1653,  2963,    0,   1676,   2986,   0},  // Hidden Valley 1
    {1677,  2987,    0,   1675,   2987,  20},  // Hidden Valley 2
    {1592,  2489,   17,   1601,   2489,   7},  // Spirituality down
    {1600,  2489,   10,   1593,   2489,  17},  // Spirituality up
    {1600,  2490,   10,   1593,   2489,  17},  // Spirituality up	
    {2666,  2072,    5,   2669,   2072, -18},  // Buc Den bath down	
    {2668,  2072,  -13,   2666,   2073,   5},  // Buc Den bath up
    {2668,  2073,  -13,   2666,   2073,   5},  // Buc Den bath up	
    {2648,  2193,    4,   2649,   2196, -20},  // Buc Den house down	
    {2649,  2195,  -14,   2649,   2193,   4},  // Buc Den house up
    {2672,  2241,    2,   2677,   2242, -20},  // Buc Den tavern down
    {2676,  2241,  -18,   2673,   2242,   2},  // Buc Den tavern up
    {2676,  2242,  -18,   2673,   2243,   2},  // Buc Den tavern up
};

function CreateTeleporters()

    //syslog( "Creating teleporters." );

    var fromX;
    var fromY;
    var fromZ;

    var toX;
    var toY;
    var toZ;

    var nbrOfTeleporters := 0;

    foreach tele in teleporters

        fromX := tele[1];
        fromY := tele[2];
        fromZ := tele[3];

        // check -255.
        if ( fromZ = -255 )
            fromZ := GetWorldHeight( fromx, fromy );
        endif

        toX := tele[4];
        toY := tele[5];
        toZ := tele[6];

        // create the teleporter.
        var teleporter;
        
        teleporter := CreateItemAtLocation( fromX, fromY, fromZ, "systemteleporter", 1 );

        // enter the destination CProps.
        if ( teleporter )
            SetObjProperty( teleporter, "DestX", toX );
            SetObjProperty( teleporter, "DestY", toY );
            SetObjProperty( teleporter, "DestZ", toZ );
            nbrOfTeleporters := nbrOfTeleporters + 1;
        else
            syslog( "Error: " + teleporter.errortext + " at: " + fromX + " " + fromY + " " + fromZ );
        endif    

    endforeach
    
    local i, teleporter;
    local cfg := readconfigfile("teleporters");
    local maxint := getconfigmaxintkey(cfg);
    for (i := 1; i <= maxint; i := i + 1)
        fromx := cfg[i].fromx;
        fromy := cfg[i].fromy;
        fromz := getmapinfo(fromx, fromy).z;
        tox := cfg[i].tox;
        toy := cfg[i].toy;
        toz := getmapinfo(tox, toy).z;
	teleporter := CreateItemAtLocation( fromX, fromY, fromZ, "systemteleporter", 1 );
	syslog ( "Creating Teleporter " + i + ".");

        if ( teleporter )
            SetObjProperty( teleporter, "DestX", toX );
            SetObjProperty( teleporter, "DestY", toY );
            SetObjProperty( teleporter, "DestZ", toZ );
        else
            syslog( "Error: " + teleporter.errortext + " at: " + fromX + " " + fromY + " " + fromZ );
        endif
     endfor
           //syslog( nbrOfTeleporters +  " teleporters created." );

endfunction

