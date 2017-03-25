#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>
#include <crypt.h>


static const int MAX_PASS_SIZE = 4;
static const char alpha[] =
"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const int alpha_length = sizeof(alpha) - 1;
static char hash[14];
static char salt[3];

void bruteAtk(char* password, int index, int position);
void bruteSelect(int max_size);

int main(int argc, char* argv[]){
    if(argc == 2){
        //initialize string containing all letters of the alphabet - size 52
        
        //set global var hash to command line input
        strncpy(hash, argv[1], 13);
        hash[13] = '\0';
        
        //acquire salt from hash string
        strncpy(salt, hash, 2);
        salt[2] = '\0';
        
        //call brute force attack sequencer
        bruteSelect(MAX_PASS_SIZE);
        printf("\n");
    }
    else{
        printf("Input Error");
        return 1;
    }
}

void bruteAtk(char* password, int index, int position){
    //iterate through the alphabet for each position in the array
    for(int i = 0; i < alpha_length; i++){
        password[index] = alpha[i];
        if(index == position - 1){
            if(strcmp(hash, crypt(password, salt)) == 0){
               printf("%s", password);
                return; 
            }
            //return;
        }
        //if password == crypt(hash,salt) print pass
        /*else if(!strcmp(password, crypt(hash, salt)) == 0){
            
        } */
        else{ bruteAtk(password, index + 1, position);}
    }
    return;
}

void bruteSelect(int max_size) {
    //allocate memory for password string
    char* password = calloc(max_size + 1, sizeof(char));
    //initialize password and call bruteAtk for each length
    for(int length = 1; length <= max_size; length++ ){
        //memset(password, 0, max_size + 1);
        bruteAtk(password, 0, length);
    }
}