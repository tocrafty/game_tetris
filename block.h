#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include <utility>
#include "rules.h"


class CRules;
class CBlock {
public:
	int speed;
	std::pair<int, int> pos;
	std::vector<std::pair<int, int>> r_pos;
	int states;

	explicit CBlock(int s);
	bool IsValid(CRules*, std::vector<std::pair<int, int>>&);
	virtual ~CBlock() = default;
	virtual void transform(CRules*);
	void Down();
};

class CBlockI : public CBlock {
public:
	explicit CBlockI(int s);
	~CBlockI() = default;
};

class CBlockL : public CBlock {
public:
	explicit CBlockL(int s);
	~CBlockL() = default;
};

class CBlockIL : public CBlock {
public:
	explicit CBlockIL(int s);
	~CBlockIL() = default;
};

class CBlockZ : public CBlock {
public:
	explicit CBlockZ(int s);
	~CBlockZ() = default;
	virtual void transform(CRules*);
};

class CBlockS : public CBlock {
public:
	explicit CBlockS(int s);
	~CBlockS() = default;
	virtual void transform(CRules*);
};

class CBlockT : public CBlock {
public:
	explicit CBlockT(int s);
	~CBlockT() = default;
};

class CBlockX : public CBlock {
public:
	explicit CBlockX(int s);
	~CBlockX() = default;
	virtual void transform(CRules*);
};

#endif