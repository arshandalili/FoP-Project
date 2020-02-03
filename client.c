#include <stdio.h>
#include <stdbool.h>
#include "cJSON.c"
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
//#include "cJK.h"
//#include "cJK.c"
#define MAX 10000
#define PORT 12345
#define SA struct sockaddr
char authtok[24];
int main(void);
void reg(void);
void logi(void);
void mainmenu(void);
void createch(void);
void joinch(void);
void logou(void);
void chmenu(void);
void sendmessage(void);
void refr(void);
void chmembers(void);
void leavech(void);

void leavech(){
    int client_socket, server_socket;
    struct sockaddr_in servaddr, cli;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Connection to the server failed...\n");
        exit(0);
    }
      char request[2*MAX]="leave ";
    strcat(request,authtok);
      send(client_socket,request,strlen(request),0);
      bzero(request, sizeof(request));
      shutdown(client_socket, SHUT_WR);
      recv(client_socket, request, sizeof(request), 0);
      char fresp[strlen(request)];
      strcpy(fresp, request);
      char err[]="Error";
      cJSON *iferr=NULL;
      cJSON *errdec;
      cJSON *sent = cJSON_Parse(fresp);
      iferr= cJSON_GetObjectItemCaseSensitive(sent, "type");
      errdec=cJSON_GetObjectItemCaseSensitive(sent, "content");
      if (strcmp(err, iferr->valuestring)==0) {
          printf("%s:\n%s\n",iferr->valuestring,errdec->valuestring);
          chmenu();
      }
      else printf("Successfully Left Channel!\n");
    shutdown(client_socket, SHUT_RDWR);
        mainmenu();


}

void chmembers(){
    int client_socket, server_socket;
    struct sockaddr_in servaddr, cli;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Connection to the server failed...\n");
        exit(0);
    }
      char request[2*MAX]="channel members ";
    strcat(request,authtok);
      send(client_socket,request,strlen(request),0);
      bzero(request, sizeof(request));
      shutdown(client_socket, SHUT_WR);
      recv(client_socket, request, sizeof(request), 0);
      char fresp[strlen(request)];
      strcpy(fresp, request);
      char err[]="Error";
      cJSON *iferr=NULL;
      cJSON *errdec;
      cJSON *sent = cJSON_Parse(fresp);
      iferr= cJSON_GetObjectItemCaseSensitive(sent, "type");
      errdec=cJSON_GetObjectItemCaseSensitive(sent, "content");
      if (strncmp(err, iferr->valuestring,5)==0) {
          printf("%s:\n%s\n",iferr->valuestring,errdec->valuestring);
      }
      else{
      cJSON *contentall=cJSON_GetObjectItemCaseSensitive(sent, "content");
          cJSON *details;
          printf("Channel members\n");
      cJSON_ArrayForEach(details, contentall){
          printf("%s\n",(details->valuestring));
      }
      }
    shutdown(client_socket, SHUT_RDWR);
        chmenu();


}

void refr(){
  int client_socket, server_socket;
    struct sockaddr_in servaddr, cli;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Connection to the server failed...\n");
        exit(0);
    }
      char request[2*MAX]="refresh ";
    strcat(request,authtok);
      send(client_socket,request,strlen(request),0);
      bzero(request, sizeof(request));
      shutdown(client_socket, SHUT_WR);
      recv(client_socket, request, sizeof(request), 0);
      char fresp[strlen(request)];
    strcpy(fresp, request);
    char err[]="Error";
    cJSON *iferr=NULL;
    cJSON *errdec;
    cJSON *sent = cJSON_Parse(fresp);
    iferr= cJSON_GetObjectItemCaseSensitive(sent, "type");
    errdec=cJSON_GetObjectItemCaseSensitive(sent, "content");
    if (strncmp(err, iferr->valuestring,5)==0) {
        printf("%s:\n%s\n",iferr->valuestring,errdec->valuestring);
    }
    else{
    cJSON *contentall=cJSON_GetObjectItemCaseSensitive(sent, "content");
        cJSON *details;
    cJSON_ArrayForEach(details, contentall){
        cJSON *sender =cJSON_GetObjectItemCaseSensitive(details, "sender");
        cJSON *content = cJSON_GetObjectItemCaseSensitive(details, "content");
        printf("%s: %s\n",(sender->valuestring), (content->valuestring));
    }
    }
    shutdown(client_socket, SHUT_RDWR);

        chmenu();

}

void sendmessage(){
  int client_socket, server_socket;
  struct sockaddr_in servaddr, cli;
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
      printf("Socket creation failed...\n");
      exit(0);
  }
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(PORT);
  if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
      printf("Connection to the server failed...\n");
      exit(0);
  }
  char message[MAX];
    char tmsg[10];
  char request[3*MAX]="send ";
  printf("Enter Your Message:\n");
    fgets(tmsg, 10, stdin);
 scanf("%[^\n]s ",message);
  strcat(request,message);
  strcat(request,", ");
  strcat(request,authtok);
    char freq[strlen(request)];
    strcpy(freq, request);
    send(client_socket,freq,sizeof(freq),0);
    bzero(request, sizeof(request));
    shutdown(client_socket, SHUT_WR);
    recv(client_socket, request, sizeof(request), 0);
    char fresp[strlen(request)];
    strcpy(fresp, request);
    char err[]="Error";
    cJSON *iferr=NULL;
    cJSON *errdec;
    cJSON *sent = cJSON_Parse(fresp);
    iferr= cJSON_GetObjectItemCaseSensitive(sent, "type");
    errdec=cJSON_GetObjectItemCaseSensitive(sent, "content");
    if (strncmp(err, iferr->valuestring,5)==0) {
        printf("%s:\n%s\n",iferr->valuestring,errdec->valuestring);
    }
    else printf("Message Successfully Sent!\n");
  shutdown(client_socket, SHUT_RDWR);
  chmenu();

}
void chmenu(){
    printf("1. Send Message\n");
    printf("2. Refresh\n");
    printf("3. Channel Members\n");
    printf("4. Leave Channel\n");
    int i2=0;
    scanf("%d",&i2);
    if(i2==1) sendmessage();
    if(i2==2) refr();
    if(i2==3) chmembers();
    if(i2==4) leavech();


}
void mainmenu(){
  printf("1. Create Channel\n");
  printf("2. Join Channel\n");
  printf("3. Logout\n");
  int io=0;
  scanf("%d", &io);
  if(io==1) createch();
  if(io==2) joinch();
  if(io==3) logou();
}


void joinch(){
  int client_socket, server_socket;
  struct sockaddr_in servaddr, cli;
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
      printf("Socket creation failed...\n");
      exit(0);
  }
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(PORT);
  if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
      printf("Connection to the server failed...\n");
      exit(0);
  }
  char chname[MAX];
  printf("Enter Channel's Name:\n");
  scanf("%s", chname);
  char request[3*MAX]="join channel ";
  strcat(request,chname);
  strcat(request,", ");
  strcat(request,authtok);
    send(client_socket,request,strlen(request),0);
    bzero(request, sizeof(request));
    shutdown(client_socket, SHUT_WR);
    recv(client_socket, request, sizeof(request), 0);
    char fresp[strlen(request)];
    strcpy(fresp, request);
    char err[]="Error";
    cJSON *iferr=NULL;
    cJSON *errdec;
    cJSON *sent = cJSON_Parse(fresp);
    iferr= cJSON_GetObjectItemCaseSensitive(sent, "type");
    errdec=cJSON_GetObjectItemCaseSensitive(sent, "content");
    shutdown(client_socket, SHUT_RDWR);
    if (strcmp(err, iferr->valuestring)==0) {
        printf("%s:\n%s\n",iferr->valuestring,errdec->valuestring);
        mainmenu();
    }
    else printf("Successfully Joined Channel!\n");
    chmenu();
}


void createch(){
  int client_socket, server_socket;
  struct sockaddr_in servaddr, cli;
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
      printf("Socket creation failed...\n");
      exit(0);
  }
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(PORT);
  if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
      printf("Connection to the server failed...\n");
      exit(0);
  }
  char chname[MAX];
  printf("Enter Channel's Name:\n");
  scanf("%s", chname);
  char request[3*MAX]="create channel ";
  strcat(request,chname);
  strcat(request,", ");
  strcat(request,authtok);
    send(client_socket,request,strlen(request),0);
    bzero(request, sizeof(request));
    shutdown(client_socket, SHUT_WR);
    recv(client_socket, request, sizeof(request), 0);
    char fresp[strlen(request)];
    strcpy(fresp, request);
    char err[]="Error";
    cJSON *iferr=NULL;
    cJSON *errdec;
    cJSON *sent = cJSON_Parse(fresp);
    iferr= cJSON_GetObjectItemCaseSensitive(sent, "type");
    errdec=cJSON_GetObjectItemCaseSensitive(sent, "content");
    shutdown(client_socket, SHUT_RDWR);
    if (strcmp(err, iferr->valuestring)==0) {
        printf("%s:\n%s\n",iferr->valuestring,errdec->valuestring);
        mainmenu();
    }
    else printf("Channel Successfully Created!\n");
    chmenu();
}




void logi(){
  int client_socket, server_socket;
  struct sockaddr_in servaddr, cli;
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
      printf("Socket creation failed...\n");
      exit(0);
  }
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(PORT);
  if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
      printf("Connection to the server failed...\n");
      exit(0);
  }
  char username[MAX];
  char pass[MAX];
  printf("Enter Username:\n");
  scanf("%s", username);
  printf("Enter Pssword:\n");
  scanf("%s", pass);
    char unamef[strlen(username)];
    strcpy(unamef, username);
    char pf[strlen(pass)];
    strcpy(pf, pass);
  char request[5*MAX]="login ";
  strcat(request,unamef);
  strcat(request,", ");
  strcat(request,pf);
    send(client_socket,request,strlen(request),0);
    bzero(request, sizeof(request));
    shutdown(client_socket, SHUT_WR);
    recv(client_socket, request, sizeof(request), 0);
    char fresp[strlen(request)];
    strcpy(fresp, request);
    char err[]="Error";
    char authtoken[]="AuthToken";
    cJSON *iferr=NULL;
    cJSON *errdec;
    cJSON *sent = cJSON_Parse(fresp);
    iferr= cJSON_GetObjectItemCaseSensitive(sent, "type");
    errdec=cJSON_GetObjectItemCaseSensitive(sent, "content");
    shutdown(client_socket, SHUT_RDWR);
    if (strcmp(err, iferr->valuestring)==0) {
        char already_logged_in[]="The user";
        if(strncmp(already_logged_in, errdec->valuestring, 8)==0){
            printf("%s:\n%s\n",iferr->valuestring,errdec->valuestring);
            mainmenu();
        }
        else{
            printf("%s:\n%s\n",iferr->valuestring,errdec->valuestring);
        main();
        }
    }
    else if(strcmp(authtoken, iferr->valuestring)==0){
        printf("Successfully Logged in\n");
        strncpy(authtok, errdec->valuestring,24);
    }
  mainmenu();

}


void reg(){
  int client_socket, server_socket;
  struct sockaddr_in servaddr, cli;
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
      printf("Socket creation failed...\n");
      exit(0);
  }
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(PORT);
  if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
      printf("Connection to the server failed...\n");
      exit(0);
  }
  char username[MAX];
  char pass[MAX];
  printf("Enter Username:\n");
  scanf("%s", username);
  printf("Enter Pssword:\n");
  scanf("%s", pass);
  char request[5*MAX];
    sprintf(request, "register %s, %s",username,pass);
    send(client_socket,request,strlen(request),0);
    bzero(request, sizeof(request));
    shutdown(client_socket, SHUT_WR);
    recv(client_socket, request, sizeof(request), 0);
    char fresp[strlen(request)];
    strcpy(fresp, request);
    char err[]="Error";
      cJSON *iferr=NULL;
      cJSON *errdec;
      cJSON *sent = cJSON_Parse(fresp);
      iferr= cJSON_GetObjectItemCaseSensitive(sent, "type");
      errdec=cJSON_GetObjectItemCaseSensitive(sent, "content");
      if (strcmp(err, iferr->valuestring)==0) {
          printf("%s:\n%s\n",iferr->valuestring,errdec->valuestring);
          main();
      }
      else printf("Successfully Registered!\n");
    shutdown(client_socket, SHUT_RDWR);
        main();

}

void logou(){
  int client_socket, server_socket;
      struct sockaddr_in servaddr, cli;
      client_socket = socket(AF_INET, SOCK_STREAM, 0);
      if (client_socket == -1) {
          printf("Socket creation failed...\n");
          exit(0);
      }
      bzero(&servaddr, sizeof(servaddr));
      servaddr.sin_family = AF_INET;
      servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
      servaddr.sin_port = htons(PORT);
      if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
          printf("Connection to the server failed...\n");
          exit(0);
      }



  char request[2*MAX]="logout ";
  strcat(request,authtok);
    send(client_socket,request,strlen(request),0);
    bzero(request, sizeof(request));
    shutdown(client_socket, SHUT_WR);
    recv(client_socket, request, sizeof(request), 0);
    char fresp[strlen(request)];
    strcpy(fresp, request);
    char err[]="Error";
      cJSON *iferr=NULL;
      cJSON *errdec;
      cJSON *sent = cJSON_Parse(fresp);
      iferr= cJSON_GetObjectItemCaseSensitive(sent, "type");
      errdec=cJSON_GetObjectItemCaseSensitive(sent, "content");
      if (strcmp(err, iferr->valuestring)==0) {
          printf("%s:\n%s\n",iferr->valuestring,errdec->valuestring);
          mainmenu();
      }
      else printf("Successfully Logged Out!\n");
    shutdown(client_socket, SHUT_RDWR);

  main();
}

int main()
{
        int i1;
        printf("Account Menu:\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit Program\n");
        scanf("%d", &i1);
        if(i1==1) reg();
        if(i1==2) logi();
        if(i1==3)  {
            int client_socket, server_socket;
            struct sockaddr_in servaddr, cli;
            client_socket = socket(AF_INET, SOCK_STREAM, 0);
            if (client_socket == -1) {
                printf("Socket creation failed...\n");
                exit(0);
            }
            bzero(&servaddr, sizeof(servaddr));
            servaddr.sin_family = AF_INET;
            servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
            servaddr.sin_port = htons(PORT);
            if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
                printf("Connection to the server failed...\n");
                exit(0);
            }
            char request[]="exit";
            send(client_socket,request,strlen(request),0);
            
            exit(0) ;
            
        }
    return 0;
}
