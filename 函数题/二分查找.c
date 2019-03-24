Position BinarySearch( List L, ElementType X) {
    if (L->Last == 0) return NotFound;
    int left = 1, right = L->Last, mid;
    do {
        mid = (left + right) / 2;
        if(L->Data[mid] == X)
            return mid;
        else if(L->Data[mid] < X)
            left = mid + 1;
        else
            right = mid - 1;
    } while(left <= right);
    return NotFound;
}

