

#include "TextPrint.h"
#include <GL\freeglut.h>
#include <GL\GL.h>

TextPrint::TextPrint(void)
{
}


TextPrint::~TextPrint(void)
{
}

/*
GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18

*/



/*
 * Prints characters from GLUT in the 3d world which will always face the screen.
 *       Do not push or pop matrices before this!
 */


void TextPrint::bitText(int x, int y, int z, 
	float r, float g, float b, void * font, char *string)
{
	glColor3f( r, g, b );
	glRasterPos3f(x, y, z);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}

// Standalone function that will automatically place words in a HUD.
void TextPrint::hudText(int x, int y, int z, 
	float r, float g, float b, void * font, char *string)
{
	glColor3f( r, g, b );
	glRasterPos3f(x, y, z);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}

}

/*	Stroke fonts:
GLUT_STROKE_ROMAN
GLUT_STROKE_MONO_ROMAN
*/

void TextPrint::strokePrint(int x, int y, int z, 
	float r, float g, float b, void * font, char *string)
{
	glColor3f( r, g, b );
	glRasterPos3f(x, y, z);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}


}
void output(GLfloat x, GLfloat y, char *text)
{
    char *p;
    
    glPushMatrix();
    glTranslatef(x, y, 0);
    for (p = text; *p; p++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    glPopMatrix();
}