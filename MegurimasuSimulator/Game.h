#pragma once
#include "FieldDrawer.h"
#include "Field.h"
#include "Team.h"

// TODO: 領域ポイントの処理
class Game
{
private:
	Field _field;
	FieldDrawer _field_drawer;
	Team _teams[2];

	GameInfo getGameInfo() const;
	std::map<TeamType, Array<Agent>> getAgentMap() const;

public:
	void Update();
	void Draw() const;

public:
	Game(const Field &field, Team team_a, Team team_b);
	virtual ~Game();
};
