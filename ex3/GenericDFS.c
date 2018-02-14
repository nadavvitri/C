#include <stdio.h>
#include "GenericDFS.h"

/**
 * This function work recursively in DFS way and update the current best node. if we reach and this
 * node equal to the best value we stop and return him. else, we search for the best by updating to
 * the biggest value of nodes.
 * @param head The head of the tree
 * @param getChildren A function that gets a node and a pointer to array of nodes.
 * the function allocates memory for an array of all the children of the node, and
 * returns the number of the children.
 * (the array might be initialized, but the function can't know how many children
 * the node has)
 * @param getVal A function that gets a node and returns its value, as int
 * @param freeNode A function that frees node from memory.
 * this function will be called for each Node returns by getChildren.
 * @param copy A function that do deep copy of Node.
 * @param best The best available value for a node, when the function encounters
 * a node with that value it stops looking and returns it.
 * If the best value can't be determined, pass UINT_MAX (defined in limits.h)
 * for that param.
 * @param curBest pointer to the current best node
 * @param curBestVal the value of the current best node
 * @return curBest iff his value equal to best value, else NULL.
 */
pNode getBestHelper(pNode head, getNodeChildrenFunc getChildren, getNodeValFunc getVal,
                    freeNodeFunc freeNode, copyNodeFunc copy, unsigned int best, pNode *curBest,
                    unsigned int curBestVal)
{
    if (head == NULL)
    {
        return NULL;
    }
    if (getVal(head) > curBestVal)
    {
        if (*curBest != NULL)
        {
            freeNode(*curBest);
        }
        *curBest = copy(head);
    }
    // if current best node equal to the best value
    if (getVal(*curBest) == best)
    {
        return curBest;
    }
    pNode *children = NULL;
    int numOfChildren = getChildren(head, &children);
    for (int i = 0; i < numOfChildren; ++i)
    {
        getBestHelper(children[i], getChildren, getVal, freeNode, copy, best, curBest,
                      getVal(*curBest));
        freeNode(children[i]);
    }
    freeNode(children);
    return NULL;
}


pNode getBest(pNode head, getNodeChildrenFunc getChildren,
              getNodeValFunc getVal, freeNodeFunc freeNode, copyNodeFunc copy, unsigned int best)
{
    // initialize node to be the candidate for the best with value equal to zero
    pNode curBest = NULL;
    unsigned int curBestVal = 0;
    // send the address to the helper function so that curBest will change from outside function
    getBestHelper(head, getChildren, getVal, freeNode, copy, best, &curBest, curBestVal);
    return curBest;
}