#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>


int main(int argc, char** argv)
{

        char line[256];
        int socketfd, clientfd;
        char buf[500];
        char *buff;


        if((socketfd = socket(AF_INET, SOCK_STREAM, 0))== -1) {
                fprintf(stderr, "Socket does not work\n");
                exit(1);
        }

        //if((send(socketfd, buf, sizeof(buf), 0))== -1) {
        //      fprintf(stderr, "Not sending messages\n");
        //      close(socketfd);
        //      exit(1);
        //}



        while(1){

                //get command line for one-word name 
                if(argc == 2){
                        printf("%s> ", argv[1]);

              //else it uses the default my_chat
                }else{
                        printf("my_chat> ");

                }

                //checking command line argments 
                if(!fgets(line, 256, stdin)){
                        fprintf(stderr, "Invalid input!\n");                                 
                }


                //quit statement 
                if (strcmp(line, "quit\n") == 0)
                {
                        fflush(stdout);
                        exit(0);
                        perror("Could not quit!\n");
                }


                if(argc == 3){
                        printf("Client: Enter Data for Server:\n");

                }

                //if((send(socketfd, buf, strlen(buf), 0))== -1) {
                //      fprintf(stderr, "Not sending messages\n");
                //      close(socketfd);
                //      exit(1);
                //}

}

}
