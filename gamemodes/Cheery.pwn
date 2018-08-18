@___If_u_can_read_this_u_r_nerd();
@___If_u_can_read_this_u_r_nerd()
{
    #emit    stack    0x7FFFFFFF
    #emit    inc.s    cellmax
    static const ___[][] = {"Copyrights", "Daniel_Cortez"};
    #emit    retn
    #emit    load.s.pri    ___
    #emit    proc
    #emit    proc
    #emit    fill    cellmax
    #emit    proc
    #emit    stack    1
    #emit    stor.alt    ___
    #emit    strb.i    2
    #emit    switch    4
    #emit    retn
    L1:
    #emit    jump    L1
    #emit    zero    cellmin
}


#include <a_samp>
#include <a_mysql>
#include <sscanf2>

#include <Pawn_CMD>

#include <foreach>
#include <streamer>

#define CopyRightString 	"(c) Copyright 2014 by Panteleev"

#include "../lib/defines"
#include "../lib/vars"
#include "../lib/functions"
#include "../lib/commands"

main() print(CopyRightString);

public OnGameModeInit() {

	new gm_Name_str[27];
	format(gm_Name_str, sizeof(gm_Name_str), "Light RP (%s)", __date);

    SetGameModeText(gm_Name_str);
    
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);

	Iter_Init(StreamedPlayers);

	ConnectMySQL();
	

	CreatePickups();
 	CreateObjects();
 	LoadTextDraws();
 	CreateVehicles();

	ShowPlayerMarkers(PLAYER_MARKERS_MODE_STREAMED);
	ShowNameTags(true);
	SetNameTagDrawDistance(25.0);
	EnableStuntBonusForAll(false);
	DisableInteriorEnterExits();
	ManualVehicleEngineAndLights();
	AllowInteriorWeapons(true);
	LimitPlayerMarkerRadius(30.0);

	new hour, minute, second;
 	gettime(hour, minute, second);

 	SetTimer("GetTimer",1000,true);

	Timer[0] = gettime()+1;
 	Timer[1] = gettime()+1800;

    
   	/*new
			hour;
	gettime(hour, _, _);*/

	if (hour < 0)
	{
		hour = hour + 24;
	}
	else if (hour > 23)
	{
		hour = hour - 24;
	}

	SetWorldTime(hour);
	SetWeather(CurrentWeather);
    
	for(new i; i < MAX_VEHICLES; i++) {
 		Fuel[i] = 200;
	  	SetVehicleNumberPlate(i, "Light RP");
	}
	
    //====
    rMenu = CreateMenu(" ", 1, 26.000000, 140.000000, 70.0, 100.0);
    SetMenuColumnHeader(rMenu, 0, "ACP CRP");
	AddMenuItem(rMenu,0,"Refresh");
	AddMenuItem(rMenu,0,"Kick");
	AddMenuItem(rMenu,0,"Warn");
	AddMenuItem(rMenu,0,"Ban");
	AddMenuItem(rMenu,0,"GMTest");
	AddMenuItem(rMenu,0,"Slap");
	AddMenuItem(rMenu,0,"Stats");
	AddMenuItem(rMenu,0,"OFF");
	//====
	
	
	Truck = CreateDynamicSphere(-52.3652,-221.7758,5.4297,8.0,-1,-1,-1);
	Area51 = CreateDynamicCube(-103.125,1645.3125,8.9843,442.96875,2179.6875,251.3157,-1,-1,-1);
	
	for(new i; i < sizeof(Repair); i++) {
 		Repair[i] = CreateDynamicCircle(RepairZone[i][0], RepairZone[i][1], 10, -1, -1, -1);
	}

	return true;
}

stock ConnectMySQL()
{
    new MySQLOpt: option_id = mysql_init_options();

    mysql_set_option(option_id, AUTO_RECONNECT, true); // it automatically reconnects when loosing connection to mysql server

	connects = mysql_connect(SQL_HOST, SQL_USER, SQL_PASS, SQL_DB, option_id);

	mysql_log(ERROR | WARNING);

	print(!"===============================================================================");
	print((mysql_errno()) ? !"                        Подключение не удалось                        "// используются тернарные условия ? :
						: !"                        Подключение успешно установлено                        ");
 	print(!"===============================================================================");
 	

	//mysql_function_query(connects, "SET NAMES cp1251", false, "", "");
	/*
	*   Кодировка для MySQL
	*/
	mysql_function_query(connects, !"SET CHARSET 'utf8'", false, "","");
	mysql_function_query(connects, !"SET NAMES 'utf8'", false, "","");
	mysql_function_query(connects, !"SET character_set_client = 'cp1251'", false, "","");
	mysql_function_query(connects, !"SET character_set_connection = 'cp1251'", false, "","");
	mysql_function_query(connects, !"SET character_set_results = 'cp1251'", false, "","");
	mysql_function_query(connects, !"SET SESSION collation_connection = 'utf8_general_ci'", false, "","");
	
	
	mysql_function_query(connects, !"SELECT HIGH_PRIORITY * FROM `houses`", 	true,	"LoadHouses", "");
   	mysql_function_query(connects, !"SELECT HIGH_PRIORITY * FROM `buisnesses`", true,	"LoadBusiness", "");
	mysql_function_query(connects, !"SELECT HIGH_PRIORITY * FROM `warehouses`", true, 	"LoadWarehouses", "");
 	mysql_function_query(connects, !"SELECT HIGH_PRIORITY * FROM `gangzones`", 	true,	"LoadGangZones", "");
 	mysql_function_query(connects, !"SELECT HIGH_PRIORITY * FROM `atm`", 		true,		"LoadAtm", "");
}

public OnGameModeExit()
{
    GlobalSave();
    
    mysql_close(connects);
    
	print("Сервер успешно выключен!");
	return true;
}

public OnPlayerRequestClass(playerid, classid)
{
	if(!Player[playerid][PlayerLogged]) {

		SetPlayerInterior(playerid, 0);
	 	SetPlayerFacingAngle(playerid, 90);
	  	SetCameraBehindPlayer(playerid);
		SetPlayerCameraPos(playerid, 1360.9023,-1571.8125,116.9395);
	 	SetPlayerCameraLookAt(playerid, 1480.2584,-1734.5576,18.6296);
	}
	else SetSpawnInfo(playerid,0,1,0.0,0.0,0.0,0.0,0,0,0,0,0,0), SpawnPlayer(playerid);
 	return true;
}

public OnPlayerConnect(playerid)
{
	ResetPlayerInfo(playerid);
	SetPlayerColor(playerid,0xFFFFFF33);

	GetPlayerName(playerid, Player[playerid][pName], MAX_PLAYER_NAME);
 	GetPlayerIp(playerid,Player[playerid][pIP], 16);

	mysql_format(connects, query,60,"SELECT * FROM `ips` WHERE `IP` = '%s' LIMIT 1", Ip(playerid));
    mysql_tquery(connects, query, "CheckIP", "i", playerid);
    
    
    player_other_timer[playerid] = SetTimerEx("PlayerUpdate", 250, true, "d", playerid);
    

	for(new i = 0; i < 100; i++) GangZoneShowForPlayer(playerid,Zone[i][gID], GetGangZoneColor(i));

	SetPVarInt(playerid,"LoginTime",gettime()+3);

	PreloadPlayerAnimations(playerid);
	LoadPlayerTextDraws(playerid);
 	SetPVarInt(playerid,"CheckSpawn",0);

	SetPVarInt(playerid,"AC_VID",INVALID_VEHICLE_ID), SetPVarInt(playerid,"ReconedID",INVALID_PLAYER_ID), SetPVarInt(playerid,"CalledID",INVALID_PLAYER_ID), SetPVarInt(playerid,"TaxiCall",INVALID_PLAYER_ID);
	SetPVarInt(playerid,"BusCheck",-1), SetPVarInt(playerid,"Race",-1), SetPVarInt(playerid,"SelectSlot",-2);
	//lva
	RemoveBuildingForPlayer(playerid, 1411, 347.1953, 1799.2656, 18.7578, 0.25);
	RemoveBuildingForPlayer(playerid, 1411, 342.9375, 1796.2891, 18.7578, 0.25);
	RemoveBuildingForPlayer(playerid, 16094, 191.1406, 1870.0391, 21.4766, 0.25);
 	//lsa
	RemoveBuildingForPlayer(playerid, 3710, 2788.1563, -2455.8828, 16.7266, 0.25);
	RemoveBuildingForPlayer(playerid, 3761, 2783.7813, -2463.8203, 14.6328, 0.25);
	RemoveBuildingForPlayer(playerid, 3624, 2788.1563, -2455.8828, 16.7266, 0.25);
	RemoveBuildingForPlayer(playerid, 3761, 2783.7813, -2448.4766, 14.6328, 0.25);
	RemoveBuildingForPlayer(playerid, 1278, 2773.3438, -2443.1719, 26.7031, 0.25);
	RemoveBuildingForPlayer(playerid, 3761, 2791.9531, -2463.8203, 14.6328, 0.25);
	RemoveBuildingForPlayer(playerid, 3761, 2797.5156, -2448.3438, 14.6328, 0.25);
	RemoveBuildingForPlayer(playerid, 3761, 2791.9531, -2448.4766, 14.6328, 0.25);
	//fbi
	RemoveBuildingForPlayer(playerid, 1331, 1004.8125, 1068.0703, 10.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1331, 1002.5625, 1068.0703, 10.6250, 0.25);
	//ash
	RemoveBuildingForPlayer(playerid, 11372, -2076.4375, -107.9297, 36.9688, 0.25);
	RemoveBuildingForPlayer(playerid, 11014, -2076.4375, -107.9297, 36.9688, 0.25);
	//cnn
	RemoveBuildingForPlayer(playerid, 8260, 1544.9375, 947.6094, 13.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 8261, 1544.9375, 947.6094, 13.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 8300, 1542.6484, 998.8984, 12.8672, 0.25);
	RemoveBuildingForPlayer(playerid, 8301, 1542.6484, 998.8984, 12.8672, 0.25);
	RemoveBuildingForPlayer(playerid, 1440, 1531.3203, 924.4609, 10.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 1440, 1531.8906, 936.3672, 10.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 640, 1537.5703, 971.0078, 10.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 640, 1544.9844, 971.0078, 10.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 1334, 1518.2500, 971.4609, 10.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 1334, 1518.2500, 979.7656, 10.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 8302, 1528.8672, 976.2734, 11.1484, 0.25);
	RemoveBuildingForPlayer(playerid, 1687, 1549.6797, 936.6172, 21.0703, 0.25);
	RemoveBuildingForPlayer(playerid, 1331, 1557.6563, 970.5625, 10.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 1334, 1557.7422, 968.3125, 10.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 640, 1552.4688, 971.0078, 10.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 1340, 1558.1953, 979.4453, 10.9453, 0.25);
	RemoveBuildingForPlayer(playerid, 1438, 1524.7656, 991.6172, 9.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1438, 1543.3672, 981.5391, 9.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 640, 1553.7656, 1016.1328, 10.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 640, 1545.5156, 1016.1328, 10.5156, 0.25);
	//logo
	TextDrawShowForPlayer(playerid,LCheery), TextDrawShowForPlayer(playerid,LRole), TextDrawShowForPlayer(playerid,LPlay), TextDrawShowForPlayer(playerid,Lchit), TextDrawShowForPlayer(playerid,Ln1);

	mysql_format(connects, query, 70, "SELECT `Name` FROM `accounts` WHERE Name = '%s'", Name(playerid));
 	mysql_tquery(connects, query, "CheckPlayer","i", playerid);

	return true;
}

public OnPlayerDisconnect(playerid, reason)
{
    if(PlayerToZone(playerid,-103.125,1645.3125,442.96875,2179.6875) && PlayerGangster(playerid)) Player[playerid][pAmmo] -= 150;
    if(GetPVarInt(playerid,"TruckHaul") > 0)  DestroyVehicle(Player[playerid][Trailer]), Player[playerid][pMoney] -= 1800;
    if(GetPVarInt(playerid,"Cuffed") == 1 && Player[playerid][pWanted] > 0 && Player[playerid][pWanted] < 7) Player[playerid][pWanted] = 22*60;

	SaveAccount(playerid);

	if(GetPVarInt(playerid,"BuyCar") != 0) DestroyVehicle(Player[playerid][pCar][3]);
    if(GetPVarInt(playerid,"ReconedID") != INVALID_PLAYER_ID) {
 		SCM(GetPVarInt(playerid,"ReconedID"),0xFF0000FF,"Игрок отключился от сервера. Слежка прекращена!");

	  	callcmd::recon(GetPVarInt(playerid, "ReconedID"), "");
  	}
    if(Iter_Count(StreamedPlayers[playerid]) != 0) Iter_Clear(StreamedPlayers[playerid]);
    if(Player[playerid][pHouse] != 9999) if(Player[playerid][pCar][0] != -1) DestroyVehicle(Player[playerid][PlayerCar]);
    if(GetPVarInt(playerid,"TaxiJob") != 0) taximans--;
    
    memset(Player[playerid], 0, _:pInfo);// Чистим массив игрока
    
	printf("KILLTIMER = player_other_timer[playerid] = %d", player_other_timer[playerid]);
	KillTimer(player_other_timer[playerid]);// Убиваем таймер игрока
    
	return true;
}

public OnPlayerSpawn(playerid)
{
    if(!Player[playerid][PlayerLogged]) return SendClientMessage(playerid, 0xAC7575FF, "Необходимо авторизоваться!");

	SetPVarInt(playerid,"AirTime",3);

	DisablePlayerRaceCheckpoint(playerid), DisablePlayerCheckpoint(playerid);

	for(new i = 0; i < 10; i++) SetPlayerSkillLevel(playerid, i, Player[playerid][Skill][i]);

	if(GetPVarInt(playerid,"TruckHaul") > 0) DestroyVehicle(Player[playerid][Trailer]), SetPVarInt(playerid,"Job",0), SetPVarInt(playerid,"TruckJob",0), SetPVarInt(playerid,"TruckHaul",0), GameTextForPlayer(playerid,"~r~-1800$",2000,1), Player[playerid][pMoney] -= 1800, DisablePlayerRaceCheckpoint(playerid);

	SetPlayerSpawn(playerid), SetPVarInt(playerid,"CheckSpawn",1),SetPVarInt(playerid,"DialogActive",0);
	return true;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	if(PlayerGangster(playerid) && (GWars[0] > 0 || GWars[1] > 0)) {
		for(new g = 0; g < sizeof(Zone); g++) {
			if(!PlayerToZone(killerid, Zone[g][gminX],Zone[g][gminY],Zone[g][gmaxX],Zone[g][gmaxY])) continue;
			if(Player[playerid][pFraction][1] == Player[killerid][pFraction][1]) continue;
			InZone[g][Player[playerid][pFraction][1]]++;
			foreach(new i : Player) if(Player[i][pFraction][1] == Zone[g][gFraction] || Player[i][pFraction][1] == Zone[g][gWar]) SendDeathMessageToPlayer(i, killerid, playerid, reason);
			return true;
	}   }
	if(GetPVarInt(playerid,"TaxiJob") != 0) taximans--;
   	SetPVarInt(playerid,"CheckSpawn",0), SetPVarInt(playerid,"Job",0), SetPVarInt(playerid,"TaxiJob",0), SetPVarInt(playerid,"MailJob",0), SetPVarInt(playerid,"MailSend",0);
   	if(PlayerLaw(killerid) && PlayerToZone(killerid,-103.125,1645.3125,442.96875,2179.6875) && PlayerGangster(playerid)) SCM(killerid,0xFFFFFFFF,"Вы ранили бандита, {03c03c}премия в размере: 200$"), Player[killerid][pMoney] += 200;
	if(PlayerCF(killerid) && (0 < Player[playerid][pWanted] < 7)) Player[playerid][pWanted] = ((Player[playerid][pWanted]*2)*60)+7, SetPlayerWantedLevel(playerid,0), SCM(killerid,0xFFC800FF,"Приступник был ранен и доставлен в тюремный госпиталь!"), GameTextForPlayer(killerid,"~g~+350$",1000,1);
	if(!PlayerCF(killerid) && (0 < Player[killerid][pWanted] < 7)) {
        Player[killerid][pWanted] = ((2 + Player[killerid][pWanted]) > 6) ? 6 : (Player[killerid][pWanted]+2), SetPlayerWantedLevel(killerid,Player[killerid][pWanted]);
        format(strock,76,"[R] Диспетчер: Совершено убийство, подозреваемый: %s",Name(killerid));
        for(new i = 7; i < 10; i++) SendRadioMessage(i, 0x1faee9AA, strock);
	}
	return true;
}

public OnVehicleSpawn(vehicleid)
{
    if(vehicleid >= taxicar[0] && vehicleid <= mailcar[1] || vehicleid >= truckcar[0] && vehicleid <= truckcar[1])
	{
		foreach(new i : Player) if(Player[i][ArendedVehicle] == vehicleid)
		{
			Player[i][ArendedVehicle] = INVALID_VEHICLE_ID, Arended[vehicleid] = false;
			if(vehicleid >= truckcar[0] && vehicleid <= truckcar[1] && (Player[i][ArendedVehicle] == vehicleid && GetPVarInt(i,"TruckHaul") > 0)) DestroyVehicle(Player[i][Trailer]), Player[i][pMoney] -= 1800, GameTextForPlayer(i,"~r~-1800$",2000,1);
	}	}
	if(Fares[vehicleid] != 0) Delete3DTextLabel(Fare[vehicleid]), Fares[vehicleid] = 0;
	if(hauls[vehicleid-77][1] != 0) DestroyDynamicPickup(haulspl[vehicleid-77]), DestroyDynamicPickup(haulsple), DestroyDynamicPickup(haulspu[vehicleid-77]), DestroyDynamicPickup(haulspue), DestroyDynamic3DTextLabel(haulstext[vehicleid-77]);
	return true;
}

public OnVehicleDeath(vehicleid, killerid) return true;

public OnPlayerText(playerid, text[])
{
	if(Player[playerid][pMute] != 0 && Player[playerid][pMute] < gettime()) Player[playerid][pMute] = 0;

	if(Player[playerid][pMute] > gettime()) {
		SCM(playerid,0xFFFFFFFF,"У вас {1faee9}бан чата!");
		return false;
	}

	if(GetPVarInt(playerid,"Chat") > gettime()) {
		SCM(playerid,0xFF0000FF,"Не флудите!");
		return false;
	}
	
	
	new strocks[144+1];
 	if(GetPVarInt(playerid,"Called") >= 3)
 	{
 		format(strocks, sizeof(strocks), "[Т] %s: %s", Name(playerid), text);

		SCM(GetPVarInt(playerid,"CalledID"),0xFFEE00FF,strocks);
 		SetPlayerChatBubble(playerid, strocks, 0xFFEE00FF, 15.0, 4000);
		//SendClientsMessage(15.0, playerid, strocks,COLOR_FADE2,COLOR_FADE2,COLOR_FADE2);
		ProxDetector(playerid, 15.0, COLOR_FADE2, strocks);
 	    return false;
 	}
  	if(strcmp(text, "чВ", true) == 0 || strcmp(text, ":D", true) == 0 || strcmp(text, "хД", true) == 0 || strcmp(text, "xD", true) == 0 || strcmp(text, "lol", true) == 0 || strcmp(text, "лол", true) == 0) {
		format(strocks,32,"%s смеётся",Name(playerid));
		ProxDetector(playerid, 25.0, COLOR_PURPLE, strocks);

		SetPlayerChatBubble(playerid, "смеётся",COLOR_PURPLE,30.0,10000);
		return false;
	}
	else if(strcmp(text, ")", true) == 0 || strcmp(text, "))", true) == 0) {
	    format(strocks,34,"%s улыбается",Name(playerid));
	    ProxDetector(playerid, 25.0, COLOR_PURPLE, strocks);
	    
		SetPlayerChatBubble(playerid, "улыбается",COLOR_PURPLE,30.0,10000);
		return false;
	}
	else if(strcmp(text, "(", true) == 0 || strcmp(text, ":C", true) == 0 || strcmp(text, "((", true) == 0) {
		format(strocks,32,"%s грустит",Name(playerid));
		SendClientsMessage(25.0, playerid, strocks,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		ProxDetector(playerid, 25.0, COLOR_PURPLE, strocks);
		
		SetPlayerChatBubble(playerid, "грустит",COLOR_PURPLE,30.0,10000);
		return false;
	}
	SetPlayerChatBubble(playerid, text, 0x34c924FF, 40.0, 7000);
	
    format(strocks, sizeof(strocks), "%s говорит: %s", Name(playerid), text);
	ProxDetector(playerid, 40.0, COLOR_FADE1, strocks);
	
 	if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_NONE) ApplyAnimation(playerid, "PED", "IDLE_CHAT",4.1,0,1,1,1,1,1),SetTimerEx("ClearChat", 1300, 0, "i", playerid);
 	SetPVarInt(playerid,"Chat", (Player[playerid][pLevel] <= 2) ? (gettime()+2) : (gettime()+1));
	return true;
}

/*stock ReplaceText(text[], &replacedText[]) {

}*/

public OnPlayerCommandText(playerid, cmdtext[])
{
	return true;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) return SetPVarInt(playerid,"AC_VID",vehicleid);

public OnPlayerExitVehicle(playerid, vehicleid) {
	if(GetPlayerState(GetPVarInt(playerid,"TaxiCall")) == PLAYER_STATE_DRIVER)  SetPVarInt(GetPVarInt(playerid,"TaxiCall"),"TaxiCall",INVALID_PLAYER_ID),SCM(GetPVarInt(playerid,"TaxiCall"),0xFFFFFFFF,"Пассажир {1faee9}вышел из вашего автомобиля!"), SetPVarInt(playerid,"TaxiCall",INVALID_PLAYER_ID);
	if(GetPVarInt(playerid,"TruckJob") > 0 && (GetPlayerVehicleID(playerid) >= truckcar[0] && GetPlayerVehicleID(playerid) <= truckcar[1]) && Player[playerid][ArendedVehicle] == vehicleid) SCM(playerid,0xAC7575FF,"У вас есть 1 минута на то, чтобы вернуться в ваш грузовик!");
	return true;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	#define	vehicleid	GetPlayerVehicleID(playerid)
	if(newstate == PLAYER_STATE_DRIVER)
	{
	    if((Player[playerid][Licenses] & (1<<0) == 0) && GetPVarInt(playerid,"Lesson") == 0 && !PlayerInBoat(GetPlayerVehicleID(playerid)) && !PlayerInBike(GetPlayerVehicleID(playerid)) && !PlayerInPlane(GetPlayerVehicleID(playerid))) SetPlayerDrunkLevel(playerid,6000), SCM(playerid,0xAC7575FF,"[Мысли]: Я же не умею водить! Нужно быть аккуратнее..."), SetPVarInt(playerid, "DrunkDriving", 1);

		if(!PlayerInBoat(GetPlayerVehicleID(playerid)) && !PlayerInBike(GetPlayerVehicleID(playerid)) && !PlayerInPlane(GetPlayerVehicleID(playerid)))
		{
			SCM(playerid,0x1faee9FF,"Для того чтобы завести или выключить двигатель нажмите {ffffff}'CTRL'");
			PlayerTextDrawSetString(playerid,sengine[playerid], (VVB<vehicleid:engines>) ? ("~g~ENGINE") : ("~r~ENGINE")),
			PlayerTextDrawSetString(playerid,slights[playerid], (VVB<vehicleid:light>) ? ("~g~LIGHTS") : ("~r~LIGHTS")),
			PlayerTextDrawSetString(playerid,slimit[playerid], (VVB<vehicleid:limit>) ? ("~r~SPEED LIMIT") : ("~g~SPEED LIMIT"));
			TextDrawShowForPlayer(playerid,sbox);
	    	TextDrawShowForPlayer(playerid,skmh);
	    	TextDrawShowForPlayer(playerid,sfuel);
	    	PlayerTextDrawShow(playerid,sengine[playerid]);
	     	PlayerTextDrawShow(playerid,slights[playerid]);
	      	PlayerTextDrawShow(playerid,slimit[playerid]);
	       	PlayerTextDrawShow(playerid,slock[playerid]);
	        PlayerTextDrawSetPreviewModel(playerid,smodel[playerid], GetVehicleModel(GetPlayerVehicleID(playerid)));
	        PlayerTextDrawSetPreviewVehCol(playerid,smodel[playerid], 3, 3);
	        PlayerTextDrawShow(playerid,smodel[playerid]);
	        PlayerTextDrawShow(playerid,sspeed[playerid]);
	        PlayerTextDrawShow(playerid,sfuelv[playerid]);
	        if(vehicleid == Player[playerid][PlayerCar]) TextDrawShowForPlayer(playerid,smilage[playerid]);
        }
		if((vehicleid >= grovecar[0] && vehicleid <= grovecar[1]) && Player[playerid][pFraction][1] != 1) SendClientMessage(playerid,COLOR_GRAD1,"Вы не член банды Grove Street Gang!"), RemovePlayerFromVehicle(playerid);
		else if((vehicleid >= ballascar[0] && vehicleid <= ballascar[1]) && Player[playerid][pFraction][1] != 2) SendClientMessage(playerid,COLOR_GRAD1,"Вы не член банды The Ballas Gang!"), RemovePlayerFromVehicle(playerid);
		else if((vehicleid >= vagoscar[0] && vehicleid <= vagoscar[1]) && Player[playerid][pFraction][1] != 3) SendClientMessage(playerid,COLOR_GRAD1,"Вы не член банды Los Santos Gang!"), RemovePlayerFromVehicle(playerid);
		else if((vehicleid >= azteccar[0] && vehicleid <= azteccar[1]) && Player[playerid][pFraction][1] != 4) SendClientMessage(playerid,COLOR_GRAD1,"Вы не член банды Various Los Aztecas Gang!"), RemovePlayerFromVehicle(playerid);
		else if((vehicleid >= rifacar[0] && vehicleid <= rifacar[1]) && Player[playerid][pFraction][1] != 5) SendClientMessage(playerid,COLOR_GRAD1,"Вы не член банды The Rifa Gang!"), RemovePlayerFromVehicle(playerid);
		else if(vehicleid >= taxicar[0] && vehicleid <= taxicar[1])
		{
			if (GetPVarInt(playerid,"TaxiJob") == 1) {
                if(Arended[vehicleid] && Player[playerid][ArendedVehicle] != vehicleid || !Arended[vehicleid] && Player[playerid][ArendedVehicle] != INVALID_VEHICLE_ID) SCM(playerid,COLOR_WHITE,"Данный автомобиль {1faee9}уже арендован либо вы уже арендовали транспорт!"), RemovePlayerFromVehicle(playerid);
				if(!Arended[vehicleid] && Player[playerid][ArendedVehicle] == INVALID_VEHICLE_ID) ShowPlayerDialog(playerid,25,DIALOG_STYLE_MSGBOX,"{1faee9}Аренда транспорта","{ffffff}Данный транспорт пренадлежит государству и стоит денег.\n{cc7722}Цена аренды составляет - {03c03c}100$","Аренда","Отмена");
			}
			else SendClientMessage(playerid,COLOR_GRAD1,"Вы не работаете в фирме TAXI!"), RemovePlayerFromVehicle(playerid);
		}
		else if(vehicleid >= rentcar[0] && vehicleid <= rentcar[1]) {
			if(Arended[vehicleid] && Player[playerid][ArendedVehicle] != vehicleid || !Arended[vehicleid] && Player[playerid][ArendedVehicle] != INVALID_VEHICLE_ID) SCM(playerid,COLOR_WHITE,"Данный автомобиль {1faee9}уже арендован либо вы уже арендовали транспорт!"), RemovePlayerFromVehicle(playerid);
			if(!Arended[vehicleid] && Player[playerid][ArendedVehicle] == INVALID_VEHICLE_ID) ShowPlayerDialog(playerid,25,DIALOG_STYLE_MSGBOX,"{1faee9}Аренда транспорта","{ffffff}Данный транспорт пренадлежит государству и стоит денег.\n{cc7722}Цена аренды составляет - {03c03c}550$","Аренда","Отмена");
		}
        else if(vehicleid >= mailcar[0] && vehicleid <= mailcar[1]) {
			if (GetPVarInt(playerid,"MailJob") == 1) {
                if(Arended[vehicleid] && Player[playerid][ArendedVehicle] != vehicleid || !Arended[vehicleid] && Player[playerid][ArendedVehicle] != INVALID_VEHICLE_ID) SCM(playerid,COLOR_WHITE,"Данный автомобиль {1faee9}уже арендован либо вы уже арендовали транспорт!"), RemovePlayerFromVehicle(playerid);
				if(!Arended[vehicleid] && Player[playerid][ArendedVehicle] == INVALID_VEHICLE_ID) ShowPlayerDialog(playerid,25,DIALOG_STYLE_MSGBOX,"{1faee9}Аренда транспорта","{ffffff}Данный транспорт пренадлежит государству и стоит денег.\n{cc7722}Цена аренды составляет - {03c03c}200$","Аренда","Отмена");
			}
			else SendClientMessage(playerid,COLOR_GRAD1,"Вы не работаете Развозчиком Почты!"), RemovePlayerFromVehicle(playerid);
		}
		else if(vehicleid >= truckcar[0] && vehicleid <= truckcar[1]) {
			if (GetPVarInt(playerid,"TruckJob") == 1) {
				if(Arended[vehicleid] && Player[playerid][ArendedVehicle] != vehicleid || !Arended[vehicleid] && Player[playerid][ArendedVehicle] != INVALID_VEHICLE_ID) SCM(playerid,COLOR_WHITE,"Данный автомобиль {1faee9}уже арендован либо вы уже арендовали транспорт!"), RemovePlayerFromVehicle(playerid);
				if(!Arended[vehicleid] && Player[playerid][ArendedVehicle] == INVALID_VEHICLE_ID) ShowPlayerDialog(playerid,25,DIALOG_STYLE_MSGBOX,"{1faee9}Аренда транспорта","{ffffff}Данный транспорт пренадлежит государству и стоит денег.\n{cc7722}Цена аренды составляет - {03c03c}1000$","Аренда","Отмена");
			}
			else SendClientMessage(playerid,COLOR_GRAD1,"Вы не работаете Дальнобойщиком!"), RemovePlayerFromVehicle(playerid);
		}
		else if((vehicleid >= armycar[0] && vehicleid <= armycar[1]) && Player[playerid][pFraction][1] != 6) SendClientMessage(playerid,COLOR_GRAD1,"Вы не служите в армии!"), RemovePlayerFromVehicle(playerid);
		else if((vehicleid >= pd[0] && vehicleid <= pd[1]) && !PlayerCop(playerid)) SendClientMessage(playerid,COLOR_GRAD1,"Вы не офицер полиции штата!"), RemovePlayerFromVehicle(playerid);
		else if((vehicleid >= fbicar[0] && vehicleid <= fbicar[1]) && Player[playerid][pFraction][1] != 10) SendClientMessage(playerid,COLOR_GRAD1,"Вы не агент FBI!"), RemovePlayerFromVehicle(playerid);
		else if((vehicleid >= sfncar[0] && vehicleid <= sfncar[1]) && Player[playerid][pFraction][1] != 13) SendClientMessage(playerid,COLOR_GRAD1,"Вы не работник SAN!"), RemovePlayerFromVehicle(playerid);
		else if((vehicleid >= cnncar[0] && vehicleid <= cnncar[1]) && Player[playerid][pFraction][1] != 14) SendClientMessage(playerid,COLOR_GRAD1,"Вы не работник CNN!"), RemovePlayerFromVehicle(playerid);
		else if((vehicleid >= srccar[0] && vehicleid <= srccar[1]) && Player[playerid][pFraction][1] != 18) SendClientMessage(playerid,COLOR_GRAD1,"У вас нет ключей от этого автомобиля."), RemovePlayerFromVehicle(playerid);
		else if(vehicleid >= drivingcar[0] && vehicleid <= drivingcar[1]) {
		    if (Player[playerid][pFraction][1] == 12 || GetPVarInt(playerid,"Lesson") == 1) {
		        if(GetPVarInt(playerid,"Lesson") == 1) SetPlayerRaceCheckpoint(playerid,1,-2055.235107,-94.230751,34.993179,-2055.235107,-94.230751,34.993179,3.0), SetPVarInt(playerid,"LessonCheck", 1), SCM(playerid,-1,"Для сдачи экзамена {03c03c}следуйте по маршруту!");
		    }
		    else SendClientMessage(playerid,COLOR_GRAD1,"Вы не сотрудник Автошколы!"), RemovePlayerFromVehicle(playerid);
		}
		if((GetTickCount() - GetPVarInt(playerid, "AC_CarTime")) < 500)	{
            SetPVarInt(playerid, "AC_CarSpam", GetPVarInt(playerid, "AC_CarSpam") + 1);
            if(GetPVarInt(playerid, "AC_CarSpam") >= 3) SCM(playerid,COLOR_LIGHTRED,"Вы были кикнуты. Опкод: {ffffff}A5C0S0"), KickEx(playerid);
        }
        SetPVarInt(playerid, "AC_CarTime", GetTickCount());
	}
	if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT && (Player[playerid][Licenses] & (1<<0) == 0)) SetPVarInt(playerid,"DrunkDriving",0), SetPlayerDrunkLevel(playerid,0);
    if(newstate == PLAYER_STATE_ONFOOT) {
	    TextDrawHideForPlayer(playerid,sbox);
	    TextDrawHideForPlayer(playerid,skmh);
	    TextDrawHideForPlayer(playerid,sfuel);
	    PlayerTextDrawHide(playerid,sengine[playerid]);
	    PlayerTextDrawHide(playerid,slights[playerid]);
	    PlayerTextDrawHide(playerid,slimit[playerid]);
	    PlayerTextDrawHide(playerid,slock[playerid]);
	    TextDrawHideForPlayer(playerid,smilage[playerid]);
    	PlayerTextDrawHide(playerid,smodel[playerid]);
    	PlayerTextDrawHide(playerid,sspeed[playerid]);
    	PlayerTextDrawHide(playerid,sfuelv[playerid]);
	}
   	if(newstate == PLAYER_STATE_PASSENGER) {
        if(Fares[vehicleid] != 0) {
			if(Player[playerid][pMoney] < Fares[vehicleid]) { RemovePlayerFromVehicle(playerid), SCM(playerid,0xFFFFFFFF,"У вас {1faee9}недостаточно денег для поездки!"); return true; }
		 	Player[playerid][pMoney] -= Fares[vehicleid];
			foreach(new i : Player) if(GetPlayerVehicleID(i) == vehicleid && GetPlayerState(i) == PLAYER_STATE_DRIVER && GetPVarInt(i,"TaxiJob") == 1) SetPVarInt(i,"Cost",GetPVarInt(i,"Cost")+Fares[vehicleid]), GameTextForPlayer(playerid, "~r~-$", 3000, 1),
			SCM(i,0x1faee9FF,"Пассажир сел в Ваш автомобиль, деньги взымаются по тарифу. {ffffff}Забрать деньги вы сможете после конца рабочего дня!"), GameTextForPlayer(i, "~g~+$", 1000, 3);
	}   }
	#undef  vehicleid
	return true;
}

public OnPlayerEnterCheckpoint(playerid)
{
    DisablePlayerCheckpoint(playerid);
    if(GetPVarInt(playerid,"MailSend") == 1) {
    	SCM(playerid,0x1faee9FF,"Вы забрали посылку.{ffffff} Продолжайте работу!"), SetPVarInt(playerid,"MainSend",2);
	    new string[68], mail[12], rh = random(Houses+1);
	    if(rh == 0) rh = 1;
		switch(random(7)) {
		    case 0: mail = "письмо";
		    case 1: mail = "посылку";
		    case 2: mail = "поветску";
		    case 3: mail = "газету";
		    case 4: mail = "журнал";
		    case 5: mail = "счета";
		    default: mail = "письма";
		}
		format(string,68,"Нужно доставить {ffffff}%s {1faee9}к дому {ffffff}№%d!",mail,rh);
		SCM(playerid,0x1faee9FF,string);
		SetPlayerRaceCheckpoint(playerid,1,House[rh][cX],House[rh][cY],House[rh][cZ],0.0,0.0,0.0,5.0);
		SetPlayerAttachedObject(playerid,0,1210, 6, 0.279000, 0.087000, -0.009000, 0.000000, -86.700035, -0.399999, 1.000000, 1.000000, 1.000000);
		SetPVarInt(playerid,"MainSend",2);
		return true;
	}
	if(GetPVarInt(playerid,"ShahtaSend") == 1) {
		ApplyAnimation(playerid, "BASEBALL", "BAT_4", 4.1, 0, 1, 1, 1, 1);
		SetTimerEx("Carry", 1400, 0, "dd", playerid,1);
        SetPlayerAttachedObject(playerid, 2, 3931, 1, 0.000000, 0.427999, -0.108999, 0.000000, 0.000000, 0.000000, 0.432999, 0.477999, 0.535999);
        SetPlayerCheckpoint(playerid,2544.184814, -463.555358, 84.762008,1.2);
        SCM(playerid,0x1faee9FF,"Вы выкопали {ffffff}несколько килограмм железной руды!");
        SetPVarInt(playerid,"ShahtaSend",2);
        return true;
	}
	if(GetPVarInt(playerid,"ShahtaSend") == 2) {
 		ApplyAnimation(playerid, "CARRY", "PUTDWN", 4.1, 0, 1, 1, 1, 1);
 		SetTimerEx("Carry", 1400, 0, "dd", playerid,0);
        SetPVarInt(playerid,"Cost",GetPVarInt(playerid,"Cost")+(35+random(15)+GetPVarInt(playerid,"ShahtaRange")));
        new string[70];
        format(string,sizeof(string),"Вы получили прибавку в виде {1faee9}%d$ за дополнительное расстояние!",GetPVarInt(playerid,"ShahtaRange"));
		SCM(playerid,0xFFFFFFFF,string);
		SCM(playerid,0xFFFFFFFF,"Вы можете {1faee9}продолжить добывать руду или закончите рабочий день.");
        new rand = random(sizeof(jP));
		SetPlayerCheckpoint(playerid, jP[rand][0],jP[rand][1],jP[rand][2], 1.2);
		SetPVarInt(playerid,"ShahtaSend",1),SetPVarInt(playerid,"ShahtaRange",rand*20);
		RemovePlayerAttachedObject(playerid,2);
		return true;
	}
	return true;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return true;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	new string[52], Float:angle;
	fcor
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		if(GetPVarInt(playerid,"TaxiCheck") == 1) {
		    DisablePlayerRaceCheckpoint(playerid), SCM(playerid,0x1faee9FF,"Вы прибыли на место вызова. {ffffff}Если клиента нет более 2х минут, смело пишите /taxicancel"), SetPVarInt(playerid,"TaxiCheck",0);
		    SCM(GetPVarInt(playerid,"TaxiCall"),0x1faee9FF,"Ваш автомобиль прибыл на место, {ffffff}поторопитесь или он уедет без вас!");
			return true;
		}
	 	if(GetPVarInt(playerid,"MainSend") == 2) {
		    DisablePlayerRaceCheckpoint(playerid), SCM(playerid,0x1faee9FF,"Посылка доставлена! {ffffff}+65$ к вашей зарплате, отправляйтесь к офису для продолжения или окончания работы!"), SetPVarInt(playerid,"Cost",GetPVarInt(playerid,"Cost")+65);
	        SetPlayerCheckpoint(playerid,1304.1097,-1874.5109,13.5525,1.0), SetPVarInt(playerid,"MailSend",1),RemovePlayerAttachedObject(playerid,0);
	        return true;
		}
		if(GetPVarInt(playerid,"LessonCheck") > 0) {
		    SetPVarInt(playerid,"LessonCheck", (GetPVarInt(playerid,"LessonCheck") == 25) ? (0) : (GetPVarInt(playerid,"LessonCheck")+1));
		    switch(GetPVarInt(playerid,"LessonCheck")) {
	  			case 1: SetPlayerRaceCheckpoint(playerid,0,-2047.537597,-84.319084,34.990756,-2074.329345,-67.896018,34.997447,3.0);
				case 2:	SetPlayerRaceCheckpoint(playerid,0,-2074.329345,-67.896018,34.997447,-2085.063720,17.284912,34.995388,3.0);
				case 3:	SetPlayerRaceCheckpoint(playerid,0,-2085.063720,17.284912,34.995388,-2153.288818,33.124378,34.994838,3.0);
				case 4:	SetPlayerRaceCheckpoint(playerid,0,-2153.288818,33.124378,34.994838,-2158.129638,98.027770,34.996036,3.0);
				case 5:	SetPlayerRaceCheckpoint(playerid,0,-2158.129638,98.027770,34.996036,-2144.610351,307.367950,34.995429,3.0);
				case 6:	SetPlayerRaceCheckpoint(playerid,0,-2144.610351,307.367950,34.995429,-2238.002197,321.875122,34.995716,3.0);
				case 7:	SetPlayerRaceCheckpoint(playerid,0,-2238.002197,321.875122,34.995716,-2365.025146,493.357971,30.213493,3.0);
				case 8:	SetPlayerRaceCheckpoint(playerid,0,-2365.025146,493.357971,30.213506,-2399.985351,569.044677,24.566589,3.0);
				case 9:	SetPlayerRaceCheckpoint(playerid,0,-2399.985351,569.044677,24.566589,-2592.640380,568.831237,14.284542,3.0);
				case 10: SetPlayerRaceCheckpoint(playerid,0,-2592.640380,568.831237,14.284542,-2609.229003,482.930786,14.286115,3.0);
				case 11: SetPlayerRaceCheckpoint(playerid,0,-2609.229003,482.930786,14.286115,-2608.751464,341.954467,4.002706,3.0);
				case 12: SetPlayerRaceCheckpoint(playerid,0,-2608.751464,341.954467,4.002706,-2645.227783,285.386505,4.006369,3.0);
				case 13: SetPlayerRaceCheckpoint(playerid,0,-2645.227783,285.386505,4.006369,-2631.548095,215.295532,4.145055,3.0);
				case 14: SetPlayerRaceCheckpoint(playerid,0,-2629.835205,215.373886,4.193134,-2564.104492,172.780670,4.372676,3.0);
				case 15: SetPlayerRaceCheckpoint(playerid,0,-2564.104492,172.780670,4.372677,-2472.129394,183.174209,9.304094,3.0);
				case 16: SetPlayerRaceCheckpoint(playerid,0,-2472.129394,183.174209,9.304050,-2265.763671,318.298492,35.323478,3.0);
	 			case 17: SetPlayerRaceCheckpoint(playerid,0,-2265.763671,318.298492,35.323482,-2161.127685,318.187011,34.995437,3.0);
				case 18: SetPlayerRaceCheckpoint(playerid,0,-2161.127685,318.187011,34.995437,-2140.408691,490.366027,34.840259,3.0);
				case 19: SetPlayerRaceCheckpoint(playerid,0,-2140.408691,490.366027,34.840259,-2020.399291,502.371551,34.839775,3.0);
				case 20: SetPlayerRaceCheckpoint(playerid,0,-2020.399291,502.371551,34.839775,-2006.278198,332.948883,34.832706,3.0);
				case 21: SetPlayerRaceCheckpoint(playerid,0,-2006.278198,332.948883,34.832706,-2008.518066,120.578140,27.362901,3.0);
				case 22: SetPlayerRaceCheckpoint(playerid,0,-2008.518066,120.578140,27.362901,-2008.938110,-59.669990,34.992099,3.0);
				case 23: SetPlayerRaceCheckpoint(playerid,0,-2008.938110,-59.669990,34.992099,-2055.235107,-94.230751,34.993179,3.0);
				case 24: SetPlayerRaceCheckpoint(playerid,1,-2055.235107,-94.230751,34.993179,-2055.235107,-94.230751,34.993179,3.0);
				case 25: {
				    new Float:health; GetVehicleHealth(GetPlayerVehicleID(playerid),health);
				    DisablePlayerRaceCheckpoint(playerid), SetPVarInt(playerid,"LessonCheck",0), SetPVarInt(playerid,"Lesson",0);
					if(health > 799.0) Player[playerid][Licenses] ^= (1<<0), ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{03c03c}Сдача на права","{ffffff}По результатам поездки\
	    			 мы можем смело заявить.\n{1faee9}Вы сдали экзамен по вождению и получаете ваше водительское удостоверение!\n\n{ffffff}Желаем Вам {E79A9A}удачи на дорогах и в любых ваших начинаниях!","Ок","");
					else ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{03c03c}Сдача на права","{ffffff}По результатам поездки\
				     мы можем Вас огорчить.\n{E79A9A}Вы не сдали экзамен по вождению и не сможете получить ваше водительское удостоверение!\n\n{ffffff}Желаем Вам {03c03c}удачи на следующей пересдаче!","Ок","");
					SetVehicleToRespawn(GetPlayerVehicleID(playerid));
				}
		    }
		    return true;
		}
		if(GetPVarInt(playerid,"TruckHaul") > 0 && IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid))) {
			DisablePlayerRaceCheckpoint(playerid), SCM(playerid,0x999589FF,"[F] Диспетчер: Отлично, груз доставлен, ты можешь продолжать работу!");
			switch(GetPVarInt(playerid,"TruckHaul")) {
				case 1: SetPVarInt(playerid,"Cost",GetPVarInt(playerid,"Cost")+2000+random(500));
				case 2: SetPVarInt(playerid,"Cost",GetPVarInt(playerid,"Cost")+2100+random(500));
				case 3: SetPVarInt(playerid,"Cost",GetPVarInt(playerid,"Cost")+2300+random(500));
				case 4: SetPVarInt(playerid,"Cost",GetPVarInt(playerid,"Cost")+1500+random(500));
			}
			SetPVarInt(playerid,"TruckHaul",0);
	  		SetPlayerRaceCheckpoint(playerid,1,-52.3652,-221.7758,5.4297,0.0,0.0,0.0,8.0), DestroyVehicle(Player[playerid][Trailer]);
	  		return true;
		}
		switch(GetPVarInt(playerid,"CheckHaul")) {
		    case 1: {
			    if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 433) return SCM(playerid,0xFFFFFFFF,"Необходимо {1faee9}находиться в грузовом транспорте!");
			    DisablePlayerRaceCheckpoint(playerid);
	   			SetVehicleParamsEx(GetPlayerVehicleID(playerid),VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,alarm,doors,bonnet,boot,objective), VNULL<GetPlayerVehicleID(playerid):engines>;
	   			GetPlayerPos(playerid, x, y, z);
		    	SetVehiclePos(GetPlayerVehicleID(playerid),x,y,z);
				GetVehicleZAngle(GetPlayerVehicleID(playerid), angle);
				x += (6.5 * floatsin(-angle+180, degrees));
				y += (6.5 * floatcos(-angle+180, degrees));
			    haulspl[GetPlayerVehicleID(playerid)-77] = CreateDynamicPickup(3014,23,x,y,z-0.2);
			    format(string,sizeof(string),"Загруженность грузовика\n{1faee9}%d/500",hauls[GetPlayerVehicleID(playerid)-77][1]);
			    haulstext[GetPlayerVehicleID(playerid)-77] = CreateDynamic3DTextLabel(string,0xFFFFFFFF,x,y,z+1.5,15.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
			    SetPVarInt(playerid,"Haul",2), SCM(playerid,0xFFFFFFFF,"Необходимо {1faee9}загрузить грузовик комплектующим, которое находится на корабле!"), SCM(playerid,0xFFFFFFFF,"После окончания загрузки {1faee9}повторно введите /haul и разгрузитесь на складе армии!");
	            return true;
			}
			case 2: {
			    if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 433) return SCM(playerid,0xFFFFFFFF,"Необходимо {1faee9}находиться в грузовом транспорте!");
			    DisablePlayerRaceCheckpoint(playerid);
	   			SetVehicleParamsEx(GetPlayerVehicleID(playerid),VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,alarm,doors,bonnet,boot,objective), VNULL<GetPlayerVehicleID(playerid):engines>;
	   			GetPlayerPos(playerid, x, y, z);
		    	SetVehiclePos(GetPlayerVehicleID(playerid),x,y,z);
				GetVehicleZAngle(GetPlayerVehicleID(playerid), angle);
				x += (6.5 * floatsin(-angle+180, degrees));
				y += (6.5 * floatcos(-angle+180, degrees));
			    haulspu[GetPlayerVehicleID(playerid)-77] = CreateDynamicPickup(3014,23,x,y,z-0.2);
			    format(string,sizeof(string),"Загруженность грузовика\n{1faee9}%d/500",hauls[GetPlayerVehicleID(playerid)-77][1]);
			    haulstext[GetPlayerVehicleID(playerid)-77] = CreateDynamic3DTextLabel(string,0xFFFFFFFF,x,y,z+1.5,15.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
			    SetPVarInt(playerid,"Haul",5), SCM(playerid,0xFFFFFFFF,"Необходимо {1faee9}разгрузить грузовик с комплектующими на склад армии!");
	            return true;
			}
			case 3: {
			    if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 455) return SCM(playerid,0xFFFFFFFF,"Необходимо {1faee9}находиться в грузовом транспорте!");
	            DisablePlayerRaceCheckpoint(playerid);
	   			SetVehicleParamsEx(GetPlayerVehicleID(playerid),VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,alarm,doors,bonnet,boot,objective), VNULL<GetPlayerVehicleID(playerid):engines>;
	   			GetPlayerPos(playerid, x, y, z);
		    	SetVehiclePos(GetPlayerVehicleID(playerid),x,y,z);
				GetVehicleZAngle(GetPlayerVehicleID(playerid), angle);
				x += (6.5 * floatsin(-angle+180, degrees));
				y += (6.5 * floatcos(-angle+180, degrees));
				haulsple = CreateDynamicPickup(2912,23,x,y,z-0.4);
			    format(string,sizeof(string),"Загруженность грузовика\n{1faee9}%d/500",hauls[GetPlayerVehicleID(playerid)-77][1]);
			    haulstext[GetPlayerVehicleID(playerid)-77] = CreateDynamic3DTextLabel(string,0xFFFFFFFF,x,y,z+1.5,15.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
			    SetPVarInt(playerid,"Haul",7), SCM(playerid,0xFFFFFFFF,"Необходимо {1faee9}загрузить грузовик ящиками с едой и броней, ящики находятся в здании!"), SCM(playerid,0xFFFFFFFF,"После окончания загрузки {1faee9}повторно введите /haul и разгрузитесь возле столовой армии!");
	            return true;
			}
			case 4: {
			    if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 455) return SCM(playerid,0xFFFFFFFF,"Необходимо {1faee9}находиться в грузовом транспорте!");
	            DisablePlayerRaceCheckpoint(playerid);
	   			SetVehicleParamsEx(GetPlayerVehicleID(playerid),VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,alarm,doors,bonnet,boot,objective), VNULL<GetPlayerVehicleID(playerid):engines>;
	   			GetPlayerPos(playerid, x, y, z);
		    	SetVehiclePos(GetPlayerVehicleID(playerid),x,y,z);
				GetVehicleZAngle(GetPlayerVehicleID(playerid), angle);
				x += (6.5 * floatsin(-angle+180, degrees));
				y += (6.5 * floatcos(-angle+180, degrees));
				haulspue = CreateDynamicPickup(2912,23,x,y,z-0.4);
			    format(string,sizeof(string),"Загруженность грузовика\n{1faee9}%d/500",hauls[GetPlayerVehicleID(playerid)-77][1]);
			    haulstext[GetPlayerVehicleID(playerid)-77] = CreateDynamic3DTextLabel(string,0xFFFFFFFF,x,y,z+1.5,15.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
			    SetPVarInt(playerid,"Haul",9), SCM(playerid,0xFFFFFFFF,"Необходимо {1faee9}разгрузить грузовик с ящиками еды и брони на склад столовой армии!");
	            return true;
			}
		}
		if(GetPVarInt(playerid,"BusCheck") != -1) {
		    SetPVarInt(playerid,"BusCheck", (GetPVarInt(playerid,"BusCheck") != 86) ? (SetPVarInt(playerid,"BusCheck",GetPVarInt(playerid,"BusCheck")+1)) : (0));
		    switch(GetPVarInt(playerid,"BusCheck")) {
				case 0: SetPlayerRaceCheckpoint(playerid,0,1214.7258,-1841.8081,13.5155,1182.3679,-1813.4288,13.5324,3.0);
				case 1: SetPlayerRaceCheckpoint(playerid,0,1182.3679,-1813.4288,13.5324,1182.6422,-1749.9556,13.5317,3.0);
				case 2: SetPlayerRaceCheckpoint(playerid,0,1182.6422,-1749.9556,13.5317,1164.6518,-1709.9053,13.8538,3.0);
				case 3: SetPlayerRaceCheckpoint(playerid,0,1164.6518,-1709.9053,13.8538,1049.4670,-1709.4333,13.5161,3.0);
				case 4: SetPlayerRaceCheckpoint(playerid,0,1049.4670,-1709.4333,13.5161,1033.1141,-1780.8559,13.6412,3.0);
				case 5: SetPlayerRaceCheckpoint(playerid,0,1033.1141,-1780.8559,13.6412,949.0809,-1775.5130,14.0698,3.0);
				case 6: SetPlayerRaceCheckpoint(playerid,0,949.0809,-1775.5130,14.0698,768.3442,-1763.9736,12.9849,3.0);
				case 7: SetPlayerRaceCheckpoint(playerid,0,768.3442,-1763.9736,12.9849,754.8100,-1655.4671,4.6401,3.0);
				case 8: SetPlayerRaceCheckpoint(playerid,0,754.8100,-1655.4671,4.6401,754.0065,-1604.0281,13.4068,3.0);
				case 9: SetPlayerRaceCheckpoint(playerid,0,754.0065,-1604.0281,13.4068,776.2551,-1558.2337,13.5159,3.0);
				case 10: SetPlayerRaceCheckpoint(playerid,0,776.2551,-1558.2337,13.5159,799.3307,-1419.7418,13.5245,3.0);
				case 11: SetPlayerRaceCheckpoint(playerid,0,799.3307,-1419.7418,13.5245,900.9696,-1402.9543,13.2621,3.0);
				case 12: SetPlayerRaceCheckpoint(playerid,0,900.9696,-1402.9543,13.2621,1184.5726,-1402.9659,13.3576,3.0);
				case 13: SetPlayerRaceCheckpoint(playerid,0,1184.5726,-1402.9659,13.3576,1206.8992,-1354.0684,13.5233,3.0);
				case 14: SetPlayerRaceCheckpoint(playerid,0,1206.8992,-1354.0684,13.5233,1208.3675,-1317.0134,13.5317,3.0);
				case 15: SetPlayerRaceCheckpoint(playerid,0,1208.3675,-1317.0134,13.5317,1240.9418,-1282.4201,13.6061,3.0);
				case 16: SetPlayerRaceCheckpoint(playerid,0,1240.9418,-1282.4201,13.6061,1326.8007,-1282.8223,13.5161,3.0);
				case 17: SetPlayerRaceCheckpoint(playerid,0,1326.8007,-1282.8223,13.5161,1345.3469,-1378.0933,13.6170,3.0);
				case 18: SetPlayerRaceCheckpoint(playerid,0,1345.3469,-1378.0933,13.6170,1385.6484,-1406.8902,13.5164,3.0);
				case 19: SetPlayerRaceCheckpoint(playerid,0,1385.6484,-1406.8902,13.5164,1439.9826,-1443.4204,13.5160,3.0);
				case 20: SetPlayerRaceCheckpoint(playerid,0,1439.9826,-1443.4204,13.5160,1435.7443,-1528.2899,13.5144,3.0);
				case 21: SetPlayerRaceCheckpoint(playerid,0,1435.7443,-1528.2899,13.5144,1427.7553,-1576.3548,13.4937,3.0);
				case 22: SetPlayerRaceCheckpoint(playerid,0,1427.7553,-1576.3548,13.4937,1427.0452,-1716.3175,13.5160,3.0);
				case 23: SetPlayerRaceCheckpoint(playerid,0,1427.0452,-1716.3175,13.5160,1481.6458,-1735.0195,13.5160,3.0);
				case 24: SetPlayerRaceCheckpoint(playerid,0,1481.6458,-1735.0195,13.5160,1636.2762,-1734.5501,13.5161,3.0);
				case 25: SetPlayerRaceCheckpoint(playerid,0,1636.2762,-1734.5501,13.5161,1807.9431,-1734.5191,13.5199,3.0);
				case 26: SetPlayerRaceCheckpoint(playerid,0,1807.9431,-1734.5191,13.5199,1824.1352,-1683.0496,13.5161,3.0);
				case 27: SetPlayerRaceCheckpoint(playerid,0,1824.1352,-1683.0496,13.5161,1835.2775,-1565.9300,13.4986,3.0);
				case 28: SetPlayerRaceCheckpoint(playerid,0,1835.2775,-1565.9300,13.4986,1960.5611,-1518.6009,3.4982,3.0);
				case 29: SetPlayerRaceCheckpoint(playerid,0,1960.5611,-1518.6009,3.4982,2139.8225,-1544.9763,2.5728,3.0);
				case 30: SetPlayerRaceCheckpoint(playerid,0,2139.8225,-1544.9763,2.5728,2281.1584,-1600.1352,3.6665,3.0);
				case 31: SetPlayerRaceCheckpoint(playerid,0,2281.1584,-1600.1352,3.6665,2436.3935,-1616.9456,13.9055,3.0);
				case 32: SetPlayerRaceCheckpoint(playerid,0,2436.3935,-1616.9456,13.9055,2669.8464,-1625.8549,16.9883,3.0);
				case 33: SetPlayerRaceCheckpoint(playerid,0,2669.8464,-1625.8549,16.9883,2752.6296,-1659.5749,12.9193,3.0);
				case 34: SetPlayerRaceCheckpoint(playerid,0,2752.6296,-1659.5749,12.9193,2840.2177,-1659.7451,10.8279,3.0);
				case 35: SetPlayerRaceCheckpoint(playerid,0,2840.2177,-1659.7451,10.8279,2886.6616,-1631.4433,11.0110,3.0);
				case 36: SetPlayerRaceCheckpoint(playerid,0,2886.6616,-1631.4433,11.0110,2926.8916,-1464.0296,11.0106,3.0);
				case 37: SetPlayerRaceCheckpoint(playerid,0,2926.8916,-1464.0296,11.0106,2911.0407,-1299.5611,11.0084,3.0);
				case 38: SetPlayerRaceCheckpoint(playerid,0,2911.0407,-1299.5611,11.0084,2890.5190,-1133.5190,11.0083,3.0);
				case 39: SetPlayerRaceCheckpoint(playerid,0,2890.5190,-1133.5190,11.0083,2896.9440,-712.1996,10.9687,3.0);
				case 40: SetPlayerRaceCheckpoint(playerid,0,2896.9440,-712.1996,10.9687,2806.0422,-431.9602,21.5206,3.0);
				case 41: SetPlayerRaceCheckpoint(playerid,0,2806.0422,-431.9602,21.5206,2737.6213,-217.0596,29.4774,3.0);
				case 42: SetPlayerRaceCheckpoint(playerid,0,2737.6213,-217.0596,29.4774,2781.2907,-30.5998,36.1099,3.0);
				case 43: SetPlayerRaceCheckpoint(playerid,0,2781.2907,-30.5998,36.1099,2819.8137,41.4951,20.1235,3.0);
				case 44: SetPlayerRaceCheckpoint(playerid,0,2819.8137,41.4951,20.1235,2720.1035,45.9398,23.3027,3.0);
				case 45: SetPlayerRaceCheckpoint(playerid,0,2720.1035,45.9398,23.3027,2653.7683,23.0374,27.6395,3.0);
				case 46: SetPlayerRaceCheckpoint(playerid,0,2653.7683,23.0374,27.6395,2712.6564,-50.6880,39.7885,3.0);
				case 47: SetPlayerRaceCheckpoint(playerid,0,2712.6564,-50.6880,39.7885,2678.0434,-225.2931,33.9906,3.0);
				case 48: SetPlayerRaceCheckpoint(playerid,0,2678.0434,-225.2931,33.9906,2615.9045,-368.0877,62.3911,3.0);
				case 49: SetPlayerRaceCheckpoint(playerid,0,2615.9045,-368.0877,62.3911,2538.8010,-400.4655,78.4447,3.0);
				case 50: SetPlayerRaceCheckpoint(playerid,0,2538.8010,-400.4655,78.4447,2522.6704,-465.4535,85.0098,3.0);
				case 51: SetPlayerRaceCheckpoint(playerid,0,2522.6704,-465.4535,85.0098,2487.1584,-538.1143,97.1043,3.0);
				case 52: SetPlayerRaceCheckpoint(playerid,0,2487.1584,-538.1143,97.1043,2396.8918,-635.6077,126.3668,3.0);
				case 53: SetPlayerRaceCheckpoint(playerid,0,2396.8918,-635.6077,126.3668,2471.1901,-742.6296,104.7819,3.0);
				case 54: SetPlayerRaceCheckpoint(playerid,0,2471.1901,-742.6296,104.7819,2679.8073,-741.1599,81.4337,3.0);
				case 55: SetPlayerRaceCheckpoint(playerid,0,2679.8073,-741.1599,81.4337,2754.4167,-617.6352,57.8182,3.0);
				case 56: SetPlayerRaceCheckpoint(playerid,0,2754.4167,-617.6352,57.8182,2689.2158,-421.1489,53.5189,3.0);
				case 57: SetPlayerRaceCheckpoint(playerid,0,2689.2158,-421.1489,53.5189,2661.0317,-322.5425,46.0815,3.0);
				case 58: SetPlayerRaceCheckpoint(playerid,0,2661.0317,-322.5425,46.0815,2681.3815,-203.4312,34.0109,3.0);
				case 59: SetPlayerRaceCheckpoint(playerid,0,2681.3815,-203.4312,34.0109,2710.6391,-171.9218,33.5696,3.0);
				case 60: SetPlayerRaceCheckpoint(playerid,0,2710.6391,-171.9218,33.5696,2708.4277,-242.7771,29.8774,3.0);
				case 61: SetPlayerRaceCheckpoint(playerid,0,2708.4277,-242.7771,29.8774,2755.9833,-405.7232,23.8799,3.0);
				case 62: SetPlayerRaceCheckpoint(playerid,0,2755.9833,-405.7232,23.8799,2875.3703,-792.5171,10.9992,3.0);
				case 63: SetPlayerRaceCheckpoint(playerid,0,2875.3703,-792.5171,10.9992,2875.0541,-1199.4987,11.0084,3.0);
				case 64: SetPlayerRaceCheckpoint(playerid,0,2875.0541,-1199.4987,11.0084,2903.0246,-1465.8748,11.0150,3.0);
				case 65: SetPlayerRaceCheckpoint(playerid,0,2903.0246,-1465.8748,11.0150,2858.6391,-1646.3564,11.0083,3.0);
				case 66: SetPlayerRaceCheckpoint(playerid,0,2858.6391,-1646.3564,11.0083,2658.8574,-1655.0290,10.8482,3.0);
				case 67: SetPlayerRaceCheckpoint(playerid,0,2658.8574,-1655.0290,10.8482,2640.8022,-1718.1658,10.8587,3.0);
				case 68: SetPlayerRaceCheckpoint(playerid,0,2640.8022,-1718.1658,10.8587,2450.4953,-1730.3443,13.6395,3.0);
				case 69: SetPlayerRaceCheckpoint(playerid,0,2450.4953,-1730.3443,13.6395,2231.0231,-1729.7091,13.5162,3.0);
				case 70: SetPlayerRaceCheckpoint(playerid,0,2231.0231,-1729.7091,13.5162,2182.7770,-1743.3729,13.5081,3.0);
				case 71: SetPlayerRaceCheckpoint(playerid,0,2182.7770,-1743.3729,13.5081,2108.9414,-1749.7916,13.5313,3.0);
				case 72: SetPlayerRaceCheckpoint(playerid,0,2108.9414,-1749.7916,13.5313,1958.7161,-1750.0834,13.5161,3.0);
				case 73: SetPlayerRaceCheckpoint(playerid,0,1958.7161,-1750.0834,13.5161,1838.8939,-1750.3997,13.5161,3.0);
				case 74: SetPlayerRaceCheckpoint(playerid,0,1838.8939,-1750.3997,13.5161,1766.8486,-1729.5883,13.5158,3.0);
				case 75: SetPlayerRaceCheckpoint(playerid,0,1766.8486,-1729.5883,13.5158,1586.0737,-1730.3204,13.5151,3.0);
				case 76: SetPlayerRaceCheckpoint(playerid,0,1586.0737,-1730.3204,13.5151,1481.7885,-1730.0996,13.5161,3.0);
				case 77: SetPlayerRaceCheckpoint(playerid,0,1481.7885,-1730.0996,13.5161,1431.8046,-1695.9593,13.5143,3.0);
				case 78: SetPlayerRaceCheckpoint(playerid,0,1431.8046,-1695.9593,13.5143,1431.7526,-1606.0292,13.5161,3.0);
				case 79: SetPlayerRaceCheckpoint(playerid,0,1431.7526,-1606.0292,13.5161,1456.1973,-1455.6472,13.4981,3.0);
				case 80: SetPlayerRaceCheckpoint(playerid,0,1456.1973,-1455.6472,13.4981,1425.4989,-1436.7102,13.5137,3.0);
				case 81: SetPlayerRaceCheckpoint(playerid,0,1425.4989,-1436.7102,13.5137,1376.4571,-1398.0107,13.5212,3.0);
				case 82: SetPlayerRaceCheckpoint(playerid,0,1376.4571,-1398.0107,13.5212,1335.8869,-1454.7347,13.5161,3.0);
				case 83: SetPlayerRaceCheckpoint(playerid,0,1335.8869,-1454.7347,13.5161,1294.8453,-1655.1020,13.5161,3.0);
				case 84: SetPlayerRaceCheckpoint(playerid,0,1294.8453,-1655.1020,13.5161,1294.8767,-1832.4523,13.5161,3.0);
				case 85: SetPlayerRaceCheckpoint(playerid,0,1294.8767,-1832.4523,13.5161,1220.8079,-1849.9962,13.5161,3.0);
				case 86: SetPlayerRaceCheckpoint(playerid,1,1182.3679,-1813.4288,13.5324,1214.7258,-1841.8081,13.5155,3.0);
			}
			return true;
		}
		if(GetPVarInt(playerid,"Race") > -1) {
		    switch(Track) {
		        case 1: {
		        	SetPVarInt(playerid,"Race", (GetPVarInt(playerid,"Race") == 21) ? (0) : (GetPVarInt(playerid,"Race")+1));
		            switch(GetPVarInt(playerid,"Race")) {
						case 0: DisablePlayerRaceCheckpoint(playerid), SetPVarInt(playerid,"Race",-1), Track = 0;
		            	case 1: SetPlayerRaceCheckpoint(playerid,0,-2724.4636,1086.3967,45.8983,-2750.9516,885.9582,65.8163,10.0);
						case 2: SetPlayerRaceCheckpoint(playerid,0,-2750.9516,885.9582,65.8163,-2750.8012,704.5006,40.7523,10.0);
						case 3: SetPlayerRaceCheckpoint(playerid,0,-2750.8012,704.5006,40.7523,-2736.5480,563.8285,14.0235,10.0);
						case 4: SetPlayerRaceCheckpoint(playerid,0,-2736.5480,563.8285,14.0235,-2544.9780,563.5501,14.0845,10.0);
						case 5: SetPlayerRaceCheckpoint(playerid,0,-2544.9780,563.5501,14.0845,-2259.7207,562.1591,34.6390,10.0);
						case 6: SetPlayerRaceCheckpoint(playerid,0,-2259.7207,562.1591,34.6390,-2023.2513,561.8760,34.6405,10.0);
						case 7: SetPlayerRaceCheckpoint(playerid,0,-2023.2513,561.8760,34.6405,-1937.6466,586.7987,34.7208,10.0);
						case 8: SetPlayerRaceCheckpoint(playerid,0,-1937.6466,586.7987,34.7208,-1897.1213,694.0928,44.7823,10.0);
						case 9: SetPlayerRaceCheckpoint(playerid,0,-1897.1213,694.0928,44.7823,-1895.4716,853.4816,34.6387,10.0);
						case 10: SetPlayerRaceCheckpoint(playerid,0,-1895.4716,853.4816,34.6387,-1880.5394,1069.9306,44.9204,10.0);
						case 11: SetPlayerRaceCheckpoint(playerid,0,-1880.5394,1069.9306,44.9204,-1881.3226,1193.7681,44.5592,10.0);
						case 12: SetPlayerRaceCheckpoint(playerid,0,-1881.3226,1193.7681,44.5592,-1787.6300,1269.1905,11.6709,10.0);
						case 13: SetPlayerRaceCheckpoint(playerid,0,-1787.6300,1269.1905,11.6709,-1717.2010,1330.1036,6.6639,10.0);
						case 14: SetPlayerRaceCheckpoint(playerid,0,-1717.2010,1330.1036,6.6639,-1926.8044,1313.8394,6.6630,10.0);
						case 15: SetPlayerRaceCheckpoint(playerid,0,-1926.8044,1313.8394,6.6630,-2067.4724,1280.7622,8.4213,10.0);
						case 16: SetPlayerRaceCheckpoint(playerid,0,-2067.4724,1280.7622,8.4213,-2271.6230,1235.9057,45.7176,10.0);
						case 17: SetPlayerRaceCheckpoint(playerid,0,-2271.6230,1235.9057,45.7176,-2273.1389,1179.5787,55.2031,10.0);
						case 18: SetPlayerRaceCheckpoint(playerid,0,-2273.1389,1179.5787,55.2031,-2416.0874,1185.6458,34.6398,10.0);
						case 19: SetPlayerRaceCheckpoint(playerid,0,-2416.0874,1185.6458,34.6398,-2492.4526,1236.3570,34.6392,10.0);
						case 20: SetPlayerRaceCheckpoint(playerid,0,-2492.4526,1236.3570,34.6392,-2653.4755,1160.6375,34.6481,10.0);
						case 21: SetPlayerRaceCheckpoint(playerid,1,-2654.9399,1156.1821,34.6481,-2724.4636,1086.3967,45.8983,10.0);
					}
		        }
			}
			return true;
		}
	}
	return true;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return true;
}

public OnRconCommand(cmd[])
{
	return true;
}

public OnPlayerRequestSpawn(playerid)
{
	return true;
}

public OnObjectMoved(objectid)
{
	return true;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return true;
}

public OnPlayerPickUpDynamicPickup(playerid, pickupid) {
    new string[280];
    for(new p; p < 7; p++) {
 		if(pickupid == haulspu[p]) {
  			if(GetPVarInt(playerid,"GetPickup") > gettime()) return true;
   			if(GetPVarInt(playerid,"Ammo") == 1) return SCM(playerid,0xFFFFFFFF,"У вас {1faee9}уже есть с собой ящик с комплектующими!");
			hauls[p][1] -= 50, RemovePlayerAttachedObject(playerid,0);
			SetPlayerAttachedObject(playerid, 0, 3014, 5, 0.000000, 0.175000, 0.205000, -78.700042, -4.699985, 13.699992, 1.000000, 1.000000, 1.000000), SetPVarInt(playerid,"Ammo",1);
 			ApplyAnimation(playerid, "CARRY", "LIFTUP", 4.1, 0, 1, 1, 1, 1);
			SetTimerEx("Carry", 1400, 0, "dd", playerid,1);
			SetPVarInt(playerid,"Haul", (hauls[p][1] == 0) ? 0 : 5);
			format(string,42,"Загруженность грузовика\n{1faee9}%d/500",hauls[p][1]);
			UpdateDynamic3DTextLabelText(haulstext[p], 0xFFFFFFFF, string);
			SetPVarInt(playerid,"Ammo",1);
			if(hauls[p][1] <= 0) {
				DestroyDynamicPickup(haulspu[p]), SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE), SCM(playerid,0xFFFFFFFF,"Грузовик {1faee9}разгружен!"), DestroyDynamic3DTextLabel(haulstext[p]);
				haulspu[GetPlayerVehicleID(playerid)-77] = -1;
			}
			SetPVarInt(playerid,"GetPickup",gettime()+3);
			return true;
		}
	 	if(pickupid == haulspl[p]) {
	 	    if(GetPVarInt(playerid,"GetPickup") > gettime()) return true;
	 	    if(Player[playerid][pFraction][1] != 6) return true;
   			if(GetPVarInt(playerid,"Ammo") == 0) return SCM(playerid,0xFFFFFFFF,"У вас {1faee9}нет с собой ящиков с комплектующими!");
			hauls[p][1] += 50, RemovePlayerAttachedObject(playerid,0);
			SetTimerEx("Carry", 1400, 0, "dd", playerid,0);
			ApplyAnimation(playerid, "CARRY", "PUTDWN", 4.1, 0, 1, 1, 1, 1);
			SetPVarInt(playerid,"Haul", (hauls[p][1] == 500) ? 0 : 2);
			format(string,42,"Загруженность грузовика\n{1faee9}%d/500",hauls[p][1]);
			UpdateDynamic3DTextLabelText(haulstext[p], 0xFFFFFFFF, string);
			SetPVarInt(playerid,"Ammo",0);
			if(hauls[p][1] >= 500) {
				DestroyDynamicPickup(haulspl[p]), RemovePlayerAttachedObject(playerid,0), SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE), SCM(playerid,0xFFFFFFFF,"Грузовик {1faee9}полон!"), DestroyDynamic3DTextLabel(haulstext[p]);
                haulspl[GetPlayerVehicleID(playerid)-77] = -1;
			}
			SetPVarInt(playerid,"GetPickup",gettime()+3);
			return true;
		}
	}
    for(new h = 0; h <= Houses; h++) {
		if(pickupid == House[h][hPickup]){
		    if(!IsPlayerInRangeOfPoint(playerid, 2.0,House[h][hX], House[h][hY], House[h][hZ])) continue;
        	if(GetPVarInt(playerid,"GetPickup") > gettime()) return true;
		    new priority[12];
		    switch(House[h][hPriority]) {
		        case 0: priority = "Фургон";
		        case 1: priority = "Эконом";
		        case 2: priority = "Обычный";
				case 3: priority = "Средний";
				case 4: priority = "Элитный";
			}
		    format(string,sizeof(string),	"{ffffff}Номер дома:\t\t\t %d\n\
		    								Гос.Цена дома:\t\t %d$\n\
											Местоположение:\t\t %s\n\
											Приоритет дома:\t\t %s\n\
											Кол-во проживающих:\t\t %d\n\
											Владелец:\t\t\t{1faee9} %s",
		    House[h][hID],House[h][hPrice],House[h][hStreet],priority,House[h][hHousemans],House[h][hOwner]);
	 		ShowPlayerDialog(playerid,8,DIALOG_STYLE_MSGBOX,"{ffffff}Дом",string, (strcmp(House[h][hOwner],"None",true)!=0) ? ("Войти") : ("Купить") ,"Отмена");
	 		SetPVarInt(playerid,"GetPickup",gettime()+7);
	 		return true;
		}
	}
	for(new b = 0; b <= Businesses; b++) {
		if(pickupid == Business[b][bPickup][0]){
		    if(!IsPlayerInRangeOfPoint(playerid, 2.0,Business[b][bX],Business[b][bY],Business[b][bZ])) continue;
        	if(GetPVarInt(playerid,"GetPickup") > gettime()) return true;
		    format(string,sizeof(string),	"{ffffff}Номер бизнеса:\t\t %d\n\
											Название:\t\t\t %s\n\
											Цена:\t\t\t\t %d$\n\
											Владелец:\t\t\t{1faee9} %s",
		    Business[b][bID],Business[b][bName],Business[b][bPrice],Business[b][bOwner]);
	 		ShowPlayerDialog(playerid,20,DIALOG_STYLE_MSGBOX,"{ffffff}Бизнес",string, (strcmp(Business[b][bOwner],"None",true)!=0) ? ("Войти") : ("Купить") ,"Отмена");
	 		SetPVarInt(playerid,"GetPickup",gettime()+3);
	 		return true;
		}
		if(pickupid == Business[b][bPickup][1]){
        	if(GetPVarInt(playerid,"GetPickup") > gettime()) return true;
		    SetPlayerInterior(playerid,0), AC_SetPlayerPos(playerid,Business[b][bX],Business[b][bY],Business[b][bZ]), SetPlayerVirtualWorld(playerid,0);
	 		SetPVarInt(playerid,"GetPickup",gettime()+3);
	 		return true;
		}
		if(pickupid == Business[b][bPickup][2]) {
			if(GetPVarInt(playerid,"GetPickup") > gettime() || GetPVarInt(playerid,"DialogActive") == 1) continue;
			SetPVarInt(playerid,"BID",b);
			switch(Business[b][bType]) {
			    case 0: {
					ShowPlayerDialog(playerid,24,DIALOG_STYLE_MSGBOX,"{03c03c}Трудоустройство","{ffffff}Государственная компания {1faee9}TAXI {ffffff}приглашает на работу водителей!\n\n {1faee9}- Для работы вам нужно иметь водительское удостоверение\n\
					  - Иметь GPS-гарнитуру\n - Иметь при себе минимум 100$ для аренды автомобиля.\n\n {ffffff}Если вы согласны вы можете начать работу, если уже работаете - закончить","Работа","Отмена");
			  		SetPVarInt(playerid,"DialogActive",1);
					SetPVarInt(playerid,"GetPickup",gettime()+3);
			    }
			    case 1: {
			        if(Business[b][bProduct] < 1) return SCM(playerid,0xAC7575FF,"На складе нет одежды!");
					SetPlayerVirtualWorld(playerid,playerid+2);
					switch(GetPlayerInterior(playerid)) {
					    case 1: AC_SetPlayerPos(playerid, 213.9570,-41.4431,1002.0234), SetPlayerFacingAngle(playerid,90.4205), SetPlayerCameraPos(playerid,211.7931,-41.2535,1002.0234+0.8), SetPlayerCameraLookAt(playerid,213.9570,-41.4431,1002.0234+0.2); // sub urban
                        case 3: AC_SetPlayerPos(playerid, 199.2533,-127.3640,1003.5152), SetPlayerFacingAngle(playerid,180.0540), SetPlayerCameraPos(playerid,199.2101,-130.8726,1003.5152+0.8), SetPlayerCameraLookAt(playerid,199.2533,-127.3640,1003.5152+0.2); // pro laps
						case 5: AC_SetPlayerPos(playerid, 207.2767,-10.3371,1001.2109), SetPlayerFacingAngle(playerid,241.9071), SetPlayerCameraPos(playerid,208.9237,-11.2379,1001.2109+0.8), SetPlayerCameraLookAt(playerid,207.2767,-10.3371,1001.2109+0.2); // victim
						case 14: AC_SetPlayerPos(playerid, 214.9792,-155.5137,1000.5234), SetPlayerFacingAngle(playerid,91.0061), SetPlayerCameraPos(playerid,213.1157,-155.9939,1000.5234+0.8), SetPlayerCameraLookAt(playerid,214.9792,-155.5137,1000.5234+0.2); // didie sash
					    case 15: AC_SetPlayerPos(playerid, 217.2881,-98.4801,1005.2578), SetPlayerFacingAngle(playerid,89.6888), SetPlayerCameraPos(playerid,215.4598,-99.8414,1005.2578+0.8), SetPlayerCameraLookAt(playerid,217.2881,-98.4801,1005.2578+0.2);// binco
					    case 18: AC_SetPlayerPos(playerid, 180.5414,-88.2082,1002.0234), SetPlayerFacingAngle(playerid,90.8593), SetPlayerCameraPos(playerid,178.4300,-88.2186,1002.0234+0.8), SetPlayerCameraLookAt(playerid,180.5414,-88.2082,1002.0234+0.2); // zip
 					}
				 	TogglePlayerControllable(playerid,0);
				    TextDrawShowForPlayer(playerid, brLeft), TextDrawShowForPlayer(playerid, brRight), TextDrawShowForPlayer(playerid, brSelect), TextDrawShowForPlayer(playerid, ButtonCancel),TextDrawShowForPlayer(playerid, tCost);
				    TextDrawSetString(Player[playerid][tCostItem],"5000$"), TextDrawShowForPlayer(playerid, Player[playerid][tCostItem]), SelectTextDraw(playerid,0x1faee9FF), Player[playerid][TDSelect]  = true, SetPVarInt(playerid,"BuySkin",5000);
					if(Player[playerid][pSex] == 1) SetPlayerSkin(playerid, 22), Player[playerid][SSCase] = 1, Player[playerid][ChosenSkin] = 22;
					else SetPlayerSkin(playerid, 9), Player[playerid][SSCase] = 1, Player[playerid][ChosenSkin] = 9;
					SetPVarInt(playerid,"GetPickup",gettime()+3);
			    }
                case 2: {
                    format(string,162,"{ffffff}Мобильный телефон [%d$]\nТелефонный номер [%d$]\nНаручные часы [%d$]\nGPS-навигатор [%d$]\nБита [%d$]\nФотоаппарат [%d$]\nРемонтный набор [%d$]",Business[b][bCost],pernumber(Business[b][bCost],12),pernumber(Business[b][bCost],20),pernumber(Business[b][bCost],35),pernumber(Business[b][bCost],56),pernumber(Business[b][bCost],72),pernumber(Business[b][bCost],100));
                    ShowPlayerDialog(playerid,52,DIALOG_STYLE_LIST,"{FFC800}Ассортимент магазина",string,"Купить","Отмена");
                    SetPVarInt(playerid,"DialogActive",1);
                }
                case 3: {
                    ShowPlayerDialog(playerid,53,DIALOG_STYLE_LIST,"{FFC800}Ассортимент магазина","{ffffff}Очки\nШляпки\nБереты\nБанданы\nМаски","Выбор","Отмена");
                    SetPVarInt(playerid,"DialogActive",1);
                }
				case 5: {
				    format(string,160,"{ffffff}Хот-дог [%d$]\nПицца [%d$]\nБургер [%d$]\nКартофель-Фри [%d$]\nКола [%d$]\nБиг-Бургер [%d$]\nПиво [%d$]",Business[b][bCost],pernumber(Business[b][bCost],12),pernumber(Business[b][bCost],20),pernumber(Business[b][bCost],35),pernumber(Business[b][bCost],56),pernumber(Business[b][bCost],72),pernumber(Business[b][bCost],100));
				    ShowPlayerDialog(playerid,53,DIALOG_STYLE_LIST,"{FFC800}Ассортимент магазина",string,"Выбор","Отмена");
				    SetPVarInt(playerid,"DialogActive",1);
				}
				case 6: {

				}
				case 7: {

				}
				case 8: {
				    ShowPlayerDialog(playerid,34,DIALOG_STYLE_MSGBOX,"{03c03c}Покупка оружия","{ffffff}Вы находитесь в магазине оружия, здесь вы можете купить любой вид оружия ( легальный ).\nЕсли хотите продолжить покупку - нажмите {1faee9}'Ок'\n\n\
	    			{FFCC00}Цена за обойму и название оружия написаны слева сверху.\n{03c03c}Для покупки оружия используйте кнопку 'BUY', {CA7575}BACK для выхода.\n{92C4DC}Листать список оружия можно с помощью стрелок снизу!","Ок","Отмена");
                    SetPVarInt(playerid,"DialogActive",1);
				}
				case 9: {

				}
			    /*
			    case 5: type = 10; // fast food
			    case 6: type = 50; // dinner
			    case 7: type = 48; // club
			    case 8: type = 6; // gun shop a.k.a ammo
			    case 9: type = 63; // pay'n'spray
			    default: type = 37; // undefined type business*/
   			}
   			return true;
		}
	}
 	if(pickupid == haulammo) {
	    if(GetPVarInt(playerid,"GetPickup") > gettime()) return true;
	    if(Player[playerid][pFraction][1] == 6 || PlayerGangster(playerid)) {
		    if(GetPVarInt(playerid,"Ammo") == 1) return SCM(playerid,0xFFFFFFFF,"У вас {1faee9}уже есть с собой ящик с комплектующими!");
		    if(LSW < 50) return SCM(playerid,0xFFFFFFFF,"На корабле {1faee9}недостаточно комплектующих!");
		    LSW -= 50;
		    format(string,58,"Комплектующие для сбора оружия\n{1faee9}На корабле: %d",LSW);
			UpdateDynamic3DTextLabelText(LSWtext, 0xFFFFFFFF, string);
		    SetPlayerAttachedObject(playerid, 0, 3014, 5, 0.000000, 0.175000, 0.205000, -78.700042, -4.699985, 13.699992, 1.000000, 1.000000, 1.000000), SetPVarInt(playerid,"Ammo",1);
	        ApplyAnimation(playerid, "CARRY", "LIFTUP", 4.1, 0, 1, 1, 1, 1);
	 		SetTimerEx("Carry", 1400, 0, "dd", playerid,1);
		    SetPVarInt(playerid,"Haul",7);
		}
		else return SCM(playerid,0x1faee9FF,"[Мысли]: {ffffff}Наверное не стоит это трогать...");
		SetPVarInt(playerid,"GetPickup",gettime()+5);
		return true;
	}
	if(pickupid == ammolv) {
	    if(GetPVarInt(playerid,"GetPickup") > gettime()) return true;
	    if(GetPVarInt(playerid,"Ammo") == 0) return SCM(playerid,0xFFFFFFFF,"У вас {1faee9}нет с собой ящика с комплектующими!");
	    if(LVW >= 50000) { SCM(playerid,0xFFFFFFFF,"Склад {1faee9}заполнен!"), RemovePlayerAttachedObject(playerid,0), SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE); return true; }
	    LVW += 50;
	    format(string,48,"Собранное оружие\n{1faee9}На складе: %d ед.",LVW);
		UpdateDynamic3DTextLabelText(LVWtext, 0xFFFFFFFF, string);
	    RemovePlayerAttachedObject(playerid,0);
        ApplyAnimation(playerid, "CARRY", "PUTDWN", 4.1, 0, 1, 1, 1, 1);
 		SetTimerEx("Carry", 1400, 0, "dd", playerid,0);
	    SetPVarInt(playerid,"Ammo",0);
	    SetPVarInt(playerid,"Haul",9);
	    SetPVarInt(playerid,"GetPickup",gettime()+5);
	    return true;
	}
 	if(pickupid == hauleat) {
	    if(GetPVarInt(playerid,"GetPickup") > gettime()) return true;
	    if(Player[playerid][pFraction][1] != 6) return true;
	    if(GetPVarInt(playerid,"EatBox") == 1) return SCM(playerid,0xFFFFFFFF,"У вас {1faee9}уже есть с собой ящик с едой!");
	    SetPlayerAttachedObject(playerid, 0, 2912, 5, 0.040000, -0.035000, 0.174000, -77.599945, -6.599995, 14.200003, 0.641000, 0.745000, 0.558999);
        ApplyAnimation(playerid, "CARRY", "LIFTUP", 4.1, 0, 1, 1, 1, 1);
 		SetTimerEx("Carry", 1400, 0, "dd", playerid,1);
   		SetPVarInt(playerid,"EatBox",1);
   		SetPVarInt(playerid,"GetPickup",gettime()+5);
   		return true;
	}
	if(pickupid == eatlv) {
	    if(GetPVarInt(playerid,"GetPickup") > gettime()) return true;
		if(GetPVarInt(playerid,"EatBox") == 1) {
	 		UpdateDynamic3DTextLabelText(LVWtext, 0xFFFFFFFF, string);
		    RemovePlayerAttachedObject(playerid,0);
	        ApplyAnimation(playerid, "CARRY", "PUTDWN", 4.1, 0, 1, 1, 1, 1);
	 		SetTimerEx("Carry", 1400, 0, "dd", playerid,0);
		    SetPVarInt(playerid,"EatBox",0);
		    SetPVarInt(playerid,"Haul",0);
	 		LVWE++;
	 		format(string,48,"Еда и Броня\n{1faee9}На складе: %d пайков",LVWE);
			UpdateDynamic3DTextLabelText(LVWEtext, 0xFFFFFFFF, string);
            SetPVarInt(playerid,"GetPickup",gettime()+10);
			return true;
		}
		if(Player[playerid][pFraction][1] == 6 && LVWE > 0) {
		    if(GetPVarInt(playerid,"GetAmmoH") > gettime()) return SCM(playerid,0xFFFFFFFF,"Брать сух.поек можно {03c03c}раз в 3 минуты!");
			SetPlayerArmorAC(playerid,100.0), SetPlayerHealth(playerid,100.0), LVWE--, SCM(playerid,0xFFFFFFFF,"Сух.поек {1faee9}выдан!");
			format(string,48,"Еда и Броня\n{1faee9}На складе: %d пайков",LVWE);
			UpdateDynamic3DTextLabelText(LVWEtext, 0xFFFFFFFF, string);
			SetPVarInt(playerid,"GetAmmoH",gettime()+180);
			return true;
		}
	}
	if(pickupid == haulspue) {
		if(GetPVarInt(playerid,"GetPickup") > gettime()) return true;
		if(Player[playerid][pFraction][1] != 6) return true;
		if(GetPVarInt(playerid,"EatBox") == 1) return SCM(playerid,0xFFFFFFFF,"У вас {1faee9}уже есть с собой ящик с едой!");
		hauls[0][1] -= 50, RemovePlayerAttachedObject(playerid,0);
		SetPlayerAttachedObject(playerid, 0, 2912, 5, 0.040000, -0.035000, 0.174000, -77.599945, -6.599995, 14.200003, 0.641000, 0.745000, 0.558999);
		ApplyAnimation(playerid, "CARRY", "LIFTUP", 4.1, 0, 1, 1, 1, 1);
		SetTimerEx("Carry", 1400, 0, "dd", playerid,1);
		format(string,42,"Загруженность грузовика\n{1faee9}%d/500",hauls[0][1]);
		UpdateDynamic3DTextLabelText(haulstext[0], 0xFFFFFFFF, string);
		SetPVarInt(playerid,"EatBox",1);
		SetPVarInt(playerid,"Haul",9);
		if(hauls[0][1] <= 0) {
			DestroyDynamicPickup(haulspue), SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE), SCM(playerid,0xFFFFFFFF,"Грузовик {1faee9}разгружен!"), DestroyDynamic3DTextLabel(haulstext[0]);
			haulspue = -1;
		}
		SetPVarInt(playerid,"GetPickup",gettime()+3),SetPVarInt(playerid,"GetAmmoH",gettime()+23);
		return true;
	}
	if(pickupid == haulsple) {
		if(GetPVarInt(playerid,"GetPickup") > gettime()) return true;
	    if(Player[playerid][pFraction][1] != 6) return true;
		if(GetPVarInt(playerid,"EatBox") == 0) return SCM(playerid,0xFFFFFFFF,"У вас {1faee9}нет с собой ящиков с едой!");
		hauls[0][1] += 50, RemovePlayerAttachedObject(playerid,0);
		SetTimerEx("Carry", 1400, 0, "dd", playerid,0);
		ApplyAnimation(playerid, "CARRY", "PUTDWN", 4.1, 0, 1, 1, 1, 1);
		format(string,42,"Загруженность грузовика\n{1faee9}%d/500",hauls[0][1]);
		UpdateDynamic3DTextLabelText(haulstext[0], 0xFFFFFFFF, string);
		SetPVarInt(playerid,"EatBox",0);
		if(hauls[0][1] >= 500) {
			DestroyDynamicPickup(haulsple), RemovePlayerAttachedObject(playerid,0), SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE), SCM(playerid,0xFFFFFFFF,"Грузовик {1faee9}полон!"), DestroyDynamic3DTextLabel(haulstext[0]);
			haulsple = -1;
		}
		SetPVarInt(playerid,"GetPickup",gettime()+3);
		return true;
	}
	if(pickupid == pickjob) {
	    if(Player[playerid][pFraction] != 0) return SCM(playerid,0xFF0000FF,"Вы уже состоите в организации!");

	}
	switch(pickupid-1) {
		case 1: { // Позиция когда выйдешь на пикап внутрений в Grove, появишься снаружи
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid,0);
			AC_SetPlayerPos(playerid,2495.2722,-1687.0764,13.5150);
			SetPlayerFacingAngle(playerid, 359.1419);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 2: {
			SetPlayerInterior(playerid,0);
			SetPlayerVirtualWorld(playerid,2);
			AC_SetPlayerPos(playerid,2457.7561,-1657.7288,2047.2317);
			SetPlayerFacingAngle(playerid,358.3682);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
			TogglePlayerControllable(playerid,0), SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 3: { // Позиция когда выйдешь на пикап внутрений в Ballas, появишься снаружи
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid,0);
			AC_SetPlayerPos(playerid,2000.1307,-1118.1412,26.781);
			SetPlayerFacingAngle(playerid, 180.6557);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
        case 4: {
            Player[playerid][pCar][3] = CreateVehicle(400,126.5469,-870.5853,1559.7384,249.5710,-1,-1,150);
		 	SetVehicleVirtualWorld(Player[playerid][pCar][3],playerid+2);
			SetPlayerPos(playerid,131.7143,-876.5355,1559.3179);
			TogglePlayerControllable(playerid,0);
			SetPlayerCameraPos(playerid,131.2243,-876.3266,1563.3444), SetPlayerCameraLookAt(playerid,126.1551,-870.4205,1559.7408,CAMERA_CUT);
			SetPlayerVirtualWorld(playerid,playerid+2);
			SetPVarInt(playerid,"BuyCase",1), SetPVarInt(playerid,"BuyCar",400);
			TextDrawShowForPlayer(playerid,asBox);
			TextDrawShowForPlayer(playerid,asCost);
			TextDrawSetString(Player[playerid][asVname], VehicleNames[GetVehicleModel(GetPlayerVehicleID(playerid)-400)]);
			TextDrawSetString(Player[playerid][asCostV],"350000$");
			TextDrawShowForPlayer(playerid,Player[playerid][asVname]);
			TextDrawShowForPlayer(playerid,Player[playerid][asCostV]);
			TextDrawShowForPlayer(playerid,asLeft);
			TextDrawShowForPlayer(playerid,asRight);
			TextDrawShowForPlayer(playerid,asBuy);
			TextDrawShowForPlayer(playerid,asExit);
			TextDrawShowForPlayer(playerid,asBBuy);
			TextDrawShowForPlayer(playerid,asBExit);
			SelectTextDraw(playerid, 0x1faee9FF), Player[playerid][TDSelect] = true;
		} // Автосалон ЛС
		case 5: {
			if(GetPVarInt(playerid,"GetPickup") > gettime()) return true;
			if(Player[playerid][pFraction][1] != 0 || (GetPVarInt(playerid,"Job") == 1 && GetPVarInt(playerid,"MailJob") < 1)) return SCM(playerid,-1,"Увы, но вы не можете тут работать, {ff0000}по скольку уже состоите в организации!");
			ShowPlayerDialog(playerid,29,DIALOG_STYLE_MSGBOX,"{cc7722}Трудоустройство","{ffffff}Вы действительно хотите {03c03c}начать{ffffff}/{ff0000}закончить {ffffff}рабочий день?\n\
			Чтобы переодеться, вам стоит лишь нажать на кнопку {03c03c}'Да'","Да","Отмена");
			SetPVarInt(playerid,"GetPickup",gettime()+10);
		}
		case 6: { // Позиция когда выйдешь на пикап внутрений в Vagos, появишься снаружи
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid,0);
			AC_SetPlayerPos(playerid,2808.7112,-1178.3368,25.3576);\
			SetPlayerFacingAngle(playerid,269.0907);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 7: { // Позиция когда выйдешь на пикап внутрений в Aztec, появишься снаружи
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid,0);
			AC_SetPlayerPos(playerid,1884.4657,-2000.8673,13.5469);
			SetPlayerFacingAngle(playerid, 181.6773);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 8: { // Позиция когда выйдешь на пикап внутрений в Rifa, появишься снаружи
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid,0);
			AC_SetPlayerPos(playerid,1946.5869,-1564.5144,13.6128);
			SetPlayerFacingAngle(playerid, 140.4446);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 9: {
			SetPlayerInterior(playerid,0);
			SetPlayerVirtualWorld(playerid,3);
			AC_SetPlayerPos(playerid,2457.7561,-1657.7288,2047.2317);
			SetPlayerFacingAngle(playerid,358.3682);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
			TogglePlayerControllable(playerid,0), SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 10: {
			SetPlayerInterior(playerid,0);
			SetPlayerVirtualWorld(playerid,4);
			AC_SetPlayerPos(playerid,2457.7561,-1657.7288,2047.2317);
			SetPlayerFacingAngle(playerid,358.3682);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
			TogglePlayerControllable(playerid,0), SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 11: {
			SetPlayerInterior(playerid,0);
			SetPlayerVirtualWorld(playerid,5);
			AC_SetPlayerPos(playerid,2457.7561,-1657.7288,2047.2317);
			SetPlayerFacingAngle(playerid,358.3682);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
			TogglePlayerControllable(playerid,0), SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 12: {
			if(GetPVarInt(playerid,"GetPickup") > gettime()) return true;
			if(Player[playerid][pFraction][1] != 0  || (GetPVarInt(playerid,"Job") == 1 && GetPVarInt(playerid,"ShahtaJob") < 1)) return SCM(playerid,-1,"Увы, но вы не можете тут работать, {ff0000}по скольку уже состоите в организации!");
			ShowPlayerDialog(playerid,30,DIALOG_STYLE_MSGBOX,"{cc7722}Трудоустройство","{ffffff}Вы действительно хотите {03c03c}начать{ffffff}/{ff0000}закончить {ffffff}рабочий день добытчика руды?\n\
			Чтобы переодеться, вам стоит лишь нажать на кнопку {03c03c}'Да'","Да","Отмена");
			SetPVarInt(playerid,"GetPickup",gettime()+10);
		}
		case 13: { // Позиция когда выйдешь на пикап внутрений в Армии, появишься снаружи
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid,0);
			AC_SetPlayerPos(playerid,226.6496,1885.1958,17.6406);
			SetPlayerFacingAngle(playerid, 90.8280);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 14: {
			SetPlayerInterior(playerid,0);
			SetPlayerVirtualWorld(playerid,1);
			AC_SetPlayerPos(playerid,-424.6073,-131.6688,2102.5557);
			SetPlayerFacingAngle(playerid,304.3306);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
			TogglePlayerControllable(playerid,0), SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 15: { // Позиция когда выйдешь на пикап внутрений в Армии, появишься снаружи
			SetPlayerInterior(playerid,1);
			SetPlayerVirtualWorld(playerid,1);
			AC_SetPlayerPos(playerid,288.2709,-38.4945,1001.5156);
			SetPlayerFacingAngle(playerid,289.6898);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 16: {
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid,0);
			AC_SetPlayerPos(playerid,347.1345,1921.5211,21.9776);
			SetPlayerFacingAngle(playerid, 177.6828);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 17: {
			if(PlayerGangster(playerid)) {
				SCM(playerid,0xFFFFFFFF,"Вы взяли {1faee9}один боевой комплект! ( +74 ед. )");
				SetPlayerAttachedObject(playerid, 0, 3026, 1, -0.372999, -0.059999, 0.000000, 0.000000, 0.000000, 0.000000, 1.470000, 1.700000, 1.349999);
				LVW -= 150, Player[playerid][pAmmo] += 150;
				SetPVarInt(playerid,"Ammo",1);
				format(string,48,"Собранное оружие\n{1faee9}На складе: %d ед.",LVW);
				UpdateDynamic3DTextLabelText(LVWtext, 0xFFFFFFFF, string);
			}
			if(Player[playerid][pFraction][1] == 6) {
				if(GetPVarInt(playerid,"GetAmmo") > gettime()) return SCM(playerid,0xFFFFFFFF,"Брать комплект можно {03c03c}раз в 3 минуты!");
				SCM(playerid,0xFFFFFFFF,"Боекомплект {1faee9}выдан!");
				switch(random(2)) {
					case 0: GiveWeapon(playerid,31,50);
					case 1: GiveWeapon(playerid,30,50);
				}
				LVW -= 150, GiveWeapon(playerid,24,24);
				format(string,48,"Собранное оружие\n{1faee9}На складе: %d ед.",LVW);
				UpdateDynamic3DTextLabelText(LVWtext, 0xFFFFFFFF, string);
				SetPVarInt(playerid,"GetAmmo",gettime()+180);
			}
		}
		case 18: { // Позиция когда выйдешь на пикап внутрений в Армии, появишься снаружи
			SetPlayerInterior(playerid,0);
			SetPlayerVirtualWorld(playerid,0);
			AC_SetPlayerPos(playerid,245.9828,1982.5568,17.6406);
			SetPlayerFacingAngle(playerid,181.1979);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 19: {
			SetPlayerInterior(playerid, 10);
			SetPlayerVirtualWorld(playerid,1);
			AC_SetPlayerPos(playerid,366.1402,-73.5867,1001.5078);
			SetPlayerFacingAngle(playerid, 270.9767);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 20: { // Позиция когда выйдешь на пикап внутрений в LSPD, появишься снаружи
			SetPlayerInterior(playerid,0);
			SetPlayerVirtualWorld(playerid,0);
			AC_SetPlayerPos(playerid,1549.1537,-1675.5107,14.8390);
			SetPlayerFacingAngle(playerid,90.5382);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 21: {
			SetPlayerInterior(playerid, 6);
			SetPlayerVirtualWorld(playerid,1);
			AC_SetPlayerPos(playerid,246.4353,67.9645,1003.6406);
			SetPlayerFacingAngle(playerid, 0.7546);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 22: {
			SetPlayerInterior(playerid,0);
			SetPlayerVirtualWorld(playerid,1);
			AC_SetPlayerPos(playerid,2457.7561,-1657.7288,2047.2317);
			SetPlayerFacingAngle(playerid,358.3682);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
			TogglePlayerControllable(playerid,0), SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 23: {
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid,0);
			AC_SetPlayerPos(playerid,2335.4360,2454.8730,14.9688);
			SetPlayerFacingAngle(playerid, 89.8069);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 24: {
			SetPlayerInterior(playerid, 6);
			SetPlayerVirtualWorld(playerid,1);
			AC_SetPlayerPos(playerid,288.8570,170.0030,1007.1794);
			SetPlayerFacingAngle(playerid, 1.6330);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 25: {
			SetPlayerInterior(playerid,0);
			SetPlayerVirtualWorld(playerid,0);
			AC_SetPlayerPos(playerid,1568.7223,-1692.5176,5.8906);
			SetPlayerFacingAngle(playerid,178.4160);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 26: {
			SetPlayerVirtualWorld(playerid,1);
			AC_SetPlayerPos(playerid,1110.8837,261.7346,1009.0015);
			SetPlayerFacingAngle(playerid, 3.3886);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
			TogglePlayerControllable(playerid,0), SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 27: {
			SetPlayerInterior(playerid,0);
			SetPlayerVirtualWorld(playerid,0);
			AC_SetPlayerPos(playerid,1415.6438,-1702.8107,13.5395);
			SetPlayerFacingAngle(playerid,238.1087);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 28: {
			if(GetPVarInt(playerid,"GetPickup") > gettime() || GetPVarInt(playerid,"DialogActive") == 1) return true;
			SetPVarInt(playerid,"DialogActive",1);
			if(Player[playerid][pBankPass] == 0) return ShowPlayerDialog(playerid,36,DIALOG_STYLE_MSGBOX,"{1faee9}Банковский счет","{ffffff}Для пользования банковскими услугами вам {AC7575}необходимо завести счёт.\nДля этого необходимо иметь при себе {ffffff}1000${03c03c} для стартового вклада.\
			\n\n{ffffff}Каждый час на вас счет будут поступать {03c03c}положительные проценты{ffffff} которые будут поднимать ваш счет.\n\n\n {1faee9}- Вы согласны?","Да","Нет");
			ShowPlayerDialog(playerid,38,DIALOG_STYLE_LIST,"{03c03c}Услуги Банка LS","{03c03c}Пополнить{ffffff}/{AC7575}Снять{ffffff} деньги\nПеревод денег на другой счёт\nИнформация о счете","Выбор","Отмена");
			SetPVarInt(playerid,"GetPickup",gettime()+3);
		}
		case 29: {
			SetPlayerVirtualWorld(playerid,1);
			AC_SetPlayerPos(playerid,1070.9171,1080.4293,1008.2859);
			SetPlayerFacingAngle(playerid, 178.8547);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
			TogglePlayerControllable(playerid,0), SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 30: {
			SetPlayerVirtualWorld(playerid,0);
			AC_SetPlayerPos(playerid,1041.6606,1016.9442,11.0000);
			SetPlayerFacingAngle(playerid,325.5169);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 31: {
			SetPlayerVirtualWorld(playerid,1);
			AC_SetPlayerPos(playerid,238.7747,1603.6788,1082.4359);
			SetPlayerFacingAngle(playerid, 270.6880);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
			TogglePlayerControllable(playerid,0), SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 32: {
			SetPlayerVirtualWorld(playerid,0);
			AC_SetPlayerPos(playerid,1481.0173,-1767.2274,18.7958);
			SetPlayerFacingAngle(playerid,0.0281);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 33: {
			if(GetPVarInt(playerid,"GetPickup") > gettime() || GetPVarInt(playerid,"DialogActive") == 1) return true;
			if(Player[playerid][pFraction][1] != 0 || (GetPVarInt(playerid,"Job") == 1 && GetPVarInt(playerid,"TruckJob") < 1)) return SCM(playerid,-1,"Увы, но вы не можете тут работать, {ff0000}по скольку уже состоите в организации либо уже работаете!");
			SetPVarInt(playerid,"DialogActive",1);
			ShowPlayerDialog(playerid,47,DIALOG_STYLE_MSGBOX,"{cc7722}Трудоустройство","{ffffff}Компании {FFC400}'Real Trucks'{ffffff} требуются опытные водители.\nСуть работы заключается в быстрой и аккуратной перевозки грузов.\n\
			{03c03c}Для работы вам требуются водительское удостоверение и 1000$ для аренды грузовика!\n\n{ffffff} - Ну что, попробуем? Если вы уже работаете и хотите закончить, нажмите {1faee9}'Работа'","Работа","Отмена");
			SetPVarInt(playerid,"GetPickup",gettime()+10);
		}
		case 34: {
			SetPlayerVirtualWorld(playerid,1), SetPlayerInterior(playerid,3);
			AC_SetPlayerPos(playerid,-2029.7258,-106.6515,1035.1719);
			SetPlayerFacingAngle(playerid, 179.0319);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 35: {
			SetPlayerVirtualWorld(playerid,0), SetPlayerInterior(playerid, 0);
			AC_SetPlayerPos(playerid,-2026.5497,-97.7488,35.1641);
			SetPlayerFacingAngle(playerid,357.4222);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 36: {
			if(GetPVarInt(playerid,"GetPickup") > gettime() || GetPVarInt(playerid,"DialogActive") == 1) return true;
			if((Player[playerid][Licenses] & (1<<0) != 0) || GetPVarInt(playerid,"Lesson") > 0) return SCM(playerid,-1,"У вас уже {1faee9}есть вод.удостоверение, либо вы уже начали экзамен!");
			if(Player[playerid][pMoney] < 800) return SCM(playerid,-1,"У вас {1faee9}недостаточно денег для начала экзамена!");
			SetPVarInt(playerid,"DialogActive",1);
			ShowPlayerDialog(playerid,49,DIALOG_STYLE_MSGBOX,"{cc7722}Экзамен по вождению","{ffffff}Автошкола {FFC400}г.San Fierro{ffffff} принимает абитуриентов.\nНа данный момент вы можете сразу сдать экзамен.\n\
			{03c03c}Перед этим вы обязательно должны знать теорию и иметь при себе 800$ как взнос.\n\n{ffffff} - Ну что, начнем? Заметь, {AC7575}при неудачной сдаче - деньги не возвращаются!","Начать","Отмена");
			SetPVarInt(playerid,"GetPickup",gettime()+10);
		}
		case 37: {
			SetPlayerVirtualWorld(playerid,1);
			AC_SetPlayerPos(playerid,1234.9799,-971.0106,1085.0042);
			SetPlayerFacingAngle(playerid, 1.5164);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
			TogglePlayerControllable(playerid,0), SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 38: {
			SetPlayerVirtualWorld(playerid,0), SetPlayerInterior(playerid, 0);
			AC_SetPlayerPos(playerid,-2049.1309,454.7401,35.1719);
			SetPlayerFacingAngle(playerid,334.9061);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 39: {
			SetPlayerVirtualWorld(playerid,0), SetPlayerInterior(playerid, 0);
			AC_SetPlayerPos(playerid,-1605.4674,714.1584,13.0535);
			SetPlayerFacingAngle(playerid, 4.9974);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 40: {
			SetPlayerVirtualWorld(playerid,1), SetPlayerInterior(playerid, 10);
			AC_SetPlayerPos(playerid,246.5547,110.1917,1003.2188);
			SetPlayerFacingAngle(playerid,1.4902);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 41: {
			SetPlayerVirtualWorld(playerid,1), SetPlayerInterior(playerid, 6);
			AC_SetPlayerPos(playerid,246.4716,83.9882,1003.6406);
			SetPlayerFacingAngle(playerid,180.1719);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);

		}
		case 42: {
		    SetPlayerVirtualWorld(playerid,0);
			AC_SetPlayerPos(playerid,1174.9514,-1323.3771,14.5938);
			SetPlayerFacingAngle(playerid,272.0658);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}
		case 43: {
		    SetPlayerVirtualWorld(playerid,1);
			AC_SetPlayerPos(playerid,1170.4658,-1310.7592,1001.5734);
			SetPlayerFacingAngle(playerid,90.1453);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
			TogglePlayerControllable(playerid,0), SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
	}
	return true;
}


public OnPlayerPickUpPickup(playerid, pickupid)
{
	return true;
}

public OnVehicleMod(playerid, vehicleid, componentid) {
	return true;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return true;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return true;
}

public OnVehicleDamageStatusUpdate(vehicleid, playerid) {
	new Float:health;
    GetVehicleHealth(vehicleid,health);
	if(health < 301.0 && GetPVarInt(playerid,"Repaired") == 0) {
	    GameTextForPlayer(playerid, "~r~ENGINE BROKEN", 2000, 1), SetVehicleHealth(vehicleid,300.0);
 		SetVehicleParamsEx(vehicleid,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,alarm,doors,bonnet,boot,objective), VNULL<vehicleid:engines>;
	}
	return true;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
    new Menu:Menu = GetPlayerMenu(playerid);
    if(Menu == rMenu) {
	    switch(row) {
	        case 0: {
         		if(GetPlayerState(GetPVarInt(playerid,"ReconID")) == PLAYER_STATE_DRIVER) PlayerSpectateVehicle(playerid, GetPlayerVehicleID(GetPVarInt(playerid,"ReconID")));
         		else PlayerSpectatePlayer(playerid, GetPVarInt(playerid,"ReconID"));
         		SetPlayerInterior(playerid, GetPlayerInterior(GetPVarInt(playerid,"ReconID")));
				SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(GetPVarInt(playerid,"ReconID")));
	        	TextDrawHideForPlayer(playerid,rvbox),
				TextDrawHideForPlayer(playerid,rvmodel[playerid]),
		 		TextDrawHideForPlayer(playerid,rvname[playerid]),
		 		TextDrawHideForPlayer(playerid,rvhealth[playerid]),
			 	TextDrawHideForPlayer(playerid,rvspeed[playerid]);
			 	if(GetPlayerState(GetPVarInt(playerid,"ReconID")) == PLAYER_STATE_DRIVER) {
	    			TextDrawShowForPlayer(playerid,rvbox),
	 				TextDrawShowForPlayer(playerid,rvmodel[playerid]),
				 	TextDrawShowForPlayer(playerid,rvname[playerid]),
				 	TextDrawShowForPlayer(playerid,rvhealth[playerid]),
				 	TextDrawShowForPlayer(playerid,rvspeed[playerid]);
			 	}
                ShowMenuForPlayer(rMenu, playerid);
	        }
	        case 1: SetPVarInt(playerid,"ReasonKick",1), ShowPlayerDialog(playerid,23,DIALOG_STYLE_INPUT,"{03c03c}Кикнуть игрока","{ffffff}Введите причину кика данного игрока.","Кик","Отмена"),ShowMenuForPlayer(rMenu, playerid);
	        case 2: SetPVarInt(playerid,"ReasonKick",2), ShowPlayerDialog(playerid,23,DIALOG_STYLE_INPUT,"{03c03c}Заварнить игрока","{ffffff}Введите причину варна для данного игрока.","Варн","Отмена"),ShowMenuForPlayer(rMenu, playerid);
	        case 3: SetPVarInt(playerid,"ReasonKick",3), ShowPlayerDialog(playerid,23,DIALOG_STYLE_INPUT,"{03c03c}Забанить игрока","{ffffff}Введите количество дней бана данного игрока.","Бан","Отмена"),ShowMenuForPlayer(rMenu, playerid);
	        case 4: {
				fcor
    			GetPlayerPos(GetPVarInt(playerid,"ReconID"),x,y,z), CreateExplosionForPlayer(GetPVarInt(playerid,"ReconID"), x,y,z+7.5, 5, 0.5), ShowMenuForPlayer(rMenu, playerid);
			}
	        case 5: {
	            new Float:health, Float:x, Float:y, Float:z;
	    		GetPlayerHealth(GetPVarInt(playerid,"ReconID"), health), SetPlayerHealth(GetPVarInt(playerid,"ReconID"), health-5.0), GetPlayerPos(GetPVarInt(playerid,"ReconID"), x, y, z), AC_SetPlayerPos(GetPVarInt(playerid,"ReconID"), x, y, z+3.0), PlayerPlaySound(GetPVarInt(playerid,"ReconID"), 1130, x, y, z+3.0);
				SCM(playerid,COLOR_LIGHTRED,"Игрок был шлепнут");
				ShowMenuForPlayer(rMenu, playerid);
			}
	        case 6: ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{03c03c}В РАЗРАБОТКЕ!","{ffffff}В {ff0000}РАЗРАБОТКЕ!","OK",""),ShowMenuForPlayer(rMenu, playerid);
	        case 7: callcmd::recon(playerid, "");
		}
	}
	return true;
}

public OnPlayerExitedMenu(playerid) {
	new Menu:Menu = GetPlayerMenu(playerid);
	if(!IsValidMenu(Menu)) return true;
	ShowMenuForPlayer(Menu, playerid);
	TogglePlayerControllable(playerid,0);
	return true;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid) {
	return true;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_ACTION && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) return callcmd::engine(playerid, "");
    
	if(newkeys & KEY_FIRE && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) VXOR<GetPlayerVehicleID(playerid):limit>, PlayerTextDrawSetString(playerid,slimit[playerid], (VVB<GetPlayerVehicleID(playerid):limit>) ? ("~r~SPEED LIMIT") : ("~g~SPEED LIMIT"));
	if(newkeys & KEY_WALK) {
	    for(new i = 0; i <= Houses; i++) {
     		if(IsPlayerInRangeOfPoint(playerid,2.5,Ints[House[i][hInt]][hiX],Ints[House[i][hInt]][hiY],Ints[House[i][hInt]][hiZ])) ShowPlayerDialog(playerid,11,DIALOG_STYLE_MSGBOX,"{1faee9}Выход","{ffffff}Куда бы вы хотели выйти?","Улица","Гараж");
      		else if(IsPlayerInRangeOfPoint(playerid,1.5,897.7181,-354.6801,2177.6160) && GetPlayerVirtualWorld(playerid) == House[i][hID]) AC_SetPlayerPos(playerid,Ints[House[i][hInt]][hiX],Ints[House[i][hInt]][hiY],Ints[House[i][hInt]][hiZ]), SetPlayerInterior(playerid,Ints[House[i][hInt]][hiInt]);
		}
	    for(new a = 0; a <= Atms; a++) {
 			if(!IsPlayerInRangeOfPoint(playerid,2.0,Atm[a][aX], Atm[a][aY], Atm[a][aZ])) continue;
   			if(Player[playerid][pBankPass] == 0) return SCM(playerid,0xAC7575FF,"У вас нет счёта в банке!");
 			ShowPlayerDialog(playerid,44,DIALOG_STYLE_LIST,"{cc7722}Услуги Банкомата","{03c03c}Пополнить{ffffff}/{AC7575}Снять{ffffff} деньги\nПополнить мобильный счёт","Далее","Отмена");
		}
	}
  	if(newkeys & KEY_CROUCH && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	  {
  	        callcmd::lights(playerid, "");
  	        
	   		#define vehid GetPlayerVehicleID(playerid)
			for(new i = 0; i <= Houses; i++) {
			    if(IsPlayerInRangeOfPoint(playerid,5.0,896.9077,-358.9295,2177.6160) && GetPlayerVirtualWorld(playerid) == House[i][hID]) {
   					SetVehiclePos(vehid,House[i][cX],House[i][cY],House[i][cZ]), SetVehicleZAngle(vehid,House[i][cA]), SetVehicleVirtualWorld(vehid, 0),AC_SetPlayerPos(playerid,House[i][cX],House[i][cY],House[i][cZ]), SetPlayerVirtualWorld(playerid,0), PutPlayerInVehicle(playerid, vehid, 0);
				}
				else if(IsPlayerInRangeOfPoint(playerid,3.0,House[i][cX],House[i][cY],House[i][cZ])) {
    				if(Player[playerid][pHouse] != i) continue;
			    	SetVehiclePos(vehid,896.9077,-358.9295,2177.6160+2.0),SetVehicleZAngle(vehid,91.2867),SetVehicleVirtualWorld(vehid, House[i][hID]);
        			AC_SetPlayerPos(playerid,896.9077,-358.9295,2177.6160+2.0), SetPlayerVirtualWorld(playerid,House[i][hID]), PutPlayerInVehicle(playerid, vehid, 0);
					PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0), TogglePlayerControllable(playerid,0), SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
				}
			}
			#undef vehid
	}
	if(newkeys & KEY_RIGHT && GetPVarInt(playerid,"SPArmy") > 0) {
		SetPVarInt(playerid,"SPArmy", (GetPVarInt(playerid,"SPArmy") > 7) ? 1 : (GetPVarInt(playerid,"SPArmy")+1));
	    switch(GetPVarInt(playerid,"SPArmy")) {
	        case 1: SetPlayerCameraPos(playerid,138.064208,1939.588256,32.955593), SetPlayerCameraLookAt(playerid,96.528137,1919.184570,18.645965,1);
			case 2: SetPlayerCameraPos(playerid,101.873970,1903.434936,36.017295), SetPlayerCameraLookAt(playerid,89.164688,1921.306152,18.406860,1);
			case 3: SetPlayerCameraPos(playerid,114.169944,1816.838500,35.398437), SetPlayerCameraLookAt(playerid,127.678741,1868.381225,18.341930,1);
			case 4: SetPlayerCameraPos(playerid,190.580947,1937.711914,25.140625), SetPlayerCameraLookAt(playerid,165.546615,1959.413818,19.149534,1);
			case 5: SetPlayerCameraPos(playerid,335.364776,1974.819702,27.725532), SetPlayerCameraLookAt(playerid,349.512329,1918.584228,22.477622,1);
			case 6: SetPlayerCameraPos(playerid,345.286743,1924.570800,30.342241), SetPlayerCameraLookAt(playerid,291.708648,1972.144531,18.140625,1);
			case 7: SetPlayerCameraPos(playerid,334.257293,1801.419799,27.924251), SetPlayerCameraLookAt(playerid,347.249145,1795.940063,18.764564,1);
	}   }
	return true;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	return true;
}

public OnPlayerUpdate(playerid)
{
    if(GetPVarInt(playerid, "AFK") >= 2) return SetPVarInt(playerid, "AFK", 0);
	return true;
}

public OnPlayerStreamIn(playerid, forplayerid) {
	Iter_Add(StreamedPlayers[forplayerid],playerid);
	if(GetPVarInt(playerid,"Mask") == 1) ShowPlayerNameTagForPlayer(forplayerid,playerid,0);
	return true;
}

public OnPlayerStreamOut(playerid, forplayerid) return Iter_Remove(StreamedPlayers[forplayerid],playerid);

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return true;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return true;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(strfind(inputtext,"%",true) != -1) return strdel(inputtext,0,strlen(inputtext));
    new dstring[255+1];
    switch(dialogid) {
		case 1: {
            if(!response) return KickEx(playerid);
            for(new i = strlen(inputtext); i != 0; --i)
			switch(inputtext[i]) { case 'А'..'Я', 'а'..'я', ' ': return ShowPlayerDialog(playerid,1,DIALOG_STYLE_MSGBOX,"{ffcc00}Ошибка ввода","{ffffff}Ваш текст содержит символы кириллици, пожалуйста смените вашу раскладку.","Повтор",""); }
			if(GetPVarInt(playerid,"LoginTime") > gettime()) {
				format(dstring, 132, "{ffffff}Аккаунт ещё не успел загрузиться пожалуйста повторите попытку\n\n{ff0000}Ник-нейм: %s\n{00ff00}Пароль:",Name(playerid));
				ShowPlayerDialog(playerid, 1, DIALOG_STYLE_PASSWORD, "{ffcc00}Авторизация", dstring, "Принять","Отмена");
				return true;
			}
			else if(!strlen(inputtext)) {
				format(dstring, 166, "{ffffff}Приветствую вас, дорогой игрок!\nВаш аккаунт зарегистрирован в системе, пожалуйста авторизуйтесь.\n\n{ff0000}Ник-нейм: %s\n{00ff00}Пароль:",Name(playerid));
				ShowPlayerDialog(playerid, 1, DIALOG_STYLE_PASSWORD, "{ffcc00}Авторизация", dstring, "Принять","Отмена");
				return true;
			}
			mysql_format(connects, query, 118, "SELECT * FROM `accounts` WHERE Name = '%s' AND `password` = '%s'",Name(playerid), inputtext);
			mysql_tquery(connects, query, "LoadAccount", "i", playerid);
        }
        case 2: {
            if(!response) return KickEx(playerid);
			if(strlen(inputtext) < 3 || strlen(inputtext) > 16) {
		    	return ShowPlayerDialog(playerid, 1, DIALOG_STYLE_INPUT, "{ffcc00}Регистрация","{ffffff}Приветствую вас, дорогой игрок!\nПеред регистрацией обратите внимание на правила:\n\n\
			  	{ff0000}- Запрещается смешивать игровой процесс с реальной жизнью.\n\
			  	{ffff00}- Игрок обязан знать все Role Play правила и правила сервера. ( След. Графа )\n\
		      	{00ff00}- Желательно перед игрой посетить наш официальный сайт www.Cheery-rp.ru\n\n\
			  	{ff0000} Пожалуйста, придумайте ваш будущий пароль:", "Далее","Отмена");
			}
            else {
    		    Player[playerid][ClothesRound] = false;
				Player[playerid][SSCase] = 0;
				Player[playerid][ChosenSkin] = 0;
				SetSpawnInfo(playerid, 0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
                strmid(Player[playerid][pPassword], inputtext, 0, strlen(inputtext), 32);
               	ShowPlayerDialog(playerid, 3, 1, "{ffcc00}Альтернативные данные", "{ffffff}Убедительная просьба ввести ваш {ff0000}настоящий {ffffff}e-mail адресс.\nСейчас на него придет код с подтверждением для продолжения регистрации\nТак-же при утере пароля вы сможете выслать восстановительное письмо на этот адресс!", "Далее", "Отмена");
				return true;
		}	}
        case 3: {
   		    if(!response) return KickEx(playerid);
         	if(strlen(inputtext) < 1 || strlen(inputtext) > 36) return ShowPlayerDialog(playerid, 3, 1, "{ffcc00}Альтернативные данные", "{ffffff}Убедительная просьба ввести ваш {ff0000}настоящий {ffffff}e-mail адресс.\nПри утере пароля вы сможете выслать восстановительное письмо на этот адресс!", "Далее", "Отмена");
			if(strfind(inputtext, "@", true) == -1 || strfind(inputtext, ".", true) == -1 || strlen(inputtext) < 5) {
				SendClientMessage(playerid, COLOR_GREY, "[Ошибка] Попробуйте еще раз");
  				return ShowPlayerDialog(playerid, 3, 1, "{ffcc00}Альтернативные данные", "{ffffff}Убедительная просьба ввести ваш {ff0000}настоящий {ffffff}e-mail адресс.\nПри утере пароля вы сможете выслать восстановительное письмо на этот адресс!", "Далее", "Отмена");
   			}
			strmid(Player[playerid][pMail], inputtext, 0, strlen(inputtext), 32);
			ShowPlayerDialog(playerid, 4, 1, "{ffcc00}Реферал", "{ffffff}Если вас пригласил друг играть на наш сервер - просьба указать его ник в данном поле.\n\n{ADFF2F}При достижении вами 4-го уровня он и вы получите вознагрождение в виде 50.000$", "Далее", "Пропуск");
		}
		case 4: {
			if(response) {
				if(!strlen(inputtext)) return ShowPlayerDialog(playerid, 4, 1, "{ffcc00}Реферал", "{ffffff}Если вас пригласил друг играть на наш сервер - просьба указать его ник в данном поле.\n\n{ADFF2F}При достижении вами 4-го уровня он и вы получите вознагрождение в виде 50.000$", "Далее", "Пропуск");
				if(strlen(inputtext) < 1 || strlen(inputtext) > MAX_PLAYER_NAME) return ShowPlayerDialog(playerid, 4, 1, "{ffcc00}Реферал", "{ffffff}Если вас пригласил друг играть на наш сервер - просьба указать его ник в данном поле.\n\n{ADFF2F}При достижении вами 4-го уровня он и вы получите вознагрождение в виде 50.000$", "Далее", "Пропуск");
	    		strmid(Player[playerid][pReferal], inputtext, 0, strlen(inputtext), MAX_PLAYER_NAME);
				format(dstring,39, "Вас пригласил %s", inputtext);
				SendClientMessage(playerid, COLOR_GREEN, dstring);
				ShowPlayerDialog(playerid,5,DIALOG_STYLE_MSGBOX, "{ffcc00}Пол вашего персонажа","{ffffff}Пожалуйста, выберите пол вашего персонажа!", "Мужской", "Женский");
			}
			else ShowPlayerDialog(playerid,5,DIALOG_STYLE_MSGBOX, "{ffcc00}Пол вашего персонажа","{ffffff}Пожалуйста, выберите пол вашего персонажа!", "Мужской", "Женский");
			return true;
		}
		case 5: {
  			new sex[8];
		    switch(response) {
		        case 1: { sex = "Мужской"; Player[playerid][pSex] = 1; }
		        default: { sex = "Женский" ; Player[playerid][pSex] = 2; }
		    }
   			Player[playerid][PlayerLogged] = true, Player[playerid][ClothesRound] = true;
			SetSpawnInfo(playerid, 0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
			SpawnPlayer(playerid);
			return true;
   		}
   		case 6: {
			if(response) {
				if(!strlen(inputtext)) return ShowPlayerDialog(playerid,7,DIALOG_STYLE_INPUT, "Вход в режим модерирования", "Введите в поле ваш пароль от панели модератора", "Вход", "Отмена");
				if(strval(inputtext) != Player[playerid][APass]) return true;
				Player[playerid][Aat] = true;
				if(strcmp(Name(playerid),"YourGame.su",true)!=0) format(dstring, sizeof(dstring), "<M> Модератор %s[%d] %d уровня перешел в режим модерирования.",Name(playerid),playerid,Player[playerid][pAdmin]), SendAdminMessage(0xEAC700FF, dstring);
				else SendClientMessage(playerid, COLOR_RED, "<A> Добро пожаловать, YourGame.su!");
	 	}   }
		case 8: {
		    if(response) {
				for(new i = 0; i <= Houses; i++) {
				    if(IsPlayerInRangeOfPoint(playerid,2.0,House[i][hX], House[i][hY], House[i][hZ])) {
						if(strcmp(House[i][hOwner],"None",true) == 0) ShowPlayerDialog(playerid,12,DIALOG_STYLE_MSGBOX,"{03c03c}Покупка дома","{ffffff}Вы действительно хотите приобрести этот дом?","Да","Нет");
						else {
							if(House[i][hLock] == 0) return GameTextForPlayer(playerid, "~r~LOCKED", 2000, 1);
			      			SetPlayerInterior(playerid,Ints[House[i][hInt]][hiInt]);
			      			AC_SetPlayerPos(playerid,Ints[House[i][hInt]][hiX],Ints[House[i][hInt]][hiY],Ints[House[i][hInt]][hiZ]), SetPlayerVirtualWorld(playerid,House[i][hID]);
		}   }   }   }   }
		case 9: {
			if(response) {
				Player[GetPVarInt(playerid,"HouseSeller")][pMoney] += GetPVarInt(playerid,"HousePrice"), Player[playerid][pMoney] -= GetPVarInt(playerid,"HousePrice");
				Player[GetPVarInt(playerid,"HouseSeller")][pMoney] += House[Player[GetPVarInt(playerid,"HouseSeller")][pHouse]][sMoney], Player[GetPVarInt(playerid,"HouseSeller")][pAmmo] += House[Player[GetPVarInt(playerid,"HouseSeller")][pHouse]][sAmmo], Player[GetPVarInt(playerid,"HouseSeller")][pDrugs] += House[Player[GetPVarInt(playerid,"HouseSeller")][pHouse]][sDrugs];
				House[Player[GetPVarInt(playerid,"HouseSeller")][pHouse]][hUpgrade] = 0;
				House[Player[GetPVarInt(playerid,"HouseSeller")][pHouse]][hCommunal] = 0;
				House[Player[GetPVarInt(playerid,"HouseSeller")][pHouse]][sMoney] = 0,House[Player[GetPVarInt(playerid,"HouseSeller")][pHouse]][sAmmo] = 0,House[Player[GetPVarInt(playerid,"HouseSeller")][pHouse]][sDrugs] = 0;
				Player[playerid][pHouse] = Player[GetPVarInt(playerid,"HouseSeller")][pHouse], strmid(House[Player[playerid][pHouse]][hOwner],Name(playerid),0,24,24),Player[GetPVarInt(playerid,"HouseSeller")][pHouse] = 9999;
				SCM(playerid,-1,"Поздравляем! Вы приобрели новый дом, всю помощь по дому вы найдете в меню помощи (/help) или на форуме!");
				Success(playerid) Success(GetPVarInt(playerid,"HouseSeller"))
				SCM(GetPVarInt(playerid,"HouseSeller"),-1,"Поздравляем! Вы успешно продали дом.");
				SaveHouse(House[Player[playerid][pHouse]][hID]);
				DeletePVar(playerid,"HouseSeller"),DeletePVar(playerid,"HousePrice");
				return true;
		}   }
		case 10: {
		    if(response) {
				#define h   Player[playerid][pHouse]
		    	switch(listitem) {
		    	    case 0: {
			 			House[h][hLock] = (House[h][hLock] == 0) ? 1 : 0;
			 			GameTextForPlayer(playerid, (House[h][hLock]) ? ("~g~Open") : ("~r~Locked"), 1000, 3);
					}
		    	    case 1: {
		    	        new priority[12], door[18+1];
					    switch(House[h][hPriority]) {
					        case 0: priority = "Фургон";
					        case 1: priority = "Эконом";
					        case 2: priority = "Обычный";
						}
						switch(House[h][hLock]) {
							case 0: door = "{ff0000}Закрыта";
							case 1: door = "{03c03c}Открыта";
						}
		    	        format(dstring,sizeof(dstring),"{ffffff}Дом\t\t\t {ff0000}№%d\n{ffffff}Владелец:\t\t %s\nСтоимость дома:\t %d$\nПроживающих:\t\t %d\nМестоположение:\t %s\nНа счету дома:\t\t %d$\nДверь:\t\t\t %s",
						House[h][hID],House[h][hOwner],House[h][hPrice],House[h][hHousemans],House[h][hStreet],House[h][hCommunal],door);
						ShowPlayerDialog(playerid,10,DIALOG_STYLE_MSGBOX,"{03c03c}Статистика дома",dstring,"Ок","");
					}
					case 2: {
					    if(GetPlayerVirtualWorld(playerid) != House[h][hID]) return SCM(playerid,0xAC7575FF,"Необходимо находиться внутри своего дома!");
						ShowPlayerDialog(playerid,62,DIALOG_STYLE_LIST,"Улучшения {1faee9}дома","Сейф\nШкаф\nГараж","Выбор","Отмена");
					}
				}
		    }
			#undef h
  		}
		case 11: {
		    for(new i = 0; i <= Houses; i++) {
					if(IsPlayerInRangeOfPoint(playerid,2.0,Ints[House[i][hInt]][hiX],Ints[House[i][hInt]][hiY],Ints[House[i][hInt]][hiZ])) {
			        	if(GetPlayerVirtualWorld(playerid) == House[i][hID]) {
							if(response) SetPlayerInterior(playerid,0), AC_SetPlayerPos(playerid,House[i][hX],House[i][hY],House[i][hZ]), SetPlayerVirtualWorld(playerid,0), SetPVarInt(playerid,"GetPickup",gettime()+7);
							else {
							    if(House[i][hUpgrade] < 3) return SCM(playerid,0xAC7575FF,"В данном доме не установлен гараж!");
								SetPlayerInterior(playerid,0), SetPlayerVirtualWorld(playerid,House[i][hID]), AC_SetPlayerPos(playerid,897.6984,-354.6799,2177.6160), SetPlayerFacingAngle(playerid,358.9425), TogglePlayerControllable(playerid,0), SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
							}
			}   }   } return true;
		}
		case 12: if(response) callcmd::buyhome(playerid, "");
		case 13: {
		    if(response) {
		    	switch(listitem) {
					case 0: ShowPlayerDialog(playerid,14,DIALOG_STYLE_INPUT,"Деньги банды","{ffffff}Пожалуйста введите сумму денег которую хотите взять или положить в банк банды.\n{ff0000}Внимание, перед суммой поставьте + или - ,плюс для того, чтобы положить, и минус для того чтобы снять.\n\
					{ffffff}Пример: {ff0000}+500","Далее","Отмена");
					case 1: ShowPlayerDialog(playerid,16,DIALOG_STYLE_INPUT,"Амуниция банды","{ffffff}Пожалуйста введите число патрон которое хотите взять или положить на склад банды.\n{ff0000}Внимание, перед числом поставьте + или - ,плюс для того, чтобы положить, и минус для того чтобы взять.\n\
					{ffffff}Пример: {ff0000}+25","Далее","Отмена");
					case 2: ShowPlayerDialog(playerid,57,DIALOG_STYLE_INPUT,"Наркотики банды","{ffffff}Пожалуйста введите число грамм которое хотите взять или положить на склад банды.\n{ff0000}Внимание, перед числом поставьте + или - ,плюс для того, чтобы положить, и минус для того чтобы взять.\n\
					{ffffff}Пример: {ff0000}+10","Далее","Отмена");
		}   }   }
		case 14: {
		    if(response) {
		        if(Player[playerid][pFraction][0] == 0) return SCM(playerid,0xFF0000FF,"Данная функция доступна только лидеру!");
		        if(strlen(inputtext) < 2) return ShowPlayerDialog(playerid,14,DIALOG_STYLE_INPUT,"Деньги банды","{ffffff}Пожалуйста введите сумму денег которую хотите взять или положить в банк банды.\n{ff0000}Внимание, перед суммой поставьте + или - ,плюс для того, чтобы положить, и минус для того чтобы снять.\n{ffffff}Пример: {ff0000}+500","Далее","Отмена");
            	for(new i = strlen(inputtext); i != 0; --i) {
           			switch(inputtext[i]) {
					   	case 'A'..'Z', 'a'..'z', ' ': return ShowPlayerDialog(playerid,14,DIALOG_STYLE_INPUT,"{ff2400}Ошибка","{ffffff}Пожалуйста повторите {03c03c}попытку.","Ок","");
					}
				}
				for(new w;w<sizeof(Ware);w++) {
					if(IsPlayerInRangeOfPoint(playerid, 3.0, Ware[w][wX], Ware[w][wY], Ware[w][wZ]) && Player[playerid][pFraction][1] == Ware[w][wFraction]) {
					    if(strfind(inputtext, "+", true) != -1) {
		    				strdel(inputtext,0,1);
							if(Player[playerid][pMoney] < strval(inputtext)) return SCM(playerid,0xFF0000FF,"У вас недостаточно денег!");
							Ware[w][wMoney] += strval(inputtext), Player[playerid][pMoney] -= strval(inputtext), Success(playerid)
							format(warehousetext,sizeof(warehousetext),"Склад %s\nАммуниции: %d\nНаркотиков: %d\nДенег: %d",Ware[w][wName], Ware[w][wAmmo], Ware[w][wDrugs], Ware[w][wMoney]);
	 						UpdateDynamic3DTextLabelText(warehouset[w], 0xFF9900FF, warehousetext);
	 						return false;
						}
	    				else if(strfind(inputtext, "-", true) != -1) {
							strdel(inputtext,0,1);
							if(Ware[w][wMoney] < strval(inputtext)) return SCM(playerid,0xFF0000FF,"В банке недостаточно денег!");
							Player[playerid][pMoney] += strval(inputtext), Ware[w][wMoney] -= strval(inputtext), Success(playerid)
							format(warehousetext,sizeof(warehousetext),"Склад %s\nАммуниции: %d\nНаркотиков: %d\nДенег: %d",Ware[w][wName], Ware[w][wAmmo], Ware[w][wDrugs], Ware[w][wMoney]);
	 						UpdateDynamic3DTextLabelText(warehouset[w], 0xFF9900FF, warehousetext);
	 						return false;
	 					}
					}
				}
			}
		}
		case 16: {
		    if(response) {
		        if(Player[playerid][pFraction][2] < 4) return SCM(playerid,0xFF0000FF,"Функция доступна с 4 ранга!");
		        if(strlen(inputtext) == 0) return ShowPlayerDialog(playerid,16,DIALOG_STYLE_INPUT,"Амуниция банды","{ffffff}Пожалуйста введите сумму патрон которую хотите взять или положить на склад банды.\n{ff0000}Внимание, перед суммой поставьте + или - ,плюс для того, чтобы положить, и минус для того чтобы взять.\n{ffffff}Пример: {ff0000}+25","Далее","Отмена");
            	for(new i = strlen(inputtext); i != 0; --i) {
           			switch(inputtext[i]) {
					   	case 'A'..'Z', 'a'..'z', ' ': return ShowPlayerDialog(playerid,16,DIALOG_STYLE_INPUT,"{ff2400}Ошибка","{ffffff}Пожалуйста повторите {03c03c}попытку.","Ок","");
					}
				}
				for(new w;w<sizeof(Ware);w++) {
					if(IsPlayerInRangeOfPoint(playerid, 3.0, Ware[w][wX], Ware[w][wY], Ware[w][wZ]) && Player[playerid][pFraction][1] == Ware[w][wFraction]) {
					    if(strfind(inputtext, "+", true) != -1) {
		    				strdel(inputtext,0,1);
							if(Player[playerid][pAmmo] < strval(inputtext)) return SCM(playerid,0xFF0000FF,"У вас недостаточно патронов!");
							Ware[w][wAmmo] += strval(inputtext), Player[playerid][pAmmo] -= strval(inputtext), Success(playerid)
							format(warehousetext,sizeof(warehousetext),"Склад %s\nАммуниции: %d\nНаркотиков: %d\nДенег: %d",Ware[w][wName], Ware[w][wAmmo], Ware[w][wDrugs], Ware[w][wMoney]);
	 						UpdateDynamic3DTextLabelText(warehouset[w], 0xFF9900FF, warehousetext);
	 						return false;
						}
	    				else if(strfind(inputtext, "-", true) != -1) {
							strdel(inputtext,0,1);
							if(Ware[w][wAmmo] < strval(inputtext)) return SCM(playerid,0xFF0000FF,"На складе недостаточно патронов!");
							Player[playerid][pAmmo] += strval(inputtext), Ware[w][wAmmo] -= strval(inputtext), Success(playerid)
							format(warehousetext,sizeof(warehousetext),"Склад %s\nАммуниции: %d\nНаркотиков: %d\nДенег: %d",Ware[w][wName], Ware[w][wAmmo], Ware[w][wDrugs], Ware[w][wMoney]);
	 						UpdateDynamic3DTextLabelText(warehouset[w], 0xFF9900FF, warehousetext);
	 						return false;
	 					}
					}
				}
			}
		}
		case 17: {
		    if(response) {
		        if(strlen(inputtext) == 0) return ShowPlayerDialog(playerid,17,DIALOG_STYLE_INPUT,"{03c03c}Сборка оружия","{ffffff}Введите желаемое количество патрон","Далее","Отмена");
            	for(new i = strlen(inputtext); i != 0; --i) {
           			switch(inputtext[i]) {
					   	case 'A'..'Z', 'a'..'z', ' ': return ShowPlayerDialog(playerid,17,DIALOG_STYLE_INPUT,"{03c03c}Сборка оружия","{ffffff}Введите желаемое количество патрон","Далее","Отмена");
				}   }
				if(strval(inputtext) <= 0 || strval(inputtext) > 9000) return ShowPlayerDialog(playerid,17,DIALOG_STYLE_INPUT,"{03c03c}Сборка оружия","{ff0000}Минимальное количество патрон - 1, максимальное - 9000\n\n{ffffff} - Повторить попытку?","Далее","Отмена");
		        if(Player[playerid][pAmmo] < strval(inputtext)) return ShowPlayerDialog(playerid,17,DIALOG_STYLE_INPUT,"{03c03c}Сборка оружия","{ff0000}У вас нет столько патрон!\n\n{ffffff} - Повторить попытку?","Далее","Отмена");
				GiveWeapon(playerid,GetPVarInt(playerid,"GunC"),strval(inputtext)), Player[playerid][pAmmo] -= strval(inputtext), SetPVarInt(playerid,"GunC",0);
			}
		}
		case 18: {
		    if(response) {
		        if(GetPVarInt(playerid,"Chat") > gettime()) return SCM(playerid,0xFFFFFFFF,"Сообщение можно отправлять {1faee9}раз в минуту!");
		        if(strlen(inputtext) == 0) return ShowPlayerDialog(playerid,18,DIALOG_STYLE_INPUT,"{1faee9}Сообщение Администрации","{ffffff}Если у вас есть жалоба на какого-либо игрока или вопрос, то вы смело можете задать его нам.\n\n\
				Форма подачи жалобы: [id нарушителя] [причина]\n\n{ff0000}Запрещено:\n - Мат\n - Оскорбления\n - Оффтоп ( сообщение не по теме )\n\n{03c03c}Наказание - от кика до бана.","Далее","Отмена");
				format(dstring,sizeof(dstring),"[Репорт от %s(%d)]: {ffffff}%s",Name(playerid),playerid,inputtext), SendAdminMessage(0x1faee9FF,dstring), SCM(playerid,0x1faee9FF,"Сообщение было отправлено администрации, ожидайте ответа!");
		        SetPVarInt(playerid,"ReportTime",gettime()+60);
		    }
		}
		case 19: {
		    if(response) {
		        switch(listitem) {
		            case 1: for(new i = GetMaxPlayers()-1; i != -1; --i) ShowPlayerNameTagForPlayer(playerid, i, (GetPVarInt(playerid,"Tags") == 1) ? (false,SetPVarInt(playerid,"Tags",0)) : (true,SetPVarInt(playerid,"Tags",1))), SCM(playerid,-1,"Запрос был {1faee9}выполнен!");
		        }
		    }
		}
		case 20: {
		    if(response) {
				for(new i = 0; i <= Businesses; i++) {
				    if(IsPlayerInRangeOfPoint(playerid,2.0,Business[i][bX], Business[i][bY], Business[i][bZ])) {
						if(strcmp(Business[i][bOwner],"None",true) == 0) ShowPlayerDialog(playerid,21,DIALOG_STYLE_MSGBOX,"{03c03c}Покупка Бизнеса","{ffffff}Вы действительно хотите приобрести этот бизнес?","Да","Нет");
						else {
							if(Business[i][bLock] == 1) return GameTextForPlayer(playerid, "~r~LOCKED", 2000, 1);
			      			if(Business[i][bType] == 0) AC_SetPlayerPos(playerid,Business[i][bIX],Business[i][bIY],Business[i][bIZ]), SetPVarInt(playerid,"GetPickup",gettime()+2);
			      			else AC_SetPlayerPos(playerid, BInts[Business[i][bInt]][biX],BInts[Business[i][bInt]][biY],BInts[Business[i][bInt]][biZ]),SetPlayerInterior(playerid,BInts[Business[i][bInt]][biInt]), SetPlayerVirtualWorld(playerid,Business[i][bVW]),SetPVarInt(playerid,"GetPickup",gettime()+2);
      					}
					}
				}
			}
		}
		case 21: if(response) callcmd::buybiz(playerid, "");
		case 22: {
			if(response) {
				Player[GetPVarInt(playerid,"BusinessSeller")][pMoney] += GetPVarInt(playerid,"BusinessPrice"), Player[playerid][pMoney] -= GetPVarInt(playerid,"BusinessPrice");
				Player[playerid][pBusiness] = Player[GetPVarInt(playerid,"BusinessSeller")][pBusiness], strmid(Business[Player[playerid][pBusiness]][bOwner],Name(playerid),0,24,24),Player[GetPVarInt(playerid,"BusinessSeller")][pBusiness] = 9999;
				SCM(playerid,-1,"Поздравляем! Вы приобрели новый дом, всю помощь по дому вы найдете в меню помощи (/help) или на форуме!");
				Success(playerid) Success(GetPVarInt(playerid,"BusinessSeller"))
				Business[Player[GetPVarInt(playerid,"BusinessSeller")][pBusiness]][bCommunal] = 0;
				SCM(GetPVarInt(playerid,"BusinessSeller"),-1,"Поздравляем! Вы успешно продали бизнес.");
				SaveHouse(Business[Player[playerid][pBusiness]][bID]);
				DeletePVar(playerid,"HouseSeller"),DeletePVar(playerid,"BusinessPrice");
				return true;
		}   }
		case 23: {
			if(response) {
			    switch(GetPVarInt(playerid,"ReasonKick")) {
			        case 1: {
			            if(strlen(inputtext) == 0) return ShowPlayerDialog(playerid,23,DIALOG_STYLE_INPUT,"{03c03c}Кикнуть игрока","{ffffff}Введите причину кика данного игрока.","Кик","Отмена"),ShowMenuForPlayer(rMenu, playerid);
      					format(dstring,116,"%s был кикнут администратором %s. Причина: %s",Name(GetPVarInt(playerid,"ReconID")),Name(playerid),inputtext);
						SendClientMessageToAll(COLOR_LIGHTRED,dstring);
						KickEx(GetPVarInt(playerid,"ReconID"));
					}
			        case 2: {}
			        case 3: {
						SetPVarInt(playerid,"days", (strlen(inputtext) == 0) ? 7 : (strval(inputtext)));
    					SetPVarInt(playerid,"ReasonKick",4);
    					ShowPlayerDialog(playerid,23,DIALOG_STYLE_INPUT,"{03c03c}Забанить игрока","{ffffff}Введите причину бана данного игрока.","Бан","Отмена"),ShowMenuForPlayer(rMenu, playerid);
					}
			        case 4: {
                        if(strlen(inputtext) == 0) return ShowPlayerDialog(playerid,23,DIALOG_STYLE_INPUT,"{03c03c}Забанить игрока","{ffffff}Введите причину бана данного игрока.","Бан","Отмена"),ShowMenuForPlayer(rMenu, playerid);
						format(dstring,116,"%s был забанен администратором %s на %d дней. Причина: %s",Name(GetPVarInt(playerid,"ReconID")),Name(playerid),GetPVarInt(playerid,"days"),inputtext);
						SendClientMessageToAll(COLOR_LIGHTRED,dstring);
						Player[GetPVarInt(playerid,"ReconID")][pBan] = gettime() + GetPVarInt(playerid,"days")*86400-43200;
						KickEx(GetPVarInt(playerid,"ReconID"));
					}
			    }
			}
		}
		case 24: {
		    if(response) {
		    	if(GetPVarInt(playerid,"Job") == 1 && GetPVarInt(playerid,"TaxiJob") < 1 || Player[playerid][pFraction][1] > 0) return SCM(playerid,0xFF0000FF,"[Ошибка]: На данный момент вы уже кем-то работаете или состоите в организации!");
				if(GetPVarInt(playerid,"TaxiJob") == 1) {
				    SetPlayerSkin(playerid,Player[playerid][pModel][0]), SetPlayerColor(playerid,0xFFFFFF33), SetPVarInt(playerid,"TaxiJob",0), SetPVarInt(playerid,"Job",0), Player[playerid][pMoney] += GetPVarInt(playerid,"Cost"), SetPVarInt(playerid,"Cost",0), GameTextForPlayer(playerid, "~g~+$", 3000, 1), taximans--;
					SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+3);
				}
		        else {
		            if(Player[playerid][pMoney] < 100) return SCM(playerid,-1,"У вас недостаточно денег {1faee9}для аренды автомобиля!");
					SetPlayerSkin(playerid,261), SetPlayerColor(playerid,0xFFB30033);
					SetPVarInt(playerid,"TaxiJob",1), SetPVarInt(playerid,"Job",1);
					taximans++;
					SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+3);
		        }
		    }
		    else SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+3);
		}
		case 25: {
            if(response) {
				#define vehicleid GetPlayerVehicleID(playerid)
				if(vehicleid >= taxicar[0] && vehicleid <= taxicar[1]) {
					if(Player[playerid][pMoney] < 100) {
				 		RemovePlayerFromVehicle(playerid), SCM(playerid,COLOR_WHITE,"У вас недостаточно денег для аренды автомобиля!");
						return true;
					}
					Arended[vehicleid] = true, Player[playerid][ArendedVehicle] = vehicleid, Player[playerid][pMoney] -= 100, SCM(playerid, COLOR_WHITE, "Транспорт {1faee9}арендован! {ffffff}Для разрыва аренды введите {1faee9}/unrent");
				}
				if(vehicleid >= rentcar[0] && vehicleid <= rentcar[1]) {
					if(Player[playerid][pMoney] < 550) {
				 		RemovePlayerFromVehicle(playerid), SCM(playerid,COLOR_WHITE,"У вас недостаточно денег для аренды автомобиля!");
						return true;
					}
					Arended[vehicleid] = true, Player[playerid][ArendedVehicle] = vehicleid, Player[playerid][pMoney] -= 550, SCM(playerid, COLOR_WHITE, "Транспорт {1faee9}арендован! {ffffff}Для разрыва аренды введите {1faee9}/unrent");

				}
				if(vehicleid >= mailcar[0] && vehicleid <= mailcar[1]) {
					if(Player[playerid][pMoney] < 200) {
				 		RemovePlayerFromVehicle(playerid), SCM(playerid,COLOR_WHITE,"У вас недостаточно денег для аренды автомобиля!");
						return true;
					}
					Arended[vehicleid] = true, Player[playerid][ArendedVehicle] = vehicleid, Player[playerid][pMoney] -= 200, SCM(playerid, COLOR_WHITE, "Транспорт {1faee9}арендован! {ffffff}Для разрыва аренды введите {1faee9}/unrent");
				}
				if(vehicleid >= truckcar[0] && vehicleid <= truckcar[1]) {
					if(Player[playerid][pMoney] < 1000) {
				 		RemovePlayerFromVehicle(playerid), SCM(playerid,COLOR_WHITE,"У вас недостаточно денег для аренды автомобиля!");
						return true;
					}
					Arended[vehicleid] = true, Player[playerid][ArendedVehicle] = vehicleid, Player[playerid][pMoney] -= 1000, SCM(playerid, COLOR_WHITE, "Транспорт {1faee9}арендован! {ffffff}Для разрыва аренды введите {1faee9}/unrent");
				}
				#undef vehicleid
			}
			else return RemovePlayerFromVehicle(playerid);
		}
		case 26: {
			if(response) {
			    switch(listitem) {
			        case 0: {
			            if(Player[playerid][pPhone][1] < 1) return SCM(playerid,0xAC7575FF,"На вашем лицевом счету недостаточно денег для звонка!");
						SetPVarInt(playerid,"Number",1), ShowPlayerDialog(playerid,27,DIALOG_STYLE_INPUT,"{03c03c}Введите номер","{ffffff}Введите номер абонента которому вы хотите позвонить!\n\n\n{1faee9} - Тарификация: 1$ в секунду","Вызов","Отмена");
					}
					case 1: ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{03c03c}В РАЗРАБОТКЕ!","{ffffff}В {ff0000}РАЗРАБОТКЕ!","OK","");
			        case 2: ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{03c03c}В РАЗРАБОТКЕ!","{ffffff}В {ff0000}РАЗРАБОТКЕ!","OK","");
			        case 3: SetPVarInt(playerid,"Number",3), ShowPlayerDialog(playerid,27,DIALOG_STYLE_INPUT,"{03c03c}Укажите местонахождение","{ffffff}[Диспетчер такси]: Пожалуйста, сообщите ваше местонахождение!\n\n\n{1faee9}После того, как вы сообщили ваше местонахождение ожидайте ответ оператора!","Далее","Отмена");
			    }
			}
			else SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
		}
		case 27: {
		    if(response) {
		        switch(GetPVarInt(playerid,"Number")) {
		            case 1: {
		                if(strlen(inputtext) < 1 || strval(inputtext) == 0) return ShowPlayerDialog(playerid,27,DIALOG_STYLE_INPUT,"{03c03c}Введите номер","{ffffff}Введите номер абонента которому вы хотите позвонить!\n\n\n{1faee9} - Тарификация: 1$ в секунду","Вызов","Отмена");
						new sucs;
						foreach(new i : Player) if(Player[i][pPhone][0] == strval(inputtext)) SetPVarInt(playerid,"CalledID",i), SetPVarInt(i,"CalledID",playerid), SetPVarInt(i,"Called",2), SetPVarInt(playerid,"Called",1), PlayerPlaySound(i,23000,0.0,0.0,0.0), sucs++;
						if(sucs == 0) {  SCM(playerid,0xFFEE00FF,"[T] Неправильно набран номер!"), SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE); return true; }
					    SetPlayerChatBubble(playerid,"пытается дозвониться",COLOR_PURPLE,30.0,4000);
					    PlayerPlaySound(playerid,3600,0.0,0.0,0.0);
					    SCM(playerid,0xFFEE00FF,"[T] Связь установлена. Ожидайте ответа абонента.");
		            }
		            case 3: {
		                if(strlen(inputtext) == 0) return ShowPlayerDialog(playerid,27,DIALOG_STYLE_INPUT,"{03c03c}Укажите местонахождение","{ffffff}[Диспетчер такси]: Пожалуйста, сообщите ваше местонахождение!\n\n\n{1faee9}После того, как вы сообщили ваше местонахождение ожидайте ответ оператора!","Далее","Отмена");
						fcor
						GetPlayerPos(playerid,x,y,z);
						SetPVarInt(playerid,"TXS",0);
						foreach(new i : Player) {
							if(IsPlayerInRangeOfPoint(i,450.0,x,y,z) && GetPVarInt(playerid,"TaxiCall") == INVALID_PLAYER_ID && i != playerid && GetPVarInt(i,"TaxiJob") == 1) {
								SetPVarInt(playerid,"TXS",GetPVarInt(playerid,"TXS")+1), format(dstring,130,"[Диспетчер]: {ffffff}Требуется такси, как можно быстрее. Местонахождение клиента: {1faee9}%s. Пейджер: %d",inputtext,playerid), SCM(i,0x1faee9FF,dstring);
								SCM(i,0x1faee9FF,"Для того, чтобы принять заказ {ffffff}Введите: /taxicall [id]");
						}   }
						if(GetPVarInt(playerid,"TXS") == 0) return SCM(playerid,0x1faee9FF,"[Диспетчер Такси]: {ffffff}К сожалению, в вашем районе пока нет свободных автомобилей."), SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
						else { SCM(playerid,0x1faee9FF,"[Диспетчер Такси]: {ffffff}Ожидайте, мы ищем водителя для вашего вызова..."), SetPVarInt(playerid,"Taxi",1)  , SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE); return true;}
			}   }   }
        	else SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
		}
		case 28: {
		     if(response) {
				switch(GetPVarInt(playerid,"Number")) {
	       			case 1: {
						if(strlen(inputtext) == 0) return ShowPlayerDialog(playerid,28,DIALOG_STYLE_INPUT,"{1faee9}Время прибытия","{ffffff}Если вы действительно хотите принять заказ, пожалуйста {03c03c}укажите примерное время прибытия на место.\n\n\n {ffffff} Пример: {1faee9}5 минут","Принять","Отмена");
						format(dstring,96,"[Таксист %s]: {ffffff}Я принял Ваш заказ и будут через {1faee9}%s",Name(playerid),inputtext);
      					SCM(GetPVarInt(playerid,"TaxiCall"),0x1faee9FF,dstring), SCM(GetPVarInt(playerid,"Taxi"),0xFFFFFFFF,"Оставайтесь на месте и {1faee9}никуда не уходите, таксист уже в пути!");
      					SetPVarInt(GetPVarInt(playerid,"TaxiCall"),"TaxiCall",playerid);
           				fcor GetPlayerPos(GetPVarInt(playerid,"TaxiCall"),x,y,z);
						SetPlayerRaceCheckpoint(playerid,1,x,y,z,0.0,0.0,0.0,3.0);
					}
					case 2: {
					    if(strlen(inputtext) == 0) return ShowPlayerDialog(playerid,28,DIALOG_STYLE_INPUT,"{1faee9}Отказ от вызова","{ffffff}Если вы действительно хотите отменить заказ, пожалуйста {03c03c}укажите причину","Отклонить","Отмена");
						format(dstring,144,"[Таксист %s]: {ffffff}Увы, но я не смогу приехать на ваш вызов по причине: {1faee9}%s",Name(playerid),inputtext), SCM(GetPVarInt(playerid,"TaxiCall"),0x1faee9FF,dstring);
						SCM(playerid,0xFFFFFFFF,"Вызов {1faee9}отменен!");
						SetPVarInt(GetPVarInt(playerid,"TaxiCall"),"TaxiCall",INVALID_PLAYER_ID);
						DisablePlayerRaceCheckpoint(playerid), SetPVarInt(playerid,"TaxiCall",INVALID_PLAYER_ID);
		}   }   }   }
		case 29: {
		    if(response) {
		        if(GetPVarInt(playerid,"MailJob") == 0) {
		            if(GetPVarInt(playerid,"Job") == 1 && GetPVarInt(playerid,"MailJob") == 0 || Player[playerid][pFraction][1] != 0) return SCM(playerid,0xFF0000FF,"[Ошибка]: На данный момент вы уже кем-то работаете или состоите в организации!");
		            if(Player[playerid][pMoney] < 200) return SCM(playerid,-1,"У вас недостаточно денег {1faee9}для аренды автомобиля!");
					SetPlayerSkin(playerid, (Player[playerid][pSex]==1) ? 71 : 69);
					SetPVarInt(playerid,"MailJob",1), SetPVarInt(playerid,"Job",1);
					SetPlayerCheckpoint(playerid,1304.1097,-1874.5109,13.5525,1.0);
					SetPVarInt(playerid,"MailSend",1);
					SCM(playerid,0x1faee9FF,"Для работы вам {ffffff}необходим служебный транспорт!");
					RemovePlayerAttachedObject(playerid,0);
		        }
		        else SetPlayerSkin(playerid,Player[playerid][pModel][0]), SetPVarInt(playerid,"MailJob",0), SetPVarInt(playerid,"MailSend",0), SetPVarInt(playerid,"Job",0), Player[playerid][pMoney] += GetPVarInt(playerid,"Cost"), SetPVarInt(playerid,"Cost",0), GameTextForPlayer(playerid, "~g~+$", 3000, 1),
		        DisablePlayerCheckpoint(playerid), DisablePlayerRaceCheckpoint(playerid), RemovePlayerAttachedObject(playerid,0);
		    }
		}
		case 30: {
		    if(response) {
		        if(GetPVarInt(playerid,"ShahtaJob") == 0) {
		            if(GetPVarInt(playerid,"Job") == 1  && GetPVarInt(playerid,"ShahtaJob") == 0 || Player[playerid][pFraction][1] != 0) return SCM(playerid,0xFF0000FF,"[Ошибка]: На данный момент вы уже кем-то работаете или состоите в организации!");
					SetPVarInt(playerid,"ShahtaJob",1), SetPVarInt(playerid,"Job",1);
					new rand = random(sizeof(jP));
					SetPlayerCheckpoint(playerid, jP[rand][0],jP[rand][1],jP[rand][2], 1.2);
					SetPVarInt(playerid,"ShahtaSend",1),SetPVarInt(playerid,"ShahtaRange",rand*18);
					SCM(playerid,0x1faee9FF,"Начинайте {ffffff}собирать руду, она разбросана по всей скале!");
					SCM(playerid,0x1faee9FF,"Это высокооплачиваемая работа, так-как {1faee9}вы будите терять много энергии и времени!");
                    SCM(playerid,0x1faee9FF,"Чем дальше находится руда, {ffffff}тем больше вы будите получать денег за неё!");
					SetPlayerAttachedObject(playerid, 0, 19160, 2, 0.102999, 0.000000, 0.000000, -0.200028, 0.000000, 0.000000, 1.125998, 1.152000, 1.252000);
					SetPlayerAttachedObject(playerid, 1, 18634, 6, 0.072999, 0.022000, 0.012000, 93.300018, -101.200012, 2.699999, 1.764998, 1.641999, 1.654998);
		        }
		        else SetPlayerSkin(playerid,Player[playerid][pModel][0]), SetPVarInt(playerid,"Job",0), SetPVarInt(playerid,"ShahtaSend",0), SetPVarInt(playerid,"ShahtaJob",0), Player[playerid][pMoney] += GetPVarInt(playerid,"Cost"), SetPVarInt(playerid,"Cost",0), GameTextForPlayer(playerid, "~g~+$", 3000, 1),
		        DisablePlayerCheckpoint(playerid), DisablePlayerRaceCheckpoint(playerid), RemovePlayerAttachedObject(playerid,0), RemovePlayerAttachedObject(playerid,1), RemovePlayerAttachedObject(playerid, 2), SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE);
		    }
		}
		case 31: {
		    if(response) {
				switch(listitem) {
				    case 0: {
				        if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 433 && GetVehicleModel(GetPlayerVehicleID(playerid)) != 455 && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SCM(playerid,0xFFFFFFFF,"Вам {1faee9}необходимо находиться в транспорте для перевозок!");
						if(LSW == 0) return SCM(playerid,0xFFFFFFFF,"На данный момент {1faee9}корабль пуст, попробуйте позже!");
                        if(haulspl[GetPlayerVehicleID(playerid)-77] != -1 || haulspu[GetPlayerVehicleID(playerid)-77] != -1) DestroyDynamicPickup(haulspl[GetPlayerVehicleID(playerid)-77]), DestroyDynamic3DTextLabel(haulstext[GetPlayerVehicleID(playerid)-77]),DestroyDynamicPickup(haulspu[GetPlayerVehicleID(playerid)-77]);
						SetPlayerRaceCheckpoint(playerid,1,2800.0447,-2437.6902,13.6307,0.0,0.0,0.0,6.0), SetPVarInt(playerid,"CheckHaul",1);
					}
					case 2: {
					    if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 433 && GetVehicleModel(GetPlayerVehicleID(playerid)) != 455 && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SCM(playerid,0xFFFFFFFF,"Вам {1faee9}необходимо находиться в транспорте для перевозок!");
						if(hauls[GetPlayerVehicleID(playerid)-77][1] == 0) return SCM(playerid,0xFFFFFFFF,"Ваш {1faee9}грузовик пуст!");
                        if(haulspl[GetPlayerVehicleID(playerid)-77] != -1 || haulspu[GetPlayerVehicleID(playerid)-77] != -1) DestroyDynamicPickup(haulspl[GetPlayerVehicleID(playerid)-77]), DestroyDynamic3DTextLabel(haulstext[GetPlayerVehicleID(playerid)-77]), DestroyDynamicPickup(haulspu[GetPlayerVehicleID(playerid)-77]);
						SetPlayerRaceCheckpoint(playerid,1,340.4890,1938.2731,17.6406,0.0,0.0,0.0,6.0), SetPVarInt(playerid,"CheckHaul",2);
					}
					case 4: DisablePlayerRaceCheckpoint(playerid);
				}
		    }
		}
		case 32: {
		    if(response) {
				switch(listitem) {
		            case 0: SetPVarFloat(playerid,"XTP",1187.3389), SetPVarFloat(playerid,"YTP",-1720.4482), SetPVarFloat(playerid,"ZTP",13.5469); // Spawn LS-1
		            case 1: SetPVarFloat(playerid,"XTP",1794.7944), SetPVarFloat(playerid,"YTP",-1899.9310), SetPVarFloat(playerid,"ZTP",13.4002); // Spawn LS-2
		            case 2: SetPVarFloat(playerid,"XTP",2489.7520), SetPVarFloat(playerid,"YTP",-1667.7712), SetPVarFloat(playerid,"ZTP",13.3438); // Grove
		            case 3: SetPVarFloat(playerid,"XTP",2000.5389), SetPVarFloat(playerid,"YTP",-1138.2733), SetPVarFloat(playerid,"ZTP",25.3131); // Ballas
		            case 4: SetPVarFloat(playerid,"XTP",2847.6748), SetPVarFloat(playerid,"YTP",-1176.9084), SetPVarFloat(playerid,"ZTP",24.7627); // Vagos
		            case 5: SetPVarFloat(playerid,"XTP",1883.0094), SetPVarFloat(playerid,"YTP",-2047.6423), SetPVarFloat(playerid,"ZTP",13.3828); // Aztec
		            case 6: SetPVarFloat(playerid,"XTP",1950.6729), SetPVarFloat(playerid,"YTP",-1596.9731), SetPVarFloat(playerid,"ZTP",13.5527); // Rifa
		            case 7: SetPVarFloat(playerid,"XTP",296.6266), SetPVarFloat(playerid,"YTP",1821.0613), SetPVarFloat(playerid,"ZTP",17.6406); // Army LV
		            case 8: SetPVarFloat(playerid,"XTP",2766.3506), SetPVarFloat(playerid,"YTP",-2450.0300), SetPVarFloat(playerid,"ZTP",14.0194); // LS Warehouse
		            case 9: SetPVarFloat(playerid,"XTP",1479.9215), SetPVarFloat(playerid,"YTP",-1723.5947), SetPVarFloat(playerid,"ZTP",13.5469); // Mayor
                    case 10: SetPVarFloat(playerid,"XTP",-50.2315), SetPVarFloat(playerid,"YTP",-280.7552), SetPVarFloat(playerid,"ZTP",5.4297); // Real Trucks Co.
                    case 11: SetPVarFloat(playerid,"XTP",-2025.5635), SetPVarFloat(playerid,"YTP",-77.4899), SetPVarFloat(playerid,"ZTP",35.3203); // Driving School
                    case 12: SetPVarFloat(playerid,"XTP",-2018.6821), SetPVarFloat(playerid,"YTP",140.0746), SetPVarFloat(playerid,"ZTP",28.1282); // Spawn SF-1
                    case 13: SetPVarFloat(playerid,"XTP",2893.4797), SetPVarFloat(playerid,"YTP",1274.9564), SetPVarFloat(playerid,"ZTP",14.9492); // Spawn LV-1
		        }
		        SetPlayerInterior(playerid, 0), SetPlayerVirtualWorld(playerid, 0);
    			if (GetPlayerState(playerid) == 2) SetVehiclePos(GetPlayerVehicleID(playerid), GetPVarFloat(playerid,"XTP"), GetPVarFloat(playerid,"YTP"), GetPVarFloat(playerid,"ZTP"));
    			else AC_SetPlayerPos(playerid, GetPVarFloat(playerid,"XTP"), GetPVarFloat(playerid,"YTP"), GetPVarFloat(playerid,"ZTP"));
				SCM(playerid,0xFFFFFFFF,"Вы были {1faee9}телепортированы в желаемую точку!");
		}   }
		case 33: {
		    if(response) {
				switch(listitem) {
				    case 0: {
				        if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 455 && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SCM(playerid,0xFFFFFFFF,"Вам {1faee9}необходимо находиться в транспорте для перевозок!");
                        if(haulspl[GetPlayerVehicleID(playerid)-77] != 0 || haulspu[GetPlayerVehicleID(playerid)-77] != 0) DestroyDynamicPickup(haulsple), DestroyDynamic3DTextLabel(haulstext[GetPlayerVehicleID(playerid)-77]),DestroyDynamicPickup(haulspue);
						SetPlayerRaceCheckpoint(playerid,1,-1478.1720,2656.4902,56.2726,0.0,0.0,0.0,3.0), SetPVarInt(playerid,"CheckHaul",3);
					}
					case 1: {
					    if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 455  && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SCM(playerid,0xFFFFFFFF,"Вам {1faee9}необходимо находиться в транспорте для перевозок!");
						if(hauls[GetPlayerVehicleID(playerid)-77][1] == 0) return SCM(playerid,0xFFFFFFFF,"Ваш {1faee9}грузовик пуст!");
                        if(haulspl[GetPlayerVehicleID(playerid)-77] != -1 || haulspu[GetPlayerVehicleID(playerid)-77] != -1) DestroyDynamicPickup(haulsple), DestroyDynamic3DTextLabel(haulstext[GetPlayerVehicleID(playerid)-77]), DestroyDynamicPickup(haulspue);
						SetPlayerRaceCheckpoint(playerid,1,255.7696,1972.0992,18.0768,0.0,0.0,0.0,3.0), SetPVarInt(playerid,"CheckHaul",4);
					}
					case 2: DisablePlayerRaceCheckpoint(playerid);
				}
		    }
		}
		case 34: {
		    if(response) {
		        if(Business[GetPVarInt(playerid,"BID")][bProduct] < 1) { SCM(playerid,0xAC7575FF,"В амуниции недостаточно оружия!"), SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2); return true; }
			    TogglePlayerControllable(playerid, 0);
			    TextDrawShowForPlayer(playerid,amBox);
			    TextDrawShowForPlayer(playerid,amPCPS);
			    TextDrawShowForPlayer(playerid,amBox2);
			    TextDrawShowForPlayer(playerid,amChit);
			    TextDrawShowForPlayer(playerid,amLeft);
			    TextDrawShowForPlayer(playerid,amChit2);
			    TextDrawShowForPlayer(playerid,amRight);
			    TextDrawShowForPlayer(playerid,amBBUY);
			    TextDrawShowForPlayer(playerid,amBBACK);
				TextDrawShowForPlayer(playerid,amBUY);
				TextDrawShowForPlayer(playerid,amBack);
			    SetPVarInt(playerid,"AmmoSCT",1), PlayerTextDrawSetString(playerid,amGun[playerid],"MP5"), PlayerTextDrawSetString(playerid,amPrice[playerid],"180$");
				SetPlayerCameraPos(playerid, 287.9030151,-105.7890015,1002.9000244), SetPlayerCameraLookAt(playerid,288.1010132,-105.1370010,1001.5000000,1);
				PlayerTextDrawShow(playerid,amGun[playerid]), PlayerTextDrawShow(playerid,amPrice[playerid]);
				SelectTextDraw(playerid, 0x92C4DCAA), Player[playerid][TDSelect] = true;
				for(new i; i < 20; i++) SCM(playerid,-1,"");
			}
			else SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
		}
		case 35: {
		    if(response) {
		        if(Player[GetPVarInt(playerid,"SearchID")][pDrugs] == 0 && GetPVarInt(GetPVarInt(playerid,"SearchID"),"Ammo") == 0) return SCM(playerid,0xCA7575FF,"У этого человека нечего изымать!");
		        Player[GetPVarInt(playerid,"SearchID")][pDrugs] = 0, SetPVarInt(GetPVarInt(playerid,"SearchID"),"Ammo",0);
                SetPlayerChatBubble(playerid, "изымает запрещенные средства", COLOR_PURPLE, 15.0, 3000);
				SCM(GetPVarInt(playerid,"SearchID"),0xCA7575FF,"У вас изъяли запрещенные средства!");
		    }
		}
		case 36: {
			if(response) {
			    if(Player[playerid][pMoney] < 1000) {
					SCM(playerid,-1,"У вас недостаточно денег {1faee9}для заведения счёта!"), SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
					return true;
				}
 				ShowPlayerDialog(playerid,37,DIALOG_STYLE_MSGBOX,"{1faee9}Оформление договра","{ffffff}Если вы согласны со всеми правилами - выберите пункт 'Да'.\n\n\n{AC7575}Для отмены 'Отмена'","Принять","Отмена");
			}
			else SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
		}
		case 37: {
		    if(response) {
				Player[playerid][pMoney] -= 1000, Player[playerid][pBank] = 1000;
				Player[playerid][pBankPass] = 1;
				ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{03c03c}Счёт активирован!","{ffffff}Поздравляем! Вы {03c03c}успешно завели счет в банке!","Ок","");
                SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
			}
			else SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
		}
		case 38: {
		    if(response) {
		        switch(listitem) {
		            case 0: ShowPlayerDialog(playerid,39,DIALOG_STYLE_INPUT,"{1faee9}Управление счётом","{ffffff}Пожалуйста введите сумму денег которую хотите взять или положить на счёт.\n{ff0000}Внимание, перед суммой поставьте + или - ,плюс для того, чтобы положить, и минус для того чтобы снять.","Далее","Отмена");
					case 1: ShowPlayerDialog(playerid,40,DIALOG_STYLE_INPUT,"{1faee9}Управление счётом","{ffffff}Пожалуйста введите ID игрока, которому {03c03c}хотите перечислить деньги.","Далее","Отмена");
					case 2: format(dstring,92,"{ffffff}Банк:\t\t{03c03c}San Andreas\n{ffffff}На счету:\t{03c03c}%d$",Player[playerid][pBank]), ShowPlayerDialog(playerid,42,DIALOG_STYLE_MSGBOX,"{1faee9}Информация о счёте",dstring,"Ок","");
				}
			}
			else SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
		}
		case 39: {
		    if(response) {
				if(strlen(inputtext) < 2) return ShowPlayerDialog(playerid,39,DIALOG_STYLE_INPUT,"{1faee9}Управление счётом","{ffffff}Пожалуйста введите сумму денег которую хотите взять или положить на счёт.\n{ff0000}Внимание, перед суммой поставьте + или - ,плюс для того, чтобы положить, и минус для того чтобы снять.","Далее","Отмена");
            	for(new i = strlen(inputtext); i != 0; --i) {
           			switch(inputtext[i]) {
					   	case 'A'..'Z', 'a'..'z', ' ': return ShowPlayerDialog(playerid,39,DIALOG_STYLE_INPUT,"{ff2400}Ошибка","{ffffff}Пожалуйста повторите {03c03c}попытку.","Ок","");
				}   }
    			if(strfind(inputtext, "+", true) != -1) {
	    			strdel(inputtext,0,1);
					if(Player[playerid][pMoney] < strval(inputtext)) return SCM(playerid,0xFF0000FF,"У вас {1faee9}недостаточно денег!");
					Player[playerid][pMoney] -= strval(inputtext), Player[playerid][pBank] += strval(inputtext);
					format(dstring,100,"{ffffff}Банк:\t\t{03c03c}San Andreas\n{ffffff}На счету:\t{03c03c}%d$",Player[playerid][pBank]), ShowPlayerDialog(playerid,42,DIALOG_STYLE_MSGBOX,"{1faee9}Изменения в счёте",dstring,"Ок","");
					SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
				 	Success(playerid)
					return true;
				}
			 	if(strfind(inputtext, "-", true) != -1) {
					strdel(inputtext,0,1);
					if(Player[playerid][pBank] < strval(inputtext)) return SCM(playerid,0xFF0000FF,"На вашем счету {1faee9}недостаточно денег!");
					Player[playerid][pMoney] += strval(inputtext), Player[playerid][pBank] -= strval(inputtext);
					format(dstring,100,"{ffffff}Банк:\t\t{03c03c}San Andreas\n{ffffff}На счету:\t{03c03c}%d$",Player[playerid][pBank]), ShowPlayerDialog(playerid,42,DIALOG_STYLE_MSGBOX,"{1faee9}Изменения в счёте",dstring,"Ок","");
					SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
				 	Success(playerid)
					return true;
				}
			}
			else SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
		}
		case 40: {
		    if(response) {
		        if(strlen(inputtext) < 1 && strlen(inputtext) > 4) return ShowPlayerDialog(playerid,40,DIALOG_STYLE_INPUT,"{1faee9}Управление счётом","{ffffff}Пожалуйста введите ID игрока, которому {03c03c}хотите перечислить деньги.","Далее","Отмена");
				if(!Player[strval(inputtext)][PlayerLogged]) return ShowPlayerDialog(playerid,40,DIALOG_STYLE_INPUT,"{1faee9}Управление счётом","{AC7575}Данный игрок оффлайн\n\n{ffffff}Повторить?","Далее","Отмена");
				if(Player[strval(inputtext)][pBankPass] == 0) { SCM(playerid,-1,"Данный человек {AC7575}ещё не завел банковский счет!"), SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2); return true; }
				ShowPlayerDialog(playerid,41,DIALOG_STYLE_INPUT,"{1faee9}Управление счётом","{ffffff}Пожалуйста введите сумму денег которую {03c03c}хотите перечислить на счёт другого игрока.","Далее","Отмена");
				SetPVarInt(playerid,"BankSend",strval(inputtext)),SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
			}
			else SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
		}
		case 41: {
		    if(response) {
		        if(strlen(inputtext) < 1) return ShowPlayerDialog(playerid,41,DIALOG_STYLE_INPUT,"{1faee9}Управление счётом","{ffffff}Пожалуйста введите сумму денег которую {03c03c}хотите перечислить на счёт другого игрока.","Далее","Отмена");
		        for(new i = strlen(inputtext); i != 0; --i) {
           			switch(inputtext[i]) {
					   	case 'A'..'Z', 'a'..'z', ' ': return ShowPlayerDialog(playerid,41,DIALOG_STYLE_INPUT,"{ff2400}Ошибка","{ffffff}Пожалуйста повторите {03c03c}попытку.","Ок","");
				}   }
				if(!Player[GetPVarInt(playerid,"BankSend")][PlayerLogged]) { SCM(playerid,0xAC7575FF,"Игрок оффлайн!"), SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2); return true; }
		        if(Player[playerid][pBank] < strval(inputtext)) return ShowPlayerDialog(playerid,41,DIALOG_STYLE_INPUT,"{1faee9}Управление счётом","{AC7575}Ошибка на вашем счету нет столько денег\n{ffffff}Повторить?","Далее","Отмена");
				Player[playerid][pBank] -= strval(inputtext), Player[GetPVarInt(playerid,"BankSend")][pBank] += strval(inputtext);
				SendClientMessage(GetPVarInt(playerid,"BankSend"),0x7fff00FF,"SMS от BANK-SA: На ваш лицевой зачисленна новая сумма!");
				format(dstring,100,"{ffffff}Банк:\t\t{03c03c}San Andreas\n{ffffff}На счету:\t{03c03c}%d$",Player[playerid][pBank]), ShowPlayerDialog(playerid,42,DIALOG_STYLE_MSGBOX,"{1faee9}Изменения в счёте",dstring,"Ок","");
				SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
			 	Success(playerid)
		    }
		    else SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
		}
		case 42: SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
		case 43: {
		    if(response) {
		        if(strlen(inputtext) < 1 || strlen(inputtext) > 16 || strval(inputtext) == 0) return ShowPlayerDialog(playerid,37,DIALOG_STYLE_INPUT,"Пароль от счёта","{ffffff}Длинна пароля не должна быть меньше 1 цифры и больше 16-ти.\n\n\n{AC7575}Желательно чтобы пароль не совпадал с паролем вашего аккаунта!","Принять","Отмена");
				Player[playerid][pBankPass] = strval(inputtext);
				format(dstring,98,"{ffffff}Пароль {03c03c}успешно изменен!\n\n{ffffff}Не забудьте ваш пароль: {AC7575}%d",Player[playerid][pBankPass]), ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{03c03c}Пароль от счёта изменен",dstring,"Ок","");
                SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
			}
			else SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
		}
		case 44: {
			if(response) {
				switch(listitem) {
		    		case 0: ShowPlayerDialog(playerid,39,DIALOG_STYLE_INPUT,"{1faee9}Управление счётом","{ffffff}Пожалуйста введите сумму денег которую хотите взять или положить на счёт.\n{ff0000}Внимание, перед суммой поставьте + или - ,плюс для того, чтобы положить, и минус для того чтобы снять.","Далее","Отмена");
		    		case 1: ShowPlayerDialog(playerid,45,DIALOG_STYLE_INPUT,"{1faee9}Мобильный баланс","{ffffff}Пожалуйста введите сумму денег которую хотите {03c03c}положить на Ваш мобильный счёт","Далее","Отмена");
		}   }   }
		case 45: {
            if(response) {
				if(strlen(inputtext) == 0) return ShowPlayerDialog(playerid,45,DIALOG_STYLE_INPUT,"{1faee9}Мобильный баланс","{ffffff}Пожалуйста введите сумму денег которую хотите {03c03c}положить на Ваш мобильный счёт","Далее","Отмена");
            	for(new i = strlen(inputtext); i != 0; --i) {
           			switch(inputtext[i]) {
					   	case 'A'..'Z', 'a'..'z', ' ': return ShowPlayerDialog(playerid,45,DIALOG_STYLE_INPUT,"{ff2400}Ошибка","{ffffff}Пожалуйста повторите {03c03c}попытку.","Ок","");
				}   }
				if(Player[playerid][pMoney] < strval(inputtext)) return SCM(playerid,0xFF0000FF,"У вас {1faee9}недостаточно денег!");
				Player[playerid][pMoney] -= strval(inputtext), Player[playerid][pPhone][1] += strval(inputtext);
				format(dstring,100,"{ffffff}Оператор:\t\t{03c03c}SA Mobile\n{ffffff}На счету телефона:\t{03c03c}%d$",Player[playerid][pPhone][1]), ShowPlayerDialog(playerid,42,DIALOG_STYLE_MSGBOX,"{1faee9}Изменения в моб.счёте",dstring,"Ок","");
				return true;
			}
		}
		case 46: {
		    if(response) {
 				format(dstring,78,"Вы назначили {ffffff}%s контролировать его организацию!",Name(GetPVarInt(playerid,"SearchID")));
		       	SCM(playerid,0x1faee9FF,dstring);
				SCM(GetPVarInt(playerid,"SearchID"),0x1faee9FF,"Мэр назначил вас контролировать {ffffff}вашу организацию!");
				Player[GetPVarInt(playerid,"SearchID")][pFraction][0] = Player[GetPVarInt(playerid,"SearchID")][pFraction][1], Player[GetPVarInt(playerid,"SearchID")][pFraction][2] = 10;
				FractionSkin(GetPVarInt(playerid,"SearchID"));
		}   }
		case 47: {
		    if(response) {
		        if(GetPVarInt(playerid,"TruckJob") == 1) {
					SCM(playerid,0x1faee9FF,"Рабочий день окончен!"), format(dstring,12,"~g~+%d",GetPVarInt(playerid,"Cost")), Player[playerid][pMoney] += GetPVarInt(playerid,"Cost"),GameTextForPlayer(playerid,dstring,2000,1), SetPVarInt(playerid,"Cost",0),
					SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2), SetPVarInt(playerid,"Job",0), SetPVarInt(playerid,"TruckJob",0), DisablePlayerRaceCheckpoint(playerid);
					if(Player[playerid][ArendedVehicle] != INVALID_VEHICLE_ID) SetVehicleToRespawn(Player[playerid][ArendedVehicle]), Player[playerid][ArendedVehicle] = INVALID_VEHICLE_ID;
				}
				else {
				    SCM(playerid,0x999589FF,"[F] Диспетчер: Ну что, как слышно? Меня зовут Джесси."), SCM(playerid,0x999589FF,"[F] Диспетчер: Мы выдали тебе рацию настроенную на волну дальнобойщиков (( /f ))");
					SCM(playerid,0x999589FF,"[F] Диспетчер: На протяжении всей твоей работы я буду тебя координировать."), SCM(playerid,0x999589FF,"[F] Диспетчер: Если вдруг тебе потребутеся помощь - у тебя есть справочник (( /help ))");
	                SCM(playerid,0x999589FF,"[F] Диспетчер: Для начала работы тебе следует арендовать грузовик."), SCM(playerid,0x999589FF,"[F] Диспетчер: Далее проследуй на точку отмеченную на твоем GPS приемнике для просмотра грузов!");
	                SCM(playerid,0x999589FF,"[F] Диспетчер: Желаю удачи!"), SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
					SetPlayerRaceCheckpoint(playerid,1,-52.3652,-221.7758,5.4297,0.0,0.0,0.0,8.0), SetPVarInt(playerid,"Job",1), SetPVarInt(playerid,"TruckJob",1);
				}
			}
		    else SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
		}
		case 48: {
		    if(response) {
		        new r,Float:a;
		        fcor
		        GetPlayerPos(playerid, x, y, z);
		    	SetVehiclePos(GetPlayerVehicleID(playerid),x,y,z);
				GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
				x += (10.5 * floatsin(-a+180, degrees));
				y += (10.5 * floatcos(-a+180, degrees));
		        GetVehiclePos(GetPlayerVehicleID(playerid),x,y,z), GetVehicleZAngle(GetPlayerVehicleID(playerid),a);
		        switch(listitem) {
		            case 0: {
		                r = random(sizeof(tH1));
		                ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{1faee9}Перевозки","{ffffff}Вы выбрали в качестве груза {1faee9}'Сырье'.{ffffff} Фура была прицеплена рабочими.\n{1faee9}Куда вести груз - показано на вашем GPS приемнике. Удачи!","Ок","");
						SetPlayerRaceCheckpoint(playerid,1,tH1[r][0],tH1[r][1],tH1[r][2],0.0,0.0,0.0,3.0), SetPVarInt(playerid,"TruckHaul",1);
						Player[playerid][Trailer] = CreateVehicle(591,x,y,z,a,1,1,86400), AttachTrailerToVehicle(Player[playerid][Trailer],GetPlayerVehicleID(playerid));
					}
		            case 1: {
		                r = random(sizeof(tH2));
		                ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{1faee9}Перевозки","{ffffff}Вы выбрали в качестве груза {1faee9}'Нефть'.{ffffff} Фура была прицеплена рабочими.\n{1faee9}Куда вести груз - показано на вашем GPS приемнике. Удачи!","Ок","");
						SetPlayerRaceCheckpoint(playerid,1,tH2[r][0],tH2[r][1],tH2[r][2],0.0,0.0,0.0,3.0), SetPVarInt(playerid,"TruckHaul",2);
						Player[playerid][Trailer] = CreateVehicle(584,x,y,z,a,1,1,86400), AttachTrailerToVehicle(Player[playerid][Trailer],GetPlayerVehicleID(playerid));
					}
		            case 2: {
		                r = random(sizeof(tH3));
		                ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{1faee9}Перевозки","{ffffff}Вы выбрали в качестве груза {1faee9}'Продукты'.{ffffff} Фура была прицеплена рабочими.\n{1faee9}Куда вести груз - показано на вашем GPS приемнике. Удачи!","Ок","");
						SetPlayerRaceCheckpoint(playerid,1,tH3[r][0],tH3[r][1],tH3[r][2],0.0,0.0,0.0,3.0), SetPVarInt(playerid,"TruckHaul",3);
						Player[playerid][Trailer] = CreateVehicle(435,x,y,z,a,1,1,86400), AttachTrailerToVehicle(Player[playerid][Trailer],GetPlayerVehicleID(playerid));
					}
		            case 3: {
		                r = random(sizeof(tH4));
		                ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{1faee9}Перевозки","{ffffff}Вы выбрали в качестве груза {1faee9}'Зерно'.{ffffff} Фура была прицеплена рабочими.\n{1faee9}Куда вести груз - показано на вашем GPS приемнике. Удачи!","Ок","");
						SetPlayerRaceCheckpoint(playerid,1,tH4[r][0],tH4[r][1],tH4[r][2],0.0,0.0,0.0,3.0), SetPVarInt(playerid,"TruckHaul",4);
						Player[playerid][Trailer] = CreateVehicle(450,x,y,z,a,1,1,86400), AttachTrailerToVehicle(Player[playerid][Trailer],GetPlayerVehicleID(playerid));
					}
		        }
		    }
		}
		case 49: {
		    if(response) {
				Player[playerid][pMoney] -= 800, GameTextForPlayer(playerid,"~r~-800$",2000,1);
				ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{FFBF00}Правила Дорожного Движения","","Ок","");
				SCM(playerid,-1,"Экзамен начат! {1faee9}Для начала вам следует взять учебный автомобиль, который стоит на стоянке!");
				SetPVarInt(playerid,"Lesson",1), SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+10);
		    }
			else SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+2);
		}
		case 50: {
		    if(response) {
		        if(GetPVarInt(GetPVarInt(playerid,"AdID"),"Advert") == 0 || !Player[GetPVarInt(playerid,"AdID")][PlayerLogged] || !IsPlayerConnected(GetPVarInt(playerid,"AdID"))) return ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{AC7575}Ошибка","{ffffff}Игрок отключился!","Ок","");
				new fraction[7];
				SCM(playerid,0xFFB65CFF,"[AD] Объявление подано!");
				if(strlen(inputtext) < 2) format(ad,sizeof(ad),"Объявление: %s.Прислал: %s[%d]", Player[GetPVarInt(playerid,"AdID")][Advertise] ,Name(GetPVarInt(playerid,"AdID")),GetPVarInt(playerid,"AdID"));
				else format(ad,sizeof(ad),"Объявление: %s.Прислал: %s(%d)", inputtext ,Name(GetPVarInt(playerid,"AdID")),GetPVarInt(playerid,"AdID"));
			    SendClientMessageToAll(0x00F52DFF,ad);
			    fraction = (Player[playerid][pFraction][1] == 13) ? ("SANews") : ("CNN");
			    format(ad,50,"Редактор %s: %s(%d)",fraction,Name(playerid),playerid);
			    SendClientMessageToAll(0x00F52DFF,ad);
			    SetPVarInt(GetPVarInt(playerid,"AdID"),"Advert",0), SetPVarInt(playerid,"AdID",INVALID_PLAYER_ID);
			}
		}
		case 51: {
		    if(response) {
		        if(Player[playerid][pMoney] < GetPVarInt(playerid,"BuySkin")) return SCM(playerid,0xAC7575FF,"У вас недостаточно денег для данной покупки!");
		        for(new i; i <= Businesses; i++) {
					if(!IsPlayerInRangeOfPoint(playerid,24.0,Business[i][bPX],Business[i][bPY],Business[i][bPZ]) && GetPlayerVirtualWorld(playerid) != Business[i][bVW] && GetPlayerInterior(playerid) != BInts[Business[i][bInt]][biInt]) continue;
					Business[i][bIncome] += GetPVarInt(playerid,"BuySkin");
					Business[i][bProduct]--;
					break;
				}
				if(Player[playerid][pSex] == 1) {
	      			switch(Player[playerid][SSCase]) {
						case 1: SetPlayerSkin(playerid, 22), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 5000;
	     				case 2: SetPlayerSkin(playerid, 3), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 15000;
						case 3: SetPlayerSkin(playerid, 5), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 4000;
						case 4: SetPlayerSkin(playerid, 6), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 12000;
						case 5: SetPlayerSkin(playerid, 7), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 10000;
						case 6: SetPlayerSkin(playerid, 18), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 25000;
						case 7: SetPlayerSkin(playerid, 19), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 30000;
						case 8: SetPlayerSkin(playerid, 20), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 40000;
						case 9: SetPlayerSkin(playerid, 21), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 10000;
						case 10: SetPlayerSkin(playerid, 23), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 20000;
						case 11: SetPlayerSkin(playerid, 28), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 40000;
						case 12: SetPlayerSkin(playerid, 29), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 50000;
						case 13: SetPlayerSkin(playerid, 30), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 50000;
						case 14: SetPlayerSkin(playerid, 37), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 5000;
						case 15: SetPlayerSkin(playerid, 42), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 15000;
						case 16: SetPlayerSkin(playerid, 46), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 150000;
	     				case 17: SetPlayerSkin(playerid, 47), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 60000;
	         			case 18: SetPlayerSkin(playerid, 48), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 60000;
	            		case 19: SetPlayerSkin(playerid, 59), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 65000;
	            		case 20: SetPlayerSkin(playerid, 60), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 15000;
	              		case 21: SetPlayerSkin(playerid, 82), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 90000;
	                	case 22: SetPlayerSkin(playerid, 83), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 90000;
	                	case 23: SetPlayerSkin(playerid, 84), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 90000;
	                	case 24: SetPlayerSkin(playerid, 101), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 30000;
	                	case 25: SetPlayerSkin(playerid, 119), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 45000;
	                	case 26: SetPlayerSkin(playerid, 121), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 20000;
	                	case 27: SetPlayerSkin(playerid, 184), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 15000;
	                	case 28: SetPlayerSkin(playerid, 185), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 110000;
	                	case 29: SetPlayerSkin(playerid, 208), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 135000;
	                	case 30: SetPlayerSkin(playerid, 223), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 165000;
	              		case 31: SetPlayerSkin(playerid, 241), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 70000;
	              		case 32: SetPlayerSkin(playerid, 242), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 70000;
	                	case 33: SetPlayerSkin(playerid, 291), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 190000;
	                	case 34: SetPlayerSkin(playerid, 292), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 230000;
	                	case 35: SetPlayerSkin(playerid, 293), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 210000;
	                	case 36: SetPlayerSkin(playerid, 299), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 310000;
	                	case 37: SetPlayerSkin(playerid, 294), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 350000;
					}
				}
				else {
				    switch(Player[playerid][SSCase]) {
						case 1: SetPlayerSkin(playerid, 9), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 15000;
	      				case 2: SetPlayerSkin(playerid, 11), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 20000;
	 					case 3: SetPlayerSkin(playerid, 12), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 50000;
	      				case 4: SetPlayerSkin(playerid, 40), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 60000;
	      				case 5: SetPlayerSkin(playerid, 56), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 5000;
	      				case 6: SetPlayerSkin(playerid, 93), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 100000;
	      				case 7: SetPlayerSkin(playerid, 91), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 200000;
	      				case 8: SetPlayerSkin(playerid, 141), Player[playerid][pModel][0] = Player[playerid][ChosenSkin], Player[playerid][pMoney] -= 300000;
					}
				}
				SetPlayerVirtualWorld(playerid,Business[GetPVarInt(playerid,"BID")][bVW]), TogglePlayerControllable(playerid,1), CancelSelectTextDraw(playerid), TextDrawHideForPlayer(playerid, brLeft), TextDrawHideForPlayer(playerid, brRight),
				TextDrawHideForPlayer(playerid, brSelect), TextDrawHideForPlayer(playerid, ButtonCancel), TextDrawHideForPlayer(playerid, tCost), TextDrawHideForPlayer(playerid, Player[playerid][tCostItem]);
				SetCameraBehindPlayer(playerid);
				format(dstring,12,"~r~-%d$",GetPVarInt(playerid,"BuySkin"));
				SCM(playerid,0x03c03cFF,"Поздравляем вас с обновкой!"), GameTextForPlayer(playerid,dstring,1000,1), SetPVarInt(playerid,"BuySkin",0);
				SetPlayerSkin(playerid, (Player[playerid][pFraction][1] > 0) ? Player[playerid][pModel][1] : Player[playerid][pModel][0]);
				PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
		}   }
		case 52: {
		    if(response) {
		        SetPVarInt(playerid,"DialogActive",0);
		        if(Business[GetPVarInt(playerid,"BID")][bProduct] < 1) {
					ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{1faee9}Информация","{ffffff}На складе данного бизнеса {AC7575}недостаточно товаров!","Ок",""),
					SetPVarInt(playerid,"GetPickup",gettime()+3);
					return true;
				}
		        switch(listitem) {
		            case 0: {
						if(Player[playerid][pPhone][0] != 0) return SCM(playerid,0xFFFFFFFF,"У вас {1faee9}уже есть мобильный телефон!");
						if(Player[playerid][pMoney] < Business[GetPVarInt(playerid,"BID")][bCost]) return SCM(playerid,0xAC7575FF,"У вас нехватает денег для совершения данной покупки!");
						Player[playerid][pMoney] -= Business[GetPVarInt(playerid,"BID")][bCost];
						Player[playerid][pPhone][0] = 9001+random(90000), Player[playerid][pPhone][1] = Business[GetPVarInt(playerid,"BID")][bCost];
						Business[GetPVarInt(playerid,"BID")][bIncome] += Business[GetPVarInt(playerid,"BID")][bCost];
						Business[GetPVarInt(playerid,"BID")][bProduct]--;
						format(dstring,32,"Ваш новый номер: {ffffff}%d",Player[playerid][pPhone][0]), SCM(playerid,0x1faee9FF,dstring);
		            }
		            case 1: {
						if(Player[playerid][pPhone][0] == 0) return SCM(playerid,0xAC7575FF,"У вас нет мобильного телефона!");
						if(Player[playerid][pMoney] < pernumber(Business[GetPVarInt(playerid,"BID")][bCost],12)) return SCM(playerid,0xAC7575FF,"У вас нехватает денег для совершения данной покупки!");
                        Player[playerid][pMoney] -= pernumber(Business[GetPVarInt(playerid,"BID")][bCost],10);
						Player[playerid][pPhone][0] = 9001+random(90000);
						Business[GetPVarInt(playerid,"BID")][bIncome] += pernumber(Business[GetPVarInt(playerid,"BID")][bCost],12);
						Business[GetPVarInt(playerid,"BID")][bProduct]--;
						format(dstring,32,"Ваш новый номер: {ffffff}%d",Player[playerid][pPhone][0]), SCM(playerid,0x1faee9FF,dstring);
					}
					case 2: {
                        if((Player[playerid][CGR] & (1<<0)) != 0) return SCM(playerid,0xAC7575FF,"У вас уже есть наручные часы!");
						if(Player[playerid][pMoney] < pernumber(Business[GetPVarInt(playerid,"BID")][bCost],20)) return SCM(playerid,0xAC7575FF,"У вас нехватает денег для совершения данной покупки!");
						Player[playerid][CGR] ^= (1<<0), SCM(playerid,0xFFFFFFFF,"Наручные часы {1faee9}приобретены!");
						Player[playerid][pMoney] -= pernumber(Business[GetPVarInt(playerid,"BID")][bCost],20);
                        Business[GetPVarInt(playerid,"BID")][bProduct]--;
						Business[GetPVarInt(playerid,"BID")][bIncome] += pernumber(Business[GetPVarInt(playerid,"BID")][bCost],20);
					}
					case 3: {
					    if((Player[playerid][CGR] & (1<<1)) != 0) return SCM(playerid,0xAC7575FF,"У вас уже есть GPS-навигатор!");
						if(Player[playerid][pMoney] < pernumber(Business[GetPVarInt(playerid,"BID")][bCost],35)) return SCM(playerid,0xAC7575FF,"У вас нехватает денег для совершения данной покупки!");
						Player[playerid][CGR] ^= (1<<1), SCM(playerid,0xFFFFFFFF,"GPS-навигатор {1faee9}приобретен!");
						Player[playerid][pMoney] -= pernumber(Business[GetPVarInt(playerid,"BID")][bCost],35);
						Business[GetPVarInt(playerid,"BID")][bIncome] += pernumber(Business[GetPVarInt(playerid,"BID")][bCost],35);
						Business[GetPVarInt(playerid,"BID")][bProduct]--;
					}
					case 4: {
                        if(Player[playerid][pMoney] < pernumber(Business[GetPVarInt(playerid,"BID")][bCost],56)) return SCM(playerid,0xAC7575FF,"У вас нехватает денег для совершения данной покупки!");
                        GiveWeapon(playerid,5,1), SCM(playerid,0xFFFFFFFF,"Бейсбольная бита {1faee9}приобретена!");
                        Player[playerid][pMoney] -= pernumber(Business[GetPVarInt(playerid,"BID")][bCost],56);
                        Business[GetPVarInt(playerid,"BID")][bIncome] += pernumber(Business[GetPVarInt(playerid,"BID")][bCost],56);
                        Business[GetPVarInt(playerid,"BID")][bProduct]--;
					}
					case 5: {
                        if(Player[playerid][pMoney] < pernumber(Business[GetPVarInt(playerid,"BID")][bCost],72)) return SCM(playerid,0xAC7575FF,"У вас нехватает денег для совершения данной покупки!");
                        Player[playerid][pMoney] -= pernumber(Business[GetPVarInt(playerid,"BID")][bCost],72);
                        GiveWeapon(playerid,43,10), SCM(playerid,0xFFFFFFFF,"Фотоаппарат {1faee9}приобретен!");
                        Business[GetPVarInt(playerid,"BID")][bProduct]--;
					}
					case 6: {
					    if((Player[playerid][CGR] & (1<<2)) != 0) return SCM(playerid,0xAC7575FF,"У вас уже есть набор для ремонта!");
                        if(Player[playerid][pMoney] < pernumber(Business[GetPVarInt(playerid,"BID")][bCost],100)) return SCM(playerid,0xAC7575FF,"У вас нехватает денег для совершения данной покупки!");
                        Player[playerid][CGR] ^= (1<<2), SCM(playerid,0xFFFFFFFF,"Набор для ремонта {1faee9}приобретен!");
                        Player[playerid][pMoney] -= pernumber(Business[GetPVarInt(playerid,"BID")][bCost],100);
                        Business[GetPVarInt(playerid,"BID")][bIncome] += pernumber(Business[GetPVarInt(playerid,"BID")][bCost],100);
                        Business[GetPVarInt(playerid,"BID")][bProduct]--;
					}
		        }
		    }
		    SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+3);
      	}
       	case 53: {
			if(response) {
				switch(listitem) {
				    case 0: SetPVarInt(playerid,"Number",1), ShowPlayerDialog(playerid,54,DIALOG_STYLE_LIST,"{FFC800}Очки","{ffffff}Черные очки {03c03c}[80$]\n{ffffff}Красные очки {03c03c}[80$]\n{ffffff}Синие очки {03c03c}[80$]\n{ffffff}X-RAY очки {AC7575}[200$]","Купить","Отмена");
					case 1: SetPVarInt(playerid,"Number",2), ShowPlayerDialog(playerid,54,DIALOG_STYLE_LIST,"{FFC800}Шляпы","{ffffff}Ковбой-1 {03c03c}[110$]\n{ffffff}Ковбой-2 {03c03c}[110$]\n{ffffff}Панама {03c03c}[90$]\n{ffffff}Чаплин {AC7575}[300$]\n{ffffff}Чаплин-Синяя {AC7575}[300$]\n{ffffff}Чаплин-Красная {AC7575}[300$]","Купить","Отмена");
				}
			}
        	ShowPlayerDialog(playerid,53,DIALOG_STYLE_LIST,"{FFC800}Ассортимент магазина","{ffffff}Очки\nШляпки\nБереты\nБанданы\nМаски","Выбор","Отмена");
        	SetPVarInt(playerid,"DialogActive",0), SetPVarInt(playerid,"GetPickup",gettime()+3);
		}
		case 54: {
		    if(response) {
				// В разработке!
		    }
		}
		case 55: {
			if(response) {
				switch(listitem) {
					case 0: {
						Player[GetPVarInt(playerid,"SearchID")][Licenses] ^= (1<<0);
						SCM(playerid,0x1faee9FF, ((Player[GetPVarInt(playerid,"SearchID")][Licenses] & (1<<0)) != 0) ? ("Водительское удостоверение {ffffff}выдано!") : ("Водительское удостоверение {ffffff}аннулировано!")), SCM(GetPVarInt(playerid,"SearchID"),0x1faee9FF, ((Player[GetPVarInt(playerid,"SearchID")][Licenses] & (1<<0)) != 0) ? ("Вам выдано {ffffff}водительское удостоверение!") : ("Ваше водительское удостоверение было {ffffff}аннулировано!"));
					}
					case 1: {
						Player[GetPVarInt(playerid,"SearchID")][Licenses] ^= (1<<1);
						SCM(playerid,0x1faee9FF, ((Player[GetPVarInt(playerid,"SearchID")][Licenses] & (1<<1)) != 0) ? ("Лицензия на управление воздушным ТС {ffffff}выдана!") : ("Лицензия на управление воздушным ТС {ffffff}аннулирована!")), SCM(GetPVarInt(playerid,"SearchID"),0x1faee9FF, ((Player[GetPVarInt(playerid,"SearchID")][Licenses] & (1<<1)) != 0) ? ("Вам выдана {ffffff}лицензия на управление воздушным ТC!") : ("Ваша лицензия на управление воздушным ТС была {ffffff}аннулирована!"));
					}
				}
			}
		}
		case 56: {
			if(response) {
		    	Player[GetPVarInt(playerid,"SearchID")][Licenses] ^= (1<<2);
				SCM(playerid,0x1faee9FF, ((Player[GetPVarInt(playerid,"SearchID")][Licenses] & (1<<2)) != 0) ? ("Лицензия на хранение оружия {ffffff}выдана!") : ("Лицензия на хранение оружия {ffffff}аннулирована!")), SCM(GetPVarInt(playerid,"SearchID"),0x1faee9FF, ((Player[GetPVarInt(playerid,"SearchID")][Licenses] & (1<<2)) != 0) ? ("Вам выдана {ffffff}лицензия на хранение оружия!") : ("Ваша лицензия на хранение оружия была {ffffff}аннулирована!"));
			}
		}
		case 57: {
		    if(response) {
		        if(Player[playerid][pFraction][2] < 4) return SCM(playerid,0xFF0000FF,"Функция доступна с 4 ранга!");
		        if(strlen(inputtext) == 0) return ShowPlayerDialog(playerid,57,DIALOG_STYLE_INPUT,"Склал банды","{ffffff}Пожалуйста введите кол-во наркотиков которое хотите взять или положить на склад банды.\n{ff0000}Внимание, перед суммой поставьте + или - ,плюс для того, чтобы положить, и минус для того чтобы взять.\n{ffffff}Пример: {ff0000}+10","Далее","Отмена");
            	for(new i = strlen(inputtext); i != 0; --i) {
           			switch(inputtext[i]) {
					   	case 'A'..'Z', 'a'..'z', ' ': return ShowPlayerDialog(playerid,57,DIALOG_STYLE_INPUT,"{ff2400}Ошибка","{ffffff}Пожалуйста повторите {03c03c}попытку.","Ок","");
					}
				}
				for(new w;w<sizeof(Ware);w++) {
					if(IsPlayerInRangeOfPoint(playerid, 3.0, Ware[w][wX], Ware[w][wY], Ware[w][wZ]) && Player[playerid][pFraction][1] == Ware[w][wFraction]) {
					    if(strfind(inputtext, "+", true) != -1) {
		    				strdel(inputtext,0,1);
							if(Player[playerid][pDrugs] < strval(inputtext)) return SCM(playerid,0xFF0000FF,"У вас недостаточно наркотиков!");
							Ware[w][wDrugs] += strval(inputtext), Player[playerid][pDrugs] -= strval(inputtext), Success(playerid)
							format(warehousetext,sizeof(warehousetext),"Склад %s\nАммуниции: %d\nНаркотиков: %d\nДенег: %d",Ware[w][wName], Ware[w][wAmmo], Ware[w][wDrugs], Ware[w][wMoney]);
	 						UpdateDynamic3DTextLabelText(warehouset[w], 0xFF9900FF, warehousetext);
	 						return false;
						}
	    				else if(strfind(inputtext, "-", true) != -1) {
							strdel(inputtext,0,1);
							if(Ware[w][wDrugs] < strval(inputtext)) return SCM(playerid,0xFF0000FF,"На складе недостаточно наркотиков!");
							Player[playerid][pDrugs] += strval(inputtext), Ware[w][wAmmo] -= strval(inputtext), Success(playerid)
							format(warehousetext,sizeof(warehousetext),"Склад %s\nАммуниции: %d\nНаркотиков: %d\nДенег: %d",Ware[w][wName], Ware[w][wAmmo], Ware[w][wDrugs], Ware[w][wMoney]);
	 						UpdateDynamic3DTextLabelText(warehouset[w], 0xFF9900FF, warehousetext);
	 						return false;
	 					}
					}
				}
			}
		}
		case 58: {
			if(response) {
			    switch(listitem) {
				    case 0: {
						format(dstring,68,"{ffffff}Прибыль: {03c03c}%i$\n{ffffff}Убытки: {AC7575}%i$",Business[Player[playerid][pBusiness]][bIncome], Business[Player[playerid][pBusiness]][bCommunal]);
						ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{ffffff}Статистика {1faee9}Бизнеса",dstring,"Ок","");
				    }
				    case 1: {
	                    format(dstring,72,"{ffffff}Товара: {03c03c}%i шт.\n{ffffff}Цена за товар: {AC7575}%i$",Business[Player[playerid][pBusiness]][bProduct], Business[Player[playerid][pBusiness]][bCost]);
						ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{ffffff}Статистика {1faee9}Бизнеса",dstring,"Ок","");
				    }
				    case 2: {
				        if(!IsPlayerInRangeOfPoint(playerid,10.0,Business[Player[playerid][pBusiness]][bX],Business[Player[playerid][pBusiness]][bY],Business[Player[playerid][pBusiness]][bZ])) return SCM(playerid,0xFFFFFFFF,"Необходимо {1faee9}находиться возле бизнеса!");
						SetPVarInt(playerid,"Number",1), ShowPlayerDialog(playerid,59,DIALOG_STYLE_INPUT,"{FFC800}Цена за товар","{ffffff}Пожалуйста {1faee9}укажите цену за продаваемый товар ( минимальную )","Далее","Отмена");
				    }
				    case 3: {
				        if(!IsPlayerInRangeOfPoint(playerid,10.0,Business[Player[playerid][pBusiness]][bX],Business[Player[playerid][pBusiness]][bY],Business[Player[playerid][pBusiness]][bZ])) return SCM(playerid,0xFFFFFFFF,"Необходимо {1faee9}находиться возле бизнеса!");
                        SetPVarInt(playerid,"Number",2), ShowPlayerDialog(playerid,59,DIALOG_STYLE_INPUT,"{FFC800}Забрать доход","{ffffff}Пожалуйста {1faee9}укажите сумму которую вы хотите снять","Далее","Отмена");
					}
				    case 4: callcmd::sellbiz(playerid, "");
				}
			}
		}
		case 59: {
		    if(response) {
		        for(new i = strlen(inputtext); i != 0; --i) {
           			switch(inputtext[i]) {
					   	case 'A'..'Z', 'a'..'z', ' ': return ShowPlayerDialog(playerid,59,DIALOG_STYLE_INPUT,"{ff2400}Ошибка","{ffffff}Пожалуйста повторите {03c03c}попытку.","Ок","");
					}
				}
		        if(GetPVarInt(playerid,"Number") == 1) {
		            if(strlen(inputtext) == 0) return ShowPlayerDialog(playerid,59,DIALOG_STYLE_INPUT,"{FFC800}Цена за товар","{ffffff}Пожалуйста {1faee9}укажите цену за продаваемый товар ( минимальную )","Далее","Отмена");
		            if(1 < strval(inputtext) > 1000) return ShowPlayerDialog(playerid,59,DIALOG_STYLE_INPUT,"{FFC800}Цена за товар","{ffffff}Цена за товар {1faee9}не должна быть меньше 1$ и не больше 1000$","Далее","Отмена");
					Business[Player[playerid][pBusiness]][bCost] = strval(inputtext), SCM(playerid,0x03c03cFF,"Цена за товар установлена!");
				}
				if(GetPVarInt(playerid,"Number") == 2) {
                    if(strlen(inputtext) == 0) return ShowPlayerDialog(playerid,59,DIALOG_STYLE_INPUT,"{FFC800}Забрать доход","{ffffff}Пожалуйста {1faee9}укажите сумму которую вы хотите снять","Далее","Отмена");
                    if(1 < strval(inputtext) > 100000) return ShowPlayerDialog(playerid,59,DIALOG_STYLE_INPUT,"{FFC800}Забрать доход","{ffffff}Сумма {1faee9}не должна быть меньше 1$ и не больше 100000$","Далее","Отмена");
					if(Business[Player[playerid][pBusiness]][bIncome] < strval(inputtext)) return ShowPlayerDialog(playerid,59,DIALOG_STYLE_INPUT,"{FFC800}Забрать доход","{ffffff}Ваш бизнес {1faee9}не имеет такого дохода!","Далее","Отмена");
                    Business[Player[playerid][pBusiness]][bIncome] -= strval(inputtext), Player[playerid][pMoney] += strval(inputtext), SCM(playerid,0x03c03cFF,"Часть с суммы заработка бизнеса снята!");
				}
		    }
		}
		case 60: {
		    if(response) {
		        new debt[84];
				SCM(playerid,0xD58000FF,"Задолжности:");
		        switch(listitem) {
		            case 0: {
		                for(new i; i <= Houses; i++) {
 							if(strcmp(House[i][hOwner],"None",true,25) == 0 || House[i][hCommunal] > -1) continue;
 							format(debt,sizeof(debt),"%Дом №%d[%s]: %d$",House[i][hID],House[i][hOwner],House[i][hCommunal]), SCM(playerid,0xDCA900FF,debt);
					}   }
		            case 1: {
		                for(new i; i <= Businesses; i++)  {
	    					if(strcmp(Business[i][bOwner],"None",true,25) == 0 || Business[i][bCommunal] > -1) continue;
							format(debt,sizeof(debt),"Бизнес %s[%s]: %d$",Business[i][bName],Business[i][bOwner],Business[i][bCommunal]), SCM(playerid,0xDCA900FF,debt);
	    }   }   }   }   }
	    case 61: {
			if(response) {
   				if(Player[playerid][pMoney] < VehicleCost[GetPVarInt(playerid,"BuyCase")]) return SCM(playerid,0xAC7575FF,"У вас недостаточно денег для покупки этого авто!");
 				switch(GetPVarInt(playerid,"BuyCase")) {
					case 1: Player[playerid][pCar][0] = GetPVarInt(playerid,"BuyCar"), Player[playerid][pMoney] -= VehicleCost[GetPVarInt(playerid,"BuyCase")], Player[playerid][pCar][1] = -1;
 					case 2: Player[playerid][pCar][0] = GetPVarInt(playerid,"BuyCar"), Player[playerid][pMoney] -= VehicleCost[GetPVarInt(playerid,"BuyCase")], Player[playerid][pCar][1] = -1;
					case 3: Player[playerid][pCar][0] = GetPVarInt(playerid,"BuyCar"), Player[playerid][pMoney] -= VehicleCost[GetPVarInt(playerid,"BuyCase")], Player[playerid][pCar][1] = -1;
				}
				TogglePlayerControllable(playerid,1), CancelSelectTextDraw(playerid), TextDrawHideForPlayer(playerid, asLeft), TextDrawHideForPlayer(playerid, asRight),
				TextDrawHideForPlayer(playerid, asCost), TextDrawHideForPlayer(playerid, asBox), TextDrawHideForPlayer(playerid, Player[playerid][asCostV]), TextDrawHideForPlayer(playerid, Player[playerid][asVname]), TextDrawHideForPlayer(playerid, asBuy);
				TextDrawHideForPlayer(playerid, asExit), TextDrawHideForPlayer(playerid, asBBuy), TextDrawHideForPlayer(playerid, asBExit);
				format(dstring,22,"~r~-%d$",VehicleCost[GetPVarInt(playerid,"BuyCase")]);
    			DestroyVehicle(Player[playerid][pCar][3]);
				SCM(playerid,0x03c03cFF,"Поздравляем вас с покупкой нового автомобиля, {ffffff}он стоит на паркове Автосалона!"), GameTextForPlayer(playerid,dstring,1000,1);
				PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
				DestroyVehicle(Player[playerid][PlayerCar]), Player[playerid][PlayerCar] = CreateVehicle(Player[playerid][pCar][0],565.0430,-1277.2322,17.2422,15.2486,Player[playerid][pCar][1],Player[playerid][pCar][2],84600);
                SetVehicleVirtualWorld(Player[playerid][PlayerCar],0);
				SetPVarInt(playerid,"BuyCase",0), SetPVarInt(playerid,"BuyCar",0), DestroyVehicle(Player[playerid][pCar][3]);
				AC_SetPlayerPos(playerid,546.3284,-1288.5500,17.2482), SetPlayerFacingAngle(playerid,0.6265), SetCameraBehindPlayer(playerid), SetPlayerVirtualWorld(playerid,0);
		}   }
		case 62: {
		    if(response) {
		        fcor
		        GetPlayerPos(playerid,x,y,z);
		        switch(listitem) {
		            case 0: {
						if(House[Player[playerid][pHouse]][hUpgrade] > 0) return SCM(playerid,0xAC7575FF,"У вас уже установлено данное улучшение!");
						if(Player[playerid][pBank] < 25000) return SCM(playerid,0xAC7575FF,"У вас недостаточно денег в банке для покупки этого апгрейда!");
						House[Player[playerid][pHouse]][hObject][0] = CreateDynamicObject(2332,x,y,z,0.0,0.0,0.0,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid));
						EditDynamicObject(playerid,House[Player[playerid][pHouse]][hObject][0]);
						SCM(playerid,0xFF0000FF,"Внимание! Для редактирования позиции объекта используйте все 6 осей.");
						SCM(playerid,0xFF0000FF,"Оси сменяются серой кнопкой ( повернутой стрелкой )");
						SCM(playerid,0xFF0000FF,"Для ходьбы или поворота камеры {ffffff}Зажмите SPRINT ( LSHIFT или Пробел! )");
		            }
					case 1: {
					    if(House[Player[playerid][pHouse]][hUpgrade] == 0) return SCM(playerid,0xAC7575FF,"Для установки этого апгрейда необходимо иметь 'Сейф'");
					    if(House[Player[playerid][pHouse]][hUpgrade] > 1) return SCM(playerid,0xAC7575FF,"У вас уже установлено данное улучшение!");
						if(Player[playerid][pBank] < 20000) return SCM(playerid,0xAC7575FF,"У вас недостаточно денег в банке для покупки этого апгрейда!");
						House[Player[playerid][pHouse]][hObject][1] = CreateDynamicObject(2025,x,y,z,0.0,0.0,0.0,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid));
						EditDynamicObject(playerid,House[Player[playerid][pHouse]][hObject][1]);
						SCM(playerid,0xFF0000FF,"Внимание! Для редактирования позиции объекта используйте все 6 осей.");
						SCM(playerid,0xFF0000FF,"Оси сменяются серой кнопкой ( повернутой стрелкой )");
						SCM(playerid,0xFF0000FF,"Для ходьбы или поворота камеры {ffffff}Зажмите SPRINT ( LSHIFT или Пробел! )");
					}
					case 2: {
					    if(House[Player[playerid][pHouse]][hUpgrade] == 0) return SCM(playerid,0xAC7575FF,"Для установки этого апгрейда необходимо иметь 'Шкаф'");
					    if(House[Player[playerid][pHouse]][hUpgrade] > 2) return SCM(playerid,0xAC7575FF,"У вас уже установлено данное улучшение!");
						if(Player[playerid][pBank] < 20000) return SCM(playerid,0xAC7575FF,"У вас недостаточно денег в банке для покупки этого апгрейда!");
						Player[playerid][pMoney] -= 20000, House[Player[playerid][pHouse]][hUpgrade] = 3;
						SCM(playerid,0x03c03cFF,"Гараж {ffffff}приобретен!");
		}   }   }   }
		case 63: {
			switch(listitem) {
			    case 0: SetPVarInt(playerid,"Number",0), ShowPlayerDialog(playerid,64,DIALOG_STYLE_INPUT,"Деньги в сейфе","{ffffff}Пожалуйста введите сумму денег которую хотите взять или положить в сейф.\n{ff0000}Внимание, перед суммой поставьте + или - ,плюс для того, чтобы положить, и минус для того чтобы снять.\n\
					{ffffff}Пример: {ff0000}+500","Далее","Отмена");
				case 1: SetPVarInt(playerid,"Number",1), ShowPlayerDialog(playerid,64,DIALOG_STYLE_INPUT,"Патроны в сейфе","{ffffff}Пожалуйста введите кол-во патрон которые хотите взять или положить в сейф.\n{ff0000}Внимание, перед суммой поставьте + или - ,плюс для того, чтобы положить, и минус для того чтобы снять.\n\
					{ffffff}Пример: {ff0000}+25","Далее","Отмена");
                case 2: SetPVarInt(playerid,"Number",2), ShowPlayerDialog(playerid,64,DIALOG_STYLE_INPUT,"Наркотики в сейфе","{ffffff}Пожалуйста введите кол-во грамм которые хотите взять или положить в сейф.\n{ff0000}Внимание, перед суммой поставьте + или - ,плюс для того, чтобы положить, и минус для того чтобы снять.\n\
					{ffffff}Пример: {ff0000}+10","Далее","Отмена");
		}   }
		case 64: {
			if(response) {
				#define	h   Player[playerid][pHouse]
				switch(GetPVarInt(playerid,"Number")) {
				    case 0: {
			    		if(strfind(inputtext, "+", true) != -1) {
   							strdel(inputtext,0,1);
							if(Player[playerid][pMoney] < strval(inputtext)) return SCM(playerid,0xFF0000FF,"У вас недостаточно денег!");
							House[h][sMoney] += strval(inputtext), Player[playerid][pMoney] -= strval(inputtext), Success(playerid)
							format(warehousetext,sizeof(warehousetext),"Сейф\nДенег: %d\nПатроны: %d\nНаркотики: %d",House[h][sMoney],House[h][sAmmo],House[h][sDrugs]);
	 						UpdateDynamic3DTextLabelText(House[h][sText], 0x1faee9FF, warehousetext);
	 						return false;
						}
	    				else if(strfind(inputtext, "-", true) != -1) {
							strdel(inputtext,0,1);
							if(House[h][sMoney] < strval(inputtext)) return SCM(playerid,0xFF0000FF,"В банке недостаточно денег!");
							Player[playerid][pMoney] += strval(inputtext), House[h][sMoney] -= strval(inputtext), Success(playerid)
							format(warehousetext,sizeof(warehousetext),"Сейф\nДенег: %d\nПатроны: %d\nНаркотики: %d",House[h][sMoney],House[h][sAmmo],House[h][sDrugs]);
	 						UpdateDynamic3DTextLabelText(House[h][sText], 0x1faee9FF, warehousetext);
	 						return false;
	 					}
					}
					case 1: {
			    		if(strfind(inputtext, "+", true) != -1) {
   							strdel(inputtext,0,1);
							if(Player[playerid][pAmmo] < strval(inputtext)) return SCM(playerid,0xFF0000FF,"У вас недостаточно денег!");
							House[h][sAmmo] += strval(inputtext), Player[playerid][pAmmo] -= strval(inputtext), Success(playerid)
							format(warehousetext,sizeof(warehousetext),"Сейф\nДенег: %d\nПатроны: %d\nНаркотики: %d",House[h][sMoney],House[h][sAmmo],House[h][sDrugs]);
	 						UpdateDynamic3DTextLabelText(House[h][sText], 0x1faee9FF, warehousetext);
	 						return false;
						}
	    				else if(strfind(inputtext, "-", true) != -1) {
							strdel(inputtext,0,1);
							if(House[h][sAmmo] < strval(inputtext)) return SCM(playerid,0xFF0000FF,"В банке недостаточно денег!");
							Player[playerid][pAmmo] += strval(inputtext), House[h][sAmmo] -= strval(inputtext), Success(playerid)
							format(warehousetext,sizeof(warehousetext),"Сейф\nДенег: %d\nПатроны: %d\nНаркотики: %d",House[h][sMoney],House[h][sAmmo],House[h][sDrugs]);
	 						UpdateDynamic3DTextLabelText(House[h][sText], 0x1faee9FF, warehousetext);
	 						return false;
	 					}
					}
					case 2: {
			    		if(strfind(inputtext, "+", true) != -1) {
   							strdel(inputtext,0,1);
							if(Player[playerid][pDrugs] < strval(inputtext)) return SCM(playerid,0xFF0000FF,"У вас недостаточно денег!");
							House[h][sDrugs] += strval(inputtext), Player[playerid][pDrugs] -= strval(inputtext), Success(playerid)
							format(warehousetext,sizeof(warehousetext),"Сейф\nДенег: %d\nПатроны: %d\nНаркотики: %d",House[h][sMoney],House[h][sAmmo],House[h][sDrugs]);
	 						UpdateDynamic3DTextLabelText(House[h][sText], 0x1faee9FF, warehousetext);
	 						return false;
						}
						else if(strfind(inputtext, "-", true) != -1) {
							strdel(inputtext,0,1);
							if(House[h][sDrugs] < strval(inputtext)) return SCM(playerid,0xFF0000FF,"В банке недостаточно денег!");
							Player[playerid][pDrugs] += strval(inputtext), House[h][sDrugs] -= strval(inputtext), Success(playerid)
							format(warehousetext,sizeof(warehousetext),"Сейф\nДенег: %d\nПатроны: %d\nНаркотики: %d",House[h][sMoney],House[h][sAmmo],House[h][sDrugs]);
	 						UpdateDynamic3DTextLabelText(House[h][sText], 0x1faee9FF, warehousetext);
	 						return false;
	 					}
					}
				}
				#undef  h
			}
		}
		case 65: {
		    if(response) {
		        if(!strlen(inputtext)) return ShowPlayerDialog(playerid,65,DIALOG_STYLE_INPUT,"{AC7575}Настройки гонки","{ffffff}Введите {03c03c}сумму ставки!","Далее","Отмена");
		        if(strval(inputtext) < 250 || strval(inputtext) > 100000) return ShowPlayerDialog(playerid,65,DIALOG_STYLE_INPUT,"{AC7575}Настройки гонки","{ffffff}Введите {03c03c}сумму ставки!\n\n\n{ffffff}Сумма {AC7575}не должна быть меньше 250$ и больше 100000$","Далее","Отмена");
				if(Player[playerid][pMoney] < strval(inputtext)) return ShowPlayerDialog(playerid,65,DIALOG_STYLE_INPUT,"{AC7575}Настройки гонки","{ff0000}У вас нет такой суммы денег!\n\n{ffffff}Введите {03c03c}сумму ставки!","Далее","Отмена");
				Rate = strval(inputtext);
				format(dstring,86,"{ffffff}Маршрут: \t{03c03c}%s\n{ffffff}Ставка:\t{03c03c}%d$",track,Rate);
				ShowPlayerDialog(playerid,66,DIALOG_STYLE_MSGBOX,"{03c03c}Настойки гонки",dstring,"Начать","Отмена");
		    }
		    else Track = 0, SetPVarInt(playerid,"Race",-1);
		}
		case 66: {
			if(response) {
			    Track = GetPVarInt(playerid,"SelectRace");
			    SetPVarInt(playerid,"Race",0), SetPlayerRaceCheckpoint(playerid,1,-2654.9399,1156.1821,34.6481,-2724.4636,1086.3967,45.8983,10.0);
			    TextDrawHideForPlayer(playerid,raBox),TextDrawHideForPlayer(playerid,raImg),TextDrawHideForPlayer(playerid,raTrack),TextDrawHideForPlayer(playerid,raDist),TextDrawHideForPlayer(playerid,raBox2),
				TextDrawHideForPlayer(playerid,raLeft),TextDrawHideForPlayer(playerid,raRight),TextDrawHideForPlayer(playerid,raSRace),TextDrawHideForPlayer(playerid,raButS),TextDrawHideForPlayer(playerid,raButC),
				TextDrawHideForPlayer(playerid,raStart),TextDrawHideForPlayer(playerid,raCancel);
				SetPVarInt(playerid,"SelectRace",0), CancelSelectTextDraw(playerid);
			}
			else Track = 0, SetPVarInt(playerid,"Race",-1);
		}
	}
	return true;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return true;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid) {
	return true;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(Player[playerid][ClothesRound] == true) {
        if(clickedid == brRight) {
	 		if(Player[playerid][pSex] == 1) {
				switch(Player[playerid][SSCase]) {
					case 1: SetPlayerSkin(playerid, 1), Player[playerid][SSCase] = 2, Player[playerid][ChosenSkin] = 1;
			        case 2: SetPlayerSkin(playerid, 2), Player[playerid][SSCase] = 3, Player[playerid][ChosenSkin] = 2;
					case 3: SetPlayerSkin(playerid, 15), Player[playerid][SSCase] = 4, Player[playerid][ChosenSkin] = 15;
					case 4: SetPlayerSkin(playerid, 26), Player[playerid][SSCase] = 5, Player[playerid][ChosenSkin] = 26;
					case 5: SetPlayerSkin(playerid, 43), Player[playerid][SSCase] = 6, Player[playerid][ChosenSkin] = 43;
					case 6: SetPlayerSkin(playerid, 44), Player[playerid][SSCase] = 7,Player[playerid][ChosenSkin] = 44;
					case 7: SetPlayerSkin(playerid, 67), Player[playerid][SSCase] = 8, Player[playerid][ChosenSkin] = 67;
					case 8: SetPlayerSkin(playerid, 72), Player[playerid][SSCase] = 9, Player[playerid][ChosenSkin] = 72;
					case 9: SetPlayerSkin(playerid, 188), Player[playerid][SSCase] = 1, Player[playerid][ChosenSkin] = 188;
				}
				PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0); }
  			else {
	    		switch(Player[playerid][SSCase]) {
			        case 1: SetPlayerSkin(playerid, 13), Player[playerid][SSCase] = 2, Player[playerid][ChosenSkin] = 13;
			        case 2: SetPlayerSkin(playerid, 55), Player[playerid][SSCase] = 3, Player[playerid][ChosenSkin] = 55;
			        case 3: SetPlayerSkin(playerid, 90), Player[playerid][SSCase] = 4, Player[playerid][ChosenSkin] = 90;
			        case 4: SetPlayerSkin(playerid, 193), Player[playerid][SSCase] = 5, Player[playerid][ChosenSkin] = 193;
			        case 5: SetPlayerSkin(playerid, 12), Player[playerid][SSCase] = 1, Player[playerid][ChosenSkin] = 12;
   				}
				PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0);
			}
		}
		if(clickedid == brLeft) {
	 		if(Player[playerid][pSex] == 1) {
			    switch(Player[playerid][SSCase]) {
			        case 1: SetPlayerSkin(playerid, 72), Player[playerid][SSCase] = 9, Player[playerid][ChosenSkin] = 72;
					case 9: SetPlayerSkin(playerid, 67), Player[playerid][SSCase] = 8, Player[playerid][ChosenSkin] = 67;
					case 8: SetPlayerSkin(playerid, 44), Player[playerid][SSCase] = 7, Player[playerid][ChosenSkin] = 44;
			        case 7: SetPlayerSkin(playerid, 43), Player[playerid][SSCase] = 6, Player[playerid][ChosenSkin] = 43;
			        case 6: SetPlayerSkin(playerid, 26), Player[playerid][SSCase] = 5, Player[playerid][ChosenSkin] = 26;
			        case 5: SetPlayerSkin(playerid, 15), Player[playerid][SSCase] = 4, Player[playerid][ChosenSkin] = 15;
			        case 4: SetPlayerSkin(playerid, 2), Player[playerid][SSCase] = 3, Player[playerid][ChosenSkin] = 2;
			        case 3: SetPlayerSkin(playerid, 1), Player[playerid][SSCase] = 2, Player[playerid][ChosenSkin] = 1;
			        case 2: SetPlayerSkin(playerid, 188), Player[playerid][SSCase] = 1, Player[playerid][ChosenSkin] = 188;
		  		}
		  		PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0); }
  			else {
     		    switch(Player[playerid][SSCase]) {
			        case 1: SetPlayerSkin(playerid, 193), Player[playerid][SSCase] = 5, Player[playerid][ChosenSkin] = 193;
			        case 5: SetPlayerSkin(playerid, 90), Player[playerid][SSCase] = 4, Player[playerid][ChosenSkin] = 90;
			        case 4: SetPlayerSkin(playerid, 55), Player[playerid][SSCase] = 3, Player[playerid][ChosenSkin] = 55;
			        case 3: SetPlayerSkin(playerid, 13), Player[playerid][SSCase] = 2, Player[playerid][ChosenSkin] = 13;
			        case 2: SetPlayerSkin(playerid, 12), Player[playerid][SSCase] = 1, Player[playerid][ChosenSkin] = 12;
   				}
				PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0);
			}
		}
		if(clickedid == brSelect) {
		   	SetPlayerSkin(playerid,Player[playerid][ChosenSkin]);
		   	Player[playerid][pModel][0] = Player[playerid][ChosenSkin];
		    Player[playerid][SSCase] = 0;
		    Player[playerid][ClothesRound] = false;
	    	TogglePlayerControllable(playerid, 1);
			new date[12], year, mounth, day;
			getdate(year, mounth, day);
		    format(date, sizeof(date), "%d.%d.%d",day,mounth,year);
			mysql_format(connects, query, 280+1, "INSERT INTO `accounts` (`Name`, `password`, `ip`, `datareg`, `mail`, `referal`) VALUES ('%e', '%e', '%s', '%s', '%s', '%s')", Name(playerid), Player[playerid][pPassword], Ip(playerid), date, Player[playerid][pMail], Player[playerid][pReferal]);
			mysql_tquery(connects, query, "","d", playerid);
			Player[playerid][PlayerLogged] = true;
     		TextDrawHideForPlayer(playerid,brLeft);
			TextDrawHideForPlayer(playerid,brRight);
			TextDrawHideForPlayer(playerid,brSelect);
		    CancelSelectTextDraw(playerid);
		    SetPlayerVirtualWorld(playerid,0);
			Player[playerid][pCity] = 1;
			Player[playerid][pLevel] = 1, Player[playerid][pExp] = 1;
			SpawnPlayer(playerid), SaveAccount(playerid);
            SetPlayerCameraPos(playerid, 1360.9023,-1571.8125,116.9395), SetPlayerCameraLookAt(playerid, 1480.2584,-1734.5576,18.6296);
			SCM(playerid, -1,"Поздравляем вас {1FE9B9}с успешной регистрацией!\n{ffffff}Для продолжения игры {F18C8C}введите ваш пароль в окошко ниже!");
			mysql_format(connects, query,70,"SELECT `Name` FROM `accounts` WHERE Name = '%s'", Name(playerid)), mysql_tquery(connects, query, "CheckPlayer","i", playerid);
			PlayerPlaySound(playerid, 30803, 0.0, 0.0, 0.0);
			return true;
		}
		if(clickedid == Text:INVALID_TEXT_DRAW) {
    		if(Player[playerid][ClothesRound] == true) {
	    		TogglePlayerControllable(playerid, 0);
	    		if(Player[playerid][pSex] == 1) SetPlayerSkin(playerid, 1), Player[playerid][SSCase] = 1, Player[playerid][ChosenSkin] = 1;
				else SetPlayerSkin(playerid, 13), Player[playerid][SSCase] = 1, Player[playerid][ChosenSkin] = 13;
				TextDrawShowForPlayer(playerid,brLeft);
				TextDrawShowForPlayer(playerid,brRight);
				TextDrawShowForPlayer(playerid,brSelect);
				SelectTextDraw(playerid, 0xFF4040AA);
				return true;
	}   }   }
	if(GetPVarInt(playerid,"Inv") > 0) {
	    if(clickedid == iCross || clickedid == Text:INVALID_TEXT_DRAW) {
		    for(new i; i < 20; i++) TextDrawHideForPlayer(playerid,iSlot[playerid][i]);
			TextDrawHideForPlayer(playerid,iBox),TextDrawHideForPlayer(playerid,iBox12),TextDrawHideForPlayer(playerid,iBox2),
			TextDrawHideForPlayer(playerid,iInv),TextDrawHideForPlayer(playerid, Player[playerid][iModel]),TextDrawHideForPlayer(playerid, Player[playerid][iSkin]),
	        TextDrawHideForPlayer(playerid, Player[playerid][iPhone]),TextDrawHideForPlayer(playerid, Player[playerid][iClock]),TextDrawHideForPlayer(playerid, Player[playerid][iGps]),
			TextDrawHideForPlayer(playerid, Player[playerid][iRepair]),TextDrawHideForPlayer(playerid,iChit),TextDrawHideForPlayer(playerid,iDrop),
			TextDrawHideForPlayer(playerid,iCross),TextDrawHideForPlayer(playerid,iUse),SetPVarInt(playerid,"Inv",0),CancelSelectTextDraw(playerid);
			return true;
		}
	    if(clickedid == Player[playerid][iSkin]) {
	        if(SS == -1) {
				TextDrawBackgroundColor(Player[playerid][iSkin],0xBDC3C7FF), TextDrawBackgroundColor(iSlot[playerid][SS],-540686337);
                SetPVarInt(playerid,"SelectSlot", -2), TextDrawShowForPlayer(playerid, Player[playerid][iSkin]), TextDrawShowForPlayer(playerid,iSlot[playerid][SS]);
				return true;
			}
			TextDrawBackgroundColor(Player[playerid][iSkin],0x2ECC71FF), SetPVarInt(playerid,"SelectSlot",-1);
			return true;
		}
		//0x2ECC71FF
		if(clickedid == iDrop) {
		    if(SS == -2) return SCM(playerid,0xAC7575FF,"Не выбран слот инвентаря!");
		    fcor
		    GetPlayerPos(playerid,x,y,z);
			if(SS >= -1) {
			    if(GetPlayerSkin(playerid) == 154) return SCM(playerid,0xAC7575FF,"На вас нет одежды!");
				DropedItem[droped][0] = CreateDynamicObject(2386,x+0.3,y,z-1.0,0.0,0.0,0.0), DropedItem[droped][1] = Player[playerid][pModel][0], SetPlayerSkin(playerid,154), Player[playerid][pModel][0] = 154,
				TextDrawBackgroundColor(Player[playerid][iSkin], 0xBDC3C7FF), TextDrawSetPreviewModel(Player[playerid][iModel], GetPlayerSkin(playerid));
			}
			else {
				DropedItem[droped][0] = CreateDynamicObject(Player[playerid][Slot][SS],x+0.3,y,z-1.0,0.0,0.0,0.0), Player[playerid][Slot][SS] = 0,
				TextDrawSetPreviewModel(iSlot[playerid][SS], 19349), TextDrawBackgroundColor(iSlot[playerid][SS], 0xBDC3C7FF);
				TextDrawShowForPlayer(playerid,iSlot[playerid][SS]);
			}
			droped--;
			SetPVarInt(playerid,"SelectSlot",-2);
			return true;
		}
		for(new i; i < 20; i++) {
			if(clickedid == iSlot[playerid][i]) {
     	  		if(SS > -2) TextDrawBackgroundColor(Player[playerid][iSkin],-540686337), TextDrawBackgroundColor(iSlot[playerid][SS],-540686337);
				TextDrawBackgroundColor(iSlot[playerid][i],0x2ECC71FF), SetPVarInt(playerid,"SelectSlot", (SS >= -2) ? -2 : i),TextDrawShowForPlayer(playerid, iSlot[playerid][i]);
			}
			break;
		}
	    return true;
	}
	if(Player[playerid][CreatePassword] == true) {
	        if(clickedid == a1) strins(getpass[playerid],"1",strlen(getpass[playerid])), TextDrawSetString(atext, getpass[playerid]);
			else if(clickedid == a2) strins(getpass[playerid],"2",strlen(getpass[playerid])), TextDrawSetString(atext, getpass[playerid]);
			else if(clickedid == a3) strins(getpass[playerid],"3",strlen(getpass[playerid])), TextDrawSetString(atext, getpass[playerid]);
			else if(clickedid == a4) strins(getpass[playerid],"4",strlen(getpass[playerid])), TextDrawSetString(atext, getpass[playerid]);
			else if(clickedid == a5) strins(getpass[playerid],"5",strlen(getpass[playerid])), TextDrawSetString(atext, getpass[playerid]);
			else if(clickedid == a6) strins(getpass[playerid],"6",strlen(getpass[playerid])), TextDrawSetString(atext, getpass[playerid]);
			else if(clickedid == a7) strins(getpass[playerid],"7",strlen(getpass[playerid])), TextDrawSetString(atext, getpass[playerid]);
			else if(clickedid == a8) strins(getpass[playerid],"8",strlen(getpass[playerid])), TextDrawSetString(atext, getpass[playerid]);
			else if(clickedid == a9) strins(getpass[playerid],"9",strlen(getpass[playerid])), TextDrawSetString(atext, getpass[playerid]);
			else if(clickedid == a0) strins(getpass[playerid],"0",strlen(getpass[playerid])), TextDrawSetString(atext, getpass[playerid]);
			else if(clickedid == ac) strdel(getpass[playerid],strlen(getpass[playerid])-1,strlen(getpass[playerid])), TextDrawSetString(atext, getpass[playerid]);
			else if(clickedid == aenter) {
			    if(strlen(getpass[playerid]) < 6 || strlen(getpass[playerid]) > 16) SCM(playerid,-1,"Пароль должен содержать не менее 6-ти цифр и не более 16!");
			    TogglePlayerControllable(playerid, 1);
	     		TextDrawHideForPlayer(playerid,abox);
				TextDrawHideForPlayer(playerid,a1);
				TextDrawHideForPlayer(playerid,a2);
				TextDrawHideForPlayer(playerid,a3);
				TextDrawHideForPlayer(playerid,a4);
				TextDrawHideForPlayer(playerid,a5);
				TextDrawHideForPlayer(playerid,a6);
				TextDrawHideForPlayer(playerid,a7);
				TextDrawHideForPlayer(playerid,a8);
				TextDrawHideForPlayer(playerid,a9);
				TextDrawHideForPlayer(playerid,a0);
				TextDrawHideForPlayer(playerid,aenter);
				TextDrawHideForPlayer(playerid,aboxtop);
				TextDrawHideForPlayer(playerid,atext);
				TextDrawHideForPlayer(playerid,ac);
				CancelSelectTextDraw(playerid);
				Player[playerid][APass] = strval(getpass[playerid]), Success(playerid)
				SCM(playerid,COLOR_WHITE,"Установка пароля прошла успешно, теперь введите команду /aat");
				strdel(getpass[playerid],0,strlen(getpass[playerid])), TextDrawSetString(atext, getpass[playerid]);
	}   }
	if(Player[playerid][TDSelect] == true && GetPVarInt(playerid,"MakeGun") == 1)
	{
	    if(clickedid == cXc) callcmd::makegun(playerid, "");
	    else if(clickedid == c1) SetPVarInt(playerid,"GunC",24), ShowPlayerDialog(playerid,17,DIALOG_STYLE_INPUT,"{03c03c}Сборка оружия","{ffffff}Введите желаемое количество патрон","Далее","Отмена");
	    else if(clickedid == c2) SetPVarInt(playerid,"GunC",23), ShowPlayerDialog(playerid,17,DIALOG_STYLE_INPUT,"{03c03c}Сборка оружия","{ffffff}Введите желаемое количество патрон","Далее","Отмена");
	    else if(clickedid == c3) SetPVarInt(playerid,"GunC",25), ShowPlayerDialog(playerid,17,DIALOG_STYLE_INPUT,"{03c03c}Сборка оружия","{ffffff}Введите желаемое количество патрон","Далее","Отмена");
	    else if(clickedid == c4) SetPVarInt(playerid,"GunC",30), ShowPlayerDialog(playerid,17,DIALOG_STYLE_INPUT,"{03c03c}Сборка оружия","{ffffff}Введите желаемое количество патрон","Далее","Отмена");
	    else if(clickedid == c5) SetPVarInt(playerid,"GunC",31), ShowPlayerDialog(playerid,17,DIALOG_STYLE_INPUT,"{03c03c}Сборка оружия","{ffffff}Введите желаемое количество патрон","Далее","Отмена");
	    else if(clickedid == c6) SetPVarInt(playerid,"GunC",29), ShowPlayerDialog(playerid,17,DIALOG_STYLE_INPUT,"{03c03c}Сборка оружия","{ffffff}Введите желаемое количество патрон","Далее","Отмена");
	    
	    callcmd::makegun(playerid, "");
	    
	    return true;
	}
 	if(Player[playerid][TDSelect] == true && GetPVarInt(playerid,"Menu") == 1)
	 {
	    if(clickedid == mm29) callcmd::menu(playerid, "");
	    
	    else if(clickedid == mm32) ShowPlayerDialog(playerid,18,DIALOG_STYLE_INPUT,"{03c03c}Сообщение Администрации","{ffffff}Если у вас есть жалоба на какого-либо игрока или вопрос, то вы смело можете задать его нам.\n\n\
		Форма подачи жалобы: [id нарушителя] [причина]\n\n{ff0000}Запрещено:\n - Мат\n - Оскорбления\n - Оффтоп ( сообщение не по теме )\n\n{03c03c}Наказание - от кика до бана.","Далее","Отмена");
	    else if(clickedid == mm35) ShowPlayerDialog(playerid,19,DIALOG_STYLE_LIST,"{03c03c}Настройки","{03c03c}Включить{ffffff}/{ff0000}Отключить {ffffff}ники","Далее","Отмена");
	    else if(clickedid == mm39) ShowPlayerDialog(playerid,20,DIALOG_STYLE_LIST,"{03c03c}Помощь по игре","{ff0000}В разработке","Далее","Отмена");
	    else if(clickedid == mm41) ShowPlayerDialog(playerid,21,DIALOG_STYLE_INPUT,"{03c03c}Донат","{ff0000}В РАЗРАБОТКЕ!","Далее","Отмена");

		callcmd::menu(playerid, "");

		return true;
	}
	if(Player[playerid][TDSelect] == true) {
        if(clickedid == amLeft) {
	        SetPVarInt(playerid,"AmmoSCT", (GetPVarInt(playerid,"AmmoSCT") == 0) ? 8 : (GetPVarInt(playerid,"AmmoSCT")-1));
		    switch(GetPVarInt(playerid,"AmmoSCT")) {
		        case 8: {
					PlayerTextDrawSetString(playerid,amGun[playerid],"Shovel"), PlayerTextDrawSetString(playerid,amPrice[playerid],"50$");
					SetPlayerCameraPos(playerid, 287.4729919,-106.4039993,1002.5000000), SetPlayerCameraLookAt(playerid,286.4360046,-106.5270004,1001.5999756,1);
				}
			    case 7: {
				    PlayerTextDrawSetString(playerid,amGun[playerid],"Gas grenade"), PlayerTextDrawSetString(playerid,amPrice[playerid],"70$");
					SetPlayerCameraPos(playerid, 287.0050049,-109.6429977,1002.5000000), SetPlayerCameraLookAt(playerid,286.2720032,-109.5429993,1001.5000000,1);
				}

				case 6: {
				    PlayerTextDrawSetString(playerid,amGun[playerid],"Deagle"), PlayerTextDrawSetString(playerid,amPrice[playerid],"200$");
					SetPlayerCameraPos(playerid, 292.5109863,-109.5469971,1002.9000244), SetPlayerCameraLookAt(playerid,292.4110107,-110.7949982,1001.5000000,1);
				}
				case 5: {
				    PlayerTextDrawSetString(playerid,amGun[playerid],"SDPistol"), PlayerTextDrawSetString(playerid,amPrice[playerid],"150$");
					SetPlayerCameraPos(playerid, 290.2770081,-109.3300018,1002.9000244), SetPlayerCameraLookAt(playerid,290.2139893,-110.5479965,1001.5000000,1);
				}
				case 4: {
				    PlayerTextDrawSetString(playerid,amGun[playerid],"Shotgun"), PlayerTextDrawSetString(playerid,amPrice[playerid],"350$");
			 		SetPlayerCameraPos(playerid, 288.0270081,-109.4300003,1002.9000244), SetPlayerCameraLookAt(playerid,287.8380127,-110.4950027,1001.5000000,1);
				}
				case 3: {
				    PlayerTextDrawSetString(playerid,amGun[playerid],"M4A1"), PlayerTextDrawSetString(playerid,amPrice[playerid],"250$");
			 		SetPlayerCameraPos(playerid, 292.5199890,-106.6920013,1002.9000244), SetPlayerCameraLookAt(playerid,292.6000061,-105.4690018,1001.5000000,1);
				}
				case 2: {
				    PlayerTextDrawSetString(playerid,amGun[playerid],"AK47"), PlayerTextDrawSetString(playerid,amPrice[playerid],"250$");
			 		SetPlayerCameraPos(playerid, 290.1459961,-106.6839981,1002.9000244), SetPlayerCameraLookAt(playerid,290.3429871,-105.4349976,1001.5000000,1);
				}
				case 1: {
					PlayerTextDrawSetString(playerid,amGun[playerid],"MP5"), PlayerTextDrawSetString(playerid,amPrice[playerid],"180$");
					SetPlayerCameraPos(playerid, 287.9030151,-105.7890015,1002.9000244), SetPlayerCameraLookAt(playerid,288.1010132,-105.1370010,1001.5000000,1);
				}
			}
		}
		if(clickedid == amRight) {
  			SetPVarInt(playerid,"AmmoSCT", (GetPVarInt(playerid,"AmmoSCT") == 9) ? 1 : (GetPVarInt(playerid,"AmmoSCT")+1));
    		switch(GetPVarInt(playerid,"AmmoSCT")) {
			    case 1: {
					PlayerTextDrawSetString(playerid,amGun[playerid],"MP5"), PlayerTextDrawSetString(playerid,amPrice[playerid],"180$");
					SetPlayerCameraPos(playerid, 287.9030151,-105.7890015,1002.9000244), SetPlayerCameraLookAt(playerid,288.1010132,-105.1370010,1001.5000000,1);
				}
				case 2: {
				    PlayerTextDrawSetString(playerid,amGun[playerid],"AK47"), PlayerTextDrawSetString(playerid,amPrice[playerid],"250$");
			 		SetPlayerCameraPos(playerid, 290.1459961,-106.6839981,1002.9000244), SetPlayerCameraLookAt(playerid,290.3429871,-105.4349976,1001.5000000,1);
				}
				case 3: {
				    PlayerTextDrawSetString(playerid,amGun[playerid],"M4A1"), PlayerTextDrawSetString(playerid,amPrice[playerid],"250$");
			 		SetPlayerCameraPos(playerid, 292.5199890,-106.6920013,1002.9000244), SetPlayerCameraLookAt(playerid,292.6000061,-105.4690018,1001.5000000,1);
				}
				case 4: {
				    PlayerTextDrawSetString(playerid,amGun[playerid],"Shotgun"), PlayerTextDrawSetString(playerid,amPrice[playerid],"350$");
			 		SetPlayerCameraPos(playerid, 288.0270081,-109.4300003,1002.9000244), SetPlayerCameraLookAt(playerid,287.8380127,-110.4950027,1001.5000000,1);
				}
				case 5: {
				    PlayerTextDrawSetString(playerid,amGun[playerid],"SDPistol"), PlayerTextDrawSetString(playerid,amPrice[playerid],"135$");
					SetPlayerCameraPos(playerid, 290.2770081,-109.3300018,1002.9000244), SetPlayerCameraLookAt(playerid,290.2139893,-110.5479965,1001.5000000,1);
				}
				case 6: {
				    PlayerTextDrawSetString(playerid,amGun[playerid],"Deagle"), PlayerTextDrawSetString(playerid,amPrice[playerid],"100$");
					SetPlayerCameraPos(playerid, 292.5109863,-109.5469971,1002.9000244), SetPlayerCameraLookAt(playerid,292.4110107,-110.7949982,1001.5000000,1);
				}
				case 7: {
				    PlayerTextDrawSetString(playerid,amGun[playerid],"Gas Grenade"), PlayerTextDrawSetString(playerid,amPrice[playerid],"70$");
					SetPlayerCameraPos(playerid, 287.0050049,-109.6429977,1002.5000000), SetPlayerCameraLookAt(playerid,286.2720032,-109.5429993,1001.5000000,1);
				}
				case 8: {
					PlayerTextDrawSetString(playerid,amGun[playerid],"Shovel"), PlayerTextDrawSetString(playerid,amPrice[playerid],"50$");
					SetPlayerCameraPos(playerid, 287.4729919,-106.4039993,1002.5000000), SetPlayerCameraLookAt(playerid,286.4360046,-106.5270004,1001.5999756,1);
				}
			}
		}
		if(clickedid == amBBUY) {
		   	switch(GetPVarInt(playerid,"AmmoSCT")) {
		   	    case 1: {
				   		if(Player[playerid][pMoney] < 180) return SCM(playerid,0xCA7575FF,"У вас недостаточно денег для этой покупки!");
				   		GiveWeapon(playerid,29,30), Player[playerid][pMoney] -= 180, GameTextForPlayer(playerid, "~g~+30 MP5", 1000, 3);
				   		Business[GetPVarInt(playerid,"BID")][bIncome] += 180;
				   		Business[GetPVarInt(playerid,"BID")][bProduct]--;
				}
		   	    case 2:  {
				   		if(Player[playerid][pMoney] < 250) return SCM(playerid,0xCA7575FF,"У вас недостаточно денег для этой покупки!");
	   					GiveWeapon(playerid,30,30), Player[playerid][pMoney] -= 250,  GameTextForPlayer(playerid, "~g~+30 AK47", 1000, 3);
	   					Business[GetPVarInt(playerid,"BID")][bIncome] += 250;
				   		Business[GetPVarInt(playerid,"BID")][bProduct]--;
				}
	   			case 3:  {
				   		if(Player[playerid][pMoney] < 250) return SCM(playerid,0xCA7575FF,"У вас недостаточно денег для этой покупки!");
				   		GiveWeapon(playerid,31,50), Player[playerid][pMoney] -= 250,  GameTextForPlayer(playerid, "~g~+50 M4A1", 1000, 3);
				   		Business[GetPVarInt(playerid,"BID")][bIncome] += 250;
				   		Business[GetPVarInt(playerid,"BID")][bProduct]--;
				}
		   	    case 4:  {
				   		if(Player[playerid][pMoney] < 350) return SCM(playerid,0xCA7575FF,"У вас недостаточно денег для этой покупки!");
				   		GiveWeapon(playerid,25,30), Player[playerid][pMoney] -= 350,  GameTextForPlayer(playerid, "~g~+30 Shotgun", 1000, 3);
				   		Business[GetPVarInt(playerid,"BID")][bIncome] += 350;
				   		Business[GetPVarInt(playerid,"BID")][bProduct]--;
				}
		   	    case 5:  {
				   		if(Player[playerid][pMoney] < 135) return SCM(playerid,0xCA7575FF,"У вас недостаточно денег для этой покупки!");
				   		GiveWeapon(playerid,23,17), Player[playerid][pMoney] -= 135,  GameTextForPlayer(playerid, "~g~+17 SDP", 1000, 3);
				   		Business[GetPVarInt(playerid,"BID")][bIncome] += 135;
				   		Business[GetPVarInt(playerid,"BID")][bProduct]--;
				}
		   	    case 6:  {
				   		if(Player[playerid][pMoney] < 100) return SCM(playerid,0xCA7575FF,"У вас недостаточно денег для этой покупки!");
				   		GiveWeapon(playerid,24,7), Player[playerid][pMoney] -= 100,  GameTextForPlayer(playerid, "~g~+7 Deagle", 1000, 3);
				   		Business[GetPVarInt(playerid,"BID")][bIncome] += 100;
				   		Business[GetPVarInt(playerid,"BID")][bProduct]--;
				}
				case 7:  {
				   		if(Player[playerid][pMoney] < 70) return SCM(playerid,0xCA7575FF,"У вас недостаточно денег для этой покупки!");
				   		GiveWeapon(playerid,17,1), Player[playerid][pMoney] -= 70,  GameTextForPlayer(playerid, "~g~+ Gas Grenade", 1000, 3);
				   		Business[GetPVarInt(playerid,"BID")][bIncome] += 70;
				   		Business[GetPVarInt(playerid,"BID")][bProduct]--;
				}
	   			case 8:  {
				   		if(Player[playerid][pMoney] < 50) return SCM(playerid,0xCA7575FF,"У вас недостаточно денег для этой покупки!");
				   		GiveWeapon(playerid,6,1), Player[playerid][pMoney] -= 50,  GameTextForPlayer(playerid, "~g~+ Showel", 1000, 3);
				   		Business[GetPVarInt(playerid,"BID")][bIncome] += 50;
				   		Business[GetPVarInt(playerid,"BID")][bProduct]--;
				}
			}
			PlayerPlaySound(playerid,1052,289.9062,-108.0327,1001.5156);
		}
		if(clickedid == amBBACK) {
			TogglePlayerControllable(playerid, 1);
     		TextDrawHideForPlayer(playerid,amBox);
			PlayerTextDrawHide(playerid,amGun[playerid]);
		    TextDrawHideForPlayer(playerid,amPCPS);
		    PlayerTextDrawHide(playerid,amPrice[playerid]);
		    TextDrawHideForPlayer(playerid,amBox2);
		    TextDrawHideForPlayer(playerid,amChit);
		    TextDrawHideForPlayer(playerid,amLeft);
		    TextDrawHideForPlayer(playerid,amChit2);
		    TextDrawHideForPlayer(playerid,amRight);
		    TextDrawHideForPlayer(playerid,amBBUY);
		    TextDrawHideForPlayer(playerid,amBBACK);
			TextDrawHideForPlayer(playerid,amBUY);
			TextDrawHideForPlayer(playerid,amBack);
			SetCameraBehindPlayer(playerid);
			CancelSelectTextDraw(playerid), Player[playerid][TDSelect] = false;
			PlayerPlaySound(playerid,1053,289.9062,-108.0327,1001.5156);
			SetPVarInt(playerid,"DialogActive",0),SetPVarInt(playerid,"GetPickup",gettime()+3);
		}
		if(clickedid == Text:INVALID_TEXT_DRAW && GetPVarInt(playerid,"AmmoSCT") > 0) {
		    TogglePlayerControllable(playerid, 1);
     		TextDrawHideForPlayer(playerid,amBox);
			PlayerTextDrawHide(playerid,amGun[playerid]);
		    TextDrawHideForPlayer(playerid,amPCPS);
		    PlayerTextDrawHide(playerid,amPrice[playerid]);
		    TextDrawHideForPlayer(playerid,amBox2);
		    TextDrawHideForPlayer(playerid,amChit);
		    TextDrawHideForPlayer(playerid,amLeft);
		    TextDrawHideForPlayer(playerid,amChit2);
		    TextDrawHideForPlayer(playerid,amRight);
		    TextDrawHideForPlayer(playerid,amBBUY);
		    TextDrawHideForPlayer(playerid,amBBACK);
			TextDrawHideForPlayer(playerid,amBUY);
			TextDrawHideForPlayer(playerid,amBack);
			SetCameraBehindPlayer(playerid);
			CancelSelectTextDraw(playerid), Player[playerid][TDSelect] = false;
			PlayerPlaySound(playerid,1053,289.9062,-108.0327,1001.5156);
			SetPVarInt(playerid,"DialogActive",0),SetPVarInt(playerid,"GetPickup",gettime()+3);
		}
		if(GetPVarInt(playerid,"BuySkin") > 0) {
			if(clickedid == brRight) {
  				//unused 1 2 15 26 43 44 67 72 188 - MAN
				//unused 13 55 90 193 12 - WOOMAN
		 		if(Player[playerid][pSex] == 1) {
		 		    Player[playerid][SSCase] = (Player[playerid][SSCase] == 37) ? (1) : (Player[playerid][SSCase]+1);
					switch(Player[playerid][SSCase]) {
						case 1: SetPlayerSkin(playerid, 22), Player[playerid][ChosenSkin] = 22, TextDrawSetString(Player[playerid][tCostItem],"5000$"), SetPVarInt(playerid,"BuySkin",5000);
				        case 2: SetPlayerSkin(playerid, 3), Player[playerid][ChosenSkin] = 3, TextDrawSetString(Player[playerid][tCostItem],"15000$"), SetPVarInt(playerid,"BuySkin", 15000);
						case 3: SetPlayerSkin(playerid, 5), Player[playerid][ChosenSkin] = 5, TextDrawSetString(Player[playerid][tCostItem],"4000$"), SetPVarInt(playerid,"BuySkin", 4000);
						case 4: SetPlayerSkin(playerid, 6), Player[playerid][ChosenSkin] = 6, TextDrawSetString(Player[playerid][tCostItem],"12000$"), SetPVarInt(playerid,"BuySkin", 12000);
						case 5: SetPlayerSkin(playerid, 7), Player[playerid][ChosenSkin] = 7, TextDrawSetString(Player[playerid][tCostItem],"10000$"), SetPVarInt(playerid,"BuySkin", 10000);
						case 6: SetPlayerSkin(playerid, 18),Player[playerid][ChosenSkin] = 18, TextDrawSetString(Player[playerid][tCostItem],"25000$"), SetPVarInt(playerid,"BuySkin", 25000);
						case 7: SetPlayerSkin(playerid, 19), Player[playerid][ChosenSkin] = 19, TextDrawSetString(Player[playerid][tCostItem],"30000$"), SetPVarInt(playerid,"BuySkin", 30000);
						case 8: SetPlayerSkin(playerid, 20), Player[playerid][ChosenSkin] = 20, TextDrawSetString(Player[playerid][tCostItem],"40000$"), SetPVarInt(playerid,"BuySkin", 40000);
						case 9: SetPlayerSkin(playerid, 21), Player[playerid][ChosenSkin] = 21, TextDrawSetString(Player[playerid][tCostItem],"10000$"), SetPVarInt(playerid,"BuySkin", 10000);
						case 10: SetPlayerSkin(playerid, 23), Player[playerid][ChosenSkin] = 23, TextDrawSetString(Player[playerid][tCostItem],"20000$"), SetPVarInt(playerid,"BuySkin", 20000);
						case 11: SetPlayerSkin(playerid, 28), Player[playerid][ChosenSkin] = 28, TextDrawSetString(Player[playerid][tCostItem],"40000$"), SetPVarInt(playerid,"BuySkin", 40000);
						case 12: SetPlayerSkin(playerid, 29), Player[playerid][ChosenSkin] = 29, TextDrawSetString(Player[playerid][tCostItem],"50000$"), SetPVarInt(playerid,"BuySkin", 50000);
						case 13: SetPlayerSkin(playerid, 30), Player[playerid][ChosenSkin] = 30, TextDrawSetString(Player[playerid][tCostItem],"50000$"), SetPVarInt(playerid,"BuySkin", 50000);
						case 14: SetPlayerSkin(playerid, 37), Player[playerid][ChosenSkin] = 37, TextDrawSetString(Player[playerid][tCostItem],"5000$"), SetPVarInt(playerid,"BuySkin", 5000);
						case 15: SetPlayerSkin(playerid, 42), Player[playerid][ChosenSkin] = 42, TextDrawSetString(Player[playerid][tCostItem],"15000$"), SetPVarInt(playerid,"BuySkin", 15000);
						case 16: SetPlayerSkin(playerid, 46), Player[playerid][ChosenSkin] = 46, TextDrawSetString(Player[playerid][tCostItem],"320000$"), SetPVarInt(playerid,"BuySkin", 320000);
                        case 17: SetPlayerSkin(playerid, 47), Player[playerid][ChosenSkin] = 47, TextDrawSetString(Player[playerid][tCostItem],"60000$"), SetPVarInt(playerid,"BuySkin", 60000);
                        case 18: SetPlayerSkin(playerid, 48), Player[playerid][ChosenSkin] = 48, TextDrawSetString(Player[playerid][tCostItem],"60000$"), SetPVarInt(playerid,"BuySkin", 60000);
                        case 19: SetPlayerSkin(playerid, 59), Player[playerid][ChosenSkin] = 59, TextDrawSetString(Player[playerid][tCostItem],"65000$"), SetPVarInt(playerid,"BuySkin", 65000);
                        case 20: SetPlayerSkin(playerid, 60), Player[playerid][ChosenSkin] = 60, TextDrawSetString(Player[playerid][tCostItem],"15000$"), SetPVarInt(playerid,"BuySkin", 15000);
                        case 21: SetPlayerSkin(playerid, 82), Player[playerid][ChosenSkin] = 82, TextDrawSetString(Player[playerid][tCostItem],"90000$"), SetPVarInt(playerid,"BuySkin", 90000);
                        case 22: SetPlayerSkin(playerid, 83), Player[playerid][ChosenSkin] = 83, TextDrawSetString(Player[playerid][tCostItem],"90000$"), SetPVarInt(playerid,"BuySkin", 90000);
                        case 23: SetPlayerSkin(playerid, 84), Player[playerid][ChosenSkin] = 84, TextDrawSetString(Player[playerid][tCostItem],"90000$"), SetPVarInt(playerid,"BuySkin", 90000);
                        case 24: SetPlayerSkin(playerid, 101), Player[playerid][ChosenSkin] = 101, TextDrawSetString(Player[playerid][tCostItem],"30000$"), SetPVarInt(playerid,"BuySkin", 30000);
                        case 25: SetPlayerSkin(playerid, 119), Player[playerid][ChosenSkin] = 119, TextDrawSetString(Player[playerid][tCostItem],"45000$"), SetPVarInt(playerid,"BuySkin", 45000);
                        case 26: SetPlayerSkin(playerid, 121), Player[playerid][ChosenSkin] = 121, TextDrawSetString(Player[playerid][tCostItem],"20000$"), SetPVarInt(playerid,"BuySkin", 20000);
                        case 27: SetPlayerSkin(playerid, 184), Player[playerid][ChosenSkin] = 184, TextDrawSetString(Player[playerid][tCostItem],"15000$"), SetPVarInt(playerid,"BuySkin", 15000);
                        case 28: SetPlayerSkin(playerid, 185), Player[playerid][ChosenSkin] = 185, TextDrawSetString(Player[playerid][tCostItem],"110000$"), SetPVarInt(playerid,"BuySkin", 110000);
                        case 29: SetPlayerSkin(playerid, 208), Player[playerid][ChosenSkin] = 208, TextDrawSetString(Player[playerid][tCostItem],"135000$"), SetPVarInt(playerid,"BuySkin", 135000);
                        case 30: SetPlayerSkin(playerid, 223), Player[playerid][ChosenSkin] = 223, TextDrawSetString(Player[playerid][tCostItem],"165000$"), SetPVarInt(playerid,"BuySkin", 165000);
                        case 31: SetPlayerSkin(playerid, 241), Player[playerid][ChosenSkin] = 241, TextDrawSetString(Player[playerid][tCostItem],"70000$"), SetPVarInt(playerid,"BuySkin", 70000);
                        case 32: SetPlayerSkin(playerid, 242), Player[playerid][ChosenSkin] = 242, TextDrawSetString(Player[playerid][tCostItem],"70000$"), SetPVarInt(playerid,"BuySkin", 70000);
                        case 33: SetPlayerSkin(playerid, 291), Player[playerid][ChosenSkin] = 291, TextDrawSetString(Player[playerid][tCostItem],"190000$"), SetPVarInt(playerid,"BuySkin", 190000);
                        case 34: SetPlayerSkin(playerid, 292), Player[playerid][ChosenSkin] = 292, TextDrawSetString(Player[playerid][tCostItem],"230000$"), SetPVarInt(playerid,"BuySkin", 230000);
                        case 35: SetPlayerSkin(playerid, 293), Player[playerid][ChosenSkin] = 293, TextDrawSetString(Player[playerid][tCostItem],"210000$"), SetPVarInt(playerid,"BuySkin", 210000);
                        case 36: SetPlayerSkin(playerid, 299), Player[playerid][ChosenSkin] = 299, TextDrawSetString(Player[playerid][tCostItem],"310000$"), SetPVarInt(playerid,"BuySkin", 310000);
                        case 37: SetPlayerSkin(playerid, 294), Player[playerid][ChosenSkin] = 294, TextDrawSetString(Player[playerid][tCostItem],"350000$"), SetPVarInt(playerid,"BuySkin", 350000);
					}
					PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0); }
	  			else {
	  			    Player[playerid][SSCase] = (Player[playerid][SSCase] == 8) ? (1) : (Player[playerid][SSCase]+1);
		    		switch(Player[playerid][SSCase]) {
				        case 1: SetPlayerSkin(playerid, 9), Player[playerid][ChosenSkin] = 9, TextDrawSetString(Player[playerid][tCostItem],"15000$");
				        case 2: SetPlayerSkin(playerid, 11), Player[playerid][ChosenSkin] = 11, TextDrawSetString(Player[playerid][tCostItem],"20000$");
				        case 3: SetPlayerSkin(playerid, 12), Player[playerid][ChosenSkin] = 12, TextDrawSetString(Player[playerid][tCostItem],"50000$");
				        case 4: SetPlayerSkin(playerid, 40), Player[playerid][ChosenSkin] = 40, TextDrawSetString(Player[playerid][tCostItem],"60000$");
				        case 5: SetPlayerSkin(playerid, 56), Player[playerid][ChosenSkin] = 56, TextDrawSetString(Player[playerid][tCostItem],"5000$");
				        case 6: SetPlayerSkin(playerid, 93), Player[playerid][ChosenSkin] = 93, TextDrawSetString(Player[playerid][tCostItem],"100000$");
				        case 7: SetPlayerSkin(playerid, 91), Player[playerid][ChosenSkin] = 91, TextDrawSetString(Player[playerid][tCostItem],"200000$");
				        case 8: SetPlayerSkin(playerid, 141), Player[playerid][ChosenSkin] = 141, TextDrawSetString(Player[playerid][tCostItem],"300000$");
	   				}
					PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0); } }
			else if(clickedid == brLeft) {
		 		if(Player[playerid][pSex] == 1) {
                    Player[playerid][SSCase] = (Player[playerid][SSCase] == 1) ? (37) : (Player[playerid][SSCase]-1);
				    switch(Player[playerid][SSCase]) {
						case 1: SetPlayerSkin(playerid, 22), Player[playerid][ChosenSkin] = 22, TextDrawSetString(Player[playerid][tCostItem],"5000$"), SetPVarInt(playerid,"BuySkin",5000);
				        case 2: SetPlayerSkin(playerid, 3), Player[playerid][ChosenSkin] = 3, TextDrawSetString(Player[playerid][tCostItem],"15000$"), SetPVarInt(playerid,"BuySkin", 15000);
						case 3: SetPlayerSkin(playerid, 5), Player[playerid][ChosenSkin] = 5, TextDrawSetString(Player[playerid][tCostItem],"4000$"), SetPVarInt(playerid,"BuySkin", 4000);
						case 4: SetPlayerSkin(playerid, 6), Player[playerid][ChosenSkin] = 6, TextDrawSetString(Player[playerid][tCostItem],"12000$"), SetPVarInt(playerid,"BuySkin", 12000);
						case 5: SetPlayerSkin(playerid, 7), Player[playerid][ChosenSkin] = 7, TextDrawSetString(Player[playerid][tCostItem],"10000$"), SetPVarInt(playerid,"BuySkin", 10000);
						case 6: SetPlayerSkin(playerid, 18),Player[playerid][ChosenSkin] = 18, TextDrawSetString(Player[playerid][tCostItem],"25000$"), SetPVarInt(playerid,"BuySkin", 25000);
						case 7: SetPlayerSkin(playerid, 19), Player[playerid][ChosenSkin] = 19, TextDrawSetString(Player[playerid][tCostItem],"30000$"), SetPVarInt(playerid,"BuySkin", 30000);
						case 8: SetPlayerSkin(playerid, 20), Player[playerid][ChosenSkin] = 20, TextDrawSetString(Player[playerid][tCostItem],"40000$"), SetPVarInt(playerid,"BuySkin", 40000);
						case 9: SetPlayerSkin(playerid, 21), Player[playerid][ChosenSkin] = 21, TextDrawSetString(Player[playerid][tCostItem],"10000$"), SetPVarInt(playerid,"BuySkin", 10000);
						case 10: SetPlayerSkin(playerid, 23), Player[playerid][ChosenSkin] = 23, TextDrawSetString(Player[playerid][tCostItem],"20000$"), SetPVarInt(playerid,"BuySkin", 20000);
						case 11: SetPlayerSkin(playerid, 28), Player[playerid][ChosenSkin] = 28, TextDrawSetString(Player[playerid][tCostItem],"40000$"), SetPVarInt(playerid,"BuySkin", 40000);
						case 12: SetPlayerSkin(playerid, 29), Player[playerid][ChosenSkin] = 29, TextDrawSetString(Player[playerid][tCostItem],"50000$"), SetPVarInt(playerid,"BuySkin", 50000);
						case 13: SetPlayerSkin(playerid, 30), Player[playerid][ChosenSkin] = 30, TextDrawSetString(Player[playerid][tCostItem],"50000$"), SetPVarInt(playerid,"BuySkin", 50000);
						case 14: SetPlayerSkin(playerid, 37), Player[playerid][ChosenSkin] = 37, TextDrawSetString(Player[playerid][tCostItem],"5000$"), SetPVarInt(playerid,"BuySkin", 5000);
						case 15: SetPlayerSkin(playerid, 42), Player[playerid][ChosenSkin] = 42, TextDrawSetString(Player[playerid][tCostItem],"15000$"), SetPVarInt(playerid,"BuySkin", 15000);
						case 16: SetPlayerSkin(playerid, 46), Player[playerid][ChosenSkin] = 46, TextDrawSetString(Player[playerid][tCostItem],"320000$"), SetPVarInt(playerid,"BuySkin", 320000);
                        case 17: SetPlayerSkin(playerid, 47), Player[playerid][ChosenSkin] = 47, TextDrawSetString(Player[playerid][tCostItem],"60000$"), SetPVarInt(playerid,"BuySkin", 60000);
                        case 18: SetPlayerSkin(playerid, 48), Player[playerid][ChosenSkin] = 48, TextDrawSetString(Player[playerid][tCostItem],"60000$"), SetPVarInt(playerid,"BuySkin", 60000);
                        case 19: SetPlayerSkin(playerid, 59), Player[playerid][ChosenSkin] = 59, TextDrawSetString(Player[playerid][tCostItem],"65000$"), SetPVarInt(playerid,"BuySkin", 65000);
                        case 20: SetPlayerSkin(playerid, 60), Player[playerid][ChosenSkin] = 60, TextDrawSetString(Player[playerid][tCostItem],"15000$"), SetPVarInt(playerid,"BuySkin", 15000);
                        case 21: SetPlayerSkin(playerid, 82), Player[playerid][ChosenSkin] = 82, TextDrawSetString(Player[playerid][tCostItem],"90000$"), SetPVarInt(playerid,"BuySkin", 90000);
                        case 22: SetPlayerSkin(playerid, 83), Player[playerid][ChosenSkin] = 83, TextDrawSetString(Player[playerid][tCostItem],"90000$"), SetPVarInt(playerid,"BuySkin", 90000);
                        case 23: SetPlayerSkin(playerid, 84), Player[playerid][ChosenSkin] = 84, TextDrawSetString(Player[playerid][tCostItem],"90000$"), SetPVarInt(playerid,"BuySkin", 90000);
                        case 24: SetPlayerSkin(playerid, 101), Player[playerid][ChosenSkin] = 101, TextDrawSetString(Player[playerid][tCostItem],"30000$"), SetPVarInt(playerid,"BuySkin", 30000);
                        case 25: SetPlayerSkin(playerid, 119), Player[playerid][ChosenSkin] = 119, TextDrawSetString(Player[playerid][tCostItem],"45000$"), SetPVarInt(playerid,"BuySkin", 45000);
                        case 26: SetPlayerSkin(playerid, 121), Player[playerid][ChosenSkin] = 121, TextDrawSetString(Player[playerid][tCostItem],"20000$"), SetPVarInt(playerid,"BuySkin", 20000);
                        case 27: SetPlayerSkin(playerid, 184), Player[playerid][ChosenSkin] = 184, TextDrawSetString(Player[playerid][tCostItem],"15000$"), SetPVarInt(playerid,"BuySkin", 15000);
                        case 28: SetPlayerSkin(playerid, 185), Player[playerid][ChosenSkin] = 185, TextDrawSetString(Player[playerid][tCostItem],"110000$"), SetPVarInt(playerid,"BuySkin", 110000);
                        case 29: SetPlayerSkin(playerid, 208), Player[playerid][ChosenSkin] = 208, TextDrawSetString(Player[playerid][tCostItem],"135000$"), SetPVarInt(playerid,"BuySkin", 135000);
                        case 30: SetPlayerSkin(playerid, 223), Player[playerid][ChosenSkin] = 223, TextDrawSetString(Player[playerid][tCostItem],"165000$"), SetPVarInt(playerid,"BuySkin", 165000);
                        case 31: SetPlayerSkin(playerid, 241), Player[playerid][ChosenSkin] = 241, TextDrawSetString(Player[playerid][tCostItem],"70000$"), SetPVarInt(playerid,"BuySkin", 70000);
                        case 32: SetPlayerSkin(playerid, 242), Player[playerid][ChosenSkin] = 242, TextDrawSetString(Player[playerid][tCostItem],"70000$"), SetPVarInt(playerid,"BuySkin", 70000);
                        case 33: SetPlayerSkin(playerid, 291), Player[playerid][ChosenSkin] = 291, TextDrawSetString(Player[playerid][tCostItem],"190000$"), SetPVarInt(playerid,"BuySkin", 190000);
                        case 34: SetPlayerSkin(playerid, 292), Player[playerid][ChosenSkin] = 292, TextDrawSetString(Player[playerid][tCostItem],"230000$"), SetPVarInt(playerid,"BuySkin", 230000);
                        case 35: SetPlayerSkin(playerid, 293), Player[playerid][ChosenSkin] = 293, TextDrawSetString(Player[playerid][tCostItem],"210000$"), SetPVarInt(playerid,"BuySkin", 210000);
                        case 36: SetPlayerSkin(playerid, 299), Player[playerid][ChosenSkin] = 299, TextDrawSetString(Player[playerid][tCostItem],"310000$"), SetPVarInt(playerid,"BuySkin", 310000);
                        case 37: SetPlayerSkin(playerid, 294), Player[playerid][ChosenSkin] = 294, TextDrawSetString(Player[playerid][tCostItem],"350000$"), SetPVarInt(playerid,"BuySkin", 350000);
					}
			  		PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0); }
	  			else {
	  			    Player[playerid][SSCase] = (Player[playerid][SSCase] == 1) ? (8) : (Player[playerid][SSCase]-1);
	     		    switch(Player[playerid][SSCase]) {
				        case 1: SetPlayerSkin(playerid, 9), Player[playerid][ChosenSkin] = 9, TextDrawSetString(Player[playerid][tCostItem],"15000$"), SetPVarInt(playerid, "BuySkin", 15000);
				        case 2: SetPlayerSkin(playerid, 11), Player[playerid][ChosenSkin] = 11, TextDrawSetString(Player[playerid][tCostItem],"20000$"), SetPVarInt(playerid,"BuySkin", 20000);
				        case 3: SetPlayerSkin(playerid, 12), Player[playerid][ChosenSkin] = 12, TextDrawSetString(Player[playerid][tCostItem],"50000$"), SetPVarInt(playerid,"BuySkin", 50000);
				        case 4: SetPlayerSkin(playerid, 40), Player[playerid][ChosenSkin] = 40, TextDrawSetString(Player[playerid][tCostItem],"60000$"), SetPVarInt(playerid,"BuySkin", 60000);
				        case 5: SetPlayerSkin(playerid, 56), Player[playerid][ChosenSkin] = 56, TextDrawSetString(Player[playerid][tCostItem],"5000$"), SetPVarInt(playerid,"BuySkin", 5000);
				        case 6: SetPlayerSkin(playerid, 93), Player[playerid][ChosenSkin] = 93, TextDrawSetString(Player[playerid][tCostItem],"100000$"), SetPVarInt(playerid,"BuySkin", 100000);
				        case 7: SetPlayerSkin(playerid, 91), Player[playerid][ChosenSkin] = 91, TextDrawSetString(Player[playerid][tCostItem],"200000$"), SetPVarInt(playerid,"BuySkin", 200000);
				        case 8: SetPlayerSkin(playerid, 141), Player[playerid][ChosenSkin] = 141, TextDrawSetString(Player[playerid][tCostItem],"300000$"), SetPVarInt(playerid,"BuySkin", 300000);
	   				}
					PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0); } }
			if(clickedid == brSelect) ShowPlayerDialog(playerid,51,DIALOG_STYLE_MSGBOX,"{FF8C00}Покупка одежды","{ffffff}Вы действительно хотите {FF8C00}купить данную одежду?","Да","Нет");
			if(clickedid == ButtonCancel || clickedid == Text:INVALID_TEXT_DRAW) {
 				SetPlayerVirtualWorld(playerid,1), TogglePlayerControllable(playerid,1), CancelSelectTextDraw(playerid), TextDrawHideForPlayer(playerid, brLeft), TextDrawHideForPlayer(playerid, brRight),
				TextDrawHideForPlayer(playerid, brSelect), TextDrawHideForPlayer(playerid, ButtonCancel), TextDrawHideForPlayer(playerid, tCost), TextDrawHideForPlayer(playerid, Player[playerid][tCostItem]);
				SetCameraBehindPlayer(playerid);
				SetPVarInt(playerid,"BuySkin",0), SetPlayerSkin(playerid, (Player[playerid][pFraction][0] > 0) ? Player[playerid][pModel][1] : Player[playerid][pModel][0]);
			}
		}
		if(GetPVarInt(playerid,"BuyCase") > 0) {
		    if(clickedid == asLeft) {
			    DestroyVehicle(Player[playerid][pCar][3]);
			    SetPVarInt(playerid,"BuyCase", (GetPVarInt(playerid,"BuyCase") == 1) ? (3) : (GetPVarInt(playerid,"BuyCase")-1));
			    switch(GetPVarInt(playerid,"BuyCase")) {
			        case 1: SetPVarInt(playerid,"BuyCar",400), TextDrawSetString(Player[playerid][asCostV],"350000$");
			        case 2: SetPVarInt(playerid,"BuyCar",401), TextDrawSetString(Player[playerid][asCostV],"170000$");
			        case 3: SetPVarInt(playerid,"BuyCar",603), TextDrawSetString(Player[playerid][asCostV],"2300000$");
			    }
			    Player[playerid][pCar][3] = CreateVehicle(GetPVarInt(playerid,"BuyCar"),126.8960,-870.0629,1559.7389,246.1619,-1,-1,150);
			    SetVehicleVirtualWorld(Player[playerid][pCar][3],playerid+2);
			    TextDrawSetString(Player[playerid][asVname],VehicleNames[GetVehicleModel(GetPlayerVehicleID(playerid)-400)]);
			}
			if(clickedid == asRight) {
			    DestroyVehicle(Player[playerid][pCar][3]);
			    SetPVarInt(playerid,"BuyCase", (GetPVarInt(playerid,"BuyCase") == 3) ? (1) : (GetPVarInt(playerid,"BuyCase")+1));
			    switch(GetPVarInt(playerid,"BuyCase")) {
			        case 1: SetPVarInt(playerid,"BuyCar",400), TextDrawSetString(Player[playerid][asCostV],"350000$");
			        case 2: SetPVarInt(playerid,"BuyCar",401), TextDrawSetString(Player[playerid][asCostV],"170000$");
			        case 3: SetPVarInt(playerid,"BuyCar",603), TextDrawSetString(Player[playerid][asCostV],"2300000$");
			    }
			    Player[playerid][pCar][3] = CreateVehicle(GetPVarInt(playerid,"BuyCar"),126.8960,-870.0629,1559.7389,246.1619,-1,-1,150);
			    SetVehicleVirtualWorld(Player[playerid][pCar][3],playerid+2);
			    TextDrawSetString(Player[playerid][asVname],VehicleNames[GetVehicleModel(GetPlayerVehicleID(playerid)-400)]);
			}
			if(clickedid == asBBuy) ShowPlayerDialog(playerid,61,DIALOG_STYLE_MSGBOX,"{FF8C00}Покупка автотранспорта","{ffffff}Вы действительно хотите {FF8C00}купить данный автотранспорт?","Да","Нет");
			if(clickedid == asBExit || clickedid == Text:INVALID_TEXT_DRAW) {
 				TogglePlayerControllable(playerid,1), CancelSelectTextDraw(playerid), TextDrawHideForPlayer(playerid, asLeft), TextDrawHideForPlayer(playerid, asRight),
				TextDrawHideForPlayer(playerid, asCost), TextDrawHideForPlayer(playerid, asBox), TextDrawHideForPlayer(playerid, Player[playerid][asCostV]), TextDrawHideForPlayer(playerid, Player[playerid][asVname]), TextDrawHideForPlayer(playerid, asBuy);
				TextDrawHideForPlayer(playerid, asExit), TextDrawHideForPlayer(playerid, asBBuy), TextDrawHideForPlayer(playerid, asBExit);
				SetPVarInt(playerid,"BuyCase",0), SetPVarInt(playerid,"BuyCar",0), DestroyVehicle(Player[playerid][pCar][3]);
				AC_SetPlayerPos(playerid,546.3284,-1288.5500,17.2482), SetPlayerFacingAngle(playerid,0.6265), SetCameraBehindPlayer(playerid), SetPlayerVirtualWorld(playerid,0);
			}
		}
	}
	if(GetPVarInt(playerid,"ChangeSkin") > 0) {
			if(clickedid == brRight) {
		 		    Player[playerid][SSCase] = (Player[playerid][SSCase] == 3) ? (1) : (Player[playerid][SSCase]+1);
					switch(Player[playerid][SSCase]) {
						case 1: SetPlayerSkin(playerid, Player[playerid][pModel][0]);
				        case 2: SetPlayerSkin(playerid, Player[playerid][OtherM][0]);
						case 3: SetPlayerSkin(playerid, Player[playerid][OtherM][1]);
					}
					PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0);
			}
			else if(clickedid == brLeft) {
                    Player[playerid][SSCase] = (Player[playerid][SSCase] == 1) ? (3) : (Player[playerid][SSCase]-1);
				    switch(Player[playerid][SSCase]) {
						case 1: SetPlayerSkin(playerid, Player[playerid][pModel][0]);
				        case 2: SetPlayerSkin(playerid, Player[playerid][OtherM][0]);
						case 3: SetPlayerSkin(playerid, Player[playerid][OtherM][1]);
					}
			  		PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0);
			}
			if(clickedid == brSelect) {
			    switch(Player[playerid][SSCase]) {
			        case 2: {
			            Player[playerid][OtherM][0] ^= (Player[playerid][pModel][0] ^= Player[playerid][OtherM][0]);
			            Player[playerid][pModel][0] ^= Player[playerid][OtherM][0];
			        }
			        case 3: {
                        Player[playerid][OtherM][1] ^= (Player[playerid][pModel][0] ^= Player[playerid][OtherM][1]);
			            Player[playerid][pModel][0] ^= Player[playerid][OtherM][1];
			        }
				}
				CancelSelectTextDraw(playerid), TextDrawHideForPlayer(playerid, brLeft), TextDrawHideForPlayer(playerid, brRight),
				TextDrawHideForPlayer(playerid, brSelect), TextDrawHideForPlayer(playerid, ButtonCancel),
				SpawnPlayer(playerid),SetPVarInt(playerid,"ChangeSkin",0);
			}
			if(clickedid == ButtonCancel || clickedid == Text:INVALID_TEXT_DRAW) { CancelSelectTextDraw(playerid), TextDrawHideForPlayer(playerid, brLeft), TextDrawHideForPlayer(playerid, brRight),
			TextDrawHideForPlayer(playerid, brSelect), TextDrawHideForPlayer(playerid, ButtonCancel), SpawnPlayer(playerid),SetPVarInt(playerid,"ChangeSkin",0); }
	}
	if(GetPVarInt(playerid,"SelectRace") != 0) {
	    if(clickedid == raLeft) {
			SetPVarInt(playerid,"SelectRace", (GetPVarInt(playerid,"SelectRace") == 1) ? 1 : GetPVarInt(playerid,"SelectRace")-1);
	        switch(GetPVarInt(playerid,"SelectRace")) {
				case 1: TextDrawSetString(raImg,"LD_RCE3:race12"), track = "San Fierro Ramp";
			}
	    }
	    if(clickedid == raRight) {
	    	SetPVarInt(playerid,"SelectRace", (GetPVarInt(playerid,"SelectRace") == 1) ? 1 : GetPVarInt(playerid,"SelectRace")+1);
	        switch(GetPVarInt(playerid,"SelectRace")) {
				case 1: TextDrawSetString(raImg,"LD_RCE3:race12"), track = "San Fierro Ramp";
			}
		}
	    if(clickedid == raButS) ShowPlayerDialog(playerid,65,DIALOG_STYLE_INPUT,"{03c03c}Настройки гонки","{ffffff}Введите сумму ставки!","Далее","Отмена");
	    if(clickedid == raButC || clickedid == Text:INVALID_TEXT_DRAW) {
		    TextDrawHideForPlayer(playerid,raBox),TextDrawHideForPlayer(playerid,raImg),TextDrawHideForPlayer(playerid,raTrack),TextDrawHideForPlayer(playerid,raDist),TextDrawHideForPlayer(playerid,raBox2),
			TextDrawHideForPlayer(playerid,raLeft),TextDrawHideForPlayer(playerid,raRight),TextDrawHideForPlayer(playerid,raSRace),TextDrawHideForPlayer(playerid,raButS),TextDrawHideForPlayer(playerid,raButC),
			TextDrawHideForPlayer(playerid,raStart),TextDrawHideForPlayer(playerid,raCancel);
			SetPVarInt(playerid,"SelectRace",0), CancelSelectTextDraw(playerid);
		}
	}
    return true;
}

public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
	if(response == EDIT_RESPONSE_FINAL) {
        SetDynamicObjectPos(objectid,x,y,z), SetDynamicObjectRot(objectid,rx,ry,rz);
        if(objectid == atm) {
 			mysql_format(connects, query, 180+1, "INSERT INTO `atm` (`x`, `y`, `z`, `rx`, `ry`, `rz`) VALUES ('%.4f', '%.4f', '%.4f', '%.4f', '%.4f', '%.4f')",x,y,z,rx,ry,rz);
    		mysql_tquery(connects, query, "", "");
		}
		if(objectid == House[Player[playerid][pHouse]][hObject][0]) {
		    House[Player[playerid][pHouse]][sX] = x,House[Player[playerid][pHouse]][sY] = y,House[Player[playerid][pHouse]][sZ] = z,
		    House[Player[playerid][pHouse]][sRX] = rx,House[Player[playerid][pHouse]][sRY] = ry,House[Player[playerid][pHouse]][sRZ] = rz;
			House[Player[playerid][pHouse]][hUpgrade] = 1;
		    SCM(playerid,0x03c03cFF,"Улучшение установлено! Для редактирования объекта используйте: {ffffff}/hedit");
		    format(warehousetext,sizeof(warehousetext),"Сейф\nДенег: %d\nПатроны: %d\nНаркотики: %d",House[Player[playerid][pHouse]][sMoney],House[Player[playerid][pHouse]][sAmmo],House[Player[playerid][pHouse]][sDrugs]);
			House[Player[playerid][pHouse]][sText] = CreateDynamic3DTextLabel(warehousetext, 0x1faee9FF,House[Player[playerid][pHouse]][sX],House[Player[playerid][pHouse]][sY],House[Player[playerid][pHouse]][sZ]+1.2,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,House[Player[playerid][pHouse]][hID],-1,-1,100.0);
		}
		if(objectid == House[Player[playerid][pHouse]][hObject][1]) {
		    House[Player[playerid][pHouse]][wX] = x,House[Player[playerid][pHouse]][wY] = y,House[Player[playerid][pHouse]][wZ] = z,
		    House[Player[playerid][pHouse]][wRX] = rx,House[Player[playerid][pHouse]][wRY] = ry,House[Player[playerid][pHouse]][wRZ] = rz;
		    House[Player[playerid][pHouse]][hUpgrade] = 2;
            SCM(playerid,0x03c03cFF,"Улучшение установлено! Для редактирования объекта используйте: {ffffff}/hedit");
		}
        return true;
    }
    return true;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid,Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ,Float:fRotX, Float:fRotY, Float:fRotZ,Float:fScaleX, Float:fScaleY, Float:fScaleZ ){
    if(response == EDIT_RESPONSE_FINAL) {
		SetPlayerAttachedObject(playerid,index,modelid,boneid,fOffsetX,fOffsetY,fOffsetZ,fRotX,fRotY,fRotZ,fScaleX,fScaleY,fScaleZ);
        printf("SetPlayerAttachedObject(playerid, %d, %d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f);",index,modelid,boneid,fOffsetX,fOffsetY,fOffsetZ,fRotX,fRotY,fRotZ,fScaleX,fScaleY,fScaleZ);
        return true;
	}
	return true;
}

public OnIncomingConnection(playerid, ip_address[], port)
{
      if(!IsPlayerConnected(playerid)) return SetPVarInt(playerid, "IncomingConnects", GetPVarInt(playerid, "IncomingConnects")+1);
      if(GetPVarInt(playerid, "IncomingConnects") == 3) return BlockIpAddress(ip_address, 10800000);
      format(strock,sizeof(strock),"[A] IP Адресс: %s:%d был забанен по подозреванию в DDoS атаке.",ip_address,port);
      SendAdminMessage(0xFF0000FF, strock);
      return true;
}

apublic PlayerTimer() {
    foreach(new playerid : Player) {
		new Float:health, Float:armour, Float:vhealth, str[32];
		#define GPW GetPlayerWeapon(playerid)
	 	new string[22], animlib[16], animname[16];
		SetPVarInt(playerid, "AFK", GetPVarInt(playerid, "AFK")+1);
	 	if(GetPVarInt(playerid, "AFK") > 3) format(string, sizeof(string), "[AFK: %d]", (GetPVarInt(playerid, "AFK")-GetPVarInt(playerid, "AFK")+GetPVarInt(playerid, "AFK"))), SetPlayerChatBubble(playerid, string, 0xFF0000FF, 35.0, 1500);
	  	if(GetPVarInt(playerid, "AFK") > 920 && Player[playerid][pAdmin] == 0) SCM(playerid,COLOR_LIGHTRED,"Вы были кикнуты за долговременное АФК!"), KickEx(playerid);
	  	if(Player[playerid][pMoney] < GetPlayerMoney(playerid) || Player[playerid][pMoney] > GetPlayerMoney(playerid)) ResetPlayerMoney(playerid), GivePlayerMoney(playerid,Player[playerid][pMoney]);
		//
		if(GetPlayerAmmo(playerid) > Player[playerid][Weapon][GetPlayerWeapon(playerid)]) ResetWeapon(playerid);
		if(GetPlayerAmmo(playerid) < Player[playerid][Weapon][GetPlayerWeapon(playerid)]) Player[playerid][Weapon][GetPlayerWeapon(playerid)] = GetPlayerAmmo(playerid);
		//
		GetPlayerArmour(playerid, armour);
		if(Player[playerid][PlayerArmor] < armour) SetPlayerArmour(playerid, Player[playerid][PlayerArmor]);
		else Player[playerid][PlayerArmor] = armour;
		//==== ANTI - CHEATS =======
		if(Player[playerid][pAdmin] < 1 && Player[playerid][PlayerLogged]) {
		    fcor
	 		GetPlayerPos(playerid, x, y, z);
			GetAnimationName(GetPlayerAnimationIndex(playerid), animlib, sizeof(animlib), animname, sizeof(animname));
	        if(strcmp(animlib, "SWIM", true) == 0 && strcmp(animname, "SWIM_crawl", true) == 0 && z > 1 && GetPlayerSpeed(playerid) > 30) SCM(playerid,COLOR_LIGHTRED,"Вы были кикнуты. Опкод: {ffffff}P3T5R1"), KickEx(playerid);
			//
			switch(GPW) { case 9,16,35..39: SCM(playerid,COLOR_LIGHTRED,"Вы были кикнуты. Опкод: {ffffff}P9T1R6"), KickEx(playerid); }
			//
			if(GetPVarInt(playerid,"AirTime") > 0) SetPVarInt(playerid, "AirTime", GetPVarInt(playerid,"AirTime")-1);
	  		if(GetPVarInt(playerid,"AirTime") == 0 && floatround(GetPlayerDistanceFromPoint(playerid,GetPVarFloat(playerid,"AX"),GetPVarFloat(playerid,"AY"),GetPVarFloat(playerid,"AZ"))) > 19  && GetPVarInt(playerid,"AC_RTime") < gettime()) {
	   			if((GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && floatround(GetPlayerDistanceFromPoint(playerid,GetPVarFloat(playerid,"AX"),GetPVarFloat(playerid,"AY"),GetPVarFloat(playerid,"AZ"))) > 20) ||
				   ((GetPlayerState(playerid) == PLAYER_STATE_DRIVER && floatround(GetPlayerDistanceFromPoint(playerid,GetPVarFloat(playerid,"AX"),GetPVarFloat(playerid,"AY"),GetPVarFloat(playerid,"AZ"))) > 50 &&
				   GetVehicleSpeed(GetPlayerVehicleID(playerid)) == 0)))  format(strock,54,"[A] %s{%d} возможно AirBreak",Name(playerid),playerid), SendAdminMessage(0xFF0000FF,strock);
				SetPVarInt(playerid,"AC_RTime",gettime()+15);
			}
			SetPVarFloat(playerid,"AX",x),SetPVarFloat(playerid,"AY",y),SetPVarFloat(playerid,"AZ",z);
			if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK) {
			    format(strock, sizeof(strock), "%s был забанен античитом на %i дней. Причина: Чит", Name(playerid), (15*86400-43200));
				SendClientMessageToAll(COLOR_LIGHTRED,strock);
				Player[playerid][pBan] = gettime() + 15*86400-43200;
				KickEx(playerid);
			}
		}
		//================================
	    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			if(GetPVarInt(playerid,"DrunkDriving") == 1) SetPlayerDrunkLevel(playerid,6000);
			UpdateSpeed(playerid);
		}
	    if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING && Player[playerid][pAdmin] > 2) {
		 	GetPlayerHealth(GetPVarInt(playerid,"ReconID"),health),GetPlayerArmour(GetPVarInt(playerid,"ReconID"),armour);
       		TextDrawSetPreviewModel(rmodel[playerid],GetPlayerSkin(GetPVarInt(playerid,"ReconID")));
	   		format(str,sizeof(str),"%s (%d)",Name(GetPVarInt(playerid,"ReconID")),GetPVarInt(playerid,"ReconID"));
			TextDrawSetString(rname[playerid],str);
			format(str,17,"Health: %.0f",health);
			TextDrawSetString(rhealth[playerid],str);
			format(str,17,"Armour: %.0f",armour);
			TextDrawSetString(rarmour[playerid],str);
			format(str,10,"Ping: %d",GetPlayerPing(GetPVarInt(playerid,"ReconID")));
		 	TextDrawSetString(rping[playerid],str);
		 	format(str,22,"Money: %d",Player[GetPVarInt(playerid,"ReconID")][pMoney]);
	 		TextDrawSetString(rmoney[playerid],str);
		 	format(str,10,"Speed: %d",GetPlayerSpeed(GetPVarInt(playerid,"ReconID")));
		 	TextDrawSetString(rspeed[playerid],str);
			format(str,22,"R-IP: %s",Player[GetPVarInt(playerid,"ReconID")][pIP]);
		 	TextDrawSetString(rrip[playerid],str);
		 	format(str,20,"IP: %s",Ip(GetPVarInt(playerid,"ReconID")));
		 	TextDrawSetString(rip[playerid],str);
		 	if(GetPlayerState(GetPVarInt(playerid,"ReconID")) == PLAYER_STATE_DRIVER) {
		 	    GetVehicleHealth(GetPlayerVehicleID(GetPVarInt(playerid,"ReconID")),vhealth);
 				TextDrawSetPreviewModel(rvmodel[playerid],GetVehicleModel(GetPlayerVehicleID(GetPVarInt(playerid,"ReconID"))));
			 	TextDrawSetString(rvname[playerid],VehicleNames[GetVehicleModel(GetPlayerVehicleID(GetPVarInt(playerid,"ReconID")))-400]);
			 	format(str,16,"Health: %.0f",vhealth);
			 	TextDrawSetString(rvhealth[playerid],str);
			 	format(str,0,"Speed: %d",GetVehicleSpeed(GetPlayerVehicleID(GetPVarInt(playerid,"ReconID"))));
			 	TextDrawSetString(rvspeed[playerid],str);
		 	}
	    }
     	if(Player[playerid][pWanted] > 7) Player[playerid][pWanted]--;
     	if(Player[playerid][pWanted] == 7) {
			Player[playerid][pWanted] = 0;
     	    if(IsPlayerInRangeOfPoint(playerid,10.0,265.0295,77.6146,1001.0391) && GetPlayerInterior(playerid) == 6) SetPlayerSkin(playerid, (Player[playerid][pFraction][1] == 0) ? Player[playerid][pModel][0] : Player[playerid][pModel][1]),
			 SetPlayerInterior(playerid,0), SetPlayerVirtualWorld(playerid,0), AC_SetPlayerPos(playerid,1544.5674,-1675.5991,13.5587), SetPlayerFacingAngle(playerid,92.0004), SetCameraBehindPlayer(playerid), SCM(playerid,0x03c03cFF,"Вы отбыли свой срок в тюрьме!");
     	}
		if(GetPVarInt(playerid,"Called") > 0) {
		    if(GetPVarInt(playerid,"Called") == 2) {
		        SetPVarInt(playerid,"CallTime",GetPVarInt(playerid,"CallTime")+1);
         		if(GetPVarInt(playerid,"CallTime") == 3) {
				    format(strock,sizeof(strock),"[T] Входящий вызов от номера %d. ( /t ), чтобы принять вызов и ( /h ) чтобы отклонить.",Player[GetPVarInt(playerid,"CalledID")][pPhone][0]);
				    SCM(playerid,0xFFEE00FF,strock);
				    SetPVarInt(playerid,"CallTime",0);
			}   }
	      	if(GetPVarInt(playerid,"Called") == 3) {
	     	    if(Player[playerid][pPhone][1] < 1) {
  	        		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE),  SetPlayerSpecialAction(GetPVarInt(playerid,"CalledID"),SPECIAL_ACTION_STOPUSECELLPHONE);
    				SCM(GetPVarInt(playerid,"CalledID"),0xFFEE00FF,"[T] Абонент положил трубку."), SCM(GetPVarInt(GetPVarInt(playerid,"CalledID"),"CalledID"),0xFFEE00FF,"[T] Абонент положил трубку.");
    				SetPVarInt(GetPVarInt(playerid,"CalledID"),"Called",0), SetPVarInt(playerid,"Called",0), SetPVarInt(playerid,"CalledID",INVALID_PLAYER_ID), SetPVarInt(GetPVarInt(playerid,"CalledID"),"CalledID",INVALID_PLAYER_ID);
	     	    }
			 	SetPVarInt(playerid,"CallTimer",GetPVarInt(playerid,"CallTimer")+1), Player[playerid][pPhone][1]--;
			}
		}
		if(GetPVarInt(playerid,"DrugTime") > 1) SetPVarInt(playerid,"DrugTime",GetPVarInt(playerid,"DrugTime")-1);
		if(GetPVarInt(playerid,"DrugTime") == 1) SetPVarInt(playerid,"DrugTime",0), SetPlayerDrunkLevel (playerid, 0), SetPlayerWeather(playerid, CurrentWeather);
		if(GetPVarInt(playerid,"FBIsp") == 1) {
      		fcor
			GetPlayerPos(GetPVarInt(playerid,"FBIspID"),x,y,z), InterpolateCameraPos(playerid,x,y,z+35.0,x,y,z+35.0,300,CAMERA_MOVE), InterpolateCameraLookAt(playerid,x,y,z,x,y,z,300,CAMERA_MOVE);
		}
	}
	#undef GPW
    return true;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) {
    if(22 < weaponid < 32) Player[playerid][Skill][weaponid-22]++;
	if(weaponid == 38) return false;
	return true;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {
    if(Player[playerid][pAdmin] < 1) return true;
    SetPlayerInterior(playerid, 0), SetPlayerVirtualWorld(playerid, 0);
    if (GetPlayerState(playerid) == 2) SetVehiclePos(GetPlayerVehicleID(playerid), fX, fY, fZ);
    else AC_SetPlayerPos(playerid, fX, fY, fZ);
    return true;
}

public OnPlayerEnterDynamicArea(playerid,areaid)
{
    if(areaid == Area) PlayAudioStreamForPlayer(playerid,"http://cheery-rp.ru/sound1.mp3",222.0781,1930.0691,28.3515,350,true);
    if(areaid == Truck) {
        if(GetPVarInt(playerid,"TruckJob") == 1 && (GetPlayerVehicleID(playerid) >= truckcar[0] && GetPlayerVehicleID(playerid) <= truckcar[1]) && GetPVarInt(playerid,"TruckHaul") == 0) {
            ShowPlayerDialog(playerid,48,DIALOG_STYLE_LIST,"{1faee9}Возможные перевозки","Сырье\nНефть\nПродукты\nЗерно","Выбор","Отмена");
	}   }
	if(areaid == Area51 && (!PlayerLaw(playerid) && GetPlayerVirtualWorld(playerid) == 0)) Player[playerid][pWanted] = ((4 + Player[playerid][pWanted]) > 6) ? 6 : (Player[playerid][pWanted]+4), SetPlayerWantedLevel(playerid,Player[playerid][pWanted]), SCM(playerid,0xFF0000FF,"Вы проникли на секретную базу, вас увидели камеры!");
    return true;
}

public OnPlayerLeaveDynamicArea(playerid,areaid)
{
    if(areaid == Area) StopAudioStreamForPlayer(playerid);
    if((areaid >= Repair[0] && areaid <= Repair[9]) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		for(new i; i < sizeof(Repair); i++) { Player[playerid][pMoney] -= 400; break; }
        for(new i = 0; i <= Businesses; i++) {
			if(IsPlayerInRangeOfPoint(playerid,20.0,Business[i][bX], Business[i][bY], Business[i][bZ])) Business[i][bIncome] += 200;
			break;
	}   }
    return true;
}

public OnPlayerGiveDamage(playerid, damagedid, Float: amount, weaponid, bodypart){
	if(bodypart == 9) SetPlayerHealth(damagedid,0);
    if(PlayerCF(playerid) && weaponid == 3 && !PlayerLaw(damagedid)) {
    	if(GetPVarInt(playerid,"Tazer") > gettime()) return true;
    	TogglePlayerControllable(damagedid,0);
	    ApplyAnimation(damagedid,"PED","KO_skid_front",4.1,0,1,1,1,0), SetTimerEx("Carry", 5000, 0, "dd", damagedid, 2);
	    SetPlayerChatBubble(damagedid, "оглушен", 0xBA4A4AFF, 35.0, 5000);
	    SCM(damagedid,0xBA4A4AFF,"Вы были оглушены!");
	    SetPVarInt(playerid,"Tazer",gettime()+8);
	}
	return true;
}
//Мод был скачан с сайта YourGame.su
