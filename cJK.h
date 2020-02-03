//
//  cJK.h
//  server
//
//  Created by Arshan Dalili on 2/2/20.
//  Copyright © 2020 Arshan Dalili. All rights reserved.
//

#ifndef cJK_h
#define cJK_h

#include <stdio.h>

#endif /* cJK_h */

char* createJSON(void);
char* ParseJSON(char*JSON);
void AddIOJSON(char*JSON,char title[],char content[]);
char* createArray(void);
void AddIAJSON(char*Array,char content[]);
int ArrayforEachAddtoJSON(char*Array,char*dstArray);
char *substring(char *string, int position, int length);
char *strremove(char *str, const char *sub);
void insert_substring(char *a, char *b, int position);
void GetOIJSON(char*JSON,char*wanted,char dst[]);
