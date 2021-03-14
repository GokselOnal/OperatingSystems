/*
    This is a What to eat program. This program makes a decision for 
    choosing which food to order by taking a vote in a group of people

    Copyright (C) 2021  Göksel can ÖNAL

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.


    GitHub link:  https://github.com/GokselOnal/OperatingSystems
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define numberOfFoods 5

int main(){

    int numberOfPeople = 0;
    printf("Please enter the number of people: ");
    scanf("%d", &numberOfPeople);

    int threshold = 3 * numberOfPeople;

    char *menu[15] = {"Kebab","Lahmacun","Burger","Pasta","Salad"};
   
    int foodPoints[5];
    foodPoints[0] = 0; //Kebab
    foodPoints[1] = 0; //Lahmacun
    foodPoints[2] = 0; //Burger
    foodPoints[3] = 0; //Pasta
    foodPoints[4] = 0; //Salad

    int prefFoodsIndx[numberOfFoods] = {0,0,0,0,0};
    for(int i = 0; i < numberOfPeople; i++){    
        printf("\n*Person %d,",i + 1);
        printf(" Make your preferences to foods\nWrite name of foods according to your preference\n\n");
        printf("Foods: %s, %s, %s, %s, %s\n",menu[0],menu[1],menu[2],menu[3],menu[4]);
        printf("Threshold: %d\n\n",threshold);
        for(int j = 0; j < numberOfFoods; j++){
            printf("%d: ",j+1);
            char foodName[15];
            scanf("%s",foodName);
            int indx2 = 0;
            int indx1 = 0;
            for(int q = 0; q < numberOfFoods; q++){
                const char *menuFoodName = menu[q];
                if(strcmp(menuFoodName,foodName) == 0){
                    indx2++;
                    indx1 = q;
                }
            }
            if(indx2 == 0){// not found
                printf("Invalid entry!\nTry again\nYou are only allowed to write ('%s', '%s', '%s', '%s', '%s')\n",menu[0],menu[1],menu[2],menu[3],menu[4]);
                j--;
            }
            else{
                if(prefFoodsIndx[indx1] == 0){
                    for(int k = 0; k < numberOfFoods; k++){
                        const char *menuFoodName = menu[k];
                        if(strcmp(menuFoodName,foodName) == 0){
                            //indx = k;
                            foodPoints[k] += (numberOfFoods - j);
                            prefFoodsIndx[k] = 1;
                        }
                    }
                }
                else{
                    printf("You are not allowed to write a food more than one times!\n");
                    j--;
                }
            }
        }
        for(int p = 0; p < numberOfFoods;p++){
            prefFoodsIndx[p] = 0;
        }
        printf("\nThanks..\n\n");
    } 
    
    int count = 0;
    for(int i = 0; i < numberOfFoods; i++){
        if(foodPoints[i] > threshold){
            count++;    
        }
    }
   
    if(numberOfPeople > 0 && count == 0){
        printf("You are eating at home/dorm today!\n");
    }
    //If there is only one food which pass the threshold, then the food will be ordered directly
    else if(count == 1){
        printf("Food passing the treshold(%d): ",threshold);
        for(int i = 0; i < numberOfFoods; i++){
            if(foodPoints[i] > threshold){
                printf("%s,point %d \n\n",menu[i],foodPoints[i]);
                printf("%s will be ordered!\n",menu[i]);
            }
        }
    }
    else if(count > 1){
        printf("\n");
        printf("Foods passing the threshold(%d): ",threshold);
        for(int i = 0; i < numberOfFoods; i++){
            if(foodPoints[i] > threshold){
                printf("%s,point %d  ",menu[i],foodPoints[i]);
            }
        }
        printf("\n\n~~Second Round~~\n\n");

      
        char *shortlist[count];
        int k = 0;
        for(int i = 0; i < numberOfFoods; i++){
            if(foodPoints[i] > threshold){
                shortlist[k] = menu[i];
                k++;
            }
        }

        int shortlistPoints[count];
        for(int i = 0; i < count; i++){
            shortlistPoints[i] = 0;
        }

      
        printf("\n");
        int prefShortlistIndx[count];
        for(int i = 0; i < count; i++){
            prefShortlistIndx[i] = 0;
        }

        for(int i = 0 ; i < numberOfPeople; i++){
            printf("*Person %d,",i + 1);
            printf(" Make your preferences to foods\nWrite name of foods according to your preference\n\n");
            printf("Options: ");
            printf("%s",shortlist[0]);
            for(int i = 1 ; i < count; i++){
                printf(", %s ", shortlist[i]);
            }
            printf("\n\n");
            for(int j = 0; j < count; j++){
                printf("%d: ",j+1);
                char foodName[15];
                scanf("%s",foodName);
                int indx2 = 0;
                int indx1 = 0;
                for(int q = 0; q < count; q++){
                    const char *shortlistFoodName = shortlist[q];
                    if(strcmp(shortlistFoodName,foodName) == 0){
                        indx2++;
                        indx1 = q;
                    }
                }

                if(indx2 == 0){
                    printf("Invalid entry!\nTry again\nYou can only allowed to write (");
                    printf("'%s'",shortlist[0]);
                    for(int i = 1; i < count; i++){
                        printf(", '%s'", shortlist[i]);
                    }
                    printf(")\n");
                    j--;
                }
                else{
                    if(prefShortlistIndx[indx1] == 0){
                        for(int k = 0; k < count; k++){
                            const char *shortlistFoodName = shortlist[k];
                            if(strcmp(shortlistFoodName,foodName) == 0){
                                shortlistPoints[k] += (count - j);
                                prefShortlistIndx[k] = 1;
                            }
                        }
                    }
                    else{
                        printf("You are not allowed to write a food more than one times!\n");
                        j--;
                    }
                }
            }
            for(int p = 0; p < count; p++){
                prefShortlistIndx[p] = 0;
            }
            printf("\nThanks..\n\n");
        }
    
        int maxShortlistPoint = shortlistPoints[0];
        int indx = 0;
        for(int i = 0; i < count; i++){
            printf("%s,point %d  ",shortlist[i],shortlistPoints[i]);
            if(shortlistPoints[i] > maxShortlistPoint){
                maxShortlistPoint = shortlistPoints[i];
            }
        }

        printf("\n\n");
        //At the end, if there is more than one food with max point, all the max pointed foods will be ordered
        for(int i = 0; i < count; i++){
            if(shortlistPoints[i] == maxShortlistPoint){
                printf("%s will be ordered!\n",shortlist[i]);
            }
        }
    }
    return 0;
}       
