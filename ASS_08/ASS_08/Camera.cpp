#include "Camera.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "Terrain.h"

Camera::Camera(double x, double y, double z){
	this->mPosition.x = x;
	this->mPosition.y = y;
	this->mPosition.z = 0.5 + Terrain::GenerateHeight(x, y, GROUND);
	this->mLookAt.x = 0;
	this->mLookAt.y = 0;
	this->mLookAt.z = 0;
	this->mRotation = 45.0;
	this->mSpeed = 0.05;
	this->minSpeed = 0.05;
	this->maxSpeed = 2.00;
	this->mRotationSpeed = 5.0;
	this->LookAt();
}
WorldPosition Camera::GetPosition(){
	return this->mPosition;
}
WorldPosition Camera::GetLookAt(){
	return this->mLookAt;
}
void Camera::setPosition(WorldPosition position){
	this->mPosition = position;
}
void Camera::setLookAt(WorldPosition lookAt){
	this->mLookAt = lookAt;
}
double Camera::GetRotation(){
	return this->mRotation;
}
double Camera::GetDX(){
	double radians = this->mRotation * M_PI / 180.0;
	double dx = cos(radians) * this->mSpeed;
	return dx;
}
double Camera::GetDY(){
	double radians = this->mRotation * M_PI / 180.0;
	double dy = sin(radians) * this->mSpeed;
	return dy;
}
void Camera::HandleKey(Key::Type key){
	switch (key){
	case Key::UP:
		this->Move();
		break;
	case Key::LEFT:
		this->mRotation += this->mRotationSpeed;
		this->LookAt();
		break;
	case Key::RIGHT:
		this->mRotation -= this->mRotationSpeed;
		this->LookAt();
		break;
	case Key::DOWN:
		this->Move(true);
		break;
	default:
		break;
	}
	return;
}
double Camera::getHeight(bool lookAt){
	double water, ground;
	if (!lookAt){
		ground = 0.5 + Terrain::GenerateHeight(this->mPosition.x, this->mPosition.y, GROUND);
		water = 0.5 + Terrain::GenerateHeight(this->mPosition.x, this->mPosition.y, WATER);
	}
	else {
		ground = 0.5 + Terrain::GenerateHeight(this->mLookAt.x, this->mLookAt.y, GROUND);
		water = 0.5 + Terrain::GenerateHeight(this->mLookAt.x, this->mLookAt.y, WATER);
	}
	if (water > ground){
		return water;
	}
	return ground;
}
void Camera::Move(bool reverse){
	if (!reverse){
		this->mPosition.x += this->GetDX();
		this->mPosition.y += this->GetDY();
		this->mPosition.z = this->getHeight();
	}
	else {
		this->mPosition.x -= this->GetDX();
		this->mPosition.y -= this->GetDY();
		this->mPosition.z = this->getHeight();
	}
	this->LookAt();
	return;
}
void Camera::LookAt(){
	this->mLookAt.x = this->mPosition.x + this->GetDX();
	this->mLookAt.y = this->mPosition.y + this->GetDY();
	this->mLookAt.z = this->getHeight(true);
}
void Camera::ChangeSpeed(double speed){
	double temp = this->mSpeed + speed;
	if (temp < this->minSpeed){
		temp = this->minSpeed;
	}
	if (temp > this->maxSpeed){
		temp = this->maxSpeed;
	}
	this->mSpeed = temp;
}