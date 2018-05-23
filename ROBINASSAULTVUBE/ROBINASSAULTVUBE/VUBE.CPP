#include <iostream>
#include <windows.h>
#include <stdint.h>

uintptr_t address_player = 0x50F4F4;
uintptr_t playerPrimary_ammo = 0x0150;
uintptr_t playerSecondary_ammo = 0x013C;
uintptr_t playerSpeed = 0x0080;
uintptr_t playerHealth = 0x00F8;
uintptr_t noRecoil = 0x4EE444;	
uintptr_t playerZpos = 0x003C;//0x40;

int main() {
	bool speedhack = false;

	HWND acWnd = FindWindowA(0, "AssaultCube");
	if (acWnd) {
		DWORD PID;
		GetWindowThreadProcessId(acWnd, &PID);
		HANDLE acHandle = OpenProcess(PROCESS_ALL_ACCESS, false, PID);

		
		if (acHandle) {
			int player = 0, pAmmo = 0, sAmmo = 0, speed = 1, healthPoints = ((uint32_t)-1) / 2, recoil = 0;
			float zPos = 0.0;
			ReadProcessMemory(acHandle, (LPCVOID)address_player, &player, 4, nullptr);

			playerHealth += player;
			playerPrimary_ammo += player;
			playerSecondary_ammo += player;
			playerSpeed += player;
			playerZpos += player;


			ReadProcessMemory(acHandle, (LPCVOID)playerPrimary_ammo, &pAmmo, 4, nullptr);
			ReadProcessMemory(acHandle, (LPCVOID)playerSecondary_ammo, &sAmmo, 4, nullptr);
			//ReadProcessMemory(acHandle, (LPCVOID)playerHealth, &healthPoints, 4, nullptr);
			//WriteProcessMemory(acHandle, (LPVOID)playerSpeed, &speed, 4, nullptr);
			
			std::cout << "Current Rifle Ammo: " << pAmmo << std::endl;
			std::cout << "Current Pistol Ammo: " << sAmmo << std::endl;
			std::cout << "Current movespeed: " << speed << std::endl;
			std::cout << "haks mad by anomynous" << std::endl;
			while (1) {	
				if(GetAsyncKeyState(0x58)) {
					int tmpSpeed = 0;
					ReadProcessMemory(acHandle, (LPVOID)playerSpeed, &tmpSpeed, 4, nullptr);
					tmpSpeed = tmpSpeed == 1 ? speed : tmpSpeed;
					WriteProcessMemory(acHandle, (LPVOID)playerSpeed, &tmpSpeed, 4, nullptr);
				}
				/*if (speedhack) {
					WriteProcessMemory(acHandle, (LPVOID)playerSpeed, &speed, 4, nullptr);
				}*/

				if (GetAsyncKeyState(VK_F1)) {
					speed = 1;
					while (GetAsyncKeyState(VK_F1)) {}
				}
				else if (GetAsyncKeyState(VK_F2)) {
					speed = 5;
					while (GetAsyncKeyState(VK_F2)) {}
				}
				else if (GetAsyncKeyState(VK_F3)) {
					speed = 25;
					while(GetAsyncKeyState(VK_F3)){}
				}
				else if (GetAsyncKeyState(VK_F4)) {
					speed = 100;
					while (GetAsyncKeyState(VK_F4)) {}
				}
				else if (GetAsyncKeyState(VK_F5)) {
					ReadProcessMemory(acHandle, (LPCVOID)playerZpos, &zPos, sizeof(zPos), nullptr);
					zPos += 0.5;
					WriteProcessMemory(acHandle, (LPVOID)playerZpos, &zPos, sizeof(zPos), nullptr);
					//while(GetAsyncKeyState(VK_F5)) {}
				}
				else if (GetAsyncKeyState(VK_F9)) {
					char lol[255];
					itoa(player, lol, 16);
					MessageBoxA(0, lol, 0, 0);
					while (GetAsyncKeyState(VK_F9)) {}
				}

				/*if (GetAsyncKeyState(0x58)) {
					speedhack = !speedhack;
					while (GetAsyncKeyState(0x58)) {}*/
					//WriteProcessMemory(acHandle, (LPVOID)playerSpeed, &speed, 4, nullptr);
				
			
				DWORD oldProtect;
				VirtualProtectEx(acHandle, (LPVOID)noRecoil, 4, PAGE_READWRITE, &oldProtect);
				WriteProcessMemory(acHandle, (LPVOID)noRecoil, &recoil, 4, nullptr);
				VirtualProtectEx(acHandle, (LPVOID)noRecoil, 4, oldProtect, nullptr);
				
				WriteProcessMemory(acHandle, (LPVOID)playerHealth, &healthPoints, 4, nullptr);
				WriteProcessMemory(acHandle, (LPVOID)playerPrimary_ammo, &pAmmo, 4, nullptr);
				Sleep(10);
			}
			
		} else {
			std::cout << "no process handle" << std::endl;
		}
	}
	else {
		std::cout << "no window handle" << std::endl;
	}
	getchar();
	return 0;
}