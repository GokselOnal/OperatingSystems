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


    GitHUb link:  https://github.com/GokselOnal/OperatingSystems
*/


#include <stdio.h>
#include <stdlib.h>

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

    int givenPoints[numberOfFoods] = {0,0,0,0,0};
    printf("\nFoods: %s, %s, %s, %s, %s\n",menu[0],menu[1],menu[2],menu[3],menu[4]);
    printf("Threshold: %d\n\n",threshold);
    for(int i = 0; i < numberOfPeople; i++){
        printf("*Person %d,",i + 1);
        printf(" Give your points(1 - 5) to foods\n");
        for(int j = 0; j < numberOfFoods; j++){
            printf("%s: ",menu[j]);
            int point = 0;
            scanf("%d:",&point);
            if(point > 5 || point < 1){
                printf("Invalid point!!\nYou can only use points(1 - 5)\nTry again\n");
                j--;
            }
            else{
                if(givenPoints[point -1] == 0){
                    foodPoints[j] += point;
                    givenPoints[point - 1] = 1;
                }else{
                    printf("You can not give a point more than once..\nTry again\n");
                    j--;
                }
            }
        }
        for(int i = 0; i < numberOfFoods;i++){
            givenPoints[i] = 0;
        }
        printf("Thanks..\n\n");
    } 


    int count = 0;
    for(int i = 0; i < numberOfFoods; i++){
        if(foodPoints[i] > threshold){
            count++;    
        }
    }
   
    if(count == 0){
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
    else{
        printf("\n\n");
        printf("Foods passing the treshold(%d): ",threshold);
        for(int i = 0; i < numberOfFoods; i++){
            if(foodPoints[i] > threshold){
                printf("%s,point %d  ",menu[i],foodPoints[i]);
            }
        }
        printf("\n\nSecond Round\n\n");

      
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

        printf("Options: ");
        for(int i = 0 ; i < count; i++){
            printf("%s  ", shortlist[i]);
        }

        printf("\n");
        int givenPointsShortlist[count];
        for(int i = 0; i < count; i++){
            givenPointsShortlist[i] = 0;
        }

        for(int i = 0 ; i < numberOfPeople; i++){
            printf("*Person %d,",i + 1);
            printf(" Give your points(1 - %d) to foods\n",count);
            for(int j = 0; j < count; j++){
                printf("%s: ",shortlist[j]);
                int point = 0;
                scanf("%d:",&point);
                if(point > count || point < 1){
                    printf("Invalid point!!\nYou can only use points(1 - %d)\nTry again\n",count);
                    j--;
                }
                else{
                    if(givenPointsShortlist[point -1] == 0){
                        shortlistPoints[j] += point;
                        givenPointsShortlist[point - 1] = 1;
                    }else{
                        printf("You can not give a point more than once..\nTry again\n");
                        j--;
                    } 
                }       
            }
            for(int i = 0; i < count; i++){
                givenPointsShortlist[i] = 0;
            }
            printf("Thanks..\n\n");
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
