#pragma once
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <ctime>
#include <iostream>

struct Params
{
	int startPos, endPos;
	const std::vector<std::vector<int>> *matrix;
};
