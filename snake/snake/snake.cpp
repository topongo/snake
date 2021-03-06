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
string::iterator it;


class piece {
public:
	int x, y;
	bool visible = false;
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
	int exec = 0;
	string output;
	bool lose = false;
	int direction = 2;
	int point = 0;
	int head_x_old = head.x;
	int head_y_old = head.y;
	int last_piece_x_old;
	int last_piece_y_old;
	int point_c;
	int point_d;
	int point_u;
	last_piece_x_old = head.x;
	last_piece_y_old = head.y;
	char input;
	int exit_code;
	bool endspace = false;
	bool retry = true;

	while (retry == true) {
		while (lose == false) {



			clock_t first_clock = clock();											//keystrokes
			do {
				if (GetKeyState(VK_UP) & 0x8000 && direction != 1)direction = 0;
				else if (GetKeyState(VK_DOWN) & 0x8000 && direction != 0) direction = 1;
				else if (GetKeyState(VK_LEFT) & 0x8000 && direction != 3) direction = 2;
				else if (GetKeyState(VK_RIGHT) & 0x8000 && direction != 2) direction = 3;
				if (GetKeyState(VK_ESCAPE) & 0x8000) {
					bool cont = false;
					cout << endl << "Pause Menu:" << endl;
					cout << "      Select function" << endl;
					cout << "         c - Continue" << endl;
					cout << "         e - Exit" << endl;
					cout << "         r - Restart" << endl;
					cin >> input;
					switch (input) {
					case 'c':
						cont = true;
						break;
					case 'e':
						lose = true;
						exit_code = 0;
						break;
					case 'r':
						lose = true;
						exit_code = 1;
						break;
					}
					if (input != 'c' && input != 'e' && input != 'r') {
						cout << endl << "Value inserted incorrect, ";
						cont = true;
					}
					if (cont) {
						cout << "Game will restart in" << endl << "3..." << endl;
						Sleep(1000);
						cout << "2..." << endl;
						Sleep(1000);
						cout << "1..." << endl;
						Sleep(1000);
						endspace = true;
						cont = false;
					}
				}
			} while (clock() < first_clock + CLOCKS_PER_SEC * 0.1);



			if (endspace) endspace = false;											//pointer space
			else if (exec != 0) {
				output += "-";
			}



			char print = NULL;														//printing
			for (int l = 0; l < 25; l++) {
				for (int c = 0; c < 80; c++) {
					print = ' ';
					if (c > 3 && l == 0 && c < 6) print = '0';
					if (c == 0 || c == 79) print = '|';
					if (l == 0 || l == 24) print = '-';
					if (c == Fruit.x && l == Fruit.y) print = '~';
					if (c == head.x && l == head.y) print = 'O';
					for (int i = 0; i < 200; i++) {
						if (c == body[i].x && l == body[i].y && body[i].visible) print = 'X';
					}
					if (c > 3 && l == 0 && c < 7) {
						print = NULL;
					}
					if (c == 79 && l == 24);
					else output += print;
					print = NULL;
				}
			}
			cout << output;
			output = "";




			head_x_old = head.x;													//tail movement init
			head_y_old = head.y;


			for (int i = 200; i > -1; i--) {
				if (body[i].visible == true) {
					last_piece_x_old = body[i].x;
					last_piece_y_old = body[i].y;
					break;
				}
			}

			for (int i = 200; i > 0; i--) {											//tail movement
				body[i].y = body[i - 1].y;
				body[i].x = body[i - 1].x;
			}
			body[0].x = head.x;
			body[0].y = head.y;



			if (head.x < 1 || head.x > 78 || head.y < 1 || head.y > 23) {			//hittedWall event
				lose = true;
				exit_code = 11;
			}



			switch (direction) {													//head movement
			case 0:
				head.y--;
				break;
			case 1:
				head.y++;
				break;
			case 2:
				head.x--;
				break;
			case 3:
				head.x++;
				break;
			}




			if (head.x == Fruit.x && head.y == Fruit.y) {							//getFruit event
				generate_fruit();
				if (tail_length == 0) {
					body[tail_length].visible = true;
					body[tail_length].x = head_x_old;
					body[tail_length].y = head_y_old;
					tail_length++;
				}
				else {
					body[tail_length].visible = true;
					body[tail_length].x = last_piece_x_old;
					body[tail_length].y = last_piece_y_old;
					tail_length++;
				}
			}



			for (int i = 0; i < 200; i++) {												//bitedTail event
				if (body[i].x == head.x && body[i].y == head.y && body[i].visible == true) {
					lose = true;
					exit_code = 10;
				}
			}

			


			exec++;

		}

		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";


		switch (exit_code) {
		case 0:
			cout << "Exited snake successfully\n\nYour score is: " << point;
			retry = false;
			break;
		case 1:
			cout << "Retrying..." << "\n\n\n";
			cout << "Game will restart in" << endl << "3..." << endl;
			Sleep(1000);
			cout << "2..." << endl;
			Sleep(1000);
			cout << "1..." << endl;
			Sleep(1000);
			break;
		case 10:
			cout << "Too bad! You eated your tail!" << endl << "Continue?  (Y/N)";
			cin >> input;
			if (input != 'y') {
				retry = false;
			}
			break;
		case 11:
			cout << "Oh no! You hitted the wall!" << endl << "Continue?  (Y/N)";
			cin >> input;
			if (input != 'y') {
				retry = false;
			}
			break;
		}
		if (retry == true) {															//resetting values
			lose = false;
			exit_code = NULL;
			tail_length = 0;
			head.x = 40;
			head.y = 12;
			exec = 0;
			output;
			lose = false;
			direction = 2;
			point = 0;
			head_x_old = head.x;
			head_y_old = head.y;
			point_c;
			point_d;
			point_u;
			last_piece_x_old = head.x;
			last_piece_y_old = head.y;
			input = ' ';
			exit_code = -1;
			endspace = false;
			for (int i = 0; i < 200; i++) {
				body[i].visible = false;
				generate_fruit();
			}
		}
	}
}