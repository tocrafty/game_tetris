#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include "block.h"
#include "rules.h"

#define BLOCKDROPPING '*'
#define BLOCK 'O'
#define WALL '#'

class CWindow {
	std::string board;
	std::string buffer;

	void Clear(std::string &);
public:
	CWindow();

	void Draw();

	void Update(CBlock*, CRules*);

};

#endif