"""
so this will be the skeleton basically psuedo code version for the c++ version
THOUGGHT PROCESS:
input: the input is going to be almost like an array on numbers:
Root [x1]
Parent  Root [xN(where N is the number of connections)]

output: we want an output of nodes that cant reach the root node

obvious LEETCODE type: trees --> BFS (queue vers) or DFS (stack vers) (almost always)
caveat we want the compliment of the visited set in the BFS/DFS?


how to get there:
number 1 : we take in the input and turn into something we can use.
key question: is there a structure to input ie is it sorted? no (yes: just do BFS straight away)
number 2: we now actually have to worry about the input as it isnt sorted so cant just do a BFS
numbers 3: we can create an 2D array or all nodes and its IMMEDIATE children
better approach: just use a hashmap it hard to iterate arrays
number 4: we also need to store the total nodes in the set as BFS/DFS will only tell us the related nodes
the compliment of that set is needed 

O(E) so far 

number 5: literally just a search of the algo? which to use?
GOOD THING: BOTH HAVE A VISITED SET BUILT INTO THEM SO DONT NEED ANY NEW IMPLIMENTATION
if wide:
use dfs (less to store)
else:
use bfs

O(V + E)(constant)


number 6:FULL set - traversed BFS set:
O(n)

number 7:sort it --> what algo is there a faster method? perhaps dynamic?
biggest over head: (O(nlog(k)))
Think: issue we arent given a guarantee of input being sorted and storing in a set creates meaning it isnt sorted
 
SORTING SCALES UP from constant to n(log(n))
"""
import sys

from collections import defaultdict, deque

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    root = int(data[0])
    print(data)

    children = defaultdict(list)
    all_nodes = set()
    all_nodes.add(root)
    for i in range(1, len(data) - 1, 2):
        parent, child = int(data[i]), int(data[i + 1])
        children[parent].append(child)
        all_nodes.add(parent)
        all_nodes.add(child)

    visited = {root}
    queue = deque([root])
    while queue:
        node = queue.popleft()
        for c in children.get(node, ()):
            if c not in visited:
                print(c)
                visited.add(c)
                queue.append(c)
    print(sorted(all_nodes - visited)) #increasing order of inode id (requirement)



if __name__ == "__main__":
    main()
