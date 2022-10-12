#pragma once

enum LAND_TYPE
{
	LOAD,
	WALL,
	START,
	END,
};

struct Land {
	int pos_x, pos_y;
	int F, G, H; //f는 기대비용 + 사용비용, g는 사용비용, h는 기대비용
	LAND_TYPE land_type;
	int visit_info; //0이면 방문x, 1이면 열기, 2이면 닫기
	Land* pre_land;
};

struct cmp {
	bool operator()(const Land* l1, const Land* l2) {
		return l1->F > l2->F;
	}
};

void initialize_land(Land* land, int pos_x, int pos_y, int f, int g, int h, LAND_TYPE land_type, int visit_info);
bool AStar(struct MapInfo* map_info, int pos_x, int pos_y, int dest_x, int dest_y);
void follow_AStar_route(struct MapInfo* map_info, int pos_x, int pos_y, int dest_x, int dest_y,struct PlayerCharacter* user, float elapsed_time);
void set_land_type(Land* land, LAND_TYPE land_type);
void reset_FGH(MapInfo* map_info);