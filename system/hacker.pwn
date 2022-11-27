#if defined _hacker_inc
	#endinput
#endif
#define _hacker_inc
#define     NPC_HACKER                              208.7502,-225.6151,1.7786

new HackFlood[MAX_PLAYERS][6];

//public`s
hacker_OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if(PRESSED(KEY_WALK))
	{
		if(IsPlayerInRangeOfPoint(playerid,1.5, NPC_HACKER)) return NPC_HackD(playerid);
	}
	return 1;
}
hacker_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	switch(dialogid){
		case D_QUEST_HACKER:{
			if(!response) return 1;
			if(PI[playerid][QuestHacker][listitem]) return SCM(playerid, COLOR_GREY, "�� ��� ��������� ������ �������!");
			if(PI[playerid][QuestHacker][0] == listitem) return ShowQuestHacker(playerid, listitem+1);
			if(!PI[playerid][QuestHacker][listitem-1]) return SCM(playerid, COLOR_GREY, "�� �� ��������� ������� �������!");
			return ShowQuestHacker(playerid, listitem+1);
		}
		case D_QUEST_HACKER_1:{
			if(!response) return 1;
			SCM(playerid, COLOR_GRAY, "[�����]: �������! ����� ������������! ������� �� ����������� ��� ��� ��������.");
			SetPVarInt(playerid,"HackerQuest1", 1);
			SCM(playerid, COLOR_GRAY, "[�������]: ������� ������ �������� � ����������� ������������ (/hacker).");
			return 1;
		}
		case D_QUEST_HACKER_2:{
			if(!response) return 1;
			SCM(playerid, COLOR_GRAY, "[�����]: ��� � �������! ����� ������������. (/hacker)");
			SCM(playerid, COLOR_GRAY, "[�����]: �������������� ���������� ������ �� ���� GPS.");
			SetPVarInt(playerid,"HackerQuest2", 1);
			EnableGPSForPlayer(playerid, 1462.8285,-775.3546,92.8073);
		}
		case D_QUEST_HACKER_3:{
			if(!response) return 1;
			SPD(playerid, D_QUEST_CLEAR, DIALOG_STYLE_INPUT, "/hacker",""W"������� ID ������ �������� ������ ���������� �� "R"�������"W":",">>>","x");
		}
		case D_QUEST_HACKER_3_1:{
			if(!response) return 1;
			if(!IsAWanteds()) return SCM(playerid, COLOR_GREY, "[�������]: � ������� ���� ������ ���. ������� ����� ������� ���� ���� �����.");
			SCM(playerid, COLOR_GREY, "[�����]: � � ���� �� ����������! ����� ������������. (/hacker)");
			SCM(playerid, COLOR_GREY, "[�����]: �������������� � ���� ������ �� ���� GPS.");
			EnableGPSForPlayer(playerid, 1643.3060,-1681.9083,21.4215);
			SetPVarInt(playerid, "HackerQuest3", 1);
		}
		case D_QUEST_HACKER_4:{
			if(!response) return 1;
			SCM(playerid, COLOR_GREY, "[�����]: �������� ���� ����. ����� ������������. (/hacker)");
			SCM(playerid, COLOR_GREY, "[�����]: �������������� � ���� ������ �� ���� GPS.");
			SCM(playerid, COLOR_RED,  "[�����]: ��� ������� ��� �� �������� ���� ��������...");
			EnableGPSForPlayer(playerid, 1395.3621,-1787.1383,13.5469);
			SetPVarInt(playerid, "HackerQuest4", 1);
		}
		case D_QUEST_CLEAR:{
			if(!response) return 1;
			new ID = strval(inputtext);
			if(!IsPlayerConnected(ID)) return SCM(playerid, COLOR_GRAY, "����� �� � ����!");
			if(!TI[ID][tLogin]) return SCM(playerid, COLOR_RED, "����� �� ����������� �� �������!");
			if(!PI[ID][pSearch]) return SCM(playerid, COLOR_GREY, "����� �� � �������");
			if(PI[ID][pSearch] > 2) return SCM(playerid, COLOR_GREY, "�� �� ������ ������� ������ ������ ���� ����!");
			SetPVarInt(playerid, "WantedID", ID);
			JobTempProcess[playerid] = 31;
			TI[playerid][tProcess][0] = 0;
			TI[playerid][tProcess][1] = 10;
			PlayerTextDrawColor(playerid, YandNsysTDPlayer[playerid][1], -1);
			for(new YN = 0;YN < 3;YN++) {
				TextDrawShowForPlayer(playerid, YandNsysTD[YN]);
				if(YN < 2) PlayerTextDrawShow(playerid,YandNsysTDPlayer[playerid][YN]);
			}
			RandomYareNforJOBS(playerid);

		}
		case D_MENU_HACKER_TEST:{
			if(!response) return 1;
			switch(listitem){
				case 0: if (!GetPVarInt(playerid, "HackerQuest1")) return SCM(playerid, COLOR_GREY, "��� �� �������� ������ ��������!"); else return StartHacker(playerid, 1);
				case 1: if (!GetPVarInt(playerid, "HackerQuest2")) return SCM(playerid, COLOR_GREY, "��� �� �������� ������ ��������!"); else return StartHacker(playerid, 2);
				case 2: if (!GetPVarInt(playerid, "HackerQuest3")) return SCM(playerid, COLOR_GREY, "��� �� �������� ������ ��������!"); else return StartHacker(playerid, 3);
				case 3: if (!GetPVarInt(playerid, "HackerQuest4")) return SCM(playerid, COLOR_GREY, "��� �� �������� ������ ��������!"); else return StartHacker(playerid, 4);
			}
			return 1;
		}
		case D_QUEST_HACKER_1_INPUT:{
			if(!response) return 1;
			new ID = strval(inputtext);
			if(ID == playerid) return SCM(playerid,COLOR_GRAY,"������ ��������� ���� ID!");
			if(!IsPlayerConnected(ID)) return SCM(playerid,COLOR_GRAY,"����� �� � ����");
			if(!TI[ID][tLogin]) return SCM(playerid, COLOR_RED, "����� �� ����������� �� �������!");
			new Float:X, Float:Y, Float:Z;
			GetPlayerPos(ID, X,Y,Z);
			if(!PlayerToPoint(15.0,playerid, X,Y,Z)) return SCM(playerid, COLOR_GRAY, "����� ������� ������! �� ������ ���� � ��� � ������� 15 ������!");
			ShowHackerStats(playerid, ID);
		}
		case D_MENU_HACKER:{
			if(!response) return 1;
			return System32Hacker(playerid, listitem+1);
		}
		case D_MENU_HACKER_ONE:
		{
			if(!response) return 1;
			if(HackFlood[playerid][0] > gettime()) return SCM(playerid, COLOR_RED, "������ ������� ����� ������������ ��� � ���."); 
			HackFlood[playerid][0] = gettime() + 3600;
			new IpD = strval(inputtext);
			if(!IsPlayerConnected(IpD)) return SCM(playerid, COLOR_RED, "����� �� � ����!");
			if(!TI[IpD][tLogin]) return SCM(playerid, COLOR_RED, "����� �� ����������� �� �������!");
			if(!PI[IpD][pPhone]) return SendClientMessage(playerid, COLOR_GREY, "� ��� ��� ��������");
			new Float:posXX, Float:PosYY, Float:posZZ;
			GetPlayerPos(IpD, posXX, PosYY, posZZ);
			if(!IsPlayerInRangeOfPoint(playerid,20.0,posXX,PosYY, posZZ)) 
				return SCM(playerid, COLOR_RED, "�� ������� ������ �� ������. ����� ������ ��������� � ������� �� 20.0 ������.");
			SetPVarInt(playerid, "PlayerID", IpD);
			ShowButton(playerid, 33);
			return 1;
		}
		case D_MENU_HACKER_TWO:{
			if(!response) return 1;
			if(HackFlood[playerid][1] > gettime()) return SCM(playerid, COLOR_RED, "������ ������� ����� ������������ ��� � 10 �����."); 
			HackFlood[playerid][1] = gettime() + 600;
			new IpD = strval(inputtext);
			if(!IsPlayerConnected(IpD)) return SCM(playerid, COLOR_RED, "����� �� � ����!");
			if(!TI[IpD][tLogin]) return SCM(playerid, COLOR_RED, "����� �� ����������� �� �������!");
			SetPVarInt(playerid, "PlayerID", IpD);
			ShowButton(playerid, 34);
		}
		case D_MENU_HACKER_THREE:{
			if(!response) return 1;
			return ShowButton(playerid, 35);
		}
		case D_MENU_HACKER_THREE_2:{
			if(!response) return 1;
			if(HackFlood[playerid][2] > gettime()) return SCM(playerid, COLOR_RED, "������ ������� ����� ������������ ��� � ���."); 
			HackFlood[playerid][2] = gettime() + 3600;
			//if(!inputtext) return SCM(playerid,COLOR_RED,"�� ������ �� ��������.");
			new string[150];
			format(string, sizeof(string), "[�����������][%d]: %s",playerid, inputtext);
			SendClientMessageToAll(0xf3E87D6ff, string);
			NextlvlHacker(playerid, 2);
			switch(random(3))
			{
				case 1: {
					PI[playerid][pSearch] = 3;
					UpdatePlayerData(playerid,"pSearch",PI[playerid][pSearch]);
					SetPlayerWantedLevel(playerid, PI[playerid][pSearch]);
					
				}
				default: {

				}
			}

			return 1;
			
			
		}
		case D_MENU_HACKER_FOUR:{
			if(!response) return 1;
			if(HackFlood[playerid][3] > gettime()) return SCM(playerid, COLOR_RED, "������ ������� ����� ������������ ��� � ���."); 
			HackFlood[playerid][3] = gettime() + 3600;
			new IpD = strval(inputtext);
			if(!IsPlayerConnected(IpD)) return SCM(playerid, COLOR_RED, "����� �� � ����!");
			if(!TI[IpD][tLogin]) return SCM(playerid, COLOR_RED, "����� �� ����������� �� �������!");
			if(PI[IpD][pJail] == 0 )  return SCM(playerid, COLOR_RED, "����� �� �������!");
	
			SetPVarInt(playerid, "PlayerID", IpD);
			ShowButton(playerid, 36);
		}
		case D_MENU_HACKER_FIVE:{
			if(!response) return 1;
			if(HackFlood[playerid][4] > gettime()) return SCM(playerid, COLOR_RED, "������ ������� ����� ������������ ��� � 15 �����."); 
			HackFlood[playerid][4] = gettime() + 900;
			return ShowButton(playerid, 37);
		}
		case D_MENU_HACKER_SIX:{
			return ShowButton(playerid, 38);
		}
		
	}
	return 1;
	
}
//
//stock`s
stock IsAWanteds()
{
	new num = 0;
	foreach(new i: Player)
	{
		if(PI[i][pSearch] < 3) num++;
	}
	return num;
}
stock DeleteHackerPVar(playerid, idx){
	if(GetPVarInt(playerid, "QuesR")) DeletePVar(playerid, "QuesR");
	switch(idx){
		case 1: if(GetPVarInt(playerid, "HackerQuest1")) DeletePVar(playerid, "HackerQuest1");
		case 2: {
			if(GetPVarInt(playerid, "HackerQuest2")) DeletePVar(playerid, "HackerQuest2");
			if(GetPVarInt(playerid, "HackPosX")){
				DeletePVar(playerid, "HackPosX");
				DeletePVar(playerid, "HackPosY");
				DeletePVar(playerid, "HackPosZ");
			}
			
		}
		case 3: {
				if(GetPVarInt(playerid, "HackerQuest3")) DeletePVar(playerid, "HackerQuest3");
				if(GetPVarInt(playerid, "WantedID")) DeletePVar(playerid, "WantedID");
			}
		case 4: if(GetPVarInt(playerid, "HackerQuest4")) DeletePVar(playerid, "HackerQuest4");
		default:{
			if(GetPVarInt(playerid, "HackerQuest1")) DeletePVar(playerid, "HackerQuest1");
			if(GetPVarInt(playerid, "HackerQuest2")) DeletePVar(playerid, "HackerQuest2");
			if(GetPVarInt(playerid, "HackerQuest3")) DeletePVar(playerid, "HackerQuest3");
			if(GetPVarInt(playerid, "HackerQuest4")) DeletePVar(playerid, "HackerQuest4");
			if(GetPVarInt(playerid, "HackPosX")){
				DeletePVar(playerid, "HackPosX");
				DeletePVar(playerid, "HackPosY");
				DeletePVar(playerid, "HackPosZ");
			}
			if(GetPVarInt(playerid, "WantedID")) DeletePVar(playerid, "WantedID");
		}
	}
	
}
stock ShowHackerStats(playerid, id){
	new str[128],string[1250];
	format(str,128,""W"���:\t\t\t\t%s",player_name[id]), strcat(string,str);
	format(str,128,"\n\n�������:\t\t\t%i",PI[id][pLevel]), strcat(string,str);

	format(str,128,"\n\n���:\t\t\t\t%s",(PI[id][pSex] == 1) ? ("�������") : ("�������")), strcat(string,str);
	format(str,128,"\n������(�):\t\t\t%s",PI[id][pMarried]), strcat(string,str);
	if(PI[id][pPhone] == 0) strcat(string,"\n\n����� ��������:\t\t�����������");
	else format(str,128,"\n\n����� ��������:\t\t%i",PI[id][pPhone]), strcat(string,str);
	format(str,128,"\n��������� ����:\t\t%i",PI[id][pMobile]), strcat(string,str);
	
	format(str,128,"\n\n������ �1:\t\t\t%s(%i)",gTransport[CarsInfo[id][carModel][0]-400][trName],CarsInfo[id][carModel][0]), strcat(string,str);
	format(str,128,"\n������ �2:\t\t\t%s(%i)",gTransport[CarsInfo[id][carModel][1]-400][trName],CarsInfo[id][carModel][1]), strcat(string,str);

	format(str,128,"\n������������:\t\t\t%i",PI[id][pCrimes]), strcat(string,str);
	format(str,128,"\n�������:\t\t\t%i",PI[id][pArrested]), strcat(string,str);
	format(str,128,"\n������� �������:\t\t%i",PI[id][pSearch]), strcat(string,str);
	if(PI[id][pMember]) format(str,128,"\n�����������:\t\t\t%s",FI[PI[id][pMember]][fName]), strcat(string,str);
	else strcat(string,"\n�����������:\t\t\t�����������");
	new house = 0;
	if(PI[id][pHouse] && !PI[id][pRoom]) {
		new classname[15];
		switch(gHouses[PI[id][pHouse]-1][houseClass]) {
		case 0: classname = "������";
		case 1: classname = "C������";
		case 2: classname = "�������";
		case 3: classname = "�������";
		}	
		format(str,128,"\n\n�����:\t\t\t��� �%d (%s)",gHouses[PI[id][pHouse]-1][houseID],classname), strcat(string,str);
		house = 1;
	}
	if(PI[id][pRoom] && !PI[id][pHouse]) {
		format(str,128,"\n\n�����:\t\t\t�������� � %d",PI[playerid][pRoom]), strcat(string,str);
		house = 1;
	}
	if(!house) strcat(string,"\n\n�����:\t\t\t\t���");
	
	if(PI[id][pBusiness]) format(str,128,"\n������:\t\t\t%s (%d)",gBusiness[PI[id][pBusiness]-1][bizzName],PI[id][pBusiness]), strcat(string,str);
	else strcat(string,"\n������:\t\t\t�����������");
	SetPVarInt(playerid, "QuesR", 1); 
	SCM(playerid, COLOR_GREY, "[�������]: ���������� � �������.");
	EnableGPSForPlayer(playerid, NPC_HACKER);
	return D(playerid,DIALOG_NONE,DSM, ""P"����������",string, "�������", "");
}
stock HackerCamera(playerid, idx)
{
	new Float:X,Float:Y,Float:Z;
	GetPlayerPos(playerid, X,Y,Z);
	SetPVarFloat(playerid, "HackPosX", X);
	SetPVarFloat(playerid, "HackPosY", Y);
	SetPVarFloat(playerid, "HackPosZ", Z);
	switch(idx)
	{
		case 1:{
			SetPlayerCameraPos(playerid, 1541.1815, -1651.5726, 26.5635);
			SetPlayerCameraLookAt(playerid, 1540.6473, -1652.4224, 26.2533);
			SetPlayerPos(playerid,1541.1815, -1651.5726, -4.5635);
			TogglePlayerControllable(playerid, 0);
			SetTimerEx("HackCamer",1000*5,false,"i",playerid);
			SCM(playerid, COLOR_GRAY, "[�����]: �������, �������� �������� ���������� ������.");
		}
		case 2:{
			SetPlayerCameraPos(playerid, 1480.5875, -1769.7512, 67.2575);
			SetPlayerCameraLookAt(playerid, 1480.6001, -1768.7527, 66.7675);
			SetPlayerPos(playerid,1480.6001, -1768.7527, 50.7675);
			TogglePlayerControllable(playerid, 0);
			PI[playerid][pSearch] = 2;
			UpdatePlayerData(playerid,"pSearch",PI[playerid][pSearch]);
			SetPlayerWantedLevel(playerid, PI[playerid][pSearch]);
			SetTimerEx("HackCamer",1000*5,false,"i",playerid);
			SCM(playerid, COLOR_GRAY, "[�����]: �������, � ��� � � �������...");
		}
	}
	
}
stock StartHacker(playerid, idx){
	switch(idx){
		case 1: return SPD(playerid, D_QUEST_HACKER_1_INPUT, DIALOG_STYLE_INPUT,"/hacker",""W"������� ID ������ � ������� ������ ������ ����������",">>>","x");
		case 2: {
			if(!IsPlayerInRangeOfPoint(playerid, 20.0, 1462.8285,-775.3546,92.8073)) return 1;
			JobTempProcess[playerid] = 29;
			TI[playerid][tProcess][0] = 0;
			TI[playerid][tProcess][1] = 10;
			PlayerTextDrawColor(playerid, YandNsysTDPlayer[playerid][1], -1);
			for(new YN = 0;YN < 3;YN++) {
				TextDrawShowForPlayer(playerid, YandNsysTD[YN]);
				if(YN < 2) PlayerTextDrawShow(playerid,YandNsysTDPlayer[playerid][YN]);
			}
			RandomYareNforJOBS(playerid);
			
		}
		case 3: {
			if(!IsPlayerInRangeOfPoint(playerid, 15.0, 1643.3060,-1681.9083,21.4215)) return 1;
			/**/
			JobTempProcess[playerid] = 30;
			TI[playerid][tProcess][0] = 0;
			TI[playerid][tProcess][1] = 10;
			PlayerTextDrawColor(playerid, YandNsysTDPlayer[playerid][1], -1);
			for(new YN = 0;YN < 3;YN++) {
				TextDrawShowForPlayer(playerid, YandNsysTD[YN]);
				if(YN < 2) PlayerTextDrawShow(playerid,YandNsysTDPlayer[playerid][YN]);
			}
			RandomYareNforJOBS(playerid);
			return 1;
		}
		case 4: {
			new vehicleid = GetPlayerVehicleID(playerid);
			if(VehicleInfo[vehicleid][vTeam] != fWHITEHOUSE) return SCM(playerid, COLOR_GRAY, "�� �� � ���������� �����.");
			JobTempProcess[playerid] = 32;
			TI[playerid][tProcess][0] = 0;
			TI[playerid][tProcess][1] = 10;
			PlayerTextDrawColor(playerid, YandNsysTDPlayer[playerid][1], -1);
			for(new YN = 0;YN < 3;YN++) {
				TextDrawShowForPlayer(playerid, YandNsysTD[YN]);
				if(YN < 2) PlayerTextDrawShow(playerid,YandNsysTDPlayer[playerid][YN]);
			}
			RandomYareNforJOBS(playerid);
			return 1;

		}
	}
	return 1;
}
stock SaveHacker(playerid, idx = false)
{
	new query[250];
	if(!idx){
		new Hacker[50];
		format(Hacker,sizeof(Hacker),"%i, %i, %i, %i",PI[playerid][QuestHacker][0], PI[playerid][QuestHacker][1], PI[playerid][QuestHacker][2], PI[playerid][QuestHacker][3]);
		mysql_format(connects, query, sizeof(query),"UPDATE `accounts` SET `pQuestHacker`= '%s' WHERE `Name` = '%s' LIMIT 1",Hacker,player_name[playerid]);
		mysql_tquery(connects,query);
		query[0] = EOS;

	}
	if(idx){
		mysql_format(connects, query, sizeof(query),"UPDATE `accounts` SET `pHackProg`= '%d' WHERE `Name` = '%s' LIMIT 1",PI[playerid][pHackProg],player_name[playerid]);
		mysql_tquery(connects, query);
		query[0] = EOS;
	}
	
	mysql_format(connects, query, sizeof(query),"UPDATE `accounts` SET `pHacker`= '%d' WHERE `Name` = '%s' LIMIT 1",PI[playerid][pHacker],player_name[playerid]);
	mysql_tquery(connects, query);
}
stock ShowQuestHacker(playerid, idx){
	switch(idx){
		case 1: SPD(playerid, D_QUEST_HACKER_1,DIALOG_STYLE_MSGBOX,"�����",""W"������, � ������ ��� �� ������ ����� �������.\n\
		� ���� ���� � ���� �����������, �� ��������� ���� � ����� ���������, � � ������� ���������� � ��������.\n\
		"R"��� ������ ���������, ��� � ��� ��������� �������, ������� ��� ������ ����.\n"GREEN"��������"W"?", ">>>","x");
		case 2: SPD(playerid, D_QUEST_HACKER_2,DIALOG_STYLE_MSGBOX,"�����",""W"������, ��� ����� ����� ���� ������.\n\
		����� �������� �� ����������, �������� ������ ������������.\n\
		����� ������, ���� ����� ���� ���.\n\
		"GREEN"��������"W"?", ">>>","x");
		case 3: SPD(playerid, D_QUEST_HACKER_3_1,DIALOG_STYLE_MSGBOX,"�����",""W"������\n\
		� ���� ����� ���������� �� GPS, �������� ���� � ���� ���� ����� �������� ���� ������ ���.\n\
		���-�� ��������� ������ ���� ������, �������� ���� ������ �� �������.\n\
		����� ������ ���� ����� ���� ���.\n\
		"GREEN"��������"W"?", ">>>","x");
		case 4: SPD(playerid, D_QUEST_HACKER_4, DIALOG_STYLE_MSGBOX, "�����", ""W"������, � ����� ��� ����� ��������� ����� ��� ������ ����.\n\
		"R"���� ����� ����� �������� � ����� ������ ������, ����� ������������ ����������� ������� ������� � ���� ���.\n\
		"W"����� ����� ��������� ������ � ����������� �����, ���������� � ���� �����.\n\
		"GREEN"��������?",">>>","x");
	}
	return 1;
}
stock ContinueQuest(playerid){
	SCM(playerid, COLOR_GREY, "�������, � � ���� �� ����������!");
	GiveMoney(playerid, 2500, "Quest Hacker #1");
	if(GetPVarInt(playerid, "HackerQuest1")) PI[playerid][QuestHacker][0] = 1, DeleteHackerPVar(playerid, 1);
	if(GetPVarInt(playerid, "HackerQuest2")) PI[playerid][QuestHacker][1] = 1, DeleteHackerPVar(playerid, 2);
	if(GetPVarInt(playerid, "HackerQuest3")) PI[playerid][QuestHacker][2] = 1, DeleteHackerPVar(playerid, 3);
	if(GetPVarInt(playerid, "HackerQuest4")) PI[playerid][QuestHacker][3] = 1, DeleteHackerPVar(playerid, 4), NextHacker(playerid);
	SaveHacker(playerid, false);
	
	return 1;
}
stock NPC_HackD(playerid){
	if(PI[playerid][QuestHacker][1] == 1 && PI[playerid][QuestHacker][0] == 1 &&
	PI[playerid][QuestHacker][2] == 1 && PI[playerid][QuestHacker][3] == 1) return SCM(playerid, COLOR_GRAY, "[�����]: ������, �� � ���� ��� ��� ���� ������ ������.");
	if(GetPVarInt(playerid, "QuesR")) return ContinueQuest(playerid);
	if(IsAGos(playerid)) return SCM(playerid,COLOR_GREY,"�� ���? ��� �� ����! �� �� ���� �����.");
	if(PI[playerid][pLevel] < 7) return SCM(playerid, COLOR_GREY, "� ��� ������� lvl. ������������ ������ ����� ����� � 7 lvl");
	if(GetPVarInt(playerid, "HackerQuest1") || GetPVarInt(playerid, "HackerQuest2") || 
	GetPVarInt(playerid, "HackerQuest3") || GetPVarInt(playerid, "HackerQuest4")) return SCM(playerid, COLOR_GREY, "[�����]: �� ��� ���?.");
	new str[300];
	format(str, sizeof(str), "��������\t\t������\n\
	1. ������ ���������� � ��������   \t [ %s"W" ]\n\
	2. �������� ������ ������������   \t [ %s"W" ]\n\
	3. �������� ���� ������ ���       \t [ %s"W" ]\n\
	4. ��������� � ������� ���. ������\t [ %s"W" ]", 

	PI[playerid][QuestHacker][0] == 0 ? ""R"�� ���������" : ""GREEN"���������",
	PI[playerid][QuestHacker][1] == 0 ? ""R"�� ���������" : ""GREEN"���������",
	PI[playerid][QuestHacker][2] == 0 ? ""R"�� ���������" : ""GREEN"���������",
	PI[playerid][QuestHacker][3] == 0 ? ""R"�� ���������" : ""GREEN"���������");
	return SPD(playerid, D_QUEST_HACKER, DIALOG_STYLE_TABLIST_HEADERS, "��������� ������", str, ">>>", "x");
}
stock ShowTestHacker(playerid){
	new str[300];
	format(str, sizeof(str), "��������\t\t������\n\
	1. ����������� ��������        \t [ %s"W" ]\n\
	2. ����� ������ ������������   \t [ %s"W" ]\n\
	3. ����� ���� ������ ���       \t [ %s"W" ]\n\
	4. ����� ���. ������           \t [ %s"W" ]",
	GetPVarInt(playerid, "HackerQuest1") == 1 ? ""GREEN"��������" : ""R"�� ��������",
	GetPVarInt(playerid, "HackerQuest2") == 1 ? ""GREEN"��������" : ""R"�� ��������",
	GetPVarInt(playerid, "HackerQuest3") == 1 ? ""GREEN"��������" : ""R"�� ��������",
	GetPVarInt(playerid, "HackerQuest4") == 1 ? ""GREEN"��������" : ""R"�� ��������");
	SPD(playerid, D_MENU_HACKER_TEST, DIALOG_STYLE_TABLIST_HEADERS, "���� ������", str, ">>>","x");
	return 1;
}
stock NextHacker(playerid){
	PI[playerid][pHacker] = 1;
	UpdatePlayerData(playerid,"pHacker",PI[playerid][pHacker]);
	return 1;
}
//
forward HackCamer(playerid);
public HackCamer(playerid){
	TogglePlayerControllable(playerid, 1);
	SetPlayerPosAC(playerid, GetPVarFloat(playerid, "HackPosX"),GetPVarFloat(playerid, "HackPosY"),GetPVarFloat(playerid, "HackPosZ"),0,0);
	SCM(playerid,COLOR_GRAY,"[�����]: ������ �� ������� �� ������ ��� ������������.");
	EnableGPSForPlayer(playerid,NPC_HACKER);
	SetPVarInt(playerid, "QuesR", 1); 
	SetCameraBehindPlayer(playerid);
}
CMD:sethacker(playerid, params[]){
	if(PI[playerid][pAdmin] < 7) return SCM(playerid, COLOR_RED, "��� �� �������� ������ �������");
	extract params -> new id, level;else return SCM(playerid, COLOR_WHITE,"�����������: /sethacker [id] [level]");
	if(!IsPlayerConnected(id)) return SCM(playerid, COLOR_GREY, "����� �� � ����!");
	if(!TI[id][tLogin]) return SCM(playerid, COLOR_RED, "����� �� ����������� �� �������!");
	PI[id][pHacker] = level;
	UpdatePlayerData(id, "pHacker", PI[id][pHacker]);
	new str[150];
	format(str, sizeof(str), "�� ������� ������ ������ %s %d hacker lvl", player_name[id], level);
	SCM(playerid, COLOR_YELLOW, str);
	str[0] = EOS;
	format(str, sizeof(str), "������������� %s ����� ��� %d hacker lvl", player_name[playerid], level);
	SCM(id, COLOR_RED, str);
	if(level == 0)
	{
		PI[id][QuestHacker][0] = 0;
		PI[id][QuestHacker][1] = 0;
		PI[id][QuestHacker][2] = 0;
		PI[id][QuestHacker][3] = 0;
		SaveHacker(id, false);
	}
	else{
		PI[id][QuestHacker][0] = 1;
		PI[id][QuestHacker][1] = 1;
		PI[id][QuestHacker][2] = 1;
		PI[id][QuestHacker][3] = 1;
		SaveHacker(id, false);
	}
	return 1;
}
CMD:hacker(playerid, params[]){
	if(IsACop(playerid)){
		extract params -> new id; else return SendClientMessage(playerid, COLOR_WHITE,"�����������: /hacker [id]");
		if(!IsPlayerConnected(id)) return SCM(playerid, COLOR_RED, "����� �� � ����!");
		if(!PI[playerid][pHacker]) return SCM(playerid, COLOR_RED, "����� �� �����!");
		return ShowStatsHacker(playerid, id);
	}
	if(IsAGos(playerid)) return SCM(playerid,COLOR_GREY,"��� �� �������� ������ �������!");
	if(PI[playerid][pLevel] < 7) return SCM(playerid, COLOR_GREY, "������ ������� ������������ ����� � 7 lvl");
	switch(PI[playerid][pHacker]){
		case 0: return ShowTestHacker(playerid);
		default: return ShowMenuHacker(playerid);
	}
	return 1;
}
stock ShowMenuHacker(playerid){
	new str[500];
	format(str, sizeof(str), "��������\t\t������\n\
	1. �������� �������            \t [ "GREEN"��������"W" ]\n\
	2. ������������ ������\t [ %s"W" ]\n\
	3. ����������� ���. �����      \t [ %s"W" ]\n\
	4. ��������� �������� �� ������\t [ %s"W" ]\n\
	5. �������� ���.���������      \t [ %s"W" ]\n\
	6. �������� ���� � �����       \t [ %s"W" ]",
	PI[playerid][pHacker] < 2 ? ""R"�������� ����� � 2 lvl Hacker" : ""GREEN"��������",
	PI[playerid][pHacker] < 3 ? ""R"�������� ����� � 3 lvl Hacker" : ""GREEN"��������",
	PI[playerid][pHacker] < 4 ? ""R"�������� ����� � 4 lvl Hacker" : ""GREEN"��������",
	PI[playerid][pHacker] < 5 ? ""R"�������� ����� � 5 lvl Hacker" : ""GREEN"��������",
	PI[playerid][pHacker] < 6 ? ""R"�������� ����� � 6 lvl Hacker" : ""GREEN"��������");
	SPD(playerid, D_MENU_HACKER, DIALOG_STYLE_TABLIST_HEADERS, "���� ������", str, ">>>","x");
	return 1;
}
stock System32Hacker(playerid, id){
	switch(id){
		case 1:{
			if(PI[playerid][pHacker] < 1) return SCM(playerid, COLOR_RED, "��� �� �������� ������ �������.");
			SPD(playerid, D_MENU_HACKER_ONE, DSI, "/hacker",""W"������� ID ������ ��� ������ ��������.",">>>","x");
		}
		case 2:{
			if(GetPVarInt(playerid, "HackReady")){
				DeletePVar(playerid, "HackReady");
				DeletePVar(playerid, "PlayerID");
				DisablePlayerCheckpoint(playerid);
				return SCM(playerid, COLOR_RED, "�� ������������� ����� ��������.");
			}
			if(PI[playerid][pHacker] < 2) return SCM(playerid, COLOR_RED, "��� �� �������� ������ �������.");
			SPD(playerid, D_MENU_HACKER_TWO, DSI, "/hacker",""W"������� ID ������ ��� ������������ � GPS.",">>>","x");
		}
		case 3:{
			if(PI[playerid][pHacker] < 3) return SCM(playerid, COLOR_RED, "��� �� �������� ������ �������.");
			SPD(playerid, D_MENU_HACKER_THREE, DSM, "/hacker",""W"�� ������������� ������ ����������� ���.�����?\n\
			���� ���� ��� �� ������ ��������� � ������.",">>>","x");
		}
		case 4:{
			if(PI[playerid][pHacker] < 4) return SCM(playerid, COLOR_RED, "��� �� �������� ������ �������.");
			SPD(playerid, D_MENU_HACKER_FOUR, DSI, "/hacker",""W"������� ID ������ �������� �� ������ ��������� �� ������.",">>>","x");
		}
		case 5:{
			if(PI[playerid][pHacker] < 5) return SCM(playerid, COLOR_RED, "��� �� �������� ������ �������.");
			if(!PI[playerid][pKeyCar]) return SCM(playerid, COLOR_RED, "� ��� ��� ����������� �������!");
			if(!GosCar(GetPlayerVehicleID(playerid))) return SCM(playerid,COLOR_RED,"�� �� � ��������������� ������!");
			SPD(playerid, D_MENU_HACKER_FIVE, DSM, "/hacker",""W"�� ������������� ������ ������������ ����������� �������?",">>>","x");
		}
		case 6:{
			if(PI[playerid][pHacker] < 6) return SCM(playerid, COLOR_RED, "��� �� �������� ������ �������.");
			SPD(playerid, D_MENU_HACKER_SIX, DSM, "/hacker",""W"�� ������������� ������ �������� ����?",">>>","x");
		}
	}
	return 1;
}
stock GosCar(vehicleid){
	switch(VehicleInfo[vehicleid][vTeam]){
		case fLSPD,fFBI,fRCSD,fMEDICLS,fMEDICSF,fMEDICLV,fARMYLS,fLSNEWS,fSFNEWS,fLVNEWS,fWHITEHOUSE: return 1;
	}
	return 0;
}
stock HideButton(playerid, id){
	switch(id){
		case 33:{
			new ID = GetPVarInt(playerid, "PlayerID");
			if(!IsPlayerConnected(ID)) return SCM(playerid, COLOR_RED, "����� ����� �� ����!");
			DeletePVar(playerid, "PlayerID");
			NextlvlHacker(playerid, 1);
			InsertPlayerHacker(playerid, "����� ��������");
			return GiveMoney(playerid, 5000, "����� ��������.");

		}
		case 34:{
			new ID = GetPVarInt(playerid, "PlayerID");
			if(!IsPlayerConnected(ID)) return SCM(playerid, COLOR_RED, "����� ����� �� ����!");
			SetPVarInt(playerid, "HackReady", 1);
			NextlvlHacker(playerid, 1);
			InsertPlayerHacker(playerid, "����� GPS");
			return 1;
		}
		case 35:{
			return SPD(playerid, D_MENU_HACKER_THREE_2, DIALOG_STYLE_INPUT, "/hacker","������� ����� ������� �� ������ ��������� � ���. �����.",">>>","x");
		}
		case 36:{
			new ID = GetPVarInt(playerid, "PlayerID");
			if(!IsPlayerConnected(ID)) return SCM(playerid, COLOR_RED, "����� ����� �� ����!");
			NextlvlHacker(playerid, 1);
			unarrest(ID);
			DeletePVar(playerid, "PlayerID");
			InsertPlayerHacker(playerid, "������������� ����� ������");
			return 1;
		}
		case 37:{
			new vehicleid = GetPlayerVehicleID(playerid);
			ToggleEngine(vehicleid, playerid);
			PI[playerid][pKeyCar] --;
			UpdatePlayerData(playerid,"pKeyCar", PI[playerid][pKeyCar]);
			SCM(playerid, COLOR_GREY, "�� ������� ������ ��������� � ������� ����������� ��������!");
			InsertPlayerHacker(playerid, "���� ���������������� ����������");
			SetPVarInt(playerid, "VehicleHackers", GetPlayerVehicleID(playerid));
			NextlvlHacker(playerid, 1);
		}
		case 38:{
			if(HackFlood[playerid][5] > gettime()) return SCM(playerid, COLOR_RED, "������ ������� ����� ������������ ��� � 6 �����."); 
			HackFlood[playerid][5] = gettime() + 21600;
			switch(random(3))
			{
				case 2:{
					PI[playerid][pSearch] = 4;
					UpdatePlayerData(playerid,"pSearch",PI[playerid][pSearch]);
					SetPlayerWantedLevel(playerid, PI[playerid][pSearch]);
					SCM(playerid, COLOR_RED, "[�������]: ��� ���� ������ 4 ������. ");
				}
				default:{ SCM(playerid, COLOR_RED, "[�����]: ����� ���� ��� �������� ��� ������ ������������."); }
			}
			GiveMoney(playerid, 150000, "Vzlom Bank");
			NextlvlHacker(playerid, 1);
			InsertPlayerHacker(playerid, "���������� �����");
			return 1;
		}
	}
	return 1;
}
hacker_OnGameModeInit() SetTimer("FindGPS",1000*5,true);

forward FindGPS();
public FindGPS(){
	foreach(Player, i){
		if(!GetPVarInt(i, "HackReady")) continue;
		new ID = GetPVarInt(i, "PlayerID");
		if(!IsPlayerConnected(i)){
			DeletePVar(i, "PlayerID");
			break;
		}
		if(!IsPlayerConnected(ID)) {
			DisablePlayerCheckpoint(i);
			DeletePVar(i, "PlayerID");
			SCM(i, COLOR_RED, "����� ����� �� ����!");
			break;

		}
		new Float:Xx, Float:Yy, Float:Zz;
		GetPlayerPos(ID, Xx,Yy,Zz);
		EnableGPSForPlayer(i, Xx, Yy, Zz);
	}
	return 1;
}
stock NextlvlHacker(playerid, count){
	PI[playerid][pHackProg]+=count;
	if(PI[playerid][pHackProg] > 19) {
		PI[playerid][pHacker] ++;
		UpdatePlayerData(playerid, "pHacker", PI[playerid][pHacker]);
		PI[playerid][pHackProg] = 0;
	}
	UpdatePlayerData(playerid, "pHackProg", PI[playerid][pHackProg]);
	new str[150];
	format(str, sizeof(str), "�� ���������� ������ ������ �������� %d/20", PI[playerid][pHackProg]);
	SCM(playerid, COLOR_YELLOW, str);
	return 1;
}
stock DeletePVarHack(playerid){
	if(GetPVarInt(playerid, "PlayerID")) DeletePVar(playerid, "PlayerID");
	if(GetPVarInt(playerid, "HackReady")) DeletePVar(playerid, "HackReady");
}
stock ShowButton(playerid, id){
	JobTempProcess[playerid] = id;
	TI[playerid][tProcess][0] = 0;
	TI[playerid][tProcess][1] = 10;
	PlayerTextDrawColor(playerid, YandNsysTDPlayer[playerid][1], -1);
	for(new YN = 0;YN < 3;YN++) {
		TextDrawShowForPlayer(playerid, YandNsysTD[YN]);
		if(YN < 2) PlayerTextDrawShow(playerid,YandNsysTDPlayer[playerid][YN]);
	}
	RandomYareNforJOBS(playerid);
	return 1;
}
stock unarrest(playerid){
	PI[playerid][pJail] = 0;
	PI[playerid][pJailTime] = 0;
	UpdatePlayerData(playerid,"pJail",PI[playerid][pJail]);
	UpdatePlayerData(playerid,"pJailTime",PI[playerid][pJailTime]);
	PI[playerid][pSearch] = 0;
	UpdatePlayerData(playerid,"pSearch",PI[playerid][pSearch]);
	SetPlayerWantedLevel(playerid, PI[playerid][pSearch]);
	PlayerSpawn(playerid);
	return 1;
}
stock ShowStatsHacker(playerid, targetid)
{
	new query[156];
	mysql_format(connects, query, sizeof(query),"SELECT * FROM `hacker_stats` WHERE `ID` = '%d'", PI[targetid][pID]);
	mysql_tquery(connects, query, "InfoHacker", "ii", playerid,targetid);
	return 1;
}
CB: InfoHacker(playerid, targetid){
	new rows,ing[1000]; 
	new dates[16], text[64];
	cache_get_row_count(rows);
	if(!rows) {
		Information(playerid, targetid, "����� � ��������� ����� ������ �� ��������.");
		return 1;
	}
	if(rows)
	{
		if(rows >= 8) {
			new query[128];
			mysql_format(connects, query, sizeof(query),"DELETE FROM `hacker_stats` WHERE `ID` = '%i';",PI[targetid][pID]);
			mysql_query(connects, query);
			for ( new i = 0 ; i < rows ; i ++ )
			{
				cache_get_value_name(i,"text", text,  64);
				cache_get_value_name(i,"date", dates, 16);
				format(ing, sizeof(ing),"%s\t"P"%d. "R"[%s]\t\t\t\t"GREEN"%s\n",ing,i+1,dates,text);
			}
			return 1;
		}
		for ( new i = 0 ; i < rows ; i ++ )
		{
			cache_get_value_name(i,"text", text,  64);
			cache_get_value_name(i,"date", dates, 16);
			format(ing, sizeof(ing),"%s\t"P"%d. "R"[%s]\t\t\t\t"GREEN"%s\n",ing,i+1,dates,text);
		}
	
	}
	Information(playerid, targetid, ing);
	return true;
}
stock Information(playerid, targetid, const text[])
{
	new title[35];
	format(title, sizeof(title), "����� %s", player_name[targetid]);
	new str[800], string[1250];
	format(str,128,""W"���:\t\t\t\t\t\t%s\n",player_name[targetid]), strcat(string,str);
	format(str,128,""W"������������������ ������ : \t\t%d/6\n",PI[targetid][pHacker]),strcat(string,str);
	strcat(string, ""W"��������� �������� ������:\n\n");
	format(str,800,"%s\n\n", text), strcat(string,str);
	SPD(playerid, dNull, DSM, title, string, ">>>","x");
	return 1;
}
stock InsertPlayerHacker(playerid, const text[]){
	MYSQL_GLOBAL[0] = EOS;
	mysql_format(connects, MYSQL_GLOBAL,sizeof(MYSQL_GLOBAL),"INSERT INTO `hacker_stats` (`ID`,`text`,`date`) VALUES ('%d','%s',NOW())",PI[playerid][pID],text);
	mysql_tquery(connects, MYSQL_GLOBAL, "","");
	return 1;
}