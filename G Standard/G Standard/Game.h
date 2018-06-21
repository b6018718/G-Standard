#pragma once
class Game
{
public:
	Game();
	~Game();

	Music music;
	Fonts fonts;

	void GameLoop();
};

