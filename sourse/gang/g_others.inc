#define MOROZ_BALLAS 0
#define MOROZ_VAGOS 1
#define MOROZ_GROVE 2
#define MOROZ_RIFA 3
#define MOROZ_AZTECAS 4

#define MAX_ATTEMPT_GANG 2

new bool:zahvat = false;
new CaptureTime = 0;
new CaptureAttempt[5]={0,...};
new CountOnZone[23];
new Text:Capture[4];

new fracmoroz [8]={0,...};
new const stock fracmorozName [8][32]={"The Ballas","The Vagos","The Grove","The Rifa","The Aztecas", "La Cosa Nostra", "Yakuza","Русской мафии"};

new IDGZ[MAX_PLAYERS] = {-1,...};
enum GzoneInfo {
	gID,
	gZone,
	Float:gCoords[4],
	gFrakVlad,
	gNapad,
	gType,
	gTime,
	ZoneOnBattle,
	gzTimer
}
new GZInfo[125][GzoneInfo];
new TOTALGZ = 0;
new VladGzone[MAX_FRACTIONS]={0,...};
stock GetIDGZ(playerid) {
	for(new i = 0; i < TOTALGZ; i++)
		if(PlayerToKvadrat(playerid,GZInfo[i][gCoords][0], GZInfo[i][gCoords][1],GZInfo[i][gCoords][2],GZInfo[i][gCoords][3])) return i;
	return -1;
}
stock GetGangZoneColor(fractionid) return (GZInfo[fractionid][gFrakVlad] == fBALLAS) ? (0xCC00FFAA) : (GZInfo[fractionid][gFrakVlad] == fRIFA) ? (0x6666FFAA) : (GZInfo[fractionid][gFrakVlad] == fVAGOS) ? (0xffff00AA) : (GZInfo[fractionid][gFrakVlad] == fGROVE) ? (0x009900AA) : (0x00CCFFAA);
stock GetGangColor(g) {
	new zx;
	switch(g) {
		case fGROVE: zx = 0x009900AA;
		case fBALLAS: zx = 0xCC00FFAA;
		case fRIFA: zx = 0x6666FFAA;
		case fAZTEC: zx = 0x00CCFFAA;
		case fVAGOS: zx = 0xffff00AA;
		default: zx = 0xC0C0C0AA;
	}
	return zx;
}
stock GFrac(frac) {
	new namegang[20];
	switch(frac) {
		case fGROVE: namegang = "Grove Street";
		case fAZTEC: namegang = "Varrios Los Aztecas";
		case fBALLAS: namegang = "East Side Ballas";
		case fRIFA: namegang = "Rifa";
		case fVAGOS: namegang = "Los Santos Vagos";
	}
	return namegang;
}
stock SendBand(color,str[]) {
	foreach(new x:Player) {
		if(IsAGang(x))
			SendClientMessage(x,color,str);
	}
	return 1;
}
EndCapt(m) {
	TextDrawHideForPlayer(m, Capture[0]);
	TextDrawHideForPlayer(m, Capture[1]);
	TextDrawHideForPlayer(m, Capture[2]);
	TextDrawHideForPlayer(m, Capture[3]);
	for(new num; num < 10; num++) SendDeathMessageToPlayer(m,6000,5005, 255);
	DeletePVar(m,"ppkz");
}