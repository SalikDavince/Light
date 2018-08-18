CMD:alogin(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	if(Player[playerid][pAdmin] < 1) return true;
	if(!Player[playerid][Aat]) return ShowPlayerDialog(playerid,6,DIALOG_STYLE_INPUT, "{ff0000}Вход в режим модерирования", "{ff0000}Введите в поле ваш {ffffff}пароль от панели модератора", "Вход", "Отмена");
 	else Player[playerid][Aat] = false, SendClientMessage(playerid, COLOR_GRAD1, "Вы вышли с режима модерирования");
	return true;
}
//alias:alogin("alog");

CMD:admin(playerid, params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
    new arank[8];
    if(Player[playerid][pAdmin] == 0) return true;
	if(sscanf(params, "s[128]",params[0])) return SendClientMessage(playerid, COLOR_WHITE, "Введите: (/a)dmin [сообщение]");
	switch(Player[playerid][pAdmin]) {
		case 5: arank = "[A]";
		case 4: arank = "[A]";
		case 3: arank = "[A]";
		case 2: arank = "[A]";
		case 1: arank = "[A]";
		default: arank = "[A]";
	}
	if(Player[playerid][Aat] == false) return true;
	else format(strock, 145, "%s %s(%d): %s",arank,Name(playerid), playerid,params[0]);
	SendAdminMessage(0xFFD781AA, strock);
	return true;
}
alias:admin("a");

CMD:m(playerid,params[]) {
	if(!Player[playerid][PlayerLogged] || !PlayerLaw(playerid)) return true;
	if(sscanf(params,"s[128]",params[0])) return SCM(playerid,0xFFFFFFFF,"Введите:{1faee9} /m(egaphone) [текст]");
	if(GetPlayerVehicleID(playerid) >= 66 && GetPlayerVehicleID(playerid) <= 85) {
	    SetPlayerChatBubble(playerid, "объявляет в рупор", 0x34c924FF, 20.0, 7000);
    	
		format(strock, sizeof(strock), "[M] %s: %s", Name(playerid), params[0]);
		//SendClientsMessage(30.0, playerid, strock, 0x00CA18FF,0x00CA18FF,0x00CA18FF);
		ProxDetector(playerid, 30.0, 0x00CA18FF, strock);
	}
	else SCM(playerid,0xFFFFFFFF,"Вы {1faee9}в служебном транспорте!");
	return true;
}

CMD:makemoderator(playerid, params[]) {
    if(Player[playerid][pAdmin] < 6 || Player[playerid][Aat] == false || !Player[playerid][PlayerLogged]) return true;
	if(sscanf(params, "u",params[0])) return SendClientMessage(playerid, COLOR_GRAD2, "Введите: /makemoderator [playerid]");
	if(!IsPlayerConnected(params[0]) || params[0] == playerid || Player[playerid][pAdmin] < Player[params[0]][pAdmin]) return true;
	if(Player[params[0]][pAdmin] > 0) {
		Player[params[0]][pAdmin] = 0;
		printf(" %s снял %s с поста модератора.",Name(playerid),Name(params[0]));
		format(strock, 54, "Вы сняли %s с поста модератора",Name(params[0]));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strock);
	}
	else {
		Player[params[0]][pAdmin] = 1;
		printf(" %s назначил на пост модератора %s.",Name(playerid),Name(params[0]));
		format(strock, 50, "Вы назначили %s модератором",Name(params[0]));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strock);
        TogglePlayerControllable(params[0], 0);
 		TextDrawShowForPlayer(params[0],abox);
		TextDrawShowForPlayer(params[0],a1);
		TextDrawShowForPlayer(params[0],a2);
		TextDrawShowForPlayer(params[0],a3);
		TextDrawShowForPlayer(params[0],a4);
		TextDrawShowForPlayer(params[0],a5);
		TextDrawShowForPlayer(params[0],a6);
		TextDrawShowForPlayer(params[0],a7);
		TextDrawShowForPlayer(params[0],a8);
		TextDrawShowForPlayer(params[0],a9);
		TextDrawShowForPlayer(params[0],a0);
		TextDrawShowForPlayer(params[0],aenter);
		TextDrawShowForPlayer(params[0],aboxtop);
		TextDrawShowForPlayer(params[0],atext);
		TextDrawShowForPlayer(params[0],ac);
		SelectTextDraw(params[0], 0xFF0000AA);
		SCM(params[0],-1,"{ffffff}Пожалуйста придумайте ваш пароль {03c03c}от панели модератора."), SCM(params[0],-1,"{ffffff}Он должен состоять {ff2400}не менее чем из 6 и не более 16 цифр.");
		Player[params[0]][CreatePassword] = true;
	}
	return true;
}

CMD:setadminpost(playerid,params[]) {
    if(Player[playerid][pAdmin] < 6 || Player[playerid][Aat] == false) return true;
	if(sscanf(params, "ud",params[0],params[1])) return SendClientMessage(playerid, 0xFFFFFFFF, "Используйте: {1faee9}/setadminpost [playerid] [lvl]");
	if(!IsPlayerConnected(params[0]) || params[0] == playerid || Player[playerid][pAdmin] < Player[params[0]][pAdmin]) return true;
	if(Player[params[0]][pAdmin] == 0) return SCM(playerid,0xFFFFFFFF,"Данный человек {1faee9}не является модератором!");
	if(params[1] < 1 || params[1] > 6) return SCM(playerid,0xFFFFFFFF,"Уровень должен быть {1faee9}не менее 1 и не более 6!");
	Player[params[0]][pAdmin] = params[1], Player[params[0]][Aat] = false,
	ShowPlayerDialog(params[0],6,DIALOG_STYLE_INPUT, "{ff0000}Вход в режим модерирования", "{ff0000}Введите в поле ваш {ffffff}пароль от панели модератора", "Вход", "Отмена");
	SCM(playerid,0xFFFFFFFF,"Уровень администрации данного человека {1faee9}изменен!"), SCM(params[0],0xFFFFFFFF,"Ваш уровень администратирования был {1faee9}изменен!");
	return true;
}

CMD:gmx(playerid,params[]) {
	if(Player[playerid][pAdmin] < 5 || Player[playerid][Aat] == false) return true;
	GameTextForAll("~r~Restart", 5000,5), GameModeExit();
	return true;
}

CMD:skin(playerid,params[]) {
	if(Player[playerid][pAdmin] < 1 || Player[playerid][Aat] == false) return true;
	if(sscanf(params,"ud",params[0],params[1])) return SendClientMessage(playerid,-1,"Введите: /skin [id] [номер скина]");
	if(params[1] < 1 || params[1] > 299) return true;
	Player[params[0]][pModel][0] = params[1];
	SetPlayerSkin(params[0],params[1]);
	return true;
}

CMD:goto(playerid, params[]) {
    if(Player[playerid][pAdmin] < 2 || Player[playerid][Aat] == false) return true;
	if(sscanf(params, "u",params[0])) return SendClientMessage(playerid, COLOR_WHITE, "Введите: /g(oto) [id]");
	fcor
	if(!IsPlayerConnected(params[0])) return true;
	if(GetPlayerState(params[0]) != 1 && GetPlayerState(params[0]) != 2 && GetPlayerState(params[0]) != 3) return SendClientMessage(playerid, COLOR_GRAD1, "Игрок не вступил в игру!");
	GetPlayerPos(params[0], x, y, z);
	if (GetPlayerState(playerid) == 2) SetVehiclePos(GetPlayerVehicleID(playerid), x, y+4, z), putPlayerInVehicle(playerid,GetPlayerVehicleID(playerid),0);
	AC_SetPlayerPos(playerid, x, y+2, z);
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(params[0]));
	SetPlayerInterior(playerid, GetPlayerInterior(params[0]));
	SendClientMessage(playerid, 0x03c03cFF, "Вы были телепортированы!");
	return true;
}

CMD:gethere(playerid, params[]) {
    if(Player[playerid][pAdmin] < 2 || Player[playerid][Aat] == false) return true;
	if(sscanf(params, "u",params[0])) return SendClientMessage(playerid, COLOR_WHITE, "Введите: /gethere [id]");
	if(!IsPlayerConnected(params[0])) return true;
	fcor
	GetPlayerPos(playerid, x, y, z);
	SetPlayerInterior(params[0],GetPlayerInterior(playerid));
	SetPlayerVirtualWorld(params[0],GetPlayerVirtualWorld(playerid));
	if(GetPlayerState(params[0]) == PLAYER_STATE_DRIVER) SetVehiclePos(GetPlayerVehicleID(params[0]), x, y+4, z), putPlayerInVehicle(params[0],GetPlayerVehicleID(params[0]),0);
	AC_SetPlayerPos(params[0],x, y+2, z);
	SendClientMessage(params[0], 0x03c03cFF, "Вы были телепортированы администрацией!");
	return true;
}

CMD:givegun(playerid, params[]) {
    if(Player[playerid][pAdmin] < 3 || Player[playerid][Aat] == false) return true;
    if(sscanf(params, "udd",params[0],params[1],params[2])) return SendClientMessage(playerid, COLOR_WHITE, "Введите: /givegun [id] [id оружия] [патроны]");
	if(params[2] < 1 || params[2] > 9999) return SendClientMessage(playerid, COLOR_GRAD1, "Нельзя меньше 1 или больше 9999 патронов!");
	GiveWeapon(params[0],params[1],params[2]);
	SendClientMessage(playerid, 0x03c03cFF, "Оружие было выдано!");
	return true;
}

CMD:givemoney(playerid, params[])
{
    if(Player[playerid][pAdmin] < 5 || Player[playerid][Aat] == false) return true;
    if(sscanf(params, "ud",params[0],params[1])) return SendClientMessage(playerid, COLOR_WHITE, "Введите: /givemoney [id] [сумма] ");
	Player[params[0]][pMoney] += params[1];
	GivePlayerMoney(params[0],params[1]);
	SendClientMessage(playerid, COLOR_GRAD1, "Деньги выданы.");
	return true;
}

CMD:veh(playerid, params[]) {
	if(Player[playerid][pAdmin] < 3 || Player[playerid][Aat] == false) return true;
	if(sscanf(params, "ddd",params[0],params[1],params[2])) return SendClientMessage(playerid, COLOR_WHITE, "Введите: /veh [id авто] [1 цвет] [2 цвет]");
	if(params[0] < 400 || params[0] > 611) return true;
    fcor
	new v;
	GetPlayerPos(playerid, x,y,z);
	v = CreateVehicle(params[0], x,y,z, 0.0, params[1], params[2], 600), v = 200;
	putPlayerInVehicle(playerid,v,0), SetVehicleParamsEx(v, VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective), VUP<v:engines>;
	return true;
}

CMD:engine(playerid,params[]){
	if(!Player[playerid][PlayerLogged]) return true;
	#define vehicleid GetPlayerVehicleID(playerid)
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return true;
	new Float:health;
	GetVehicleHealth(vehicleid,health);
    if(health < 301.0) return GameTextForPlayer(playerid, "~r~ENGINE BROKEN", 2000, 3);
    if(Fuel[vehicleid] < 1) return GameTextForPlayer(playerid, "~r~FUEL END", 2000, 3);
    GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
 	SetVehicleParamsEx(vehicleid, (!VVB<vehicleid:engines>) ? (VEHICLE_PARAMS_ON) : (VEHICLE_PARAMS_OFF) ,lights,alarm,doors,bonnet,boot,objective);
 	VXOR<vehicleid:engines>;
    PlayerTextDrawSetString(playerid,sengine[playerid], (VVB<vehicleid:engines>) ? ("~g~ENGINE") : ("~r~ENGINE"));
 	#undef  vehicleid
	return true;
}

CMD:lights(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
    #define vehicleid GetPlayerVehicleID(playerid)
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return true;
    GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
 	SetVehicleParamsEx(vehicleid,engine, (!VVB<vehicleid:light>) ? (VEHICLE_PARAMS_ON) : (VEHICLE_PARAMS_OFF) ,alarm,doors,bonnet,boot,objective);
 	VXOR<vehicleid:light>;
	PlayerTextDrawSetString(playerid,slights[playerid], (VVB<vehicleid:light>) ? ("~g~LIGHTS") : ("~r~LIGHTS"));
 	#undef  vehicleid
	return true;
}

CMD:buyhome(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	if(Player[playerid][pHouse] != 9999) return SCM(playerid,0xFFFFFFFF,"На данный момент на сервере можно иметь только один дом!");
 	for(new h = 0 ; h <= Houses; h++) {
  		if(IsPlayerInRangeOfPoint(playerid,3.0,House[h][hX],House[h][hY],House[h][hZ])) {
	    	if(Player[playerid][pMoney] < House[h][hPrice]) return SCM(playerid,0xFFFFFFFF,"У вас недостаточно денег для покупки дома!");
	     	if(strcmp(House[h][hOwner],"None",true)!=0) return SCM(playerid,0xFFFFFFFF,"Данный дом уже имеет владельца!");
	       	strmid(House[h][hOwner],Name(playerid),0,24,24), Player[playerid][pHouse] = h, Player[playerid][pMoney] -= House[h][hPrice];
            SetPlayerInterior(playerid,Ints[House[Player[playerid][pHouse]][hInt]][hiInt]);
   			AC_SetPlayerPos(playerid,Ints[House[Player[playerid][pHouse]][hInt]][hiX],Ints[House[Player[playerid][pHouse]][hInt]][hiY],Ints[House[Player[playerid][pHouse]][hInt]][hiZ]), SetPlayerVirtualWorld(playerid,House[Player[playerid][pHouse]][hID]);
			ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{03c03c}Покупка дома","{ffffff}Поздравляем вас с успешной покупкой дома!\nНе забывайте вовремя оплачивать коммунальные услуги в банке.\nКаждый час со счета вашего дома взымается: {FFC8C8}150$\n\
	        {AC7575}\n\nПри неуплате больше 3000 вы будите автоматически выселены из дома!","Ок","");
	        SaveHouse(h), DestroyDynamicPickup(House[h][hPickup]), DestroyDynamicMapIcon(House[h][hIcon]);
	        House[h][hIcon] = CreateDynamicMapIcon(House[h][hX],House[h][hY],House[h][hZ],32,COLOR_WHITE,0,-1,-1);
			House[h][hPickup] = CreateDynamicPickup(1272,1,House[h][hX],House[h][hY],House[h][hZ]);
			House[h][hCommunal] = 0;
			if(Player[playerid][pCar][0] != -1) {
				Player[playerid][PlayerCar] = CreateVehicle(Player[playerid][pCar][0],896.8502, (!PlayerInBike(Player[playerid][pCar][0])) ? (-358.9444) : (-356.3848) ,2177.2405,89.8153,Player[playerid][pCar][1],Player[playerid][pCar][2],86400);
        		SetVehicleVirtualWorld(Player[playerid][PlayerCar],House[Player[playerid][pHouse]][hID]);
	}	}   }
 	return true;
}

CMD:sellhome(playerid, params[]) {
	if(Player[playerid][pHouse] == 9999 || strcmp(Name(playerid), House[Player[playerid][pHouse]][hOwner], true) == -1) return true;
    if(!IsPlayerInRangeOfPoint(playerid,3.0,House[Player[playerid][pHouse]][hX], House[Player[playerid][pHouse]][hY], House[Player[playerid][pHouse]][hZ])) return SCM(playerid,0xFFFFFFFF,"Необходимо находиться {1faee9}возле дома!");
	strmid(House[Player[playerid][pHouse]][hOwner], "None", 0, strlen("None"), 24);
	Player[playerid][pMoney] += House[Player[playerid][pHouse]][hPrice]/2;
	#define h	Player[playerid][pHouse]
	DestroyDynamicPickup(House[h][hPickup]), DestroyDynamicMapIcon(House[h][hIcon]);
	House[h][hIcon] = CreateDynamicMapIcon(House[h][hX],House[h][hY],House[h][hZ],31,COLOR_WHITE,0,-1,-1);
	House[h][hPickup] = CreateDynamicPickup(1273,1,House[h][hX],House[h][hY],House[h][hZ]);
    Player[playerid][pMoney] += House[h][sMoney], Player[playerid][pAmmo] += House[h][sAmmo], Player[playerid][pDrugs] += House[h][sDrugs];
	House[h][hUpgrade] = 0, House[h][sMoney] = 0, House[h][sAmmo] = 0, House[h][sDrugs] = 0;
	House[h][hCommunal] = 0;
	if(Player[playerid][pCar][0] != -1) DestroyVehicle(Player[playerid][PlayerCar]);
	Player[playerid][pHouse] = 9999;
	SCM(playerid,0xAC7575FF,"Вы успешно продали ваш дом!");
	SaveHouse(h), SaveAccount(playerid);
	#undef h
	return true;
}

CMD:changehome(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	new string[90+1];
    if(Player[playerid][pHouse] == 9999) return true;
    if(sscanf(params,"ud",params[0],params[1])) return SCM(playerid,-1,"Введите: /changehome [id] [цена (не более 30% от цены дома)]");
    if(!IsPlayerInRangeOfPoint(playerid,3.0,House[Player[playerid][pHouse]][hX], House[Player[playerid][pHouse]][hY], House[Player[playerid][pHouse]][hZ])) return SCM(playerid,0xFFFFFFFF,"Необходимо находиться возле дома!");
    if(!IsPlayerInRangeOfPoint(params[0],3.0,House[Player[playerid][pHouse]][hX], House[Player[playerid][pHouse]][hY], House[Player[playerid][pHouse]][hZ])) return SCM(playerid,0xFFFFFFFF,"Необходимо находиться возле дома!");
	if(Player[params[0]][pHouse] != 9999) return SCM(playerid,-1,"Данный человек уже владеет домом!");
	if(params[1] > House[Player[playerid][pHouse]][hPrice] + ((House[Player[playerid][pHouse]][hPrice]*30)/100)) return true;
	if(Player[params[0]][pMoney] < params[1]) return SCM(playerid,-1,"Кажется, у покупателя не совсем хватает денег на эту покупку.");
	format(string,sizeof(string),"{ffffff}Вы действительно хотите приобрести дом {ff0000}№%d {ffffff}за {cc7722}%d$",House[Player[playerid][pHouse]][hID],params[1]);
	ShowPlayerDialog(params[0],9,DIALOG_STYLE_MSGBOX,"{ffffff}Покупка дома",string,"Да","Нет");
	SCM(playerid,-1,"Вы предложили покупателю оформить договор {03c03c}о покупке дома");
	SetPVarInt(params[0],"HouseSeller",playerid), SetPVarInt(params[0],"HousePrice",params[1]);
	return true;
}

CMD:buybiz(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	if(Player[playerid][pBusiness] != 9999) return SCM(playerid,0xFFFFFFFF,"На данный момент на сервере можно иметь только один бизнес!");
 	for(new b = 0 ; b <= Businesses; b++) {
  		if(IsPlayerInRangeOfPoint(playerid,3.0,Business[b][bX],Business[b][bY],Business[b][bZ])) {
	    	if(Player[playerid][pMoney] < Business[b][bPrice]) return SCM(playerid,0xFFFFFFFF,"У вас недостаточно денег для покупки бизнеса!");
	     	if(strcmp(Business[b][bOwner],"None",true)!=0) return SCM(playerid,0xFFFFFFFF,"Данный бизнес уже имеет владельца!");
	       	strmid(Business[b][bOwner],Name(playerid),0,24,24), Player[playerid][pBusiness] = b, Player[playerid][pMoney] -= Business[b][bPrice];
	       	Business[b][bCommunal] = 0;
	       	SetPVarInt(playerid,"GetPickup",gettime()+3);
	        ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{03c03c}Покупка бизнеса","{ffffff}Поздравляем вас с успешной покупкой бизнеса!\nНе забывайте вовремя оплачивать коммунальные услуги в банке.\nКаждый час со счета вашего бизнеса взымается: {FFC8C8}250$\n\
	        {AC7575}\n\nПри неуплате больше 3000 ваш бизнес будет автоматически продан!","Ок","");
	        SaveBusiness(b);
	        format(strock,101,"Бизнес: {1faee9}%s\n{ffffff}Владелец: {1faee9}%s",Business[Player[playerid][pBusiness]][bName],Business[Player[playerid][pBusiness]][bOwner]);
			UpdateDynamic3DTextLabelText(Business[Player[playerid][pBusiness]][bText],0xFFFFFFFF,strock);
			break;
	}   }
 	return true;
}

CMD:sellbiz(playerid, params[]) {
	if(Player[playerid][pBusiness] == 9999 || strcmp(Name(playerid), Business[Player[playerid][pBusiness]][bOwner], true) == -1) return true;
    if(!IsPlayerInRangeOfPoint(playerid,5.0,Business[Player[playerid][pBusiness]][bX], Business[Player[playerid][pBusiness]][bY], Business[Player[playerid][pBusiness]][bZ])) return SCM(playerid,0xFFFFFFFF,"Необходимо находиться возле бизнеса!");
	strmid(Business[Player[playerid][pBusiness]][bOwner], "None", 0, strlen("None"), 24);
	Player[playerid][pMoney] += Business[Player[playerid][pBusiness]][bPrice]/2; SaveBusiness(Player[playerid][pBusiness]);
	Player[playerid][pMoney] += Business[Player[playerid][pBusiness]][bIncome], Business[Player[playerid][pBusiness]][bCommunal] = 0;
	SaveBusiness(Player[playerid][pBusiness]);
	SCM(playerid,0xAC7575FF,"Вы успешно продали ваш бизнес!");
	format(strock,101,"Бизнес: {1faee9}%s\n{ffffff}Владелец: {1faee9}%s",Business[Player[playerid][pBusiness]][bName],Business[Player[playerid][pBusiness]][bOwner]);
	UpdateDynamic3DTextLabelText(Business[Player[playerid][pBusiness]][bText],0xFFFFFFFF,strock);
	Player[playerid][pBusiness] = 9999;
	return true;
}

CMD:changebiz(playerid,params[]) {
	new string[90+1];
    if(Player[playerid][pBusiness] == 9999) return true;
    if(sscanf(params,"ud",params[0],params[1])) return SCM(playerid,-1,"Введите: /changebiz [id] [цена (не более 30% от цены бизнеса)]");
    if(!IsPlayerInRangeOfPoint(playerid,5.0,Business[Player[playerid][pBusiness]][bX], Business[Player[playerid][pBusiness]][bY], Business[Player[playerid][pBusiness]][bZ])) return SCM(playerid,0xFFFFFFFF,"Необходимо находиться возле бизнеса!");
    if(!IsPlayerInRangeOfPoint(params[0],5.0,Business[Player[playerid][pBusiness]][bX], Business[Player[playerid][pBusiness]][bY], Business[Player[playerid][pBusiness]][bZ])) return SCM(playerid,0xFFFFFFFF,"Покупателю необходимо находиться возле бизнеса!");
	if(Player[params[0]][pBusiness] != 9999) return SCM(playerid,-1,"Данный человек уже владеет бизнесом!");
	if(params[1] > Business[Player[playerid][pBusiness]][bPrice] + ((Business[Player[playerid][pBusiness]][bPrice]*30)/100)) return true;
	if(Player[params[0]][pMoney] < params[1]) return SCM(playerid,-1,"Кажется, у покупателя не совсем хватает денег на эту покупку.");
	format(string,sizeof(string),"{ffffff}Вы действительно хотите приобрести бизнес {ff0000}№%s {ffffff}за {cc7722}%d$",Business[Player[playerid][pBusiness]][bName],params[1]);
	ShowPlayerDialog(params[0],22,DIALOG_STYLE_MSGBOX,"{ffffff}Покупка Бизнеса",string,"Да","Нет");
	SCM(playerid,-1,"Вы предложили покупателю оформить договор {03c03c}о покупке бизнеса");
	SetPVarInt(params[0],"BusinessSeller",playerid), SetPVarInt(params[0],"BusinessPrice",params[1]);
	return true;
}

CMD:sellcar(playerid, params[]) {
	if(Player[playerid][pHouse] == 9999 || Player[playerid][pCar][0] == -1) return true;
    if(!IsPlayerInRangeOfPoint(playerid,25.0,542.3050,-1293.9307,17.2422)) return SCM(playerid,0xAC7575FF,"Необходимо находиться возле автосалона!");
	SCM(playerid,0xAC7575FF,"Вы успешно продали ваш автомобиль!");
	Player[playerid][pCar][0] = -1, DestroyVehicle(Player[playerid][PlayerCar]);
	return true;
}

CMD:mhcp(playerid, params[])
{
    if(Player[playerid][pAdmin] < 5 || Player[playerid][Aat] == false) return true;
	if(sscanf(params, "d",params[0])) return SendClientMessage(playerid, COLOR_WHITE, "Введите: /mhcp [№ дома]");
	new Float: x, Float:y, Float:z,Float:a;
	GetPlayerPos(playerid, x, y, z), GetPlayerFacingAngle(playerid,a);
	House[params[0]][cX] = x, House[params[0]][cY]= y, House[params[0]][cZ] = z, House[params[0]][cA] = a;
	SendClientMessage(playerid, COLOR_WHITE, "Координаты для домашнего автомобиля установлены!");
	SaveHouse(params[0]);
	return true;
}

CMD:mbbp(playerid, params[])
{
    if(Player[playerid][pAdmin] < 5 || Player[playerid][Aat] == false) return true;
	if(sscanf(params, "d",params[0])) return SendClientMessage(playerid, COLOR_WHITE, "Введите: /mbbp [ID @бизнеса]");
	new Float: x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	Business[params[0]][bPX] = x, Business[params[0]][bPY]= y, Business[params[0]][bPZ] = z;
	SendClientMessage(playerid, COLOR_WHITE, "Координаты для пикапа покупки товара в бизнесе установлены!");
	SaveBusiness(params[0]);
	return true;
}

CMD:mbip(playerid, params[])
{
    if(Player[playerid][pAdmin] < 5 || Player[playerid][Aat] == false) return true;
	if(sscanf(params, "d",params[0])) return SendClientMessage(playerid, COLOR_WHITE, "Введите: /mbip [ID @бизнеса]");
	new Float: x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	Business[params[0]][bIX] = x, Business[params[0]][bIY]= y, Business[params[0]][bIZ] = z;
	SendClientMessage(playerid, COLOR_WHITE, "Координаты для пикапа в интерьере!");
	SaveBusiness(params[0]);
	return true;
}

CMD:hmenu(playerid,params[]) if(Player[playerid][pHouse] != 9999) ShowPlayerDialog(playerid,10,DIALOG_STYLE_LIST,"{03c03c}Меню дома","{03c03c}Открыть{ffffff}/{ff2400}Закрыть {ffffff}дверь\nСтатистика дома\nУлучшения дома\nЖильцы","Выбор","Отмена");

CMD:object(playerid,params[]) {
	if(Player[playerid][pAdmin] < 3 || Player[playerid][Aat] == false) return true;
	fcor
	GetPlayerPos(playerid,x,y,z);
	if(sscanf(params,"d",params[0])) return SCM(playerid,COLOR_WHITE,"Введите: /object [id объекта]");
	objects[cobjects] = CreateDynamicObject(params[0],x+0.5,y+0.5,z,0.0,0.0,0.0);
	EditDynamicObject(playerid,objects[cobjects]);
	cobjects++;
	return true;
}

CMD:deleteobject(playerid,params[]) {
    if(Player[playerid][pAdmin] < 3 || Player[playerid][Aat] == false) return true;
	DestroyDynamicObject(objects[cobjects]);
	cobjects--;
	return true;
}

CMD:playerobject(playerid,params[]) {
	if(Player[playerid][pAdmin] < 2 || Player[playerid][Aat] == false) return true;
	if(sscanf(params,"uddd",params[0],params[1],params[2],params[3])) return SCM(playerid,COLOR_WHITE,"Введите: /playerobject [id игрока] [индекс] [id объекта] [часть тела]");
	if(params[3] <= 0 || params[3] > 18) return true;
	RemovePlayerAttachedObject(params[0],params[1]);
	SetPlayerAttachedObject(params[0],params[1],params[2],params[3],0.0,0.0,0.0,0.0,0.0,0.0);
	EditAttachedObject(params[0],params[1]);
	return true;
}


CMD:removeplayerobject(playerid,params[]) {
	if(!Player[playerid][PlayerLogged] || Player[playerid][pAdmin] < 2 || Player[playerid][Aat] == false) return true;
	if(sscanf(params,"u",params[0])) return SCM(playerid,COLOR_WHITE,"");
	for(new i; i < 20; i++) RemovePlayerAttachedObject(params[0],i);
	return true;
}
alias:removeplayerobject("rpo");

CMD:me(playerid, params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	if(Player[playerid][pMute] > gettime()) return SCM(playerid,0xFFFFFFFF,"У вас {1faee9}бан чата!");
	if(sscanf(params, "s[128]", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "Введите: /me [действие]");
	
	format(strock, MAX_PLAYER_NAME+135, "%s %s", Name(playerid), params[0]);
	//SendClientsMessage(30.0, playerid, strock, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	ProxDetector(playerid, 30.0, COLOR_PURPLE, strock);
	
	SetPlayerChatBubble(playerid,params[0],COLOR_PURPLE,30.0,10000);
	return true;
}

CMD:do(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	if(Player[playerid][pMute] > gettime()) return SCM(playerid,0xFFFFFFFF,"У вас {1faee9}бан чата!");
 	if(isnull(params)) return SendClientMessage(playerid, COLOR_GRAD2, "Используйте: /do [действие]");
    
	format(strock, sizeof(strock), "%s %s", params, Name(playerid));
    //SendClientsMessage(30.0, playerid, strock, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	ProxDetector(playerid, 30.0, COLOR_PURPLE, strock);
    
	return true;
}

CMD:try(playerid,params[]) {
    if(!Player[playerid][PlayerLogged]) return true;
    if(Player[playerid][pMute] > gettime()) return SCM(playerid,0xFFFFFFFF,"У вас {1faee9}бан чата!");
   	new temptryrand = random(2);
  	if(isnull(params)) return SendClientMessage(playerid, COLOR_GRAD2, "Используйте: /try [действие]");
  	
	format(strock, sizeof(strock), (temptryrand == 1) ? ("%s %s | {34c924}Удачно") : ("%s %s | {ff0000}Неудачно") ,Name(playerid), params);
  	SendClientsMessage(30.0, playerid, strock, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	ProxDetector(playerid, 30.0, COLOR_PURPLE, strock);
    
	return true;
}

CMD:time(playerid,params[])
{
	if(!Player[playerid][PlayerLogged]) return true;
	if((Player[playerid][CGR] & (1<<0)) == 0) return SCM(playerid,0xAC7575FF,"У вас нет наручных часов, но вы можете спросить время у прохожих!");
	new mtext[24],year, mounth,day,hour,minuite,second; getdate(year, mounth, day); gettime(hour,minuite,second);
	if(!IsPlayerConnected(playerid)) return true;
  	ApplyAnimation(playerid,"COP_AMBIENT","Coplook_watch",4.1,0,0,0,0,0);
	
   	format(strock, 41, "%s смотрит на часы", Name(playerid));
   	//SendClientsMessage(25.0, playerid, strock, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	ProxDetector(playerid, 25.0, COLOR_PURPLE, strock);
	
   	switch(mounth) {
   	    case 1: mtext = "Января";
   	    case 2: mtext = "Февраля";
        case 3: mtext = "Марта";
        case 4: mtext = "Апреля";
        case 5: mtext = "Мая";
        case 6: mtext = "Июня";
        case 7: mtext = "Июля";
        case 8: mtext = "Августа";
        case 9: mtext = "Сентября";
        case 10: mtext = "Октября";
        case 11: mtext = "Ноября";
        case 12: mtext = "Декабря"; }
    format(strock, 70,"\t{ffffff}Сегодня {1faee9}%d %s\t\n\t{ffffff}%d:%d {1faee9}минут\t", day, mtext, hour, minuite),
	ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{ffffff}Точное время",strock,"Ок","");
    return true;
}

CMD:hp(playerid, params[])
{
    if(Player[playerid][pAdmin] < 1 || Player[playerid][Aat] == false) return true;
	if(IsPlayerInAnyVehicle(playerid)) RepairVehicle(GetPlayerVehicleID(playerid)),SetPlayerHealth(playerid, 100.0), PlayerPlaySound(playerid, 32000, 0.0, 0.0, 0.0);
	SetPlayerHealth(playerid, 100);
	return true;
}

CMD:makeleader(playerid,params[]) {
	if(!Player[playerid][PlayerLogged] || Player[playerid][pAdmin] < 4 || Player[playerid][Aat] == false) return true;
	if(sscanf(params,"ud",params[0],params[1])) return SendClientMessage(playerid,COLOR_LIGHTBLUE,"Введите: /makeleader [id] [Организация]");
	if(!IsPlayerConnected(params[0])) return true;
	if(Player[params[0]][pBankPass] == 0) return SCM(playerid,0xAC7575FF,"У данного человека нет банковского счета!");
	Player[params[0]][pFraction][2] = (params[1] == 11) ? 5 :10; Player[params[0]][pFraction][1] = params[1], Player[params[0]][pFraction][0] = params[1];
	SendClientMessage(playerid,0x1faee9FF,"Игрок назначен контролировать данную организацию!");
	SendClientMessage(params[0],0x1faee9FF,"Вы были назначены контролировать данную организацию!");
	FractionSkin(params[0]), SpawnPlayer(params[0]);
	return true;
}

CMD:makemember(playerid, params[]) {
    if(!Player[playerid][PlayerLogged] || (Player[playerid][pFraction][1] == 11 && Player[playerid][pFraction][2] < 4) && (Player[playerid][pFraction][1] != 11 && Player[playerid][pFraction][2] < 9)) return true;
 	if(sscanf(params,"u",params[0])) return SendClientMessage(playerid,COLOR_LIGHTBLUE,"Используйте: /makemember [id]");
 	if(Player[params[0]][pBankPass] == 0) return SCM(playerid,0xAC7575FF,"У данного человека нет банковского счета!");
 	if(params[0] == playerid) return SendClientMessage(playerid,COLOR_LIGHTBLUE, "[Мысли]: Как же я могу сам себя пригласить?");
  	if(!IsPlayerConnected(playerid) || !IsPlayerConnected(params[0])) return SendClientMessage(playerid,COLOR_LIGHTBLUE,"[Мысли]: Странно, видимо он спит...");
    if(!PlayerToPlayer(playerid, params[0], 8.0)) return SendClientMessage(playerid,COLOR_LIGHTBLUE,"[Мысли]: Надо бы подойти к нему поближе.");
    if(Player[params[0]][pFraction][1] != 0) return SCM(playerid,COLOR_LIGHTBLUE,"[Мысли]: Видимо он уже состоит в другой организации. Разузнаю.");
	if(PlayerCF(playerid) && ((Player[params[0]][Licenses] & (1<<2)) == 0)) return SCM(playerid,0xAC7575FF,"У данного человека отсутствует лицензия на хранение оружия!");
    SendClientMessage(playerid,COLOR_LIGHTBLUE,"[Мысли]: Отлично, приглашение удалось!"), SendClientMessage(params[0],COLOR_LIGHTBLUE,"[Мысли]: Меня пригласили, думаю я не подведу.");
	Player[params[0]][pFraction][1] = Player[playerid][pFraction][1],Player[params[0]][pFraction][2] = 1;
	FractionSkin(params[0]),FractionColor(params[0]);
	return true;
}

CMD:setpost(playerid,params[]) {
	if(!Player[playerid][PlayerLogged] || Player[playerid][pFraction][0] == 0) return true;
    if(sscanf(params,"ud",params[0],params[1])) return SendClientMessage(playerid,COLOR_LIGHTBLUE,"Введите: /setpost [id] [должность ID]");
    if(Player[playerid][pFraction][1] == 11 && (params[1] < 1 || params[1] > 4)) return SendClientMessage(playerid,COLOR_LIGHTBLUE,"Ошибка ID должности не должен быть ниже 1 и привышать 4!");
    if(Player[playerid][pFraction][1] != 11 && (params[1] < 1 || params[1] > 9)) return SendClientMessage(playerid,COLOR_LIGHTBLUE,"Ошибка ID должности не должен быть ниже 1 и привышать 9!");
    if(params[0] == playerid) return SendClientMessage(playerid,COLOR_LIGHTBLUE, "Вы указали свой ID!");
	if(!IsPlayerConnected(playerid) || !IsPlayerConnected(params[0])) return SendClientMessage(playerid,COLOR_LIGHTBLUE,"Ошибка, данный человек оффлайн!");
	if(Player[params[0]][pFraction][1] != Player[playerid][pFraction][1]) return SendClientMessage(playerid,COLOR_LIGHTBLUE,"Ошибка, данный игрок не состоит в вашей организации!");
	Player[params[0]][pFraction][2] = params[1];
	SCM(playerid,COLOR_LIGHTBLUE,"Человек повышен/понижен в должности!");
	SCM(params[0],COLOR_LIGHTBLUE,"Вы повышены/понижены в должности!");
	FractionSkin(params[0]);
	TogglePlayerControllable(playerid,1);
	return true;
}

CMD:dismiss(playerid,params[])
{
    if(!Player[playerid][PlayerLogged] || (Player[playerid][pFraction][1] == 11 && Player[playerid][pFraction][2] < 4) && (Player[playerid][pFraction][1] != 11 && Player[playerid][pFraction][2] < 8)) return true;
    if(sscanf(params,"u",params[0])) return SendClientMessage(playerid,COLOR_LIGHTBLUE,"Введите: /dismiss [id]");
    if(Player[playerid][pFraction][1] != Player[params[0]][pFraction][1]) return SendClientMessage(playerid,COLOR_LIGHTBLUE,"Ошибка, данный игрок не состоит в вашей организации, либо вы не уполномочены!");
   	if(params[0] == playerid) return SendClientMessage(playerid,COLOR_LIGHTBLUE, "Вы указали свой ID!");
   	if(Player[playerid][pFraction][2] < Player[params[0]][pFraction][2]) return true;
	if(!IsPlayerConnected(playerid) || !IsPlayerConnected(params[0])) return SendClientMessage(playerid,COLOR_LIGHTBLUE,"Ошибка, данный человек оффлайн!");
	Player[params[0]][pFraction][2] = 0,Player[params[0]][pFraction][1] = 0;
	SetPlayerSkin(params[0],Player[params[0]][pModel][0]),SetPlayerColor(params[0],0xFFFFFF33);
	SCM(playerid,COLOR_RED,"Человек был уволен из организации!");
	SCM(params[0],COLOR_RED,"Вы были уволены из организации!");
	return true;
}

CMD:adismiss(playerid,params[])
{
	if(Player[playerid][pAdmin] < 4 || !Player[playerid][Aat]) return true;
	if(sscanf(params,"u",params[0])) return SCM(playerid,COLOR_WHITE,"Введите: {1faee9}/adismiss [id]");
	Player[params[0]][pFraction][0] = 0,Player[params[0]][pFraction][1] = 0,Player[params[0]][pFraction][2] = 0;
	SCM(playerid,COLOR_WHITE,"Игрок был {1faee9}уволен.");
	return true;
}

CMD:createhouse(playerid,params[]) {
	new str[24];
	if(Player[playerid][pAdmin] < 6 || Player[playerid][Aat] == false) return true;
	if(sscanf(params,"ddds[32]",params[0],params[1],params[2],params[3])) return SCM(playerid,COLOR_WHITE,"Используйте: /createhouse [Интерьер (0-33)] [Цена] [Приоритет] [Улица]");
  	fcor
  	GetPlayerPos(playerid,x,y,z);
	Houses++;
  	mysql_format(connects, query, 250, "INSERT INTO `houses` (`ID`, `Owner`, `X`, `Y`, `Z`, `Price`, `Lock`, `Int`, `Street`, `Priority`) VALUES ('%d', 'None', '%.4f', '%.4f', '%.4f', '%d', '0', '%d', '%s', '%d')",Houses,x,y,z,params[1],params[0],params[3],params[2]);
	mysql_tquery(connects, query, "", "");
   	strmid(House[Houses][hOwner], "None", 0, strlen("None"), 24);
   	House[Houses][hX] = x, House[Houses][hY] = y, House[Houses][hZ] = z, House[Houses][hLock] = 0;
	House[Houses][hInt] = params[0], House[Houses][hPrice] = params[1], strmid(House[Houses][hStreet], params[3], 0, strlen(params[3]), 32), House[Houses][hPriority] = params[2], House[Houses][hID] = Houses;
   	CreateDynamicMapIcon(House[Houses][hX], House[Houses][hY],House[Houses][hZ],31,0);
   	House[Houses][hPickup] = CreateDynamicPickup(1273, 1, House[Houses][hX], House[Houses][hY],House[Houses][hZ]);
	SCM(playerid,0x03c03cFF,"Дом создан! Для того, чтобы поставить координаты автомобиля - встаньте на будущее место авто и введите /mhcp");
	format(str,sizeof(str),"ID дома: {ffffff}%d",Houses);
	SCM(playerid,0x03c03cFF,str);
   	SetPVarInt(playerid,"GetPickup",gettime()+3);
    return true;
}

CMD:createwarehouse(playerid,params[]) {
	if(Player[playerid][pAdmin] < 6 || Player[playerid][Aat] == false) return true;
	if(sscanf(params,"ds[24]",params[0],params[1])) return SCM(playerid,COLOR_WHITE,"Используйте: /createwarehouse [Организация] [Название склада]");
	fcor
	GetPlayerPos(playerid,x,y,z);
  	mysql_format(connects, query, 200, "INSERT INTO `warehouses` (`name`, `x`, `y`, `z` , `fraction`) VALUES ('%s', '%.4f', '%.4f', '%.4f', '%d')",params[1],x,y,z,params[0]);
    mysql_tquery(connects, query, "", "");
	Wars++;
	Ware[Wars][wFraction] = params[1];
	SCM(playerid,-1,"{ff0000}Склад успешно создан, для его активации - перезапустите сервер!");
	SaveWarehouse(Ware[Wars][wID]);
    return true;
}

CMD:createbusiness(playerid,params[]) {
	if(Player[playerid][pAdmin] < 6 || Player[playerid][Aat] == false) return true;
	if(sscanf(params,"dddds[24]",params[0],params[1],params[2],params[3],params[4])) return SCM(playerid,COLOR_WHITE,"Используйте: /createbusiness [Цена] [@Тип] [Интерьер (0-34)] [Вирт.Мир] [Название *24сим*]");
	fcor
	new type;
  	GetPlayerPos(playerid,x,y,z);
	Businesses++;
  	switch(params[1]) {
 		case 0: type = 42;
	}
   	strmid(Business[Businesses][bOwner], "None", 0, strlen("None"), 24);
   	Business[Businesses][bX] = x, Business[Businesses][bY] = y, Business[Businesses][bZ] = z, Business[Businesses][bLock] = 0;
	Business[Businesses][bInt] = params[2], Business[Businesses][bPrice] = params[0], Business[Businesses][bType] = params[1], Business[Businesses][bID] = Businesses;
	Business[Businesses][bIcon] = CreateDynamicMapIcon(Business[Businesses][bX],Business[Businesses][bY],Business[Businesses][bZ],type,COLOR_WHITE,0,-1,-1);
	Business[Businesses][bPickup][0] = CreateDynamicPickup(1274,1,Business[Businesses][bX],Business[Businesses][bY],Business[Businesses][bZ]);
	mysql_format(connects, query, 270, "INSERT INTO `buisnesses` (`ID`, `Owner`, `name`, `X`, `Y`, `Z`, `Price`, `Lock`, `Int`, `Type`, `Cost`, `VW`) VALUES ('%i', 'None', '%s', '%.4f', '%.4f', '%.4f', '%i', '1', '%i', '%i', '0', '%i')",Businesses,params[4],x,y,z,params[0],params[1],params[2],params[3]);
    mysql_tquery(connects, query, "", "");
	SCM(playerid,0x1faee9FF,"Бизнес успешно создан!");
	SaveBusiness(Business[Businesses][bID]);
   	SetPVarInt(playerid,"GetPickup",gettime()+3);
    return true;
}


CMD:ware(playerid,params[]) if(PlayerGangster(playerid) && PositionWarehouse(playerid)) ShowPlayerDialog(playerid,13,DIALOG_STYLE_LIST,"Склад Банды", "Снять/Положить деньги в банк\nВзять/Положить патроны\nВзять/Положить наркотики", "Выбор", "Отмена");

CMD:gcolor(playerid,params[]) {
	if(!Player[playerid][PlayerLogged] || Player[playerid][pAdmin] < 6 || Player[playerid][Aat] == false) return true;
	if(sscanf(params,"d",params[0])) return true;
	for(new i = 0; i < sizeof(Zone); i++) {
 		if(!PlayerToZone(playerid, Zone[i][gminX],Zone[i][gminY],Zone[i][gmaxX],Zone[i][gmaxY])) continue;
   		Zone[i][gFraction] = params[0];
     	GangZoneStopFlashForAll(Zone[i][gID]);
      	GangZoneHideForAll(Zone[i][gID]);
       	GangZoneShowForAll(Zone[i][gID], GetGangZoneColor(i));
        SaveGangZone(i);
        break;
	}
	return true;
}

CMD:capture(playerid,params[]) {
	if(!PlayerGangster(playerid) || !Player[playerid][PlayerLogged]) return true;
 	if(PositionSpawnGang(playerid)) return SCM(playerid,0xFF0000FF,"Эту территорию нельзя осквернять, так-как она всегда под защитой другой банды!");
    if(GetPlayerVirtualWorld(playerid) != 0) return true;
	if(Time()) return SendClientMessage(playerid, 0xFF0000FF, "Время когда можно начинать войну за территорию - с 10:00 до 00:00 ( только в четные часы )!");
	new gangsters = 0;
 	for(new g = 0; g < sizeof(Zone); g++)  	{
		if(!PlayerToZone(playerid, Zone[g][gminX],Zone[g][gminY],Zone[g][gmaxX],Zone[g][gmaxY])) continue;
		if(InWar[Zone[g][gFraction]] != 0 || InWar[Zone[g][gWar]] != 0) return SCM(playerid,0xAC7575FF,"Ваша или вражеская банда уже проводит войну за территорию!");
		if(Zone[g][gFraction] == Player[playerid][pFraction][1]) return SendClientMessage(playerid, 0xAC7575FF, "Ваша банда уже контролирует эту территорию!");
		foreach(new i : Player) if(Player[i][pFraction][1] == Zone[g][gFraction]) gangsters++;
		//if(gangsters == 0) return SendClientMessage(playerid, 0xAC7575FF, "Никого из бандитов банды владеющей этой зоной нет!");
  		new string[20];
    	switch(Zone[g][gFraction]) {
	        case 1: format(string,sizeof(string),"Grove Street Gang");
	        case 2: format(string,sizeof(string),"The Ballas Gang");
    	}
    	SendRadioMessage(Zone[g][gFraction], 0xFF0000FF, "Одна из ваших территорий подверглась атаке вражеской банды!");
     	SendRadioMessage(Zone[g][gFraction], 0xFF0000FF, "У вас есть 5 минут чтобы отвоевать территорию!");
     	format(strock,sizeof(strock),"%s спровоцировал войну за территорию с %s. У вас есть 5 минут чтобы отвоевать территорию!",Name(playerid),string);
     	SendRadioMessage(Player[playerid][pFraction][1], 0xFF0000FF, strock);
     	GangZoneFlashForAll(Zone[g][gID], 0xFF000099);
		Zone[g][gTime] = 15, ZoneOnBattle[g] = 1, Zone[g][gWar] = Player[playerid][pFraction][1];
		InWar[Zone[g][gWar]] = 1, InWar[Zone[g][gFraction]] = 1;
		if(GWars[0] == 0) GWars[0] = g;
		else GWars[1] = g;
		foreach(new i : Player) {
		    if(Player[i][pFraction][1] == Zone[g][gFraction] || Player[i][pFraction][1] == Zone[g][gWar]) {
    			PlayerTextDrawSetString(i,gFGang[i],GetGangName(Zone[g][gFraction]));
				PlayerTextDrawSetString(i,gTGang[i],GetGangName(Zone[g][gWar]));
		  		format(string,4,"%i",Zone[g][gID]);
				PlayerTextDrawSetString(i,gIDs[i], string);
				TextDrawShowForPlayer(i,gBox);
				PlayerTextDrawShow(i,gFGang[i]);
				PlayerTextDrawShow(i,gTGang[i]);
				PlayerTextDrawShow(i,gFScore[i]);
				PlayerTextDrawShow(i,gTScore[i]);
				TextDrawShowForPlayer(i,gArea);
				PlayerTextDrawShow(i,gIDs[i]);
				TextDrawShowForPlayer(i,gsTime);
				PlayerTextDrawShow(i,gTimeTick[i]);
		}   }
        break;
	}
	return true;
}

CMD:makegun(playerid,params[]) {
    if(!Player[playerid][PlayerLogged]) return true;
	if(GetPVarInt(playerid,"MakeGun") == 0) {
		new ammos[16];
	    TextDrawShowForPlayer(playerid,cBox);
	    TextDrawShowForPlayer(playerid,cMYG);
	    PlayerTextDrawShow(playerid,cAmmo[playerid]);
	    TextDrawShowForPlayer(playerid,cXc);
	    TextDrawShowForPlayer(playerid,c1);
	    TextDrawShowForPlayer(playerid,c2);
	    TextDrawShowForPlayer(playerid,c3);
	    TextDrawShowForPlayer(playerid,c4);
	    TextDrawShowForPlayer(playerid,c5);
	    TextDrawShowForPlayer(playerid,c6);
	    TextDrawShowForPlayer(playerid,cDeagle);
	    TextDrawShowForPlayer(playerid,cKolt);
	    TextDrawShowForPlayer(playerid,cShotgun);
	    TextDrawShowForPlayer(playerid,cAKM);
	    TextDrawShowForPlayer(playerid,cM4A1);
	    TextDrawShowForPlayer(playerid,cMP5);
	    TextDrawShowForPlayer(playerid,cSAW);
	    format(ammos,16,"You Ammo: %d",Player[playerid][pAmmo]);
	    PlayerTextDrawSetString(playerid,cAmmo[playerid],ammos);
	    SetPVarInt(playerid,"MakeGun",1);
	    SelectTextDraw(playerid, 0xFF0000AA), Player[playerid][TDSelect] = true;
	}
	else {
	    TextDrawHideForPlayer(playerid,cBox);
	    TextDrawHideForPlayer(playerid,cMYG);
	    PlayerTextDrawHide(playerid,cAmmo[playerid]);
	    TextDrawHideForPlayer(playerid,cXc);
	    TextDrawHideForPlayer(playerid,c1);
	    TextDrawHideForPlayer(playerid,c2);
	    TextDrawHideForPlayer(playerid,c3);
	    TextDrawHideForPlayer(playerid,c4);
	    TextDrawHideForPlayer(playerid,c5);
	    TextDrawHideForPlayer(playerid,c6);
	    TextDrawHideForPlayer(playerid,cDeagle);
	    TextDrawHideForPlayer(playerid,cKolt);
	    TextDrawHideForPlayer(playerid,cShotgun);
	    TextDrawHideForPlayer(playerid,cAKM);
	    TextDrawHideForPlayer(playerid,cM4A1);
	    TextDrawHideForPlayer(playerid,cMP5);
	    TextDrawHideForPlayer(playerid,cSAW);
        SetPVarInt(playerid,"MakeGun",0), Player[playerid][TDSelect] = false, CancelSelectTextDraw(playerid);
	}
	return true;
}


CMD:menu(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
    if(GetPVarInt(playerid,"Menu") == 0) ShowStats(playerid);
	else {
	    TextDrawHideForPlayer(playerid,mm0);
        TextDrawHideForPlayer(playerid,mm1);
        TextDrawHideForPlayer(playerid,mm2);
        TextDrawHideForPlayer(playerid,mm3);
        TextDrawHideForPlayer(playerid,mm4);
        TextDrawHideForPlayer(playerid,mm5);
        TextDrawHideForPlayer(playerid,mm6);
        PlayerTextDrawHide(playerid,mm7[playerid]);
        TextDrawHideForPlayer(playerid,mm8);
        TextDrawHideForPlayer(playerid,mm9);
        TextDrawHideForPlayer(playerid,mm10);
        TextDrawHideForPlayer(playerid,mm11);
        TextDrawHideForPlayer(playerid,mm12);
        TextDrawHideForPlayer(playerid,mm13);
        TextDrawHideForPlayer(playerid,mm14);
        TextDrawHideForPlayer(playerid,mm15);
        TextDrawHideForPlayer(playerid,mm16);
        TextDrawHideForPlayer(playerid,mm17);
        TextDrawHideForPlayer(playerid,mm18);
        TextDrawHideForPlayer(playerid,mm19);
	    PlayerTextDrawHide(playerid,mm20[playerid]);
	    PlayerTextDrawHide(playerid,mm21[playerid]);
	    PlayerTextDrawHide(playerid,mm22[playerid]);
	    PlayerTextDrawHide(playerid,mm23[playerid]);
	    PlayerTextDrawHide(playerid,mm24[playerid]);
	    PlayerTextDrawHide(playerid,mm25[playerid]);
	    PlayerTextDrawHide(playerid,mm26[playerid]);
	    PlayerTextDrawHide(playerid,mm27[playerid]);
	    PlayerTextDrawHide(playerid,mm28[playerid]);
	    TextDrawHideForPlayer(playerid,mm29);
	    TextDrawHideForPlayer(playerid,mm30);
	    TextDrawHideForPlayer(playerid,mm31);
	    TextDrawHideForPlayer(playerid,mm32);
	    TextDrawHideForPlayer(playerid,mm33);
	    TextDrawHideForPlayer(playerid,mm34);
		TextDrawHideForPlayer(playerid,mm35);
		TextDrawHideForPlayer(playerid,mm36);
	    TextDrawHideForPlayer(playerid,mm37);
	    TextDrawHideForPlayer(playerid,mm38);
	    TextDrawHideForPlayer(playerid,mm39);
	    TextDrawHideForPlayer(playerid,mm40);
	    TextDrawHideForPlayer(playerid,mm41);
		TextDrawHideForPlayer(playerid,mm42);
		PlayerTextDrawHide(playerid,mm43[playerid]);
		TextDrawHideForPlayer(playerid,mm44);
		PlayerTextDrawHide(playerid,mm45[playerid]);
	    PlayerTextDrawHide(playerid,mm46[playerid]);
	    PlayerTextDrawHide(playerid,mm47[playerid]);
        SetPVarInt(playerid,"Menu",0);
		Player[playerid][TDSelect] = false;
		CancelSelectTextDraw(playerid);
	}
	return true;
}
alias:menu("help", "mm");

CMD:spcars(playerid, params[]) {
    if(!IsPlayerConnected(playerid)) return true;
	if(Player[playerid][pAdmin] < 4 || Player[playerid][Aat] == false) return true;
	for(new v; v < MAX_VEHICLES; v++) if(IsVehicleOccupied(v) == -1) SetVehicleToRespawn(v);
	return true;
}

CMD:gmcheck(playerid,params[]) {
    fcor
    if(Player[playerid][pAdmin] < 2 || Player[playerid][Aat] == false) return true;
    if(sscanf(params,"u",params[0])) return SCM(playerid,0xFFFFFFFF,"Введите: /gmcheck [id]");
    GetPlayerPos(params[0],x,y,z);
    CreateExplosionForPlayer(params[0], x,y,z+7.5, 5, 0.5);
    return true;
}


CMD:pm(playerid, params[]) {
    if(Player[playerid][pAdmin] < 1 || Player[playerid][Aat] == false) return true;
	if(sscanf(params, "us[64]",params[0],params[1])) return SendClientMessage(playerid, 0xFFFFFFFF, "Введите: /pm [id] [текст]");
	if(!IsPlayerConnected(params[0])) return true;
	format(strock, sizeof(strock), "Ответ от %s: %s",Name(playerid),params[1]);
	SendClientMessage(params[0], 0x1faee9FF, strock);
	PlayerPlaySound(params[0], 30800, 0.0, 0.0, 0.0);
	format(strock, sizeof(strock), "Ответ к %s[%d]: %s",Name(params[0]),params[0],params[1]);
	SendAdminMessage(0x1faee9FF,strock);
	return true;
}
alias:pm("ans");

CMD:pay(playerid, params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
    if(sscanf(params, "ud", params[0],params[1])) return SendClientMessage(playerid, 0xFFFFFFFF, "Введите: /pay [id] [сумма]");
    if(Player[playerid][pLevel] < 2) return SCM(playerid,0xFFFFFFFF,"Передавать деньги можно {AC7575}только со 2 уровня!");
	if(params[1] < 1 || params[1] > 100000) return SendClientMessage(playerid, 0xFFFFFFFF, "Минимальная сумма для передачи 1$, максимальная - 30.000$."), SCM(playerid,0xFFFFFFFF,"Крупные суммы можно перевести через банк ( комиссия ).");
	if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, 0xFFFFFFFF, "Данный игрок оффлайн.");
	if(params[0] == INVALID_PLAYER_ID || params[0] == playerid) return true;
	if(!PlayerToPlayer(playerid, params[0], 5.0)) return SendClientMessage(playerid, 0xFFFFFFFF, "Вы слишком далеко.");
	if(Player[playerid][pMoney] < params[1]) return SCM(playerid,0xFFFFFFFF,"У вас недостаточно наличных.");
	Player[params[0]][pMoney] += params[1];
	Player[playerid][pMoney] -= params[1];
	format(strock, 52, "Вы передали %s[%d] %d$",Name(params[0]),params[0],params[1]);
	SendClientMessage(playerid, COLOR_GRAD1, strock);
	PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0);
	format(strock, 54, "Вы получили %d$ от %s[%d]",params[1],Name(playerid), playerid);
	SendClientMessage(params[0], COLOR_GRAD1, strock);
	PlayerPlaySound(params[0], 30800, 0.0, 0.0, 0.0);
	return true;
}

CMD:sms(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	if(Player[playerid][pPhone][0] == 0) return SCM(playerid,0xAC7575FF,"У вас нет мобильного телефона!");
 	if(GetPVarInt(playerid,"SmsTime") > gettime()) return SCM(playerid,0xAC7575FF,"Не флуди!");
	if(sscanf(params,"us[128]",params[0],params[1])) return SCM(playerid,0xFFFFFFFF,"Введите: {1faee9}/sms [id] [сообщение]");
	if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, 0xFFFFFFFF, "Данный игрок оффлайн.");
	if(Player[playerid][pPhone][1] < 0) return SCM(playerid,0xAC7575FF,"У вас недостаточно денег для отправки смс!");
	format(strock, sizeof(strock), "SMS от %s[%d]: %s",Name(playerid),playerid,params[1]);
	SendClientMessage(params[0], 0x7fff00FF, strock);
	PlayerPlaySound(params[0], 6401, 0.0, 0.0, 0.0);
	format(strock, sizeof(strock), "SMS к %s[%d]: %s",Name(params[0]),params[0],params[1]);
	SendClientMessage(playerid, 0x7fff00FF, strock);
	Player[playerid][pPhone][1] -= 5;
	PlayerPlaySound(playerid, 6401, 0.0, 0.0, 0.0);
	GameTextForPlayer(playerid,"~r~-5$",1000,3);
	SetPVarInt(playerid,"SmsTime",gettime()+5);
	return true;
}

CMD:ban(playerid,params[]){
	if(Player[playerid][pAdmin] < 2 || Player[playerid][Aat] == false) return true;
	if(sscanf(params,"uds[128]",params[0],params[1],params[2])) return SCM(playerid,0xFFFFFFFF,"Используйте: {1faee9}/ban [id] [дни] [причина]");
	if(strcmp(Name(params[0]),"George_Houser",true)==0) return SCM(playerid,COLOR_LIGHTRED,"Данного человека невозможно кикнуть!");
	if(params[0] == INVALID_PLAYER_ID || !IsPlayerConnected(params[0]) || params[0] == playerid) return true;
 	format(strock, sizeof(strock), "%s был забанен администратором %s на %d дней. Причина: %s", Name(params[0]),Name(playerid),params[1],params[2]);
	SendClientMessageToAll(COLOR_LIGHTRED,strock);
	Player[params[0]][pBan] = gettime() + params[1]*86400-43200;
	KickEx(params[0]);
	return true;
}

CMD:global(playerid,params[]){
	if(Player[playerid][pAdmin] < 2 || Player[playerid][Aat] == false) return true;
	if(sscanf(params,"s[144]",params[0])) return true;
	format(strock,144,"Администратор %s: %s",Name(playerid),params[0]);
	SendClientMessageToAll(0xff9218FF,strock);
	return true;
}


CMD:recon(playerid,params[]){
	if(Player[playerid][pAdmin] < 2 || Player[playerid][Aat] == false) return true;
	if(GetPVarInt(playerid,"Recon") == 1) {
	    SetPVarInt(playerid,"Recon",2);
		TogglePlayerSpectating(playerid, false);
		HideMenuForPlayer(rMenu,playerid);
		TextDrawHideForPlayer(playerid,rbox), TextDrawHideForPlayer(playerid,rmodel[playerid]),  TextDrawHideForPlayer(playerid,rname[playerid]), TextDrawHideForPlayer(playerid,rhealth[playerid]), TextDrawHideForPlayer(playerid,rarmour[playerid]), TextDrawHideForPlayer(playerid,rping[playerid]),
		TextDrawHideForPlayer(playerid,rmoney[playerid]), TextDrawHideForPlayer(playerid,rspeed[playerid]), TextDrawHideForPlayer(playerid,rrip[playerid]), TextDrawHideForPlayer(playerid,rip[playerid]), TextDrawHideForPlayer(playerid,rcopy);
	 	TextDrawHideForPlayer(playerid,rvbox), TextDrawHideForPlayer(playerid,rvmodel[playerid]), TextDrawHideForPlayer(playerid,rvname[playerid]), TextDrawHideForPlayer(playerid,rvhealth[playerid]), TextDrawHideForPlayer(playerid,rvspeed[playerid]);
	    SetPVarInt(GetPVarInt(playerid,"ReconID"),"ReconedID",INVALID_PLAYER_ID), SetPVarInt(playerid,"ReconID",INVALID_PLAYER_ID);
	    return true;
	}
	if(sscanf(params,"u",params[0])) return SCM(playerid,0xFFFFFFFF,"Используйте: /sp(ectate) [id]");
    if(params[0] == playerid) return  SCM(playerid,0xFF0000FF,"Слежка за самим собой - невозможна!");
    if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, 0xFF0000FF, "Игрок оффлайн!");
    fcor
    GetPlayerPos(playerid,x,y,z);
    if(GetPVarInt(playerid,"Recon") == 0) {
        SetPVarInt(playerid,"Skin",GetPlayerSkin(playerid));
        SetPVarFloat(playerid,"X",x),SetPVarFloat(playerid,"Y",y),SetPVarFloat(playerid,"Z",z), SetPVarInt(playerid,"Interior",GetPlayerInterior(playerid)), SetPVarInt(playerid,"VW",GetPlayerVirtualWorld(playerid));
		SetPlayerInterior(playerid, GetPlayerInterior(params[0]));
		SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(params[0]));
		TextDrawSetPreviewModel(rmodel[playerid],GetPlayerSkin(params[0]));
		TogglePlayerSpectating(playerid, true);
		PlayerSpectatePlayer(playerid, params[0]);
		TextDrawShowForPlayer(playerid,rbox), TextDrawShowForPlayer(playerid,rmodel[playerid]),  TextDrawShowForPlayer(playerid,rname[playerid]), TextDrawShowForPlayer(playerid,rhealth[playerid]), TextDrawShowForPlayer(playerid,rarmour[playerid]), TextDrawShowForPlayer(playerid,rping[playerid]),
	 	TextDrawShowForPlayer(playerid,rmoney[playerid]), TextDrawShowForPlayer(playerid,rspeed[playerid]), TextDrawShowForPlayer(playerid,rrip[playerid]), TextDrawShowForPlayer(playerid,rip[playerid]), TextDrawShowForPlayer(playerid,rcopy);
		if(GetPlayerState(params[0]) == PLAYER_STATE_DRIVER) {
  			PlayerSpectateVehicle(playerid, GetPlayerVehicleID(params[0]));
  			new Float:vHealth; GetVehicleHealth(GetPlayerVehicleID(params[0]),vHealth); GetVehicleSpeed(GetPlayerVehicleID(params[0]));
            TextDrawShowForPlayer(playerid,rvbox), TextDrawShowForPlayer(playerid,rvmodel[playerid]), TextDrawShowForPlayer(playerid,rvname[playerid]), TextDrawShowForPlayer(playerid,rvhealth[playerid]), TextDrawShowForPlayer(playerid,rvspeed[playerid]);
		}
      	ShowMenuForPlayer(rMenu,playerid);
        SetPVarInt(playerid,"ReconID",params[0]), SetPVarInt(params[0],"ReconedID",playerid),SetPVarInt(playerid,"Recon",1);
	}
	return true;
}
alias:recon("spectate", "re");


CMD:hello(playerid, params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	if(sscanf(params, "u", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "Введите: /hello(/hi) {1faee9}[id]");
	if(!IsPlayerConnected(playerid) || IsPlayerInAnyVehicle(playerid) || !IsPlayerConnected(params[0]) || params[0] == playerid || !PlayerToPlayer(playerid, params[0], 2.0)) return true;
	new Float:angle;
	GetPlayerFacingAngle(playerid, angle), SetPlayerFacingAngle(params[0], angle + 180);
	ApplyAnimation(playerid, "GANGS", "hndshkfa",4.0,0,0,0,0,0,1), ApplyAnimation(params[0], "GANGS", "hndshkfa",4.0,0,0,0,0,0,1);
	return true;
}
alias:hello("hi");


CMD:radio(playerid,params[]) {
	new string[144], post[16+1];
	if(Player[playerid][pFraction][1] == 0) return true;
	if(sscanf(params,"s[128]",params[0])) return SCM(playerid,-1,"Используйте: {1faee9}/r(adio) [сообщение]");
	switch(Player[playerid][pFraction][1]) {
		case 1: {
		    switch(Player[playerid][pFraction][2]) {
		        case 1: post = "Beginner";
		        case 2: post = "Buddy";
		        case 3: post = "Killer";
		        case 4: post = "Dog";
		        case 5: post = "Drug dealer";
		        case 6: post = "Crazy";
		        case 7: post = "Initiator";
		        case 8: post = "Bloody";
		        case 9: post = "Chief";
		        case 10: post = "Father";
		}   }
		case 2: {
		    switch(Player[playerid][pFraction][2]) {
		        case 1: post = "Cock";
		        case 2: post = "Dog";
		        case 3: post = "Kracker";
		        case 4: post = "Hight-Roller";
		        case 5: post = "Drug dealer";
		        case 6: post = "Scoundrel";
		        case 7: post = "Killer";
		        case 8: post = "Junior Boss";
		        case 9: post = "Old Gangster";
		        case 10: post = "Big Willy";
		}   }
		case 3: {
			switch(Player[playerid][pFraction][2]) {
				case 10: post = "Padre";
				case 9: post = "Son Pandillas";
				case 8: post = "Vigilante";
				case 7: post = "Tirador";
				case 6: post = "Peligroso";
				case 5: post = "Comerciante";
				case 4: post = "Desconocido";
				case 3: post = "Iniciador";
				case 2: post = "Bandido";
				case 1: post = "Esperanto";
		}   }
		case 4: {
			switch(Player[playerid][pFraction][2]) {
				case 10: post = "Ringleader";
				case 9: post = "Native Latinos";
				case 8: post = "Bootbkack";
				case 7: post = "Thug";
				case 6: post = "Hoodlum";
				case 5: post = "Trafficker";
				case 4: post = "Soladato";
				case 3: post = "Verificado";
				case 2: post = "Novato";
				case 1: post = "Stanger";
		}   }
		case 5: {
			switch(Player[playerid][pFraction][2]) {
				case 10: post = "Papi";
				case 9: post = "Rifecado";
				case 8: post = "Gracio";
				case 7: post = "Oneci";
				case 6: post = "Eltoro";
				case 5: post = "Gerendo";
				case 4: post = "Pantalones";
				case 3: post = "Elcostro";
				case 2: post = "Elmoro";
				case 1: post = "Mestro";
		}   }
		case 6: {
			switch(Player[playerid][pFraction][2]) {
				case 10: post = "Генерал";
				case 9: post = "Полковник";
				case 8: post = "Подполковник";
				case 7: post = "Майор";
				case 6: post = "Капитан";
				case 5: post = "Лейтенант";
				case 4: post = "Штаб-Сержант";
				case 3: post = "Сержант";
				case 2: post = "Капрал";
				case 1: post = "Рядовой";
		}   }
		case 7..9: {
			switch(Player[playerid][pFraction][2]) {
				case 10: post = "Шеф";
				case 9: post = "Зам.Шефа";
				case 8: post = "Капитан";
				case 7: post = "Лейтенант";
				case 6: post = "Детектив";
				case 5: post = "Глава SWAT";
				case 4: post = "Боец SWAT";
				case 3: post = "Сержант";
				case 2: post = "Офицер";
				case 1: post = "Постовой";
		}   }
		case 10: {
			switch(Player[playerid][pFraction][2]) {
				case 10: post = "Ген.Прокурор";
				case 9: post = "Директор FBI";
				case 8: post = "Секретный Агент";
				case 7: post = "Спец.Агент";
				case 6: post = "Старший Агент";
				case 5: post = "Агент Разведки";
				case 4: post = "Агент";
				case 3: post = "Младший Агент";
				case 2: post = "Помощник Агента";
				case 1: post = "Оп.Работник";
		}   }
		case 13,14: {
		    switch(Player[playerid][pFraction][2]) {
				case 10: post = "Директор";
				case 9: post = "Зам.Директора";
				case 8: post = "Тех.Директор";
				case 7: post = "Продюссер";
				case 6: post = "Репортер";
				case 5: post = "Сценарист";
				case 4: post = "Тех.Режиссер";
				case 3: post = "Радиоведущи";
				case 2: post = "Редактор";
				case 1: post = "Стажер";
		}   }
		case 15: {
		    switch(Player[playerid][pFraction][2]) {
				case 10: post = "Вор в законе";
				case 9: post = "Криминальный";
				case 8: post = "Координатор";
				case 7: post = "Гангстер";
				case 6: post = "Теневик";
				case 5: post = "Рецидивист";
				case 4: post = "Солдат";
				case 3: post = "Преступник";
				case 2: post = "Рекетир";
				case 1: post = "Бандит";
		}   }
		case 16: {
		    switch(Player[playerid][pFraction][2]) {
		    	case 10: post = "Сен Сей";
				case 9: post = "Такаши";
				case 8: post = "Тсу Ши";
				case 7: post = "Джи Зу";
				case 6: post = "Пак Тсе Син";
				case 5: post = "Шанхай";
				case 4: post = "Лао Бан";
				case 3: post = "Шан-Ши";
				case 2: post = "Лунг Тао";
				case 1: post = "Чанг Лао";
		}   }
		case 17: {
		    switch(Player[playerid][pFraction][2]) {
		    	case 10: post = "Глав.Врач";
				case 9: post = "Зав.Отделением";
				case 8: post = "Хирург";
				case 7: post = "Доктор";
				case 6: post = "Нарколог";
				case 5: post = "Ординатор";
				case 4: post = "Врач";
				case 3: post = "Медик";
				case 2: post = "Санитар";
				case 1: post = "Интерн";
		    }
		}
		case 18: {
		    switch(Player[playerid][pFraction][2]) {
		    	case 10: post = "Босс";
				case 9: post = "Заместитель";
				case 8: post = "Воин";
				case 7: post = "Координатор";
				case 6: post = "Свой";
				case 5: post = "Опасный";
				case 4: post = "Дестроер";
				case 3: post = "Гонщик";
				case 2: post = "Легавый";
				case 1: post = "Помощник";
		    }
		}
	}
	format(string, sizeof(string), "[R] %s %s: %s",post,Name(playerid), params[0]);
	SendRadioMessage(Player[playerid][pFraction][1], 0x1faee9AA, string);
	SetPlayerChatBubble(playerid, "разговаривает по рации",COLOR_PURPLE,30.0,3000);
	return true;
}
alias:radio("r");

CMD:family(playerid,params[]) {
	new string[144];
	if(GetPVarInt(playerid,"TruckJob") == 0) return true;
	if(sscanf(params,"s[128]",params[0])) return SCM(playerid,-1,"Используйте: {1faee9}/f [сообщение]");
	SetPlayerChatBubble(playerid, "разговаривает по рации",COLOR_PURPLE,30.0,3000);
	format(string, sizeof(string), "[F] %s: %s",Name(playerid), params[0]);
	foreach(new i : Player) if(GetPVarInt(i,"TruckJob") == 1) SCM(i, 0x999589FF, string);
	return true;
}
alias:family("f");


CMD:call(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	if(Player[playerid][pPhone][0] == 0) return SCM(playerid,0xAC7575FF,"У вас нет мобильного телефона, но вы можете воспользоваться будкой!");
	if(GetPVarInt(playerid,"Called") != 0) return SCM(playerid,0xAC7575FF,"Вы уже разговаривате по мобильному!");
	ShowPlayerDialog(playerid,26,DIALOG_STYLE_LIST,"{03c03c}Набор номера","{ffffff}Ввести номер\nСлужба полиции\nСлужба Скорой Помощи\nСлужба Такси","Далее","Отмена");
	SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
	return true;
}
alias:call("c");

CMD:cc(playerid,params[]) for(new i; i<20;i++) SCM(playerid,-1,"");

CMD:t(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	if(GetPVarInt(playerid,"CalledID") == INVALID_PLAYER_ID) return SCM(playerid,-1,"Вам никто {1faee9}не звонит!");
	SetPVarInt(GetPVarInt(playerid,"CalledID"),"Called",3), SetPVarInt(playerid,"Called",4);
	SCM(GetPVarInt(playerid,"CalledID"),0xFFEE00FF,"[T] Абонент ответил.");
	SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
	return true;
}

CMD:h(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
    if(GetPVarInt(playerid,"CalledID") == INVALID_PLAYER_ID) return SCM(playerid,-1,"Вам никто {1faee9}не звонит либо вы никому не звоните!");
    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE),  SetPlayerSpecialAction(GetPVarInt(playerid,"CalledID"),SPECIAL_ACTION_STOPUSECELLPHONE);
    SCM(GetPVarInt(playerid,"CalledID"),0xFFEE00FF,"[T] Абонент положил трубку."), SCM(GetPVarInt(GetPVarInt(playerid,"CalledID"),"CalledID"),0xFFEE00FF,"[T] Абонент положил трубку.");
    SetPVarInt(GetPVarInt(playerid,"CalledID"),"Called",0), SetPVarInt(playerid,"Called",0), SetPVarInt(playerid,"CalledID",INVALID_PLAYER_ID), SetPVarInt(GetPVarInt(playerid,"CalledID"),"CalledID",INVALID_PLAYER_ID);
    return true;
}

CMD:banip(playerid, params[]) {
	if(Player[playerid][pAdmin] < 5 || !Player[playerid][Aat]) return true;
    if(sscanf(params,"s[16]", params[0])) return SendClientMessage(playerid,COLOR_WHITE,"Введите: {ff0000}/banip [ip]");
    mysql_format(connects, query,60,"INSERT INTO `ips` (`IP`) VALUE ('%s')",params[0]);
    mysql_tquery(connects, query, "", "");
    format(strock, 76, "IP: %s заблокирован администратором %s", params[0], Name(playerid));
    SendAdminMessage(COLOR_RED,strock);
    return true;
}

CMD:unbanip(playerid, params[]) {
    if(sscanf(params,"s[16]", params[0])) return SendClientMessage(playerid,COLOR_WHITE,"Введите: {1faee9}/unbanip [ip]");
    mysql_format(connects, query,60,"DELETE FROM `ips` WHERE `IP` = '%s' LIMIT 1",params[0]);
    mysql_tquery(connects, query, "", "");
    format(strock, 76, "IP: %s разблокирован администратором %s", params[0], Name(playerid));
    SendAdminMessage(0x1faee9FF,strock);
    return true;
}

/*CMD:banipex(playerid, params[]) {
	if(Player[playerid][pAdmin] < 6 || !Player[playerid][Aat]) return true;
	new string[24];
    if(sscanf(params,"s[12]", params[0])) return SendClientMessage(playerid,0xFF0000FF,"/banipex ip");
    new cell[4][4]; split(params[0],cell,'.');
	format(string,sizeof(string),"banip %s.%s.*.*",cell[0],cell[1]);
	SCM(playerid,0xFF0000FF,string);
	SendRconCMD(string);
	return true;
}*/

CMD:crash(playerid, params[]) {
    if(Player[playerid][pAdmin] < 5 || !Player[playerid][Aat]) return true;
    if(sscanf(params,"u", params[0])) return SendClientMessage(playerid,0xFF0000FF,"/crash id");
	SetPlayerSkin(params[0],999);
	return true;
}

CMD:unrent(playerid,params[]) {
	if(Player[playerid][ArendedVehicle] == INVALID_VEHICLE_ID) return SCM(playerid,0x1faee9FF,"[Мысли]: {ffffff}Я же ничего не арендовал.");
	if(Player[playerid][ArendedVehicle] >= truckcar[0] && Player[playerid][ArendedVehicle] <= truckcar[1] && GetPVarInt(playerid,"TruckHaul") > 0) DestroyVehicle(Player[playerid][Trailer]), Player[playerid][pMoney] -= 1800, GameTextForPlayer(playerid,"~r~-1800$",2000,3);
    Arended[Player[playerid][ArendedVehicle]] = false, SetVehicleToRespawn(Player[playerid][ArendedVehicle]), Player[playerid][ArendedVehicle] = INVALID_VEHICLE_ID, SCM(playerid,COLOR_WHITE,"Договор аренды {1faee9}разорван!");
	return true;
}

CMD:taxicall(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	if(GetPVarInt(playerid,"TaxiTime") > gettime()) return SCM(playerid,0xFFFFFFFF,"Номер занят, либо вы звоните слишком часто!");
	if(GetPVarInt(playerid,"TaxiJob") == 0 || GetPVarInt(playerid,"TaxiCall") != INVALID_PLAYER_ID) return SCM(playerid,0x555555FF,"Вы не таксист или уже приняли вызов!");
	if(sscanf(params,"u",params[0])) return SCM(playerid,0xFFFFFFFF,"Введите: {1faee9}/taxicall [id заказчика]");
	if(GetPVarInt(params[0],"Taxi") == 0) return SCM(playerid,0xFFFFFFFF,"Этот человек {1faee9}не заказывал такси!");
	SetPVarInt(playerid,"Number",1), ShowPlayerDialog(playerid,28,DIALOG_STYLE_INPUT,"{1faee9}Время прибытия","{ffffff}Если вы действительно хотите принять заказ, пожалуйста {03c03c}укажите примерное время прибытия на место.","Принять","Отмена");
	SetPVarInt(playerid,"TaxiCall",params[0]), SetPVarInt(params[0],"TaxiCall",playerid), SetPVarInt(playerid,"TaxiCheck",1), SetPVarInt(params[0],"Taxi",0);
	SetPVarInt(playerid,"TaxiTime",gettime()+30);
	return true;
}

CMD:taxicancel(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
    if(GetPVarInt(playerid,"TaxiJob") == 0 && GetPVarInt(playerid,"TaxiCall") == INVALID_PLAYER_ID) return SCM(playerid,0x555555FF,"Вы не таксист или не принимали вызов!");
    SetPVarInt(playerid,"Number",2), ShowPlayerDialog(playerid,28,DIALOG_STYLE_INPUT,"{1faee9}Отказ от вызова","{ffffff}Если вы действительно хотите отменить заказ, пожалуйста {03c03c}укажите причину","Отклонить","Отмена");
	return true;
}

CMD:fare(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	if(Fares[GetPlayerVehicleID(playerid)] > 0) { Delete3DTextLabel(Fare[GetPlayerVehicleID(playerid)]), Fares[GetPlayerVehicleID(playerid)] = 0, SCM(playerid,0xFFFFFFFF,"Рабочий день {1faee9}окончен!"); return true; }
	if(GetPVarInt(playerid,"TaxiJob") == 0) return SCM(playerid,0xFFFFFFFF,"Вы не работаете таксистом!");
	if(GetPVarInt(playerid,"TaxiCall") != INVALID_PLAYER_ID) return SCM(playerid,0xFFFFFFFF,"Сначала закончите заказ!");
	if(sscanf(params,"d",params[0])) return SCM(playerid,0xFFFFFFFF,"Введите: {1faee9}/fare [тариф]");
	if(params[0] < 10 || params[0] > 500) return SCM(playerid,0xFFFFFFFF,"Тариф за проезд не должен быть {1faee9}не менее 10$ и не более 500$!");
	if(Fares[GetPlayerVehicleID(playerid)] == 0) {
		new fstring[32];
		Fares[GetPlayerVehicleID(playerid)] = params[0];
		fcor GetVehiclePos(GetPlayerVehicleID(playerid),x,y,z);
		format(fstring,sizeof(fstring),"TAXI\n{1faee9}Тариф: {ffffff}%d$",params[0]);
		Fare[GetPlayerVehicleID(playerid)] = Create3DTextLabel(fstring, 0xFFC400FF, x, y, z+1.3, 40.0, 0, 0), Attach3DTextLabelToVehicle(Fare[GetPlayerVehicleID(playerid)],GetPlayerVehicleID(playerid),0.0,0.0,1.7);
	}
	return true;
}

CMD:skills(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	format(strock,sizeof(strock),"Оружие\t\tВыстрелено\n\n{ffffff}SDPistol:\t\t %d\nDeagle:\t\t %d\nShotgun:\t\t %d\nMP5:\t\t\t %d\nAK47:\t\t\t %d\nM4A1:\t\t\t %d",Player[playerid][Skill][1],
	Player[playerid][Skill][2],Player[playerid][Skill][3],Player[playerid][Skill][7],Player[playerid][Skill][8],Player[playerid][Skill][9]);
	ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{1faee9}Навыки владения оружием",strock,"Ок","");
	return true;
}

CMD:gate(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
    if(!IsPlayerInRangeOfPoint(playerid,15.0,126.9390030,1942.5059814,18.1000004) && !IsPlayerInRangeOfPoint(playerid,15.0,94.1539993,1914.4200439,17.2299995)
	&& !IsPlayerInRangeOfPoint(playerid,15.0,349.3800049,1800.5159912,17.2299995) && !IsPlayerInRangeOfPoint(playerid,15.0,1544.8372,-1627.1372,13.3828)) return SCM(playerid,0xFFFFFFFF,"Необходимо находиться {1faee9}возле ворот!");
    if(IsPlayerInRangeOfPoint(playerid,15.0,126.9390030,1942.5059814,18.1000004)) {
        if(Player[playerid][pFraction][1] != 6 && Player[playerid][pFraction][1] != 10) return SCM(playerid,0xFFFFFFFF,"У вас {03c03c}нет ключа для открытия этих ворот!");
		if(gatearmy[0][1] == 0) MoveDynamicObject(gatearmy[0][0],119.4879989624, 1942.5200195313, 18.10000038147,2.0,-1000.0,-1000.0,-1000.0), gatearmy[0][1] = 1;
		else MoveDynamicObject(gatearmy[0][0],126.9390030,1942.5059814,18.1000004,2.0,-1000.0,-1000.0,-1000.0), gatearmy[0][1] = 0;
	}
    if(IsPlayerInRangeOfPoint(playerid,15.0,94.1539993,1914.4200439,17.2299995)) {
        if(Player[playerid][pFraction][1] != 6 && Player[playerid][pFraction][1] != 10) return SCM(playerid,0xFFFFFFFF,"У вас {03c03c}нет ключа для открытия этих ворот!");
		if(gatearmy[1][1] == 0) MoveDynamicObject(gatearmy[1][0],93.981002807617, 1905.833984375, 17.229999542236,2.0,-1000.0,-1000.0,-1000.0), gatearmy[1][1] = 1;
		else MoveDynamicObject(gatearmy[1][0],94.1539993,1914.4200439,17.2299995,2.0,-1000.0,-1000.0,-1000.0), gatearmy[1][1] = 0;
	}
	if(IsPlayerInRangeOfPoint(playerid,15.0,349.3800049,1800.5159912,17.2299995)) {
	    if(Player[playerid][pFraction][1] != 6 && Player[playerid][pFraction][1] != 10) return SCM(playerid,0xFFFFFFFF,"У вас {03c03c}нет ключа для открытия этих ворот!");
		if(gatearmy[2][1] == 0) MoveDynamicObject(gatearmy[2][0],340.98599243164, 1794.3260498047, 17.229999542236,2.0,-1000.0,-1000.0,-1000.0), gatearmy[2][1] = 1;
		else MoveDynamicObject(gatearmy[2][0],349.3800049,1800.5159912,17.2299995,2.0,-1000.0,-1000.0,-1000.0), gatearmy[2][1] = 0;
	}
	return true;
}

CMD:haul(playerid,params[]) {
	if(Player[playerid][pFraction][1] != 6) return true;
	if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 433) return ShowPlayerDialog(playerid,31,DIALOG_STYLE_LIST,"{03c03c}Перевозки","{ffffff}Загрузить комплекты на складе LS\nЗагрузить оружие на складе армии\nРазгрузка на складе армии\nРазгрузка на складе организации\nОтключить метку","Далее","Отмена");
	if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 455) return ShowPlayerDialog(playerid,33,DIALOG_STYLE_LIST,"{03c03c}Продуктовые перевозки","{ffffff}Загрузить пайки на складе ELQ-BK\nРазгрузка на складе столовой армии\nОтключить метку","Далее","Отмена");
	return true;
}

CMD:kick(playerid,params[]) {
	if(Player[playerid][pAdmin] < 1 || !Player[playerid][Aat]) return true;
	if(sscanf(params,"us[24]",params[0],params[1])) return SCM(playerid,0xFFFFFFFF,"Введите: {1faee9}/kick [id] [причина]");
	if(Player[params[0]][pAdmin] > 1) return SCM(playerid,0xFFFFFFFF,"Кикнуть {1faee9}модератора невозможно!");
    format(strock,116,"%s был кикнут администратором %s. Причина: %s",Name(params[0]),Name(playerid),params[1]);
	SendClientMessageToAll(COLOR_LIGHTRED,strock);
	KickEx(params[0]);
	return true;
}

CMD:skick(playerid,params[]) {
	if(Player[playerid][pAdmin] < 3 || !Player[playerid][Aat]) return true;
	if(sscanf(params,"u",params[0])) return SCM(playerid,0xFFFFFFFF,"Введите: {1faee9}/skick [id]");
	if(Player[params[0]][pAdmin] > 1) return SCM(playerid,0xFFFFFFFF,"Кикнуть {1faee9}модератора невозможно!");
	SendClientMessage(playerid,COLOR_GRAD2,"Игрок был кикнут тихим киком!");
	KickEx(params[0]);
	return true;
}

CMD:mute(playerid,params[]) {
    if(Player[playerid][pAdmin] < 2 || !Player[playerid][Aat]) return true;
	if(sscanf(params,"uds[24]",params[0],params[1],params[2])) return SCM(playerid,0xFFFFFFFF,"Введите: {1faee9}/mute [id] [минуты] [причина]");
	if(params[1] == 0) { Player[params[0]][pMute] = 0, SCM(params[0],0xFFFFFFFF,"С вас {1faee9}снят бан чата!"), SCM(playerid,0xFFFFFFFF,"Бан чата {1faee9}снят с игрока!"); return true; }
	format(strock,136,"%s получил бан чата от администратора %s на %d минут. Причина: %s",Name(params[0]),Name(playerid),params[1],params[2]);
	SendClientMessageToAll(COLOR_LIGHTRED,strock);
	Player[params[0]][pMute] = gettime()+params[1];
	return true;
}

CMD:tp(playerid,params[]) {
    if(Player[playerid][pAdmin] < 2  || !Player[playerid][Aat]) return true;
    ShowPlayerDialog(playerid,32,DIALOG_STYLE_LIST,"{03c03c}Телепорт-Лист","{ffffff}Spawn LS-1\nSpawn LS-2\nGrove\nBallas\nVagos\nAztec\nRifa\nArmy LV\nLS Warehouse\nМэрия\nДальнобойщики\nАвтошкола\nSpawn SF-1\nSpawn LV-1","Выбор","Отмена");
	return true;
}

CMD:setweather(playerid,params[]) {
	if(Player[playerid][pAdmin] < 4 || !Player[playerid][Aat]) return true;
	if(sscanf(params,"d",params[0])) return SCM(playerid,0xFFFFFFFF,"Введите: {1faee9}/setweather [id погоды]");
	Timer[1] = gettime()+1800, setproperty(0, "sw", params[0]), SetWeather(getproperty(0, "sw", _));
	return true;
}

CMD:warehouse(playerid,params[]) {
	if(Player[playerid][pFraction][1] == 0) return true;
	new string[44];
	switch(Player[playerid][pFraction][1]) {
	    case 6: {
			if(LVW == 0) string = "{ff0000}Требуются комплекты!";
			else if(LVW <= 3500) string = "{ff0000}Комплекты кончаются!";
			else if(LVW <= 5000) string = "{FF7300}Комплектов хватит на 20-30 человек!";
			else if(LVW <= 10000) string = "{FFB300}Недостаточно для развозки!";
			else if(30000 <= LVW >= 30000) string = "{04F200}Отличное!";
			format(strock,170,"{ffffff}На главном складе:\t\t {03c03c}%d комплектов\n{ffffff}На складе столовой:\t\t {03c03c}%d пайков\n\n\n{ffffff}Состояние склада:\t\t %s",LVW,LVWE,string);
			ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{03c03c}Склады армии",strock,"Ок","");
		}
	}
	return true;
}

CMD:sparmy(playerid,params[]) {
	if(Player[playerid][pFraction][1] != 6) return true;
	if(Player[playerid][pFraction][2] < 3) return SCM(playerid,0xFFFFFFFF,"Наблюдение за армией разрешено только со звания: {03c03c}Сержант!");
	if(GetPVarInt(playerid,"SPArmy") > 0) { TogglePlayerControllable(playerid,1), SetCameraBehindPlayer(playerid), SetPVarInt(playerid,"SPArmy",0); return true; }
	if(!IsPlayerInRangeOfPoint(playerid,1.5,246.8405,1860.9401,14.0840)) return SCM(playerid,0xFFFFFFFF,"Необходимо находиться {03c03c}возле аппарата, в бункере!");
	SetPVarInt(playerid,"SPArmy",1), TogglePlayerControllable(playerid,0), SetPlayerCameraPos(playerid,138.064208,1939.588256,32.955593), SetPlayerCameraLookAt(playerid,96.528137,1919.184570,18.645965,2);
	SCM(playerid,0xFFFFFFFF,"Режим наблюдения {03c03c}включен!"), SCM(playerid,0xFFFFFFFF,"Для переключения между камерами используйте пр.Кнопку мыши (RMB)"), SCM(playerid,0xFFFFFFFF,"Для выхода из режима наблюдения {03c03c}повторно введите /sparmy");
	return true;
}

CMD:putback(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
    if(GetPVarInt(playerid,"Ammo") == 0 && GetPVarInt(playerid,"EatBox") == 0) return SCM(playerid,0x03c03cFF,"У вас {ffffff}нет с собой комплектов!");
	RemovePlayerAttachedObject(playerid,0), SetPlayerAttachedObject(playerid, 0, 3026, 1, -0.230000, -0.069999, 0.000000, 0.000000, 0.000000, 0.000000, 1.220000, 0.930999, 1.052999), SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE);
 	return true;
}


CMD:wanted(playerid,params[]) {
	if(!PlayerCF(playerid)) return true;
	if(sscanf(params,"us[32]",params[0],params[1])) return SCM(playerid,COLOR_WHITE,"Введите: {1faee9}/wd [id] [Причина розыска]");
	if(Player[params[0]][pWanted] >= 6) return  SCM(playerid,COLOR_WHITE,"У данного человека уже {1faee9}максимальный уровень розыска.");
	if(PlayerCF(params[0]) || Player[playerid][pFraction][1] == 11) return SCM(playerid,COLOR_WHITE,"Данный человек законослужащий!");
	Player[params[0]][pWanted] += 1;
	SetPlayerWantedLevel(params[0],Player[params[0]][pWanted]), SCM(params[0],COLOR_WHITE,"{ff8800}Вы совершили преступление и были добавлены в список разыскиваемых!");
	format(strock,142,"[R] %s: %s совершил преступление: %s. Будьте бдительны!",Name(playerid),Name(params[0]),params[1]);
	for(new i = 10; i > 7; i--) SendRadioMessage(i, 0x1faee9AA, strock);
	PlayCrimeReportForPlayer(playerid, params[0], 21);
	return true;
}

CMD:unwanted(playerid,params[]) {
 	if(!PlayerCF(playerid)) return true;
	if(sscanf(params,"u",params[0])) return SCM(playerid,COLOR_WHITE,"Введите: {1faee9}/unwanted [id]");
	if(Player[params[0]][pWanted] == 0) return  SCM(playerid,COLOR_WHITE,"Данный человек {1faee9}не в розыске.");
	Player[params[0]][pWanted] -= 1, SetPlayerWantedLevel(params[0],Player[params[0]][pWanted]);
	return true;
}

CMD:arrest(playerid,params[]) {
    if(!PlayerCF(playerid)) return true;
    if(sscanf(params,"u",params[0])) return SCM(playerid,COLOR_WHITE,"Введите: {1faee9}/arrest [id]");
	if(GetPVarInt(params[0],"Cuffed") == 1) return SCM(playerid,COLOR_WHITE,"Данный человек {1faee9}уже аррестован!");
	if(!PlayerToPlayer(playerid, params[0], 2.0)) return SendClientMessage(playerid, 0x1faee9FF, "Вы слишком далеко.");
	SetPVarInt(params[0],"Cuffed",1), SetPVarInt(params[0],"CuffedID",playerid);
	SetPlayerAttachedObject(params[0], 1, 19418, 6, 0.085000, 0.041999, 0.002999, 0.000000, 0.000000, 87.199981, 0.955000, 1.142999, 1.457999);
 	SetPlayerSpecialAction(params[0],SPECIAL_ACTION_CUFFED);
 	SetPlayerChatBubble(playerid,"проводит задержание преступника",COLOR_PURPLE,30.0,5000);
 	ApplyAnimation(playerid,"INT_HOUSE","wash_up",4.1,0,0,0,0,0), SetTimerEx("RukiOff", 1200, false, "d", playerid);
    return true;
}

CMD:let(playerid,params[]) {
    if(!PlayerCF(playerid)) return true;
    if(sscanf(params,"u",params[0])) return SCM(playerid,COLOR_WHITE,"Введите: {1faee9}/let [id]");
	if(GetPVarInt(params[0],"Cuffed") == 0) return SCM(playerid,COLOR_WHITE,"Данный человек {1faee9}не аррестован!");
	if(!PlayerToPlayer(playerid, params[0], 2.0)) return SendClientMessage(playerid, 0x1faee9FF, "Вы слишком далеко.");
	SetPVarInt(params[0],"Cuffed",0);
	RemovePlayerAttachedObject(params[0],1);
	SetPlayerSpecialAction(params[0],SPECIAL_ACTION_NONE);
	ApplyAnimation(playerid,"INT_HOUSE","wash_up",4.1,0,0,0,0,0), SetTimerEx("RukiOff", 1200, false, "d", playerid);
	return true;
}

CMD:jail(playerid,params[]) {
    if(!PlayerCF(playerid)) return true;
    if(sscanf(params,"ud",params[0],params[1])) return SCM(playerid,COLOR_WHITE,"Введите: {1faee9}/jail [id] [срок заключения (минуты)]");
    if(params[1] < 1 || params[1] > 3600) return SCM(playerid,-1,"Срок не должен быть менее 1-й минуты и не более часа ( 60 )");
    if(Player[params[0]][pWanted] == 0) return SCM(playerid,-1,"Данный {1faee9}человек законопослушен и не находится в розыске!");
    if(Player[params[0]][pWanted] > 6) return SCM(playerid,-1,"Данный {1faee9}человек уже находится под арестом!");
    if(!PlayerToPlayer(playerid, params[0], 2.0)) return SendClientMessage(playerid, 0x1faee9FF, "Вы слишком далеко.");
	if(!IsPlayerInRangeOfPoint(playerid,15.0,264.7275,78.5209,1001.0391)) return SCM(playerid,COLOR_WHITE,"Необходимо {1faee9}находиться возле тюремной решетки!");
	SetPlayerWantedLevel(params[0],0);
	Player[params[0]][pWanted] = ((params[1])*60)+7;
	SpawnPlayer(params[0]);
	SCM(playerid,-1,"Преступник был {ff0000}осужден.");
 	SCM(params[0],-1,"Вы были осуждены за преступление! {ff0000}Отбывайте ваш срок в тюрьме вашего города.");
	return true;
}

CMD:alarm(playerid,params[]) {
    if(Player[playerid][pFraction][1] != 6 && Player[playerid][pFraction][2] < 7) return true;
	if(!Alarm) {
     	Area = CreateDynamicSphere(222.0781,1930.0691,28.3515,350*2.0,-1,-1,-1);
      	Alarm = true;
       	SendClientMessage(playerid,0xFF0000FF,"Тревога!");
       	Timer[2] = gettime()+45;
       	SendRadioMessage(6, 0xFF0000FF,"[R] Тревога: Общая тревога!");
	}
  	else {
  		foreach(new i : Player) if(IsPlayerInDynamicArea(i,Area)) StopAudioStreamForPlayer(i);
    	DestroyDynamicArea(Area);
     	Alarm = false;
      	SendClientMessage(playerid,0x03c03cFF,"Режим тревоги был снят.");
      	SendRadioMessage(6, 0x03c03cFF,"[R] Тревога: Режим тревоги был снят!");
	}
 	return true;
}

CMD:find(playerid,params[]) {
	if(!PlayerCF(playerid)) return true;
	if(PlayerCop(playerid) && Player[playerid][pFraction][2] < 6) return SCM(playerid,0x1faee9FF,"Эта функция {1faee9}не доступна для вашей должности!");
	if(sscanf(params,"u",params[0])) return SCM(playerid,0x1faee9FF,"Используйте: {ffffff}/find [id]");
	if(!IsPlayerConnected(params[0]) || params[0] == playerid) return SCM(playerid,0xFFFFFF66,"Данного человека не получилось засечь!");
	fcor GetPlayerPos(params[0],x,y,z);
	SCM(playerid,0xFFFFFFFF,"Приблизительное местонахождение человека {5083B2}отмечено на вашем GPS приемнике!");
	SetPlayerCheckpoint(playerid,x,y,z,2.0);
	return true;
}

CMD:usedrugs(playerid,params[]) {
    if(GetPVarInt(playerid,"UseDrugs") > gettime()) return SCM(playerid,0xAC7575FF,"Если вы будите употреблять наркотики так часто - вы можете вскоре погибнуть!");
	new hour,m;
	gettime(hour,m,m);
	if(!Player[playerid][PlayerLogged]) return true;
	if(Player[playerid][pDrugs] == 0) return SCM(playerid,0xCA7575FF,"У вас нет наркотиков!");
	if(sscanf(params,"d",params[0])) return SCM(playerid,0xFFFFFFFF,"Используйте: {1faee9}/usedrugs [количество]");
	if(Player[playerid][pDrugs] < params[0]) return SCM(playerid,0xCA7575FF,"У вас нет столько наркотиков!");
	if(params[0] < 1 || params[1] > 10) return SCM(playerid,0xFFFFFFFF,"Количество не должно быть меньше 1 и больше 10!");
	new Float:health;
	GetPlayerHealth(playerid,health);
	Player[playerid][pDrugs] -= params[0];
	ApplyAnimation(playerid,"SMOKING","M_smk_drag",4.1,0,0,0,0,0,1);
	SetPlayerDrunkLevel(playerid, 5000);
	if(hour > 5 && hour < 20) SetPlayerWeather(playerid, 188);
	SetPVarInt(playerid,"DrugTime",31);
	SetPlayerHealth(playerid,health+params[0]*10);
    SetPlayerChatBubble(playerid, "употребил наркотик", COLOR_PURPLE, 30.0, 4000);
    SetPVarInt(playerid,"UseDrugs",gettime()+20);
	return true;
}

CMD:drugs(playerid,params[]) Player[playerid][pDrugs] = 500;

CMD:search(playerid,params[]) {
	if(!PlayerCF(playerid)) return true;
	if(PlayerCop(playerid) && Player[playerid][pFraction][2] < 3) return SCM(playerid,0x1faee9FF,"Эта функция {1faee9}не доступна для вашей должности!");
	if(sscanf(params,"u",params[0])) return SCM(playerid,0xFFFFFFFF,"Используйте: {1faee9}/search [id]");
	if(!IsPlayerConnected(params[0])) return true;
	if(!PlayerToPlayer(playerid, params[0], 2.0)) return SendClientMessage(playerid, 0x1faee9FF, "Вы слишком далеко.");
	new string[156];
	SetPVarInt(playerid,"SearchID",params[0]);
    ApplyAnimation(playerid,"INT_HOUSE","wash_up",4.1,0,0,0,0,0), SetTimerEx("RukiOff", 1200, false, "d", playerid);
	format(string,sizeof(string),"{ffffff}Найденные предметы:\n\nНаркотики:\t\t{CA7575}%d гр.\n{ffffff}Комплекты:\t\t{CA7575}%d к.\n\n{ffffff}Для того чтобы изъять предметы нажмите {CA7575}'Изъять'",Player[params[0]][pDrugs],GetPVarInt(playerid,"Ammo"));
	ShowPlayerDialog(playerid,35,DIALOG_STYLE_MSGBOX,"{03c03c}Обыск",string,"Изъять","Отмена");
	return true;
}

CMD:admins(playerid,params[]) {
	if(Player[playerid][pAdmin] < 1 || !Player[playerid][Aat]) return true;
	new admins[38];
	SCM(playerid,0x1faee9FF,"Администрация Online:");
	foreach(new i : Player) {
	    if(Player[i][pAdmin] < 1) continue;
	    format(admins,sizeof(admins),"%s[%i]: %i lvl",Name(i),i,Player[i][pAdmin]), SCM(playerid,0xB4FFFFFF,admins);
	}
	return true;
}

CMD:members(playerid,params[]) {
	if(Player[playerid][pFraction][1] == 0) return true;
	new members[52+1], post[16];
	SCM(playerid,0x1faee9FF,"Рабочие вашей организации Online:");
	foreach(new i : Player) {
		if(Player[i][pFraction][1] == Player[playerid][pFraction][1]) {
			switch(Player[i][pFraction][1]) {
				case 1: {
				    switch(Player[i][pFraction][2]) {
				        case 1: post = "Beginner";
				        case 2: post = "Buddy";
				        case 3: post = "Killer";
				        case 4: post = "Dog";
				        case 5: post = "Drug dealer";
				        case 6: post = "Crazy";
				        case 7: post = "Initiator";
				        case 8: post = "Bloody";
				        case 9: post = "Chief";
				        case 10: post = "Father";
				}   }
				case 2: {
				    switch(Player[i][pFraction][2]) {
				        case 1: post = "Cock";
				        case 2: post = "Dog";
				        case 3: post = "Kracker";
				        case 4: post = "Hight-Roller";
				        case 5: post = "Drug dealer";
				        case 6: post = "Scoundrel";
				        case 7: post = "Killer";
				        case 8: post = "Junior Boss";
				        case 9: post = "Old Gangster";
				        case 10: post = "Big Willy";
				}   }
				case 3: {
					switch(Player[i][pFraction][2]) {
						case 10: post = "Padre";
						case 9: post = "Son Pandillas";
						case 8: post = "Vigilante";
						case 7: post = "Tirador";
						case 6: post = "Peligroso";
						case 5: post = "Comerciante";
						case 4: post = "Desconocido";
						case 3: post = "Iniciador";
						case 2: post = "Bandido";
						case 1: post = "Esperanto";
				}   }
				case 4: {
					switch(Player[i][pFraction][2]) {
						case 10: post = "Ringleader";
						case 9: post = "Native Latinos";
						case 8: post = "Bootbkack";
						case 7: post = "Thug";
						case 6: post = "Hoodlum";
						case 5: post = "Trafficker";
						case 4: post = "Soladato";
						case 3: post = "Verificado";
						case 2: post = "Novato";
						case 1: post = "Stanger";
				}   }
				case 5: {
					switch(Player[i][pFraction][2]) {
						case 10: post = "Papi";
						case 9: post = "Rifecado";
						case 8: post = "Gracio";
						case 7: post = "Oneci";
						case 6: post = "Eltoro";
						case 5: post = "Gerendo";
						case 4: post = "Pantalones";
						case 3: post = "Elcostro";
						case 2: post = "Elmoro";
						case 1: post = "Mestro";
				}   }
				case 6: {
					switch(Player[i][pFraction][2]) {
						case 10: post = "Генерал";
						case 9: post = "Полковник";
						case 8: post = "Подполковник";
						case 7: post = "Майор";
						case 6: post = "Капитан";
						case 5: post = "Лейтенант";
						case 4: post = "Штаб-Сержант";
						case 3: post = "Сержант";
						case 2: post = "Капрал";
						case 1: post = "Рядовой";
				}   }
				case 7..9: {
					switch(Player[i][pFraction][2]) {
						case 10: post = "Шеф";
						case 9: post = "Зам.Шефа";
						case 8: post = "Капитан";
						case 7: post = "Лейтенант";
						case 6: post = "Детектив";
						case 5: post = "Глава SWAT";
						case 4: post = "Боец SWAT";
						case 3: post = "Сержант";
						case 2: post = "Офицер";
						case 1: post = "Постовой";
				}   }
				case 10: {
					switch(Player[i][pFraction][2]) {
						case 10: post = "Ген.Прокурор";
						case 9: post = "Директор FBI";
						case 8: post = "Секретный Агент";
						case 7: post = "Спец.Агент";
						case 6: post = "Старший Агент";
						case 5: post = "Агент Разведки";
						case 4: post = "Агент";
						case 3: post = "Младший Агент";
						case 2: post = "Помощник Агента";
						case 1: post = "Оп.Работник";
				}   }
				case 15: {
				    switch(Player[i][pFraction][2]) {
				    	case 10: post = "Вор в законе";
						case 9: post = "Криминальный";
						case 8: post = "Координатор";
						case 7: post = "Гангстер";
						case 6: post = "Теневик";
						case 5: post = "Рецидивист";
						case 4: post = "Солдат";
						case 3: post = "Преступник";
						case 2: post = "Рекетир";
						case 1: post = "Бандит";
				}   }
				case 16: {
				    switch(Player[i][pFraction][2]) {
				    	case 10: post = "Сен Сей";
						case 9: post = "Такаши";
						case 8: post = "Тсу Ши";
						case 7: post = "Джи Зу";
						case 6: post = "Пак Тсе Син";
						case 5: post = "Шанхай";
						case 4: post = "Лао Бан";
						case 3: post = "Шан-Ши";
						case 2: post = "Лунг Тао";
						case 1: post = "Чанг Лао";
				}   }
				case 17: {
				    switch(Player[i][pFraction][2]) {
					    case 10: post = "Глав.Врач";
						case 9: post = "Зав.Отделением";
						case 8: post = "Хирург";
						case 7: post = "Доктор";
						case 6: post = "Нарколог";
						case 5: post = "Ординатор";
						case 4: post = "Врач";
						case 3: post = "Медик";
						case 2: post = "Санитар";
						case 1: post = "Интерн";
				}   }
			}
			format(members,sizeof(members),"%s[%d] - %s",Name(i),i,post), SCM(playerid,0xB4FFFFFF,members);
		}
	}
	return true;
}

#if !defined CopyRightString
    #error CopyRight Panteleev has been Deleted!
#endif


CMD:ooc(playerid, params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
 	if(isnull(params)) return SendClientMessage(playerid, COLOR_GRAD2, "Используйте: /o(oc) [NON-RP чат]");
 	new string[128+1];
    format(string, sizeof(string), "(( %s[%d]: %s ))",Name(playerid),playerid,params);
    //SendClientsMessage(30.0, playerid, string, 0x95B7B7FF,0x95B7B7FF,0x95B7B7FF);
	ProxDetector(playerid, 30.0, COLOR_WHITE, string);
	
	SetPlayerChatBubble(playerid,string,0x95B7B7FF,30.0,4000);
    return true;
}
alias:ooc("o");

#define LawCar(%0)  GetPlayerVehicleID(%0) >= pd[0] && GetPlayerVehicleID(%0) <= pd[1]

CMD:wp(playerid,params[]) {
	if(!Player[playerid][PlayerLogged] || !PlayerCF(playerid)) return true;
	if(LawCar(playerid) || IsPlayerInRangeOfPoint(playerid,50.0,238.5037,77.0737,1005.0391)) {
	    new pc[38];
		SCM(playerid,0xD85252FF,"Разыскиваются:");
		foreach(new i : Player) if(0 < Player[i][pWanted] < 6) format(pc,sizeof(pc),"%s[%d]: %d LW",Name(i),i,Player[i][pWanted]), SCM(playerid,0xDF9D9DFF,pc);
	}
	else SCM(playerid,0xAC7575FF,"Необходимо находиться в служебном автомобиле либо в отделении!");
	return true;
}

CMD:passport(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	if(sscanf(params,"u",params[0])) return SCM(playerid,-1,"Используйте: {1faee9}/passport [id]");
	if(!IsPlayerConnected(params[0])) return true;
	if(!PlayerToPlayer(playerid, params[0], 2.0)) return SendClientMessage(playerid,0x1faee9FF,"Необходимо находиться {ffffff}рядом!");
	new fraction[11],city[14],string[180+1], wd[4];
	switch(Player[playerid][pFraction][1]) {
	    case 1..5,15,16,18: fraction = "Неизвестно";
	    case 6: fraction = "Army";
	    case 7: fraction = "LSPD";
	    case 8: fraction = "SFPD";
	    case 9: fraction = "LVPD";
	    case 10: fraction = "FBI";
	    case 11: fraction = "Мерия";
	    case 12: fraction = "Автошкола";
	    case 13: fraction = "SANews";
	    case 14: fraction = "CNN";
	    case 17: fraction = "Мин.Здрав";
	    default: fraction = "Не состоит";
	}
	switch(Player[playerid][pCity]) {
	    case 1: city = "Los Santos";
	    case 2: city = "San Fierro";
	    case 3: city = "Las Venturas";
	}
	wd = (0 < Player[playerid][pWanted] < 7) ? ("Да") : ("Нет");
	format(string,sizeof(string),"{ffffff}Имя:\t\t\t%s\nЛет в штате:\t\t%d\nРазыскивается:\t%s\nТелефон:\t\t%d\nОрганизация:\t\t%s\nРанг:\t\t\t%d\nПрописка\t\t{03c03c}%s",Name(playerid),Player[playerid][pLevel], wd, Player[playerid][pPhone], fraction, Player[playerid][pFraction][2], city);
	ShowPlayerDialog(params[0],999,DIALOG_STYLE_MSGBOX,"{03c03c}Паспорт",string,"Ок","");
	
	format(string,41,"%s показал паспорт", Name(playerid));
	//SendClientsMessage(30.0,playerid,string,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	ProxDetector(playerid, 30.0, COLOR_PURPLE, string);
	
	SetPlayerChatBubble(playerid,"показал паспорт",COLOR_PURPLE,30.0,3000);
	return true;
}

CMD:addatm(playerid,params[]) {
	new Float:X,Float:Y,Float:Z;
	if(Player[playerid][pAdmin] < 5 || Player[playerid][Aat] == false) return true;
	GetPlayerPos(playerid,X,Y,Z);
	atm = CreateDynamicObject(2754,X+0.5,Y+0.5,Z,0.0,0.0,0.0);
	EditDynamicObject(playerid,atm);
	return true;
}

CMD:getinfo(playerid,params[]) {
	if(Player[playerid][pFraction][1] != 10) return true;
	if(Player[playerid][pFraction][2] < 5) return SCM(playerid,0xAC7575FF,"Вам недоступна данная функция! ( с 5 ранга )");
	if(sscanf(params,"u",params[0])) return SCM(playerid,-1,"Используйте: {1faee9}/getinfo [id]");
	if(!IsPlayerConnected(params[0])) return true;
	new fraction[11],city[14],string[220+1], wd[4], no[4];
	switch(Player[params[0]][pFraction][1]) {
	    case 1..5: fraction = "Неизвестно";
	    case 6: fraction = "Army";
	    case 7: fraction = "LSPD";
	    case 8: fraction = "SFPD";
	    case 9: fraction = "LVPD";
	    case 10: fraction = "FBI";
	    case 11: fraction = "Мерия";
	    case 12: fraction = "Автошкола";
	    case 13: fraction = "News SF";
	    case 14: fraction = "News LV";
	    case 15: fraction = "Мин.Здрав";
	    default: fraction = "Не состоит";
	}
	switch(Player[params[0]][pCity]) {
	    case 1: city = "Los Santos";
	    case 2: city = "San Fierro";
	    case 3: city = "Las Venturas";
	    default: city = "Los Santos";
	}
	wd = (0 < Player[params[0]][pWanted] < 7) ? ("Да") : ("Нет");
	no = "Нет";
	string = "{ffffff}Имя:\t\t\t%s\nЛет в штате:\t\t%d\nРазыскивается:\t%s\nТелефон:\t\t%d\nОрганизация:\t\t%s\nРанг:\t\t\t%d\nПрописка\t\t{03c03c}%s\nДом:\t\t\t{03c03c}";
	strcat(string, (Player[playerid][pHouse] != 9999) ? ("%d") : ("Нет"));
	strcat(string, (Player[playerid][pCar][0] != -1) ? ("\nАвто:\t\t\t{03c03c}%d") : ("\nАвто:\t\t\t{AC7575}Нет"));
	format(string,sizeof(string),string,Name(params[0]),Player[params[0]][pLevel], wd, Player[params[0]][pPhone], fraction, Player[params[0]][pFraction][2], city, (Player[params[0]][pHouse] != 9999) ? Player[params[0]][pHouse] : -1 ,Player[params[0]][pCar][0]);
	ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"{03c03c}Информация о человеке",string,"Ок","");
	
	format(string,41,"%s пользуется КПК", Name(playerid));
	//SendClientsMessage(30.0,playerid,string,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	ProxDetector(playerid, 30.0, COLOR_PURPLE, string);
	
	SetPlayerChatBubble(playerid,"пользуется КПК",COLOR_PURPLE,30.0,3000);
	return true;
}

CMD:mask(playerid,params[]) {
	if(GetPVarInt(playerid,"Mask") == 1) {
	    SetPVarInt(playerid,"Mask",0), FractionColor(playerid);
        
		format(strs,41,"%s снял маску", Name(playerid));
		//SendClientsMessage(30.0,playerid,strs,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		ProxDetector(playerid, 30.0, COLOR_PURPLE, strs);
		
		SetPlayerChatBubble(playerid,"снял маску с лица",COLOR_PURPLE,30.0,3000);
		RemovePlayerAttachedObject(playerid,0);
		foreach(new i : Player) if(IsPlayerStreamedIn(i,playerid)) ShowPlayerNameTagForPlayer(i,playerid,1);
		return true;
	}
	if(Player[playerid][pFraction][1] != 10) return true;
	SetPVarInt(playerid,"Mask",1);
	SetPlayerAttachedObject(playerid, 0, 19163, 2, 0.053999, 0.029000, 0.003000, 1.600002, 87.599967, -173.800064, 1.122001, 1.228003, 1.387001);
 	
	format(strs,41,"%s надел маску", Name(playerid));
	//SendClientsMessage(30.0,playerid,strs,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	ProxDetector(playerid, 30.0, COLOR_PURPLE, strs);
	
	SetPlayerChatBubble(playerid,"надел маску на лицо",COLOR_PURPLE,30.0,3000);
	SetPlayerColor(playerid,0x00000000);
	foreach(new i : Player) if(IsPlayerStreamedIn(i,playerid)) ShowPlayerNameTagForPlayer(i,playerid,0);
	return true;
}

CMD:satellite(playerid,params[]) {
    if(Player[playerid][pFraction][1] != 10) return true;
    if(Player[playerid][pFraction][2] < 5) return SCM(playerid,0xAC7575FF,"Вам недоступна данная функция! ( с 5 ранга )");
    if(GetPVarInt(playerid,"FBIsp") == 1) { TogglePlayerSpectating(playerid,0), SetPVarInt(playerid,"FBIsp",0), SpawnPlayer(playerid); return true; }
	if(!IsPlayerInRangeOfPoint(playerid,2.0,1080.7931,1068.1979,1018.2078)) return SCM(playerid,0xAC7575FF,"Необходимо находиться возле пункта слежки!");
	if(sscanf(params,"u",params[0])) return SCM(playerid,-1,"Используйте: {1faee9}/satellite [id]");
	if(params[0] == playerid || !Player[playerid][PlayerLogged]) return true;
	if(GetPlayerInterior(params[0]) != 0 || GetPlayerVirtualWorld(params[0]) != 0) return SCM(playerid,0xAC7575FF,"Данная персона находится в здании!");
	fcor
	GetPlayerPos(params[0],x,y,z);
	SetPVarInt(playerid,"FBIsp",1), SetPVarInt(playerid,"FBIspID",params[0]);
	
	format(strs,50,"%s пользуется спутником", Name(playerid));
	//SendClientsMessage(30.0,playerid,strs,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	ProxDetector(playerid, 30.0, COLOR_PURPLE, strs);
	
	SetPlayerChatBubble(playerid,"пользуется спутником",COLOR_PURPLE,30.0,3000);
	TogglePlayerSpectating(playerid, 1);
	SetPlayerVirtualWorld(playerid,0);
    PlayerSpectatePlayer(playerid, params[0], SPECTATE_MODE_FIXED);
	SetPlayerCameraPos(playerid,x,y,z+35.0);
 	SetPlayerCameraLookAt(playerid,x,y,z,CAMERA_CUT);
 	SetPVarInt(playerid,"Recon",2);
    return true;
}

CMD:setleader(playerid,params[]) {
	if(Player[playerid][pFraction][0] != 11) return true;
	if(sscanf(params,"u",params[0])) return SCM(playerid,0xFFFFFFFF,"Используйте: {1faee9}/setleader [id]");
	if(params[0] == playerid || !Player[playerid][PlayerLogged]) return true;
	if(Player[params[0]][pFraction][1] == 0 || Player[params[0]][pFraction][1] == 11) return SCM(playerid,0x1faee9FF,"Данный игрок {ffffff}нигде не состоит, либо состоит в Мэрии!");
    if(!PlayerToPlayer(playerid, params[0], 4.0)) return SendClientMessage(playerid,0x1faee9FF,"Необходимо находиться {ffffff}рядом!");
    new fraction[14];
    switch(Player[params[0]][pFraction][1]) {
	    case 6: fraction = "Army";
	    case 7: fraction = "LSPD";
	    case 8: fraction = "SFPD";
	    case 9: fraction = "LVPD";
	    case 10: fraction = "FBI";
	    case 12: fraction = "Автошкола";
		case 13: fraction = "Мин.Здрав";
	
	}
	SetPVarInt(playerid,"SearchID",params[0]);
	format(strs,142,"{ffffff}Вы действительно хотите назначить {1faee9}%s {ffffff}назначить контролировать организацию {03c03c}%s?",Name(params[0]),fraction);
	ShowPlayerDialog(playerid,46,DIALOG_STYLE_MSGBOX,"{1faee9}Назначение главы",strs,"Да","Нет");
	return true;
}



CMD:advertise(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	if(Player[playerid][pLevel] < 2) return SCM(playerid,0xAC7575FF,"Объявление можно отправить только после 2-х годового проживания в штате!");
	if(GetPVarInt(playerid,"Advert") == 1) return SCM(playerid,0xFFFFFFFF,"Вы уже подали объявление! {1faee9}Ожидайте его проверки!");
    if(isnull(params)) return SCM(playerid,0xFFFFFFFF,"Используйте: {1faee9}/ad(vertise) [объявление]");
    if(Player[playerid][pMoney] < strlen(params)*SymbolPrice) return SCM(playerid,0xAC7575FF,"У вас недостаточно денег для посылки объявления!");
	Player[playerid][pMoney] -= strlen(params)*SymbolPrice, GameTextForPlayer(playerid,"~g~Sended!",1000,3);
	strmid(Player[playerid][Advertise],params,0,strlen(params),114), SetPVarInt(playerid,"Advert",1);
	format(strs,144,"[AD] %s[%d]: %s",Name(playerid),playerid,params);
	SendRadioMessage(13,0xFFB65CFF,strs), SendRadioMessage(13,0xFFB65CFF,"[AD] Для редактирования объявления введите /e [id отправителя] или /no [id] для отмены.");
	return true;
}
alias:advertise("ad");


CMD:edit(playerid,params[]) {
	if(Player[playerid][pFraction][1] != 13) return true;
	if(119 < GetPlayerVehicleID(playerid) > 123 || !IsPlayerInRangeOfPoint(playerid,60.0,1229.9835,-952.2786,1085.0042)) return SCM(playerid,0xAC7575FF,"Вы должны находиться в студии, либо в служебном автомобиле!");
	if(sscanf(params,"u",params[0])) return SCM(playerid,0xFFFFFFFF,"Используйте: {1faee9}/e(dit) [id]");
	if(GetPVarInt(params[0],"Advert") == 0) return SCM(playerid,0xAC7575FF,"Данный человек не подавал объявлений!");
	SetPVarInt(playerid,"AdID",params[0]);
	format(strs,200,"{ffffff}%s\n\n{FFB65C}Если вы оставите поле пустым, объявление пройдет неотредактированным!",Player[params[0]][Advertise]);
	ShowPlayerDialog(playerid,50,DIALOG_STYLE_INPUT,"{FFB65C}Редакция Радио",strs,"Отправить","Отмена");
	return true;
}

CMD:no(playerid,params[]) {
    if(Player[playerid][pFraction][1] != 13) return true;
    if(119 < GetPlayerVehicleID(playerid) > 123 || !IsPlayerInRangeOfPoint(playerid,60.0,1229.9835,-952.2786,1085.0042)) return SCM(playerid,0xAC7575FF,"Вы должны находиться в студии, либо в служебном автомобиле!");
	if(sscanf(params,"u",params[0])) return SCM(playerid,0xFFFFFFFF,"Используйте: {1faee9}/no [id]");
    if(GetPVarInt(params[0],"Advert") == 0) return SCM(playerid,0xAC7575FF,"Данный человек не подавал объявлений!");
    SetPVarInt(params[0],"Advert",0), SCM(playerid,0x792800FF,"[AD] Объявление отклонено!"), SCM(playerid,0x792800FF,"Ваше объявление было отклонено!");
	return true;
}

CMD:news(playerid,params[]) {
    if(Player[playerid][pFraction][1] != 13) return true;
    new adv[91];
    SCM(playerid,0xD58000FF,"Неотредактированные объявления:");
    foreach(new i : Player) if(GetPVarInt(i,"Advert") == 1) format(adv,sizeof(adv),"%s[%d] - %s",Name(i),i,Player[i][Advertise]), SCM(playerid,0xDCA900FF,adv);
    return true;
}

CMD:int(playerid,params[]) {
    if(sscanf(params,"d",params[0])) return SCM(playerid,0xFFFFFFFF,"/int №");
    AC_SetPlayerPos(playerid,Ints[params[0]][hiX],Ints[params[0]][hiY],Ints[params[0]][hiZ]);
	SetPlayerInterior(playerid,Ints[params[0]][hiInt]);
    return true;
}

CMD:bint(playerid,params[]) {
    if(sscanf(params,"d",params[0])) return SCM(playerid,0xFFFFFFFF,"/bint №");
    AC_SetPlayerPos(playerid,BInts[params[0]][biX],BInts[params[0]][biY],BInts[params[0]][biZ]);
	SetPlayerInterior(playerid,BInts[params[0]][biInt]);
    return true;
}


CMD:lock(playerid,params[]) {
	if(sscanf(params,"d",params[0])) return SCM(playerid,-1,"Используйте: {1faee9}/lock [№ авто ( 0 - дом; 1 - аренда)]");
	if((params[0] == 0 && Player[playerid][pHouse] == 9999) || (params[0] == 1 && Player[playerid][ArendedVehicle] == INVALID_VEHICLE_ID)) return SCM(playerid,0xAC7575FF,"У вас нету дома, либо вы не арендовали авто!");
	fcor
	new car;
	car = (params[0] == 0) ? Player[playerid][PlayerCar] : Player[playerid][ArendedVehicle];
	GetVehiclePos(car, x,y,z);
	if(!IsPlayerInRangeOfPoint(playerid,3.0,x,y,z)) return SCM(playerid,0xAC7575FF,"Необходимо находиться рядом с автомобилем!");
    SetVehicleParamsEx(car, engine, lights, alarm, (!VVB<car:lock>) ? (1) : (0), bonnet, boot, objective);
	VXOR<car:lock>;
	PlayerPlaySound(playerid,24600,0.0,0.0,0.0);
	GameTextForPlayer(playerid, (VVB<car:lock>) ? ("~r~LOCK") : ("~g~OPEN") ,1000,3);
	PlayerTextDrawSetString(playerid,slock[playerid], 	(VVB<car:lock>)	? ("~r~LOCK") : ("~g~OPEN"));
	return true;
}

CMD:uptrailer(playerid,params[]) {
	if(GetPVarInt(playerid,"TruckHaul") < 1) return true;
	AttachTrailerToVehicle(Player[playerid][Trailer],GetPlayerVehicleID(playerid));
	return true;
}

CMD:settime(playerid,params[]) {
    if(Player[playerid][pAdmin] < 5 || (sscanf(params,"d",params[0]))) return true;
    SetWorldTime(params[0]);
	return true;
}

CMD:setlicense(playerid,params[]) {
    if(Player[playerid][pFraction][1] != 12) return true;
    if(sscanf(params,"u",params[0])) return SCM(playerid,0xFFFFFFFF,"Используйте: {1faee9}/setlicense [id]");
    if(!Player[params[0]][PlayerLogged]) return true;
    SetPVarInt(playerid,"SearchID",params[0]);
    ShowPlayerDialog(playerid,55,DIALOG_STYLE_LIST,"{1faee9}Выдача лицензий","Выдать/Изъять вод. удостоверение\nВыдать/Изъять лиц. на воздушный ТС","Выбор","Отмена");
	return true;
}

CMD:nullcar(playerid,params[]) {
    if(!PlayerCF(playerid) && Player[playerid][pFraction][1] != 12) return true;
    if(sscanf(params,"u",params[0])) return SCM(playerid,0xFFFFFFFF,"Используйте: {1faee9}/nullcar [id]");
	if(!Player[params[0]][PlayerLogged]) return true;
	if((Player[params[0]][Licenses] & (1<<0)) == 0) return SCM(playerid,0xAC7575FF,"Данный игрок не имеет водительского удостоверения!");
	Player[params[0]][Licenses] ^= (1<<0);
	
	format(strs,85,"%s аннулируровал вод. удостоверение у %s",Name(playerid),Name(params[0]));
	//SendClientsMessage(25.0, playerid, strs, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	ProxDetector(playerid, 25.0, COLOR_PURPLE, strs);
	
	SetPlayerChatBubble(playerid,"аннулирует вод. удостоверение",COLOR_PURPLE,25.0,2000);
	SCM(params[0],0x1faee9FF,"Ваше водительское удостоверение было аннулировано!");
	return true;
}

CMD:ticket(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	if(GetPVarInt(playerid,"Ticket") > 0) {
		if(Player[playerid][pMoney] < GetPVarInt(playerid,"Ticket")) return SCM(playerid,0xAC7575FF,"У вас недостаточно средств для оплаты штрафа!");
		Player[playerid][pMoney] -= GetPVarInt(playerid,"Ticket");
		Ware[5][wMoney] += GetPVarInt(playerid,"Ticket");
		SetPVarInt(playerid,"Ticket",0);
		SCM(playerid,0x03c03cFF,"Штраф успешно оплачен!");
		Player[playerid][pWanted]--,SetPlayerWantedLevel(playerid,Player[playerid][pWanted]);
		SCM(GetPVarInt(playerid,"TicketID"),0x03c03cFF,"Штраф был оплачен!"), Player[GetPVarInt(playerid,"TicketID")][pMoney] += percent(GetPVarInt(playerid,"Ticket"),45), GameTextForPlayer(GetPVarInt(playerid,"TicketID"),"~g~+$",1000,1);
		return true;
	}
	if(!PlayerCF(playerid)) return true;
	if(sscanf(params,"uds[24]",params[0],params[1],params[2])) return SCM(playerid,0xFFFFFFFF,"Используйте: {1faee9}/ticket [id] [сумма] [причина]");
	SCM(playerid,COLOR_POLICE,"Штраф успешно выписан!");
	format(strs,76,"Вам выписан штраф в %i$, причина: %s.",params[1],params[2]);
	SCM(params[0],COLOR_POLICE,strs);
	SCM(params[0],COLOR_POLICE,"Для оплаты используйте (( /ticket )). На срок оплаты штрафа вам присвоен +1 ур. розыска!");
	SetPVarInt(params[0],"Ticket",params[1]), SetPVarInt(params[0],"TicketID",playerid);
	if(Player[params[0]][pWanted] < 6) Player[params[0]][pWanted]++,SetPlayerWantedLevel(params[0],Player[params[0]][pWanted]);
	return true;
}

CMD:licenses(playerid,params[]) {
	if(!Player[playerid][PlayerLogged]) return true;
	if(sscanf(params,"u",params[0])) return SCM(playerid,0xFFFFFFFF,"Используйте: {1faee9}/licenses [id]");
	new l[3][5];
	l[0] = ((Player[playerid][Licenses] & (1<<0)) != 0) ? ("Есть") : ("Нет");
	l[1] = ((Player[playerid][Licenses] & (1<<1)) != 0) ? ("Есть") : ("Нет");
	l[2] = ((Player[playerid][Licenses] & (1<<2)) != 0) ? ("Есть") : ("Нет");
	format(strs,130,"{ffffff}Вод. права:\t\t{1faee9}%s\n{ffffff}Воз. права:\t\t{1faee9}%s\n{ffffff}Лицензия на оружие:\t{1faee9}%s",l[0],l[1],l[2]);
	ShowPlayerDialog(params[0],999,DIALOG_STYLE_MSGBOX,"{1faee9}Лицензии игрока",strs,"Ок","");
	return true;
}

CMD:setgunlic(playerid,params[]) {
	if(!PlayerCop(playerid)) return true;
	if(Player[playerid][pFraction][2] < 7) return SCM(playerid,0xFFFFFFFF,"Для использования этой функции ваше звание должно быть не ниже {5083B2}Лейтенанта!");
    if(sscanf(params,"u",params[0])) return SCM(playerid,0xFFFFFFFF,"Используйте: {1faee9}/setgunlic [id]");
    if(!Player[params[0]][PlayerLogged]) return true;
	SetPVarInt(playerid,"SearchID",params[0]);
    ShowPlayerDialog(playerid,56,DIALOG_STYLE_MSGBOX,"{1faee9}Управление лицензией", ((Player[params[0]][Licenses] & (1<<2)) == 0) ? ("{ffffff}Вы действительно хотите {03c03c}выдать лицензию на оружие этому человеку?") : ("{ffffff}Вы действительно хотите {AC7575}изъять лицензию на оружие у этого человека?") , "Да","Нет");
	return true;
}

CMD:gps(playerid,params[]) {
	if((Player[playerid][CGR] & (1<<1)) == 0) return SCM(playerid,0xAC7575FF,"У вас нет GPS-навигатора!");
	ShowPlayerDialog(playerid,54,DIALOG_STYLE_LIST,"(FFC800}Точки GPS","Мэрия LS\nАвтошкола\nДобыча руды\nДальнобойщики","Метка","Отмена");
	return true;
}

CMD:business(playerid,params[]) {
	if(Player[playerid][pBusiness] == 9999) return SCM(playerid,0xAC7575FF,"Вы не владеете бизнесом!");
	ShowPlayerDialog(playerid,58,DIALOG_STYLE_LIST,"{1faee9}Управление бизнесом","{ffffff}Прибыль/Убытки\nТовары\nУстановить цену за товар\nСнять прибыль\nПродать бизнес","Выбор","Отмена");
	return true;
}

CMD:debtors(playerid,params[]) {
	if(Player[playerid][pFraction][1] != 11) return true;
	ShowPlayerDialog(playerid,60,DIALOG_STYLE_LIST,"{C2EAF2}Задолжности","{ffffff}Должники за дом\nДолжники за бизнес","Выбор","Отмена");
	return true;
}

CMD:prods(playerid,params[]) {
	if(sscanf(params,"d",params[0])) return true;
	Business[Player[playerid][pBusiness]][bProduct] = params[0];
	return true;
}

CMD:russianboycar(playerid,params[]) {
	if(Player[playerid][pAdmin] < 1 || !Player[playerid][Aat]) return true;
	#define	vehicleid   GetPlayerVehicleID(playerid)
	if(!IsPlayerInAnyVehicle(playerid)) return true;
    new bumper,other[3];
    GetVehicleDamageStatus(vehicleid,bumper,other[0],other[1],other[2]);
    bumper ^= ((3<<20)|(3<<24));
	SendClientMessage(playerid,-1, ((bumper & (3<<24)) != 0) ? ("Пацанский таз радует глаз!") : ("Пацанский таз уже не радует глаз..."));
    UpdateVehicleDamageStatus(GetPlayerVehicleID(playerid),bumper,other[0],other[1],other[2]);
    AddVehicleComponent(vehicleid,1087), AddVehicleComponent(vehicleid,1079);
    #undef vehicleid
	return true;
}

CMD:unjail(playerid,params[]) {
	if(sscanf(params,"u",params[0])) return true;
	if(!Player[params[0]][PlayerLogged]) return true;
	Player[params[0]][pWanted] = 8;
	return true;
} // ТЕСТ КОМАНДА

CMD:safe(playerid,params[]) {
	if(Player[playerid][pHouse] == 9999 || House[Player[playerid][pHouse]][hUpgrade] == 0 || !IsPlayerInRangeOfPoint(playerid,3.0,House[Player[playerid][pHouse]][sX],House[Player[playerid][pHouse]][sY],House[Player[playerid][pHouse]][sZ])) return SCM(playerid,0xAC7575FF,"У вас нет дома, либо вы не возле сейфа!");
	ShowPlayerDialog(playerid,63,DIALOG_STYLE_LIST,"{1faee9}Сейф","Деньги\nПатроны\nНаркотики","Выбор","Отмена");
	return true;
}

CMD:clothes(playerid,params[]) {
    if(Player[playerid][pHouse] == 9999 || House[Player[playerid][pHouse]][hUpgrade] < 2 || !IsPlayerInRangeOfPoint(playerid,3.0,House[Player[playerid][pHouse]][wX],House[Player[playerid][pHouse]][wY],House[Player[playerid][pHouse]][wZ])) return SCM(playerid,0xAC7575FF,"У вас нет дома, либо вы не возле шкафа!");
	SetPlayerInterior(playerid,14), SetPlayerPos(playerid,257.7437,-41.4953,1002.0234), SetPlayerFacingAngle(playerid,91.0359), SetPlayerCameraPos(playerid,255.7959,-42.4666,1002.0234+1.2), SetPlayerCameraLookAt(playerid,257.7437,-41.4953,1002.0234,CAMERA_CUT), TogglePlayerControllable(playerid,0);
    TextDrawShowForPlayer(playerid, brLeft), TextDrawShowForPlayer(playerid, brRight), TextDrawShowForPlayer(playerid, brSelect), TextDrawShowForPlayer(playerid, ButtonCancel);
    SelectTextDraw(playerid,0x1faee9FF), SetPVarInt(playerid,"ChangeSkin",1);
	SetPlayerSkin(playerid, Player[playerid][pModel][0]), Player[playerid][SSCase] = 1;
	return true;
}

CMD:fixcar(playerid,params[]) {
	DestroyVehicle(Player[playerid][PlayerCar]);
    Player[playerid][PlayerCar] = CreateVehicle(Player[playerid][pCar][0],896.8502, (!PlayerInBike(Player[playerid][pCar][0])) ? (-358.9444) : (-356.3848) ,2177.2405,89.8153,Player[playerid][pCar][1],Player[playerid][pCar][2],86400);
    SetVehicleVirtualWorld(Player[playerid][PlayerCar],House[Player[playerid][pHouse]][hID]);
} // ТЕСТ КОМАНДА

CMD:car(playerid,params[]) {
	if(sscanf(params,"d",params[0])) return true;
	Player[playerid][pCar][0] = params[0];
	return true;
} // ТЕСТ КОМАНДА


CMD:as(playerid,params[]) AC_SetPlayerPos(playerid,466.0654297,-941.5517578,2381.8439941);
CMD:hs(playerid,params[]) AC_SetPlayerPos(playerid,1152.97009, -1281.46863, 1002.29999);
CMD:cnn(playerid,params[]) AC_SetPlayerPos(playerid,2035.02905, -1320.85706, 1536.28564);
CMD:autsln(playerid,params[]) AC_SetPlayerPos(playerid,124.43925, -875.05670, 1558.42749);

CMD:inv(playerid,params[]) {
	if(GetPVarInt(playerid,"Inv") > 0) {
		for(new i; i < 20; i++) TextDrawHideForPlayer(playerid,iSlot[playerid][i]);
		TextDrawHideForPlayer(playerid,iBox),TextDrawHideForPlayer(playerid,iBox12),TextDrawHideForPlayer(playerid,iBox2),
		TextDrawHideForPlayer(playerid,iInv),TextDrawHideForPlayer(playerid, Player[playerid][iModel]),TextDrawHideForPlayer(playerid, Player[playerid][iSkin]),
        TextDrawHideForPlayer(playerid, Player[playerid][iPhone]),TextDrawHideForPlayer(playerid, Player[playerid][iClock]),TextDrawHideForPlayer(playerid, Player[playerid][iGps]),
		TextDrawHideForPlayer(playerid, Player[playerid][iRepair]),TextDrawHideForPlayer(playerid,iChit),TextDrawHideForPlayer(playerid,iDrop),
		TextDrawHideForPlayer(playerid,iCross),TextDrawHideForPlayer(playerid,iUse),SetPVarInt(playerid,"Inv",0),CancelSelectTextDraw(playerid);
		return true;
	}
	TextDrawSetPreviewModel(Player[playerid][iSkin], (GetPlayerSkin(playerid) != 154) ? 2689 : 19349);
	TextDrawSetPreviewModel(Player[playerid][iModel], GetPlayerSkin(playerid));
	TextDrawSetPreviewModel(Player[playerid][iPhone], (Player[playerid][pPhone][0] != 0) ? 18866 : 19349);
	TextDrawSetPreviewModel(Player[playerid][iClock],  ((Player[playerid][CGR] & (1<<0)) != 0) ? 19046 : 19349);
	TextDrawSetPreviewModel(Player[playerid][iGps],  ((Player[playerid][CGR] & (1<<1)) != 0) ? 18875 : 19349);
	TextDrawSetPreviewModel(Player[playerid][iRepair],  ((Player[playerid][CGR] & (1<<2)) != 0) ? 18635 : 19349);
	for(new i; i < 20; i++) TextDrawSetPreviewModel(iSlot[playerid][i], (Player[playerid][Slot][i] != 0) ? Player[playerid][Slot][i] : 19349) , TextDrawShowForPlayer(playerid,iSlot[playerid][i]);
	TextDrawShowForPlayer(playerid,iBox),TextDrawShowForPlayer(playerid,iBox12),TextDrawShowForPlayer(playerid,iBox2),
	TextDrawShowForPlayer(playerid,iInv),TextDrawShowForPlayer(playerid, Player[playerid][iModel]),TextDrawShowForPlayer(playerid, Player[playerid][iSkin]),
 	TextDrawShowForPlayer(playerid, Player[playerid][iPhone]),TextDrawShowForPlayer(playerid, Player[playerid][iClock]),TextDrawShowForPlayer(playerid, Player[playerid][iGps]),
	TextDrawShowForPlayer(playerid, Player[playerid][iRepair]),TextDrawShowForPlayer(playerid,iChit),TextDrawShowForPlayer(playerid,iDrop),
	TextDrawShowForPlayer(playerid,iCross),TextDrawShowForPlayer(playerid,iUse),SetPVarInt(playerid,"Inv",1), SelectTextDraw(playerid,0x2ECC71FF);
	return true;
}

CMD:track(playerid,params[]) {
	Track = 1, SetPVarInt(playerid,"Race",0), SetPlayerRaceCheckpoint(playerid,1,-2654.9399,1156.1821,34.6481,-2724.4636,1086.3967,45.8983,10.0);
	return true;
}

CMD:race(playerid,params[]) {
	if(Player[playerid][pFraction][1] != 18) return true;
 	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SCM(playerid,0xAC7575FF,"Вы не в автомобиле!");
	if(RaceTime > gettime()) return SCM(playerid,0xAC7575FF,"Начинать гонку можно только раз в час!");
	if(Track != 0) return SCM(playerid,0xAC7575FF,"Гонка уже начата!");
	if(GetPVarInt(playerid,"SelectRace") == 1) {
		TextDrawHideForPlayer(playerid,raBox),TextDrawHideForPlayer(playerid,raImg),TextDrawHideForPlayer(playerid,raTrack),TextDrawHideForPlayer(playerid,raDist),TextDrawHideForPlayer(playerid,raBox2),
		TextDrawHideForPlayer(playerid,raLeft),TextDrawHideForPlayer(playerid,raRight),TextDrawHideForPlayer(playerid,raSRace),TextDrawHideForPlayer(playerid,raButS),TextDrawHideForPlayer(playerid,raButC),
		TextDrawHideForPlayer(playerid,raStart),TextDrawHideForPlayer(playerid,raCancel);
		SetPVarInt(playerid,"SelectRace",0), CancelSelectTextDraw(playerid);
		return true;
	}
	TextDrawShowForPlayer(playerid,raBox),TextDrawShowForPlayer(playerid,raImg),TextDrawShowForPlayer(playerid,raTrack),TextDrawShowForPlayer(playerid,raDist),TextDrawShowForPlayer(playerid,raBox2),
	TextDrawShowForPlayer(playerid,raLeft),TextDrawShowForPlayer(playerid,raRight),TextDrawShowForPlayer(playerid,raSRace),TextDrawShowForPlayer(playerid,raButS),TextDrawShowForPlayer(playerid,raButC),
	TextDrawShowForPlayer(playerid,raStart),TextDrawShowForPlayer(playerid,raCancel);
	SelectTextDraw(playerid,0xFFFFFFFF), SetPVarInt(playerid,"SelectRace",1);
	return true;
}

CMD:buyhangout(playerid,params[])
{
	#define m   Player[playerid][pFraction][1]-15 // фракция -15 ( массив же на 3 ячейки 0 - РМ 1 - Яки - 2 - ЛКН )
	if(!Player[playerid][PlayerLogged] || m != 15 || m != 16 ) return true;
	if(Player[playerid][pFraction][2] < 9) return true; // ранг
	if(Mafia[m][mHouse] != -1) return SCM(playerid,0xAC7575FF,"Ваша мафия уже имеет подпольный дом!");
 	for(new h = 0 ; h <= Houses; h++)
 	{
  		if(IsPlayerInRangeOfPoint(playerid,3.0,House[h][hX],House[h][hY],House[h][hZ]))
  		{
	    	if(Mafia[m][mMoney] < House[h][hPrice]) return SCM(playerid,0xAC7575FF,"На счету мафии недостаточно средств!");
	     	if(strcmp(House[h][hOwner],"None",true)!=0) return SCM(playerid,0xAC7575FF,"Данный дом уже имеет владельца!");
	     	new string[15];
			switch(m)
			{
			    case 0: string = "Russian Mafia";
			    case 1: string = "Yakuza";
			    case 2: string = "La Cosa Nostra";
			}
	       	strmid(House[h][hOwner],string,0,24,24), Mafia[m][mHouse] = h, Mafia[m][mMoney] -= House[h][hPrice];
   			SendClientMessage(playerid,0x03c03cFF,"Дом мафии успешно куплен! Не забывайте пополнять баланс дома.");
	        SaveHouse(h), DestroyDynamicPickup(House[h][hPickup]), DestroyDynamicMapIcon(House[h][hIcon]);
	        House[h][hIcon] = CreateDynamicMapIcon(House[h][hX],House[h][hY],House[h][hZ],32,COLOR_WHITE,0,-1,-1);
			House[h][hPickup] = CreateDynamicPickup(1272,1,House[h][hX],House[h][hY],House[h][hZ]);
			House[h][hCommunal] = 0, House[h][hLock] = 1;
		}
	}
	#undef m
 	return true;
}

CMD:sellhangout(playerid, params[])
{
    #define m   Player[playerid][pFraction][1]-15
   	#define h	Mafia[m][mHouse]
	new string[15];
	switch(m)
	{
   		case 0: string = "Russian Mafia";
   		case 1: string = "Yakuza";
   		case 2: string = "La Cosa Nostra";
	}
	if(h == -1 || strcmp(string, House[h][hOwner], true) == -1) return true;
    if(!IsPlayerInRangeOfPoint(playerid,3.0,House[h][hX], House[h][hY], House[h][hZ])) return SCM(playerid,0xFFFFFFFF,"Необходимо находиться {1faee9}возле дома!");
	strmid(House[h][hOwner], "None", 0, strlen("None"), 24);
	Mafia[m][mMoney] += House[h][hPrice]; // По-скольку не обычный дом, то полная цена
	DestroyDynamicPickup(House[h][hPickup]), DestroyDynamicMapIcon(House[h][hIcon]);
	House[h][hIcon] = CreateDynamicMapIcon(House[h][hX],House[h][hY],House[h][hZ],31,COLOR_WHITE,0,-1,-1);
	House[h][hPickup] = CreateDynamicPickup(1273,1,House[h][hX],House[h][hY],House[h][hZ]);
	Mafia[m][mUpgrade] = 0;
	House[h][hCommunal] = 0;
	if(Player[playerid][pCar][0] != -1) DestroyVehicle(Player[playerid][PlayerCar]);
	Mafia[m][mHouse] = -1;
	SCM(playerid,0xAC7575FF,"Вы успешно продали дом мафии!");
	SaveHouse(h), SaveAccount(playerid);
	#undef h
	#undef m
	return true;
}

/*CMD:buygen(playerid,params[])
{
    #define m   Player[playerid][pFraction][1]-15
   	#define h	Mafia[m][mHouse]
    if(House[h][hUpgrade] > 0) return SCM(playerid,0xAC7575FF,"У вас уже установлено оборудование!");
	if(Mafia[m][mMoney] < 25000) return SCM(playerid,0xAC7575FF,"В банке мафии недостаточно денег для покупки оборудования!");
	House[Player[playerid][pHouse]][hObject][0] = CreateDynamicObject(2332,x,y,z,0.0,0.0,0.0,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid));
	EditDynamicObject(playerid,House[Player[playerid][pHouse]][hObject][0]);
	SCM(playerid,0xFF0000FF,"Внимание! Для редактирования позиции объекта используйте все 6 осей.");
	SCM(playerid,0xFF0000FF,"Оси сменяются серой кнопкой ( повернутой стрелкой )");
	return true;
}*/

/*CMD:settax(playerid,params[]) {
	if(sscanf(params,"d",params[0])) return SCM(playerid,-1,"Используйте: {1faee9}/settax [Сумма налога 0 - отключить, 50 - максимум]");
    taxt = params[0]+random(10);
    SCM(playerid,0x03c03cFF,"Сумма налога установлена: %i. Сумма: %i + %i (Доп. сумма)",tax,params[0],random(10));
	return true;
}*/
