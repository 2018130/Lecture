#include "AStar.h"
#include "MainLogic.h"
#include "UI.h"
#include <queue>

void initialize_land(Land* land, int pos_x, int pos_y, int f, int g, int h, LAND_TYPE land_type, int visit_info)
{
	if (land == nullptr) return;

	land->pos_x = pos_x;
	land->pos_y = pos_y;
	land->F = f;
	land->G = g;
	land->H = h;
	land->land_type = land_type;
	land->visit_info = visit_info;
}

void set_land_type(Land* land, LAND_TYPE land_type)
{
	if (land == nullptr) return;

	land->land_type = land_type;
}

bool AStar(MapInfo* map_info, int pos_x, int pos_y, int dest_x, int dest_y) {
	if (map_info == nullptr) return false;

	std::priority_queue<Land*, std::vector<Land*>, cmp> pq;
	pq.push(&map_info->lands[pos_y][pos_x]);
	map_info->lands[pos_y][pos_x].F = 0;
	map_info->lands[pos_y][pos_x].G = 0;
	map_info->lands[pos_y][pos_x].H = 0;

	//상 하 좌 우
	int dx[] = { 0, 0, -1, 1 };
	int dy[] = { -1, 1, 0, 0 };
	int max_idx = map_info->map_size - 1;

	while (!pq.empty()) {
		Land* cur_land = pq.top();
		pq.pop();

		if (cur_land->visit_info == 2) continue;
		//방문한 노드 닫기
		cur_land->visit_info = 2;
		//목표 노드이면 스탑
		if (cur_land->pos_x == dest_x && cur_land->pos_y == dest_y) {
			reset_FGH(map_info);
			return true;
		}

		//상, 하, 좌, 우 체크
		for (int i = 0; i < 4; i++) {
			int tmp_x = cur_land->pos_x + dx[i];
			int tmp_y = cur_land->pos_y + dy[i];
			//배열범위 체크
			if (tmp_x < 0 || tmp_y < 0 || tmp_x > max_idx || tmp_y > max_idx) continue;
			if (map_info->lands[tmp_y][tmp_x].visit_info == 2) continue;
			if (map_info->lands[tmp_y][tmp_x].land_type == LAND_TYPE::WALL) continue;

			//기존 f 보다 새 f가 더 작으면 교체
			int new_g = cur_land->G + 10;
			int new_h = (abs(dest_x - tmp_x) + abs(dest_y - tmp_y)) * 5;
			if (new_g + new_h < map_info->lands[tmp_y][tmp_x].F) {
				map_info->lands[tmp_y][tmp_x].F = new_g + new_h;
				map_info->lands[tmp_y][tmp_x].G = new_g;
				map_info->lands[tmp_y][tmp_x].H = new_h;
				map_info->lands[tmp_y][tmp_x].pre_land = cur_land;
			}
			
			//체크한 자리 열기(방문처리)
			map_info->lands[tmp_y][tmp_x].visit_info = 1;
			//체크한 자리 큐에 넣기
			pq.push(&map_info->lands[tmp_y][tmp_x]);
		}
	}

	reset_FGH(map_info);
	return false;
}

void follow_AStar_route(MapInfo* map_info, int pos_x, int pos_y, int dest_x, int dest_y, PlayerCharacter* user, float elapsed_time)
{
	if (map_info->lands[dest_y][dest_x].pre_land != nullptr) {
		Land* pre_land = map_info->lands[dest_y][dest_x].pre_land;

		if (pre_land != nullptr && !(pos_x == dest_x && pos_y == dest_y)) {
			follow_AStar_route(map_info, pos_x, pos_y, pre_land->pos_x, pre_land->pos_y, user, elapsed_time);

			check_key(map_info, user);
			user->pos[0] = pre_land->pos_x;
			user->pos[1] = pre_land->pos_y;

			system("cls");
			display_description(map_info, user, elapsed_time);
			display_map(map_info, dest_x, dest_y);
		}
	}
}

void reset_FGH(MapInfo* map_info)
{
	for (int i = 0; i < map_info->map_size; i++) {
		for (int j = 0; j < map_info->map_size; j++) {
			map_info->lands[i][j].F = BILLION;
			map_info->lands[i][j].G = BILLION;
			map_info->lands[i][j].H = BILLION;
			map_info->lands[i][j].visit_info = 0;
		}
	}
}