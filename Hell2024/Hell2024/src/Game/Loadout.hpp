#pragma once
#include "Player.hpp"

class LoadoutManager
{
public:
    static void GiveInitialLoadout(Player* player)
	{
        player->GiveWeapon("Knife");
        // player.GiveWeapon("GoldenKnife");
        player->GiveWeapon("Glock");
        player->GiveWeapon("GoldenGlock");
        player->GiveWeapon("Tokarev");
        // player.GiveWeapon("Smith & Wesson");
        player->GiveWeapon("AKS74U");
        player->GiveWeapon("P90");
        player->GiveWeapon("Shotgun");
        player->GiveWeapon("SPAS");

        player->GiveAmmo("Glock", 80000);
        player->GiveAmmo("Tokarev", 200);
        player->GiveAmmo("AKS74U", 999999);
        player->GiveAmmo("Shotgun", 6666);

        player->GiveRedDotToWeapon("GoldenGlock");
        // player.GiveSilencerToWeapon("Glock");
	}
};