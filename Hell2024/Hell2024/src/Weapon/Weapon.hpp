//#pragma once
//
////#include "Game/Player.hpp"
//
//namespace Weapon
//{
//	void PlayFireSound(WeaponInfo* weaponInfo)
//	{
//        int rand = std::rand() % weaponInfo->audioFiles.fire.size();
//        assert(rand);
//        assert(weaponInfo->name != "");
//        //std::cout << weaponInfo->name << "\n";
//        if (weaponInfo->name == "P90" || weaponInfo->name == "AKS74U")
//        {
//            Audio::PlayAudio(weaponInfo->audioFiles.fire[rand], 0.2f);
//        }
//        else if (weaponInfo->name == "Smith & Wesson")
//        {
//            Audio::PlayAudio(weaponInfo->audioFiles.fire[rand], 0.45f);
//        }
//        else
//        {
//            Audio::PlayAudio(weaponInfo->audioFiles.fire[rand], 1.0f);
//        }
//	}
//};