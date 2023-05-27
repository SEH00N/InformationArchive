#include <fstream>
#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{

}

bool Stage::Init(const char* fileName)
{
	std::ifstream readStream;
	if (readStream.is_open())
		return false;

	readStream.open(fileName);

	for (int i = 0; i < HEIGHT; ++i)
	{
		readStream.getline(stage[i], WIDTH + 1);

		for (int j = 0; j < WIDTH; ++j)
		{
			if (stage[i][j] == (char)StageBlockType::Start)
			{
				startPos.x = j;
				startPos.y = i;
			}
			if (stage[i][j] == (char)StageBlockType::End)
			{
				endPos.x = j;
				endPos.y = i;
			}
		}
	}
		
	return true;
}

void Stage::Render()
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{

		}
	}
}
