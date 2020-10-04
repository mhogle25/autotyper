#include <stdio.h>
#include <stdlib.h>

#define WINVER 0x0500
#include <windows.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void keyPress(INPUT&, int);

int main()
{
	//Begin, prompt user for starting number
	string filename;
	cout << "Enter filename: ";
	cin >> filename;

	// Pause for 5 seconds.
	cout << "Beginning in 5...\n";
	Sleep(1000);
	cout << "4...\n";
	Sleep(1000);
	cout << "3...\n";
	Sleep(1000);
	cout << "2...\n";
	Sleep(1000);
	cout << "1...\n";
	Sleep(1000);

	while (true) {
		ifstream fileStream;
		fileStream.open(filename);

		if (fileStream.is_open()) {
			// This structure will be used to create the keyboard
			// input event.
			INPUT ip;

			while (!fileStream.eof()) {
				string word;
				fileStream >> word;
				int length = word.size();

				for (int i = 0; i < length; i++) {
					char character = word[i];
					character = toupper(character);
					keyPress(ip, (int)character);
					Sleep(10);
				}

				//Press Enter
				keyPress(ip, 0xD);

				Sleep(rand() % 2001);
			}
		} else {
			cout << "The filename was incorrect or the file does not exist.\n";
			main();
			return 0;
		}

		fileStream.close();
	}

	return 0;
}

void keyPress(INPUT& ip, int keyCode) {
	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = keyCode; // virtual-key code for the key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
}