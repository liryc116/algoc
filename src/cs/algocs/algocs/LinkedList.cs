using System;

namespace algocs
{
    public class LinkedList<T>
    {
        // A rather Sentinel implementation of Linked Lists
        private LinkedList<T> next;
        private T value;

        public LinkedList(T val, LinkedList<T> next = null)
        {
            this.value = val;
            this.next = next;
        }

        public T getValue()
        { return this.value; }

        public LinkedList<T> getNext()
        { return this.next; }

        // "Inserts" as first
        public void list_push(T val)
        {
            LinkedList<T> new_block = new LinkedList<T>(val, this.next);
            this.next = new_block;
        }

        public void list_insert(T val, int index)
        {
            LinkedList<T> tmp = this;
            for (int i = 0; i < index; tmp = this.next, i++) ;
            tmp.list_push(val);
        }
        
        public void list_pop_front(LinkedList<T> block)
        {
            block.next = this.next;
        }

        public void list_pop(LinkedList <T>block, int n)
        {
            block.next = this.next;
            this.next = block;
        }
        
        public bool list_is_in(T x)
        {
            LinkedList<T> tmp = this;
            while (tmp!=null && !(Equals(tmp.value, x)))
                tmp = tmp.next;

            return tmp != null && tmp.value == x;
        }
        
        public LinkedList<T> list_find(T x)
        {
            LinkedList<T> tmp = this;
            while (tmp!=null && !Equals(tmp.value, x))
                tmp = tmp.next;

            return tmp;
        }
        
        public bool list_is_sorted(T x)
        {
            LinkedList<T> tmp = this;
            while (tmp!=null && tmp.value!=x)
                tmp = tmp.next;

            return tmp != null && tmp.value == x;
        }
        

        public void list_rev()
        {
        }

        public LinkedList<T> list_split_half()
        {
            LinkedList<T> half = this;
            
            return half;
        }
    }
}