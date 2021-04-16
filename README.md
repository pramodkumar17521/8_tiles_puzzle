# 8_tiles_puzzle
8 tiles puzzle problem is solved using A - Star algorithm in C++ programming language

***A\* Algorithm works as:***

It maintains a tree of paths originating at the start node.
It extends those paths one edge at a time.
It continues until its termination criterion is satisfied.
 

A* Algorithm extends the path that minimizes the following function-

f(n) = g(n) + h(n)     -- Heuristic function

 

Here,

‘n’ is the last node on the path
g(n) -> level of node in tree
h(n) -> no. of mismatched tiles in  or current and final state
 

Algorithm-
 

The implementation of A* Algorithm involves maintaining two lists- OPEN and CLOSED.
OPEN contains those nodes that have been evaluated by the heuristic function but have not been expanded into successors yet.
CLOSED contains those nodes that have already been visited.
 

The algorithm is as follows-

 

1. Step:
Define a list OPEN.
Initially, OPEN consists solely of a single node, the start node S.
 

2. Step:
If the list is empty, return failure and exit.

 

3. Step:
Remove node n with the smallest value of f(n) from OPEN and move it to list CLOSED.
If node n is a goal state, return success and exit.
 

4. Step:
Expand node n.

 

5. Step:
If any successor to n is the goal node, return success and the solution by tracing the path from goal node to S.
Otherwise, go to Step-06.
 

6. Step:
For each successor node,
Apply the evaluation function f to the node.
If the node has not been in either list, add it to OPEN.
 

7. Step:
Go back to Step 02.
