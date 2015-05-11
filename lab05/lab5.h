#ifndef BST_H
#define BST_H
#define TEST

#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <map>
#include <list>
#include <math.h>

using namespace std;

#define nil 0

//#define Value int //restore for testing.

template <typename Value>
class BST {
    class Node 
    {   // binary tree node
        public:
            Node* left;
            Node* right;
            Value value;
            bool selected;
            Node( const Value v = Value() )
            : value(v), left(nil), right(nil), selected(false)
            {}
            Value& content() { return value; }
            bool isInternal() { return left != nil && right != nil; }
            bool isExternal() { return left != nil || right != nil; }
            bool isLeaf() { return left == nil && right == nil; }
            int height() {
            // returns the height of the subtree rooted at this node
            // FILL IN
                if(isLeaf()) return 0;
                Node* cur = this;
                return heightHelper(cur);
                
            }
            int size() {
            // returns the size of the subtree rooted at this node,
            // FILL IN
                int count = 1;
                if (left != nil) count += left->size();
                if (right != nil) count += right->size();
                return count;
            }
        
        private:
            int heightHelper(Node* cur)
            {
                if(cur == nil) return -1;
                
                int rightH = heightHelper(cur->right);
                int leftH = heightHelper(cur->left);
                
                if (rightH > leftH) return rightH + 1;
                else return leftH + 1;
            }
    }; // Node
    // const Node* nil; // later nil will point to a sentinel node.
    int count;
    int numselected;
    public:
        Node* root;
        // LAB 5 FUNCTIONS
        //Part 1
        void minCover()
        {
            Node* cur = root;
            minCoverHelper(cur);
        }
        
        void minCoverHelper(Node* cur) 
        {
            if (cur->left != nil) minCoverHelper(cur->left);
            if (cur->right != nil) minCoverHelper(cur->right);
            if(cur->left != nil && !cur->left->selected)
            {
                cur->selected = true;
                numselected += 1;
            }
            else if(cur->right != nil && !cur->right->selected)
            {
                cur->selected = true;
                numselected += 1;
            }
        }
        
        void displayMinCover()
        {
            Node* cur = root;
            cout << "Part 1" << endl;
            displayMinCoverHelper(cur);
            cout << endl << numselected << endl;
        }
        
        void displayMinCoverHelper(Node* cur) const
        {
            if(cur->left != nil) displayMinCoverHelper(cur->left);
            if(cur->selected)
            {
                cout << cur->value << " ";
            }
            if(cur->right != nil) displayMinCoverHelper(cur->right);
        }
        
        //Part 2
        void findSumPath(Node* n, int sum, int buffer[])
        {
            cout << "Part 2" << endl;
            
            buffer[0] = n->value;
            
            int buffersum = n->value;

            if(n->left != nil) findSumPath(n->left, sum, buffer, buffersum);
            if(n->right != nil) findSumPath(n->right, sum, buffer, buffersum);
            
            for(int i = 0; i < sizeof(buffer); ++i)
            {
                buffer[i] = 0;
            }
            
            cout << endl;
        }
        //Helper function
        void findSumPath(Node* n, int sum, int buffer[], int buffersum)
        {
            int index = 0;
            buffersum += n->value;
            
            if(buffersum > sum) return;

            for(int i = 0; buffer[i] != 0; ++i)
            {
                index += 1;
            }

            buffer[index] = n->value;
            
            if(n->isLeaf() && buffersum == sum)
            {
                for(int i = 0; i <= index; ++i)
                {
                    cout << buffer[i] << " ";
                    buffer[i] = 0;
                }
                return;
            }
            if(n->isLeaf())
            {
                for(int i = 1; i <= index; ++i)
                {
                    buffer[i] = 0;
                }
            }
            
            if(n->left != nil) findSumPath(n->left, sum, buffer, buffersum);
            if(n->right != nil) findSumPath(n->right, sum, buffer, buffersum);
        }
        
        //Part 3
        void vertSum(Node* cur, int hd, std::map<int, int>& m)
        {
            cout << "Part 3" << endl;
            
            vertSumHelper(cur, hd, m);
            
            for(std::map<int,int>::iterator i = m.begin(); i != m.end();++i)
            {
                cout << i->second << ' ';
            }
            cout << endl;
        }
        
        void vertSumHelper(Node* cur, int hd, std::map<int, int> &m)
        {
            if(cur != nil)
            {
                vertSumHelper(cur->left, hd - 1, m);
                vertSumHelper(cur->right, hd + 1, m);
                
                m[hd] = cur->value + m[hd];
            }
        }
        int size() {
        // size of the overall tree.
        // FILL IN
            if(root == nil) return 0;
            Node * cur = root;
            return size(cur);
        }
        bool empty() {return size() == 0;}
        void print_node( const Node* n ) {
        // Print the node’s value.
        // FILL IN
            cout << n->value;
        }
        bool search (Value x) {
        // search for a Value in the BST and return true iff it was found.
        // FILL IN
            Node *cur = root;
            
            while (cur != nil)
            {
                if (cur->value == x) return true;
                if (cur->value < x) cur = cur->right;
                else if (cur->value > x) cur = cur->left;
            }
            return false;
        }
        void preorder()const {
        // Traverse and print the tree one Value per line in preorder.
        // FILL IN
            Node *cur = root;
            preorder(cur);
        }
        void postorder()const {
        // Traverse and print the tree one Value per line in postorder.
        // FILL IN
            Node *cur = root;
            postorder(cur);
        }
        void inorder()const {
        // Traverse and print the tree one Value per line in inorder.
        // FILL IN
            Node *cur = root;
            inorder(cur);
        }
        
        Value& operator[] (int n) {
        // returns reference to the value field of the n-th Node.
        // FILL IN
            if(n >= size() || n < 0)
            {
                cout << "Error: Out of bounds" << endl;
                exit(-1);
            }
            Node * cur = root;
            if(n == 0)
            {
                while(!cur->isLeaf())
                {
                    cur = cur->left;
                }
                return cur->value;
            }
            nthNode(cur,n);
            return cur->value;
        }
        
        BST() : count(0), root(nil), numselected(0) {}
        void insert( Value X ) { root = insert( X, root ); }
        Node* insert( Value X, Node* T ) {
            // The normal binary-tree insertion procedure ...
            if ( T == nil ) 
            {
                T = new Node( X ); // the only place that T gets updated.
            } 
            else if ( X < T->value ) 
            {
                T->left = insert( X, T->left );
            } 
            else if ( X > T->value ) 
            {
                T->right = insert( X, T->right );
            } 
            else 
            {
                T->value = X;
            }
            // later, rebalancing code will be installed here
            return T;
        }
        void remove( Value X ) { root = remove( X, root ); }
        Node* remove( Value X, Node*& T ) {
            // The normal binary-tree removal procedure ...
            // Weiss’s code is faster but way more intricate.
            if ( T != nil ) 
            {
                if ( X > T->value ) 
                {
                    T->right = remove( X, T->right );
                } 
                else if ( X < T->value ) 
                {
                    T->left = remove( X, T->left );
                } 
                else 
                { // X == T->value
                    if ( T->right != nil ) 
                    {
                        Node* x = T->right;
                        while ( x->left != nil ) x = x->left;
                        T->value = x->value; // successor’s value
                        T->right = remove( T->value, T->right );
                    } 
                    else if ( T->left != nil ) 
                    {
                        Node* x = T->left;
                        while ( x->right != nil ) x = x->right;
                        T->value = x->value; // predecessor’s value
                        T->left = remove( T->value, T->left );
                    } 
                    else 
                    { // *T is external
                        delete T;
                        T = nil; // the only updating of T
                    }
                }
            }
            // later, rebalancing code will be installed here
            return T;
        }
        void okay( ) { okay( root ); }
        void okay( Node* T ) {
            // diagnostic code can be installed here
            return;
        }
        
    private:
        void inorder(Node * cur) const
            {
                if(cur->left != nil) inorder(cur->left);
                cout << cur->value << endl;
                if(cur->right != nil) inorder(cur->right);
            }
        void postorder(Node* cur) const
        {
            if (cur->left != nil) postorder(cur->left);
            if (cur->right != nil) postorder(cur->right);
            cout << cur->value << endl;
        }
        void preorder(Node* cur) const
        {
            cout << cur->value << endl;
            if (cur->left != nil) preorder(cur->left);
            if (cur->right != nil) preorder(cur->right);
        }
        Node* nthNode(Node *cur, int n)
        {
            if (n == 0) return cur;
            if(cur->left != nil) nthNode(cur->left, n);
            n -= 1;
            if(cur->right != nil) nthNode(cur->right, n);
        }
        int size(Node* cur)
        {
            if(cur == nil) return 0;
            else 
            {
                return size(cur->left) + size(cur->right) + 1;
            }
            
        }
}; // BST

#endif