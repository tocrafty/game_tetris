#include "block.h"

using namespace std;

CBlock::CBlock(int s) : speed(s), pos(WIDTH/2, HEIGHT), states(1) {
	vector<pair<int, int>>(4).swap(r_pos);
}

bool CBlock::IsValid(CRules *rules, vector<pair<int, int>> &r_pos){
	for (auto &b : r_pos){
		if (rules->land[pos.first+b.first][pos.second+b.second+1])
			return false;
	}
	return true;
}

void CBlock::transform(CRules *rules){
	int tmp = states;
	int old_x = pos.first;
	auto next_r_pos = r_pos;
	{
		tmp = (tmp + 1) % 4 + 1;
		int max = 0, min = WIDTH-1;
		for (auto &a : next_r_pos){
			//x=y, y=-x tranformation
			swap(a.first, a.second);
			a.second = -a.second;
			//get minimum and maximum of x direction
			max = std::max(max, a.first);
			min = std::min(min, a.first);
		}
		if (max + pos.first > WIDTH-1){
			pos.first = WIDTH - 1 - max;
		}
		if (min + pos.first < 0){
			pos.first = -min;
		}
	}
	if (IsValid(rules, next_r_pos)){
		r_pos = next_r_pos;
		states = tmp;
	}
	else {
		pos.first = old_x;
	}
}

void CBlockZ::transform(CRules *rules){
	vector<pair<int, int>> next_r_pos(4);
	switch(states){
	case 1:
		next_r_pos[0] = {-1, 0};
		next_r_pos[1] = {0, 0};
		next_r_pos[2] = {0, -1};
		next_r_pos[3] = {1, -1};
		bool tmp;
		tmp = false;
		if (pos.first == 0) {
			tmp = true;
			pos.first = 1;
		}
		if (IsValid(rules, next_r_pos)) {
			r_pos = next_r_pos;
			states = 2;
		}
		else if (tmp) pos.first = 0;
		break;
	case 2://transform to case 1
		next_r_pos[0] = {0, -1};
		next_r_pos[1] = {0, 0};
		next_r_pos[2] = {1, 0};
		next_r_pos[3] = {1, 1};
		if (IsValid(rules, next_r_pos)) {
			r_pos = next_r_pos;
			states = 1;
		}
		break;
	}
}

void CBlockS::transform(CRules *rules){
	vector<pair<int, int>> next_r_pos(4);
	switch(states){
	case 1:
		next_r_pos[0] = {-1, -1};
		next_r_pos[1] = {0, -1};
		next_r_pos[2] = {0, 0};
		next_r_pos[3] = {1, 0};
		bool tmp;
		tmp = false;
		if (pos.first == 0) {
			tmp = true;
			pos.first = 1;
		}
		if (IsValid(rules, next_r_pos)) {
			r_pos = next_r_pos;
			states = 2;
		}
		else if (tmp) pos.first = 0;
		break;
	case 2:
		next_r_pos[0] = {0, 1};
		next_r_pos[1] = {0, 0};
		next_r_pos[2] = {1, 0};
		next_r_pos[3] = {1, -1};
		if (IsValid(rules, next_r_pos)) {
			r_pos = next_r_pos;
			states = 1;
		}
		break;
	}
}

void CBlockX::transform(CRules *rules){
	return;
}

void CBlock::Down(){
	speed = 3;
}

//initialization

CBlockI::CBlockI(int s) : CBlock(s){
	r_pos[0] = {0, 1};
	r_pos[1] = {0, 0};
	r_pos[2] = {0, -1};
	r_pos[3] = {0, -2};
}

CBlockL::CBlockL(int s) : CBlock(s) {
	r_pos[0] = {-1, 1};
	r_pos[1] = {0, 1};
	r_pos[2] = {0, 0};
	r_pos[3] = {0, -1};
}

CBlockIL::CBlockIL(int s) : CBlock(s) {
	r_pos[0] = {1, 1};
	r_pos[1] = {0, 1};
	r_pos[2] = {0, 0};
	r_pos[3] = {0, -1};
}

CBlockZ::CBlockZ(int s) : CBlock(s) {
	r_pos[0] = {1, 1};
	r_pos[1] = {1, 0};
	r_pos[2] = {0, 0};
	r_pos[3] = {0, -1};
}

CBlockS::CBlockS(int s) : CBlock(s) {
	r_pos[0] = {-1, 1};
	r_pos[1] = {-1, 0};
	r_pos[2] = {0, 0};
	r_pos[3] = {0, -1};
}

CBlockT::CBlockT(int s) : CBlock(s) {
	r_pos[0] = {-1, 0};
	r_pos[1] = {0, 1};
	r_pos[2] = {0, 0};
	r_pos[3] = {1, 0};
}

CBlockX::CBlockX(int s) : CBlock(s) {
	r_pos[0] = {0, 0};
	r_pos[1] = {1, 0};
	r_pos[2] = {0, -1};
	r_pos[3] = {1, -1};
}