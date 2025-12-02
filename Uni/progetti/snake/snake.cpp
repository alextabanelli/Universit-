//
// Created by Matth on 27/03/2025.
//
#include "snake.h"

snake::snake(bool *v) {
    s=new body;
    s->cell=v;
    s->next=NULL;
}

void snake::push_back(bool *v) {
    psnake p=s;
    *v=true;

    if (s==NULL)
        s=new body;

    while (p->next != NULL) {
        p=p->next;
    }

    p->next=new body;
    p=p->next;
    p->cell=v;
    p->next=NULL;
}

void snake::pop_front() {
    if(s==NULL) return;
    psnake p=s;
    *(s->cell)=false;

    if (s->next!=NULL)
        s=s->next;

    delete p;
}

bool snake::is_snake(bool *v) {
    psnake p=s;

    while (p!=NULL) {
        if (v==p->cell) {
            return true;
        }
        p=p->next;
    }

    return false;
}

bool snake::is_head(bool *v) {
    psnake p=s;

    while (p->next!=NULL) {
        p=p->next;
    }

    if (v==p->cell)
        return true;
    else
        return false;
}

int snake::get_facing() {
    return facing;
}

void snake::change_facing(int f) {
    facing=f;
}