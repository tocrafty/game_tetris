#include <iostream>
#include <time.h>
#include <windows.h>
#include "window.h"

using namespace std;
extern int SPEED;

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)



int main() {
	CWindow* window = new CWindow();
	CRules* rules = new CRules();
	CBlock* block = rules->RandomBlock();
	bool gameover = false;
	clock_t frameClock = clock();
	clock_t dropClock = clock();
	clock_t transClock = clock();
	char input;
	while(!gameover){
		if (clock() - frameClock > CLOCKS_PER_SEC/60.0f){
			frameClock = clock();
			if (KEY_DOWN('W'))
				input = 'W';
			if (KEY_DOWN('S'))
				input = 'S';
			if (KEY_DOWN('A'))
				input = 'A';
			if (KEY_DOWN('D'))
				input = 'D';

			if (clock() - transClock > CLOCKS_PER_SEC/60.0f*10){
				transClock = clock();
				if (input == 'W'){
					block->transform(rules);
					input = ' ';
				}
				switch(input){
				case 'S':
					block->Down();
					input = ' ';
					break;
				case 'A':
					rules->BlockLeft(block);
					input = ' ';
					break;
				case 'D':
					rules->BlockRight(block);
					input = ' ';
					break;
				default:
					break;
				}
			}

			//block drop down one tile
			if (clock() - dropClock > CLOCKS_PER_SEC/60.0f*block->speed){
				dropClock = clock();
				if (!rules->BlockDropping(block)){
					rules->Merge(block);
					rules->BlockErase();
					if (rules->score - rules->oldscore > 2){
						rules->oldscore = rules->score;
						SPEED--;
					}
				}
				if (rules->GameOver())
					gameover = true;
			}
			window->Update(block, rules);
			window->Draw();
		}
	}
	cout << "gameover" << endl;
	delete window;
	delete rules;
	delete block;
}