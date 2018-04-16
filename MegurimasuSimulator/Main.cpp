﻿
# include <Siv3D.hpp> // OpenSiv3D v0.2.4
#include <HamFramework.hpp>
#include "Game.h"
#include "RandomTeam.h"

struct CommonData
{
	const String field_path = U"../Field01.json";
	Game game =
	{
		Field::Create(field_path),
		std::shared_ptr<Team>(new RandomTeam(TeamType::A)),
		std::shared_ptr<Team>(new RandomTeam(TeamType::B))
	};
};

using MyApp = SceneManager<String, CommonData>;

namespace Scenes
{
	struct Game : MyApp::Scene
	{
	public:
		Game(const InitData& init)
			: IScene(init)
		{
			auto data = getData();
			data.field_path;
			data.game.InitAgents(JSONReader(data.field_path)[U"InitPos"].get<Point>());
		}

		void update() override
		{
			if (MouseL.down() || KeyEnter.pressed())
			{
				getData().game.Update();
			}
		}

		void draw() const override
		{
			getData().game.Draw();
		}
	};
}

void Main()
{
	MyApp manager;
	manager.add<Scenes::Game>(U"Game");
	
	FontAsset::Register(U"Cell", 16, Typeface::Black);

	while (System::Update())
	{
		if (!manager.update())
		{
			break;
		}
	}
}
