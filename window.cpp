
#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include "window.h"

using namespace std;

CWindow::CWindow(){
	Clear(board);
	Clear(buffer);
}

void CWindow::Clear(string &board){
	string((HEIGHT+5)*(WIDTH+3), ' ').swap(board);
	for (int i = WIDTH + 2; i < board.size(); i += WIDTH+3)
		board[i] = '\n';
	for (int i = 4*(WIDTH + 3); i < board.size(); i += WIDTH+3){
		board[i] = WALL;
		board[i+WIDTH+1] = WALL;
	}
	for (int i = (HEIGHT+4)*(WIDTH+3); i + 1 < board.size(); ++i)
		board[i] = WALL;
}

void CWindow::Update(CBlock* block, CRules *rules) {
	for (int i = 0; i < WIDTH; ++i){
		for (int j = 1; j < HEIGHT + 1; ++j)
			if (rules->land[i][j])
				buffer[(HEIGHT+4-j)*(WIDTH+3)+i+1] = BLOCK;
	}
	for (auto &a : block->r_pos){
		buffer[(HEIGHT + 3 - a.second - block->pos.second) * (WIDTH + 3) +
			a.first + block->pos.first + 1] = BLOCKDROPPING;
	}
	ostringstream oss;
	oss << "\nscore: " << rules->score;
	buffer += oss.str();
}

void CWindow::Draw(){
	board = buffer;
	// system("cls");
	cout << board << endl;
	Clear(buffer);
}
