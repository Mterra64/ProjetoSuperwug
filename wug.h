#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "data.h"
#include "util.h"


void  print_wug(wug_t *w);
void  print_population(wug_t** population, const int size);


void genome2features(const int genome[16], int features[4]);



int  report_population(wug_t** population, const int size);


int  rank(const wug_t* w);


bool insert_ranked(wug_t** population, wug_t* w, int* size, int capacity);







