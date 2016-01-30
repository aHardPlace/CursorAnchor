/*	
 *	Cursor Anchor
 *
 *	Moves the cursor to an anchor point when a key is hit.
 *
 *	Author: github.com/aHardPlace
 *	Version: 1.0
 *  Dependancies: RapidJSON
 *
 *  JSON Configuration file not to exceed 2048 bytes.
 *	Title art generated at network-science.de/ascii
 */

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include <windows.h>

#include <RapidJSON\StringBuffer.h>
#include <RapidJSON\Document.h>
#include <RapidJSON\PrettyWriter.h>

class key {
public:
	key():
		alias(),
		code() {}

	const char *alias;
	int code;
};

class anchor: public key {
public:
	anchor():
		key(),
		point() {}

	POINT point;
};

class anchors {
private:
	rapidjson::Document m_ConfigDocJSON;
	key m_ConfigKey;
	std::vector<anchor> m_Anchors;
	HANDLE m_StdOutHandle;
	short m_PrintRow;

public:
	anchors():
		m_ConfigDocJSON(),
		m_ConfigKey(),
		m_Anchors(),
		m_StdOutHandle(GetStdHandle(STD_OUTPUT_HANDLE)),
		m_PrintRow() {}

	anchors(const anchors&) = delete;
	anchors(const anchors&&) = delete;
	anchors& operator=(const anchors&) = delete;
	anchors& operator=(const anchors&&) = delete;

	void LoadConfig(const char *file) {
		std::FILE *configFile = fopen(file, "rb");
		if (configFile == NULL) {
			std::cout << "ERROR: Failed to load \"cfg\\json.cfg\". Loading default configuration." << std::endl;
			const char *defaultJSON = "{\"configKey\":{\"code\":\"0x71\",\"alias\":\"F2\"},\"anchors\":[{\"code\":\"0x72\",\"alias\":\"F3\"},{\"code\":\"0x73\",\"alias\":\"F4\"}]}";
			m_ConfigDocJSON.Parse(defaultJSON);
		}
		else {
			char configBuffer[2048];
			fread(configBuffer, sizeof(char), 2048, configFile);
			m_ConfigDocJSON.Parse(configBuffer);
			fclose(configFile);
		}

		assert(m_ConfigDocJSON.IsObject());
		assert(m_ConfigDocJSON.HasMember("configKey"));
		assert(m_ConfigDocJSON.HasMember("anchors"));

		m_ConfigKey.alias = m_ConfigDocJSON["configKey"]["alias"].GetString();
		m_ConfigKey.code = strtol(m_ConfigDocJSON["configKey"]["code"].GetString(), NULL, 16);

		for (rapidjson::SizeType i = 0; i < m_ConfigDocJSON["anchors"].Size(); ++i) {
			anchor newAnchor;
			newAnchor.alias = m_ConfigDocJSON["anchors"][i]["alias"].GetString();
			newAnchor.code = strtol(m_ConfigDocJSON["anchors"][i]["code"].GetString(), NULL, 16);
			if (m_ConfigDocJSON["anchors"][i].HasMember("x")) {
				newAnchor.point.x = m_ConfigDocJSON["anchors"][i]["x"].GetInt();
			}
			else {
				newAnchor.point.x = GetSystemMetrics(SM_CXSCREEN) / 2;
			}
			if (m_ConfigDocJSON["anchors"][i].HasMember("y")) {
				newAnchor.point.y = m_ConfigDocJSON["anchors"][i]["y"].GetInt();
			}
			else {
				newAnchor.point.y = GetSystemMetrics(SM_CYSCREEN) / 2;
			}
			m_Anchors.push_back(newAnchor);
		}
	
		CONSOLE_SCREEN_BUFFER_INFO StdOutInfo;
		GetConsoleScreenBufferInfo(m_StdOutHandle, &StdOutInfo);
		m_PrintRow = StdOutInfo.dwCursorPosition.Y;
	}
	void WriteConfig(const char *file) {
		FILE *JSONout = fopen(file, "wb");
		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		writer.SetIndent('\t', 1);
		m_ConfigDocJSON.Accept(writer);
		fputs(buffer.GetString(), JSONout);
		fclose(JSONout);
	}
	void Poll() {
		for (auto &entry: m_Anchors) {
			if (GetAsyncKeyState(entry.code) & 1) { // checking lowest bit stops spam unless button is held
				if (GetAsyncKeyState(m_ConfigKey.code) & 1) {
					POINT cursor;
					GetCursorPos(&cursor);
					entry.point.x = cursor.x;
					entry.point.y = cursor.y;

					COORD printCoord = {0, m_PrintRow};
					SetConsoleCursorPosition(m_StdOutHandle, printCoord);
					Print();
				}
				else {
					SetCursorPos(entry.point.x, entry.point.y);
				}
			}
		}
	}
	void Print() {
		std::cout << "\tConfiguration Key: " << m_ConfigKey.alias << std::endl;
		std::cout << "\tAnchors:" << std::endl;
		for (auto &entry: m_Anchors) {
			std::cout << "\t\t" << entry.alias << ": [ " << entry.point.x << ", " << entry.point.y << " ]    " << std::endl;
		}
	}
};

int main() {
	SetConsoleTitle("Cursor Anchor");

	std::cout <<
		"  ______  __    __  ______       _______   ______   ______           \n" \
		" /      ||  |  |  ||   _  \\     /       | /  __  \\ |   _  \\       \n" \
		"|  ,----'|  |  |  ||  |_)  |   |   (----`|  |  |  ||  |_)  |         \n" \
		"|  |     |  |  |  ||      /     \\   \\    |  |  |  ||      /        \n" \
		"|  `----.|  `--'  ||  |\\  \\------)   |   |  `--'  ||  |\\  \\----. \n" \
		" \\______| \\______/ |__| `.__________/     \\______/ |__| `._____|  \n" \
		"     ___      __   __   ______  __    __   ______   ______           \n" \
		"    /   \\    |  \\ |  | /      ||  |  |  | /  __  \\ |   _  \\      \n" \
		"   /  _  \\   |   \\|  ||  ,----'|  |__|  ||  |  |  ||  |_)  |       \n" \
		"  /  /_\\  \\  |  . `  ||  |     |   __   ||  |  |  ||      /        \n" \
		" /  _____  \\ |  |\\   ||  `----.|  |  |  ||  `--'  ||  |\\  \\----. \n" \
		"/__/     \\__\\|__| \\__| \\______||__|  |__| \\______/ |__| `._____|\n"
	<< std::endl;

	anchors Anchors;
	Anchors.LoadConfig("cfg\\json.cfg");
	Anchors.Print();

	while (true) {
		Anchors.Poll();
		Sleep(40); // sensibly arbitrary milliseconds
	}

	return 0;
}
