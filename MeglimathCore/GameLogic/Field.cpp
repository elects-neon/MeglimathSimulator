#include "Field.h"

int Field::aggregateAreaPoint(TileType tile)
{
	_status = Grid<bool>(_cells.size() + Point(2, 2), true);

	dfsAreaPoint(Point(0, 0), tile);

	int area_point = 0;
	for (size_t i : step(_status.width()))
	{
		for (size_t k : step(_status.height()))
		{
			if (_status[k][i])
			{
				area_point += Abs(_cells[k - 1][i - 1].GetPoint());
			}
		}
	}

	return area_point;
}


void Field::dfsAreaPoint(Point pos, TileType tile)
{
	// �͈͊O�Ȃ�I��
	if (pos.x < 0 || pos.x > _cells.width() + 1
		|| pos.y < 0 || pos.y > _cells.height() + 1)
	{
		return;
	}

	// �T���ς݂Ȃ�I��
	if (_status[pos.y][pos.x] == false)
	{
		return;
	}

	_status[pos.y][pos.x] = false;
	if (pos.x == 0 || pos.x == _cells.width() + 1 ||
		pos.y == 0 || pos.y == _cells.height() + 1)
	{
		// �[�͒T���̂ݍs��
	}
	else if (_cells[pos.y - 1][pos.x - 1].GetTile() == tile)
	{
		// �������̃^�C�����u����Ă�����I��
		return;
	}

	Point delta[] = { Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0) };

	// �l���֒T������
	for (int i : step(4))
	{
		dfsAreaPoint(pos + delta[i], tile);
	}
}

int Field::aggregateTilePoint(TileType tile)
{
	int sum_tile_point = 0;

	//	�^�C���̎�ނ���v����Z���̓��_�̍��v���v�Z����
	for (size_t i : step(_cells.width()))
	{
		for (size_t k : step(_cells.height()))
		{
			if (_cells[k][i].GetTile() == tile)
			{
				sum_tile_point += _cells[k][i].GetPoint();
			}
		}
	}

	return sum_tile_point;
}

int Field::aggregateTotalPoint(TileType tile)
{
	return aggregateAreaPoint(tile) + aggregateTilePoint(tile);
}

void Field::UpdatePoint()
{
	for (int i : step(2))
	{
		_points[i] = 
		{ aggregateAreaPoint((TileType)i), aggregateTilePoint((TileType)i) };
	}
}

Grid<Cell> Field::GetCells() const
{
	return _cells;
}

Array<int> Field::GetAreaPoints() const
{
	return Array<int>().append({ _points[0].GetArea(), _points[1].GetArea() });
}

Array<int> Field::GetTilePoints() const
{
	return Array<int>().append({ _points[0].GetTile(), _points[1].GetTile() });
}

Array<int> Field::GetTotalPoints() const
{
	return Array<int>().append({ _points[0].GetTotal(), _points[1].GetTotal() });
}

int Field::GetTurn() const
{
	return _turn;
}

void Field::PaintCell(Point pos, TeamType team)
{
	_cells[pos.y][pos.x].PaintedBy(team);
}

void Field::RemoveTile(Point pos)
{
	_cells[pos.y][pos.x].RemoveTile();
}

bool Field::IsInField(Point pos) const
{
	return (0 <= pos.x && pos.x < _cells.width()) && (0 <= pos.y && pos.y < _cells.height());
}

Step Field::DecideStepByDirection(Point pos, Direction dir) const
{
	if (dir == Direction::Stop)
	{
		return Step{ Action::Stop, Direction::Stop };
	}

	// ���W����w��̕����ɐi�񂾌�̍��W
	Point next_pos = pos.moveBy(Transform::DirToDelta(dir));

	if (!IsInField(next_pos))
	{
		return Step{ Action::Stop };
	}

	// �i�񂾐�̃^�C���̗L���ŃA�N�V���������߂�
	if (_cells[next_pos.y][next_pos.x].GetTile() == TileType::None)
	{
		return Step{ Action::Move, dir };
	}
	else
	{
		return Step{ Action::RemoveTile, dir };
	}
}

Field::Field()
{
}

void Field::operator=(const Field & other)
{
	_cells = other._cells;
}


Field::Field(Size size)
	:Field(Grid<Cell>(size))
{}

Field::Field(Grid<Cell> cells)
{
	_cells = cells;
}

Field::Field(FilePath file)
{
	JSONReader json(file);

	Size size = json[U"Size"].get<Size>();
	auto points = json[U"Points"].arrayView();

	// ���͂����^�C���|�C���g�̐�
	Size data_size = Size((size.x + 1) / 2, (size.y + 1) / 2);

	_cells = Grid<Cell>(size);

	// �^�C���|�C���g���O���b�h��ɐ��^���ē���
	int idx = 0;
	for (int i : step(data_size.y))
	{
		for (int k : step(data_size.x))
		{
			_cells[i][k] = points[idx].get<int>();
			// �f�[�^���R�s�[
			_cells[size.y - 1 - i][size.x - 1 - k] = _cells[i][k];
			_cells[size.y - 1 - i][k] = _cells[i][k];
			_cells[i][size.x - 1 - k] = _cells[i][k];

			idx++;
		}
	}

	_turn = json[U"Turn"].get<int>();

	if (json[U"Tiles"].isEmpty())
	{
		return;
	}

	// �e�X�g�p�Ƀ^�C����񂪂���ꍇ�ǂݍ���œ��͂���
	auto tiles = json[U"Tiles"].arrayView();

	for (int i : step(size.y))
	{
		for (int k : step(size.x))
		{
			switch (tiles[i].getString()[k])
			{
			case 'a':
				_cells[i][k].PaintedBy(TeamType::A);
				break;
			case 'b':
				_cells[i][k].PaintedBy(TeamType::B);
				break;
			default:
				break;
			}
		}
	}

}


Field::~Field()
{
}