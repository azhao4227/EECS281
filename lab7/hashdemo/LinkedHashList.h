// EECS 281, Dr. David Paoletti

// A template class for a singly linked list, specifically tailored
// to work with a hash table.  It can store keys of any type,
// along with a value of another (possibly the same) type.

#ifndef LINKEDHASHLIST_H
#define LINKEDHASHLIST_H


template <class KEYTYPE, class VALUETYPE>
class LinkedHashList {
private:
    struct ListNode {
        KEYTYPE key;
        VALUETYPE value;
        ListNode *next;

        ListNode(const KEYTYPE &key, const VALUETYPE &value, ListNode *next = nullptr) :
            key{ key }, value{ value }, next{ next }
        {
        } // constructor

        // Implicit destruction
        ~ListNode() {
            delete next;
        } // destructor
    }; // struct ListNode

    ListNode *head;

public:
    LinkedHashList() : head{ nullptr } {
    } // constructor


    // Look at how the destruction proceeds...
    ~LinkedHashList() {
        delete head;
    } // destructor

    // To make this complete, we SHOULD add a copy constructor
    // and operator=().

    // Add a node to the linked list.  If the key is not in the list,
    // it is added at the head.  If the key is already in the list,
    // the value is updated.
    void add(const KEYTYPE &key, const VALUETYPE &value) {
        ListNode *ptr = head;

        while (ptr) {
            if (ptr->key == key) {
                // Do not insert a duplicate; update value
                ptr->value = value;
                return;
            }
            ptr = ptr->next;
        } // while

        // Not in list, add at head
        head = new ListNode(key, value, head);
    } // add()


    // Remove the given key from the list, along with its corresponding value
    void remove(const KEYTYPE &key) {
        ListNode *nodePtr, *previousNodePtr = nullptr;

        // If the list is empty, do nothing.
        if (!head)
            return;

        // Determine if the first node is the one to delete.
        if (head->key == key) {
            nodePtr = head;
            head = head->next;
            nodePtr->next = nullptr;
            delete nodePtr;
        } // if
        else {
            // Initialize nodePtr to head of list.
            nodePtr = head;

            // Skip all nodes which are not equal to num.
            while (nodePtr != nullptr && nodePtr->key != key) {
                previousNodePtr = nodePtr;
                nodePtr = nodePtr->next;
            } // while

            // If nodePtr points to a node, link the previous
            // node to the node after nodePtr, then delete
            // nodePtr.
            if (nodePtr) {
                previousNodePtr->next = nodePtr->next;
                nodePtr->next = nullptr;
                delete nodePtr;
            } // if
        } // else
    } // remove()


    // If the key is not present, it is added,
    // since a reference to the value must be returned
    VALUETYPE &get(const KEYTYPE &key) {
        ListNode *ptr = head;

        while (ptr) {
            if (ptr->key == key)
                return ptr->value;

            ptr = ptr->next;
        } // while

        // Never found; add with default value
        head = new ListNode(key, VALUETYPE(), head);

        // Always added at the head of the list
        return head->value;
    } // get()


    // Clear out the linked list via implicit destruction.
    void clear() {
        delete head;
        head = nullptr;
    } // clear()

}; // LinkedHashList


#endif // LINKEDHASHLIST_H
