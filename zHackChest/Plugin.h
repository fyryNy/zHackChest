// This file added in headers queue
// File: "Headers.h"

namespace GOTHIC_ENGINE {
	int BaseLevel;
	int AttPerLevel;

	bool_t CanFail;

	string Dexterity;
	string Mana;
	string Strength;

	string AlreadyOpened;
	string FailedToOpen;
	string KeyMissing;
	string MissingItem;
	string NeedMoreAttr;
	string NeverOpen;
	string NoPicklockTalent;
	string OpenedSuccessfully;
	string PicklockMissing;
	string Toofar_Away;

	int idxKeyMissing;
	int idxMissingItem;
	int idxNeverOpen;
	int idxNoPicklockTalent;
	int idxToofar_Away;
	int idxPicklockMissing;

	static std::map<int, std::vector<int>> KeyCombos;
}