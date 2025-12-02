//Visita alberi


struct node {
    int elem;
    node* left;
    node* right;
}

//DFS

//Pre-ordine
void preordine (node T){
    if (T != NULL){
        visit(T);
        preordine(T.left);
        preordine(T.right);
    }
}

//Post-ordine
void postordine (node T){
    if (T != NULL){
        postordine(T.left);
        postordine(T.right);
        visit(T);
    }
}

//In-ordine
void inordine (node T){
    if (T != NULL){
        inordine(T.left);
        visit(T);
        inordine(T.right);
    }
}


//BFS

//Visita in ampiezza

void BFS (tree T){
    Queue Q;
    if (T.root != NULL) enqueue(Q,T.root);
    while (Q.size != 0){
        x = dequeue(Q);
        visit(x);
        if (x.left != NULL) enqueue(Q, x.left);
        if (x.right != NULL) enqueue(Q, x.right);
    }
}


//Ricerca BST

nodo search (BST T, key k){
    tmp = T.root;
    while (T.root != NULL){
        if (k == tmp.key) return tmp;
        else if (k < tmp.key) tmp = tmp.left;
        else tmp = tmp.right;
    }
    return NULL;
}

nodo BSTinsert (BST T, key k, data D){
    nodo = node(k,D);
    prev = NULL;
    curr = T.root;
    while (curr != NULL){
        prev = curr;
        if (k < curr.key) curr = curr.left;
        else curr = curr.right;
    }
    if (prev == NULL) T.root = nodo;
    else nodo.parent = prev;
    if (k < prev.key) prev.left = nodo;
    else prev.right = nodo;
    return nodo;
}


void disconnect(BST T, node v){
    p = v.parent;
    if (v.right == NULL) c = v.left;
    else c = v.right;
    if (p == NULL) T.root = c;
    else if (p.left == v) p.left = c;
    else p.right = c;
    if (c != NULL) c.parent = p; 
}


nodo BSTdelete (BST T, key k){
    v = search(T,k);
    if (v != NULL) {
        if (v.left != NULL and v.right != NULL){
            u = predecessor(v);
            swap(v,u);
            v = u;
        }
        disconnect(T,v);
    }
    return v;
}


//Alberi AVL

void rightrotate (ALV T, node u){
    if (u != NULL and u.left != NULL){
        v = u.left;
        u.left = v.right;
        v.right = u;
        if (u.left != NULL) u.left.parent = u;
        v.parent = u.parent;
        if (u.parent == NULL) T.root = v;
        else if (u.parent.left == u) v.parent.left = v;
        else v.parent.right = v;
        u.parent = v;
    }
    updateheight(u);
    updateheight(v);
}

void leftrotate (ALV T, node v){
    if (v != NULL and v.right != NULL){
        u = v.right;
        v.right = u.left;
        u.left = v;
        if (v.right != NULL) v.right.parent = v;
        u.parent = v.parent;
        if (v.parent == NULL) T.root = u;
        else if (v.parent.left == v) u.parent.left = u;
        else u.parent.right = u;
        v.parent = u;
    }
    updateheight(u);
    updateheight(v);
}

//Bilancia l'albero

void balance (ALV T, node u){
    b = balancefactor(u);
    if (b == 2){
        if (balancefactor(u.left) == -1) leftrotate(T,u.left);
        rightrotate(T,u);
    }
    else if (b == -2){
        if (balancefactor(u.right) == -1) rightrotate(T,u.right);
        leftrotate(T,u);
    }
}

//AVL insert

nodo AVLinsert(AVL T, key k, data d){
    v = BSTinsert(T,k,d);
    p = v.parent;
    while (p != NULL and |balancefactor(p)| != 2){
        updateheight(p);
        p = p.parent;
    }
    if (p != NULL) balance(T,p);
    return v;
}


//AVL delete

nodo AVLdelete(AVL T, key k, data d){
    v = BSTdelete(T,k);
    if (v != NULL) {
        p = v.parent;
        while (p != NULL){
            if (|balancefactor(p)| == 2) balance(T,p);
            else updateheight(p);
            p = p.parent;
        }
    }
    return v;
}