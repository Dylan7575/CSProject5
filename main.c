#include <string.h>
#include "stdio.h"
#include "stdlib.h"
#include "help.h"

#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>

#include "linmath.h"
#include <assert.h>


float rot = 0;
float scl= 1;
float trans_x =0;
float trans_y =0;
float sh = 0;


int heighter;
int widther;
int maxval;

typedef struct {
	float Position[2];
	float TexCoord[2];
} Vertex;

// (-1, 1)  (1, 1)
// (-1, -1) (1, -1)

Vertex vertexes[] = {
		{{-1, 1}, {0, 0}}, //Bottom Left
		{{1, 1},  {1, 0}},  //Bottom Right
		{{-1, -1},  {0, 1}},  //Top Left

		{{1, 1}, {1, 0}}, //Bottom Right
		{{1, -1},  {1, 1}}, //Top Right
		{{-1, -1},  {0, 1}} //Top Left
};

const GLubyte Indices[] = {
		0, 1, 2,
		2, 3, 0
};


static const char* vertex_shader_text =
		"uniform mat4 MVP;\n"
				"attribute vec2 TexCoordIn;\n"
				"attribute vec2 vPos;\n"
				"varying vec2 TexCoordOut;\n"
				"void main()\n"
				"{\n"
				"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
				"    TexCoordOut = TexCoordIn;\n"
				"}\n";

static const char* fragment_shader_text =
		"varying vec2 TexCoordOut;\n"
				"uniform sampler2D Texture;\n"
				"void main()\n"
				"{\n"
				"    gl_FragColor = texture2D(Texture, TexCoordOut);\n"
				"}\n";

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (key == GLFW_KEY_UP && action == GLFW_PRESS){
		trans_y += 0.1;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS){
		trans_y -= 0.1;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS){
		trans_x -= 0.1;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
		trans_x += 0.1;
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS){
		rot += 0.1;
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS){
		rot -= 0.1;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS){
		scl -= 0.1;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS){
		scl += 0.1;
	}
	if (key == GLFW_KEY_Z && action == GLFW_PRESS){
		sh -= 0.1;
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS){
		sh += 0.1;
	}
}

void glCompileShaderOrDie(GLuint shader) {
	GLint compiled;
	glCompileShader(shader);
	glGetShaderiv(shader,
				  GL_COMPILE_STATUS,
				  &compiled);
	if (!compiled) {
		GLint infoLen = 0;
		glGetShaderiv(shader,
					  GL_INFO_LOG_LENGTH,
					  &infoLen);
		char* info = malloc(infoLen+1);
		GLint done;
		glGetShaderInfoLog(shader, infoLen, &done, info);
		printf("Unable to compile shader: %s\n", info);
		exit(1);
	}
}

int main(int argc,char**argv)
{
	FILE* out= fopen("/Users/dylanlafrenz/ClionProjects/FInal430/ouret.ppm","w+");
	ppm = fopen(argv[1],"r");
	if(ppm==NULL){
		fprintf(stderr,"No input image detected");
		exit(1);
	}
	P=malloc(sizeof(char)*3);
	comment = malloc(sizeof(char)*128);
	p_type();
	read_comment();
	read_header();
	get_data();


	fclose(ppm);


	//unsigned char * image=malloc(heighter*widther*3*sizeof(unsigned char));
	int temp=0;


	if(strcmp(P,"P6")==0){
		for(int i =0;i<heighter*widther;i++){
			pix[i].r=data[temp++];
			pix[i].g=data[temp++];
			pix[i].b=data[temp++];

		}
	}




	//write_p6(out);
	fclose(out);


	fclose(ppm);
	GLFWwindow* window;
	GLuint vertex_buffer, vertex_shader, fragment_shader, program,index_buffer;
	GLint mvp_location, vpos_location, vcol_location;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(800, 600, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	// gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glfwSwapInterval(1);

	// NOTE: OpenGL error checks have been omitted for brevity

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShaderOrDie(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShaderOrDie(fragment_shader);

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	// more error checking! glLinkProgramOrDie!

	mvp_location = glGetUniformLocation(program, "MVP");
	assert(mvp_location != -1);

	vpos_location = glGetAttribLocation(program, "vPos");
	assert(vpos_location != -1);

	GLint texcoord_location = glGetAttribLocation(program, "TexCoordIn");
	assert(texcoord_location != -1);

	GLint tex_location = glGetUniformLocation(program, "Texture");
	assert(tex_location != -1);

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location,
						  2,
						  GL_FLOAT,
						  GL_FALSE,
						  sizeof(Vertex),
						  (void*) 0);

	glEnableVertexAttribArray(texcoord_location);
	glVertexAttribPointer(texcoord_location,
						  2,
						  GL_FLOAT,
						  GL_FALSE,
						  sizeof(Vertex),
						  (void*) (sizeof(float) * 2));

	int image_width = heighter;
	int image_height = widther;


	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,heighter, widther, 0, GL_RGB,
				 GL_UNSIGNED_BYTE, pix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
	glUniform1i(tex_location, 0);

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;
		mat4x4 m, p, mvp;
		mat4x4 trans,rotate,sheer,scale;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float) height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		mat4x4_identity(m);//main matrix
		//using the lin math header file to to transformations
		mat4x4_identity(trans);//translate matrix
		mat4x4_translate(trans,trans_x,trans_y,0);
		mat4x4_add(m,trans,m);

		mat4x4_identity(sheer); //sheer matrix
		mat4x4_sheer(sheer, sheer, sh, sh);
		mat4x4_add(m, sheer, m);

		mat4x4_identity(scale); //scale  matrix
		mat4x4_scale_aniso(scale, scale, scl, scl, scl);
		mat4x4_add(m, scale, m);

		mat4x4_identity(rotate);   //rotate matrix
		mat4x4_rotate_Z(rotate, rotate, rot);
		mat4x4_mul(m, rotate, m);







		mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4_mul(mvp, p, m);







		glUseProgram(program);
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
//! [code]






void read_header(){
	fscanf(ppm,"%i ",&heighter);
	fscanf(ppm,"%i ",&widther);
	fscanf(ppm,"%i ",&maxval);

}
void p_type(){
	fread(P,1,2,ppm);
	if(strcmp(&P[0],"P")==0){
		fprintf(stderr,"Not a PPM FIle");
		exit(1);
	}

	P[2]='\0';
}
void read_comment(){
	char la =fgetc(ppm);
	char a = fgetc(ppm);
	//printf("%c%c",la,a);
	if(a=='#'){
		while(a!='\n'){
			a=fgetc(ppm);
		}
		ungetc(a,ppm);
	}
	else{
		ungetc(a,ppm);
	}



}
void get_data(){
	int i =0;
	//printf("%s",P);
	pix = malloc(heighter*widther*sizeof(Pixel));

	if(strcmp(&P[1],"6")==0){
			data=malloc(heighter*widther*3*sizeof(unsigned char));
			fread(data,sizeof(unsigned char),heighter*widther*3,ppm);
	}

	else{
		printf("%i %i %i",heighter,widther,maxval);
		pix = malloc(heighter*widther*sizeof(Pixel));

		while (i<heighter *widther){
			fscanf(ppm,"%i",&pix[i].r);
			fscanf(ppm,"%i",&pix[i].g);
			fscanf(ppm,"%i",&pix[i].b);
			i++;
		}
	}
}
void write_p3(FILE* out){
	fwrite(P,2,1,out);
	fwrite("\n",1,1,out);
	fprintf(out,"%i",heighter);
	fwrite(" ",1,1,out);
	fprintf(out,"%i",widther);
	fwrite(" ",1,1,out);
	fprintf(out,"%i",maxval);
	fwrite("\n",1,1,out);
	int i =0;
	while (i<heighter*widther){
		fprintf(out,"%i %i %i\n",pix[i].r,pix[i].g,pix[i].b);
		i++;
	}
	free(pix);
}
void write_p6(FILE*out){
	fwrite(P,2,1,out);
	fwrite("\n",1,1,out);
	fprintf(out,"%i",heighter);
	fwrite(" ",1,1,out);
	fprintf(out,"%i",widther);
	fwrite(" ",1,1,out);
	fprintf(out,"%i",maxval);
	fwrite("\n",1,1,out);
	fwrite(data,1,heighter*widther*3,out);

	free(pix);

}
