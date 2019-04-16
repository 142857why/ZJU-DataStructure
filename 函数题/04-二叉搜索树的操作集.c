BinTree Find(BinTree BST, ElementType X) {
    while(BST) {
        if(BST->Data == X)
            break;
        else if(X < BST->Data)
            BST = BST->Left;
        else
            BST = BST->Right;
    }
    return BST;
}

BinTree FindMin(BinTree BST) {
    while(BST && BST->Left)
        BST = BST->Left;
    return BST;
}

BinTree FindMax(BinTree BST) {
    while(BST && BST->Right)
        BST = BST->Right;
    return BST;
}

BinTree Insert(BinTree BST, ElementType X) {
    if(!BST) {
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    } else {
        if(BST->Data > X)
            BST->Left = Insert(BST->Left, X);
        else
            BST->Right = Insert(BST->Right, X);
    }
    return BST;
}

BinTree Delete(BinTree BST, ElementType X) {
    Position Tmp;
    if(!BST)
        printf("Not Found\n");
    else if(X < BST->Data)
        BST->Left = Delete(BST->Left, X);
    else if(X > BST->Data)
        BST->Right = Delete(BST->Right, X);
    else if(BST->Left && BST->Right) {
        Tmp = FindMin(BST->Right);
        BST->Data = Tmp->Data;
        BST->Right = Delete(BST->Right, BST->Data);
    } else {
        Tmp = BST;
        BST = (BST->Left)?BST->Left:BST->Right;
        free(Tmp);
    }
    return BST;
}

