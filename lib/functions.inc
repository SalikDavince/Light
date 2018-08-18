apublic SendClientsMessage(Float:max_radius,pointplayerid,text[],color1,color2,color3) {// убрать и заменить на ProxDetector
    fcor
	new Float:distance;
    GetPlayerPos(pointplayerid,x,y,z);
    SendClientMessage(pointplayerid,color1,text);
    if(Iter_Count(StreamedPlayers[pointplayerid]) == 0) return true;
    foreach(new i : StreamedPlayers[pointplayerid]) {
        if(IsPlayerInRangeOfPoint(i,max_radius,x,y,z)) {
            distance = GetPlayerDistanceFromPoint(i,x,y,z);
            if(distance >= 0.0 && distance < max_radius/3) SendClientMessage(i,color1,text);
            if(distance >= max_radius/3 && distance < max_radius/3*2) SendClientMessage(i,color2,text);
            if(distance >= max_radius/3*2 && distance <= max_radius) SendClientMessage(i,color3,text);
    }	}	return true;	}
	
stock ProxDetector(playerid, Float:max_range, color, string[], Float:max_ratio = 1.6)//thx to ziggy
{
    new
        Float:pos_x,
        Float:pos_y,
        Float:pos_z,
        Float:range,
        Float:range_ratio,
        Float:range_with_ratio,
        clr_r, clr_g, clr_b,
        Float:color_r, Float:color_g, Float:color_b;
        
    if (!GetPlayerPos(playerid, pos_x, pos_y, pos_z)) {
        return 0;
    }
    
   	SendClientMessage(playerid, color, string);

	if(Iter_Count(StreamedPlayers[playerid]) == 0) return true;

    color_r = float(color >> 24 & 0xFF);
    color_g = float(color >> 16 & 0xFF);
    color_b = float(color >> 8 & 0xFF);
    range_with_ratio = max_range * max_ratio;

    foreach(new i : StreamedPlayers[playerid]) {
    
		/*if(spectating[i] != -1)	{
			SendClientMessage(i, color, string);//Админка
			continue;
		}*/
		
        range = GetPlayerDistanceFromPoint(i, pos_x, pos_y, pos_z);
        if (range > max_range) {
            continue;
        }

        range_ratio = (range_with_ratio - range) / range_with_ratio;
        clr_r = floatround(range_ratio * color_r);
        clr_g = floatround(range_ratio * color_g);
        clr_b = floatround(range_ratio * color_b);

        SendClientMessage(i, (color & 0xFF) | (clr_b << 8) | (clr_g << 16) | (clr_r << 24), string);
    }
    return 1;
}

apublic CheckIP(playerid) {
    new
		rows;
	cache_get_row_count(rows);
    if(rows) { ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"Блокировка","{ff0000}Ваш IP адресс заблокирован!","Ок",""); return KickEx(playerid); }
    return true;
}

apublic LoadAccount(playerid) {
    new
		rows;
	cache_get_row_count(rows);
	if(rows) {
		
		cache_get_value_name_int(0, "ID", Player[playerid][pMysqlID]);
		
		cache_get_value_name(0, "Name", Name(playerid));
		
		cache_get_value_name(0, "password", Player[playerid][pPassword]);
		cache_get_value_name(0, "ip", Player[playerid][pIP]);
		cache_get_value_name(0, "datareg", Player[playerid][pRegData]);
		cache_get_value_name(0, "mail", Player[playerid][pMail]);
		cache_get_value_name(0, "referal", Player[playerid][pReferal]);
		
		
		cache_get_value_name_int(0, "sex", Player[playerid][pSex]);
		cache_get_value_name_int(0, "model", Player[playerid][pModel][0]);
		cache_get_value_name_int(0, "modelorg", Player[playerid][pModel][1]);

		cache_get_value_name_int(0, "level", Player[playerid][pLevel]);
		cache_get_value_name_int(0, "admin", Player[playerid][pAdmin]);
		cache_get_value_name_int(0, "apass", Player[playerid][APass]);
		cache_get_value_name_int(0, "money", Player[playerid][pMoney]);
		cache_get_value_name_int(0, "house", Player[playerid][pHouse]);
		cache_get_value_name_int(0, "leader", Player[playerid][pFraction][0]);
		cache_get_value_name_int(0, "member", Player[playerid][pFraction][1]);
		cache_get_value_name_int(0, "rank", Player[playerid][pFraction][2]);
		cache_get_value_name_int(0, "ammo", Player[playerid][pAmmo]);
		cache_get_value_name_int(0, "car", Player[playerid][pCar][0]);
		cache_get_value_name_int(0, "carcol1", Player[playerid][pCar][1]);
		cache_get_value_name_int(0, "carcol2", Player[playerid][pCar][2]);
		 
		cache_get_value_name_float(0,"milage", Player[playerid][pMilage]);
		
		cache_get_value_name_int(0, "ban", Player[playerid][pBan]);
		cache_get_value_name_int(0, "business", Player[playerid][pBusiness]);
		cache_get_value_name_int(0, "phone", Player[playerid][pPhone][0]);
		cache_get_value_name_int(0, "phonemoney", Player[playerid][pPhone][1]);
		cache_get_value_name_int(0, "sdp", Player[playerid][Skill][1]);
		cache_get_value_name_int(0, "deagle", Player[playerid][Skill][2]);
		cache_get_value_name_int(0, "shotgun", Player[playerid][Skill][3]);
		cache_get_value_name_int(0, "mp5", Player[playerid][Skill][7]);
		cache_get_value_name_int(0, "ak47", Player[playerid][Skill][8]);
		cache_get_value_name_int(0, "m4", Player[playerid][Skill][9]);
		cache_get_value_name_int(0, "mute", Player[playerid][pMute]);
		cache_get_value_name_int(0, "wanted", Player[playerid][pWanted]);
		cache_get_value_name_int(0, "city", Player[playerid][pCity]);
		cache_get_value_name_int(0, "drugs", Player[playerid][pDrugs]);
		cache_get_value_name_int(0, "exp", Player[playerid][pExp]);
		cache_get_value_name_int(0, "bank", Player[playerid][pBank]);
		cache_get_value_name_int(0, "bankpass", Player[playerid][pBankPass]);
		cache_get_value_name_int(0, "licenses", Player[playerid][Licenses]);
		cache_get_value_name_int(0, "cgr", Player[playerid][CGR]);
		cache_get_value_name_int(0, "model1", Player[playerid][OtherM][0]);
		cache_get_value_name_int(0, "model2", Player[playerid][OtherM][1]);
		
	}
	else {
		if(GetPVarInt(playerid, "ErrorLoginPassword") == 2) { SendClientMessage(playerid,0xAC7575FF,"Лимит попыток иссяк."); return KickEx(playerid); }
		SetPVarInt(playerid, "ErrorLoginPassword", GetPVarInt(playerid, "ErrorLoginPassword") + 1);
		ShowPlayerDialog(playerid, 1, DIALOG_STYLE_MSGBOX, "{ffffff}Неверный пароль!", "{AC7575}Введенный вами пароль неправильный!", "Повтор", "Отмена");
		return true;
	}
	if(gettime() >= Player[playerid][pBan]) Player[playerid][pBan] = 0;
 	else {
		format(strock, 54, "{ff0000}Вы забанены на сервере. До разбана %d дней(ь/я)",(Player[playerid][pBan]-43200)/86400);
    	ShowPlayerDialog(playerid,9990,0,"Ошибка",strock,"Ок","");
     	return KickEx(playerid);
  	}
	Player[playerid][PlayerLogged] = true, GivePlayerMoney(playerid,Player[playerid][pMoney]), SetPlayerScore(playerid, Player[playerid][pLevel]);
	for(new i = 0; i < 20; i++) SCM(playerid,-1,"");
	if(Player[playerid][pHouse] != 9999 && House[Player[playerid][pHouse]][hCommunal] <= -2350) 
	{
  		strmid(House[Player[playerid][pHouse]][hOwner], "None", 0, strlen("None"), 24);
		Player[playerid][pMoney] += House[Player[playerid][pHouse]][hPrice]/3; SaveHouse(Player[playerid][pHouse]);
		DestroyDynamicPickup(House[Player[playerid][pHouse]][hPickup]), DestroyDynamicMapIcon(House[Player[playerid][pHouse]][hIcon]);
		House[Player[playerid][pHouse]][hIcon] = CreateDynamicMapIcon(House[Player[playerid][pHouse]][hX],House[Player[playerid][pHouse]][hY],House[Player[playerid][pHouse]][hZ],31,COLOR_WHITE,0,-1,-1);
		House[Player[playerid][pHouse]][hPickup] = CreateDynamicPickup(1273,1,House[Player[playerid][pHouse]][hX],House[Player[playerid][pHouse]][hY],House[Player[playerid][pHouse]][hZ]);
		if(Player[playerid][pCar][0] != -1) DestroyVehicle(Player[playerid][PlayerCar]);
		Player[playerid][pHouse] = 9999;
		SCM(playerid,0xFF0000FF,"Вы были выселены из дома за долгую неуплату коммунальных услуг! Треть суммы со стоимости дома вам возвращена.");
	}
	if(Player[playerid][pBusiness] != 9999 && Business[Player[playerid][pBusiness]][bCommunal] <= -2850) 
	{
  		strmid(Business[Player[playerid][pBusiness]][bOwner], "None", 0, strlen("None"), 24);
		Player[playerid][pMoney] += Business[Player[playerid][pBusiness]][bPrice]/3; SaveBusiness(Player[playerid][pBusiness]);
		format(strock,101,"Бизнес: {1faee9}%s\n{ffffff}Владелец: {1faee9}%s",Business[Player[playerid][pBusiness]][bName],Business[Player[playerid][pBusiness]][bOwner]);
		UpdateDynamic3DTextLabelText(Business[Player[playerid][pBusiness]][bText],0xFFFFFFFF,strock);
		Player[playerid][pBusiness] = 9999;
		SCM(playerid,0xFF0000FF,"Ваш бизнес был продан за долгую неуплату коммунальных услуг! Треть суммы со стоимости бизнеса вам возвращена.");
	}
	SetPVarInt(playerid,"PlayedTime",gettime()+900);
	if(0 < Player[playerid][pWanted] < 7) SetPlayerWantedLevel(playerid,Player[playerid][pWanted]);
	SpawnPlayer(playerid);
	if(Player[playerid][pHouse] != 9999 && Player[playerid][pCar][0] != -1) {
		Player[playerid][PlayerCar] = CreateVehicle(Player[playerid][pCar][0],896.8502, (!PlayerInBike(Player[playerid][pCar][0])) ? (-358.9444) : (-356.3848) ,2177.2405,89.8153,Player[playerid][pCar][1],Player[playerid][pCar][2],86400);
        SetVehicleVirtualWorld(Player[playerid][PlayerCar],House[Player[playerid][pHouse]][hID]);
	}
	if(0 < Player[playerid][pFraction][1] < 6) {
		for(new i; i < sizeof(Zone); i++) {
			if(ZoneOnBattle[i] == 1) {
				if(Player[playerid][pFraction][1] == Zone[i][gFraction] || Player[playerid][pFraction][1] == Zone[i][gWar]) {
				    GangZoneFlashForPlayer(playerid,Zone[i][gID],0xFF000099);
					TextDrawShowForPlayer(playerid,gBox),
					PlayerTextDrawShow(playerid,gFGang[playerid]),
					PlayerTextDrawShow(playerid,gTGang[playerid]),
					PlayerTextDrawShow(playerid,gFScore[playerid]),
					PlayerTextDrawShow(playerid,gTScore[playerid]),
					TextDrawShowForPlayer(playerid,gArea),
					PlayerTextDrawShow(playerid,gIDs[playerid]),
					TextDrawShowForPlayer(playerid,gsTime),
					PlayerTextDrawShow(playerid,gTimeTick[playerid]);
					break;
	}   }   }   }
	return true;
}

/*stock CreateAccount(playerid, password[])
{

 	new
	 	create_acc_string[185 - (2*10) + MAX_PLAYER_NAME + 32 + 11 + 5 + 16 + (2*2) + (4*2)];

	gettime(hour, minute, second);
	getdate(year, month, day);
	
	format(data,sizeof(data),
		"%02d.%02d.%04d %02d:%02d:%02d",
		day,month,year,
		hour,minute,second
	);
	
	//strmid(Player[playerid][pKey], password, 0, 36, 36);
	
	
	//Player[playerid][pLevel] = 1;
	//Player[playerid][pMoney] = 70;
	
	//ServerGivePlayerHealth(playerid, 100.0);
	
	mysql_format(connects,
		create_acc_string, sizeof(create_acc_string),
		!"INSERT INTO `accounts` (`Nickname`,`Password`,`Money`,`Level`,`DataRegister`,`IPRegister`,`Sex`,`Reg`,`Model`,`Char`) \
		VALUE ('%e', '%e', '%i', '%i', NOW(), '%s', '%i', '%i', '%i', '%i')",
		Player[playerid][pName],
		password,
		Player[playerid][pMoney],
	 	Player[playerid][pLevel],
	 	data,
	  	Player[playerid][pIP],
	  	Player[playerid][pSex],
	   	false,
	    Player[playerid][pModel],
		Player[playerid][pChar]
	);
	
	mysql_function_query(connects, create_acc_string, true, "", "");

	//print("---------?AAA---------");
	//printf(create_acc_string);
	//print("----------------------");

	format(create_acc_string,sizeof(create_acc_string),
 		"(( %s [ID: %d] ca?aaeno?e?iaaeny ia na?aa?a. IP {FFFFFF}%s ))",
 		Player[playerid][pName], playerid, Player[playerid][pIP]
 	);
 	
	SendAdminMessage(COLOR_GREY, create_acc_string, 1);
	return true;
}*/

CreatePickups() {
	pickup[0] = CreateDynamicPickup(1318,23,0.0,0.0,3000.0,3);
	pickup[1] = CreateDynamicPickup(1318,23,2457.6394,-1660.8143,2047.2317,1);// Пикап внутри Grove
	pickup[2] = CreateDynamicPickup(1314,23,2000.0424,-1114.0535,27.1250); // Пикап снаружи Ballas
	pickup[3] = CreateDynamicPickup(1318,23,2457.6394,-1660.8143,2047.2317,2);// Пикап внутри Ballas
	pickup[4] = CreateDynamicPickup(19134,23,542.3050,-1293.9307,17.2422); // Автосалон ЛС
	pickup[5] = CreateDynamicPickup(1210,23,1304.5807,-1868.3346,13.5469); // Устройство на работу почтальона
	CreateDynamic3DTextLabel("Почтовая служба\n{ffffff}Трудоустройство",0x1faee9FF,1304.5807,-1868.3346,13.5469+1.5,30.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	CreateDynamicMapIcon(1304.5807,-1868.3346,13.5469,55,COLOR_WHITE,0,-1,-1);
	pickup[6] = CreateDynamicPickup(1318,23,2457.6394,-1660.8143,2047.2317,3);// Пикап внутри Vagos
	pickup[7] = CreateDynamicPickup(1318,23,2457.6394,-1660.8143,2047.2317,4);// Пикап внутри Aztec
	pickup[8] = CreateDynamicPickup(1318,23,2457.6394,-1660.8143,2047.2317,5);// Пикап внутри Rifa
	pickup[9] = CreateDynamicPickup(1314,23,2808.0703,-1175.9146,25.3803); // Пикап снаружи Vagos
	pickup[10] = CreateDynamicPickup(1314,23,1888.9291,-2000.9448,13.5469); // Пикап снаружи Aztec
	pickup[11] = CreateDynamicPickup(1314,23,1944.8779,-1561.2952,13.6257); // Пикап снаружи Rifa
	pickup[12] = CreateDynamicPickup(1210,23,2543.1885,-474.8704,84.9128); // Пикап устройства на работу шахтера
	pickup[13] = CreateDynamicPickup(1318,23,-427.2457,-132.7925,2102.5557,1); // выход армия
	pickup[14] = CreateDynamicPickup(1318,23,231.4112,1885.0485,17.6406); //вход армия
	CreateDynamic3DTextLabel("КАЗАРМА №1",0x03c03cAA,231.4112,1885.0485,17.6406+1.0,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	pickup[15] = CreateDynamicPickup(1318,23,352.6138,1924.1447,21.9776); // Вход в аммо армии
	pickup[16] = CreateDynamicPickup(1318,23,285.4662,-41.8055,1001.5156,1); // Выход из аммо армии
	pickup[17] = CreateDynamicPickup(1239,2,299.1338,-40.8164,1001.5156,1); // Взятие оружия
	pickup[18] = CreateDynamicPickup(1318,23,362.8792,-75.1772,1001.5078,1); // Выход из столовой армии
	pickup[19] = CreateDynamicPickup(1318,23,246.3739,1986.5935,17.6406); // Вход в столовую армии
	pickup[20] = CreateDynamicPickup(1318,23,246.8161,62.3221,1003.6406,1); // Выход из LSPD-1
	pickup[21] = CreateDynamicPickup(1318,23,1555.5009,-1675.5850,16.1953); // Вход в LSPD-1
	CreateDynamic3DTextLabel("Los Santos Police Dept.",0x373737FF,1555.5009,-1675.5850,16.1953+1.0,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	pickup[22] = CreateDynamicPickup(1314,23,2495.3635,-1691.1387,14.7656); // Пикап снаружи Grove
	pickup[23] = CreateDynamicPickup(1318,23,288.7962,166.9547,1007.1719,1); // LVPD Int
	pickup[24] = CreateDynamicPickup(1318,23,2337.1404,2459.3130,14.9742); // LVPD World
	pickup[25] = CreateDynamicPickup(1318,23,246.4474,88.0090,1003.6406,1); // Garage LSPD Int
	pickup[26] = CreateDynamicPickup(19133,23,1411.3575,-1699.8102,13.5395); // Пикап Банка LS
	pickup[27] = CreateDynamicPickup(19133,23,1110.8750,258.0923,1009.0015,1); // Пикап выхода из Банка LS
	CreateDynamic3DTextLabel("БАНК",0x03c03cAA,1411.3575,-1699.8102,13.5395+1.0,35.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	pickup[28] = CreateDynamicPickup(1239,23,1106.7876,271.0233,1009.0015,1); // Банковские услуги LS
	CreateDynamic3DTextLabel("Банковские услуги",0x1faee9FF,1106.7876,271.0233,1009.0015+1.0,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	CreateDynamic3DTextLabel("Пункт слежки FBI",0xAA8E3DFF,1080.7931,1068.1979,1018.2078+1.0,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	pickup[29] = CreateDynamicPickup(1318,23,1039.0293,1013.0238,11.0000); // Пикап FBI
	pickup[30] = CreateDynamicPickup(1318,23,1070.4307,1085.1260,1008.2859,1); // Пикап выхода из FBI
	pickup[31] = CreateDynamicPickup(19132,23,1481.0107,-1772.3140,18.7958); // Пикап Mayor
	CreateDynamic3DTextLabel("МЭРИЯ",0x1faee9AA,1481.0107,-1772.3140,18.7958+1.0,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	pickup[32] = CreateDynamicPickup(19132,23,234.4862,1603.6831,1082.4359,1); // Пикап выхода из Mayor
	pickup[33] = CreateDynamicPickup(19134,23,-49.8815,-269.3627,6.6332); // Пикап Дальнобойщиков Trucks Job
	CreateDynamic3DTextLabel("Устройство на работу {03c03c}'Дальнобойщик'",0xFFFFFFFF,-49.8815,-269.3627,6.6332+1.0,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	pickup[34] = CreateDynamicPickup(19132,23,-2026.5984,-102.0665,35.1641); // Пикап Автошколы
	CreateDynamic3DTextLabel("АВТОШКОЛА",0xE13D3DAA,-2026.5984,-102.0665,35.1641+1.0,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	pickup[35] = CreateDynamicPickup(19132,23,-2026.8752,-103.6017,1035.1836,1); // Пикап выхода из Автошколы
	pickup[36] = CreateDynamicPickup(19134,23,-2022.3501,-116.7481,1035.1719,1); // Авто-сдача на права
	CreateDynamic3DTextLabel("Автоматическая сдача\n{ffffff}На вод.права",0x1faee9FF,-2022.3501,-116.7481,1035.1719+1.0,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	pickup[37] = CreateDynamicPickup(1318,23,-2051.5396,450.6917,35.1719); // Пикап SFN
	CreateDynamic3DTextLabel("San Andreas News",0x00C4FFFF,-2051.5396,450.6917,35.1719+1.0,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	pickup[38] = CreateDynamicPickup(1318,23,1234.9098,-974.9842,1085.0042,1); // Пикап выхода из SFN
	pickup[39] = CreateDynamicPickup(1318,23,246.4100,107.2987,1003.2188,1); // Пикап внутри SFPD
	pickup[40] = CreateDynamicPickup(1318,23,-1605.5288,710.2736,13.8672); // Пикап снаружи SFPD
	pickup[41] = CreateDynamicPickup(1318,23,1568.6445,-1689.9703,6.2188); // Garage LSPD World
	pickup[42] = CreateDynamicPickup(1318,23,1172.9064,-1310.7794,1001.5734,1); // Пикап внутри MOH
	pickup[43] = CreateDynamicPickup(1318,23,1172.0767,-1323.3424,15.4030); // Пикап снаружи MOH
	//=== TDS ===
	CreateDynamic3DTextLabel("Гараж\n{ffffff}Вход/Выход {1faee9}'LALT'",0x00D900FF,897.6984,-354.6799,2177.6160+1.2,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
    CreateDynamic3DTextLabel("Гараж\n{ffffff}Выехать {1faee9}'Сигнал'",0x00D900FF,896.9077,-358.9295,2177.6160+1.2,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
    CreateDynamic3DTextLabel("Переплавка {1faee9}железной руды!",0x00D900FF,-1118.7550049,-1622.7889404,76.3349991+1.2,30.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
    CreateDynamic3DTextLabel("Управление воротами {03c03c}/gate",0xFFFFFFFF,126.9390030,1942.5059814,18.1000004+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
    CreateDynamic3DTextLabel("Управление воротами {03c03c}/gate",0xFFFFFFFF,94.1539993,1914.4200439,17.2299995+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
    CreateDynamic3DTextLabel("Управление воротами {03c03c}/gate",0xFFFFFFFF,349.3800049,1800.5159912,17.2299995+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
    LSWtext = CreateDynamic3DTextLabel("Комплектующие для сбора оружия\n{1faee9}На корабле: 50000",0xFFFFFFFF,2838.0381,-2436.6475,14.5998+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
    LVWtext = CreateDynamic3DTextLabel("Собранное оружие\n{1faee9}На складе: 1000 ед.",0xFFFFFFFF,298.1099,-31.5498,1001.5156+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,1,1,-1,100.0);
    LVWEtext = CreateDynamic3DTextLabel("Еда и Броня\n{1faee9}На складе: 35 пайков",0xFFFFFFFF,376.5800,-68.0185,1001.5151+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,1,10,-1,100.0);
    CreateDynamic3DTextLabel("Взять {1faee9}комплектующие",0xFFFFFFFF,299.1338,-40.8164,1001.5156+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,1,1,-1,100.0);
    CreateDynamic3DTextLabel("Склад с {03c03c}выделенной едой\n\nПоставщик: {ffffff}Burger King SA",0xFFFFFFFF,-1479.4716,2621.5715,58.7813+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
    CreateDynamic3DTextLabel("Наблюдение за армией с камер\n{03c03c}/sparmy",0xFFFFFFFF,246.8405,1860.9401,14.0840+1.2,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	CreateDynamic3DTextLabel("San Fierro Police Dept.",0x373737FF,-1605.5288,710.2736,13.8672+1.0,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	//=== TD ===
	CreateDynamic3DTextLabel("Рагрузочный пункт\n{ffffff}'Сырье'",0x1faee9FF,979.7341,2134.1187,10.8203+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	CreateDynamic3DTextLabel("Рагрузочный пункт\n{ffffff}'Сырье'",0x1faee9FF,2842.1775,902.4745,10.7578+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	CreateDynamic3DTextLabel("Рагрузочный пункт\n{ffffff}'Сырье'",0x1faee9FF,-2447.0544,740.8016,35.0156+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	//Нефть
	CreateDynamic3DTextLabel("Рагрузочный пункт\n{ffffff}'Нефть'",0x1faee9FF,-1052.4037,-652.3160,32.0078+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	CreateDynamic3DTextLabel("Рагрузочный пункт\n{ffffff}'Нефть'",0x1faee9FF,2647.9568,-1473.5526,30.4507+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	CreateDynamic3DTextLabel("Рагрузочный пункт\n{ffffff}'Нефть'",0x1faee9FF,-2267.5535,541.3361,35.0156+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	//Продукты
	CreateDynamic3DTextLabel("Рагрузочный пункт\n{ffffff}'Продукты'",0x1faee9FF,-2267.5535,541.3361,35.0156+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	CreateDynamic3DTextLabel("Рагрузочный пункт\n{ffffff}'Продукты'",0x1faee9FF,-1479.0654,2658.2813,55.8359+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	CreateDynamic3DTextLabel("Рагрузочный пункт\n{ffffff}'Продукты'",0x1faee9FF,1767.1118,-1860.1760,13.5791+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	//Зерно
	CreateDynamic3DTextLabel("Рагрузочный пункт\n{ffffff}'Зерно'",0x1faee9FF,-376.5928,-1423.2186,25.7266+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	CreateDynamic3DTextLabel("Рагрузочный пункт\n{ffffff}'Зерно'",0x1faee9FF,-1056.2471,-1205.1371,129.0166+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	CreateDynamic3DTextLabel("Рагрузочный пункт\n{ffffff}'Зерно'",0x1faee9FF,-1725.4534,-121.6313,3.5489+1.5,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,-1,-1,-1,100.0);
	//============== Unjail texts ========
	CreateDynamic3DTextLabel("Внести залог за человека\n{ffffff}/unjail",0x1faee9FF,249.3893,67.7630,1003.6406+1.2,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,1,-1,-1,100.0);
	CreateDynamic3DTextLabel("Внести залог за человека\n{ffffff}/unjail",0x1faee9FF,240.5096,112.8605,1003.2188+1.2,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,1,-1,-1,100.0);
	CreateDynamic3DTextLabel("Внести залог за человека\n{ffffff}/unjail",0x1faee9FF,292.3687,180.2949,1007.1794+1.2,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,1,-1,-1,100.0);
	CreateDynamic3DTextLabel("Устройство {1faee9}на работу",0xFFFFFFFF,270.5312,1603.7384,1083.2759+1.2,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,1,-1,-1,100.0);
	//====================================================================================
    CreateDynamicMapIcon(1555.5009,-1675.5850,16.1953,30,COLOR_WHITE,0,-1,-1,100.0); // LSPD
    CreateDynamicMapIcon(231.4112,1885.0485,17.6406,20,0x03c03c55,0,-1,-1,100.0); // ARMY LV
    CreateDynamicMapIcon(1368.8578,-1279.8552,13.5469,6,0x03c03c55,0,-1,-1,100.0); // AMMO
    CreateDynamicMapIcon(1411.3575,-1699.8102,13.5395,52,0x03c03c55,0,-1,-1,100.0); // Банк LS
    CreateDynamicMapIcon(-49.8815,-269.3627,6.6332,51,0x03c03c55,0,-1,-1,100.0); // Дальнобойщики Trucks
    CreateDynamicMapIcon(-2026.5984,-102.0665,35.1641,36,0x03c03c55,0,-1,-1,100.0); // Автошкола Driving School SF
    CreateDynamicMapIcon(-1605.5288,710.2736,13.8672,30,COLOR_WHITE,0,-1,-1,100.0); // SFPD
	//=====================================================================================
	haulammo = CreateDynamicPickup(3014,23,2838.0381,-2436.6475,14.5998); // LSWarehouse pickup
	ammolv = CreateDynamicPickup(3014,23,298.1099,-31.5498,1001.5156,1); // LVWarehouse pickup
	hauleat = CreateDynamicPickup(2912,23,-1479.4716,2621.5715,58.7813-0.5); // LSWarehouse pickup
	eatlv = CreateDynamicPickup(2912,23,376.5800,-68.0185,1001.5151-1.2,1); // EAT LVArmy pickup
	pickjob = CreateDynamicPickup(19134,23,270.5312,1603.7384,1083.2759,1); // Пикап устройства на работу водителя автобуса
}

ResetPlayerInfo(playerid) {
    for(new pInfo:i; i < pInfo; ++i) Player[playerid][i] = 0;
	Player[playerid][pFraction][0] = 0, Player[playerid][pFraction][1] = 0,Player[playerid][pFraction][2] = 0;
	Player[playerid][pHouse] = 9999;
	Player[playerid][pCar][0] = -1,Player[playerid][pCar][1] = 0,Player[playerid][pCar][2] = 0,Player[playerid][pCar][3] = 0,Player[playerid][pMilage] = 0.0;
	Player[playerid][pBusiness] = 9999;
	Player[playerid][PlayerLogged] = false;
	Player[playerid][Aat] = false;
	Player[playerid][TDSelect] = false;
	Player[playerid][ArendedVehicle] = INVALID_VEHICLE_ID;
	Player[playerid][pCity] = 1;
	Player[playerid][pModel][0] = 78,Player[playerid][pModel][1] = 78;
	Player[playerid][OtherM][0] = 78,Player[playerid][OtherM][1] = 78;
	Player[playerid][pPhone][0] = 0,Player[playerid][pPhone][1] = 0;
	for(new i = 0; i < 10; i++) RemovePlayerAttachedObject(playerid,i), Player[playerid][Skill][i] = 0;
}

apublic CheckPlayer(playerid) {
    new
		rows;
	cache_get_row_count(rows);
  	SetPlayerCameraPos(playerid, 1360.9023,-1571.8125,116.9395), SetPlayerCameraLookAt(playerid, 1480.2584,-1734.5576,18.6296);
   	if(rows) {
		format(strock, 168+1, "{ffffff}Приветствую вас, дорогой игрок!\nВаш аккаунт зарегистрирован в системе, пожалуйста авторизуйтесь.\n\n{ff0000}Ник-нейм: %s\n{00ff00}Пароль:",Name(playerid));
		ShowPlayerDialog(playerid, 1, DIALOG_STYLE_PASSWORD, "{ffcc00}Авторизация", strock, "Принять","Отмена");
  	}
  	else ShowPlayerDialog(playerid, 2, DIALOG_STYLE_INPUT, "{ffcc00}Регистрация","{ffffff}Приветствую вас, дорогой игрок!\nПеред регистрацией обратите внимание на правила:\n\n{ff0000} Пожалуйста, придумайте ваш будущий пароль:", "Далее","Отмена");
  	return true;
}

apublic SaveAccount(playerid)
{
	if(!IsPlayerConnected(playerid)) return true;
	if(1 > GetPlayerState(playerid) > 3) return true;
	if(GetPlayerSkin(playerid) == 0 || GetPlayerSkin(playerid) == 74) return true;
	if(Player[playerid][PlayerLogged] == true) {
		query = "UPDATE `accounts` SET `level` = '%i', `sex`= '%i', `model` = '%i', `modelorg` = '%i', `admin` = '%i', `apass` = '%i', `money` = '%i', `house` = '%i', `leader` = '%i', `member` = '%i', `rank` = '%i', ";
		strcat(query,"`ammo` = '%i', `car` = '%i', `carcol1` = '%i', `carcol2` = '%i', `milage`= '%.1f', `ban` = '%i', `business` = '%i', `phone` = '%i', `phonemoney` = '%i', ");
		strcat(query,"`sdp` = '%i', `deagle` = '%i', `shotgun` = '%i', `mp5` = '%i', `ak47` = '%i', `m4` = '%i', `mute` = '%i', `wanted` = '%i',`city` = '%i', `drugs` = '%i', `exp` = '%i', ");
		strcat(query,"`bank` = '%i', `bankpass` = '%i', `licenses` = '%i', `cgr` = '%i',`model1`='%i',`model2`='%i' WHERE `Name` = '%e'");
		mysql_format(connects,query,800,query, Player[playerid][pLevel], Player[playerid][pSex], Player[playerid][pModel][0],Player[playerid][pModel][1],Player[playerid][pAdmin],Player[playerid][APass],Player[playerid][pMoney],
		Player[playerid][pHouse],Player[playerid][pFraction][0],Player[playerid][pFraction][1],Player[playerid][pFraction][2],Player[playerid][pAmmo],Player[playerid][pCar][0],Player[playerid][pCar][1],Player[playerid][pCar][2],
		Player[playerid][pMilage],Player[playerid][pBan],Player[playerid][pBusiness],Player[playerid][pPhone][0],Player[playerid][pPhone][1],Player[playerid][Skill][1],Player[playerid][Skill][2],Player[playerid][Skill][3]
		,Player[playerid][Skill][7],Player[playerid][Skill][8],Player[playerid][Skill][9],Player[playerid][pMute],Player[playerid][pWanted],Player[playerid][pCity],Player[playerid][pDrugs],Player[playerid][pExp],
		Player[playerid][pBank],Player[playerid][pBankPass],Player[playerid][Licenses],Player[playerid][CGR],Player[playerid][OtherM][0],Player[playerid][OtherM][1],Name(playerid));
  		mysql_tquery(connects,query,"","");
	}
	return true;
}

apublic GlobalSave() {
	foreach(new i : Player) SaveAccount(i);
	for(new h = 0; h <= Houses; h++) SaveHouse(h);
	for(new w = 0; w < sizeof(Ware); w++) SaveWarehouse(w);
	for(new b = 0; b <= Businesses; b++) SaveBusiness(b);
 	print("Общее сохранение завершено!");
}

apublic LoadHouses() {
	//new content[32];
    new
		rows;
	cache_get_row_count(rows);
	if(rows)
	{
		for(new h; h < rows; h++)
		{
			cache_get_value_name_int(h, "ID", House[h][hID]);
			
			cache_get_value_name(h,"Owner",House[h][hOwner]);
			cache_get_value_name(h,"Street",House[h][hStreet]); //strmid(House[h][hStreet], content, 0, strlen(content), 32);
			
			cache_get_value_name_float(h,"X",House[h][hX]);
			cache_get_value_name_float(h,"Y",House[h][hY]);
			cache_get_value_name_float(h,"Z",House[h][hZ]);
			cache_get_value_name_float(h,"cX",House[h][cX]);
			cache_get_value_name_float(h,"cY",House[h][cY]);
			cache_get_value_name_float(h,"cZ",House[h][cZ]);
			cache_get_value_name_float(h,"cA",House[h][cA]);
			
			cache_get_value_name_int(h,"Price",House[h][hPrice]);
			cache_get_value_name_int(h,"Lock",House[h][hLock]);
			cache_get_value_name_int(h,"Int",House[h][hInt]);
			

			cache_get_value_name_int(h,"Priority",House[h][hPriority]);
			cache_get_value_name_int(h,"Housemans", House[h][hHousemans]);
			cache_get_value_name_int(h,"Upgrade", House[h][hUpgrade]);
			cache_get_value_name_int(h,"Communal", House[h][hCommunal]);
			
			cache_get_value_name_float(h,"sX",House[h][sX]);
			cache_get_value_name_float(h,"sY", House[h][sY]);
			cache_get_value_name_float(h,"sZ", House[h][sZ]);
			cache_get_value_name_float(h,"sRX", House[h][sRX]);
			cache_get_value_name_float(h,"sRY", House[h][sRY]);
			cache_get_value_name_float(h,"sRZ", House[h][sRZ]);
			cache_get_value_name_float(h,"wX", House[h][wX]);
			cache_get_value_name_float(h,"wY", House[h][wY]);
			cache_get_value_name_float(h,"wZ", House[h][wZ]);
			cache_get_value_name_float(h,"wRX", House[h][wRX]);
			cache_get_value_name_float(h,"wRY",House[h][wRY]);
			cache_get_value_name_float(h,"wRZ", House[h][wRZ]);
			
			cache_get_value_name_int(h,"sMoney", House[h][sMoney]);
			cache_get_value_name_int(h,"sAmmo", House[h][sAmmo]);
			cache_get_value_name_int(h,"sDrugs", House[h][sDrugs]);
			
			Houses = h+1;
			
			House[h][hIcon] = CreateDynamicMapIcon(House[h][hX],House[h][hY],House[h][hZ], (strcmp(House[h][hOwner],"None",true)==0) ? (31) : (32) ,COLOR_WHITE,0,-1,-1);
			House[h][hPickup] = CreateDynamicPickup( (strcmp(House[h][hOwner],"None",true)==0) ? (1273) : (1272) ,1,House[h][hX],House[h][hY],House[h][hZ]);
			if(House[h][hUpgrade] > 0) {
			    House[h][hObject][0] = CreateDynamicObject(2332,House[h][sX],House[h][sY],House[h][sZ],House[h][sRX],House[h][sRY],House[h][sRZ],House[h][hID]),
				format(warehousetext,sizeof(warehousetext),"Сейф\nДенег: %d\nПатроны: %d\nНаркотики: %d",House[h][sMoney],House[h][sAmmo],House[h][sDrugs]);
				House[h][sText] = CreateDynamic3DTextLabel(warehousetext, 0x1faee9FF,House[h][sX],House[h][sY],House[h][sZ]+1.2,20.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,House[h][hID],-1,-1,100.0);
				if(House[h][hUpgrade] > 1) House[h][hObject][1] = CreateDynamicObject(2025,House[h][wX],House[h][wY],House[h][wZ],House[h][wRX],House[h][wRY],House[h][wRZ],House[h][hID]);
		}   }
	}
	printf("[Cheery RP] Houses: %i",Houses);
	return true;
}

stock SaveHouse(h) {
	mysql_format(connects, query,550+1,"UPDATE `houses` SET `Owner`='%s',`X`='%.4f',`Y`='%.4f',`Z`='%.4f',`cX`='%.4f',`cY`='%.4f',`cZ`='%.4f',`cA`='%.4f',`Price`='%i',`Lock`='%i',`Int`='%i',`Housemans`='%i',\
	`Upgrade`='%i',`Communal`='%i',`sX`='%.4f',`sY`='%.4f',`sZ`='%.4f',`sRX`='%.4f',`sRY`='%.4f',`sRZ`='%.4f',`wX`='%.4f',`wY`='%.4f',`wZ`='%.4f'\
	,`wRX`='%.4f',`wRY`='%.4f',`wRZ`='%.4f',`sMoney`='%i',`sAmmo`='%i',`sDrugs`='%i' WHERE `ID` = '%i'",
	House[h][hOwner],House[h][hX],House[h][hY],House[h][hZ],House[h][cX],House[h][cY],House[h][cZ],House[h][cA], House[h][hPrice],House[h][hLock],House[h][hInt],House[h][hHousemans],House[h][hUpgrade],House[h][hCommunal],
	House[h][sX],House[h][sY],House[h][sZ],House[h][sRX],House[h][sRY],House[h][sRZ],House[h][wX],House[h][wY],House[h][wZ],House[h][wRX],House[h][wRY],House[h][wRZ],House[h][sMoney],
	House[h][sAmmo],House[h][sDrugs],House[h][hID]);
	mysql_tquery(connects, query, "", "");
	return true;	}


apublic LoadWarehouses() {//нужно после очищать массив
	//new content[24];
    new
		rows;
	cache_get_row_count(rows);
	if(rows)
	{
		for(new w = 0; w < rows; w++)
		{
			cache_get_value_name_int(w,"ID", Ware[w][wID]);
			
			cache_get_value_name(w,"name", Ware[w][wName]);
			
			cache_get_value_name_int(w,"money",Ware[w][wMoney]);
			cache_get_value_name_int(w,"ammo",Ware[w][wAmmo]);
			cache_get_value_name_int(w,"drugs",Ware[w][wDrugs]);
			
			cache_get_value_name_float(w,"x",Ware[w][wX]);
			cache_get_value_name_float(w,"y",Ware[w][wY]);
			cache_get_value_name_float(w,"z",Ware[w][wZ]);
			
			cache_get_value_name_int(w,"fraction",Ware[w][wFraction]);
			
		    Wars++;
			
		    if(0 < Ware[w][wFraction] < 6) CreatePickup(1239,23,Ware[w][wX],Ware[w][wY],Ware[w][wZ],w+1);
		    if(0 < Ware[w][wFraction] < 6) format(warehousetext,sizeof(warehousetext),"Склад %s\nАммуниции: %d\nНаркотиков: %d\nДенег: %d", Ware[w][wName], Ware[w][wAmmo], Ware[w][wDrugs], Ware[w][wMoney]);
		    if(Ware[w][wFraction] == 11) format(warehousetext,sizeof(warehousetext),"Казна %s\nНалог: %d\nСобрано: %d$", Ware[w][wName], Ware[w][wAmmo], Ware[w][wMoney]);
		    if(Ware[w][wFraction] == 13 || Ware[w][wFraction] == 14) format(warehousetext,sizeof(warehousetext),"Фонд %s\nЦена за символ: %d\nСобрано: %d$", Ware[w][wName], Ware[w][wAmmo], Ware[w][wMoney]);
   			warehouset[w] = CreateDynamic3DTextLabel(warehousetext,0xFF9900FF, Ware[w][wX],Ware[w][wY],Ware[w][wZ]+1.0,10,INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 0, (Ware[w][wFraction] != 11) ? (w+1) : (1) , -1, -1);
		}
	}
	return true;
}

apublic LoadAtm() {
	//new content[24];
	new
		rows;
	cache_get_row_count(rows);
	if(rows) {
		for(new a = 0; a < rows; a++) {
			
			cache_get_value_name_int(a,"ID",Atm[a][aID]);
			
			cache_get_value_name_float(a,"x", Atm[a][aX]);
			cache_get_value_name_float(a,"y", Atm[a][aY]);
			cache_get_value_name_float(a,"z", Atm[a][aZ]);
			cache_get_value_name_float(a,"rx", Atm[a][aRX]);
			cache_get_value_name_float(a,"ry", Atm[a][aRY]);
			cache_get_value_name_float(a,"rz", Atm[a][aRZ]);
			
			Atms = a;
			
		    Atm[a][aID] =  CreateDynamicObject(2754,Atm[a][aX],Atm[a][aY],Atm[a][aZ],Atm[a][aRX],Atm[a][aRY],Atm[a][aRZ]);
	  		CreateDynamic3DTextLabel("Банкомат\nИспользуйте	 {ffffff}'LALT'",0x1faee9AA, Atm[a][aX],Atm[a][aY],Atm[a][aZ]+1.3,25.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 0, -1, -1);
		}
	}
	return true;
}

stock SaveWarehouse(w) {
	mysql_format(connects, query,200,"UPDATE `warehouses` SET `money` = '%d', `ammo` = '%d', `drugs` = '%d' WHERE `ID` = '%d'", Ware[w][wMoney] ,Ware[w][wAmmo] ,Ware[w][wDrugs], Ware[w][wID]);
	mysql_tquery(connects, query, "", "");
	return true;	}


apublic LoadBusiness() {
	//new content[32]
	new type;
	new
		rows;
	cache_get_row_count(rows);
	if(rows)
	{
		for(new b; b < rows; b++)
		{
	        cache_get_value_name_int(b, "ID", Business[b][bID]);
			
			//cache_get_value_name(b, "Owner", content,connects), strmid(Business[b][bOwner], content, 0, strlen(content), 24);
			
			cache_get_value_name(b,"Owner", Business[b][bOwner]);
			
			cache_get_value_name(b, "name", Business[b][bName]);
			
			cache_get_value_name_float(b, "X", Business[b][bX]);
			cache_get_value_name_float(b, "Y", Business[b][bY]);
			cache_get_value_name_float(b, "Z", Business[b][bZ]);
			cache_get_value_name_float(b, "iX", Business[b][bIX]);
			cache_get_value_name_float(b, "iY", Business[b][bIY]);
			cache_get_value_name_float(b, "iZ", Business[b][bIZ]);
			cache_get_value_name_float(b, "pX", Business[b][bPX]);
			cache_get_value_name_float(b, "pY", Business[b][bPY]);
			cache_get_value_name_float(b, "pZ", Business[b][bPZ]);
			
			cache_get_value_name_int(b, "Price", Business[b][bPrice]);
			cache_get_value_name_int(b, "Lock", Business[b][bLock]);
			cache_get_value_name_int(b, "Int", Business[b][bInt]);
			cache_get_value_name_int(b, "Type", Business[b][bType]);
			cache_get_value_name_int(b, "Cost", Business[b][bCost]);
			cache_get_value_name_int(b, "VW", Business[b][bVW]);
			cache_get_value_name_int(b, "Communal", Business[b][bCommunal]);
			cache_get_value_name_int(b, "Income", Business[b][bIncome]);
			cache_get_value_name_int(b, "Product", Business[b][bProduct]);
			
			Businesses = b+1;
			
			switch(Business[b][bType]) {
			    case 0: type = 42; // taxi
			    case 1: type = 45;// skin shop
			    case 2: type = 47; // 24/7
			    case 3: type = 47; // fun items
			    case 4: type = 55; // Gas stantions
			    case 5: type = 10; // fast food
			    case 6: type = 50; // dinner
			    case 7: type = 48; // club
			    case 8: type = 6; // gun shop a.k.a ammo
			    case 9: type = 63; // pay'n'spray
			    default: type = 37; // undefined type business
			}
			
			Business[b][bIcon] = CreateDynamicMapIcon(Business[b][bX],Business[b][bY],Business[b][bZ],type,COLOR_WHITE,0,-1,-1);
			Business[b][bPickup][0] = CreateDynamicPickup(1274,23,Business[b][bX],Business[b][bY],Business[b][bZ]);
		 	if(Business[b][bType] == 0) Business[b][bPickup][1] = CreateDynamicPickup(1318,23,Business[b][bIX],Business[b][bIY],Business[b][bIZ],0);
	 		if(Business[b][bType] != 0 && Business[b][bType] != 9) Business[b][bPickup][1] = CreateDynamicPickup(1318,23,BInts[Business[b][bInt]][biX],BInts[Business[b][bInt]][biY],BInts[Business[b][bInt]][biZ],Business[b][bVW],BInts[Business[b][bInt]][biInt]);
            Business[b][bPickup][2] = CreateDynamicPickup(1274,23,Business[b][bPX],Business[b][bPY],Business[b][bPZ],Business[b][bVW],BInts[Business[b][bInt]][biInt]);
		 	CreateDynamic3DTextLabel("Услуги бизнеса",0x1FAEE9FF, Business[b][bPX],Business[b][bPY],Business[b][bPZ]+1.0,8.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 0, -1, -1);
			format(strock,sizeof(strock),"{ffffff}Бизнес: {1faee9}%s\n{ffffff}Владелец: {1faee9}%s",Business[b][bName],Business[b][bOwner]);
   			Business[b][bText] = CreateDynamic3DTextLabel(strock,0xFFFFFFFF, Business[b][bX],Business[b][bY],Business[b][bZ]+1.0,20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 0, -1, -1);
		}
	}
	printf("[Cheery RP] Business: %i",Businesses);
	return true;
}

stock SaveBusiness(b) {
	mysql_format(connects, query,450+1,"UPDATE `buisnesses` SET `Owner` = '%s', `X` = '%.4f', `Y` = '%.4f', `Z` = '%.4f', `iX` = '%.4f', `iY` = '%.4f', `iZ` = '%.4f', `pX` = '%.4f', `pY` = '%.4f', `pZ` = '%.4f', `Price` = '%i', `Lock` = '%i', `Int` = '%i',\
	`Type` = '%i', `Cost` = '%i', `Communal` = '%i', `Income` = '%i', `Product` = '%i' WHERE `ID` = '%i'",
	Business[b][bOwner],Business[b][bX],Business[b][bY],Business[b][bZ],Business[b][bIX],Business[b][bIY],Business[b][bIZ],Business[b][bPX],Business[b][bPY],Business[b][bPZ], Business[b][bPrice],Business[b][bLock],
	Business[b][bInt],Business[b][bType],Business[b][bCost],Business[b][bCommunal],Business[b][bIncome],Business[b][bProduct],Business[b][bID]);
	mysql_tquery(connects, query, "", "");
	return true;	}

apublic LoadGangZones() {
	//new content[24];
	new Zones = 0;
	
	new
		rows;
	cache_get_row_count(rows);
	if(rows)
	{
		for(new g = 0; g < rows; g++)
		{
			cache_get_value_name_int(g, "ID", Zone[g][gID]);
			cache_get_value_name_int(g, "fraction", Zone[g][gFraction]);
			
			cache_get_value_name_float(g, "minx", Zone[g][gminX]);
			cache_get_value_name_float(g, "miny", Zone[g][gminY]);
			cache_get_value_name_float(g, "maxx", Zone[g][gmaxX]);
			cache_get_value_name_float(g, "maxy", Zone[g][gmaxY]);
			
			Zone[g][gID] = GangZoneCreate(Zone[g][gminX],Zone[g][gminY],Zone[g][gmaxX],Zone[g][gmaxY]);
			
			GangZoneShowForAll(Zone[g][gID], GetGangZoneColor(g));
			
			ZoneOnBattle[g] = 0;
		 	Zones++;
		}
    }
    printf("[Cheery RP] Gangzones: %i", Zones);
    return true;
}

stock SaveGangZone(g) {
	mysql_format(connects, query, 136,"UPDATE `gangzones` SET `fraction`='%d',`minx`='%.4f',`miny`='%.4f',`maxx`='%.4f',`maxy`='%.4f' WHERE `ID` = '%d'", Zone[g][gFraction], Zone[g][gminX],Zone[g][gminY],Zone[g][gmaxX],Zone[g][gmaxY], Zone[g][gID]);
    mysql_tquery(connects, query, "", "");
    return true; }

apublic SetPlayerSpawn(playerid) {
    if(Player[playerid][ClothesRound] == true)
	{
 		SetPlayerVirtualWorld(playerid, playerid), AC_SetPlayerPos(playerid,2114.0164,-2697.9404,1842.6862), SetCameraBehindPlayer(playerid), SetPlayerFacingAngle(playerid,267.9624),SetPlayerCameraPos(playerid,2117.0164 + 3,-2697.9404,1842.6862),SetPlayerCameraLookAt(playerid,2117.0164,-2697.9404,1842.6862);
	    TogglePlayerControllable(playerid, 0);
	    if(Player[playerid][pSex] == 1) SetPlayerSkin(playerid, 1), Player[playerid][SSCase] = 1, Player[playerid][ChosenSkin] = 1;
		else SetPlayerSkin(playerid, 12), Player[playerid][SSCase] = 1, Player[playerid][ChosenSkin] = 12;
 		TextDrawShowForPlayer(playerid,brLeft), TextDrawShowForPlayer(playerid,brRight), TextDrawShowForPlayer(playerid,brSelect);
		SelectTextDraw(playerid, 0xFF4040AA);
		return true;
	}
	if(GetPVarInt(playerid,"Recon") == 2) {
		SetPlayerSkin(playerid,GetPVarInt(playerid,"Skin")), AC_SetPlayerPos(playerid,GetPVarFloat(playerid,"X"),GetPVarFloat(playerid,"Y"),GetPVarFloat(playerid,"Z")), SetPlayerInterior(playerid,GetPVarInt(playerid,"Interior")), \
		SetPlayerVirtualWorld(playerid,GetPVarInt(playerid,"VW"));
		SetPVarInt(playerid,"Recon",0);
		return true;
	}
	if(Player[playerid][pWanted] > 6) {
		switch(Player[playerid][pCity]) {
		    case 1: SetPlayerSkin(playerid, 8), SetPlayerVirtualWorld(playerid,1), SetPlayerInterior(playerid,6), AC_SetPlayerPos(playerid,265.0295,77.6146,1001.0391);
		}
		return true;
	}
	#define house   Player[playerid][pHouse]
 	if(house != 9999) {
		SetPlayerInterior(playerid,Ints[House[Player[playerid][pHouse]][hInt]][hiInt]);
		SetPlayerVirtualWorld(playerid,House[house][hID]);
		SetPlayerSkin(playerid, (Player[playerid][pFraction][1] == 0 || Player[playerid][pFraction][1] == 18) ? Player[playerid][pModel][0] : Player[playerid][pModel][1]);
     	AC_SetPlayerPos(playerid,Ints[House[house][hInt]][hiX],Ints[House[house][hInt]][hiY],Ints[House[house][hInt]][hiZ]);
     	FractionColor(playerid);
	    return true;
	}
	#undef house
	switch(Player[playerid][pFraction][1])
	{
	    case 1..5: {
			SetPlayerInterior(playerid,0), AC_SetPlayerPos(playerid,2461.9443,-1643.4260,2047.2329), SetCameraBehindPlayer(playerid),
			SetPlayerFacingAngle(playerid, 179.6538), SetPlayerVirtualWorld(playerid,Player[playerid][pFraction][1]), FractionSkin(playerid), FractionColor(playerid);
			TogglePlayerControllable(playerid, 0);
			SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 6: {
		    SetPlayerInterior(playerid,0), AC_SetPlayerPos(playerid,-414.4763,-117.0656,2102.5557), SetCameraBehindPlayer(playerid),
			SetPlayerFacingAngle(playerid, 128.5722), SetPlayerVirtualWorld(playerid,1), FractionSkin(playerid), FractionColor(playerid);
			TogglePlayerControllable(playerid, 0);
			SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 7: {
		    AC_SetPlayerPos(playerid,238.5037,77.0737,1005.0391), SetCameraBehindPlayer(playerid),
			SetPlayerFacingAngle(playerid, 271.5605), SetPlayerInterior(playerid,6), SetPlayerVirtualWorld(playerid,1), FractionSkin(playerid), FractionColor(playerid);
		}
		case 8: {
            AC_SetPlayerPos(playerid,255.5256,117.5640,1003.2188), SetCameraBehindPlayer(playerid),
			SetPlayerFacingAngle(playerid, 89.0757), SetPlayerInterior(playerid,10), SetPlayerVirtualWorld(playerid,1), FractionSkin(playerid), FractionColor(playerid);
		}
		case 9: {
  			AC_SetPlayerPos(playerid,252.0126,190.3469,1008.1719), SetCameraBehindPlayer(playerid),
			SetPlayerFacingAngle(playerid, 266.4450), SetPlayerInterior(playerid,3), SetPlayerVirtualWorld(playerid,1), FractionSkin(playerid), FractionColor(playerid);
		}
		case 10: {
		    SetPlayerVirtualWorld(playerid,1), AC_SetPlayerPos(playerid,1068.7886,1057.4652,1008.2859), SetCameraBehindPlayer(playerid),
			SetPlayerFacingAngle(playerid, 0.8776), FractionSkin(playerid), FractionColor(playerid);
			TogglePlayerControllable(playerid, 0);
			SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 11: {
		    SetPlayerVirtualWorld(playerid,1), AC_SetPlayerPos(playerid, 292.8196,1608.3123,1083.2759), SetCameraBehindPlayer(playerid),
			SetPlayerFacingAngle(playerid, 49.8905), FractionSkin(playerid), FractionColor(playerid);
			TogglePlayerControllable(playerid, 0);
			SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 12: {
		    AC_SetPlayerPos(playerid,-2027.5558,-116.8153,1035.1719), SetCameraBehindPlayer(playerid),
			SetPlayerFacingAngle(playerid, 86.1800), SetPlayerInterior(playerid,3), SetPlayerVirtualWorld(playerid,1), FractionSkin(playerid), FractionColor(playerid);
		}
		case 13,14: {
		    SetPlayerVirtualWorld(playerid, (Player[playerid][pFraction][1] == 13) ? 1 : 2) , AC_SetPlayerPos(playerid, 1229.9835,-952.2786,1085.0042), SetCameraBehindPlayer(playerid),
			SetPlayerFacingAngle(playerid, 89.6892), FractionSkin(playerid), FractionColor(playerid);
			TogglePlayerControllable(playerid, 0);
			SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 15: {
		    SetPlayerInterior(playerid,0), AC_SetPlayerPos(playerid,1534.6427,751.2248,11.0234), SetCameraBehindPlayer(playerid),
			SetPlayerFacingAngle(playerid, 271.4035), SetPlayerVirtualWorld(playerid,0), FractionSkin(playerid), FractionColor(playerid);
		}
		case 16: {
		    SetPlayerInterior(playerid,0), AC_SetPlayerPos(playerid,2628.1311,1824.2505,11.0234), SetCameraBehindPlayer(playerid),
			SetPlayerFacingAngle(playerid, 90.5275), SetPlayerVirtualWorld(playerid,0), FractionSkin(playerid), FractionColor(playerid);
		}
		case 17: {
		    SetPlayerInterior(playerid,0), AC_SetPlayerPos(playerid,1168.8516,-1270.1460,1001.5732), SetCameraBehindPlayer(playerid),
			SetPlayerFacingAngle(playerid, 128.0995), SetPlayerVirtualWorld(playerid,1), FractionSkin(playerid), FractionColor(playerid);
			TogglePlayerControllable(playerid, 0);
			SetTimerEx("PickupFreeze", 2100, false, "i", playerid);
		}
		case 18: {
		    SetPlayerInterior(playerid,0), AC_SetPlayerPos(playerid,-2486.1147,791.9860,35.1719), SetCameraBehindPlayer(playerid),
			SetPlayerFacingAngle(playerid, 265.6512), SetPlayerVirtualWorld(playerid,0), FractionSkin(playerid), FractionColor(playerid);
		}
		default: {
		    switch(Player[playerid][pLevel]) {
		        case 1,2: {
			 		SetPlayerSkin(playerid,Player[playerid][pModel][0]), SetPlayerColor(playerid,0xFFFFFF33), SetPlayerInterior(playerid,0), SetPlayerVirtualWorld(playerid,0);
					switch(random(2)) {
			  			case 0: AC_SetPlayerPos(playerid,1206.3497,-1750.7460,13.5938),SetCameraBehindPlayer(playerid),SetPlayerFacingAngle(playerid, 44.4938);
				    	case 1: AC_SetPlayerPos(playerid,1761.4923,-1896.2115,13.5619),SetCameraBehindPlayer(playerid),SetPlayerFacingAngle(playerid, 269.8004);
				}   }
				case 3..7: SetPlayerSkin(playerid,Player[playerid][pModel][0]), SetPlayerColor(playerid,0xFFFFFF33), SetPlayerInterior(playerid,0), SetPlayerVirtualWorld(playerid,0), AC_SetPlayerPos(playerid,-1973.0544,137.9011,27.6875),SetCameraBehindPlayer(playerid),SetPlayerFacingAngle(playerid, 88.2247);
				default: SetPlayerSkin(playerid,Player[playerid][pModel][0]), SetPlayerColor(playerid,0xFFFFFF33), SetPlayerInterior(playerid,0), SetPlayerVirtualWorld(playerid,0), AC_SetPlayerPos(playerid,2850.8823,1290.8140,11.3906),SetCameraBehindPlayer(playerid),SetPlayerFacingAngle(playerid, 90.4167);
		}   }
	}
	return true;
}

CreateObjects() {
	//---------====== Выбор скина ========-------------- Choose Skin
    CreateDynamicObject(19464,2115.4641113,-2694.7229004,1841.5689697,0.0000000,90.0000000,358.0000000); //object(wall104) (1)
	CreateDynamicObject(19464,2115.2600098,-2700.6450195,1841.5689697,0.0000000,90.0000000,358.0000000); //object(wall104) (2)
	CreateDynamicObject(19462,2112.8349609,-2698.7009277,1843.4360352,0.0000000,0.0000000,357.7500000); //object(wall102) (1)
	CreateDynamicObject(19450,2113.9890137,-2693.8750000,1843.4360352,0.0000000,0.0000000,293.7500000); //object(wall090) (1)
	CreateDynamicObject(19450,2113.3369141,-2701.3459473,1843.4360352,0.0000000,0.0000000,243.7469482); //object(wall090) (2)
	CreateDynamicObject(2283,2113.1250000,-2695.5061035,1843.8909912,0.0000000,0.0000000,87.5000000); //object(frame_thick_3) (1)
	CreateDynamicObject(2274,2113.3469238,-2700.3999023,1843.3909912,0.0000000,0.0000000,88.0000000); //object(frame_fab_6) (1)
	CreateDynamicObject(2256,2113.0090332,-2697.8569336,1842.6660156,0.0000000,0.0000000,87.7500000); //object(frame_clip_3) (1)
	CreateDynamicObject(1702,2114.5710449,-2694.8798828,1841.6860352,0.0000000,0.0000000,22.0000000); //object(kb_couch06) (1)
	CreateDynamicObject(2082,2115.6120605,-2696.1499023,1841.6860352,0.0000000,0.0000000,23.0000000); //object(coffee_med_3) (1)
	CreateDynamicObject(1215,2117.7360840,-2692.9819336,1842.2509766,0.0000000,0.0000000,0.0000000); //object(bollardlight) (1)
	CreateDynamicObject(1215,2113.1040039,-2700.9089355,1841.8900146,0.0000000,0.0000000,0.0000000); //object(bollardlight) (2)
	CreateDynamicObject(1723,2116.0039062,-2702.1569824,1841.6860352,0.0000000,0.0000000,131.5000000); //object(mrk_seating1) (1)
	CreateDynamicObject(19171,2114.5979004,-2701.8720703,1844.0269775,90.0000000,90.0000000,62.5002136); //object(gtasamap8) (1)
	CreateDynamicObject(2818,2114.4460449,-2698.4680176,1841.6860352,0.0000000,0.0000000,88.5000000); //object(gb_bedrug02) (1)
	CreateDynamicObject(19452,2114.0759277,-2697.8930664,1845.0000000,0.0000000,91.9999695,356.7500000); //object(wall092) (1)
	CreateDynamicObject(19452,2117.3000488,-2698.0600586,1844.9000244,0.0000000,91.5001221,356.9980469); //object(wall092) (2)
	CreateDynamicObject(1215,2113.7539062,-2694.6455078,1841.8699951,0.0000000,0.0000000,0.0000000); //object(bollardlight) (3)
	CreateDynamicObject(1215,2117.7353516,-2692.9814453,1842.2509766,0.0000000,0.0000000,0.0000000); //object(bollardlight) (4)
	CreateDynamicObject(1215,2117.3701172,-2702.8469238,1842.2509766,0.0000000,0.0000000,0.0000000); //object(bollardlight) (5)
	CreateDynamicObject(1215,2117.3701172,-2702.8466797,1842.2509766,0.0000000,0.0000000,0.0000000); //object(bollardlight) (6)
	CreateDynamicObject(8168,1678.9399414,-1091.0699463,24.8540001,0.0000000,0.0000000,288.0000000); //object(vgs_guardhouse01) (1)
	//---------============ Ballas ============------
	CreateDynamicObject(19379,1996.4370117,-1188.1770020,1470.0000000,0.0000000,90.0000000,89.9998779); //object(wall027) (1)
	CreateDynamicObject(19455,1996.4370117,-1193.2650146,1471.8360596,0.0000000,0.0000000,90.0000000); //object(wall095) (1)
	CreateDynamicObject(1498,1997.7010498,-1193.2010498,1470.0860596,0.0000000,0.0000000,0.0000000); //object(gen_doorext03) (1)
	CreateDynamicObject(19379,2006.0699463,-1188.1770020,1470.0000000,0.0000000,90.0000000,90.0000000); //object(wall027) (2)
	CreateDynamicObject(19455,2006.0450439,-1193.2650146,1471.8360596,0.0000000,0.0000000,90.0000000); //object(wall095) (2)
	CreateDynamicObject(19455,2001.2700195,-1195.6469727,1471.8360596,0.0000000,0.0000000,0.0000000); //object(wall095) (3)
	CreateDynamicObject(19392,2001.2700195,-1189.2409668,1471.8360596,0.0000000,0.0000000,0.0000000); //object(wall040) (1)
	CreateDynamicObject(19455,2001.2700195,-1182.8540039,1471.8360596,0.0000000,0.0000000,0.0000000); //object(wall095) (4)
	CreateDynamicObject(19379,1996.4370117,-1177.6870117,1470.0000000,0.0000000,90.0000000,90.0000000); //object(wall027) (3)
	CreateDynamicObject(19455,1998.5040283,-1182.0689697,1471.8360596,0.0000000,0.0000000,90.0000000); //object(wall095) (7)
	CreateDynamicObject(19377,1986.8170166,-1180.3830566,1470.0000000,0.0000000,90.0000000,90.0000000); //object(wall025) (1)
	CreateDynamicObject(19392,1991.7020264,-1183.7430420,1471.8360596,0.0000000,0.0000000,0.0000000); //object(wall040) (2)
	CreateDynamicObject(19389,1991.5989990,-1183.7430420,1471.8360596,0.0000000,0.0000000,0.0000000); //object(wall037) (1)
	CreateDynamicObject(19451,1986.7490234,-1182.5729980,1471.8360596,0.0000000,0.0000000,90.0000000); //object(wall091) (2)
	CreateDynamicObject(19451,1986.7419434,-1185.6230469,1471.8360596,0.0000000,0.0000000,90.0000000); //object(wall091) (3)
	CreateDynamicObject(19451,1988.5119629,-1184.9520264,1471.8360596,0.0000000,0.0000000,0.0000000); //object(wall091) (4)
	CreateDynamicObject(2518,1991.0989990,-1185.0000000,1470.3000488,0.0000000,0.0000000,180.0000000); //object(cj_b_sink2) (1)
	CreateDynamicObject(2670,1989.9100342,-1185.3289795,1470.1779785,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_1) (1)
	CreateDynamicObject(2528,1989.0999756,-1184.2769775,1470.0860596,0.0000000,0.0000000,90.0000000); //object(cj_toilet3) (1)
	CreateDynamicObject(19455,1988.8769531,-1182.0689697,1471.8360596,0.0000000,0.0000000,90.0000000); //object(wall095) (8)
	CreateDynamicObject(1494,1991.7020264,-1184.4849854,1470.0860596,0.0000000,0.0000000,90.0000000); //object(gen_doorint03) (1)
	CreateDynamicObject(1710,1996.7530518,-1192.6689453,1470.0860596,0.0000000,0.0000000,180.0000000); //object(kb_couch07) (1)
	CreateDynamicObject(2048,1991.7979736,-1186.8599854,1472.3370361,0.0000000,0.0000000,90.0000000); //object(cj_flag2) (1)
	CreateDynamicObject(2315,1995.6560059,-1190.4279785,1470.0860596,0.0000000,0.0000000,180.0000000); //object(cj_tv_table4) (1)
	CreateDynamicObject(1786,1994.7640381,-1190.1960449,1470.5820312,0.0000000,0.0000000,0.0000000); //object(swank_tv_4) (1)
	CreateDynamicObject(2838,1992.5570068,-1191.3990479,1470.0860596,0.0000000,0.0000000,0.0000000); //object(gb_takeaway03) (1)
	CreateDynamicObject(1764,1998.7800293,-1183.8330078,1470.0860596,0.0000000,0.0000000,310.0000000); //object(low_couch_2) (2)
	CreateDynamicObject(19455,1998.2860107,-1182.2409668,1471.8360596,0.0000000,0.0000000,38.0000000); //object(wall095) (9)
	CreateDynamicObject(1432,2004.0000000,-1191.3929443,1470.0860596,0.0000000,0.0000000,0.0000000); //object(dyn_table_2) (1)
	CreateDynamicObject(19455,2006.1059570,-1184.5699463,1471.8360596,0.0000000,0.0000000,90.0000000); //object(wall095) (10)
	CreateDynamicObject(19455,2007.1960449,-1189.1899414,1471.8360596,0.0000000,0.0000000,0.0000000); //object(wall095) (11)
	CreateDynamicObject(2132,2003.8439941,-1185.1059570,1470.0860596,0.0000000,0.0000000,0.0000000); //object(cj_kitch2_sink) (1)
	CreateDynamicObject(2131,2001.8840332,-1185.1090088,1470.0860596,0.0000000,0.0000000,0.0000000); //object(cj_kitch2_fridge) (1)
	CreateDynamicObject(2340,2005.8310547,-1185.0970459,1470.0860596,0.0000000,0.0000000,0.0000000); //object(cj_kitch2_washer) (1)
	CreateDynamicObject(2341,2006.8039551,-1185.0930176,1470.0860596,0.0000000,0.0000000,0.0000000); //object(cj_kitch2_corner) (1)
	CreateDynamicObject(3034,2004.1639404,-1193.1789551,1472.1169434,0.0000000,0.0000000,180.0000000); //object(bd_window) (1)
	CreateDynamicObject(2823,2005.9040527,-1185.0550537,1471.1390381,0.0000000,0.0000000,0.0000000); //object(gb_kitchtakeway01) (1)
	CreateDynamicObject(1763,2006.5949707,-1188.3449707,1470.0860596,0.0000000,0.0000000,270.0000000); //object(low_couch_1) (1)
	CreateDynamicObject(1520,2006.4820557,-1190.2440186,1470.0860596,0.0000000,0.0000000,0.0000000); //object(dyn_wine_bounce) (1)
	CreateDynamicObject(1512,2006.4279785,-1190.0999756,1470.2840576,0.0000000,0.0000000,0.0000000); //object(dyn_wine_03) (1)
	CreateDynamicObject(4227,2007.1440430,-1199.8050537,1471.5909424,0.0000000,0.0000000,270.0000000); //object(graffiti_lan01) (2)
	CreateDynamicObject(1498,1993.9150391,-1182.1479492,1470.0860596,0.0000000,0.0000000,0.0000000); //object(gen_doorext03) (2)
	CreateDynamicObject(1487,1995.6350098,-1190.4899902,1470.7790527,0.0000000,0.0000000,0.0000000); //object(dyn_wine_1) (9)
	CreateDynamicObject(19392,1991.7020264,-1190.1290283,1471.8360596,0.0000000,0.0000000,0.0000000); //object(wall040) (3)
	CreateDynamicObject(19359,1991.5989990,-1186.9470215,1471.8360596,0.0000000,0.0000000,0.0000000); //object(wall007) (1)
	CreateDynamicObject(19363,1991.7020264,-1186.9470215,1471.8360596,0.0000000,0.0000000,0.0000000); //object(wall011) (1)
	CreateDynamicObject(19363,1991.7020264,-1193.3060303,1471.8360596,0.0000000,0.0000000,0.0000000); //object(wall011) (2)
	CreateDynamicObject(1502,1991.7020264,-1190.8800049,1470.0860596,0.0000000,0.0000000,90.0000000); //object(gen_doorint04) (1)
	CreateDynamicObject(19379,1986.8170166,-1190.9179688,1470.0000000,0.0000000,90.0000000,89.9999390); //object(wall027) (4)
	CreateDynamicObject(19455,1986.8780518,-1188.5369873,1471.8360596,0.0000000,0.0000000,90.0000000); //object(wall095) (13)
	CreateDynamicObject(19363,1988.5679932,-1190.0520020,1471.8360596,0.0000000,0.0000000,0.0000000); //object(wall011) (4)
	CreateDynamicObject(19455,1987.0009766,-1194.6870117,1471.8360596,0.0000000,0.0000000,90.0000000); //object(wall095) (15)
	CreateDynamicObject(19363,1986.8879395,-1191.5699463,1471.8360596,0.0000000,0.0000000,90.0000000); //object(wall011) (6)
	CreateDynamicObject(19363,1985.3769531,-1189.8790283,1471.8360596,0.0000000,0.0000000,0.0000000); //object(wall011) (7)
	CreateDynamicObject(19379,1977.1929932,-1190.9179688,1470.0000000,0.0000000,90.0000000,90.0000000); //object(wall027) (5)
	CreateDynamicObject(19455,1977.2860107,-1188.5369873,1471.8360596,0.0000000,0.0000000,90.0000000); //object(wall095) (16)
	CreateDynamicObject(19455,1977.4000244,-1194.6870117,1471.8360596,0.0000000,0.0000000,90.0000000); //object(wall095) (17)
	CreateDynamicObject(19455,1981.7419434,-1191.5860596,1471.8360596,0.0000000,0.0000000,0.0000000); //object(wall095) (18)
	CreateDynamicObject(1271,1984.8089600,-1189.1719971,1470.4360352,0.0000000,0.0000000,0.0000000); //object(gunbox) (1)
	CreateDynamicObject(1271,1983.7580566,-1189.1510010,1470.4360352,0.0000000,0.0000000,0.0000000); //object(gunbox) (2)
	CreateDynamicObject(1271,1982.5570068,-1189.1269531,1470.4360352,0.0000000,0.0000000,0.0000000); //object(gunbox) (4)
	CreateDynamicObject(1271,1983.0150146,-1190.0119629,1470.4360352,0.0000000,0.0000000,0.0000000); //object(gunbox) (5)
	CreateDynamicObject(1271,1983.8900146,-1190.0290527,1470.4360352,0.0000000,0.0000000,0.0000000); //object(gunbox) (6)
	CreateDynamicObject(1271,1984.7650146,-1190.0450439,1470.4360352,0.0000000,0.0000000,0.0000000); //object(gunbox) (7)
	CreateDynamicObject(1271,1983.8060303,-1189.7020264,1471.1269531,0.0000000,0.0000000,0.0000000); //object(gunbox) (8)
	CreateDynamicObject(1271,1984.5689697,-1190.2669678,1471.1269531,0.0000000,0.0000000,0.0000000); //object(gunbox) (10)
	CreateDynamicObject(1271,1984.6510010,-1189.2700195,1471.1269531,0.0000000,0.0000000,0.0000000); //object(gunbox) (12)
	CreateDynamicObject(1271,1984.4759521,-1189.6250000,1471.8179932,0.0000000,0.0000000,0.0000000); //object(gunbox) (13)
	CreateDynamicObject(3052,1982.2110596,-1190.0069580,1470.2120361,0.0000000,0.0000000,0.0000000); //object(db_ammo) (2)
	CreateDynamicObject(3052,1982.2500000,-1190.4689941,1470.2120361,0.0000000,0.0000000,0.0000000); //object(db_ammo) (3)
	CreateDynamicObject(3052,1982.2469482,-1190.3580322,1470.4959717,0.0000000,0.0000000,40.0000000); //object(db_ammo) (4)
	CreateDynamicObject(3052,1982.9919434,-1190.1109619,1470.9029541,0.0000000,0.0000000,350.0000000); //object(db_ammo) (5)
	CreateDynamicObject(3052,1982.9890137,-1190.2640381,1471.1870117,0.0000000,0.0000000,359.9969482); //object(db_ammo) (6)
	CreateDynamicObject(3052,1983.8609619,-1190.2669678,1470.9029541,0.0000000,0.0000000,359.9945068); //object(db_ammo) (7)
	CreateDynamicObject(3052,1984.4930420,-1190.5300293,1471.5939941,0.0000000,0.0000000,359.9945068); //object(db_ammo) (8)
	CreateDynamicObject(1706,1990.6569824,-1194.0389404,1470.0860596,0.0000000,0.0000000,180.0000000); //object(kb_couch03) (2)
	CreateDynamicObject(2670,1990.7559814,-1193.4959717,1470.1779785,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_1) (2)
	CreateDynamicObject(17969,1984.8000488,-1188.6510010,1472.0830078,0.0000000,0.0000000,90.0000000); //object(hub_graffitti) (2)
	CreateDynamicObject(1271,1982.3640137,-1194.1070557,1470.4360352,0.0000000,0.0000000,0.0000000); //object(gunbox) (14)
	CreateDynamicObject(1271,1982.4680176,-1193.0939941,1470.4360352,0.0000000,0.0000000,0.0000000); //object(gunbox) (15)
	CreateDynamicObject(1271,1982.3549805,-1193.5760498,1471.1269531,0.0000000,0.0000000,0.0000000); //object(gunbox) (16)
	CreateDynamicObject(1502,2001.2700195,-1189.9899902,1470.0860596,0.0000000,0.0000000,90.0000000); //object(gen_doorint04) (2)
	CreateDynamicObject(2821,2003.9329834,-1191.3430176,1470.7010498,0.0000000,0.0000000,0.0000000); //object(gb_foodwrap01) (2)
	CreateDynamicObject(1575,1982.5679932,-1189.0539551,1470.7500000,0.0000000,0.0000000,0.0000000); //object(drug_white) (1)
	CreateDynamicObject(1575,1983.7690430,-1189.9300537,1471.4799805,0.0000000,0.0000000,0.0000000); //object(drug_white) (2)
	CreateDynamicObject(1575,1983.7490234,-1189.5500488,1471.4799805,0.0000000,0.0000000,0.0000000); //object(drug_white) (3)
	CreateDynamicObject(1575,1983.0889893,-1190.7089844,1470.0999756,0.0000000,0.0000000,0.0000000); //object(drug_white) (4)
	CreateDynamicObject(2262,2005.0789795,-1185.1829834,1472.0930176,0.0000000,0.0000000,0.0000000); //object(frame_slim_3) (1)
	CreateDynamicObject(2674,2005.9610596,-1189.3139648,1470.1080322,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_2) (1)
	CreateDynamicObject(2673,1998.9510498,-1184.8850098,1470.1739502,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_5) (1)
	CreateDynamicObject(19377,2006.0699463,-1188.1770020,1473.6500244,0.0000000,90.0000000,89.9999695); //object(wall025) (2)
	CreateDynamicObject(19377,1996.4370117,-1188.1770020,1473.6500244,0.0000000,90.0000000,89.9999390); //object(wall025) (3)
	CreateDynamicObject(19377,1986.8170166,-1190.9179688,1473.6500244,0.0000000,90.0000000,89.9999390); //object(wall025) (4)
	CreateDynamicObject(19377,1977.1929932,-1190.7700195,1473.6500244,0.0000000,90.0000000,90.0000000); //object(wall025) (5)
	CreateDynamicObject(19377,1996.4370117,-1177.6870117,1473.6500244,0.0000000,90.0000000,89.9999695); //object(wall025) (6)
	CreateDynamicObject(19377,1986.8170166,-1180.3830566,1473.6500244,0.0000000,90.0000000,90.0000000); //object(wall025) (7)
	CreateDynamicObject(18608,1995.0989990,-1182.4790039,1474.6999512,0.0000000,0.0000000,0.0000000); //object(counts_lights01) (1)
	CreateDynamicObject(18608,2004.3060303,-1185.1810303,1474.6999512,0.0000000,0.0000000,0.0000000); //object(counts_lights01) (2)
	CreateDynamicObject(18608,2004.2840576,-1188.4360352,1474.6999512,0.0000000,0.0000000,0.0000000); //object(counts_lights01) (3)
	CreateDynamicObject(18608,1995.0989990,-1186.1800537,1474.6999512,0.0000000,0.0000000,0.0000000); //object(counts_lights01) (4)
	CreateDynamicObject(18608,1982.6870117,-1193.1199951,1474.6999512,0.0000000,0.0000000,90.0000000); //object(counts_lights01) (5)
	CreateDynamicObject(18608,1979.5169678,-1193.1199951,1474.6999512,0.0000000,0.0000000,90.0000000); //object(counts_lights01) (6)
	//============= Garage ==================
	CreateDynamicObject(19449,903.9710083,-358.8359985,2176.5297852,0.0000000,90.0000000,180.0000000); //object(wall089) (1)
	CreateDynamicObject(19449,893.5280151,-358.8640137,2176.5300293,0.0000000,90.0000000,359.9945068); //object(wall089) (4)
	CreateDynamicObject(19456,900.8709717,-363.6149902,2178.3659668,0.0000000,0.0000000,269.5000000); //object(wall096) (1)
	CreateDynamicObject(19364,894.4489136,-363.5729980,2178.3659668,0.0000000,0.0000000,90.0000000); //object(wall012) (1)
	CreateDynamicObject(19456,892.9500122,-358.8269958,2178.3659668,0.0000000,0.0000000,179.4946289); //object(wall096) (2)
	CreateDynamicObject(19364,894.5410156,-354.1969910,2178.3659668,0.0000000,0.0000000,90.0000000); //object(wall012) (2)
	CreateDynamicObject(19456,900.9600220,-354.1969910,2178.3659668,0.0000000,0.0000000,269.9946289); //object(wall096) (3)
	CreateDynamicObject(19456,905.7550049,-359.0060120,2178.3659668,0.0000000,0.0000000,179.4891357); //object(wall096) (4)
	CreateDynamicObject(5020,892.9899902,-358.9049988,2178.3010254,0.0000000,0.0000000,359.5000000); //object(mul_las) (1)
	CreateDynamicObject(19454,904.4000244,-358.9320068,2180.1999512,0.0000000,90.0000000,0.0000000); //object(wall094) (1)
	CreateDynamicObject(19454,900.9000244,-358.9909973,2180.1999512,0.0000000,90.0000000,0.0000000); //object(wall094) (2)
	CreateDynamicObject(19454,897.4019775,-358.9909973,2180.1999512,0.0000000,90.0000000,0.0000000); //object(wall094) (3)
	CreateDynamicObject(19454,893.9019775,-359.0639954,2180.1999512,0.0000000,90.0000000,0.0000000); //object(wall094) (4)
	CreateDynamicObject(14438,903.2239990,-358.9559937,2182.1398926,0.0000000,0.0000000,0.0000000); //object(carter-light04) (4)
	CreateDynamicObject(2446,903.0510254,-354.5100098,2176.6159668,0.0000000,0.0000000,0.0000000); //object(cj_ff_conter_5) (1)
	CreateDynamicObject(2485,903.0549927,-354.6289978,2177.6599121,0.0000000,0.0000000,344.0000000); //object(model_car_1) (1)
	CreateDynamicObject(1738,905.4619751,-357.1440125,2177.2709961,0.0000000,0.0000000,90.0000000); //object(cj_radiator_old) (1)
	CreateDynamicObject(1738,905.4609985,-358.1940002,2177.2709961,0.0000000,0.0000000,90.0000000); //object(cj_radiator_old) (2)
	CreateDynamicObject(1738,905.4710083,-359.2439880,2177.2709961,0.0000000,0.0000000,90.0000000); //object(cj_radiator_old) (3)
	CreateDynamicObject(1749,902.0289917,-354.7290039,2176.6159668,0.0000000,0.0000000,310.0000000); //object(med_tv_3) (1)
	CreateDynamicObject(1778,905.2329712,-354.8890076,2176.6159668,0.0000000,0.0000000,310.0000000); //object(cj_mop_pail) (1)
	CreateDynamicObject(2226,901.7570190,-354.7529907,2177.1860352,0.0000000,0.0000000,0.0000000); //object(low_hi_fi_3) (1)
	CreateDynamicObject(19357,900.4890137,-356.7650146,2176.5300293,0.0000000,90.0000000,0.0000000); //object(wall005) (1)
	CreateDynamicObject(19357,896.9890137,-356.7650146,2176.5300293,0.0000000,90.0000000,0.0000000); //object(wall005) (2)
	CreateDynamicObject(19357,896.9890137,-361.0469971,2176.5300293,0.0000000,90.0000000,0.0000000); //object(wall005) (3)
	CreateDynamicObject(19436,896.6459961,-358.9330139,2174.6159668,0.0000000,90.0000000,0.0000000); //object(wall076) (1)
	CreateDynamicObject(19436,900.1409912,-358.9330139,2174.6159668,0.0000000,90.0000000,0.0000000); //object(wall076) (2)
	CreateDynamicObject(19363,896.9429932,-358.2789917,2175.0129395,90.0000000,90.0000000,180.0000000); //object(wall011) (2)
	CreateDynamicObject(19363,896.9299927,-359.5589905,2175.0129395,90.0000000,90.0000000,179.9945068); //object(wall011) (3)
	CreateDynamicObject(19436,895.1808472,-359.0050049,2174.7658691,0.0000000,0.0000000,0.0000000); //object(wall076) (4)
	CreateDynamicObject(19363,900.3040161,-358.2789917,2175.0129395,90.0000000,90.0000000,179.9945068); //object(wall011) (4)
	CreateDynamicObject(19363,899.7819824,-359.5589905,2175.0129395,90.0000000,90.0000000,179.9945068); //object(wall011) (5)
	CreateDynamicObject(14877,901.5100098,-358.9360046,2174.5310059,0.0000000,0.0000000,0.0000000); //object(michelle-stairs) (1)
	CreateDynamicObject(19357,900.4790039,-361.0469971,2176.5300293,0.0000000,90.0000000,0.0000000); //object(wall005) (5)
	CreateDynamicObject(19357,900.4799805,-364.2489929,2176.5300293,0.0000000,90.0000000,0.0000000); //object(wall005) (6)
	CreateDynamicObject(19357,896.9898682,-364.2489929,2176.5300293,0.0000000,90.0000000,0.0000000); //object(wall005) (7)
	CreateDynamicObject(19357,900.4890137,-353.5990295,2176.5300293,0.0000000,90.0000000,0.0000000); //object(wall005) (8)
	CreateDynamicObject(19357,896.9890137,-353.5990295,2176.5300293,0.0000000,90.0000000,0.0000000); //object(wall005) (9)
	CreateDynamicObject(1114,901.9099731,-363.1279907,2176.6159668,287.0000000,23.0000000,8.0000000); //object(exh_lr_slv2) (1)
	CreateDynamicObject(1023,903.0789795,-363.3049927,2176.6159668,0.0000000,0.0000000,0.0000000); //object(spl_b_bbb_m) (1)
	CreateDynamicObject(1184,902.6430054,-362.9649963,2176.7749023,0.0000000,0.0000000,186.0000000); //object(rbmp_lr_bl1) (1)
	CreateDynamicObject(1079,893.0009766,-362.7709961,2179.4040527,0.0000000,0.0000000,0.0000000); //object(wheel_sr1) (1)
	CreateDynamicObject(1079,893.0540161,-355.0350037,2179.4040527,0.0000000,0.0000000,0.0000000); //object(wheel_sr1) (2)
	CreateDynamicObject(3785,895.2670288,-358.8970032,2175.9699707,0.0000000,0.0000000,0.0000000); //object(bulkheadlight) (1)
	CreateDynamicObject(2277,899.3989868,-363.0289917,2178.7241211,0.0000000,350.0000000,180.0000000); //object(frame_fab_2) (1)
	CreateDynamicObject(2276,897.0520020,-362.9809875,2178.5568848,0.0000000,0.0000000,179.5000000); //object(frame_fab_3) (1)
	CreateDynamicObject(1960,899.4569702,-354.3559875,2178.7438965,0.0000000,0.0000000,0.0000000); //object(record2) (1)
	CreateDynamicObject(1961,895.5369873,-354.3089905,2178.5219727,0.0000000,0.0000000,0.0000000); //object(record3) (1)
	CreateDynamicObject(1962,900.3649902,-354.3089905,2178.4260254,0.0000000,0.0000000,0.0000000); //object(record1) (1)
	CreateDynamicObject(1763,904.7280273,-361.3529968,2176.6159668,0.0000000,0.0000000,240.0000000); //object(low_couch_1) (1)
	CreateDynamicObject(1759,904.5390015,-359.5870056,2176.6169434,0.0000000,0.0000000,300.0000000); //object(low_single_1) (1)
	CreateDynamicObject(1817,903.1619873,-362.0989990,2176.6159668,0.0000000,0.0000000,40.0000000); //object(coffee_med_2) (1)
	CreateDynamicObject(2000,899.4489746,-363.0700073,2176.6240234,0.0000000,0.0000000,180.0000000); //object(filing_cab_nu) (1)
	CreateDynamicObject(2063,897.2109985,-363.1409912,2177.5249023,0.0000000,0.0000000,356.7500000); //object(cj_greenshelves) (1)
	CreateDynamicObject(2066,900.2119751,-363.4849854,2176.6159668,0.0000000,0.0000000,10.0000000); //object(cj_m_fileing2) (1)
	CreateDynamicObject(1650,900.4890137,-354.4700012,2176.9230957,0.0000000,0.0000000,310.0000000); //object(petrolcanm) (1)
	CreateDynamicObject(1650,899.8800049,-354.4349976,2176.9230957,0.0000000,0.0000000,258.9957275); //object(petrolcanm) (2)
	CreateDynamicObject(1650,899.9270020,-354.8219910,2176.7229004,90.0000000,0.0000000,258.9916992); //object(petrolcanm) (3)
	CreateDynamicObject(2690,893.2189941,-354.4070129,2178.5249023,0.0000000,0.0000000,10.0000000); //object(cj_fire_ext) (1)
	CreateDynamicObject(1506,898.4769897,-354.2430115,2176.6250000,0.0000000,0.0000000,180.0000000); //object(gen_doorext08) (1)
	//================= Autosalon ==============
	AddStaticVehicleEx(412,466.0654297,-941.5517578,2381.8439941,340.0000000,-1,-1,700); //Voodoo
	CreateDynamicObject(19458,426.4689941,-984.9739990,2387.9880371,0.0000000,90.0000000,0.0000000); //object(wall098) (1)
	CreateDynamicObject(19458,429.9689941,-984.9739990,2387.9880371,0.0000000,90.0000000,0.0000000); //object(wall098) (2)
	CreateDynamicObject(19458,433.4689941,-984.9739990,2387.9880371,0.0000000,90.0000000,0.0000000); //object(wall098) (3)
	CreateDynamicObject(19458,436.9620056,-984.9739990,2387.9880371,0.0000000,90.0000000,0.0000000); //object(wall098) (5)
	CreateDynamicObject(19458,436.9620056,-994.5999756,2387.9880371,0.0000000,90.0000000,0.0000000); //object(wall098) (6)
	CreateDynamicObject(19458,433.4689941,-994.5999756,2387.9880371,0.0000000,90.0000000,0.0000000); //object(wall098) (7)
	CreateDynamicObject(19458,429.9689941,-994.5999756,2387.9880371,0.0000000,90.0000000,0.0000000); //object(wall098) (8)
	CreateDynamicObject(19458,426.4700012,-994.5999756,2387.9880371,0.0000000,90.0000000,0.0000000); //object(wall098) (9)
	CreateDynamicObject(19458,422.9699097,-994.5999756,2387.9880371,0.0000000,90.0000000,0.0000000); //object(wall098) (10)
	CreateDynamicObject(19458,422.9700012,-984.9739990,2387.9880371,0.0000000,90.0000000,0.0000000); //object(wall098) (12)
	CreateDynamicObject(19450,435.7399902,-984.0750122,2389.8239746,0.0000000,0.0000000,38.0000000); //object(wall090) (1)
	CreateDynamicObject(19450,433.9819946,-998.3200073,2389.8239746,0.0000000,0.0000000,279.9945068); //object(wall090) (3)
	CreateDynamicObject(19450,425.6579895,-998.9459839,2389.8239746,0.0000000,0.0000000,267.4920654); //object(wall090) (4)
	CreateDynamicObject(19458,428.3599854,-978.4169922,2387.9880371,0.0000000,90.0000000,270.0000000); //object(wall098) (14)
	CreateDynamicObject(19358,432.7958984,-978.7314453,2389.8239746,0.0000000,0.0000000,0.0000000); //object(wall006) (1)
	CreateDynamicObject(19450,428.4719849,-977.1729736,2389.8239746,0.0000000,0.0000000,89.9962158); //object(wall090) (6)
	CreateDynamicObject(19358,424.3580017,-978.7899780,2389.8239746,0.0000000,0.0000000,346.2500000); //object(wall006) (2)
	CreateDynamicObject(19450,423.9746094,-985.0546875,2389.8239746,0.0000000,0.0000000,179.9945068); //object(wall090) (7)
	CreateDynamicObject(19400,430.2493896,-984.1799927,2389.8239746,0.0000000,0.0000000,270.0000000); //object(wall048) (2)
	CreateDynamicObject(19354,433.0280151,-983.1710205,2389.8239746,0.0000000,0.0000000,310.0000000); //object(wall002) (2)
	CreateDynamicObject(19354,425.6000061,-984.1779785,2389.8239746,0.0000000,0.0000000,269.9957275); //object(wall002) (3)
	CreateDynamicObject(1502,427.1700134,-984.2169800,2388.0739746,0.0000000,0.0000000,0.0000000); //object(gen_doorint04) (1)
	CreateDynamicObject(1649,430.3030090,-984.1450195,2388.7399902,0.0000000,90.0000000,0.0000000); //object(wglasssmash) (1)
	CreateDynamicObject(19448,425.4609985,-981.7680054,2391.5690918,0.0000000,90.0000000,0.0000000); //object(wall088) (1)
	CreateDynamicObject(19448,425.4580078,-991.3989868,2391.5690918,0.0000000,90.0000000,0.0000000); //object(wall088) (2)
	CreateDynamicObject(19448,428.9599609,-981.7675781,2391.5690918,0.0000000,90.0000000,0.0000000); //object(wall088) (3)
	CreateDynamicObject(19448,432.4590149,-981.7670288,2391.5690918,0.0000000,90.0000000,0.0000000); //object(wall088) (4)
	CreateDynamicObject(19448,432.4590149,-991.4190063,2391.5690918,0.0000000,90.0000000,0.0000000); //object(wall088) (5)
	CreateDynamicObject(19448,428.9599915,-991.3989868,2391.5690918,0.0000000,90.0000000,0.0000000); //object(wall088) (6)
	CreateDynamicObject(19448,435.9270020,-986.6500244,2391.5690918,0.0000000,90.0000000,0.0000000); //object(wall088) (7)
	CreateDynamicObject(19450,437.3590088,-990.7249756,2389.8239746,0.0000000,0.0000000,359.9945068); //object(wall090) (8)
	CreateDynamicObject(19358,437.3590088,-997.0419922,2389.8239746,0.0000000,0.0000000,0.0000000); //object(wall006) (3)
	CreateDynamicObject(19448,435.9270020,-996.2069702,2391.5690918,0.0000000,90.0000000,0.0000000); //object(wall088) (8)
	CreateDynamicObject(19448,429.3630066,-997.9599609,2391.5690918,0.0000000,90.0000000,270.0000000); //object(wall088) (9)
	CreateDynamicObject(19450,423.9750061,-994.0020142,2389.8239746,0.0000000,0.0000000,179.9945068); //object(wall090) (10)
	CreateDynamicObject(19356,422.9400024,-997.9599609,2391.5690918,0.0000000,90.0000000,270.0000000); //object(wall004) (1)
	CreateDynamicObject(14438,431.1499939,-988.7940063,2393.3500977,0.0000000,0.0000000,90.0000000); //object(carter-light04) (1)
	CreateDynamicObject(3963,424.0859985,-992.7910156,2390.3200684,0.0000000,0.0000000,269.0000000); //object(lee_plane08) (1)
	CreateDynamicObject(2290,428.9840088,-997.7949829,2388.0739746,0.0000000,0.0000000,180.0000000); //object(swk_couch_1) (1)
	CreateDynamicObject(2290,424.9240112,-996.0599976,2388.0739746,0.0000000,0.0000000,89.9944763); //object(swk_couch_1) (2)
	CreateDynamicObject(2282,424.5639954,-996.5770264,2389.7770996,0.0000000,0.0000000,90.0000000); //object(frame_thick_4) (1)
	CreateDynamicObject(2280,424.5880127,-989.0999756,2389.0991211,0.0000000,0.0000000,90.0000000); //object(frame_thick_1) (1)
	CreateDynamicObject(1754,428.8829956,-994.1229858,2388.0739746,0.0000000,0.0000000,320.0000000); //object(swank_single_1) (1)
	CreateDynamicObject(2082,426.7690125,-996.0709839,2388.0739746,0.0000000,0.0000000,0.0000000); //object(coffee_med_3) (1)
	CreateDynamicObject(2161,430.9429932,-977.2670288,2389.9128418,0.0000000,0.0000000,0.0000000); //object(med_office_unit_4) (1)
	CreateDynamicObject(2162,429.1059875,-977.2589722,2389.9128418,0.0000000,0.0000000,0.0000000); //object(med_office_unit_1) (1)
	CreateDynamicObject(2164,430.5260010,-977.2949829,2388.0739746,0.0000000,0.0000000,0.0000000); //object(med_office_unit_5) (1)
	CreateDynamicObject(2164,428.7669983,-977.3040161,2388.0739746,0.0000000,0.0000000,0.0000000); //object(med_office_unit_5) (2)
	CreateDynamicObject(2167,432.9450073,-983.2570190,2388.0739746,0.0000000,0.0000000,220.0000000); //object(med_office_unit_7) (1)
	CreateDynamicObject(2197,432.6719971,-982.1480103,2388.0739746,0.0000000,0.0000000,304.5000000); //object(filling_cabinet) (1)
	CreateDynamicObject(2606,430.1740112,-983.8889771,2391.3769531,40.0000000,0.0000000,180.0000000); //object(cj_police_counter2) (1)
	CreateDynamicObject(2008,430.6140137,-983.4819946,2388.0739746,0.0000000,0.0000000,180.0000000); //object(officedesk1) (1)
	CreateDynamicObject(2165,426.4339905,-982.4840088,2388.0739746,0.0000000,0.0000000,270.0000000); //object(med_office_desk_1) (1)
	CreateDynamicObject(2310,425.0809937,-982.8959961,2388.5729980,0.0000000,0.0000000,210.0000000); //object(mike_din_chair) (1)
	CreateDynamicObject(2310,430.4159851,-982.2080078,2388.5729980,0.0000000,0.0000000,49.9981689); //object(mike_din_chair) (2)
	CreateDynamicObject(2270,425.0280151,-978.5360107,2389.7939453,0.0000000,0.0000000,75.5000000); //object(frame_wood_6) (1)
	CreateDynamicObject(2238,425.6260071,-978.0339966,2388.4819336,0.0000000,0.0000000,0.0000000); //object(cj_lava_lamp) (1)
	CreateDynamicObject(2105,427.2179871,-995.6480103,2389.0229492,0.0000000,0.0000000,0.0000000); //object(cj_mlight14) (1)
	CreateDynamicObject(948,436.5710144,-997.2369995,2388.0739746,0.0000000,0.0000000,0.0000000); //object(plant_pot_10) (1)
	CreateDynamicObject(2001,424.8840027,-998.1359863,2388.0739746,0.0000000,0.0000000,0.0000000); //object(nu_plant_ofc) (1)
	CreateDynamicObject(2011,433.9809875,-983.7890015,2388.0739746,0.0000000,0.0000000,0.0000000); //object(nu_plant2_ofc) (1)
	CreateDynamicObject(1172,431.2330017,-983.7329712,2388.6950684,0.0000000,0.0000000,180.0000000); //object(fbmp_c_l) (1)
	CreateDynamicObject(1115,430.2269897,-984.2680054,2388.6000977,0.0000000,0.0000000,180.0000000); //object(fbb_lr_slv1) (1)
	CreateDynamicObject(1111,430.2409973,-984.5670166,2389.1499023,0.0000000,0.0000000,180.0000000); //object(bnt_lr_slv1) (1)
	CreateDynamicObject(1079,426.4590149,-984.2890015,2390.4140625,0.0000000,0.0000000,270.0000000); //object(wheel_sr1) (1)
	CreateDynamicObject(2310,436.3500061,-987.3430176,2388.5729980,0.0000000,0.0000000,51.9982910); //object(mike_din_chair) (3)
	CreateDynamicObject(1536,437.2714844,-992.3242188,2388.0739746,0.0000000,0.0000000,270.0000000); //object(gen_doorext15) (1)
	CreateDynamicObject(2816,427.2919922,-995.2689819,2388.5739746,0.0000000,0.0000000,0.0000000); //object(gb_bedmags01) (1)
	CreateDynamicObject(2311,435.2999878,-988.2890015,2388.0739746,0.0000000,0.0000000,266.0000000); //object(cj_tv_table2) (1)
	CreateDynamicObject(2310,436.4179993,-990.7930298,2388.5729980,0.0000000,0.0000000,320.4982910); //object(mike_din_chair) (3)
	CreateDynamicObject(2001,436.9540100,-989.4409790,2388.0739746,0.0000000,0.0000000,0.0000000); //object(nu_plant_ofc) (2)
	CreateDynamicObject(2071,430.1629944,-998.6030273,2389.5891113,0.0000000,0.0000000,222.0000000); //object(cj_mlight5) (1)
	CreateDynamicObject(2259,436.7770081,-988.2540283,2390.1440430,0.0000000,0.0000000,270.0000000); //object(frame_clip_6) (1)
	CreateDynamicObject(2140,436.0299988,-985.0520020,2388.0739746,0.0000000,0.0000000,300.0000000); //object(cj_k3_tall_unit1) (1)
	CreateDynamicObject(2509,426.4270020,-984.2639771,2390.4008789,0.0000000,0.0000000,0.0000000); //object(cj_hobby_shelf_6) (1)
	CreateDynamicObject(2099,433.0849915,-998.2369995,2388.0739746,0.0000000,0.0000000,194.0000000); //object(med_hi_fi_1) (1)
	CreateDynamicObject(2818,430.2489929,-989.8969727,2388.0739746,0.0000000,0.0000000,0.0000000); //object(gb_bedrug02) (1)
	CreateDynamicObject(2818,428.2720032,-989.9069824,2388.0739746,0.0000000,0.0000000,0.0000000); //object(gb_bedrug02) (2)
	CreateDynamicObject(2818,430.2539978,-991.0120239,2388.0739746,0.0000000,0.0000000,0.0000000); //object(gb_bedrug02) (3)
	CreateDynamicObject(2818,428.2780151,-991.0209961,2388.0739746,0.0000000,0.0000000,0.0000000); //object(gb_bedrug02) (4)
	CreateDynamicObject(19462,471.5126953,-939.3886719,2380.6000977,0.0000000,90.0000000,90.0000000); //object(wall102) (1)
	CreateDynamicObject(19462,471.5150146,-942.8660278,2380.6000977,0.0000000,90.0000000,90.0000000); //object(wall102) (2)
	CreateDynamicObject(19462,471.5159912,-946.3649902,2380.6000977,0.0000000,90.0000000,90.0000000); //object(wall102) (3)
	CreateDynamicObject(19462,461.8880005,-946.3740234,2380.6000977,0.0000000,90.0000000,90.0000000); //object(wall102) (4)
	CreateDynamicObject(19462,461.8810120,-942.8779907,2380.6000977,0.0000000,90.0000000,90.0000000); //object(wall102) (5)
	CreateDynamicObject(19462,461.8810120,-939.3889771,2380.6000977,0.0000000,90.0000000,90.0000000); //object(wall102) (6)
	CreateDynamicObject(19462,471.5156250,-935.8886719,2380.6000977,0.0000000,90.0000000,90.0000000); //object(wall102) (7)
	CreateDynamicObject(19462,461.8808594,-935.8994141,2380.6000977,0.0000000,90.0000000,90.0000000); //object(wall102) (8)
	CreateDynamicObject(13649,465.7359924,-941.8449707,2380.2849121,0.0000000,0.0000000,0.0000000); //object(ramplandpad01) (2)
	CreateDynamicObject(19454,457.1359863,-943.3029785,2382.4360352,0.0000000,0.0000000,0.0000000); //object(wall094) (1)
	CreateDynamicObject(19454,461.9230042,-948.0100098,2382.4360352,0.0000000,0.0000000,270.0000000); //object(wall094) (2)
	CreateDynamicObject(19454,457.0929871,-933.7119751,2382.4360352,0.0000000,0.0000000,0.5000000); //object(wall094) (3)
	CreateDynamicObject(19454,471.3989868,-948.0499878,2382.4360352,0.0000000,0.0000000,269.5000000); //object(wall094) (4)
	CreateDynamicObject(19454,474.4689941,-943.2290039,2382.4360352,0.0000000,0.0000000,1.4946289); //object(wall094) (5)
	CreateDynamicObject(19462,461.8880005,-932.4409790,2380.6000977,0.0000000,90.0000000,90.0000000); //object(wall102) (8)
	CreateDynamicObject(19462,471.5169983,-932.4349976,2380.6000977,0.0000000,90.0000000,90.0000000); //object(wall102) (8)
	CreateDynamicObject(19454,474.2359924,-933.6690063,2382.4360352,0.0000000,0.0000000,1.4941406); //object(wall094) (6)
	CreateDynamicObject(19462,471.5270081,-928.9359741,2380.6000977,0.0000000,90.0000000,90.0000000); //object(wall102) (8)
	CreateDynamicObject(19462,461.9159851,-928.9420166,2380.6000977,0.0000000,90.0000000,90.0000000); //object(wall102) (8)
	CreateDynamicObject(14667,459.1709900,-934.2689819,2382.5080566,0.0000000,0.0000000,0.0000000); //object(int_7_11a41) (1)
	CreateDynamicObject(19449,458.9129944,-943.3179932,2384.1999512,0.0000000,90.0000000,0.0000000); //object(wall089) (1)
	CreateDynamicObject(19449,462.3890076,-943.3530273,2384.1999512,0.0000000,90.0000000,0.0000000); //object(wall089) (2)
	CreateDynamicObject(19449,465.8900146,-943.3410034,2384.1999512,0.0000000,90.0000000,0.0000000); //object(wall089) (3)
	CreateDynamicObject(19449,469.3640137,-943.3670044,2384.1999512,0.0000000,90.0000000,0.0000000); //object(wall089) (4)
	CreateDynamicObject(19449,472.8169861,-943.4270020,2384.1999512,0.0000000,90.0000000,0.0000000); //object(wall089) (5)
	CreateDynamicObject(19449,458.9079895,-933.7249756,2384.1999512,0.0000000,90.0000000,0.0000000); //object(wall089) (7)
	CreateDynamicObject(19449,462.4070129,-933.7490234,2384.1999512,0.0000000,90.0000000,0.0000000); //object(wall089) (8)
	CreateDynamicObject(19449,465.8469849,-934.0050049,2384.1999512,0.0000000,90.0000000,0.0000000); //object(wall089) (9)
	CreateDynamicObject(19449,469.3439941,-933.7689819,2384.1999512,0.0000000,90.0000000,0.0000000); //object(wall089) (10)
	CreateDynamicObject(19449,472.8200073,-933.8740234,2384.1999512,0.0000000,90.0000000,0.0000000); //object(wall089) (11)
	//
	CreateDynamicObject(19502,2463.7226562,-1657.5048828,2049.1770020,0.0000000,0.0000000,0.0000000); //object(lvhouse3int) (1)
	CreateDynamicObject(19457,2465.9851074,-1649.0429688,2047.9820557,0.0000000,0.0000000,269.5000000); //object(wall097) (1)
	CreateDynamicObject(19365,2456.8588867,-1650.4090576,2047.9820557,0.0000000,0.0000000,168.5000000); //object(wall013) (2)
	CreateDynamicObject(19457,2456.5139160,-1656.6779785,2047.9820557,0.0000000,0.0000000,179.4946289); //object(wall097) (3)
	CreateDynamicObject(19365,2470.6169434,-1650.6719971,2047.9820557,0.0000000,0.0000000,179.2500000); //object(wall013) (3)
	CreateDynamicObject(19365,2470.5800781,-1653.8699951,2047.9820557,0.0000000,0.0000000,177.2474365); //object(wall013) (4)
	CreateDynamicObject(19365,2469.5148926,-1655.8929443,2047.9820557,0.0000000,0.0000000,125.4974365); //object(wall013) (5)
	CreateDynamicObject(19457,2470.4189453,-1661.5670166,2047.9000244,0.0000000,0.0000000,359.4946289); //object(wall097) (5)
	CreateDynamicObject(19457,2459.0910645,-1661.7779541,2047.9000244,0.0000000,0.0000000,359.7391357); //object(wall097) (6)
	CreateDynamicObject(1498,2456.8789062,-1661.2650146,2046.1999512,0.0000000,0.0000000,0.0000000); //object(gen_doorext03) (2)
	CreateDynamicObject(1492,2463.4450684,-1656.8979492,2046.2320557,0.0000000,0.0000000,0.0000000); //object(gen_doorint02) (2)
	CreateDynamicObject(19365,2466.5520020,-1656.8270264,2047.9820557,0.0000000,0.0000000,89.7434082); //object(wall013) (8)
	CreateDynamicObject(19365,2461.8759766,-1656.8580322,2047.9820557,0.0000000,0.0000000,89.4918213); //object(wall013) (9)
	CreateDynamicObject(19438,2459.4699707,-1656.8330078,2047.9820557,0.0000000,0.0000000,89.2500000); //object(wall078) (1)
	CreateDynamicObject(19365,2458.7370605,-1658.4300537,2047.9820557,0.0000000,0.0000000,179.2391357); //object(wall013) (10)
	CreateDynamicObject(19438,2458.7099609,-1660.8360596,2047.9820557,0.0000000,0.0000000,179.4974365); //object(wall078) (2)
	CreateDynamicObject(2283,2466.7519531,-1649.1590576,2048.4121094,0.0000000,0.0000000,0.0000000); //object(frame_thick_3) (1)
	CreateDynamicObject(19438,2464.2351074,-1656.8640137,2050.3500977,0.0000000,0.0000000,90.5000000); //object(wall078) (3)
	CreateDynamicObject(1417,2470.1298828,-1654.2159424,2046.2819824,0.0000000,0.0000000,267.7500000); //object(dyn_cupboard) (1)
	CreateDynamicObject(1765,2468.6069336,-1651.5150146,2046.2320557,0.0000000,0.0000000,297.0000000); //object(low_single_2) (1)
	CreateDynamicObject(1765,2464.2390137,-1651.7609863,2046.2320557,0.0000000,0.0000000,42.9989014); //object(low_single_2) (2)
	CreateDynamicObject(1814,2466.0310059,-1653.1569824,2046.2320557,0.0000000,0.0000000,348.0000000); //object(coffee_med_1) (1)
	CreateDynamicObject(2102,2466.1689453,-1652.6450195,2046.7390137,0.0000000,0.0000000,206.0000000); //object(low_hi_fi_2) (1)
	CreateDynamicObject(1712,2466.3081055,-1650.6760254,2046.2320557,0.0000000,0.0000000,0.0000000); //object(kb_couch05) (1)
	CreateDynamicObject(1731,2457.6159668,-1661.1440430,2048.9199219,0.0000000,0.0000000,270.0000000); //object(cj_mlight3) (1)
	CreateDynamicObject(14438,2468.9770508,-1656.1650391,2051.3400879,0.0000000,0.0000000,180.0000000); //object(carter-light04) (2)
	CreateDynamicObject(1783,2467.6369629,-1655.9499512,2046.3020020,0.0000000,0.0000000,0.0000000); //object(swank_video_2) (1)
	CreateDynamicObject(1786,2467.7338867,-1656.2189941,2046.3759766,0.0000000,0.0000000,180.0000000); //object(swank_tv_4) (1)
	CreateDynamicObject(1738,2467.5270996,-1649.3530273,2046.8000488,0.0000000,0.0000000,0.0000000); //object(cj_radiator_old) (1)
	CreateDynamicObject(1738,2466.4121094,-1649.3499756,2046.8000488,0.0000000,0.0000000,0.0000000); //object(cj_radiator_old) (2)
	CreateDynamicObject(1951,2467.1630859,-1653.0080566,2046.9270020,0.0000000,0.0000000,0.0000000); //object(kb_beer01) (1)
	CreateDynamicObject(1950,2466.7829590,-1652.8179932,2046.8000488,0.0000000,90.0000000,0.0000000); //object(kb_beer) (1)
	CreateDynamicObject(1665,2467.2050781,-1652.7509766,2046.7490234,0.0000000,0.0000000,0.0000000); //object(propashtray1) (1)
	CreateDynamicObject(1544,2467.5148926,-1652.3879395,2046.2320557,0.0000000,0.0000000,0.0000000); //object(cj_beer_b_1) (1)
	CreateDynamicObject(2816,2467.4619141,-1650.8879395,2046.7430420,0.0000000,0.0000000,0.0000000); //object(gb_bedmags01) (1)
	CreateDynamicObject(2835,2466.6140137,-1652.0729980,2046.2320557,0.0000000,0.0000000,0.0000000); //object(gb_livingrug04) (1)
	CreateDynamicObject(14867,2466.3330078,-1664.0920410,2047.7080078,0.0000000,0.0000000,0.0000000); //object(bobbie-cupboards) (1)
	CreateDynamicObject(19121,2464.4470215,-1654.4160156,2051.0000000,0.0000000,0.0000000,0.0000000); //object(bollardlight1) (1)
	CreateDynamicObject(19121,2457.4379883,-1659.9730225,2051.0000000,0.0000000,0.0000000,0.0000000); //object(bollardlight1) (3)
	CreateDynamicObject(19365,2460.7749023,-1664.4539795,2047.9000244,0.0000000,0.0000000,90.0000000); //object(wall013) (11)
	CreateDynamicObject(3497,2464.2270508,-1656.5939941,2049.2470703,0.0000000,0.0000000,0.0000000); //object(vgsxrefbballnet2) (1)
	CreateDynamicObject(2281,2470.0061035,-1653.2320557,2047.9000244,0.0000000,9.0000000,268.0000000); //object(frame_thick_5) (1)
	CreateDynamicObject(18659,2460.9060059,-1656.7239990,2047.9000244,10.0000000,0.0000000,269.7500000); //object(spraytag1) (1)
	CreateDynamicObject(941,2468.2719727,-1661.6669922,2046.6779785,0.0000000,0.0000000,52.0000000); //object(cj_df_worktop_3) (1)
	CreateDynamicObject(941,2464.8249512,-1662.2550049,2046.6779785,0.0000000,0.0000000,357.7478027); //object(cj_df_worktop_3) (2)
	CreateDynamicObject(937,2462.0720215,-1661.5670166,2046.6800537,0.0000000,0.0000000,320.0000000); //object(cj_df_worktop) (1)
	CreateDynamicObject(18661,2461.2460938,-1656.7180176,2048.0000000,338.0000000,0.0000000,270.0000000); //object(spraytag3) (1)
	CreateDynamicObject(18662,2460.6411133,-1656.7290039,2048.1489258,0.0000000,0.0000000,269.7500000); //object(spraytag4) (1)
	CreateDynamicObject(18663,2461.4450684,-1656.7399902,2048.1489258,10.0000000,0.0000000,269.7473145); //object(spraytag5) (1)
	CreateDynamicObject(2255,2466.7028809,-1656.2629395,2047.4119873,0.0000000,0.0000000,179.5000000); //object(frame_clip_2) (1)
	CreateDynamicObject(2000,2470.2241211,-1649.5030518,2046.2320557,0.0000000,0.0000000,309.5000000); //object(filing_cab_nu) (1)
	CreateDynamicObject(2007,2469.3510742,-1657.7590332,2046.2290039,0.0000000,0.0000000,310.0000000); //object(filing_cab_nu01) (1)
	CreateDynamicObject(2046,2470.1831055,-1659.2900391,2048.0700684,0.0000000,0.0000000,270.0000000); //object(cj_guncupboard) (1)
	CreateDynamicObject(2063,2459.7028809,-1658.9799805,2047.1280518,0.0000000,0.0000000,270.0000000); //object(cj_greenshelves) (1)
	CreateDynamicObject(2129,2467.6630859,-1657.4210205,2046.2320557,0.0000000,0.0000000,0.0000000); //object(cj_k1_low_unit) (1)
	CreateDynamicObject(2160,2465.9790039,-1657.1540527,2046.2340088,0.0000000,0.0000000,0.0000000); //object(cj_k6_low_unit3) (1)
	CreateDynamicObject(19508,2460.3974609,-1642.4199219,2048.4750977,0.0000000,0.0000000,90.0000000); //object(lshouse2int) (1)
	CreateDynamicObject(19438,2457.5549316,-1648.8620605,2047.9820557,0.0000000,0.0000000,89.2474365); //object(wall078) (6)
	CreateDynamicObject(19438,2458.3911133,-1648.1610107,2047.9820557,0.0000000,0.0000000,357.9974365); //object(wall078) (7)
	CreateDynamicObject(19438,2459.6479492,-1648.1689453,2047.9820557,0.0000000,0.0000000,357.9974365); //object(wall078) (8)
	CreateDynamicObject(19438,2460.3779297,-1648.9689941,2047.9820557,0.0000000,0.0000000,267.9949951); //object(wall078) (9)
	CreateDynamicObject(19430,2459.0759277,-1648.1440430,2046.1400146,0.0000000,90.0000000,0.0000000); //object(wall070) (2)
	CreateDynamicObject(19430,2459.0751953,-1648.1400146,2049.3200684,0.0000000,90.0000000,0.0000000); //object(wall070) (3)
	CreateDynamicObject(19453,2464.4260254,-1647.4069824,2047.9830322,0.0000000,0.0000000,90.0000000); //object(wall093) (1)
	CreateDynamicObject(19453,2465.4760742,-1643.0290527,2047.9830322,0.0000000,0.0000000,0.0000000); //object(wall093) (2)
	CreateDynamicObject(19453,2460.6850586,-1638.4110107,2047.9830322,0.0000000,0.0000000,270.0000000); //object(wall093) (3)
	CreateDynamicObject(19453,2455.7199707,-1642.9189453,2047.9830322,0.0000000,0.0000000,178.0000000); //object(wall093) (4)
	CreateDynamicObject(19361,2456.9140625,-1647.3840332,2047.9830322,0.0000000,0.0000000,90.0000000); //object(wall009) (1)
	CreateDynamicObject(19434,2459.0449219,-1647.4100342,2050.1420898,179.9945068,0.0000000,90.0000000); //object(wall074) (1)
	CreateDynamicObject(14892,2436.7250977,-1637.9670410,2046.4000244,0.0000000,0.0000000,180.0000000); //object(mp_sfpd_win2) (1)
	CreateDynamicObject(16637,2398.3210449,-1597.6650391,2028.6419678,0.0000000,0.0000000,0.0000000); //object(ghostgardoor) (2)
	CreateDynamicObject(14892,2455.8491211,-1683.5150146,2046.4000244,0.0000000,0.0000000,269.4945068); //object(mp_sfpd_win2) (2)
	CreateDynamicObject(14438,2468.1140137,-1642.5739746,2051.3400879,0.0000000,0.0000000,179.9945068); //object(carter-light04) (3)
	CreateDynamicObject(19121,2460.9750977,-1642.9580078,2050.0000000,0.0000000,0.0000000,0.0000000); //object(bollardlight1) (6)
	CreateDynamicObject(1742,2464.8320312,-1647.4530029,2046.2330322,0.0000000,0.0000000,181.0000000); //object(med_bookshelf) (1)
	CreateDynamicObject(1743,2463.1120605,-1646.1490479,2046.1999512,0.0000000,0.0000000,180.0000000); //object(med_cabinet_3) (1)
	CreateDynamicObject(2025,2456.3378906,-1646.9969482,2046.3029785,0.0000000,0.0000000,126.2500000); //object(mrk_wrobe_tmp) (1)
	CreateDynamicObject(1796,2461.8659668,-1645.4899902,2046.2330322,0.0000000,0.0000000,270.0000000); //object(low_bed_4) (1)
	CreateDynamicObject(1796,2461.8300781,-1642.9820557,2046.2330322,0.0000000,0.0000000,270.0000000); //object(low_bed_4) (2)
	CreateDynamicObject(1796,2461.8740234,-1640.1009521,2046.2330322,0.0000000,0.0000000,270.0000000); //object(low_bed_4) (3)
	CreateDynamicObject(2100,2460.0839844,-1638.7679443,2046.2330322,0.0000000,0.0000000,0.0000000); //object(med_hi_fi_2) (1)
	CreateDynamicObject(2130,2456.3510742,-1641.4139404,2046.2399902,0.0000000,0.0000000,88.7500000); //object(cj_k1_sink) (1)
	CreateDynamicObject(2131,2455.7810059,-1644.7480469,2046.2399902,0.0000000,0.0000000,90.0000000); //object(cj_kitch2_fridge) (1)
	CreateDynamicObject(2135,2456.2910156,-1642.5639648,2046.2330322,0.0000000,0.0000000,88.0000000); //object(cj_k3_cooker) (1)
	CreateDynamicObject(2147,2456.4108887,-1639.1989746,2046.2399902,0.0000000,0.0000000,88.0000000); //object(cj_kitch1_fridge) (1)
	CreateDynamicObject(2596,2456.1870117,-1643.6359863,2049.0000000,25.0000000,0.0000000,87.7500000); //object(cj_sex_tv) (1)
	CreateDynamicObject(2833,2459.3679199,-1643.0909424,2046.2330322,0.0000000,0.0000000,0.0000000); //object(gb_livingrug02) (1)
	CreateDynamicObject(1594,2459.9660645,-1642.5400391,2046.7099609,0.0000000,0.0000000,334.0000000); //object(chairsntable) (1)
	CreateDynamicObject(2850,2459.9040527,-1642.6949463,2047.1879883,0.0000000,0.0000000,50.0000000); //object(gb_kitchdirt04) (1)
	CreateDynamicObject(2852,2463.1379395,-1641.4909668,2046.2330322,0.0000000,0.0000000,0.0000000); //object(gb_bedmags02) (1)
	CreateDynamicObject(2853,2462.4960938,-1639.5410156,2046.2330322,0.0000000,0.0000000,0.0000000); //object(gb_bedmags03) (1)
	CreateDynamicObject(2855,2464.0061035,-1643.1689453,2046.8809814,0.0000000,0.0000000,0.0000000); //object(gb_bedmags05) (1)
	CreateDynamicObject(2863,2456.2519531,-1641.2860107,2047.2900391,0.0000000,0.0000000,0.0000000); //object(gb_kitchplatecln03) (1)
	CreateDynamicObject(2226,2462.6088867,-1647.0419922,2047.1999512,0.0000000,0.0000000,190.0000000); //object(low_hi_fi_3) (1)
	CreateDynamicObject(1738,2465.3420410,-1641.5720215,2046.6999512,0.0000000,0.0000000,270.0000000); //object(cj_radiator_old) (3)
	CreateDynamicObject(1738,2465.3220215,-1644.2960205,2046.6999512,0.0000000,0.0000000,270.0000000); //object(cj_radiator_old) (4)
	CreateDynamicObject(2257,2465.3740234,-1642.8929443,2047.5000000,0.0000000,20.0000000,270.0000000); //object(frame_clip_4) (1)
	CreateDynamicObject(3119,2466.4460449,-1654.3800049,2046.5360107,0.0000000,0.0000000,0.0000000); //object(cs_ry_props) (1)
	CreateDynamicObject(2670,2461.3068848,-1644.7879639,2046.3249512,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_1) (1)
	CreateDynamicObject(2671,2462.6169434,-1653.3850098,2046.2320557,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_3) (1)
	CreateDynamicObject(2673,2463.0859375,-1650.9670410,2046.3199463,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_5) (1)
	CreateDynamicObject(2674,2466.7980957,-1651.6999512,2046.2530518,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_2) (1)
	CreateDynamicObject(3014,2467.9279785,-1660.1779785,2046.4479980,0.0000000,0.0000000,86.0000000); //object(cr_guncrate) (1)
	CreateDynamicObject(3014,2468.2700195,-1659.2740479,2046.4479980,0.0000000,0.0000000,135.9954834); //object(cr_guncrate) (2)
	CreateDynamicObject(3014,2469.1120605,-1660.0539551,2046.4479980,0.0000000,0.0000000,45.9942627); //object(cr_guncrate) (3)
	CreateDynamicObject(349,2468.0900879,-1661.5129395,2047.1999512,90.0000000,0.0000000,89.0000000); //object(1)
	CreateDynamicObject(348,2468.3840332,-1660.8430176,2047.1999512,90.0000000,0.0000000,0.7500000); //object(2)
	CreateDynamicObject(344,2467.8200684,-1662.2209473,2047.4040527,0.0000000,0.0000000,0.0000000); //object(3)
	CreateDynamicObject(1575,2466.0729980,-1662.4599609,2047.2740479,0.0000000,0.0000000,0.0000000); //object(drug_white) (1)
	CreateDynamicObject(1575,2465.1120605,-1661.9270020,2047.2740479,0.0000000,0.0000000,320.0000000); //object(drug_white) (2)
	CreateDynamicObject(1575,2465.2600098,-1662.5009766,2047.2740479,0.0000000,0.0000000,32.9987793); //object(drug_white) (3)
	CreateDynamicObject(1575,2464.5810547,-1661.9110107,2047.2740479,0.0000000,0.0000000,329.9957275); //object(drug_white) (4)
	CreateDynamicObject(1575,2465.7758789,-1662.0069580,2047.2740479,0.0000000,0.0000000,29.9908447); //object(drug_white) (5)
	CreateDynamicObject(1575,2468.0839844,-1661.6960449,2047.0500488,0.0000000,0.0000000,32.9974365); //object(drug_white) (6)
	CreateDynamicObject(1550,2462.1721191,-1661.5670166,2047.5489502,0.0000000,0.0000000,0.0000000); //object(cj_money_bag) (1)
	CreateDynamicObject(2674,2462.6750488,-1659.2750244,2046.2380371,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_2) (2)
	CreateDynamicObject(2670,2465.4951172,-1659.0729980,2046.3100586,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_1) (2)
	CreateDynamicObject(1764,2457.2690430,-1651.5849609,2046.2320557,0.0000000,0.0000000,79.2500000); //object(low_couch_2) (1)
	CreateDynamicObject(1815,2456.9799805,-1653.2619629,2046.2320557,0.0000000,0.0000000,0.0000000); //object(coffee_low_2) (1)
	CreateDynamicObject(1747,2457.5380859,-1653.3249512,2046.7290039,0.0000000,0.0000000,200.0000000); //object(low_tv_2) (1)
	// =========== Taxi
	CreateDynamicObject(19462,851.0230103,-1662.2110596,12.5000000,0.0000000,90.0000000,0.0000000); //object(wall102) (1)
	CreateDynamicObject(19462,847.5300293,-1662.2120361,12.5000000,0.0000000,90.0000000,0.0000000); //object(wall102) (2)
	CreateDynamicObject(19462,851.0224609,-1652.5791016,12.5000000,0.0000000,90.0000000,0.0000000); //object(wall102) (3)
	CreateDynamicObject(19462,847.5300293,-1652.5870361,12.5000000,0.0000000,90.0000000,0.0000000); //object(wall102) (4)
	CreateDynamicObject(19462,844.0300293,-1662.2120361,12.5000000,0.0000000,90.0000000,0.0000000); //object(wall102) (5)
	CreateDynamicObject(19462,844.0300293,-1652.5870361,12.5000000,0.0000000,90.0000000,0.0000000); //object(wall102) (6)
	CreateDynamicObject(1536,853.1929932,-1656.6529541,12.5550003,0.0000000,0.0000000,90.0000000); //object(gen_doorext15) (1)
	CreateDynamicObject(19450,852.6259766,-1662.2099609,11.8999996,180.0000000,0.0000000,0.0000000); //object(wall090) (1)
	CreateDynamicObject(19450,852.6259766,-1652.6059570,11.8999996,180.0000000,0.0000000,0.0000000); //object(wall090) (2)
	CreateDynamicObject(19358,852.6400146,-1655.9709473,14.0000000,0.0000000,0.0000000,0.0000000); //object(wall006) (1)
	CreateDynamicObject(1536,852.5670166,-1655.1789551,12.5550003,0.0000000,0.0000000,270.0000000); //object(gen_doorext15) (2)
	CreateDynamicObject(19431,852.6400146,-1658.3790283,14.0000000,0.0000000,0.0000000,0.0000000); //object(wall071) (1)
	CreateDynamicObject(19431,852.6400146,-1653.5610352,14.0000000,0.0000000,0.0000000,0.0000000); //object(wall071) (2)
	CreateDynamicObject(1649,852.6400146,-1660.2609863,15.0000000,0.0000000,0.0000000,269.7500000); //object(wglasssmash) (1)
	CreateDynamicObject(1649,852.6220093,-1664.6779785,15.0000000,0.0000000,0.0000000,269.7473145); //object(wglasssmash) (2)
	CreateDynamicObject(19450,848.1708984,-1666.5869141,13.8999996,0.0000000,0.0000000,90.0000000); //object(wall090) (3)
	CreateDynamicObject(19450,847.9492188,-1648.5068359,13.8999996,0.0000000,0.0000000,90.7470703); //object(wall090) (4)
	CreateDynamicObject(1649,852.5780029,-1652.6569824,15.0000000,0.0000000,0.0000000,269.7473145); //object(wglasssmash) (3)
	CreateDynamicObject(1649,852.6099854,-1648.3000488,15.0000000,0.0000000,0.0000000,269.4973145); //object(wglasssmash) (4)
	CreateDynamicObject(19450,843.9290161,-1662.0839844,13.8999996,0.0000000,0.0000000,8.0000000); //object(wall090) (5)
	CreateDynamicObject(19450,843.9379883,-1652.5839844,13.8999996,0.0000000,0.0000000,351.9980469); //object(wall090) (6)
	CreateDynamicObject(19454,851.1090088,-1663.0179443,15.7200003,0.0000000,90.0000000,0.0000000); //object(wall094) (1)
	CreateDynamicObject(19454,847.6099854,-1663.0179443,15.7200003,0.0000000,90.0000000,0.0000000); //object(wall094) (2)
	CreateDynamicObject(19454,844.1199951,-1663.0179443,15.7200003,0.0000000,90.0000000,0.0000000); //object(wall094) (3)
	CreateDynamicObject(19454,844.6480103,-1653.3879395,15.7200003,0.0000000,90.0000000,0.0000000); //object(wall094) (4)
	CreateDynamicObject(19454,848.1400146,-1653.3879395,15.7200003,0.0000000,90.0000000,0.0000000); //object(wall094) (5)
	CreateDynamicObject(19454,851.6396484,-1653.3876953,15.7200003,0.0000000,90.0000000,0.0000000); //object(wall094) (6)
	CreateDynamicObject(3920,853.0989990,-1659.8360596,15.0979996,0.0000000,0.0000000,270.0000000); //object(lib_veg3) (2)
	CreateDynamicObject(3920,853.1040039,-1648.2290039,15.0979996,0.0000000,0.0000000,270.0000000); //object(lib_veg3) (3)
	CreateDynamicObject(983,855.9060059,-1670.9470215,13.2379999,0.0000000,0.0000000,300.0000000); //object(fenceshit3) (1)
	CreateDynamicObject(983,855.8640137,-1658.2779541,13.2379999,0.0000000,0.0000000,239.9981689); //object(fenceshit3) (2)
	CreateDynamicObject(983,858.8079834,-1664.6159668,13.2379999,0.0000000,0.0000000,179.9963379); //object(fenceshit3) (3)
	CreateDynamicObject(1364,859.8790283,-1664.7850342,13.3389997,0.0000000,0.0000000,90.0000000); //object(cj_bush_prop) (1)
	CreateDynamicObject(983,855.8439941,-1641.0749512,13.2379999,0.0000000,0.0000000,239.9963379); //object(fenceshit3) (4)
	CreateDynamicObject(983,855.9060059,-1653.4449463,13.2379999,0.0000000,0.0000000,299.9981689); //object(fenceshit3) (5)
	CreateDynamicObject(983,858.6560059,-1647.2340088,13.2379999,0.0000000,0.0000000,179.9945068); //object(fenceshit3) (6)
	CreateDynamicObject(1364,859.6459961,-1647.2280273,13.3389997,0.0000000,0.0000000,90.0000000); //object(cj_bush_prop) (2)
	CreateDynamicObject(2254,852.5059814,-1653.9379883,14.6400003,0.0000000,0.0000000,270.0000000); //object(frame_clip_1) (1)
	CreateDynamicObject(14438,848.4080200,-1657.8549805,17.7900009,0.0000000,0.0000000,90.0000000); //object(carter-light04) (1)
	CreateDynamicObject(19121,849.3469849,-1666.6400146,18.0000000,0.0000000,0.0000000,0.0000000); //object(bollardlight1) (6)
	CreateDynamicObject(19121,840.6640015,-1665.6789551,18.0000000,0.0000000,0.0000000,0.0000000); //object(bollardlight1) (9)
	CreateDynamicObject(19121,850.1270142,-1651.8680420,18.0000000,0.0000000,0.0000000,0.0000000); //object(bollardlight1) (10)
	CreateDynamicObject(19121,842.7969971,-1650.8769531,18.0000000,0.0000000,0.0000000,0.0000000); //object(bollardlight1) (11)
	CreateDynamicObject(2240,845.1840210,-1649.4670410,13.1840000,0.0000000,0.0000000,0.0000000); //object(plant_pot_8) (1)
	CreateDynamicObject(2241,851.9630127,-1649.3680420,13.0900002,0.0000000,0.0000000,0.0000000); //object(plant_pot_5) (1)
	CreateDynamicObject(2289,850.6320190,-1666.4510498,14.5279999,0.0000000,0.0000000,180.0000000); //object(frame_2) (1)
	CreateDynamicObject(2290,847.5349731,-1649.4799805,12.5860004,0.0000000,0.0000000,0.0000000); //object(swk_couch_1) (1)
	CreateDynamicObject(2119,848.2470093,-1652.1810303,12.5860004,0.0000000,0.0000000,30.0000000); //object(med_dinning_6) (2)
	CreateDynamicObject(1754,846.1069946,-1651.5389404,12.5860004,0.0000000,0.0000000,62.0000000); //object(swank_single_1) (1)
	CreateDynamicObject(1754,851.6040039,-1652.0190430,12.5860004,0.0000000,0.0000000,247.9958496); //object(swank_single_1) (2)
	CreateDynamicObject(2164,844.1190186,-1662.8220215,12.6000004,0.0000000,0.0000000,97.7500000); //object(med_office_unit_5) (1)
	CreateDynamicObject(2608,851.7239990,-1665.5889893,13.2969999,0.0000000,0.0000000,230.2500000); //object(polce_shelf) (1)
	CreateDynamicObject(2609,845.0130005,-1666.1130371,13.3179998,0.0000000,0.0000000,136.0000000); //object(cj_p_fileing1) (1)
	CreateDynamicObject(2737,847.6500244,-1666.4429932,13.9809999,0.0000000,0.0000000,180.0000000); //object(police_nb_car) (1)
	CreateDynamicObject(2285,844.8579712,-1664.5770264,14.5349998,0.0000000,0.0000000,98.0000000); //object(frame_1) (1)
	CreateDynamicObject(1714,846.9439697,-1662.9300537,12.5860004,0.0000000,0.0000000,170.0000000); //object(kb_swivelchair1) (1)
	CreateDynamicObject(1722,844.1510010,-1660.2349854,12.5860004,0.0000000,0.0000000,278.0000000); //object(off_chairnu) (1)
	CreateDynamicObject(1722,844.0629883,-1659.4659424,12.5860004,0.0000000,0.0000000,277.9980469); //object(off_chairnu) (2)
	CreateDynamicObject(2008,846.0419922,-1661.7979736,12.5860004,0.0000000,0.0000000,0.0000000); //object(officedesk1) (1)
	CreateDynamicObject(2009,850.2379761,-1662.5400391,12.5860004,0.0000000,0.0000000,270.0000000); //object(officedesk2l) (1)
	CreateDynamicObject(1806,850.5289917,-1663.7519531,12.5860004,0.0000000,0.0000000,342.0000000); //object(med_office_chair) (1)
	CreateDynamicObject(1811,851.2420044,-1661.4849854,13.2119999,0.0000000,0.0000000,0.0000000); //object(med_din_chair_5) (1)
	CreateDynamicObject(1808,852.2769775,-1657.7869873,12.5860004,0.0000000,0.0000000,270.0000000); //object(cj_watercooler2) (1)
	CreateDynamicObject(2099,844.0150146,-1657.3800049,12.5860004,0.0000000,0.0000000,70.0000000); //object(med_hi_fi_1) (1)
	CreateDynamicObject(2202,847.9609985,-1665.6450195,12.5860004,0.0000000,0.0000000,180.0000000); //object(photocopier_2) (1)
	CreateDynamicObject(2596,849.1939697,-1666.2020264,15.2539997,20.0000000,0.0000000,186.0000000); //object(cj_sex_tv) (1)
	CreateDynamicObject(2813,847.7650146,-1649.5620117,13.0939999,0.0000000,0.0000000,0.0000000); //object(gb_novels01) (1)
	CreateDynamicObject(2816,848.2440186,-1652.1679688,13.3809996,0.0000000,0.0000000,0.0000000); //object(gb_bedmags01) (1)
	CreateDynamicObject(2827,846.2890015,-1661.7170410,13.3990002,0.0000000,0.0000000,0.0000000); //object(gb_novels05) (1)
	CreateDynamicObject(948,849.5079956,-1665.8420410,12.5860004,0.0000000,0.0000000,0.0000000); //object(plant_pot_10) (1)
	CreateDynamicObject(2247,850.9160156,-1662.3220215,13.8629999,0.0000000,0.0000000,0.0000000); //object(plant_pot_15) (1)
	CreateDynamicObject(3439,856.1810303,-1664.3929443,16.6679993,0.0000000,0.0000000,0.0000000); //object(aprtree01_lvs) (1)
	CreateDynamicObject(3439,856.1829834,-1647.1939697,16.6679993,0.0000000,0.0000000,0.0000000); //object(aprtree01_lvs) (2)
	CreateDynamicObject(2835,850.9869995,-1656.4200439,12.5860004,0.0000000,0.0000000,90.0000000); //object(gb_livingrug04) (1)
	CreateDynamicObject(1738,844.5200195,-1652.4310303,13.2410002,0.0000000,0.0000000,80.2500000); //object(cj_radiator_old) (1)
	CreateDynamicObject(1738,844.3020020,-1653.5190430,13.2410002,0.0000000,0.0000000,76.2451172); //object(cj_radiator_old) (2)
	//===== Resp and Mail ====
	CreateDynamicObject(982,1189.8959961,-1769.8249512,13.2620001,0.0000000,0.0000000,0.0000000); //object(fenceshit) (1)
	CreateDynamicObject(982,1189.8730469,-1742.4890137,13.2620001,0.0000000,0.0000000,0.0000000); //object(fenceshit) (2)
	CreateDynamicObject(983,1189.8730469,-1726.4870605,13.2399998,0.0000000,0.0000000,0.0000000); //object(fenceshit3) (2)
	CreateDynamicObject(982,1202.7650146,-1722.1760254,13.2620001,0.0000000,0.0000000,270.0000000); //object(fenceshit) (3)
	CreateDynamicObject(983,1218.7270508,-1722.1750488,13.2410002,0.0000000,0.0000000,270.0000000); //object(fenceshit3) (3)
	CreateDynamicObject(984,1234.6049805,-1722.2939453,13.1920004,0.0000000,0.0000000,270.0000000); //object(fenceshit2) (3)
	CreateDynamicObject(983,1244.1910400,-1722.3000488,13.2410002,0.0000000,0.0000000,270.0000000); //object(fenceshit3) (4)
	CreateDynamicObject(982,1247.3940430,-1735.0880127,13.2620001,0.0000000,0.0000000,0.0000000); //object(fenceshit) (6)
	CreateDynamicObject(982,1207.5429688,-1734.9689941,13.2620001,0.0000000,0.0000000,0.0000000); //object(fenceshit) (7)
	CreateDynamicObject(984,1215.5229492,-1747.7519531,13.1920004,0.0000000,0.0000000,270.0000000); //object(fenceshit2) (6)
	CreateDynamicObject(1360,1210.3129883,-1749.4549561,13.3660002,0.0000000,0.0000000,36.0000000); //object(cj_bush_prop3) (1)
	CreateDynamicObject(1364,1206.4389648,-1743.3809814,13.3769999,0.0000000,0.0000000,270.0000000); //object(cj_bush_prop) (1)
	CreateDynamicObject(1361,1206.3830566,-1727.8229980,13.3109999,0.0000000,0.0000000,0.0000000); //object(cj_bush_prop2) (1)
	CreateDynamicObject(955,1203.8559570,-1762.4399414,12.7799997,0.0000000,0.0000000,252.0000000); //object(cj_ext_sprunk) (1)
	CreateDynamicObject(1257,1187.4439697,-1751.8349609,13.8500004,0.0000000,0.0000000,0.0000000); //object(bustopm) (1)
	CreateDynamicObject(1340,1198.9079590,-1732.9139404,13.7010002,0.0000000,0.0000000,90.0000000); //object(chillidogcart) (1)
	CreateDynamicObject(1341,1201.2600098,-1732.7259521,13.5749998,0.0000000,0.0000000,270.2500000); //object(icescart_prop) (1)
	CreateDynamicObject(1342,1196.3769531,-1732.9809570,13.6070004,0.0000000,0.0000000,270.0000000); //object(noodlecart_prop) (1)
	CreateDynamicObject(3861,1205.3399658,-1732.5340576,13.7419996,0.0000000,0.0000000,0.0000000); //object(marketstall01_sfxrf) (1)
	CreateDynamicObject(1372,1200.9510498,-1727.8320312,12.5679998,0.0000000,0.0000000,0.0000000); //object(cj_dump2_low) (1)
	CreateDynamicObject(1338,1199.2590332,-1727.8800049,13.2790003,0.0000000,0.0000000,0.0000000); //object(binnt08_la) (1)
	CreateDynamicObject(1299,1202.7480469,-1728.3179932,13.0240002,0.0000000,0.0000000,22.0000000); //object(smashboxpile) (1)
	CreateDynamicObject(1280,1195.2380371,-1737.7769775,12.9790001,0.0000000,0.0000000,180.0000000); //object(parkbench1) (1)
	CreateDynamicObject(1280,1195.1330566,-1741.0689697,12.9790001,0.0000000,0.0000000,149.9945068); //object(parkbench1) (2)
	CreateDynamicObject(1280,1192.0429688,-1742.0770264,12.9790001,0.0000000,0.0000000,89.9908447); //object(parkbench1) (3)
	CreateDynamicObject(1536,1304.9699707,-1867.5560303,12.5469999,0.0000000,0.0000000,270.0000000); //object(gen_doorext15) (1)
	CreateDynamicObject(18001,1304.9339600,-1874.0229492,14.2709999,0.0000000,0.0000000,270.0000000); //object(int_barbera07) (1)
	//==== Gang Farm ====
	CreateDynamicObject(1498, 1944.0739746094, -1561.5059814453, 12.619999885559, 0, 0, 45.25); // Объект 0
	CreateDynamicObject(820, 2458.1369628906, -1715.0329589844, 12.534000396729, 0, 0, 320); // Объект 1
	CreateDynamicObject(820, 2461.2099609375, -1714.4260253906, 12.534000396729, 0, 0, 59.998779296875); // Объект 2
	CreateDynamicObject(820, 1893.1839599609, -1993.3100585938, 12.546999931335, 0, 0, 0); // Объект 3
	CreateDynamicObject(820, 1889.3480224609, -1993.5570068359, 12.546999931335, 0, 0, 106); // Объект 4
	CreateDynamicObject(820, 1931.958984375, -1545.6469726563, 12.640999794006, 0, 0, 280); // Объект 5
	CreateDynamicObject(820, 1927.8260498047, -1547.4239501953, 12.640999794006, 0, 0, 109.99755859375); // Объект 6
	CreateDynamicObject(820, 2814.6708984375, -1210.0520019531, 24.208000183105, 0, 0, 0); // Объект 7
	CreateDynamicObject(820, 2818.5161132813, -1211.9720458984, 24.208000183105, 0, 0, 160); // Объект 8
	CreateDynamicObject(820, 2009.4090576172, -1120.501953125, 25.42200088501, 0, 0, 0); // Объект 9
	//====== Shahta ===
	CreateDynamicObject(16337,-1098.7010498,-1630.9799805,75.3669968,0.0000000,0.0000000,180.0000000); //object(des_cranecontrol) (2)
	CreateDynamicObject(929,-1118.7550049,-1622.7889404,76.3349991,0.0000000,0.0000000,0.0000000); //object(generator) (1)
	CreateDynamicObject(943,-1118.8079834,-1619.3740234,76.1399994,0.0000000,0.0000000,0.0000000); //object(generator_low) (1)
	CreateDynamicObject(1635,-1120.3830566,-1621.4300537,78.5530014,0.0000000,0.0000000,180.0000000); //object(nt_aircon1dbl) (1)
	CreateDynamicObject(6930,-1058.0290527,-1622.9289551,82.5999985,0.0000000,0.0000000,270.0000000); //object(vegasplant05) (1)
	CreateDynamicObject(901,-1111.3649902,-1656.1369629,73.0000000,0.0000000,0.0000000,60.0000000); //object(searock05) (1)
	CreateDynamicObject(901,-1118.4139404,-1658.4189453,73.0000000,1.0000000,21.0000000,83.9963379); //object(searock05) (2)
	CreateDynamicObject(906,-1116.2449951,-1653.4570312,75.0000000,0.0000000,0.0000000,260.0000000); //object(p_rubblebig) (1)
	CreateDynamicObject(899,-1115.0169678,-1674.5429688,77.0000000,0.0000000,0.0000000,0.0000000); //object(searock03) (1)
	CreateDynamicObject(900,-1096.7609863,-1667.2189941,77.0000000,0.0000000,0.0000000,12.0000000); //object(searock04) (1)
	CreateDynamicObject(896,-1112.3909912,-1625.0340576,68.9000015,0.0000000,1.0000000,30.0000000); //object(searock06) (1)
	CreateDynamicObject(896,-1110.4549561,-1616.8590088,68.9000015,0.0000000,0.9997559,219.9981689); //object(searock06) (2)
	CreateDynamicObject(1257,-1054.1020508,-1642.1889648,77.7229996,0.0000000,0.0000000,80.0000000); //object(bustopm) (2)
	CreateDynamicObject(1257,-1056.2290039,-1658.3790283,77.7229996,0.0000000,0.0000000,259.9969482); //object(bustopm) (3)
	CreateDynamicObject(18728,-1118.8470459,-1622.8489990,75.5000000,0.0000000,0.0000000,0.0000000); //object(smoke_flare) (1)
	CreateDynamicObject(18671,-1065.6070557,-1618.2819824,90.7829971,0.0000000,0.0000000,0.0000000); //object(carwashspray) (1)
	CreateDynamicObject(18671,-1050.4060059,-1618.2189941,90.7829971,0.0000000,0.0000000,0.0000000); //object(carwashspray) (2)
	CreateDynamicObject(18676,-1118.6679688,-1622.5019531,75.6999969,0.0000000,0.0000000,358.0000000); //object(coke_trail) (1)
	CreateDynamicObject(936,-1117.9449463,-1616.3559570,75.8420029,0.0000000,0.0000000,50.0000000); //object(cj_df_worktop_2) (1)
	CreateDynamicObject(937,-1117.2099609,-1625.8380127,75.8489990,0.0000000,0.0000000,310.0000000); //object(cj_df_worktop) (1)
	CreateDynamicObject(941,-1115.5229492,-1615.7149658,75.8420029,0.0000000,0.0000000,0.0000000); //object(cj_df_worktop_3) (1)
	CreateDynamicObject(1421,-1119.5729980,-1626.6250000,76.1370010,0.0000000,0.0000000,310.0000000); //object(dyn_boxes) (1)
	CreateDynamicObject(1305,-1112.6190186,-1637.9969482,74.8000031,0.0000000,0.0000000,40.0000000); //object(dyn_quarryrock01) (1)
	CreateDynamicObject(1305,-1111.3759766,-1636.8599854,74.8000031,0.0000000,20.0000000,199.9957275); //object(dyn_quarryrock01) (2)
	CreateDynamicObject(1305,-1111.2969971,-1638.7089844,74.8000031,0.0000000,19.9951172,129.9951172); //object(dyn_quarryrock01) (3)
	CreateDynamicObject(1303,-1110.0090332,-1636.9990234,75.1999969,0.0000000,0.0000000,0.0000000); //object(dyn_quarryrock03) (1)
	CreateDynamicObject(1303,-1109.5269775,-1638.3289795,75.1999969,0.0000000,0.0000000,60.0000000); //object(dyn_quarryrock03) (2)
	CreateDynamicObject(1303,-1108.6899414,-1637.4200439,75.1999969,0.0000000,0.0000000,289.9963379); //object(dyn_quarryrock03) (3)
	CreateDynamicObject(1303,-1108.6319580,-1638.8179932,75.1999969,0.0000000,0.0000000,289.9951172); //object(dyn_quarryrock03) (4)
	CreateDynamicObject(1303,-1108.9179688,-1636.7049561,75.1999969,0.0000000,0.0000000,29.9951172); //object(dyn_quarryrock03) (5)
	CreateDynamicObject(1303,-1107.9670410,-1636.7409668,75.1999969,0.0000000,0.0000000,343.9926758); //object(dyn_quarryrock03) (6)
	CreateDynamicObject(1303,-1107.6820068,-1638.1540527,75.1999969,0.0000000,0.0000000,344.9874268); //object(dyn_quarryrock03) (7)
	//==== Army LS Int =========
	CreateDynamicObject(14667,-424.5509949,-121.1719971,2103.5400391,0.0000000,0.0000000,0.0000000); //object(int_7_11a41) (1)
	CreateDynamicObject(7507,-464.1600037,-127.1019974,2102.0000000,0.0000000,0.0000000,90.0000000); //object(vgnlowbuild09) (1)
	CreateDynamicObject(1498,-427.6690063,-133.5639954,2101.4899902,0.0000000,0.0000000,90.0000000); //object(gen_doorext03) (1)
	CreateDynamicObject(1796,-410.8129883,-117.6029968,2101.5549316,0.0000000,0.0000000,0.0000000); //object(low_bed_4) (1)
	CreateDynamicObject(1796,-413.2109985,-117.6060028,2101.5549316,0.0000000,0.0000000,0.0000000); //object(low_bed_4) (2)
	CreateDynamicObject(1796,-415.8020020,-117.6220016,2101.5549316,0.0000000,0.0000000,0.0000000); //object(low_bed_4) (3)
	CreateDynamicObject(1796,-418.3770142,-117.5589981,2101.5549316,0.0000000,0.0000000,0.0000000); //object(low_bed_4) (4)
	CreateDynamicObject(1796,-419.3240051,-121.0550003,2101.5549316,0.0000000,0.0000000,0.0000000); //object(low_bed_4) (6)
	CreateDynamicObject(1796,-417.3840027,-121.0589981,2101.5549316,0.0000000,0.0000000,0.0000000); //object(low_bed_4) (7)
	CreateDynamicObject(1796,-415.3779907,-121.0449982,2101.5549316,0.0000000,0.0000000,0.0000000); //object(low_bed_4) (8)
	CreateDynamicObject(1796,-413.2210083,-121.0169983,2101.5549316,0.0000000,0.0000000,0.0000000); //object(low_bed_4) (9)
	CreateDynamicObject(1796,-411.0669861,-121.0380020,2101.5549316,0.0000000,0.0000000,0.0000000); //object(low_bed_4) (10)
	CreateDynamicObject(19451,-413.4360046,-123.3799973,2103.3049316,0.0000000,0.0000000,270.0000000); //object(wall091) (1)
	CreateDynamicObject(19389,-421.3729858,-121.6899033,2103.3049316,0.0000000,0.0000000,0.0000000); //object(wall037) (1)
	CreateDynamicObject(19359,-419.8559875,-123.3809967,2103.3049316,0.0000000,0.0000000,270.0000000); //object(wall007) (1)
	CreateDynamicObject(7507,-427.8330078,-174.8000031,2102.0000000,0.0000000,0.0000000,180.0000000); //object(vgnlowbuild09) (5)
	CreateDynamicObject(7507,-413.1820068,-77.1439972,2102.0000000,0.0000000,0.0000000,0.0000000); //object(vgnlowbuild09) (6)
	CreateDynamicObject(7507,-372.5220032,-127.5370026,2102.0000000,0.0000000,0.0000000,269.9945068); //object(vgnlowbuild09) (7)
	CreateDynamicObject(19451,-421.2059937,-115.2959976,2103.3049316,0.0000000,0.0000000,178.0000000); //object(wall091) (2)
	CreateDynamicObject(19389,-423.0650024,-123.3809967,2103.3049316,0.0000000,0.0000000,90.0000000); //object(wall037) (2)
	CreateDynamicObject(19359,-426.2749939,-123.3809967,2103.3049316,0.0000000,0.0000000,270.0000000); //object(wall007) (2)
	CreateDynamicObject(1492,-423.8460083,-123.3730011,2101.5439453,0.0000000,0.0000000,0.0000000); //object(gen_doorint02) (1)
	CreateDynamicObject(1492,-421.3720093,-120.9088974,2101.5439453,0.0000000,0.0000000,270.0000000); //object(gen_doorint02) (2)
	CreateDynamicObject(18001,-413.0100098,-123.4469986,2105.7529297,0.0000000,180.0000000,0.0000000); //object(int_barbera07) (1)
	CreateDynamicObject(18001,-421.1600037,-123.4469986,2105.7529297,0.0000000,0.0000000,0.0000000); //object(int_barbera07) (2)
	CreateDynamicObject(18001,-429.3200073,-123.4469986,2105.7529297,0.0000000,180.0000000,0.0000000); //object(int_barbera07) (3)
	CreateDynamicObject(14762,-415.0429993,-113.6949997,2103.8999023,0.0000000,0.0000000,270.0000000); //object(arsewinows) (1)
	CreateDynamicObject(2108,-409.5729980,-114.5579987,2101.5549316,0.0000000,0.0000000,0.0000000); //object(cj_mlight13) (1)
	CreateDynamicObject(2025,-409.6080017,-122.9629974,2101.5549316,0.0000000,0.0000000,180.0000000); //object(mrk_wrobe_tmp) (1)
	CreateDynamicObject(2306,-411.8659973,-115.4789963,2101.5549316,0.0000000,0.0000000,0.0000000); //object(swank_cabinet_4d) (1)
	CreateDynamicObject(2306,-414.3649902,-115.5070038,2101.5549316,0.0000000,0.0000000,0.0000000); //object(swank_cabinet_4d) (2)
	CreateDynamicObject(2306,-416.9920044,-115.4779968,2101.5549316,0.0000000,0.0000000,0.0000000); //object(swank_cabinet_4d) (3)
	CreateDynamicObject(2306,-419.6499939,-115.5749969,2101.5549316,0.0000000,0.0000000,0.0000000); //object(swank_cabinet_4d) (4)
	CreateDynamicObject(1208,-425.6690063,-113.8539963,2101.5549316,0.0000000,0.0000000,180.0000000); //object(washer) (1)
	CreateDynamicObject(1738,-426.8980103,-113.8929977,2102.2089844,0.0000000,0.0000000,0.0000000); //object(cj_radiator_old) (1)
	CreateDynamicObject(1738,-409.2980042,-116.8229980,2102.2089844,0.0000000,0.0000000,270.0000000); //object(cj_radiator_old) (2)
	CreateDynamicObject(1738,-420.9660034,-116.6060028,2102.2099609,0.0000000,0.0000000,90.0000000); //object(cj_radiator_old) (3)
	CreateDynamicObject(1751,-421.3450012,-123.2880020,2104.5000000,20.0000000,0.0000000,142.0000000); //object(med_tv_4) (1)
	CreateDynamicObject(1778,-420.6830139,-122.6880035,2101.5620117,0.0000000,0.0000000,0.0000000); //object(cj_mop_pail) (1)
	CreateDynamicObject(2130,-427.1449890,-116.6559982,2101.5549316,0.0000000,0.0000000,90.0000000); //object(cj_k1_sink) (1)
	CreateDynamicObject(2132,-427.2109985,-118.6770020,2101.5549316,0.0000000,0.0000000,90.0000000); //object(cj_kitch2_sink) (1)
	CreateDynamicObject(2514,-421.9500122,-114.4359970,2101.5549316,0.0000000,0.0000000,320.0000000); //object(cj_toilet1) (1)
	CreateDynamicObject(2517,-424.6679993,-115.1250000,2101.5549316,0.0000000,0.0000000,0.0000000); //object(cj_shower1) (1)
	CreateDynamicObject(14867,-415.1860046,-122.9850006,2103.0849609,0.0000000,0.0000000,0.0000000); //object(bobbie-cupboards) (1)
	CreateDynamicObject(2230,-420.2070007,-123.1790009,2101.5620117,0.0000000,0.0000000,168.0000000); //object(swank_speaker_2) (1)
	CreateDynamicObject(2844,-420.3670044,-115.9850006,2101.5549316,0.0000000,0.0000000,0.0000000); //object(gb_bedclothes03) (1)
	CreateDynamicObject(1235,-420.8800049,-120.5179977,2102.0581055,0.0000000,0.0000000,0.0000000); //object(wastebin) (1)
	CreateDynamicObject(2670,-422.6050110,-114.2450027,2101.6469727,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_1) (1)
	CreateDynamicObject(2748,-410.9429932,-135.4100037,2102.1599121,0.0000000,0.0000000,270.0000000); //object(cj_donut_chair2) (1)
	CreateDynamicObject(2747,-412.3229980,-135.4069977,2101.9750977,0.0000000,0.0000000,90.0000000); //object(cj_donut_table) (1)
	CreateDynamicObject(2746,-414.0549927,-135.3320007,2102.1520996,0.0000000,0.0000000,270.0000000); //object(cj_donut_chair) (1)
	CreateDynamicObject(2747,-415.8009949,-135.4160004,2101.9750977,0.0000000,0.0000000,90.0000000); //object(cj_donut_table) (2)
	CreateDynamicObject(2746,-417.5150146,-135.3670044,2102.1520996,0.0000000,0.0000000,270.0000000); //object(cj_donut_chair) (2)
	CreateDynamicObject(2747,-419.3009949,-135.4019928,2101.9750977,0.0000000,0.0000000,90.0000000); //object(cj_donut_table) (3)
	CreateDynamicObject(2746,-421.0650024,-135.3529968,2102.1520996,0.0000000,0.0000000,270.0000000); //object(cj_donut_chair) (3)
	CreateDynamicObject(2747,-422.7659912,-135.3849945,2101.9750977,0.0000000,0.0000000,90.0000000); //object(cj_donut_table) (4)
	CreateDynamicObject(2746,-424.4570007,-135.3690033,2102.1520996,0.0000000,0.0000000,270.0000000); //object(cj_donut_chair) (4)
	CreateDynamicObject(2747,-426.0849915,-135.3130035,2101.9750977,0.0000000,0.0000000,90.0000000); //object(cj_donut_table) (5)
	CreateDynamicObject(2639,-427.2179871,-135.3650055,2102.1818848,0.0000000,0.0000000,270.0000000); //object(cj_pizza_chair3) (1)
	CreateDynamicObject(12842,-414.6010132,-128.9920044,2102.0090332,0.0000000,0.0000000,0.0000000); //object(cos_pizseats) (1)
	CreateDynamicObject(2677,-418.1960144,-132.7760010,2101.8278809,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_7) (1)
	CreateDynamicObject(2675,-417.5790100,-125.8870010,2101.6201172,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_6) (1)
	CreateDynamicObject(2676,-417.5409851,-128.2250061,2101.6589355,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_8) (1)
	CreateDynamicObject(2672,-410.8519897,-131.1390076,2101.8430176,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_4) (1)
	CreateDynamicObject(2671,-410.8880005,-127.6070023,2101.5559082,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_3) (1)
	CreateDynamicObject(2670,-415.0009766,-129.4667969,2101.6479492,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_1) (2)
	CreateDynamicObject(14892,-408.5119934,-151.9609985,2105.0000000,0.0000000,180.0000000,90.0000000); //object(mp_sfpd_win2) (1)
	CreateDynamicObject(2670,-414.4400024,-125.0520020,2101.6479492,0.0000000,0.0000000,234.0000000); //object(proc_rubbish_1) (2)
	//=== Wahta ===
 	CreateDynamicObject(1684,2546.4689941,-472.3179932,85.3399963,0.0000000,0.0000000,253.9949951); //object(portakabin) (1)
	CreateDynamicObject(12929,2543.7570801,-462.3989868,83.0999985,0.0000000,0.0000000,344.0000000); //object(sw_shed06) (1)
	CreateDynamicObject(1257,2517.2460938,-461.8900146,84.5559998,5.0000000,0.0000000,160.0000000); //object(bustopm) (1)
	CreateDynamicObject(1319,2537.0039062,-449.1749878,82.5469971,0.0000000,0.0000000,0.0000000); //object(ws_ref_bollard) (2)
	CreateDynamicObject(1319,2524.5891113,-446.9330139,82.5469971,0.0000000,0.0000000,0.0000000); //object(ws_ref_bollard) (3)
	CreateDynamicObject(3864,2560.6799316,-485.6799927,89.9209976,0.0000000,0.0000000,0.0000000); //object(ws_floodlight) (1)
	CreateDynamicObject(3872,2553.9990234,-485.6870117,90.6999969,0.0000000,0.0000000,0.0000000); //object(ws_floodbeams) (1)
	CreateDynamicObject(3785,2543.1579590,-475.9750061,86.0739975,0.0000000,0.0000000,161.2500000); //object(bulkheadlight) (1)
	CreateDynamicObject(19125,2536.5400391,-460.3290100,82.9000015,0.0000000,0.0000000,0.0000000); //object(bollardlight5) (1)
	CreateDynamicObject(906,2545.0048828,-465.2359924,83.0000000,0.0000000,0.0000000,346.0000000); //object(p_rubblebig) (1)
	CreateDynamicObject(906,2543.7539062,-465.6640015,83.0000000,90.0000000,0.0000000,147.2479248); //object(p_rubblebig) (2)
	CreateDynamicObject(943,2551.0148926,-462.5130005,84.5240021,0.0000000,0.0000000,168.0000000); //object(generator_low) (1)
	CreateDynamicObject(929,2550.3000488,-465.8500061,84.7570038,0.0000000,0.0000000,348.0000000); //object(generator) (1)
	CreateDynamicObject(18725,2550.1240234,-466.0220032,83.5999985,0.0000000,0.0000000,0.0000000); //object(smoke30lit) (1)
	CreateDynamicObject(18688,2550.1311035,-466.3559875,84.1999969,0.0000000,0.0000000,0.0000000); //object(fire) (1)
	CreateDynamicObject(6976,2538.2199707,-526.3530273,87.5999985,0.0000000,0.0000000,296.0000000); //object(shamheliprt04) (4)
	//=== ARMY 51 ==========
	CreateDynamicObject(8150,212.6470032,1799.1080322,19.7420006,0.0000000,0.0000000,180.0000000); //object(vgsselecfence04) (1)
	CreateDynamicObject(8210,121.9639969,1799.0629883,19.7420006,0.0000000,0.0000000,0.0000000); //object(vgsselecfence12) (1)
	CreateDynamicObject(8210,94.4970016,1826.5520020,19.7420006,0.0000000,0.0000000,270.0000000); //object(vgsselecfence12) (2)
	CreateDynamicObject(8210,94.5019989,1882.1169434,19.7420006,0.0000000,0.0000000,270.0000000); //object(vgsselecfence12) (3)
	CreateDynamicObject(987,94.8050003,1935.0389404,16.9279995,0.0000000,0.0000000,267.9949951); //object(elecfence_bar) (2)
	CreateDynamicObject(987,104.2340012,1942.3439941,16.9279995,0.0000000,0.0000000,217.9949951); //object(elecfence_bar) (3)
	CreateDynamicObject(987,116.1610031,1942.3179932,16.9279995,0.0000000,0.0000000,179.9907227); //object(elecfence_bar) (4)
	CreateDynamicObject(987,128.1380005,1942.3079834,16.9279995,0.0000000,0.0000000,179.9890137); //object(elecfence_bar) (5)
	gatearmy[0][0] = CreateDynamicObject(976,126.9390030,1942.5059814,18.1000004,0.0000000,0.0000000,0.0000000); //object(phils_compnd_gate) (1)
	gatearmy[1][0] = CreateDynamicObject(969,94.1539993,1914.4200439,17.2299995,0.0000000,0.0000000,89.7500000); //object(electricgate) (1)
	CreateDynamicObject(16096,138.3309937,1939.5419922,20.2070007,0.0000000,0.0000000,270.0000000); //object(des_a51guardbox04) (1)
	CreateDynamicObject(5837,96.3909988,1911.1639404,18.8150005,0.0000000,0.0000000,270.0000000); //object(ci_guardhouse1) (1)
	CreateDynamicObject(8210,294.8859863,1854.5959473,19.7420006,0.0000000,0.0000000,90.2500000); //object(vgsselecfence12) (5)
	CreateDynamicObject(8210,279.5880127,1905.4549561,19.7420006,0.0000000,0.0000000,123.2471924); //object(vgsselecfence12) (6)
	CreateDynamicObject(8210,264.5530090,1956.5489502,19.7420006,0.0000000,0.0000000,89.4946289); //object(vgsselecfence12) (7)
	CreateDynamicObject(8210,264.8500061,2012.0970459,19.7420006,0.0000000,0.0000000,89.4891357); //object(vgsselecfence12) (8)
	CreateDynamicObject(8210,283.7720032,2060.7829590,19.7420006,0.0000000,0.0000000,47.7391357); //object(vgsselecfence12) (9)
	CreateDynamicObject(3707,365.7059937,1925.2550049,24.5869999,0.0000000,0.0000000,180.0000000); //object(rdwarhusmed) (1)
	CreateDynamicObject(3776,348.2950134,1984.0000000,25.5149994,0.0000000,0.0000000,226.0000000); //object(ci_bstage) (1)
	CreateDynamicObject(9260,251.2500000,2008.1169434,21.8490009,0.0000000,0.0000000,0.0000000); //object(hrborbuild_sfn03) (1)
	CreateDynamicObject(16770,229.4259949,1989.2030029,18.2310009,0.0000000,0.0000000,90.0000000); //object(des_gunbldg01) (1)
	CreateDynamicObject(3279,196.1280060,1997.1619873,16.6480007,0.0000000,0.0000000,0.0000000); //object(a51_spottower) (1)
	CreateDynamicObject(3279,365.1090088,2067.9399414,16.6410007,0.0000000,0.0000000,270.0000000); //object(a51_spottower) (2)
	CreateDynamicObject(987,285.4010010,1806.2530518,16.9279995,0.0000000,0.0000000,47.9949951); //object(elecfence_bar) (10)
	CreateDynamicObject(987,275.9700012,1798.9050293,16.9279995,0.0000000,0.0000000,37.9937744); //object(elecfence_bar) (11)
	CreateDynamicObject(3279,351.9129944,1807.8900146,17.0979996,0.0000000,0.0000000,200.0000000); //object(a51_spottower) (3)
	CreateDynamicObject(5837,338.6570129,1796.5429688,18.8150005,0.0000000,0.0000000,32.0000000); //object(ci_guardhouse1) (2)
	gatearmy[2][0] = CreateDynamicObject(969,349.3800049,1800.5159912,17.2299995,0.0000000,0.0000000,213.7473145); //object(electricgate) (3)
	CreateDynamicObject(3783,235.1179962,1885.0710449,18.9370003,0.0000000,0.0000000,270.0000000); //object(las2xref01_lax) (1)
	CreateDynamicObject(3783,192.6690063,1885.0250244,18.9370003,0.0000000,0.0000000,90.0000000); //object(las2xref01_lax) (2)
	CreateDynamicObject(8210,141.9199982,1970.3160400,19.7420006,0.0000000,0.0000000,270.0000000); //object(vgsselecfence12) (10)
	CreateDynamicObject(8210,165.6399994,2011.7590332,19.7420006,0.0000000,0.0000000,210.2500000); //object(vgsselecfence12) (11)
	CreateDynamicObject(8406,162.2100067,1941.1569824,22.7740002,0.0000000,0.0000000,0.0000000); //object(carparksign01_lvs) (1)
	CreateDynamicObject(984,182.8090057,1941.3100586,17.2999992,0.0000000,0.0000000,270.0000000); //object(fenceshit2) (1)
	CreateDynamicObject(984,146.8370056,1941.3420410,18.6000004,0.0000000,0.0000000,270.0000000); //object(fenceshit2) (2)
	CreateDynamicObject(1496,245.6109924,1987.0119629,16.6919994,0.0000000,0.0000000,0.0000000); //object(gen_doorshop02) (1)
	//=== LS Warehouse ====
	CreateDynamicObject(1278,2773.3149414,-2431.7219238,26.8269997,0.0000000,0.0000000,270.0000000); //object(sub_floodlite) (1)
	CreateDynamicObject(5020,2819.0300293,-2435.6259766,10.6000004,358.0000000,90.0000000,90.0000000); //object(mul_las) (1)
	CreateDynamicObject(5020,2813.8200684,-2435.6420898,11.5000000,20.0000000,90.0000000,90.0000000); //object(mul_las) (2)
	CreateDynamicObject(970,2818.6140137,-2437.2419434,11.1770000,0.0000000,358.0000000,0.0000000); //object(fencesmallb) (1)
	CreateDynamicObject(970,2818.5710449,-2433.9909668,11.1770000,0.0000000,357.9949951,0.0000000); //object(fencesmallb) (2)
	CreateDynamicObject(970,2813.9250488,-2434.1459961,12.0719995,0.0000000,20.0000000,0.0000000); //object(fencesmallb) (4)
	CreateDynamicObject(970,2813.9270020,-2437.2480469,12.0719995,0.0000000,19.9951172,0.0000000); //object(fencesmallb) (5)
	CreateDynamicObject(970,2810.8610840,-2431.8391113,13.1800003,0.0000000,0.0000000,270.0000000); //object(fencesmallb) (6)
	CreateDynamicObject(970,2810.9289551,-2439.4929199,13.1800003,0.0000000,0.0000000,270.0000000); //object(fencesmallb) (7)
	CreateDynamicObject(5020,2824.3820801,-2434.9699707,11.5000000,320.0000000,90.0000000,90.0000000); //object(mul_las) (3)
	CreateDynamicObject(1423,2820.9560547,-2432.6789551,11.7989998,0.0000000,0.0000000,90.0000000); //object(dyn_roadbarrier_4) (1)
	CreateDynamicObject(1423,2821.0959473,-2438.6088867,11.7989998,0.0000000,0.0000000,270.0000000); //object(dyn_roadbarrier_4) (2)
	//== EL Q_EatWarehouse ====
	CreateDynamicObject(2991,-1477.4919434,2617.5349121,58.4090004,0.0000000,0.0000000,90.0000000); //object(imy_bbox) (1)
	CreateDynamicObject(2912,-1478.5939941,2620.0969238,57.7809982,0.0000000,0.0000000,0.0000000); //object(temp_crate1) (1)
	CreateDynamicObject(2912,-1478.5909424,2620.0729980,58.4809990,0.0000000,0.0000000,20.0000000); //object(temp_crate1) (2)
	CreateDynamicObject(2912,-1478.3900146,2619.8181152,59.5000000,90.0000000,90.0000000,129.9951172); //object(temp_crate1) (3)
	CreateDynamicObject(2912,-1477.4730225,2620.4079590,57.7809982,0.0000000,0.0000000,40.0000000); //object(temp_crate1) (4)
	CreateDynamicObject(2912,-1477.9560547,2621.6530762,57.7809982,0.0000000,0.0000000,339.9957275); //object(temp_crate1) (5)
	CreateDynamicObject(931,-1484.2469482,2611.7109375,58.8429985,0.0000000,0.0000000,0.0000000); //object(rack3) (1)
	//== LSPD =========
	CreateDynamicObject(996,1537.7929688,-1681.0529785,13.1320000,0.0000000,0.0000000,90.0000000); //object(lhouse_barrier1) (1)
	CreateDynamicObject(996,1537.7519531,-1671.4439697,13.1320000,0.0000000,0.0000000,90.0000000); //object(lhouse_barrier1) (2)
	CreateDynamicObject(997,1534.5260010,-1681.9110107,12.5469999,0.0000000,0.0000000,0.0000000); //object(lhouse_barrier3) (1)
	CreateDynamicObject(997,1534.5610352,-1663.6040039,12.5469999,0.0000000,0.0000000,0.0000000); //object(lhouse_barrier3) (2)
	CreateDynamicObject(1257,1536.5279541,-1688.5639648,13.8260002,0.0000000,0.0000000,0.0000000); //object(bustopm) (1)
	CreateDynamicObject(982,1534.5959473,-1650.6660156,13.2299995,0.0000000,0.0000000,0.0000000); //object(fenceshit) (1)
	CreateDynamicObject(983,1537.0450439,-1635.8349609,13.2299995,0.0000000,0.0000000,310.0000000); //object(fenceshit3) (1)
	CreateDynamicObject(983,1542.6469727,-1633.2979736,13.2299995,0.0000000,0.0000000,278.7457275); //object(fenceshit3) (2)
	CreateDynamicObject(983,1544.9260254,-1620.6920166,13.0799999,0.0000000,0.0000000,357.9957275); //object(fenceshit3) (3)
	CreateDynamicObject(16003,2325.7041016,2470.0119629,39.4059982,0.0000000,0.0000000,0.0000000); //object(drvin_ticket) (1)
	//======= BANK Folleah ======
	CreateDynamicObject(19376, 1097.96338, 272.12219, 1007.91553,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19376, 1097.96338, 262.48849, 1007.91553,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19376, 1108.46326, 272.12219, 1007.91553,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19376, 1108.46326, 262.48849, 1007.91553,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19354, 1112.11011, 257.62131, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1108.89832, 257.62131, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1105.69507, 257.62131, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1102.48877, 257.62131, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1099.28088, 257.62131, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1096.07654, 257.62131, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1092.86755, 257.62131, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1092.86755, 257.62131, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1096.07654, 257.62131, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1099.28088, 257.62131, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1102.48877, 257.62131, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1105.69507, 257.62131, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1108.89832, 257.62131, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1112.11011, 257.62131, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(16780, 1110.33215, 260.69394, 1011.77002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18084, 1106.50659, 258.62741, 1009.79999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1092.86157, 259.27658, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1092.86157, 262.48550, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1092.86157, 265.69360, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1092.86157, 268.90189, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1092.86157, 272.10730, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1092.86157, 275.30811, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1092.86157, 259.27661, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1092.86157, 262.48550, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1092.86157, 265.69360, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1092.86157, 268.90189, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1092.86157, 272.10730, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1092.86157, 275.30811, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1113.60645, 259.27661, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1113.62036, 262.48550, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1113.62036, 265.69360, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1113.62036, 268.90189, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1113.62036, 272.10730, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1113.62036, 275.30811, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1113.60645, 259.27661, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1113.62036, 262.48550, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1113.62036, 265.69360, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1113.62036, 268.90189, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1113.62036, 272.10730, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1113.62036, 275.30811, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1112.11011, 276.81641, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1108.89832, 276.81641, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1105.69507, 276.81641, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1102.48877, 276.81641, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1099.28088, 276.81641, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1096.07654, 276.81641, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1092.86755, 276.81641, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2942, 1113.20325, 262.32681, 1008.59998,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2942, 1113.20325, 264.85309, 1008.59998,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19361, 1092.86755, 276.81641, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1096.07654, 276.81641, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1099.28088, 276.81641, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1102.48877, 276.81641, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1105.69507, 276.81641, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1108.89832, 276.81641, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1112.11011, 276.81641, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1759, 1106.44116, 265.04922, 1007.99841,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1759, 1106.44116, 263.70410, 1007.99841,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1759, 1106.44116, 262.33829, 1007.99841,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1759, 1106.44116, 260.94861, 1007.99841,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2067, 1104.82312, 276.29419, 1007.99878,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2164, 1105.93091, 276.72842, 1008.00244,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2208, 1104.73120, 257.06143, 1008.00262,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2606, 1108.66980, 276.89111, 1010.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2608, 1108.65637, 276.49823, 1008.59998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3437, 1100.66492, 258.53873, 1008.00250,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(3494, 1108.61389, 257.86230, 1008.00067,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3494, 1113.10950, 257.86081, 1008.00067,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1886, 1113.26001, 259.12860, 1011.62891,   0.00000, 0.00000, -149.00000);
	CreateDynamicObject(2422, 1105.37085, 272.88754, 1008.79999,   0.00000, 0.00000, -25.00000);
	CreateDynamicObject(2434, 1112.88794, 272.07828, 1008.00250,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2434, 1110.74988, 271.85840, 1008.00250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 1109.82141, 271.85840, 1008.00317,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 1108.89404, 271.85840, 1008.00317,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 1107.96643, 271.85840, 1008.00317,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 1107.04089, 271.85840, 1008.00317,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 1106.11487, 271.85840, 1008.00317,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 1105.18640, 271.85840, 1008.00317,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 1104.26025, 271.85840, 1008.00317,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18092, 1106.93787, 272.52621, 1008.29999,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2422, 1108.99548, 273.03818, 1008.79999,   0.00000, 0.00000, 25.00000);
	CreateDynamicObject(1715, 1106.01453, 273.56879, 1008.00269,   0.00000, 0.00000, -18.00000);
	CreateDynamicObject(1715, 1108.01514, 273.59842, 1008.00269,   0.00000, 0.00000, 25.00000);
	CreateDynamicObject(1715, 1106.91370, 273.52484, 1008.00269,   0.00000, 0.00000, -4.00000);
	CreateDynamicObject(1546, 1109.09912, 272.97186, 1008.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1719, 1107.74597, 272.50790, 1008.84003,   0.00000, 0.00000, 4.00000);
	CreateDynamicObject(1808, 1113.37146, 273.36026, 1008.00232,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2201, 1106.70801, 272.22180, 1008.72998,   0.00000, 0.00000, -93.00000);
	CreateDynamicObject(2202, 1110.56763, 276.33563, 1008.00287,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2067, 1104.11975, 276.29419, 1007.99878,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2067, 1103.53748, 276.29419, 1007.99878,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2067, 1102.79651, 276.29422, 1007.99878,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2828, 1105.74329, 272.50613, 1008.79938,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2738, 1093.29871, 258.40781, 1008.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2739, 1093.47217, 262.23495, 1008.00043,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2738, 1093.29871, 259.89670, 1008.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2738, 1093.29871, 261.38351, 1008.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1099.62073, 259.25079, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1099.62073, 262.46109, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1099.62073, 267.17490, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2741, 1093.54773, 261.97177, 1008.90747,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2742, 1093.08948, 265.78961, 1009.05182,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2813, 1113.22034, 268.59219, 1008.50000,   0.00000, 0.00000, -69.00000);
	CreateDynamicObject(2314, 1113.19128, 268.14877, 1008.00189,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2894, 1113.19873, 269.69952, 1008.50348,   0.00000, 0.00000, -113.00000);
	CreateDynamicObject(2287, 1113.03040, 264.23593, 1010.31677,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2286, 1113.51550, 261.72092, 1010.79999,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2282, 1113.05872, 266.60333, 1010.70740,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2280, 1113.03125, 269.74567, 1010.66852,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19361, 1099.62073, 259.25079, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1099.62073, 262.46109, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 1093.26855, 259.16229, 1009.00110,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 1093.26855, 260.64740, 1009.00110,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 1093.26855, 262.11411, 1009.00110,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1491, 1094.92432, 257.70193, 1008.00269,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1491, 1094.92432, 259.20859, 1008.00269,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1491, 1094.92432, 260.69519, 1008.00269,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2741, 1093.54773, 260.48889, 1008.90747,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2741, 1093.54773, 258.99951, 1008.90747,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1099.62073, 267.17490, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1098.10510, 268.76346, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1094.89417, 268.76349, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1091.68359, 268.76349, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1098.10510, 268.76349, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1094.89417, 268.76349, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1091.68359, 268.76349, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 1092.88867, 263.81000, 1009.00110,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 1092.88867, 267.00089, 1009.00110,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 1093.91699, 268.68854, 1009.00110,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 1097.12097, 268.68851, 1009.00110,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 1098.70020, 267.40717, 1009.00110,   0.00000, 0.00000, 33.00000);
	CreateDynamicObject(19367, 1099.53833, 262.06296, 1009.00110,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 1099.53833, 258.86310, 1009.00110,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 1098.00574, 257.66669, 1009.00110,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 1094.80518, 257.66669, 1009.00110,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 1091.60425, 257.66669, 1009.00110,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 1092.88867, 260.42999, 1009.00110,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 1092.88867, 257.23029, 1009.00110,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1097.76294, 267.17859, 1010.79999,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(1491, 1099.61328, 264.05847, 1008.00269,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19355, 1094.26733, 267.17859, 1010.79999,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19355, 1097.76294, 263.96960, 1010.79999,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19355, 1094.26733, 263.96960, 1010.79999,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19355, 1097.76294, 260.74359, 1010.79999,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19355, 1097.76294, 257.54959, 1010.79999,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19355, 1094.26733, 260.74899, 1010.79999,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19355, 1094.26733, 257.55240, 1010.79999,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(2739, 1093.47217, 263.00421, 1008.00043,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2739, 1093.47217, 263.79080, 1008.00043,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2739, 1093.47217, 264.57111, 1008.00043,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2742, 1093.08948, 266.54269, 1009.05182,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2742, 1093.08948, 267.32031, 1009.05182,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19454, 1101.40369, 261.88782, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 1101.40369, 271.52081, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 1097.91760, 271.52081, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 1094.41736, 271.52081, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 1104.90491, 261.88779, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 1108.38770, 261.88779, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 1111.86938, 261.88779, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 1104.88464, 271.52081, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 1108.36182, 271.52081, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 1111.84363, 271.52081, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 1111.81177, 281.13519, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 1108.32373, 281.13519, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 1104.85437, 281.13519, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 1101.35071, 281.13519, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 1097.87781, 281.13519, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 1094.37805, 281.13519, 1011.72137,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19354, 1099.62097, 270.29807, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1101.15088, 271.89047, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19354, 1102.56189, 271.87598, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1099.62097, 270.29810, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1101.15088, 271.89050, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19361, 1102.56189, 271.87601, 1011.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19427, 1110.03381, 271.87601, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19434, 1110.03381, 271.87601, 1011.00153,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1886, 1100.16772, 258.22992, 1011.62891,   0.00000, 0.00000, -222.00000);
	CreateDynamicObject(1759, 1105.34143, 266.03082, 1007.99841,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1759, 1105.34143, 264.71121, 1007.99841,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1759, 1105.34143, 263.34790, 1007.99841,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1759, 1105.34143, 261.94739, 1007.99841,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1569, 1109.39563, 257.68051, 1008.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1569, 1112.36414, 257.68442, 1008.00000,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(3494, 1101.80103, 263.10239, 1008.00067,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1649, 1105.72717, 257.73349, 1010.40002,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(19354, 1099.65259, 273.50421, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19354, 1099.65259, 276.71451, 1007.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2634, 1099.64648, 274.52249, 1009.50000,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19361, 1099.65259, 273.50421, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1099.65259, 276.71451, 1011.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2921, 1099.69458, 276.27234, 1010.83228,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2922, 1099.74036, 275.72107, 1009.39008,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19427, 1113.79932, 271.87601, 1007.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19434, 1113.79932, 271.87601, 1011.00153,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2572, 1103.12207, 259.02924, 1008.00299,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(2273, 1100.19763, 266.34595, 1010.12488,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2271, 1100.23083, 267.62729, 1010.24127,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2261, 1100.20508, 269.29138, 1009.84949,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2259, 1100.17578, 271.12369, 1010.20001,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1710, 1100.38269, 266.95541, 1008.00092,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1665, 1101.44202, 259.44717, 1008.52002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1775, 1102.45422, 271.32281, 1008.99933,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(630, 1113.17102, 263.59570, 1009.00153,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(633, 1113.00330, 259.17569, 1008.99957,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(633, 1108.73718, 259.17569, 1008.99957,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(638, 1106.69861, 258.32568, 1008.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2010, 1113.01245, 266.96579, 1008.00085,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2010, 1113.05920, 270.76984, 1008.00085,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(16780, 1110.33215, 267.64929, 1011.77002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(16780, 1102.99060, 267.64929, 1011.77002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3857, 1113.78784, 271.80029, 1013.69019,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(3857, 1105.65259, 271.82501, 1012.29999,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(1649, 1101.33582, 257.73090, 1010.40002,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(18084, 1103.89673, 258.62741, 1009.79999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18084, 1101.35254, 258.62741, 1009.79999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 1099.53259, 264.73969, 1012.25000,   0.00000, 0.00000, 0.00000);
	//==== Ammo GTA IV ==========
	CreateDynamicObject(353,288.1010132,-105.1370010,1001.5000000,84.0000000,270.0000000,300.0000000); //object(1)
	CreateDynamicObject(355,290.3429871,-105.4349976,1001.5000000,85.9973755,269.9832764,260.0087280); //object(2)
	CreateDynamicObject(356,292.6000061,-105.4690018,1001.5000000,85.9954834,269.9780273,260.0079346); //object(3)
	CreateDynamicObject(349,287.8380127,-110.4950027,1001.5000000,85.9954834,269.9780273,64.0079346); //object(5)
	CreateDynamicObject(347,290.2139893,-110.5479965,1001.5000000,90.0000000,202.1830597,131.8012695); //object(6)
	CreateDynamicObject(348,292.4110107,-110.7949982,1001.5000000,85.9954834,269.9779968,64.0063477); //object(7)
	CreateDynamicObject(343,286.2720032,-109.5429993,1001.5000000,90.0000000,340.0000000,0.0000000); //object(8)
	CreateDynamicObject(337,286.4360046,-106.5270004,1001.5999756,0.0000000,91.9999695,117.9999390); //object(9)
	//==== FBI ====
	CreateDynamicObject(1411, 1175.88, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1170.68, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1165.52, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1160.34, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1155.16, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1149.98, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1144.81, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1139.64, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1134.47, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1129.28, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1124.12, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1118.96, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1113.80, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1108.62, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1103.44, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1098.26, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1093.09, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1087.91, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1082.73, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1077.55, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1072.39, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1067.21, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1062.05, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1056.86, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1051.70, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1046.54, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(1411, 1041.37, 1164.36, 11.17,   356.86, 0.00, 0.00);
	CreateDynamicObject(966, 1031.14, 1182.90, 9.66,   0.00, 0.00, 0.00);
	CreateDynamicObject(7091, 1056.98, 1015.11, 22.61,   0.00, 0.00, 11.00);
	CreateDynamicObject(7091, 1054.95, 1019.56, 22.61,   0.00, 0.00, 33.00);
	CreateDynamicObject(7091, 1052.00, 1023.04, 22.61,   0.00, 0.00, 55.00);
	CreateDynamicObject(7091, 1047.85, 1025.16, 22.61,   0.00, 0.00, 76.00);
	CreateDynamicObject(7091, 1042.94, 1025.59, 22.61,   0.00, 0.00, 91.00);
	CreateDynamicObject(1411, 1155.39, 945.30, 11.39,   357.00, 0.00, -222.00);
	CreateDynamicObject(1411, 1151.51, 948.73, 11.39,   357.00, 0.00, -222.00);
	CreateDynamicObject(1411, 1147.67, 952.18, 11.39,   357.00, 0.00, -222.00);
	CreateDynamicObject(1411, 1143.80, 955.65, 11.39,   357.00, 0.00, -222.00);
	CreateDynamicObject(1411, 1139.97, 959.13, 11.39,   357.00, 0.00, -222.00);
	CreateDynamicObject(1411, 1136.13, 962.60, 11.39,   357.00, 0.00, -222.00);
	CreateDynamicObject(1411, 1132.28, 966.05, 11.39,   357.00, 0.00, -222.00);
	CreateDynamicObject(1411, 1128.41, 969.47, 11.39,   357.00, 0.00, -222.00);
	CreateDynamicObject(1411, 1124.56, 972.92, 11.39,   357.00, 0.00, -222.00);
	CreateDynamicObject(1411, 1120.74, 976.39, 11.39,   357.00, 0.00, -222.00);
	CreateDynamicObject(3934,1088.5209961,1073.9210205,9.8380003,0.0000000,0.0000000,90.0000000); //object(helipad01) (1)
	CreateDynamicObject(9697,982.6580200,1106.1409912,9.8350000,0.0000000,0.0000000,90.5000000); //object(carspaces3_sfw) (1)
	CreateDynamicObject(9697,1003.0819702,1054.1560059,9.8350000,0.0000000,0.0000000,270.4998779); //object(carspaces3_sfw) (2)
	//== Автошкола
	CreateDynamicObject(982,-2087.6379395,-80.3440018,34.8600006,0.0000000,0.0000000,90.0000000); //object(fenceshit) (1)
	CreateDynamicObject(984,-2068.4389648,-80.3359985,34.8009987,0.0000000,0.0000000,270.0000000); //object(fenceshit2) (1)
	CreateDynamicObject(996,-2061.8720703,-87.8779984,34.9129982,0.0000000,0.0000000,90.0000000); //object(lhouse_barrier1) (1)
	CreateDynamicObject(997,-2061.7050781,-88.8820038,34.3199997,0.0000000,0.0000000,302.0000000); //object(lhouse_barrier3) (1)
	CreateDynamicObject(970,-2059.9870605,-100.1409988,34.7159996,0.0000000,0.0000000,270.0000000); //object(fencesmallb) (1)
	//== FBI ===
	CreateDynamicObject(16665, 1069.77637, 1068.12402, 1018.20001,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(19377, 1070.44287, 1081.08618, 1007.20001,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1070.44287, 1071.46606, 1007.20001,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19355, 1073.02722, 1084.22620, 1007.27612,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1067.80029, 1084.22620, 1007.27612,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1067.78870, 1081.21753, 1007.42102,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1073.03101, 1081.21753, 1007.42102,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1067.80029, 1080.28577, 1007.27612,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1067.78870, 1077.27466, 1007.42102,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1073.03101, 1077.27466, 1007.42102,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1073.02722, 1080.28577, 1007.27612,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1067.80029, 1076.35864, 1007.27612,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1073.02722, 1076.35864, 1007.27612,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1067.78870, 1073.34302, 1007.42102,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1073.03101, 1073.34302, 1007.42102,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1067.80029, 1072.41602, 1007.27612,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1073.02722, 1072.41602, 1007.27612,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1067.78870, 1073.34302, 1010.59998,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1067.80029, 1072.41602, 1010.77002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1067.80029, 1076.35864, 1010.77002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1067.78870, 1077.27466, 1010.59998,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1067.80029, 1080.28577, 1010.77002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1067.78870, 1081.21753, 1010.59998,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1067.80029, 1084.22620, 1010.77002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1073.02722, 1084.22620, 1010.77002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1073.03101, 1081.21753, 1010.59998,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1073.02722, 1080.28577, 1010.77002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1073.03101, 1077.27466, 1010.59998,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1073.02722, 1076.35864, 1010.77002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1073.03101, 1073.34302, 1010.59998,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1073.02722, 1072.41602, 1010.77002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1067.80029, 1072.41602, 1014.27002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1067.80029, 1076.35864, 1014.27002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1067.80029, 1080.28577, 1014.27002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1067.80029, 1084.22620, 1014.27002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1073.02722, 1072.41602, 1014.27002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1073.02722, 1076.35864, 1014.27002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1073.02722, 1080.28577, 1014.27002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1073.02722, 1084.22620, 1014.27002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1067.78870, 1073.34302, 1013.79999,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1067.78870, 1077.27466, 1013.79999,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1067.78870, 1081.21753, 1013.79999,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1073.03101, 1081.21753, 1013.79999,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1073.03101, 1077.27466, 1013.79999,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1073.03101, 1073.34302, 1013.79999,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1073.48376, 1085.72339, 1007.42102,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(19358, 1067.35767, 1085.72339, 1007.42102,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(19355, 1070.41992, 1085.70593, 1007.27612,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19358, 1067.35767, 1085.72339, 1010.59998,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(19358, 1073.48376, 1085.72339, 1010.59998,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(19358, 1067.35767, 1085.72339, 1013.79999,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(19358, 1073.48376, 1085.72339, 1013.79999,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(19355, 1070.41992, 1085.70593, 1010.77002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19355, 1070.41992, 1085.70593, 1014.27002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19385, 1071.33887, 1070.89465, 1009.03003,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19355, 1068.13306, 1070.89465, 1009.03003,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19355, 1067.21387, 1070.89465, 1012.53003,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19355, 1070.41626, 1070.89465, 1012.53003,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19355, 1073.61731, 1070.89465, 1012.53003,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19447, 1070.71118, 1071.51733, 1014.79999,   0.00000, 45.00000, 90.00000);
	CreateDynamicObject(19379, 1070.45142, 1086.11169, 1015.40002,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1070.45142, 1076.48218, 1015.40002,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1059.94373, 1071.46606, 1007.20001,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1059.94373, 1061.84509, 1007.20001,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1070.44287, 1061.84509, 1007.20001,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19361, 1074.53418, 1070.71484, 1009.03003,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19390, 1071.33887, 1070.71484, 1009.03003,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19453, 1065.05676, 1070.69836, 1009.03003,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19453, 1057.00220, 1065.93469, 1009.03003,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19390, 1058.64819, 1070.69836, 1009.03003,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19453, 1057.00220, 1056.30811, 1009.03003,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19377, 1059.94373, 1052.23267, 1007.20001,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1070.44287, 1052.23267, 1007.20001,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19453, 1072.15698, 1065.84705, 1009.03003,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19453, 1072.15698, 1056.24048, 1009.03003,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19453, 1061.65381, 1051.66248, 1009.03003,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14596, 1056.44373, 1071.86365, 1017.90002,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(14597, 1075.33020, 1068.35474, 1026.60999,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(19453, 1071.28638, 1051.66248, 1009.03003,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 1065.75574, 1070.67834, 1010.70001,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19447, 1065.70203, 1073.91882, 1019.46997,   0.00000, 0.00000, -9.00000);
	CreateDynamicObject(19447, 1065.69165, 1062.31641, 1019.46997,   0.00000, 0.00000, 9.00000);
	CreateDynamicObject(19447, 1062.79773, 1071.38269, 1022.79999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19447, 1064.41394, 1068.81604, 1018.00012,   0.00000, -65.50000, 0.00000);
	CreateDynamicObject(19447, 1062.54578, 1068.74329, 1021.25000,   0.00000, -65.50000, 0.00000);
	CreateDynamicObject(19355, 1063.32617, 1066.93494, 1019.46997,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19355, 1063.39734, 1069.28418, 1019.46997,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19447, 1062.72839, 1068.67725, 1021.50000,   0.00000, 90.50000, 0.00000);
	CreateDynamicObject(19459, 1064.19751, 1070.67859, 1010.70001,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 1075.38318, 1070.67834, 1011.52002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 1057.00244, 1065.93469, 1010.70001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19459, 1057.00244, 1056.30396, 1010.70001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19459, 1061.34033, 1051.67529, 1010.70001,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 1070.96191, 1051.67529, 1010.70001,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 1072.14307, 1065.99194, 1010.70001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19459, 1072.14307, 1056.37476, 1010.70001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19379, 1062.19946, 1065.77405, 1010.74969,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1072.69629, 1065.77405, 1010.74969,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1072.69629, 1056.15308, 1010.74969,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1062.19946, 1056.15308, 1010.74969,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19459, 1053.06494, 1070.67859, 1010.70001,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(16662, 1081.36536, 1067.80408, 1018.45001,   0.00000, 0.00000, -115.00000);
	CreateDynamicObject(16782, 1082.93103, 1068.22681, 1019.18127,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2009, 1069.09070, 1076.49756, 1024.61072,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1999, 1067.11340, 1075.50830, 1024.61133,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1806, 1065.82654, 1076.20239, 1024.61243,   0.00000, 0.00000, -113.00000);
	CreateDynamicObject(1806, 1068.55798, 1076.17639, 1024.61243,   0.00000, 0.00000, 69.00000);
	CreateDynamicObject(14632, 1086.41858, 1071.30798, 1026.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2167, 1073.43762, 1075.69019, 1024.59998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2167, 1073.43762, 1076.58972, 1024.59998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2167, 1073.43762, 1077.56946, 1024.59998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2167, 1073.43762, 1078.46960, 1024.59998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2167, 1073.38623, 1075.64856, 1024.59998,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2167, 1073.38623, 1076.53357, 1024.59998,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2167, 1073.38623, 1078.41626, 1024.59998,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2167, 1073.38623, 1077.50549, 1024.59998,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1703, 1083.98022, 1070.64624, 1024.61169,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1703, 1087.92493, 1069.28259, 1024.61169,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1703, 1086.07849, 1066.06738, 1024.61169,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1817, 1084.52954, 1067.77271, 1024.61670,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14643, 1074.37341, 1090.66492, 1008.33313,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14570, 1090.07922, 1071.16724, 1007.84998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1067.28174, 1080.22144, 1007.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19355, 1068.83899, 1081.73877, 1006.34998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1068.83899, 1084.94031, 1006.34998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19355, 1067.42676, 1081.70032, 1009.59998,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19355, 1067.42676, 1085.18701, 1009.59998,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(14570, 1073.65454, 1092.03088, 1007.84998,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19380, 1067.88110, 1084.98047, 1004.41803,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1502, 1057.86316, 1070.67932, 1007.28467,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1776, 1064.84338, 1070.23792, 1008.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2001, 1065.99194, 1070.14380, 1007.25000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2001, 1063.73535, 1070.14380, 1007.25000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2001, 1057.69556, 1070.14380, 1007.25000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1502, 1061.89233, 1067.35608, 1024.60510,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19385, 1061.92542, 1068.10107, 1026.34998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19385, 1061.05603, 1068.11426, 1020.56000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1502, 1061.10815, 1067.36133, 1018.80518,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1502, 1061.47412, 1067.37610, 1012.99573,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1502, 1070.55249, 1070.76526, 1007.28711,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2162, 1067.57434, 1081.95386, 1024.61084,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2002, 1069.13293, 1081.44531, 1024.61121,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2169, 1064.54419, 1081.44873, 1024.59998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2164, 1070.02234, 1081.93689, 1024.59998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1999, 1064.59131, 1060.67371, 1024.61133,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2009, 1070.95935, 1056.24487, 1024.61072,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1999, 1064.53125, 1058.18640, 1024.61133,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2164, 1067.66418, 1056.20850, 1024.59998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2164, 1067.61450, 1057.00830, 1024.59998,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2164, 1067.66418, 1057.99243, 1024.59998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2164, 1067.61450, 1058.78369, 1024.59998,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2162, 1071.44739, 1058.34827, 1024.61084,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2162, 1071.44739, 1060.17346, 1024.61084,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2169, 1065.57751, 1055.27979, 1024.59998,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(19447, 1065.67212, 1062.31213, 1020.90002,   0.00000, 0.00000, 9.00000);
	CreateDynamicObject(19447, 1065.68445, 1073.92847, 1020.90002,   0.00000, 0.00000, -9.00000);
	CreateDynamicObject(19355, 1063.38770, 1069.26660, 1020.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19355, 1063.36975, 1066.94702, 1020.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19428, 1064.12000, 1067.88733, 1021.20001,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19460, 1067.62280, 1069.26563, 1014.59998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19375, 1066.98413, 1065.25977, 1016.40002,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19460, 1072.26428, 1064.45032, 1014.59998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19460, 1062.86584, 1062.25781, 1014.59998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19460, 1067.37109, 1061.11792, 1014.59998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19378, 1068.10339, 1064.58252, 1012.91901,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(14895, 1077.71008, 1066.34460, 1019.70001,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2162, 1071.93811, 1055.88196, 1024.61060,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2162, 1071.93811, 1057.68701, 1024.61060,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2164, 1071.94324, 1059.62439, 1024.61255,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14850, 1077.56079, 1046.63696, 1006.09998,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(14455, 1072.01306, 1061.81982, 1014.59998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(5171, 1067.33618, 1065.17285, 1013.47998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(5171, 1071.79700, 1065.51184, 1013.47998,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(5171, 1065.15930, 1069.28271, 1013.47998,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(14455, 1063.62683, 1061.35974, 1014.59998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2608, 1071.84814, 1059.70276, 1008.50537,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2604, 1071.64026, 1062.69312, 1008.00000,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2200, 1057.21753, 1061.27930, 1007.28583,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2200, 1057.21753, 1059.05859, 1007.28583,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2200, 1057.21753, 1056.83838, 1007.28583,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2199, 1057.21753, 1063.51379, 1007.28583,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2164, 1071.44739, 1061.96912, 1024.61169,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2163, 1071.49023, 1075.99292, 1024.61279,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2163, 1071.49023, 1077.74609, 1024.61279,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1806, 1065.21814, 1061.32825, 1024.61243,   0.00000, 0.00000, 69.00000);
	CreateDynamicObject(1806, 1065.30310, 1058.19238, 1024.61243,   0.00000, 0.00000, 23.00000);
	CreateDynamicObject(1806, 1070.35974, 1056.14685, 1024.61243,   0.00000, 0.00000, 23.00000);
	CreateDynamicObject(1806, 1076.18018, 1056.74329, 1024.61243,   0.00000, 0.00000, -69.00000);
	CreateDynamicObject(1806, 1075.58081, 1060.88025, 1024.61243,   0.00000, 0.00000, 18.00000);
	CreateDynamicObject(1806, 1077.65039, 1060.10291, 1024.61243,   0.00000, 0.00000, 18.00000);
	CreateDynamicObject(2210, 1072.17908, 1062.13123, 1025.30005,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2610, 1075.23486, 1063.84387, 1025.40002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1755, 1057.64966, 1054.74426, 1007.28510,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1744, 1073.10730, 1084.59485, 1007.28497,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1744, 1073.10730, 1080.78381, 1007.28497,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1744, 1073.10730, 1076.86279, 1007.28497,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1744, 1073.10730, 1072.93628, 1007.28497,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(14461, 1061.98401, 1053.60535, 1009.50000,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1806, 1068.27307, 1062.50012, 1007.28668,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1806, 1068.19177, 1065.15710, 1007.28668,   0.00000, 0.00000, 98.00000);
	CreateDynamicObject(1806, 1068.12378, 1066.93372, 1007.28668,   0.00000, 0.00000, 25.00000);
	CreateDynamicObject(1806, 1065.86597, 1065.95142, 1007.28668,   0.00000, 0.00000, -171.00000);
	CreateDynamicObject(1806, 1063.53455, 1065.29431, 1007.28668,   0.00000, 0.00000, -76.00000);
	CreateDynamicObject(1806, 1060.69678, 1065.45117, 1007.28668,   0.00000, 0.00000, -149.00000);
	CreateDynamicObject(1806, 1062.09851, 1056.34570, 1007.28668,   0.00000, 0.00000, -149.00000);
	CreateDynamicObject(1806, 1064.05139, 1056.37927, 1007.28668,   0.00000, 0.00000, -33.00000);
	CreateDynamicObject(1806, 1066.50464, 1056.52112, 1007.28668,   0.00000, 0.00000, 69.00000);
	CreateDynamicObject(1806, 1066.72107, 1054.28149, 1007.28668,   0.00000, 0.00000, -76.00000);
	CreateDynamicObject(1806, 1068.81946, 1053.26782, 1007.28668,   0.00000, 0.00000, 84.00000);
	CreateDynamicObject(1806, 1070.97974, 1055.54553, 1007.28668,   0.00000, 0.00000, 193.00000);
	CreateDynamicObject(1760, 1060.84631, 1052.34778, 1007.28699,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1893, 1060.46313, 1056.13025, 1010.65411,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1065.45117, 1055.48413, 1010.65411,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1893, 1067.83582, 1053.23462, 1010.65411,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1893, 1069.88708, 1054.70215, 1010.65411,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1067.53564, 1063.66321, 1010.65411,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1067.87402, 1067.41431, 1010.65411,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1066.73315, 1067.29578, 1016.30865,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1066.73315, 1063.18542, 1016.30872,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1416, 1070.17920, 1071.68762, 1007.79999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1416, 1070.17920, 1073.10754, 1007.79999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1416, 1070.17920, 1074.52087, 1007.79999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1806, 1069.27063, 1072.62390, 1007.28778,   0.00000, 0.00000, 25.00000);
	CreateDynamicObject(1806, 1069.12732, 1074.33228, 1007.28778,   0.00000, 0.00000, -84.00000);
	CreateDynamicObject(2164, 1069.22253, 1071.01648, 1007.28619,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2202, 1064.15942, 1052.14807, 1007.28632,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2190, 1070.43164, 1074.35364, 1008.37842,   0.00000, 0.00000, -84.00000);
	CreateDynamicObject(2190, 1070.39673, 1073.03699, 1008.37842,   0.00000, 0.00000, -91.00000);
	CreateDynamicObject(640, 1068.24377, 1078.32886, 1012.50000,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(640, 1068.24377, 1082.25403, 1012.50000,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(640, 1068.24377, 1085.19116, 1012.50000,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(640, 1068.24377, 1074.39636, 1012.50000,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(640, 1072.56775, 1074.39636, 1012.50000,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(640, 1072.56775, 1078.32886, 1012.50000,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(640, 1072.56775, 1082.25403, 1012.50000,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(640, 1072.56775, 1085.19116, 1012.50000,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(2607, 1063.53503, 1066.13098, 1007.70001,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2605, 1061.02075, 1066.13098, 1007.70001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2605, 1068.18665, 1063.68115, 1007.70001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2607, 1065.91943, 1065.36133, 1007.70001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2605, 1067.65247, 1065.12500, 1007.70001,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2605, 1067.65247, 1067.08301, 1007.70001,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2605, 1068.25330, 1053.43103, 1007.70001,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2605, 1067.39258, 1054.40967, 1007.70001,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2605, 1066.30945, 1057.07422, 1007.70001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2605, 1064.21545, 1057.07422, 1007.70001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2605, 1062.17566, 1057.07422, 1007.70001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2607, 1070.96838, 1054.94250, 1007.70001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2607, 1071.53430, 1057.21814, 1007.70001,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1806, 1070.87854, 1056.68604, 1007.28668,   0.00000, 0.00000, 4.00000);
	CreateDynamicObject(1806, 1070.91785, 1063.12561, 1007.28668,   0.00000, 0.00000, -76.00000);
	CreateDynamicObject(2605, 1063.68823, 1054.46729, 1007.70001,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1806, 1063.39575, 1055.10339, 1007.28668,   0.00000, 0.00000, -156.00000);
	CreateDynamicObject(2605, 1061.58472, 1054.46729, 1007.70001,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1806, 1061.51416, 1055.16248, 1007.28668,   0.00000, 0.00000, -200.00000);
	CreateDynamicObject(2001, 1071.49988, 1064.98560, 1007.25000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2607, 1070.88354, 1052.47278, 1007.70001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1806, 1070.99219, 1053.19861, 1007.28668,   0.00000, 0.00000, 164.00000);
	CreateDynamicObject(2001, 1057.75244, 1052.35754, 1007.25000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2001, 1057.58289, 1064.91272, 1007.25000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1538, 1069.71130, 1085.55347, 1007.28546,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19440, 1058.41248, 1070.67896, 1010.57001,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2605, 1067.76367, 1059.89209, 1007.70001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2605, 1065.65771, 1059.89209, 1007.70001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1806, 1065.72229, 1059.21741, 1007.28668,   0.00000, 0.00000, 25.00000);
	CreateDynamicObject(1806, 1067.83435, 1059.41089, 1007.28668,   0.00000, 0.00000, 11.00000);
	CreateDynamicObject(2605, 1061.72815, 1058.55017, 1007.70001,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2605, 1061.72815, 1060.55029, 1007.70001,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2605, 1061.72815, 1062.57043, 1007.70001,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1806, 1062.33643, 1058.38049, 1007.28668,   0.00000, 0.00000, 25.00000);
	CreateDynamicObject(1806, 1062.36157, 1060.64331, 1007.28668,   0.00000, 0.00000, 113.00000);
	CreateDynamicObject(1806, 1062.22839, 1062.60413, 1007.28668,   0.00000, 0.00000, 91.00000);
	CreateDynamicObject(2607, 1064.03271, 1062.60876, 1007.70001,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2607, 1064.86487, 1062.63513, 1007.70001,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1806, 1065.32996, 1062.59631, 1007.28668,   0.00000, 0.00000, 91.00000);
	CreateDynamicObject(1806, 1067.00220, 1064.47070, 1007.28668,   0.00000, 0.00000, 91.00000);
	CreateDynamicObject(2202, 1068.27087, 1060.86340, 1007.28632,   0.00000, 0.00000, -180.00000);
	//==== MAYOR ====
	CreateDynamicObject(19377, 311.73651, 1629.58252, 1084.29761,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19379, 289.02151, 1628.29297, 1079.49084,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 299.49371, 1628.29297, 1079.49084,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 309.99249, 1628.29297, 1079.49084,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 309.99249, 1618.66248, 1079.49084,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 299.49371, 1618.66248, 1079.49084,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 289.02151, 1618.66248, 1079.49084,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 299.49371, 1609.02747, 1079.49084,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 309.99249, 1609.02747, 1079.49084,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 314.97095, 1621.55396, 1084.29761,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19377, 311.73645, 1613.47827, 1084.29761,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19377, 303.56491, 1632.99939, 1084.29761,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19377, 303.56491, 1610.08801, 1084.29761,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19377, 295.39651, 1629.60828, 1084.29761,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19377, 291.92819, 1621.55396, 1084.29761,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19379, 296.12665, 1628.78247, 1090.29761,   0.00000, 45.00000, -45.00000);
	CreateDynamicObject(19379, 303.58176, 1631.89832, 1090.29761,   0.00000, 45.00000, -90.00000);
	CreateDynamicObject(19379, 310.91165, 1628.85645, 1090.29761,   0.00000, -45.00000, 45.00000);
	CreateDynamicObject(19379, 303.53555, 1611.18835, 1090.29761,   0.00000, 45.00000, 90.00000);
	CreateDynamicObject(19379, 293.04758, 1621.53345, 1090.29761,   0.00000, -45.00000, 180.00000);
	CreateDynamicObject(19379, 313.87088, 1621.55774, 1090.29761,   0.00000, 45.00000, 180.00000);
	CreateDynamicObject(19379, 310.95044, 1614.24988, 1090.29761,   0.00000, -45.00000, -45.00000);
	CreateDynamicObject(19379, 296.12320, 1614.30798, 1090.29761,   0.00000, 45.00000, 45.00000);
	CreateDynamicObject(19377, 295.36649, 1613.46802, 1089.90002,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19391, 295.18210, 1613.81934, 1083.69995,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19377, 295.36652, 1613.46802, 1076.69995,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19377, 299.46982, 1609.34094, 1079.69995,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19377, 290.78891, 1618.02612, 1079.69995,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19379, 309.21063, 1616.14905, 1093.29761,   0.00000, 90.00000, -90.00000);
	CreateDynamicObject(19379, 309.23560, 1626.65149, 1093.29761,   0.00000, 90.00000, -90.00000);
	CreateDynamicObject(19379, 299.62888, 1626.64331, 1093.29761,   0.00000, 90.00000, -90.00000);
	CreateDynamicObject(19379, 299.58582, 1616.15320, 1093.29761,   0.00000, 90.00000, -90.00000);
	CreateDynamicObject(10145, 303.47449, 1620.95984, 1116.40002,   0.00000, 0.00000, -11.00000);
	CreateDynamicObject(19377, 298.91760, 1614.97156, 1076.50000,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19377, 292.12250, 1621.77563, 1076.50000,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19377, 293.70789, 1623.17896, 1076.19995,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19377, 300.49460, 1616.39148, 1076.19995,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19377, 308.77280, 1608.13342, 1076.19995,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19377, 297.57510, 1611.57495, 1076.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19362, 301.76379, 1610.94873, 1080.00000,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19379, 297.64670, 1608.93005, 1081.71997,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19379, 290.84720, 1615.73096, 1081.71997,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19362, 302.46268, 1609.28638, 1081.69995,   0.00000, 90.00000, -45.00000);
	CreateDynamicObject(19362, 302.72562, 1611.93750, 1079.69995,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19362, 302.67514, 1609.52185, 1081.30005,   0.00000, 90.00000, -45.00000);
	CreateDynamicObject(19362, 302.90829, 1609.77283, 1080.90002,   0.00000, 90.00000, -45.00000);
	CreateDynamicObject(19362, 303.24710, 1610.03491, 1080.50000,   0.00000, 90.00000, -45.00000);
	CreateDynamicObject(19362, 303.55109, 1610.38086, 1080.09998,   0.00000, 90.00000, -45.00000);
	CreateDynamicObject(19362, 303.96851, 1610.74512, 1079.69995,   0.00000, 90.00000, -45.00000);
	CreateDynamicObject(19377, 305.67267, 1608.22449, 1076.40002,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19377, 305.92615, 1608.40027, 1076.09998,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19377, 306.16205, 1608.64050, 1075.69995,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19377, 306.54581, 1608.87805, 1075.30005,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19377, 306.85818, 1609.21619, 1074.90002,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19377, 301.97055, 1608.01172, 1076.19995,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19379, 305.11469, 1604.46338, 1081.37500,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19379, 296.83643, 1612.73804, 1081.37500,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19379, 290.02451, 1619.55005, 1081.37500,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19362, 292.09830, 1621.18787, 1081.55005,   0.00000, 90.00000, -45.00000);
	CreateDynamicObject(19377, 302.03561, 1617.93787, 1075.69995,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19362, 304.30771, 1613.52002, 1079.19995,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19377, 295.23160, 1624.74500, 1075.69995,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19377, 303.35501, 1619.27808, 1075.19995,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19362, 305.61850, 1614.84802, 1078.69995,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19377, 296.54459, 1626.08997, 1075.19995,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19379, 298.36581, 1614.28857, 1080.88000,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19379, 291.55801, 1621.09595, 1080.88000,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19379, 292.87711, 1622.43005, 1080.37000,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19379, 299.69009, 1615.61914, 1080.37000,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19362, 292.24960, 1624.10583, 1081.04004,   0.00000, 90.00000, -45.00000);
	CreateDynamicObject(19362, 292.96509, 1626.15100, 1080.55005,   0.00000, 90.00000, -45.00000);
	CreateDynamicObject(19377, 308.31213, 1625.52979, 1076.19995,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19379, 311.98499, 1629.20459, 1081.37500,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19379, 316.48318, 1627.34900, 1081.37000,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19377, 304.94241, 1633.70447, 1076.19995,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(19377, 316.48050, 1622.16211, 1076.19995,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19379, 309.69608, 1634.15710, 1081.37000,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(2115, 306.17285, 1628.33545, 1081.46216,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(2115, 306.39941, 1628.56201, 1081.77002,   90.00000, 0.00000, -45.00000);
	CreateDynamicObject(2115, 307.79169, 1627.17004, 1081.77002,   90.00000, 0.00000, -45.00000);
	CreateDynamicObject(2115, 309.18399, 1625.78003, 1081.77002,   90.00000, 0.00000, -45.00000);
	CreateDynamicObject(2115, 310.56705, 1624.39587, 1081.77002,   90.00000, 0.00000, -45.00000);
	CreateDynamicObject(2115, 307.56903, 1626.93958, 1081.46216,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(2115, 308.95743, 1625.55347, 1081.46216,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(2115, 310.34286, 1624.16736, 1081.46216,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(1616, 293.45038, 1616.08777, 1086.88196,   0.00000, 0.00000, -135.00000);
	CreateDynamicObject(11245, 297.13510, 1615.65808, 1086.31787,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(11245, 297.51920, 1627.80579, 1086.31787,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(11245, 294.55615, 1621.59155, 1086.31787,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11245, 312.28778, 1621.51514, 1086.31787,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(11245, 309.67981, 1615.18030, 1086.31787,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(11245, 303.23492, 1612.83167, 1086.31787,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(11245, 303.60071, 1630.25146, 1086.31787,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(11245, 309.88370, 1627.64795, 1086.31787,   0.00000, 0.00000, -135.00000);
	CreateDynamicObject(19362, 313.31067, 1621.63916, 1079.40002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19362, 313.30515, 1621.03894, 1079.09998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19362, 313.27997, 1620.49109, 1078.80005,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19362, 313.30817, 1619.99622, 1078.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19362, 313.29825, 1619.48315, 1078.09998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19362, 311.72476, 1623.14526, 1079.40002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 311.69916, 1622.54529, 1079.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 311.70148, 1622.00061, 1078.80005,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 311.71014, 1621.50903, 1078.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 311.72000, 1621.00183, 1078.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 313.34839, 1623.33411, 1081.06104,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19362, 313.34628, 1622.74011, 1080.76099,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19362, 313.35846, 1622.18958, 1080.46106,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19362, 313.36652, 1621.70752, 1080.16101,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19362, 313.37778, 1621.18933, 1079.76099,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19461, 287.20593, 1612.50012, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19370, 293.95709, 1612.41968, 1081.96265,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19370, 293.54709, 1612.04102, 1082.14001,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19369, 293.08679, 1613.58618, 1084.00000,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19369, 294.82071, 1611.82385, 1084.00000,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19379, 289.85760, 1608.13623, 1082.18994,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19461, 297.08981, 1607.39587, 1084.00000,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19461, 294.43170, 1603.41187, 1084.00000,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19461, 291.45432, 1599.64600, 1084.00000,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19379, 299.47717, 1604.89697, 1082.18994,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19461, 284.65250, 1606.45239, 1084.00000,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19369, 279.71100, 1609.82349, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19369, 273.30450, 1609.82349, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19397, 276.51071, 1609.82349, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19397, 280.95291, 1612.50012, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19369, 277.75562, 1612.50012, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19369, 274.55780, 1612.50012, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19369, 271.35809, 1612.47632, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19379, 289.85760, 1597.64929, 1082.18994,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19379, 280.22000, 1608.13623, 1082.18994,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19379, 270.58801, 1608.13416, 1082.18994,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19379, 280.24063, 1618.63220, 1082.18994,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19379, 260.95801, 1608.13623, 1082.18994,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19397, 270.84610, 1611.09863, 1084.00000,   0.00000, 0.00000, 35.00000);
	CreateDynamicObject(19379, 280.22009, 1597.64929, 1082.18994,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19379, 270.58792, 1597.64917, 1082.18994,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19379, 260.95801, 1597.64929, 1082.18994,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19450, 261.87311, 1612.42139, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 255.72400, 1611.17517, 1084.00000,   0.00000, 0.00000, 105.00000);
	CreateDynamicObject(19447, 294.15497, 1593.75146, 1087.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 265.19800, 1612.42358, 1087.50000,   180.00000, 0.00000, 90.00000);
	CreateDynamicObject(2207, 271.70001, 1609.29590, 1082.19995,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2193, 276.13559, 1620.32666, 1082.26904,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2181, 279.39676, 1621.37805, 1082.27380,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2182, 283.10153, 1621.38306, 1082.27539,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1714, 311.25577, 1624.46301, 1081.45911,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(1714, 309.92947, 1625.82495, 1081.45911,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(1714, 308.49115, 1627.21973, 1081.45911,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(1714, 307.13632, 1628.58203, 1081.45911,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19358, 273.29971, 1609.81531, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19388, 270.84601, 1611.09595, 1084.00000,   0.00000, 0.00000, 35.00000);
	CreateDynamicObject(19388, 276.51099, 1609.81531, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19447, 276.69257, 1604.95569, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19458, 278.00671, 1604.95288, 1083.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19458, 278.00671, 1595.33203, 1083.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19458, 278.00671, 1604.95288, 1087.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19458, 278.00671, 1595.33203, 1087.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19447, 276.69260, 1595.32898, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19450, 276.51160, 1609.81445, 1087.50000,   180.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 268.99860, 1613.73157, 1087.50000,   180.00000, 0.00000, 35.00000);
	CreateDynamicObject(19447, 273.19110, 1604.95569, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 269.70551, 1604.95569, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 266.20700, 1604.95569, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 273.19110, 1595.32898, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 269.70551, 1595.32898, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 266.20700, 1595.32471, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19450, 276.56750, 1596.00110, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 263.79471, 1592.92578, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 255.72400, 1593.86487, 1084.00000,   0.00000, 0.00000, 73.75000);
	CreateDynamicObject(19447, 269.70551, 1614.57678, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 266.20700, 1614.57690, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(2208, 272.60001, 1604.73303, 1082.48999,   -90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2207, 271.70001, 1604.63953, 1082.19995,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2207, 271.70001, 1600.03748, 1082.19995,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2208, 272.60001, 1600.10266, 1082.48999,   -90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2208, 272.60001, 1595.49915, 1082.48999,   -90.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 268.41669, 1592.63025, 1084.00000,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(3858, 271.68384, 1602.58179, 1086.19995,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19447, 276.44470, 1611.59729, 1085.80005,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19450, 263.79471, 1592.92578, 1087.50000,   180.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 268.41669, 1592.63025, 1087.50000,   180.00000, 0.00000, -45.00000);
	CreateDynamicObject(19450, 276.56750, 1596.00110, 1087.50000,   180.00000, 0.00000, 90.00000);
	CreateDynamicObject(3437, 259.52261, 1608.48059, 1080.27490,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(3494, 271.68381, 1606.03455, 1084.80005,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19379, 251.33189, 1608.13623, 1082.18994,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19379, 251.33189, 1597.64929, 1082.18994,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19450, 252.56841, 1611.18604, 1084.00000,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19447, 249.20561, 1603.44653, 1087.58997,   0.00000, 45.00000, 0.00000);
	CreateDynamicObject(19447, 262.70578, 1603.44604, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 259.20810, 1603.44971, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 255.70461, 1603.44604, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 252.20087, 1603.44800, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 250.34607, 1608.88013, 1087.58997,   0.00000, 45.00000, -45.00000);
	CreateDynamicObject(19450, 255.72400, 1611.17517, 1087.50000,   180.00000, 0.00000, 105.00000);
	CreateDynamicObject(19447, 262.69986, 1613.07654, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19450, 271.69739, 1605.24097, 1087.50000,   180.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 271.69739, 1595.60889, 1087.50000,   180.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 252.56841, 1611.18604, 1087.50000,   180.00000, 0.00000, -45.00000);
	CreateDynamicObject(19450, 255.72400, 1593.86487, 1087.50000,   180.00000, 0.00000, 73.75000);
	CreateDynamicObject(19450, 249.15410, 1599.11914, 1087.50000,   180.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 249.15410, 1608.74670, 1087.50000,   180.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 253.61600, 1598.71521, 1087.50000,   180.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 253.61600, 1598.71521, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19447, 252.20090, 1613.07727, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 255.70461, 1613.07727, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 259.20810, 1613.07727, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(3494, 271.68381, 1601.43762, 1084.80005,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3494, 271.68381, 1596.76086, 1084.80005,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 259.25909, 1594.06091, 1087.50000,   180.00000, 0.00000, 11.00000);
	CreateDynamicObject(3437, 259.52261, 1601.09424, 1080.27490,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(3437, 258.42490, 1609.59766, 1079.00000,   0.00000, 0.00000, 35.00000);
	CreateDynamicObject(3437, 258.42490, 1599.90674, 1079.00000,   0.00000, 0.00000, -35.00000);
	CreateDynamicObject(3437, 255.96910, 1609.18530, 1078.00000,   0.00000, 0.00000, 62.00000);
	CreateDynamicObject(3437, 255.96910, 1600.43628, 1078.00000,   0.00000, 0.00000, -62.00000);
	CreateDynamicObject(19461, 275.55911, 1617.27808, 1084.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 284.66309, 1617.24988, 1084.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 280.13321, 1621.92542, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2193, 279.36853, 1617.08899, 1082.26904,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2193, 281.32648, 1618.05322, 1082.26904,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2193, 284.14233, 1614.05994, 1082.26904,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2182, 277.12955, 1613.14502, 1082.27539,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2193, 278.38589, 1616.12854, 1082.26904,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2193, 283.08038, 1619.43335, 1082.26904,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1491, 270.38101, 1611.72986, 1082.23999,   0.00000, 0.00000, -55.00000);
	CreateDynamicObject(19447, 253.71536, 1611.17688, 1087.58997,   0.00000, 45.00000, -62.00000);
	CreateDynamicObject(19447, 254.77242, 1610.86011, 1087.58997,   0.00000, -45.00000, 105.00000);
	CreateDynamicObject(19447, 258.75879, 1615.43213, 1090.90002,   45.00000, 0.00000, 13.00000);
	CreateDynamicObject(19447, 262.70581, 1593.82385, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 259.20810, 1593.81677, 1088.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(366, 275.64005, 1609.69336, 1083.57129,   0.00000, 43.00000, -185.00000);
	CreateDynamicObject(19450, 242.65999, 1605.74194, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 242.66000, 1601.51978, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 233.03729, 1601.51978, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 233.02721, 1605.74194, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19447, 242.66000, 1601.51978, 1080.52002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19447, 233.03729, 1601.51978, 1080.52002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19447, 233.02721, 1605.74194, 1080.52002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19447, 242.66000, 1605.74194, 1080.52002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19447, 246.57312, 1603.72144, 1080.52002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19447, 245.99519, 1603.67847, 1080.19995,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19447, 245.43652, 1603.78345, 1079.97998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19447, 244.88512, 1603.76282, 1079.76001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19447, 247.66434, 1603.09485, 1082.00000,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 247.10126, 1603.08643, 1081.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 246.54829, 1603.06628, 1081.57996,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 243.30090, 1602.85254, 1081.34998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 239.80130, 1602.72009, 1081.34998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 236.30124, 1602.74268, 1081.34998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 232.79958, 1602.72546, 1081.34998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19450, 247.39832, 1596.78784, 1084.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 243.99030, 1598.71521, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19447, 247.38760, 1602.81287, 1085.80005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19450, 250.82765, 1609.14026, 1084.00000,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19447, 246.11884, 1602.89819, 1085.80005,   0.00000, 75.00000, 0.00000);
	CreateDynamicObject(19447, 242.78011, 1603.19189, 1085.34998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 239.27823, 1603.22998, 1085.34998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 235.77818, 1603.30212, 1085.34998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 233.99930, 1603.32544, 1083.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19447, 233.99930, 1603.32544, 1086.59998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19369, 294.82071, 1611.82385, 1080.50000,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19369, 293.08679, 1613.58618, 1080.50000,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19447, 286.06329, 1611.59729, 1085.80005,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19447, 274.68079, 1614.07483, 1085.81995,   0.00000, 90.00000, -55.00000);
	CreateDynamicObject(19447, 286.06329, 1608.11621, 1085.80005,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19447, 286.06329, 1615.09814, 1085.80005,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19447, 286.06329, 1618.57642, 1085.80005,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19447, 286.06329, 1622.03589, 1085.80005,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19447, 276.44470, 1615.07520, 1085.80005,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19447, 276.44470, 1618.56079, 1085.80005,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19447, 276.44470, 1622.05054, 1085.80005,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19447, 294.38110, 1612.05432, 1085.80005,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19447, 291.87021, 1609.54492, 1085.81006,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19447, 289.40424, 1607.07776, 1085.81006,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19447, 286.93594, 1604.62463, 1085.81006,   0.00000, 90.00000, 45.00000);
	CreateDynamicObject(19447, 294.75250, 1603.14441, 1085.81006,   0.00000, 90.00000, -45.00000);
	CreateDynamicObject(1491, 280.17004, 1612.50439, 1082.23999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18014, 269.18683, 1594.97498, 1082.59998,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(18014, 264.26605, 1593.22290, 1085.59998,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(18014, 259.24496, 1595.58228, 1085.59998,   0.00000, 90.00000, 11.00000);
	CreateDynamicObject(3920, 264.40900, 1604.85742, 1087.70581,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2010, 255.93060, 1600.56970, 1083.86450,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2010, 258.39429, 1599.92517, 1084.86169,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2010, 259.56433, 1601.05786, 1086.14001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2010, 255.93181, 1609.13342, 1083.86475,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2010, 258.41199, 1609.53210, 1084.86670,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2010, 259.55582, 1608.44983, 1086.14099,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8853, 260.81979, 1604.49438, 1088.69995,   0.00000, 180.00000, 90.00000);
	CreateDynamicObject(3920, 251.64259, 1604.85742, 1087.70581,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3920, 251.07439, 1604.14246, 1087.70581,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(3920, 263.77469, 1604.14246, 1087.70581,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(19450, 259.25909, 1594.06091, 1084.00000,   0.00000, 0.00000, 11.00000);
	CreateDynamicObject(19165, 312.27951, 1614.14270, 1083.70752,   0.00000, 90.00000, 135.00000);
	CreateDynamicObject(19174, 309.91031, 1631.29358, 1083.72473,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19174, 313.77078, 1627.43494, 1083.72473,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19173, 314.88690, 1622.04333, 1083.10046,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19172, 302.51614, 1632.90698, 1082.62048,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19171, 310.07925, 1611.94141, 1083.68604,   0.00000, 90.00000, 135.00000);
	CreateDynamicObject(19168, 306.10596, 1610.15906, 1083.10400,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19166, 292.01779, 1620.71631, 1083.66650,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19165, 292.00845, 1623.53625, 1083.74902,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19168, 294.71445, 1628.81689, 1082.95715,   0.00000, 90.00000, -45.00000);
	CreateDynamicObject(19170, 296.63062, 1630.72864, 1082.61682,   0.00000, 90.00000, -45.00000);
	CreateDynamicObject(2894, 306.66373, 1628.09619, 1082.26282,   0.00000, 0.00000, -33.00000);
	CreateDynamicObject(1734, 290.49557, 1603.27368, 1085.70728,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1709, 296.49469, 1616.90393, 1081.75000,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(1710, 302.75256, 1613.11450, 1081.45776,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(1710, 298.78516, 1616.97363, 1081.45776,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(14629, 307.66849, 1619.39612, 1093.20288,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14629, 314.92926, 1641.41699, 1093.20288,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14622, 241.62480, 1587.08301, 1082.25000,   0.00000, 0.00000, 105.00000);
	CreateDynamicObject(14622, 235.09378, 1595.92346, 1082.25000,   0.00000, 0.00000, -105.00000);
	CreateDynamicObject(14622, 231.58490, 1593.32410, 1081.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14622, 231.58490, 1589.05542, 1081.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14591, 234.00075, 1601.87488, 1086.48987,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14591, 234.00070, 1599.98682, 1086.48987,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14487, 259.11816, 1598.75220, 1088.70325,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14487, 259.11819, 1610.15198, 1088.70325,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2621, 263.45221, 1598.42041, 1083.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2622, 266.83890, 1598.42041, 1083.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2373, 250.38881, 1598.56873, 1082.27490,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2372, 253.55968, 1599.56128, 1082.27563,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1804, 261.01260, 1596.90906, 1082.59998,   0.00000, 0.00000, 101.00000);
	CreateDynamicObject(1804, 261.57538, 1594.21191, 1082.59998,   0.00000, 0.00000, 101.00000);
	CreateDynamicObject(1804, 263.21725, 1595.18933, 1082.59998,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1804, 265.99438, 1595.25110, 1082.59998,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1808, 260.36353, 1601.10071, 1082.27576,   0.00000, 0.00000, 120.00000);
	CreateDynamicObject(2186, 273.44427, 1609.24597, 1082.27625,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2596, 272.27216, 1597.29224, 1085.64856,   0.00000, 0.00000, 127.00000);
	CreateDynamicObject(2816, 272.07968, 1598.29431, 1082.97632,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2828, 271.93652, 1604.20984, 1082.97522,   0.00000, 0.00000, -135.00000);
	CreateDynamicObject(2854, 272.19568, 1609.21545, 1082.97412,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14527, 274.10001, 1611.26318, 1083.31201,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1663, 272.84589, 1599.20801, 1082.69995,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1663, 273.13913, 1603.80054, 1082.69995,   0.00000, 0.00000, -76.00000);
	CreateDynamicObject(1663, 273.10910, 1608.19482, 1082.69995,   0.00000, 0.00000, -229.00000);
	CreateDynamicObject(1715, 303.60651, 1614.91370, 1080.96643,   0.00000, 0.00000, 156.00000);
	CreateDynamicObject(1715, 301.79700, 1616.70459, 1080.96643,   0.00000, 0.00000, 127.00000);
	CreateDynamicObject(1715, 300.35275, 1618.25146, 1080.96643,   0.00000, 0.00000, 131.00000);
	CreateDynamicObject(1715, 298.72729, 1619.86499, 1080.96643,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(1715, 296.99460, 1621.56274, 1080.96643,   0.00000, 0.00000, 149.00000);
	CreateDynamicObject(1715, 295.08572, 1623.53833, 1080.96643,   0.00000, 0.00000, 120.00000);
	CreateDynamicObject(2172, 284.08398, 1616.65979, 1082.27625,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2172, 276.09973, 1616.47766, 1082.27625,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2190, 271.84991, 1602.99878, 1082.97583,   0.00000, 0.00000, 120.00000);
	CreateDynamicObject(2190, 271.89230, 1600.00854, 1082.97583,   0.00000, 0.00000, 47.00000);
	CreateDynamicObject(2190, 271.70361, 1607.97754, 1082.97583,   0.00000, 0.00000, 91.00000);
	CreateDynamicObject(14527, 285.48389, 1611.26318, 1083.31201,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14527, 291.55121, 1609.39954, 1083.31201,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1491, 294.67999, 1614.42175, 1081.90002,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(1734, 293.35480, 1607.47485, 1085.70728,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1734, 279.73462, 1611.22290, 1085.70728,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1734, 286.73187, 1608.20667, 1085.70728,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2289, 270.05563, 1594.44678, 1084.41675,   0.00000, 0.00000, -135.00000);
	CreateDynamicObject(2286, 265.61319, 1612.30676, 1083.90381,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2282, 263.72275, 1611.82227, 1083.96899,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2274, 261.70624, 1611.81067, 1084.10730,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2267, 282.66510, 1608.59143, 1083.92773,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(2266, 284.57462, 1607.34827, 1083.84692,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(2265, 286.18399, 1605.73645, 1083.59070,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(2262, 288.13147, 1603.78479, 1083.64343,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(2260, 290.67014, 1601.23718, 1083.67371,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(2256, 292.39835, 1601.55750, 1083.89795,   0.00000, 0.00000, -135.00000);
	CreateDynamicObject(2257, 295.86383, 1605.00696, 1083.75293,   0.00000, 0.00000, -135.00000);
	CreateDynamicObject(2258, 296.78568, 1607.55347, 1083.69751,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(2260, 294.11548, 1609.56384, 1083.72241,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(14455, 277.89420, 1596.73914, 1083.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14455, 277.89420, 1602.58899, 1083.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3089, 234.10539, 1602.13806, 1082.69995,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3089, 234.10228, 1605.09998, 1082.69995,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19388, 268.28809, 1612.44263, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(9316, 265.42737, 1631.41052, 1084.27563,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 269.64551, 1617.25378, 1084.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 266.87833, 1617.35828, 1084.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(9316, 266.53046, 1621.88562, 1086.50000,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(19461, 269.64551, 1617.25378, 1087.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 266.88202, 1617.36646, 1087.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19379, 270.80475, 1618.63464, 1082.18994,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19461, 269.64551, 1626.86035, 1084.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 266.87830, 1626.99231, 1084.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 266.88812, 1625.19763, 1087.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 269.64551, 1626.88245, 1087.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 262.43564, 1629.91052, 1088.50000,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19461, 263.35931, 1633.02429, 1088.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 264.17453, 1628.80664, 1088.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19397, 268.76749, 1632.19006, 1088.50000,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19379, 265.11298, 1619.22034, 1089.21216,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 275.61261, 1619.22034, 1089.21216,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19461, 260.00775, 1619.19446, 1090.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 264.74353, 1614.47485, 1090.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19379, 275.59366, 1628.85205, 1089.21216,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19461, 274.37830, 1614.47485, 1090.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 284.01141, 1614.47485, 1090.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 280.71466, 1619.16443, 1090.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 280.71469, 1628.76855, 1090.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 275.82037, 1633.55090, 1090.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 271.06979, 1628.79041, 1090.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 259.45700, 1624.02258, 1090.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 264.17450, 1628.80664, 1092.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 266.88809, 1628.76965, 1091.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 269.66306, 1629.13806, 1089.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19447, 268.60107, 1617.10339, 1085.90002,   12.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 268.59476, 1625.32007, 1089.99902,   41.00000, 90.00000, 0.00000);
	CreateDynamicObject(1715, 305.65228, 1615.57239, 1080.45557,   0.00000, 0.00000, 142.00000);
	CreateDynamicObject(1715, 303.91571, 1617.26331, 1080.45557,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(1715, 302.23718, 1618.92188, 1080.45557,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(1715, 300.74850, 1620.38757, 1080.45557,   0.00000, 0.00000, 127.00000);
	CreateDynamicObject(1715, 299.11423, 1622.06238, 1080.45557,   0.00000, 0.00000, 127.00000);
	CreateDynamicObject(1715, 297.28201, 1623.86365, 1080.45557,   0.00000, 0.00000, 120.00000);
	CreateDynamicObject(3920, 266.54404, 1612.56226, 1087.70581,   11.00000, 0.00000, 180.00000);
	CreateDynamicObject(3920, 270.17905, 1612.24280, 1087.70581,   11.00000, 0.00000, 127.00000);
	CreateDynamicObject(3920, 271.70502, 1603.35254, 1087.70581,   11.00000, 0.00000, 90.00000);
	CreateDynamicObject(3920, 269.42130, 1593.33044, 1087.70581,   11.00000, 0.00000, 47.00000);
	CreateDynamicObject(3920, 262.31262, 1592.84692, 1087.70581,   11.00000, 0.00000, 0.00000);
	CreateDynamicObject(2190, 307.90848, 1626.28442, 1082.26221,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(2816, 307.68451, 1626.98694, 1082.26270,   0.00000, 0.00000, -40.00000);
	CreateDynamicObject(2854, 310.48422, 1624.00781, 1082.26099,   0.00000, 0.00000, 127.00000);
	CreateDynamicObject(3089, 267.53064, 1612.42542, 1083.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1491, 268.21381, 1632.71265, 1086.73657,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19447, 268.31650, 1629.30200, 1090.50000,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(2030, 290.98227, 1602.06702, 1082.69995,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1760, 294.46234, 1609.11462, 1082.27502,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(1760, 286.91202, 1604.99866, 1082.27502,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(1760, 284.51953, 1607.36743, 1082.27502,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(1755, 289.73145, 1602.31042, 1082.27795,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(1755, 293.13931, 1602.95935, 1082.27795,   0.00000, 0.00000, -135.00000);
	CreateDynamicObject(1760, 295.61087, 1605.40125, 1082.27502,   0.00000, 0.00000, -135.00000);
	CreateDynamicObject(1455, 290.37302, 1602.41113, 1083.17004,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1544, 290.40930, 1602.14758, 1083.09790,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1665, 291.38000, 1602.19958, 1083.10999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(633, 293.52859, 1609.90576, 1083.27502,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(633, 291.11273, 1611.89856, 1083.27502,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(638, 289.26865, 1611.98840, 1082.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(638, 286.34891, 1611.98840, 1082.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(638, 283.38910, 1611.98840, 1082.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(638, 290.79874, 1606.37781, 1082.90002,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(638, 288.91406, 1604.48267, 1082.90002,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(633, 296.27573, 1606.56018, 1083.27502,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(633, 293.35428, 1603.39429, 1083.27502,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2010, 291.28284, 1606.87964, 1082.30005,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2010, 288.83392, 1604.40002, 1082.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2011, 290.68216, 1606.19629, 1082.19995,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2011, 289.52466, 1605.14404, 1082.19995,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2853, 309.35339, 1625.12048, 1082.26160,   0.00000, 0.00000, -47.00000);
	CreateDynamicObject(3034, 234.12007, 1603.24390, 1082.09998,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(3034, 234.08946, 1604.14355, 1082.09998,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19174, 272.59683, 1606.00171, 1082.19995,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19174, 272.59680, 1601.16443, 1082.19995,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19174, 272.59680, 1596.47803, 1082.19995,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1491, 275.72949, 1609.81104, 1082.23999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1663, 283.56458, 1615.80994, 1082.69995,   0.00000, 0.00000, 50.00000);
	CreateDynamicObject(1663, 283.45929, 1613.69788, 1082.69995,   0.00000, 0.00000, 18.00000);
	CreateDynamicObject(1663, 283.45132, 1618.77698, 1082.69995,   0.00000, 0.00000, 127.00000);
	CreateDynamicObject(1663, 278.81323, 1615.53650, 1082.69995,   0.00000, 0.00000, 127.00000);
	CreateDynamicObject(1663, 276.90631, 1613.77014, 1082.69995,   0.00000, 0.00000, -76.00000);
	CreateDynamicObject(1663, 276.29019, 1617.16284, 1082.69995,   0.00000, 0.00000, -91.00000);
	CreateDynamicObject(1663, 276.77100, 1620.75818, 1082.69995,   0.00000, 0.00000, -185.00000);
	CreateDynamicObject(1663, 279.85132, 1620.96997, 1082.69995,   0.00000, 0.00000, -185.00000);
	CreateDynamicObject(1663, 283.59164, 1620.90515, 1082.69995,   0.00000, 0.00000, -222.00000);
	CreateDynamicObject(1663, 280.45129, 1617.46582, 1082.69995,   0.00000, 0.00000, 18.00000);
	CreateDynamicObject(1663, 278.93298, 1617.71216, 1082.69995,   0.00000, 0.00000, -33.00000);
	//=== HOSPITAL ===
	CreateDynamicObject(19461, 1152.97009, -1281.46863, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1152.97009, -1291.10327, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1152.97009, -1300.72595, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1173.43164, -1310.35803, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1173.43164, -1300.72595, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1173.43164, -1291.10327, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1173.43213, -1281.48865, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1173.43164, -1300.72595, 1005.79999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1173.43164, -1310.35803, 1005.79999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1169.29114, -1299.87183, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1160.74841, -1304.56763, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1169.29114, -1299.87183, 1005.79999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1160.74841, -1304.56763, 1005.79999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1160.74841, -1314.17664, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1160.74841, -1314.17664, 1005.79999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1168.80322, -1315.04492, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1159.17432, -1315.04492, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1165.55981, -1315.04492, 1005.79999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1175.18225, -1315.04492, 1005.79999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19378, 1155.57666, -1310.95642, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1155.57666, -1301.34619, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19397, 1160.74841, -1298.15686, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19378, 1166.07239, -1295.09827, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19461, 1164.02881, -1299.82947, 1005.79999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19378, 1166.07239, -1285.49316, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1166.07239, -1275.88538, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19397, 1160.74841, -1294.95605, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1155.94043, -1296.53015, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1155.99121, -1286.03589, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3857, 1160.75549, -1289.76697, 1001.09998,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19378, 1155.57666, -1290.74878, 1004.10498,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19362, 1153.03003, -1284.38354, 1002.45001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 1153.59998, -1284.38354, 1002.15002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 1154.17004, -1284.38354, 1001.84998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 1154.73999, -1284.38354, 1001.54999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 1155.31006, -1284.38354, 1001.25000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 1155.88000, -1284.38354, 1000.95001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 1156.44995, -1284.38354, 1000.65002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 1157.02002, -1284.38354, 1000.34998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 1157.58997, -1284.38354, 1000.04999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 1158.16003, -1284.38354, 999.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 1158.72998, -1284.38354, 999.45001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 1159.30005, -1284.38354, 999.15002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1154.73901, -1282.86902, 1000.00000,   0.50000, 0.00000, 90.00000);
	CreateDynamicObject(19370, 1157.63269, -1284.44666, 1000.82001,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19370, 1157.05261, -1284.48083, 1001.12000,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19370, 1156.49377, -1284.50244, 1001.41998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19370, 1155.91406, -1284.47632, 1001.71997,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19370, 1155.35425, -1284.41028, 1002.02002,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19370, 1154.77258, -1284.38806, 1002.32001,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19370, 1154.21387, -1284.42749, 1002.62000,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19370, 1153.63354, -1284.37793, 1002.91998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19370, 1153.07068, -1284.38708, 1003.21997,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19370, 1152.49158, -1284.38574, 1003.52002,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19370, 1151.92749, -1284.44531, 1003.82001,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1155.57666, -1310.95642, 1004.19995,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1155.57666, -1301.34619, 1004.19995,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1166.07239, -1295.09827, 1004.19995,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1166.07239, -1285.49316, 1004.19995,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1155.62195, -1290.51306, 1004.19995,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1155.57666, -1278.10474, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19461, 1154.00000, -1282.86694, 1005.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19379, 1147.19482, -1286.18579, 1004.19000,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1147.85278, -1286.39526, 1004.12000,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19461, 1163.63489, -1282.86694, 1005.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1149.22192, -1287.45044, 1005.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1168.34814, -1287.60669, 1005.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19378, 1156.56152, -1291.76294, 1004.10602,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1155.57666, -1291.71912, 1004.19952,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19461, 1148.21729, -1276.74121, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1168.66992, -1267.00525, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1173.43213, -1271.86365, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1159.05017, -1267.00525, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1130.18665, -1267.00525, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1131.85022, -1271.60657, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1131.85022, -1281.22803, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1144.12158, -1281.60950, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1146.87561, -1276.74194, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1134.44055, -1281.90540, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1127.71106, -1286.06995, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3857, 1169.72546, -1293.51245, 1001.09998,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19397, 1164.58032, -1298.25854, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19442, 1165.41309, -1293.55652, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19378, 1176.57019, -1295.09827, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1176.57019, -1285.49316, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1176.57019, -1275.88538, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1166.07239, -1266.25146, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1155.57666, -1268.48694, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1145.08569, -1278.10474, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1145.08569, -1268.48694, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1134.61597, -1268.48694, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1134.61597, -1278.10474, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1134.61597, -1287.72766, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1145.08569, -1287.72766, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19397, 1140.45605, -1276.74194, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19397, 1137.26233, -1276.74194, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19397, 1134.06091, -1276.74194, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1127.67139, -1276.74194, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19378, 1176.57019, -1266.25146, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19461, 1168.34851, -1295.03979, 1005.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1162.70227, -1299.16675, 1005.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1157.94910, -1303.89966, 1005.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1145.87488, -1290.84326, 1005.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1150.59729, -1295.68030, 1005.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1150.59729, -1308.49756, 1005.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19397, 1150.59729, -1302.08716, 1005.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1157.96094, -1313.52576, 1005.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1154.74451, -1313.23792, 1005.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19397, 1152.21289, -1303.58484, 1005.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3857, 1156.88550, -1303.54871, 1007.09998,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19379, 1145.08240, -1301.34619, 1004.20001,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19461, 1145.80054, -1306.06628, 1005.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1145.78271, -1296.69482, 1005.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1141.14270, -1301.32361, 1005.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3857, 1162.94177, -1270.33105, 1001.09998,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(3857, 1169.86255, -1274.00586, 1001.09998,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19397, 1164.52539, -1273.98914, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19378, 1153.74268, -1287.55212, 1007.72998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1164.23584, -1287.55212, 1007.72998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1164.23584, -1297.17871, 1007.72998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1153.74268, -1297.17871, 1007.72998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1154.82275, -1306.80334, 1007.72998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1144.32520, -1301.37915, 1007.73090,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1154.82275, -1316.43604, 1007.72998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1162.54626, -1301.49255, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1166.07996, -1301.49255, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1169.00000, 6137.00000, -1301.49255,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1169.61365, -1301.49255, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1173.14746, -1301.49255, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1162.53943, -1304.74597, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1162.53943, -1307.99939, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1162.53943, -1311.25281, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1162.53943, -1314.50623, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1166.07996, -1304.74597, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1169.61365, -1304.74597, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1173.14746, -1304.74597, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1166.07996, -1307.99939, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1169.61365, -1307.99939, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1173.14746, -1307.99939, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1166.07996, -1311.25281, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1169.61365, -1311.25281, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1173.14746, -1311.25281, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1166.07996, -1314.50623, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1169.61365, -1314.50623, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19357, 1173.14746, -1314.50623, 1006.00720,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(2885, 1166.13757, -1313.26331, 1006.25958,   -90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2885, 1176.93469, -1313.26331, 1006.25958,   -90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19071, 1190.82776, -1315.02368, 998.00000,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19461, 1175.13403, -1314.45898, 1000.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1165.50061, -1314.45898, 1000.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1174.83179, -1314.45898, 1006.56500,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(19461, 1172.82556, -1314.45496, 1006.56500,   180.00000, 0.00000, -90.00000);
	CreateDynamicObject(19461, 1163.19702, -1314.45496, 1006.56500,   180.00000, 0.00000, -90.00000);
	CreateDynamicObject(19380, 1165.80920, -1319.27881, 1002.58002,   -11.00000, 90.00000, 0.00000);
	CreateDynamicObject(19071, 1190.72778, -1314.97156, 999.00000,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(3383, 1154.59851, -1288.80017, 1000.55573,   0.00000, 0.00000, -98.00000);
	CreateDynamicObject(19381, 1166.01965, -1304.76550, 1006.01001,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19381, 1166.01965, -1314.39465, 1006.01001,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19381, 1176.51270, -1314.39465, 1006.01001,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19381, 1176.51270, -1304.76550, 1006.01001,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(3657, 1172.93103, -1305.75305, 1001.00000,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3657, 1172.93103, -1301.91052, 1001.00000,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3657, 1168.20886, -1300.36218, 1001.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2308, 1154.53784, -1282.29700, 1000.55688,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2198, 1153.55603, -1279.22974, 1000.55621,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2185, 1155.96411, -1282.41870, 1000.55688,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19397, 1152.62952, -1267.00525, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19442, 1150.22644, -1267.00525, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19397, 1147.82178, -1267.00525, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19442, 1145.42224, -1267.00525, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19397, 1143.00903, -1267.00525, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19442, 1140.60449, -1267.00525, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19397, 1138.21021, -1267.00525, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19442, 1135.80103, -1267.00525, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1137.67603, -1257.54944, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1147.30725, -1257.54944, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1156.93359, -1257.54944, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1153.46033, -1262.12817, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1134.04077, -1262.23804, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1139.04480, -1262.19775, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1143.83508, -1262.15259, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1148.64795, -1262.17542, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19378, 1148.35925, -1258.85498, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19378, 1137.86938, -1258.85498, 1004.09998,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(3383, 1166.66077, -1295.43689, 1000.55573,   0.00000, 0.00000, -142.00000);
	CreateDynamicObject(3383, 1172.32825, -1296.10083, 1000.55573,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2184, 1162.94995, -1312.71375, 1000.55548,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(2184, 1164.81702, -1310.34009, 1000.55548,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2184, 1164.45300, -1307.34619, 1000.55548,   0.00000, 0.00000, 135.00000);
	CreateDynamicObject(2183, 1168.23328, -1272.54614, 1000.55853,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2182, 1171.89319, -1267.57434, 1000.55438,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2181, 1169.70142, -1267.54639, 1000.55731,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2181, 1167.28113, -1267.54639, 1000.55731,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2181, 1164.82776, -1267.54639, 1000.55731,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2174, 1132.44495, -1275.21863, 1000.55652,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2174, 1132.44495, -1270.04358, 1000.55603,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2171, 1132.44495, -1272.39832, 1000.55603,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2169, 1155.10535, -1295.98950, 1000.55627,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2165, 1157.84070, -1295.99658, 1000.55652,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(3387, 1170.05542, -1299.40173, 1000.55713,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3388, 1169.05566, -1299.40173, 1000.55682,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3386, 1168.06482, -1299.40173, 1000.55713,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19071, 1160.81604, -1329.90173, 999.00000,   180.00000, 90.00000, 0.00000);
	CreateDynamicObject(19071, 1160.77625, -1329.79651, 998.00000,   180.00000, 90.00000, 0.00000);
	CreateDynamicObject(19461, 1161.30798, -1304.71252, 1000.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1161.30798, -1314.32910, 1000.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19442, 1160.66077, -1299.82703, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1161.34814, -1304.71008, 1006.56500,   180.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1161.36804, -1314.32910, 1006.56500,   180.00000, 0.00000, 0.00000);
	CreateDynamicObject(19380, 1176.30823, -1319.27881, 1002.58002,   -11.00000, 90.00000, 0.00000);
	CreateDynamicObject(19380, 1156.51782, -1304.98987, 1002.58002,   -11.00000, 90.00000, -90.00000);
	CreateDynamicObject(19380, 1156.51782, -1315.48022, 1002.58002,   -11.00000, 90.00000, -90.00000);
	CreateDynamicObject(19461, 1165.79871, -1316.17468, 1005.29999,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19461, 1175.42859, -1316.17468, 1005.29999,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19461, 1159.65833, -1304.68787, 1005.29999,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19461, 1159.65833, -1314.30701, 1005.29999,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(1337, 1172.77649, -1308.41797, 1001.19000,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1334, 1135.56030, -1284.32129, 1001.66998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1139.31982, -1281.53040, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1136.39331, -1281.47559, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1334, 1132.73340, -1280.34558, 1001.66998,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1330, 1153.56592, -1280.16687, 1000.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1558, 1132.46973, -1277.43799, 1000.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1558, 1132.48132, -1278.62793, 1000.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1172.33582, -1299.16675, 1005.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14455, 1151.87891, -1313.16162, 1005.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14632, 1166.34155, -1314.60620, 1004.14001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2610, 1150.99780, -1310.73767, 1005.09998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2610, 1150.99780, -1310.23718, 1005.09998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2610, 1150.99780, -1309.73621, 1005.09998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2610, 1150.99780, -1309.23889, 1005.09998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2610, 1150.99780, -1308.73511, 1005.09998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2610, 1150.99780, -1308.23718, 1005.09998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2610, 1173.04236, -1269.74036, 1001.40002,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2610, 1173.04236, -1270.24316, 1001.40002,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2610, 1173.04236, -1270.74365, 1001.40002,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2610, 1173.04236, -1271.24255, 1001.40002,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2610, 1153.33521, -1293.93689, 1001.40002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2610, 1157.46521, -1286.43323, 1001.40002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2610, 1157.96350, -1286.43323, 1001.40002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2610, 1158.46313, -1286.43323, 1001.40002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2608, 1150.89697, -1305.78247, 1005.35101,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2608, 1154.65894, -1296.23938, 1002.50000,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2604, 1159.86292, -1289.45483, 1001.29999,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2574, 1149.58728, -1258.10962, 1000.55542,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2574, 1144.65894, -1258.13330, 1000.55542,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2574, 1139.83240, -1258.10681, 1000.55542,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2574, 1134.83752, -1258.10120, 1000.55542,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2451, 1142.67651, -1297.47302, 1004.28491,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2419, 1145.70288, -1297.47302, 1004.28558,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2418, 1148.12659, -1297.47302, 1004.28607,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2341, 1141.66638, -1305.51990, 1004.28381,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(3383, 1142.81604, -1301.36646, 1004.28412,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3383, 1145.77930, -1301.36646, 1004.28412,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3383, 1148.52063, -1301.36646, 1004.28412,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2199, 1153.13379, -1292.41382, 1000.55750,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2167, 1160.00757, -1296.50122, 1000.55670,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2167, 1158.96606, -1296.50122, 1000.55670,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1893, 1165.80322, -1283.78442, 1004.00745,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1165.80322, -1279.39746, 1004.00739,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1155.74133, -1279.39746, 1004.00739,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1155.17505, -1272.15491, 1004.00739,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1148.19849, -1272.15491, 1004.00739,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1138.76086, -1272.15491, 1004.00739,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1167.69495, -1270.62695, 1004.00739,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1135.89917, -1263.35645, 1004.00739,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1141.09338, -1263.35645, 1004.00739,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1145.84058, -1263.35645, 1004.00739,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1150.55859, -1263.35645, 1004.00739,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 1157.12598, -1295.30408, 1001.15002,   0.00000, 0.00000, 69.00000);
	CreateDynamicObject(1811, 1159.06165, -1288.95776, 1001.15002,   0.00000, 0.00000, -178.00000);
	CreateDynamicObject(1811, 1163.31348, -1309.34875, 1001.15002,   0.00000, 0.00000, -193.00000);
	CreateDynamicObject(14481, 1137.04065, -1280.78894, 1002.70001,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2828, 1163.56885, -1311.59119, 1001.32849,   0.00000, 0.00000, 25.00000);
	CreateDynamicObject(2827, 1162.93811, -1306.34802, 1001.33020,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2826, 1163.83215, -1307.11487, 1001.33014,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2813, 1164.36353, -1310.21802, 1001.32904,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1147.04419, -1278.39819, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2738, 1143.55066, -1277.54456, 1001.00000,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2718, 1141.31018, -1303.76025, 1006.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2718, 1141.31018, -1299.61377, 1006.90002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2526, 1136.98621, -1281.28491, 1000.55511,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2524, 1138.73792, -1279.95789, 1000.55518,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1569, 1173.32092, -1312.25171, 1000.55658,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1569, 1173.31494, -1309.26099, 1000.55658,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1523, 1160.80322, -1295.70862, 1000.55768,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1523, 1164.61255, -1299.01013, 1000.55768,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1171.56934, -1288.04590, 1002.29999,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(19461, 1171.57117, -1281.35156, 1002.29999,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(1502, 1142.22766, -1267.02075, 1000.55585,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1491, 1163.75134, -1274.00903, 1000.55695,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2924, 1172.85620, -1279.97620, 1001.70001,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(2924, 1170.45496, -1282.38672, 1001.70001,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(2949, 1160.78296, -1298.87439, 1000.55811,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1502, 1147.03418, -1267.02075, 1000.55579,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1502, 1151.84119, -1267.02075, 1000.55579,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1502, 1137.42432, -1267.02075, 1000.55579,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1523, 1133.27344, -1276.76746, 1000.55768,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1491, 1136.47839, -1276.76746, 1000.55688,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1491, 1139.67737, -1276.76746, 1000.55688,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1491, 1142.32642, -1278.33069, 1000.55688,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1147.04419, -1280.05933, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1491, 1142.32642, -1279.99023, 1000.55688,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1491, 1142.32642, -1281.64966, 1000.55688,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1147.04419, -1281.72009, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1491, 1142.32642, -1283.31287, 1000.55688,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1144.20398, -1283.40002, 1002.29999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2738, 1143.55066, -1279.28564, 1001.00000,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2738, 1143.55066, -1280.86682, 1001.00000,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2738, 1143.55066, -1282.54333, 1001.00000,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2524, 1138.73792, -1279.05151, 1000.55518,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1893, 1161.64014, -1297.78137, 1007.63617,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1161.64014, -1286.48096, 1007.63623,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1153.66711, -1297.63269, 1007.63623,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1893, 1153.80774, -1308.43176, 1007.63623,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1893, 1145.92334, -1301.92578, 1007.63623,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1523, 1150.63782, -1302.83179, 1004.28741,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1523, 1151.42102, -1303.63867, 1004.28741,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19377, 1175.13330, -1315.02649, 1001.66412,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19377, 1165.50818, -1315.02649, 1001.66412,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19377, 1160.75867, -1304.64575, 1001.66412,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19377, 1160.75867, -1314.26892, 1001.66412,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19454, 1160.65747, -1281.50769, 26.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19454, 1154.48169, -1282.84998, 1002.29999,   26.50000, 0.00000, 90.00000);
	CreateDynamicObject(1796, 1143.00940, -1264.02954, 1000.55676,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1796, 1142.62781, -1260.55566, 1000.55682,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1796, 1142.62781, -1262.75061, 1000.55682,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1796, 1142.62781, -1264.97693, 1000.55682,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2145, 1139.34790, -1263.75488, 998.40002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2145, 1139.34790, -1261.52979, 998.40002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2145, 1139.34790, -1259.33447, 998.40002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2145, 1143.53113, -1260.29224, 998.40002,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1796, 1134.84888, -1263.46838, 1000.55682,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1796, 1135.47302, -1262.75061, 1000.55682,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1796, 1135.47302, -1260.55566, 1000.55682,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1796, 1147.42896, -1264.97693, 1000.55682,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2145, 1135.57190, -1266.73608, 998.40002,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2145, 1138.74719, -1262.03198, 998.40002,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2145, 1138.74719, -1259.83826, 998.40002,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1997, 1149.86169, -1283.97363, 1004.28656,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1808, 1169.49097, -1286.39136, 1000.55481,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(2146, 1170.65491, -1288.00647, 1001.03998,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(1997, 1172.75916, -1275.54248, 1000.55640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2146, 1171.67236, -1277.24829, 1001.03998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2146, 1171.67236, -1278.45947, 1001.03998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1997, 1156.78418, -1279.33899, 1000.55640,   0.00000, 0.00000, -149.00000);
	CreateDynamicObject(1811, 1157.11230, -1281.43213, 1001.15002,   0.00000, 0.00000, -193.00000);
	CreateDynamicObject(1811, 1154.13086, -1278.55957, 1001.15002,   0.00000, 0.00000, 11.00000);
	CreateDynamicObject(1722, 1157.81128, -1305.53381, 1004.28607,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1722, 1157.81128, -1304.75867, 1004.28607,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1722, 1150.76794, -1304.20520, 1004.28607,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1808, 1150.06238, -1290.59644, 1004.28290,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(14532, 1166.72729, -1299.26306, 1001.53003,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14532, 1165.40784, -1299.26465, 1001.53003,   0.00000, 0.00000, -25.00000);
	CreateDynamicObject(14532, 1169.98242, -1294.33679, 1001.53003,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2131, 1144.88770, -1305.49023, 1004.28632,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2340, 1146.37585, -1305.49756, 1004.28699,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2340, 1148.02576, -1305.49756, 1004.28699,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2523, 1150.37817, -1305.48669, 1004.28778,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1796, 1152.25012, -1265.37732, 1000.55682,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1796, 1147.46729, -1262.75061, 1000.55682,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1796, 1149.89417, -1262.75061, 1000.55682,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1796, 1149.89417, -1260.45190, 1000.55682,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1796, 1145.10205, -1260.16187, 1000.55682,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2145, 1144.17224, -1263.46033, 998.40002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2145, 1144.17224, -1265.68286, 998.40002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2145, 1148.32764, -1261.39246, 998.40002,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2145, 1153.17468, -1259.72913, 998.40002,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2145, 1153.17468, -1262.03247, 998.40002,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2145, 1148.97607, -1264.15588, 998.40002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2161, 1151.87964, -1276.64868, 1000.55518,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2161, 1150.55920, -1276.64868, 1000.55518,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2161, 1149.23523, -1276.64868, 1000.55518,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2161, 1147.91406, -1276.64868, 1000.55518,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2161, 1146.60095, -1276.64868, 1000.55518,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2162, 1151.87964, -1276.64868, 1001.90997,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2161, 1150.11792, -1276.64868, 1001.90002,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2161, 1148.81641, -1276.64868, 1001.90002,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2161, 1147.49707, -1276.64868, 1001.90002,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2163, 1131.95203, -1269.97083, 1002.56189,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2164, 1133.54456, -1267.12817, 1000.55609,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2167, 1135.33472, -1267.12817, 1000.55652,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 1165.44995, -1268.06409, 1001.15002,   0.00000, 0.00000, -55.00000);
	CreateDynamicObject(1811, 1167.69202, -1267.78162, 1001.15002,   0.00000, 0.00000, -98.00000);
	CreateDynamicObject(1811, 1170.15503, -1268.28406, 1001.15002,   0.00000, 0.00000, -105.00000);
	CreateDynamicObject(2392, 1135.82507, -1280.82336, 1003.59998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2392, 1135.82507, -1279.50403, 1003.59998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2392, 1135.82507, -1278.51050, 1003.59998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2392, 1134.68372, -1279.50403, 1003.59998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2182, 1158.39282, -1272.61499, 1000.55621,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2181, 1159.39978, -1267.59045, 1000.55688,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2172, 1157.38928, -1270.57678, 1000.55713,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2193, 1157.37036, -1268.59875, 1000.55487,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2198, 1161.35083, -1267.60327, 1000.55554,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1811, 1161.98633, -1268.56665, 1001.15002,   0.00000, 0.00000, -84.00000);
	CreateDynamicObject(1811, 1159.93555, -1268.05432, 1001.15002,   0.00000, 0.00000, -96.00000);
	CreateDynamicObject(1811, 1158.24219, -1268.55176, 1001.15002,   0.00000, 0.00000, -69.00000);
	CreateDynamicObject(1811, 1158.36975, -1270.93628, 1001.15002,   0.00000, 0.00000, 76.00000);
	CreateDynamicObject(19461, 1156.87134, -1268.29321, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1893, 1159.76709, -1270.92285, 1004.00739,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1760, 1156.25061, -1267.71521, 1000.55530,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1760, 1156.25061, -1270.70044, 1000.55530,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1616, 1172.93323, -1313.19299, 1004.68951,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2448, 1166.32983, -1285.49036, 1004.28546,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2446, 1165.34167, -1285.46033, 1004.28552,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2446, 1164.34204, -1285.46033, 1004.28552,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2446, 1163.34998, -1285.46033, 1004.28552,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2543, 1167.76758, -1284.68433, 1004.28607,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2542, 1165.32983, -1283.43579, 1004.28998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2543, 1167.76758, -1283.66016, 1004.28607,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2541, 1166.32251, -1283.43579, 1004.28766,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19435, 1160.90039, -1284.20386, 1004.95599,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19435, 1159.24377, -1286.02576, 1004.95599,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1154.73950, -1282.84900, 1000.00000,   0.50000, 0.00000, 90.00000);
	CreateDynamicObject(2146, 1164.47559, -1285.63440, 1001.03998,   0.00000, 0.00000, 4.00000);
	CreateDynamicObject(2146, 1165.11206, -1287.65442, 1001.03998,   0.00000, 0.00000, -76.00000);
	CreateDynamicObject(2146, 1145.54761, -1267.94141, 1001.03998,   0.00000, 0.00000, -84.00000);
	CreateDynamicObject(1997, 1135.22961, -1269.35498, 1000.55640,   0.00000, 0.00000, -149.00000);
	CreateDynamicObject(2146, 1144.09473, -1276.09668, 1001.03998,   0.00000, 0.00000, -91.00000);
	CreateDynamicObject(2146, 1161.93274, -1272.31348, 1001.03998,   0.00000, 0.00000, -171.00000);
	CreateDynamicObject(1997, 1162.62744, -1277.38745, 1000.55640,   0.00000, 0.00000, -127.00000);
	CreateDynamicObject(2685, 1137.24890, -1276.65710, 1003.25000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1731, 1173.20032, -1312.83936, 1002.11023,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1731, 1173.20032, -1308.79199, 1002.11023,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1731, 1173.20032, -1303.80383, 1002.11023,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1731, 1165.50671, -1300.12622, 1002.11023,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1731, 1160.98193, -1296.60754, 1002.11023,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1731, 1160.95007, -1286.04358, 1002.11023,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(19442, 1164.58032, -1295.85498, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19442, 1164.58032, -1294.27014, 1002.29999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1731, 1165.40137, -1293.31104, 1002.11023,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3383, 1165.84424, -1271.48010, 998.09998,   0.00000, 0.00000, -98.00000);
	CreateDynamicObject(3383, 1171.51965, -1271.55884, 998.09998,   0.00000, 0.00000, -98.00000);
	CreateDynamicObject(3383, 1143.25830, -1281.93982, 998.09998,   0.00000, 0.00000, -185.00000);
	CreateDynamicObject(8710, 1176.96387, -1290.25623, 970.84003,   0.00000, -90.00000, 0.00000);
	CreateDynamicObject(19379, 1153.82739, -1262.11011, 1000.50000,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1143.34448, -1262.11011, 1000.50000,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1132.84302, -1262.11011, 1000.50000,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(1432, 1165.69385, -1288.15320, 1004.34998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1432, 1165.69385, -1291.71021, 1004.34998,   0.00000, 0.00000, -55.00000);
	CreateDynamicObject(1432, 1165.69385, -1296.11279, 1004.34998,   0.00000, 0.00000, 40.00000);
	CreateDynamicObject(1432, 1161.16968, -1288.15320, 1004.34998,   0.00000, 0.00000, 62.00000);
	CreateDynamicObject(1432, 1161.16968, -1291.71021, 1004.34998,   0.00000, 0.00000, 120.00000);
	CreateDynamicObject(1432, 1161.16968, -1296.11279, 1004.34998,   0.00000, 0.00000, 62.00000);
	//=== News
	CreateDynamicObject(19379, 1238.04578, -971.15283, 1083.91821,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19071, 1232.49353, -998.97314, 1081.99048,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1248.54700, -971.15277, 1083.91821,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1248.54700, -961.52979, 1083.91821,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19071, 1237.35828, -998.96674, 1081.99048,   0.00000, 90.00000, 180.00000);
	CreateDynamicObject(19450, 1235.67627, -975.44714, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1233.03577, -973.61285, 1083.00476,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1228.30530, -968.88055, 1083.00476,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1236.83081, -973.61292, 1083.00476,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1241.56506, -968.88062, 1083.00476,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 1242.12427, -968.87317, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 1227.68201, -968.87323, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19447, 1232.42041, -973.77838, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19447, 1237.41553, -973.77838, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1236.83081, -973.61292, 1088.00476,   180.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1241.56506, -968.88062, 1088.00476,   180.00000, 0.00000, 90.00000);
	CreateDynamicObject(19461, 1233.03577, -973.61292, 1088.00476,   180.00000, 0.00000, 0.00000);
	CreateDynamicObject(19461, 1228.30530, -968.88062, 1088.00476,   180.00000, 0.00000, 90.00000);
	CreateDynamicObject(19380, 1242.09546, -973.75903, 1084.48438,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19380, 1227.75183, -973.71002, 1084.48438,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19447, 1228.18054, -975.41376, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19447, 1241.67505, -975.41382, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19379, 1238.04578, -961.52979, 1083.91821,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19446, 1236.34998, -974.04657, 1087.50000,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19446, 1236.69409, -970.54315, 1087.50000,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19450, 1239.08899, -956.96143, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 1226.27087, -956.96136, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19388, 1232.67383, -956.96143, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19379, 1227.55066, -961.52979, 1083.91821,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1227.54736, -971.15277, 1083.91821,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19450, 1228.34070, -961.71136, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19388, 1228.34070, -968.13312, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1240.57202, -969.29651, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1240.57202, -956.50348, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1218.05579, -968.87323, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 1216.64917, -956.96143, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19379, 1217.07690, -961.52979, 1083.91821,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1217.05798, -971.15277, 1083.91821,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19450, 1208.43103, -968.87323, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 1207.03589, -956.96143, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19358, 1238.90320, -961.22931, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19431, 1237.38232, -960.43829, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19379, 1238.04578, -951.91040, 1083.91821,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1227.54468, -951.89038, 1083.91821,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1259.03577, -961.52979, 1083.91821,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1259.03577, -971.15277, 1083.91821,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19450, 1248.72083, -956.96143, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 1258.34998, -956.96143, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 1251.74841, -968.87323, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 1261.37695, -968.87323, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 1258.75354, -961.92993, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1258.75354, -971.53748, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19388, 1240.57202, -962.89191, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1212.18372, -961.64899, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1212.18372, -971.28320, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1223.46118, -952.07660, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1240.10181, -952.07660, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19379, 1227.54468, -942.26709, 1083.91821,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 1238.04578, -942.26709, 1083.91821,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19450, 1231.14490, -947.32495, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1808, 1231.29065, -968.59790, 1084.00183,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2186, 1241.07800, -959.92493, 1084.00195,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2186, 1245.85144, -957.49640, 1084.00195,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2186, 1249.98889, -957.49371, 1084.00195,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2186, 1253.70667, -957.48694, 1084.00195,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2186, 1253.37646, -965.85132, 1084.00195,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2186, 1247.33276, -967.56189, 1084.00195,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2186, 1258.21509, -963.69208, 1084.00195,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2239, 1213.40894, -958.08453, 1083.99524,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2239, 1216.81104, -958.65900, 1083.99524,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(2239, 1216.81104, -966.36530, 1083.99524,   0.00000, 0.00000, -135.00000);
	CreateDynamicObject(2239, 1213.40894, -966.74030, 1083.99524,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(3963, 1212.34631, -964.40088, 1085.37231,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3962, 1212.38550, -961.53430, 1085.42053,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2262, 1228.90833, -966.35400, 1085.87830,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2263, 1228.93506, -964.76819, 1086.15613,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2264, 1228.93933, -963.42035, 1086.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2265, 1228.91504, -961.73358, 1085.85999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2261, 1228.93420, -959.79907, 1086.05811,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2260, 1230.18091, -957.51825, 1085.99231,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19327, 1235.13953, -964.72302, 1085.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19358, 1235.03528, -964.67224, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19328, 1234.93591, -963.83612, 1085.12268,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19329, 1235.13684, -964.37689, 1086.22156,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19167, 1240.47607, -964.81610, 1085.50000,   0.00000, 90.00000, 180.00000);
	CreateDynamicObject(19165, 1240.49634, -966.45038, 1086.59998,   90.00000, 90.00000, 180.00000);
	CreateDynamicObject(19173, 1240.47388, -966.18915, 1085.50000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19169, 1240.48645, -968.03857, 1084.90002,   0.00000, 90.00000, 180.00000);
	CreateDynamicObject(19171, 1240.49426, -968.01367, 1086.59998,   0.00000, 90.00000, 180.00000);
	CreateDynamicObject(19174, 1240.48584, -965.91522, 1084.33826,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19450, 1220.33081, -959.35577, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19388, 1220.33081, -965.76514, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1220.33081, -972.16998, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1221.51746, -947.32501, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19388, 1237.55566, -947.32501, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 1243.96692, -947.32501, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 1242.52441, -942.59381, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1222.72534, -942.61890, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1229.27563, -939.27307, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19388, 1229.27563, -945.67621, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1224.46289, -942.18756, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 1234.09741, -937.94916, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19450, 1243.71948, -937.94922, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19368, 1229.21472, -942.46887, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19396, 1229.21472, -945.67621, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19368, 1227.61560, -942.23846, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19368, 1224.40454, -942.23853, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19368, 1227.62830, -947.20361, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19368, 1224.41968, -947.20361, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19368, 1222.80591, -945.56311, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19368, 1222.80591, -942.36377, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 1212.23486, -964.01752, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 1212.23486, -960.81818, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(16378, 1226.00024, -960.37079, 1084.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1226.66650, -964.66809, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19431, 1224.26208, -964.66809, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(16154, 1256.04602, -960.23688, 1084.00354,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14640, 1228.18115, -941.26001, 1083.69995,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(14632, 1249.51074, -959.20667, 1084.30005,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14455, 1242.26404, -946.54480, 1085.40002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14455, 1243.18140, -938.19128, 1085.40002,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(9362, 1234.13855, -944.52472, 1084.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(5171, 1239.36572, -943.14093, 1084.44995,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2610, 1229.70117, -940.07648, 1084.80005,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2610, 1229.70117, -940.57098, 1084.80005,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2610, 1229.70117, -941.07068, 1084.80005,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2610, 1229.70117, -941.57123, 1084.80005,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2610, 1229.70117, -942.07239, 1084.80005,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2610, 1229.70117, -942.57318, 1084.80005,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2606, 1223.63855, -949.33807, 1086.50000,   11.00000, 0.00000, 90.00000);
	CreateDynamicObject(2606, 1223.63855, -951.41162, 1086.50000,   11.00000, 0.00000, 90.00000);
	CreateDynamicObject(2606, 1223.63855, -953.49707, 1086.50000,   11.00000, 0.00000, 90.00000);
	CreateDynamicObject(2606, 1223.63855, -953.49707, 1085.90002,   5.00000, 0.00000, 90.00000);
	CreateDynamicObject(2606, 1223.63855, -951.41162, 1085.90002,   5.00000, 0.00000, 90.00000);
	CreateDynamicObject(2606, 1223.63855, -949.33807, 1085.90002,   5.00000, 0.00000, 90.00000);
	CreateDynamicObject(2604, 1225.58057, -956.39008, 1084.65002,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2199, 1225.40601, -947.45935, 1084.00183,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2604, 1223.99915, -950.30176, 1084.65002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2163, 1223.49060, -953.46698, 1084.00159,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2163, 1223.49060, -955.21057, 1084.00159,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2162, 1228.83447, -956.87103, 1084.00330,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2161, 1230.67651, -956.88177, 1084.00049,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2161, 1230.67651, -956.88177, 1085.34998,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2024, 1232.08228, -941.48987, 1084.00244,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1758, 1229.86353, -939.31818, 1084.00281,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1742, 1236.08679, -957.00684, 1084.00366,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(14461, 1256.81494, -964.11481, 1086.03271,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14489, 1223.71606, -932.29376, 1085.90002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14742, 1217.93091, -939.73853, 1085.44421,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14860, 1226.09888, -942.75836, 1085.49377,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(14860, 1225.91931, -946.03516, 1085.49377,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1761, 1231.48315, -938.54773, 1084.00220,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2256, 1242.42542, -939.88562, 1085.90002,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3864, 1220.03308, -961.95630, 1081.30005,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3872, 1209.51978, -960.93579, 1082.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2600, 1218.14441, -959.72058, 1084.50000,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(2600, 1218.13049, -966.08630, 1084.50000,   0.00000, 0.00000, -135.00000);
	CreateDynamicObject(1215, 1217.92859, -965.87994, 1085.19995,   0.00000, 90.00000, 135.00000);
	CreateDynamicObject(1215, 1217.92798, -959.93835, 1085.19995,   0.00000, 90.00000, -135.00000);
	CreateDynamicObject(642, 1215.11719, -967.60394, 1084.00415,   -47.00000, 0.00000, 0.00000);
	CreateDynamicObject(642, 1219.77625, -963.04553, 1084.00415,   -47.00000, 0.00000, 90.00000);
	CreateDynamicObject(642, 1215.21558, -958.39240, 1084.00415,   -47.00000, 0.00000, 180.00000);
	CreateDynamicObject(2111, 1213.44873, -962.39252, 1084.40002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1702, 1215.34253, -964.80212, 1084.00549,   0.00000, 0.00000, 149.00000);
	CreateDynamicObject(1755, 1213.93518, -961.60846, 1084.00439,   0.00000, 0.00000, 33.00000);
	CreateDynamicObject(2162, 1238.44031, -956.91010, 1084.00330,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2161, 1239.97327, -954.22705, 1084.00049,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2161, 1239.97327, -952.73932, 1084.00049,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2163, 1240.02917, -950.49170, 1084.00159,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2163, 1240.02917, -950.49170, 1084.90002,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1742, 1240.15479, -948.66235, 1084.00366,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2200, 1227.10461, -947.51343, 1083.99878,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2204, 1230.76489, -947.44501, 1084.00024,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2199, 1233.87012, -947.45575, 1084.00220,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2197, 1229.19983, -948.73621, 1084.00500,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2197, 1229.88049, -948.73621, 1084.00500,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14895, 1237.86145, -958.41107, 1079.05005,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1244.51428, -956.62653, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1248.56470, -956.62653, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1252.52356, -956.62653, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14895, 1244.14612, -966.00763, 1079.05005,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1254.81824, -968.95117, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1250.79810, -968.95117, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19450, 1246.79236, -968.95117, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2166, 1227.29065, -951.37933, 1084.00354,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2166, 1228.31250, -953.34344, 1084.00354,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2165, 1229.25256, -950.39435, 1084.00488,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2165, 1231.23218, -950.39429, 1084.00488,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2165, 1233.21460, -950.39429, 1084.00488,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2165, 1235.19434, -950.39429, 1084.00488,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14834, 1232.08655, -968.12927, 1084.19995,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14834, 1237.78271, -968.12927, 1084.19995,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14834, 1231.27258, -957.59821, 1084.19995,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14834, 1236.13367, -947.88568, 1084.19995,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14834, 1238.97070, -947.88568, 1084.19995,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(14834, 1229.87097, -943.92346, 1084.19995,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(14834, 1224.10840, -947.91199, 1084.19995,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2356, 1249.41956, -965.97473, 1084.00488,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2356, 1249.58423, -968.06396, 1084.00488,   0.00000, 0.00000, 44.00000);
	CreateDynamicObject(2356, 1253.21350, -967.94092, 1084.00488,   0.00000, 0.00000, -4.00000);
	CreateDynamicObject(2356, 1256.04980, -967.94177, 1084.00488,   0.00000, 0.00000, 47.00000);
	CreateDynamicObject(2356, 1256.24292, -966.27716, 1084.00488,   0.00000, 0.00000, -47.00000);
	CreateDynamicObject(2356, 1249.83948, -960.60663, 1084.00488,   0.00000, 0.00000, 43.00000);
	CreateDynamicObject(2356, 1250.06726, -958.49744, 1084.00488,   0.00000, 0.00000, 113.00000);
	CreateDynamicObject(2356, 1247.32031, -960.22192, 1084.00488,   0.00000, 0.00000, 25.00000);
	CreateDynamicObject(2356, 1243.25769, -958.41803, 1084.00488,   0.00000, 0.00000, 25.00000);
	CreateDynamicObject(2356, 1242.75256, -960.52765, 1084.00488,   0.00000, 0.00000, -76.00000);
	CreateDynamicObject(2356, 1235.76965, -951.15143, 1084.00488,   0.00000, 0.00000, -76.00000);
	CreateDynamicObject(2356, 1234.07788, -951.15259, 1084.00488,   0.00000, 0.00000, 11.00000);
	CreateDynamicObject(2356, 1232.13049, -951.23242, 1084.00488,   0.00000, 0.00000, -11.00000);
	CreateDynamicObject(2356, 1230.33984, -951.11304, 1084.00488,   0.00000, 0.00000, 62.00000);
	CreateDynamicObject(2356, 1228.10425, -951.46307, 1084.00488,   0.00000, 0.00000, 62.00000);
	CreateDynamicObject(2356, 1224.80908, -951.02692, 1084.00488,   0.00000, 0.00000, 62.00000);
	CreateDynamicObject(2356, 1224.61646, -948.91089, 1084.00488,   0.00000, 0.00000, 171.00000);
	CreateDynamicObject(2356, 1225.82410, -955.58783, 1084.00488,   0.00000, 0.00000, 273.00000);
	CreateDynamicObject(2356, 1224.41211, -955.87048, 1084.00488,   0.00000, 0.00000, 185.00000);
	CreateDynamicObject(2496, 1234.91052, -964.74847, 1085.00000,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2499, 1234.95398, -965.32166, 1086.19995,   -30.00000, 0.00000, 90.00000);
	CreateDynamicObject(2495, 1234.99170, -963.81299, 1086.59497,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2491, 1229.13013, -966.33606, 1084.00269,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2484, 1228.18213, -946.93323, 1085.65002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 1236.83606, -960.09918, 1084.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 1235.91345, -960.09918, 1084.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 1234.98999, -960.09918, 1084.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 1234.06189, -960.09918, 1084.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1886, 1218.14941, -966.15546, 1084.88171,   180.00000, 0.00000, 45.00000);
	CreateDynamicObject(1886, 1218.23193, -959.68213, 1084.88171,   180.00000, 0.00000, 135.00000);
	CreateDynamicObject(14487, 1235.05298, -944.23486, 1087.12231,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14487, 1250.01196, -959.14020, 1087.12231,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14487, 1249.24976, -966.82257, 1087.12231,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1616, 1237.26086, -957.45923, 1087.30005,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(18006, 1223.34229, -959.63898, 1085.63916,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19388, 1221.87000, -964.66809, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14487, 1224.03992, -936.97144, 1087.12231,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14487, 1246.45850, -936.97137, 1087.12231,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14487, 1218.28040, -936.29736, 1087.12231,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19377, 1238.54163, -963.97729, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1228.04675, -963.97729, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1217.56018, -963.97729, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1207.06970, -963.97729, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1207.06970, -954.35468, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1217.56018, -954.35468, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1228.04675, -954.35468, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1238.54163, -954.35468, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1249.02478, -963.97729, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1259.51172, -963.97729, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1259.51172, -954.35468, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1249.02478, -954.35468, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1238.54163, -944.72070, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1238.54163, -935.09711, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1228.04492, -935.09711, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 1228.04492, -944.72070, 1087.55005,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(2948, 1233.97839, -975.39911, 1084.00000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2948, 1235.88953, -975.39441, 1084.00000,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1502, 1240.57202, -963.64142, 1083.97998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1502, 1231.88611, -956.96143, 1083.97998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1502, 1236.77271, -947.32501, 1083.97998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1502, 1229.27563, -946.42572, 1083.97998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1502, 1228.34070, -968.87579, 1083.97998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1502, 1220.33081, -966.51672, 1083.97998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1502, 1221.08533, -964.66809, 1083.97998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14762, 1258.64465, -965.64758, 1085.73547,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(14762, 1239.97986, -954.35999, 1085.73547,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(14762, 1222.00684, -947.09021, 1085.59998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1742, 1224.24548, -947.25946, 1084.00403,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1703, 1226.80835, -942.85358, 1084.00537,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1964, 1224.56250, -944.68018, 1084.94995,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2115, 1224.77478, -945.57880, 1084.00574,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2287, 1228.25232, -942.78809, 1086.13525,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2286, 1224.09119, -942.34369, 1085.93909,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14705, 1213.52173, -962.33173, 1084.98999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2332, 1223.37476, -942.67059, 1084.45996,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2190, 1224.74939, -945.48083, 1084.80664,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2190, 1235.82922, -960.36267, 1085.05371,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2190, 1234.16980, -960.31946, 1085.05371,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2201, 1236.67346, -960.18506, 1085.05408,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2607, 1239.53015, -958.45093, 1084.40002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19358, 1240.08508, -958.60114, 1085.75000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19358, 1239.09937, -959.85760, 1085.75000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2356, 1236.27332, -959.04468, 1084.00488,   0.00000, 0.00000, -215.00000);
	CreateDynamicObject(2356, 1234.42908, -959.10583, 1084.00488,   0.00000, 0.00000, -142.00000);
	CreateDynamicObject(2309, 1223.97046, -945.53760, 1084.00623,   0.00000, 0.00000, -55.00000);
	CreateDynamicObject(2209, 1227.44360, -947.10419, 1084.00500,   0.00000, 0.00000, 0.00000);
	//=== CNN ======
	CreateDynamicObject(4113,1536.7390137,946.8060303,45.7900009,0.0000000,0.0000000,102.0000000); //object(lanofficeblok1) (1)
	CreateDynamicObject(9697,1523.1309814,1020.8519897,9.8350000,0.0000000,0.2300110,90.0000000); //object(carspaces3_sfw) (1)
	CreateDynamicObject(9697,1552.3659668,1019.8419800,9.8350000,0.0000000,359.7699890,270.0000000); //object(carspaces3_sfw) (2)
	CreateDynamicObject(1412,1557.4980469,1012.4130249,11.0939999,0.0000000,0.0000000,270.0000000); //object(dyn_mesh_2) (1)
	CreateDynamicObject(1412,1557.4859619,1007.2189941,11.0939999,0.0000000,0.0000000,270.0000000); //object(dyn_mesh_2) (2)
	CreateDynamicObject(1412,1557.4919434,1001.9680176,11.0939999,0.0000000,0.0000000,270.0000000); //object(dyn_mesh_2) (3)
	CreateDynamicObject(1412,1557.4949951,996.7910156,11.0939999,0.0000000,0.0000000,270.0000000); //object(dyn_mesh_2) (4)
	CreateDynamicObject(1412,1557.4930420,991.6199951,11.0939999,0.0000000,0.0000000,270.0000000); //object(dyn_mesh_2) (5)
	CreateDynamicObject(1412,1557.5090332,986.4420166,11.0939999,0.0000000,0.0000000,270.0000000); //object(dyn_mesh_2) (6)
	CreateDynamicObject(1412,1557.5080566,981.1970215,11.0939999,0.0000000,0.0000000,270.0000000); //object(dyn_mesh_2) (7)
	CreateDynamicObject(1412,1557.5109863,975.9559937,11.0939999,0.0000000,0.0000000,270.0000000); //object(dyn_mesh_2) (8)
	CreateDynamicObject(1412,1557.5030518,970.7030029,11.0939999,0.0000000,0.0000000,270.0000000); //object(dyn_mesh_2) (9)
	CreateDynamicObject(1412,1557.5000000,965.4169922,11.0939999,0.0000000,0.0000000,270.0000000); //object(dyn_mesh_2) (10)
	CreateDynamicObject(1412,1555.4840088,961.1820068,11.0939999,0.0000000,0.0000000,38.0000000); //object(dyn_mesh_2) (11)
	CreateDynamicObject(1412,1550.5300293,959.4219971,11.0939999,0.0000000,0.0000000,1.9962158); //object(dyn_mesh_2) (12)
	CreateDynamicObject(1569,1527.4339600,961.7169800,9.7799997,0.0000000,0.0000000,356.0000000); //object(adam_v_door) (1)
	CreateDynamicObject(1569,1545.1250000,932.6179810,9.8199997,0.0000000,0.0000000,49.2500000); //object(adam_v_door) (2)
	CreateDynamicObject(3763,1536.3199463,930.6420288,115.0100021,0.0000000,0.0000000,0.0000000); //object(ce_radarmast3) (1)
	CreateDynamicObject(3244,1533.5539551,886.6040039,9.8199997,0.0000000,0.0000000,0.0000000); //object(pylon_big1_) (1)
	CreateDynamicObject(3107,1549.1719971,962.9589844,81.8209991,0.0000000,0.0000000,0.0000000); //object(wongs_erection2) (1)
	CreateDynamicObject(3030,1522.5739746,964.9669800,81.8209991,0.0000000,0.0000000,0.0000000); //object(wongs_erection) (1)
	CreateDynamicObject(16003,1544.4570312,938.7680054,83.5439987,0.0000000,0.0000000,134.0000000); //object(drvin_ticket) (1)
	//=== CNN ===
	new news_map_obj[12]; // ?????????? ??? ???????? ?????????

	// ??? ? ?????????
	news_map_obj[0] = CreateDynamicObject(19377, 2040.17297, -1308.45544, 1536.23853,   0.00000, -90.00000, 0.00000);
	CreateDynamicObject(19377, 2050.65942, -1308.45544, 1536.23853,   0.00000, -90.00000, 0.00000);
	CreateDynamicObject(19377, 2040.17297, -1318.06079, 1536.23853,   0.00000, -90.00000, 0.00000);
	CreateDynamicObject(19377, 2050.65942, -1318.06079, 1536.23853,   0.00000, -90.00000, 0.00000);
	CreateDynamicObject(19377, 2061.15723, -1318.06079, 1536.23853,   0.00000, -90.00000, 0.00000);
	news_map_obj[1] = CreateDynamicObject(19377, 2061.15723, -1308.45544, 1536.23853,   0.00000, -90.00000, 0.00000);

	for(new i=news_map_obj[0]; i<=news_map_obj[1]; i++) {
	SetDynamicObjectMaterial(i, 0, 14847, "mp_policesf", "mp_cop_floor", 0); }

	// ????? ? ???????
	news_map_obj[2] = CreateDynamicObject(19456, 2035.52551, -1310.29272, 1538.07251,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 2034.94666, -1305.47180, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19456, 2035.47888, -1303.97412, 1538.07251,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19364, 2040.27356, -1305.54016, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19456, 2033.99402, -1305.59229, 1537.36353,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19456, 2037.96509, -1300.95923, 1537.56250,   0.00000, 0.00000, 0.00000);
	news_map_obj[3] = CreateDynamicObject(19393, 2040.27356, -1308.73694, 1538.07251,   0.00000, 0.00000, 0.00000);

	for(new i=news_map_obj[2]; i<=news_map_obj[3]; i++) {
	SetDynamicObjectMaterial(i, 0, 18020, "genintintfastb2", "Bow_sub_walltiles", 0); }

	// ????? ? ???? ??? ???????????
	news_map_obj[4] = CreateDynamicObject(19453, 2058.70117, -1322.78967, 1538.07251,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19453, 2068.31665, -1322.78967, 1538.07251,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19453, 2066.25000, -1318.06079, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19453, 2058.34570, -1306.98804, 1538.07251,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19453, 2053.84912, -1311.82007, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 2066.25000, -1308.50537, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 2053.84912, -1318.20276, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 2066.25000, -1311.67139, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19361, 2064.75977, -1306.98804, 1540.58105,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19455, 2034.91260, -1318.06079, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19455, 2034.91260, -1308.45544, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19455, 2039.72827, -1322.83496, 1538.07251,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19455, 2049.33228, -1322.83496, 1538.07251,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19363, 2036.51379, -1318.89722, 1538.07251,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19363, 2039.19421, -1317.78857, 1538.07251,   0.00000, 0.00000, -45.00000);
	CreateDynamicObject(19392, 2040.30164, -1315.10999, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19363, 2040.30164, -1311.93945, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19392, 2040.30164, -1308.73694, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19363, 2040.30164, -1305.54016, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19392, 2044.30164, -1315.10999, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19455, 2044.30164, -1308.70825, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19455, 2039.50012, -1303.92725, 1538.07251,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19455, 2049.03125, -1316.62695, 1538.07251,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19455, 2053.84106, -1311.82007, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19455, 2049.06274, -1307.03931, 1538.07251,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19392, 2053.84106, -1321.38916, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19455, 2035.50513, -1310.35242, 1538.07251,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19363, 2053.84106, -1318.20276, 1538.07251,   0.00000, 0.00000, 0.00000);
	news_map_obj[5] = CreateDynamicObject(19390, 2053.84912, -1321.38916, 1538.07251,   0.00000, 0.00000, 0.00000);

	for(new i=news_map_obj[4]; i<=news_map_obj[5]; i++) {
	SetDynamicObjectMaterial(i, 0, 14847, "mp_policesf", "mp_cop_ceiling", 0); }

	// ????? ? ????????
	news_map_obj[6] = CreateDynamicObject(19365, 2050.13574, -1314.95081, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19365, 2048.61865, -1313.43298, 1538.07251,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19365, 2047.10107, -1314.95081, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19394, 2044.32959, -1315.10999, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19457, 2049.09204, -1316.56165, 1538.07251,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19457, 2044.32959, -1308.70825, 1538.07251,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19457, 2049.06274, -1307.06726, 1538.07251,   0.00000, 0.00000, 90.00000);
	news_map_obj[7] = CreateDynamicObject(19457, 2053.81299, -1311.82007, 1538.07251,   0.00000, 0.00000, 0.00000);

	for(new i=news_map_obj[6]; i<=news_map_obj[7]; i++) {
	SetDynamicObjectMaterial(i, 0, 14595, "papaerchaseoffice", "wall_stone6_256", 0); }

	// ???????
	news_map_obj[8] = CreateDynamicObject(19378, 2040.17297, -1308.45544, 1539.90564,   0.00000, -90.00000, 0.00000);
	CreateDynamicObject(19378, 2040.17297, -1318.06079, 1539.90564,   0.00000, -90.00000, 0.00000);
	CreateDynamicObject(19378, 2050.65942, -1308.45544, 1539.90564,   0.00000, -90.00000, 0.00000);
	CreateDynamicObject(19378, 2050.65942, -1318.06079, 1539.90564,   0.00000, -90.00000, 0.00000);
	CreateDynamicObject(19378, 2061.15723, -1318.06079, 1539.90564,   0.00000, -90.00000, 0.00000);
	news_map_obj[9] = CreateDynamicObject(19378, 2061.15723, -1308.45544, 1539.90564,   0.00000, -90.00000, 0.00000);

	for(new i=news_map_obj[8]; i<=news_map_obj[9]; i++) {
	SetDynamicObjectMaterial(i, 0, 14847, "mp_policesf", "mp_cop_floor2", 0); }

	news_map_obj[10] = CreateDynamicObject(19362, 2064.55762, -1317.20605, 1537.56860,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 2064.55762, -1314.00403, 1537.56860,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19362, 2063.45020, -1311.32507, 1537.56860,   0.00000, 0.00000, 45.00000);
	news_map_obj[11] = CreateDynamicObject(19362, 2063.44824, -1319.88660, 1537.56860,   0.00000, 0.00000, -45.00000);

	for(new i=news_map_obj[10]; i<=news_map_obj[11]; i++) {
	SetDynamicObjectMaterial(i, 0, 14847, "mp_policesf", "mp_cop_ceiling", 0xFFFFFFFF); }

	CreateDynamicObject(3031, 2055.88599, -1318.63501, 1537.76526,   0.00000, 0.00000, 20.00000);
	CreateDynamicObject(2894, 2056.34521, -1312.89575, 1537.13049,   0.00000, 0.00000, 70.00000);
	CreateDynamicObject(2256, 2064.45361, -1315.58813, 1538.15161,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1702, 2063.36108, -1317.07031, 1536.32068,   0.00000, 0.00000, -100.00000);
	CreateDynamicObject(1702, 2063.01050, -1312.10498, 1536.32068,   0.00000, 0.00000, -80.00000);
	CreateDynamicObject(1702, 2063.39233, -1314.58191, 1536.32068,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3274, 2054.19897, -1319.23462, 1534.30164,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3274, 2057.28809, -1307.77551, 1534.30164,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1663, 2055.14087, -1312.22351, 1536.77075,   0.00000, 0.00000, 80.00000);
	CreateDynamicObject(2185, 2056.42334, -1313.19958, 1536.32617,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14532, 2056.56982, -1315.02295, 1537.30286,   0.00000, 0.00000, 60.00000);
	CreateDynamicObject(367, 2056.57910, -1312.42969, 1537.16907,   0.00000, 5.50000, 20.00000);
	CreateDynamicObject(1253, 2053.75073, -1321.37549, 1539.34033,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1828, 2061.35327, -1315.41602, 1536.32495,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14393, 2065.01978, -1298.18396, 1538.56335,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(14392, 2065.02368, -1298.21301, 1537.56824,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(14391, 2064.10742, -1299.76965, 1537.28992,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2423, 2044.68604, -1319.19543, 1536.32495,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2266, 2045.61792, -1317.21167, 1538.19299,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1789, 2054.82080, -1319.96521, 1536.88574,   0.00000, 0.00000, 20.00000);
	CreateDynamicObject(1809, 2054.14868, -1318.55615, 1536.32556,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2104, 2053.85181, -1316.80750, 1536.30786,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(927, 2053.96802, -1317.67102, 1537.76050,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(928, 2056.34595, -1316.68127, 1536.60632,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(926, 2056.55786, -1317.29883, 1536.60632,   0.00000, 0.00000, 50.00000);
	CreateDynamicObject(928, 2057.05713, -1316.82214, 1536.60632,   0.00000, 0.00000, -40.00000);
	CreateDynamicObject(1230, 2054.36963, -1317.77100, 1536.74695,   0.00000, 0.00000, 80.00000);
	CreateDynamicObject(1502, 2063.14551, -1306.99219, 1536.32190,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1502, 2066.17749, -1306.94556, 1536.32190,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1726, 2043.62415, -1310.88318, 1536.32544,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1726, 2043.62415, -1308.47485, 1536.32544,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1753, 2044.95886, -1313.04297, 1536.32483,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1806, 2036.10986, -1318.51013, 1536.32642,   0.00000, 0.00000, 20.00000);
	CreateDynamicObject(1808, 2039.98328, -1313.31775, 1536.32642,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2008, 2035.51697, -1317.13916, 1536.32507,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2008, 2036.53259, -1316.10547, 1536.32507,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1806, 2036.00586, -1315.62134, 1536.32642,   0.00000, 0.00000, 170.00000);
	CreateDynamicObject(2202, 2039.71765, -1311.06323, 1536.32605,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(948, 2039.90784, -1313.92310, 1536.32666,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2826, 2036.39417, -1316.23279, 1537.13574,   0.00000, 0.00000, 40.00000);
	CreateDynamicObject(2837, 2035.63940, -1316.94617, 1537.13855,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19422, 2036.88123, -1317.22961, 1537.13745,   0.00000, 0.00000, 20.00000);
	CreateDynamicObject(1723, 2035.58801, -1313.02747, 1536.32544,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1753, 2053.02295, -1315.93604, 1536.32483,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1714, 2051.74487, -1307.74890, 1536.32495,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2616, 2035.04590, -1314.36194, 1538.42017,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3077, 2046.26978, -1308.35376, 1536.32324,   0.00000, 0.00000, 20.00000);
	CreateDynamicObject(2615, 2045.51355, -1308.68591, 1538.61719,   0.00000, 0.00000, 20.00000);
	CreateDynamicObject(2966, 2052.70801, -1309.13904, 1537.12305,   0.00000, 0.00000, -140.00000);
	CreateDynamicObject(2424, 2045.72534, -1319.26917, 1536.32495,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2424, 2046.65137, -1319.26917, 1536.32495,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2424, 2047.57776, -1319.26917, 1536.32495,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2424, 2048.50366, -1319.26917, 1536.32495,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2423, 2049.43335, -1319.27014, 1536.32495,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2424, 2049.50732, -1318.23291, 1536.32495,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2424, 2044.68750, -1318.26624, 1536.32495,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2826, 2044.69031, -1318.76074, 1537.37732,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2827, 2048.65186, -1319.29797, 1537.37732,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3387, 2054.32422, -1308.89099, 1535.60364,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(3389, 2054.32422, -1309.91516, 1535.60364,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2185, 2056.60547, -1307.61780, 1536.32617,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1809, 2056.27148, -1307.68274, 1537.13232,   0.00000, 0.00000, -20.00000);
	CreateDynamicObject(19422, 2055.72778, -1307.78259, 1537.13403,   0.00000, 0.00000, 40.00000);
	CreateDynamicObject(1722, 2040.46082, -1312.97180, 1536.32544,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1722, 2040.47034, -1312.35474, 1536.32544,   0.00000, 0.00000, -80.00000);
	CreateDynamicObject(1722, 2040.47461, -1311.51880, 1536.32544,   0.00000, 0.00000, -95.00000);
	CreateDynamicObject(1722, 2040.50623, -1306.32031, 1536.32544,   0.00000, 0.00000, -95.00000);
	CreateDynamicObject(1722, 2040.48340, -1305.61304, 1536.32544,   0.00000, 0.00000, -87.00000);
	CreateDynamicObject(2267, 2047.55383, -1316.76526, 1538.51501,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2269, 2049.53711, -1317.20776, 1538.19397,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2271, 2051.23657, -1317.20764, 1538.19397,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2270, 2052.75806, -1317.21802, 1538.18604,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1726, 2053.22192, -1316.98279, 1536.32544,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1775, 2053.25171, -1319.80640, 1537.42065,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2194, 2050.38818, -1309.71667, 1537.36865,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2190, 2052.30078, -1309.84741, 1537.10046,   0.00000, 0.00000, 210.00000);
	CreateDynamicObject(2184, 2050.60376, -1309.82422, 1536.32397,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1704, 2053.25073, -1311.22815, 1536.32068,   0.00000, 0.00000, -150.00000);
	CreateDynamicObject(1704, 2050.80273, -1311.58484, 1536.32068,   0.00000, 0.00000, -210.00000);
	CreateDynamicObject(2827, 2050.85962, -1309.23315, 1537.09607,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2264, 2044.92896, -1312.83606, 1538.31458,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2262, 2044.91321, -1311.46802, 1538.34460,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2315, 2051.27173, -1314.55933, 1536.32507,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2826, 2051.49951, -1314.64526, 1536.81360,   0.00000, 0.00000, 80.00000);
	CreateDynamicObject(2840, 2052.52954, -1314.59705, 1536.81384,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2010, 2045.00977, -1310.09241, 1536.32471,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1502, 2040.32874, -1315.85913, 1536.32495,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1502, 2040.31970, -1309.48462, 1536.32495,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2011, 2038.66638, -1319.01343, 1536.32471,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1722, 2039.07422, -1318.17676, 1536.32544,   0.00000, 0.00000, 220.00000);
	CreateDynamicObject(1722, 2039.52161, -1317.70642, 1536.32544,   0.00000, 0.00000, 225.00000);
	CreateDynamicObject(1722, 2040.03467, -1317.18152, 1536.32544,   0.00000, 0.00000, 229.00000);
	CreateDynamicObject(2961, 2044.63708, -1316.74207, 1537.64099,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2962, 2044.63708, -1316.74207, 1537.64099,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1502, 2044.33215, -1315.85535, 1536.32495,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1502, 2053.86743, -1322.13647, 1536.32495,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2515, 2035.26392, -1309.44214, 1537.56897,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2685, 2040.15393, -1307.60107, 1538.06653,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2515, 2035.26392, -1307.94214, 1537.56897,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2515, 2035.26392, -1306.44214, 1537.56897,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2515, 2035.26392, -1304.94214, 1537.56897,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2676, 2036.46069, -1306.26746, 1536.44470,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2742, 2038.61694, -1304.24841, 1537.97327,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2742, 2039.56091, -1304.24841, 1537.97327,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2254, 2039.28015, -1317.84814, 1538.44592,   0.00000, 0.00000, 45.00000);
	CreateDynamicObject(2257, 2041.32629, -1322.72278, 1538.03992,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2258, 2044.32629, -1322.72278, 1538.03992,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2256, 2047.12683, -1322.72278, 1538.03992,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1533, 2035.02905, -1322.35706, 1536.28564,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2261, 2040.88232, -1313.05823, 1538.03992,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2262, 2040.88232, -1311.05823, 1538.13391,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2010, 2043.74341, -1304.48352, 1536.32471,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2263, 2043.71875, -1306.87866, 1538.13391,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2264, 2043.71875, -1308.87866, 1538.13391,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2265, 2043.71875, -1310.87866, 1538.13391,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2260, 2043.71875, -1312.87866, 1538.13391,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1533, 2035.02905, -1320.85706, 1536.28564,   0.00000, 0.00000, 90.00000);
	//====== AUTOSALON? ======
	new autoshop_map_obj[8];
	autoshop_map_obj[0] = CreateDynamicObject(19378, 95.09840, -881.71838, 1562.77161,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19378, 99.47200, -877.00922, 1562.77161,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19378, 104.22450, -881.71838, 1562.77161,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19378, 108.95280, -886.44690, 1562.77161,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19378, 95.09840, -891.32019, 1562.77161,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19378, 99.47200, -896.02502, 1562.77161,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19378, 109.05840, -896.02502, 1562.77161,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19376, 122.05411, -872.26044, 1559.64954,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19376, 127.01973, -867.43799, 1559.64954,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(19376, 132.15077, -872.25995, 1559.64954,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19376, 127.00801, -876.97180, 1559.64954,   90.00000, 0.00000, 90.00000);
	autoshop_map_obj[1] = CreateDynamicObject(19378, 107.42280, -891.17297, 1562.77161,   0.00000, 0.00000, 0.00000);

	for(new i=autoshop_map_obj[0]; i<=autoshop_map_obj[1]; i++) {
	SetDynamicObjectMaterial(i, 0, 14390, "dr_gsnew", "concpanel_la", 0); }

	autoshop_map_obj[2] = CreateDynamicObject(19377, 104.29410, -887.33063, 1562.74731,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 99.97200, -891.32019, 1557.76245,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 110.43640, -891.32019, 1557.76245,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 99.97200, -881.71838, 1557.76245,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 127.19500, -872.23901, 1557.83899,   0.00000, 90.00000, 0.00000);
	autoshop_map_obj[3] = CreateDynamicObject(19377, 104.29410, -877.79260, 1562.74731,   0.00000, 90.00000, 0.00000);

	for(new i=autoshop_map_obj[2]; i<=autoshop_map_obj[3]; i++) {
	SetDynamicObjectMaterial(i, 0, 14390, "dr_gsnew", "AH_flroortile12", 0); }

	autoshop_map_obj[4] = CreateDynamicObject(19436, 99.84550, -892.06250, 1566.01025,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19436, 99.13100, -891.34833, 1560.92285,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19436, 99.84550, -892.06250, 1560.92285,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19436, 99.13100, -891.34833, 1557.46521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19436, 99.84550, -890.63452, 1560.92285,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19436, 100.56100, -891.34833, 1560.92285,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19436, 100.56100, -891.34833, 1557.46521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19436, 99.84550, -890.63452, 1557.46521,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19436, 99.13110, -879.95599, 1563.46118,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19436, 99.13110, -883.44189, 1563.46118,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19436, 99.13110, -886.92157, 1563.46118,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19436, 99.13110, -890.39917, 1563.46118,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19436, 100.79280, -892.06189, 1563.46118,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(19436, 104.25870, -892.06189, 1563.46118,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(19436, 107.75000, -892.06189, 1563.46118,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(19436, 99.13100, -891.34833, 1566.01025,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19436, 99.84550, -892.06250, 1557.46521,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19436, 99.13100, -879.00818, 1566.01025,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19377, 99.13110, -880.40277, 1557.42297,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19436, 99.84550, -885.13251, 1560.92285,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19436, 99.84550, -885.13251, 1557.46521,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19377, 100.55910, -880.40277, 1557.42297,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19455, 122.15720, -870.67358, 1558.68445,   30.00000, 0.00000, 0.00000);
	CreateDynamicObject(19455, 125.45663, -867.46295, 1562.39954,   30.00000, 0.00000, -90.00000);
	autoshop_map_obj[5] = CreateDynamicObject(19436, 106.55790, -892.06250, 1566.01025,   0.00000, 0.00000, 90.00000);

	for(new i=autoshop_map_obj[4]; i<=autoshop_map_obj[5]; i++) {
	SetDynamicObjectMaterial(i, 0, 14390, "dr_gsnew", "mp_cloth_subwall", 0); }

	autoshop_map_obj[6] = CreateDynamicObject(19379, 99.72332, -881.63184, 1567.81860,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19379, 99.72330, -891.23480, 1567.81860,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 127.19500, -872.23901, 1563.33618,   0.00000, 90.00000, 0.00000);
	autoshop_map_obj[7] = CreateDynamicObject(19379, 110.21090, -891.23480, 1567.81860,   0.00000, 90.00000, 0.00000);

	for(new i=autoshop_map_obj[6]; i<=autoshop_map_obj[7]; i++) {
	SetDynamicObjectMaterial(i, 0, 14847, "mp_policesf", "mp_cop_floor2", 0); }

	CreateDynamicObject(14411, 97.02610, -880.04199, 1559.64380,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3851, 99.21240, -885.20410, 1565.93652,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3851, 106.24920, -891.98071, 1565.93652,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2434, 101.69600, -888.73389, 1557.84766,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2435, 101.69600, -887.80322, 1557.84766,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2435, 102.82950, -888.89978, 1557.84766,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 103.75750, -888.89978, 1557.84766,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 104.68600, -888.89978, 1557.84766,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 105.61440, -888.89978, 1557.84766,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 106.54240, -888.89978, 1557.84766,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2435, 107.47240, -888.89978, 1557.84766,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1536, 105.00002, -886.54712, 1557.83008,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1537, 104.81020, -895.91156, 1557.83008,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1537, 103.31020, -895.91162, 1557.83008,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2008, 102.62402, -880.66376, 1562.83313,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2009, 99.84582, -891.38983, 1562.83313,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2010, 103.76044, -877.52649, 1562.83313,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2011, 103.79475, -886.20642, 1562.83313,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1702, 106.80354, -888.27032, 1562.83313,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1705, 99.39778, -888.71198, 1562.83313,   0.00000, 0.00000, 10.00000);
	CreateDynamicObject(1714, 100.71313, -891.63763, 1562.83313,   0.00000, 0.00000, 177.00000);
	CreateDynamicObject(1705, 106.76404, -890.74994, 1562.83313,   0.00000, 0.00000, -110.00000);
	CreateDynamicObject(1715, 103.02323, -885.61053, 1562.83313,   0.00000, 0.00000, 170.00000);
	CreateDynamicObject(1722, 103.66249, -882.73572, 1562.83313,   0.00000, 0.00000, 170.00000);
	CreateDynamicObject(1808, 104.52174, -886.75391, 1562.83313,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1727, 96.03548, -894.38745, 1557.85022,   0.00000, 0.00000, 95.00000);
	CreateDynamicObject(1822, 97.26376, -894.28101, 1557.84937,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1726, 98.96620, -895.31384, 1557.85022,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(948, 95.94113, -895.25482, 1557.84839,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1715, 103.02334, -887.50049, 1557.85022,   0.00000, 0.00000, 10.00000);
	CreateDynamicObject(1715, 106.72617, -887.41473, 1557.85022,   0.00000, 0.00000, -10.00000);
	CreateDynamicObject(1722, 107.28467, -891.98145, 1557.84937,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1722, 107.25199, -892.60327, 1557.84937,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1722, 107.23843, -893.20447, 1557.84937,   0.00000, 0.00000, 94.00000);
	CreateDynamicObject(1722, 107.27648, -891.34100, 1557.84937,   0.00000, 0.00000, 94.00000);
	CreateDynamicObject(2011, 106.81670, -895.46936, 1557.85022,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2001, 99.89583, -892.56989, 1557.84937,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2066, 105.56864, -887.08160, 1562.83423,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2067, 106.16660, -887.06561, 1562.83423,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2067, 106.76460, -887.06561, 1562.83423,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2008, 102.62400, -884.16382, 1562.83313,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1715, 103.05286, -881.75720, 1562.83313,   0.00000, 0.00000, 185.00000);
	CreateDynamicObject(1722, 102.58692, -882.63763, 1562.83313,   0.00000, 0.00000, 190.00000);
	CreateDynamicObject(1722, 102.96960, -879.09760, 1562.83313,   0.00000, 0.00000, 190.00000);
	CreateDynamicObject(2116, 105.30257, -890.14185, 1562.63025,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2186, 101.97437, -877.59119, 1562.83423,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2190, 106.36742, -889.14441, 1558.90137,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2190, 103.39906, -889.19763, 1558.90137,   0.00000, 0.00000, 190.00000);
	CreateDynamicObject(2199, 104.04583, -885.09192, 1557.84912,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2239, 95.69992, -892.83563, 1557.84998,   0.00000, 0.00000, 40.00000);
	CreateDynamicObject(2254, 100.68328, -891.35663, 1560.43982,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2255, 99.83424, -885.72760, 1560.43982,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2256, 102.43217, -877.10901, 1560.43982,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2257, 100.67200, -882.65521, 1560.43982,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2258, 100.67400, -879.64191, 1560.43982,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2185, 101.49226, -879.21906, 1557.84961,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1714, 102.38699, -877.60608, 1557.85059,   0.00000, 0.00000, 10.00000);
	CreateDynamicObject(1722, 102.95179, -880.66248, 1557.84900,   0.00000, 0.00000, 10.00000);
	CreateDynamicObject(1722, 101.67253, -880.61951, 1557.84900,   0.00000, 0.00000, -10.00000);
	CreateDynamicObject(2649, 122.60023, -874.31555, 1561.64526,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(2707, 129.81380, -872.83197, 1558.66284,   0.00000, 180.00000, 0.00000);
	CreateDynamicObject(2707, 129.81380, -867.71997, 1558.66284,   0.00000, 180.00000, 0.00000);
	CreateDynamicObject(2707, 122.36980, -872.83197, 1558.66284,   0.00000, 180.00000, 0.00000);
	CreateDynamicObject(19379, 129.80750, -868.08929, 1553.39856,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19379, 125.07830, -872.81927, 1553.39856,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19379, 124.64490, -868.09113, 1558.56018,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(948, 122.63081, -876.56750, 1557.92578,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1703, 125.34460, -876.28271, 1557.92578,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2657, 122.16595, -872.27997, 1562.85095,   0.00000, -90.00000, 90.00000);
	CreateDynamicObject(2260, 122.61310, -872.22180, 1561.27161,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2261, 122.65070, -871.16858, 1561.76160,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2262, 122.63190, -869.82953, 1561.66357,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2263, 122.66270, -870.82037, 1560.97754,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2264, 123.49940, -868.07727, 1560.97754,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2265, 124.63124, -868.03369, 1561.78955,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(631, 122.67726, -873.50421, 1558.81226,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1536, 132.12131, -869.68469, 1557.92102,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(638, 131.67903, -875.48651, 1558.61426,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1704, 126.93530, -875.99951, 1557.92578,   0.00000, 0.00000, 190.00000);
	CreateDynamicObject(1704, 131.51479, -872.99158, 1557.92578,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2311, 124.06928, -875.06281, 1557.92505,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2824, 125.54414, -875.00085, 1558.42749,   0.00000, 0.00000, 20.00000);
	CreateDynamicObject(2825, 124.43925, -875.05670, 1558.42749,   0.00000, 0.00000, -20.00000);
	//============================= SRC =============================
	CreateDynamicObject(8406,-2469.1689453,798.1409912,39.6969986,0.0000000,0.0000000,0.0000000); //object(carparksign01_lvs) (1)
	CreateDynamicObject(10281,-2495.8369141,787.9699707,39.3030014,0.0000000,0.0000000,90.0000000); //object(michsign_sfe) (1)
	CreateDynamicObject(14826,-2507.3291016,767.5040283,34.9360008,0.0000000,0.0000000,180.0000000); //object(int_kbsgarage2) (1)
	CreateDynamicObject(11480,-2507.9960938,767.9290161,36.3660011,0.0000000,0.0000000,270.0000000); //object(des_nwt_carport) (1)
	CreateDynamicObject(13591,-2491.5471191,758.8820190,34.7999992,0.0000000,0.0000000,0.0000000); //object(kickcar28) (1)
	CreateDynamicObject(3594,-2494.0061035,758.7249756,35.6800003,0.0000000,0.0000000,216.0000000); //object(la_fuckcar1) (1)
	CreateDynamicObject(3242,-2493.2019043,789.8319702,36.1080017,0.0000000,0.0000000,90.0000000); //object(conhoos1) (1)
	CreateDynamicObject(849,-2491.7270508,796.3980103,34.4720001,0.0000000,0.0000000,0.0000000); //object(cj_urb_rub_3) (1)
	CreateDynamicObject(1450,-2489.6230469,796.8560181,34.7719994,0.0000000,0.0000000,0.0000000); //object(dyn_crate_3) (1)
	CreateDynamicObject(1440,-2493.3159180,782.9320068,34.6910019,0.0000000,0.0000000,0.0000000); //object(dyn_box_pile_3) (1)
	CreateDynamicObject(1165,-2463.8200684,773.2769775,34.0000000,19.0000000,90.0000000,0.0000000); //object(fbmp_c_u) (1)
	CreateDynamicObject(1150,-2463.3750000,773.9299927,34.5550003,0.0000000,0.0000000,202.0000000); //object(rbmp_a_f) (1)
	CreateDynamicObject(1128,-2456.6420898,797.4979858,35.7999992,55.0000000,0.0000000,270.0000000); //object(rf_lr_bl1) (1)
	CreateDynamicObject(3302,-2487.6240234,760.5889893,34.2620010,0.0000000,0.0000000,56.0000000); //object(cxrf_corpanel) (1)
	CreateDynamicObject(2674,-2488.9121094,789.6560059,34.1940002,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_2) (1)
	CreateDynamicObject(2673,-2487.7519531,790.6240234,34.2599983,0.0000000,0.0000000,0.0000000); //object(proc_rubbish_5) (1)
	CreateDynamicObject(2670,-2487.5019531,792.8670044,34.2639999,0.0000000,0.0000000,292.0000000); //object(proc_rubbish_1) (1)
	CreateDynamicObject(19126,-2476.6899414,798.3469849,34.3219986,0.0000000,0.0000000,0.0000000); //object(bollardlight6) (1)
	CreateDynamicObject(19126,-2456.8850098,798.3029785,34.3219986,0.0000000,0.0000000,0.0000000); //object(bollardlight6) (2)
	CreateDynamicObject(19125,-2496.5449219,778.1530151,34.3219986,0.0000000,0.0000000,0.0000000); //object(bollardlight5) (1)
	CreateDynamicObject(19125,-2486.2661133,773.1510010,34.3219986,0.0000000,0.0000000,0.0000000); //object(bollardlight5) (2)
	CreateDynamicObject(19124,-2475.3278809,773.2849731,34.3219986,0.0000000,0.0000000,0.0000000); //object(bollardlight4) (1)
}

apublic ClearChat(playerid) return ApplyAnimation(playerid,"CARRY","crry_prtial",4.0,0,0,0,0,0,0);

apublic Carry(playerid, action) {
	switch(action) {
	    case 0: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	    case 1: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
	    case 2: TogglePlayerControllable(playerid,1);
	}
	ApplyAnimation(playerid,"CARRY","crry_prtial",4.0,0,0,0,0,0,0);
	return true;
}

stock GiveWeapon(playerid,weaponid,ammo) Player[playerid][Weapon][weaponid] += ammo, GivePlayerWeapon(playerid,weaponid,ammo);

stock ResetWeapon(playerid) {
	ResetPlayerWeapons(playerid);
 	for(new i=0;i<47;i++) if(Player[playerid][Weapon][i] > 0) GivePlayerWeapon(playerid,i,Player[playerid][Weapon][i]);
}

stock SetPlayerArmorAC(playerid, Float: Armor) Player[playerid][PlayerArmor] = Armor, SetPlayerArmour(playerid, Armor);

CreateVehicles(){
	//--- Grove Gang ---
    grovecar[0] = AddStaticVehicleEx(478,2505.5148926,-1694.7790527,13.6330004,0.0000000,86,1,500); //Walton
	AddStaticVehicleEx(466,2492.0349121,-1683.0959473,13.2570000,342.0000000,86,1,500); //Glendale
	AddStaticVehicleEx(466,2487.0339355,-1683.2469482,13.2570000,341.9989014,86,1,500); //Glendale
	AddStaticVehicleEx(567,2482.1999512,-1682.9270020,13.3079996,342.0000000,86,1,500); //Savanna
	grovecar[1] = AddStaticVehicleEx(492,2499.2199707,-1683.4000244,13.2609997,286.0000000,86,1,500); //Greenwood
	ballascar[0] = AddStaticVehicleEx(566,1992.6459961,-1128.7049561,25.5890007,120.0000000,18,1,500); //Tahoma
	AddStaticVehicleEx(566,1999.3959961,-1128.8520508,25.5890007,119.9981689,18,1,500); //Tahoma
	AddStaticVehicleEx(517,2006.8590088,-1128.7170410,25.2560005,122.0000000,18,1,500); //Majestic
	AddStaticVehicleEx(478,2001.9210205,-1120.8299561,26.8430004,180.0000000,18,1,500); //Walton
	ballascar[1] = AddStaticVehicleEx(412,1994.1359863,-1119.3289795,26.7240009,270.0000000,18,1,500); //Voodoo
	taxicar[0] = AddStaticVehicleEx(420,869.9650269,-1658.2490234,13.3970003,180.0000000,6,1,80); //Taxi
	AddStaticVehicleEx(420,874.4370117,-1658.3599854,13.3970003,180.0000000,6,1,80); //Taxi
	AddStaticVehicleEx(420,878.8120117,-1658.3929443,13.3970003,180.0000000,6,1,80); //Taxi
	AddStaticVehicleEx(420,883.6129761,-1658.3620605,13.3970003,180.0000000,6,1,80); //Taxi
	AddStaticVehicleEx(420,888.1119995,-1658.3979492,13.3970003,180.0000000,6,1,80); //Taxi
	AddStaticVehicleEx(420,892.5620117,-1658.4329834,13.3970003,180.0000000,6,1,80); //Taxi
	AddStaticVehicleEx(420,870.1190186,-1669.1739502,13.3970003,0.0000000,6,1,80); //Taxi
	AddStaticVehicleEx(420,874.4190063,-1669.1130371,13.3970003,0.0000000,6,1,80); //Taxi
	AddStaticVehicleEx(420,879.1209717,-1669.1710205,13.3970003,0.0000000,6,1,80); //Taxi
	AddStaticVehicleEx(420,883.5209961,-1669.1080322,13.3970003,0.0000000,6,1,80); //Taxi
	AddStaticVehicleEx(420,887.8959961,-1669.0450439,13.3970003,0.0000000,6,1,80); //Taxi
	AddStaticVehicleEx(420,892.3709717,-1668.9809570,13.3970003,0.0000000,6,1,80); //Taxi
	AddStaticVehicleEx(438,892.4669800,-1678.9809570,13.7469997,180.0000000,6,1,80); //Cabbie
	AddStaticVehicleEx(438,888.1669922,-1679.0419922,13.7469997,180.0000000,6,1,80); //Cabbie
	AddStaticVehicleEx(438,883.4920044,-1679.1080322,13.7469997,180.0000000,6,1,80); //Cabbie
	AddStaticVehicleEx(438,878.9660034,-1679.1719971,13.7469997,180.0000000,6,1,80); //Cabbie
	AddStaticVehicleEx(438,874.4160156,-1679.2359619,13.7469997,180.0000000,6,1,80); //Cabbie
	taxicar[1] = AddStaticVehicleEx(438,870.4409790,-1679.2919922,13.7469997,180.0000000,6,1,80); //Cabbie
	AddStaticVehicleEx(509,1209.5379639,-1737.7290039,13.1829996,268.0000000,2,1,70); //Bike
	AddStaticVehicleEx(509,1209.4649658,-1736.0789795,13.1829996,267.9949951,2,1,70); //Bike
	AddStaticVehicleEx(509,1209.3859863,-1734.2790527,13.1829996,267.9949951,2,1,70); //Bike
	AddStaticVehicleEx(509,1209.3129883,-1732.6290283,13.1829996,267.9949951,2,1,70); //Bike
	AddStaticVehicleEx(509,1209.2419434,-1731.1049805,13.1829996,267.9949951,2,1,70); //Bike
	AddStaticVehicleEx(509,1209.2530518,-1729.3790283,13.1829996,267.9949951,2,1,70); //Bike
	AddStaticVehicleEx(509,1209.2640381,-1727.6789551,13.1829996,267.9949951,2,1,70); //Bike
	AddStaticVehicleEx(509,1209.2750244,-1726.0789795,13.1829996,267.9949951,2,1,70); //Bike
	AddStaticVehicleEx(509,1209.2819824,-1724.6269531,13.1829996,267.9949951,2,1,70); //Bike
	rentcar[0] = AddStaticVehicleEx(518,1244.3120117,-1732.5069580,13.3820000,0.0000000,-1,-1,300); //Buccaneer
	AddStaticVehicleEx(534,1240.1429443,-1732.4210205,13.4080000,0.0000000,-1,-1,300); //Remington
	AddStaticVehicleEx(405,1236.0250244,-1732.3489990,13.5819998,0.0000000,-1,-1,300); //Sentinel
	AddStaticVehicleEx(496,1232.1009521,-1732.8740234,13.3690004,0.0000000,-1,-1,300); //Blista Compact
	rentcar[1] = AddStaticVehicleEx(439,1228.2869873,-1732.5959473,13.5799999,0.0000000,-1,-1,70); //Stallion
	mailcar[0] = AddStaticVehicleEx(586,1302.7120361,-1876.2370605,13.1499996,0.0000000,7,1,70); //Wayfarer
	AddStaticVehicleEx(586,1300.5860596,-1876.1629639,13.1499996,0.0000000,7,1,70); //Wayfarer
	AddStaticVehicleEx(586,1298.5600586,-1876.2130127,13.1499996,0.0000000,7,1,70); //Wayfarer
	AddStaticVehicleEx(586,1296.4849854,-1876.2640381,13.1499996,0.0000000,7,1,70); //Wayfarer
	AddStaticVehicleEx(586,1291.6860352,-1876.4429932,13.1499996,0.0000000,7,1,70); //Wayfarer
	AddStaticVehicleEx(586,1294.0350342,-1876.3549805,13.1499996,0.0000000,7,1,70); //Wayfarer
	mailcar[1] = AddStaticVehicleEx(479,1290.9460449,-1868.3320312,13.4510002,0.0000000,2,1,70); //Regina
 	vagoscar[0] = AddStaticVehicleEx(576,2829.6494140625,-1191.265625,24.559999465942,309.99572753906,6,1,500);
    AddStaticVehicleEx(467,2828.572265625,-1176.8173828125,24.879999160767,243.99536132813,1,6,500);
    AddStaticVehicleEx(467,2828.5,-1172.5920410156,24.879999160767,244,1,6,500);
    AddStaticVehicleEx(478,2829.0180664063,-1199.3449707031,24.773000717163,2,6,1,500);
    vagoscar[1] = AddStaticVehicleEx(575,2829.3159179688,-1168.7189941406,24.743000030518,244,6,1,500);
    azteccar[0] = AddStaticVehicleEx(507,1877.2340087891,-2018.1639404297,13.489000320435,220,2,53,500);
    AddStaticVehicleEx(507,1876.2629394531,-2022.9389648438,13.489000320435,219.99572753906,2,53,500);
    AddStaticVehicleEx(491,1888.9019775391,-2018.958984375,13.4390001297,140,2,1,500);
    AddStaticVehicleEx(419,1889.3603515625,-2024.3046875,13.468999862671,140,2,1,500);
    azteccar[1] = AddStaticVehicleEx(478,1883.107421875,-2011.1875,13.626999855042,180,2,1,500);
    rifacar[0] = AddStaticVehicleEx(475,1934.9379882813,-1563.4919433594,13.470000267029,220,7,1,500);
    AddStaticVehicleEx(540,1933.6850585938,-1568.0539550781,13.569000244141,220,7,1,500);
    AddStaticVehicleEx(540,1933.5269775391,-1576.3289794922,13.569000244141,220,7,1,500);
    AddStaticVehicleEx(546,1932.3590087891,-1581.0140380859,13.407999992371,220,7,1,500);
    rifacar[1] = AddStaticVehicleEx(478,1931.1479492188,-1588.6700439453,13.642000198364,180,7,1,500);
    armycar[0] = AddStaticVehicleEx(432,214.5910034,1864.4449463,13.2399998,0.0000000,-1,-1,500); //Rhino
	AddStaticVehicleEx(470,182.6799927,1949.2960205,18.0979996,90.0000000,102,1,500); //Patriot
	AddStaticVehicleEx(470,182.5469971,1955.3160400,18.0979996,90.0000000,102,1,500); //Patriot
	AddStaticVehicleEx(470,182.4960022,1961.1970215,18.0979996,90.0000000,102,1,500); //Patriot
	AddStaticVehicleEx(470,182.5760040,1966.9520264,18.0979996,90.0000000,102,1,500); //Patriot
	AddStaticVehicleEx(470,182.6190033,1972.6579590,18.0979996,90.0000000,102,1,500); //Patriot
	AddStaticVehicleEx(500,149.9420013,1946.8189697,19.5720005,270.0000000,16,16,500); //Mesa
	AddStaticVehicleEx(500,150.0729980,1951.3260498,19.5720005,270.0000000,16,16,500); //Mesa
	AddStaticVehicleEx(579,150.1649933,1956.3570557,19.3899994,270.0000000,99,1,500); //Huntley
	AddStaticVehicleEx(579,150.3959961,1961.2840576,19.3899994,270.0000000,99,1,500); //Huntley
	AddStaticVehicleEx(437,149.8890076,1973.2170410,19.6149998,180.0000000,16,16,500); //Coach
	AddStaticVehicleEx(455,255.8379974,1974.9859619,18.2110004,180.0000000,16,1,800); //Flatbed
	AddStaticVehicleEx(433,277.3210144,1949.0460205,18.2110004,270.0000000,-1,-1,800); //Barracks
	AddStaticVehicleEx(433,277.1839905,1956.3459473,18.2110004,270.0000000,-1,-1,800); //Barracks
	AddStaticVehicleEx(433,277.0450134,1963.1960449,18.2110004,270.0000000,-1,-1,800); //Barracks
	AddStaticVehicleEx(433,277.0310059,1982.2089844,18.2110004,270.0000000,-1,-1,800); //Barracks
	AddStaticVehicleEx(433,276.5769958,1990.0720215,18.2110004,270.0000000,-1,-1,800); //Barracks
	AddStaticVehicleEx(433,276.1459961,1997.5340576,18.2110004,270.0000000,-1,-1,800); //Barracks
	AddStaticVehicleEx(548,296.9230042,2021.5529785,19.5410004,160.0000000,-1,-1,500); //Cargobob
	armycar[1] = AddStaticVehicleEx(548,313.7950134,2020.2230225,19.5410004,159.9993896,-1,-1,500); //Cargobob
	pd[0] = AddStaticVehicleEx(596,1535.8389893,-1678.1739502,13.2030001,0.0000000,1,-1,700); //Police Car (LSPD)
	AddStaticVehicleEx(596,1535.9410400,-1667.1479492,13.2030001,180.0000000,1,-1,700); //Police Car (LSPD)
	AddStaticVehicleEx(596,1559.1550293,-1710.1949463,5.7110000,0.0000000,1,-1,700); //Police Car (LSPD)
	AddStaticVehicleEx(596,1570.5489502,-1710.4730225,5.7110000,0.0000000,1,-1,700); //Police Car (LSPD)
	AddStaticVehicleEx(596,1574.6180420,-1710.4830322,5.7110000,0.0000000,1,-1,700); //Police Car (LSPD)
	AddStaticVehicleEx(596,1578.5920410,-1710.4300537,5.7110000,0.0000000,1,-1,700); //Police Car (LSPD)
	AddStaticVehicleEx(596,1583.4160156,-1710.4060059,5.7110000,0.0000000,1,-1,700); //Police Car (LSPD)
	AddStaticVehicleEx(596,1587.3662109,-1710.3388672,5.7110000,0.0000000,1,-1,700); //Police Car (LSPD)
	AddStaticVehicleEx(596,1591.4824219,-1710.3212891,5.7110000,0.0000000,1,-1,700); //Police Car (LSPD)
	AddStaticVehicleEx(596,1595.5570068,-1710.3740234,5.7110000,0.0000000,1,-1,700); //Police Car (LSPD)
	AddStaticVehicleEx(599,1564.8906250,-1710.0712891,6.2760000,0.0000000,1,-1,700); //Police Ranger
	AddStaticVehicleEx(601,1600.8409424,-1704.1290283,5.8210001,88.0000000,-1,-1,700); //S.W.A.T. Van
	AddStaticVehicleEx(427,1601.1850586,-1696.1070557,6.1389999,90.0000000,-1,1,700); //Enforcer
	AddStaticVehicleEx(528,1600.8590088,-1700.2380371,6.0760002,90.0000000,-1,-1,700); //FBI Truck
	AddStaticVehicleEx(497,1557.1610107,-1611.3220215,13.6479998,110.0000000,-1,1,700); //Police Maverick
	AddStaticVehicleEx(523,1561.9040527,-1696.1259766,5.5570002,268.0000000,-1,-1,700); //HPV1000
	AddStaticVehicleEx(523,1562.0090332,-1693.3790283,5.5570002,267.9949951,-1,-1,700); //HPV1000
	AddStaticVehicleEx(523,-1591.9589844,708.9780273,-5.5819998,0.0000000,-1,-1,700); //HPV1000
	AddStaticVehicleEx(523,-1588.4639893,709.1519775,-5.5819998,0.0000000,-1,-1,700); //HPV1000
	AddStaticVehicleEx(597,-1573.8809814,706.0709839,-5.3720002,90.0000000,1,-1,700); //Police Car (SFPD)
	AddStaticVehicleEx(599,-1573.5269775,712.4060059,-4.8569999,90.0000000,1,-1,700); //Police Ranger
	AddStaticVehicleEx(597,-1573.8850098,718.1400146,-5.3720002,90.0000000,1,-1,700); //Police Car (SFPD)
	AddStaticVehicleEx(597,-1573.9189453,722.2890015,-5.3720002,90.0000000,1,-1,700); //Police Car (SFPD)
	AddStaticVehicleEx(597,-1573.8559570,726.5139771,-5.3720002,90.0000000,1,-1,700); //Police Car (SFPD)
	AddStaticVehicleEx(597,-1573.8439941,730.6389771,-5.3720002,90.0000000,1,-1,700); //Police Car (SFPD)
	AddStaticVehicleEx(597,-1573.8320312,734.4639893,-5.3720002,90.0000000,1,0,700); //Police Car (SFPD)
	AddStaticVehicleEx(597,-1573.8199463,738.7639771,-5.3720002,90.0000000,1,0,700); //Police Car (SFPD)
	AddStaticVehicleEx(597,-1573.8079834,742.5130005,-5.3720002,90.0000000,1,0,700); //Police Car (SFPD)
	AddStaticVehicleEx(427,-1579.7960205,748.5720215,-4.9940000,180.0000000,1,0,700); //Enforcer
	AddStaticVehicleEx(601,-1584.0179443,748.7520142,-5.3119998,180.0000000,-1,-1,700); //S.W.A.T. Van
	AddStaticVehicleEx(598,2277.0019531,2432.1179199,3.1429999,0.0000000,1,0,700); //Police Car (LVPD)
	AddStaticVehicleEx(598,2272.8310547,2432.1989746,3.1429999,0.0000000,1,0,700); //Police Car (LVPD)
	AddStaticVehicleEx(598,2268.4309082,2432.2839355,3.1429999,0.0000000,1,0,700); //Police Car (LVPD)
	AddStaticVehicleEx(598,2264.2089844,2432.3659668,3.1429999,0.0000000,1,0,700); //Police Car (LVPD)
	AddStaticVehicleEx(598,2259.6608887,2432.4541016,3.1429999,0.0000000,1,0,700); //Police Car (LVPD)
	AddStaticVehicleEx(598,2286.1831055,2431.8989258,3.1429999,0.0000000,0,0,700); //Police Car (LVPD)
	AddStaticVehicleEx(601,2290.1750488,2432.1750488,3.2040000,0.0000000,-1,-1,700); //S.W.A.T. Van
	AddStaticVehicleEx(599,2294.3769531,2431.7529297,3.6589999,0.0000000,-1,-1,700); //Police Ranger
	AddStaticVehicleEx(523,2255.4460449,2431.5849609,2.9340000,0.0000000,-1,-1,700); //HPV1000
	AddStaticVehicleEx(523,2251.4450684,2431.6508789,2.9340000,0.0000000,-1,-1,700); //HPV1000
	AddStaticVehicleEx(497,2339.0480957,2471.7890625,38.9490013,140.0000000,1,-1,700); //Police Maverick
	pd[1] = AddStaticVehicleEx(497,-1681.1610107,705.8660278,30.8670006,270.0000000,1,-1,700); //Police Maverick
	fbicar[0] = AddStaticVehicleEx(497,1088.5000000,1072.8530273,11.1029997,0.0000000,0,0,800); //Police Maverick
	AddStaticVehicleEx(490,1002.8449707,1069.4350586,11.1400003,92.0000000,-1,-1,800); //FBI Rancher
	AddStaticVehicleEx(490,1002.8040161,1073.7609863,11.1400003,91.9995117,-1,-1,800); //FBI Rancher
	AddStaticVehicleEx(490,1002.7700195,1078.2640381,11.1400003,91.9995117,-1,-1,800); //FBI Rancher
	AddStaticVehicleEx(490,1002.6119995,1082.5279541,11.1400003,91.9995117,-1,-1,800); //FBI Rancher
	AddStaticVehicleEx(490,1002.6469727,1086.9050293,11.1400003,91.9995117,-1,-1,800); //FBI Rancher
	AddStaticVehicleEx(490,1002.5460205,1091.3079834,11.1400003,91.9995117,-1,-1,800); //FBI Rancher
	AddStaticVehicleEx(427,1001.8220215,1095.6949463,11.0679998,92.0000000,0,0,800); //Enforcer
	AddStaticVehicleEx(427,1001.7990112,1099.9949951,11.0679998,89.9995117,0,0,800); //Enforcer
	fbicar[1] = AddStaticVehicleEx(528,1003.0289917,1104.3570557,11.0050001,90.0000000,-1,-1,800); //FBI Truck
	drivingcar[0] = AddStaticVehicleEx(507,-2064.2810059,-83.9749985,35.2000008,180.0000000,3,3,30); //Elegant
	AddStaticVehicleEx(507,-2068.5690918,-83.8320007,35.1139984,180.0000000,3,3,30); //Elegant
	AddStaticVehicleEx(507,-2072.8439941,-83.9609985,35.1139984,180.0000000,3,3,30); //Elegant
	AddStaticVehicleEx(507,-2077.1169434,-83.9449997,35.1139984,180.0000000,3,3,30); //Elegant
	AddStaticVehicleEx(507,-2081.1201172,-83.9509964,35.1139984,180.0000000,3,3,30); //Elegant
	AddStaticVehicleEx(507,-2085.2980957,-83.9570007,35.1139984,180.0000000,3,3,30); //Elegant
	AddStaticVehicleEx(507,-2089.6520996,-83.9850006,35.1139984,180.0000000,3,3,30); //Elegant
	drivingcar[1] = AddStaticVehicleEx(507,-2093.8688965,-83.9660034,35.1139984,180.0000000,3,3,30); //Elegant
	sfncar[0] = AddStaticVehicleEx(582,-2031.5479736,461.7470093,35.3269997,0.0000000,2,1,800); //Newsvan
	AddStaticVehicleEx(582,-2022.6230469,461.6340027,35.3269997,0.0000000,2,1,800); //Newsvan
	AddStaticVehicleEx(582,-2051.3049316,469.2229919,35.3269997,270.0000000,2,1,800); //Newsvan
	AddStaticVehicleEx(582,-2051.3659668,478.7479858,35.3269997,270.0000000,2,1,800); //Newsvan
	sfncar[1] = AddStaticVehicleEx(582,-2050.9169922,488.5390015,35.3269997,270.0000000,2,1,800); //Newsvan
	truckcar[0] = AddStaticVehicleEx(515,-61.1640015,-303.8179932,6.5830002,270.0000000,-1,-1,60); //Roadtrain
	AddStaticVehicleEx(515,-61.1549988,-310.7980042,6.5830002,270.0000000,24,77,60); //Roadtrain
	AddStaticVehicleEx(515,-61.3660011,-317.9939880,6.5830002,270.0000000,-1,-1,60); //Roadtrain
	AddStaticVehicleEx(515,-61.2760010,-325.1480103,6.5830002,270.0000000,-1,-1,60); //Roadtrain
	AddStaticVehicleEx(515,-60.5960007,-338.3859863,6.5830002,310.0000000,2,2,60); //Roadtrain
	AddStaticVehicleEx(403,-30.9370003,-276.6600037,6.1230001,270.0000000,6,6,60); //Linerunner
	AddStaticVehicleEx(403,-30.9290009,-283.2720032,6.1230001,270.0000000,-1,-1,60); //Linerunner
	AddStaticVehicleEx(403,-30.8600006,-290.2760010,6.1230001,270.0000000,-1,-1,60); //Linerunner
	AddStaticVehicleEx(514,-2.2670000,-301.1759949,6.4007492,90.0000000,-1,-1,60); //Tanker
	AddStaticVehicleEx(514,-2.1300001,-307.9739990,6.4010000,90.0000000,-1,-1,60); //Tanker
	AddStaticVehicleEx(514,-1.9880000,-315.0220032,6.4010000,90.0000000,-1,-1,60); //Tanker
	AddStaticVehicleEx(514,-1.9730000,-321.7940063,6.1290002,90.0000000,3,3,60); //Tanker
	truckcar[1] = AddStaticVehicleEx(403,-31.0779991,-297.0679932,6.1230001,270.0000000,-1,-1,60); //Linerunner
	cnncar[0] = AddStaticVehicleEx(582,1551.7180176,969.4459839,10.9750004,90.0000000,2,1,600); //Newsvan
	AddStaticVehicleEx(582,1551.7810059,973.9600220,10.9870005,90.0000000,2,1,600); //Newsvan
	AddStaticVehicleEx(582,1551.6949463,978.3350220,10.9870005,90.0000000,2,1,600); //Newsvan
	AddStaticVehicleEx(582,1551.6090088,982.7080078,10.9870005,90.0000000,2,1,600); //Newsvan
	AddStaticVehicleEx(582,1551.5240479,987.0070190,10.9870005,90.0000000,2,1,600); //Newsvan
	cnncar[1] = AddStaticVehicleEx(488,1535.7979736,951.9849854,83.0859985,286.0000000,2,1,600); //News Chopper
	srccar[0] = AddStaticVehicleEx(402,-2460.0449219,777.6464844,35.1119995,90.0000000,3,1,600); //Buffalo
	AddStaticVehicleEx(506,-2459.9599609,782.0195312,35.0620003,90.0000000,114,1,600); //Super GT
	AddStaticVehicleEx(559,-2459.8779297,786.3439941,34.8821983,90.0000000,6,1,600); //Jester
	AddStaticVehicleEx(603,-2460.0649414,790.5260010,35.1749992,90.0000000,1,2,600); //Phoenix
	AddStaticVehicleEx(480,-2459.8740234,794.5700073,34.9874687,90.0000000,2,1,600); //Comet
	AddStaticVehicleEx(451,-2483.5229492,776.5079956,34.9430008,0.0000000,0,0,600); //Turismo
	AddStaticVehicleEx(415,-2479.8911133,776.5139771,35.0429993,0.0000000,0,0,600); //Cheetah
	AddStaticVehicleEx(411,-2475.9221191,776.5219727,34.9580002,0.0000000,0,0,600); //Infernus
	AddStaticVehicleEx(541,-2472.0239258,776.4790039,34.8590012,0.0000000,0,0,600); //Bullet
	AddStaticVehicleEx(429,-2468.2561035,776.7239990,34.8334351,0.0000000,0,0,600); //Banshee
	AddStaticVehicleEx(405,-2489.2451172,766.6400146,35.1720009,0.0000000,-1,-1,600); //Sentinel
	AddStaticVehicleEx(426,-2493.4909668,766.8499756,34.8694839,0.0000000,-1,-1,600); //Premier
	srccar[1] = AddStaticVehicleEx(445,-2497.8200684,766.8699951,35.0796928,0.0000000,-1,-1,600); //Admiral

}

apublic LoadTextDraws()
{
	// Buttons Skin
    brLeft = TextDrawCreate(280.000000, 351.000000, "LD_BEAT:left");
	TextDrawBackgroundColor(brLeft, 255);
	TextDrawFont(brLeft, 4);
	TextDrawLetterSize(brLeft, 0.500000, 1.000000);
	TextDrawColor(brLeft, 1104210329);
	TextDrawSetOutline(brLeft, 0);
	TextDrawSetProportional(brLeft, 1);
	TextDrawSetShadow(brLeft, 1);
	TextDrawUseBox(brLeft, 1);
	TextDrawBoxColor(brLeft, 255);
	TextDrawTextSize(brLeft, 37.000000, 30.000000);
	TextDrawSetSelectable(brLeft, 1);

	brRight = TextDrawCreate(320.000000, 350.000000, "LD_BEAT:right");
	TextDrawBackgroundColor(brRight, 255);
	TextDrawFont(brRight, 4);
	TextDrawLetterSize(brRight, 0.500000, 1.000000);
	TextDrawColor(brRight, 1104210329);
	TextDrawSetOutline(brRight, 0);
	TextDrawSetProportional(brRight, 1);
	TextDrawSetShadow(brRight, 1);
	TextDrawUseBox(brRight, 1);
	TextDrawBoxColor(brRight, 255);
	TextDrawTextSize(brRight, 37.000000, 30.000000);
	TextDrawSetSelectable(brRight, 1);

	brSelect = TextDrawCreate(50.000000, 394.000000, "PICK");
	TextDrawAlignment(brSelect, 2);
	TextDrawBackgroundColor(brSelect, 1104210295);
	TextDrawFont(brSelect, 3);
	TextDrawLetterSize(brSelect, 1.000000, 2.500000);
	TextDrawColor(brSelect, 153);
	TextDrawSetOutline(brSelect, 1);
	TextDrawSetProportional(brSelect, 1);
	TextDrawSetSelectable(brSelect, 1);

	ButtonCancel = TextDrawCreate(603.000000, 394.000000, "LD_BEAT:cross");
	TextDrawBackgroundColor(ButtonCancel, -16776961);
	TextDrawFont(ButtonCancel, 4);
	TextDrawLetterSize(ButtonCancel, 1.000000, 2.499999);
	TextDrawColor(ButtonCancel, -1660944129);
	TextDrawSetOutline(ButtonCancel, 1);
	TextDrawSetProportional(ButtonCancel, 1);
	TextDrawUseBox(ButtonCancel, 1);
	TextDrawBoxColor(ButtonCancel, 255);
	TextDrawTextSize(ButtonCancel, 30.000000, 31.000000);
	TextDrawSetSelectable(ButtonCancel, 1);

	tCost = TextDrawCreate(510.000000, 205.000000, "Cost:");
	TextDrawBackgroundColor(tCost, 85);
	TextDrawFont(tCost, 2);
	TextDrawLetterSize(tCost, 0.300000, 1.000000);
	TextDrawColor(tCost, 96492799);
	TextDrawSetOutline(tCost, 1);
	TextDrawSetProportional(tCost, 1);
	TextDrawSetSelectable(tCost, 0);
	
	// Admin Password
    abox = TextDrawCreate(330.000000, 163.000000, "_");
	TextDrawAlignment(abox, 2);
	TextDrawBackgroundColor(abox, 255);
	TextDrawFont(abox, 1);
	TextDrawLetterSize(abox, 0.500000, 18.000000);
	TextDrawColor(abox, -1);
	TextDrawSetOutline(abox, 0);
	TextDrawSetProportional(abox, 1);
	TextDrawSetShadow(abox, 1);
	TextDrawUseBox(abox, 1);
	TextDrawBoxColor(abox, -205);
	TextDrawTextSize(abox, -10.000000, 103.000000);
	TextDrawSetSelectable(abox, 0);

	a1 = TextDrawCreate(300.000000, 170.000000, "1");
	TextDrawAlignment(a1, 2);
	TextDrawBackgroundColor(a1, 255);
	TextDrawFont(a1, 2);
	TextDrawLetterSize(a1, 0.500000, 3.099999);
	TextDrawColor(a1, -1);
	TextDrawSetOutline(a1, 0);
	TextDrawSetProportional(a1, 1);
	TextDrawSetShadow(a1, 1);
	TextDrawUseBox(a1, 1);
	TextDrawBoxColor(a1, -16777165);
	TextDrawTextSize(a1, 30.000000, 21.000000);
	TextDrawSetSelectable(a1, 1);

	a2 = TextDrawCreate(330.000000, 170.000000, "2");
	TextDrawAlignment(a2, 2);
	TextDrawBackgroundColor(a2, 255);
	TextDrawFont(a2, 2);
	TextDrawLetterSize(a2, 0.500000, 3.099999);
	TextDrawColor(a2, -1);
	TextDrawSetOutline(a2, 0);
	TextDrawSetProportional(a2, 1);
	TextDrawSetShadow(a2, 1);
	TextDrawUseBox(a2, 1);
	TextDrawBoxColor(a2, -16777165);
	TextDrawTextSize(a2, 30.000000, 21.000000);
	TextDrawSetSelectable(a2, 1);

	a3 = TextDrawCreate(360.000000, 170.000000, "3");
	TextDrawAlignment(a3, 2);
	TextDrawBackgroundColor(a3, 255);
	TextDrawFont(a3, 2);
	TextDrawLetterSize(a3, 0.500000, 3.099999);
	TextDrawColor(a3, -1);
	TextDrawSetOutline(a3, 0);
	TextDrawSetProportional(a3, 1);
	TextDrawSetShadow(a3, 1);
	TextDrawUseBox(a3, 1);
	TextDrawBoxColor(a3, -16777165);
	TextDrawTextSize(a3, 30.000000, 21.000000);
	TextDrawSetSelectable(a3, 1);

	a4 = TextDrawCreate(300.000000, 210.000000, "4");
	TextDrawAlignment(a4, 2);
	TextDrawBackgroundColor(a4, 255);
	TextDrawFont(a4, 2);
	TextDrawLetterSize(a4, 0.500000, 3.099999);
	TextDrawColor(a4, -1);
	TextDrawSetOutline(a4, 0);
	TextDrawSetProportional(a4, 1);
	TextDrawSetShadow(a4, 1);
	TextDrawUseBox(a4, 1);
	TextDrawBoxColor(a4, -16777165);
	TextDrawTextSize(a4, 30.000000, 21.000000);
	TextDrawSetSelectable(a4, 1);

	a5 = TextDrawCreate(330.000000, 210.000000, "5");
	TextDrawAlignment(a5, 2);
	TextDrawBackgroundColor(a5, 255);
	TextDrawFont(a5, 2);
	TextDrawLetterSize(a5, 0.500000, 3.099999);
	TextDrawColor(a5, -1);
	TextDrawSetOutline(a5, 0);
	TextDrawSetProportional(a5, 1);
	TextDrawSetShadow(a5, 1);
	TextDrawUseBox(a5, 1);
	TextDrawBoxColor(a5, -16777165);
	TextDrawTextSize(a5, 30.000000, 21.000000);
	TextDrawSetSelectable(a5, 1);

	a6 = TextDrawCreate(360.000000, 210.000000, "6");
	TextDrawAlignment(a6, 2);
	TextDrawBackgroundColor(a6, 255);
	TextDrawFont(a6, 2);
	TextDrawLetterSize(a6, 0.500000, 3.099999);
	TextDrawColor(a6, -1);
	TextDrawSetOutline(a6, 0);
	TextDrawSetProportional(a6, 1);
	TextDrawSetShadow(a6, 1);
	TextDrawUseBox(a6, 1);
	TextDrawBoxColor(a6, -16777165);
	TextDrawTextSize(a6, 30.000000, 21.000000);
	TextDrawSetSelectable(a6, 1);

	a7 = TextDrawCreate(300.000000, 250.000000, "7");
	TextDrawAlignment(a7, 2);
	TextDrawBackgroundColor(a7, 255);
	TextDrawFont(a7, 2);
	TextDrawLetterSize(a7, 0.500000, 3.099999);
	TextDrawColor(a7, -1);
	TextDrawSetOutline(a7, 0);
	TextDrawSetProportional(a7, 1);
	TextDrawSetShadow(a7, 1);
	TextDrawUseBox(a7, 1);
	TextDrawBoxColor(a7, -16777165);
	TextDrawTextSize(a7, 30.000000, 21.000000);
	TextDrawSetSelectable(a7, 1);

	a8 = TextDrawCreate(330.000000, 250.000000, "8");
	TextDrawAlignment(a8, 2);
	TextDrawBackgroundColor(a8, 255);
	TextDrawFont(a8, 2);
	TextDrawLetterSize(a8, 0.500000, 3.099999);
	TextDrawColor(a8, -1);
	TextDrawSetOutline(a8, 0);
	TextDrawSetProportional(a8, 1);
	TextDrawSetShadow(a8, 1);
	TextDrawUseBox(a8, 1);
	TextDrawBoxColor(a8, -16777165);
	TextDrawTextSize(a8, 30.000000, 21.000000);
	TextDrawSetSelectable(a8, 1);

	a9 = TextDrawCreate(360.000000, 250.000000, "9");
	TextDrawAlignment(a9, 2);
	TextDrawBackgroundColor(a9, 255);
	TextDrawFont(a9, 2);
	TextDrawLetterSize(a9, 0.500000, 3.099999);
	TextDrawColor(a9, -1);
	TextDrawSetOutline(a9, 0);
	TextDrawSetProportional(a9, 1);
	TextDrawSetShadow(a9, 1);
	TextDrawUseBox(a9, 1);
	TextDrawBoxColor(a9, -16777165);
	TextDrawTextSize(a9, 30.000000, 21.000000);
	TextDrawSetSelectable(a9, 1);

	a0 = TextDrawCreate(330.000000, 290.000000, "0");
	TextDrawAlignment(a0, 2);
	TextDrawBackgroundColor(a0, 255);
	TextDrawFont(a0, 2);
	TextDrawLetterSize(a0, 0.500000, 3.099999);
	TextDrawColor(a0, -1);
	TextDrawSetOutline(a0, 0);
	TextDrawSetProportional(a0, 1);
	TextDrawSetShadow(a0, 1);
	TextDrawUseBox(a0, 1);
	TextDrawBoxColor(a0, -16777165);
	TextDrawTextSize(a0, 30.000000, 21.000000);
	TextDrawSetSelectable(a0, 1);

	aenter = TextDrawCreate(357.000000, 328.000000, "Enter");
	TextDrawAlignment(aenter, 2);
	TextDrawBackgroundColor(aenter, 255);
	TextDrawFont(aenter, 2);
	TextDrawLetterSize(aenter, 0.400000, 1.099999);
	TextDrawColor(aenter, -1);
	TextDrawSetOutline(aenter, 0);
	TextDrawSetProportional(aenter, 1);
	TextDrawSetShadow(aenter, 1);
	TextDrawUseBox(aenter, 1);
	TextDrawBoxColor(aenter, 65331);
	TextDrawTextSize(aenter, 30.000000, 50.000000);
	TextDrawSetSelectable(aenter, 1);

	aboxtop = TextDrawCreate(330.000000, 151.000000, "_");
	TextDrawAlignment(aboxtop, 2);
	TextDrawBackgroundColor(aboxtop, 255);
	TextDrawFont(aboxtop, 1);
	TextDrawLetterSize(aboxtop, 0.500000, 1.000000);
	TextDrawColor(aboxtop, -1);
	TextDrawSetOutline(aboxtop, 0);
	TextDrawSetProportional(aboxtop, 1);
	TextDrawSetShadow(aboxtop, 1);
	TextDrawUseBox(aboxtop, 1);
	TextDrawBoxColor(aboxtop, 65331);
	TextDrawTextSize(aboxtop, -10.000000, 103.000000);
	TextDrawSetSelectable(aboxtop, 0);

	atext = TextDrawCreate(278.000000, 150.000000, "_");
	TextDrawBackgroundColor(atext, 255);
	TextDrawFont(atext, 2);
	TextDrawLetterSize(atext, 0.200000, 1.000000);
	TextDrawColor(atext, 0xFFFFFFFF);
	TextDrawSetOutline(atext, 0);
	TextDrawSetProportional(atext, 1);
	TextDrawSetShadow(atext, 1);
	TextDrawSetSelectable(atext, 0);
	
	ac = TextDrawCreate(360.000000, 290.000000, "C");
	TextDrawAlignment(ac, 2);
	TextDrawBackgroundColor(ac, 255);
	TextDrawFont(ac, 2);
	TextDrawLetterSize(ac, 0.500000, 3.099999);
	TextDrawColor(ac, -1);
	TextDrawSetOutline(ac, 0);
	TextDrawSetProportional(ac, 1);
	TextDrawSetShadow(ac, 1);
	TextDrawUseBox(ac, 1);
	TextDrawBoxColor(ac, 65331);
	TextDrawTextSize(ac, 30.000000, 21.000000);
	TextDrawSetSelectable(ac, 1);
	//Wars
	gBox = TextDrawCreate(581.000000, 182.000000, "_");
	TextDrawAlignment(gBox, 2);
	TextDrawLetterSize(gBox, 0.500000, 6.700000);
	TextDrawColor(gBox, -1);
	TextDrawSetOutline(gBox, 0);
	TextDrawSetProportional(gBox, 1);
	TextDrawSetShadow(gBox, 1);
	TextDrawUseBox(gBox, 1);
	TextDrawBoxColor(gBox, 34);
	TextDrawTextSize(gBox, 30.000000, 90.000000);
	TextDrawSetSelectable(gBox, 0);

	gArea = TextDrawCreate(569.000000, 227.000000, "Area ID:");
	TextDrawAlignment(gArea, 2);
	TextDrawBackgroundColor(gArea, 255);
	TextDrawFont(gArea, 2);
	TextDrawLetterSize(gArea, 0.200000, 1.000000);
	TextDrawColor(gArea, 16777215);
	TextDrawSetOutline(gArea, 0);
	TextDrawSetProportional(gArea, 1);
	TextDrawSetShadow(gArea, 1);
	TextDrawSetSelectable(gArea, 0);
	
	gsTime = TextDrawCreate(562.000000, 185.000000, "Time:");
	TextDrawAlignment(gsTime, 2);
	TextDrawBackgroundColor(gsTime, 255);
	TextDrawFont(gsTime, 2);
	TextDrawLetterSize(gsTime, 0.180000, 1.300000);
	TextDrawColor(gsTime, -252706561);
	TextDrawSetOutline(gsTime, 0);
	TextDrawSetProportional(gsTime, 1);
	TextDrawSetShadow(gsTime, 1);
	TextDrawSetSelectable(gsTime, 0);
	//========= Gun ===
	cBox = TextDrawCreate(330.000000, 78.000000, "_");
	TextDrawAlignment(cBox, 2);
	TextDrawBackgroundColor(cBox, 68);
	TextDrawFont(cBox, 1);
	TextDrawLetterSize(cBox, 0.500000, 23.000000);
	TextDrawColor(cBox, -1);
	TextDrawSetOutline(cBox, 0);
	TextDrawSetProportional(cBox, 1);
	TextDrawSetShadow(cBox, 1);
	TextDrawUseBox(cBox, 1);
	TextDrawBoxColor(cBox, 34);
	TextDrawTextSize(cBox, 0.000000, 183.000000);
	TextDrawSetSelectable(cBox, 0);

	cMYG = TextDrawCreate(329.000000, 79.000000, "Make You Gun");
	TextDrawAlignment(cMYG, 2);
	TextDrawBackgroundColor(cMYG, 255);
	TextDrawFont(cMYG, 2);
	TextDrawLetterSize(cMYG, 0.300000, 2.000000);
	TextDrawColor(cMYG, -1);
	TextDrawSetOutline(cMYG, 0);
	TextDrawSetProportional(cMYG, 1);
	TextDrawSetShadow(cMYG, 1);
	TextDrawSetSelectable(cMYG, 0);

	cXc = TextDrawCreate(414.000000, 65.000000, "LD_BEAT:cross");
	TextDrawAlignment(cXc, 2);
	TextDrawBackgroundColor(cXc, 255);
	TextDrawFont(cXc, 4);
	TextDrawLetterSize(cXc, 1.190000, 1.500000);
	TextDrawColor(cXc, -16776961);
	TextDrawSetOutline(cXc, 0);
	TextDrawSetProportional(cXc, 1);
	TextDrawSetShadow(cXc, 1);
	TextDrawUseBox(cXc, 1);
	TextDrawBoxColor(cXc, -16777114);
	TextDrawTextSize(cXc, 8.000000, 9.000000);
	TextDrawSetSelectable(cXc, 1);

	c1 = TextDrawCreate(253.000000, 130.000000, "1");
	TextDrawBackgroundColor(c1, 0);
	TextDrawFont(c1, 5);
	TextDrawLetterSize(c1, 2.549999, 6.499999);
	TextDrawColor(c1, -1);
	TextDrawSetOutline(c1, 0);
	TextDrawSetProportional(c1, 1);
	TextDrawSetShadow(c1, 1);
	TextDrawUseBox(c1, 1);
	TextDrawBoxColor(c1, 0);
	TextDrawTextSize(c1, 49.000000, 54.000000);
	TextDrawSetPreviewModel(c1, 348);
	TextDrawSetPreviewRot(c1, 0.000000, 0.000000, 67.000000, 1.000000);
	TextDrawSetSelectable(c1, 1);

	c2 = TextDrawCreate(304.000000, 130.000000, "2");
	TextDrawBackgroundColor(c2, 0);
	TextDrawFont(c2, 5);
	TextDrawLetterSize(c2, 2.549999, 6.499999);
	TextDrawColor(c2, -1);
	TextDrawSetOutline(c2, 0);
	TextDrawSetProportional(c2, 1);
	TextDrawSetShadow(c2, 1);
	TextDrawUseBox(c2, 1);
	TextDrawBoxColor(c2, 0);
	TextDrawTextSize(c2, 57.000000, 57.000000);
	TextDrawSetPreviewModel(c2, 347);
	TextDrawSetPreviewRot(c2, 347.000000, -10.000000, 60.000000, 1.000000);
	TextDrawSetSelectable(c2, 1);

	c3 = TextDrawCreate(362.000000, 130.000000, "3");
	TextDrawBackgroundColor(c3, 0);
	TextDrawFont(c3, 5);
	TextDrawLetterSize(c3, 2.549999, 6.499999);
	TextDrawColor(c3, -1);
	TextDrawSetOutline(c3, 0);
	TextDrawSetProportional(c3, 1);
	TextDrawSetShadow(c3, 1);
	TextDrawUseBox(c3, 1);
	TextDrawBoxColor(c3, 0);
	TextDrawTextSize(c3, 57.000000, 57.000000);
	TextDrawSetPreviewModel(c3, 349);
	TextDrawSetPreviewRot(c3, -10.000000, -30.000000, 0.000000, 2.000000);
	TextDrawSetSelectable(c3, 1);
	
	c4 = TextDrawCreate(253.000000, 194.000000, "4");
	TextDrawBackgroundColor(c4, 0);
	TextDrawFont(c4, 5);
	TextDrawLetterSize(c4, 2.549999, 6.499999);
	TextDrawColor(c4, -1);
	TextDrawSetOutline(c4, 0);
	TextDrawSetProportional(c4, 1);
	TextDrawSetShadow(c4, 1);
	TextDrawUseBox(c4, 1);
	TextDrawBoxColor(c4, 0);
	TextDrawTextSize(c4, 49.000000, 54.000000);
	TextDrawSetPreviewModel(c4, 355);
	TextDrawSetPreviewRot(c4, 0.000000, -40.000000, 0.000000, 1.600000);
	TextDrawSetSelectable(c4, 1);

	c5 = TextDrawCreate(309.000000, 194.000000, "5");
	TextDrawBackgroundColor(c5, 0);
	TextDrawFont(c5, 5);
	TextDrawLetterSize(c5, 2.549999, 6.499999);
	TextDrawColor(c5, -1);
	TextDrawSetOutline(c5, 0);
	TextDrawSetProportional(c5, 1);
	TextDrawSetShadow(c5, 1);
	TextDrawUseBox(c5, 1);
	TextDrawBoxColor(c5, 0);
	TextDrawTextSize(c5, 49.000000, 54.000000);
	TextDrawSetPreviewModel(c5, 356);
	TextDrawSetPreviewRot(c5, 0.000000, -40.000000, 0.000000, 1.600000);
	TextDrawSetSelectable(c5, 1);

	c6 = TextDrawCreate(364.000000, 194.000000, "6");
	TextDrawBackgroundColor(c6, 0);
	TextDrawFont(c6, 5);
	TextDrawLetterSize(c6, 2.549999, 6.499999);
	TextDrawColor(c6, -1);
	TextDrawSetOutline(c6, 0);
	TextDrawSetProportional(c6, 1);
	TextDrawSetShadow(c6, 1);
	TextDrawUseBox(c6, 1);
	TextDrawBoxColor(c6, 0);
	TextDrawTextSize(c6, 49.000000, 54.000000);
	TextDrawSetPreviewModel(c6, 353);
	TextDrawSetPreviewRot(c6, 0.000000, -10.000000, 50.000000, 1.600000);
	TextDrawSetSelectable(c6, 1);

	cDeagle = TextDrawCreate(261.000000, 180.000000, "Deagle");
	TextDrawBackgroundColor(cDeagle, 255);
	TextDrawFont(cDeagle, 2);
	TextDrawLetterSize(cDeagle, 0.200000, 1.000000);
	TextDrawColor(cDeagle, -16776961);
	TextDrawSetOutline(cDeagle, 0);
	TextDrawSetProportional(cDeagle, 1);
	TextDrawSetShadow(cDeagle, 1);
	TextDrawSetSelectable(cDeagle, 0);

	cKolt = TextDrawCreate(315.000000, 180.000000, "Kolt-45");
	TextDrawBackgroundColor(cKolt, 255);
	TextDrawFont(cKolt, 2);
	TextDrawLetterSize(cKolt, 0.200000, 1.000000);
	TextDrawColor(cKolt, -16776961);
	TextDrawSetOutline(cKolt, 0);
	TextDrawSetProportional(cKolt, 1);
	TextDrawSetShadow(cKolt, 1);
	TextDrawSetSelectable(cKolt, 0);

	cShotgun = TextDrawCreate(370.000000, 180.000000, "Shotgun");
	TextDrawBackgroundColor(cShotgun, 255);
	TextDrawFont(cShotgun, 2);
	TextDrawLetterSize(cShotgun, 0.200000, 1.000000);
	TextDrawColor(cShotgun, -16776961);
	TextDrawSetOutline(cShotgun, 0);
	TextDrawSetProportional(c6, 1);
	TextDrawSetShadow(cShotgun, 1);
	TextDrawSetSelectable(cShotgun, 0);

	cAKM = TextDrawCreate(265.000000, 240.000000, "AK-47");
	TextDrawBackgroundColor(cAKM, 255);
	TextDrawFont(cAKM, 2);
	TextDrawLetterSize(cAKM, 0.200000, 1.000000);
	TextDrawColor(cAKM, -16776961);
	TextDrawSetOutline(cAKM, 0);
	TextDrawSetProportional(cAKM, 1);
	TextDrawSetShadow(cAKM, 1);
	TextDrawSetSelectable(cAKM, 0);

	cM4A1 = TextDrawCreate(323.000000, 240.000000, "M4A1");
	TextDrawBackgroundColor(cM4A1, 255);
	TextDrawFont(cM4A1, 2);
	TextDrawLetterSize(cM4A1, 0.200000, 1.000000);
	TextDrawColor(cM4A1, -16776961);
	TextDrawSetOutline(cM4A1, 0);
	TextDrawSetProportional(cM4A1, 1);
	TextDrawSetShadow(cM4A1, 1);
	TextDrawSetSelectable(cM4A1, 0);

	cMP5 = TextDrawCreate(379.000000, 240.000000, "MP5");
	TextDrawBackgroundColor(cMP5, 255);
	TextDrawFont(cMP5, 2);
	TextDrawLetterSize(cMP5, 0.200000, 1.000000);
	TextDrawColor(cMP5, -16776961);
	TextDrawSetOutline(cMP5, 0);
	TextDrawSetProportional(cMP5, 1);
	TextDrawSetShadow(cMP5, 1);
	TextDrawSetSelectable(cMP5, 0);

	cSAW = TextDrawCreate(330.000000, 268.000000, "Select any weapon");
	TextDrawAlignment(cSAW, 2);
	TextDrawBackgroundColor(cSAW, 255);
	TextDrawFont(cSAW, 2);
	TextDrawLetterSize(cSAW, 0.300000, 2.000000);
	TextDrawColor(cSAW, -1);
	TextDrawSetOutline(cSAW, 0);
	TextDrawSetProportional(cSAW, 1);
	TextDrawSetShadow(cSAW, 1);
	TextDrawSetSelectable(cSAW, 0);
	//==============================================
	mm0 = TextDrawCreate(319.000000, 100.000000, "_");
	TextDrawAlignment(mm0, 2);
	TextDrawBackgroundColor(mm0, 255);
	TextDrawFont(mm0, 1);
	TextDrawLetterSize(mm0, 0.500000, 22.100000);
	TextDrawColor(mm0, -1);
	TextDrawSetOutline(mm0, 0);
	TextDrawSetProportional(mm0, 1);
	TextDrawSetShadow(mm0, 1);
	TextDrawUseBox(mm0, 1);
	TextDrawBoxColor(mm0, 85);
	TextDrawTextSize(mm0, 20.000000, 201.000000);
	TextDrawSetSelectable(mm0, 0);

	mm1 = TextDrawCreate(319.000000, 88.000000, "_");
	TextDrawAlignment(mm1, 2);
	TextDrawBackgroundColor(mm1, 255);
	TextDrawFont(mm1, 1);
	TextDrawLetterSize(mm1, 0.500000, 1.000000);
	TextDrawColor(mm1, -1);
	TextDrawSetOutline(mm1, 0);
	TextDrawSetProportional(mm1, 1);
	TextDrawSetShadow(mm1, 1);
	TextDrawUseBox(mm1, 1);
	TextDrawBoxColor(mm1, 10944511);
	TextDrawTextSize(mm1, 0.000000, 210.000000);
	TextDrawSetSelectable(mm1, 0);

	mm2 = TextDrawCreate(215.000000, 245.000000, "LD_BEAT:chit");
	TextDrawAlignment(mm2, 2);
	TextDrawBackgroundColor(mm2, 0);
	TextDrawFont(mm2, 4);
	TextDrawLetterSize(mm2, 0.500000, 1.000000);
	TextDrawColor(mm2, -1);
	TextDrawSetOutline(mm2, 1);
	TextDrawSetProportional(mm2, 1);
	TextDrawUseBox(mm2, 1);
	TextDrawBoxColor(mm2, 0);
	TextDrawTextSize(mm2, 85.000000, 17.000000);
	TextDrawSetPreviewModel(mm2, 297);
	TextDrawSetPreviewRot(mm2, 0.000000, 0.000000, 25.000000, 1.000000);
	TextDrawSetSelectable(mm2, 0);

	mm3 = TextDrawCreate(316.000000, 88.000000, "MAIN MENU");
	TextDrawAlignment(mm3, 2);
	TextDrawBackgroundColor(mm3, -222);
	TextDrawFont(mm3, 2);
	TextDrawLetterSize(mm3, 0.189999, 0.899999);
	TextDrawColor(mm3, -1);
	TextDrawSetOutline(mm3, 1);
	TextDrawSetProportional(mm3, 1);
	TextDrawSetSelectable(mm3, 0);

	mm4 = TextDrawCreate(319.000000, 302.000000, "_");
	TextDrawAlignment(mm4, 2);
	TextDrawBackgroundColor(mm4, 255);
	TextDrawFont(mm4, 1);
	TextDrawLetterSize(mm4, 0.500000, 4.099998);
	TextDrawColor(mm4, -1);
	TextDrawSetOutline(mm4, 0);
	TextDrawSetProportional(mm4, 1);
	TextDrawSetShadow(mm4, 1);
	TextDrawUseBox(mm4, 1);
	TextDrawBoxColor(mm4, 10944511);
	TextDrawTextSize(mm4, -22.000000, 310.000000);
	TextDrawSetSelectable(mm4, 0);

	mm5 = TextDrawCreate(220.000000, 87.000000, "LD_BEAT:chit");
	TextDrawBackgroundColor(mm5, -1);
	TextDrawFont(mm5, 4);
	TextDrawLetterSize(mm5, 0.500000, 1.000000);
	TextDrawColor(mm5, -1);
	TextDrawSetOutline(mm5, 1);
	TextDrawSetProportional(mm5, 1);
	TextDrawUseBox(mm5, 1);
	TextDrawBoxColor(mm5, 255);
	TextDrawTextSize(mm5, 10.000000, 11.000000);
	TextDrawSetSelectable(mm5, 0);

	mm6 = TextDrawCreate(408.000000, 87.000000, "LD_BEAT:chit");
	TextDrawBackgroundColor(mm6, 255);
	TextDrawFont(mm6, 4);
	TextDrawLetterSize(mm6, 0.500000, 1.000000);
	TextDrawColor(mm6, -1);
	TextDrawSetOutline(mm6, 0);
	TextDrawSetProportional(mm6, 1);
	TextDrawSetShadow(mm6, 1);
	TextDrawUseBox(mm6, 1);
	TextDrawBoxColor(mm6, 255);
	TextDrawTextSize(mm6, 10.000000, 11.000000);
	TextDrawSetSelectable(mm6, 0);

	mm8 = TextDrawCreate(190.000000, 290.000000, "LD_BEAT:chit");
	TextDrawBackgroundColor(mm8, 255);
	TextDrawFont(mm8, 4);
	TextDrawLetterSize(mm8, 0.500000, 1.000000);
	TextDrawColor(mm8, -1);
	TextDrawSetOutline(mm8, 0);
	TextDrawSetProportional(mm8, 1);
	TextDrawSetShadow(mm8, 1);
	TextDrawUseBox(mm8, 1);
	TextDrawBoxColor(mm8, 255);
	TextDrawTextSize(mm8, -51.000000, 61.000000);
	TextDrawSetSelectable(mm8, 0);

	mm9 = TextDrawCreate(500.000000, 290.000000, "LD_BEAT:chit");
	TextDrawBackgroundColor(mm9, 255);
	TextDrawFont(mm9, 4);
	TextDrawLetterSize(mm9, 0.500000, 1.000000);
	TextDrawColor(mm9, -1);
	TextDrawSetOutline(mm9, 0);
	TextDrawSetProportional(mm9, 1);
	TextDrawSetShadow(mm9, 1);
	TextDrawUseBox(mm9, 1);
	TextDrawBoxColor(mm9, 255);
	TextDrawTextSize(mm9, -51.000000, 61.000000);
	TextDrawSetSelectable(mm9, 0);

	mm10 = TextDrawCreate(295.000000, 102.000000, "STATS");
	TextDrawBackgroundColor(mm10, 51);
	TextDrawFont(mm10, 2);
	TextDrawLetterSize(mm10, 0.319999, 1.399999);
	TextDrawColor(mm10, -1);
	TextDrawSetOutline(mm10, 0);
	TextDrawSetProportional(mm10, 1);
	TextDrawSetShadow(mm10, 1);
	TextDrawSetSelectable(mm10, 0);

	mm11 = TextDrawCreate(306.000000, 122.000000, "First Name:");
	TextDrawBackgroundColor(mm11, 51);
	TextDrawFont(mm11, 2);
	TextDrawLetterSize(mm11, 0.150000, 1.100000);
	TextDrawColor(mm11, -1);
	TextDrawSetOutline(mm11, 0);
	TextDrawSetProportional(mm11, 1);
	TextDrawSetShadow(mm11, 1);
	TextDrawSetSelectable(mm11, 0);

	mm12 = TextDrawCreate(306.000000, 132.000000, "Last Name:");
	TextDrawBackgroundColor(mm12, 51);
	TextDrawFont(mm12, 2);
	TextDrawLetterSize(mm12, 0.150000, 1.100000);
	TextDrawColor(mm12, -1);
	TextDrawSetOutline(mm12, 0);
	TextDrawSetProportional(mm12, 1);
	TextDrawSetShadow(mm12, 1);
	TextDrawSetSelectable(mm12, 0);

	mm13 = TextDrawCreate(306.000000, 142.000000, "Age In State:");
	TextDrawBackgroundColor(mm13, 51);
	TextDrawFont(mm13, 2);
	TextDrawLetterSize(mm13, 0.150000, 1.100000);
	TextDrawColor(mm13, -1);
	TextDrawSetOutline(mm13, 0);
	TextDrawSetProportional(mm13, 1);
	TextDrawSetShadow(mm13, 1);
	TextDrawSetSelectable(mm13, 0);

	mm14 = TextDrawCreate(306.000000, 152.000000, "Workplace:");
	TextDrawBackgroundColor(mm14, 51);
	TextDrawFont(mm14, 2);
	TextDrawLetterSize(mm14, 0.150000, 1.100000);
	TextDrawColor(mm14, -1);
	TextDrawSetOutline(mm14, 0);
	TextDrawSetProportional(mm14, 1);
	TextDrawSetShadow(mm14, 1);
	TextDrawSetSelectable(mm14, 0);

	mm15 = TextDrawCreate(306.000000, 162.000000, "Post:");
	TextDrawBackgroundColor(mm15, 51);
	TextDrawFont(mm15, 2);
	TextDrawLetterSize(mm15, 0.150000, 1.100000);
	TextDrawColor(mm15, -1);
	TextDrawSetOutline(mm15, 0);
	TextDrawSetProportional(mm15, 1);
	TextDrawSetShadow(mm15, 1);
	TextDrawSetSelectable(mm15, 0);

	mm16 = TextDrawCreate(306.000000, 172.000000, "SEX:");
	TextDrawBackgroundColor(mm16, 51);
	TextDrawFont(mm16, 2);
	TextDrawLetterSize(mm16, 0.150000, 1.100000);
	TextDrawColor(mm16, -1);
	TextDrawSetOutline(mm16, 0);
	TextDrawSetProportional(mm16, 1);
	TextDrawSetShadow(mm16, 1);
	TextDrawSetSelectable(mm16, 0);

	mm17 = TextDrawCreate(306.000000, 182.000000, "Phone:");
	TextDrawBackgroundColor(mm17, 51);
	TextDrawFont(mm17, 2);
	TextDrawLetterSize(mm17, 0.150000, 1.100000);
	TextDrawColor(mm17, -1);
	TextDrawSetOutline(mm17, 0);
	TextDrawSetProportional(mm17, 1);
	TextDrawSetShadow(mm17, 1);
	TextDrawSetSelectable(mm17, 0);

	mm18 = TextDrawCreate(306.000000, 192.000000, "L-IP:");
	TextDrawBackgroundColor(mm18, 51);
	TextDrawFont(mm18, 2);
	TextDrawLetterSize(mm18, 0.150000, 1.100000);
	TextDrawColor(mm18, -1);
	TextDrawSetOutline(mm18, 0);
	TextDrawSetProportional(mm18, 1);
	TextDrawSetShadow(mm18, 1);
	TextDrawSetSelectable(mm18, 0);

	mm19 = TextDrawCreate(306.000000, 202.000000, "Level Investigation:");
	TextDrawBackgroundColor(mm19, 51);
	TextDrawFont(mm19, 2);
	TextDrawLetterSize(mm19, 0.150000, 1.100000);
	TextDrawColor(mm19, -1);
	TextDrawSetOutline(mm19, 0);
	TextDrawSetProportional(mm19, 1);
	TextDrawSetShadow(mm19, 1);
	TextDrawSetSelectable(mm19, 0);

	mm29 = TextDrawCreate(427.000000, 68.000000, "LD_BEAT:cross");
	TextDrawBackgroundColor(mm29, 255);
	TextDrawFont(mm29, 4);
	TextDrawLetterSize(mm29, 0.500000, 1.000000);
	TextDrawColor(mm29, 767361023);
	TextDrawSetOutline(mm29, 0);
	TextDrawSetProportional(mm29, 1);
	TextDrawSetShadow(mm29, 1);
	TextDrawUseBox(mm29, 1);
	TextDrawBoxColor(mm29, 255);
	TextDrawTextSize(mm29, 10.000000, 11.000000);
	TextDrawSetSelectable(mm29, 1);

	mm30 = TextDrawCreate(186.000000, 328.000000, "LD_BEAT:chit");
	TextDrawBackgroundColor(mm30, 255);
	TextDrawFont(mm30, 4);
	TextDrawLetterSize(mm30, 0.500000, 1.000000);
	TextDrawColor(mm30, 255);
	TextDrawSetOutline(mm30, 0);
	TextDrawSetProportional(mm30, 1);
	TextDrawSetShadow(mm30, 1);
	TextDrawUseBox(mm30, 1);
	TextDrawBoxColor(mm30, 255);
	TextDrawTextSize(mm30, 70.000000, 11.000000);
	TextDrawSetSelectable(mm30, 0);

	mm31 = TextDrawCreate(208.000000, 329.000000, "REPORT");
	TextDrawBackgroundColor(mm31, 153);
	TextDrawFont(mm31, 2);
	TextDrawLetterSize(mm31, 0.159998, 0.899999);
	TextDrawColor(mm31, -16776961);
	TextDrawSetOutline(mm31, 0);
	TextDrawSetProportional(mm31, 1);
	TextDrawSetShadow(mm31, 1);
	TextDrawSetSelectable(mm31, 0);

	mm32 = TextDrawCreate(205.000000, 301.000000, "reportmodel");
	TextDrawBackgroundColor(mm32, 0);
	TextDrawFont(mm32, 5);
	TextDrawLetterSize(mm32, 1.000000, 1.000000);
	TextDrawColor(mm32, -1);
	TextDrawSetOutline(mm32, 0);
	TextDrawSetProportional(mm32, 1);
	TextDrawSetShadow(mm32, 1);
	TextDrawUseBox(mm32, 1);
	TextDrawBoxColor(mm32, 0);
	TextDrawTextSize(mm32, 30.000000, 40.000000);
	TextDrawSetPreviewModel(mm32, 1247);
	TextDrawSetPreviewRot(mm32, -16.000000, 0.000000, 25.000000, 1.000000);
	TextDrawSetSelectable(mm32, 1);

	mm33 = TextDrawCreate(253.000000, 328.000000, "LD_BEAT:chit");
	TextDrawBackgroundColor(mm33, 255);
	TextDrawFont(mm33, 4);
	TextDrawLetterSize(mm33, 0.500000, 1.000000);
	TextDrawColor(mm33, 255);
	TextDrawSetOutline(mm33, 0);
	TextDrawSetProportional(mm33, 1);
	TextDrawSetShadow(mm33, 1);
	TextDrawUseBox(mm33, 1);
	TextDrawBoxColor(mm33, 255);
	TextDrawTextSize(mm33, 70.000000, 11.000000);
	TextDrawSetSelectable(mm33, 0);

	mm34 = TextDrawCreate(272.000000, 329.000000, "SETTINGS");
	TextDrawBackgroundColor(mm34, 153);
	TextDrawFont(mm34, 2);
	TextDrawLetterSize(mm34, 0.159998, 0.899999);
	TextDrawColor(mm34, -1);
	TextDrawSetOutline(mm34, 0);
	TextDrawSetProportional(mm34, 1);
	TextDrawSetShadow(mm34, 1);
	TextDrawSetSelectable(mm34, 0);

	mm35 = TextDrawCreate(269.000000, 299.000000, "settingmodel");
	TextDrawBackgroundColor(mm35, 0);
	TextDrawFont(mm35, 5);
	TextDrawLetterSize(mm35, 1.000000, 1.000000);
	TextDrawColor(mm35, -1);
	TextDrawSetOutline(mm35, 0);
	TextDrawSetProportional(mm35, 1);
	TextDrawSetShadow(mm35, 1);
	TextDrawUseBox(mm35, 1);
	TextDrawBoxColor(mm35, 0);
	TextDrawTextSize(mm35, 30.000000, 40.000000);
	TextDrawSetPreviewModel(mm35, 18638);
	TextDrawSetPreviewRot(mm35, 65.000000, 292.000000, 68.000000, 0.699998);
	TextDrawSetSelectable(mm35, 1);

	mm36 = TextDrawCreate(320.000000, 328.000000, "LD_BEAT:chit");
	TextDrawBackgroundColor(mm36, 255);
	TextDrawFont(mm36, 4);
	TextDrawLetterSize(mm36, 0.500000, 1.000000);
	TextDrawColor(mm36, 255);
	TextDrawSetOutline(mm36, 0);
	TextDrawSetProportional(mm36, 1);
	TextDrawSetShadow(mm36, 1);
	TextDrawUseBox(mm36, 1);
	TextDrawBoxColor(mm36, 255);
	TextDrawTextSize(mm36, 70.000000, 11.000000);
	TextDrawSetSelectable(mm36, 0);

	mm37 = TextDrawCreate(387.000000, 328.000000, "LD_BEAT:chit");
	TextDrawBackgroundColor(mm37, 255);
	TextDrawFont(mm37, 4);
	TextDrawLetterSize(mm37, 0.500000, 1.000000);
	TextDrawColor(mm37, 255);
	TextDrawSetOutline(mm37, 0);
	TextDrawSetProportional(mm37, 1);
	TextDrawSetShadow(mm37, 1);
	TextDrawUseBox(mm37, 1);
	TextDrawBoxColor(mm37, 255);
	TextDrawTextSize(mm37, 70.000000, 11.000000);
	TextDrawSetSelectable(mm37, 0);

	mm38 = TextDrawCreate(354.000000, 329.000000, "HELP");
	TextDrawAlignment(mm38, 2);
	TextDrawBackgroundColor(mm38, 153);
	TextDrawFont(mm38, 2);
	TextDrawLetterSize(mm38, 0.159998, 0.899999);
	TextDrawColor(mm38, 16711935);
	TextDrawSetOutline(mm38, 0);
	TextDrawSetProportional(mm38, 1);
	TextDrawSetShadow(mm38, 1);
	TextDrawSetSelectable(mm38, 0);

	mm39 = TextDrawCreate(337.000000, 298.000000, "helpmodel");
	TextDrawBackgroundColor(mm39, 0);
	TextDrawFont(mm39, 5);
	TextDrawLetterSize(mm39, 1.000000, 1.000000);
	TextDrawColor(mm39, -1);
	TextDrawSetOutline(mm39, 0);
	TextDrawSetProportional(mm39, 1);
	TextDrawSetShadow(mm39, 1);
	TextDrawUseBox(mm39, 1);
	TextDrawBoxColor(mm39, 0);
	TextDrawTextSize(mm39, 30.000000, 40.000000);
	TextDrawSetPreviewModel(mm39, 1239);
	TextDrawSetPreviewRot(mm39, 0.000000, 0.000000, 0.000000, 1.000000);
	TextDrawSetSelectable(mm39, 1);

	mm40 = TextDrawCreate(422.000000, 329.000000, "DONATE");
	TextDrawAlignment(mm40, 2);
	TextDrawBackgroundColor(mm40, 153);
	TextDrawFont(mm40, 2);
	TextDrawLetterSize(mm40, 0.159998, 0.899999);
	TextDrawColor(mm40, -16776961);
	TextDrawSetOutline(mm40, 0);
	TextDrawSetProportional(mm40, 1);
	TextDrawSetShadow(mm40, 1);
	TextDrawSetSelectable(mm40, 0);

	mm41 = TextDrawCreate(403.000000, 298.000000, "donatmodel");
	TextDrawBackgroundColor(mm41, 0);
	TextDrawFont(mm41, 5);
	TextDrawLetterSize(mm41, 1.000000, 1.000000);
	TextDrawColor(mm41, -1);
	TextDrawSetOutline(mm41, 0);
	TextDrawSetProportional(mm41, 1);
	TextDrawSetShadow(mm41, 1);
	TextDrawUseBox(mm41, 1);
	TextDrawBoxColor(mm41, 0);
	TextDrawTextSize(mm41, 30.000000, 40.000000);
	TextDrawSetPreviewModel(mm41, 1550);
	TextDrawSetPreviewRot(mm41, -20.000000, 0.000000, 30.000000, 0.800000);
	TextDrawSetSelectable(mm41, 1);

	mm42 = TextDrawCreate(303.000000, 228.000000, "house");
	TextDrawBackgroundColor(mm42, 0);
	TextDrawFont(mm42, 5);
	TextDrawLetterSize(mm42, 0.500000, 1.000000);
	TextDrawColor(mm42, -1);
	TextDrawSetOutline(mm42, 0);
	TextDrawSetProportional(mm42, 1);
	TextDrawSetShadow(mm42, 1);
	TextDrawUseBox(mm42, 1);
	TextDrawBoxColor(mm42, 0);
	TextDrawTextSize(mm42, 30.000000, 31.000000);
	TextDrawSetPreviewModel(mm42, 1272);
	TextDrawSetPreviewRot(mm42, -16.000000, 0.000000, 25.000000, 1.000000);
	TextDrawSetSelectable(mm42, 0);

	mm44 = TextDrawCreate(380.000000, 230.000000, "biz");
	TextDrawBackgroundColor(mm44, 0);
	TextDrawFont(mm44, 5);
	TextDrawLetterSize(mm44, 0.500000, 1.000000);
	TextDrawColor(mm44, -1);
	TextDrawSetOutline(mm44, 0);
	TextDrawSetProportional(mm44, 1);
	TextDrawSetShadow(mm44, 1);
	TextDrawUseBox(mm44, 1);
	TextDrawBoxColor(mm44, 0);
	TextDrawTextSize(mm44, 30.000000, 31.000000);
	TextDrawSetPreviewModel(mm44, 1274);
	TextDrawSetPreviewRot(mm44, 0.000000, 0.000000, 200.000000, 1.000000);
	TextDrawSetSelectable(mm44, 0);
	//==
	sbox = TextDrawCreate(541.000000, 380.000000, "_");
	TextDrawAlignment(sbox, 2);
	TextDrawBackgroundColor(sbox, 255);
	TextDrawFont(sbox, 1);
	TextDrawLetterSize(sbox, 0.509999, 5.899999);
	TextDrawColor(sbox, -1);
	TextDrawSetOutline(sbox, 0);
	TextDrawSetProportional(sbox, 1);
	TextDrawSetShadow(sbox, 1);
	TextDrawUseBox(sbox, 1);
	TextDrawBoxColor(sbox, 85);
	TextDrawTextSize(sbox, -4.000000, 153.000000);
	TextDrawSetSelectable(sbox, 0);

	skmh = TextDrawCreate(512.000000, 384.000000, "KM/H:");
	TextDrawBackgroundColor(skmh, 255);
	TextDrawFont(skmh, 2);
	TextDrawLetterSize(skmh, 0.250000, 1.200000);
	TextDrawColor(skmh, 11468799);
	TextDrawSetOutline(skmh, 0);
	TextDrawSetProportional(skmh, 1);
	TextDrawSetShadow(skmh, 1);
	TextDrawSetSelectable(skmh, 0);

	sfuel = TextDrawCreate(512.000000, 402.000000, "FUEL:");
	TextDrawBackgroundColor(sfuel, 255);
	TextDrawFont(sfuel, 2);
	TextDrawLetterSize(sfuel, 0.250000, 1.200000);
	TextDrawColor(sfuel, 11468799);
	TextDrawSetOutline(sfuel, 0);
	TextDrawSetProportional(sfuel, 1);
	TextDrawSetShadow(sfuel, 1);
	TextDrawSetSelectable(sfuel, 0);
	//=============== RECON ============
	rbox = TextDrawCreate(557.000000, 120.000000, "_");
	TextDrawAlignment(rbox, 2);
	TextDrawBackgroundColor(rbox, 255);
	TextDrawFont(rbox, 1);
	TextDrawLetterSize(rbox, 1.600000, 18.000000);
	TextDrawColor(rbox, -1);
	TextDrawSetOutline(rbox, 0);
	TextDrawSetProportional(rbox, 1);
	TextDrawSetShadow(rbox, 1);
	TextDrawUseBox(rbox, 1);
	TextDrawBoxColor(rbox, 68);
	TextDrawTextSize(rbox, 20.000000, 101.000000);
	TextDrawSetSelectable(rbox, 0);
	
	rcopy = TextDrawCreate(550.000000, 275.000000, "admin cp Cheery rp");
	TextDrawBackgroundColor(rcopy, 255);
	TextDrawFont(rcopy, 2);
	TextDrawLetterSize(rcopy, 0.129999, 0.699998);
	TextDrawColor(rcopy, -1);
	TextDrawSetOutline(rcopy, 0);
	TextDrawSetProportional(rcopy, 1);
	TextDrawSetShadow(rcopy, 1);
	TextDrawSetSelectable(rcopy, 0);

	rvbox = TextDrawCreate(557.000000, 300.000000, "_");
	TextDrawAlignment(rvbox, 2);
	TextDrawBackgroundColor(rvbox, 255);
	TextDrawFont(rvbox, 1);
	TextDrawLetterSize(rvbox, 1.600000, 6.000000);
	TextDrawColor(rvbox, -1);
	TextDrawSetOutline(rvbox, 0);
	TextDrawSetProportional(rvbox, 1);
	TextDrawSetShadow(rvbox, 1);
	TextDrawUseBox(rvbox, 1);
	TextDrawBoxColor(rvbox, 68);
	TextDrawTextSize(rvbox, 20.000000, 101.000000);
	TextDrawSetSelectable(rvbox, 0);

	//========= Ammo =======
	amBox = TextDrawCreate(313.000000, 23.000000, "_");
	TextDrawAlignment(amBox, 2);
	TextDrawBackgroundColor(amBox, 255);
	TextDrawFont(amBox, 1);
	TextDrawLetterSize(amBox, 0.500000, 3.999995);
	TextDrawColor(amBox, -1);
	TextDrawSetOutline(amBox, 0);
	TextDrawSetProportional(amBox, 1);
	TextDrawSetShadow(amBox, 1);
	TextDrawUseBox(amBox, 1);
	TextDrawBoxColor(amBox, 119);
	TextDrawTextSize(amBox, 0.000000, 103.000000);
	TextDrawSetSelectable(amBox, 0);

	amPCPS = TextDrawCreate(264.000000, 45.000000, "PRICE CLIPS:");
	TextDrawBackgroundColor(amPCPS, 255);
	TextDrawFont(amPCPS, 2);
	TextDrawLetterSize(amPCPS, 0.140000, 1.200000);
	TextDrawColor(amPCPS, -1);
	TextDrawSetOutline(amPCPS, 0);
	TextDrawSetProportional(amPCPS, 1);
	TextDrawSetShadow(amPCPS, 1);
	TextDrawSetSelectable(amPCPS, 0);

	amBox2 = TextDrawCreate(543.000000, 382.000000, "_");
	TextDrawAlignment(amBox2, 2);
	TextDrawBackgroundColor(amBox2, 0);
	TextDrawFont(amBox2, 1);
	TextDrawLetterSize(amBox2, 0.500000, 1.799999);
	TextDrawColor(amBox2, 255);
	TextDrawSetOutline(amBox2, 1);
	TextDrawSetProportional(amBox2, 1);
	TextDrawUseBox(amBox2, 1);
	TextDrawBoxColor(amBox2, 119);
	TextDrawTextSize(amBox2, 0.000000, 103.000000);
	TextDrawSetSelectable(amBox2, 0);

	amChit = TextDrawCreate(494.000000, 381.000000, "LD_BEAT:chit");
	TextDrawBackgroundColor(amChit, 255);
	TextDrawFont(amChit, 4);
	TextDrawLetterSize(amChit, 1.149999, 1.299999);
	TextDrawColor(amChit, 1549556991);
	TextDrawSetOutline(amChit, 1);
	TextDrawSetProportional(amChit, 1);
	TextDrawUseBox(amChit, 1);
	TextDrawBoxColor(amChit, 1549556991);
	TextDrawTextSize(amChit, 17.000000, 19.000000);
	TextDrawSetSelectable(amChit, 0);

	amLeft = TextDrawCreate(498.000000, 386.000000, "LD_BEAT:left");
	TextDrawBackgroundColor(amLeft, 255);
	TextDrawFont(amLeft, 4);
	TextDrawLetterSize(amLeft, 1.159999, 1.399999);
	TextDrawColor(amLeft, -1);
	TextDrawSetOutline(amLeft, 1);
	TextDrawSetProportional(amLeft, 1);
	TextDrawUseBox(amLeft, 1);
	TextDrawBoxColor(amLeft, 1549556991);
	TextDrawTextSize(amLeft, 9.000000, 10.000000);
	TextDrawSetSelectable(amLeft, 1);

	amChit2 = TextDrawCreate(574.000000, 381.000000, "LD_BEAT:chit");
	TextDrawBackgroundColor(amChit2, 255);
	TextDrawFont(amChit2, 4);
	TextDrawLetterSize(amChit2, 1.149999, 1.399999);
	TextDrawColor(amChit2, 1549556991);
	TextDrawSetOutline(amChit2, 1);
	TextDrawSetProportional(amChit2, 1);
	TextDrawUseBox(amChit2, 1);
	TextDrawBoxColor(amChit2, 1549556991);
	TextDrawTextSize(amChit2, 17.000000, 19.000000);
	TextDrawSetSelectable(amChit2, 0);

	amRight = TextDrawCreate(579.000000, 386.000000, "LD_BEAT:right");
	TextDrawBackgroundColor(amRight, 255);
	TextDrawFont(amRight, 4);
	TextDrawLetterSize(amRight, 1.159999, 1.399999);
	TextDrawColor(amRight, -1);
	TextDrawSetOutline(amRight, 1);
	TextDrawSetProportional(amRight, 1);
	TextDrawUseBox(amRight, 1);
	TextDrawBoxColor(amRight, 1549556991);
	TextDrawTextSize(amRight, 9.000000, 10.000000);
	TextDrawSetSelectable(amRight, 1);
	
	amBBUY = TextDrawCreate(527.000000, 385.000000, "_");
	TextDrawAlignment(amBBUY, 2);
	TextDrawBackgroundColor(amBBUY, 255);
	TextDrawFont(amBBUY, 0);
	TextDrawLetterSize(amBBUY, 1.159999, 1.099999);
	TextDrawColor(amBBUY, 96492799);
	TextDrawSetOutline(amBBUY, 1);
	TextDrawSetProportional(amBBUY, 1);
	TextDrawUseBox(amBBUY, 1);
	TextDrawBoxColor(amBBUY, 11537527);
	TextDrawTextSize(amBBUY, 29.000000, 22.000000);
	TextDrawSetSelectable(amBBUY, 1);

	amBBACK = TextDrawCreate(556.000000, 385.000000, "_");
	TextDrawAlignment(amBBACK, 2);
	TextDrawBackgroundColor(amBBACK, 255);
	TextDrawFont(amBBACK, 0);
	TextDrawLetterSize(amBBACK, 1.159999, 1.099999);
	TextDrawColor(amBBACK, 96492799);
	TextDrawSetOutline(amBBACK, 1);
	TextDrawSetProportional(amBBACK, 1);
	TextDrawUseBox(amBBACK, 1);
	TextDrawBoxColor(amBBACK, -1023410057);
	TextDrawTextSize(amBBACK, 29.000000, 22.000000);
	TextDrawSetSelectable(amBBACK, 1);
	
	amBUY = TextDrawCreate(517.000000, 386.000000, "BUY");
 	TextDrawBackgroundColor(amBUY, 255);
	TextDrawFont(amBUY, 2);
	TextDrawLetterSize(amBUY, 0.250000, 0.799999);
	TextDrawColor(amBUY, 255);
	TextDrawSetOutline(amBUY, 0);
	TextDrawSetProportional(amBUY, 1);
	TextDrawSetShadow(amBUY, 0);
	TextDrawSetSelectable(amBUY, 0);

	amBack = TextDrawCreate(545.000000, 386.000000, "BACK");
	TextDrawBackgroundColor(amBack, 255);
	TextDrawFont(amBack, 2);
	TextDrawLetterSize(amBack, 0.210000, 0.799999);
	TextDrawColor(amBack, 255);
	TextDrawSetOutline(amBack, 0);
	TextDrawSetProportional(amBack, 1);
	TextDrawSetShadow(amBack, 0);
	TextDrawSetSelectable(amBack, 0);
	//==== LOGO ====
	LCheery = TextDrawCreate(547.000000, 4.000000, "Cheery");
	TextDrawBackgroundColor(LCheery, 153);
	TextDrawFont(LCheery, 3);
	TextDrawLetterSize(LCheery, 0.319999, 0.999998);
	TextDrawColor(LCheery, -1);
	TextDrawSetOutline(LCheery, 1);
	TextDrawSetProportional(LCheery, 1);
	TextDrawSetSelectable(LCheery, 0);

	LRole = TextDrawCreate(552.000000, 13.000000, "Role");
	TextDrawBackgroundColor(LRole, 153);
	TextDrawFont(LRole, 3);
	TextDrawLetterSize(LRole, 0.319999, 0.999998);
	TextDrawColor(LRole, -1);
	TextDrawSetOutline(LRole, 1);
	TextDrawSetProportional(LRole, 1);
	TextDrawSetSelectable(LRole, 0);

	LPlay = TextDrawCreate(550.000000, 22.000000, "Play");
	TextDrawBackgroundColor(LPlay, 153);
	TextDrawFont(LPlay, 3);
	TextDrawLetterSize(LPlay, 0.319999, 0.999998);
	TextDrawColor(LPlay, -1);
	TextDrawSetOutline(LPlay, 1);
	TextDrawSetProportional(LPlay, 1);
	TextDrawSetSelectable(LPlay, 0);

	Lchit = TextDrawCreate(580.000000, 24.000000, "LD_BEAT:chit");
	TextDrawBackgroundColor(Lchit, 10092441);
	TextDrawFont(Lchit, 4);
	TextDrawLetterSize(Lchit, 0.270000, 2.900000);
	TextDrawColor(Lchit, 10092356);
	TextDrawSetOutline(Lchit, 1);
	TextDrawSetProportional(Lchit, 1);
	TextDrawUseBox(Lchit, 1);
	TextDrawBoxColor(Lchit, 255);
	TextDrawTextSize(Lchit, 51.000000, 9.000000);
	TextDrawSetSelectable(Lchit, 0);

	Ln1 = TextDrawCreate(593.000000, 3.000000, "#1");
	TextDrawBackgroundColor(Ln1, 10092322);
	TextDrawFont(Ln1, 3);
	TextDrawLetterSize(Ln1, 0.409999, 3.000000);
	TextDrawColor(Ln1, -1);
	TextDrawSetOutline(Ln1, 1);
	TextDrawSetProportional(Ln1, 1);
	TextDrawSetSelectable(Ln1, 0);
	//==== Autosalon
	asBox = TextDrawCreate(119.000000, 231.000000, "_");
	TextDrawAlignment(asBox, 2);
	TextDrawBackgroundColor(asBox, 255);
	TextDrawFont(asBox, 2);
	TextDrawLetterSize(asBox, 1.000000, 4.000000);
	TextDrawColor(asBox, -1);
	TextDrawSetOutline(asBox, 0);
	TextDrawSetProportional(asBox, 1);
	TextDrawSetShadow(asBox, 1);
	TextDrawUseBox(asBox, 1);
	TextDrawBoxColor(asBox, 85);
	TextDrawTextSize(asBox, 0.000000, 161.000000);
	TextDrawSetSelectable(asBox, 0);


	asCost = TextDrawCreate(44.000000, 245.000000, "Cost:");
	TextDrawBackgroundColor(asCost, 255);
	TextDrawFont(asCost, 2);
	TextDrawLetterSize(asCost, 0.280000, 1.599998);
	TextDrawColor(asCost, 96492799);
	TextDrawSetOutline(asCost, 0);
	TextDrawSetProportional(asCost, 1);
	TextDrawSetShadow(asCost, 1);
	TextDrawSetSelectable(asCost, 0);
	
	asLeft = TextDrawCreate(37.000000, 273.000000, "LD_BEAT:left");
	TextDrawBackgroundColor(asLeft, 255);
	TextDrawFont(asLeft, 4);
	TextDrawLetterSize(asLeft, 0.509999, 1.100000);
	TextDrawColor(asLeft, -1);
	TextDrawSetOutline(asLeft, 0);
	TextDrawSetProportional(asLeft, 1);
	TextDrawSetShadow(asLeft, 1);
	TextDrawUseBox(asLeft, 1);
	TextDrawBoxColor(asLeft, 255);
	TextDrawTextSize(asLeft, 20.000000, 21.000000);
	TextDrawSetSelectable(asLeft, 1);

	asRight = TextDrawCreate(182.000000, 272.000000, "LD_BEAT:right");
	TextDrawBackgroundColor(asRight, 255);
	TextDrawFont(asRight, 4);
	TextDrawLetterSize(asRight, 0.509999, 1.100000);
	TextDrawColor(asRight, -1);
	TextDrawSetOutline(asRight, 0);
	TextDrawSetProportional(asRight, 1);
	TextDrawSetShadow(asRight, 1);
	TextDrawUseBox(asRight, 1);
	TextDrawBoxColor(asRight, 255);
	TextDrawTextSize(asRight, 20.000000, 21.000000);
	TextDrawSetSelectable(asRight, 1);

	asBuy = TextDrawCreate(77.000000, 277.000000, "BUY");
	TextDrawBackgroundColor(asBuy, 255);
	TextDrawFont(asBuy, 3);
	TextDrawLetterSize(asBuy, 0.509999, 1.100000);
	TextDrawColor(asBuy, 96492799);
	TextDrawSetOutline(asBuy, 0);
	TextDrawSetProportional(asBuy, 1);
	TextDrawSetShadow(asBuy, 0);
	TextDrawSetSelectable(asBuy, 0);

	asExit = TextDrawCreate(128.000000, 277.000000, "exit");
	TextDrawBackgroundColor(asExit, 255);
	TextDrawFont(asExit, 3);
	TextDrawLetterSize(asExit, 0.509999, 1.100000);
	TextDrawColor(asExit, -1401588225);
	TextDrawSetOutline(asExit, 0);
	TextDrawSetProportional(asExit, 1);
	TextDrawSetShadow(asExit, 0);
	TextDrawSetSelectable(asExit, 0);

	asBBuy = TextDrawCreate(66.000000, 271.000000, "LD_OTB2:ButnC");
	TextDrawBackgroundColor(asBBuy, 255);
	TextDrawFont(asBBuy, 4);
	TextDrawLetterSize(asBBuy, 0.500000, 1.000000);
	TextDrawColor(asBBuy, 96492629);
	TextDrawSetOutline(asBBuy, 0);
	TextDrawSetProportional(asBBuy, 1);
	TextDrawSetShadow(asBBuy, 1);
	TextDrawUseBox(asBBuy, 1);
	TextDrawBoxColor(asBBuy, 255);
	TextDrawTextSize(asBBuy, 50.000000, 40.000000);
	TextDrawSetSelectable(asBBuy, 1);

	asBExit = TextDrawCreate(120.000000, 271.000000, "LD_OTB2:ButnC");
	TextDrawBackgroundColor(asBExit, 255);
	TextDrawFont(asBExit, 4);
	TextDrawLetterSize(asBExit, 0.500000, 1.000000);
	TextDrawColor(asBExit, -1401588395);
	TextDrawSetOutline(asBExit, 0);
	TextDrawSetProportional(asBExit, 1);
	TextDrawSetShadow(asBExit, 1);
	TextDrawUseBox(asBExit, 1);
	TextDrawBoxColor(asBExit, 255);
	TextDrawTextSize(asBExit, 50.000000, 40.000000);
	TextDrawSetSelectable(asBExit, 1);
	//======= Race ======
	raBox = TextDrawCreate(321.000000, 220.000000, "_");
	TextDrawAlignment(raBox, 2);
	TextDrawBackgroundColor(raBox, 255);
	TextDrawFont(raBox, 1);
	TextDrawLetterSize(raBox, 0.500000, 20.899999);
	TextDrawColor(raBox, -1);
	TextDrawSetOutline(raBox, 0);
	TextDrawSetProportional(raBox, 1);
	TextDrawSetShadow(raBox, 1);
	TextDrawUseBox(raBox, 1);
	TextDrawBoxColor(raBox, 68);
	TextDrawTextSize(raBox, 10.000000, 160.000000);
	TextDrawSetSelectable(raBox, 0);

	raImg = TextDrawCreate(251.000000, 222.000000, "LD_RCE3:race12");
	TextDrawBackgroundColor(raImg, 0xFFFFFFFF);
	TextDrawFont(raImg, 4);
	TextDrawLetterSize(raImg, 0.500000, 1.000000);
	TextDrawColor(raImg, 0xFFFFFFFF);
	TextDrawSetOutline(raImg, 0);
	TextDrawSetProportional(raImg, 1);
	TextDrawSetShadow(raImg, 1);
	TextDrawUseBox(raImg, 1);
	TextDrawBoxColor(raImg, 0xFFFFFFFF);
	TextDrawTextSize(raImg, 138.000000, 148.000000);
	TextDrawSetSelectable(raImg, 0);

	raTrack = TextDrawCreate(320.000000, 375.000000, "San Fierro Ramp");
	TextDrawAlignment(raTrack, 2);
	TextDrawBackgroundColor(raTrack, 255);
	TextDrawFont(raTrack, 1);
	TextDrawLetterSize(raTrack, 0.300000, 1.400000);
	TextDrawColor(raTrack, -1);
	TextDrawSetOutline(raTrack, 1);
	TextDrawSetProportional(raTrack, 1);
	TextDrawSetSelectable(raTrack, 0);

	raDist = TextDrawCreate(321.000000, 390.000000, "Distance: 5.3 KM");
	TextDrawAlignment(raDist, 2);
	TextDrawBackgroundColor(raDist, 255);
	TextDrawFont(raDist, 1);
	TextDrawLetterSize(raDist, 0.300000, 1.400000);
	TextDrawColor(raDist, -106);
	TextDrawSetOutline(raDist, 1);
	TextDrawSetProportional(raDist, 1);
	TextDrawSetSelectable(raDist, 0);

	raBox2 = TextDrawCreate(321.000000, 198.000000, "_");
	TextDrawAlignment(raBox2, 2);
	TextDrawBackgroundColor(raBox2, 255);
	TextDrawFont(raBox2, 1);
	TextDrawLetterSize(raBox2, 0.600000, 1.499999);
	TextDrawColor(raBox2, -1);
	TextDrawSetOutline(raBox2, 0);
	TextDrawSetProportional(raBox2, 1);
	TextDrawSetShadow(raBox2, 1);
	TextDrawUseBox(raBox2, 1);
	TextDrawBoxColor(raBox2, 85);
	TextDrawTextSize(raBox2, 0.000000, 160.000000);
	TextDrawSetSelectable(raBox2, 0);

	raLeft = TextDrawCreate(242.000000, 198.000000, "LD_BEAT:left");
	TextDrawAlignment(raLeft, 2);
	TextDrawBackgroundColor(raLeft, 255);
	TextDrawFont(raLeft, 4);
	TextDrawLetterSize(raLeft, 0.600000, 1.499999);
	TextDrawColor(raLeft, 1104210227);
	TextDrawSetOutline(raLeft, 0);
	TextDrawSetProportional(raLeft, 1);
	TextDrawSetShadow(raLeft, 1);
	TextDrawUseBox(raLeft, 1);
	TextDrawBoxColor(raLeft, 85);
	TextDrawTextSize(raLeft, 16.000000, 14.000000);
	TextDrawSetSelectable(raLeft, 1);

	raRight = TextDrawCreate(384.000000, 198.000000, "LD_BEAT:right");
	TextDrawAlignment(raRight, 2);
	TextDrawBackgroundColor(raRight, 255);
	TextDrawFont(raRight, 4);
	TextDrawLetterSize(raRight, 0.600000, 1.499999);
	TextDrawColor(raRight, 1104210227);
	TextDrawSetOutline(raRight, 0);
	TextDrawSetProportional(raRight, 1);
	TextDrawSetShadow(raRight, 1);
	TextDrawUseBox(raRight, 1);
	TextDrawBoxColor(raRight, 85);
	TextDrawTextSize(raRight, 16.000000, 14.000000);
	TextDrawSetSelectable(raRight, 1);

	raSRace = TextDrawCreate(321.000000, 178.000000, "Start Race!");
	TextDrawAlignment(raSRace, 2);
	TextDrawBackgroundColor(raSRace, 255);
	TextDrawFont(raSRace, 1);
	TextDrawLetterSize(raSRace, 0.300000, 1.400000);
	TextDrawColor(raSRace, 1104210431);
	TextDrawSetOutline(raSRace, 1);
	TextDrawSetProportional(raSRace, 1);
	TextDrawSetSelectable(raSRace, 0);

	raButS = TextDrawCreate(281.000000, 198.000000, "LD_OTB2:butnC");
	TextDrawAlignment(raButS, 2);
	TextDrawBackgroundColor(raButS, 255);
	TextDrawFont(raButS, 4);
	TextDrawLetterSize(raButS, 0.600000, 1.499999);
	TextDrawColor(raButS, 16711731);
	TextDrawSetOutline(raButS, 0);
	TextDrawSetProportional(raButS, 1);
	TextDrawSetShadow(raButS, 1);
	TextDrawUseBox(raButS, 1);
	TextDrawBoxColor(raButS, 85);
	TextDrawTextSize(raButS, 32.000000, 22.000000);
	TextDrawSetSelectable(raButS, 1);

	raButC = TextDrawCreate(324.000000, 198.000000, "LD_OTB2:butnC");
	TextDrawAlignment(raButC, 2);
	TextDrawBackgroundColor(raButC, 255);
	TextDrawFont(raButC, 4);
	TextDrawLetterSize(raButC, 0.600000, 1.499999);
	TextDrawColor(raButC, -16777165);
	TextDrawSetOutline(raButC, 0);
	TextDrawSetProportional(raButC, 1);
	TextDrawSetShadow(raButC, 1);
	TextDrawUseBox(raButC, 1);
	TextDrawBoxColor(raButC, 85);
	TextDrawTextSize(raButC, 32.000000, 22.000000);
	TextDrawSetSelectable(raButC, 1);

	raStart = TextDrawCreate(297.000000, 199.000000, "START");
	TextDrawAlignment(raStart, 2);
	TextDrawBackgroundColor(raStart, 255);
	TextDrawFont(raStart, 2);
	TextDrawLetterSize(raStart, 0.149999, 0.899999);
	TextDrawColor(raStart, 68);
	TextDrawSetOutline(raStart, 0);
	TextDrawSetProportional(raStart, 1);
	TextDrawSetShadow(raStart, 0);
	TextDrawSetSelectable(raStart, 0);

	raCancel = TextDrawCreate(340.000000, 199.000000, "CANCEL");
	TextDrawAlignment(raCancel, 2);
	TextDrawBackgroundColor(raCancel, 255);
	TextDrawFont(raCancel, 2);
	TextDrawLetterSize(raCancel, 0.149999, 0.899999);
	TextDrawColor(raCancel, 85);
	TextDrawSetOutline(raCancel, 0);
	TextDrawSetProportional(raCancel, 1);
	TextDrawSetShadow(raCancel, 0);
	TextDrawSetSelectable(raCancel, 0);
	//========== INVENTORY ==========
	iBox = TextDrawCreate(320.000000, 137.000000, "_");
	TextDrawAlignment(iBox, 2);
	TextDrawBackgroundColor(iBox, -1);
	TextDrawFont(iBox, 0);
	TextDrawLetterSize(iBox, 0.500000, 17.899995);
	TextDrawColor(iBox, -1);
	TextDrawSetOutline(iBox, 0);
	TextDrawSetProportional(iBox, 1);
	TextDrawSetShadow(iBox, 1);
	TextDrawUseBox(iBox, 1);
	TextDrawBoxColor(iBox, 102);
	TextDrawTextSize(iBox, 210.000000, 239.000000);
	TextDrawSetSelectable(iBox, 0);

	iChit = TextDrawCreate(227.000000, 268.000000, "LD_BEAT:chit");
	TextDrawBackgroundColor(iChit, 0);
	TextDrawFont(iChit, 4);
	TextDrawLetterSize(iChit, 0.469999, 1.000000);
	TextDrawColor(iChit, 882572185);
	TextDrawSetOutline(iChit, 1);
	TextDrawSetProportional(iChit, 1);
	TextDrawUseBox(iChit, 1);
	TextDrawBoxColor(iChit, 1104210431);
	TextDrawTextSize(iChit, 65.000000, 26.000000);
	TextDrawSetPreviewModel(iChit, 78);
	TextDrawSetPreviewRot(iChit, -10.000000, 0.000000, -20.000000, 1.000000);
	TextDrawSetSelectable(iChit, 0);
	
	iInv = TextDrawCreate(320.000000, 125.000000, "INVENTORY");
	TextDrawAlignment(iInv, 2);
	TextDrawBackgroundColor(iInv, 882572066);
	TextDrawFont(iInv, 1);
	TextDrawLetterSize(iInv, 0.300000, 1.000000);
	TextDrawColor(iInv, -1);
	TextDrawSetOutline(iInv, 1);
	TextDrawSetProportional(iInv, 1);
	TextDrawUseBox(iInv, 1);
	TextDrawBoxColor(iInv, 882572287);
	TextDrawTextSize(iInv, 0.000000, 239.000000);
	TextDrawSetSelectable(iInv, 0);

	iDrop = TextDrawCreate(216.000000, 286.000000, "DROP");
	TextDrawAlignment(iDrop, 2);
	TextDrawBackgroundColor(iDrop, 882572117);
	TextDrawFont(iDrop, 2);
	TextDrawLetterSize(iDrop, 0.200000, 0.999997);
	TextDrawColor(iDrop, -1);
	TextDrawSetOutline(iDrop, 0);
	TextDrawSetProportional(iDrop, 1);
	TextDrawSetShadow(iDrop, 0);
	TextDrawUseBox(iDrop, 1);
	TextDrawBoxColor(iDrop, 882572287);
	TextDrawTextSize(iDrop, 50.000000, 24.000000);
	TextDrawSetSelectable(iDrop, 1);

	iCross = TextDrawCreate(426.000000, 125.000000, "LD_BEAT:cross");
	TextDrawAlignment(iCross, 2);
	TextDrawBackgroundColor(iCross, 882572117);
	TextDrawFont(iCross, 4);
	TextDrawLetterSize(iCross, 0.270000, 1.199998);
	TextDrawColor(iCross, 882572134);
	TextDrawSetOutline(iCross, 1);
	TextDrawSetProportional(iCross, 1);
	TextDrawUseBox(iCross, 1);
	TextDrawBoxColor(iCross, -1);
	TextDrawTextSize(iCross, 10.000000, 10.000000);
	TextDrawSetSelectable(iCross, 1);

	iBox12 = TextDrawCreate(216.000000, 143.000000, "_");
	TextDrawAlignment(iBox12, 2);
	TextDrawBackgroundColor(iBox12, 255);
	TextDrawFont(iBox12, 0);
	TextDrawLetterSize(iBox12, 0.500000, 15.199999);
	TextDrawColor(iBox12, -1);
	TextDrawSetOutline(iBox12, 0);
	TextDrawSetProportional(iBox12, 1);
	TextDrawSetShadow(iBox12, 1);
	TextDrawUseBox(iBox12, 1);
	TextDrawBoxColor(iBox12, 882572287);
	TextDrawTextSize(iBox12, 89.000000, 24.000000);
	TextDrawSetSelectable(iBox12, 0);
	
	iBox2 = TextDrawCreate(356.000000, 157.000000, "_");
	TextDrawAlignment(iBox2, 2);
	TextDrawBackgroundColor(iBox2, 255);
	TextDrawFont(iBox2, 0);
	TextDrawLetterSize(iBox2, 0.500000, 14.099999);
	TextDrawColor(iBox2, -1);
	TextDrawSetOutline(iBox2, 0);
	TextDrawSetProportional(iBox2, 1);
	TextDrawSetShadow(iBox2, 1);
	TextDrawUseBox(iBox2, 1);
	TextDrawBoxColor(iBox2, 882572287);
	TextDrawTextSize(iBox2, 89.000000, 125.000000);
	TextDrawSetSelectable(iBox2, 0);

    iUse = TextDrawCreate(356.000000, 273.000000, "USE");
	TextDrawAlignment(iUse, 2);
	TextDrawBackgroundColor(iUse, 32567586);
	TextDrawFont(iUse, 2);
	TextDrawLetterSize(iUse, 0.200000, 0.999997);
	TextDrawColor(iUse, 882572287);
	TextDrawSetOutline(iUse, 0);
	TextDrawSetProportional(iUse, 1);
	TextDrawSetShadow(iUse, 0);
	TextDrawUseBox(iUse, 1);
	TextDrawBoxColor(iUse, -319753729);
	TextDrawTextSize(iUse, 47.000000, 22.000000);
	TextDrawSetSelectable(iUse, 1);

}

apublic LoadPlayerTextDraws(playerid) {
	smodel[playerid] = CreatePlayerTextDraw(playerid,524.000000, 370.000000, "Model");
	PlayerTextDrawBackgroundColor(playerid,smodel[playerid], 0);
	PlayerTextDrawFont(playerid,smodel[playerid], 5);
	PlayerTextDrawLetterSize(playerid,smodel[playerid], -0.899999, 0.300000);
	PlayerTextDrawColor(playerid,smodel[playerid], -1);
	PlayerTextDrawSetOutline(playerid,smodel[playerid], 1);
	PlayerTextDrawSetProportional(playerid,smodel[playerid], 1);
	PlayerTextDrawAlignment(playerid,smodel[playerid], 1);
	PlayerTextDrawBoxColor(playerid,smodel[playerid], 0);
	PlayerTextDrawTextSize(playerid,smodel[playerid], -66.000000, 73.000000);
	PlayerTextDrawSetPreviewModel(playerid, smodel[playerid], 437);
	PlayerTextDrawSetPreviewRot(playerid, smodel[playerid], -10.000000, 0.000000, 20.000000,1.000000);
	PlayerTextDrawSetSelectable(playerid,smodel[playerid], 0);

	sspeed[playerid] = CreatePlayerTextDraw(playerid,550.000000, 383.000000, "0");
	PlayerTextDrawBackgroundColor(playerid,sspeed[playerid], 255);
	PlayerTextDrawFont(playerid,sspeed[playerid], 2);
	PlayerTextDrawLetterSize(playerid,sspeed[playerid], 0.270000, 1.400000);
	PlayerTextDrawColor(playerid,sspeed[playerid], -1);
	PlayerTextDrawSetOutline(playerid,sspeed[playerid], 0);
	PlayerTextDrawSetProportional(playerid,sspeed[playerid], 1);
	PlayerTextDrawSetShadow(playerid,sspeed[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,sspeed[playerid], 0);

	sfuelv[playerid] = CreatePlayerTextDraw(playerid,550.000000, 401.000000, "0");
	PlayerTextDrawBackgroundColor(playerid,sfuelv[playerid], 255);
	PlayerTextDrawFont(playerid,sfuelv[playerid], 2);
	PlayerTextDrawLetterSize(playerid,sfuelv[playerid], 0.270000, 1.400000);
	PlayerTextDrawColor(playerid,sfuelv[playerid], -1);
	PlayerTextDrawSetOutline(playerid,sfuelv[playerid], 0);
	PlayerTextDrawSetProportional(playerid,sfuelv[playerid], 1);
	PlayerTextDrawSetShadow(playerid,sfuelv[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,sfuelv[playerid], 0);

	sengine[playerid] = CreatePlayerTextDraw(playerid,513.000000, 419.000000, "ENGINE");
	PlayerTextDrawBackgroundColor(playerid,sengine[playerid], 255);
	PlayerTextDrawFont(playerid,sengine[playerid], 2);
	PlayerTextDrawLetterSize(playerid,sengine[playerid], 0.150000, 1.100000);
	PlayerTextDrawColor(playerid,sengine[playerid], -16776961);
	PlayerTextDrawSetOutline(playerid,sengine[playerid], 0);
	PlayerTextDrawSetProportional(playerid,sengine[playerid], 1);
	PlayerTextDrawSetShadow(playerid,sengine[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,sengine[playerid], 0);

	slights[playerid] = CreatePlayerTextDraw(playerid,544.000000, 419.000000, "LIGHTS");
	PlayerTextDrawBackgroundColor(playerid,slights[playerid], 255);
	PlayerTextDrawFont(playerid,slights[playerid], 2);
	PlayerTextDrawLetterSize(playerid,slights[playerid], 0.150000, 1.100000);
	PlayerTextDrawColor(playerid,slights[playerid], -16776961);
	PlayerTextDrawSetOutline(playerid,slights[playerid], 0);
	PlayerTextDrawSetProportional(playerid,slights[playerid], 1);
	PlayerTextDrawSetShadow(playerid,slights[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,slights[playerid], 0);

	slimit[playerid] = CreatePlayerTextDraw(playerid,574.000000, 419.000000, "SPEED LIMIT");
	PlayerTextDrawBackgroundColor(playerid,slimit[playerid], 255);
	PlayerTextDrawFont(playerid,slimit[playerid], 2);
	PlayerTextDrawLetterSize(playerid,slimit[playerid], 0.150000, 1.100000);
	PlayerTextDrawColor(playerid,slimit[playerid], -16776961);
	PlayerTextDrawSetOutline(playerid,slimit[playerid], 0);
	PlayerTextDrawSetProportional(playerid,slimit[playerid], 1);
	PlayerTextDrawSetShadow(playerid,slimit[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,slimit[playerid], 0);

	slock[playerid] = CreatePlayerTextDraw(playerid,593.000000, 386.000000, "Lock");
	PlayerTextDrawAlignment(playerid,slock[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,slock[playerid], 255);
	PlayerTextDrawFont(playerid,slock[playerid], 2);
	PlayerTextDrawLetterSize(playerid,slock[playerid], 0.200000, 1.000000);
	PlayerTextDrawColor(playerid,slock[playerid], -16776961);
	PlayerTextDrawSetOutline(playerid,slock[playerid], 0);
	PlayerTextDrawSetProportional(playerid,slock[playerid], 1);
	PlayerTextDrawSetShadow(playerid,slock[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,slock[playerid], 0);

	smilage[playerid] = TextDrawCreate(593.000000, 403.000000, "~y~milage");
	TextDrawAlignment(smilage[playerid], 2);
	TextDrawBackgroundColor(smilage[playerid], 255);
	TextDrawFont(smilage[playerid], 2);
	TextDrawLetterSize(smilage[playerid], 0.200000, 1.000000);
	TextDrawColor(smilage[playerid], 96492799);
	TextDrawSetOutline(smilage[playerid], 0);
	TextDrawSetProportional(smilage[playerid], 1);
	TextDrawSetShadow(smilage[playerid], 1);
	TextDrawSetSelectable(smilage[playerid], 0);
	//== Wars
	gFGang[playerid] = CreatePlayerTextDraw(playerid,540.000000, 200.000000, "Owner");
	PlayerTextDrawBackgroundColor(playerid,gFGang[playerid], 255);
	PlayerTextDrawFont(playerid,gFGang[playerid], 2);
	PlayerTextDrawLetterSize(playerid,gFGang[playerid], 0.200000, 1.000000);
	PlayerTextDrawColor(playerid,gFGang[playerid], 16711935);
	PlayerTextDrawSetOutline(playerid,gFGang[playerid], 0);
	PlayerTextDrawSetProportional(playerid,gFGang[playerid], 1);
	PlayerTextDrawSetShadow(playerid,gFGang[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,gFGang[playerid], 0);

	gTGang[playerid] = CreatePlayerTextDraw(playerid,540.000000, 211.000000, "Enemies");
	PlayerTextDrawBackgroundColor(playerid,gTGang[playerid], 255);
	PlayerTextDrawFont(playerid,gTGang[playerid], 2);
	PlayerTextDrawLetterSize(playerid,gTGang[playerid], 0.200000, 1.000000);
	PlayerTextDrawColor(playerid,gTGang[playerid], -16776961);
	PlayerTextDrawSetOutline(playerid,gTGang[playerid], 0);
	PlayerTextDrawSetProportional(playerid,gTGang[playerid], 1);
	PlayerTextDrawSetShadow(playerid,gTGang[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,gTGang[playerid], 0);

	gFScore[playerid] = CreatePlayerTextDraw(playerid,614.000000, 200.000000, "0");
	PlayerTextDrawAlignment(playerid,gFScore[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,gFScore[playerid], 255);
	PlayerTextDrawFont(playerid,gFScore[playerid], 2);
	PlayerTextDrawLetterSize(playerid,gFScore[playerid], 0.200000, 1.000000);
	PlayerTextDrawColor(playerid,gFScore[playerid], -1);
	PlayerTextDrawSetOutline(playerid,gFScore[playerid], 0);
	PlayerTextDrawSetProportional(playerid,gFScore[playerid], 1);
	PlayerTextDrawSetShadow(playerid,gFScore[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,gFScore[playerid], 0);

	gTScore[playerid] = CreatePlayerTextDraw(playerid,614.000000, 211.000000, "0");
	PlayerTextDrawAlignment(playerid,gTScore[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,gTScore[playerid], 255);
	PlayerTextDrawFont(playerid,gTScore[playerid], 2);
	PlayerTextDrawLetterSize(playerid,gTScore[playerid], 0.200000, 1.000000);
	PlayerTextDrawColor(playerid,gTScore[playerid], -1);
	PlayerTextDrawSetOutline(playerid,gTScore[playerid], 0);
	PlayerTextDrawSetProportional(playerid,gTScore[playerid], 1);
	PlayerTextDrawSetShadow(playerid,gTScore[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,gTScore[playerid], 0);

	gTimeTick[playerid] = CreatePlayerTextDraw(playerid,597.000000, 185.000000, "10:00");
	PlayerTextDrawAlignment(playerid,gTimeTick[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,gTimeTick[playerid], 255);
	PlayerTextDrawFont(playerid,gTimeTick[playerid], 2);
	PlayerTextDrawLetterSize(playerid,gTimeTick[playerid], 0.180000, 1.300000);
	PlayerTextDrawColor(playerid,gTimeTick[playerid], -252706561);
	PlayerTextDrawSetOutline(playerid,gTimeTick[playerid], 0);
	PlayerTextDrawSetProportional(playerid,gTimeTick[playerid], 1);
	PlayerTextDrawSetShadow(playerid,gTimeTick[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,gTimeTick[playerid], 0);

	gIDs[playerid] = CreatePlayerTextDraw(playerid,603.000000, 227.000000, "0");
	PlayerTextDrawAlignment(playerid,gIDs[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,gIDs[playerid], 255);
	PlayerTextDrawFont(playerid,gIDs[playerid], 2);
	PlayerTextDrawLetterSize(playerid,gIDs[playerid], 0.189999, 1.000000);
	PlayerTextDrawColor(playerid,gIDs[playerid], 16777215);
	PlayerTextDrawSetOutline(playerid,gIDs[playerid], 0);
	PlayerTextDrawSetProportional(playerid,gIDs[playerid], 1);
	PlayerTextDrawSetShadow(playerid,gIDs[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,gIDs[playerid], 0);
	//==== Gun ===
	cAmmo[playerid] = CreatePlayerTextDraw(playerid,301.000000, 100.000000, "You Ammo: 0");
	PlayerTextDrawBackgroundColor(playerid,cAmmo[playerid], 255);
	PlayerTextDrawFont(playerid,cAmmo[playerid], 2);
	PlayerTextDrawLetterSize(playerid,cAmmo[playerid], 0.200000, 1.000000);
	PlayerTextDrawColor(playerid,cAmmo[playerid], -16776961);
	PlayerTextDrawSetOutline(playerid,cAmmo[playerid], 0);
	PlayerTextDrawSetProportional(playerid,cAmmo[playerid], 1);
	PlayerTextDrawSetShadow(playerid,cAmmo[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,cAmmo[playerid], 0);

	mm7[playerid] = CreatePlayerTextDraw(playerid,182.000000, 109.000000, "Model");
	PlayerTextDrawBackgroundColor(playerid,mm7[playerid], 0);
	PlayerTextDrawFont(playerid,mm7[playerid], 5);
	PlayerTextDrawLetterSize(playerid,mm7[playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,mm7[playerid], -1);
	PlayerTextDrawSetOutline(playerid,mm7[playerid], 0);
	PlayerTextDrawSetProportional(playerid,mm7[playerid], 1);
	PlayerTextDrawSetShadow(playerid,mm7[playerid], 1);
	PlayerTextDrawAlignment(playerid,mm7[playerid], 1);
	PlayerTextDrawBoxColor(playerid,mm7[playerid], 0);
	PlayerTextDrawTextSize(playerid,mm7[playerid], 140.000000, 161.000000);
	PlayerTextDrawSetPreviewModel(playerid,mm7[playerid], 294);
	PlayerTextDrawSetPreviewRot(playerid,mm7[playerid], -16.000000, 0.000000, 25.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,mm7[playerid], 0);

	mm20[playerid] = CreatePlayerTextDraw(playerid,416.000000, 122.000000, "George");
	PlayerTextDrawAlignment(playerid,mm20[playerid], 3);
	PlayerTextDrawBackgroundColor(playerid,mm20[playerid], 51);
	PlayerTextDrawFont(playerid,mm20[playerid], 2);
	PlayerTextDrawLetterSize(playerid,mm20[playerid], 0.150000, 1.100000);
	PlayerTextDrawColor(playerid,mm20[playerid], 767361023);
	PlayerTextDrawSetOutline(playerid,mm20[playerid], 0);
	PlayerTextDrawSetProportional(playerid,mm20[playerid], 1);
	PlayerTextDrawSetShadow(playerid,mm20[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,mm20[playerid], 0);

	mm21[playerid] = CreatePlayerTextDraw(playerid,416.000000, 132.000000, "Houser");
	PlayerTextDrawAlignment(playerid,mm21[playerid], 3);
	PlayerTextDrawBackgroundColor(playerid,mm21[playerid], 51);
	PlayerTextDrawFont(playerid,mm21[playerid], 2);
	PlayerTextDrawLetterSize(playerid,mm21[playerid], 0.150000, 1.100000);
	PlayerTextDrawColor(playerid,mm21[playerid], 767361023);
	PlayerTextDrawSetOutline(playerid,mm21[playerid], 0);
	PlayerTextDrawSetProportional(playerid,mm21[playerid], 1);
	PlayerTextDrawSetShadow(playerid,mm21[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,mm21[playerid], 0);

	mm22[playerid] = CreatePlayerTextDraw(playerid,416.000000, 142.000000, "2 (1/12)");
	PlayerTextDrawAlignment(playerid,mm22[playerid], 3);
	PlayerTextDrawBackgroundColor(playerid,mm22[playerid], 51);
	PlayerTextDrawFont(playerid,mm22[playerid], 2);
	PlayerTextDrawLetterSize(playerid,mm22[playerid], 0.150000, 1.100000);
	PlayerTextDrawColor(playerid,mm22[playerid], 767361023);
	PlayerTextDrawSetOutline(playerid,mm22[playerid], 0);
	PlayerTextDrawSetProportional(playerid,mm22[playerid], 1);
	PlayerTextDrawSetShadow(playerid,mm22[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,mm22[playerid], 0);

	mm23[playerid] = CreatePlayerTextDraw(playerid,416.000000, 152.000000, "Fraction");
	PlayerTextDrawAlignment(playerid,mm23[playerid], 3);
	PlayerTextDrawBackgroundColor(playerid,mm23[playerid], 51);
	PlayerTextDrawFont(playerid,mm23[playerid], 2);
	PlayerTextDrawLetterSize(playerid,mm23[playerid], 0.150000, 1.100000);
	PlayerTextDrawColor(playerid,mm23[playerid], 767361023);
	PlayerTextDrawSetOutline(playerid,mm23[playerid], 0);
	PlayerTextDrawSetProportional(playerid,mm23[playerid], 1);
	PlayerTextDrawSetShadow(playerid,mm23[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,mm23[playerid], 0);

	mm24[playerid] = CreatePlayerTextDraw(playerid,416.000000, 162.000000, "Post");
	PlayerTextDrawAlignment(playerid,mm24[playerid], 3);
	PlayerTextDrawBackgroundColor(playerid,mm24[playerid], 51);
	PlayerTextDrawFont(playerid,mm24[playerid], 2);
	PlayerTextDrawLetterSize(playerid,mm24[playerid], 0.150000, 1.100000);
	PlayerTextDrawColor(playerid,mm24[playerid], 767361023);
	PlayerTextDrawSetOutline(playerid,mm24[playerid], 0);
	PlayerTextDrawSetProportional(playerid,mm24[playerid], 1);
	PlayerTextDrawSetShadow(playerid,mm24[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,mm24[playerid], 0);

	mm25[playerid] = CreatePlayerTextDraw(playerid,416.000000, 172.000000, "Man");
	PlayerTextDrawAlignment(playerid,mm25[playerid], 3);
	PlayerTextDrawBackgroundColor(playerid,mm25[playerid], 51);
	PlayerTextDrawFont(playerid,mm25[playerid], 2);
	PlayerTextDrawLetterSize(playerid,mm25[playerid], 0.150000, 1.100000);
	PlayerTextDrawColor(playerid,mm25[playerid], 767361023);
	PlayerTextDrawSetOutline(playerid,mm25[playerid], 0);
	PlayerTextDrawSetProportional(playerid,mm25[playerid], 1);
	PlayerTextDrawSetShadow(playerid,mm25[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,mm25[playerid], 0);

	mm26[playerid] = CreatePlayerTextDraw(playerid,416.000000, 182.000000, "127.0.0.1");
	PlayerTextDrawAlignment(playerid,mm26[playerid], 3);
	PlayerTextDrawBackgroundColor(playerid,mm26[playerid], 51);
	PlayerTextDrawFont(playerid,mm26[playerid], 2);
	PlayerTextDrawLetterSize(playerid,mm26[playerid], 0.150000, 1.100000);
	PlayerTextDrawColor(playerid,mm26[playerid], 767361023);
	PlayerTextDrawSetOutline(playerid,mm26[playerid], 0);
	PlayerTextDrawSetProportional(playerid,mm26[playerid], 1);
	PlayerTextDrawSetShadow(playerid,mm26[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,mm26[playerid], 0);

	mm27[playerid] = CreatePlayerTextDraw(playerid,416.000000, 192.000000, "127.0.0.1");
	PlayerTextDrawAlignment(playerid,mm27[playerid], 3);
	PlayerTextDrawBackgroundColor(playerid,mm27[playerid], 51);
	PlayerTextDrawFont(playerid,mm27[playerid], 2);
	PlayerTextDrawLetterSize(playerid,mm27[playerid], 0.150000, 1.100000);
	PlayerTextDrawColor(playerid,mm27[playerid], 767361023);
	PlayerTextDrawSetOutline(playerid,mm27[playerid], 0);
	PlayerTextDrawSetProportional(playerid,mm27[playerid], 1);
	PlayerTextDrawSetShadow(playerid,mm27[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,mm27[playerid], 0);

	mm28[playerid] = CreatePlayerTextDraw(playerid,416.000000, 202.000000, "0");
	PlayerTextDrawAlignment(playerid,mm28[playerid], 3);
	PlayerTextDrawBackgroundColor(playerid,mm28[playerid], 51);
	PlayerTextDrawFont(playerid,mm28[playerid], 2);
	PlayerTextDrawLetterSize(playerid,mm28[playerid], 0.150000, 1.100000);
	PlayerTextDrawColor(playerid,mm28[playerid], -16776961);
	PlayerTextDrawSetOutline(playerid,mm28[playerid], 0);
	PlayerTextDrawSetProportional(playerid,mm28[playerid], 1);
	PlayerTextDrawSetShadow(playerid,mm28[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,mm28[playerid], 0);

	mm43[playerid] = CreatePlayerTextDraw(playerid,341.000000, 229.000000, "car");
	PlayerTextDrawBackgroundColor(playerid,mm43[playerid], 0);
	PlayerTextDrawFont(playerid,mm43[playerid], 5);
	PlayerTextDrawLetterSize(playerid,mm43[playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,mm43[playerid], -1);
	PlayerTextDrawSetOutline(playerid,mm43[playerid], 0);
	PlayerTextDrawSetProportional(playerid,mm43[playerid], 1);
	PlayerTextDrawSetShadow(playerid,mm43[playerid], 1);
	PlayerTextDrawAlignment(playerid,mm43[playerid], 1);
	PlayerTextDrawBoxColor(playerid,mm43[playerid], 0);
	PlayerTextDrawTextSize(playerid,mm43[playerid], 30.000000, 31.000000);
	PlayerTextDrawSetPreviewModel(playerid,mm43[playerid], 411);
	PlayerTextDrawSetPreviewRot(playerid,mm43[playerid], -16.000000, 0.000000, 25.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,mm43[playerid], 0);

	mm45[playerid] = CreatePlayerTextDraw(playerid,319.000000, 266.000000, "House: ID");
	PlayerTextDrawAlignment(playerid,mm45[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,mm45[playerid], 51);
	PlayerTextDrawFont(playerid,mm45[playerid], 2);
	PlayerTextDrawLetterSize(playerid,mm45[playerid], 0.119998, 0.899999);
	PlayerTextDrawColor(playerid,mm45[playerid], 767361023);
	PlayerTextDrawSetOutline(playerid,mm45[playerid], 0);
	PlayerTextDrawSetProportional(playerid,mm45[playerid], 1);
	PlayerTextDrawSetShadow(playerid,mm45[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,mm45[playerid], 0);

	mm46[playerid] = CreatePlayerTextDraw(playerid,358.000000, 267.000000, "CAR: INFERNUS");
	PlayerTextDrawAlignment(playerid,mm46[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,mm46[playerid], 51);
	PlayerTextDrawFont(playerid,mm46[playerid], 2);
	PlayerTextDrawLetterSize(playerid,mm46[playerid], 0.099999, 0.799998);
	PlayerTextDrawColor(playerid,mm46[playerid], 767361023);
	PlayerTextDrawSetOutline(playerid,mm46[playerid], 0);
	PlayerTextDrawSetProportional(playerid,mm46[playerid], 1);
	PlayerTextDrawSetShadow(playerid,mm46[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,mm46[playerid], 0);

	mm47[playerid] = CreatePlayerTextDraw(playerid,398.000000, 267.000000, "BUSINESS: Pay'N'Spray");
	PlayerTextDrawAlignment(playerid,mm47[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,mm47[playerid], 51);
	PlayerTextDrawFont(playerid,mm47[playerid], 2);
	PlayerTextDrawLetterSize(playerid,mm47[playerid], 0.079998, 0.799998);
	PlayerTextDrawColor(playerid,mm47[playerid], 767361023);
	PlayerTextDrawSetOutline(playerid,mm47[playerid], 0);
	PlayerTextDrawSetProportional(playerid,mm47[playerid], 1);
	PlayerTextDrawSetShadow(playerid,mm47[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,mm47[playerid], 0);
	//======== RECON =====================
	rmodel[playerid] = TextDrawCreate(487.000000, 135.000000, "model");
	TextDrawBackgroundColor(rmodel[playerid], 0);
	TextDrawFont(rmodel[playerid], 5);
	TextDrawLetterSize(rmodel[playerid], 0.500000, 1.000000);
	TextDrawColor(rmodel[playerid], -1);
	TextDrawSetOutline(rmodel[playerid], 0);
	TextDrawSetProportional(rmodel[playerid], 1);
	TextDrawSetShadow(rmodel[playerid], 1);
	TextDrawUseBox(rmodel[playerid], 1);
	TextDrawBoxColor(rmodel[playerid], 0);
	TextDrawTextSize(rmodel[playerid], 74.000000, 79.000000);
	TextDrawSetPreviewModel(rmodel[playerid], 107);
	TextDrawSetPreviewRot(rmodel[playerid], -16.000000, 0.000000, 25.000000, 1.000000);
	TextDrawSetSelectable(rmodel[playerid], 0);

	rname[playerid] = TextDrawCreate(559.000000, 120.000000, "George_Houser (999)");
	TextDrawAlignment(rname[playerid], 2);
	TextDrawBackgroundColor(rname[playerid], 68);
	TextDrawFont(rname[playerid], 2);
	TextDrawLetterSize(rname[playerid], 0.119999, 1.200000);
	TextDrawColor(rname[playerid], -16776961);
	TextDrawSetOutline(rname[playerid], 0);
	TextDrawSetProportional(rname[playerid], 1);
	TextDrawSetShadow(rname[playerid], 1);
	TextDrawSetSelectable(rname[playerid], 0);

	rhealth[playerid] = TextDrawCreate(549.000000, 143.000000, "Health: 100");
	TextDrawBackgroundColor(rhealth[playerid], 255);
	TextDrawFont(rhealth[playerid], 2);
	TextDrawLetterSize(rhealth[playerid], 0.140000, 1.399999);
	TextDrawColor(rhealth[playerid], -1);
	TextDrawSetOutline(rhealth[playerid], 0);
	TextDrawSetProportional(rhealth[playerid], 1);
	TextDrawSetShadow(rhealth[playerid], 1);
	TextDrawSetSelectable(rhealth[playerid], 0);

	rarmour[playerid] = TextDrawCreate(549.000000, 156.000000, "Armour: 0");
	TextDrawBackgroundColor(rarmour[playerid], 255);
	TextDrawFont(rarmour[playerid], 2);
	TextDrawLetterSize(rarmour[playerid], 0.140000, 1.399999);
	TextDrawColor(rarmour[playerid], -1);
	TextDrawSetOutline(rarmour[playerid], 0);
	TextDrawSetProportional(rarmour[playerid], 1);
	TextDrawSetShadow(rarmour[playerid], 1);
	TextDrawSetSelectable(rarmour[playerid], 0);

	rping[playerid] = TextDrawCreate(549.000000, 169.000000, "Ping: 30");
	TextDrawBackgroundColor(rping[playerid], 255);
	TextDrawFont(rping[playerid], 2);
	TextDrawLetterSize(rping[playerid], 0.140000, 1.399999);
	TextDrawColor(rping[playerid], -1);
	TextDrawSetOutline(rping[playerid], 0);
	TextDrawSetProportional(rping[playerid], 1);
	TextDrawSetShadow(rping[playerid], 1);
	TextDrawSetSelectable(rping[playerid], 0);

	rmoney[playerid] = TextDrawCreate(549.000000, 182.000000, "Money: 100");
	TextDrawBackgroundColor(rmoney[playerid], 255);
	TextDrawFont(rmoney[playerid], 2);
	TextDrawLetterSize(rmoney[playerid], 0.140000, 1.399999);
	TextDrawColor(rmoney[playerid], -1);
	TextDrawSetOutline(rmoney[playerid], 0);
	TextDrawSetProportional(rmoney[playerid], 1);
	TextDrawSetShadow(rmoney[playerid], 1);
	TextDrawSetSelectable(rmoney[playerid], 0);

	rspeed[playerid] = TextDrawCreate(549.000000, 195.000000, "Speed Player: 0");
	TextDrawBackgroundColor(rspeed[playerid], 255);
	TextDrawFont(rspeed[playerid], 2);
	TextDrawLetterSize(rspeed[playerid], 0.140000, 1.399999);
	TextDrawColor(rspeed[playerid], -1);
	TextDrawSetOutline(rspeed[playerid], 0);
	TextDrawSetProportional(rspeed[playerid], 1);
	TextDrawSetShadow(rspeed[playerid], 1);
	TextDrawSetSelectable(rspeed[playerid], 0);

	rrip[playerid] = TextDrawCreate(526.000000, 224.000000, "R-IP: 255.255.255.255");
	TextDrawBackgroundColor(rrip[playerid], 255);
	TextDrawFont(rrip[playerid], 2);
	TextDrawLetterSize(rrip[playerid], 0.140000, 1.399999);
	TextDrawColor(rrip[playerid], 1153368063);
	TextDrawSetOutline(rrip[playerid], 0);
	TextDrawSetProportional(rrip[playerid], 1);
	TextDrawSetShadow(rrip[playerid], 1);
	TextDrawSetSelectable(rrip[playerid], 0);

	rip[playerid] = TextDrawCreate(528.000000, 250.000000, "IP: 255.255.255.255");
	TextDrawBackgroundColor(rip[playerid], 255);
	TextDrawFont(rip[playerid], 2);
	TextDrawLetterSize(rip[playerid], 0.140000, 1.399999);
	TextDrawColor(rip[playerid], 1153368063);
	TextDrawSetOutline(rip[playerid], 0);
	TextDrawSetProportional(rip[playerid], 1);
	TextDrawSetShadow(rip[playerid], 1);
	TextDrawSetSelectable(rip[playerid], 0);
	
	rvmodel[playerid] = TextDrawCreate(495.000000, 292.000000, "modelcar");
	TextDrawBackgroundColor(rvmodel[playerid], 0);
	TextDrawFont(rvmodel[playerid], 5);
	TextDrawLetterSize(rvmodel[playerid], 0.500000, 1.000000);
	TextDrawColor(rvmodel[playerid], -1);
	TextDrawSetOutline(rvmodel[playerid], 0);
	TextDrawSetProportional(rvmodel[playerid], 1);
	TextDrawSetShadow(rvmodel[playerid], 1);
	TextDrawUseBox(rvmodel[playerid], 1);
	TextDrawBoxColor(rvmodel[playerid], 0);
	TextDrawTextSize(rvmodel[playerid], 64.000000, 71.000000);
	TextDrawSetPreviewModel(rvmodel[playerid], 411);
	TextDrawSetPreviewRot(rvmodel[playerid], -16.000000, 0.000000, 25.000000, 1.000000);
	TextDrawSetSelectable(rvmodel[playerid], 0);

	rvname[playerid] = TextDrawCreate(559.000000, 301.000000, "Infernus (411)");
	TextDrawAlignment(rvname[playerid], 2);
	TextDrawBackgroundColor(rvname[playerid], 68);
	TextDrawFont(rvname[playerid], 2);
	TextDrawLetterSize(rvname[playerid], 0.119999, 1.200000);
	TextDrawColor(rvname[playerid], -16776961);
	TextDrawSetOutline(rvname[playerid], 0);
	TextDrawSetProportional(rvname[playerid], 1);
	TextDrawSetShadow(rvname[playerid], 1);
	TextDrawSetSelectable(rvname[playerid], 0);

	rvhealth[playerid] = TextDrawCreate(558.000000, 317.000000, "Health: 1000");
	TextDrawBackgroundColor(rvhealth[playerid], 255);
	TextDrawFont(rvhealth[playerid], 2);
	TextDrawLetterSize(rvhealth[playerid], 0.140000, 1.399999);
	TextDrawColor(rvhealth[playerid], -1);
	TextDrawSetOutline(rvhealth[playerid], 0);
	TextDrawSetProportional(rvhealth[playerid], 1);
	TextDrawSetShadow(rvhealth[playerid], 1);
	TextDrawSetSelectable(rvhealth[playerid], 0);

	rvspeed[playerid] = TextDrawCreate(558.000000, 337.000000, "Speed: 0");
	TextDrawBackgroundColor(rvspeed[playerid], 255);
	TextDrawFont(rvspeed[playerid], 2);
	TextDrawLetterSize(rvspeed[playerid], 0.140000, 1.399999);
	TextDrawColor(rvspeed[playerid], -1);
	TextDrawSetOutline(rvspeed[playerid], 0);
	TextDrawSetProportional(rvspeed[playerid], 1);
	TextDrawSetShadow(rvspeed[playerid], 1);
	TextDrawSetSelectable(rvspeed[playerid], 0);
	//=== Ammo ===
	amGun[playerid] = CreatePlayerTextDraw(playerid,313.000000, 25.000000, "M4A1");
	PlayerTextDrawAlignment(playerid,amGun[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,amGun[playerid], 255);
	PlayerTextDrawFont(playerid,amGun[playerid], 1);
	PlayerTextDrawLetterSize(playerid,amGun[playerid], 0.300000, 1.300000);
	PlayerTextDrawColor(playerid,amGun[playerid], -1);
	PlayerTextDrawSetOutline(playerid,amGun[playerid], 1);
	PlayerTextDrawSetProportional(playerid,amGun[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,amGun[playerid], 0);
	
	amPrice[playerid] = CreatePlayerTextDraw(playerid,362.000000, 45.000000, "200$");
	PlayerTextDrawAlignment(playerid,amPrice[playerid], 3);
	PlayerTextDrawBackgroundColor(playerid,amPrice[playerid], 255);
	PlayerTextDrawFont(playerid,amPrice[playerid], 2);
	PlayerTextDrawLetterSize(playerid,amPrice[playerid], 0.190000, 1.100000);
	PlayerTextDrawColor(playerid,amPrice[playerid], -1);
	PlayerTextDrawSetOutline(playerid,amPrice[playerid], 0);
	PlayerTextDrawSetProportional(playerid,amPrice[playerid], 1);
	PlayerTextDrawSetShadow(playerid,amPrice[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,amPrice[playerid], 0);
	//==== Buy skin
	Player[playerid][tCostItem] = TextDrawCreate(550.000000, 205.000000, "$");
	TextDrawBackgroundColor(Player[playerid][tCostItem], 85);
	TextDrawFont(Player[playerid][tCostItem], 2);
	TextDrawLetterSize(Player[playerid][tCostItem], 0.300000, 1.000000);
	TextDrawColor(Player[playerid][tCostItem], 96492799);
	TextDrawSetOutline(Player[playerid][tCostItem], 1);
	TextDrawSetProportional(Player[playerid][tCostItem], 1);
	TextDrawSetSelectable(Player[playerid][tCostItem], 0);
	//=== Autosalon
	Player[playerid][asVname] = TextDrawCreate(114.000000, 232.000000, "Moonbeam");
	TextDrawAlignment(Player[playerid][asVname], 2);
	TextDrawBackgroundColor(Player[playerid][asVname], 255);
	TextDrawFont(Player[playerid][asVname], 2);
	TextDrawLetterSize(Player[playerid][asVname], 0.189999, 1.000000);
	TextDrawColor(Player[playerid][asVname], -1);
	TextDrawSetOutline(Player[playerid][asVname], 0);
	TextDrawSetProportional(Player[playerid][asVname], 1);
	TextDrawSetShadow(Player[playerid][asVname], 1);
	TextDrawSetSelectable(Player[playerid][asVname], 0);

	Player[playerid][asCostV] = TextDrawCreate(194.000000, 246.000000, "1200000$");
	TextDrawAlignment(Player[playerid][asCostV], 3);
	TextDrawBackgroundColor(Player[playerid][asCostV], 255);
	TextDrawFont(Player[playerid][asCostV], 2);
	TextDrawLetterSize(Player[playerid][asCostV], 0.270000, 1.500000);
	TextDrawColor(Player[playerid][asCostV], -1401588225);
	TextDrawSetOutline(Player[playerid][asCostV], 0);
	TextDrawSetProportional(Player[playerid][asCostV], 1);
	TextDrawSetShadow(Player[playerid][asCostV], 1);
	TextDrawSetSelectable(Player[playerid][asCostV], 0);
	//========== INVENTORY ==========
	Player[playerid][iModel] = TextDrawCreate(202.000000, 145.000000, "md");
	TextDrawBackgroundColor(Player[playerid][iModel], 0);
	TextDrawFont(Player[playerid][iModel], 5);
	TextDrawLetterSize(Player[playerid][iModel], 0.500000, 1.000000);
	TextDrawColor(Player[playerid][iModel], -1);
	TextDrawSetOutline(Player[playerid][iModel], 0);
	TextDrawSetProportional(Player[playerid][iModel], 1);
	TextDrawSetShadow(Player[playerid][iModel], 0);
	TextDrawUseBox(Player[playerid][iModel], 1);
	TextDrawBoxColor(Player[playerid][iModel], -256);
	TextDrawTextSize(Player[playerid][iModel], 112.000000, 156.000000);
	TextDrawSetPreviewModel(Player[playerid][iModel], 154);
	TextDrawSetPreviewRot(Player[playerid][iModel], -20.000000, 0.000000, -20.000000, 1.000000);
	TextDrawSetSelectable(Player[playerid][iModel], 0);

	Player[playerid][iSkin] = TextDrawCreate(204.000000, 143.000000, "skin");
	TextDrawBackgroundColor(Player[playerid][iSkin], -540686337);
	TextDrawFont(Player[playerid][iSkin], 5);
	TextDrawLetterSize(Player[playerid][iSkin], 0.500000, 1.000000);
	TextDrawColor(Player[playerid][iSkin], -1);
	TextDrawSetOutline(Player[playerid][iSkin], 0);
	TextDrawSetProportional(Player[playerid][iSkin], 1);
	TextDrawSetShadow(Player[playerid][iSkin], 1);
	TextDrawUseBox(Player[playerid][iSkin], 1);
	TextDrawBoxColor(Player[playerid][iSkin], 0);
	TextDrawTextSize(Player[playerid][iSkin], 24.000000, 27.000000);
	TextDrawSetPreviewModel(Player[playerid][iSkin], 2689);
	TextDrawSetPreviewRot(Player[playerid][iSkin], -16.000000, 0.000000, -180.000000, 0.699998);
	TextDrawSetSelectable(Player[playerid][iSkin], 1);

	Player[playerid][iPhone] = TextDrawCreate(204.000000, 171.000000, "phone");
	TextDrawBackgroundColor(Player[playerid][iPhone], -540686337);
	TextDrawFont(Player[playerid][iPhone], 5);
	TextDrawLetterSize(Player[playerid][iPhone], 0.500000, 1.000000);
	TextDrawColor(Player[playerid][iPhone], -1);
	TextDrawSetOutline(Player[playerid][iPhone], 0);
	TextDrawSetProportional(Player[playerid][iPhone], 1);
	TextDrawSetShadow(Player[playerid][iPhone], 1);
	TextDrawUseBox(Player[playerid][iPhone], 1);
	TextDrawBoxColor(Player[playerid][iPhone], 0);
	TextDrawTextSize(Player[playerid][iPhone], 24.000000, 27.000000);
	TextDrawSetPreviewModel(Player[playerid][iPhone], 18866);
	TextDrawSetPreviewRot(Player[playerid][iPhone], -90.000000, 42.000000, 182.000000, 0.800000);
	TextDrawSetSelectable(Player[playerid][iPhone], 0);

	Player[playerid][iClock] = TextDrawCreate(204.000000, 199.000000, "clock");
	TextDrawBackgroundColor(Player[playerid][iClock], -540686337);
	TextDrawFont(Player[playerid][iClock], 5);
	TextDrawLetterSize(Player[playerid][iClock], 0.500000, 1.000000);
	TextDrawColor(Player[playerid][iClock], -1);
	TextDrawSetOutline(Player[playerid][iClock], 0);
	TextDrawSetProportional(Player[playerid][iClock], 1);
	TextDrawSetShadow(Player[playerid][iClock], 1);
	TextDrawUseBox(Player[playerid][iClock], 1);
	TextDrawBoxColor(Player[playerid][iClock], 0);
	TextDrawTextSize(Player[playerid][iClock], 24.000000, 27.000000);
	TextDrawSetPreviewModel(Player[playerid][iClock], 19046);
	TextDrawSetPreviewRot(Player[playerid][iClock], -45.000000, 24.000000, -15.000000, 0.600000);
	TextDrawSetSelectable(Player[playerid][iClock], 0);

	Player[playerid][iGps] = TextDrawCreate(204.000000, 227.000000, "gps");
	TextDrawBackgroundColor(Player[playerid][iGps], -540686337);
	TextDrawFont(Player[playerid][iGps], 5);
	TextDrawLetterSize(Player[playerid][iGps], 0.500000, 1.000000);
	TextDrawColor(Player[playerid][iGps], -1);
	TextDrawSetOutline(Player[playerid][iGps], 0);
	TextDrawSetProportional(Player[playerid][iGps], 1);
	TextDrawSetShadow(Player[playerid][iGps], 1);
	TextDrawUseBox(Player[playerid][iGps], 1);
	TextDrawBoxColor(Player[playerid][iGps], 0);
	TextDrawTextSize(Player[playerid][iGps], 24.000000, 26.000000);
	TextDrawSetPreviewModel(Player[playerid][iGps], 18875);
	TextDrawSetPreviewRot(Player[playerid][iGps], -90.000000, -20.000000, -180.000000, 0.699998);
	TextDrawSetSelectable(Player[playerid][iGps], 0);

	Player[playerid][iRepair] = TextDrawCreate(204.000000, 254.000000, "repair");
	TextDrawBackgroundColor(Player[playerid][iRepair], -540686337);
	TextDrawFont(Player[playerid][iRepair], 5);
	TextDrawLetterSize(Player[playerid][iRepair], 0.500000, 1.000000);
	TextDrawColor(Player[playerid][iRepair], -1);
	TextDrawSetOutline(Player[playerid][iRepair], 0);
	TextDrawSetProportional(Player[playerid][iRepair], 1);
	TextDrawSetShadow(Player[playerid][iRepair], 0);
	TextDrawUseBox(Player[playerid][iRepair], 1);
	TextDrawBoxColor(Player[playerid][iRepair], 0);
	TextDrawTextSize(Player[playerid][iRepair], 24.000000, 26.000000);
	TextDrawSetPreviewModel(Player[playerid][iRepair], 18635);
	TextDrawSetPreviewRot(Player[playerid][iRepair], 0.000000, 0.000000, 0.000000, 0.899999);
	TextDrawSetSelectable(Player[playerid][iRepair], 0);
	iSlot[playerid][0] = TextDrawCreate(294.000000, 158.000000, "slot");
	iSlot[playerid][1] = TextDrawCreate(319.000000, 158.000000, "slot");
	iSlot[playerid][2] = TextDrawCreate(344.000000, 158.000000, "slot");
	iSlot[playerid][3] = TextDrawCreate(369.000000, 158.000000, "slot");
	iSlot[playerid][4] = TextDrawCreate(394.000000, 158.000000, "slot");
	iSlot[playerid][5] = TextDrawCreate(294.000000, 186.000000, "slot");
	iSlot[playerid][6] = TextDrawCreate(319.000000, 186.000000, "slot");
	iSlot[playerid][7] = TextDrawCreate(344.000000, 186.000000, "slot");
	iSlot[playerid][8] = TextDrawCreate(369.000000, 186.000000, "slot");
	iSlot[playerid][9] = TextDrawCreate(394.000000, 186.000000, "slot");
	iSlot[playerid][10] = TextDrawCreate(294.000000, 214.000000, "slot");
	iSlot[playerid][11] = TextDrawCreate(319.000000, 214.000000, "slot");
	iSlot[playerid][12] = TextDrawCreate(344.000000, 214.000000, "slot");
	iSlot[playerid][13] = TextDrawCreate(369.000000, 214.000000, "slot");
	iSlot[playerid][14] = TextDrawCreate(394.000000, 214.000000, "slot");
	iSlot[playerid][15] = TextDrawCreate(294.000000, 242.000000, "slot");
	iSlot[playerid][16] = TextDrawCreate(319.000000, 242.000000, "slot");
	iSlot[playerid][17] = TextDrawCreate(344.000000, 242.000000, "slot");
	iSlot[playerid][18] = TextDrawCreate(369.000000, 242.000000, "slot");
	iSlot[playerid][19] = TextDrawCreate(394.000000, 242.000000, "slot");
	for(new i; i < 20; i++) {
	    TextDrawBackgroundColor(iSlot[playerid][i], -540686337);
		TextDrawFont(iSlot[playerid][i], 5);
		TextDrawLetterSize(iSlot[playerid][i], 0.500000, 1.000000);
		TextDrawColor(iSlot[playerid][i], -1);
		TextDrawSetOutline(iSlot[playerid][i], 0);
		TextDrawSetProportional(iSlot[playerid][i], 1);
		TextDrawSetShadow(iSlot[playerid][i], 1);
		TextDrawUseBox(iSlot[playerid][i], 1);
		TextDrawBoxColor(iSlot[playerid][i], 0);
		TextDrawTextSize(iSlot[playerid][i], 24.000000, 27.000000);
		TextDrawSetPreviewModel(iSlot[playerid][i], 19349);
		TextDrawSetPreviewRot(iSlot[playerid][i], -16.000000, 0.000000, -180.000000, 0.699998);
		TextDrawSetSelectable(iSlot[playerid][i], 1);
	}
}

SendAdminMessage(color, string[]) foreach(new i : Player) if(Player[i][pAdmin] >= 1) SendClientMessage(i, color, string);

SendRadioMessage(member, color, string[]) foreach(new i : Player) if(Player[i][pFraction][1] == member) SendClientMessage(i, color, string);

stock Engine(vehicleid,bool:launched) return launched ? SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_ON, -1, -1, -1, -1, -1, -1) : SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, -1, -1, -1, -1, -1, -1);

stock EngineStatus(vehicleid) {
	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
	return engine;
}

apublic GetTimer() {
	new GetTime = gettime();
    if(Timer[0] <= GetTime && Timer[0] != 0) {
		Timer[0] = GetTime+1, PlayerTimer(), UpdateTime();
		if(GWars[0] != 0) GangZoneStatus(GWars[0]);
		else if(GWars[1] != 0) GangZoneStatus(GWars[1]);
	}
    if(Timer[1] <= GetTime && Timer[1] != 0) Timer[1] = GetTime+1800, LSW += 5000, format(strock,58,"Комплектующие для сбора оружия\n{1faee9}На корабле: %d",LSW), UpdateDynamic3DTextLabelText(LSWtext, 0xFFFFFFFF, strock), setproperty(0, "sw", random(20)), SetWeather(getproperty(0, "sw", _));
    if(Timer[2] <= GetTime && Timer[2] != 0 && Alarm == true) { Timer[2] = GetTime+45; foreach(new i : Player) if(IsPlayerInDynamicArea(i,Area)) PlayAudioStreamForPlayer(i,"http://cheery-rp.ru/sound1.mp3",222.0781,1930.0691,28.3515,350,true); }
    if(Timer[3] <= GetTime && Timer[3] != 0) PayDay = 0;
	return true;
}

apublic UpdateTime() {
	new minute, second, hour, string[28],tax;
   	gettime(hour,minute,second);
 	if((minute == 0 && second >= 0 && second <= 10) && PayDay == 0) 
	{
		CurrentWeather = AllowWeather[random(12)];
		SetWeather(CurrentWeather);
		
   	    PayDay = 1;
   	    Timer[3] = gettime()+10;
   	    SetWorldTime(hour);
   	    SendClientMessageToAll(0x1faee9FF,"<~~~~~~~~~~~~~~~~~~~~~~~~~~ [ {ffffff}PAYDAY{1faee9} ] ~~~~~~~~~~~~~~~~~~~~~~~~~~~>");
	   	format(string,24,"В штате: {1FE9B9}%d:00",hour), SendClientMessageToAll(0xFFFFFFFF,string);
	   	foreach(new playerid : Player) {
	   	    if(GetPVarInt(playerid,"PlayedTime") <= gettime() && Player[playerid][PlayerLogged]) {
		   		Player[playerid][pExp]++;
	    		if(Player[playerid][pExp] == Player[playerid][pLevel]*6) {
	 				Player[playerid][pLevel]++, Player[playerid][pExp] = 0, SCM(playerid,0x03c03cFF,"Поздравляем вы прожили ещё один год в штате!"), SetPlayerScore(playerid,Player[playerid][pLevel]);
	 				if(Player[playerid][pLevel] == 3) Player[playerid][pCity] = 2, SCM(playerid,0x03c03cFF,"Ваше место прописки было изменено Мэрией штата! Теперь вы проживаете в {ffffff}г.San Fierro!");
	 				else if(Player[playerid][pLevel] == 5) Player[playerid][pCity] = 3, SCM(playerid,0x03c03cFF,"Ваше место прописки было изменено Мэрией штата! Теперь вы проживаете в {ffffff}г.Las Venturas!");
				}
		    	switch(Player[playerid][pFraction][1]) {
					case 6..10: SetPVarInt(playerid,"fprice",Player[playerid][pFraction][2]*1005+random(75)), Player[playerid][pMoney] += GetPVarInt(playerid,"fprice");
					default: SetPVarInt(playerid,"fprice",0);
			}   }
			else SCM(playerid,0xFFFFFFFF,"Для получения зарплаты и опыта необходимо находиться на сервере {F18C8C}не менее 15 минут!"), SetPVarInt(playerid,"fprice",0);
			tax = tax+random(50);
			format(string,27,"Зар.плата: {1FE9B9}+%d$",GetPVarInt(playerid,"fprice")), SCM(playerid,0xFFFFFFFF,string);
			if(Player[playerid][pLevel] > 2 && Player[playerid][pBankPass] != 0)  format(string,20,"Налог: {F18C8C}-%d$",tax), SCM(playerid,0xFFFFFFFF,string),  Player[playerid][pMoney] -= tax;
			else SCM(playerid,0xFFFFFFFF,"Налог: {03c03c}0$");
			if(Player[playerid][pHouse] != 9999) {
		 		SCM(playerid,0xFFFFFFFF,"Плата за дом: {F18C8C}-150$");
				if(House[Player[playerid][pHouse]][hCommunal] <= -2350) {
				    strmid(House[Player[playerid][pHouse]][hOwner], "None", 0, strlen("None"), 24);
					Player[playerid][pMoney] += House[Player[playerid][pHouse]][hPrice]/3; SaveHouse(Player[playerid][pHouse]);
					DestroyDynamicPickup(House[Player[playerid][pHouse]][hPickup]), DestroyDynamicMapIcon(House[Player[playerid][pHouse]][hIcon]);
					House[Player[playerid][pHouse]][hIcon] = CreateDynamicMapIcon(House[Player[playerid][pHouse]][hX],House[Player[playerid][pHouse]][hY],House[Player[playerid][pHouse]][hZ],31,COLOR_WHITE,0,-1,-1);
					House[Player[playerid][pHouse]][hPickup] = CreateDynamicPickup(1273,1,House[Player[playerid][pHouse]][hX],House[Player[playerid][pHouse]][hY],House[Player[playerid][pHouse]][hZ]);
					if(Player[playerid][pCar][0] != -1) DestroyVehicle(Player[playerid][PlayerCar]);
					Player[playerid][pHouse] = 9999;
					SCM(playerid,0xFF0000FF,"Вы были выселены из дома за долгую неуплату коммунальных услуг! Треть суммы со стоимости дома вам возвращена.");
			}   }
			if(Player[playerid][pBusiness] != 9999) {
		 		SCM(playerid,0xFFFFFFFF,"Плата за бизнес: {F18C8C}-250$");
		 		if(Business[Player[playerid][pBusiness]][bCommunal] <= -2850) {
				    strmid(Business[Player[playerid][pBusiness]][bOwner], "None", 0, strlen("None"), 24);
					Player[playerid][pMoney] += Business[Player[playerid][pBusiness]][bPrice]/3; SaveBusiness(Player[playerid][pBusiness]);
					format(strock,101,"Бизнес: {1faee9}%s\n{ffffff}Владелец: {1faee9}%s",Business[Player[playerid][pBusiness]][bName],Business[Player[playerid][pBusiness]][bOwner]);
					UpdateDynamic3DTextLabelText(Business[Player[playerid][pBusiness]][bText],0xFFFFFFFF,strock);
					Player[playerid][pBusiness] = 9999;
					SCM(playerid,0xFF0000FF,"Ваш бизнес был продан за долгую неуплату коммунальных услуг! Треть суммы со стоимости бизнеса вам возвращена.");
			}   }
			if(0 < Player[playerid][pWanted] < 7) Player[playerid][pWanted]--, SetPlayerWantedLevel(playerid,Player[playerid][pWanted]);
			
		}  	SendClientMessageToAll(0x1faee9FF,"<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>");
  		for(new b; b <= Businesses; b++) { if(strcmp(Business[b][bOwner],"None",true,25) == 0) continue; Business[b][bCommunal] -= 250; }
		for(new h; h <= Houses; h++) { if(strcmp(House[h][hOwner],"None",true,25) == 0) continue; House[h][hCommunal] -= 150; }
	}		
 	if(hour == 04 && minute == 55 && second == 00) {
   	    SendClientMessageToAll(COLOR_RED,"<~~~~~~~~~~~~~~~~~ [ Утренний Рестарт ] ~~~~~~~~~~~~~~~~~~~~~~~>");
        SendClientMessageToAll(COLOR_RED,"Внимание, через 6 минут - рестарт сервера!");
		SendClientMessageToAll(COLOR_RED,"<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>");
		print("Утренний рестарт сервера!");
		GlobalSave();
   	}
   	else if(hour == 05 && minute == 01 && second == 00) GameTextForAll("~r~Restart", 10000,5), GameModeExit();
   	return true;
}

static p_AnimationLibraries[][] =
{
    !"AIRPORT",		!"ATTRACTORS",		!"BAR",				!"BASEBALL",
    !"BD_FIRE",		!"BEACH",			!"BENCHPRESS",		!"BF_INJECTION",
    !"BIKED",		!"BIKEH",			!"BIKELEAP",		!"BIKES",
    !"BIKEV",		!"BIKE_DBZ",		!"BMX",				!"BOMBER",
    !"BOX",			!"BSKTBALL",		!"BUDDY",			!"BUS",
    !"CAMERA",		!"CAR",				!"CARRY",			!"CAR_CHAT",
    !"CASINO",		!"CHAINSAW",		!"CHOPPA",			!"CLOTHES",
    !"COACH",		!"COLT45",			!"COP_AMBIENT",		!"COP_DVBYZ",
    !"CRACK",		!"CRIB",			!"DAM_JUMP",		!"DANCING",
    !"DEALER",		!"DILDO",			!"DODGE",			!"DOZER",
    !"DRIVEBYS",	!"FAT",				!"FIGHT_B",			!"FIGHT_C",
    !"FIGHT_D",		!"FIGHT_E",			!"FINALE",			!"FINALE2",
    !"FLAME",		!"FLOWERS",			!"FOOD",			!"FREEWEIGHTS",
    !"GANGS",		!"GHANDS",			!"GHETTO_DB",		!"GOGGLES",
    !"GRAFFITI",	!"GRAVEYARD",		!"GRENADE",			!"GYMNASIUM",
    !"HAIRCUTS",	!"HEIST9",			!"INT_HOUSE",		!"INT_OFFICE",
    !"INT_SHOP",	!"JST_BUISNESS",	!"KART",			!"KISSING",
    !"KNIFE",		!"LAPDAN1",			!"LAPDAN2",			!"LAPDAN3",
    !"LOWRIDER",	!"MD_CHASE",		!"MD_END",			!"MEDIC",
    !"MISC",		!"MTB",				!"MUSCULAR",		!"NEVADA",
    !"ON_LOOKERS",	!"OTB",				!"PARACHUTE",		!"PARK",
    !"PAULNMAC",	!"PED",				!"PLAYER_DVBYS",	!"PLAYIDLES",
    !"POLICE",		!"POOL",			!"POOR",			!"PYTHON",
    !"QUAD",		!"QUAD_DBZ",		!"RAPPING",			!"RIFLE",
    !"RIOT",		!"ROB_BANK",		!"ROCKET",			!"RUSTLER",
    !"RYDER",		!"SCRATCHING",		!"SHAMAL",			!"SHOP",
    !"SHOTGUN",		!"SILENCED",		!"SKATE",			!"SMOKING",
    !"SNIPER",		!"SPRAYCAN",		!"STRIP",			!"SUNBATHE",
    !"SWAT",		!"SWEET",			!"SWIM",			!"SWORD",
    !"TANK",		!"TATTOOS",			!"TEC",				!"TRAIN",
    !"TRUCK",		!"UZI",				!"VAN",				!"VENDING",
    !"VORTEX",		!"WAYFARER",		!"WEAPONS",			!"WUZI",
    !"WOP",			!"GFUNK",			!"RUNNINGMAN"
};
stock PreloadPlayerAnimations(playerid) {
	for(new i = 0; i < sizeof(p_AnimationLibraries); i++) {
		ApplyAnimation(playerid,
			p_AnimationLibraries[i],
			!"null",
			0.0, 0, 0, 0, 0, 0
		);
	}
	return true;
}

apublic UpdateSpeed(playerid)  {
	#define vehicleid GetPlayerVehicleID(playerid)
	new str[14];
 	//if(GetPlayerVehicleID(playerid) != GetPVarInt(playerid,"AC_VID")) { SetPVarInt(playerid,"AC_VID",INVALID_VEHICLE_ID),  SCM(playerid,COLOR_LIGHTRED,"Вы были кикнуты. Опкод: {ffffff}U6S5P3"), KickEx(playerid); return true; }
	if(GetVehicleSpeed(vehicleid) > 127 && Player[playerid][pAdmin] < 1) return SCM(playerid,COLOR_LIGHTRED,"Вы были кикнуты. Опкод: {ffffff}U1S2P7"), KickEx(playerid);
	if(PlayerInBoat(GetPlayerVehicleID(playerid)) && PlayerInBike(GetPlayerVehicleID(playerid)) && PlayerInPlane(GetPlayerVehicleID(playerid))) return true;
	fcor
 	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
	if(VVB<vehicleid:limit>) {
		GetVehicleVelocity(vehicleid,x,y,z);
  		if((x > 0.45 || x < -0.45) || (y > 0.45 || y < -0.45)) SetVehicleVelocity(vehicleid,x*0.78,y*0.78,z);
	}
 	if(Fuel[vehicleid] < 1) {
 		Fuel[vehicleid] = 0,GameTextForPlayer(playerid, "~r~FUEL END", 2000, 1);
 		SetVehicleParamsEx(vehicleid,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,alarm,doors,bonnet,boot,objective), VNULL<vehicleid:engines>;
 		return true;
  	}
  	if(VVB<vehicleid:engines>) {
	  	Fuel[vehicleid] -= 0.0080,format(str, sizeof(str), (Fuel[vehicleid] <= 70) ? ("~r~%.0f") : ("~g~%.0f") ,Fuel[vehicleid]), PlayerTextDrawSetString(playerid,sfuelv[playerid],str);
	  	if(vehicleid == Player[playerid][PlayerCar]) Player[playerid][pMilage] += (GetVehicleSpeed(vehicleid)/2.65)/1000, format(str, sizeof(str),"%.1f KM",Player[playerid][pMilage]), TextDrawSetString(smilage[playerid],str);
	}
  	format(str, sizeof(str), "%d", GetVehicleSpeed(vehicleid)), PlayerTextDrawSetString(playerid,sspeed[playerid],str);
  	#undef vehicleid
  	return true;
}

GetVehicleSpeed(vehicleid) {
    fcor
    GetVehicleVelocity(vehicleid, x, y, z);
    return floatround(floatsqroot(x*x + y*y + z*z)*100.5);
}

PlayerToPlayer(playerid,params,Float:radious) {
	new Float:X,Float:Y,Float:Z,Float:X1,Float:Y1,Float:Z1;
	GetPlayerPos(playerid,X,Y,Z), GetPlayerPos(params,X1,Y1,Z1);
	if(IsPlayerInRangeOfPoint(playerid,radious,X1,Y1,Z1)) return true;
	return false;
}

FractionSkin(playerid) {
	switch(Player[playerid][pFraction][1]) {
	    case 1: {
			switch(Player[playerid][pFraction][2]){
				case 1..2: SetPlayerSkin(playerid,105), Player[playerid][pModel][1] = 105;
				case 3..4: SetPlayerSkin(playerid,106), Player[playerid][pModel][1] = 106;
				case 6..7: SetPlayerSkin(playerid,107), Player[playerid][pModel][1] = 107;
				case 8: SetPlayerSkin(playerid,269), Player[playerid][pModel][1] = 107;
				case 9: SetPlayerSkin(playerid,271), Player[playerid][pModel][1] = 271;
				case 10: SetPlayerSkin(playerid,270), Player[playerid][pModel][1] = 270;
			}
			if(Player[playerid][pSex] == 2) SetPlayerSkin(playerid,193), Player[playerid][pModel][1] = 193;
		}
		case 2: {
			switch(Player[playerid][pFraction][2]){
				case 1..2: SetPlayerSkin(playerid,103), Player[playerid][pModel][1] = 103;
				case 3..6: SetPlayerSkin(playerid,102), Player[playerid][pModel][1] = 102;
				case 7..10: SetPlayerSkin(playerid,104), Player[playerid][pModel][1] = 104;
			}
			if(Player[playerid][pSex] == 2) SetPlayerSkin(playerid,195), Player[playerid][pModel][1] = 195;
		}
		case 3: {
			switch(Player[playerid][pFraction][2]){
				case 1..2: SetPlayerSkin(playerid,109), Player[playerid][pModel][1] = 108;
				case 3..6: SetPlayerSkin(playerid,109), Player[playerid][pModel][1] = 109;
				case 7..10: SetPlayerSkin(playerid,110), Player[playerid][pModel][1] = 110;
			}
			if(Player[playerid][pSex] == 2) SetPlayerSkin(playerid,190), Player[playerid][pModel][1] = 190;
		}
		case 4: {
			switch(Player[playerid][pFraction][2]){
				case 1..2: SetPlayerSkin(playerid,114), Player[playerid][pModel][1] = 114;
				case 3..6: SetPlayerSkin(playerid,116), Player[playerid][pModel][1] = 116;
				case 7..10: SetPlayerSkin(playerid,115), Player[playerid][pModel][1] = 115;
			}
			if(Player[playerid][pSex] == 2) SetPlayerSkin(playerid,56), Player[playerid][pModel][1] = 56;
		}
		case 5: {
			switch(Player[playerid][pFraction][2]){
				case 1..2: SetPlayerSkin(playerid,175), Player[playerid][pModel][1] = 175;
				case 3..6: SetPlayerSkin(playerid,174), Player[playerid][pModel][1] = 174;
				case 7..10: SetPlayerSkin(playerid,173), Player[playerid][pModel][1] = 173;
			}
			if(Player[playerid][pSex] == 2) SetPlayerSkin(playerid,41), Player[playerid][pModel][1] = 41;
		}
		case 6: {
			switch(Player[playerid][pFraction][2]){
				case 1..7: SetPlayerSkin(playerid,287), Player[playerid][pModel][1] = 287;
				case 8..10: SetPlayerSkin(playerid,179), Player[playerid][pModel][1] = 179;
			}
			if(Player[playerid][pSex] == 2) SetPlayerSkin(playerid,191), Player[playerid][pModel][1] = 191;
		}
		case 7..9: {
			switch(Player[playerid][pFraction][2]){
				case 1: SetPlayerSkin(playerid,284), Player[playerid][pModel][1] = 284;
				case 2: SetPlayerSkin(playerid,280), Player[playerid][pModel][1] = 280;
				case 3: SetPlayerSkin(playerid,282), Player[playerid][pModel][1] = 282;
				case 4,5: SetPlayerSkin(playerid,285), Player[playerid][pModel][1] = 285;
				case 6: SetPlayerSkin(playerid,281), Player[playerid][pModel][1] = 281;
				case 7,8: SetPlayerSkin(playerid,288), Player[playerid][pModel][1] = 288;
				case 9,10: SetPlayerSkin(playerid,283), Player[playerid][pModel][1] = 283;
			}
			if(Player[playerid][pSex] == 2) SetPlayerSkin(playerid,141), Player[playerid][pModel][1] = 141;
		}
		case 10: {
		    switch(Player[playerid][pFraction][2]){
				case 1..7: SetPlayerSkin(playerid,286), Player[playerid][pModel][1] = 286;
				case 8: SetPlayerSkin(playerid,166), Player[playerid][pModel][1] = 166;
				case 9,10 : SetPlayerSkin(playerid,165), Player[playerid][pModel][1] = 165;
			}
			if(Player[playerid][pSex] == 2) SetPlayerSkin(playerid,150), Player[playerid][pModel][1] = 150;
		}
		case 11: {
		    switch(Player[playerid][pFraction][2]){
		        case 1: SetPlayerSkin(playerid,227), Player[playerid][pModel][1] = 227;
		        case 2: SetPlayerSkin(playerid,17), Player[playerid][pModel][1] = 17;
				case 3: SetPlayerSkin(playerid,164), Player[playerid][pModel][1] = 164;
				case 4: SetPlayerSkin(playerid,295), Player[playerid][pModel][1] = 295;
				case 5 : SetPlayerSkin(playerid,295), Player[playerid][pModel][1] = 295;
			}
			if(Player[playerid][pSex] == 2) SetPlayerSkin(playerid,148), Player[playerid][pModel][1] = 148;
		}
		case 12: {
		    switch(Player[playerid][pFraction][2]){
		        case 1..4: SetPlayerSkin(playerid,20), Player[playerid][pModel][1] = 20;
		        case 5..7: SetPlayerSkin(playerid,170), Player[playerid][pModel][1] = 170;
				case 8..10 : SetPlayerSkin(playerid,240), Player[playerid][pModel][1] = 240;
			}
			if(Player[playerid][pSex] == 2) SetPlayerSkin(playerid,219), Player[playerid][pModel][1] = 219;
		}
		case 13,14: {
		    switch(Player[playerid][pFraction][2]){
		        case 1..3: SetPlayerSkin(playerid,101), Player[playerid][pModel][1] = 101;
                case 4,5: SetPlayerSkin(playerid,250), Player[playerid][pModel][1] = 250;
		        case 6,7: SetPlayerSkin(playerid,290), Player[playerid][pModel][1] = 290;
				case 8..10 : SetPlayerSkin(playerid,147), Player[playerid][pModel][1] = 147;
			}
			if(Player[playerid][pSex] == 2) SetPlayerSkin(playerid,93), Player[playerid][pModel][1] = 93;
		}
		case 15: {
		    switch(Player[playerid][pFraction][2]){
		        case 1..3: SetPlayerSkin(playerid,111), Player[playerid][pModel][1] = 111;
                case 4,5: SetPlayerSkin(playerid,112), Player[playerid][pModel][1] = 112;
		        case 7,8: SetPlayerSkin(playerid,125), Player[playerid][pModel][1] = 125;
				case 9,10 : SetPlayerSkin(playerid,126), Player[playerid][pModel][1] = 126;
			}
			if(Player[playerid][pSex] == 2) SetPlayerSkin(playerid,91), Player[playerid][pModel][1] = 91;
		}
		case 16: {
		    switch(Player[playerid][pFraction][2]){
		        case 1..3: SetPlayerSkin(playerid,123), Player[playerid][pModel][1] = 123;
                case 4,5: SetPlayerSkin(playerid,118), Player[playerid][pModel][1] = 118;
		        case 7,8: SetPlayerSkin(playerid,208), Player[playerid][pModel][1] = 208;
				case 9,10 : SetPlayerSkin(playerid,120), Player[playerid][pModel][1] = 120;
			}
			if(Player[playerid][pSex] == 2) SetPlayerSkin(playerid,169), Player[playerid][pModel][1] = 169;
		}
		case 17: {
		    switch(Player[playerid][pFraction][2]) {
		        case 1..3: SetPlayerSkin(playerid,274), Player[playerid][pModel][1] = 274;
		        case 4..6: SetPlayerSkin(playerid,276), Player[playerid][pModel][1] = 276;
		        case 7..8: SetPlayerSkin(playerid,275), Player[playerid][pModel][1] = 275;
		        case 9,10: SetPlayerSkin(playerid,70), Player[playerid][pModel][1] = 70;
		    }
			if(Player[playerid][pSex] == 2) SetPlayerSkin(playerid,219), Player[playerid][pModel][1] = 219;
		}
		case 18: SetPlayerSkin(playerid,Player[playerid][pModel][0]);
	}
	return true;
}

stock FractionColor(playerid) {
	switch(Player[playerid][pFraction][1]) {
	    case 0: SetPlayerColor(playerid,0xFFFFFF33);
	    case 1: SetPlayerColor(playerid,0x00D90033);
	    case 2: SetPlayerColor(playerid,0xD900D333);
	    case 3: SetPlayerColor(playerid,0xFFC80133);
	    case 4: SetPlayerColor(playerid,0x00FFFF33);
	    case 5: SetPlayerColor(playerid,0x008CF033);
	    case 6: SetPlayerColor(playerid,0xF5DAB933);
	    case 7..9: SetPlayerColor(playerid,0x37373733);
	    case 10: SetPlayerColor(playerid,0xDDA64733);
	    case 11: SetPlayerColor(playerid,0xB2E9EA33);
	    case 12: SetPlayerColor(playerid,0xE13D3D33);
	    case 13: SetPlayerColor(playerid,0x00B3FF33);
	    case 15: SetPlayerColor(playerid,0x50697133);
	    case 16: SetPlayerColor(playerid,0xF6520C33);
		case 17: SetPlayerColor(playerid,0xF8353533);
		case 18: SetPlayerColor(playerid,0xD5FF0033);
	}
	return true;
}

apublic KickPlayer(playerid) Kick(playerid);

apublic PickupFreeze(playerid) return TogglePlayerControllable(playerid,1);

PositionWarehouse(playerid) return (IsPlayerInRangeOfPoint(playerid, 3.0, 2465.1421,-1661.2888,2047.2004) && GetPlayerVirtualWorld(playerid) == Player[playerid][pFraction][1]) ? true : false;

PositionSpawnGang(playerid) return (PlayerToZone(playerid, Zone[Zone[36][gID]][gminX],Zone[Zone[36][gID]][gminY],Zone[Zone[36][gID]][gmaxX],Zone[Zone[36][gID]][gmaxY]) ||
	PlayerToZone(playerid, Zone[Zone[11][gID]][gminX],Zone[Zone[11][gID]][gminY],Zone[Zone[11][gID]][gmaxX],Zone[Zone[11][gID]][gmaxY]) ||
	PlayerToZone(playerid, Zone[Zone[79][gID]][gminX],Zone[Zone[79][gID]][gminY],Zone[Zone[79][gID]][gmaxX],Zone[Zone[79][gID]][gmaxY]) ||
 	PlayerToZone(playerid, Zone[Zone[72][gID]][gminX],Zone[Zone[72][gID]][gminY],Zone[Zone[72][gID]][gmaxX],Zone[Zone[72][gID]][gmaxY]) ||
 	PlayerToZone(playerid, Zone[Zone[42][gID]][gminX],Zone[Zone[42][gID]][gminY],Zone[Zone[42][gID]][gmaxX],Zone[Zone[42][gID]][gmaxY]) ) ? true : false;


GetGangZoneColor(g) {
    new color;
    switch(Zone[g][gFraction])
    {
        case 1: color = 0x29CA5299;
        case 2: color = 0xB322E499;
	    case 3: color = 0xFFC80199;
	    case 4: color = 0x00FFFF99;
	    case 5: color = 0x008CF099;
        default: color = 0xFFFFFF00;
    }
    return color;
}

stock PlayerToZone(playerid, Float:min_x, Float:min_y, Float:max_x, Float:max_y) {
    fcor
    GetPlayerPos(playerid, x, y, z);
    return ((x <= max_x && x >= min_x) && (y <= max_y && y >= min_y)) ? true : false;
}

stock GetGangName(f) {
	new string[16];
    switch(f) {
    	case 1: string = "Grove Gang:";
     	case 2: string = "Ballas Gang:";
     	case 3: string = "Vagos Gang:";
     	case 4: string = "Aztec Gang:";
     	case 5: string = "Rifa Gang:";
    }
    return string;
}

apublic GangZoneStatus(i) {
   	new zwarstr[8];
   	if(ZoneOnBattle[i] == 1) {
	   	if(Zone[i][gTime] > 0) Zone[i][gTime]--;
	    foreach(new x : Player) {
    		if(Player[x][pFraction][1] == Zone[i][gWar] || Player[x][pFraction][1] == Zone[i][gFraction]) {
				format(zwarstr,4,"%i",InZone[i][Zone[i][gFraction]]);
				PlayerTextDrawSetString(x,gFScore[x],zwarstr);
				format(zwarstr,4,"%i",InZone[i][Zone[i][gWar]]);
				PlayerTextDrawSetString(x,gTScore[x],zwarstr);
				format(zwarstr,6,"%i",Zone[i][gTime]);
				PlayerTextDrawSetString(x,gTimeTick[x], zwarstr);
			}
			if(Zone[i][gTime] < 1 && InZone[i][Zone[i][gFraction]] != InZone[i][Zone[i][gWar]]) {
				new winner;
				winner = (InZone[i][Zone[i][gFraction]] > InZone[i][Zone[i][gWar]]) ? Zone[i][gFraction] : Zone[i][gWar];
				if(winner == Zone[i][gFraction]) SendRadioMessage(Zone[i][gFraction], 0x03c03cFF, "Вам удалось отвоевать территорию!"), SendRadioMessage(Zone[i][gWar], 0xAC7575FF, "Вам не удалось отвоевать территорию!");
				else SendRadioMessage(Zone[i][gWar], 0x03c03cFF, "Вам удалось отвоевать территорию!"), SendRadioMessage(Zone[i][gFraction], 0xAC7575FF, "Вам не удалось отвоевать территорию!");
				if(Player[x][pFraction][1] == Zone[i][gFraction] || Player[x][pFraction][1] == Zone[i][gWar]) {
					TextDrawHideForPlayer(x,gBox),PlayerTextDrawHide(x,gFGang[x]),PlayerTextDrawHide(x,gTGang[x]),PlayerTextDrawHide(x,gFScore[x]),PlayerTextDrawHide(x,gTScore[x]),TextDrawHideForPlayer(x,gArea),
					PlayerTextDrawHide(x,gIDs[x]),TextDrawHideForPlayer(x,gsTime),PlayerTextDrawHide(x,gTimeTick[x]);
				}
				if(GWars[0] == i) GWars[0] = 0;
				else GWars[1] = 0;
				InWar[Zone[i][gWar]] = 0, InWar[Zone[i][gFraction]] = 0;
				ZoneOnBattle[i] = 0, Zone[i][gWar] = 0, Zone[i][gFraction] = winner;
				GangZoneStopFlashForAll(Zone[i][gID]), GangZoneHideForAll(Zone[i][gID]), GangZoneShowForAll(Zone[i][gID],GetGangZoneColor(i));
				SaveGangZone(i);
				break;
}   }   }   }

Time() {
	new minute,second,hour;
	gettime(hour,minute,second);
	return ((hour >= 10 && hour <= 00 && (hour % 2 == 0)) && minute <= 15) ? true : false;
}

stock split(const strsrc[], strdest[][], delimiter) {
    new i, li, aNum, len;
    while(i <= strlen(strsrc)) {
        if(strsrc[i] == delimiter || i == strlen(strsrc)) {
            len = strmid(strdest[aNum], strsrc, li, i, 128);
            strdest[aNum][len] = 0;
            li = i+1;
            aNum++;
        }
        i++;
    }
    return true;
}

GetSplitName(name[],val) {
    new names[2][MAX_PLAYER_NAME];
    split(name, names, '_');
    return names[val];
}

apublic IsVehicleOccupied(vehicleid) {
	foreach(new i : Player) return (IsPlayerInVehicle(i,vehicleid)) ? i : -1;
	return -1;
}

GetPlayerSpeed(playerid) {
    new Float:Coord[4]; GetPlayerVelocity(playerid, Coord[0], Coord[1], Coord[2]);
    return floatround(floatsqroot(floatpower(floatabs(Coord[0]), 2.0) + floatpower(floatabs(Coord[1]), 2.0) + floatpower(floatabs(Coord[2]), 2.0)) * 213.3);
}

apublic ShowStats(playerid) {
    new string[44+1];
    PlayerTextDrawSetString(playerid,mm20[playerid],GetSplitName(Name(playerid),0));
    PlayerTextDrawSetString(playerid,mm21[playerid],GetSplitName(Name(playerid),1));
    format(string,15,"%d (%d/%d)",Player[playerid][pLevel],Player[playerid][pExp],Player[playerid][pLevel]*6);
    PlayerTextDrawSetString(playerid,mm22[playerid],string);
    switch(Player[playerid][pFraction][1]) {
		case 1: string = "Grove Gang";
  		case 2: string = "Ballas Gang";
  		case 3: string = "Vagos Gang";
  		case 4: string = "Aztecas Gang";
  		case 5: string = "Rifa Gang";
  		case 6: string = "Army LV";
  		case 7: string = "LSPD";
  		case 8: string = "SFPD";
  		case 9: string = "LVPD";
  		case 10: string = "FBI";
  		case 11: string = "Mayor";
  		case 12: string = "Dr.School";
	    case 13: string = "SANews";
	    case 14: string = "CNN";
	    case 15: string = "Rus. Mafia";
	    case 16: string = "Triada Maf.";
	    case 17: string = "MOH";
	    case 18: string = "Race Club";
		default: string = "None";
  	}
   	PlayerTextDrawSetString(playerid,mm23[playerid],string);
   	format(string,4,"%d",Player[playerid][pFraction][2]);
   	PlayerTextDrawSetString(playerid,mm24[playerid],string);
    PlayerTextDrawSetString(playerid,mm25[playerid], (Player[playerid][pSex] == 1) ? ("Man") : ("Woman"));
	format(string,8,"%d",Player[playerid][pPhone]);
	PlayerTextDrawSetString(playerid,mm26[playerid],string);
	PlayerTextDrawSetString(playerid,mm27[playerid],Ip(playerid));
	PlayerTextDrawSetPreviewModel(playerid,mm43[playerid], (Player[playerid][pCar][0] > 1) ? Player[playerid][pCar][0] : 0);
	PlayerTextDrawSetPreviewVehCol(playerid,mm43[playerid], Player[playerid][pCar][1], Player[playerid][pCar][2]);
	if(Player[playerid][pHouse] == 9999) string = "House: None";
	else format(string,sizeof(string), "House: %d", Player[playerid][pHouse]);
	PlayerTextDrawSetString(playerid,mm45[playerid],string);
	if(Player[playerid][pBusiness] == 9999) string = "Buss: None";
	else format(string,sizeof(string), "Buss: %s",Business[Player[playerid][pBusiness]][bName]);
	PlayerTextDrawSetString(playerid,mm47[playerid],string);
	PlayerTextDrawSetString(playerid,mm46[playerid], (Player[playerid][pCar][0] > 100) ? ("Car: Yes") : ("Car: None"));
   	TextDrawShowForPlayer(playerid,mm0);
   	TextDrawShowForPlayer(playerid,mm1);
   	TextDrawShowForPlayer(playerid,mm2);
   	TextDrawShowForPlayer(playerid,mm3);
   	TextDrawShowForPlayer(playerid,mm4);
   	TextDrawShowForPlayer(playerid,mm5);
   	TextDrawShowForPlayer(playerid,mm6);
   	PlayerTextDrawSetPreviewModel(playerid,mm7[playerid], GetPlayerSkin(playerid));
   	PlayerTextDrawShow(playerid,mm7[playerid]);
   	TextDrawShowForPlayer(playerid,mm8);
   	TextDrawShowForPlayer(playerid,mm9);
   	TextDrawShowForPlayer(playerid,mm10);
   	TextDrawShowForPlayer(playerid,mm11);
   	TextDrawShowForPlayer(playerid,mm12);
   	TextDrawShowForPlayer(playerid,mm13);
   	TextDrawShowForPlayer(playerid,mm14);
   	TextDrawShowForPlayer(playerid,mm15);
   	TextDrawShowForPlayer(playerid,mm16);
   	TextDrawShowForPlayer(playerid,mm17);
   	TextDrawShowForPlayer(playerid,mm18);
   	TextDrawShowForPlayer(playerid,mm19);
   	PlayerTextDrawShow(playerid,mm20[playerid]);
   	PlayerTextDrawShow(playerid,mm21[playerid]);
   	PlayerTextDrawShow(playerid,mm22[playerid]);
   	PlayerTextDrawShow(playerid,mm23[playerid]);
   	PlayerTextDrawShow(playerid,mm24[playerid]);
   	PlayerTextDrawShow(playerid,mm25[playerid]);
   	PlayerTextDrawShow(playerid,mm26[playerid]);
   	PlayerTextDrawShow(playerid,mm27[playerid]);
   	PlayerTextDrawShow(playerid,mm28[playerid]);
   	TextDrawShowForPlayer(playerid,mm29);
   	TextDrawShowForPlayer(playerid,mm30);
   	TextDrawShowForPlayer(playerid,mm31);
   	TextDrawShowForPlayer(playerid,mm32);
   	TextDrawShowForPlayer(playerid,mm33);
   	TextDrawShowForPlayer(playerid,mm34);
	TextDrawShowForPlayer(playerid,mm35);
	TextDrawShowForPlayer(playerid,mm36);
 	TextDrawShowForPlayer(playerid,mm37);
 	TextDrawShowForPlayer(playerid,mm38);
 	TextDrawShowForPlayer(playerid,mm39);
 	TextDrawShowForPlayer(playerid,mm40);
 	TextDrawShowForPlayer(playerid,mm41);
	TextDrawShowForPlayer(playerid,mm42);
	PlayerTextDrawShow(playerid,mm43[playerid]);
	TextDrawShowForPlayer(playerid,mm44);
	PlayerTextDrawShow(playerid,mm45[playerid]);
  	PlayerTextDrawShow(playerid,mm46[playerid]);
  	PlayerTextDrawShow(playerid,mm47[playerid]);
	SetPVarInt(playerid,"Menu",1);
  	SelectTextDraw(playerid, 0xFF464655),Player[playerid][TDSelect] = true;
 	return true;
}

PlayerGangster(playerid)  return (Player[playerid][pFraction][1] >= GROVE && Player[playerid][pFraction][1] <= RIFA) ? true : false;
PlayerLaw(playerid)  return (Player[playerid][pFraction][1] >= ARMY && Player[playerid][pFraction][1] <= FBI) ? true : false;
PlayerCF(playerid)  return (Player[playerid][pFraction][1] >= LSPD && Player[playerid][pFraction][1] <= FBI) ? true : false;
PlayerCop(playerid)  return (Player[playerid][pFraction][1] >= LSPD && Player[playerid][pFraction][1] <= LVPD) ? true : false;
PlayerInBoat(vehicleid)	{	switch(GetVehicleModel(vehicleid)) {	case 472,473,493,595,484,430,432,452..454,446: return true; }	return false;	}
PlayerInBike(vehicleid)	{	switch(GetVehicleModel(vehicleid)) {	case 448,435,449,450,457,462,464,465,481,485,501,509,510,530,564,569,570,584,594,606,607,608,610,611: return true; } return false;	}
PlayerInPlane(vehicleid)	{	switch(GetVehicleModel(vehicleid)) {	case 592,577,511,512,593,520,553,476,519,460,513:  return true; }   return false; }

AC_SetPlayerPos(playerid, Float:x, Float:y, Float:z)	SetPlayerPos(playerid,x,y,z), SetPVarFloat(playerid,"AX",x),SetPVarFloat(playerid,"AY",y),SetPVarFloat(playerid,"AZ",z), SetPVarInt(playerid,"AirTime",3);

stock memset(array[], value, size=sizeof array)
{   //pro-pawn.ru/showthread.php?14919
    static fill_instruction_offset=0;
    emit {
        load.pri fill_instruction_offset
        jnz fill_array
        lctrl 6
        move.alt
        lctrl 0
        add
        move.alt
        lctrl 1
        sub.alt
        add.c (cellbits / charbits * 23)
        stor.pri fill_instruction_offset
    fill_array:
        load.s.pri size
        shl.c.pri 2
        sref.pri fill_instruction_offset
        load.s.pri value
        load.s.alt array
        fill 1
    }
    return 0;
}

// ================== Anti - Cheats =============

#if !defined CopyRightString
    #error CopyRight Panteleev has been Deleted!
#endif
