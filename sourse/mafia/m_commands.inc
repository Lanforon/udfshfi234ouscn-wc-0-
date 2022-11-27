static giveplayerid;
CMD:bizwar(playerid) {
	if(!IsAMafia(playerid)) return ErrorMessage(playerid, "Вы не мафиози");
	if(PI[playerid][pRank] < 7) return ErrorMessage(playerid, "Вам не доступна данная команда");
	if(BizWarTime[0] > 0 || BizWarTime[1] > 0) return ErrorMessage(playerid, "Война за бизнес уже идет");
	if(BizHourTime > 0) return ErrorMessage(playerid, "Стрелы за бизнес проходят 1 раз в 30 минут");
	if(tmphour < 12 || tmphour > 20) return ErrorMessage(playerid, "Использовать команду можно только с 12:00 до 20:00");
	new gang1 = -1;
	switch(PI[playerid][pMember]) {
		case fLCN: gang1 = MOROZ_LCN;
		case fYAKUZA: gang1 = MOROZ_YAKUZA;
		case fRM: gang1 = MOROZ_RM;
	}
	if(gang1 != -1) {
		if(fracmoroz[gang1] > unix) return ErrorMessage(playerid, "Ваша мафия не может принимать участия в войнах. (заморожена администратором)");
	}
	for(new h;h<gBusinessCount;h++) {
		if(!IsPlayerInRangeOfPoint(playerid,3,gBusiness[h][bizzX], gBusiness[h][bizzY], gBusiness[h][bizzZ])) continue;
		new gang = -1;
		switch(gBusiness[h][bizzMafia]) {
			case fLCN: gang = MOROZ_LCN;
			case fYAKUZA: gang = MOROZ_YAKUZA;
			case fRM: gang = MOROZ_RM;
		}
		if(gang != -1) {
			if(fracmoroz[gang] > unix) return ErrorMessage(playerid, "Мафия, которой Вы хотите забить стрелу не может принимать участия в войнах. (заморожена администратором)");
		}
		if(gBusiness[h][bizzMafia] == PI[playerid][pMember]) return ErrorMessage(playerid, "Этот бизнес под крышей Вашей мафии");
		if(gBusiness[h][bizzMafia] <= 0) {
			gBusiness[h][bizzMafia] = PI[playerid][pMember];
			UpdateBusinessData(h+1,"mafia",gBusiness[h][bizzMafia]);
			UpdateBusinessText(h);
			SendClientMessage(playerid, COLOR_BLUE, "Бизнес взят под крышу Вашей мафии");
			return 1;
		}
		else {
			new string[156];
			format(string, sizeof(string), ""W"Данный бизнес "GREEN"%s"W" принадлежит {%06x}%s\n\n"BLUE"\tВы согласны начать захват бизнеса?",gBusiness[h][bizzName], gFractionSpawn[gBusiness[h][bizzMafia]][fracColor] >>> 8,GetMN(gBusiness[h][bizzMafia]));
			if(IsPlayerInBandOnline(gBusiness[h][bizzMafia]) < 2) return ErrorMessage(playerid,"Мафия на которую вы собираетесь напасть нет в сети");
			D(playerid,D_BIZWAR,DIALOG_STYLE_MSGBOX,"{FFCD00}Атака бизнеса",string,"Да","Нет");
			SetPVarInt(playerid, "bizwar_id", h);
			return 1;
		}
	}
	return ErrorMessage(playerid, "Необходимо находиться рядом с бизнесом");
}
CMD:bizlist(playerid, params[]) {
	if(!IsAMafia(playerid)) return ErrorMessage(playerid, "Вы не мафиози");
	new count_business = 1,string[5000];
	string = "№. Название + Доход бизнеса за сегодня\n\n";
	new fracid = -1;
	switch(PI[playerid][pMember]) {
		case fLCN:fracid = 0;
		case fYAKUZA:fracid = 1;
		case fRM:fracid = 2;
	}
	for(new i; i<gBusinessCount; i++) {
		if(gBusiness[i][bizzMafia] != PI[playerid][pMember]) continue;
		if(fracid != -1) {
			if(count_business > 50) break;
			format(string, sizeof(string), ""W"%s%i. %s + "GREEN"$%d\n",string, count_business, gBusiness[i][bizzName],gBankMafia[fracid][i]);
			count_business++;
		}
	}
	if(count_business < 50) D(playerid, DIALOG_NONE, DSM, "Бизнесы мафии", string, "Закрыть", "");
	else D(playerid, dBizList, DSM, "Бизнесы мафии", string, "Далее", "Закрыть");
	return 1;
}
CMD:tie(playerid,params[]) {
	if(sscanf(params,"d",giveplayerid)) return SendEsp(playerid, "/tie [id]");
	if(!IsAMafia(playerid)) return ErrorMessage(playerid, "Вам недоступна данная команда");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ErrorMessage(playerid,"Вы не водитель");
	if(GetPVarInt(playerid,"PlayerTied"))  return ErrorMessage(playerid, "Вы связаны");
	if(GetPVarInt(giveplayerid,"PlayerTied")) return ErrorMessage(playerid, "Игрок уже связан");
	if (!IsPlayerStream(5.0, playerid, giveplayerid)) return ErrorMessage(playerid, "Игрок далеко от Вас");
	if(giveplayerid == playerid) return ErrorMessage(playerid,not_id);
	if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != 2 && !IsPlayerInVehicle(giveplayerid, GetPlayerVehicleID(playerid))) return ErrorMessage(playerid, "Игрок не в машине");
	new string[128];
	format(string, sizeof(string), "достал веревку и завязал %s на узел", player_name[giveplayerid]);
	MeAction(playerid,string, 5.0);
	TogglePlayerControllable(giveplayerid, 0);
	SetPVarInt(giveplayerid,"PlayerTied", true);
	return 1;
}
CMD:untie(playerid,params[]) {
	if(sscanf(params,"d",giveplayerid)) return SendClientMessage(playerid, CWHITE, "Используйте: /untie [id]");
	else if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid,not_id);
	else if(!IsPlayerStream(5.0, playerid, giveplayerid)) return ErrorMessage(playerid, "Игрок далеко от Вас");
	else if(GetPVarInt(playerid,"PlayerTied"))  return ErrorMessage(playerid, "Вы связаны");
	else if(!GetPVarInt(giveplayerid,"PlayerTied")) return ErrorMessage(playerid, "Игрок не связан");
	else if(giveplayerid == playerid)  return ErrorMessage(playerid,not_id);
	new string[128];
	format(string, sizeof(string), "%s развязал %s", player_name[playerid] ,player_name[giveplayerid]);
	SendStreamMessage(30.0, playerid, string, 0xE75480FF);
	TogglePlayerControllable(giveplayerid, 1);
	DeletePVar(giveplayerid,"PlayerTied");
	return 1;
}
CMD:givephone(playerid,params[]) {
	if(!IsAMafia(playerid)) return ErrorMessage(playerid, "Вы не мафиози");
	else if(PI[playerid][pRank] < 3) return ErrorMessage(playerid, "Вам недоступна эта функция");
	else if(sscanf(params,"d",giveplayerid))return SendEsp(playerid, "/givephone [id]");
	else if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid, not_id);
	else if (!IsPlayerStream(5.0, playerid, giveplayerid)) return ErrorMessage(playerid, "Игрок далеко от Вас");
	else if(giveplayerid == playerid) return ErrorMessage(playerid, "Нельзя вернуть телефон самому себе");
	new string[128];
	format(string, sizeof(string), "%s вернул Вам телефон", player_name[playerid]);
	SendClientMessage(giveplayerid, 0x6ab1ffaa, string);
	DeletePVar(giveplayerid,"takephone");
	format(string, sizeof(string), "%s вернул телефон %s 'y", player_name[playerid] ,player_name[giveplayerid]);
	SendStreamMessage(30.0, playerid, string, 0xE75480FF);
	return 1;
}

CMD:takephone(playerid,params[]) {
	if(!IsAMafia(playerid)) return ErrorMessage(playerid, "Вы не мафиози");
	if(PI[playerid][pRank] < 3) return ErrorMessage(playerid, "Вам недоступна эта функция");
	if(sscanf(params,"d",giveplayerid))return SendEsp(playerid, "/takephone [id]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid, not_id);
	if(GetPVarInt(giveplayerid,"takephone") || !PI[giveplayerid][pPhone]) return ErrorMessage(playerid, "У него нет телефона");
	if(!IsPlayerStream(5.0, playerid, giveplayerid)) return ErrorMessage(playerid, "Игрок далеко от Вас");
	if(giveplayerid == playerid) return ErrorMessage(playerid, not_id);
	new string[128];
	format(string, sizeof(string), "%s забрал у Вас мобильный", player_name[playerid]);
	SendClientMessage(giveplayerid, 0x6ab1ffaa, string);
	SetPVarInt(giveplayerid,"takephone", true);
	format(string, sizeof(string), "%s забрал мобильный у %s", player_name[playerid] ,player_name[giveplayerid]);
	SendStreamMessage(30.0, playerid, string, 0xE75480FF);
	return 1;
}
CMD:gag(playerid,params[]) {
	if(sscanf(params,"d",giveplayerid)) return SendEsp(playerid, "/gag [id]");
	if(!IsPlayerConnected(giveplayerid)) return ErrorMessage(playerid, not_id);
	if(giveplayerid == playerid) return ErrorMessage(playerid, not_id);
	if(!GetPVarInt(giveplayerid,"PlayerTied")) return ErrorMessage(playerid, "Игрок не связан");
	if(GetPVarInt(playerid,"PlayerTied")) return ErrorMessage(playerid, "Вы связаны");
	if(!IsPlayerStream(8.0, playerid, giveplayerid)) return ErrorMessage(playerid, "Игрок далеко от Вас");
	new string[128];
	if(GetPVarInt(giveplayerid,"gag")) {
		DeletePVar(giveplayerid,"gag");
		format(string, sizeof(string), "%s вытащил кляп у %s'a", player_name[playerid] ,player_name[giveplayerid]);
		SendStreamMessage(30.0, playerid, string, 0xE75480FF);
	}
	else {
		if(!IsAMafia(playerid)) return ErrorMessage(playerid, "Вам недоступна данная команда");
		SetPVarInt(giveplayerid,"gag", true);
		SetPVarInt(giveplayerid,"TieTime", 600);
		format(string, sizeof(string), "%s вставил кляп в рот %s'у", player_name[playerid] ,player_name[giveplayerid]);
		SendStreamMessage(30.0, playerid, string, 0xE75480FF);
	}
	return 1;
}