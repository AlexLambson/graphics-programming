#include "Terrain.h"
#include <math.h>
#include <cmath>
#include "glut.h"

Terrain::Terrain(int x, int y, bool store){
	this->size.x = x;
	this->size.y = y;
	if (store){
		this->GenerateTerrain(GROUND);
		this->GenerateTerrain(WATER);
	}
}
void Terrain::GenerateTerrain(TerrainType terrain){
	if (terrain == GROUND){
		this->GroundPoints.resize(this->size.x + 1);
	}
	else {
		this->WaterPoints.resize(this->size.x + 1);
	}
	for (int i = 0; i < this->size.x + 1; i++){
		if (terrain == GROUND){
			this->GroundPoints[i].resize(this->size.y + 1);
		}
		else {
			this->WaterPoints[i].resize(this->size.y + 1);
		}
		for (int j = 0; j < this->size.y + 1; j++){
			double height = this->GenerateHeight(i, j, terrain);
			WorldPosition point;
			if (terrain == GROUND){
				//glColor3d(GenerateColor(height, RED), GenerateColor(height, GREEN), GenerateColor(height, BLUE));
				point.z = height;
				point.red = GenerateColor(height, RED);
				point.green = GenerateColor(height, GREEN);
				point.blue = GenerateColor(height, BLUE);
				this->GroundPoints[i][j] = point;
			}
			else {
				//glColor4d(0, 0, 0.7, 0.7);
				point.z = height;
				this->WaterPoints[i][j] = point;
			}
		}
	}
}
void Terrain::Draw(TerrainType terrain){
	if (this->GroundPoints.size() > 0){
		this->DrawMemory(terrain);
		return;
	}
	glBegin(GL_QUADS);
		for (int i = 0; i < this->size.x; i++){
			for (int j = 0; j < this->size.y; j++){
				double height = this->GenerateHeight(i, j, terrain);
				if (terrain == GROUND){
					glColor3d(GenerateColor(height, RED), GenerateColor(height, GREEN), GenerateColor(height, BLUE));
				}
				else {
					glColor4d(0, 0, 0.7, 0.5);
				}
				glVertex3d(i, j, height);
				glVertex3d(i + 1, j, this->GenerateHeight(i+1, j, terrain));
				glVertex3d(i + 1, j + 1, this->GenerateHeight(i+1, j+1, terrain));
				glVertex3d(i, j + 1, this->GenerateHeight(i, j+1, terrain));
			}
		}
	glEnd();
}
void Terrain::DrawMemory(TerrainType terrain){
	glBegin(GL_QUADS);
	for (int i = 0; i < this->size.x; i++){
		for (int j = 0; j < this->size.y; j++){
			WorldPosition point;
			if (terrain == WATER){
				point = this->WaterPoints[i][j];
				glColor4d(0, 0, 0.7, 0.5);
				glVertex3d(i, j, point.z);
				glVertex3d(i + 1, j, this->WaterPoints[i + 1][j].z);
				glVertex3d(i + 1, j + 1, this->WaterPoints[i + 1][j + 1].z);
				glVertex3d(i, j + 1, this->WaterPoints[i][j + 1].z);
			}
			else{
				point = this->GroundPoints[i][j];
				glColor3d(point.red, point.green, point.blue);
				glVertex3d(i, j, point.z);
				glVertex3d(i + 1, j, this->GroundPoints[i + 1][j].z);
				glVertex3d(i + 1, j + 1, this->GroundPoints[i + 1][j + 1].z);
				glVertex3d(i, j + 1, this->GroundPoints[i][j + 1].z);
			}
		}
	}
	glEnd();
}
double Terrain::GenerateHeight(double x, double y, TerrainType terrain){
	double z = 0;
	double zScaling = 0.9;
	if (terrain == WATER){
		zScaling = 0.1;
	}
	z += 2 * sin(.4*y);
	z += 1.5 * cos(.3*x);
	z += 4 * sin(.2*x)*cos(.3*y);
	z += 6 * sin(.11*x)*cos(.03*y);
	z *= zScaling;
	if (terrain == WATER){
		z += waterHeight;
	}
	return z;
}
double GenerateColor(double height, Color color){
	double colorValue;
	switch (color)
	{
	case RED:
		//green is always 155 through 255
		colorValue = abs(sin(height * 0.05) - 0.1);
		break;
	case GREEN:
		colorValue = fmax(0.2, abs(sin(height * 0.05)));
		break;
	case BLUE:
		colorValue = fmax(0.2, sin(height * 0.05));
		break;
	default:
		break;
	}
	return colorValue;
}