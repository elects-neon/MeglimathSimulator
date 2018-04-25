#include "KeyBoardTeam.h"



Optional<Direction> KeyBoardTeam::DecideDirectionByKey()
{
	Optional<Direction> dir = none;

	// Rightから反時計回りに方向キーを指定
	Array<Key> keys = { KeyD, KeyE, KeyW, KeyQ, KeyA, KeyZ, KeyX, KeyC, KeyS };

	for (int i : step(9))
	{
		if (keys[i].down())
		{
			return Optional<Direction>(static_cast<Direction>(i));
		}
	}
	
	return dir;
}

void KeyBoardTeam::Update(const Field & field)
{
	// すでに行動が決定していた場合終了
	if (_next_steps[0].has_value() && _next_steps[1].has_value())
	{
		return;
	}

	// 次にどちらの行動を決定するのかを設定
	int index = (_next_steps[0].has_value() ? 1 : 0);

	Optional<Direction> next_dir = DecideDirectionByKey();

	if (!next_dir.has_value())
	{
		return;
	}

	// 二人目のエージェントの行動が決まったら準備完了
	if (index == 1)
	{
		_is_ready = true;
	}

	_next_steps[index] =
		field.DecideStepByDirection(_agents[index].GetPosition(), next_dir.value());
}

KeyBoardTeam::KeyBoardTeam(TeamType type)
	: Team(type, Agent(), Agent())
{
	_is_ready = false;
}

KeyBoardTeam::KeyBoardTeam(TeamType type, Agent agent1, Agent agent2)
	: Team(type, agent1, agent2)
{
	_is_ready = false;
}

KeyBoardTeam::~KeyBoardTeam()
{
}
