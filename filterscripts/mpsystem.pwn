/*
	FilterScript by - Timon
*/
#include <a_samp>
#include <foreach>
#include <sscanf2>

#define D_ADDMP           3578

#define NameServer        "[World RP]" // �������� �� �������� ������ �������
#define DontCreateMP      "[!] ������� �������� �����������."
#define MAX_MPCAR         20
#define MAX_TIMER         20

// ��������� ������  D_ADDMP+14

new TOTALMPCAR;
new CarMP[MAX_MPCAR];
new bool:CreateMP = false;
new bool:TeleportMP = false;
new Float:NameMP[100];
new Float:PrizMP[100];
new Float:PosMP[3];
new Count;
new Text3D:text3dmp;
new objectmp[2];


public OnFilterScriptInit()
{
	printf("\n\n\n\n----------------------------------\n\n\n** MP System ������� ��������...\n\n��������� ������� FS - Timon.\n\n\n----------------------------------\n\n\n\n");
	return true;
}

public OnFilterScriptExit()
{
	return true;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
	    case D_ADDMP:
	    {
		    if(response)
		    {
		    	switch(listitem)
				{
					case 0:
					{
					    if(CreateMP == true) return SendClientMessage(playerid, 0xAFAFAF, "������ ��������� ��������� ����������� �����.");
					    ShowPlayerDialog(playerid, D_ADDMP+1, DIALOG_STYLE_INPUT, "{9ACD32}� �������� �����������", "{FF0000}��������! {FFFF00}������: �����, 50 ��������\n\n{FFFFFF}������� �������� � ����:", "�������", "�����");
					}
					case 1:
					{
                        if(CreateMP == false) return SendClientMessage(playerid, 0xAFAFAF, DontCreateMP);
                        if(TeleportMP == true)
                        {
                            new name[50];
                            new strmsg[400];
							GetPlayerName(playerid, name, sizeof(name));
                            format(strmsg, 400, "{9ACD32}%s ������������� %s {FF0000}������{9ACD32} �������� �� ����������� %s.", NameServer, name, NameMP);
                            SendClientMessageToAll(0x9ACD32AA, strmsg);
							TeleportMP = false;
                        }
                        else
                        {
                            new name[50];
                            new strmsg[400];
							GetPlayerName(playerid, name, sizeof(name));
                            format(strmsg, 400, "{9ACD32}%s ������������� %s {00FF00}������{9ACD32} �������� �� ����������� %s.", NameServer, name, NameMP);
                            SendClientMessageToAll(0x9ACD32AA, strmsg);
                            SendClientMessageToAll(0xFF6347AA, "�������� �� ����������� || /gomp ");
                            TeleportMP = true;
                        }
                        DialogADDMP(playerid);
					}
					case 2:
					{
					    if(CreateMP == false) return SendClientMessage(playerid, 0xAFAFAF, DontCreateMP);
						new Float:PlayerPos[3];
						GetPlayerPos(playerid, PlayerPos[0], PlayerPos[1], PlayerPos[2]);
					    foreach(new i:Player)
						{
						    if(PlayerToPoint(50.0, i, PlayerPos[0], PlayerPos[1], PlayerPos[2]))
							{
							    SetPlayerHealth(i, 100);
	        					SetPlayerArmour(i, 0);
	        					SendClientMessage(i, 0xFF6347AA, "������������� ��������� ����: HP - 100 | Armour - 0");
							}
						}
						DialogADDMP(playerid);
					}
					case 3:
					{
					    if(CreateMP == false) return SendClientMessage(playerid, 0xAFAFAF, DontCreateMP);
					    ShowPlayerDialog(playerid, D_ADDMP+2, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} ������ ������ �������", "{FF0000}��������! {FFFF00}������: 24, 200 | (����: ���� � 200 ��������)\n\n{FFFFFF}������� ID ������ � ���-�� ������:", "������", "�����");
					}
					case 4:
					{
					    if(CreateMP == false) return SendClientMessage(playerid, 0xAFAFAF, DontCreateMP);
						new Float:PlayerPos[3];
						GetPlayerPos(playerid, PlayerPos[0], PlayerPos[1], PlayerPos[2]);
					    foreach(new i:Player)
						{
						    if(PlayerToPoint(50.0, i, PlayerPos[0], PlayerPos[1], PlayerPos[2]))
							{
								ResetPlayerWeapons(i);
	        					SendClientMessage(i, 0xFF6347AA, "������������� ������� � ���� ������.");
							}
						}
						DialogADDMP(playerid);
					}
					case 5:
					{
					    if(CreateMP == false) return SendClientMessage(playerid, 0xAFAFAF, DontCreateMP);
					    ShowPlayerDialog(playerid, D_ADDMP+3, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} �������� ������", "{FF0000}��������! {FFFF00}������: 522, 3, 9 | (����: NRG ������-�����)\n\n{FFFFFF}������� ID ������ � �����:", "����", "�����");
					}
					case 6:
					{
					    if(CreateMP == false) return SendClientMessage(playerid, 0xAFAFAF, DontCreateMP);
					    ShowPlayerDialog(playerid, D_ADDMP+6, DIALOG_STYLE_MSGBOX, "{9ACD32}�{FFFFFF} �������� ����", "{FFFF00}A{FFFFFF} - ������.\n{FFFF00}B{FFFFFF} - ���� (50m).", "A", "B");
					}
					case 7:
					{
					    if(CreateMP == false) return SendClientMessage(playerid, 0xAFAFAF, DontCreateMP);
					    ShowPlayerDialog(playerid, D_ADDMP+9, DIALOG_STYLE_MSGBOX, "{9ACD32}�{FFFFFF} ���������� ����\n", "{FFFF00}A{FFFFFF} - ������.\n{FFFF00}B{FFFFFF} - ���� (50m).", "A", "B");
					}
					case 8:
					{
					    if(CreateMP == false) return SendClientMessage(playerid, 0xAFAFAF, DontCreateMP);
					    ShowPlayerDialog(playerid, D_ADDMP+13, DIALOG_STYLE_MSGBOX, "{9ACD32}�{FFFFFF} ���������� �������\n", "������ ��������� - 50m.", "Freeze", "Unfreeze");
					}
					case 9:
					{
					    if(CreateMP == false) return SendClientMessage(playerid, 0xAFAFAF, DontCreateMP);
					    ShowPlayerDialog(playerid, D_ADDMP+14, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} ���� ������\n", "������� ����� �� ������� ������ �������� ������:", "������", "�����");
					}
					case 10:
					{
					    if(CreateMP == false) return SendClientMessage(playerid, 0xAFAFAF, DontCreateMP);
					    ShowPlayerDialog(playerid, D_ADDMP+4, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} �������� ����������", "������� ID ����������:", "����", "�����");
					}
					case 11:
					{
					    if(CreateMP == false) return SendClientMessage(playerid, 0xAFAFAF, DontCreateMP);
					    ShowPlayerDialog(playerid, D_ADDMP+5, DIALOG_STYLE_MSGBOX, "{9ACD32}�{FFFFFF} ������� �����������", "{FFFFFF}�� ������������� ������ {FF0000}�������{FFFFFF} ������ �����������?", "��", "�����");
					}
				}
			}
		}
		case D_ADDMP+1:
	    {
		    if(response)
		    {
		        if(sscanf(inputtext,"p<,>s[32]s[32]", NameMP, PrizMP)) return ShowPlayerDialog(playerid, D_ADDMP+1, DIALOG_STYLE_INPUT, "{9ACD32}� �������� �����������", "{FF0000}��������! {FFFF00}������: �����, 50 ��������\n\n{FFFFFF}������� �������� � ����:", "�������", "�����");
				new strmsg[300];
				new name[50];
				GetPlayerName(playerid, name, sizeof(name));
				format(strmsg, 300, "{9ACD32}%s ������� ����������� {FFFF00}%s{9ACD32} ��������������� %s. {FFFF00}����: %s{9ACD32}.", NameServer, NameMP, name, PrizMP);
				SendClientMessageToAll(0x9ACD32AA, strmsg);
				SendClientMessageToAll(0xFF6347AA, "�������� �� ����������� {00FF00}������{FF6347} || /gomp ");
				
				GetPlayerPos(playerid, PosMP[0], PosMP[1], PosMP[2]);

				TeleportMP = true;
				CreateMP = true;
				CreateText(playerid);
				
				DialogADDMP(playerid);
			}
			else return DialogADDMP(playerid);
		}
		case D_ADDMP+2:
	    {
		    if(response)
		    {
		        new gun;
		        new patr;
		        if(sscanf(inputtext,"p<,>ii", gun, patr)) return ShowPlayerDialog(playerid, D_ADDMP+2, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} ������ ������ �������", "{FF0000}��������! {FFFF00}������: 24, 200 | (����: ���� � 200 ��������)\n\n{FFFFFF}������� ID ������ � ���-�� ������:", "������", "�����");
				new Float:PlayerPos[3];
				GetPlayerPos(playerid, PlayerPos[0], PlayerPos[1], PlayerPos[2]);
			    foreach(new i:Player)
				{
				    if(PlayerToPoint(50.0, i, PlayerPos[0], PlayerPos[1], PlayerPos[2]))
					{
					    GivePlayerWeapon(i, gun, patr);
    					SendClientMessage(i, 0xFF6347AA, "������������� ����� ���� ������.");
					}
				}
				DialogADDMP(playerid);
			}
            else return DialogADDMP(playerid);
		}
		case D_ADDMP+3:
	    {
		    if(response)
		    {
		        new idveh, c1, c2;
          		new strmsg[200];
		        if(sscanf(inputtext,"p<,>iii", idveh, c1, c2)) return ShowPlayerDialog(playerid, D_ADDMP+3, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} �������� ������", "{FF0000}��������! {FFFF00}������: 522, 3, 9 | (����: NRG ������-�����)\n\n{FFFFFF}������� ID ������ � �����:", "����", "�����");
		        if(TOTALMPCAR == MAX_MPCAR) return SendClientMessage(playerid, 0xAFAFAFAA, "�� ������� ����������� ���-�� ����� ��� �����������."), DialogADDMP(playerid);
		        if(c1 > 255 || c1 < 0) return SendClientMessage(playerid, 0xAFAFAFAA, "ID ������ �� 0 �� 255."), ShowPlayerDialog(playerid, D_ADDMP+3, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} �������� ������", "{FF0000}��������! {FFFF00}������: 522, 3, 9 | (����: NRG ������-�����)\n\n{FFFFFF}������� ID ������ � �����:", "����", "�����");
				if(c2 > 255 || c2 < 0) return SendClientMessage(playerid, 0xAFAFAFAA, "ID ������ �� 0 �� 255."), ShowPlayerDialog(playerid, D_ADDMP+3, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} �������� ������", "{FF0000}��������! {FFFF00}������: 522, 3, 9 | (����: NRG ������-�����)\n\n{FFFFFF}������� ID ������ � �����:", "����", "�����");
				if(idveh > 611 || idveh < 400) return SendClientMessage(playerid, 0xAFAFAFAA, "ID ����� �� 400 �� 611."), ShowPlayerDialog(playerid, D_ADDMP+3, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} �������� ������", "{FF0000}��������! {FFFF00}������: 522, 3, 9 | (����: NRG ������-�����)\n\n{FFFFFF}������� ID ������ � �����:", "����", "�����");

                CreateMPCAR(playerid, idveh, c1, c2);
				format(strmsg, 450, "{9ACD32}%s ������ ������� ���������. �����: %d/19", NameServer, TOTALMPCAR);
                SendClientMessage(playerid, 0xFF6347AA, strmsg);

			}
            else return DialogADDMP(playerid);
		}
		case D_ADDMP+4:
	    {
		    if(response)
		    {
		        new idwin;
		        new name[50];
          		new strmsg[450];
          		new strmsg2[250];
		        if(sscanf(inputtext,"i", idwin)) return ShowPlayerDialog(playerid, D_ADDMP+4, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} �������� ����������", "������� ID ����������:", "����", "�����");
		        if(!IsPlayerConnected(idwin)) return SendClientMessage(playerid, 0xAFAFAFAA, "����� �� ������."), ShowPlayerDialog(playerid, D_ADDMP+4, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} �������� ����������", "������� ID ����������:", "����", "�����");
				GetPlayerName(idwin, name, sizeof(name));
                format(strmsg, 450, "{9ACD32}%s ����������� ����������� {FFFF00}%s{9ACD32} ����: {FFFF00}%s{9ACD32}.", NameServer, NameMP, name);
                SendClientMessageToAll(0x9ACD32AA, strmsg);
				format(strmsg2, 250, "{9ACD32}%s ::: ����: {FFFF00}%s{9ACD32}.", NameServer, PrizMP);
                SendClientMessageToAll(0x9ACD32AA, strmsg2);
                
                TeleportMP = false;
				CreateMP = false;
				DestroyMPCAR();
				Delete3DTextLabel(Text3D:text3dmp);
				
				DestroyMPCAR();
				DestroyObject(objectmp[0]);
				DestroyObject(objectmp[1]);
			}
            else return DialogADDMP(playerid);
		}
		case D_ADDMP+5:
	    {
		    if(response)
		    {
		        new name[50];
          		new strmsg[300];
				GetPlayerName(playerid, name, sizeof(name));
                format(strmsg, 300, "{9ACD32}%s ����������� %s ���� {FF0000}�������{9ACD32} ��������������� %s.", NameServer, NameMP, name);
                SendClientMessageToAll(0x9ACD32AA, strmsg);

                TeleportMP = false;
				CreateMP = false;
				DestroyMPCAR();
				Delete3DTextLabel(Text3D:text3dmp);
				
				DestroyMPCAR();
			}
            else return DialogADDMP(playerid);
		}
		case D_ADDMP+6:
	    {
		    if(response)
		    {
	     		ShowPlayerDialog(playerid, D_ADDMP+7, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} �������� ���� � ������", "{FF0000}��������! {FFFF00}������: 4, 245 | (����: ������ � ID 4 ���������� ���� 245)\n\n{FFFFFF}������� ID ������ � ID �����:", "����", "�����");
			}
            else
            {
                ShowPlayerDialog(playerid, D_ADDMP+8, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} �������� ���� � ���� (50m)", "{FF0000}��������! {FFFF00}������: 245 | (����: ������� � ������� 50m ���������� ���� 245)\n\n{FFFFFF}������� ID �����:", "����", "�����");
            }
		}
		case D_ADDMP+7:
	    {
		    if(response)
		    {
				new id, skin;
		        if(sscanf(inputtext,"p<,>ii", id, skin)) return ShowPlayerDialog(playerid, D_ADDMP+7, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} �������� ���� � ������", "{FF0000}��������! {FFFF00}������: 4, 245 | (����: ������ � ID 4 ���������� ���� 245)\n\n{FFFFFF}������� ID ������ � ID �����:", "����", "�����");
	            if(!IsPlayerConnected(id)) return SendClientMessage(playerid, 0xAFAFAFAA, "����� �� ������."), ShowPlayerDialog(playerid, D_ADDMP+7, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} �������� ���� � ������", "{FF0000}��������! {FFFF00}������: 4, 245 | (����: ������ � ID 4 ���������� ���� 245)\n\n{FFFFFF}������� ID ������ � ID �����:", "����", "�����");
	            if(skin > 299 || skin < 1) return SendClientMessage(playerid, 0xAFAFAFAA, "ID ������ �� 1 �� 299."), ShowPlayerDialog(playerid, D_ADDMP+7, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} �������� ���� � ������", "{FF0000}��������! {FFFF00}������: 4, 245 | (����: ������ � ID 4 ���������� ���� 245)\n\n{FFFFFF}������� ID ������ � ID �����:", "����", "�����");
				SetPlayerSkin(id, skin);
				SendClientMessage(id, 0x9ACD32AA, "������������� ������� ��� ����.");
				SendClientMessage(playerid, 0x9ACD32AA, "�� �������� ���� ������.");
			}
	        else return DialogADDMP(playerid);
		}
		case D_ADDMP+8:
	    {
		    if(response)
		    {
				new skin;
		        if(sscanf(inputtext,"i", skin)) return ShowPlayerDialog(playerid, D_ADDMP+8, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} �������� ���� � ���� (50m)", "FF0000}��������! {FFFF00}������: 245 | (����: ������� � ������� 50m ���������� ���� 245)\n\n{FFFFFF}������� ID �����:", "����", "�����");
	            if(skin > 299 || skin < 1) return SendClientMessage(playerid, 0xAFAFAFAA, "ID ������ �� 1 �� 299."), ShowPlayerDialog(playerid, D_ADDMP+8, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} �������� ���� � ���� (50m)", "{FF0000}��������! {FFFF00}������: 245 | (����: ������� � ������� 50m ���������� ���� 245)\n\n{FFFFFF}������� ID �����:", "����", "�����");
                new Float:PlayerPos[3];
				GetPlayerPos(playerid, PlayerPos[0], PlayerPos[1], PlayerPos[2]);
			    foreach(new i:Player)
				{
				    if(PlayerToPoint(50.0, i, PlayerPos[0], PlayerPos[1], PlayerPos[2]))
					{
					    SetPlayerSkin(i, skin);
						SendClientMessage(i, 0x9ACD32AA, "������������� ������� ���� ����.");
					}
				}
			}
	        else return DialogADDMP(playerid);
		}
		case D_ADDMP+9:
	    {
		    if(response)
		    {

                ShowPlayerDialog(playerid, D_ADDMP+10, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} ���������� ���� � ������", "������� ID ������:", "����", "�����");
			}
            else
            {
                new textclist[1500];
    			strcat(textclist, "{FFFF00}������\n{FFD700}�������\n{FFD1DC}���������-�������\n{FFA500}���������\n{FF7F50}����������\n{FF47CA}������ � ����\n{FF0000}�������\n{FF00FF}������\n{F28500}������������\n{000000}������\n{FFFFFF}�����\n{B2EC5D}��������\n{B0E0E6}������� �������\n");
    			strcat(textclist, "{B00000}��������\n{ADFF2F}������-������\n{ACE1AF}����-�������\n{A91D11}����������-���������\n{9D9101}����� ������\n{9ACD32}�����-�������\n{99FF99}���������\n{AFAFAF}�����\n{964B00}����������\n{8B00FF}����������\n{87CEEB}��������\n{0000FF}�����\n{00FF00}����\n");
				ShowPlayerDialog(playerid, D_ADDMP+11, DIALOG_STYLE_LIST, "{9ACD32}�{FFFFFF} ���������� ���� � ���� (50m)\n", textclist, "�������", "�����");
			}
		}
		case D_ADDMP+10:
	    {
		    if(response)
		    {
                new id;
		        if(sscanf(inputtext,"i", id)) return ShowPlayerDialog(playerid, D_ADDMP+10, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} ���������� ���� � ������", "������� ID ������:", "����", "�����");
				if(!IsPlayerConnected(id)) return SendClientMessage(playerid, 0xAFAFAFAA, "����� �� ������."), ShowPlayerDialog(playerid, D_ADDMP+10, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} ���������� ���� � ������", "������� ID ������:", "����", "�����");
				
				SetPVarInt(playerid, "PlayerColor", id);
				
                new textclist[1500];
    			strcat(textclist, "{FFFF00}������\n{FFD700}�������\n{FFD1DC}���������-�������\n{FFA500}���������\n{FF7F50}����������\n{FF47CA}������ � ����\n{FF0000}�������\n{FF00FF}������\n{F28500}������������\n{000000}������\n{FFFFFF}�����\n{B2EC5D}��������\n{B0E0E6}������� �������\n");
    			strcat(textclist, "{B00000}��������\n{ADFF2F}������-������\n{ACE1AF}����-�������\n{A91D11}����������-���������\n{9D9101}����� ������\n{9ACD32}�����-�������\n{99FF99}���������\n{AFAFAF}�����\n{964B00}����������\n{8B00FF}����������\n{87CEEB}��������\n{0000FF}�����\n{00FF00}����\n");
				ShowPlayerDialog(playerid, D_ADDMP+12, DIALOG_STYLE_LIST, "{9ACD32}�{FFFFFF} ���������� ���� � ���� (50m)\n", textclist, "�������", "�����");
			}
            else return DialogADDMP(playerid);
		}
		case D_ADDMP+12:
	    {
	        new idp = GetPVarInt(playerid, "PlayerColor");
		    if(response)
		    {
                switch(listitem)
                {
                    case 0:	SetPlayerColor(idp, 0xFFFF00AA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {FFFF00}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 1:	SetPlayerColor(idp, 0xFFD700AA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {FFD700}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 2:	SetPlayerColor(idp, 0xFFD1DCAA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {FFD1DC}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 3:	SetPlayerColor(idp, 0xFFA500AA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {FFA500}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 4:	SetPlayerColor(idp, 0xFF7F50AA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {FF7F50}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 5:	SetPlayerColor(idp, 0xFF47CAAA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {FF47CA}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 6:	SetPlayerColor(idp, 0xFF0000AA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {FF0000}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 7:	SetPlayerColor(idp, 0xFF00FFAA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {FF00FF}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 8:	SetPlayerColor(idp, 0xF28500AA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {F28500}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 9:	SetPlayerColor(idp, 0x000000AA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {000000}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 10: SetPlayerColor(idp, 0xFFFFFFAA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {FFFFFF}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 11: SetPlayerColor(idp, 0xB2EC5DAA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {B2EC5D}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 12: SetPlayerColor(idp, 0xB0E0E6AA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {B0E0E6}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 13: SetPlayerColor(idp, 0xB00000AA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {B00000}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 14: SetPlayerColor(idp, 0xADFF2FAA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {ADFF2F}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 15: SetPlayerColor(idp, 0xACE1AFAA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {ACE1AF}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 16: SetPlayerColor(idp, 0xA91D11AA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {A91D11}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 17: SetPlayerColor(idp, 0x9D9101AA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {9D9101}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 18: SetPlayerColor(idp, 0x9ACD32AA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {9ACD32}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 19: SetPlayerColor(idp, 0x99FF99AA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {99FF99}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 20: SetPlayerColor(idp, 0xAFAFAFAA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {AFAFAF}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 21: SetPlayerColor(idp, 0x964B00AA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {964B00}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 22: SetPlayerColor(idp, 0x8B00FFAA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {8B00FF}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 23: SetPlayerColor(idp, 0x87CEEBAA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {87CEEB}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 24: SetPlayerColor(idp, 0x0000FFAA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {0000FF}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
					case 25: SetPlayerColor(idp, 0x00FF00AA), SendClientMessage(idp, 0x9ACD32AA, "������������� ��������� ��� ����: {00FF00}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ����������.");
				}
			}
            else return DialogADDMP(playerid);
            DeletePVar(playerid, "PlayerColor");
		}
		case D_ADDMP+11:
	    {
	        new Float:PlayerPos[3];
			GetPlayerPos(playerid, PlayerPos[0], PlayerPos[1], PlayerPos[2]);
	        foreach(new i:Player)
			{
   				if(PlayerToPoint(50.0, i, PlayerPos[0], PlayerPos[1], PlayerPos[2]))
				{
		    		if(response)
		    		{
                		switch(listitem)
                		{
		                    case 0:	SetPlayerColor(i, 0xFFFF00AA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {FFFF00}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 1:	SetPlayerColor(i, 0xFFD700AA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {FFD700}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 2:	SetPlayerColor(i, 0xFFD1DCAA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {FFD1DC}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 3:	SetPlayerColor(i, 0xFFA500AA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {FFA500}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 4:	SetPlayerColor(i, 0xFF7F50AA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {FF7F50}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 5:	SetPlayerColor(i, 0xFF47CAAA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {FF47CA}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 6:	SetPlayerColor(i, 0xFF0000AA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {FF0000}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 7:	SetPlayerColor(i, 0xFF00FFAA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {FF00FF}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 8:	SetPlayerColor(i, 0xF28500AA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {F28500}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 9:	SetPlayerColor(i, 0x000000AA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {000000}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 10: SetPlayerColor(i, 0xFFFFFFAA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {FFFFFF}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 11: SetPlayerColor(i, 0xB2EC5DAA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {B2EC5D}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 12: SetPlayerColor(i, 0xB0E0E6AA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {B0E0E6}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 13: SetPlayerColor(i, 0xB00000AA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {B00000}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 14: SetPlayerColor(i, 0xADFF2FAA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {ADFF2F}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 15: SetPlayerColor(i, 0xACE1AFAA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {ACE1AF}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 16: SetPlayerColor(i, 0xA91D11AA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {A91D11}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 17: SetPlayerColor(i, 0x9D9101AA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {9D9101}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 18: SetPlayerColor(i, 0x9ACD32AA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {9ACD32}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 19: SetPlayerColor(i, 0x99FF99AA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {99FF99}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 20: SetPlayerColor(i, 0xAFAFAFAA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {AFAFAF}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 21: SetPlayerColor(i, 0x964B00AA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {964B00}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 22: SetPlayerColor(i, 0x8B00FFAA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {8B00FF}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 23: SetPlayerColor(i, 0x87CEEBAA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {87CEEB}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 24: SetPlayerColor(i, 0x0000FFAA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {0000FF}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
							case 25: SetPlayerColor(i, 0x00FF00AA), SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ��� ����: {00FF00}|||||||."), SendClientMessage(playerid, 0x9ACD32AA, "���� ���������� ���� (50m).");
						}
					}
					else return DialogADDMP(playerid);
				}
			}
		}
		case D_ADDMP+13:
	    {
	        new Float:PlayerPos[3];
			GetPlayerPos(playerid, PlayerPos[0], PlayerPos[1], PlayerPos[2]);
        	foreach(new i:Player)
			{
				if(PlayerToPoint(50.0, i, PlayerPos[0], PlayerPos[1], PlayerPos[2]))
				{
		    		if(response)
		    		{
		    		    if(!IsPlayerAdmin(i)) return TogglePlayerControllable(i, false);
						SendClientMessage(i, 0x9ACD32AA, "������������� ��������� ����.");
					}
            		else
            		{
                        TogglePlayerControllable(i, true);
						SendClientMessage(i, 0x9ACD32AA, "������������� ���� ���������.");
            		}
				}
			}
		}
		case D_ADDMP+14:
	    {
		    if(response)
		    {
		        new countn;
		        if(sscanf(inputtext,"i", countn)) return ShowPlayerDialog(playerid, D_ADDMP+14, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} ���� ������\n", "������� ����� �� ������� ������ �������� ������:", "������", "�����");
		        if(countn > MAX_TIMER) return SendClientMessage(playerid, 0xAFAFAFAA, "�������� 20 ������."), ShowPlayerDialog(playerid, D_ADDMP+14, DIALOG_STYLE_INPUT, "{9ACD32}�{FFFFFF} ���� ������\n", "������� ����� �� ������� ������ �������� ������:", "������", "�����");
				Count = countn;
				MpTimer(playerid);
			}
			else return DialogADDMP(playerid);
		}
	}
	return true;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if (strcmp("/fsmp", cmdtext, true) == 0)
	{
	    if(!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, 0xAFAFAFAA, "�� �� �������������.");
        DialogADDMP(playerid);
		return true;
	}
	if (strcmp("/gomp", cmdtext, true) == 0)
	{
		if(CreateMP == false) return SendClientMessage(playerid, 0xAFAFAFAA, "�� ������ ������ ����������� ���.");
		if(TeleportMP == false) return SendClientMessage(playerid, 0xAFAFAFAA, "�������� �� ����������� ������. �������� ����� ��� ������� �������������...");
		SetPlayerPos(playerid, PosMP[0], PosMP[1], PosMP[2]);
		SendClientMessage(playerid, 0x00FF00AA, "�� ������� ����������������� �� �����������.");
		return true;
	}
	return false;
}

stock DialogADDMP(playerid)
{
	new texttelep[100];
	switch(TeleportMP)
	{
	    case 0: texttelep = "{00FF00}�������";
	    case 1: texttelep = "{FF0000}�������";
	}
	if(CreateMP == true)
	{
		new strmp[900];
		new textmp[900];
		format(strmp, 900, "{9ACD32}�{AFAFAF} �������� �����������: %s | ����: %s\n{9ACD32}� %s{FFFFFF} �������� �� �����������\n", NameMP, PrizMP, texttelep);
		strcat(textmp, strmp);
		format(strmp, 900, "{9ACD32}�{FFFFFF} ���������� HP ������� (50m)\n{9ACD32}�{FFFFFF} ������ ������ ������� (50m)\
		\n{9ACD32}�{FFFFFF} ����������� ������� (50m)\n{9ACD32}�{FFFFFF} �������� ������ [%d/19]\n{9ACD32}�{FFFFFF} �������� ����\n{9ACD32}�{FFFFFF} ���������� ����\n{9ACD32}�{FFFFFF} ���������� �������\n{9ACD32}�{FFFFFF} ���� ������\n", TOTALMPCAR);
		strcat(textmp, strmp);
		strcat(textmp, "{9ACD32}�{FFFFFF} �������� ����������\n{9ACD32}�{FFFFFF} ������� �����������");
		ShowPlayerDialog(playerid, D_ADDMP, DIALOG_STYLE_LIST, "{9ACD32}���� �����������", textmp, "�������", "�������");
	}
	else
	{
	    new strmp[900];
		new textmp[900];
		format(strmp, 900, "{9ACD32}�{FFFFFF} ������� �����������\n{9ACD32}� %s{FFFFFF} �������� �� �����������\n", texttelep);
		strcat(textmp, strmp);
		format(strmp, 900, "{9ACD32}�{FFFFFF} ���������� HP ������� (50m)\n{9ACD32}�{FFFFFF} ������ ������ ������� (50m)\
		\n{9ACD32}�{FFFFFF} ����������� ������� (50m)\n{9ACD32}�{FFFFFF} �������� ������ [%d/19]\n{9ACD32}�{FFFFFF} �������� ����\n{9ACD32}�{FFFFFF} ���������� ����\n{9ACD32}�{FFFFFF} ���������� �������\n{9ACD32}�{FFFFFF} ���� ������\n", TOTALMPCAR);
		strcat(textmp, strmp);
		strcat(textmp, "{9ACD32}�{FFFFFF} �������� ����������\n{9ACD32}�{FFFFFF} ������� �����������");
		ShowPlayerDialog(playerid, D_ADDMP, DIALOG_STYLE_LIST, "{9ACD32}���� �����������", textmp, "�������", "�������");
	}
	return true;
}

forward PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z);
public PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z)
{
	if(IsPlayerConnected(playerid))
	{
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		tempposx = (oldposx -x);
		tempposy = (oldposy -y);
		tempposz = (oldposz -z);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
		{
			return true;
		}
	}
	return false;
}

stock CreateMPCAR(playerid, vehicleid, color1, color2)
{
	new Float:pPos[3], Float:Angle;
	GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
	GetPlayerFacingAngle(playerid, Angle);
	
	TOTALMPCAR++;
	
	CarMP[TOTALMPCAR] = CreateVehicle(vehicleid, pPos[0], pPos[1], pPos[2], Angle, color1, color2, 80000);
	PutPlayerInVehicle(playerid, CarMP[TOTALMPCAR], 0);
	return true;
}

stock DestroyMPCAR()
{
	DestroyVehicle(CarMP[0]);
	DestroyVehicle(CarMP[1]);
	DestroyVehicle(CarMP[2]);
	DestroyVehicle(CarMP[3]);
	DestroyVehicle(CarMP[4]);
	DestroyVehicle(CarMP[5]);
	DestroyVehicle(CarMP[6]);
	DestroyVehicle(CarMP[7]);
	DestroyVehicle(CarMP[8]);
	DestroyVehicle(CarMP[9]);
	DestroyVehicle(CarMP[10]);
	DestroyVehicle(CarMP[11]);
	DestroyVehicle(CarMP[12]);
	DestroyVehicle(CarMP[13]);
	DestroyVehicle(CarMP[14]);
	DestroyVehicle(CarMP[15]);
	DestroyVehicle(CarMP[16]);
	DestroyVehicle(CarMP[17]);
	DestroyVehicle(CarMP[18]);
	DestroyVehicle(CarMP[19]);
	
	TOTALMPCAR = 0;
	return true;
}

stock D_COLOR(playerid)
{
    new textclist[1500];
    strcat(textclist, "{FFFF00}������\n{FFD700}�������\n{FFD1DC}���������-�������\n{FFA500}���������\n{FF7F50}����������\n{FF47CA}������ � ����\n{FF0000}�������\n{FF00FF}������\n{F28500}������������\n{000000}������\n{FFFFFF}�����\n{B2EC5D}��������\n{B0E0E6}������� �������\n");
    strcat(textclist, "{B00000}��������\n{ADFF2F}������-������\n{ACE1AF}����-�������\n{A91D11}����������-���������\n{9D9101}����� ������\n{9ACD32}�����-�������\n{99FF99}���������\n{AFAFAF}�����\n{964B00}����������\n{8B00FF}����������\n{87CEEB}��������\n{0000FF}�����\n{00FF00}����\n");
	ShowPlayerDialog(playerid, D_ADDMP+9, DIALOG_STYLE_LIST, "{9ACD32}�{FFFFFF} ���������� ����\n", textclist, "�������", "�����");
	return true;
}

forward MpTimer(playerid);
public MpTimer(playerid)
{
    new Float:PlayerPos[3];
	GetPlayerPos(playerid, PlayerPos[0], PlayerPos[1], PlayerPos[2]);
    foreach(new i:Player)
	{
		if(PlayerToPoint(50.0, i, PlayerPos[0], PlayerPos[1], PlayerPos[2]))
		{
			if (Count > 0)
			{
				new string[150];
				format(string, sizeof(string), "~y~MP Started: %d", Count);
				GameTextForPlayer(i, string, 2500, 6);
				Count--;
				SetTimer("MpTimer", 1000, false);
			}
			else
			{
				Count = 0;
				TogglePlayerControllable(i, true);
				GameTextForAll("~y~Go go go!", 2500, 1);
				PlayerPlaySound(i, 3200, 0.0, 0.0, 0.0);
			}
		}
	}
	return true;
}

stock CreateText(playerid)
{
	new strtext[300];
	new name[50];
	GetPlayerName(playerid, name, sizeof(name));
    format(strtext, 300, "� �����������: %s. | ����: %s.\n� {FF6347}�������� �����������: %s[%d]", NameMP, PrizMP, name, playerid);
    
	text3dmp = Create3DTextLabel(strtext, 0x9ACD32FF, PosMP[0], PosMP[1], PosMP[2], 50.0, 0);
	objectmp[0] = CreateObject(18724, PosMP[0], PosMP[1], PosMP[2], 0.0, 0.0, 0.0);
	objectmp[1] = CreateObject(18728, PosMP[0], PosMP[1], PosMP[2], 0.0, 0.0, 0.0);
	return true;
}
