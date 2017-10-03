#include "rules.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

int SPEED = 30;

using namespace std;

CRules::CRules() : height(0){
	vector<vector<bool>> (WIDTH, vector<bool>(HEIGHT+5, false)).swap(land);
	for (int i = 0; i < WIDTH; i++)
		land[i][0] = true;
	srand(time(nullptr));
}

bool CRules::BlockDropping(CBlock* block){
	for (auto a : block->r_pos){
		if (land[a.first+block->pos.first][a.second+block->pos.second]){
			return false;
		}
	}
	block->pos.second--;
	return true;
}

//the pointor must be transport by reference, since we use delete and new in this scop!
void CRules::Merge(CBlock* &block) {
	for (auto &b : block->r_pos){
		land[b.first+block->pos.first][b.second+block->pos.second+1] = true;
		bool signal = true;
		for (int i = 0; i < WIDTH; i++){
			if (land[i][b.second+block->pos.second+1] == false){
				signal = false;
				break;
			}
		}
		if (signal){
			erasing.insert(b.second+block->pos.second+1);
		}
		height = std::max(height, b.second + block->pos.second + 1);
	}
	delete block;
	block = RandomBlock();
}

void CRules::BlockErase(){
	int sz = erasing.size();
	if (erasing.size() != 0){
		int i = *erasing.begin(), j = i;
		while(i < HEIGHT+5){
			while(erasing.find(j) != erasing.end()) ++j;
			if (j < HEIGHT+5){
				for (int k = 0; k < WIDTH; k++)
					land[k][i] = land[k][j];
				++j;
			}
			else
				for (int k = 0; k < WIDTH; k++)
					land[k][i] = false;
			++i;
		}
		height -= erasing.size();
		set<int>().swap(erasing);
	}
	score += sz;
}

bool CRules::GameOver(){
	if (height > HEIGHT + 1)
		return true;
	return false;
}

void CRules::BlockLeft(CBlock *block){
	int xMin = WIDTH;
	for (auto &a : block->r_pos)
		xMin = min(xMin, a.first + block->pos.first);
	if (xMin <= 0) return;
	block->pos.first--;
	if (!block->IsValid(this, block->r_pos))
		block->pos.first++;
}

void CRules::BlockRight(CBlock *block){
	int xMax = 0;
	for (auto &a : block->r_pos)
		xMax = max(xMax, a.first + block->pos.first);
	if (xMax >= WIDTH - 1) return;
	block->pos.first++;
	if (!block->IsValid(this, block->r_pos))
		block->pos.first--;
}

CBlock* CRules::RandomBlock() {
	int tmp = rand() % 7;
	switch(tmp){
	case 0:
		return new CBlockI(SPEED);
		break;
	case 1:
		return new CBlockL(SPEED);
		break;
	case 2:
		return new CBlockIL(SPEED);
		break;
	case 3:
		return new CBlockZ(SPEED);
		break;
	case 4:
		return new CBlockS(SPEED);
		break;
	case 5:
		return new CBlockT(SPEED);
		break;
	case 6:
		return new CBlockX(SPEED);
		break;
	}
}

int CRules::score = 0;
int CRules::oldscore = 0;