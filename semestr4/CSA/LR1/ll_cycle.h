#pragma once

typedef struct node {
    int value;
    struct node *next;
} node;

bool ll_has_cycle(node *);