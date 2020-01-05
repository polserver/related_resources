//v0.7c
//Raid Constants

//-params-  (passed to startraid())
const PA_LOCATION      :=1;
const PA_GROUP         :=2;
const PA_DIFFICULTY    :=3;
const PA_STARTERNAME   :=4;
const PA_STOPNOGOLD    :=5;
const PA_RAIDGUARDS    :=6;
const PA_REWARDPLAYERS :=7;
const PA_RAIDTYPE      :=8;
const PA_PROVOKE       :=9; //na
const PA_RAIDWAR       :=10; //na


//-Raidsettings- (Updated only on startup)

const SET_XGOAL        :=1;
const SET_YGOAL        :=2;
const SET_YOINKAMOUNT  :=3;
const SET_STOPNOGOLD   :=4;
const SET_TOTALRAIDERS :=5;
const SET_PROVOKE      :=6;
const SET_RAIDERTYPE   :=7;
const SET_RAIDERWAR    :=9; //na
const SET_CHARGEPOINT  :=10; //na
const SET_CHARGESTR    :=11; //na

//-Raidupdateinfo- (real time updated)
const UPD_GOLDLEFT      :=1;


//-RaidType (PA_RAIDTYPE) -
const RAID_RAIDNOGOLD              :=0;
const RAID_RAIDWITHGOLD            :=1;
//const RAID_TOWNRUN               :=2;
//const RAID_KILLMONSTERGENERATOR  :=3;

//Monster Specific
const YOINK_DIST := 3; //doubles for a waypoint finde
const DEX_UPGD := 100; //for getting the npcs to the location faster (will change in pol.94 i suppose)
const SLEEP_TIME := 500; //sleep time for running towards chest (in ms) (lower for laggy shards)

//raidtown.src Specific
const MAX_TRIES		:= 4; //How many tries per npc till it fails
const CHECK_FOR_ERRORS := 0; //enable if townraid dont work, this will tell u why
const RANDOM_SPAWNS := 1; //spawn dudes in groups randomly from the groups list?

const TXTCMD_PATH := "/textcmd/seer/raidtown";

/*
-Params-
[1] - location string
[2] - group string
[3] - difficulty string
[4] - townraid starter name
[5] - stop the raid if no gold left
[6] - raidguards enabled
[7] - players get gold reward on winning
[8] - RaidType 
       0: raid with no gold
       1: raid with gold
[9] - Raiders dont attack unless provoked (so players choose who they fight)
[10] - RaidWar


-Saved Global Info-
	"raidname":     Name of raid
	"raidsettings": [1] -x cord of monster goal
					[2] -y cord of monster goal
					[3] -Amount monsters loot per yoink
					[4] -Does the raid stop when theres no gold left
					[5] -Total amount of raiders that will be spawned
					[6] -Monsters Dont attack unless provoked
					[7] -name of group thats raiding
					[8] -Do the raiders attack other raiders of a different raid?

	"raidupdateinfo": [1] -Amount left in goldpile

	"raiddead":		Dead raider count
	"raidwaypoints":  [1+x] -xwaypoint no[x]
			  [2+x] -ywaypoint no[x]
	"RaidcfgOK":    Temp var (remove)

-RaidTypes
RAID_RAIDNOGOLD: A simple raid
RAID_RAIDWITHGOLD: A raid with a big pile o gold in the middle
RAID_TOWNRUN: Monsters run through town, and if at least 25% make it, the players 'loose'
RAID_KILLMONSTERGENERATOR: there is a 'leader' monster in the middle of the spawn rect, this guy has to be 
                           killed in order for the raid to be stopped.
*/