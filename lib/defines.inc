
#define 	SQL_HOST 									"localhost"//localhost
#define 	SQL_USER 									"root"//root
#define 	SQL_DB										"Light"
#define 	SQL_PASS									""

#define apublic%0(%1)   	forward%0(%1);  public%0(%1)
#define Name(%0)			Player[%0][pName]
#define Ip(%0)      		Player[%0][pIP]
#define SCM                 SendClientMessage
#define Success(%0)         ShowPlayerDialog(%0,990,DIALOG_STYLE_MSGBOX,"{cc7722}Успешно","{ffffff}Вы {03c03c}успешно {ffffff}выполнили данную операцию!","Ок","");
#define Error               ShowPlayerDialog(playerid,990,DIALOG_STYLE_MSGBOX,"{ff2400}Ошибка!","{ffffff}Операция {ff2400}не удалась!","Ок","");

#define COLOR_PURPLE        0xFF80CAFF
#define COLOR_GRAD1 		0xB4B5B7FF
#define COLOR_GRAD2 		0xBFC0C2FF
#define COLOR_GRAD3 		0xCBCCCEFF
#define COLOR_GRAD4 		0xD8D8D8FF
#define COLOR_GRAD5 		0xE3E3E3FF
#define COLOR_GRAD6 		0xF0F0F0FF
#define COLOR_GREY 			0xAFAFAFAA
#define COLOR_GREEN 		0x33AA33AA
#define COLOR_RED 			0xff0000AA
#define COLOR_FADE1 		0xE6E6E6E6
#define COLOR_FADE2 		0xC8C8C8C8
#define COLOR_FADE3 		0xAAAAAAAA
#define COLOR_FADE4 		0x8C8C8C8C
#define COLOR_FADE5 		0x6E6E6E6E
#define COLOR_WHITE         0xFFFFFFFF
#define COLOR_LIGHTBLUE     0x6495EDFF
#define COLOR_LIGHTRED 		0xFF6347FF

#undef MAX_PLAYERS
const MAX_PLAYERS = 100;

#undef MAX_VEHICLES
const MAX_VEHICLES = 400;

#define MAX_HOUSES          500
#define MAX_BIZNES  		65
#define MAX_ATMS    		65
#define MAX_DROPED_ITEMS    200

#define KickEx(%0) SetTimerEx("KickPlayer",500,false,"i",%0)

#define GROVE   1
#define BALLAS  2
#define VAGOS   3
#define AZTEC   4
#define RIFA    5
#define ARMY    6
#define LSPD    7
#define SFPD    8
#define LVPD    9
#define FBI     10
#define MAYOR   11

#define	fcor	new Float:x, Float:y, Float:z;
#define	putPlayerInVehicle(%0,%1,%2) SetPVarInt(%0,"AC_VID",%1), PutPlayerInVehicle(%0,%1,%2)

#define percent(%0,%1)  %0+((%0/100)*%1)
#define pernumber(%0,%1)  %0+((%0*%1)/100)

#define COLOR_POLICE    0x5083B2FF
#define COLOR_ARMY      0x03c03cFF
#define COLOR_NEG       0xAC7575FF
#define COLOR_SERVER    0x1FAEE9FF

#define	VVB<%0:%1>		(VVB[%0] & %1)
#define VXOR<%0:%1>  	VVB[%0] ^= %1
#define VNULL<%0:%1>  	VVB[%0] &= ~%1
#define VUP<%0:%1>  	VVB[%0] |= %1
#define VRES<%0>		VVB[%0] = BooleanVVar:0

new MySQL:connects;

new Iterator:StreamedPlayers[MAX_PLAYERS]<MAX_PLAYERS-1>;

#define SS  GetPVarInt(playerid,"SelectSlot")
