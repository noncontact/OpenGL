#include<stdio.h>
#include <stdlib.h>
#include "gl\glut.h"
#include <math.h>
#define GL_PI 3.1415f//원주율

GLdouble ex = 4.0, ey = 5.0, ez = 6.0;
GLdouble tx = 0.0, ty = 0.0, tz = 0.0;
GLdouble ax = 0.0, ay = 1.0;
GLdouble angle = 0.0;
GLdouble zoom =120.0;
int W,H;
double sx, sy;
#define SCALE 360.0
int cx, cy;
double ca;

int mousex,mousey, mousebutton,moveTrue;//마우스

GLfloat ambient[][4] = {
	{0.2, 0.2, 0.2, 1.0}
	,{0.4, 0.0, 0.4, 1.0}
	,{0.1, 0.2, 0.0, 1.0}
	,{0.0, 0.0, 0.7, 1.0}
	,{0.7, 0.0, 0.0, 1.0}
	,{0.0, 0.7, 0.0, 1.0}
	,{0.6, 0.5, 0.8, 1.0}
};
GLfloat diffuse[][4] = {
	{1.0, 0.8, 0.0, 1.0},
	{0.2,0.2,0.2,1}
	,{0.1, 0.2, 0.0, 1.0}
	,{0.0, 0.0, 0.7, 1.0}
	,{0.7, 0.0, 0.0, 1.0}
	,{0.0, 0.7, 0.0, 1.0}
	,{0.6, 0.5, 0.8, 1.0}
};
GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_shininess[] = { 100.0 };
void init(){//init 카메라및 환경
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_position1[] = { 1.0, 1.0, -1.0, 0.0 };
	GLfloat light_position2[] = { -1.0, 1.0, 1.0, 0.0 };
	glClearColor (0, 0, 0, 1.0);
	glShadeModel (GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient[0]);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse[0]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient[3]);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse[3]);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
	 glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
}
void reshape (int w, int h)
{
	sx = 1.0 / (double)w;
    sy = 1.0 / (double)h;
	W=w;
	H=h;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(zoom, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
void idle(void)
{
  glutPostRedisplay();
}
void mouseClick(int button,int state,int x,int y){
	//마우스 클릭 함수
	 mousebutton=button;
	switch (button) {
  case GLUT_LEFT_BUTTON:
    switch (state) {
    case GLUT_DOWN:
      glutIdleFunc(idle);
     
      cx = x;
      cy = y;
      
      ca = angle;
      break;
    case GLUT_UP:
      glutIdleFunc(0);
      break;
    default:
      break;
    }
    break;
  case GLUT_MIDDLE_BUTTON:
	  
	  switch (state) {
		case GLUT_DOWN:
		 cx = x;
		 cy = y;

		 break;
	  }
	  break;
	    case GLUT_RIGHT_BUTTON:
	  
	  switch (state) {
		case GLUT_DOWN:
		zoom+=5;
		printf("%lf",zoom);
		glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(zoom, (GLfloat) W/(GLfloat) H, 1.0, 20.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

		 glutPostRedisplay();
		 break;
	  }
	  break;
  default:
    break;
  }
}
void mouseMotion(int x,int y){
	double dx, dy, a;

 if(mousebutton==GLUT_LEFT_BUTTON){
  dx = (x - cx) * sx;
  dy = (y - cy) * sy;
  a = sqrt(dx * dx + dy * dy);

  if (a != 0.0) {
    angle = fmod(ca + SCALE * a, 360.0);
    ax = dy / a;
    ay = dx / a;

    glutPostRedisplay();
  }
 }
 else if(mousebutton==GLUT_MIDDLE_BUTTON){
	 if(x>cx)
	 glTranslated(1,0,0);
	 else if(x<cx)
		 glTranslated(-1,0,0);
	 
	 cx=x;
	 cy=y;
	  glutPostRedisplay();
 }
	
		
}
void keyboard(unsigned char key,int x,int y){
	switch(key){
	case'0':
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		break;
	case '1':
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		break;
	case'2':
		glEnable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		break;
	case'3':
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void multcube(int h,float r){
	int i;
	glPushMatrix();
	for(i=0;i<h;i++){
	glutSolidCube(r);
	glTranslated(0,-r,0);
	}
	glPopMatrix();
}
void createCylinder( GLfloat radius, GLfloat h)
{
    GLfloat x, y, angle;
	glPushMatrix();
	glRotated(90,1,0,0);
    glBegin(GL_TRIANGLE_FAN);           
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0, 0, 0);
 
    for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
    {
        x = radius*sin(angle);
        y =  radius*cos(angle);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(x, y, 0);
    }
    glEnd();
 
    glBegin(GL_QUAD_STRIP);            //원기둥의 옆면
    for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
    {
        x = 0 + radius*sin(angle);
        y = 0 + radius*cos(angle);
        glNormal3f(sin(angle), cos(angle), 0.0f);
        glVertex3f(x, y, 0);
        glVertex3f(x, y, 0 + h);
    }
    glEnd();
 
    glBegin(GL_TRIANGLE_FAN);           //원기둥의 밑면
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0, 0 + h);
    for(angle = (2.0f*GL_PI); angle > 0.0f; angle -= (GL_PI/8.0f))
    {
        x = 0 + radius*sin(angle);
        y = 0 + radius*cos(angle);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(x, y, 0 + h);
    }
    glEnd();
	glPopMatrix();
}

void createHalfSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius)
{
    GLfloat angley;  //y축 값을 구하기 위한 각도
    GLfloat nexty;  //다음 y축 값을 구하기 위한 각도
    GLfloat anglex;  //x, y축 값을 구하기 위한 각도
 
    glColor3ub(136, 206, 250);  //반구의 색 지정
    glBegin(GL_QUAD_STRIP);
    for(angley = 0.0f; angley <= (0.5f*GL_PI); angley += ((0.5f*GL_PI)/8.0f))  //반구만 그려야 하므로 0.5곱함
    {
        y = radius*sin(angley);     //y축 값 계산
        nexty = angley+((0.5f*GL_PI)/8.0f);  //다음 angley값 저장
        for(anglex = 0.0f; anglex < (2.0f*GL_PI); anglex += (GL_PI/8.0f))
        {
            x = radius*cos(angley)*sin(anglex);
            z = radius*cos(angley)*cos(anglex);
            glNormal3f(-cos(angley)*sin(anglex), -sin(angley), -cos(angley)*cos(anglex)); //반구의 안쪽으로 normal 벡터 생성
            glVertex3f(x, y, z);
 
            x = radius*cos(nexty)*sin(anglex);
            z = radius*cos(nexty)*cos(anglex);
            glNormal3f(-cos(nexty)*sin(anglex), -sin(nexty), -cos(nexty)*cos(anglex));
            glVertex3f(x, radius*sin(nexty), z);
        }
    }
    glEnd();
}
void Hemisphere(float r) 
{
    double clipEq[]={0.0, 1.0, 0.0, 0.0};
	double angle,x,y;

 glPushMatrix();
   glClipPlane(GL_CLIP_PLANE0, clipEq);
  glEnable (GL_CLIP_PLANE0);
   
   // Transform
   glutSolidSphere(r,15,15);
    glDisable (GL_CLIP_PLANE0);

	glBegin(GL_TRIANGLE_FAN);           
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0, 0, 0);
	for(angle = (2.0f*GL_PI); angle >= 0; angle -= (GL_PI/16.0f))
    {
        x =  r*sin(angle);
        y =  r*cos(angle);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(x, 0, y);
    }
    glEnd();
   glPopMatrix();

}
void structa(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[0]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glPushMatrix();
	glTranslated(0,2,0);
	glutSolidSphere(1,15,15);
	glPushMatrix();
	glTranslated(1.6,0,0);
	multcube(3,1.5);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-1.6,0,0);
	multcube(3,1.5);
	glPopMatrix();
	glPushMatrix();
	glTranslated(1.6,0.6,0);
	glutSolidSphere(0.6,15,15);
	glTranslated(-3.2,0,0);
	glutSolidSphere(0.6,15,15);
	glPopMatrix();
	glPopMatrix();
}
void structb(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[1]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[1]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glPushMatrix();
	glTranslated(0,-1.2,0);
	glPushMatrix();
	Hemisphere(1.2);
	createCylinder(0.9,0.6);
	glRotated(180,1,0,0);
	glTranslated(0,-0.5,0);
	Hemisphere(1.2);
	glPopMatrix();
	glPushMatrix();
	glTranslated(1,0.5,0);
	glRotated(90,-1,0,0);
	glutSolidCone(0.2,0.4,5,5);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-1,0.5,0);
	glRotated(90,-1,0,0);
	glutSolidCone(0.2,0.4,5,5);
	glPopMatrix();
	glPopMatrix();
}
void structc(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[2]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[2]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glPushMatrix();
	glTranslated(0,4.2,0);
	glPushMatrix();
	createCylinder(0.7,6);
	glRotated(90,-1,0,0);
	glutSolidCone(0.7,1,20,10);
	glPopMatrix();
	glPushMatrix();
	glRotated(90,-1,0,0);
	glutSolidTorus(0.5f, 2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,0,-0.5);
	glRotated(90,1,0,0);
	createCylinder(0.3,1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,0,1.5);
	glRotated(90,1,0,0);
	createCylinder(0.3,1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.5,0,0);
	glRotated(90,0,0,1);
	createCylinder(0.3,1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-1.5,0,0);
	glRotated(90,0,0,1);
	createCylinder(0.3,1);
	glPopMatrix();
	glPopMatrix();
}
void structd(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[3]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[3]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glPushMatrix();
	glTranslated(0,1.7,0);
	createCylinder(0.5,3.6);
	glTranslated(1,-0.6,0);
	createCylinder(0.5,3);
	glTranslated(-0.5,-0.9,0);
	multcube(2,1);
	glTranslated(0,-1.75,0.7);
	glutSolidCube(0.7);
	glTranslated(0,0.55,-0.1);
	glutSolidCube(0.5);
	glPopMatrix();
}
void suq(int r){
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0,1,0);
	glVertex3f(r,0,r);
	glVertex3f(r,0,-r);
	glVertex3f(-r,0,r);
	glVertex3f(-r,0,-r);
	glEnd();
}
void surf(){
	suq(1);
	glRotated(180,1,0,0);
	suq(1);
}
void obja(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[4]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[4]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glPushMatrix();
	glTranslated(0,0,0.-0.3);
	createCylinder(0.15,0.6);
	glTranslated(0,0,0.6);
	createCylinder(0.15,0.6);
	glPopMatrix();
	glPushMatrix();
	glRotated(30,0,0,-1);
	surf();
	glPopMatrix();
}
void objb(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[5]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[5]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glPushMatrix();
	glRotated(90,-1,0,0);
	createCylinder(0.3,3);
	createCylinder(0.4,0.7);
	glPopMatrix();
}
void objc(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[6]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[6]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(0,-0.3,-1);
	glVertex3f(0,-0.3,1);
	glEnd();
	createCylinder(0.5,1);
	glPushMatrix();
	glRotated(90,-1,0,0);
	glutSolidCone(0.5,1,20,10);
	glPopMatrix();
	glTranslated(0,1,0);
	createCylinder(0.3,1);
	glTranslated(0,0.5,0);
	glPushMatrix();
	glRotated(180,1,0,0);
	Hemisphere(0.7);
	glPopMatrix();
	glTranslated(0,0.3,0);
	createCylinder(0.1,0.4);
	glTranslated(0,0.1,0);
	glutSolidSphere(0.1,20,20);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,-0.5,-2);
	glRotated(90,0,0,1);
	surf();
	glTranslated(0,0,1);
	surf();
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,-0.5,2);
	glRotated(90,0,0,1);
	surf();
	glTranslated(0,0,-1);
	surf();
	glPopMatrix();
}
void land(){
	GLfloat a[]={1,0.4,0.1};
	glMaterialfv(GL_FRONT, GL_AMBIENT, a);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[2]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	suq(100);
	glRotated(180,1,0,0);
	suq(100);

}
void mydisplay(){
	 double dx = tx - ex, dy = ty - ey, dz = tz - ez;
  double d = sqrt(dx * dx + dy * dy + dz * dz);
  int i;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
	glPushMatrix();
	 glTranslated(0.0, 0.0, -d);
  glRotated(angle, ax, ay, 0.0);
  glTranslated(0.0, 0.0, d);
  gluLookAt(ex, ey, ez, tx, ty, tz, 0.0, 1.0, 0.0);
	
	glPushMatrix();
	glTranslated(-1,0,-5);
	structc();
	glPushMatrix();
	glTranslated(0,-1.5,0);
	for(i=0;i<3;i++){
	objb();
	glTranslated(0.2,0,3);
	}
	glPopMatrix();
	glTranslated(-3,0,3);
	structa();
	glTranslated(5,0,0);
	structa();
	glTranslated(3,0,3);
	for(i=0;i<5;i++){
	structd();
	glTranslated(-2.5,0,0);
	}
	glPushMatrix();
	glTranslated(3.5,-1.5,0.2);
	glRotated(90,0,1,0);
	for(i=0;i<3;i++){
	objb();
	glTranslated(0.2,0,3);
	}
	glPopMatrix();
	glTranslated(3,0,3);
	structb();
	glTranslated(10,0,0);
	structb();
	glTranslated(-3,-1.5,0);
	glRotated(90,0,1,0);
	for(i=0;i<3;i++){
	objb();
	glTranslated(0,0,-3);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(7,0,-4);
	for(i=0;i<4;i++){
	obja();
	glTranslated(0,0,2.3);
	}
	glPopMatrix();
	glPushMatrix();
	glTranslated(-6,8,-5);
	glRotated(150,0,0,-1);
	objc();
	glPopMatrix();
	glTranslated(0,-1.8,0);
	
	land();
	glPopMatrix();
	
	glutSwapBuffers();
}

int main(int argc,char** argv){
	//glut init
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//actual window size
	glutInitWindowSize(500,500);
	//initial window location, top-left corner
	glutInitWindowPosition(0,0);

	glutCreateWindow("HW3_15010949_조은석");

	glutDisplayFunc(mydisplay);
	glutReshapeFunc(reshape);
	glutMouseFunc( mouseClick );
	glutMotionFunc( mouseMotion );
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();//gl함수만 반복
	return 0;
}



