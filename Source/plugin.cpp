/* Basic library import */
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


/* SAMP GDK Library */
#include "SDK/sampgdk/a_players.h"
#include "SDK/sampgdk/a_samp.h"
#include "SDK/sampgdk/core.h"
#include "SDK/sampgdk/sdk.h"
#include "SDK/sampgdk/types.h"
#include "SDK/sampgdk/bool.h"
#include "SDK/sampgdk/interop.h"
#include "SDK/sampgdk/export.h"
#include "SDK/sampgdk/platform.h"
#include "SDK/sampgdk/a_vehicles.h"

/* Dodatna biblioteka */
#include "bauer_h.h"

/*//Varijable

float xyz[3][MAX_PLAYERS];
*/

using sampgdk::logprintf;

void SAMPGDK_CALL PrintTickCountTimer(int timerid, void *params) {
  logprintf("Tick count: %d", GetTickCount());
}

/*void SAMPGDK_CALL Detekcija(int timerid, void *params) {
for(char i=0; i<MAX_PLAYERS; i++) 
  {
  if(GetPVarInt(i, "AdminSecured") == 0)
  {
	char ping = GetPlayerPing(i);
	if(ping > 600)
	{
		GetPlayerName(i, ime, sizeof(ime));
		SendClientMessage(i, -1, "Kikovan si zbog prevelikog pinga");
		Kick(i);
	}
  }
		
  }
}*/

float floatsqroot(float &value) {
	return sqrt(value);
}

float floatadd(float &oper1, float &oper2) {
	return oper1 + oper2;
}

float floatpower(float &value, float &exponent) {
	return pow(value, exponent);
}
		
float floatsub(float &oper1, float &oper2) {
	return oper2 - oper1;
}

float floatabs(float &value) {
	return abs(value);
}

float floatmul(float &oper1, float &oper2) {
	return oper1 * oper2;
}

float floatround(float f,float pres)
{
    return (float) (floor(f*(1.0f/pres) + 0.5)/(1.0f/pres));
}

float GetSpeed(int playerid) {
                
	IsPlayerInAnyVehicle(playerid)? GetVehicleVelocity(GetPlayerVehicleID(playerid), &xyz[0][playerid], &xyz[1][playerid], &xyz[2][playerid]):
    GetPlayerVelocity(playerid, &xyz[0][playerid], &xyz[1][playerid], &xyz[2][playerid]);
    return 235 * sqrtf(powf(xyz[2][playerid], 2) + powf(xyz[1][playerid], 2) + powf(xyz[0][playerid], 2));
}

float Log(string String[]) {
	
	ofstream logfile;
	logfile.open ("Bauer_AC/log.txt");
	logfile << "%s \n", String;
	logfile.close();
	return 1;
	
}
	

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit() {
 logprintf(""); 
  logprintf("==================================="); 
  logprintf("== SAMP*X Plugin by Bauer loaded.=="); 
  logprintf("== All natives sucesfully loaded!==");
  logprintf("==	  Version: %s           ==", VERSION);
  logprintf("==	 LAST UPDATE: %s ==", UPDATE);
  logprintf("==================================="); 
  SetTimer(10000, true, PrintTickCountTimer, 0);
  //SetTimer(3000, true, Detekcija, 0);
  RCONZ = 1;
  FLYH = 1;
  SPEEDH = 1;
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid) {
  SendClientMessage(playerid, 0xFFFFFFFF, "This server is using SAMP*X Plugin by Bauer!");
  //NovacStart[playerid] = GetPlayerMoney(playerid);
  Secured[playerid] = 1;
  Kickk[playerid] = 0;
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn (int playerid) {
  NovacStart[playerid] = GetPVarInt(playerid, "Moneyyy");
  SetPVarInt(playerid, "AdminSecured", 0);
  GetPlayerHealth(playerid, helts);
  HeltiIgraca[playerid] = (int) helts;
  //SetPVarInt(playerid, "Money", 0);
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerUpdate(int playerid) {
if(GetPVarInt(playerid, "AdminSecured") == 0)
{
  if(GetSpeed(playerid) > 285)
    {
        SendClientMessage(playerid,-1,"Nemoj da koristis SpeedHack. Admini su obavesteni"); TogglePlayerControllable(playerid, false);
		Kick(playerid);
		GetPlayerName(playerid, ime, sizeof(ime));
		string upis;
		upis = "Speed Hack. Korisnik: %s ", ime;
        return 1;
    }
}
//Anti High Ping
if(GetPVarInt(playerid, "AdminSecured") == 0)
  {
	char ping = GetPlayerPing(playerid);
	if(ping > 600)
	{
		GetPlayerName(playerid, ime, sizeof(ime));
		SendClientMessage(playerid, -1, "Kikovan si zbog prevelikog pinga");
		Kick(playerid);
	}
  }
//Anti Money Hack
char novac;
novac = GetPlayerMoney(playerid);
if(GetPVarInt(playerid, "AdminSecured") == 0)
{
if(GetPVarInt(playerid, "Money") == 0 && novac > GetPVarInt(playerid, "Moneyyy"))
{
  ResetPlayerMoney (playerid);
  GivePlayerMoney (playerid, GetPVarInt(playerid, "Moneyyy"));
  GivePlayerMoney (playerid, NovacStart[playerid]);
  SendClientMessage(playerid, -1, "Novac ti je vracen na pocetno stanje zbog Moneay Hacka-a");
}
if(GetPVarInt(playerid, "Money") == 1)
{
	NovacStart[playerid] = GetPVarInt(playerid, "Moneyyy");
	SetPVarInt(playerid, "Money", 0);
}
}
//Anti JP Hack
if(GetPVarInt(playerid, "AdminSecured") == 0)
{
if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK)
{
    SendClientMessage(playerid,-1,"Kikovani ste zbog jetpack hacka!");
    Kick(playerid);
    return 1;
}
}
/*//Anti Armour Hack
if(GetPVarInt(playerid, "ArmorProtect") == 0)
{
GetPlayerArmour(playerid, Armour);
if( (int) Armour > 99)
{
    SendClientMessage(playerid,-1,"Kikovani ste zbog armour hacka!");
    //Kick(playerid);
    return 1;
}
if(GetPVarInt(playerid, "ArmorProtect") == 1)
{
	SetPVarInt(playerid, "ArmorProtect", 0);
}
}*/
//Anti Health Hack
if(GetPVarInt(playerid, "HpProtected") == 0)
{
GetPlayerHealth(playerid, Health);
if( (int) Health > HeltiIgraca[playerid])
{
    SetPlayerHealth(playerid, HeltiIgraca[playerid]);
	SendClientMessage(playerid,-1,"Helti su vam smanjeni zbog health hack-a!");
    return 1;
}
if(GetPVarInt(playerid, "HpProtected") == 1)
{
	SetPVarInt(playerid, "HpProtected", 0);
}
}
  return true;
}


PLUGIN_EXPORT bool PLUGIN_CALL OnRconLoginAttempt(const char *ip, const char *password, bool success) {
if(!success) 
{
    {
        printf("POGRESNA RCON SIFRA! IP %s KORISTIO SIFRU %s",ip, password);
        char pip[16];
        for(char i=0; i<MAX_PLAYERS; i++) 
        {
			if(GetPVarInt(i, "AdminSecured") == 0)
			{
            GetPlayerIp(i, pip, sizeof(pip));
			GetPlayerName(i, ime, sizeof(ime));
			if(!strcmp(ip, pip)) //If a player's IP is the IP that failed the login
			{
				SendClientMessage(i, 0xFFFFFFFF, "Pogresio si sifru, ZBOGOM!"); 
				Ban(i); 
			}
		}
	}
}
}
return 1;
}


PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
  return sampgdk::Supports() | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
  return sampgdk::Load(ppData);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
 logprintf(" * SAMP*X Plugin by Bauer was unloaded."); 
 SendClientMessageToAll(-1,"SAMP*X Plugin by Bauer is turned off!"); 
 sampgdk::Unload();
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
  sampgdk::ProcessTick();
}
