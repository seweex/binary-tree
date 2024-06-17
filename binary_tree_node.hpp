#ifndef __BINARY_TREE_NODE_H__
#define __BINARY_TREE_NODE_H__ 1

#include "stddef.h"
#include <stdexcept>

template <typename T>
class binary_tree_node
{
    T * m_data;
    binary_tree_node<T> * m_left;
    binary_tree_node<T> * m_right;

    inline void remove_native(const T& key, binary_tree_node<T>* parent)
    {
        if (key > *m_data)
            m_right->remove_native(key, this);
        else if (key < *m_data)
            m_left->remove_native(key, this);
        else
        {
            if (!m_left && !m_right)
            {
                if (!parent)
                {
                    delete this;
                    return;
                }
                if (parent->m_left == this)
                {
                    delete parent->m_left;
                    parent->m_left = nullptr;
                }
                else if (parent->m_right == this)
                {
                    delete parent->m_right;
                    parent->m_right = nullptr;
                }          
            }
            else if (m_left != m_right) 
            {
                binary_tree_node<T>* existing_child = m_left ? m_left : m_right;

                *m_data = *existing_child->m_data;
                *m_left = *existing_child->m_left;
                *m_right = *existing_child->m_right;
                delete existing_child;
            }
            else if (m_left && m_right)
            {
                if (!m_right->m_left)
                {
                    *m_data = *m_right->m_data;

                    binary_tree_node<T>* right_right = m_right->m_right;
                    *m_right = *m_right->m_right;

                    delete right_right;
                }
                else
                {
                    *m_data = *m_right->m_left->m_data;
                    m_right->m_left->remove_native(*m_right->m_left->m_data, m_right);
                }
            }
        }
    }
    
public:

    /* Init */

    inline binary_tree_node(const T& data) :
        m_data(new T(data)),
        m_left(nullptr),
        m_right(nullptr) {}

    inline binary_tree_node(const T& data, binary_tree_node<T> * left, binary_tree_node<T> * right) :
        m_data(new T(data)),
        m_left(new binary_tree_node<T>(left)),
        m_right(new binary_tree_node<T>(right)) {}

    inline binary_tree_node(T&& data) :
        m_data(new T(data)),
        m_left(nullptr),
        m_right(nullptr) {}

    inline binary_tree_node(T&& data, binary_tree_node<T> * left, binary_tree_node<T> * right) :
        m_data(new T(data)),
        m_left(new binary_tree_node<T>(left)),
        m_right(new binary_tree_node<T>(right)) {}

    /* Copy */

    inline binary_tree_node(const binary_tree_node<T>& other) :
        m_data(new T(*other.m_data)),
        m_left(other.m_left ? new binary_tree_node<T>(*other.m_left) : nullptr),
        m_right(other.m_right ? new binary_tree_node<T>(*other.m_right) : nullptr) {}
    
    inline binary_tree_node(binary_tree_node<T>&& other) :
        m_data(new T(*other.m_data)),
        m_left(other.m_left ? new binary_tree_node<T>(*other.m_left) : nullptr),
        m_right(other.m_right ? new binary_tree_node<T>(*other.m_right) : nullptr) {}

    inline binary_tree_node<T>& operator=(const binary_tree_node<T>& other)
    {
        if (m_data)
            *m_data = *other.m_data;
        else
            m_data = new T(*other.m_data);
        
        if (m_left)
            *m_left = *other.m_left;
        else
            m_left = new binary_tree_node<T>(*other.m_left);

        if (m_right)
            *m_right = *other.m_right;
        else
            m_right = new binary_tree_node<T>(*other.m_right);

        return *this;
    }

    inline binary_tree_node<T>& operator=(binary_tree_node<T>&& other)
    {
        if (m_data)
            *m_data = *other.m_data;
        else
            m_data = new T(*other.m_data);
        
        if (m_left)
            *m_left = *other.m_left;
        else
            m_left = new binary_tree_node<T>(*other.m_left);

        if (m_right)
            *m_right = *other.m_right;
        else
            m_right = new binary_tree_node<T>(*other.m_right);
    }

    /* Delete */

    inline ~binary_tree_node() 
    {
        delete m_data;
        delete m_left;
        delete m_right;
    }

    /* Methods */

    inline T& get() { return *m_data; }
    inline const T& get() const { return *m_data; }

    inline binary_tree_node<T>* left() { return m_left; }
    inline const binary_tree_node<T>* left() const { return m_left; }

    inline binary_tree_node<T>* right() { return m_right; }
    inline const binary_tree_node<T>* right() const { return m_right; }

    inline void set(const T& data) { *m_data = data; }
    inline void set(T&& data) { *m_data = data; }

    inline void set_left(const binary_tree_node<T>& left) {
        m_left ? *m_left = left : m_left = new binary_tree_node<T>(left);
    }
    inline void set_left(binary_tree_node<T>&& left) {
        m_left ? *m_left = left : m_left = new binary_tree_node<T>(left);
    }

    inline void set_right(const binary_tree_node<T>& right) {
        m_right ? *m_right = left : m_right = new binary_tree_node<T>(right);
    }
    inline void set_right(binary_tree_node<T>&& right) {
        m_right ? *m_right = left : m_right = new binary_tree_node<T>(right);
    }

    inline size_t child_count() const 
    {
        size_t count = 0;

        if (m_left) 
            count += m_left->child_count() + 1;
        if (m_right)
            count += m_right->child_count() + 1;

        return count;
    }

    inline void add(const binary_tree_node<T>& data)
    {
        if(data < *m_data)
        {
            if (m_left)
                m_left->add(data);
            else
                m_left = new binary_tree_node<T>(data);
        }
        else 
        {
            if (m_right)
                m_right->add(data);
            else
                m_right = new binary_tree_node<T>(data);
        }
    }
    inline void add(binary_tree_node<T>&& data)
    {
        if(data < *m_data)
        {
            if (m_left)
                m_left->add(data);
            else
                m_left = new binary_tree_node<T>(data);
        }
        else 
        {
            if (m_right)
                m_right->add(data);
            else
                m_right = new binary_tree_node<T>(data);
        }
    }
    inline void add(const T& data)
    {
        if(data < *m_data)
        {
            if (m_left)
                m_left->add(data);
            else
                m_left = new binary_tree_node<T>(data);
        }
        else 
        {
            if (m_right)
                m_right->add(data);
            else
                m_right = new binary_tree_node<T>(data);
        }
    }
    inline void add(T&& data)
    {
        if(data < *m_data)
        {
            if (m_left)
                m_left->add(data);
            else
                m_left = new binary_tree_node<T>(data);
        }
        else 
        {
            if (m_right)
                m_right->add(data);
            else
                m_right = new binary_tree_node<T>(data);
        }
    }

    inline void remove(const T& data)
    {
        remove_native(data, nullptr);
    }
    inline void remove(T&& data)
    {
        remove_native(data, nullptr);
    }

    template<typename... RestArgsTy>
    inline void traverse_infix(void (*func)(binary_tree_node<T>&, RestArgsTy...), RestArgsTy... args)
    {
        if (m_left) 
            m_left->traverse_infix(func, args...);

        func(*this, args...);

        if (m_right)  
            m_right->traverse_infix(func, args...);
    }
    
    template<typename... RestArgsTy>
    inline void traverse_postfix(void (*func)(binary_tree_node<T>&, RestArgsTy...), RestArgsTy... args)
    {
        if (m_left) 
            m_left->traverse_postfix(func, args...);
        if (m_right)  
            m_right->traverse_postfix(func, args...);

        func(*this, args...);
    }
    
    template<typename... RestArgsTy>
    inline void traverse_prefix(void (*func)(binary_tree_node<T>&, RestArgsTy...), RestArgsTy... args)
    {
        func(*this, args...);

        if (m_left) 
            m_left->traverse_prefix(func, args...);
        if (m_right)  
            m_right->traverse_prefix(func, args...);
    }

    inline binary_tree_node<T>& find(const binary_tree_node<T>& key)
    {
        if (*key.m_data == *m_data)
            return *this;
        else if(*key.m_data > *m_data)
            return m_right ? m_right->find(key) : throw std::invalid_argument("Invalid key");
        else if (*key.m_data < *m_data)
            return m_left ? m_left->find(key) : throw std::invalid_argument("Invalid key");
        else 
            throw std::invalid_argument("Invalid key");
    }
    inline binary_tree_node<T>& find(binary_tree_node<T>&& key)
    {
        if (*key.m_data == *m_data)
            return *this;
        else if(*key.m_data > *m_data)
            return m_right ? m_right->find(key) : throw std::invalid_argument("Invalid key");
        else if (*key.m_data < *m_data)
            return m_left ? m_left->find(key) : throw std::invalid_argument("Invalid key");
        else 
            throw std::invalid_argument("Invalid key");
    }
    inline binary_tree_node<T>& find(const T& key)
    {
        if (key == *m_data)
            return *this;
        else if(key > *m_data)
            return m_right ? m_right->find(key) : throw std::invalid_argument("Invalid key");
        else if (key < *m_data)
            return m_left ? m_left->find(key) : throw std::invalid_argument("Invalid key");
        else 
            throw std::invalid_argument("Invalid key");;
    }
    inline binary_tree_node<T>& find(T&& key)
    {
        if (key == *m_data)
            return *this;
        else if(key > *m_data)
            return m_right ? m_right->find(key) : throw std::invalid_argument("Invalid key");
        else if (key < *m_data)
            return m_left ? m_left->find(key) : throw std::invalid_argument("Invalid key");
        else 
            throw std::invalid_argument("Invalid key");
    }

    inline bool operator==(const binary_tree_node<T>& other) const { return *m_data == *other.m_data; } 
    inline bool operator==(binary_tree_node<T>&& other) const { return *m_data == *other.m_data; } 

    inline bool operator!=(const binary_tree_node<T>& other) const { return *m_data!= *other.m_data; }
    inline bool operator!=(binary_tree_node<T>&& other) const { return *m_data!= *other.m_data; }

    inline bool operator<(const binary_tree_node<T>& other) const { return *m_data < *other.m_data; }
    inline bool operator<(binary_tree_node<T>&& other) const { return *m_data < *other.m_data; }
};
#endif