/**Göksel can Önal, S011827 
 * This is the kitchen simulation code for OzuRest.
 * French chef and 3 students from gastronomy department are preparing delicious meals in here
**/
#include "meal.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GLOVE_COUNT 3
#define POT_SIZE 3
#define APPRENTICE_COUNT 3
#define MEALS_TO_PREPARE 4
#define REQUIRED_INGREDIENTS 3

struct meal Menu[4] = {
    {"Menemen", {{"Tomato", 3}, {"Onion", 4}, {"Egg", 1}}, 10},
    {"Chicken Pasta", {{"Pasta", 2}, {"Chicken", 5}, {"Curry", 2}}, 8}, 
    {"Beef Steak", {{"Beef", 7}, {"Pepper", 3}, {"Garlic", 2}}, 13}, 
    {"Ali Nazik", {{"Eggplant", 4}, {"Lamb Meat", 4}, {"Yoghurt", 1}}, 10}
}; 

int meal_counter = 0;
int meal_ing_counter = 0;
int pot_counter = 0;

pthread_mutex_t glove_mutex[GLOVE_COUNT];
pthread_mutex_t ingredient_mutex;
pthread_mutex_t pot_mutex;


void put_gloves(int apprentice_id) {
    printf("Apprentice %d is picking gloves \n", apprentice_id);
    if(apprentice_id == 0){
        pthread_mutex_lock(&glove_mutex[0]);
        pthread_mutex_lock(&glove_mutex[1]);
    }
    else if(apprentice_id = 1){
        pthread_mutex_lock(&glove_mutex[1]);
        pthread_mutex_lock(&glove_mutex[2]); 
    }
    else{
        pthread_mutex_lock(&glove_mutex[2]);
        pthread_mutex_lock(&glove_mutex[0]);
    }
    printf("Apprentice %d has picked gloves\n", apprentice_id);
}

void remove_gloves(int apprentice_id) {
    if(apprentice_id == 0){
        pthread_mutex_unlock(&glove_mutex[0]);
        pthread_mutex_unlock(&glove_mutex[1]);
    }
    else if(apprentice_id = 1){
        pthread_mutex_unlock(&glove_mutex[1]);
        pthread_mutex_unlock(&glove_mutex[2]); 
    }
    else{
        pthread_mutex_unlock(&glove_mutex[2]);
        pthread_mutex_unlock(&glove_mutex[0]);
    }
    printf("Apprentice %d has removed gloves\n", apprentice_id);
}

void pick_ingredient(int apprentice_id, int* meal_index, int* ing_index) {
    put_gloves(apprentice_id);
    *meal_index = meal_counter;
    *ing_index = meal_ing_counter;
    printf("Apprentice %d has taken ingredient %s\n", apprentice_id, Menu[*meal_index].ingredients[*ing_index].name);
   
   if(meal_ing_counter < 2){
        pthread_mutex_lock(&ingredient_mutex);
        meal_ing_counter = meal_ing_counter + 1;  
        pthread_mutex_unlock(&ingredient_mutex);
   }
   else{
        pthread_mutex_lock(&ingredient_mutex);
        meal_index = meal_index + 1; 
        pthread_mutex_unlock(&ingredient_mutex);
   }
    remove_gloves(apprentice_id);
} 

void prepare_ingredient(int apprentice_id, int meal_index, int ing_index) {
    printf("Apprentice %d is preparing: %s \n", apprentice_id, Menu[meal_index].ingredients[ing_index].name);
    sleep(Menu[meal_index].ingredients[ing_index].time_to_process);
    printf("Apprentice %d is done preparing %s \n", apprentice_id, Menu[meal_index].ingredients[ing_index].name);
}

void put_ingredient(int id, int meal_index, int ing_index) {
    while(1) {
        if(pot_counter < 3){
            printf("Apprentince %d is trying to put %s into pot\n", id, Menu[meal_index].ingredients[ing_index].name);
            pthread_mutex_lock(&pot_mutex);
            pot_counter = pot_counter + 1;
            printf("Apprentince %d has put %s into pot\n", id, Menu[meal_index].ingredients[ing_index].name);
            pthread_mutex_unlock(&pot_mutex);
            break;
        }
    }
}

void help_chef(int apprentice_id) {
    int meal_index, meal_ingredient_index;
    pick_ingredient(apprentice_id, &meal_index, &meal_ingredient_index);
    prepare_ingredient(apprentice_id, meal_index, meal_ingredient_index);
    put_ingredient(apprentice_id, meal_index, meal_ingredient_index);
}

void *apprentice(int *apprentice_id) {
    printf("Im apprentice %d\n", *apprentice_id);
    while(1) {
        if(meal_counter == MEALS_TO_PREPARE) break;
        help_chef(*apprentice_id);
    }
    pthread_exit(NULL);
}

void *chef() {
    
    while(1) {
        if(pot_counter == 3){
            printf("Chef is preparing meal %s\n", Menu[meal_counter].name);
            sleep(Menu[meal_counter].time_to_prepare);
            printf("Chef prepared the meal %s\n",  Menu[meal_counter].name); 

            pthread_mutex_lock(&ingredient_mutex);
            meal_ing_counter = 0;
            meal_counter = meal_counter + 1;
            pot_counter = 0; 
            pthread_mutex_unlock(&ingredient_mutex);

            sleep(3); 
        if(meal_counter == MEALS_TO_PREPARE)
            break;
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t apprentice_threads[APPRENTICE_COUNT];
    pthread_t chef_thread;

    int apprentice_ids[APPRENTICE_COUNT] = {0 ,1 ,2};
    
    for(int i = 0; i < GLOVE_COUNT; i++){
        pthread_mutex_init(&glove_mutex[i],NULL);
    }
    for(int i = 0; i < APPRENTICE_COUNT; i++){
        pthread_create(&apprentice_threads[i],NULL,apprentice,&apprentice_ids[i]);
    }
    pthread_create(&chef_thread,NULL,chef,NULL);

    for (size_t i = 0; i < APPRENTICE_COUNT; i++){
        pthread_join(apprentice_threads[i],NULL);
    }
    pthread_join(chef_thread, NULL);

    return 0;
}
