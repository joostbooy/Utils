#ifndef LinkedList_h
#define LinkedList_h

// Static linked list, sorted by key

template <typename type, const uint16_t kMaxSize>
class LinkedList{

public:

    inline void init() {
        size = 0;
        head = 0;					// 0 is the tail
        head_available_slots = 1;	// Cannot be the same as head

        for (uint16_t i = 1; i < kMaxSize; ++i) {
            node[i].next = i + 1;
        }
    }

    inline bool readable(){
        return size > 0;
    }

    inline bool writeable(){
        return size < kMaxSize;
    }

    inline void add(type* value) {
        uint16_t n = new_node();
        memcpy(&node[n].data, value, sizeof(type));
        node[n].next = head;
        head = n;
    }

    inline void sort(uint16_t key, type* value){
        uint16_t n = new_node();
        memcpy(&node[n].data, value, sizeof(type));

        if ((!head) || (key < node[head].key)) {
            node[n].key = key;
            node[n].next = head;
            head = n;
        } else {
            uint16_t prev = head;
            uint16_t curr = node[prev].next;

            while ((curr) && (key >= node[curr].key)) {
                prev = node[prev].next;
                curr = node[prev].next;
            }
            node[prev].next = n;
            node[n].key = key;
            node[n].next = curr;
        }
    }

    inline type pull(){
        type data = node[head].data;

        uint8_t temp = head;
        head = node[head].next;

        node[temp].next = head_available_slots;
        head_available_slots = temp;

        --size;
        return data;
    }

    inline type peek(){
        type data = node[head].data;
        return data;
    }

    inline void clear(){
        while (readable()) {
            pull();
        }
    }

private:

    struct Node {
        type data;
        uint16_t key;
        uint16_t next;
    };

    Node node[kMaxSize + 1]; // +tail
    uint16_t size;
    uint16_t head, head_available_slots;

    uint8_t new_node(){
        uint8_t slot = head_available_slots;
        head_available_slots = node[head_available_slots].next;
        ++size;
        return slot;
    }

};

#endif
