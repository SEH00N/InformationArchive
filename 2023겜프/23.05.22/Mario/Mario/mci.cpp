#include <windows.h>s
#include <mmsystem.h>
#include <Digitalv.h>

#pragma comment(lib, "winmm.lib")

MCI_OPEN_PARMS openBGM;
MCI_PLAY_PARMS playBGM;
MCI_OPEN_PARMS openEffect;
MCI_PLAY_PARMS playEffect;
UINT deviceID;
UINT deviceID2;

void PlayingBGM()
{
	openBGM.lpstrElementName = TEXT("sound/dreams.mp3");
	openBGM.lpstrDeviceType = TEXT("mpegvideo");
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&openBGM);
	deviceID = openBGM.wDeviceID;
	mciSendCommand(deviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)&playBGM);
}

void PlayingEffect()
{
	openEffect.lpstrElementName = TEXT("sound/random.wav");
	openEffect.lpstrDeviceType = TEXT("waveaudio");
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&openEffect);
	deviceID2 = openEffect.wDeviceID;
	mciSendCommand(deviceID2, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&playEffect);
	Sleep(100);
	mciSendCommand(deviceID2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)&playEffect);
}

int main()
{
	PlayingBGM();
	while (true)
	{
		if(GetAsyncKeyState(VK_RETURN) && 0x8000)
			PlayingEffect();
	}
}