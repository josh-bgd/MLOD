//
//  prixTuring-file.c
//  OpenCProject
//
//  Created by Josua  on 14/10/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>



int main(void){
    char fileName[] = "turingWinners.txt";
    FILE* f;
    
    f = fopen(fileName, "r");
    
    if ((f = fopen(fileName, "r"))==NULL) {
        printf("Code de l'erreur : %d\n", errno);
        return EXIT_FAILURE;
        
    }
    
    char buffer[10];
    while (fgets(buffer, 10, f) !=NULL){
        printf("%s", buffer);
    }
    
    fclose(f);
    return EXIT_SUCCESS;
}


