#include "Physics.h"
#include "Circle.h"
const double COLLISION_FRICTION = 0.99;
struct vectortype
{
	double x;
	double y;
};

Physics::Physics(){
	//nothing for now. 
	//will hold physics variables later
}
void Physics::HandleCollisions(){

	//put collisions into set if handled
	//to check if not 
	for(unsigned int i = 0; i < this->Collidables.size(); i++){
		Shape *me = this->Collidables[i];
		for (unsigned int j = 0; j < this->Collidables.size(); j++){
			if (i == j){
				continue;
			}
			//check set to see if these physics have been handled for these objects
			
			Shape *other = this->Collidables[j];
			if (me->shapeType == Shape::ShapeType::Circle){
				Circle *myCircle = dynamic_cast<Circle *>(me);
				Circle *otherCircle = dynamic_cast<Circle *>(other);
				if (myCircle->Intercepts(otherCircle)){
					this->Collide(i, j);
				}
			}
		}
	}
}
void Physics::ApplyGravity(){
	for each(Shape *shape in Collidables){
		vector<double> myVelocity = shape->shapePoint.GetVelocity();
		myVelocity[1] -= this->Gravity;
		shape->shapePoint.setVelocity(myVelocity[0], myVelocity[1]);
	}
}
void Physics::ApplyAirFriction(){
	for each(Shape *shape in Collidables){
		vector<double> myVelocity = shape->shapePoint.GetVelocity();
		myVelocity[1] *= this->AirFriction;
		myVelocity[0] *= this->AirFriction;
		shape->shapePoint.setVelocity(myVelocity[0], myVelocity[1]);
	}
}
void Physics::UpdateObjects(){
	for each(Shape *shape in this->Collidables){
		shape->Update();
	}
}
void Physics::FindMouseCollisions(int mouseX, int mouseY, double screenX, double screenY){
	mouseX *= 1.0;
	mouseY *= 1.0;
	mouseY = screenY - mouseY;
	Point point = Point(mouseX, mouseY);
	Circle *mouse = new Circle(point, 40.0);
	for each(Shape *shape in this->Collidables){
		Circle *circle = dynamic_cast<Circle *>(shape);
		if (circle->Intercepts(mouse)){
			Point newPoint = circle->GetCenterPoint();
			vector<double> v = newPoint.GetVelocity();
			double x = newPoint.GetX();
			double y = newPoint.GetY();
			if (x > mouseX){
				v[0] += 1.0;
			}
			else{
				v[0] -= 1.0;
			}
			if (y > mouseY){
				v[1] += 1.0;
			}
			else {
				v[1] -= 1.0;
			}
			newPoint.setVelocity(v[0], v[1]);
			circle->setCenterPoint(newPoint);
			this->UpdateObjects();
		}
	}
}
void Physics::Collide(int p1, int p2)//, my_circle particles[])
{
	
	vectortype en; // Center of Mass coordinate system, normal component
	vectortype et; // Center of Mass coordinate system, tangential component
	vectortype u[2]; // initial velocities of two particles
	vectortype um[2]; // initial velocities in Center of Mass coordinates
	double umt[2]; // initial velocities in Center of Mass coordinates, tangent component
	double umn[2]; // initial velocities in Center of Mass coordinates, normal component
	vectortype v[2]; // final velocities of two particles
	double m[2];	// mass of two particles
	double M; // mass of two particles together
	vectortype V; // velocity of two particles together
	double size;
	int i;

	double xdif = this->Collidables[p1]->getnextx() - this->Collidables[p2]->getnextx();
	double ydif = this->Collidables[p1]->getnexty() - this->Collidables[p2]->getnexty();

	// set Center of Mass coordinate system
	size = sqrt(xdif*xdif + ydif*ydif);
	xdif /= size; ydif /= size; // normalize
	en.x = xdif;
	en.y = ydif;
	et.x = ydif;
	et.y = -xdif;

	// set u values
	u[0].x = this->Collidables[p1]->shapePoint.GetVelocityX();
	u[0].y = this->Collidables[p1]->shapePoint.GetVelocityY();
	m[0] = this->Collidables[p1]->getradius()*this->Collidables[p1]->getradius();
	u[1].x = this->Collidables[p2]->shapePoint.GetVelocityX();// getdx();
	u[1].y = this->Collidables[p2]->shapePoint.GetVelocityY();//getdy();
	m[1] = this->Collidables[p2]->getradius()*this->Collidables[p2]->getradius();

	// set M and V
	M = m[0] + m[1];
	V.x = (u[0].x*m[0] + u[1].x*m[1]) / M;
	V.y = (u[0].y*m[0] + u[1].y*m[1]) / M;

	// set um values
	um[0].x = m[1] / M * (u[0].x - u[1].x);
	um[0].y = m[1] / M * (u[0].y - u[1].y);
	um[1].x = m[0] / M * (u[1].x - u[0].x);
	um[1].y = m[0] / M * (u[1].y - u[0].y);

	// set umt and umn values
	for (i = 0; i<2; i++)
	{
		umt[i] = um[i].x * et.x + um[i].y * et.y;
		umn[i] = um[i].x * en.x + um[i].y * en.y;
	}

	// set v values
	for (i = 0; i<2; i++)
	{
		v[i].x = umt[i] * et.x - umn[i] * en.x + V.x;
		v[i].y = umt[i] * et.y - umn[i] * en.y + V.y;
	}

	// reset particle values
	this->Collidables[p1]->shapePoint.setVelocityX(v[0].x*COLLISION_FRICTION);
	this->Collidables[p1]->shapePoint.setVelocityY(v[0].y*COLLISION_FRICTION);
	this->Collidables[p2]->shapePoint.setVelocityX(v[1].x*COLLISION_FRICTION);
	this->Collidables[p2]->shapePoint.setVelocityY(v[1].y*COLLISION_FRICTION);

} /* Collide */