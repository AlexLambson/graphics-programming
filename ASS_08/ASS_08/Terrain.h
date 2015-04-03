#pragma once
#include <cstdlib>
#include <vector>
#include "Helpers.h"
using namespace std;

enum Color
{
	RED,
	GREEN,
	BLUE
};
enum TerrainType{
	GROUND,
	WATER
};
class Terrain{
public:
	Terrain(int x, int y, bool store = false);
	void Draw(TerrainType terrain);
	WorldSize size;
	double static GenerateHeight(double x, double y, TerrainType terrain);
	vector < vector<WorldPosition> > GroundPoints;
	vector < vector<WorldPosition> > WaterPoints;
	void GenerateTerrain(TerrainType terrain);
	void DrawMemory(TerrainType terrain);
	/*
private:
	class point{
	public:
		point(int x, int y, int z);
		void Draw();
		Color mColor;
		ArrayPosition mArrayPos;
		WorldPosition mWorldPosition;
	};
	//no need to store points
	//vector<vector<point>> points;
	*/
};
double GenerateColor(double height, Color color);