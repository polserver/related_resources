////////////////////////////////////////////////////////////////////////////
//  HOTSPOTS.INC - Places hotspots into the world.
//
//  This file is to be included into start.src.
//
//  Author: Brian  8th Oct 2001   - brian@pcsys.demon.co.uk
//
////////////////////////////////////////////////////////////////////////////

use uo;
use os;
use cfgfile;
//
//
// Format:
// { posX, posY, posZ, action, npctype, amount },
//
//

var hotspots := {
    {5175,   615,     0,   "harm",      0,               0},  // Deceit LV 1 (Centre of Circle)
    {5226,   541,     0,   "summon",    "Skeleton",      2},  // Deceit LV1 (Center Stone Circle)
    {5227,   717,     0,   "heal",      0,               0},  // Deceit LV1 (Center Stone Circle)
    {5151,   717,     0,   "heal",      0,               0},  // Deceit LV2 (Center Stone Circle)
    {5218,   731,     -20, "heal",      0,               0},  // Deceit LV2 (Center Stone Circle)
    {5221,   731,     -20, "harm",      0,               0},  // Deceit LV2 (Center Stone Circle)
    {5281,   667,     2,   "summon",    "fireelemental", 1},  // Deceit LV3 
    {5452,  1921,     5,   "summon",    "liche",         1},  // Covetous LV1
    {5426,  1900,     5,   "summon",    "skeleton",      8},  // Covetous LV1
    {5538,  1881,     0,   "summon",    "bonemage",      2},  // Covetous LV3
    {5541,  1809,     0,   "summon",    "bloodliche",    1},  // Covetous LV3
    {5473,   754,    10,   "heal",      0,               0},  // Despise LV2 
    {5386,   851,    55,   "lightning", 0,               0},  // Despise LV3
    {5450,  1002,     5,   "heal",      0,               0},  // Despise LV3
    {5666,  1315,     0,   "strength",  0,               0},  // Fire Dung
    {4595,  3574,    75,   "summon",    "daemon",        0},  // Fire Pit, Nr Hyloth
    {5986,   208,    44,   "clumsy",    0,               0},  // Hyloth
    {5970,   147,    22,   "heal",      0,               0},  // Hyloth
    {6086,   178,     0,   "summon",    "daemon",        0},  // Hyloth
    {6054,    47,     0,   "heal",      0,               0},  // Hyloth
    {6083,    90,    22,   "poison",    0,               2},  // Hyloth
    {5666,   310,     0,   "random",    0,               0},  // Ice Dungeon
    {5663,   313,     0,   "random",    0,               0},  // Ice Dungeon
    {5481,   205,     0,   "summon",    "skeleton",      3},  // Shame LV4
    {5483,   205,     0,   "summon",    "skeleton",      3},  // Shame LV4
    {5488,   206,     0,   "summon",    "zombie",        3},  // Shame LV4
    {5488,   204,     0,   "summon",    "bonemage",      2},  // Shame LV4
    {5488,   202,     0,   "summon",    "bonewarlock",   2},  // Shame LV4
    {5488,   200,     0,   "summon",    "boneknight",    2},  // Shame LV4
    {5496,   203,     0,   "summon",    "liche",         1},  // Shame LV4
    {5703,   658,     0,   "random",    0,               0},  // Wrong LV3
    {5704,   658,     0,   "random",    0,               0},  // Wrong LV3
    {2437,  1105,     8,   "firefield", "all",          10},  // Cove Cemetry - FireField, All sides, 10 Seconds
    {2441,  1102,     8,   "summon",    "skeleton",      1},  // Cove Cemetry
    {2443,  1110,     8,   "summon",    "zombie",        2},  // Cove Cemetry
    {2428,  1109,     8,   "summon",    "shade",         2},  // Cove Cemetry
    {1388,  1481,    10,   "summon",    "skeleton",      1},  // Britain Cemetry
    {1378,  1447,    10,   "summon",    "zombie",        1},  // Britain Cemetry
    {1374,  1445,    10,   "summon",    "boneknight",    1},  // Britain Cemetry
    {1374,  1447,    10,   "summon",    "skeleton",      1},  // Britain Cemetry
    {1343,  1473,    10,   "summon",    "skeleton",      1},  // Britain Cemetry
    {1280,  3723,     0,   "summon",    "wraith",        1},  // Jhelom Cemetry
    {1284,  3714,     0,   "summon",    "shade",         1},  // Jhelom Cemetry
    {1275,  3715,     0,   "summon",    "liche",         1},  // Jhelom Cemetry
    {1294,  3725,     0,   "summon",    "skeleton",      2},  // Jhelom Cemetry
    {1292,  3744,     0,   "summon",    "zombie",        3},  // Jhelom Cemetry
    {1286,  3748,     0,   "summon",    "shade",         1},  // Jhelom Cemetry
    {1282,  3750,     0,   "summon",    "wraith",        1},  // Jhelom Cemetry
    {4549,  1317,     8,   "summon",    "skeleton",      2},  // Moonglow Cemetry
    {4547,  1317,     8,   "summon",    "liche",         1},  // Moonglow Cemetry
    {4532,  1317,     8,   "summon",    "bonewarlock",   1},  // Moonglow Cemetry
    {4530,  1324,     8,   "summon",    "bonemage",      1},  // Moonglow Cemetry
    {4536,  1324,     8,   "summon",    "zombie",        3},  // Moonglow Cemetry
    {4549,  1324,     8,   "summon",    "spectre",       1},  // Moonglow Cemetry
    {4544,  1309,    18,   "poisfield", "east",         15},  // Moonglow Cemetry - PoisonField, East Only, 15 Seconds
    {4552,  1304,    18,   "parafield", "south",        15},  // Moonglow Cemetry - ParalyseField, South Only, 15 Seconds
    {3546,  1147,    20,   "summon",    "wraith",        1},  // Nu'Jelm Cemetry
    {3509,  1147,    30,   "summon",    "skeleton",      8},  // Nu'Jelm Cemetry
    {3522,  1155,    20,   "summon",    "zombie",        3},  // Nu'Jelm Cemetry
    {3526,  1152,    20,   "summon",    "shade",         1},  // Nu'Jelm Cemetry
    {3526,  1159,    20,   "summon",    "bonekight",     1},  // Nu'Jelm Cemetry
    {2744,   858,     0,   "firefield", "all",           5},  // Vesper Cemetry - FireField, all, 5 secs
    {2762,   859,     0,   "summon",    "wraith",        1},  // Vesper Cemetry
    {2766,   859,     0,   "summon",    "shade",         1},  // Vesper Cemetry
    {2763,   863,     0,   "summon",    "zombie",        3},  // Vesper Cemetry
    {2767,   882,     0,   "summon",    "skeleton",      2},  // Vesper Cemetry
    {2763,   887,     0,   "summon",    "boneknight",    1},  // Vesper Cemetry
    {2759,   887,     0,   "summon",    "bonemage",      1},  // Vesper Cemetry
    {2763,   893,     0,   "summon",    "bonewarlock",   1},  // Vesper Cemetry
    {2734,   888,     0,   "summon",    "spectre",       1},  // Vesper Cemetry
    {2730,   876,     0,   "summon",    "liche",         1},  // Vesper Cemetry
    { 728,  1128,     0,   "summon",    "skeleton",      6},  // Yew Cemetry
    { 713,  1131,     0,   "summon",    "liche",         1},  // Yew Cemetry
    { 723,  1106,     0,   "enerfield", "south",         9},  // Vesper Cemetry - EnergyField, South, 9 secs
    { 723,  1105,     0,   "stonewall", "south",         9},  // Vesper Cemetry - Wall of Stone, South, 9 secs
};

function CreateHotspots()

    //syslog( "Creating teleporters." );

    var posX;
    var posY;
    var posZ;

    var action, npctype, amount;

    foreach hotspot in hotspots

        posX := hotspot[1];
        posY := hotspot[2];
        posZ := hotspot[3];

        action := hotspot[4];
        npctype := hotspot[5];
        amount := hotspot[6];

        // create the hotspot.
        var hotspot;
        
        hotspot := CreateItemAtLocation( posX, posY, posZ, "systemhotspot", 1 );
        SetObjProperty(hotspot,"Action",action);
        SetObjProperty(hotspot,"NPCType",npctype);
        SetObjProperty(hotspot,"Amount",amount);

    endforeach
    
endfunction

