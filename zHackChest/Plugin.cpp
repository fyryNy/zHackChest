// This file added in headers queue
// File: "Sources.h"
#include "resource.h"

namespace GOTHIC_ENGINE {
	void PrintMsg(zSTRING text) {
		ogame->GetTextView()->Printwin(text);
	}

	void oCNpc::AI_PlaySoundFromVob(zSTRING sound, zCVob* vob) {
		oCMsgConversation* msg = nullptr;

#if ENGINE == Engine_G1
		msg = new oCMsgConversation(oCMsgConversation::EV_PLAYSOUND, sound);
#else
		msg = new oCMsgConversation(oCMsgConversation::EV_SNDPLAY, sound);
#endif
		msg->f_yes = true;
		msg->target = vob;
		GetEM(false)->OnMessage(msg, this);

		return;
	}

	void oCNpc::AI_DrawWeapon() {
		oCMsgWeapon* msgWeapon = new oCMsgWeapon(oCMsgWeapon::EV_DRAWWEAPON, 0, 0);
		GetEM(false)->OnMessage(msgWeapon, this);

		return;
	}

	void oCNpc::AI_RemoveWeapon() {
		oCMsgWeapon* msgWeapon = new oCMsgWeapon(oCMsgWeapon::EV_REMOVEWEAPON, 0, 0);
		GetEM(false)->OnMessage(msgWeapon, this);

		return;
	}

	void oCNpc::AI_PlayAni(zSTRING anim) {
		oCMsgConversation* msgPlayAni = new oCMsgConversation(oCMsgConversation::EV_PLAYANI_NOOVERLAY, anim);
		msgPlayAni->number = 0;
		GetEM(false)->OnMessage(msgPlayAni, this);

		return;
	}

	bool_t CallFunc(int idx) {
		if (idx != Invalid) {
			parser->SetInstance("SELF", player);
			parser->CallFunc(idx);
			return true;
		}
		return false;
	}

	void Shrugeg(string msg) {
		PrintMsg(Z msg);
		player->AI_PlayAni("T_DONTKNOW");
	}

	bool_t oCNpc::InSameRoom(zCVob* vob) {
		if (!vob)
			return false;

		const zSTRING* portalNameNpc = this->GetSectorNameVobIsIn();
		const zSTRING* portalNameVob = vob->GetSectorNameVobIsIn();

		if (portalNameNpc && portalNameVob) {
			if (portalNameNpc->CompareI(portalNameVob))
				return true;
		}
		else if (!portalNameNpc && !portalNameVob)
			return true;

		return false;
	}

	int CalculateHackChestLevel(int x) {
		int level;

		level = BaseLevel + (x * AttPerLevel);

		if (level > 100)
			level = 100;

		return level;
	}

	bool_t CanHackChest() {
		if (!ogame)
			return false;

		if (ogame->singleStep)
			return false;

		if (ogame->pause_screen)
			return false;

		if (!player)
			return false;

		if (oCZoneMusic::s_herostatus != oHERO_STATUS_STD)
			return false;

		if (player->fmode != 0)
			return false;

		if (player->IsUnconscious())
			return false;

		if (player->attribute[NPC_ATR_HITPOINTS] <= 0)
			return false;

		if (player->sleepingMode != zVOB_AWAKE)
			return false;

		if (player->interactMob || player->interactItem)
			return false;

		if (player->inventory2.IsOpen())
			return false;

		if (!player->IsHuman())
			return false;

		if (player->GetBodyState() >= BS_SWIM)
			return false;

		if (player->anictrl && player->anictrl->IsInWeaponChoose())
			return false;

		if (!oCInformationManager::GetInformationManager().HasFinished())
			return false;

		if (!player->GetEM()->IsEmpty(true))
			return false;

		if (zcon->IsVisible())
			return false;

		return true;
	}

	bool_t CanUseLockPick() {
#if ENGINE == Engine_G1
		return true;
#endif
		zCPar_Symbol* symbol = parser->GetSymbol("NPC_TALENT_PICKLOCK");

		if (!symbol)
			return false;

		int symbolValue;
		symbol->GetValue(symbolValue, 0);
		if (symbolValue <= 0)
			return false;

		int symbolSkill = player->GetTalentSkill(symbolValue);

		if (symbolSkill <= 0) {
			if (!CallFunc(idxNoPicklockTalent))
				Shrugeg(NoPicklockTalent);

			return false;
		}

		return true;
	}

	bool_t HasLockPick(zSTRING lockpickInstanceName) {
		int lockpickIndex = parser->GetIndex(lockpickInstanceName);
		if (lockpickIndex < 0)
			return false;

		oCItem* lockpickItem = player->IsInInv(lockpickIndex, 1);
		if (!lockpickItem)
			return false;

		if (lockpickItem->amount < 1)
			return false;

		return true;
	}

	void HackChest(int atr) {
		zCVob* focusVob = player->GetFocusVob();

		if (!focusVob)
			return;

		oCMobLockable* vob = focusVob->CastTo<oCMobLockable>();
		if (!vob)
			return;

		oCMobContainer* chest = focusVob->CastTo<oCMobContainer>();
		oCMobDoor* door = focusVob->CastTo<oCMobDoor>();

		if (!door && !chest)
			return;

		if (door && !door->sceme.StartWith("DOOR")) {
			player->AI_PlayAni("T_DONTKNOW");
			return;
		}

		if (chest && !player->InSameRoom(focusVob)) {
			player->AI_PlayAni("T_DONTKNOW");
			return;
		}

		oCMsgMovement* msgStopMovement = new oCMsgMovement(oCMsgMovement::EV_STANDUP, 1);
		player->GetEM()->OnMessage(msgStopMovement, player);

		if (!vob->locked) {
			Shrugeg(AlreadyOpened);

			return;
		}

		if (vob->locked && vob->pickLockStr.IsEmpty() && vob->keyInstance.IsEmpty()) {
			if (!CallFunc(idxNeverOpen))
				Shrugeg(NeverOpen);

			return;
		}

		if (vob->locked && vob->pickLockStr.IsEmpty() && !vob->keyInstance.IsEmpty()) {
			if (!CallFunc(idxKeyMissing))
				Shrugeg(KeyMissing);

			return;
		}

		float curDist = player->GetDistanceToVob(*focusVob);
		if (curDist > 250.0f && atr != NPC_ATR_MANA) {
			if (!CallFunc(idxToofar_Away))
				Shrugeg(Toofar_Away);

			return;
		}

		if (!CanUseLockPick())
			return;

		int atrNeeded = CalculateHackChestLevel(vob->pickLockStr.Length());
		int atrPlayer = player->attribute[atr];

		string atrName = "";
		if (atr == NPC_ATR_STRENGTH)
			atrName = Strength;
		if (atr == NPC_ATR_DEXTERITY)
			atrName = Dexterity;
		if (atr == NPC_ATR_MANA)
			atrName = Mana;

		if (atrPlayer < atrNeeded) {
			Shrugeg(NeedMoreAttr + " " + atrName + ": " + atrPlayer + "/" + atrNeeded);

			return;
		}

		zSTRING anim = "";
		int randy = rand() % 100;
		bool_t fail = (CanFail && atrPlayer <= randy) ? true : false;

		if (atr == NPC_ATR_STRENGTH) {
			bool_t kickDoor = false;
			oCItem* weapon = player->GetEquippedMeleeWeapon();

			if (!weapon) {
				if (door) {
					anim = "T_KICKDOOR";
					kickDoor = true;
				}
				else {
					if (!CallFunc(idxMissingItem))
						Shrugeg(MissingItem);

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
				}
			}

			if (kickDoor) {
				player->AI_PlayAni(anim);
			}
			else {
				player->AI_DrawWeapon();
				player->AI_PlayAni(anim);
				player->AI_RemoveWeapon();
			}

			if (kickDoor && fail)
				player->AI_PlayAni("T_FALLB_2_FALLENB");
		}
		else if (atr == NPC_ATR_DEXTERITY) {
#if ENGINE == Engine_G1
			zSTRING lockpickInstanceName = "ITKELOCKPICK";
#else
			zSTRING lockpickInstanceName = "ITKE_LOCKPICK";
#endif
			if (!HasLockPick(lockpickInstanceName)) {
				if (!CallFunc(idxPicklockMissing))
					Shrugeg(PicklockMissing);

				return;
			}

			if (chest) {
				player->AI_PlayAni("T_CHESTBIG_STAND_2_S0");
				player->AI_PlayAni("T_CHESTBIG_S0_UNLOCK");
				player->AI_PlayAni("T_CHESTBIG_S0_2_STAND");
			}
			if (door)
				player->AI_PlayAni("T_DOOR_FRONT_S0_TRY");

			player->RemoveFromInv(lockpickInstanceName, 1);

			if (fail)
				player->AI_PlaySoundFromVob("PICKLOCK_BROKEN", vob);
			else
				player->AI_PlaySoundFromVob("PICKLOCK_SUCCESS", vob);
		}
		else if (atr == NPC_ATR_MANA) {
			if (fail || player->attribute[NPC_ATR_MANAMAX] == atrNeeded) {
				fail = false;
				oCVisualFX* vis = oCVisualFX::CreateAndPlay("SPELLFX_TELEPORT", player, 0, 1, 0, 0, 0);
				player->AI_PlayAni("T_MAGRUN_2_HEASHOOT");
				player->AI_PlaySoundFromVob("PICKLOCK_SUCCESS", vob);
				player->AI_PlayAni("T_HEASHOOT_2_STAND");
				if (vis)
					vis->Release();
			}
			else {
				oCVisualFX* vis = oCVisualFX::CreateAndPlay("SPELLFX_CHARM", player, vob, 1, 0, 0, 0);
				player->AI_PlayAni("T_MAGRUN_2_FBTSHOOT");
				player->AI_PlaySoundFromVob("PICKLOCK_SUCCESS", vob);
				player->AI_PlayAni("T_FBTSHOOT_2_STAND");
				if (vis)
					vis->Release();
			}

			player->attribute[atr] -= atrNeeded;
		}

		player->AssessUseMob_S(vob);

		if (fail) {
			PrintMsg(Z FailedToOpen);
			return;
		}

		PrintMsg(Z OpenedSuccessfully);
		vob->locked = false;
	}

	void Game_Entry() {
	}

	void Game_Init() {
		TSystemLangID lang = Union.GetSystemLanguage();

		InitKeyCodes();

		KeyCombos.insert(std::pair<int, std::vector<int>>(NPC_ATR_STRENGTH, GetKeyCombo(zoptions->ReadString("HackChest", "HotKeyStr", "KEY_T"))));
		KeyCombos.insert(std::pair<int, std::vector<int>>(NPC_ATR_DEXTERITY, GetKeyCombo(zoptions->ReadString("HackChest", "HotKeyDex", "KEY_Y"))));
		KeyCombos.insert(std::pair<int, std::vector<int>>(NPC_ATR_MANA, GetKeyCombo(zoptions->ReadString("HackChest", "HotKeyMan", "KEY_U"))));

		CanFail = zoptions->ReadBool("HackChest", "CanFail", true);

		BaseLevel = zoptions->ReadInt("HackChest", "BaseLevel", 20);
		AttPerLevel = zoptions->ReadInt("HackChest", "AttPerLevel", 5);

		Dexterity = (string)zoptions->ReadString("HackChest", "Dexterity", lang == Lang_Pol ? "zrêcznoœci" : "dexterity");
		Mana = (string)zoptions->ReadString("HackChest", "Mana", lang == Lang_Pol ? "many" : "mana");
		Strength = (string)zoptions->ReadString("HackChest", "Strength", lang == Lang_Pol ? "si³y" : "strength");

		idxKeyMissing = parser->GetIndex("PLAYER_MOB_MISSING_KEY");
		idxMissingItem = parser->GetIndex("PLAYER_MOB_MISSING_ITEM");
		idxNoPicklockTalent = parser->GetIndex("PLAYER_MOB_MISSING_LOCKPICK");
		idxNeverOpen = parser->GetIndex("PLAYER_MOB_NEVER_OPEN");
		idxPicklockMissing = parser->GetIndex("PLAYER_MOB_MISSING_LOCKPICK");
		idxToofar_Away = parser->GetIndex("PLAYER_MOB_TOO_FAR_AWAY");

		AlreadyOpened = (string)zoptions->ReadString("HackChest", "AlreadyOpened", lang == Lang_Pol ? "Ten zamek jest ju¿ otwarty." : "It is already opened.");
		FailedToOpen = (string)zoptions->ReadString("HackChest", "FailedToOpen", lang == Lang_Pol ? "Nie uda³o siê otworzyæ zamka." : "Failed to open the lock.");

		if (idxKeyMissing == Invalid)
			KeyMissing = (string)zoptions->ReadString("HackChest", "KeyMissing", lang == Lang_Pol ? "Potrzebujê w³aœciwego klucza." : "I need the right key.");

		if (idxMissingItem == Invalid)
			MissingItem = (string)zoptions->ReadString("HackChest", "MissingItem", lang == Lang_Pol ? "Brak mi odpowiedniego przedmiotu." : "I don't have the right item.");

		NeedMoreAttr = (string)zoptions->ReadString("HackChest", "NeedMoreAttr", lang == Lang_Pol ? "Potrzebujê wiêcej" : "I need more");

		if (idxNeverOpen == Invalid)
			NeverOpen = (string)zoptions->ReadString("HackChest", "NeverOpen", lang == Lang_Pol ? "Tego nie da siê otworzyæ." : "It will never open.");

		if (idxNoPicklockTalent == Invalid)
			NoPicklockTalent = (string)zoptions->ReadString("HackChest", "NoPicklockTalent", lang == Lang_Pol ? "Brak mi odpowiedniej umiejêtnoœci." : "I don't have that skill.");

		OpenedSuccessfully = (string)zoptions->ReadString("HackChest", "OpenedSuccessfully", lang == Lang_Pol ? "Uda³o siê otworzyæ zamek." : "Lock opened successfully");

		if (idxPicklockMissing == Invalid)
			PicklockMissing = (string)zoptions->ReadString("HackChest", "PicklockMissing", lang == Lang_Pol ? "Potrzebujê wytrycha." : "I need a lockpick.");

		if (idxToofar_Away == Invalid)
			Toofar_Away = (string)zoptions->ReadString("HackChest", "Toofar_Away", lang == Lang_Pol ? "To za daleko." : "It's too far away.");
	}

	void Game_Exit() {
	}

	void Game_PreLoop() {
	}

	void Game_Loop() {
		if (!CanHackChest())
			return;

		if (GetKeyComboToggled(KeyCombos.find(NPC_ATR_STRENGTH)->second))
			HackChest(NPC_ATR_STRENGTH);
		else if (GetKeyComboToggled(KeyCombos.find(NPC_ATR_DEXTERITY)->second))
			HackChest(NPC_ATR_DEXTERITY);
		else if (GetKeyComboToggled(KeyCombos.find(NPC_ATR_MANA)->second))
			HackChest(NPC_ATR_MANA);
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