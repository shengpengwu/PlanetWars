

#ifndef H_TEXTPRINT
#define H_TEXTPRINT

#include "Model.h"

class TextPrint
{
public:
	TextPrint(void);
	~TextPrint(void);
	void bitText(int x, int y, int z, float r, float g, float b, void * font, char *string);
	void hudText(int x, int y, int z, float r, float g, float b, void * font, char *string);
	void strokePrint(int x, int y, int z, float r, float g, float b, void * font, char *string);
private:
};

#endif