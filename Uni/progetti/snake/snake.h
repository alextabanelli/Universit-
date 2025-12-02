//
// Created by Matth on 27/03/2025.
//
#include<iostream>

using namespace std;

#ifndef SNAKE_H
#define SNAKE_H

struct body{
    bool *cell=NULL;
    body *next=NULL;
};
typedef body *psnake;

class snake {
private:
    //attributi
    psnake s=NULL;
    int facing=1;

    //metodi
public:
    snake(bool *v);
    void push_back(bool *v);
    void pop_front();
    bool is_snake(bool *v);
    bool is_head(bool *v);
    int get_facing();
    void change_facing(int f);
};

#endif //SNAKE_H
