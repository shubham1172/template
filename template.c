/**
* @author: Shubham Sharma
* @ver 0.1
* 
* A utility file to create templates on the go for your favorite programming languages.
* Useful for writing tests where you don't have to create the basic template again and again.
*/

#include<stdio.h>
#include<string.h>	
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

char *template;	//stores the template to be displayed
char *command;	//stores the command to be executed
char *filename; //stores the filename of the file with path

//displays help
void help(){
	template =  "template\n\n"
			    "v0.1\n"
				"syntax: template [type] [filename] [-o]\n"
				"type: html, js, c, java \n"
				"filename: output file name (by default it is printed to stdout)\n"
				"-o: opens the file in gedit\n"
				"developed by 1172 www.github.com/shubham1172\n";
	printf("%s", template);
}

//check if a file exists
int checkFile(){
	int flag = 0;
	struct stat buffer;
	flag = (stat(filename, &buffer)==0);
	return flag;
}

//create a file if it doesn't exist
void makeFile(){
	if(!checkFile()){
		const char *pre = "echo \"";
		const char *suf = "\" >> ";
		command = (char *)malloc(strlen(pre)+strlen(suf)+strlen(template)+strlen(filename)+4);
		strcpy(command, pre);
		strcat(command, template);
		strcat(command, suf);
		strcat(command, filename);
	}else{
		printf("File already exists!\n");
	}
}

//opens a file with gedit
void openFile(){
	const char *pre = "gedit ";
	command = (char *)malloc(strlen(pre)+strlen(filename)+2);
	strcpy(command, pre);
	strcat(command, filename);
}

//print a template on screen
void print(){	
	printf("%s", template);
}

//template for html
void html(){
	template =  "<!DOCTYPE html>\n"
				"<html>\n"
				"    <head>\n"
				"\t<title></title>\n"
				"    </head>\n"
				"    <body>\n"
				"    </body>\n"
				"</html>\n";
}

//template for js
void js(){
	template = "window.onload = function(){\n"
			   	"	console.log(\"Hello, world!\");\n"
			   	"}\n";
}

//template for C
void c(){
	template = "#include<stdio.h>\n"
				"#include<stdlib.h>\n"
				"\nint main(){\n"
				"    printf(\"Hello, world!\");\n"
				"}\n";
}

//template for JAVA
void java(){
	template = "class Solution{\n"
				"	public static void main(String[] args){\n"
				"		System.out.println(\"Hello, world!\").\n"
				"	}\n"
				"}\n";
}

int main(int argc, char* argv[]){
	int flag = 1;
	if(argc>=2){
		if(strcmp(argv[1], "html")==0||strcmp(argv[1], "HTML")==0){
			html();
		}else if(strcmp(argv[1], "java")==0||strcmp(argv[1], "JAVA")==0){
			java();
		}else if(strcmp(argv[1], "C")==0||strcmp(argv[1], "c")==0){
			c();
		}else if(strcmp(argv[1], "js")==0||strcmp(argv[1], "JS")==0){
			js();
		}else
			flag = 0;
		if(flag&&argc==2)
			print();
		if(flag&&argc>=3){
			filename = (char *)malloc(strlen(argv[2]+1));
			strcpy(filename, argv[2]);
			makeFile();
			system(command);	
		}if(flag&&argc==4){
			if(strcmp(argv[3], "-o")==0){
				openFile();
				system(command);
			}else
				flag = 0;
		}
	}else
		flag = 0;
	if(!flag)
		help();
}
