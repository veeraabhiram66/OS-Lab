#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(){
    FILE *ip,*op;
    char ch;
    ip=fopen("Input1.txt","r");
    op=fopen("Output1.txt","w");
    if(ip==NULL)
    {
        printf("Invalid file");
    }

    while((ch=fgetc(ip))!=EOF){
        if(isalpha(ch)){
            if(isupper(ch)){
                ch=tolower(ch);
            }
            else{
                ch=toupper(ch); 
            }
        }
        fputc(ch,op);   
    }
    printf("Text copied  successfully\n");
    fclose(ip);
    fclose(op);
}