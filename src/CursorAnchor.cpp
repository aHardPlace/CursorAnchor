/*	
 *	Cursor Anchor
 *
 *	Moves the cursor to an anchor point when a key is hit.
 *
 *	Author: github.com/aHardPlace
 *	Version: 1.0
 *
 *	Title art generated at network-science.de/ascii
 */

#include <iostream>
#include <fstream>
#include <vector>

#include <windows.h>

struct key {
	std::string alias;
	int code;
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

	key configKey{"NULL", -1};
	std::vector<std::pair<key, POINT>> anchors;

	{
		std::ifstream configFile("cfg\\anchors.cfg");
		if (!configFile) {
			std::cerr << "Failed to open config file \"res\\anchors.cfg\"" << std::endl;
			return -1;
		}
		while (configFile) {
			int nextChar = configFile.peek();
			if (nextChar == '#' || nextChar == '\n') {
				configFile.ignore(512, '\n');
			}
			else {
				std::string type, alias;
				int code;
				configFile >> type >> alias >> std::hex >> code;
				if (type == "anc") {
					anchors.emplace_back(
						key{
							alias,
							code
						},
						POINT{
							GetSystemMetrics(SM_CXSCREEN) / 2, 
							GetSystemMetrics(SM_CYSCREEN) / 2
						}
					);
				}
				else if (type == "cfg") {
					if (configKey.code == -1) {
						configKey.alias = alias;
						configKey.code = code;
					}
					else {
						std::cout << "Ignoring multiple configuration key assignments." << std::endl;
					}
				}
				else if (nextChar != EOF) {
					std::cerr << "Error reading config file." << std::endl;
				}
			}
		}

		configFile.close();
	}

	std::cout << "\tConfiguration Key: " << configKey.alias << std::endl;
	std::cout << "\tAnchors:" << std::endl;
	for (auto entry: anchors) {
		std::cout << "\t\t" << entry.first.alias << ": [ " << entry.second.x << ", " << entry.second.y << " ]    " << std::endl;
	}

	while (true) {
		for (auto &entry: anchors) {
			if (GetAsyncKeyState(entry.first.code) & 1) { // checking lowest bit stops spam unless button is held
				if (GetAsyncKeyState(configKey.code) & 1) {
					POINT cursor;
					GetCursorPos(&cursor);
					entry.second.x = cursor.x;
					entry.second.y = cursor.y;

					HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
					COORD coord = {0, 13};
					SetConsoleCursorPosition(hStdOut, coord);
					std::cout << "\tConfiguration Key: " << configKey.alias << std::endl;
					std::cout << "\tAnchors:" << std::endl;
					for (auto entry: anchors) {
						std::cout << "\t\t" << entry.first.alias << ": [ " << entry.second.x << ", " << entry.second.y << " ]    " << std::endl;
					}
				}
				else {
					SetCursorPos(entry.second.x, entry.second.y);
				}
			}
		}

		Sleep(40); // sensibly arbitrary milliseconds
	}

	return 0;
}
