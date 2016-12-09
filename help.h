char* P;
char* comment;

unsigned char * data;
FILE *ppm;
typedef struct{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}Pixel;
Pixel* pix;


void read_header();
void p_type();
void read_comment();
void get_data();
void write_p3(FILE* out);
void write_p6(FILE*out);