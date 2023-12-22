#include "videoLinkedList.h"
#ifdef videoLinkedList_H

videoLinkedList::videoLinkedList() : first(0), mySize(0) {}

videoLinkedList::videoLinkedList(const videoLinkedList& origList) : first(0), last(0), mySize(origList.mySize) {
    if (origList.mySize == 0) {
        first = last = 0;
        return;
    }
    videoLinkedList::NodePointer origPtr, lastPtr;
    first = new Node(origList.first->data);
    lastPtr = first;
    origPtr = origList.first->next;
    while (origPtr != origList.first)
    {
        lastPtr->next = new Node(origPtr->data);
        lastPtr->next->prev = lastPtr;
        origPtr = origPtr->next;
        lastPtr = lastPtr->next;
    }
    lastPtr->next = first;
    first->prev = lastPtr;
    last = lastPtr;
}

inline videoLinkedList::~videoLinkedList() {
    videoLinkedList::NodePointer prev = first, ptr;
    while (prev != 0)
    {
        ptr = prev->next;
        delete prev;
        prev = ptr;
    }
}

bool videoLinkedList::empty() {
    return mySize == 0;
}

const videoLinkedList& videoLinkedList::operator=(const videoLinkedList& rightSide) {
    if (rightSide.mySize == 0) {
        first = last = 0;
        return *this;
    }
    if (this != &rightSide) {
        this->~videoLinkedList();
        mySize = rightSide.mySize;
        videoLinkedList::NodePointer origPtr = rightSide.first;
        videoLinkedList::NodePointer lastPtr = 0;
        videoLinkedList::NodePointer newNode = new Node(origPtr->data);
        first = newNode;
        lastPtr = newNode;
        origPtr = origPtr->next;
        while (origPtr != rightSide.first) {
            newNode = new Node(origPtr->data);
            lastPtr->next = newNode;
            newNode->prev = lastPtr;
            lastPtr = newNode;
            origPtr = origPtr->next;
        }
        last = lastPtr;
        last->next = first;
        first->prev = last;
    }
    return *this;
}


void videoLinkedList::insert(ElementType& dataVal, int index) {
    if (index < 0 || index > mySize)
    {
        cerr << "Illegal location to insert -- " << index << endl;
        return;
    }
    mySize++;
    videoLinkedList::NodePointer newPtr = new Node(dataVal);
    if (first == NULL) {

        newPtr->next = newPtr;
        newPtr->prev = newPtr;
        first = newPtr;
        last = newPtr;
    }
    if (first == last) {
        newPtr->next = first;
        newPtr->prev = first;
        first->next = newPtr;
        first->prev = newPtr;
        last = newPtr;
    }
    if (index == 0)
    {
        newPtr->next = first;
        first = newPtr;
        last->next = first;
        first->prev = last;
    }
    else {
        videoLinkedList::NodePointer predPtr = first;
        videoLinkedList::NodePointer nextPtr = NULL;
        for (int i = 1; i < index; i++)
            predPtr = predPtr->next;
        nextPtr = predPtr->next;
        if (predPtr == last) {
            newPtr->next = first;
            newPtr->prev = last;
            first->prev = newPtr;
            last->next = newPtr;
            last = newPtr;
        }
        else {
            newPtr->next = nextPtr;
            newPtr->prev = predPtr;
            predPtr->next = newPtr;
            nextPtr->prev = newPtr;
        }
    }
}

void videoLinkedList::push(ElementType& dataVal) {
    mySize++;
    videoLinkedList::NodePointer newPtr = new Node(dataVal);

    if (!first) {
        newPtr->next = newPtr;
        newPtr->prev = newPtr;
        first = newPtr;
        last = newPtr;
    }
    else {
        newPtr->next = first;
        newPtr->prev = last;
        first->prev = newPtr;
        last->next = newPtr;
        last = newPtr;
    }
}

void videoLinkedList::erase(int index) {
    if (index < 0 || index >= mySize) {
        cerr << "Illegal location to delete -- " << index << endl;
        return;
    }
    if (empty()) {
        cerr << "Cannot delete from an empty list." << endl;
        return;
    }

    NodePointer ptr = first;
    if (index == 0) { 
        first = first->next;
        if (mySize == 1) {
            last = nullptr;
        }
        else {
            last->next = first;
            first->prev = last;
        }
    }
    else {
        for (int i = 0; i < index; i++) {
            ptr = ptr->next;
        }
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        if (index == mySize - 1) { 
            last = ptr->prev;
        }
    }

    delete ptr;
    mySize--;

    if (mySize == 0) {
        first = last = nullptr;
    }
}


void videoLinkedList::pop() {
    if (empty()) {
        cerr << "Cannot delete from an empty list." << endl;
        return;
    }

    mySize--;
    if (mySize == 1) {
        delete first;
        first = nullptr;
        last = first;
    }
    else {
        videoLinkedList::NodePointer predPtr = first,
            ptr = first->next;
        while (predPtr->next != last) {
            predPtr = predPtr->next;
            ptr = ptr->next;
        }
        last = predPtr;
        delete ptr;
        predPtr->next = first;
        first->prev = last;
    }
}

int videoLinkedList::searchByName(const string& name) {
    int loc;
    videoLinkedList::NodePointer tempP = first;
    for (loc = 0; loc < mySize; loc++)
        if (tempP->data.getFileName() == name)
            return loc;
        else
            tempP = tempP->next;
    return -1;
}

string videoLinkedList::searchByIndex(int index) {
    if (index < 0 || index >= mySize) {
        cout << "Error Out of bounds\n";
    }

    NodePointer tempP = first;
    for (int loc = 0; loc < index; ++loc) {
        tempP = tempP->next;
    }

    return tempP->data.getFilePath();
}

int videoLinkedList::searchByPath(const string& path) {
    int loc;
    videoLinkedList::NodePointer tempP = first;
    for (loc = 0; loc < mySize; loc++)
        if (tempP->data.getFilePath() == path)
            return loc;
        else
            tempP = tempP->next;
    return -1;
}

void videoLinkedList::display(ostream& out) const {
    videoLinkedList::NodePointer ptr = first;
    while (ptr != last)
    {
        out << ptr->data.getFileName() << "  ";
        ptr = ptr->next;
    }
    out << last->data.getFileName() << " ";
}


int videoLinkedList::nodeCount() {
    if (first == nullptr)
        return 0;

    int count = 1;
    videoLinkedList::NodePointer ptr = first->next;

    while (ptr != first) {
        count++;
        ptr = ptr->next;
    }

    return count;
}

void videoLinkedList::swap(const string& name1, const string& name2) {
    int indexFirst = searchByName(name1);
    int indexSecond = searchByName(name2);

    if (indexFirst == -1 || indexSecond == -1) {
        cout << "One or both elements not found in the list. Cannot swap." << endl;
        return;
    }

    NodePointer nodeFirst = first;
    NodePointer nodeSecond = first;

    for (int i = 0; i < indexFirst; ++i) {
        nodeFirst = nodeFirst->next;
    }

    for (int i = 0; i < indexSecond; ++i) {
        nodeSecond = nodeSecond->next;
    }

    ElementType temp = nodeFirst->data;
    nodeFirst->data = nodeSecond->data;
    nodeSecond->data = temp;
}

ostream& operator<<(ostream& out, const videoLinkedList& aList) {
    aList.display(out);
    return out;
}

#endif