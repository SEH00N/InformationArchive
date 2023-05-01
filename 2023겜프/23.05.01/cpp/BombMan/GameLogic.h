#pragma once

#include <vector>

//#define HORIZONTAL	20
//#define VERTICAL	20

const int HORIZONTAL = 21;
const int VERTICAL = 20;

typedef struct POS_t {
	int x;
	int y;
}POS, *PPOS;

typedef struct PLAYER_t {
	POS tPos;			// ��ġ
	POS tNewPos;
	int iBombPower;		// ��ź �Ŀ�
	int iBombCount;		// ��ź ����
	bool bSlime;		// ������
	bool bWallPush;		// ��Ǫ��
	bool bPushToggle;	// �� �б� ����ġ
}PLAYER, *PPLAYER;

typedef struct BOOM_t {
	int x;
	int y;
	int life;
	bool bDie;
}BOOM, *PBOOM;

enum class MAPTYPE {
	WALL = '0',
	ROAD = '1',
	START = '2',
	END = '3',
	WATERBOMB = 'b',
	TWINKLE = 'p',
	POWER = '4',
	SLIME = '5',
	PUSH = '6'
};

void AsciiArt();
void Init(char _cMaze[VERTICAL][HORIZONTAL], PPLAYER _pPlayer, PPOS _pStartPos, PPOS _pEndPos);
void Update(char _cMaze[VERTICAL][HORIZONTAL], PPLAYER _pPlayer, std::vector<BOOM>& _vecBoom, std::vector<POS>& _vecBoomEffect);
void Render(char _cMaze[VERTICAL][HORIZONTAL], PPLAYER _pPlayer, std::vector<POS>& _vecBoomEffect);

void BombCreate(char _cMaze[VERTICAL][HORIZONTAL], PPLAYER _pPlayer, std::vector<BOOM>& _vecBoom);