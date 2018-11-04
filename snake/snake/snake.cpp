// snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <map>
#include <string>
#include <random>
#include <ctime>
#include <chrono>


using namespace std;


class piece {
public:
	string type;
	int x, y;
};

class fruit {
public:
	int x, y;
};

fruit Fruit;

void generate_fruit() {
	srand(time(NULL));
	Fruit.x = (rand() % 77) + 2;
	Fruit.y = (rand() % 22) + 2;
}

int main(){
	generate_fruit();
	auto start = std::chrono::high_resolution_clock::now();
	piece head;
	piece *body;
	body = new piece[200];
	int tail_length = 0;
	head.x = 40;
	head.y = 12;
	head.type = "head";
	int exec = 0;
	string output;
	bool lose = false;
	int direction = 2;
	while (lose == false) {



		clock_t first_clock = clock();											//keystrokes
		while (clock() < first_clock + CLOCKS_PER_SEC * 0.1) {
			if (GetKeyState(VK_UP) & 0x8000) direction = 0;
			else if (GetKeyState(VK_DOWN) & 0x8000) direction = 1;
			else if (GetKeyState(VK_LEFT) & 0x8000) direction = 2;
			else if (GetKeyState(VK_RIGHT) & 0x8000) direction = 3;
		}



		if (exec != 0) {														//pointer space
			output += "-";
		}



		char print = NULL;														//printing
		for (int l = 0; l < 25; l++) {
			for (int c = 0; c < 80; c++) {
				print = ' ';
				if (c == 0 || c == 79) print = '|';
				if (l == 0 || l == 24) print = '-';
				if (c == Fruit.x && l == Fruit.y) print = '~';
				if (c == head.x && l == head.y ) print = 'O';
				for (int i = 0; i < 200; i++) {
					if (c == body[i].x && l == body[i].y) print = 'X';
				}
				if (c == 79 && l == 24);
				else output += print;
				print = NULL;
			}
		}
		cout << output;
		output = "";


		




		switch (direction) {													//snake movement
		case 0:
			head.y--;
			for (int i = 0; i < 200; i++) {
				body[i].y--;
			}
			break;
		case 1:
			head.y++;
			for (int i = 0; i < 200; i++) {
				body[i].y++;
			}
			break;
		case 2:
			head.x--;
			for (int i = 0; i < 200; i++) {
				body[i].x--;
			}
			break;
		case 3:
			head.x++;
			for (int i = 0; i < 200; i++) {
				body[i].x++;
			}
			break;
		}




		if (head.x == Fruit.x && head.y == Fruit.y) {							//events
			generate_fruit();
			if (tail_length == 0) {
				body[tail_length].x = head.x;
				body[tail_length].y = head.y;
				tail_length++;
			}
			else {
				body[tail_length].x = body[tail_length - 1].x;
				body[tail_length].y = body[tail_length - 1].y;
				tail_length++;
			}
		}


		exec++;

	}
}