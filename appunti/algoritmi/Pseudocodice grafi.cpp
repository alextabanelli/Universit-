//Grafi

tree BFS (graph G=(V,E), vertex s){
    for (each v in V){
        v.mark=false;
    }
    tree T = s;
    Q = new Queue;
    Q.enqueue(s);
    s.mark = true;
    s.dist = 0;
    while (Q.size != 0){
        u = Q.dequeue();
        visit(u);
        for (each v adiancente a u){
            if (!v.mark) {
                v.mark = true;
                T = T union v;
                Q.enqueue(v);
                v.parent = u;
                v.dist = u.dist+1;
            }
        }
    }
    return T;
}