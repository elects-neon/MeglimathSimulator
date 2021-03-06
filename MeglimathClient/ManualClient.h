#pragma once
#include "Client.h"

#include <Siv3D.hpp>

class ManualClient :
	public Client
{
protected:
	virtual Optional<Direction> decideDirection() = 0;
	bool _is_pressed_shift;

public:
	Think NextThink(GameInfo info) override
	{
		// 行動決定していない場合の処理
		for (auto i : step(2))
		{
			if (!_directions[i].has_value())
			{
				_directions[i] = Direction(Random(0, 7));
			}
		}

		// 方向からStepに変換
		Step steps[2];
		for (auto i : step(2))
		{
			if (_is_pressed_shift)
			{
				steps[i].action = Action::RemoveTile;
			}
			else
			{
				steps[i].action = Action::Move;
			}

			steps[i].direction = _directions[i].value();
		}
		Think next_think = { steps[0], steps[1] };

		// 初期化処理
		for (auto & direction : _directions)
		{
			direction.reset();
		}
		_is_ready = false;

		return next_think;
	}

	void Update() override
	{
		if (_is_ready)
		{
			return;
		}

		auto & decide_dir
			= (_directions[0].has_value() ? _directions[1] : _directions[0]);

		decide_dir = decideDirection();

		if (_directions[0].has_value() && _directions[1].has_value())
		{
			_is_ready = true;
		}
	}

public:
	void SetTeamType(TeamType type);

private:
	Optional<Direction> _directions[2];

public:
	ManualClient();
	ManualClient(TeamType type);
	~ManualClient();
};

