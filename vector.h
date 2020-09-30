//
// Created by root on 2020/8/31.
//
#pragma once


#ifndef DATA_STRUCTURE_VECTOR_H
#define DATA_STRUCTURE_VECTOR_H

#endif //DATA_STRUCTURE_VECTOR_H

#define MIN_VECTOR_SIZE 128
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct c_vector
{
    void* value;
    size_t curr_size,totol_size,cap_space;
}c_vector;
/*
 * size is a[10]  10 is size cap
 * curr_len is  a[10] real cap
 * tot_len is space cap
 *
 * */
void Del_vector(c_vector* cv);
c_vector* Init_vector(const size_t _size);
int Insert_vector_back(c_vector* cv,const void* value);
c_vector * Expend_vector(c_vector* cv);
int Vector_push_back(c_vector* cv,const void* value);
void* Vetor_get(c_vector* cv,size_t size);






