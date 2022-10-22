// This file added in headers queue
// File: "Sources.h"
#include "resource.h"

namespace GOTHIC_ENGINE {
	void PrintMsg(zSTRING text) {
		screenHack->ClrPrintwin();
		screenHack->PrintTimedCX(550, text, 3000.0f, &zCOLOR(255, 255, 255));
	}

	int CalculateHackChestLevel(int x) {
		int level;

		level = baselevel + (x * 5);

		if (level > 100)
			level = 100;

		return level;
	}

	void oCNpc::AI_PlaySoundFromVob(zSTRING sound, zCVob* vob) {
		oCMsgConversation* msg = new oCMsgConversation(oCMsgConversation::EV_SNDPLAY, sound);
		msg->f_yes = true;
		msg->target = vob;
		GetEM()->OnMessage(msg, this);
	}

	void oCNpc::AI_DrawWeapon(int useFist) {
		oCMsgWeapon* msgWeapon = new oCMsgWeapon(oCMsgWeapon::EV_DRAWWEAPON, 0, 0);
		msgWeapon->useFist = useFist;
		GetEM()->OnMessage(msgWeapon, this);
	}

	void oCNpc::AI_RemoveWeapon() {
		oCMsgWeapon* msgWeapon = new oCMsgWeapon(oCMsgWeapon::EV_REMOVEWEAPON, 0, 0);
		GetEM()->OnMessage(msgWeapon, this);
	}

	void oCNpc::AI_PlayAni(zSTRING anim) {
		oCMsgConversation* msgPlayAni = new oCMsgConversation(oCMsgConversation::EV_PLAYANI_NOOVERLAY, anim);
		msgPlayAni->number = 0;
		this->GetEM()->OnMessage(msgPlayAni, this);
	}

	bool_t CanUseLockPick() {
		zCParser* par = zCParser::GetParser();
		zCPar_Symbol* symbol = par->GetSymbol("NPC_TALENT_PICKLOCK");

		if (!symbol)
			return false;

		int symbolValue;
		symbol->GetValue(symbolValue, 0);
		if (symbolValue <= 0)
			return false;

		int symbolSkill = player->GetTalentSkill(symbolValue);

		if (symbolSkill <= 0) {
			int idx = par->GetIndex("PLAYER_MOB_MISSING_LOCKPICK");
			if (idx != Invalid) {
				par->SetInstance("SELF", player);
				par->CallFunc(idx);
			}

			return false;
		}

		return true;
	}

	bool_t HasLockPick() {
		zCParser* par = zCParser::GetParser();

		int lockpickIndex = par->GetIndex("ITKE_LOCKPICK");
		if (lockpickIndex < 0)
			return false;

		oCItem* lockpickItem = player->IsInInv(lockpickIndex, 1);
		if (!lockpickItem)
			return false;

		if (lockpickItem->amount < 1)
			return false;

		return true;
	}

	bool_t CanHackChest() {
		if (oCZoneMusic::s_herostatus != oHERO_STATUS_STD)
			return false;

		if (player->fmode != 0)
			return false;

		if (player->IsUnconscious())
			return false;

		if (player->attribute[NPC_ATR_HITPOINTS] <= 0)
			return false;

		if (ogame->singleStep)
			return false;

		if (player->interactMob || player->interactItem)
			return false;

		if (!oCInformationManager::GetInformationManager().HasFinished())
			return false;

		if (player->inventory2.IsOpen())
			return false;

		if (!player->IsHuman())
			return false;

		if (player->GetBodyState() >= BS_SWIM)
			return false;

		if (player->anictrl && player->anictrl->IsInWeaponChoose())
			return false;

		if (!player->GetEM(true)->IsEmpty(false))
			return false;

		return true;
	}

	void HackChestStr() {
		zCParser* par = zCParser::GetParser();

		zCVob* focusVob = player->GetFocusVob();

		if (!focusVob)
			return;

		curDist = player->GetDistanceToVob(*focusVob);

		oCMobLockable* vob = focusVob->CastTo<oCMobLockable>();
		if (!vob)
			return;

		oCMobContainer* chest = focusVob->CastTo<oCMobContainer>();
		oCMobDoor* door = focusVob->CastTo<oCMobDoor>();

		if (!door && !chest)
			return;

		if (door && !door->sceme.StartWith("DOOR"))
			return;

		if (!vob->locked || vob->pickLockStr.IsEmpty())
			return;

		if (curDist > maxDist) {
			int idx = par->GetIndex("PLAYER_MOB_TOO_FAR_AWAY");
			if (idx != Invalid) {
				par->SetInstance("SELF", player);
				par->CallFunc(idx);
			}
			return;
		}

		if (!CanUseLockPick())
			return;

		oCMsgMovement* msgStopMovement = new oCMsgMovement(oCMsgMovement::EV_STANDUP, 1);
		player->GetEM()->OnMessage(msgStopMovement, player);

		int strNeeded = CalculateHackChestLevel(vob->pickLockStr.Length());
		int strPlayer = player->attribute[NPC_ATR_STRENGTH];

		if (strPlayer < strNeeded)
		{
			PrintMsg("Wymagana si³a: " + Z strPlayer + Z"/" + Z strNeeded);
			player->AI_PlayAni("T_DONTKNOW");
			return;
		}

		zSTRING anim = "";
		int useFist = 0;
		oCItem* weapon = player->GetEquippedMeleeWeapon();

		if (!weapon) {
			if (door) {
				anim = "T_KICKDOOR";
				useFist = 1;
			}
			else {
				PrintMsg("Potrzebujê broni!");
				return;
			}
		}
		else {
			if ((weapon->flags & ITM_FLAG_SWD) || (weapon->flags & ITM_FLAG_AXE))
				anim = "T_1HSBREAKCHEST";
			else if ((weapon->flags & ITM_FLAG_2HD_SWD) || (weapon->flags & ITM_FLAG_2HD_AXE))
				anim = "T_2HSBREAKCHEST";
			else {
				anim = "T_1HSBREAKCHEST";
				useFist = 1;
			}
		}

		player->AI_DrawWeapon(useFist);
		player->AI_PlayAni(anim);
		player->AI_RemoveWeapon();

		player->AssessUseMob_S(vob);

		int randy = rand() % 100;

		if (strPlayer < randy)
			return;

		vob->locked = false;
	}

	void HackChestDex() {
		zCParser* par = zCParser::GetParser();

		zCVob* focusVob = player->GetFocusVob();

		if (!focusVob)
			return;

		curDist = player->GetDistanceToVob(*focusVob);

		oCMobLockable* vob = focusVob->CastTo<oCMobLockable>();
		if (!vob)
			return;

		oCMobContainer* chest = focusVob->CastTo<oCMobContainer>();
		oCMobDoor* door = focusVob->CastTo<oCMobDoor>();

		if (!door && !chest)
			return;

		if (door && !door->sceme.StartWith("DOOR"))
			return;

		if (!vob->locked || vob->pickLockStr.IsEmpty())
			return;

		if (curDist > maxDist) {
			int idx = par->GetIndex("PLAYER_MOB_TOO_FAR_AWAY");
			if (idx != Invalid) {
				par->SetInstance("SELF", player);
				par->CallFunc(idx);
			}
			return;
		}

		if (!CanUseLockPick())
			return;

		if (!HasLockPick()) {
			int idx = par->GetIndex("PLAYER_MOB_MISSING_LOCKPICK");
			if (idx != Invalid) {
				par->SetInstance("SELF", player);
				par->CallFunc(idx);
			}
			return;
		}

		oCMsgMovement* msgStopMovement = new oCMsgMovement(oCMsgMovement::EV_STANDUP, 1);
		player->GetEM()->OnMessage(msgStopMovement, player);

		int dexNeeded = CalculateHackChestLevel(vob->pickLockStr.Length());
		int dexPlayer = player->attribute[NPC_ATR_DEXTERITY];

		if (dexPlayer < dexNeeded)
		{
			PrintMsg("Wymagana zrêcznoœæ: " + Z dexPlayer + Z"/" + Z dexNeeded);
			player->AI_PlayAni("T_DONTKNOW");
			return;
		}
		//player->AI_PlayAni("T_PLUNDER");
		player->AI_PlayAni("T_CHESTBIG_STAND_2_S0");
		player->AssessUseMob_S(vob);
		player->AI_PlayAni("T_CHESTBIG_S0_UNLOCK");
		player->RemoveFromInv("ITKE_LOCKPICK", 1);

		int randy = rand() % 100;

		if (dexPlayer < randy) {
			player->AI_PlaySoundFromVob("PICKLOCK_BROKEN", vob);
		}
		else {
			player->AI_PlaySoundFromVob("PICKLOCK_SUCCESS", vob);
			vob->locked = false;
		}

		player->AI_PlayAni("T_CHESTBIG_S0_2_STAND");
	}

	void Game_Entry() {
	}

	void Game_Init() {
		if (!screenHack) {
			screenHack = zNEW(zCView)(0, 0, 8192, 8192);
			screen->InsertItem(screenHack);
		}
	}

	void Game_Exit() {
	}

	void Game_PreLoop() {
	}

	void Game_Loop() {
		if (zKeyToggled(KEY_T) && CanHackChest())
			HackChestStr();
		else if (zKeyToggled(KEY_Y) && CanHackChest())
			HackChestDex();
	}

	void Game_PostLoop() {
	}

	void Game_MenuLoop() {
	}

	// Information about current saving or loading world
	TSaveLoadGameInfo& SaveLoadGameInfo = UnionCore::SaveLoadGameInfo;

	void Game_SaveBegin() {
	}

	void Game_SaveEnd() {
	}

	void LoadBegin() {
	}

	void LoadEnd() {
	}

	void Game_LoadBegin_NewGame() {
		LoadBegin();
	}

	void Game_LoadEnd_NewGame() {
		LoadEnd();
	}

	void Game_LoadBegin_SaveGame() {
		LoadBegin();
	}

	void Game_LoadEnd_SaveGame() {
		LoadEnd();
	}

	void Game_LoadBegin_ChangeLevel() {
		LoadBegin();
	}

	void Game_LoadEnd_ChangeLevel() {
		LoadEnd();
	}

	void Game_LoadBegin_Trigger() {
	}

	void Game_LoadEnd_Trigger() {
	}

	void Game_Pause() {
	}

	void Game_Unpause() {
	}

	void Game_DefineExternals() {
	}

	void Game_ApplyOptions() {
	}

	/*
	Functions call order on Game initialization:
	  - Game_Entry           * Gothic entry point
	  - Game_DefineExternals * Define external script functions
	  - Game_Init            * After DAT files init

	Functions call order on Change level:
	  - Game_LoadBegin_Trigger     * Entry in trigger
	  - Game_LoadEnd_Trigger       *
	  - Game_Loop                  * Frame call window
	  - Game_LoadBegin_ChangeLevel * Load begin
	  - Game_SaveBegin             * Save previous level information
	  - Game_SaveEnd               *
	  - Game_LoadEnd_ChangeLevel   *

	Functions call order on Save game:
	  - Game_Pause     * Open menu
	  - Game_Unpause   * Click on save
	  - Game_Loop      * Frame call window
	  - Game_SaveBegin * Save begin
	  - Game_SaveEnd   *

	Functions call order on Load game:
	  - Game_Pause              * Open menu
	  - Game_Unpause            * Click on load
	  - Game_LoadBegin_SaveGame * Load begin
	  - Game_LoadEnd_SaveGame   *
	*/

#define AppDefault True
	CApplication* lpApplication = !CHECK_THIS_ENGINE ? Null : CApplication::CreateRefApplication(
		Enabled(AppDefault) Game_Entry,
		Enabled(AppDefault) Game_Init,
		Enabled(AppDefault) Game_Exit,
		Enabled(AppDefault) Game_PreLoop,
		Enabled(AppDefault) Game_Loop,
		Enabled(AppDefault) Game_PostLoop,
		Enabled(AppDefault) Game_MenuLoop,
		Enabled(AppDefault) Game_SaveBegin,
		Enabled(AppDefault) Game_SaveEnd,
		Enabled(AppDefault) Game_LoadBegin_NewGame,
		Enabled(AppDefault) Game_LoadEnd_NewGame,
		Enabled(AppDefault) Game_LoadBegin_SaveGame,
		Enabled(AppDefault) Game_LoadEnd_SaveGame,
		Enabled(AppDefault) Game_LoadBegin_ChangeLevel,
		Enabled(AppDefault) Game_LoadEnd_ChangeLevel,
		Enabled(AppDefault) Game_LoadBegin_Trigger,
		Enabled(AppDefault) Game_LoadEnd_Trigger,
		Enabled(AppDefault) Game_Pause,
		Enabled(AppDefault) Game_Unpause,
		Enabled(AppDefault) Game_DefineExternals,
		Enabled(AppDefault) Game_ApplyOptions
	);
}