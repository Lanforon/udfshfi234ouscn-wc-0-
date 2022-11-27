new BizWarTime[2] = 0,
	BizHourTime = 0,
	Text:Bizwar[3],
	biz_war_gangzone = - 1,
	war_gangzone = - 1;

#define MOROZ_LCN 5
#define MOROZ_YAKUZA 6
#define MOROZ_RM 7
new gBankMafia[3][MAX_BUSINESS_COUNT];

enum MzoneInfo {
	bFrakVlad,
	bNapad,
	bBiz,
	bCountDead[18]
}
new Float:mafia_zone[3][4] = {
	{351.314666, 2455.576416, 439.314666, 2551.576416},//аэро
	{393.8914,983.9361, 324.6188,833.3795},//карьер
	{-789.8281,2015.9144, -662.7654,2083.9297}//дамба
};
new MZInfo[MzoneInfo];
stock GetMN(fraca) {
	new mafianame[28];
	switch(fraca) {
		case fYAKUZA: mafianame = "Japan Mafia";
		case fRM: mafianame = "Russian Mafia";
		case fLCN: mafianame = "Italian Mafia";
	}
	return mafianame;
}
stock MafiaTimeCapture(faction, MafiaNapadss) {
	SendFamilyMessage(faction, 0xFF0000FF, "Внимание, стрела началась!");
    SendFamilyMessage(MafiaNapadss, 0xFF0000FF, "Внимание, стрела началась!");
	BizWarTime[0] = 0;
	BizWarTime[1] = 60*10;
	return true;
}
BizWarTimer() {
	if(BizWarTime[1] > 0) {
		BizWarTime[1]--;
		new kv1,kv2;
		foreach(new playerid:Player) {
			if(GetPVarInt(playerid,"ppkz2") && !IsAMafia(playerid)) EndBizwar(playerid);
			if(MZInfo[bFrakVlad]!=PI[playerid][pMember] && MZInfo[bNapad] != PI[playerid][pMember]) continue;
			if(PlayerToKvadrat(playerid, mafia_zone[war_gangzone][0], mafia_zone[war_gangzone][1],mafia_zone[war_gangzone][2],mafia_zone[war_gangzone][3])) {
				if(MZInfo[bFrakVlad] == PI[playerid][pMember]) kv1++;
				else kv2++;
			}
		}
		foreach(new m:Player) {
			new string[128];
			if(GetPVarInt(m,"ppkz2") && !IsAMafia(m)) EndBizwar(m);
			if(MZInfo[bFrakVlad]!=PI[m][pMember] && MZInfo[bNapad] != PI[m][pMember]) continue;
			if(!GetPVarInt(m,"ppkz2")) {
				GangZoneFlashForPlayer(m,biz_war_gangzone,gFractionSpawn[MZInfo[bNapad]][fracColor]);
				TextDrawShowForPlayer(m, Bizwar[0]);
				format(string,50,"~w~Time: ~g~%s",date("%ii:%ss",BizWarTime[1]));
				TextDrawSetString(Bizwar[0],string);
				format(string,50,"~w~%s ~g~0 ~w~Kills: ~g~0",GetMN(MZInfo[bFrakVlad]));
				TextDrawSetString(Bizwar[1],string);
				TextDrawShowForPlayer(m, Bizwar[1]);
				format(string,50,"~w~%s ~g~0 ~w~Kills: ~g~0",GetMN(MZInfo[bNapad]));
				TextDrawSetString(Bizwar[2],string);
				TextDrawShowForPlayer(m, Bizwar[2]);
				SetPVarInt(m,"ppkz2",true);
			}
			else {
				format(string,50,"~w~Time: ~g~%s",date("%ii:%ss",BizWarTime[1]));
				TextDrawSetString(Bizwar[0],string);
				format(string,50,"~w~%s ~g~%d ~w~Kills: ~g~%d",GetMN(MZInfo[bFrakVlad]),kv1,MZInfo[bCountDead][MZInfo[bFrakVlad]]);
				TextDrawSetString(Bizwar[1],string);
				format(string,50,"~w~%s ~g~%d ~w~Kills: ~g~%d",GetMN(MZInfo[bNapad]),kv2,MZInfo[bCountDead][MZInfo[bNapad]]);
				TextDrawSetString(Bizwar[2],string);
			}
		}
		if(BizWarTime[1] == 1) {
			new mafianame[24];
			switch(MZInfo[bNapad]) {
				case fYAKUZA: mafianame = "Japan Mafia";
				case fRM: mafianame = "Russian Mafia";
				case fLCN: mafianame = "Italian Mafia";
			}
			new mafianamev[24],string[240];
			switch(MZInfo[bFrakVlad]) {
				case fYAKUZA: mafianamev = "Japan Mafia";
				case fRM: mafianamev = "Russian Mafia";
				case fLCN: mafianamev = "Italian Mafia";
			}
			if(MZInfo[bCountDead][MZInfo[bFrakVlad]] > MZInfo[bCountDead][MZInfo[bNapad]]) {
				format(string,sizeof(string), "%s не удалось отобрать у вас контроль над бизнесом %s. Бизнес отбит",GetMN(MZInfo[bNapad]),gBusiness[MZInfo[bBiz]][bizzName]);
				SendFamilyMessage(MZInfo[bFrakVlad], 0xFF0000FF, string);
				format(string,sizeof(string), "Вам не удалось отобрать у мафии %s котроль над бизнесом %s. Бизнес оставлен",GetMN(MZInfo[bFrakVlad]),gBusiness[MZInfo[bBiz]][bizzName]);
				SendFamilyMessage(MZInfo[bNapad], 0xFF0000FF, string);
			}
			else if(MZInfo[bCountDead][MZInfo[bFrakVlad]] == MZInfo[bCountDead][MZInfo[bNapad]]) {
				format(string,sizeof(string), "Стрела за бизнес %s закончилась ничьей. Бизнес потерян",gBusiness[MZInfo[bBiz]][bizzName]);
				SendFamilyMessage(MZInfo[bFrakVlad], 0xFF0000FF, string);
				format(string,sizeof(string), "Стрела за бизнес %s закончилась ничьей. Бизнес оставлен",gBusiness[MZInfo[bBiz]][bizzName]);
				SendFamilyMessage(MZInfo[bNapad], 0xFF0000FF, string);
				UpdateBusinessText(MZInfo[bBiz]);
			}
			else {
				format(string,sizeof(string), "%s забрала у вас контроль над бизнесом %s. Бизнес потерян",GetMN(MZInfo[bNapad]),gBusiness[MZInfo[bBiz]][bizzName]);
				SendFamilyMessage(MZInfo[bFrakVlad], 0xFF0000FF, string);
				format(string,sizeof(string), "Вы отобрали контроль над бизнесом %s у мафии %s. Бизнес захвачен",gBusiness[MZInfo[bBiz]][bizzName],GetMN(MZInfo[bFrakVlad]));
				SendFamilyMessage(MZInfo[bNapad], 0xFF0000FF, string);
				gBusiness[MZInfo[bBiz]][bizzMafia] = MZInfo[bNapad];
				UpdateBusinessData(MZInfo[bBiz]+1,"mafia",gBusiness[MZInfo[bBiz]][bizzMafia]);
				UpdateBusinessText(MZInfo[bBiz]);
			}
			new id_killed = -1;
			new max_killed = -1;
			foreach(new i:Player) {
				if(GetPVarInt(i,"killed_shot")) {
					if(GetPVarInt(i,"killed_shot")>max_killed) {
						max_killed = GetPVarInt(i,"killed_shot");
						id_killed = i;
					}
					DeletePVar(i,"killed_shot");
				}
			}
			foreach(new m:Player) {
				if(MZInfo[bFrakVlad]!=PI[m][pMember] && MZInfo[bNapad]!=PI[m][pMember]) continue;
				if(id_killed != -1 && max_killed != -1) {
					format(string,128,"Уничтожил больше всего противников "W"%s {E6251E}Убийств: "W"%i", player_name[id_killed],max_killed);
					SendClientMessage(m,0xE8FF1CFF,string);
				}
				EndBizwar(m);
			}
			MZInfo[bFrakVlad] = 0;
			MZInfo[bNapad] = 0;
			MZInfo[bBiz] = 255;

			GangZoneStopFlashForAll(biz_war_gangzone);
			GangZoneHideForAll(biz_war_gangzone);
			GangZoneDestroy(biz_war_gangzone);
			biz_war_gangzone = - 1;
			war_gangzone = - 1;

			BizWarTime[1] = 0;
			BizHourTime = 1;
			MZInfo[bCountDead][MZInfo[bNapad]] = 0;
			MZInfo[bCountDead][MZInfo[bFrakVlad]] = 0;
		}
	}
}
EndBizwar(m) {
	TextDrawHideForPlayer(m,Bizwar[0]);
	TextDrawHideForPlayer(m,Bizwar[1]);
	TextDrawHideForPlayer(m,Bizwar[2]);
	DeletePVar(m,"ppkz2");
	for(new num; num < 10; num++) SendDeathMessageToPlayer(m,6000,5005, 255);
}