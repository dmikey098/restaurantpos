#pragma once
#include <ios>
#include <iostream>
#include <istream>
#include <iomanip>
#include <limits>
#include <string>
#include <sstream> 
#include <vector>
#include <windows.h>
using namespace std;

void viewLogo();
void centerText(string text, int newLine);
void ClearScreen();
int viewMenu(int, bool);
void viewTitle(string);
void debugScreen(vector<string> str);
void pause();
bool confirm(string);
string getStringInput(string);
double getDoubleInput(string);
int getIntegerInput(string);