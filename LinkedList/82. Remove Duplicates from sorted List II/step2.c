//以前書いたコードを手直ししようとしたらコンパイルエラーが出て、かつロジックにも問題があったので、新しくつくる

struct ListNode* deleteDuplicates(struct ListNode* head)
{
    struct ListNode* sentinelPtr;
    sentinelPtr->next = head;
    struct ListNode* currentNodePtr = sentinelPtr->next;
    struct ListNode* lastUniqueNodePtr = sentinelPtr;
    
    if(currentNodePtr == NULL)
    {
        return NULL;
    }

    if(currentNodePtr->next == NULL)
    {
        return head;
    }

    while(currentNodePtr->next != NULL)
    {
        if(currentNodePtr->val != currentNodePtr->next->val)
        {
            lastUniqueNodePtr->next = currentNodePtr;
            lastUniqueNodePtr = lastUniqueNodePtr->next;
            currentNodePtr = currentNodePtr->next;
            continue;
        }

        lastUniqueNodePtr->next = NULL;

        int duplicateValue = currentNodePtr->val;

        while(currentNodePtr != NULL && currentNodePtr->val == duplicateValue)
        {
            currentNodePtr = currentNodePtr->next;
        }
    }

    return sentinelPtr->next;
}
