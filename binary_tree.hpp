#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__ 1

#include "binary_tree_node.hpp"

template <typename T>
class binary_tree
{
    binary_tree_node<T>* m_root;

public:

    /* Init */

    inline binary_tree() : 
        m_root(nullptr) {}

    inline binary_tree(const binary_tree_node<T>& other) :
        m_root(new binary_tree_node<T>(other)) {}
    inline binary_tree(binary_tree_node<T>&& other) :
        m_root(new binary_tree_node<T>(other)) {}

    /* Copy */

    inline binary_tree(const binary_tree<T>& other) :
        m_root(other.m_root ? m_root = new binary_tree_node<T>(*other.m_root) : nullptr) {}
    inline binary_tree(binary_tree<T>&& other) :
        m_root(m_root = new binary_tree_node<T>(other)) {}

    inline binary_tree& operator=(const binary_tree& other)
    {
        *m_root = *other.m_root;
    }
    inline binary_tree& operator=(binary_tree&& other)
    {
        *m_root = *other.m_root;
    }

    /* Delete */

    inline ~binary_tree() { delete m_root; }

    /* Methods */

    inline size_t size() const { return m_root->child_count(); }

    inline const binary_tree_node<T>* root() const { return m_root; }
    inline       binary_tree_node<T>* root()       { return m_root; }
};

#endif