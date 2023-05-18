#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "book.h"

    Book* make_book(int numLines){
        
        Book* newBook = malloc(sizeof(Book));

        newBook->characterCount = 0;
        newBook->lineCount = 0;
        newBook->lines = malloc(numLines*sizeof(char*));

        return newBook;

    }

    void burn_book(Book* bookPtr){
    
        for (int i = 0; i < bookPtr->lineCount; i++) {

        free(bookPtr->lines[i]);

     }

        free(bookPtr->lines);

        free(bookPtr);

    }

    bool save_book(Book* bookPtr, char* fileName){
        
        bool savedContents = 1;
        
        if (bookPtr == NULL){
            savedContents = 0;
        }

        if (fileName == NULL){
            savedContents = 0;
        }

        FILE* filePtr = fopen(fileName, "w");

        for (int i = 0; i < bookPtr->lineCount; i++){
            fprintf(filePtr, "%s", bookPtr->lines[i]);
        }

        fclose(filePtr);
        
        return savedContents;

    }

     bool fill_book(Book* bookPtr, char* fileName){
        
        FILE* filePtr;
        bool success = 1;

        char* buffer = malloc(sizeof(char) * 100000);

        filePtr = fopen(fileName, "r");
        

        if(filePtr == NULL){
            return success = 0;
        }

        int i = 0;
        while(fgets(buffer, 99999, filePtr) != NULL){

            bookPtr->lines[i] = malloc(sizeof(char) * 100000);
            strcpy(bookPtr->lines[i], buffer);
            bookPtr->lineCount++;
            i++;


        }

        free(buffer);
        fclose(filePtr);

        return success;
            
    }

    int edit_book(Book* bookPtr, char* word){
        
        int linesRemoved = 0;
   
        if(word == NULL){
            return linesRemoved;
        }
            
        if(bookPtr == NULL){
            return linesRemoved;
        }

        for(int i = 0; i < bookPtr->lineCount; i++){

            if(strstr(bookPtr->lines[i], word) != NULL){
                
                free(bookPtr->lines[i]);
                for(int j = i; j < bookPtr->lineCount - 1; j++){

                    bookPtr->lines[j] = bookPtr->lines[j+1];
                }

                bookPtr->lineCount--;
                i--;
                linesRemoved++;

            }

        }

        return linesRemoved;

    }

    void read_book(Book* bookPtr){
    
    for (int i = 0; i < bookPtr->lineCount; i++) {
         printf("%s", bookPtr->lines[i]);
        }

    }

