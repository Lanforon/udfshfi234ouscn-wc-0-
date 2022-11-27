static giveplayerid;
#define CADMIN_INFO 0xAFAFAFAA
//=================================== 1 уровень ===================================//
CMD:a(playerid, params[]) {
    if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
	new string[144],text[101];
	if(sscanf(params,"s[100]",text)) return SendEsp(playerid,"/a [текст]");
	format(string, sizeof(string), ""YELLOW"[A - %d]"BLUE" %s(%i): %s",PI[playerid][pAdmin],player_name[playerid],playerid,text);
	SendAdminMessage(COLOR_YELLOW, string);
	return true;
}
CMD:kick(playerid, params[]) {
    if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
	new text[65],string[356];
	if(sscanf(params, "us[64]",giveplayerid,text)) return SendEsp(playerid, "/kick [playerid] [причина]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	if(PI[playerid][pAdmin] < PI[giveplayerid][pAdmin]) return 1;
	if(GetString(player_name[giveplayerid],"Oscar_Floyd")) return 1;
	if(IsAIP(text)) return 1;
	format(string, 128, "Администратор %s кикнул %s. Причина: %s",player_name[playerid],player_name[giveplayerid],text);
	SendClientMessageToAll(COLOR_LIGHTRED, string);
	WriteLog(LOG_KICK,player_name[playerid],player_name[giveplayerid],text);
	gAdmin[playerid][ADMIN_KICK] ++;
	new hour,minute;
	new year,month,day;

	getdate(year, month, day);
	gettime(hour,minute);
	static const f_str[] = "\
			"W"Внимание! Вы были "NO"кикнуты"W" с сервера.\n\n\
			"W"Кикнул: "NO"%s\n\
			"W"Дата: "ORANGE"%d-%d-%d %02d:%02d\n\
			"W"Причина: "ORANGE"%s\n\n\
			"W"Если вы считаете, что это ошибка, сделайте скриншот(F8) данного окна,\n\
			иначе Ваша жалоба будет не принята.";
	format(string,sizeof(string),f_str,player_name[playerid], day, month, year,hour, minute, text);

	new str[MAX_PLAYER_NAME+1];
	format(str,sizeof(str),"%s",player_name[giveplayerid]);
	D(giveplayerid, DIALOG_NONE, DSM, str, string, "Закрыть", "");
	Kick(giveplayerid);
	return true;
}
ALT:pm:ans;
CMD:pm(playerid, params[]) {
    if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
	new text[77],string[144];
    if(sscanf(params, "us[76]",giveplayerid,text)) return SendEsp(playerid, "/pm [playerid] [текст]");
    if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	if(IsAIP(text)) return 1;
	if(giveplayerid == playerid) return ErrorMessage(playerid,"Нельзя ответить самому себе");
	format(string, sizeof(string), "Ответ от %s[%i]: %s",player_name[playerid],playerid,text);
	SendClientMessage(giveplayerid, 0xffa141FF, string);
	format(string, sizeof(string), ""W"%s[%i] {FFa500}К "W"%s[%i]: {FFa500}%s",player_name[playerid],playerid,player_name[giveplayerid],giveplayerid,text);
	SendAdminMessage(0xFfa500AA, string);
	gAdmin[playerid][ADMIN_PM] ++;
    return true;
}
CMD:mute(playerid, params[]) {
    if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
	new time, text[33],string[144];	
	if(sscanf(params, "uds[32]",giveplayerid,time,text)) return SendEsp(playerid, "/mute [playerid] [минуты] [причина]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	if(IsAIP(text)) return 1;
	if(strlen(text) > 30) return ErrorMessage(playerid,"Причина должна быть меньше 30 символов");
 	if(time > 120) return ErrorMessage(playerid,"Выдать бан чата можно максимум на 120 минут");
	if(PI[giveplayerid][pMute] > 0) {
		PI[giveplayerid][pMute] = 0;
		UpdatePlayerData(giveplayerid,"mute",0);
		format(string, sizeof(string), "Администратор %s снял бан чата у %s",player_name[playerid],player_name[giveplayerid]);
		SendClientMessageToAll(COLOR_LIGHTRED, string);
		return true;
	}
	PI[giveplayerid][pMute] = time*60;
	UpdatePlayerData(giveplayerid,"mute",PI[giveplayerid][pMute]);
	format(string, sizeof(string), "Администратор %s заблокировал чат %s на %d мин. Причина: %s",player_name[playerid],player_name[giveplayerid], time, text);
	SendClientMessageToAll(COLOR_LIGHTRED, string);
	SendClientMessage(giveplayerid, COLOR_GREEN, "Время до снятия бана чата: "W"/time");
	gAdmin[playerid][ADMIN_MUTE] ++;
	WriteLog(LOG_MUTE,player_name[playerid],player_name[giveplayerid],text);
	return true;
}
CMD:weap(playerid,params[]) {
	if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
	if(sscanf(params,"u", giveplayerid)) return	SendEsp(playerid, "/weap [playerid]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	new Gun[13], Ammo[13],string[700];
	for(new i = 0; i < 13; i++) {
		GetPlayerWeaponData(giveplayerid, i, Gun[i], Ammo[i]);
		format(string, sizeof(string), "%s"W"Slot: %i\t Weaponid: %i\t Ammo: %i\n", string, i, Gun[i], Ammo[i]);
		if(i == 12) format(string, sizeof(string), "%s\n",string);
	}
	for(new slot = 2; slot <= 6; slot++) {
		GetPlayerWeaponData(giveplayerid, slot, Gun[slot], Ammo[slot]);
		format(string, sizeof(string), "%s{33AA33}Слот %i: %i\n",string, slot, PI[giveplayerid][pWeapon]);
	}
	D(playerid, DIALOG_NONE, DSM, player_name[giveplayerid], string, "Закрыть", "");
	return 1;
}
CMD:admins(playerid) {
 	if(PI[playerid][pAdmin] < 1 && !PI[playerid][pVips]) return true;
	new string[512];
	SendClientMessage(playerid, 0x33CC00AA, "Администрация онлайн:");
	foreach(new i : Player) {
		if(!IsPlayerConnected(i) || (!TI[i][tLogin]) || (PI[i][pAdmin] <= 0)) continue;
		if(TI[i][tAFK] >= 3) format(string, sizeof(string), "[A - %d] %s[%i] {ff0000}AFK",PI[i][pAdmin],player_name[i],i, Convert(TI[i][tAFK]));
		if(TI[i][tAFK] < 3) format(string, sizeof(string), "[A - %d] %s[%i]",PI[i][pAdmin],player_name[i],i);
		if(GetPlayerState(i) == PLAYER_STATE_SPECTATING) format(string, sizeof(string), "[A - %d] %s[%i] {33CC00}> /sp %d",PI[i][pAdmin],player_name[i],i,PI[i][pID]);
		SendClientMessage(playerid,COLOR_YELLOW,string);
	}
	return 1;
}
CMD:jail(playerid, params[]) {
    if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
	new time,text[31],string[144];
    if(sscanf(params, "uds[30]",giveplayerid,time,text)) return SendEsp(playerid, "/jail [playerid] [минуты] [причина]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	if(PI[giveplayerid][pJailTime]) return ErrorMessage(playerid, "Игрок в тюрьме");
	if(time > 120 || time < 5) return ErrorMessage(playerid, "От 5 до 120 минут");
	if(strlen(text) > 30) return ErrorMessage(playerid,"Причина должна быть меньше 30 символов");
	format(string, sizeof(string), "Вы посадили %s в тюрьму",player_name[giveplayerid]);
	SendClientMessage(playerid, COLOR_LIGHTRED, string);

	format(string, sizeof(string), "[A] %s[%d] посадил в тюрьму игрока %s[%d] на %d минут. Причина: %s",player_name[playerid],playerid,player_name[giveplayerid],giveplayerid,time,text);
	SendAdminMessage(CADMIN_INFO, string);

	DelGun(giveplayerid);
	PI[giveplayerid][pJail] = 2;
	PI[giveplayerid][pJailTime] = time*60;

	UpdatePlayerData(giveplayerid,"pJailTime", PI[giveplayerid][pJailTime]);
	UpdatePlayerData(giveplayerid,"pJail", 2);

	GameTextForPlayer(giveplayerid, "~w~YOU IN ~R~JAIL", 5000, 4);
	format(string, sizeof(string), "Вы были посажены в тюрьму администратором %s на %i минут(ы). Причина: %s",player_name[playerid],time,text);
	SendClientMessage(giveplayerid, COLOR_LIGHTRED, string);
	SendClientMessage(giveplayerid, COLOR_GREEN, "Время до выхода на свободу: "W"/time");
	SpawnPlayer(giveplayerid);
	gAdmin[playerid][ADMIN_JAIL] ++;
	WriteLog(LOG_JAIL,player_name[playerid],player_name[giveplayerid],text);
	return true;
}
CMD:unjail(playerid, params[]) {
	if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
	if(sscanf(params, "u",giveplayerid)) return SendEsp(playerid, "/unjail [playerid]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	if(!PI[giveplayerid][pJailTime] && PI[giveplayerid][pJail] == 0) return ErrorMessage(playerid, "Игрок не в тюрьме");
	new string[128];
	format(string, sizeof(string), "Вы освободили %s", player_name[giveplayerid]);
	SendClientMessage(playerid, 0x09B000AA, string);
	format(string, sizeof(string), "[A] %s[%d] выпустил игрока %s[%d] из тюрьмы.",player_name[playerid],playerid,player_name[giveplayerid],giveplayerid);
	AdmMSG(CADMIN_INFO,string,3);
	SendClientMessage(giveplayerid,COLOR_GREEN, "Администратор выпустил Вас на свободу!");
	PI[giveplayerid][pJailTime] = 0;
	PI[giveplayerid][pJail] = 0;
	UpdatePlayerData(giveplayerid,"pJailTime", 0);
	UpdatePlayerData(giveplayerid,"pJail", 0);
	SpawnPlayer(giveplayerid);
	return 1;
}
CMD:prisoners(playerid, params[]) {
	if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;

	new string[(57+MAX_PLAYER_NAME-4+3+11+1)*30];
	foreach(new i: Player) {
		if(!PI[i][pJailTime]) continue;
		format(string, sizeof(string), "%s"ORANGE"%s"W" | ID: "BLUE"%d"W" | Время: "GREEN"%d\n", string, player_name [i], i, PI[i][pJailTime]);
	}
	if(isnull(string)) ErrorMessage(playerid, "Заключенных нет");
	else D(playerid, DIALOG_NONE, DSM, "Список заключенных", string, "Закрыть", "");
	return 1;
}
ALT:aad:msg;
CMD:aad(playerid, params[]) {
	if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
	if(isnull(params) || strlen(params) > 100) return SendEsp(playerid,"/aad [сообщение]");
	new string[144];
	format(string, sizeof(string), "Администратор %s: %s", player_name[playerid], params);
	SendClientMessageToAll(0xFFCD00AA,string);
	return 1;
}
CMD:alock(playerid, params[]) {
	if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
	GetVehicleParamsEx(GetNearestVehicle(playerid),engine,lights,alarm,doors,bonnet,boot,objective);
	PlayerPlaySound(playerid, 24600, 0.0, 0.0, 0.0);
	switch(doors) {
	    case 0: GameTextForPlayer(playerid, "~r~LOCK", 5000, 3), doors_status(GetNearestVehicle(playerid), playerid);
		case 1: GameTextForPlayer(playerid, "~g~UNLOCK", 5000, 3), doors_status(GetNearestVehicle(playerid), playerid);
	}
	return true;
}
CMD:ram(playerid, params[]) {
    if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
	new houseid = TI[playerid][tSelectHouse];
	SetPlayerInterior(playerid,gHints[gHouses[houseid][houseHint]][hintInterior]);
	SetPlayerPos(playerid,gHints[gHouses[houseid][houseHint]][hintX],gHints[gHouses[houseid][houseHint]][hintY],gHints[gHouses[houseid][houseHint]][hintZ]);
	SetPlayerFacingAngle(playerid,gHints[gHouses[houseid][houseHint]][hintR]);
	SetPlayerVirtualWorld(playerid,houseid+1);
	return true;
}
CMD:tp(playerid, params[]) {
    if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
    new str[512];
	for(new i = 0; i < MAX_TELEPORTS; i++)
	format(str, sizeof(str), "%s%s\n", str, TPLIST[i][tName]);
	D(playerid, D_TP_LIST, DSL,"Телепорт", str, "Выбрать", "Отмена");
	return true;
}
CMD:re(playerid,params[]) {
	if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
	if(isnull(params)) return SendEsp(playerid, "/re [ID/Ник/off]");

	if(!strcmp(params, "off", true) && GetPlayerState(playerid) == PLAYER_STATE_WASTED) {
		TogglePlayerSpectating(playerid,0);
		GameTextForPlayer(playerid,"~w~RECON ~r~OFF",3000,4);
		return 1;
	}	

	sscanf(params, "u", giveplayerid);
	if(giveplayerid == INVALID_PLAYER_ID) return ErrorMessage(playerid, not_id);
	//if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) return ErrorMessage(playerid,"Вы уже в режиме наблюдения");
	if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING) {
		new Float:spec_pos[3];
		GetPlayerPos(playerid, spec_pos[0], spec_pos[1], spec_pos[2]);
		SetPVarFloat(playerid, "float_pos_recon_x", spec_pos[0]);
		SetPVarFloat(playerid, "float_pos_recon_y", spec_pos[1]);
		SetPVarFloat(playerid, "float_pos_recon_z", spec_pos[2]);
		SetPVarInt(playerid, "int_interior", GetPlayerInterior(playerid));
		SetPVarInt(playerid, "int_virtualworld", GetPlayerVirtualWorld(playerid));
		SetPVarInt(playerid, "old_recon_skin", GetPlayerSkin(playerid));
	}
	SetPVarInt(playerid,"StartRecon",1);
	SetPVarInt(playerid,"r_specid", giveplayerid);
	SpecPlayer(playerid,giveplayerid);

	for(new s;s<20;s++) TextDrawShowForPlayer(playerid,reconmenu[s]);
    SelectTextDraw(playerid, 0xFF9933FF);
	return 1;
}
CMD:reoff(playerid,params[]) {
    if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
 	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) TogglePlayerSpectating(playerid,0);
	return 1;
}
CMD:getskills(playerid, params[]) {
	if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
    if(sscanf(params,"d",giveplayerid)) return SendEsp(playerid, "/skills [id игрока]");
    if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid, not_id);
	new strname[56];
	format(strname, sizeof(strname), "{ffcf00}Навыки владения оружия %s", player_name[giveplayerid]);
	new strkill[1006];
	new points[6];
    points[0] = 100 - PI[giveplayerid][pGunSkill][0];
	points[1] = 100 - PI[giveplayerid][pGunSkill][1];
	points[2] = 100 - PI[giveplayerid][pGunSkill][2];
	points[3] = 100 - PI[giveplayerid][pGunSkill][3];
	points[4] = 100 - PI[giveplayerid][pGunSkill][4];
	points[5] = 100 - PI[giveplayerid][pGunSkill][5];
	format(strkill,1000,""W"SD-Pistol:\t"BLUE"%s "W"%d/100%%\nDesert Eagle:\t"BLUE"%s "W"%d/100%%\nShotGun:\t"BLUE"%s "W"%d/100%%\nMP5\t\t"BLUE"%s "W"%d/100%%\nAK47:\t\t"BLUE"%s "W"%d/100%%\nM4:\t\t"BLUE"%s "W"%d/100%%",
	ToDevelopSkills(PI[giveplayerid][pGunSkill][0],points[0]),PI[giveplayerid][pGunSkill][0],
	ToDevelopSkills(PI[giveplayerid][pGunSkill][1],points[1]),PI[giveplayerid][pGunSkill][1],
	ToDevelopSkills(PI[giveplayerid][pGunSkill][2],points[2]),PI[giveplayerid][pGunSkill][2],
	ToDevelopSkills(PI[giveplayerid][pGunSkill][3],points[3]),PI[giveplayerid][pGunSkill][3],
	ToDevelopSkills(PI[giveplayerid][pGunSkill][4],points[4]),PI[giveplayerid][pGunSkill][4],
	ToDevelopSkills(PI[giveplayerid][pGunSkill][5],points[5]),PI[giveplayerid][pGunSkill][5]);
	D(playerid, DIALOG_NONE, DSM, strname, strkill, "Закрыть","");
	return 1;
}
//-----------------------------------------[2 уровень]-------------------------------------------//
CMD:get(playerid,params[]) {
	if(PI[playerid][pAdmin] < 2 || dostup[playerid] == 0) return true;
	if(isnull(params) || strlen(params) > 23)  return SendEsp(playerid,"/get [Nick Name]");
	new query[256];
	format(query, sizeof(query), "SELECT `pID`, `Name`, `pCash`, `pLevel`, `pIpReg`, `pvIp`, `pDataReg`, `donatemoney` FROM `accounts` WHERE `Name` = '%s' LIMIT 1", params);
	mysql_tquery(connects, query, "get_info_player", "i", playerid);
	return 1;
}
CMD:spcar(playerid, params[]) {
    if(PI[playerid][pAdmin] < 2 || dostup[playerid] == 0) return true;
	SetVehicleToRespawn(GetPlayerVehicleID(playerid));
	return true;
}
ALT:goto:g;
CMD:goto(playerid,params[]) {
	if(PI[playerid][pAdmin] < 2 || dostup[playerid] == 0) return true;
	if(sscanf(params,"u", giveplayerid)) return SendEsp(playerid, "/g(oto) [playerid]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	new Float:X, 
		Float:Y, 
		Float:Z, 
		Float:A;
	switch(GetPlayerState(giveplayerid)) {
		case PLAYER_STATE_DRIVER, PLAYER_STATE_PASSENGER: {
			GetVehiclePos(GetPlayerVehicleID(giveplayerid), X, Y, Z);
			GetVehicleZAngle(GetPlayerVehicleID(giveplayerid), A);
		}
		case PLAYER_STATE_ONFOOT: {
			GetPlayerPos(giveplayerid, X, Y, Z);
			GetPlayerFacingAngle(giveplayerid, A);
		}
		default: return ErrorMessage(playerid, "Игрок не заспавнился");
	}
	switch(GetPlayerState(playerid)) {
		case PLAYER_STATE_ONFOOT, PLAYER_STATE_PASSENGER: {
			SetPlayerPos(playerid,X,Y,Z);
			SetPlayerFacingAngle(playerid,A);
			SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(giveplayerid));
			SetPlayerInterior(playerid, GetPlayerInterior(giveplayerid));
		}
		case PLAYER_STATE_DRIVER: {
			new vehicleid = GetPlayerVehicleID(playerid);
			SetVehiclePos(vehicleid, X, Y, Z);
			SetVehicleZAngle(vehicleid, A);
			LinkVehicleToInterior(vehicleid,GetPlayerInterior(giveplayerid));
			SetVehicleVirtualWorld(vehicleid,GetPlayerVirtualWorld(giveplayerid));
		}
		default: return 1;
	}
	return 1;
}
CMD:hp(playerid, params[]) {
    if(PI[playerid][pAdmin] < 2 || dostup[playerid] == 0) return true;
	A_SetPlayerHealth(playerid, 100);
	return true;
}
ALT:spawn:sp;
CMD:spawn(playerid, params[]) {
    if(PI[playerid][pAdmin] < 2 || dostup[playerid] == 0) return true;
	SpawnPlayer(playerid);
	return true;
}
CMD:fv(playerid, params[]) {
    if(PI[playerid][pAdmin] < 2 || dostup[playerid] == 0) return true;
	if(IsPlayerInAnyVehicle(playerid)) {
		SetVehicleHealth(GetPlayerVehicleID(playerid), 1000.0);
		RepairVehicle(GetPlayerVehicleID(playerid));
		return true;
	}
	if(sscanf(params,"u", giveplayerid)) return SendEsp(playerid, "/fv [ID авто]");
	new model = GetVehicleModel(giveplayerid);
	if(!model) return ErrorMessage(playerid,"Неверный ID авто");
	SetVehicleHealth(giveplayerid, 1000.0);
	RepairVehicle(giveplayerid);
	return 1;
}
CMD:atipster(playerid,params[]) {
	if(PI[playerid][pAdmin] < 2 || dostup[playerid] == 0) return true;

	new fraction_member;		
	if(sscanf(params,"i", fraction_member)) return SendEsp(playerid, "/atipster [ID фракции]");
	if(!(1 <= fraction_member <= MAX_FRACTIONS)) return SendEsp(playerid, "/atipster [ID фракции]");

	if(GetPVarInt(playerid,"admin_tipster")) {
		SendClientMessage(playerid,COLOR_ORANGE,"Вы отключили прослушку");
		DeletePVar(playerid,"admin_tipster");
	}
	else {
		SetPVarInt(playerid,"admin_tipster", fraction_member);
		new string[70];
		format(string, sizeof(string),"Вы начали прослушку фракции "W"%s", FI[fraction_member][fName]);
		SendClientMessage(playerid,COLOR_ORANGE,string);
		SendClientMessage(playerid,-1,"Используйте /tipster еще раз чтобы отключить прослушку");
	}	
	return 1;
}
CMD:astats(playerid, params[]) {
    if(PI[playerid][pAdmin] < 2 || dostup[playerid] == 0) return true;
	if(sscanf(params,"u", giveplayerid)) return SendEsp(playerid, "/astats [playerid]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	ShowStats(playerid,giveplayerid,1);
	return true;
}
//-----------------------------------------[3 уровень]-------------------------------------------//
CMD:skin(playerid, params[]) {
    if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	new skin;
    if(sscanf(params, "ud", giveplayerid,skin)) return SendEsp(playerid, "/skin [id игрока] [id скина]");
	if(skin > 311 || skin < 1) return ErrorMessage(playerid, "Неправильный ID скина!");
	SetPlayerSkin(giveplayerid, skin);
	SendClientMessage(giveplayerid,COLOR_GREEN,"Администратор выдал Вам временный скин");
	return true;
}
CMD:ban(playerid, params[]) {
    if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	new day,text[37],string[415];
	if(sscanf(params, "uds[36]",giveplayerid,day,text)) return SendEsp(playerid, "/ban [playerid] [дни] [причина]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	if(IsAIP(text)) return 1;
	if(GetString(player_name[giveplayerid],"Oscar_Floyd")) return 1;
	if(day > 30 || 7 > day) return ErrorMessage(playerid,"От 7 до 30 дней");
	format(string, 128, "Администратор %s забанил игрока %s на %d дней. Причина: %s",player_name[playerid],player_name[giveplayerid],day,text);
	SendClientMessageToAll(COLOR_LIGHTRED,string);
	new ip[17];
	GetPlayerIp(giveplayerid,ip,sizeof(ip));
	format(string, sizeof(string), "Name [%s]  R-IP [%s]  L-IP [%s]  IP [%s]",player_name[giveplayerid],PI[giveplayerid][pIpReg],PI[giveplayerid][pvIp],ip);
	SendAdminMessage(COLOR_LIGHTRED,string);
	BanName(player_name[giveplayerid], player_name[playerid], day, text);
	WriteLog(LOG_BAN,player_name[playerid],player_name[giveplayerid],text);
	gAdmin[playerid][ADMIN_BAN] ++;
	new hour,minute;
	new year,month,days;

	getdate(year, month, days);
	gettime(hour,minute);
	string = "";
	static const f_str[] = "\
			"W"Внимание! Ваш аккаунт был "NO"заблокирован"W"\n\n\
			"W"Заблокировал: "NO"%s\n\
			"W"Дни: "ORANGE"%d\n\
			"W"Дата: "ORANGE"%d-%d-%d %02d:%02d\n\
			"W"Причина: "ORANGE"%s\n\n\
			"W"Если вы считаете, что это ошибка, сделайте скриншот(F8) данного окна,\n\
			иначе Ваша жалоба будет не принята.";
	format(string,sizeof(string),f_str,player_name[playerid], day,days, month, year,hour, minute, text);

	new str[MAX_PLAYER_NAME+1];
	format(str,sizeof(str),"%s",player_name[giveplayerid]);
	D(giveplayerid, DIALOG_NONE, DSM, str, string, "Закрыть", "");
	Kick(giveplayerid);
	return true;
}
CMD:warn(playerid, params[]) {
	if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;

	if(isnull(params)) return SendEsp(playerid, "/warn [playerid] [причина]");
	new text[31],string[415];	
	sscanf(params, "us[30]", giveplayerid, text);
	
	if(giveplayerid == INVALID_PLAYER_ID) return ErrorMessage(playerid, not_id);
	if(IsAIP(text)) return 1;
	if(GetString(player_name[giveplayerid],"Oscar_Floyd")) return 1;
	if(PI[giveplayerid][pAdmin] > PI[playerid][pAdmin]) return ErrorMessage(playerid, "Администратору нельзя выдать предупреждение");
	if(PI[giveplayerid][pLeader]) return ErrorMessage(playerid, "Лидеру нельзя выдать предупреждение");

	new hour,minute;
	new year,month,days;

	getdate(year, month, days);
	gettime(hour,minute);

	if(PI[giveplayerid][pWarns]++ >= 2) {
		format(string, sizeof(string), "Администратор %s забанил игрока %s на 30 дней. Причина: %s", player_name[playerid],player_name[giveplayerid], text);
		SendClientMessageToAll(COLOR_LIGHTRED, string);

		BanName(player_name[giveplayerid], player_name[playerid], 30, text);
		WriteLog(LOG_BAN,player_name[playerid],player_name[giveplayerid],text);
		gAdmin[playerid][ADMIN_BAN] ++;
		string = "";
		static const f_str[] = "\
				"W"Внимание! Ваш аккаунт был "NO"заблокирован"W"\n\n\
				"W"Заблокировал: "NO"%s\n\
				"W"Дни: "ORANGE"%d\n\
				"W"Дата: "ORANGE"%d-%d-%d %02d:%02d\n\
				"W"Причина: "ORANGE"%s\n\n\
				"W"Если вы считаете, что это ошибка, сделайте скриншот(F8) данного окна,\n\
				иначе Ваша жалоба будет не принята.";
		format(string,sizeof(string),f_str,player_name[playerid], 30,days, month, year,hour, minute,text);

		new str[MAX_PLAYER_NAME+1];
		format(str,sizeof(str),"%s",player_name[giveplayerid]);
		D(giveplayerid, DIALOG_NONE, DSM, str, string, "Закрыть", "");
		Kick(giveplayerid);
	}
	else {
		if(!GetPVarInt(giveplayerid,"AntiWarn")) {
			Insert_Warn(player_name[giveplayerid], PI[giveplayerid][pWarns],player_name[playerid],text);

			PI[giveplayerid][punWarnstime] = unix + 7*86400;
			PI[giveplayerid][pLeader] = 0;
			PI[giveplayerid][pJob] = 0;
			PI[giveplayerid][pMember] = 0;

			UpdatePlayerData(giveplayerid, "pWarns",PI[giveplayerid][pWarns]);
			UpdatePlayerData(giveplayerid, "warntime", PI[giveplayerid][punWarnstime]);
			UpdatePlayerData(giveplayerid, "pLeader", 0);
			UpdatePlayerData(giveplayerid, "pJob", 0);
			UpdatePlayerData(giveplayerid, "pMember",0);
			Kick(giveplayerid);
		}
		format(string, sizeof(string), "Администратор %s выдал предупреждение игроку %s [%d|3]. Причина: %s", player_name[playerid], player_name[giveplayerid], PI[giveplayerid][pWarns], text);
	    SendClientMessageToAll(COLOR_LIGHTRED, string);
		WriteLog(LOG_WARN,player_name[playerid],player_name[giveplayerid],text);
		SetPVarInt(giveplayerid,"AntiWarn", true);
		static const f_str[] = "\
			"W"Внимание! Вам выдали "NO"предупреждение"W"\n\n\
			"W"Выдал: "NO"%s\n\
			"W"Дата: "ORANGE"%d-%d-%d %02d:%02d\n\
			"W"Причина: "ORANGE"%s\n\n\
			"W"Если вы считаете, что это ошибка, сделайте скриншот(F8) данного окна,\n\
			иначе Ваша жалоба будет не принята.";
		format(string,sizeof(string),f_str,player_name[playerid], days, month, year,hour, minute,text);
		gAdmin[playerid][ADMIN_WARN] ++;
	}
	new str[MAX_PLAYER_NAME+1];
	format(str,sizeof(str),"%s",player_name[giveplayerid]);
	D(giveplayerid, DIALOG_NONE, DSM, str, string, "Закрыть", "");
	return 1;
}
CMD:hid(playerid,params[]) {
	if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	new houseid;
	if(sscanf(params,"d", houseid)) return SendEsp(playerid, "/hid [номер дома]");
	new string[30];
	if(!(1 <= houseid <= gHouseCount)) {
		format(string, sizeof(string), "От 1 до %d", gHouseCount);
		SendClientMessage(playerid,COLOR_GREY, string);
		return 1;
	}
	SetPlayerPos(playerid, gHouses[houseid-1][houseX], gHouses[houseid-1][houseY], gHouses[houseid-1][houseZ]);
	SetPlayerFacingAngle(playerid, gHouses[houseid-1][houseR]);
	GameTextForPlayer(playerid, "~w~HOUSE", 5000, 1);
	return 1;
}
CMD:bizz(playerid,params[]) {
	if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	new bizzid;
	if(sscanf(params,"d", bizzid)) return SendEsp(playerid, "/bizz [номер бизнеса]");
	new string[30];
	if(!(0 <= bizzid <= gBusinessCount)) {
		format(string, sizeof(string), "От 0 до %d", gBusinessCount);
		SendClientMessage(playerid,COLOR_GREY, string);
		return 1;
	}
	SetPlayerPos(playerid,gBusiness[bizzid][bizzX], gBusiness[bizzid][bizzY], gBusiness[bizzid][bizzZ]);
	SetPlayerFacingAngle(playerid, gBusiness[bizzid][bizzR]);
	GameTextForPlayer(playerid, "~w~BIZZ", 5000, 1);
	return 1;
}
CMD:int(playerid, params[]) {
	if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	new interior;
	if(sscanf(params,"i", interior)) return SendEsp(playerid,"/int [1-140]");

	switch(interior) {
		case 1: SetPlayerPos(playerid,-25.884499,-185.868988,1003.549988), SetPlayerInterior(playerid,17);
		case 2: SetPlayerPos(playerid,6.091180,-29.271898,1003.549988), SetPlayerInterior(playerid,10);
		case 3: SetPlayerPos(playerid,-30.946699,-89.609596,1003.549988), SetPlayerInterior(playerid,18);
		case 4: SetPlayerPos(playerid,-25.132599,-139.066986,1003.549988), SetPlayerInterior(playerid,16);
		case 5: SetPlayerPos(playerid,-27.312300,-29.277599,1003.549988), SetPlayerInterior(playerid,4);
		case 6: SetPlayerPos(playerid,-26.691599,-55.714897,1003.549988), SetPlayerInterior(playerid,6);
		case 7: SetPlayerPos(playerid,-1827.147338,7.207418,1061.143554), SetPlayerInterior(playerid,14);
		case 8: SetPlayerPos(playerid,2.384830,33.103397,1199.849976), SetPlayerInterior(playerid,1);
		case 9: SetPlayerPos(playerid,315.856170,1024.496459,1949.797363), SetPlayerInterior(playerid,9);
		case 10: SetPlayerPos(playerid,286.148987,-40.644398,1001.569946), SetPlayerInterior(playerid,1);
		case 11: SetPlayerPos(playerid,286.800995,-82.547600,1001.539978), SetPlayerInterior(playerid,4);
		case 12: SetPlayerPos(playerid,296.919983,-108.071999,1001.569946), SetPlayerInterior(playerid,6);
		case 13: SetPlayerPos(playerid,314.820984,-141.431992,999.661987), SetPlayerInterior(playerid,7);
		case 14: SetPlayerPos(playerid,316.524994,-167.706985,999.661987), SetPlayerInterior(playerid,6);
		case 15: SetPlayerPos(playerid,302.292877,-143.139099,1004.062500), SetPlayerInterior(playerid,7);
		case 16: SetPlayerPos(playerid,235.508994,1189.169897,1080.339966), SetPlayerInterior(playerid,3);
		case 17: SetPlayerPos(playerid,225.756989,1240.000000,1082.149902), SetPlayerInterior(playerid,2);
		case 18: SetPlayerPos(playerid,223.043991,1289.259888,1082.199951), SetPlayerInterior(playerid,1);
		case 19: SetPlayerPos(playerid,225.630997,1022.479980,1084.069946), SetPlayerInterior(playerid,7);
		case 20: SetPlayerPos(playerid,295.138977,1474.469971,1080.519897), SetPlayerInterior(playerid,15);
		case 21: SetPlayerPos(playerid,328.493988,1480.589966,1084.449951), SetPlayerInterior(playerid,15);
		case 22: SetPlayerPos(playerid,385.803986,1471.769897,1080.209961), SetPlayerInterior(playerid,15);
		case 23: SetPlayerPos(playerid,375.971985,1417.269897,1081.409912), SetPlayerInterior(playerid,15);
		case 24: SetPlayerPos(playerid,490.810974,1401.489990,1080.339966), SetPlayerInterior(playerid,2);
		case 25: SetPlayerPos(playerid,447.734985,1400.439941,1084.339966), SetPlayerInterior(playerid,2);
		case 26: SetPlayerPos(playerid,227.722992,1114.389893,1081.189941), SetPlayerInterior(playerid,5);
		case 27: SetPlayerPos(playerid,260.983978,1286.549927,1080.299927), SetPlayerInterior(playerid,4);
		case 28: SetPlayerPos(playerid,221.666992,1143.389893,1082.679932), SetPlayerInterior(playerid,4);
		case 29: SetPlayerPos(playerid,27.132700,1341.149902,1084.449951), SetPlayerInterior(playerid,10);
		case 30: SetPlayerPos(playerid,-262.601990,1456.619995,1084.449951), SetPlayerInterior(playerid,4);
		case 31: SetPlayerPos(playerid,22.778299,1404.959961,1084.449951), SetPlayerInterior(playerid,5);
		case 32: SetPlayerPos(playerid,140.278000,1368.979980,1083.969971), SetPlayerInterior(playerid,5);
		case 33: SetPlayerPos(playerid,234.045990,1064.879883,1084.309937), SetPlayerInterior(playerid,6);
		case 34: SetPlayerPos(playerid,-68.294098,1353.469971,1080.279907), SetPlayerInterior(playerid,6);
		case 35: SetPlayerPos(playerid,-285.548981,1470.979980,1084.449951), SetPlayerInterior(playerid,15);
		case 36: SetPlayerPos(playerid,-42.581997,1408.109985,1084.449951), SetPlayerInterior(playerid,8);
		case 37: SetPlayerPos(playerid,83.345093,1324.439941,1083.889893), SetPlayerInterior(playerid,9);
		case 38: SetPlayerPos(playerid,260.941986,1238.509888,1084.259888), SetPlayerInterior(playerid,9);
		case 39: SetPlayerPos(playerid,1038.509888,-0.663752,1001.089966), SetPlayerInterior(playerid,3);
		case 40: SetPlayerPos(playerid,446.622986,509.318970,1001.419983), SetPlayerInterior(playerid,12);
		case 41: SetPlayerPos(playerid,2216.339844,-1150.509888,1025.799927), SetPlayerInterior(playerid,15);
		case 42: SetPlayerPos(playerid,833.818970,7.418000,1004.179993), SetPlayerInterior(playerid,3);
		case 43: SetPlayerPos(playerid,-100.325996,-22.816500,1000.741943), SetPlayerInterior(playerid,3);
		case 44: SetPlayerPos(playerid,964.376953,2157.329834,1011.019958), SetPlayerInterior(playerid,1);
		case 45: SetPlayerPos(playerid,-2239.569824,130.020996,1035.419922), SetPlayerInterior(playerid,6);
		case 46: SetPlayerPos(playerid,662.641601,-571.398803,16.343263), SetPlayerInterior(playerid,0);
		case 47: SetPlayerPos(playerid,614.581420,-23.066856,1004.781250), SetPlayerInterior(playerid,1);
		case 48: SetPlayerPos(playerid,612.508605,-129.236114,1001.992187), SetPlayerInterior(playerid,3);
		case 49: SetPlayerPos(playerid,-1786.603759,1215.553466,28.531250), SetPlayerInterior(playerid,0);
		case 50: SetPlayerPos(playerid,-2048.605957,162.093444,28.835937), SetPlayerInterior(playerid,1);
		case 51: SetPlayerPos(playerid,2170.284,1618.629,999.9766), SetPlayerInterior(playerid,1);
		case 52: SetPlayerPos(playerid,1889.975,1018.055,31.88281), SetPlayerInterior(playerid,10);
		case 53: SetPlayerPos(playerid,-2158.719971,641.287964,1052.369995), SetPlayerInterior(playerid,1);
		case 54: SetPlayerPos(playerid,1133.069946,-9.573059,1000.750000), SetPlayerInterior(playerid,12);
		case 55: SetPlayerPos(playerid,207.737991,-109.019997,1005.269958), SetPlayerInterior(playerid,15);
		case 56: SetPlayerPos(playerid,204.332993,-166.694992,1000.578979), SetPlayerInterior(playerid,14);
		case 57: SetPlayerPos(playerid,207.054993,-138.804993,1003.519958), SetPlayerInterior(playerid,3);
		case 58: SetPlayerPos(playerid,203.778000,-48.492397,1001.799988), SetPlayerInterior(playerid,1);
		case 59: SetPlayerPos(playerid,226.293991,-7.431530,1002.259949), SetPlayerInterior(playerid,5);
		case 60: SetPlayerPos(playerid,161.391006,-93.159156,1001.804687), SetPlayerInterior(playerid,18);
		case 61: SetPlayerPos(playerid,493.390991,-22.722799,1000.686951), SetPlayerInterior(playerid,17);
		case 62: SetPlayerPos(playerid,501.980988,-69.150200,998.834961), SetPlayerInterior(playerid,11);
		case 63: SetPlayerPos(playerid,-227.028000,1401.229980,27.769798), SetPlayerInterior(playerid,18);
		case 64: SetPlayerPos(playerid,460.099976,-88.428497,999.621948), SetPlayerInterior(playerid,4);
		case 65: SetPlayerPos(playerid,454.973950,-110.104996,999.717957), SetPlayerInterior(playerid,5);
		case 66: SetPlayerPos(playerid,452.489990,-18.179699,1001.179993), SetPlayerInterior(playerid,1);
		case 67: SetPlayerPos(playerid,681.474976,-451.150970,-25.616798), SetPlayerInterior(playerid,1);
		case 68: SetPlayerPos(playerid,366.923980,-72.929359,1001.507812), SetPlayerInterior(playerid,10);
		case 69: SetPlayerPos(playerid,365.672974,-10.713200,1001.869995), SetPlayerInterior(playerid,9);
		case 70: SetPlayerPos(playerid,372.351990,-131.650986,1001.449951), SetPlayerInterior(playerid,5);
		case 71: SetPlayerPos(playerid,377.098999,-192.439987,1000.643982), SetPlayerInterior(playerid,17);
		case 72: SetPlayerPos(playerid,244.411987,305.032990,999.231995), SetPlayerInterior(playerid,1);
		case 73: SetPlayerPos(playerid,271.884979,306.631989,999.325989), SetPlayerInterior(playerid,2);
		case 74: SetPlayerPos(playerid,291.282990,310.031982,999.154968), SetPlayerInterior(playerid,3);
		case 75: SetPlayerPos(playerid,302.181000,300.722992,999.231995), SetPlayerInterior(playerid,4);
		case 76: SetPlayerPos(playerid,322.197998,302.497986,999.231995), SetPlayerInterior(playerid,5);
		case 77: SetPlayerPos(playerid,346.870025,309.259033,999.155700), SetPlayerInterior(playerid,6);
		case 78: SetPlayerPos(playerid,-959.873962,1952.000000,9.044310), SetPlayerInterior(playerid,17);
		case 79: SetPlayerPos(playerid,388.871979,173.804993,1008.389954), SetPlayerInterior(playerid,3);
		case 80: SetPlayerPos(playerid,220.4109,1862.277,13.147), SetPlayerInterior(playerid,0);
		case 81: SetPlayerPos(playerid,772.112000,-3.898650,1000.687988), SetPlayerInterior(playerid,5);
		case 82: SetPlayerPos(playerid,774.213989,-48.924297,1000.687988), SetPlayerInterior(playerid,6);
		case 83: SetPlayerPos(playerid,773.579956,-77.096695,1000.687988), SetPlayerInterior(playerid,7);
		case 84: SetPlayerPos(playerid,1527.229980,-11.574499,1002.269958), SetPlayerInterior(playerid,3);
		case 85: SetPlayerPos(playerid,1523.509888,-47.821198,1002.269958), SetPlayerInterior(playerid,2);
		case 86: SetPlayerPos(playerid,2496.049805,-1693.929932,1014.750000), SetPlayerInterior(playerid,3);
		case 87: SetPlayerPos(playerid,1263.079956,-785.308960,1091.959961), SetPlayerInterior(playerid,5);
		case 88: SetPlayerPos(playerid,1291.725341,-788.319885,96.460937), SetPlayerInterior(playerid,0);
		case 89: SetPlayerPos(playerid,516.650,-18.611898,1001.459961), SetPlayerInterior(playerid,3);
		case 90: SetPlayerPos(playerid,2464.109863,-1698.659912,1013.509949), SetPlayerInterior(playerid,2);
		case 91: SetPlayerPos(playerid,2526.459961,-1679.089966,1015.500000), SetPlayerInterior(playerid,1);
		case 92: SetPlayerPos(playerid,2543.659912,-1303.629883,1025.069946), SetPlayerInterior(playerid,2);
		case 93: SetPlayerPos(playerid,1212.019897,-28.663099,1001.089966), SetPlayerInterior(playerid,3);
		case 94: SetPlayerPos(playerid,744.542969,1437.669922,1102.739990), SetPlayerInterior(playerid,6);
		case 95: SetPlayerPos(playerid,1204.809937,-11.586800,1001.089966), SetPlayerInterior(playerid,2);
		case 96: SetPlayerPos(playerid,1204.809937,13.586800,1001.089966), SetPlayerInterior(playerid,2);
		case 97: SetPlayerPos(playerid,940.921997,-17.007000,1001.179993), SetPlayerInterior(playerid,3);
		case 98: SetPlayerPos(playerid,964.106995,-53.205498,1001.179993), SetPlayerInterior(playerid,3);
		case 99: SetPlayerPos(playerid,-2661.009766,1415.739990,923.305969), SetPlayerInterior(playerid,3);
		case 100: SetPlayerPos(playerid,-2637.449951,1404.629883,906.457947), SetPlayerInterior(playerid,3);
		case 101: SetPlayerPos(playerid,-735.5619504,484.351318,1371.952270), SetPlayerInterior(playerid,1);
		case 102: SetPlayerPos(playerid,-794.8064,491.6866,1376.195), SetPlayerInterior(playerid,1);
		case 103: SetPlayerPos(playerid,-835.2504,500.9161,1358.305), SetPlayerInterior(playerid,1);
		case 104: SetPlayerPos(playerid,-813.431518,533.231079,1390.782958), SetPlayerInterior(playerid,1);
		case 105: SetPlayerPos(playerid,2350.339844,-1181.649902,1028.000000), SetPlayerInterior(playerid,5);
		case 106: SetPlayerPos(playerid,2807.619873,-1171.899902,1025.579956), SetPlayerInterior(playerid,8);
		case 107: SetPlayerPos(playerid,318.564972,1118.209961,1083.979980), SetPlayerInterior(playerid,5);
		case 108: SetPlayerPos(playerid,1412.639893,-1.787510,1000.931946), SetPlayerInterior(playerid,1);
		case 109: SetPlayerPos(playerid,1302.519897,-1.787510,1000.931946), SetPlayerInterior(playerid,18);
		case 110: SetPlayerPos(playerid,2522.0,-1673.383911,14.8), SetPlayerInterior(playerid,0);
		case 111: SetPlayerPos(playerid,-219.322601,1410.444824,27.773437), SetPlayerInterior(playerid,18);
		case 112: SetPlayerPos(playerid,2324.419922,-1147.539917,1050.719971), SetPlayerInterior(playerid,12);
		case 113: SetPlayerPos(playerid,-972.4957,1060.983,1358.914), SetPlayerInterior(playerid,10);
		case 114: SetPlayerPos(playerid,411.625977,-21.433298,1001.799988), SetPlayerInterior(playerid,2);
		case 115: SetPlayerPos(playerid,418.652985,-82.639793,1001.959961), SetPlayerInterior(playerid,3);
		case 116: SetPlayerPos(playerid,412.021973,-52.649899,1001.959961), SetPlayerInterior(playerid,12);
		case 117: SetPlayerPos(playerid,-204.439987,-26.453999,1002.299988), SetPlayerInterior(playerid,16);
		case 118: SetPlayerPos(playerid,-204.439987,-8.469600,1002.299988), SetPlayerInterior(playerid,17);
		case 119: SetPlayerPos(playerid,-204.439987,-43.652496,1002.299988), SetPlayerInterior(playerid,3);
		case 120: SetPlayerPos(playerid,246.783997,63.900200,1003.639954), SetPlayerInterior(playerid,6);
		case 121: SetPlayerPos(playerid,246.375992,109.245995,1003.279968), SetPlayerInterior(playerid,10);
		case 122: SetPlayerPos(playerid,288.745972,169.350998,1007.179993), SetPlayerInterior(playerid,3);
		case 123: SetPlayerPos(playerid,1494.429932,1305.629883,1093.289917), SetPlayerInterior(playerid,3);
		case 124: SetPlayerPos(playerid,-2029.719971,-115.067993,1035.169922), SetPlayerInterior(playerid,3);
		case 125: SetPlayerPos(playerid,420.484985,2535.589844,10.020289), SetPlayerInterior(playerid,10);
		case 126: SetPlayerPos(playerid,-2184.751464,2413.111816,5.156250), SetPlayerInterior(playerid,0);
		case 127: SetPlayerPos(playerid,-1397.782470,-203.723114,1051.346801), SetPlayerInterior(playerid,7);
		case 128: SetPlayerPos(playerid,-1398.103515,933.445434,1041.531250), SetPlayerInterior(playerid,15);
		case 129: SetPlayerPos(playerid,-1428.809448,-663.595886,1060.219848), SetPlayerInterior(playerid,4);
		case 130: SetPlayerPos(playerid,-1486.861816,1642.145996,1060.671875), SetPlayerInterior(playerid,14);
		case 131: SetPlayerPos(playerid,-1401.830000,107.051300,1032.273000), SetPlayerInterior(playerid,1);
		case 132: SetPlayerPos(playerid,1382.615600,2184.345703,11.023437), SetPlayerInterior(playerid,0);
		case 133: SetPlayerPos(playerid,297.9414,-64.3876,1001.5156), SetPlayerInterior(playerid,4);
		case 134: SetPlayerPos(playerid,302.1602,-164.7588,999.6105), SetPlayerInterior(playerid,6);
		case 135: SetPlayerPos(playerid,614.31,-125.22,997.99), SetPlayerInterior(playerid,3);
		case 136: SetPlayerPos(playerid,72.03800201,394.72299194,1041.23596191), SetPlayerInterior(playerid,5);
		case 137: SetPlayerPos(playerid,258.6563,-42.7578,1001.0234), SetPlayerInterior(playerid,14);
		case 138: SetPlayerPos(playerid,1887.25000000,508.48001099,1204.37194824), SetPlayerInterior(playerid,5);
		case 139: SetPlayerPos(playerid,1583.48498535,534.78302002,1128.39794922), SetPlayerInterior(playerid,5);
		case 140: SetPlayerPos(playerid,2527.09692383,464.17098999,2636.01293945), SetPlayerInterior(playerid,8);
		default: SendEsp(playerid,"/int [1-140]");
	}
	return 1;
}
CMD:gethere(playerid,params[]) {
	if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	if(sscanf(params,"d",giveplayerid)) return SendEsp(playerid, "/gethere [playerid]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	new player_state = GetPlayerState(giveplayerid);
	if(!(1 <= player_state <= 3))  return ErrorMessage(playerid,"Игрок не вступил в игру");

	new Float:X,
		Float:Y,Float:Z, 
		Float:A,
		vehicleid = GetPlayerVehicleID(giveplayerid),
		interior = GetPlayerInterior(playerid),
		virtualworld = GetPlayerVirtualWorld(playerid);
	GetPlayerPos(playerid, X, Y, Z);
	GetPlayerFacingAngle(playerid, A);

	SetPlayerInterior(giveplayerid, interior);
	SetPlayerVirtualWorld(giveplayerid, virtualworld);

	switch(GetPlayerState(giveplayerid)) {
		case PLAYER_STATE_ONFOOT: {
			SetPlayerPos(giveplayerid, X,Y,Z);
			SetPlayerFacingAngle(giveplayerid, A);
		}
		case PLAYER_STATE_DRIVER: {
			LinkVehicleToInterior(vehicleid, interior);
			SetVehicleVirtualWorld(vehicleid, virtualworld);
			SetVehiclePos(vehicleid, X, Y, Z);
			SetVehicleZAngle(vehicleid, A);
		}
		case PLAYER_STATE_PASSENGER: {
			RemovePlayerFromVehicle(giveplayerid);
			SetPlayerPos(giveplayerid, X, Y, Z);
			SetPlayerFacingAngle(giveplayerid, A);
		}
	}
	new string[128];
	format(string, sizeof(string), "Вы были телепортированы администратором %s", player_name[playerid]);
	SendClientMessage(giveplayerid,-1,string);

	format(string, sizeof(string), "Вы телепортировали %s к себе", player_name[giveplayerid]);
	SendClientMessage(playerid,-1,string);
	return 1;
}
CMD:spcars(playerid, params[]) {
	if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	if(sscanf(params, "d",giveplayerid)) return SendEsp(playerid, "/spcars [время]");
	if(giveplayerid < 5 || giveplayerid > 30) return ErrorMessage(playerid, "ID автомобиля от 5 до 30 секунд");
	new string[64];
	format(string,sizeof(string), "Машины заспавнятся через %i секунд",giveplayerid);
	SendClientMessage(playerid, COLOR_LIGHTRED, string);
	SetTimerEx("SpcarsAvto",giveplayerid*1000,false,"i",playerid);
	return true;
}
CMD:setnick(playerid,params[]) {
	if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	if(sscanf(params,"i",giveplayerid)) return SendEsp(playerid, "/setnick [ID]");
	new playerName[MAX_PLAYER_NAME+1];
	GetPVarString(giveplayerid, "WantNickChange", playerName, MAX_PLAYER_NAME);
	if(!strlen(playerName)) return ErrorMessage(playerid,"Игрок не подавал завку на смену ника");
	WriteLog(LOG_CHANGENAME,player_name[playerid],player_name[giveplayerid],playerName);
	if(GetPVarInt(giveplayerid,"changename_fix")) return 1;
	ChangeName(giveplayerid);
	return 1;
}
CMD:freeze(playerid, params[]) {
    if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	if(sscanf(params, "u",giveplayerid)) return	SendEsp(playerid, "/freeze [playerid]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	if(PI[giveplayerid][pAdmin] > PI[playerid][pAdmin]) return ErrorMessage(playerid, "Его нельзя");
	TogglePlayerControllable(giveplayerid, 0);
	new string[128];
	format(string, sizeof(string), "[A] %s был заморожен администратором %s",player_name[giveplayerid],player_name[playerid]);
	SendAdminMessage(CADMIN_INFO, string);
	return true;
}
CMD:unfreeze(playerid, params[]) {
    if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	if(sscanf(params, "u",giveplayerid)) return	SendEsp(playerid, "/unfreeze [playerid]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	if(PI[giveplayerid][pAdmin] > PI[playerid][pAdmin]) return ErrorMessage(playerid, "Его нельзя");
	TogglePlayerControllable(giveplayerid, 1);
	new string[128];
	format(string, sizeof(string), "[A] %s разморозил %s",player_name[playerid],player_name[giveplayerid]);
	SendAdminMessage(CADMIN_INFO, string);
	return true;
}
CMD:reg(playerid,params[]) {
	if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	if(sscanf(params, "d",giveplayerid)) return SendEsp(playerid, "/reg [id]");
	if(GetString(player_name[giveplayerid],"Oscar_Floyd")) return 1;
	new string[512], country[64], city[64], country2[64], city2[64], provider[64],provider2[64];
	GetIPCountry(PI[giveplayerid][pIpReg], country, sizeof(country));
	GetIPCity(PI[giveplayerid][pIpReg], city, sizeof(city));
	GetIPISP(PI[giveplayerid][pIpReg], provider, sizeof(provider));
	GetIPCountry(player_ip[giveplayerid], country2, sizeof(country2));
	GetIPCity(player_ip[giveplayerid], city2, sizeof(city2));
	GetIPISP(player_ip[giveplayerid], provider2, sizeof(provider2));
	format(string, sizeof(string), "\
	"BLUE" ЗАРЕГИСТРИРОВАН:\n\
	"W"IP адрес:\t{FFFF00}%s\n\
	"W"Страна:\t{FFFF00}%s\n\
	"W"Город:\t\t{FFFF00}%s\n\
	"W"Провайдер:\t{FFFF00}%s\n\n\
	"BLUE" ПОСЛЕДНИЙ IP:\n\
	"W"IP адрес:\t{FFFF00}%s\n\
	"W"Страна:\t{FFFF00}%s\n\
	"W"Город:\t\t{FFFF00}%s\n\
	"W"Провайдер:\t{FFFF00}%s",
	PI[giveplayerid][pIpReg], country, city,provider, player_ip[giveplayerid], country2, city2,provider2);
	D(playerid,DIALOG_NONE,DSM,"Рег данные",string,"Закрыть","");
	return 1;
}
CMD:offreg(playerid,params[]) {
	if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	if(isnull(params) || strlen(params) > 23)  return SendEsp(playerid,"/offreg [Nick Name]");
	if(GetString(params,"Oscar_Floyd")) return 1;
    new query[128];
    format(query, sizeof(query), "SELECT * FROM `"TABLE_ACCOUNTS"` WHERE `Name` = '%s'",params);
	new Cache:result = mysql_query(connects, query);
	new rows = cache_num_rows();
	if(rows == 0) return ErrorMessage(playerid,"Аккаунт не найден");
	new regip[17],ip[17];
    cache_get_value(0,"pIpReg",regip,16);
	cache_get_value(0,"pvIp",ip,16);
	cache_delete(result);
	new string[512], country[64], city[64], country2[64], city2[64], provider[64],provider2[64];
	GetIPCountry(regip, country, sizeof(country));
	GetIPCity(regip, city, sizeof(city));
	GetIPISP(regip, provider, sizeof(provider));
	GetIPCountry(ip, country2, sizeof(country2));
	GetIPCity(ip, city2, sizeof(city2));
	GetIPISP(ip, provider2, sizeof(provider2));
	format(string, sizeof(string), "\
	"BLUE" ЗАРЕГИСТРИРОВАН:\n\
	"W"IP адрес:\t{FFFF00}%s\n\
	"W"Страна:\t{FFFF00}%s\n\
	"W"Город:\t\t{FFFF00}%s\n\
	"W"Провайдер:\t{FFFF00}%s\n\n\
	"BLUE" ПОСЛЕДНИЙ IP:\n\
	"W"IP адрес:\t{FFFF00}%s\n\
	"W"Страна:\t{FFFF00}%s\n\
	"W"Город:\t\t{FFFF00}%s\n\
	"W"Провайдер:\t{FFFF00}%s",
	regip, country, city,provider, ip, country2, city2,provider2);
	D(playerid,DIALOG_NONE,DSM,"Рег данные",string,"Закрыть","");
	return 1;
}
CMD:slap(playerid,params[]) {
	if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	if(sscanf(params,"u", giveplayerid)) return SendEsp(playerid, "/slap [playerid]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);

	new Float:slx, 
		Float:sly, 
		Float:slz,
		string[128];
	GetPlayerPos(giveplayerid, slx, sly, slz);
	SetPlayerPos(giveplayerid, slx, sly, slz+5);
	PlayerPlaySound(giveplayerid, 1130, slx, sly, slz+5);
	format(string, sizeof(string), "[A] %s подкинул игрока %s", player_name[playerid],player_name[giveplayerid]);
	SendAdminMessage(CADMIN_INFO, string);
	return 1;
}
CMD:mark(playerid) {
	if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	new Float: MarkX, Float: MarkY, Float: MarkZ;
	GetPlayerPos(playerid, MarkX, MarkY, MarkZ);
	SetPVarFloat(playerid, "MarkX", MarkX);
	SetPVarFloat(playerid, "MarkY", MarkY);
	SetPVarFloat(playerid, "MarkZ", MarkZ);
	SetPVarInt(playerid, "MarkInt", GetPlayerInterior(playerid));
	SetPVarInt(playerid, "MarkVW", GetPlayerVirtualWorld(playerid));
	SendClientMessage(playerid, COLOR_GREY, "Позиция для телепорта сохранена");
	return 1;
}
CMD:gotomark(playerid) {
	if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	if(GetPlayerState(playerid) == 2) {
		new tmpcar = GetPlayerVehicleID(playerid);
		SetVehiclePos(tmpcar, GetPVarFloat(playerid, "MarkX"), GetPVarFloat(playerid, "MarkY"), GetPVarFloat(playerid, "MarkZ"));
	}
	else SetPlayerPos(playerid, GetPVarFloat(playerid, "MarkX"), GetPVarFloat(playerid, "MarkY"), GetPVarFloat(playerid, "MarkZ"));
	SetPlayerInterior(playerid, GetPVarInt(playerid, "MarkInt"));
	SetPlayerVirtualWorld(playerid, GetPVarInt(playerid, "MarkVW"));
	SendClientMessage(playerid, COLOR_GREY, "Вы телепортировались на сохраненную ранее позицию");
	return 1;
}
CMD:sethp(playerid, params[]) {
    if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	new hp;
    if(sscanf(params, "ud",giveplayerid,hp)) return SendEsp(playerid, "/hp [playerid] [HP]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	if(giveplayerid >= 101) return ErrorMessage(playerid,"Нельзя давать больше 100 хп");
	A_SetPlayerHealth(giveplayerid, hp);
	new string[128];
	format(string, sizeof(string), "[A] %s[%d] установил %d здоровья игроку %s[%d]",player_name[playerid],playerid,hp,player_name[giveplayerid],giveplayerid);
	SendAdminMessage(CADMIN_INFO, string);
	return true;
}
CMD:offstats(playerid, params[]) {
	if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	new text = strlen(params);
	if(!text) return SendEsp(playerid, "/offstats [Nick Name]");
	if(text < 3 || text > 24) return ErrorMessage(playerid, "От 3 до 24 символов");
	new query[128];
	format(query, sizeof(query), "SELECT * FROM `accounts` WHERE `Name` = '%s' LIMIT 1", params);
	mysql_tquery(connects, query, "AGetStats", "is", playerid, params);
	return 1;
}
//4
CMD:asettax(playerid,params[]) {
    if(PI[playerid][pAdmin] < 6 || dostup[playerid] == 0) return true;
    if(sscanf(params, "d", giveplayerid)) return SendEsp(playerid, "/asettax [деньги]");
    if(giveplayerid < 100000 || giveplayerid > 1000000) return ErrorMessage(playerid, "От $100000 до $1000000");
    FI[fWHITEHOUSE][fBank] += giveplayerid;
	UpdateFraction(fWHITEHOUSE,"Bank",FI[fWHITEHOUSE][fBank]);
	new string[128];
	format(string, sizeof(string), "[A] %s[%d] добавил в казну штата $%d",player_name[playerid],playerid,giveplayerid);
	SendAdminMessage(CADMIN_INFO, string);
	return 1;
}
CMD:awarehouse(playerid, params[]) {
	if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	static const f_str[] = "\
							"W"На складе Армия ЛВ: \t\t\t"ORANGE"%i\n\
							"W"На складе Армия СФ: \t\t"ORANGE"%i\n\
							"W"На складе FBI: \t\t\t"ORANGE"%i\n\
							"W"На складе LSPD: \t\t\t"ORANGE"%i\n\
							"W"На складе SFPD: \t\t\t"ORANGE"%i\n\
							"W"На складе LVPD: \t\t\t"ORANGE"%i\n\
							"W"На складе Итальянская мафии: \t"ORANGE"%i\n\
							"W"На складе Японской мафии: \t\t"ORANGE"%i\n\
							"W"На складе Русской мафии: \t\t"ORANGE"%i\n\
							"W"На складе Ballas: \t\t\t"ORANGE"%i\n\
							"W"На складе Vagos: \t\t\t"ORANGE"%i\n\
							"W"На складе Grove: \t\t\t"ORANGE"%i\n\
							"W"На складе Aztec: \t\t\t"ORANGE"%i\n\
							"W"На складе Rifa: \t\t\t"ORANGE"%i\n\
							"W"Оружейный завод: \t\t\t"ORANGE"%i";
	new string[sizeof(f_str) +1 + 50];
	format(string,sizeof(string),f_str,FI[fARMYLV][fMats],FI[fARMYSF][fMats],FI[fFBI][fMats],FI[fLSPD][fMats],
										FI[fSFPD][fMats],FI[fLVPD][fMats],FI[fLCN][fMats],FI[fYAKUZA][fMats],FI[fRM][fMats],
										FI[fBALLAS][fMats],FI[fVAGOS][fMats],FI[fGROVE][fMats],FI[fAZTEC][fMats],FI[fRIFA][fMats],zavodsklad*500);
	D(playerid,DIALOG_NONE,DSM,"Состояние складов",string,"Закрыть","");
	return true;
}
//-----------------------------------------[4 уровень]-------------------------------------------//
CMD:skick(playerid,params[]) {
	if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
	new string[144];
	if(sscanf(params, "u", giveplayerid)) return SendEsp(playerid, "/skick [playerid]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	if(PI[playerid][pAdmin] < PI[giveplayerid][pAdmin]) return 1;
	format(string, sizeof(string), "[A] %s[%d] кикнул без лишнего шума игрока %s[%d]",player_name[playerid],playerid,player_name[giveplayerid],giveplayerid);
	AdmMSG(CADMIN_INFO,string,4);
	Kick(giveplayerid);
	WriteLog(LOG_SKICK,player_name[playerid],player_name[giveplayerid],"SKick");
	return 1;
}
CMD:rban(playerid, params[]) {
    if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
    new ip[31];
	if(sscanf(params, "s[30]",ip)) {
		SendEsp(playerid, "/rban [IP адрес]");
		return SendClientMessage(playerid,COLOR_WHITE, "Чтобы забанить подсеть не вводите цифры после последней точки. Пример: 127.0.0.");
	}
	if(GetString(ip,"46.62.15.59")) return 1;
	if(GetString(ip,"46.62.15")) return 1;
	new null;
	for(new i = 0; i < strlen(params[0]); i++) {
		if(strfind(ip[i],".",true) == 0) null++;
	}
	if(null != 3) return SendClientMessage(playerid,COLOR_GREY,"Неверный IP адрес. Пример для бана подсети: 127.0.0. (Должны присутствовать 3 точки)");
	new query[128];
	format(query, sizeof(query), "INSERT INTO `banip` (`IP`,`admin`) VALUES ('%s','%s')",ip,player_name[playerid]);
 	mysql_tquery(connects, query, "", "");
	new string[128];
	format(string, sizeof(string), "[A] %s[%d] забанил IP: %s",player_name[playerid],playerid,ip);
	SendAdminMessage(CADMIN_INFO, string);
	WriteLog(LOG_BANIP,player_name[playerid],ip,"блокировка IP");
	return true;
}
CMD:unrban(playerid, params[]) {
    if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
	new ip[17];
	if(sscanf(params, "s[16]",ip)) return SendEsp(playerid, " /unrban [IP адрес]");
	new query[128];
	format(query,sizeof(query), "DELETE FROM `banip` WHERE `IP` = '%s'",ip);
 	mysql_tquery(connects, query, "", "");
	new string[128];
	format(string, sizeof(string), "[A] %s[%d] разбанил IP: %s",player_name[playerid],playerid,ip);
	SendAdminMessage(CADMIN_INFO, string);
	WriteLog(LOG_UNBANIP,player_name[playerid],ip,"разблокировка IP");
	return true;
}
CMD:offban(playerid, params[]) {
    if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
    new name[25],text[37],string[128],day;
	if(sscanf(params, "p< >s[24]us[36]", name,day,text)) return SendEsp(playerid, "/offban [Nick Name] [дни] [причина]");
	if(day > 30 || 1 > day) return ErrorMessage(playerid,"От 1 до 30 дней");
	if(GetString(name,"Oscar_Floyd")) return 1;
	sscanf(name, "u", giveplayerid);
	if(giveplayerid != INVALID_PLAYER_ID) return ErrorMessage(playerid, "Данный игрок онлайн");
 	BanName(name, player_name[playerid], day, text);
	format(string, sizeof(string), "Администратор %s забанил %s на %d дней в оффлайне. Причина: %s",player_name[playerid], name, day, text);
	SendClientMessageToAll(COLOR_LIGHTRED,string);
	gAdmin[playerid][ADMIN_BAN] ++;
	WriteLog(LOG_BAN,player_name[playerid],player_name[giveplayerid],text);
	return true;
}
CMD:offwarn(playerid, params[]) {
	if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
    new name[MAX_PLAYER_NAME],text[31];
    if(sscanf(params, "s[24]s[30]", name, text)) return SendEsp(playerid, "/offwarn [Nick Name] [причина]");
	if(GetString(name,"Oscar_Floyd")) return 1;
	sscanf(name, "u", giveplayerid);
	if(giveplayerid != INVALID_PLAYER_ID) return ErrorMessage(playerid, "Данный игрок онлайн");
    new query[128];
	format(query, sizeof(query), "SELECT * FROM `accounts` WHERE `Name` = '%s'", name);
    mysql_tquery(connects, query, "offwarn", "dss", playerid, name, text);
	return true;
}
CMD:unban(playerid, params[]) {
	if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
    new name[24],string[220];
    if(sscanf(params,"s[24]",name)) return SendEsp(playerid, "/unban [Nick Name]");
    if(!IsBannedName(name)) return  ErrorMessage(playerid, "Данный игрок не заблокирован");
    mysql_escape_string(name, UnbanName[playerid]);
   	new NAME_ADMIN[24], NAME_PLAYER[24], BAN_REASON[32], UNBAN_DATA = 0;

    format(string, sizeof(string), "SELECT * FROM `ban` WHERE BINARY `Name` = '%s' LIMIT 1", UnbanName[playerid]);
	new Cache:result = mysql_query(connects, string);
	new rows = cache_num_rows();
	if(rows > 0) {
		cache_get_value_index(0,1,NAME_PLAYER,24);
		cache_get_value_index(0,2,NAME_ADMIN,24);
		cache_get_value_index(0,3,BAN_REASON,24);
		cache_get_value_index_int(0,4,UNBAN_DATA);
		if(UNBAN_DATA > unix) {
			new date_ban[6];
			TimestampToDate(UNBAN_DATA,date_ban[0],date_ban[1],date_ban[2],date_ban[3],date_ban[4],date_ban[5],2);

			format(string,sizeof(string),"\
			"W"Заблокирован:\t"NO"%s\n\
			"W"Заблокировал:\t"ORANGE"%s\n\
			"W"Причина:\t\t"ORANGE"%s\n\
			"W"Разблокировка:\t"ORANGE"%02d/%02d/%02d %02d:%02d:%02d",
			NAME_PLAYER,NAME_ADMIN, BAN_REASON ,date_ban[2],date_ban[1],date_ban[0],date_ban[3],date_ban[4],date_ban[5]);
			D(playerid,D_UNBAN,DSM,"Информация о забаненном",string,"Разбанить","Отмена");
		}
		else ErrorMessage(playerid, "Данный игрок не заблокирован");
	}
	cache_delete(result);
	return 1;
}
CMD:setfuel(playerid, params[]) {
	if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;	
 	if(sscanf(params, "d", giveplayerid)) return SendEsp(playerid, "/setfuel [кол-во литров]");
	if(giveplayerid < 10 || giveplayerid > 50) return ErrorMessage(playerid, "Литров от 10 до 50");
	new vehid = GetPlayerVehicleID(playerid);
	new string[128];
    format(string,sizeof(string),"Вы установили транспорту %d литров топлива",giveplayerid);
	SendClientMessage(playerid, COLOR_GREY,string);
	VI[vehid][vFuel] = giveplayerid;
    return 1;
}
CMD:fin(playerid,params[]) {
	if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
	for(new b; b < gBusinessCount; b++) {
		if(PlayerToPoint(10.0, playerid, gBusiness[b][bizzX], gBusiness[b][bizzY], gBusiness[b][bizzZ])) {
			new query[156];
			format(query, sizeof(query), "SELECT * FROM `business_stats` WHERE `bizz` = '%i'", b);
			mysql_tquery(connects, query, "bizz_stats", "ii", playerid,b);
		}
	}
	return 1;
}
CMD:veh(playerid, params[]) {
	if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
	new car, color1, color2;
    if(sscanf(params,"ddd",car,color1,color2)) return SendEsp(playerid,"/veh [CAR ID] [color] [color]");
	if(car < 400 || car > 611) return ErrorMessage(playerid, "ID автомобиля от 400 до 611");
	if(color1 < 0 || color1 > 256 || color2 < 0 || color2 > 256) return ErrorMessage(playerid, "№ цвета автомобиля от 0 до 256");
	new Float:X,Float:Y,Float:Z;
	GetPlayerPos(playerid, X,Y,Z);
	X += 1.5;
	new carid = A_CreateVehicle(car, X,Y,Z,0.0, color1, color2, -1);
    SetVehicleParamsEx(carid,false,false,false,false,false,false,false);
	LinkVehicleToInterior(carid, GetPlayerInterior(playerid));
	VI[carid][veX] = X;
	VI[carid][veY] = Y;
	VI[carid][veZ] = Z;
	VI[carid][vFuel] = 100.0;
	
	AdminCar[carid] = 1;
	
	new string[90];
	format(string, sizeof(string), "[A] %s[%d] создал авто. ID: %i",player_name[playerid],playerid,carid);
	SendAdminMessage(CADMIN_INFO, string);
	return true;
}
CMD:unwarn(playerid,params[]) {
	if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
    if(sscanf(params, "d", giveplayerid)) return SendEsp(playerid, "/unwarn [playerid]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	if(PI[giveplayerid][pWarns] == 0) return ErrorMessage(playerid, "У игрока нет предупреждений");
    new query[128];
    format(query, sizeof(query), "DELETE FROM `warns` WHERE `name` = '%s' AND `warn` = '%d'", player_name[giveplayerid], PI[giveplayerid][pWarns]);
	mysql_tquery(connects, query, "", "");
	PI[giveplayerid][pWarns]--;
	UpdatePlayerData(giveplayerid,"pWarns",PI[giveplayerid][pWarns]);
	new string[92];
	format(string, sizeof(string), "[A] %s[%d] удалил 1 предупреждение игроку %s[%d]", player_name[playerid], playerid, player_name[giveplayerid],giveplayerid);
	SendAdminMessage(CADMIN_INFO, string);

	format(string, sizeof(string), "Администратор %s удалил Вам 1 предупреждение", player_name[playerid]);
	SendClientMessage(giveplayerid, COLOR_GREEN, string);
	return 1;
}
CMD:weather(playerid, params[]) {
    if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
	if(sscanf(params, "d",giveplayerid)) return SendEsp(playerid, "/weather [id]");
	new string[128];
	format(string, sizeof(string), "[A] %s сменил номер погоды на %d", player_name[playerid], giveplayerid);
	SendAdminMessage(CADMIN_INFO, string);
	SetWeather(giveplayerid);
	return true;
}
CMD:uval(playerid, params[]) {
	if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
	new reason[31];
	if(sscanf(params, "ds[30]", giveplayerid, reason)) return SendEsp(playerid, "/uval [id] [причина]");

	if(giveplayerid == INVALID_PLAYER_ID) return ErrorMessage(playerid, not_id);

	if(!PI[giveplayerid][pMember]) return ErrorMessage(playerid, "Игрок не состоит в организации");
	if(GetString(FI[GetTeamID(giveplayerid)][fLeader],player_name[giveplayerid])) return ErrorMessage(playerid,"Лидера можно снять только через /makeleader");

	static const f_str[] = "Администратор %s[%i] уволил Вас из организации. Причина: %s";
	new string[sizeof(f_str) +1 + (-2 + 25) + (-2 + 4) + (-2 + 31)];

	format(string, sizeof(string), f_str, player_name[playerid],playerid, reason);
	SendClientMessage(giveplayerid, 0xFF182DFF, string);

	format(string, sizeof(string), "[A] %s[%d] выгнал игрока %s[%d] из фракции",player_name[playerid],playerid,player_name[giveplayerid],giveplayerid);
	SendAdminMessage(CADMIN_INFO, string);

	SetPlayerArmour(giveplayerid, 0);
	ResetPlayerWeapons(giveplayerid);

	if(start_work[giveplayerid]) {
		SendClientMessage(giveplayerid,COLOR_BLUE,"Рабочий день окончен");
		start_work[giveplayerid] = 0;
		UpdatePlayerData(giveplayerid, "FracDuty", 0);
	}
	PI[giveplayerid][pMember] = 0;
	PI[giveplayerid][pRank] = 0;
	PI[giveplayerid][pFracSkin] = 0;
	if(PI[giveplayerid][pLeader]) PI[giveplayerid][pLeader] = 0;
	SetPlayerColor(giveplayerid, TEAM_HIT_COLOR);
	if(PI[giveplayerid][pHouse] > 0) PI[giveplayerid][pSpawn] = 1;
	else PI[giveplayerid][pSpawn] = 0;
	skin_player(giveplayerid);
	SaveAccount(giveplayerid);
	return 1;
}
CMD:ears(playerid) {
	if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
	static const command_message[][] = {
		"Слушать смс ON",
		"Слушать смс OFF"
	};
	SendClientMessage(playerid, COLOR_REDD, command_message[GetPVarInt(playerid, "BigEarSms")]);
	SetPVarInt(playerid, "BigEarSms", !GetPVarInt(playerid, "BigEarSms"));
	return 1;
}
CMD:hpall(playerid,params[]) {
    if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
    if(sscanf(params, "d", giveplayerid)) return SendEsp(playerid, "/hpall [радиус]");
    if(giveplayerid < 5 || giveplayerid > 15) return ErrorMessage(playerid, "Радиус от 5 до 15 метров");
    new Float:pos[3];
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    foreach(new i:Player) {
        if(IsPlayerInRangeOfPoint(i, params[0], pos[0], pos[1], pos[2])) {
            A_SetPlayerHealth(i, 100.0);
            SendClientMessage(i, COLOR_GREY, "Администратор восстановил Вам здоровье");
        }
	}
	SendClientMessage(playerid, 0x66cc00FF, "Всем игрокам в указанном радиусе было восстановлено здоровье");
	return 1;
}
CMD:gettax(playerid, params[]) {
	if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;	
	new string[128];
	format(string, sizeof(string), "В казне штата: "GREEN"$%i", FI[fWHITEHOUSE][fBank]);
	SendClientMessage(playerid, COLOR_WHITE, string);
	return 1;
}
CMD:sban(playerid, params[]) {
    if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
	new day,text[37],string[415];
	if(sscanf(params, "uds[36]",giveplayerid,day,text)) return SendEsp(playerid, "/sban [playerid] [дни] [причина]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	if(IsAIP(text)) return 1;
	if(GetString(player_name[giveplayerid],"Oscar_Floyd")) return 1;
	if(day > 30 || 7 > day) return ErrorMessage(playerid,"От 7 до 30 дней");
	format(string, 144, "[A] %s[%d] %s забанил игрока %s без лишнего шума на %d дней. Причина: %s",player_name[playerid],playerid, player_name[giveplayerid],day,text);
	AdmMSG(CADMIN_INFO,string,3);
	new ip[17];
	GetPlayerIp(giveplayerid,ip,sizeof(ip));
	format(string, sizeof(string), "Name [%s]  R-IP [%s]  L-IP [%s]  IP [%s]",player_name[giveplayerid],PI[giveplayerid][pIpReg],PI[giveplayerid][pvIp],ip);
	AdmMSG(CADMIN_INFO,string,3);
	BanName(player_name[giveplayerid], player_name[playerid], day, text);
	WriteLog(LOG_SBAN,player_name[playerid],player_name[giveplayerid],text);
	gAdmin[playerid][ADMIN_BAN] ++;
	new hour,minute;
	new year,month,days;

	getdate(year, month, days);
	gettime(hour,minute);
	string = "";
	static const f_str[] = "\
			"W"Внимание! Ваш аккаунт был "NO"заблокирован"W"\n\n\
			"W"Заблокировал: "NO"%s\n\
			"W"Дни: "ORANGE"%d\n\
			"W"Дата: "ORANGE"%d-%d-%d %02d:%02d\n\
			"W"Причина: "ORANGE"%s\n\n\
			"W"Если вы считаете, что это ошибка, сделайте скриншот(F8) данного окна,\n\
			иначе Ваша жалоба будет не принята.";
	format(string,sizeof(string),f_str,player_name[playerid], day,days, month, year,hour, minute, text);

	new str[MAX_PLAYER_NAME+1];
	format(str,sizeof(str),"%s",player_name[giveplayerid]);
	D(giveplayerid, DIALOG_NONE, DSM, str, string, "Закрыть", "");
	Kick(giveplayerid);
	return true;
}
CMD:settime(playerid, params[]) {
    if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
    if(sscanf(params, "d",giveplayerid)) return SendEsp(playerid, "/settime [час] (0-23)");
	SetWorldTime(giveplayerid);
	return true;
}
CMD:gun(playerid, params[]) {
    if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
	new gun,ammo;
    if(sscanf(params, "udd",giveplayerid,gun,ammo)) return SendEsp(playerid, "/gun [id] [id оружия] [патроны]");
	if(ammo < 1 || ammo > 9999) return ErrorMessage(playerid, "Нельзя меньше 1 или больше 9999 патронов!");
	if(!PI[giveplayerid][pAdmin] && (gun != 24 && gun != 25 && gun != 29 && gun != 30 && gun != 31)) return
	ErrorMessage(playerid,"Данное оружие доступно только администрации");
	GiveWeapon(giveplayerid,gun,ammo);
	
	static const f_str[] = "Оружие было выдано игроку %s";
	new string[sizeof(f_str) +1 + (-2 + MAX_PLAYER_NAME)];

	new str[128];
	format(str, sizeof(str), "[A] %s[%d] выдал оружие [gun %d | patron %d] игроку %s[%d]",player_name[playerid],playerid,gun,ammo,player_name[giveplayerid],giveplayerid);
	SendAdminMessage(CADMIN_INFO,str);
	
	format(string,sizeof(string),f_str, player_name[giveplayerid]);
	SendClientMessage(playerid,-1,string);
	return true;
}
//-----------------------------------------[5 уровень]-------------------------------------------//
CMD:amusic(playerid, params[]) {
	if(PI[playerid][pAdmin] < 5 || dostup[playerid] == 0) return true;	
	new Float:radius, link[101];
	if(sscanf(params, "fs[100]", radius, link)) return SendEsp(playerid, "/amusic [радиус] [ссылка]");
	new Float:x, Float:y, Float:z, string[128];

	if(!(0.0 <= radius <= 500.0)) return ErrorMessage(playerid, "Радиус не может быть меньше 0 или больше 500");	

	GetPlayerPos(playerid, x, y, z);
	format(string, sizeof(string), "%s", link);
	PlayAudioStreamForPlayer(playerid, string, x,y,z, radius, true);

	format(string, sizeof(string), "Вы включили радио и назначили дистанцию %0.1f", radius);
	SendClientMessage(playerid,COLOR_GREY,string);
	return 1;
}
CMD:tempzone(playerid, params[]) {
    if(PI[playerid][pAdmin] < 5 || dostup[playerid] == 0) return true;
    if(sscanf(params, "d",giveplayerid)) return SendEsp(playerid, "/tempzone [банда]");
	for(new i = 0; i < TOTALGZ; i++) {
		if(PlayerToKvadrat(playerid,GZInfo[i][gCoords][0], GZInfo[i][gCoords][1],GZInfo[i][gCoords][2],GZInfo[i][gCoords][3])) {
			GZInfo[i][gFrakVlad] = giveplayerid;
			GangZoneStopFlashForAll(GZInfo[i][gZone]);
			GangZoneHideForAll(GZInfo[i][gZone]);
			GangZoneShowForAll(GZInfo[i][gZone],GetGangZoneColor(i));
			new query[128];
			format(query,sizeof(query),"UPDATE `"TABLE_GANGZONE"` SET `gang_owner` = '%i' WHERE `id` = %i",GZInfo[i][gFrakVlad],GZInfo[i][gID]);
 			mysql_tquery(connects, query, "", "");
			return true;
		}
	}
	return true;
}
CMD:respv(playerid, params[]) {
	if(PI[playerid][pAdmin] < 5 || dostup[playerid] == 0) return true;
	new Float: position[3],Float:rad;
	if(sscanf(params, "f", rad)) return SendEsp(playerid, "/respv [рудиус]");
	if(rad > 100 || rad < 2) return ErrorMessage(playerid, "Радиус от 2 до 100");
	GetPlayerPos(playerid, position[0], position[1], position[2]);
	for(new i = 0; i < MAX_VEHICLES; i++) {
	    if(GetVehicleModel(i) > 399) {
			GetVehiclePos(i,position[0],position[1],position[2]);
			if(IsPlayerInRangeOfPoint(playerid,rad,position[0],position[1],position[2])) SetVehicleToRespawn(i);
		}
	}
	SendClientMessage(playerid, COLOR_GREEN, "Машины в выбранном радиусе заспавнены");
	return true;
}
//-----------------------------------------[6 уровень]-------------------------------------------//
CMD:realodbans(playerid, params[]) {
    if(PI[playerid][pAdmin] < 6 || dostup[playerid] == 0) return true;
	SendRconCommand("reloadbans");
	SendClientMessage(playerid, COLOR_WHITE, "Бан-лист перезагружен");
	return true;
}
CMD:saveall(playerid, params[]) {
    if(PI[playerid][pAdmin] < 6 || dostup[playerid] == 0) return true;
    SaveServer();
	SendClientMessage(playerid,COLOR_GREY, "Все данные сохранены");
	return true;
}
CMD:gmx(playerid,params[]) {
    if(PI[playerid][pAdmin] < 6 || dostup[playerid] == 0) return true;
	SendClientMessageToAll(COLOR_YELLOW, "Через две минуты произойдет автоматическая перезагрузка сервера");
	SendClientMessageToAll(COLOR_YELLOW, "Просьба закончить все свои работы. Спасибо за понимание");
	SetTimer("OnServerRestarting", 120000, false);
	return true;
}
CMD:delacc(playerid, params[]) {
	if(PI[playerid][pAdmin] < 6 || dostup[playerid] == 0) return true;
	new name[25];
    if(sscanf(params,"S()[24]",name)) return SendEsp(playerid, "/delacc [Nick Name]");
	if(GetString(name,"Oscar_Floyd")) return 1;
	if(!strlen(name)) {
	    if(GetPVarInt(playerid, "delstatus")) {
	        SendClientMessage(playerid, COLOR_YELLOW, "Вы отменили удаление аккаунта");
            DeletePVar(playerid, "delstatus");
	    }
	    else SendEsp(playerid, "/delacc [Nick Name]");
	}
	else {
		new query[128];
		format(query, sizeof(query), "SELECT * FROM `accounts` WHERE `Name` = '%s'", name);
	    mysql_tquery(connects, query, "CheckDelAcc", "ds", playerid, name);
	}
	return true;
}
//-----------------------------------------[5 уровень]-------------------------------------------//
CMD:tpcor(playerid,params[]) {
    if(PI[playerid][pAdmin] < 5 || dostup[playerid] == 0) return true;
	new Float:x,Float:z,Float:y;
	if(sscanf(params,"fff",x,y,z)) return SendEsp(playerid,"/tpcor [x] [y] [z]");
	SetPlayerPos(playerid,Float:x,Float:y,Float:z);
	return 1;
}

CMD:addzone(playerid, params[]) {
    if(PI[playerid][pAdmin] < 6 || !dostup[playerid]) return true;
	new string[256],str[56];
    strcat(string,"Создать зеленую зону\n");
    for(new g = 1; g <= TOTALZONE; g++) {
    	format(str, sizeof(str), "%i. %s\n", GREENZONE[g][grid], GREENZONE[g][grName]);
     	strcat(string,str);
	}
 	return D(playerid, D_GREENZONE, 2, "Зеленые зоны", string, "Выбрать", "Закрыть");
}
CMD:svw(playerid,params[]) {
	if(PI[playerid][pAdmin] < 5 || dostup[playerid] == 0) return true;
	if(sscanf(params, "d",giveplayerid)) return SendEsp(playerid, "/sv [WORLD]");
	SetPlayerVirtualWorld(playerid,giveplayerid);
	
	static const f_str[] = "Виртуальный мир: %i";
	new string[sizeof(f_str) +1 + (-2 + 4)];
	
  	format(string, sizeof(string), f_str,giveplayerid);
 	SendClientMessage(playerid,-1,string);
	return 1;
}
CMD:si(playerid,params[]) {
    if(PI[playerid][pAdmin] < 5 || dostup[playerid] == 0) return true;
    if(sscanf(params, "d",giveplayerid)) return SendEsp(playerid, "/si [INTERIOR]");
    SetPlayerInterior(playerid,giveplayerid);
    
    static const f_str[] = "Интерьер: %i";
	new string[sizeof(f_str) +1 + (-2 + 4)];

  	format(string, sizeof(string), f_str,giveplayerid);
 	SendClientMessage(playerid,-1,string);
    return 1;
}
CMD:payday(playerid, params[]) {
	if(PI[playerid][pAdmin] < 7 || dostup[playerid] == 0) return true;
	if(!GetString(player_name[playerid],"Oscar_Floyd")) return 1;
	PayDay();
	return true;
}
CMD:cc(playerid, params[]) {
    if(PI[playerid][pAdmin] < 5 || dostup[playerid] == 0) return true;
	for(new i = 0; i < 60; i++) SendClientMessageToAll(COLOR_WHITE, "");
	SendClientMessageToAll(-1,"Игровой чат очищен администрацией сервера");
	return true;
}

CMD:setskin(playerid, params[]) {
    if(PI[playerid][pAdmin] < 6 || dostup[playerid] == 0) return true;
	new skin;
    if(sscanf(params, "ud", giveplayerid,skin)) return SendEsp(playerid, "/setskin [id игрока] [id скина]");
	if(skin > 311 || skin < 1) return ErrorMessage(playerid, "Неправильный ID скина!");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	PI[giveplayerid][pSkin] = skin;
	new string[72];
	format(string, sizeof(string), "Вы изменили скин %s на номер: %i",player_name[giveplayerid],skin);
	SendClientMessage(playerid, 0x6495EDFF, string);
	SetPlayerSkin(giveplayerid, PI[giveplayerid][pSkin]);
	UpdatePlayerData(giveplayerid,"Skin",PI[giveplayerid][pSkin]);
	return true;
}

CMD:setstat(playerid, params[]) {
    if(PI[playerid][pAdmin] < 6 || dostup[playerid] == 0) return true;
	if(!GetString(player_name[playerid],"Oscar_Floyd") && !GetString(player_name[playerid],"John_Rayderess")) return 1;
	new stat,amount;
	if(sscanf(params, "udd",giveplayerid,stat,amount)) {
		SendEsp(playerid, "/setstat [id] [номер] [количество]");
		SendClientMessage(playerid, COLOR_GRAD4, "[1] Уровень | [2] Законопослушность| [3] Боеприпасы");
		SendClientMessage(playerid, COLOR_GRAD3, "[4] Номер телефона | [5] Exp");
		SendClientMessage(playerid, COLOR_GRAD2, "[6] VIP | [7] Работа игрока| [8] Деньги в банке");
		SendClientMessage(playerid, COLOR_GRAD2, "[9] Счёт мобильного | [10] Деньги | [11] Наркотики");
		SendClientMessage(playerid, COLOR_GRAD2, "[12] Донат счётчик [13] Наркозависимость [14] ФракСкин");
		return true;
	}
	if(!IsPlayerConnected(giveplayerid)) return true;
	if(giveplayerid == INVALID_PLAYER_ID) return true;
	switch (stat) {
		case 1: {
			PI[giveplayerid][pLevel] = amount;
   			DollahScoreUpdate(giveplayerid);
			UpdatePlayerData(giveplayerid,"pLevel",amount);
		}
		case 2: PI[giveplayerid][pZakonp] = amount,UpdatePlayerData(giveplayerid,"pZakonp",amount);
        case 3: PI[giveplayerid][pMats] = amount,UpdatePlayerData(giveplayerid,"pMats",amount);
		case 4: PI[giveplayerid][pPhone] = amount,UpdatePlayerData(giveplayerid,"pPhone",amount);
		case 5: PI[giveplayerid][pExp] = amount;
		case 6: PI[giveplayerid][pVips] = unix + amount*86400,UpdatePlayerData(giveplayerid,"pVips",PI[giveplayerid][pVips]);
		case 7: PI[giveplayerid][pJob] = amount,UpdatePlayerData(giveplayerid,"pJob",amount);
		case 8: PI[giveplayerid][pBank] = amount,UpdatePlayerData(giveplayerid,"pBank",amount);
		case 9: PI[giveplayerid][pMobile] = amount,UpdatePlayerData(giveplayerid,"pMobile",amount);
		case 10: PI[giveplayerid][pCash] = amount,UpdatePlayerData(giveplayerid,"pCash",amount);
		case 11: PI[giveplayerid][pDrugs] = amount,UpdatePlayerData(giveplayerid,"pDrugs",amount);
		case 12: PI[giveplayerid][pRouble] = amount,UpdatePlayerData(giveplayerid,"donatemoney",amount);
		case 13: PI[giveplayerid][pAddiction] = amount;
		case 14: PI[giveplayerid][pFracSkin] = amount,UpdatePlayerData(giveplayerid,"pModel",amount);
	}
	SendClientMessage(playerid, COLOR_REDD, "Изменено");
	return true;
}
CMD:setmats(playerid,params[]) {
	if(PI[playerid][pAdmin] < 6 || dostup[playerid] == 0) return true;
	new amount;
	if(sscanf(params, "dd",giveplayerid,amount)) SendEsp(playerid, "/setstat [id] [количество]"),
	SendEsp(playerid, "1. Полиция ЛС | 2. Полиция СФ | 3. Полиция ЛВ | 4. ФБР | 5. Армия СФ | 6. Армия ЛВ"),
	SendEsp(playerid, "7. Ballas | 8. Vagos | 9. Grove | 10. Aztec | 11. Rifa"),
	SendEsp(playerid, "12. Итальянская мафия(LCN) | 13. Японская мафия(YAKUZA) | 14. Русская мафия(RM)"),
	SendEsp(playerid, "15. Оружейный завод | 16. Нефтезавод | 17. Цена за 1г нарко притон");
	switch(giveplayerid) {
		case 1: FI[fLSPD][fMats] = amount,UpdateFraction(fLSPD,"Mats",FI[fLSPD][fMats]);
		case 2: FI[fSFPD][fMats] = amount,UpdateFraction(fSFPD,"Mats",FI[fSFPD][fMats]);
		case 3: FI[fLVPD][fMats] = amount,UpdateFraction(fLVPD,"Mats",FI[fLVPD][fMats]);
		case 4: FI[fFBI][fMats] = amount,UpdateFraction(fFBI,"Mats",FI[fFBI][fMats]);
		case 5: FI[fARMYSF][fMats] = amount,UpdateFraction(fARMYSF,"Mats",FI[fARMYSF][fMats]);
		case 6: FI[fARMYLV][fMats] = amount,UpdateFraction(fARMYLV,"Mats",FI[fARMYLV][fMats]);

		case 7: FI[fBALLAS][fMats] = amount,UpdateFraction(fBALLAS,"Mats",FI[fBALLAS][fMats]);
		case 8: FI[fVAGOS][fMats] = amount,UpdateFraction(fVAGOS,"Mats",FI[fVAGOS][fMats]);
		case 9: FI[fGROVE][fMats] = amount,UpdateFraction(fGROVE,"Mats",FI[fGROVE][fMats]);
		case 10: FI[fAZTEC][fMats] = amount,UpdateFraction(fAZTEC,"Mats",FI[fAZTEC][fMats]);
		case 11: FI[fRIFA][fMats] = amount,UpdateFraction(fRIFA,"Mats",FI[fRIFA][fMats]);

		case 12: FI[fLCN][fMats] = amount,UpdateFraction(fLCN,"Mats",FI[fLCN][fMats]);
		case 13: FI[fYAKUZA][fMats] = amount,UpdateFraction(fYAKUZA,"Mats",FI[fYAKUZA][fMats]);
		case 14: FI[fRM][fMats] = amount,UpdateFraction(fRM,"Mats",FI[fRM][fMats]);

		case 15: zavodsklad = amount,UpdateOtherData("gun_mats",zavodsklad);
		case 16: oilsklad = amount,UpdateOtherData("oil_mats",oilsklad);
		case 17: pricedrugs = amount,UpdateOtherData("pricedrugs",pricedrugs);
		default: ErrorMessage(playerid,"Произошла ошибка");
	}
	SendClientMessage(playerid,COLOR_GREEN,"Вы успешно пополнили склад");
	return 1;
}
CMD:getip(playerid, params[]) {
    if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
	if(sscanf(params, "u",giveplayerid)) return SendEsp(playerid, "/getip [playerid]");
    new ip[15],string[128];
	GetPlayerIp(giveplayerid,ip,15);
	format(string, sizeof(string), "Nik [%s]   R-IP [%s]   L-IP [%s]   IP [%s]",player_name[giveplayerid],PI[giveplayerid][pIpReg],PI[giveplayerid][pvIp],ip);
	SendClientMessage(playerid,0x6BB3FFAA,string);
	return true;
}
CMD:makeadmin(playerid, params[]) {
	if(PI[playerid][pAdmin] < 6 || dostup[playerid] == 0) return true;
	new Name[30],Level;
	if(sscanf(params, "s[30]d",Name,Level)) return SendEsp(playerid, "/makeadmin [id / ник] [уровень]");
	if(!(0 <= Level <= 6)) return ErrorMessage(playerid, "От 0 до 6");
	if(!strcmp(Name,"_") || !strcmp(Name,"Oscar_Floyd")) {
		SendClientMessage(playerid,COLOR_REDD,"Наивный)");
		return 1;
	}
	new query[128];
	if(!isNumeric(Name)) {
		new id_name = strval(Name);
		if(!IsPlayerConnected(id_name)) return ErrorMessage(playerid, not_id);

		if(!strcmp(player_name[id_name],"_") || !strcmp(player_name[id_name],"Oscar_Floyd")) {
			SendClientMessage(playerid,COLOR_REDD,"Наивный)");
			return 1;
		}
		format(query, sizeof(query), "SELECT * FROM `admin` WHERE `name` = '%s' LIMIT 1", player_name[id_name]);
		mysql_pquery(connects, query, "Moderator", "dsd",playerid,player_name[id_name],Level);
		return 1;
	}
	format(query, sizeof(query), "SELECT * FROM `admin` WHERE `name` = '%s' LIMIT 1", Name);
	mysql_pquery(connects, query, "Moderator", "dsd",playerid,Name,Level);
	return 1;
}

CMD:last(playerid, params[]) {
    if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return ErrorMessage(playerid, "Вам недоступна эта функция");
    if(sscanf(params, "s[25]",giveplayerid)) return SendEsp(playerid, "/last [Nick_Name]");
    new QUERY[128];
    format(QUERY, sizeof(QUERY), "SELECT * FROM `"TABLE_ACCOUNTS"` WHERE `Name` = '%s'",giveplayerid);
	new Cache:result = mysql_query(connects, QUERY);
	new rows = cache_num_rows();
	if(rows == 0) return ErrorMessage(playerid,"Аккаунт не найден");
    cache_get_value_name(0, "pOnline",QUERY,30);
    static const f_str[] = "Ник: %s | Последний вход: %s";
	new string[sizeof(f_str) +1 + (-2 + MAX_PLAYER_NAME) + (-2 + 9)];
	format(string,sizeof(string),f_str,giveplayerid,QUERY);
	SendClientMessage(playerid,COLOR_BLUE,string);
	cache_delete(result);
	return true;
}
CMD:makeleader(playerid, params[]) {
    if(PI[playerid][pAdmin] < 5 || dostup[playerid] == 0) return true;
	new string[64], strings[1024];
	strcat(strings,"№\tОрганизация\tЛидер\n");
	for(new i = 1;i < MAX_FRACTIONS;i ++) {
		format(string,sizeof(string),"%i\t%s\t%s\n",i,FI[i][fName],FI[i][fLeader]);
		strcat(strings,string);
	}
	D(playerid,D_MAKELEADER_INFO,DSTH,"Лидеры организаций",strings,"Выбрать","Отмена");
	return 1;
}
CMD:inthouse(playerid, params[]) {
	if(PI[playerid][pAdmin] < 7 || dostup[playerid] == 0) return true;
	if(!GetPVarInt(playerid,"select_house")) return 1;
    new str[1512];
	for(new i = 0; i < HINTS_COUNT; i++)
	format(str, sizeof(str), "%s%d %s\n", str, i+1,gHints[i][hintDescription]);
	D(playerid, D_TP_HOUSE, DSL,"Интерьеры домов", str, "Выбрать", "Отмена");
	return true;
}
CMD:infoips(playerid,params[]) {
    if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
    if(sscanf(params, "s",params[0])) return SendEsp(playerid, "/infoips [IP]");
    new QUERY[256];
    format(QUERY, sizeof(QUERY), "SELECT HIGH_PRIORITY * FROM `"TABLE_ACCOUNTS"` WHERE `pvIp` LIKE '%s'",params[0]);
	new Cache:result = mysql_query(connects, QUERY);
	new rows = cache_num_rows();
	if(rows == 0) return ErrorMessage(playerid,"IP адрес не найден");
    new tmpas[16],regip[16],mname[32];
    for(new i = 0; i < rows; i++) {
	    cache_get_value_name(i, "Name", mname, MAX_PLAYER_NAME);
	    cache_get_value_name(i, "pvIp", tmpas, 16);
	    cache_get_value_name(i, "pIpReg", regip, 16);

		static const f_str[] = "%s | LAST-IP: %s | REG-IP: %s";
		new string[sizeof(f_str) +1 + (-2 + MAX_PLAYER_NAME) + (-2 + 16) + (-2 + 16)];

		format(string,sizeof(string),f_str,mname,tmpas, regip);
		SendClientMessage(playerid,COLOR_WHITE,string);
	}
    cache_delete(result);
	return true;
}
CMD:mutelist(playerid, params[]) {
    if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
	new countmute = 0,string[512];
	foreach(new i:Player) {
		if(PI[i][pMute] > 0 && IsPlayerConnected(i)) {
			format(string, sizeof(string), ""YELLOW"%d. "ORANGE"%s"W" | ID: "BLUE"%d"W" | Секунд: "GREEN"%d",countmute+1,player_name[i],i,PI[i][pMute]);
			countmute++;
		}
	}
	if(countmute == 0) return ErrorMessage(playerid, "Нет игроков с Баном чата");
	D(playerid, DIALOG_NONE, DSM, "Игроки с баном чата", string, "Закрыть", "");
	return true;
}
CMD:agetip(playerid, params[]) {
    if(PI[playerid][pAdmin] < 4 || dostup[playerid] == 0) return true;
	if(sscanf(params, "s[42]",params[0])) return SendEsp(playerid, "/agetip [Ник]");
	new QUERY[128];
	format(QUERY, sizeof(QUERY), "SELECT * FROM `"TABLE_ACCOUNTS"` WHERE `Name` = '%s'",params[0]);
	new Cache:result = mysql_query(connects, QUERY),ip[2][17];
	new rows = cache_num_rows();
	if(rows == 0) return ErrorMessage(playerid,"Аккаунт не найден!");
	
	cache_get_value_name(0, "pIp",ip[0],16);
	cache_get_value_name(0, "pIpReg",ip[1],16);

	static const f_str[] = "Ник: %s | IP: %s | IP при регистрации: %s";
	new string[sizeof(f_str) +1 + (-2 + MAX_PLAYER_NAME) + (-2 + 17) + (-2 + 17)];

	format(string,sizeof(string),f_str,params[0],ip[0],ip[1]);
	SendClientMessage(playerid,COLOR_BLUE,string);
	cache_delete(result);
	return true;
}
CMD:captfreeze(playerid,params[]) {
	if(PI[playerid][pAdmin] < 5 || dostup[playerid] == 0) return true;
	new gang_id, time,string[128];
	if(sscanf(params,"ii",gang_id, time)) {
		SendClientMessage(playerid,COLOR_GREY,"/captfreeze [id] [часов]");
		SendClientMessage(playerid,COLOR_GREY,"1 - The Ballas | 2 - The Vagos | 3 - The Grove");
		SendClientMessage(playerid,COLOR_GREY,"4 - The Rifa | 5 - The Aztecas | 6 - LCN");
		SendClientMessage(playerid,COLOR_GREY,"7 - Yakuza | 8 - Russian Mafia");
		return 1;
	}
	if(gang_id < 1 || gang_id > 8 || time < 0) {
		SendClientMessage(playerid,COLOR_GREY,"/captfreeze [id] [часов]");
		SendClientMessage(playerid,COLOR_GREY,"1 - The Ballas | 2 - The Vagos | 3 - The Grove");
		SendClientMessage(playerid,COLOR_GREY,"4 - The Rifa | 5 - The Aztecas | 6 - LCN");
		SendClientMessage(playerid,COLOR_GREY,"7 - Yakuza | 8 - Russian Mafia");
		return 1;
	}
	if(time == 0) {
		fracmoroz[gang_id-1] = 0;
		format(string, sizeof(string), "Администратор %s разморозил банду %s",player_name[playerid],fracmorozName[gang_id-1]);
	}
	else {
		fracmoroz[gang_id-1] = unix+(3600*time);
		format(string, sizeof(string), "Администратор %s заморозил банду %s на %d час(ов)",player_name[playerid],fracmorozName[gang_id-1],time);
	}
	SendClientMessageToAll(COLOR_LIGHTRED,string);
	UpdateMorozed();
	return 1;
}


CMD:createost(playerid) {
	if(PI[playerid][pAdmin] < 7 || dostup[playerid] == 0) return true;
	if(GetPVarInt(playerid,"TotalOst_")) return 1;
	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid,X,Y,Z);
	ostanovka[TotalOst][ostID] = CreateDynamicObject(1257,X,Y+0.5,Z,0.0,0.0,0.0,-1,-1,-1,200.0,200.0);

	ostanovka[TotalOst][ostX] = X;
	ostanovka[TotalOst][ostY] = Y+0.5;
	ostanovka[TotalOst][ostZ] = Z;

	Streamer_Update(playerid);
	new string[128];
	format(string, sizeof(string), "Вы создали остановку "W"(slot: %i)",TotalOst);
	SendClientMessage(playerid,COLOR_BLUE,string);
	SendClientMessage(playerid,COLOR_BLUE,"Для редактирования её месторасположения, используйте "W"/editost");

	SetPVarInt(playerid,"TotalOst_", TotalOst+1);
	TotalOst++;
	return 1;
}

CMD:editost(playerid) {
	if(PI[playerid][pAdmin] < 7 || dostup[playerid] == 0) return true;
	if(!GetPVarInt(playerid,"TotalOst_")) return 1;

	new slot = GetPVarInt(playerid,"TotalOst_")-1;
	EditDynamicObject(playerid,ostanovka[slot][ostID]);
	SendClientMessage(playerid,COLOR_BLUE,"После редактирования, для сохранения введите "W"/finishost");
	return 1;
}

CMD:finishost(playerid) {
	if(PI[playerid][pAdmin] < 7 || dostup[playerid] == 0) return true;
	if(!GetPVarInt(playerid,"TotalOst_")) return 1;
	new slot = GetPVarInt(playerid,"TotalOst_")-1;

	new Float:X, Float:Y, Float:Z;
	new Float:rX, Float:rY, Float:rZ;

	GetDynamicObjectPos(ostanovka[slot][ostID],X,Y,Z);
	GetDynamicObjectRot(ostanovka[slot][ostID],rX,rY,rZ);

	DestroyDynamicObject(ostanovka[slot][ostID]);
	ostanovka[slot][ostID] = CreateDynamicObject(1257,ostanovka[slot][ostX],ostanovka[slot][ostY],ostanovka[slot][ostZ],
														 ostanovka[slot][ostrX],ostanovka[slot][ostrY],ostanovka[slot][ostrZ],-1,-1,-1,200.0,200.0);
	Streamer_Update(playerid);

	new query[512];
	format(query,sizeof(query),"INSERT INTO `ostanovka`(`X`, `Y`, `Z`, `rX`, `rY`, `rZ`) VALUES ('%f','%f','%f','%f','%f','%f')",ostanovka[slot][ostX],ostanovka[slot][ostY],ostanovka[slot][ostZ],ostanovka[slot][ostrX],ostanovka[slot][ostrY],ostanovka[slot][ostrZ]);
	mysql_pquery(connects,query);

	SendClientMessage(playerid,COLOR_GREEN,"Остановка сохранена.");
	DeletePVar(playerid,"TotalOst_");
	return 1;
}
CMD:warns(playerid, params[]) {
	if(PI[playerid][pAdmin] != 0) {
	    if(PI[playerid][pAdmin] < 2 || dostup[playerid] == 0) return true;
	    if(sscanf(params, "d", giveplayerid)) return SendEsp(playerid, "/warns [playerid]");
		if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	    if(PI[giveplayerid][pWarns] == 0) return ErrorMessage(playerid,"На данном аккаунте предупреждений нет");
		new query[128];
	    format(query, sizeof(query), "SELECT * FROM `warns` WHERE `name` = '%s' ORDER BY `warn` DESC LIMIT %d", player_name[giveplayerid], PI[giveplayerid][pWarns]);
	    mysql_tquery(connects, query, "warninfo", "ii", giveplayerid,0);
	    SetPVarInt(giveplayerid, "warninfo", playerid);
	}
	else {
	    if(PI[playerid][pWarns] == 0) return ErrorMessage(playerid,"На Вашем аккаунте предупреждений нет");
	    new query[128];
	    format(query, sizeof(query), "SELECT * FROM `warns` WHERE `name` = '%s' ORDER BY `warn` DESC LIMIT %d", player_name[playerid], PI[playerid][pWarns]);
	    mysql_tquery(connects, query, "warninfo", "ii", playerid,1);
	}
	return 1;
}
CMD:history(playerid, params[]) {
    if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	if(sscanf(params, "d",giveplayerid)) return SendEsp(playerid, "/history [ID]");
    D(playerid,D_ADMIN_HISTORY,DSL,"История предупреждений","1. Бан чата\n2. Кик\n3. Варн\n4. Блокировка аккаунта\n5. Jail\n6. Смена ника\n7. Разблокировка аккаунта\n8. Блокировка IP\n9. Разблокировка IP\n10. Тихий кик\n11. Тихий бан","Выбрать","Отмена");
    SetPVarInt(playerid,"GIVEPLAYERID",giveplayerid);
	return true;
}
CMD:apanel(playerid, params[]) {
    if(PI[playerid][pAdmin] < 6 || dostup[playerid] == 0) return true;
    D(playerid,D_ADMIN_PANEL,DSL,"Админ панель","1. Игроки в тюрьме\n2. Игроки с баном чата\n3. Бонусы\n4. Промокоды","Выбрать","Отмена");
	return true;
}
CMD:admstats(playerid,params[]) {
	if(PI[playerid][pAdmin] < 6 || dostup[playerid] == 0) return true;
	if(sscanf(params, "d",giveplayerid)) return SendEsp(playerid, "/admstats [id]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	new year, month, day, hour, minute, second;
	timestamp_to_date(gAdminTime[giveplayerid], year, month, day, hour, minute, second);

	new string[512];

	format(string, 128, "Онлайн администратора "W"%s"YELLOW" за эту неделю: "GREEN"%i дней %i часов %i минут %i секунд",player_name[giveplayerid],day-1, hour, minute, second);
	SendClientMessage(playerid,COLOR_YELLOW,string);

	format(string,450,""ORANGE"Киков: "W"\t\t%d\n"ORANGE"Банов: "W"\t\t%d\n"ORANGE"Мутов: "W"\t\t%d\n"ORANGE"Ответов: "W"\t\t%d\n"ORANGE"Варнов: "W"\t\t%d\n"ORANGE"Джайлов: "W"\t\t%d",gAdmin[giveplayerid][0],gAdmin[giveplayerid][1],gAdmin[giveplayerid][2],gAdmin[giveplayerid][3],gAdmin[giveplayerid][4],gAdmin[giveplayerid][5]);
	D(playerid,DIALOG_NONE,DSM,player_name[giveplayerid],string,"Закрыть","");
	return 1;
}
/*CMD:ahelp(playerid, params[]) {
    if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
if(a_info[playerid][aRankID] >= 1) strcat(stringer, "{FFFFFF}1 уровень: {FFC919}/prisoners, /prison, /mute, /unmute, /rmute, /unrmute, /unjail, /re, /cw, /ap, /togphone, /aheal, /admin, /a, /goto, /gethere, /knocklist, /offjail, /hp, /tp, /startregzombie, /ans, /object\n");
if(a_info[playerid][aRankID] >= 2) strcat(stringer, "{FFFFFF}2 уровень: {FFC919}/getstats, /slap, /skin, /iwep, /sp, /freeze, /unfreeze\n");
if(a_info[playerid][aRankID] >= 3) strcat(stringer, "{FFFFFF}3 уровень: {FFC919}/kick, /skick, /getip, /alock, /get, /mark, /gotomark \n");
if(a_info[playerid][aRankID] >= 4) strcat(stringer, "{FFFFFF}4 уровень: {FFC919}/amusic, /sban, /adellaction, /warnmans, /mutelist, /offmute, /getban, /int\n");
if(a_info[playerid][aRankID] >= 5) strcat(stringer, "{FFFFFF}5 уровень: {FFC919}/uval, /iban, /ban, /ainvite, /fid, /atipster, /spawncars, /chatsms, /chatpm, /offban, /unban, /veh, /delveh, /pgetip, /agetip, /gotogz, /gzcolor\n");
if(a_info[playerid][aRankID] >= 6) strcat(stringer, "{FFFFFF}6 уровень: {FFC919}/warn, /tempmember, /setname, /aad, /clear, /unwarn, /offunwarn, /offwarn, /sethp, /gotospawn, /weather, /unbanip, /banip, /agetipreg, /setbizwar, /createmp\n");
if(a_info[playerid][aRankID] >= 7) strcat(stringer, "{FFFFFF}7 уровень: {FFC919}/agetstats, /fuelcars, /startpb, /startrace, /checkpbtime, /checkracetime, /mp, /givegun, /alldelveh, /gangfreeze, /mafiafreeze\n");
if(a_info[playerid][aRankID] >= 8) strcat(stringer, "{FFFFFF}8 уровень: {FFC919}/tempskin, /offgoto, /biz, /hbject, /hbjectedit\n");
if(a_info[playerid][aRankID] >= 9) strcat(stringer, "{FFFFFF}9 уровень: {FFC919}/setskin, /spveh, /agiverank\n");
if(a_info[playerid][aRankID] >= 10) strcat(stringer, "{FFFFFF}10 уровень: {FFC919}/house, /ranks, /deletehit, /contracts\n");
if(a_info[playerid][aRankID] >= 11) strcat(stringer, "{FFFFFF}11 уровень: {FFC919}/lmenu, /elections, /makeleader, /changerank, /offleader, /hpoint, /lpoint, /avigl, /unvigl, /changefractiongun, /changefractionskin\n");
if(a_info[playerid][aRankID] >= 12) strcat(stringer, "{FFFFFF}12 уровень: {FFC919}/setstats /delacc /giverouble /agivevip /addhouse /changehousepos /changehouseposcar /addbizz /point /createost /avig /admstat /sethouseklass /loadmap /deletemap\n");
ShowPlayerDialog(playerid,0000,DIALOG_STYLE_MSGBOX,"{ffffff}Команды администратора",stringer,"Закрыть","");
	return true;
}*/
CMD:agiverank(playerid,params[]) {
	if(PI[playerid][pAdmin] < 6 || dostup[playerid] == 0) return true;
	new rankid;
	if(sscanf(params,"ui", giveplayerid, rankid)) return SendEsp(playerid, "/agiverank [id] [ранг]");
	if(giveplayerid == INVALID_PLAYER_ID) return ErrorMessage(playerid, not_id);
	if(!PI[giveplayerid][pMember]) return ErrorMessage(playerid, "Игрок не в организации");
	if(rankid > (FI[PI[giveplayerid][pMember]][fMaxRang]-1) || rankid < 1) return ErrorMessage(playerid, "Вы допустили ошибку");
	new string[128];
	format(string, sizeof(string), "[A] %s изменил ранг игроку %s c %d на %d", player_name[playerid],player_name[giveplayerid],PI[giveplayerid][pRank],rankid);
	SendAdminMessage(CADMIN_INFO,string);

	format(string, sizeof(string), "Администратор "W"%s"BLUE" изменил Вам ранг на %d",player_name[playerid],rankid);
	SendClientMessage(giveplayerid, COLOR_BLUE, string);

	PI[giveplayerid][pRank] = rankid;
	UpdatePlayerData(giveplayerid,"pRank", rankid);
	return 1;
}
CMD:setbizmafia(playerid, params[]) {
	if(PI[playerid][pAdmin] < 5 || dostup[playerid] == 0) return true;

	new mafiaid;
	if(sscanf(params,"d",mafiaid)) {
		SendEsp(playerid, "/setbizmafia [номер]");
		SendClientMessage(playerid,COLOR_GREY, "1 - Итальянская | 2 - Японская | 3 - Русская");
		return 1;
	}
	if(mafiaid < 1 || mafiaid > 3) return 1;
	for(new b; b < gBusinessCount; b++) {
		if(!PlayerToPoint(4.0,playerid,gBusiness[b][bizzX],gBusiness[b][bizzY],gBusiness[b][bizzZ])) continue;
		switch(mafiaid) {
			case 1: gBusiness[b][bizzMafia] = fLCN;
			case 2: gBusiness[b][bizzMafia] = fYAKUZA;
			case 3: gBusiness[b][bizzMafia] = fRM;
		}
		static const mafia_name[][] = {
			"Итальянская мафия",
			"Японская мафия",
			"Русская мафия"
		};
		new string[128];
		format(string, sizeof(string), "[A] %s изменил контроль бизнеса %s - %s", player_name[playerid], gBusiness[b][bizzName], mafia_name[mafiaid-1]);
		SendAdminMessage(CADMIN_INFO,string);
		UpdateBusinessText(b);
		UpdateBusinessData(b+1,"mafia",gBusiness[b][bizzMafia]);
		break;
	}
	return 1;
}
CMD:gspawn(playerid, params[]) {
	if(PI[playerid][pAdmin] < 3 || dostup[playerid] == 0) return true;
	if(sscanf(params,"u", giveplayerid)) return SendEsp(playerid, "/gspawn [id]");

	if(giveplayerid == INVALID_PLAYER_ID) return ErrorMessage(playerid, not_id);
	SpawnPlayer(giveplayerid);
	new string[128];
	format(string, sizeof(string), "[A] %s[%d] заспавнил игрока %s[%d]",player_name[playerid],playerid,player_name[giveplayerid],giveplayerid);
	SendAdminMessage(CADMIN_INFO,string);
	format(string, sizeof(string), "Вас заспавнил администратор %s[%d]",player_name[playerid],playerid);
	SendClientMessage(giveplayerid, COLOR_GREY, string);
	return 1;
}
CMD:vibor(playerid) {
	if(PI[playerid][pAdmin] < 7 || dostup[playerid] == 0) return true;
	D(playerid, D_ELECTION, DSL, "Управление выборами", "1. Список кандидатов\n2. Добавить кандидата\n3. Снять кандитата\n4. Окончить выборы", "Выбрать", "Закрыть");
	return 1;
}
CMD:timestat(playerid) {
	if(PI[playerid][pAdmin] < 6 || dostup[playerid] == 0) return true;
	new str[256];
	format(str, sizeof(str),"Последнее время прокрутки Timer_Unix: (%d ms). пик: (%d ms).\n", time_grandtimer, time_grandtimer_max);
	format(str, sizeof(str),"%sПоследнее время прокрутки OnPlayerUpdate: (%d ms). пик: (%d ms).\nПоследнее время прокрутки \"newkeys\": (%d ms). пик: (%d ms).", str, time_update,time_update_max,time_newkeys,time_newkeys_max);
	D(playerid,DIALOG_NONE,DSM,"Нагрузка мода", str, "Закрыть", "");
	return 1;
}
CMD:changename(playerid, params[]) {
	if(PI[playerid][pAdmin] < 7 || dostup[playerid] == 0) return true;
    new bizz[65];
    if(sscanf(params, "s[64]", bizz)) return SendEsp(playerid,"/changename [название]");
    for(new b; b < gBusinessCount; b++) {
		if(PlayerToPoint(10.0, playerid, gBusiness[b][bizzX], gBusiness[b][bizzY], gBusiness[b][bizzZ])) {
			strmid(gBusiness[b][bizzName],bizz, 0, strlen(bizz), 64);
			new query[128];
			format(query,sizeof(query),"UPDATE `business` SET `name` = '%s' WHERE `id` = '%i'",gBusiness[b][bizzName],b+1);
 			mysql_tquery(connects, query, "", "");
			UpdateBusinessText(b);
		}
	}
	return 1;
}
CMD:changeprice(playerid, params[]) {
	if(PI[playerid][pAdmin] < 7 || dostup[playerid] == 0) return true;
	new price;
    if(sscanf(params, "d", price)) return SendEsp(playerid,"/changeprice [price]");
    for(new b; b < gBusinessCount; b++) {
		if(PlayerToPoint(10.0, playerid, gBusiness[b][bizzX], gBusiness[b][bizzY], gBusiness[b][bizzZ])) {
			gBusiness[b][bizzSellPrice] = price;
			new query[128];
			format(query,sizeof(query),"UPDATE `business` SET `sellprice` = '%d' WHERE `id` = '%i'",gBusiness[b][bizzSellPrice],b+1);
 			mysql_tquery(connects, query, "", "");
			UpdateBusinessText(b);
		}
	}
	return 1;
}
CMD:getvw(playerid) {
	if(PI[playerid][pAdmin] < 1 || dostup[playerid] == 0) return true;
	new str[64];
	format(str, sizeof(str), "Виртуальный мир: %i, %i",GetPlayerVirtualWorld(playerid),PI[playerid][pHotel]);
 	SendClientMessage(playerid,-1,str);
	return 1;
}
CMD:createatm(playerid, params[]) {
	if(PI[playerid][pAdmin] < 7 || dostup[playerid] == 0) return true;
	new atmID = -1;
	for(new a = 1; a < MAX_ATM; a++) {
		if(ATMData[a][atm_Taken] == 0) {
			atmID = a;
			break;
		}
	}
	if(atmID == -1) return ErrorMessage(playerid, "Максимальное количество банкоматов достигнуто");
	CreateATM(playerid, atmID);
	return 1;
}

CMD:editatm(playerid, params[]) {
	if(PI[playerid][pAdmin] < 7 || dostup[playerid] == 0) return true;
	new atmID, title[29];
	if(!sscanf(params, "i", atmID)) {
		if(atmID < 1 || atmID > MAX_ATM) return ErrorMessage(playerid, "Указан неверный банкомат!");

		if(ATMData[atmID][atm_Taken] == 0) return ErrorMessage(playerid, "Банкомат, который Вы хотите редактировать, не активен");

		EdittingATM[playerid] = atmID;

		format(title, sizeof(title), "Изменение ATM: (ID: %d)", atmID);
		D(playerid, DIALOG_ATM_EDIT, DSL, title, "Изменение позиции(редактор)\nПеренести позицию на свои координаты\nУдаление ATM", "Далее", "Отмена");
	}
	else SendEsp(playerid, "/editatm [atmID]");
	return 1;
}
CMD:poscar(playerid, params[]) {
	if(PI[playerid][pAdmin] < 7 || dostup[playerid] == 0) return true;
	if(sscanf(params, "d",params[0])) return SendEsp(playerid, "/poscar [дом]");
	new carid = GetPlayerVehicleID(playerid);
	if(GetVehicleModel(carid) != 560) return ErrorMessage(playerid, "Сядьте в султан");
	
	new Float: lwx, Float:lwy, Float:lwz,Float:a;
	GetVehiclePos(carid,lwx, lwy, lwz);
	GetVehicleZAngle(carid,a);

	gHouses[params[0]-1][houseParkX] = lwx;
	gHouses[params[0]-1][houseParkY] = lwy;
	gHouses[params[0]-1][houseParkZ] = lwz;
	gHouses[params[0]-1][houseParkR] = a;
	SetVehicleToRespawn(GetPlayerVehicleID(playerid));
	SendClientMessage(playerid, COLOR_GREEN, "Координаты машины установлены(Я надеюсь ты поставил машину ровно)");
	new query[256];
	format(query,sizeof(query),"UPDATE `houses` SET `parkx` = '%.2f',`parky` = '%.2f',`parkz` = '%.2f',`parkr` = '%.2f' WHERE id = '%d'",gHouses[params[0]-1][houseParkX],gHouses[params[0]-1][houseParkY],gHouses[params[0]-1][houseParkZ],gHouses[params[0]-1][houseParkR],params[0]);
	mysql_tquery(connects, query);
	return true;
}
CMD:useint(playerid, params[]) {
	if(PI[playerid][pAdmin] < 7 || dostup[playerid] == 0) return true;
	if(edit_int[playerid] == -1) return ErrorMessage(playerid, "Интерьер не выбран");
	D(playerid, D_HOUSE_INT_1,DSM,"Редактор дома | Интерьер","Вы действительно хотите поставить данный интерьер в дом?","Поставить","Отмена");
	return 1;
}
CMD:edithouse(playerid, params[]) {
	if(PI[playerid][pAdmin] < 7 || dostup[playerid] == 0) return true;
	if(sscanf(params, "i", params[0])) return SendEsp(playerid, "/edithouse [ид дома]");
	new classname[15];
	switch(gHouses[params[0]-1][houseClass]) {
		case 0: classname = "Эконом";
		case 1: classname = "Cредний";
		case 2: classname = "Элитный";
		case 3: classname = "Особняк";
	}	
	static const f_str[] = ""YELLOW" ДОМ № %d\n\
							"ORANGE"1."W" Класс дома\t"BLUE"%s\n\
							"ORANGE"2."W" Интерьер дома\t"BLUE"%s\n\
							"ORANGE"3."W" Стоимость дома\t"BLUE"%d\n\
							"ORANGE"4."W" Парковка автомобиля\t"BLUE"%f %f %f %f\n\
							"ORANGE"5."W" ТП к дому";
	new string[500];
	format(string,sizeof(string),f_str,params[0],classname,gHints[gHouses[params[0]-1][houseHint]][hintDescription],gHouses[params[0]-1][housePrice],gHouses[params[0]-1][houseParkX],gHouses[params[0]-1][houseParkY],gHouses[params[0]-1][houseParkZ],gHouses[params[0]-1][houseParkR]);
	D(playerid,D_ADDHOUSE,DSL,"Редактор дома",string,"Изменить","Отмена");
	SetPVarInt(playerid,"select_house",params[0]);
    return true;
} 
CMD:addradar(playerid, params[]) {
	if(PI[playerid][pAdmin] < 7 || dostup[playerid] == 0) return true;
    if(sscanf(params, "i", params[0])) return SendEsp(playerid, "/addradar [скорость]");
    new Float:X, Float:Y, Float:Z;
    GetPlayerPos(playerid, X, Y, Z);
	new query[156];
	mysql_format(connects, query, sizeof(query), "INSERT INTO radar(`rX`, `rY`, `rZ`, `rSpeed`) VALUES ('%f', '%f', '%f', '%i')",X,Y,Z,params[0]);
	mysql_tquery(connects, query);
	gRadarCount++;
	gRadar[gRadarCount][radarid] = gRadarCount;
    gRadar[gRadarCount][radarObj] = CreateDynamicObject(18880, X+1, Y+1, Z+1, 0.0,0.0,0.0);
	gRadar[gRadarCount][radarX] = X;
	gRadar[gRadarCount][radarY] = Y;
	gRadar[gRadarCount][radarZ] = Z;
	gRadar[gRadarCount][radarSpeed] = params[0];
	IsRadar[gRadarCount] = CreateDynamicSphere(X,Y,Z, 100, 0, 0);
	static const f_str[] = "Радар "GREEN"№%d"W"\nМаксимальная скорость: "NO"%d "W"км/ч";
	new string[sizeof(f_str) +1 + (-2 + 3) + (-2 + 5)];
	format(string,sizeof(string),f_str,gRadar[gRadarCount][radarid],gRadar[gRadarCount][radarSpeed]);
	Is3DRadar[gRadarCount] = CreateDynamic3DTextLabel(string,-1,gRadar[gRadarCount][radarX], gRadar[gRadarCount][radarY], gRadar[gRadarCount][radarZ]+5,20.0);
    return true;
} 
CMD:editradar(playerid, params[]) {
	if(PI[playerid][pAdmin] < 7 || dostup[playerid] == 0) return true;
    if(sscanf(params, "ii", params[0],params[1])) return SendEsp(playerid, "/editradar [id радара] [скорость]");
	SetPVarInt(playerid, "addrad", 1);
	SetPVarInt(playerid,"radar_edit",params[0]);
	SetPVarInt(playerid, "speed", params[1]);
    EditDynamicObject(playerid, gRadar[params[0]][radarObj]);
    return true;
}
CMD:mp(playerid, params[]) {
    if(Teleport == 0) return 1;
    if(PI[playerid][pJailTime] >= 1) return ErrorMessage(playerid, "Вы в тюрьме");
    D(playerid, D_MP_3, DSM, "Телепортация", "\n\n"W"Вы уверены, что хотите попасть в место проведения мероприятия?\n\n", "Да", "Нет");
    return 1;
}
CMD:gomp(playerid, params[]) {
    if(PI[playerid][pAdmin] < 5 || dostup[playerid] == 0) return true;
    if(Teleport == 0) D(playerid, D_MP, DSL, "МЕРОПРИЯТИЕ", "1. Создать телепорт\n2. Раздать оружие\n3. Раздать жизнь\n4. Раздать броню\n5. Обезоружить всех\n6. Забрать броню\n7. Ввести название", "Выбрать", "Отмена");
	else D(playerid, D_MP, DSL, "МЕРОПРИЯТИЕ", "1. Удалить телепорт\n2. Раздать оружие\n3. Раздать жизнь\n4. Раздать броню\n5. Обезоружить всех\n6. Забрать броню", "Выбрать", "Отмена");
    return 1;
}