#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//prints Name and phone number of a single contact.
void print(Key k, Value v){
    printf("%s, %s\n", k, v);
}

//Compares two Names. Returns 0 if they are the same, -1 if p is greater
//than s and 1 if s is greater than p.
int compare(Key p, Key s){
    return strcmp(p, s);
}

//Takes an input from the user which is asked to type one of the foru commands:
//A,D,P,Q. Only those commands are accepted and are passed back.
void userInput(char *command){
    char line[100];
    bool invalid = true;
    do{
        printf("Please enter your command:");
        fgets(line,sizeof(line),stdin);
        sscanf(line,"%c",command);
        *command = toupper(*command);
        char *comms = "ADPQadpq";
        int contains = strcspn(line,comms);
        if(strlen(line) == 2 && contains == 0){
            invalid = false;
        }
        else{
            printf("Invalid input, please try again.\n");
        }
    } while(invalid);
}

//Applies the command that was successfully inputted by user. If command is P it
//will print all the contacts. If command is Q it will exit the program. If
//command is A it will ask user to enter the name and phone number for a new
//conntact and it will add it to the tree. If command is D it will prompt the
//user for the name of the contact that is to be deleted and will delete it.
void applyCommand(char *command, tree *t, bool *finished){
    if(*command == 'P'){
        printTree(t);
    }
    if(*command == 'Q'){
        *finished = true;
    }
    if(*command == 'A'){
        printf("Please enter contact name: ");
        char input[100];
        char *name = malloc(20);
        char *phoneNumber = malloc(10);
        fgets(input, sizeof(input), stdin);
        sscanf(input,"%s",name);
        Key newKey = malloc(sizeof(Key));
        newKey = (Key) {name};
        printf("Now enter the phone number: ");
        fgets(input, sizeof(input), stdin);
        sscanf(input,"%s",phoneNumber);
        Value newVal = malloc(sizeof(Value));
        newVal = (Value) {phoneNumber};
        insert(newKey, newVal, t);
        printf("Contact successfully added!\n");
    }
    if(*command == 'D'){
        printf("Please enter contact name: ");
        char input[100];
        char *name = malloc(20);
        fgets(input, sizeof(input), stdin);
        sscanf(input,"%s",name);
        Key *newKey = malloc(sizeof(Key));
        *newKey = (Key) {name};
        delete(*newKey, t);
        printf("Contact successfully deleted!\n");
    }
}

//Creates new, empty tree (contact list) and prints out the details on how to
//use the program. It will then continuosly prompt user for the commands untill
//he enters command Q which will exit the program.
int main(){
    tree *t = newTree();
    printf("\nWelcome to your personal contact list.\n");
    printf("Please use the following four commands:\n");
    printf("A: Allows you to add new contact.\n");
    printf("D: Allows you to delete an existing contact.\n");
    printf("P: Prints all your contacts.\n");
    printf("Q: Exits the program.\n\n");
    bool finished = false;
    do{
        char command;
        userInput(&command);
        applyCommand(&command, t, &finished);
    } while(!finished);
    return 0;
}
