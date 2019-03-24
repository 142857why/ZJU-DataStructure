List Merge(List L1, List L2) {
    List L = ( List )malloc( sizeof( struct Node ) );
    List t = L, l1 = L1->Next, l2 = L2->Next;
    while(l1 && l2) {
        if(l1->Data <= l2->Data)
        {
            t->Next = l1;
            l1 = l1->Next;
        } else {
            t->Next = l2;
            l2 = l2->Next;
        }
        t = t->Next;
    }
    if(l1)
        t->Next = l1;
    if(l2)
        t->Next = l2;
    L1->Next = NULL;
    L2->Next = NULL;
    return L;
}
