#pragma once
#include "Cell.h"
#include "Transform.h"

// TODO: FieldGeneratorを作成

class Field
{
private:
	Grid<Cell> _cells;

public:
	Grid<Cell> GetCells() const;

	/// <summary>
	/// セルを塗る
	/// </summary>
	/// <param name="pos">塗るセルの座標</param>
	/// <param name="team">セルを塗るチーム</param>
	void PaintCell(Point pos, TeamType team);

	/// <summary>
	/// タイルを取る
	/// </summary>
	/// <param name="pos">タイルの座標</param>
	void RemoveTile(Point pos);

public:
	Field();

	void operator=(const Field& other);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="size">フィールドの大きさ</param>
	Field(Size size);

	virtual ~Field();
};
