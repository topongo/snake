// snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <map>
#include <string>


using namespace std;


class body {
public:
	string type;
	int x, y;
};

class fruit {
public:
	int x, y;
};

int main(){
	body head;
	head.x = 40;
	head.y = 12;
	head.type = "head";
	int exec = 0;
	string output;
	bool lose = false;
	while (lose == false) {
		if (exec != 0) {
			output += "-";
		}
		for (int l = 0; l < 25; l++) {
			for (int c = 0; c < 80; c++) {
				if (l == 24 && c == 79);
				else
					if (l == 0 || l == 24) {
						output += "-";
					}
					else
						if (c == 0 || c == 79) {
							output += "|";
						}
						else
							if (c == head.x && l == head.y ) {  output += "O"; }
							else
								output += " ";
			}
		}
		cout << output;
		output = "";
		head.x += 1;
		Sleep(200);
		exec++;

	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
