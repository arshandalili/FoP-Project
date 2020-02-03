#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
//#include "cJSON.c"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include "cJK.h"
//#include "cJK.c"
#define MAX 10000
#define PORT 12345
#define SA struct sockaddr
char authtok[24];
FILE *users;
FILE *channels;
FILE *at;
FILE *un;
FILE *cn;
int main(void);


int dircheck(char*filename){
    int cond=1;
   struct dirent *de;
      DIR *dr = opendir(".");
      if (dr == NULL)
      {
          printf("Could not open current directory" );
          return 0;
      }
      while ((de = readdir(dr)) != NULL)
          if (strcmp(filename, de->d_name)==0) {
              cond=0;
          }
    if (cond==0) {
        closedir(dr);
        return 0;
    }
      closedir(dr);
      return 1;
}





/*
int sendmessage(char messagets[],char authtoken[],int client_socket,int server_socket){
    char channel[MAX],chname[MAX];
    char tmsg[MAX];
    if((cn=fopen("channelname.txt", "r"))!=NULL){
            fgets(channel, MAX,cn);
            fclose(cn);
    }
    else{
        char*content = NULL;
          char*type = NULL;
          char*err = createJSON();
          content = cJSON_CreateString("You are not in this channel.");
          type= cJSON_CreateString("Error");
          cJSON_AddItemToObject(err, "type", type);
          cJSON_AddItemToObject(err, "content", content);
          char*errors=cJSON_PrintUnformatted(err);
          send(client_socket,errors,strlen(errors),0);
          close(client_socket);
          close(server_socket);
        return 0;
    }
    strcpy(chname, channel);
    strcat(channel, ".channel.json");
    char usn[MAX];
    if((at=fopen("authtok.txt", "r"))!=NULL){
        fgets(authtok, 25, at);
        fclose(at);
    }
    if((un=fopen("username.txt", "r"))!=NULL){
            fgets(usn, MAX, un);
            fclose(un);
    }
    if (strncmp(authtok, authtoken, 24)==0) {
        if(dircheck(channel)==0){
            if((channels=fopen(channel, "r"))!=NULL){
            fgets(tmsg, MAX, channels);
            fclose(channels);
            }
             if((channels=fopen(channel, "w"))!=NULL){
            char*curde=cJSON_Parse(tmsg);
    char*messages = NULL;
        char*msg=NULL;
        char*sender=NULL;
        messages= cJSON_GetObjectItem(curde, "messages");
        sender=cJSON_CreateString(usn);
        msg=cJSON_CreateString(messagets);
        char*eachmsg=createJSON();
        cJSON_AddItemToObject(eachmsg, "sender", sender);
        cJSON_AddItemToObject(eachmsg, "content", msg);
        cJSON_AddItemToArray(messages, eachmsg);
        char* wtp=cJSON_PrintUnformatted(curde);
        fprintf(channels, "%s\n",wtp);
        fclose(channels);
             }
        char*content = NULL;
        char*type = NULL;
        char*err = createJSON();
           content = cJSON_CreateString("");
        type= cJSON_CreateString("Successful");
           cJSON_AddItemToObject(err, "type", type);
        cJSON_AddItemToObject(err, "content", content);
        char*errors=cJSON_PrintUnformatted(err);
        send(client_socket,errors,strlen(errors),0);
        close(client_socket);
        close(server_socket);
        return 0;
    }
    }
    else{
        char*content = NULL;
          char*type = NULL;
          char*err = createJSON();
          content = cJSON_CreateString("Wrong AuthToken");
          type= cJSON_CreateString("Error");
          cJSON_AddItemToObject(err, "type", type);
          cJSON_AddItemToObject(err, "content", content);
          char*errors=cJSON_PrintUnformatted(err);
          send(client_socket,errors,strlen(errors),0);
          close(client_socket);
          close(server_socket);
        return 0;

    }
    return 0;
}





int chmembers(char authtoken[],int client_socket,int server_socket){
    char channel[MAX],chname[MAX];
    if((cn=fopen("channelname.txt", "r"))!=NULL){
            fgets(channel, MAX, cn);
            fclose(cn);
    }
    strcpy(chname, channel);
    strcat(channel, ".channel.json");
    char usn[MAX];
    if((at=fopen("authtok.txt", "r"))!=NULL){
        fgets(authtok, 25, at);
        fclose(at);
    }
    if (strncmp(authtok, authtoken, 24)==0) {
        if(dircheck(channel)==0){
            channels=fopen(channel, "r");
            char tmsg[MAX];
            fgets(tmsg, MAX, channels);

            char*content = NULL;
            char*type = NULL;
            char*err = createJSON();
                content = cJSON_CreateArray();
            type= cJSON_CreateString("List");
               cJSON_AddItemToObject(err, "type", type);
            cJSON_AddItemToObject(err, "content", content);

            char*curde=cJSON_Parse(tmsg);
    char*mems = NULL;
        char*mem=NULL;
        mems= cJSON_GetObjectItem(curde, "members");
            cJSON_ArrayForEach(mem, mems){
                cJSON_AddItemToArray(content, mem);
            }

        fclose(channels);

        char*errors=cJSON_PrintUnformatted(err);
            printf("%s\n",errors);
        send(client_socket,errors,strlen(errors),0);
        close(client_socket);
        close(server_socket);
            return 0;
    }
        else{
            char*content = NULL;
              char*type = NULL;
              char*err = createJSON();
              content = cJSON_CreateString("You are not in this channel.");
              type= cJSON_CreateString("Error");
              cJSON_AddItemToObject(err, "type", type);
              cJSON_AddItemToObject(err, "content", content);
              char*errors=cJSON_PrintUnformatted(err);
              send(client_socket,errors,strlen(errors),0);
              close(client_socket);
              close(server_socket);
            return 0;

        }
    }
    else{
        char*content = NULL;
          char*type = NULL;
          char*err = createJSON();
          content = cJSON_CreateString("Wrong AuthToken");
          type= cJSON_CreateString("Error");
          cJSON_AddItemToObject(err, "type", type);
          cJSON_AddItemToObject(err, "content", content);
          char*errors=cJSON_PrintUnformatted(err);
          send(client_socket,errors,strlen(errors),0);
          close(client_socket);
          close(server_socket);
        return 0;

    }
    return 0;
}




int refr(char authtoken[],int client_socket,int server_socket){
    int po=0;
    char channel[MAX],chname[MAX];
    if((cn=fopen("channelname.txt", "r"))!=NULL){
            fgets(channel, MAX, cn);
            fclose(cn);
    }
    strcpy(chname, channel);
    strcat(channel, ".channel.json");
    char usn[MAX],usn2[MAX];
    if((at=fopen("authtok.txt", "r"))!=NULL){
        fgets(authtok, 25, at);
        fclose(at);
    }
    if((un=fopen("username.txt", "r"))!=NULL){

            fgets(usn, MAX, un);
            fclose(un);
    }
    strcpy(usn2, usn);
    strcat(usn, ".user.json");
    printf("%s\n%s\n",authtoken,authtok);
    if (strncmp(authtok, authtoken,24)==0) {
        if(dircheck(usn)==0){
    if((users=fopen(usn, "r"))!=NULL){
        char msg[MAX];
        fgets(msg, MAX, users);
        char*message = cJSON_Parse(msg);
        char*point= GetOIJSON(message, "point");
        po=point->valuedouble;
        fclose(users);
    }
        }
    if(dircheck(channel)==0){
             if((channels=fopen(channel, "r"))!=NULL){
            char tmsg[MAX];
            fgets(tmsg, MAX, channels);

            char*content = NULL;
            char*type = NULL;
            char*err = createJSON();
                content = cJSON_CreateArray();
            type= cJSON_CreateString("List");
               cJSON_AddItemToObject(err, "type", type);
            cJSON_AddItemToObject(err, "content", content);

            char*curde=cJSON_Parse(tmsg);
    char*mems = NULL;
        char*mem=NULL;
        mems= cJSON_GetObjectItem(curde, "messages");
        int i=0;
            cJSON_ArrayForEach(mem, mems){
                if (i==po) {
                    cJSON_AddItemToArray(content, mem);

                }
                i++;
            }
                 for (int j=0; j<po-2; j++) {
                     cJSON_DeleteItemFromArray(content, j);
                 }
                 char *pre=cJSON_Print(content);
                 printf("%s\n",pre);
                 po=i;
        fclose(channels);
                 char * ncj;
            if((users=fopen(usn, "r"))!=NULL){
                char msg[MAX];
                fgets(msg, MAX, users);
                char*message = cJSON_Parse(msg);
                char*point=cJSON_CreateNumber(po);
                cJSON_DeleteItemFromObject(message, "point");
                cJSON_AddItemToObject(message, "point", point);
                ncj=cJSON_PrintUnformatted(message);
                fprintf(users, "%s",ncj);
                fclose(users);
            }
                 if((users=fopen(usn, "w"))!=NULL){
                     fprintf(users, "%s",ncj);
                     fclose(users);
                 }
        char*errors=cJSON_PrintUnformatted(err);
        send(client_socket,errors,strlen(errors),0);
        close(client_socket);
        close(server_socket);
             }
        return 0;
    }
        else{
            char*content = NULL;
              char*type = NULL;
              char*err = createJSON();
              content = cJSON_CreateString("You are not in this channel.");
              type= cJSON_CreateString("Error");
              cJSON_AddItemToObject(err, "type", type);
              cJSON_AddItemToObject(err, "content", content);
              char*errors=cJSON_PrintUnformatted(err);
              send(client_socket,errors,strlen(errors),0);
              close(client_socket);
              close(server_socket);
            return 0;

        }

    }
    else{
        char*content = NULL;
          char*type = NULL;
          char*err = createJSON();
          content = cJSON_CreateString("Wrong AuthToken");
          type= cJSON_CreateString("Error");
          cJSON_AddItemToObject(err, "type", type);
          cJSON_AddItemToObject(err, "content", content);
          char*errors=cJSON_PrintUnformatted(err);
          send(client_socket,errors,strlen(errors),0);
          close(client_socket);
          close(server_socket);
        return 0;

    }
    return 0;
}





int leavech(char authtoken[],int client_socket,int server_socket){
    char channel[MAX],chname[MAX];
    if((cn=fopen("channelname.txt", "r"))!=NULL){
            fgets(channel, MAX, cn);
            fclose(cn);
    }
    strcpy(chname, channel);
    strcat(channel, ".channel.json");
    char usn[MAX];
    if((at=fopen("authtok.txt", "r"))!=NULL){
        fgets(authtok, 25, at);
        fclose(at);
    }
    if (strncmp(authtok, authtoken, 24)==0) {
        if(dircheck(channel)==0){
            channels=fopen(channel, "r");
            char tmsg[MAX];
            fgets(tmsg, MAX, channels);
            fclose(channels);
            channels=fopen(channel, "w");
            char*curde=cJSON_Parse(tmsg);
    char*messages = NULL;
        char*msg=NULL;
        char*sender=NULL;
        messages= cJSON_GetObjectItem(curde, "messages");
        sender=cJSON_CreateString("server");
        char wtwam[MAX];
            if((un=fopen("username.txt", "r"))!=NULL){

                fgets(usn, MAX, un);
                fclose(un);
        }
        strcpy(wtwam, usn);
        strcat(wtwam, " left ");
        strcat(wtwam, chname);
        strcat(wtwam, ".");
        msg=cJSON_CreateString(wtwam);
        char*eachmsg=createJSON();
        cJSON_AddItemToObject(eachmsg, "sender", sender);
        cJSON_AddItemToObject(eachmsg, "content", msg);
        cJSON_AddItemToArray(messages, eachmsg);
        char*mems = NULL;
            char*mem = NULL;
        mems=cJSON_GetObjectItem(curde, "members");
            int i=0;
            cJSON_ArrayForEach(mem, mems){
                if (strcmp(mem->valuestring,usn)==0) {
                    cJSON_DeleteItemFromArray(mems, i);
                }
                i++;
            }
        char* wtp=cJSON_PrintUnformatted(curde);
        fprintf(channels, "%s",wtp);
        fclose(channels);
        char*content = NULL;
        char*type = NULL;
        char*err = createJSON();
           content = cJSON_CreateString("");
        type= cJSON_CreateString("Successful");
           cJSON_AddItemToObject(err, "type", type);
        cJSON_AddItemToObject(err, "content", content);
        char*errors=cJSON_PrintUnformatted(err);
        send(client_socket,errors,strlen(errors),0);
        close(client_socket);
        close(server_socket);
        return 0;

    }
        else{
            char*content = NULL;
              char*type = NULL;
              char*err = createJSON();
              content = cJSON_CreateString("You are not in this channel.");
              type= cJSON_CreateString("Error");
              cJSON_AddItemToObject(err, "type", type);
              cJSON_AddItemToObject(err, "content", content);
              char*errors=cJSON_PrintUnformatted(err);
              send(client_socket,errors,strlen(errors),0);
              close(client_socket);
              close(server_socket);
            return 0;



        }
    }
    else{
        char*content = NULL;
          char*type = NULL;
          char*err = createJSON();
          content = cJSON_CreateString("Wrong AuthToken.");
          type= cJSON_CreateString("Error");
          cJSON_AddItemToObject(err, "type", type);
          cJSON_AddItemToObject(err, "content", content);
          char*errors=cJSON_PrintUnformatted(err);
          send(client_socket,errors,strlen(errors),0);
          close(client_socket);
          close(server_socket);
        return 0;
    }

    return 0;
}


*/




int logou(char authtoken[],int client_socket,int server_socket){
    if((at=fopen("authtok.txt", "r"))!=NULL){
        fgets(authtok, 25, at);
        fclose(users);
    }
    if (memcmp(authtok, authtoken, 24)==0) {
        char atok[24];
        if((at=fopen("authtok.txt", "w"))!=NULL){
            for (int i=0; i<24; i++) {
                atok[i]='a';
            }
            fprintf(at, "%s\n",atok);
            fclose(at);
        }
        char content[MAX] = "";
                char type[MAX] = "Successful";
              char err[MAX] ="{}";
                   AddIOJSON(err, "type", type);
                AddIOJSON(err, "content", content);
              printf("%s\n",err);
                char*errors=err;
                send(client_socket,errors,strlen(errors),0);
        close(client_socket);
              close(server_socket);
        return 0;
    }
    return 0;
}







int joinch(char channel[], char chname[],char authtoken[],int client_socket,int server_socket){
    strcat(channel, ".channel.json");
    char usn[MAX],chdetails[MAX];
    if((at=fopen("authtok.txt", "r"))!=NULL){
        fgets(authtok, 25, at);
        fclose(at);
    }
    if (strncmp(authtok, authtoken, 24)==0) {
        if(dircheck(channel)==1){
            if((channels=fopen(channel, "r"))!=NULL){
                fgets(chdetails, MAX, channels);
                fclose(channels);
            }
            if((channels=fopen(channel, "w"))!=NULL){
    char messages[MAX]="[]";
            char mem[MAX]="[]";
                printf("1\n");
       AddIOJSON(chdetails, "name", chname);
        AddIOJSON(chdetails, "messages", messages);
            AddIOJSON(chdetails, "members", mem);
        char wtwam[MAX];
            if((un=fopen("username.txt", "r"))!=NULL){
                fgets(usn, MAX, un);
                fclose(un);
        }
        strcpy(wtwam, usn);
        strcat(wtwam, " created ");
        strcat(wtwam, chname);
        strcat(wtwam, ".");
        char eachmsg[MAX]="{}";
                printf("hi\n");
        AddIOJSON(eachmsg, "sender", "server");
        AddIOJSON(eachmsg, "content", wtwam);
        AddIAJSON(messages, eachmsg);
            AddIAJSON(mem, usn);
                printf("2\n");
        fprintf(channels, "%s",chdetails);
        fclose(channels);
            }
        char content[MAX] = "";
                char type[MAX] = "Successful";
              char err[MAX] ="{}";
                   AddIOJSON(err, "type", type);
                AddIOJSON(err, "content", content);
              printf("%s\n",err);
                char*errors=err;
                send(client_socket,errors,strlen(errors),0);
        close(client_socket);
              close(server_socket);
            if((cn=fopen("channelname.txt", "w"))!=NULL){
                    fprintf(cn, "%s",chname);
                    fclose(cn);
            }
        return 0;

    }
        else{
            char content[MAX] = "Name not available";
                    char type[MAX] = "Successful";
                  char err[MAX] ="{}";
                       AddIOJSON(err, "type", type);
                    AddIOJSON(err, "content", content);
                    send(client_socket,err,strlen(err),0);
            close(client_socket);
                  close(server_socket);
                  return 0;
        }
    }
    else{
        char content[MAX] = "Wrong AuthToken";
                char type[MAX] = "Successful";
              char err[MAX] ="{}";
                   AddIOJSON(err, "type", type);
                AddIOJSON(err, "content", content);
                send(client_socket,err,strlen(err),0);
        close(client_socket);
              close(server_socket);
              return 0;
    }
    return 0;
}






int createch(char channel[], char chname[],char authtoken[],int client_socket,int server_socket){
    strcat(channel, ".channel.json");
    char usn[MAX];
    if((at=fopen("authtok.txt", "r"))!=NULL){
        fgets(authtok, 25, at);
        fclose(at);
    }
    if (strncmp(authtok, authtoken, 24)==0) {
        if(dircheck(channel)==1){
            if((channels=fopen(channel, "w"))!=NULL){
    char messages[MAX]="[]";
    char chdetails[MAX] ="{}";
        char sender[MAX];
            char mem[MAX]="[]";
                printf("1\n");
       AddIOJSON(chdetails, "name", chname);
        AddIOJSON(chdetails, "messages", messages);
            AddIOJSON(chdetails, "members", mem);
        char wtwam[MAX];
            if((un=fopen("username.txt", "r"))!=NULL){
                fgets(usn, MAX, un);
                fclose(un);
        }
        strcpy(wtwam, usn);
        strcat(wtwam, " created ");
        strcat(wtwam, chname);
        strcat(wtwam, ".");
        char eachmsg[MAX]="{}";
                printf("hi\n");
        AddIOJSON(eachmsg, "sender", "server");
        AddIOJSON(eachmsg, "content", wtwam);
        AddIAJSON(messages, eachmsg);
            AddIAJSON(mem, usn);
                printf("2\n");
        fprintf(channels, "%s",chdetails);
        fclose(channels);
            }
        char content[MAX] = "";
                char type[MAX] = "Successful";
              char err[MAX] ="{}";
                   AddIOJSON(err, "type", type);
                AddIOJSON(err, "content", content);
              printf("%s\n",err);
                char*errors=err;
                send(client_socket,errors,strlen(errors),0);
        close(client_socket);
              close(server_socket);
            if((cn=fopen("channelname.txt", "w"))!=NULL){
                    fprintf(cn, "%s",chname);
                    fclose(cn);
            }
        return 0;

    }
        else{
            char content[MAX] = "Name not available";
                    char type[MAX] = "Successful";
                  char err[MAX] ="{}";
                       AddIOJSON(err, "type", type);
                    AddIOJSON(err, "content", content);
                    send(client_socket,err,strlen(err),0);
            close(client_socket);
                  close(server_socket);
                  return 0;
        }
    }
    else{
        char content[MAX] = "Wrong AuthToken";
                char type[MAX] = "Successful";
              char err[MAX] ="{}";
                   AddIOJSON(err, "type", type);
                AddIOJSON(err, "content", content);
                send(client_socket,err,strlen(err),0);
        close(client_socket);
              close(server_socket);
              return 0;
    }
    return 0;
}


int reg(char user[], char uname[],char pass[],int client_socket,int server_socket){
  strcat(user, ".user.json");
      if(dircheck(user)==1){
  if((users=fopen(user, "a"))!=NULL){
    char*username = uname;
    char*password = pass;
    char userdetails[MAX] = "{}";
       AddIOJSON(userdetails, "username", username);
    AddIOJSON(userdetails, "password", password);
     AddIOJSON(userdetails, "point", "0");
      printf("%s\n",userdetails);
        fprintf(users, "%s",userdetails);
        fclose(users);
        char content[MAX] = "";
        char type[MAX] = "Successful";
      char err[MAX] ="{}";
           AddIOJSON(err, "type", type);
        AddIOJSON(err, "content", content);
      printf("%s\n",err);
        char*errors=err;
        send(client_socket,errors,strlen(errors),0);
close(client_socket);
      close(server_socket);
      return 0;
    }
  }
  else{
    char*content = "This username is not available.";
    char*type = "Error";
    char*err = createJSON();
       AddIOJSON(err, "type", type);
    AddIOJSON(err, "content", content);
    char*errors=err;
    send(client_socket,errors,strlen(errors),0);
close(client_socket);
  close(server_socket);
  return 0;
  }
    return 0;
}

int logi(char user[], char uname[],char pass[],int client_socket,int server_socket){
  strcat(user, ".user.json");
      if(dircheck(user)==0){
  if((users=fopen(user, "r"))!=NULL){
      char msg[MAX];
      fgets(msg, MAX, users);
      char password[MAX];
      GetOIJSON(msg, "password",password);
      if (strcmp(password, pass)==0) {
        char tok[24];
        srand(time(0));
             for (int i=0; i<24; i++) {
                 sprintf(&tok[i], "%d",rand()%10);
             }
          printf("%s\n",tok);
        strncpy(authtok, tok,24);
          if((at=fopen("authtok.txt", "w"))!=NULL){
              fprintf(at, "%s",tok);
              fclose(at);
          }
          if((un=fopen("username.txt", "w"))!=NULL){
              fprintf(un, "%s",uname);
              fclose(un);
          }
          char err [MAX]="{}";
           AddIOJSON(err, "type", "AuthToken");
        AddIOJSON(err, "content", authtok);
        send(client_socket,err,strlen(err),0);
        close(client_socket);
          close(server_socket);

          return 0;
      }
      else{

            char err [MAX]="{}";
             AddIOJSON(err, "type", "Error");
          AddIOJSON(err, "content", "Wrong password.");
          send(client_socket,err,strlen(err),0);
          close(client_socket);
            close(server_socket);
          return 0;
      }
    }
  }
    else{
        char err [MAX]="{}";
           AddIOJSON(err, "type", "Error");
        AddIOJSON(err, "content", "Username is not valid.");
        send(client_socket,err,strlen(err),0);
        close(client_socket);
          close(server_socket);
        return 0;
    }
    return 0;
}


int main(){
     int server_socket, client_socket;
    while (1) {
    struct sockaddr_in server, client;
         server_socket = socket(AF_INET, SOCK_STREAM, 0);
           if (server_socket == -1) {
             printf("Socket creation failed...\n");
             exit(0);
           }
           bzero(&server, sizeof(server));
           server.sin_family = AF_INET;
           server.sin_addr.s_addr = htonl(INADDR_ANY);
           server.sin_port = htons(PORT);
        int opt = 1;
        if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt))<0) {perror("setsockopt");exit(EXIT_FAILURE);}if(setsockopt(server_socket, SOL_SOCKET, SO_REUSEPORT, (char *)&opt, sizeof(opt))<0)   {
                  perror("setsockopt");exit(EXIT_FAILURE);}
        if ((bind(server_socket, (SA*)&server, sizeof(server))) != 0) {
          printf("Socket binding failed...\n");
          exit(0);
        }
        if ((listen(server_socket, 5)) != 0) {
          printf("Listen failed...\n");
          exit(0);
        }
        socklen_t len = sizeof(client);
    client_socket = accept(server_socket, (SA*)&client, &len);
    if (client_socket < 0) {
      printf("Server accceptance failed...\n");
      exit(0);
    }
    char request[MAX];
    bzero(request, sizeof(request));
    recv(client_socket, request, sizeof(request), 0);
    char f_part[MAX];
    sscanf(request,"%s",f_part);
    if (memcmp("register", f_part,8)==0) {
        shutdown(client_socket, SHUT_RD);
       char user[MAX],pass[MAX];
      sscanf(request,"%*s %s %s",user,pass);
        char userf[strlen(user)-1],userff[strlen(user)-1];
        strncpy(userf, user,strlen(user)-1);
        strcpy(userff,userf);
        printf("%s is 0\n%s is 1\n%s is 2\n",user,userf,userff);
        reg(userf,userff ,pass, client_socket,server_socket);
    }
    if (memcmp("login", f_part,5)==0) {
      shutdown(client_socket, SHUT_RD);
     char user[MAX],pass[MAX];
    sscanf(request,"%*s %s %s",user,pass);
      char userf[strlen(user)-1],userff[strlen(user)-1];
      strncpy(userf, user,strlen(user)-1);
      strcpy(userff,userf);
        printf("%s\n%s\n%s\n",user,userf,pass);
      logi(userf,userff ,pass, client_socket,server_socket);
    }
//    if (memcmp("create", f_part,6)==0) {
//        shutdown(client_socket, SHUT_RD);
//       char channelname[MAX],authtoken[MAX];
//      sscanf(request,"%*s %*s %s %s",channelname,authtoken);
//        char channelnamef[MAX],channelnameff[MAX];
//        strncpy(channelnamef, channelname, strlen(channelname)-1);
//        strncpy(channelnameff, channelnamef, strlen(channelname)-1);
//        createch(channelnamef,channelnameff, authtoken, client_socket,server_socket);
//    }
//    if (memcmp("join", f_part,4)==0) {
//        shutdown(client_socket, SHUT_RD);
//       char channelname[MAX],authtoken[MAX];
//      sscanf(request,"%*s %*s %s %s",channelname,authtoken);
//        char channelnamef[MAX],channelnameff[MAX];
//        strncpy(channelnamef, channelname, strlen(channelname)-1);
//        strncpy(channelnameff, channelnamef, strlen(channelname)-1);
//        joinch(channelnamef,channelnameff, authtoken, client_socket,server_socket);
//    }
    if (memcmp("logout", f_part,6)==0) {
        shutdown(client_socket, SHUT_RD);
       char authtoken[MAX];
      sscanf(request,"%*s %s",authtoken);
        logou(authtoken,client_socket,server_socket);
    }
//    if (memcmp("send", f_part,4)==0) {
//        shutdown(client_socket, SHUT_RD);
//       char message[MAX],authtoken[MAX];
//      sscanf(request,"%*s %s %s",message,authtoken);
//        char messagef[MAX];
//        strncpy(messagef, message, strlen(message)-1);
//        sendmessage(message, authtoken,client_socket,server_socket);
//    }
//    if (memcmp("leave", f_part,5)==0) {
//            shutdown(client_socket, SHUT_RD);
//           char authtoken[MAX];
//          sscanf(request,"%*s %s",authtoken);
//            leavech(authtoken,client_socket,server_socket);
//    }
//    if (memcmp("channel", f_part,7)==0) {
//        shutdown(client_socket, SHUT_RD);
//       char authtoken[MAX];
//      sscanf(request,"%*s %*s %s",authtoken);
//        chmembers(authtoken,client_socket,server_socket);
//    }
//    if (memcmp("refresh", f_part,7)==0) {
//        shutdown(client_socket, SHUT_RD);
//       char authtoken[MAX];
//      sscanf(request,"%*s %s",authtoken);
//        refr(authtoken,client_socket,server_socket);
//    }
    if (memcmp("exit", f_part,4)==0) {
        break;
    }
    }

    return 0;
}











