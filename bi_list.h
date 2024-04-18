//
// Created by aleks on 29.11.2023.
//

#ifndef RING_BI_LIST_H
#define RING_BI_LIST_H

#include <ctime>
#include <stdexcept>

template <typename Key, typename Info>
class bi_list{
private:
    struct node{
        Key key;
        Info info;
        node* previous;
        node* next;
        node(const Key &newKey, const Info &newInfo, node* prev, node* nxt) : key(newKey), info(newInfo), previous(prev), next(nxt){};
        node() : previous(this), next(this){};
        ~node(){
            next= nullptr;
            previous= nullptr;
        }
    }; // Struct node consisting of Key, Info, and pointer to previous and next node
    node* sentinel; //I am using sentinel node to make other methods easier to implement
    int size; //Size of the list
public:
    //used for iterating over the list and its const variant
    class iterator {
    private:
        const bi_list *owner; //used for checkin if two or more iterators belong to the same list
        node* current;

    public:
        //constructors
        iterator(node* node, bi_list* own) : current(node), owner(own) {};
        iterator(const iterator& other) : current(other.current), owner(other.owner){};

        //assignment operator
        iterator& operator=(const iterator& other){
            if(*this==other) return *this;
            this->owner=other.owner;
            this->current=other.current;
            return *this;
        }

        //equality operators
        bool operator==(const iterator& other) const {
            return this->owner == other.owner && this->current == other.current;
        }
        bool operator!=(const iterator& other) const {
            return !(*this== other);
        }

        //Increment operators
        iterator& operator++() {
            current = current->next;
            return *this;
        }
        iterator  operator++(int) {
            const iterator temp = *this;
            current = current->next;
            return temp;
        }
        iterator operator+(int count){
            for (int i = 0; i < count; ++i) {
                if(current==owner->sentinel) break;
                current=current->next;
            }
            return *this;
        }

        // Decrement operators
        iterator& operator--() {
            current = current->previous;
            return *this;
        }
        iterator  operator--(int){
            iterator temp = *this;
            current = current->previous;
            return temp;
        }
        iterator operator-(int count){
            for (int i = 0; i < count; ++i) {
                if(current==owner->sentinel) break;
                current=current->previous;
            }
            return *this;
        }

        //Dereference operator
        std::pair<Key, Info> operator*() {
            return std::make_pair(this->current->key,this->current->info);
        }

        //getters
        [[nodiscard]] const Key &returnKey()const {
            return current->key;
        }
        [[nodiscard]] Info &returnInfo(){
            return current->info;
        }
        [[nodiscard]] const Info &returnInfo() const{
            return current->info;
        }

        //setters
        void addInfo(const Info& inf){
            current->info+=inf;
        }
        void updateInfo(const Info& inf){
            current->info=inf;
        }
        
        friend class bi_list;
    };
    class const_iterator {
    private:
        const bi_list *owner;
        node* current;

    public:
        //constructors
        const_iterator(node* node,const bi_list* own) : current(node), owner(own) {};
        const_iterator(const const_iterator& other) : current(other.current), owner(other.owner){};

        //assignment operator
        const_iterator& operator=(const const_iterator& other){
            if(*this==other) return *this;
            this->owner=other.owner;
            this->current=other.current;
            return *this;
        }

        //equality operators
        bool operator!=(const const_iterator& other)  {
            return current != other.current||owner!=other.owner;
        }
        bool operator==(const const_iterator &other){
            return current==other.current&&owner==other.owner;
        }

        // Dereference operator
        std::pair<Key, Info> operator*() {
            return std::make_pair(this->current->key,this->current->info);
        }

        // Increment operators
        const_iterator& operator++() {
            current = current->next;
            return *this;
        }
        const_iterator  operator++(int) {
            const const_iterator temp = *this;
            current = current->next;
            return temp;
        }
        const_iterator operator+(int count){
            for (int i = 0; i < count; ++i) {
                if(current==owner->sentinel) break;
                current=current->next;
            }
            return *this;
        }

        // Decrement operators
        const_iterator& operator--() {
            current = current->previous;
            return *this;
        }
        const_iterator  operator--(int){
            const const_iterator temp = *this;
            current = current->previous;
            return temp;
        }
        const_iterator operator-(int count){
            for (int i = 0; i < count; ++i) {
                if(current==owner->sentinel) break;
                current=current->previous;
            }
            return *this;
        }

        //getters
        [[nodiscard]] const Key &returnKey()const {
            return current->key;
        }
        [[nodiscard]] const Info &returnInfo() const{
            return current->info;
        }

        friend class bi_list;
    };

    //constructors
    bi_list(){
        sentinel = new node();
       sentinel->next = sentinel;
       sentinel->previous = sentinel;
       size=0;
    }
    bi_list(const bi_list& src) {
        sentinel = new node();
        sentinel->next = sentinel;
        sentinel->previous = sentinel;
        size = 0;
        for (auto it = src.begin(); it != src.end(); ++it) {
            push_back(it.returnKey(), it.returnInfo());
        }
    }
    ~bi_list(){
        clear();
        delete sentinel;
    }

    //equality operators
    bi_list& operator=(const bi_list& src) {
        if (this == &src) return *this;

        clear();

        for (const_iterator it = src.begin(); it != src.end(); it++) {
            push_back(it.returnKey(), it.returnInfo());
        }
        return *this;
    }

    [[nodiscard]] int getSize() const{
        return size;
    };

    //used for traversal over the list
    [[nodiscard]] iterator begin() {
        return iterator(sentinel->next, this);
    }
    [[nodiscard]] const_iterator begin() const {
        return const_iterator(sentinel->next, this);
    }
    [[nodiscard]] iterator end() {
        return iterator(sentinel, this);
    }
    [[nodiscard]] const_iterator end() const {
        return const_iterator(sentinel, this);
    }

    //addition and deletion of elements in front/back of the list
    iterator push_front(const Key& key, const Info& info){
        iterator it = iterator(new node(key, info, sentinel, sentinel->next), this);
        sentinel->next->previous=it.current;
        sentinel->next=it.current;
        size++;
        return it;
    }
    iterator push_back(const Key& key, const Info& info){
        iterator it = iterator(new node(key, info,sentinel->previous, sentinel), this);
        sentinel->previous->next=it.current;
        sentinel->previous=it.current;
        size++;
        return it;
    }
    iterator pop_front(){
        if(sentinel->next==sentinel) return iterator(sentinel, this);
        node* toDel = sentinel->next;
        sentinel->next=sentinel->next->next;
        toDel->next->previous=sentinel;
        delete toDel;
        size--;
        return begin();
    }
    //deletion of a list
    int clear(){
        int counter=0;
        while(sentinel->next!=sentinel) {
            pop_front();
            counter++;
        }
        return counter;
    }

    //search and helper functions
    int numberOfOccurrences(const Key& key){
        int counter=0;
        for ( auto it = begin();it!=end();++it){
            if(it.returnKey()==key) counter++;
        }
        return counter;
    }
    [[nodiscard]] iterator find(int occurrence, const Key& key){
        if(occurrence<1) return iterator(nullptr, this);
        iterator it= begin();
        for(it; it!=end();++it){
            if(it.returnKey()==key) {
                occurrence--;
                if(occurrence==0) return it;
            }
        }
        return iterator(nullptr, this);
    }
    [[nodiscard]] const_iterator find(int occurrence, const Key& key) const{
        if(occurrence<1) return iterator(nullptr, this);
        const_iterator it= begin();
        for(it; it!=end();++it){
            if(it.returnKey()==key) {
                occurrence--;
                if(occurrence==0) return it;
            }
        }
        return iterator(nullptr, this);
    }
    //addition and deletion of elements in a given position
    iterator insert(iterator position, const Key& key, const Info& info){
        if(position.owner!=this) throw std::logic_error("Iterator belongs to a different list instance");
        node* newNode = new node(key, info, position.current->previous, position.current);
        position.current->previous->next=newNode;
        position.current->previous=newNode;
        size++;
        return --position;
    }
    iterator erase(iterator position){
        if(position.owner!=this) throw std::logic_error("Iterator belongs to a different list instance");
        if(size==0) return position;
        node* temp = position.current;
        position++;
        temp->previous->next=temp->next;
        temp->next->previous= temp->previous;
        delete temp;
        size--;
        return position;
    }
};

#endif //RING_BI_LIST_H
