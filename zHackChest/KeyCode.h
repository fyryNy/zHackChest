// Supported with union (c) 2020 Union team
// Union HEADER file

namespace GOTHIC_ENGINE {
	static std::map<string, int> KeyCodes;
	static std::map<string, int> KeyModifiers;

	void InitKeyCodes() {
		KeyCodes.insert(std::pair<string, int>("KEY_ESCAPE", KEY_ESCAPE));
		KeyCodes.insert(std::pair<string, int>("KEY_1", KEY_1));
		KeyCodes.insert(std::pair<string, int>("KEY_2", KEY_2));
		KeyCodes.insert(std::pair<string, int>("KEY_3", KEY_3));
		KeyCodes.insert(std::pair<string, int>("KEY_4", KEY_4));
		KeyCodes.insert(std::pair<string, int>("KEY_5", KEY_5));
		KeyCodes.insert(std::pair<string, int>("KEY_6", KEY_6));
		KeyCodes.insert(std::pair<string, int>("KEY_7", KEY_7));
		KeyCodes.insert(std::pair<string, int>("KEY_8", KEY_8));
		KeyCodes.insert(std::pair<string, int>("KEY_9", KEY_9));
		KeyCodes.insert(std::pair<string, int>("KEY_0", KEY_0));
		KeyCodes.insert(std::pair<string, int>("KEY_MINUS", KEY_MINUS));
		KeyCodes.insert(std::pair<string, int>("KEY_EQUALS", KEY_EQUALS));
		KeyCodes.insert(std::pair<string, int>("KEY_BACK", KEY_BACK));
		KeyCodes.insert(std::pair<string, int>("KEY_TAB", KEY_TAB));
		KeyCodes.insert(std::pair<string, int>("KEY_Q", KEY_Q));
		KeyCodes.insert(std::pair<string, int>("KEY_W", KEY_W));
		KeyCodes.insert(std::pair<string, int>("KEY_E", KEY_E));
		KeyCodes.insert(std::pair<string, int>("KEY_R", KEY_R));
		KeyCodes.insert(std::pair<string, int>("KEY_T", KEY_T));
		KeyCodes.insert(std::pair<string, int>("KEY_Y", KEY_Y));
		KeyCodes.insert(std::pair<string, int>("KEY_U", KEY_U));
		KeyCodes.insert(std::pair<string, int>("KEY_I", KEY_I));
		KeyCodes.insert(std::pair<string, int>("KEY_O", KEY_O));
		KeyCodes.insert(std::pair<string, int>("KEY_P", KEY_P));
		KeyCodes.insert(std::pair<string, int>("KEY_LBRACKET", KEY_LBRACKET));
		KeyCodes.insert(std::pair<string, int>("KEY_RBRACKET", KEY_RBRACKET));
		KeyCodes.insert(std::pair<string, int>("KEY_RETURN", KEY_RETURN));
		KeyCodes.insert(std::pair<string, int>("KEY_LCONTROL", KEY_LCONTROL));
		KeyCodes.insert(std::pair<string, int>("KEY_A", KEY_A));
		KeyCodes.insert(std::pair<string, int>("KEY_S", KEY_S));
		KeyCodes.insert(std::pair<string, int>("KEY_D", KEY_D));
		KeyCodes.insert(std::pair<string, int>("KEY_F", KEY_F));
		KeyCodes.insert(std::pair<string, int>("KEY_G", KEY_G));
		KeyCodes.insert(std::pair<string, int>("KEY_H", KEY_H));
		KeyCodes.insert(std::pair<string, int>("KEY_J", KEY_J));
		KeyCodes.insert(std::pair<string, int>("KEY_K", KEY_K));
		KeyCodes.insert(std::pair<string, int>("KEY_L", KEY_L));
		KeyCodes.insert(std::pair<string, int>("KEY_SEMICOLON", KEY_SEMICOLON));
		KeyCodes.insert(std::pair<string, int>("KEY_APOSTROPHE", KEY_APOSTROPHE));
		KeyCodes.insert(std::pair<string, int>("KEY_GRAVE", KEY_GRAVE));
		KeyCodes.insert(std::pair<string, int>("KEY_LSHIFT", KEY_LSHIFT));
		KeyCodes.insert(std::pair<string, int>("KEY_BACKSLASH", KEY_BACKSLASH));
		KeyCodes.insert(std::pair<string, int>("KEY_Z", KEY_Z));
		KeyCodes.insert(std::pair<string, int>("KEY_X", KEY_X));
		KeyCodes.insert(std::pair<string, int>("KEY_C", KEY_C));
		KeyCodes.insert(std::pair<string, int>("KEY_V", KEY_V));
		KeyCodes.insert(std::pair<string, int>("KEY_B", KEY_B));
		KeyCodes.insert(std::pair<string, int>("KEY_N", KEY_N));
		KeyCodes.insert(std::pair<string, int>("KEY_M", KEY_M));
		KeyCodes.insert(std::pair<string, int>("KEY_COMMA", KEY_COMMA));
		KeyCodes.insert(std::pair<string, int>("KEY_PERIOD", KEY_PERIOD));
		KeyCodes.insert(std::pair<string, int>("KEY_SLASH", KEY_SLASH));
		KeyCodes.insert(std::pair<string, int>("KEY_RSHIFT", KEY_RSHIFT));
		KeyCodes.insert(std::pair<string, int>("KEY_MULTIPLY", KEY_MULTIPLY));
		KeyCodes.insert(std::pair<string, int>("KEY_LMENU", KEY_LMENU));
		KeyCodes.insert(std::pair<string, int>("KEY_SPACE", KEY_SPACE));
		KeyCodes.insert(std::pair<string, int>("KEY_CAPITAL", KEY_CAPITAL));
		KeyCodes.insert(std::pair<string, int>("KEY_F1", KEY_F1));
		KeyCodes.insert(std::pair<string, int>("KEY_F2", KEY_F2));
		KeyCodes.insert(std::pair<string, int>("KEY_F3", KEY_F3));
		KeyCodes.insert(std::pair<string, int>("KEY_F4", KEY_F4));
		KeyCodes.insert(std::pair<string, int>("KEY_F5", KEY_F5));
		KeyCodes.insert(std::pair<string, int>("KEY_F6", KEY_F6));
		KeyCodes.insert(std::pair<string, int>("KEY_F7", KEY_F7));
		KeyCodes.insert(std::pair<string, int>("KEY_F8", KEY_F8));
		KeyCodes.insert(std::pair<string, int>("KEY_F9", KEY_F9));
		KeyCodes.insert(std::pair<string, int>("KEY_F10", KEY_F10));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMLOCK", KEY_NUMLOCK));
		KeyCodes.insert(std::pair<string, int>("KEY_SCROLL", KEY_SCROLL));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPAD7", KEY_NUMPAD7));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPAD8", KEY_NUMPAD8));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPAD9", KEY_NUMPAD9));
		KeyCodes.insert(std::pair<string, int>("KEY_SUBTRACT", KEY_SUBTRACT));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPAD4", KEY_NUMPAD4));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPAD5", KEY_NUMPAD5));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPAD6", KEY_NUMPAD6));
		KeyCodes.insert(std::pair<string, int>("KEY_ADD", KEY_ADD));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPAD1", KEY_NUMPAD1));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPAD2", KEY_NUMPAD2));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPAD3", KEY_NUMPAD3));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPAD0", KEY_NUMPAD0));
		KeyCodes.insert(std::pair<string, int>("KEY_DECIMAL", KEY_DECIMAL));
		KeyCodes.insert(std::pair<string, int>("KEY_OEM_102", KEY_OEM_102));
		KeyCodes.insert(std::pair<string, int>("KEY_F11", KEY_F11));
		KeyCodes.insert(std::pair<string, int>("KEY_F12", KEY_F12));
		KeyCodes.insert(std::pair<string, int>("KEY_F13", KEY_F13));
		KeyCodes.insert(std::pair<string, int>("KEY_F14", KEY_F14));
		KeyCodes.insert(std::pair<string, int>("KEY_F15", KEY_F15));
		KeyCodes.insert(std::pair<string, int>("KEY_KANA", KEY_KANA));
		KeyCodes.insert(std::pair<string, int>("KEY_ABNT_C1", KEY_ABNT_C1));
		KeyCodes.insert(std::pair<string, int>("KEY_CONVERT", KEY_CONVERT));
		KeyCodes.insert(std::pair<string, int>("KEY_NOCONVERT", KEY_NOCONVERT));
		KeyCodes.insert(std::pair<string, int>("KEY_YEN", KEY_YEN));
		KeyCodes.insert(std::pair<string, int>("KEY_ABNT_C2", KEY_ABNT_C2));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPADEQUALS", KEY_NUMPADEQUALS));
		KeyCodes.insert(std::pair<string, int>("KEY_PREVTRACK", KEY_PREVTRACK));
		KeyCodes.insert(std::pair<string, int>("KEY_AT", KEY_AT));
		KeyCodes.insert(std::pair<string, int>("KEY_COLON", KEY_COLON));
		KeyCodes.insert(std::pair<string, int>("KEY_UNDERLINE", KEY_UNDERLINE));
		KeyCodes.insert(std::pair<string, int>("KEY_KANJI", KEY_KANJI));
		KeyCodes.insert(std::pair<string, int>("KEY_STOP", KEY_STOP));
		KeyCodes.insert(std::pair<string, int>("KEY_AX", KEY_AX));
		KeyCodes.insert(std::pair<string, int>("KEY_UNLABELED", KEY_UNLABELED));
		KeyCodes.insert(std::pair<string, int>("KEY_NEXTTRACK", KEY_NEXTTRACK));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPADENTER", KEY_NUMPADENTER));
		KeyCodes.insert(std::pair<string, int>("KEY_RCONTROL", KEY_RCONTROL));
		KeyCodes.insert(std::pair<string, int>("KEY_MUTE", KEY_MUTE));
		KeyCodes.insert(std::pair<string, int>("KEY_CALCULATOR", KEY_CALCULATOR));
		KeyCodes.insert(std::pair<string, int>("KEY_PLAYPAUSE", KEY_PLAYPAUSE));
		KeyCodes.insert(std::pair<string, int>("KEY_MEDIASTOP", KEY_MEDIASTOP));
		KeyCodes.insert(std::pair<string, int>("KEY_VOLUMEDOWN", KEY_VOLUMEDOWN));
		KeyCodes.insert(std::pair<string, int>("KEY_VOLUMEUP", KEY_VOLUMEUP));
		KeyCodes.insert(std::pair<string, int>("KEY_WEBHOME", KEY_WEBHOME));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPADCOMMA", KEY_NUMPADCOMMA));
		KeyCodes.insert(std::pair<string, int>("KEY_DIVIDE", KEY_DIVIDE));
		KeyCodes.insert(std::pair<string, int>("KEY_SYSRQ", KEY_SYSRQ));
		KeyCodes.insert(std::pair<string, int>("KEY_RMENU", KEY_RMENU));
		KeyCodes.insert(std::pair<string, int>("KEY_PAUSE", KEY_PAUSE));
		KeyCodes.insert(std::pair<string, int>("KEY_HOME", KEY_HOME));
		KeyCodes.insert(std::pair<string, int>("KEY_UP", KEY_UP));
		KeyCodes.insert(std::pair<string, int>("KEY_PRIOR", KEY_PRIOR));
		KeyCodes.insert(std::pair<string, int>("KEY_LEFT", KEY_LEFT));
		KeyCodes.insert(std::pair<string, int>("KEY_RIGHT", KEY_RIGHT));
		KeyCodes.insert(std::pair<string, int>("KEY_END", KEY_END));
		KeyCodes.insert(std::pair<string, int>("KEY_DOWN", KEY_DOWN));
		KeyCodes.insert(std::pair<string, int>("KEY_NEXT", KEY_NEXT));
		KeyCodes.insert(std::pair<string, int>("KEY_INSERT", KEY_INSERT));
		KeyCodes.insert(std::pair<string, int>("KEY_DELETE", KEY_DELETE));
		KeyCodes.insert(std::pair<string, int>("KEY_LWIN", KEY_LWIN));
		KeyCodes.insert(std::pair<string, int>("KEY_RWIN", KEY_RWIN));
		KeyCodes.insert(std::pair<string, int>("KEY_APPS", KEY_APPS));
		KeyCodes.insert(std::pair<string, int>("KEY_POWER", KEY_POWER));
		KeyCodes.insert(std::pair<string, int>("KEY_SLEEP", KEY_SLEEP));
		KeyCodes.insert(std::pair<string, int>("KEY_WAKE", KEY_WAKE));
		KeyCodes.insert(std::pair<string, int>("KEY_WEBSEARCH", KEY_WEBSEARCH));
		KeyCodes.insert(std::pair<string, int>("KEY_WEBFAVORITES", KEY_WEBFAVORITES));
		KeyCodes.insert(std::pair<string, int>("KEY_WEBREFRESH", KEY_WEBREFRESH));
		KeyCodes.insert(std::pair<string, int>("KEY_WEBSTOP", KEY_WEBSTOP));
		KeyCodes.insert(std::pair<string, int>("KEY_WEBFORWARD", KEY_WEBFORWARD));
		KeyCodes.insert(std::pair<string, int>("KEY_WEBBACK", KEY_WEBBACK));
		KeyCodes.insert(std::pair<string, int>("KEY_MYCOMPUTER", KEY_MYCOMPUTER));
		KeyCodes.insert(std::pair<string, int>("KEY_MAIL", KEY_MAIL));
		KeyCodes.insert(std::pair<string, int>("KEY_MEDIASELECT", KEY_MEDIASELECT));
		KeyCodes.insert(std::pair<string, int>("KEY_BACKSPACE", KEY_BACKSPACE));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPADSTAR", KEY_NUMPADSTAR));
		KeyCodes.insert(std::pair<string, int>("KEY_LALT", KEY_LALT));
		KeyCodes.insert(std::pair<string, int>("KEY_CAPSLOCK", KEY_CAPSLOCK));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPADMINUS", KEY_NUMPADMINUS));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPADPLUS", KEY_NUMPADPLUS));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPADPERIOD", KEY_NUMPADPERIOD));
		KeyCodes.insert(std::pair<string, int>("KEY_NUMPADSLASH", KEY_NUMPADSLASH));
		KeyCodes.insert(std::pair<string, int>("KEY_RALT", KEY_RALT));
		KeyCodes.insert(std::pair<string, int>("KEY_UPARROW", KEY_UPARROW));
		KeyCodes.insert(std::pair<string, int>("KEY_PGUP", KEY_PGUP));
		KeyCodes.insert(std::pair<string, int>("KEY_LEFTARROW", KEY_LEFTARROW));
		KeyCodes.insert(std::pair<string, int>("KEY_RIGHTARROW", KEY_RIGHTARROW));
		KeyCodes.insert(std::pair<string, int>("KEY_DOWNARROW", KEY_DOWNARROW));
		KeyCodes.insert(std::pair<string, int>("KEY_PGDN", KEY_PGDN));
		KeyCodes.insert(std::pair<string, int>("KEY_CIRCUMFLEX", KEY_CIRCUMFLEX));

		KeyModifiers.insert(std::pair<string, int>("KEY_LCONTROL", KEY_LCONTROL));
		KeyModifiers.insert(std::pair<string, int>("KEY_RCONTROL", KEY_RCONTROL));
		KeyModifiers.insert(std::pair<string, int>("KEY_LSHIFT", KEY_LSHIFT));
		KeyModifiers.insert(std::pair<string, int>("KEY_RSHIFT", KEY_RSHIFT));
		KeyModifiers.insert(std::pair<string, int>("KEY_LMENU", KEY_LMENU));
		KeyModifiers.insert(std::pair<string, int>("KEY_RMENU", KEY_RMENU));
		KeyModifiers.insert(std::pair<string, int>("KEY_LALT", KEY_LALT));
		KeyModifiers.insert(std::pair<string, int>("KEY_RALT", KEY_RALT));
	}

	int GetKeyCode(string key) {
		for (auto it = std::begin(KeyCodes); it != std::end(KeyCodes); ++it)
			if (it->first == key)
				return it->second;

		return Invalid;
	}

	std::vector<int> GetKeyCombo(string combo) {
		std::vector<int> result;
		Array<string> splits = combo.Split("+");

		for (uint i = 0; i < splits.GetNum(); i++) {
			string split = splits[i].Shrink();
			int keyCode = GetKeyCode(split);
			if (keyCode != Invalid)
				result.push_back(keyCode);
		}

		return result;
	}

	bool_t IsKeyModifier(int key) {
		for (auto it = std::begin(KeyModifiers); it != std::end(KeyModifiers); ++it)
			if (it->second == key)
				return true;

		return false;
	}

	bool_t IsAnyModifierPressed() {
		for (auto it = std::begin(KeyModifiers); it != std::end(KeyModifiers); ++it)
			if (zKeyPressed(it->second))
				return true;
		
		return false;
	}

	bool_t GetKeyComboToggled(std::vector<int> combo) {
		if (combo.empty())
			return false;

		if (combo.size() == 1) {
			int key = combo.front();
			if (IsKeyModifier(key))
				return false;

			if (IsAnyModifierPressed())
				return false;

			if (zKeyToggled(key))
				return true;
		}
		else if (combo.size() == 2) {
			if (IsKeyModifier(combo.front()) && IsKeyModifier(combo.back()))
				return false;

			int key1 = combo.front();
			int key2 = combo.back();

			if (zKeyPressed(key1))
				if (zKeyToggled(key2))
					return true;
		}

		return false;
	}
}