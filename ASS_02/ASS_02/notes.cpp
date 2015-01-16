/*
Circle should have a draw and an update function. 

set all values to 0 except the one I am working on
eg. to test for gravity
	v = 0;
	bounce friction = 0;
	air friction = 0;
	gravity = some number;


*/

void Circle::update(){

	///Ideas, super ball;

	/*add gravity{
		dy -= gravity;
	}
	*/
	/*add air friction{
		dx *= air_friction (the closer to veloctiy it is, the closer to a vaccuum it is. [velocity = 1.0; air_friction = 0.999; is mollasses, air_friction = 0.99999999999999999999; is air])
		dy *= ^;
	}
	*/
	/*check wall collisions :: bounce friction{
		dy *= bounce_friciton less close to dy eg. (v = 1.0, bounce = 0.999)
		dx *= ^;
	}
	*/
	/*
	ball to ball collisions{
		Check if they will collide if they continue on this path
	}
	*/
	//adding velocity to position
}
void circle::draw(){

}
/*
1. r = (rand() % 10000) / 10000.0
2. give a number between 0 and 1
3. r /= 5;
4. gives between 0 and .2;
5. r -= .1;
*/