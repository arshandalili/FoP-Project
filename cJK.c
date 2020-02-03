#include "cJK.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include "cJSON.c"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#define MAX 10000

char *substring(char *string, int position, int length);
char *strremove(char *str, const char *sub);
void insert_substring(char *a, char *b, int position);
char* createJSON(){
    char*a="{}";
    return a;
}
//Del
char* ParseJSON(char*JSON){
    char *result;
    sscanf(JSON, "{ %s }",result);
    return result;
}
void GetOIJSON(char*JSON,char*wanted,char dst[]){
    char*token=strtok(JSON, ",");
    token=strremove(token, "{");
    while (token!=NULL){
        printf("%s\n",token);
        if (strncmp(token, wanted, strlen(wanted))==0) {
            token=strremove(token, "}");
            sscanf(token, "%*s %*s %s",dst);
            printf("%s\n",dst);
        }
        token = strtok(NULL, ",");
    }
}
void GetOIAJSON(char*c,char se[],char me[]){
    char*token=strtok(c, ",");
    token=strremove(token, "{");
            token=strremove(token, "}");
            sscanf(token, "%s %*s %s",se,me);
}
void AddIOJSON(char JSON[],char title[],char content[]){

    char nIO[MAX];
    bzero(nIO, MAX);
    if (strlen(JSON)!=2) {
        strcat(nIO, ",");
    }
    strcat(nIO, title);
    strcat(nIO, " : ");
    strcat(nIO, content);
    insert_substring(JSON, nIO, strlen(JSON));
}

char* createArray(){
    char*a="[]";
    return a;
}
void AddIAJSON(char*Array,char content[]){
    char nIA[MAX];
    bzero(nIA, MAX);
    if (strlen(Array)!=2) {
        strcat(nIA, ",");
    }
    strcat(nIA, content);
    insert_substring(Array, nIA, strlen(Array));
}

int ArrayforEachAddtoJSON(char*Array,char*dstArray){
    char*token=strtok(Array, ",");
       token=strremove(token, "[");
       while (token!=NULL){
           AddIAJSON(dstArray, token);
           token = strtok(NULL, ",");
       }
    return 0;
}

int ArrayforEachGPfJSON(char*Array,char se[],char me[]){
    char*token=strtok(Array, ",");
       token=strremove(token, "[");
       while (token!=NULL){
           GetOIAJSON(token, se, me);
           token = strtok(NULL, ",");
       }
    return 0;
}

char *strremove(char *str, const char *sub) {
    char *p, *q, *r;
    if ((q = r = strstr(str, sub)) != NULL) {
        size_t len = strlen(sub);
        while ((r = strstr(p = r + len, sub)) != NULL) {
            while (p < r)
                *q++ = *p++;
        }
        while ((*q++ = *p++) != '\0')
            continue;
    }
    return str;
}

void insert_substring(char *a, char *b, int position)
{
   char *f, *e;
   int length;
   
   length = strlen(a);
   
   f = substring(a, 1, position - 1 );
   e = substring(a, position, length-position+1);

   strcpy(a, "");
   strcat(a, f);
   free(f);
   strcat(a, b);
   strcat(a, e);
   free(e);
}

char *substring(char *string, int position, int length)
{
   char *pointer;
   int c;
 
   pointer = malloc(length+1);
   
   if( pointer == NULL )
       exit(EXIT_FAILURE);
 
   for( c = 0 ; c < length ; c++ )
      *(pointer+c) = *((string+position-1)+c);
       
   *(pointer+c) = '\0';
 
   return pointer;
}

void DelIAJSON(char*Array,int index){
    char*token=strtok(Array, ",");
    token=strremove(token, "[");
    int i=0;
    while (token!=NULL){
        if (i<=index) {
            token=strremove(token, "]");
            strcat(token, ",");
            strremove(Array, token);
        }
        i++;
        token = strtok(NULL, ",");
    }
}

void DelIOJSON(char*JSON,char content[]){
    char*token=strtok(JSON, ",");
    token=strremove(token, "{");
    while (token!=NULL){
        if (strncmp(token, content, strlen(content))==0) {
            token=strremove(token, "}");
            strcat(token, ",");
            strremove(JSON, token);
        }
        token = strtok(NULL, ",");
    }
}




