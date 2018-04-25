#include "Drawer.h"

void Drawer::DrawField(const Field & field, Array<Agent> agents) const
{
	// セルとタイルポイントの描画
	Rect r;
	
	auto cells = field.GetCells();
	
	for (int i = 0; i < cells.size().x; i++)
	{
		for (int k = 0; k < cells.size().y; k++)
		{
			Point pos(i, k);
			Point top_left_pos = fieldOrigin + pos * cellSize;
			
			r = Rect(top_left_pos, cellSize);

			// エージェントがいる場合タイルを描画しない
			Color tile_color;
			auto is_in_agent = [pos](const Agent & agent) {return agent.GetPosition() == pos; };
			if (agents.includes_if(is_in_agent))
			{
				tile_color = Palette::White;
			}
			else
			{
				tile_color = Transform::ColorOf(cells[k][i].GetTile());
			}

			r.draw(tile_color);

			r.drawFrame(1.0, Palette::Gray);

			FontAsset(U"Cell")(cells[k][i].GetPoint()).drawAt(r.center(), Palette::Black);
		}
	}
}

void Drawer::DrawAgents(std::map<TeamType, Array<Agent>> agents) const
{
	Point pos;
	int32 edge_width = Sqrt(2) * cellSize.x / 2.0;

	auto center = [=](Point pos) {return fieldOrigin + pos * cellSize + cellSize / 2; };
	for(TeamType team : {TeamType::A, TeamType::B})
	{
		// 一人目のエージェントを描画
		Circle(center(agents[team][0].GetPosition()), cellSize.x / 2)
			.drawFrame(2.0, Transform::ColorOf(team));

		// 二人目のエージェントを描画
		Rect(Arg::center = center(agents[team][1].GetPosition()), edge_width).rotated(45_deg)
			.drawFrame(2.0, Transform::ColorOf(team));
	}
}

void Drawer::DrawStatus(const std::map<TeamType, Think> & thinks, const Field & field, int turn) const
{
	if (thinks.size() == 0)
	{
		return;
	}
	
	Array<String> messages =
	{
		U"Team A : ",
		String(U"Agent 1 : ") + Transform::ToString(thinks.at(TeamType::A).steps[0]),
		String(U"Agent 2 : ") + Transform::ToString(thinks.at(TeamType::A).steps[1]),
		String(U"Total Point : ") + ToString(field.GetTotalPoint()[0]),
		String(U"\n"),
		U"Team B : ",
		String(U"Agent 1 : ") + Transform::ToString(thinks.at(TeamType::B).steps[0]),
		String(U"Agent 2 : ") + Transform::ToString(thinks.at(TeamType::B).steps[1]),
		String(U"Total Point : ") + ToString(field.GetTotalPoint()[1]),
		String(U"\n"),
		String(U"Turn : ") + ToString(turn)
	};

	for (int i : step(messages.size()))
	{
		FontAsset(U"Stat")(messages[i]).draw(statOrigin + Point(0, i * 16));
	}
}

Drawer::Drawer()
{
}


Drawer::~Drawer()
{
}

void Drawer::operator=(const Drawer & other)
{}
