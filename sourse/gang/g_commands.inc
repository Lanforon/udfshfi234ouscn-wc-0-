static giveplayerid;
CMD:capture(playerid, params[]) {
	if(sscanf(params,"i",giveplayerid)) return SendEsp(playerid,"/capture [тип захвата (1 - по киллам | 2 - по мясу)]");
	if(giveplayerid != 1 && giveplayerid != 2) return SendEsp(playerid,"/capture [тип захвата (1 - по киллам | 2 - по мясу)]");
	if(zahvat == true) return ErrorMessage(playerid, "В данный момент идёт захват территории");
	if(!IsAGang(playerid)) return ErrorMessage(playerid, "Вам не доступна эта функция");
	if(PI[playerid][pRank] < 7) return ErrorMessage(playerid, "Доступно с 7 ранга");
	if(tmphour < 10 || tmphour > 23) return ErrorMessage(playerid, "Использовать команду можно только с 10:00 до 23:00");
	new string[244];
	if(CaptureTime > unix) {
		new year, month, day, hour, minute, second;
		timestamp_to_date(CaptureTime - unix, year, month, day, hour, minute, second);
		format(string,128,"Таймер до следующего захвата {AFAFAF}[%02d:%02d]", minute, second);
		ErrorMessage(playerid, string);
		return 1;
	}
	new gang1 = -1;
	switch(PI[playerid][pMember]) {
		case fBALLAS: gang1 = MOROZ_BALLAS;
		case fVAGOS: gang1 = MOROZ_VAGOS;
		case fGROVE: gang1 = MOROZ_GROVE;
		case fAZTEC: gang1 = MOROZ_AZTECAS;
		case fRIFA: gang1 = MOROZ_RIFA;
	}
	if(gang1 != -1) {
		if(fracmoroz[gang1] > unix) {
			ErrorMessage(playerid,"Ваша банда заморожена");
			return 1;
		}
	}
	IDGZ[playerid] = GetIDGZ(playerid);
	if(IDGZ[playerid] != -1) {
		new i = IDGZ[playerid];
		if(PI[playerid][pMember] == GZInfo[i][gFrakVlad]) return ErrorMessage(playerid,"Вы не можете захватить собственную территорию");
		if(i == 90 && black_prods[9] > unix) return ErrorMessage(playerid,"В данный момент борьба за чёрный рынок недоступна");
		if(!IsPlayerInBandOnline(GZInfo[i][gFrakVlad])) return ErrorMessage(playerid, "Банда на которую вы собираетесь напасть нет в сети / Меньше трёх человек");

		new gang = -1;

		switch(GZInfo[i][gFrakVlad]) {
			case fBALLAS: gang = MOROZ_BALLAS;
			case fVAGOS: gang = MOROZ_VAGOS;
			case fGROVE: gang = MOROZ_GROVE;
			case fAZTEC: gang = MOROZ_AZTECAS;
			case fRIFA: gang = MOROZ_RIFA;
		}
		if(gang != -1) {
			if(fracmoroz[gang] > unix) {
				ErrorMessage(playerid,"Банду которую вы хотите захватить невозможно");
				ErrorMessage(playerid,"Она заморожена администратором, ожидайте сообщения в чате когда заморозка будет снята");
				return 1;
			}
		}
		new attemptslot= -1;
		switch(PI[playerid][pMember]) {
			case fVAGOS: attemptslot = 0;
			case fBALLAS: attemptslot = 1;
			case fGROVE: attemptslot = 2;
			case fRIFA: attemptslot = 3;
			case fAZTEC: attemptslot = 4;
		}
		if(attemptslot != -1) {
			if(CaptureAttempt[attemptslot] >= MAX_ATTEMPT_GANG) {
				format(string, 128, "Ваша банда уже воевала более %i раз", MAX_ATTEMPT_GANG);
				ErrorMessage(playerid, string);
				return 1;
			}
		}
		format(string, sizeof(string), ""W"Данная территория принадлежит банде {%06x}%s\n\n"BLUE"\tВы согласны начать её захват?",gFractionSpawn[GZInfo[i][gFrakVlad]][fracColor] >>> 8,FI[GZInfo[i][gFrakVlad]][fName]);
		D(playerid, D_CAPTURE, DSM,"Захват территории", string, "Согласен", "Отмена");
		SetPVarInt(playerid, "TypeBattle", giveplayerid);
		SetPVarInt(playerid, "capture_gz_id", i);
		return 1;
	}
	else ErrorMessage(playerid, "Необходимо находится на территории которую хотите завоевать");
	return 1;
}
CMD:sklad(playerid, params[]) {
	if((!IsAGang(playerid) && !IsAMafia(playerid)) || PI[playerid][pRank] < FI[GetTeamID(playerid)][fInviteRang]) return ErrorMessage(playerid,"Вам недоступна данная команда");
	new str[9];
	if(FI[GetTeamID(playerid)][fSklad] == 0) FI[GetTeamID(playerid)][fSklad] = 1,str = "открыл";
	else FI[GetTeamID(playerid)][fSklad] = 0,str = "закрыл";
	static const f_str[] = "[F] %s[%d] %s(а) склад";
	new string[sizeof(f_str) +1 + (-2 + MAX_PLAYER_NAME) + (-2 + 4) + (-2 + 9)];

	format(string,sizeof(string),f_str,player_name[playerid],playerid,str);
	SendFamilyMessage(PI[playerid][pMember],0x6ab1ffaaff,string);
	UpdateFraction(GetTeamID(playerid),"Sklad",FI[GetTeamID(playerid)][fSklad]);
	return 1;
}
CMD:sellgun(playerid,params[]) {
    new weapname[24];
    if(!IsAGang(playerid)) return ErrorMessage(playerid,"Вы не бандит");
	if(sscanf(params,"udd",giveplayerid,params[1],params[2])) return SendEsp(playerid,"/sellgun [id игрока] [к-во патронов] [цена]");
	if(!IsPlayerConnected(giveplayerid) || giveplayerid == playerid) return ErrorMessage(playerid,not_id);
	if(GetPlayerDistanceToPlayer(playerid,giveplayerid) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(giveplayerid)) return ErrorMessage(playerid,"Вы далеко друг от друга");
	if(params[2] > 10000 || params[2] < 1) return ErrorMessage(playerid,"Цена должна быть от $1 до $10.000");
	if(params[1] > 100 || params[1] < 1) return ErrorMessage(playerid,"От 1 до 100 патрон");
	if(!GetPlayerWeapon(playerid)) return ErrorMessage(playerid,"Возьмите в руку то оружие, которое хотите продать");
	if(GetPlayerAmmo(playerid) < params[1]) return ErrorMessage(playerid,"У Вас недостаточно патронов");
	new id = GetIDGZ(playerid);
	if(PI[playerid][pMember] != GZInfo[id][gFrakVlad]) return ErrorMessage(playerid,"Продавать оружие можно только на своей территории");


	SetPVarInt(playerid,"gunoffee",giveplayerid);
	SetPVarInt(giveplayerid,"gunoffee",giveplayerid);
	SetPVarInt(giveplayerid,"gunoffer",playerid);
	SetPVarInt(giveplayerid,"gunprice",params[2]);
	SetPVarInt(giveplayerid,"gunammo",params[1]);
	SetPVarInt(giveplayerid,"gunid",GetPlayerWeapon(playerid));
	GetWeaponName(GetPlayerWeapon(playerid),weapname,24);

	new string[325];
	format(string, sizeof(string), "Вы предложили "W"%s"BLUE" купить "W"%s"BLUE" за "GREEN"$%d."BLUE" Патронов: "W"%d",player_name[giveplayerid],weapname,params[2],params[1]);
	SendClientMessage(playerid, COLOR_BLUE, string);
	format(string, sizeof(string), ""W"%s"BLUE" предложил Вам купить "W"%s"BLUE" за "GREEN"$%d."BLUE" Патронов: "W"%d",player_name[playerid],weapname,params[2],params[1]);
	SendClientMessage(giveplayerid, COLOR_BLUE, string);
	SendClientMessage(giveplayerid,COLOR_BLUE,"Нажмите "YES"Y "BLUE"чтобы согласиться "NO"N "BLUE"для отказа");
	return true;
}
CMD:bmarket(playerid) {
	if(!IsAGang(playerid) && PI[playerid][pRank] < FI[GetTeamID(playerid)][fInviteRang]) return ErrorMessage(playerid,"Вам недоступна данная команда");
	if(black_prods[0] != GetTeamID(playerid)) return ErrorMessage(playerid,"Чёрный рынок крышует другая банда");
	static const f_str[] = "Наименование\tЦена\tСклад\n\
							Наркотики\t%d\t%d\n\
							Боеприпасы\t%d\t%d\n\
							Бронежелет\t%d\t%d\n\
							Армейская форма\t%d\t%d\n";
	new string[sizeof(f_str) +2 + (-2 + 5) + (-2 + 5) + (-2 + 5) + (-2 + 5) + (-2 + 5) + (-2 + 5) + (-2 + 5) + (-2 + 5)];
	format(string,sizeof(string),f_str,black_prods[5],black_prods[1],black_prods[6],black_prods[2],black_prods[7],black_prods[3],black_prods[8],black_prods[4]);
	D(playerid,D_BLACK_MARKET,DSTH,"Чёрный рынок",string,"Выбрать","Отмена");
	return 1;
}
ALT:bandchat:bc;
CMD:bandchat(playerid, params[]) {
	if(!IsAGang(playerid)) return ErrorMessage(playerid,"Вы не бандит");
	if(PI[playerid][pRank] < FI[GetTeamID(playerid)][fInviteRang]) return ErrorMessage(playerid,"Вам недоступна данная команда");
	if(isnull(params) || strlen(params) > 100) return SendEsp(playerid, "/bc [текст]");
	if(PI[playerid][pMute] > 0) return ErrorMessage(playerid, "У Вас бан чата");
	if(GetPVarInt(playerid,"gag")) return ErrorMessage(playerid, "У Вас кляп");
	new string[144];
	format(string, sizeof(string), "[BC] {%06x}%s "W"%s[%d]: %s", gFractionSpawn[PI[playerid][pMember]][fracColor] >>> 8,FI[PI[playerid][pMember]][fName],player_name[playerid],playerid, params);
	SendBand(COLOR_RED, string);
	return 1;
}
CMD:sellzone(playerid,params[]) {
	IDGZ[playerid] = GetIDGZ(playerid);
	if(IDGZ[playerid] != -1) {
		new i = IDGZ[playerid];
		if(PI[playerid][pLeader] != GZInfo[i][gFrakVlad]) return ErrorMessage(playerid, "Вы не на своей территории");
		else if(sscanf(params,"dd",giveplayerid,params[1])) return SendEsp(playerid, "/sellzone [id] [цена]");
		else if(params[1] < 10000 || params[1] > 100000) return ErrorMessage(playerid, "Цена должна быть: от 10000 до 100000");
		else if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid, not_id);
		else if(!IsPlayerStream(5.0, playerid, giveplayerid)) return ErrorMessage(playerid, "Вы далеко от этого человека");
		else if(giveplayerid == playerid) return ErrorMessage(playerid, "Эта итак Ваша территория");

		new string[325];
		format(string, sizeof(string), "Вы предложили "W"%s"BLUE" купить территорию за "GREEN"$%d",player_name[giveplayerid],params[1]);
		SendClientMessage(playerid, COLOR_BLUE, string);
		format(string, sizeof(string), ""W"%s"BLUE" предложил Вам купить территорию за за "GREEN"$%d",player_name[playerid],params[1]);
		SendClientMessage(giveplayerid, COLOR_BLUE, string);
		SendClientMessage(giveplayerid,COLOR_BLUE,"Нажмите "YES"Y "BLUE"чтобы согласиться "NO"N "BLUE"для отказа");

		SetPVarInt(giveplayerid,"ZoneOffer", playerid + 1);
		SetPVarInt(giveplayerid,"ZonePrice", params[1]);
		SetPVarInt(giveplayerid,"sellzone", PI[playerid][pMember]);
	}
	return 1;
}