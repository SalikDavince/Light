new
	query[1001],
	Text:brLeft, Text:brRight, Text:brSelect, Text:ButtonCancel, Text:tCost;


enum pInfo 
{ 
	pMysqlID,
	pName[MAX_PLAYER_NAME],
	//Ip[16],
	pPassword[32],
	pMail[32],
	pIP[16],
	pRegData[24],
	pLevel,
	pReferal[MAX_PLAYER_NAME],
	pAdmin,
	pSex,
	pModel[2],
	APass,
	pMoney,
	pHouse,
	pFraction[3],
	pAmmo,
	pCar[4],
	Float:pMilage,
	pBan,
	pBusiness,
	pPhone[2],
	Skill[10],
	pMute,
	pWanted,
	pCity,
	pDrugs,
	pExp,
	pBank,
	pBankPass,
	Licenses,
	CGR,
	OtherM[2],
	Text:iModel,
	Text:iSkin,
	Text:iPhone,
	Text:iClock,
	Text:iGps,
	Text:iRepair,
	Slot[20],
	//local
	Advertise[81],
	bool:PlayerLogged,
	bool:ClothesRound,
	bool:CreatePassword,
	bool:TDSelect,
	bool:Aat,
	SSCase,
	ChosenSkin,
	Float:PlayerArmor,
	ArendedVehicle,
	Trailer,
	PlayerCar,
	Weapon[47],
	Text:tCostItem,
	Text:asVname,
	Text:asCostV 
};

//___________________ Weather _________________________

new AllowWeather[12] = {0,2,0,3,5,10,10,11,13,14,17,18};
new CurrentWeather = 2;

//-----------------------------------------------------


//___________________ Player Timer ____________________

new player_other_timer[MAX_PLAYERS];

//-----------------------------------------------------

new
	Player[MAX_PLAYERS][pInfo],
 	strock[255+1],
	engine,lights,alarm,doors,bonnet,boot,objective,
	Timer[4],
	Float:Fuel[MAX_VEHICLES],
	getpass[MAX_PLAYERS][21],
	//txd
	Text:abox, // box
	Text:a1, // 1
	Text:a2, // 2
	Text:a3, // 3
	Text:a4, // 4
	Text:a5, // 5
	Text:a6, // 6
	Text:a7, // 7
	Text:a8, // 8
	Text:a9, // 9
	Text:a0, // 0
	Text:aenter, // enter
	Text:aboxtop, // box top
	Text:atext, // text
	Text:ac, // ac
	//speedtxd
	Text:sbox,
	PlayerText:smodel[MAX_PLAYERS],
	Text:skmh,
	PlayerText:sspeed[MAX_PLAYERS],
	Text:sfuel,
	PlayerText:sfuelv[MAX_PLAYERS],
	PlayerText:sengine[MAX_PLAYERS],
	PlayerText:slights[MAX_PLAYERS],
	PlayerText:slimit[MAX_PLAYERS],
	PlayerText:slock[MAX_PLAYERS],
	Text:smilage[MAX_PLAYERS],
	//wars
	Text:gBox,
	PlayerText:gFGang[MAX_PLAYERS],
	PlayerText:gTGang[MAX_PLAYERS],
	PlayerText:gFScore[MAX_PLAYERS],
	PlayerText:gTScore[MAX_PLAYERS],
	Text:gArea,
	PlayerText:gIDs[MAX_PLAYERS],
	Text:gsTime,
	PlayerText:gTimeTick[MAX_PLAYERS],
	//=== Recon
	Text:rbox,
	Text:rmodel[MAX_PLAYERS],
	Text:rname[MAX_PLAYERS],
	Text:rhealth[MAX_PLAYERS],
	Text:rarmour[MAX_PLAYERS],
	Text:rping[MAX_PLAYERS],
	Text:rmoney[MAX_PLAYERS],
	Text:rspeed[MAX_PLAYERS],
	Text:rrip[MAX_PLAYERS],
	Text:rip[MAX_PLAYERS],
	Text:rcopy,
	Text:rvbox,
	Text:rvmodel[MAX_PLAYERS],
	Text:rvname[MAX_PLAYERS],
	Text:rvhealth[MAX_PLAYERS],
	Text:rvspeed[MAX_PLAYERS],
	Menu:rMenu,
	//guns
	Text:cBox,
	Text:cMYG,
	PlayerText:cAmmo[MAX_PLAYERS],
	Text:cXc,
	Text:c1,
	Text:c2,
	Text:c3,
	Text:c4,
	Text:c5,
	Text:c6,
	Text:cDeagle,
	Text:cKolt,
	Text:cShotgun,
	Text:cAKM,
	Text:cM4A1,
	Text:cMP5,
	Text:cSAW,
	//MainMenu
	Text:mm0,
	Text:mm1,
	Text:mm2,
	Text:mm3,
	Text:mm4,
	Text:mm5,
	Text:mm6,
	PlayerText:mm7[MAX_PLAYERS],
	Text:mm8,
	Text:mm9,
	Text:mm10,
	Text:mm11,
	Text:mm12,
	Text:mm13,
	Text:mm14,
	Text:mm15,
	Text:mm16,
	Text:mm17,
	Text:mm18,
	Text:mm19,
	PlayerText:mm20[MAX_PLAYERS],
	PlayerText:mm21[MAX_PLAYERS],
	PlayerText:mm22[MAX_PLAYERS],
	PlayerText:mm23[MAX_PLAYERS],
	PlayerText:mm24[MAX_PLAYERS],
	PlayerText:mm25[MAX_PLAYERS],
	PlayerText:mm26[MAX_PLAYERS],
	PlayerText:mm27[MAX_PLAYERS],
	PlayerText:mm28[MAX_PLAYERS],
	Text:mm29,
	Text:mm30,
	Text:mm31,
	Text:mm32,
	Text:mm33,
	Text:mm34,
	Text:mm35,
	Text:mm36,
	Text:mm37,
	Text:mm38,
	Text:mm39,
	Text:mm40,
	Text:mm41,
	Text:mm42,
	PlayerText:mm43[MAX_PLAYERS],
	Text:mm44,
	PlayerText:mm45[MAX_PLAYERS],
	PlayerText:mm46[MAX_PLAYERS],
	PlayerText:mm47[MAX_PLAYERS],
	//============================
	Text:amBox,
	PlayerText:amGun[MAX_PLAYERS],
	Text:amPCPS,
	PlayerText:amPrice[MAX_PLAYERS],
	Text:amBox2,
	Text:amChit,
	Text:amLeft,
	Text:amChit2,
	Text:amRight,
	Text:amBBUY,
	Text:amBBACK,
	Text:amBUY,
	Text:amBack,
	//== Logo ===
	Text:LCheery,
	Text:LRole,
	Text:LPlay,
	Text:Lchit,
	Text:Ln1,
	//== Autosalon ===
	Text:asBox,
	Text:asCost,
	Text:asLeft,
	Text:asRight,
	Text:asBuy,
	Text:asExit,
	Text:asBBuy,
	Text:asBExit,
	//== Race ===
	Text:raBox,
	Text:raImg,
	Text:raTrack,
	Text:raDist,
	Text:raBox2,
	Text:raLeft,
	Text:raRight,
	Text:raSRace,
	Text:raButS,
	Text:raButC,
	Text:raStart,
	Text:raCancel,
	//===== INVENTORY =====
	Text:iBox, Text:iChit, Text:iInv,
 	Text:iDrop, Text:iCross, Text:iBox12,
 	Text:iBox2, Text:iUse, Text:iSlot[MAX_PLAYERS][20],
	RaceTime, track[20], Rate;

new VehicleNames[212][] = 
{ 
	"Landstalker","Bravura","Buffalo","Linerunner","Pereniel","Sentinel","Dumper","Firetruck","Trashmaster","Stretch","Manana","Infernus", "Voodoo","Pony","Mule","Cheetah","Ambulance","Leviathan","Moonbeam","Esperanto","Taxi","Washington","Bobcat","Mr Whoopee","BF Injection",
	"Hunter","Premier","Enforcer","Securicar","Banshee","Predator","Bus","Rhino","Barracks","Hotknife","Trailer","Previon","Coach","Cabbie", "Stallion","Rumpo","RC Bandit","Romero","Packer","Monster","Admiral","Squalo","Seasparrow","Pizzaboy","Tram","Trailer","Turismo","Speeder",
	"Reefer","Tropic","Flatbed","Yankee","Caddy","Solair","Berkley's RC Van","Skimmer","PCJ-600","Faggio","Freeway","RC Baron","RC Raider", "Glendale","Oceanic","Sanchez","Sparrow","Patriot","Quad","Coastguard","Dinghy","Hermes","Sabre","Rustler","ZR3 50","Walton","Regina",
	"Comet","BMX","Burrito","Camper","Marquis","Baggage","Dozer","Maverick","News Chopper","Rancher","FBI Rancher","Virgo","Greenwood", "Jetmax","Hotring","Sandking","Blista Compact","Police Maverick","Boxville","Benson","Mesa","RC Goblin","Hotring A","Hotring B",
	"Bloodring Banger","Rancher","Super GT","Elegant","Journey","Bike","Mountain Bike","Beagle","Cropdust","Stunt","Tanker","RoadTrain", "Nebula","Majestic","Buccaneer","Shamal","Hydra","FCR-900","NRG-500","HPV1000","Cement Truck","Tow Truck","Fortune","Cadrona","FBI Truck",
	"Willard","Forklift","Tractor","Combine","Feltzer","Remington","Slamvan","Blade","Freight","Streak","Vortex","Vincent","Bullet","Clover", "Sadler","Firetruck","Hustler","Intruder","Primo","Cargobob","Tampa","Sunrise","Merit","Utility","Nevada","Yosemite","Windsor","Monster A",
	"Monster B","Uranus","Jester","Sultan","Stratum","Elegy","Raindance","RC Tiger","Flash","Tahoma","Savanna","Bandito","Freight","Trailer", "Kart","Mower","Duneride","Sweeper","Broadway","Tornado","AT-400","DFT-30","Huntley","Stafford","BF-400","Newsvan","Tug","Trailer A","Emperor",
	"Wayfarer","Euros","Hotdog","Club","Trailer B","Trailer C","Andromada","Dodo","RC Cam","Launch","Police Car","Police Car", "Police Car","Police Ranger","Picador","S.W.A.T.","Alpha","Phoenix","Glendale","Sadler","L Trailer A","L Trailer B", "Stair Trailer","Boxville","Farm Plow","U Trailer" 
};

new VehicleCost[212] = {0,350000,170000,2300000};

enum hInfo { hID, hOwner[MAX_PLAYER_NAME], Float:hX, Float:hY, Float:hZ, Float:cX, Float:cY, Float:cZ, Float:cA, hPrice, hLock, hInt, hStreet[32], hPriority, hHousemans, hUpgrade, hCommunal, hPickup, hIcon, hObject[2],
Float:sX,Float:sY,Float:sZ,Float:sRX,Float:sRY,Float:sRZ,Float:wX,Float:wY,Float:wZ,Float:wRX,Float:wRY,Float:wRZ,sMoney,sAmmo,sDrugs,Text3D:sText }
new House[MAX_HOUSES][hInfo], Houses = 0;

enum bInfo { bID, bOwner[MAX_PLAYER_NAME], Float:bX, Float:bY, Float:bZ, Float:bIX, Float:bIY, Float:bIZ, Float:bPX, Float:bPY, Float:bPZ, bPrice, bLock, bInt, bType, bCost, bVW, bName[24], bCommunal, bIncome, bPickup[3], bIcon, bProduct, Text3D:bText }
new
	Business[MAX_BIZNES][bInfo], Businesses = 0;

enum wInfo { wID, wName[24], wMoney, wAmmo, wDrugs, Float:wX, Float:wY, Float:wZ, wFraction }
new Ware[14][wInfo], Wars = 0;

enum aInfo { aID, Float:aX, Float:aY, Float:aZ, Float:aRX, Float:aRY, Float:aRZ }
new Atm[MAX_ATMS][aInfo],atm,Atms;

enum hiInfo
{
    Float:hiX,
	Float:hiY,
	Float:hiZ,
	hiInt
};

new Ints[][hiInfo] =
{
    {235.2729,1186.6792,1080.2578,3}, {226.7885,1239.9581,1082.1406,2},
    {223.043991,1289.259888,1082.199951,1}, {225.7228,1021.4439,1084.0177,7},
    {295.1349,1472.2554,1080.2578,15}, {327.9419,1477.7242,1084.4375,15},
    {387.2256,1471.6602,1080.1949,15}, {2214.3853,-1150.5216,1025.7969,15},
    {2468.8435,-1698.3000,1013.5078,2}, {2251.85,-1138.16,1050.63,9},
    {2270.4192,-1210.4694,1047.5625,10}, {2496.0000,-1692.0834,1014.7422,3},
    {1298.8008,-796.8387,1084.0078,5}, {2259.3813,-1135.8168,1050.6403,10},
    {2365.2283,-1135.5980,1050.8826,8}, {2324.3735,-1149.5469,1050.7101,12},
    {2233.6013,-1115.2625,1050.8828,5}, {2317.7849,-1026.7660,1050.2178,9},
    {226.2956,1114.2144,1080.9929,5}, {446.3247,509.9662,1001.4195,12},
    {447.0615,1397.0634,1084.3047,2}, {261.0322,1284.2946,1080.2578,4},
    {306.1966,307.819,1003.3047,4}, {23.9752,1340.1592,1084.3750,10},
    {221.9219,1140.1938,1082.6094,4}, {-260.4861,1456.7474,1084.3672,4},
    {234.0683,1063.7152,1084.2123,6}, {-68.7855,1351.1959,1080.2109,6},
    {-283.4380,1471.1089,1084.3750,15}, {-42.5952,1405.4697,1084.4297,8},
    {83.0813,1322.2817,1083.8662,9}, {22.8343,1403.3235,1084.4370,5},
    {243.7175,305.0327,999.1484,1}, {2218.4031,-1076.3712,1050.4844,1}
};

enum biInfo
{
    Float:biX,Float:biY,Float:biZ,biInt
};
new BInts[][biInfo] =
{
    {460.5565,-88.6059,999.5546,4},
	{362.8727,-75.1703,1001.5078,10},
	{364.9013,-11.7618,1001.8515,9},
	{372.3661,-133.5245,1001.4921,5},
	{377.1179,-193.3061,1000.6328,17},
	{-2240.7827,137.2179,1035.4140,6},
	{-100.3088,-25.0384,1000.7187,3},
	{-25.8655,-188.2894,1003.5468,0},
	{6.0392,-31.7611,1003.5494,10},
	{-31.0350,-92.0112,1003.5468,18},
	{-25.8903,-141.4185,1003.5468,16},
	{-27.2182,-31.7608,1003.5572,4},
	{-27.4584,-58.1958,1003.5468,6},
	{834.6683,7.4049,1004.1870,3},
	{207.6767,-111.2668,1005.1328,15},
	{204.3454,-168.7704,1000.5234,0},
	{207.0198,-140.3763,1003.5078,3},
	{203.7683,-50.6646,1001.8046,1},
	{227.4698,-8.1981,1002.2109,5},
	{161.3930,-97.1108,1001.8046,18},
	{315.7442,-143.6632,999.6015,7},
	{285.3699,-41.7166,1001.5156,1},
	{285.7845,-86.7201,1001.5228,4},
	{296.7973,-112.0710,1001.5156,6},
	{316.3183,-170.2974,999.5937,6},
	{0.0,0.0,0.0,0}
};

new
	objects[300], cobjects,
	grovecar[2], ballascar[2], taxicar[2], rentcar[2], mailcar[2], vagoscar[2], azteccar[2], rifacar[2], armycar[2], pd[2], fbicar[2], drivingcar[2], sfncar[2], truckcar[2], cnncar[2], srccar[2],
	pickup[51],
	warehousetext[200],
	Text3D:warehouset[10];

enum gInfo { gID ,gFraction, Float:gminX, Float:gminY, Float:gmaxX, Float:gmaxY, gZone, gWar, gTime };
new
	Zone[100][gInfo],
	ZoneOnBattle[sizeof(Zone)],
	InWar[6];

new
	bool:Arended[MAX_VEHICLES],
	taximans = 0,
	Fares[MAX_VEHICLES],
	Text3D:Fare[MAX_VEHICLES],

	Float:jP[29][3] = {
	{2557.199707, -555.663024, 115.321357},
	{2554.412597, -565.088012, 118.204284},
	{2559.945556, -563.907714, 118.252197},
	{2564.978759, -563.328918, 117.356834},
	{2567.812500, -559.626037, 115.274276},
	{2582.209716, -562.532043, 111.024909},
	{2580.091308, -570.622558, 114.349761},
	{2573.497314, -572.345703, 117.131118},
	{2567.951171, -578.486267, 120.875595},
	{2579.454345, -585.047180, 119.770965},
	{2575.132080, -591.728271, 123.273986},
	{2569.281250, -594.134948, 125.273284},
	{2561.898193, -594.605651, 127.140510},
	{2549.882080, -594.563476, 125.199768},
	{2535.989013, -594.767944, 122.326057},
	{2539.217285, -583.724304, 120.655090},
	{2543.427246, -601.693298, 125.489051},
	{2549.166992, -603.435668, 127.339965},
	{2554.781005, -609.047058, 130.598937},
	{2556.480468, -622.731567, 136.000488},
	{2561.696533, -630.167907, 136.162261},
	{2567.692138, -632.806213, 135.983520},
	{2570.412109, -639.199645, 136.224578},
	{2576.758300, -648.528991, 136.348007},
	{2583.934570, -649.001342, 135.955886},
	{2585.678466, -655.273071, 136.107788},
	{2580.822021, -657.501831, 136.475448},
	{2572.254394, -651.785339, 136.736724},
	{2564.565673, -646.437500, 136.962463}
	},

	gatearmy[3][2],
	LSW = 15000,  LVW = 1000, LVWE = 35,
	Text3D:LSWtext,
	Text3D:LVWtext,
	Text3D:LVWEtext,
	haulammo, ammolv, hauleat, eatlv, pickjob,
	hauls[7][2],
	Text3D:haulstext[7],
	haulspu[7], haulspl[7], haulspue, haulsple,
	Area,Truck,Area51, // AREAS
	bool:Alarm,
	PayDay = 0,
	strs[255+1],

	Float:tH1[3][3] = {
	{979.7341,2134.1187,10.8203},
	{2842.1775,902.4745,10.7578},
	{-2447.0544,740.8016,35.0156}
	},
	//Нефть
	Float:tH2[3][3] = {
	{-1052.4037,-652.3160,32.0078},
	{2647.9568,-1473.5526,30.4507},
	{-2267.5535,541.3361,35.0156}
	},
	//Продукты
	Float:tH3[3][3] = {
	{-2267.5535,541.3361,35.0156},
	{-1479.0654,2658.2813,55.8359},
	{1767.1118,-1860.1760,13.5791}
	},
	//Зерно
	Float:tH4[3][3] = {
	{-376.5928,-1423.2186,25.7266},
	{-1056.2471,-1205.1371,129.0166},
	{-1725.4534,-121.6313,3.5489}
	},

	SymbolPrice = 12,
	ad[116+1],
	Repair[10],
	Float:RepairZone[10][2] =
	{
	    {1025.05, -1024.23},
	    {487.68, -1740.87},
	    {-1420.73, 2583.37},
	    {-1904.39, 284.97},
	    {1975.60, 2162.16},
	    {-2425.91, 1022.33},
	    {2065.38, -1831.51},
	    {-99.55, 1118.36},
	    {721.07, -455.94},
	    {2393.74, 1493.01}
	};

enum BooleanVVar:(<<= 1)
{
	engines = 1,
	light,
	lock,
	limit
}

new BooleanVVar:VVB[MAX_VEHICLES], Track, droped, DropedItem[MAX_DROPED_ITEMS][2],
	GWars[2], InZone[sizeof(Zone)][6];
	
	
enum mInfo
{
	mMoney,
	mHouse,
	mDrugs,
	mUpgrade
}

new Mafia[3][mInfo];
