#include largest

// Remove the largest and return the number of items
// We removed it.
int remove_largest(node* & head, int & largest){
   if(!head)
        return 0;
    if (head->data > largest)
        largest = head->data;
    int count = remove_largest(head->next, largest);
    if (head->data == largest)
    {
        node * hold = head->next;
        delete head;
        head = hold;
        ++count;
    }
    return count;
}