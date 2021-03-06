#ifndef parser_h
#define parser_h

#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <sstream>
#include <vector>
using namespace std;
using namespace tinyxml2;


typedef struct {
  float x;
  float y;
  float z;
} Ponto;

typedef std::vector<Ponto> pointsStruct;


vector<string> split(const string& s, char delimiter);
vector<string> getfiles (char* path);
vector<Ponto> getpontos(char* path);

#endif