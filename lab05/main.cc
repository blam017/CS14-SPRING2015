#include "lab5.h"

using namespace std;

int main()
{
    BST<int> test;
    
    test.insert(50);
    test.insert(20);
    test.insert(60);
    test.insert(10);
    test.insert(40);
    test.insert(70);
    test.insert(35);
    test.insert(45);
    
    test.inorder();
    test.minCover();
    test.displayMinCover();
    
    
    int a[1000];
    test.findSumPath(test.root, 180, a);
    
    std::map<int, int> m;
    test.vertSum(test.root, 0, m);
    
    return 0;
}