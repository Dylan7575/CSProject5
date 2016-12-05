#include <string.h>
#include "stdio.h"
#include "stdlib.h"
#include "help.h"
#include "<GLFW/glfw3.h">
int height;
int width;
int maxval;

void read_header(){
	fscanf(ppm,"%i",&height);
	fscanf(ppm,"%i ",&width);
	fscanf(ppm,"%i ",&maxval);
}
void p_type(){
	fread(P,1,2,ppm);
}
void read_comment(){
	fgetc(ppm);
	char a = fgetc(ppm);
	if(a=='#'){
		while(a!='\n'){
			a=fgetc(ppm);
		}
		ungetc(a,ppm);
	}

}
void get_data(){
	int i =0;

	if(strcmp("P6",P)==0){
		data = malloc(sizeof(Pixel)*height*width*3);
		fread(data,1,height * width*3,ppm);
	}
	else{
		pix = malloc(height*width*sizeof(Pixel));
		while (i<height *width){
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
	fprintf(out,"%i",height);
	fwrite(" ",1,1,out);
	fprintf(out,"%i",width);
	fwrite(" ",1,1,out);
	fprintf(out,"%i",maxval);
	fwrite("\n",1,1,out);
	int i =0;
	while (i<height*width){
		fprintf(out,"%i %i %i\n",pix[i].r,pix[i].g,pix[i].b);
		i++;
	}
}
void write_p6(FILE*out){
	fwrite(P,2,1,out);
	fwrite("\n",1,1,out);
	fprintf(out,"%i",height);
	fwrite(" ",1,1,out);
	fprintf(out,"%i",width);
	fwrite(" ",1,1,out);
	fprintf(out,"%i",maxval);
	fwrite("\n",1,1,out);
	fwrite(data,height*width*3,1,out);

}
int main(int argc,char**argv) {
	FILE* out= fopen("/Users/dylanlafrenz/ClionProjects/FInal430/ouret.ppm","w+");
	ppm = fopen(argv[1],"r");
	P=malloc(sizeof(char)*2);
	comment = malloc(sizeof(char)*128);
	p_type();
	read_comment();
	read_header();
	get_data();
	write_p6(out);
	fclose(out);
	fclose(ppm);

}