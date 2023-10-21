#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#define ESC 27

int ombro = 0, cotovelo = 0, mao = 0, indicador = 0,
	polegar = 0, anelar = 0, cameray = 0, camerax = 0;

void init(void);
void keyboard (unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Braço Robótico");
	
	init ();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    
    return EXIT_SUCCESS;
}	

void init(void){
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST); 
}

void reshape (int w, int h){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    gluPerspective(60, (float)w/(float)h , 1.0, 9.0); //(angulo, aspecto, ponto_proximo, ponto distante)
    gluLookAt(0.0,0.0,7.0,  // posicao da camera (olho)
              0.0,1.0,0.0,  // direcao da camera (geralmente para centro da cena)
              0.0,1.0,0.0); // sentido ou orientacao da camera (de cabeca para cima)

    glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y){
	switch (key) {
		case 'o': ombro = (ombro - 5) % 360; break;
		case 'O': ombro = (ombro + 5) % 360; break; 
		case 'c': cotovelo = (cotovelo - 5) % 360; break; 
		case 'C': cotovelo = (cotovelo + 5) % 360; break;
		case 'm': mao = (mao - 5) % 360; break; 
		case 'M': mao = (mao + 5) % 360; break; 
		case 'i': indicador = (indicador - 5) % 360; break; 
		case 'I': indicador = (indicador + 5) % 360; break; 
		case 'a': anelar = (anelar - 5) % 360; break; 
		case 'A': anelar = (anelar + 5) % 360; break; 
		case 'p': polegar = (polegar - 5) % 360; break; 
		case 'P': polegar = (polegar + 5) % 360; break; 
		case 'y': cameray = (cameray - 5) % 360; break; 
		case 'Y': cameray = (cameray + 5) % 360; break; 
		case 'x': camerax = (camerax - 5) % 360; break; 
		case 'X': camerax = (camerax + 5) % 360; break; 
		case ESC: exit(EXIT_SUCCESS); break; 
	}
    glutPostRedisplay();
}

void display(void){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    //rotação da camera
    glRotatef((GLfloat) cameray, 0, 1, 0);
    glRotatef((GLfloat) camerax, 1, 0, 0);
    
    //articulacao ombro
    glPushMatrix();
    	glTranslatef(0, -1, 0);
    	glColor3f(0, 0, 0);
    	glutSolidSphere(0.5, 30, 30);
    glPopMatrix();
    
    //movimento braço
    glPushMatrix();
    	glTranslatef(0, -1, 0);
    	glRotatef((GLfloat) ombro, 0, 0, 1);
    	glTranslatef(0, 1, 0);
    	
    	//braço
    	glPushMatrix();
			glRotatef(90, 0, 0, 1);
			glScalef(2, 0.5, 0.5);
			glColor3f(1, 0.5, 0);
			glutSolidCube(1);
    	glPopMatrix();
    	
    	//articulacao cotovelo
    	glPushMatrix();
    		glTranslatef(0, 1, 0);
    		glColor3f(0, 0, 0);
    		glutSolidSphere(0.4, 30, 30);
    	glPopMatrix();
    	
    	//movimento antebraço
    	glPushMatrix();
    		glTranslatef(0, 1, 0);
    		glRotatef((GLfloat) cotovelo, 0, 0, 1);
    		glTranslatef(0, 1, 0);
    		
    		//antebraço
    		glPushMatrix();
				glRotatef(90, 0, 0, 1);
				glScalef(2, 0.4, 0.4);
				glColor3f(1, 0, 0.5);
				glutSolidCube(1);    			
    		glPopMatrix();
    		
    		//articulacao mão
    		glPushMatrix();
    			glTranslatef(0, 1, 0);
    			glColor3f(0, 0, 0);
    			glutSolidSphere(0.35, 30, 30);
    		glPopMatrix();
    		
    		//movimento mão
    		glPushMatrix();
    			glTranslatef(0, 1, 0);
    			glRotatef((GLfloat) mao, 0, 0, 1);
    			glTranslatef(0, 0.5, 0);
    			
    			//mao
    			glPushMatrix();
    				glRotatef(90, 0, 0, 1);
    				glScalef(1, 0.45, 0.45);
    				glColor3f(0, 1, 0.5);
    				glutSolidCube(1);
    			glPopMatrix();
    			
    			//movimento polegar
    			glPushMatrix();
    				glTranslatef(0.15, 0.4, 0);
    				glRotatef((GLfloat) polegar, 0, 0, 1);
    				glTranslatef(0, 0.2, 0);
    				
    				//polegar
    				glPushMatrix();
    					glRotatef(90, 0, 0, 1);
    					glScalef(0.5, 0.25, 0.25);
    					glColor3f(1, 0, 1);
    					glutSolidCube(0.5);
    				glPopMatrix();
    			glPopMatrix();
    			
    			//movimento indicador
    			glPushMatrix();
    				glTranslatef(-0.15, 0.4, -0.15);
    				glRotatef((GLfloat) indicador, -1, 0, 1);
    				glTranslatef(0, 0.2, 0);
    				
    				//indicador
    				glPushMatrix();
    					glRotatef(90, 0, 0, 1);
    					glScalef(0.5, 0.25, 0.25);
    					glColor3f(1, 0, 0);
    					glutSolidCube(0.5);
    				glPopMatrix();
    			glPopMatrix();
    			
    			//movimento anelar
    			glPushMatrix();
    				glTranslatef(-0.15, 0.4, 0.15);
    				glRotatef((GLfloat) anelar, 1, 0, 1);
    				glTranslatef(0, 0.2, 0);
    				
    				//anelar
    				glPushMatrix();
    					glRotatef(90, 0, 0, 1);
    					glScalef(0.5, 0.25, 0.25);
    					glColor3f(0, 0, 1);
    					glutSolidCube(0.5);
    				glPopMatrix();
    			glPopMatrix();
    		glPopMatrix();
    	glPopMatrix();
    	
    glPopMatrix();
	
	glutSwapBuffers();
}
