#pragma once

#include "FroggerGame.h"

void createLights(){
	_directionalLight = LightSource(LightSource::_num::DIRECTIONAL);
	for(int i = 0; i<6;i++)
		_pointLight[i] = LightSource(LightSource::_num::POINT);
	_spotLight = LightSource(LightSource::_num::SPOTLIGHT);

	_directionalLight.setDirection(0.0f, -1, 0.0f);
	_pointLight[0].setPosition(28.0f, 4.0f, 2.0f);
	_pointLight[1].setPosition(0.0f, 4.0f, 2.0f);
	_pointLight[2].setPosition(-28.0f, 4.0f, 2.0f);
	_pointLight[3].setPosition(28.0f, 4.0f, -25.0f);
	_pointLight[4].setPosition(0.0f, 4.0f, -25.0f);
	_pointLight[5].setPosition(-28.0f, 4.0f, -25.0f);

	_spotLight.setPosition(frog->getPosition());
	_spotLight.setDirection(0,-1,-1);
}

/////////////////////////////////////////////////////////////////////// SHADERs

GLuint setupShaders() {


	
	/////////////////////////////////////////////////

	// Shader for models
	shader.init();

	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/shader.vert");
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/shader.frag");

	// set semantics for the shader variables
	shader.setProgramOutput(0,"outputF");
	shader.setVertexAttribName(VSShaderLib::VERTEX_COORD_ATTRIB, "position");
	shader.setVertexAttribName(VSShaderLib::NORMAL_ATTRIB, "normal");
	shader.setVertexAttribName(VSShaderLib::TEXTURE_COORD_ATTRIB, "texCoord");
	shader.prepareProgram();

	shader.setUniform("texUnit", 0);

	printf("InfoLog for Model Shader\n%s\n\n", shader.getAllInfoLogs().c_str());
	
	return(shader.isProgramValid());
}

void setupFontShader(){

			// Shader for fonts
	shaderF.init();
	shaderF.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/color.vert");
	shaderF.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/color.frag");

	// set semantics for the shader variables
	shaderF.setProgramOutput(0,"outputF");
	shaderF.setVertexAttribName(VSShaderLib::VERTEX_COORD_ATTRIB, "position");
	shaderF.setVertexAttribName(VSShaderLib::TEXTURE_COORD_ATTRIB, "texCoord");

	shaderF.prepareProgram();

	// add sampler uniforms
	shaderF.setUniform("texUnit", 0);

	printf("InfoLog for Font Shader\n%s\n\n", shaderF.getAllInfoLogs().c_str());
}


/////////////////////////////////////////////////////////////////////// SCENE
void updateBillboardAngle(){
	float objToCam[3];
	float objToCamProj[3];
	objToCamProj[0] = frog->getPosition()[0] - tree->getPosition()[0];;
	objToCamProj[1] = 0;
	objToCamProj[2] = frog->getPosition()[2] -  tree->getPosition()[2];

	Lib::vsml->normalize(objToCamProj);

	Lib::vsml->crossProduct(lookat,objToCamProj, upaux);

	angleCosine = Lib::vsml->dotProduct(lookat, objToCamProj);

	if ((angleCosine < 0.99990) && (angleCosine > -0.9999))
      angleCosine = acos(angleCosine)*180.0/3.1415; 
	/*

	objToCam[0] = frog->getPosition()[0] - tree->getPosition()[0];
	objToCam[1] = frog->getPosition()[1] -  tree->getPosition()[1];
	objToCam[2] = frog->getPosition()[2] -  tree->getPosition()[2];


	Lib::vsml->normalize(objToCam);

	angleCosine2 =  Lib::vsml->dotProduct(objToCamProj,objToCam);
	upaux2[0] = 1;
	upaux2[1] = 0;
	upaux2[2] = 0;

	if ((angleCosine2 < 0.99990) && (angleCosine2 > -0.9999)) {
		if (objToCam[1] < 0){
			 angleCosine2 = acos(angleCosine2)*180.0/3.14;
			 upaux2[0] = 1;
		}
		else{
			angleCosine2 = acos(angleCosine2)*180.0/3.14;
			upaux2[0] = -1;
		}
	}
	else
		angleCosine2 = 0;
		*/
}

void updateStaticScenario(){
	//if(camera == MOBILE)
	updateBillboardAngle();

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	tree->update(angleCosine, angleCosine2, upaux[0], upaux[1], upaux[2], upaux2[0], upaux2[1], upaux2[2]);
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	bottomRoadside->update();
	Lib::vsml->popMatrix(VSMathLib::MODEL);
	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	upperRoadside->update();
	Lib::vsml->popMatrix(VSMathLib::MODEL);
	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	road->update();
	Lib::vsml->popMatrix(VSMathLib::MODEL);
	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	river->update();
	Lib::vsml->popMatrix(VSMathLib::MODEL);
	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	upperRiverside->update();
	Lib::vsml->popMatrix(VSMathLib::MODEL);

}

void drawTimberlogs(int row, int direction){
	int r;
	float f;
	float speed[3];
	int place;

	switch(row) {
	case LOG_ONE: 
		place = 0; 
		break;
	case LOG_TWO: 
		place = 1; 
		break;
	case LOG_THREE: 
		place = 2; 
		break;
	}

	if(direction == RIGHT)
		f = -TIMBERLOG_SPEED;
	if(direction == LEFT)
		f = TIMBERLOG_SPEED;

	speed[0] = f * elapsed; speed[1] = 0; speed[2] = 0;

	for (int i = 0; i < OBJS_PER_ROW; i++){
		timberlogs->at(place*OBJS_PER_ROW + i) = new TimberLog(speed, row, direction);
		r = Lib::random(5,10);
		timberlogs->at(place*OBJS_PER_ROW + i)->setHeight(r);
		timberlogs->at(place*OBJS_PER_ROW + i)->draw();
	}

}

void drawTurtles(int row, int direction){
	float f;
	float speed[3];
	int place;

	switch(row){
	case TURTLE_ONE:
		place = 0;
		break;
	case TURTLE_TWO:
		place = 1;
		break;
	}

	if(direction == RIGHT)
		f = -TURTLE_SPEED;
	if(direction == LEFT)
		f = TURTLE_SPEED;

	speed[0] = f * elapsed; speed[1] = 0; speed[2] = 0;

	for (int i = 0; i < OBJS_PER_ROW; i++){
		turtles->at(place*OBJS_PER_ROW + i) = new Turtle(speed, row, direction);
		turtles->at(place*OBJS_PER_ROW + i)->draw();
	}
}

void drawBuses(int row, int direction){
	float f;
	float speed[3];
	int place;

	switch(row){
	case BUS_ONE: 
		place = 0; 
		break;
	case BUS_TWO: 
		place = 1; 
		break;
	}

	if(direction == RIGHT)
		f = -BUS_SPEED;
	if(direction == LEFT)
		f = BUS_SPEED;

	speed[0] = f * elapsed; speed[1] = 0; speed[2] = 0;

	for (int i = 0; i < OBJS_PER_ROW; i++){
		buses->at(place*OBJS_PER_ROW + i) = new Bus(speed, row, direction);
		buses->at(place*OBJS_PER_ROW + i)->draw();
	}
}

void drawCars(int row, int direction){
	float f;
	float speed[3];
	int place;

	switch(row){
	case CAR_ONE: 
		place = 0;
		break;
	case CAR_TWO: 
		place = 1;
		break;
	case CAR_THREE:
		place = 2;
		break;
	}

	if(direction == RIGHT)
		f = -CAR_SPEED;
	if(direction == LEFT)
		f = CAR_SPEED;

	speed[0] = f * elapsed; speed[1] = 0; speed[2] = 0;

	for (int i = 0; i < OBJS_PER_ROW; i++){
		cars->at(place*OBJS_PER_ROW + i) = new Car(speed, row, direction);
		cars->at(place*OBJS_PER_ROW + i)->draw();
	}
}

void initDynamicObjects() {
	timberlogs = new std::vector<TimberLog *>(3 * OBJS_PER_ROW);
	turtles = new std::vector<Turtle *>(2 * OBJS_PER_ROW);
	buses = new std::vector<Bus *>(2 * OBJS_PER_ROW);
	cars = new std::vector<Car *> (3 * OBJS_PER_ROW);
}

void drawObjects(){

	drawTimberlogs(LOG_THREE, RIGHT);
	drawTurtles(TURTLE_TWO, RIGHT);
	drawTimberlogs(LOG_TWO, LEFT);
	drawTimberlogs(LOG_ONE, RIGHT);
	drawTurtles(TURTLE_ONE, LEFT);
	drawBuses(BUS_TWO, RIGHT);
	drawCars(CAR_THREE, LEFT);
	drawCars(CAR_TWO, RIGHT);
	drawBuses(BUS_ONE, LEFT);
	drawCars(CAR_ONE, RIGHT);
}


void updateTimberlogsPosition(int delta_t) {
	for(int j = 0; j < 3; j++)
		for (int i = 0; i < OBJS_PER_ROW; i++)
			timberlogs->at(j*OBJS_PER_ROW + i)->move(delta_t);
}

void updateTurtlesPosition(int delta_t) {
	for(int j = 0; j < 2; j++)
		for (int i = 0; i < OBJS_PER_ROW; i++)
			turtles->at(j*OBJS_PER_ROW + i)->move(delta_t);
}

void updateBusesPosition(int delta_t) {
	for(int j = 0; j < 2; j++)
		for (int i = 0; i < OBJS_PER_ROW; i++)
			buses->at(j*OBJS_PER_ROW + i)->move(delta_t);
}

void updateCarsPosition(int delta_t) {
	for(int j = 0; j < 3; j++)
		for (int i = 0; i < OBJS_PER_ROW; i++)
			cars->at(j*OBJS_PER_ROW + i)->move(delta_t);
}

void updateFrogPosition(int delta_t) {
	if(frogMovement == LEFT)
		frog->moveLeft(delta_t);
	if(frogMovement == RIGHT)
		frog->moveRight(delta_t);
	if(frogMovement == FRONT)
		frog->moveUp(delta_t);
	if(frogMovement == BACK)
		frog->moveDown(delta_t);
}

void updateTimberlogs() {
	for(int j = 0; j < 3; j++)
		for (int i = 0; i < OBJS_PER_ROW; i++)
			timberlogs->at(j*OBJS_PER_ROW + i)->update();
}

void updateTurtles() {

	for(int j = 0; j < 2; j++)
		for (int i = 0; i < OBJS_PER_ROW; i++)
			turtles->at(j*OBJS_PER_ROW + i)->update();
}

void updateBuses() {
	for(int j = 0; j < 2; j++)
		for (int i = 0; i < OBJS_PER_ROW; i++)
			buses->at(j*OBJS_PER_ROW + i)->update();
}

void updateCars() {
	for(int j = 0; j < 3; j++)
		for (int i = 0; i < OBJS_PER_ROW; i++)
			cars->at(j*OBJS_PER_ROW + i)->update();
}

void hitObstacle(){
	frog->initialPos();
	totalLifes -= 1;
	vsfl.prepareSentence(lifes, "Lifes: " + std::to_string(totalLifes));
}

void getPoints(){
	totalPoints += 10;
	vsfl.prepareSentence(points, "Points: " + std::to_string(totalPoints));
}

void resetPosition(){
	frog->initialPos();
}

DynamicObject *tur, *tim;
float speed;
void checkForCollision(int delta_t){

	frog->resetSpeed();

	if(frog->collide(upperRiverside->getBox())){
		getPoints();
		resetPosition();
	}

	for (auto & element : *cars) {
		if(frog->collide(element->getBox())) hitObstacle();
	}

	for (auto & element : *buses) {
		if(frog->collide(element->getBox())) hitObstacle();
	}

		//if on the river
	if(frog->collide(river->getBox())){

	for (auto & element : *turtles) {
		if(frog->collide(element->getBox())){
			tur = element; 
			break;}  else tur = NULL;
		
	}

	for (auto & element : *timberlogs) {
		if(frog->collide(element->getBox())){
			tim = element;
			break;}  else tim = NULL;
	}

	if(tim != NULL && frog->collide(tim->getBox())
		|| tur != NULL && frog->collide(tur->getBox())){

		if(tur != NULL){
			speed = tur->getSpeed()[0];
			if(speed < 0){
				frog->assumeSpeed(-speed);
				frog->moveRight(delta_t);}
			else{
			frog->assumeSpeed(+speed);
			frog->moveLeft(delta_t);
			}
		} else{
			speed = tim->getSpeed()[0];
			if(speed < 0){
				frog->assumeSpeed(-speed);
				frog->moveRight(delta_t);}
			else{
			frog->assumeSpeed(+speed);
			frog->moveLeft(delta_t);
			}
		}

	} else hitObstacle();

	}
}

void endGame(){
	frogMovement = -1;
	gameOver = true;
}

void updateObjectsPosition(int delta_t){
	
	if(totalLifes < 1) endGame();

	updateTimberlogsPosition(delta_t);
	updateTurtlesPosition(delta_t);
	updateBusesPosition(delta_t);
	updateCarsPosition(delta_t);

	updateFrogPosition(delta_t);

	checkForCollision(delta_t);

	_spotLight.setPosition(frog->getPosition());

	if(frogMovement == LEFT)
	_spotLight.setDirection(1,-1 ,0);
	else if(frogMovement == RIGHT)
	_spotLight.setDirection(-1,-1 ,0);
	else if(frogMovement == FRONT)
	_spotLight.setDirection(0,-1 ,-1);
	else if(frogMovement == BACK)
	_spotLight.setDirection(0,-1 ,1);
}

void updateObjects(){
	frog->update();
	updateTimberlogs();
	updateTurtles();
	updateBuses();
	updateCars();
}

void animate(int value)
{
	// Set up the next timer tick
	glutTimerFunc(TIMERMSECS, animate, 0);

	// Measure the elapsed time
	float currTime = glutGet(GLUT_ELAPSED_TIME);
	int timeSincePrevFrame = currTime - prevTime;
	float elapsedTime = currTime - startTime;
	elapsed = (elapsedTime + 100000) * 0.00001f;

	//update the objects
	updateObjectsPosition(timeSincePrevFrame);

	// Force a redisplay to render the new image
	glutPostRedisplay();

	prevTime = currTime;
}

void updateUniforms(){
	GLint myLoc;
	int p = shader.getProgramIndex();
	GLfloat white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat cutoff = 0.9;
	GLfloat spotexponent = 5;
	GLfloat constant = 1, linear = 1, quadratic = 1;

	myLoc = glGetUniformLocation(p, "Lights[0].isEnabled");
	glProgramUniform1iv(p, myLoc, 1, &_pointLightOn);

	myLoc = glGetUniformLocation(p, "Lights[1].isEnabled");
	glProgramUniform1iv(p, myLoc, 1, &_pointLightOn);

	myLoc = glGetUniformLocation(p, "Lights[2].isEnabled");
	glProgramUniform1iv(p, myLoc, 1, &_pointLightOn);

	myLoc = glGetUniformLocation(p, "Lights[3].isEnabled");
	glProgramUniform1iv(p, myLoc, 1, &_pointLightOn);

	myLoc = glGetUniformLocation(p, "Lights[4].isEnabled");
	glProgramUniform1iv(p, myLoc, 1, &_pointLightOn);

	myLoc = glGetUniformLocation(p, "Lights[5].isEnabled");
	glProgramUniform1iv(p, myLoc, 1, &_pointLightOn);

	myLoc = glGetUniformLocation(p, "Lights[6].isEnabled");
	glProgramUniform1iv(p, myLoc, 1, &_spotLightOn);

	myLoc = glGetUniformLocation(p, "Lights[7].isEnabled");
	glProgramUniform1iv(p, myLoc, 1, &_directionalLightOn);

	////

	myLoc = glGetUniformLocation(p, "Lights[0].isLocal");
	glProgramUniform1iv(p, myLoc, 1, &YES);

	myLoc = glGetUniformLocation(p, "Lights[1].isLocal");
	glProgramUniform1iv(p, myLoc, 1, &YES);

	myLoc = glGetUniformLocation(p, "Lights[2].isLocal");
	glProgramUniform1iv(p, myLoc, 1, &YES);

	myLoc = glGetUniformLocation(p, "Lights[3].isLocal");
	glProgramUniform1iv(p, myLoc, 1, &YES);

	myLoc = glGetUniformLocation(p, "Lights[4].isLocal");
	glProgramUniform1iv(p, myLoc, 1, &YES);

	myLoc = glGetUniformLocation(p, "Lights[5].isLocal");
	glProgramUniform1iv(p, myLoc, 1, &YES);

	myLoc = glGetUniformLocation(p, "Lights[6].isLocal");
	glProgramUniform1iv(p, myLoc, 1, &YES);

	myLoc = glGetUniformLocation(p, "Lights[7].isLocal");
	glProgramUniform1iv(p, myLoc, 1, &NO);

	////

	myLoc = glGetUniformLocation(p, "Lights[0].isSpot");
	glProgramUniform1iv(p, myLoc, 1, &NO);

	myLoc = glGetUniformLocation(p, "Lights[1].isSpot");
	glProgramUniform1iv(p, myLoc, 1, &NO);

	myLoc = glGetUniformLocation(p, "Lights[2].isSpot");
	glProgramUniform1iv(p, myLoc, 1, &NO);

	myLoc = glGetUniformLocation(p, "Lights[3].isSpot");
	glProgramUniform1iv(p, myLoc, 1, &NO);

	myLoc = glGetUniformLocation(p, "Lights[4].isSpot");
	glProgramUniform1iv(p, myLoc, 1, &NO);

	myLoc = glGetUniformLocation(p, "Lights[5].isSpot");
	glProgramUniform1iv(p, myLoc, 1, &NO);

	myLoc = glGetUniformLocation(p, "Lights[6].isSpot");
	glProgramUniform1iv(p, myLoc, 1, &YES);

	myLoc = glGetUniformLocation(p, "Lights[7].isSpot");
	glProgramUniform1iv(p, myLoc, 1, &NO);

	////

	myLoc = glGetUniformLocation(p, "Lights[0].color");
	glProgramUniform4fv(p, myLoc, 1, white);

	myLoc = glGetUniformLocation(p, "Lights[1].color");
	glProgramUniform4fv(p, myLoc, 1, white);

	myLoc = glGetUniformLocation(p, "Lights[2].color");
	glProgramUniform4fv(p, myLoc, 1, white);

	myLoc = glGetUniformLocation(p, "Lights[3].color");
	glProgramUniform4fv(p, myLoc, 1, white);

	myLoc = glGetUniformLocation(p, "Lights[4].color");
	glProgramUniform4fv(p, myLoc, 1, white);

	myLoc = glGetUniformLocation(p, "Lights[5].color");
	glProgramUniform4fv(p, myLoc, 1, white);

	myLoc = glGetUniformLocation(p, "Lights[6].color");
	glProgramUniform4fv(p, myLoc, 1, white);

	myLoc = glGetUniformLocation(p, "Lights[7].color");
	glProgramUniform4fv(p, myLoc, 1, white);

	/////

	myLoc = glGetUniformLocation(p, "Lights[0].position");
	glProgramUniform3fv(p, myLoc, 1, _pointLight[0].getPosition());

	myLoc = glGetUniformLocation(p, "Lights[1].position");
	glProgramUniform3fv(p, myLoc, 1, _pointLight[1].getPosition());

	myLoc = glGetUniformLocation(p, "Lights[2].position");
	glProgramUniform3fv(p, myLoc, 1, _pointLight[2].getPosition());

	myLoc = glGetUniformLocation(p, "Lights[3].position");
	glProgramUniform3fv(p, myLoc, 1, _pointLight[3].getPosition());

	myLoc = glGetUniformLocation(p, "Lights[4].position");
	glProgramUniform3fv(p, myLoc, 1, _pointLight[4].getPosition());

	myLoc = glGetUniformLocation(p, "Lights[5].position");
	glProgramUniform3fv(p, myLoc, 1, _pointLight[5].getPosition());

	myLoc = glGetUniformLocation(p, "Lights[6].position");
	glProgramUniform3fv(p, myLoc, 1, _spotLight.getPosition());

	myLoc = glGetUniformLocation(p, "Lights[7].position");
	glProgramUniform3fv(p, myLoc, 1, _directionalLight.getDirection());

	/////

	myLoc = glGetUniformLocation(p, "Lights[6].coneDirection");
	glProgramUniform3fv(p, myLoc, 1, _spotLight.getDirection());

	/////

	myLoc = glGetUniformLocation(p, "Lights[6].spotCosCutoff");
	glProgramUniform1fv(p, myLoc, 1, &cutoff);

	/////

	myLoc = glGetUniformLocation(p, "Lights[6].spotExponent");
	glProgramUniform1fv(p, myLoc, 1, &spotexponent);

	/////

	myLoc = glGetUniformLocation(p, "Lights[0].constantAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &constant);

	myLoc = glGetUniformLocation(p, "Lights[1].constantAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &constant);

	myLoc = glGetUniformLocation(p, "Lights[2].constantAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &constant);

	myLoc = glGetUniformLocation(p, "Lights[3].constantAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &constant);

	myLoc = glGetUniformLocation(p, "Lights[4].constantAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &constant);

	myLoc = glGetUniformLocation(p, "Lights[5].constantAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &constant);

	myLoc = glGetUniformLocation(p, "Lights[6].constantAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &constant);

	myLoc = glGetUniformLocation(p, "Lights[7].constantAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &constant);

	/////

	myLoc = glGetUniformLocation(p, "Lights[0].linearAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &linear);

	myLoc = glGetUniformLocation(p, "Lights[1].linearAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &linear);

	myLoc = glGetUniformLocation(p, "Lights[2].linearAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &linear);

	myLoc = glGetUniformLocation(p, "Lights[3].linearAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &linear);

	myLoc = glGetUniformLocation(p, "Lights[4].linearAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &linear);

	myLoc = glGetUniformLocation(p, "Lights[5].linearAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &linear);

	myLoc = glGetUniformLocation(p, "Lights[6].linearAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &linear);

	myLoc = glGetUniformLocation(p, "Lights[7].linearAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &linear);

	/////

	myLoc = glGetUniformLocation(p, "Lights[0].quadraticAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &quadratic);

	myLoc = glGetUniformLocation(p, "Lights[1].quadraticAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &quadratic);

	myLoc = glGetUniformLocation(p, "Lights[2].quadraticAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &quadratic);

	myLoc = glGetUniformLocation(p, "Lights[3].quadraticAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &quadratic);

	myLoc = glGetUniformLocation(p, "Lights[4].quadraticAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &quadratic);

	myLoc = glGetUniformLocation(p, "Lights[5].quadraticAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &quadratic);

	myLoc = glGetUniformLocation(p, "Lights[6].quadraticAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &quadratic);

	myLoc = glGetUniformLocation(p, "Lights[7].quadraticAttenuation");
	glProgramUniform1fv(p, myLoc, 1, &quadratic);
}

void StencilFunction(){
	glEnable(GL_STENCIL_TEST);
	glClearStencil(0x0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT  | GL_STENCIL_BUFFER_BIT);

	Lib::vsml->loadIdentity(VSMathLib::VIEW);
	Lib::vsml->loadIdentity(VSMathLib::MODEL);

	// set camera
	switch(camera){
	case PERSPECTIVE:
		Lib::vsml->lookAt(0, 35, -45, 0,0,0, 0,0,1);
		StencilFunction();
		break;
	case ORTHO:
		glDisable(GL_STENCIL_TEST);
		Lib::vsml->lookAt(0, 10, 0, 0,0,0, 0,0,1);
		break;
	case MOBILE:
		glDisable(GL_STENCIL_TEST);
		cameraPosition[0] = frog->getPosition()[0]+0.25;
		cameraPosition[1] = 4.0f;
		cameraPosition[2] =  frog->getPosition()[2]-2;

		Lib::vsml->lookAt(cameraPosition[0], cameraPosition[1],cameraPosition[2],
			frog->getPosition()[0]+camX, frog->getPosition()[1]+camY,  frog->getPosition()[2] + 5+camZ,
			0.0f, 1.0f,  0.0f);
		break;
	}

	updateUniforms();

	// use our shader
	glUseProgram(shader.getProgramIndex());

	//glStencilFunc(GL_ALWAYS, 1, 1);
	//glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	updateStaticScenario();

	glClear(GL_DEPTH_BUFFER_BIT); // inicializa o z_buffer
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glStencilFunc(GL_EQUAL, 1, 1);

	updateObjects();

	 for (int i=0; i<MAX_PARTICULAS; i++)
	{
		if(particles[i].life > 0.0f) /* só desenha as que ainda estão vivas */
		{
			particles[i].update();
		}
	}

	 		if(camera == MOBILE && flareOn){

			float fy = 1.0 - lookat_Y / 10 - 2.5;

			if(fy > 0) {

				float cosine = abs(fy / sqrt(fy*fy + 12.25));

				Lib::vsml->pushMatrix(VSMathLib::PROJECTION);
				Lib::vsml->loadIdentity(VSMathLib::PROJECTION);
				Lib::vsml->ortho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1, 1);
				Lib::vsml->loadIdentity(VSMathLib::VIEW);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
				glBlendFunc(GL_ONE,GL_ZERO);
				flare->FLARE_render(cosine);
				glDisable(GL_BLEND);
				Lib::vsml->popMatrix(VSMathLib::PROJECTION);
			}
		}

	glUseProgram(shaderF.getProgramIndex());

	vsfl.renderSentence(10,10,lifes);

	vsfl.renderSentence(10, 30, points);

	if(gameOver){
		vsfl.renderSentence(10, 50, gameover);
	}

	glutSwapBuffers();
}


/////////////////////////////////////////////////////////////////////// CALLBACKS

void display()
{
	++FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderScene();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	float ratio;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	ratio = (1.0f * w) / h;
	Lib::vsml->loadIdentity(VSMathLib::PROJECTION);

	switch(camera){
	case PERSPECTIVE:
		Lib::vsml->perspective(53.13f, ratio, 0.1f, 10000.0f);
		break;

	case ORTHO:
		Lib::vsml->ortho(-30,30,-30,30,-30,30);
		glClearStencil(0);
		glClear(GL_STENCIL_BUFFER_BIT);
		glDisable(GL_STENCIL_TEST);
		break;

	case MOBILE:
		Lib::vsml->perspective(45.0f, ratio, 1.0f, 100.0f);
		glClearStencil(0);
		glClear(GL_STENCIL_BUFFER_BIT);
		glDisable(GL_STENCIL_TEST);
		break;

	}
}

void restartGame(){
	if(gameOver && totalLifes < 1){
		
		totalLifes = 5;
		totalPoints = 0;
		vsfl.prepareSentence(lifes, "Lifes: " + std::to_string(totalLifes));
		vsfl.prepareSentence(points, "Points: " + std::to_string(totalPoints));
		gameOver = false;}

}

void initParticles(void)
{
 GLfloat v, theta, phi;
 int i;

 for(i=0; i<MAX_PARTICULAS; i++)
    {
	particles[i] = Particle(0,5,0);
	particles[i].getParticle()->setTexture(testParticle._iTex, testParticle._texID, GL_TEXTURE_2D);
	v = 0.8*frand()+0.2;
    phi = frand()*M_PI;
    theta = 2.0*frand()*M_PI;
    particles[i].vx = v * cos(theta) * sin(phi);
    particles[i].vy = v * cos(phi);
    particles[i].vz = v * sin(theta) * sin(phi);
	particles[i].ax =  0.1f; /* simular um pouco de vento */
    particles[i].ay = -0.15f; /* simular a aceleração da gravidade */
    particles[i].az =  0.0f;
	
	/* tom amarelado que vai ser multiplicado pela textura que varia entre branco e preto */
	particles[i].r = 0.882f;
	particles[i].g = 0.552f;	
	particles[i].b = 0.211f;

	particles[i].life = 1.0f;		/* vida inicial */                
	particles[i].fade = 0.005f;	    /* step de decréscimo da vida para cada iteração */
	particles[i].draw();
	}
}
// ------------------------------------------------------------
//
// Events from the Keyboard
//
void processKeys(unsigned char key, int xx, int yy)
{

	switch(key) {

	case 27:
		glutLeaveMainLoop();
		break;
	case '1': camera = PERSPECTIVE; 
		reshape(WinX, WinY);
		break;
	case '2': camera = ORTHO; 
		reshape(WinX, WinY);
		break;
	case '3': camera = MOBILE; 
		reshape(WinX, WinY);
		break;
	case 'O':
	case 'o':
		if(!gameOver){
		frogMovement = LEFT;
		//glutPostRedisplay();
		}
		break;
	case 'P':
	case 'p':
		if(!gameOver){
		frogMovement = RIGHT;
		//glutPostRedisplay();
		}
		break;
	case 'Q':
	case 'q':
		if(!gameOver){
		frogMovement = FRONT;
		//glutPostRedisplay();
		}
		break;
	case 'A':
	case 'a':
		if(!gameOver){
		frogMovement = BACK;
		//glutPostRedisplay();
		}
		break;
	case 'C':
	case 'c':
		if(_pointLightOn == 1) _pointLightOn = 0;
		else _pointLightOn = 1;
		break;
	case 'N':
	case 'n':
		if(_directionalLightOn == 1) _directionalLightOn = 0;
		else _directionalLightOn = 1;
		break;
	case 'S':
	case 's':
		if(_spotLightOn == 1) _spotLightOn = 0;
		else _spotLightOn = 1;
		break;
	case 'R':
	case 'r':
		restartGame();
		break;
	case 'i':
	case 'I':
		initParticles();
		break;
	case 'y':
	case 'Y':
		flareOn = !flareOn;
		break;
	}

	//  uncomment this if not using an idle func
	//	glutPostRedisplay();
}

void keyboardUp(unsigned char key, int xx, int yy)
{

	switch(key) {
	case 'O':
	case 'o':
		frogMovement = -1;
		//glutPostRedisplay();
		break;
	case 'P':
	case 'p':
		frogMovement = -1;
		//glutPostRedisplay();
		break;
	case 'Q':
	case 'q':
		frogMovement = -1;
		//glutPostRedisplay();
		break;
	case 'A':
	case 'a':
		frogMovement = -1;
		//glutPostRedisplay();
		break;

	}
}


// ------------------------------------------------------------
//
// Mouse Events
//
// Mouse handling.
int     nButton = 0;
int     xMouse = 0, yMouse = 0;

void mouseButton(int button, int state, int xx, int yy)
{
	// start tracking the mouse
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON){
			tracking = 1;
			camera_moving = true;}
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
	}

	//stop tracking the mouse
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			camera_moving = false;
			alpha -= (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			r += (yy - startY) * 0.01f;
			if (r < 0.1f)
				r = 0.1f;
		}
		tracking = 0;
	}
}

void mouseMove(int xx, int yy)
{

	int deltaX, deltaY;
	float alphaAux, betaAux;
	float rAux;

	deltaX =  - xx + startX;
	deltaY =    yy - startY;

		// left mouse button: move camera
	if (camera_moving) {
		lookat_X = deltaX;
		lookat_Y = deltaY;
		flare->FLARE_position(xx, yy);
	}

	// left mouse button: move camera
	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0f)
			betaAux = 85.0f;
		else if (betaAux < -85.0f)
			betaAux = -85.0f;
		rAux = r;

		camX = rAux * sin(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
		camZ = rAux * cos(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
		camY = rAux *   						       sin(betaAux * 3.14f / 180.0f);
	}

	// right mouse button
	else if (tracking == 2 && camera == ORTHO) {

		frog->move(-xx/30.0f, 0, -yy/30.0f);
	}


}



void iterate(int value)
{
	int i;
	float h; 

	/* Método de Euler de integração de eq. diferenciais ordinárias 
		h representa o step de tempo; dv/dt = a; dx/dt = v; e conhecem-se os valores iniciais de x e v */

	h=0.125f;
	for (i=0; i<MAX_PARTICULAS; i++)
	{
		particles[i].x += (h*particles[i].vx);
		particles[i].y += (h*particles[i].vy);
		particles[i].z += (h*particles[i].vz);
		particles[i].vx += (h*particles[i].ax);
		particles[i].vy += (h*particles[i].ay);
		particles[i].vz += (h*particles[i].az);
		particles[i].life -= particles[i].fade;
	}
 glutPostRedisplay();
 glutTimerFunc(33,iterate,1);
}

/////////////////////////////////////////////////////////////////////// SETUP

void setupCallbacks() 
{
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	//	Mouse and Keyboard Callbacks
	glutKeyboardFunc(processKeys);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	//glutPostRedisplay();

	// Start the timer
	glutTimerFunc(TIMERMSECS, animate, 0);

	// Initialize the time variables
	startTime = glutGet(GLUT_ELAPSED_TIME);
	prevTime = startTime;

}

void setupOpenGL() {
	std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glClearStencil(0x0);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void setupGLEW() {
	glewExperimental = GL_TRUE;
	GLenum result = glewInit() ; 
	if (result != GLEW_OK) { 
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	} 
	GLenum err_code = glGetError();
	printf ("Vendor: %s\n", glGetString (GL_VENDOR));
	printf ("Renderer: %s\n", glGetString (GL_RENDERER));
	printf ("Version: %s\n", glGetString (GL_VERSION));
	printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));

}

void setupGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA|GLUT_MULTISAMPLE|GLUT_ALPHA);

	glutInitContextVersion (3, 3);
	glutInitContextProfile (GLUT_CORE_PROFILE );

	glutInitWindowPosition(100,100);
	glutInitWindowSize(WinX,WinY);
	WindowHandle = glutCreateWindow(CAPTION);
	if(WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void initVSL() {

	//	 Init Lib::vsml
	Lib::vsml->setUniformBlockName("Matrices");
	Lib::vsml->setUniformName(VSMathLib::PROJECTION, "m_proj");
	Lib::vsml->setUniformName(VSMathLib::PROJ_VIEW_MODEL, "m_pvm");
	Lib::vsml->setUniformName(VSMathLib::NORMAL, "m_normal");
	Lib::vsml->setUniformName(VSMathLib::VIEW_MODEL, "m_viewModel");
}



void initShapes(){

	tree = new Billboard(-20,0,-3);
	tree->draw();

	frog = new Frog(frogSpeed);
	frog->draw();

	initDynamicObjects();
	drawObjects();

	bottomRoadside = new Roadside(-30, -1, -30);
	bottomRoadside->draw();
	road = new Road(-30, -1, -25);
	road->draw();
	upperRoadside = new Roadside(-30, -1, -5);
	upperRoadside->draw();
	river = new River(-30, -1, 0);
	river->draw();
	upperRiverside = new Riverside(-30, -1, 25);
	upperRiverside->draw();

	testParticle = Particle(true);
	flare = new Flare();
}

void initFonts(){

	vsfl.load("fonts/couriernew10");
	vsfl.setFixedFont(true);
	vsfl.setColor(1.0f, 0.5f, 0.25f, 1.0f);
	lifes = vsfl.genSentence();
	points = vsfl.genSentence();
	gameover = vsfl.genSentence();

	vsfl.prepareSentence(lifes, "Lifes: " + std::to_string(totalLifes));
	vsfl.prepareSentence(points, "Points: " + std::to_string(totalPoints));
	vsfl.prepareSentence(gameover, "GAME OVER!");
}

void init(int argc, char* argv[])
{
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();

	setupCallbacks();


	setupShaders();
	setupFontShader();
	initVSL();
	initFonts();
	initShapes();

	createLights();

}

void PressEnterToContinue()
{
	std::cout << "Press ENTER to continue... " << std::flush;
	std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
}

int main(int argc, char* argv[])
{
	init(argc, argv);
	glutTimerFunc(33,iterate,1);

	glutMainLoop();	


	PressEnterToContinue();
}

///////////////////////////////////////////////////////////////////////