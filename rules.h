#ifndef RULES_H
#define RULES_H

#include <vector>
#include <set>
#include "block.h"

#define WIDTH 13
#define HEIGHT 20


class CBlock;
class CRules {
public:
	int height;
	std::set<int> erasing;
	std::vector<std::vector<bool>> land;
	static int score;
	static int oldscore;

	explicit CRules();
	bool BlockDropping(CBlock*);
	void BlockLeft(CBlock*);
	void BlockRight(CBlock*);

	void Merge(CBlock*&);
	void BlockErase(); //set new block
	bool GameOver();
	CBlock* RandomBlock();

};

#endif