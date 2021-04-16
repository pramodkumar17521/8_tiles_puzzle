// Program to solve eight tiles problem
/*

A* Algorithm works as-

It maintains a tree of paths originating at the start node.
It extends those paths one edge at a time.
It continues until its termination criterion is satisfied.
 

A* Algorithm extends the path that minimizes the following function-

f(n) = g(n) + h(n)

 

Here,

‘n’ is the last node on the path
g(n) -> level of node in tree
h(n) -> no. of mismatched tiles in  or current and final state
 

Algorithm-
 

The implementation of A* Algorithm involves maintaining two lists- OPEN and CLOSED.
OPEN contains those nodes that have been evaluated by the heuristic function but have not been expanded into successors yet.
CLOSED contains those nodes that have already been visited.
 

The algorithm is as follows-

 

Step-01:
 

Define a list OPEN.
Initially, OPEN consists solely of a single node, the start node S.
 

Step-02:
 

If the list is empty, return failure and exit.

 

Step-03:
 

Remove node n with the smallest value of f(n) from OPEN and move it to list CLOSED.
If node n is a goal state, return success and exit.
 

Step-04:
 

Expand node n.

 

Step-05:
 

If any successor to n is the goal node, return success and the solution by tracing the path from goal node to S.
Otherwise, go to Step-06.
 

Step-06:
 

For each successor node,

Apply the evaluation function f to the node.
If the node has not been in either list, add it to OPEN.
 

Step-07:
 

Go back to Step-02.

*/


#include<bits/stdc++.h>
using namespace std;

struct Node{
    int arr[3][3];   // 2 D array to store tiles or matrix
    int i, j;        // variable to store position of 0 in 2D matrix
    int g=0, h=-1;   // g variable to store value of g(n) means level of tree at which Node exists
                     // h store value of h(n) means no. of mismatch tiles in current and final state
    int f = 0;       // it store value of heuristic function f(n) = g(n) + h(n)
    char ans;        // it store a character of range [A - I] 
    Node *parent = NULL;  // it points to the parent node of current node

    Node()
    {
       // constructor call when we create a variable of type Node
    }
    Node(Node *n)
    {  /* copy constructor -  calls when we create a new variable of type Node
          by passing existing variable of type Node as parameter
         */
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                this->arr[i][j] = n->arr[i][j];
            }
        }
        this->i = n->i, this->j = n->j;
        this->h = n->h, this->g = n->g, this->f = n->f; 
        this->ans = n->ans;
        this->parent = n->parent;
    }
};



char map_alphabates[9] = {'A','B','C','D','E','F','G','H','I'}; /* It map the characters A to I to the numbers 0 to 8
 0 -> A, 1 -> B, .........  8->I
 these indexes are calculates as follows:
  let position of 0 in current state matrix is (2,2) assume as (i, j) then index =  i*3 + j = 2*3 + 2 = 8 => I
matix:   1 2 3 
         4 5 6
         7 8 0
*/
vector<Node*> close;  // close list to maintain record of visited nodes

struct compare{
    /*  It is custom comparator which helps 
        us to compare two Node type objects
    */
    bool operator()(Node* const& n1, Node* const& n2)
    {  /*
        we comparing two objects based on their heuristic function values ie.  f value of Node.
        this helps us in creating minimum heap
        */
        return n1->f > n2->f;
    }
};

priority_queue<Node*, vector<Node*>, compare > open; /* open is a priority queue
 which works as min heap, whose top element always has minimum f value among all 
 elements of the heap / queue
*/

void print(Node *current)
{  /*
     function to print the Node
    */
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            cout<<current->arr[i][j]<<" ";
        }
        cout<<endl;
    }
     cout<<"i: "<<current->i<<" j: "<<current->j<<endl;
       cout<<"f: "<<current->f<<" g: "<<current->g<<" h: "<<current->h<<endl;
       cout<<"ans: "<<current->ans<<endl;
}

int calculate_h(Node *current, Node *final)
{ /*
    function to calculate h(n) value.
    ie. used to calculate no. of misplaced tiles in current node
    as compare to final Node
*/
    int ans=0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(current->arr[i][j] != final->arr[i][j])
            {  
                ans++;
            }
        }
    }
    return ans;
}

void swap(int *a, int *b)
{  /* function to swap to 
     values ie. before swap: a=2, b=3
     after swap: b=2, a=3
   */
    int temp = *a;
    *a = *b;
    *b = temp;
}

Node* move_left(Node *current, Node *final)
{   /*
      move 0 in matrix to one place left of its current position
      0 1      1 0
          ===>  
      2 3      2  3
    */
    Node *curr = new Node(current);
    swap(&curr->arr[curr->i][curr->j], &curr->arr[curr->i][curr->j-1]);
    
    curr->j = curr->j-1;
    curr->h = calculate_h(curr, final);
    curr->g = curr->g +1;
    curr->f = curr->h + curr->g;
    curr->ans = map_alphabates[curr->i * 3 + curr->j];

    return curr;
 
}
Node* move_right(Node *current, Node *final)
{    /*
      move 0 in matrix to one place right of its current position
      1 0      0 1
          ===>  
      2 3      2  3
    */
    Node *curr = new Node(current);

    swap(&curr->arr[curr->i][curr->j], &curr->arr[curr->i][curr->j+1]);
    
    curr->j = curr->j+1;
    curr->h = calculate_h(curr, final);
    curr->g = curr->g +1;
    curr->f = curr->h + curr->g;
    curr->ans = map_alphabates[curr->i * 3 + curr->j];
    curr->parent = current;
    //print(curr);
    return curr;

}
Node* move_up(Node *current, Node *final)
{   /*
      move 0 in matrix to one place upper of its current position
      1 2      0 2
          ===>  
      0 3      1  3
    */
    Node *curr = new Node(current);

    swap(&curr->arr[curr->i][curr->j], &curr->arr[curr->i-1][curr->j]);
    
    curr->i = curr->i-1;
    curr->h = calculate_h(curr, final);
    curr->g = curr->g + 1;
    curr->f = curr->h + curr->g;
    curr->ans = map_alphabates[curr->i * 3 + curr->j];
    curr->parent = current;

    return curr;
    
}
Node* move_down(Node *current, Node *final)
{   /*
      move 0 in matrix to one place down of its current position
      0 2      1 2
          ===>  
      1 3      0  3
    */
    Node *curr = new Node(current);
    swap(&curr->arr[curr->i][curr->j], &curr->arr[curr->i+1][curr->j]);
    
    curr->i = curr->i+1;
    curr->h = calculate_h(curr, final);
    curr->g = curr->g +1;
    curr->f = curr->h + curr->g;
    curr->ans = map_alphabates[curr->i * 3 + curr->j];
    curr->parent = current;
    //print(curr);
    return curr;
}

Node* find_min_f(Node *curr1, Node *curr2)
{
    return (curr1->f < curr2->f) ? curr1 : curr2;
}

bool isEqual(Node *n1, Node *n2)
{   /*
      function to check wether two nodes are equal or not.
      here i am comparing each element of one matrix
      to the corresponding element of other matrix
    */

    for(int i=0; i<3; i++)
       for(int j=0; j<3; j++)
          if(n1->arr[i][j] != n2->arr[i][j])
             return false;

    return true;
}

bool isPresentInClose(Node *curr)
{   /* This is a function to check wether current node
       is present in closed list or not.
    */
    bool flag1 = false;
    for(int i=0; i<close.size(); i++)
    {
        if( isEqual(curr, close[i]))
        {
            return true;
        }
    }
    return false;
}

bool isPresentInOpen(Node *n1, priority_queue<Node*, vector<Node*>, compare > q)
{   /* This is a function to check wether current node
       is present in open list or not.
    */
    while(! q.empty())
    {
        Node *curr = q.top();
        q.pop();

        if( isEqual(n1, curr))
        {
            return true;
        }
    }
    return false;
}

void solve(Node *current, Node *final)
{    
    if(current->h==0)
    {   /* if h(n) of current node is equals to 0.
           means there is no tile misplace in current node.
           ie. current state is same as final state
           then I push current node in close list and return from
           the function.
      */
        close.push_back(current);
        return;
    }
     /* If current state is not same as final state then 
        I push current state to open list
        and loop until either my open list gets empty
        or I found a state which is same as final state
     */
    open.push(current);        
    
    while(!open.empty())
    { 
      Node *curr;
      curr = open.top();  // assigning top element of open list (priority queue) to curr
      current = curr;     // ie. node with lowest heuristic value among all Nodes in open list
      open.pop();
      close.push_back(curr);   // Now I am going to explore my current node, SO I pushed it 
                               // into close list.
      vector<Node*> successor;   // a array for storing the successor nodes of current node
        if(curr->h==0)
        { /*
            if current state is same as final state
            then returns from the function
           */
            return;
        }
        else if(current->i==0 && current->j==0)
        {  /* 0  1  2
              3  4  5 ==> then we can move 0 to one place left or down to its current place
              6  7  8
           */
            Node *curr1 =  move_down(current, final);
            Node *curr2 =  move_right(current, final);
            successor.push_back(curr1);
            successor.push_back(curr2);
        }
        else if(current->i==0 && current->j==1)
        {   /* 1  0  2
               3  4  5 ==> then we can move 0 to one place left, right or down to its current place
               6  7  8
           */
            Node *curr1 =  move_down(current, final);
            Node *curr2 =  move_right(current, final);
            Node *curr3 =  move_left(current, final) ;
            successor.push_back(curr1);
            successor.push_back(curr2);
            successor.push_back(curr3);
        }
        else if(current->i==0 && current->j==2)
        {   /* 1  2  0
               3  4  5 ==> then we can move 0 to one place right or down to its current place
               6  7  8
           */
            Node *curr1 =  move_down(current, final);
            Node *curr2 =  move_left(current, final);
            successor.push_back(curr1);
            successor.push_back(curr2);
        }
        else if(current->i==1 && current->j==0)
        {   /* 1  2  3
               0  4  5 ==> then we can move 0 to one place right, up or down to its current place
               6  7  8
           */
            Node *curr1 =  move_up(current, final);
            Node *curr2 =  move_down(current, final);
            Node *curr3 =  move_right(current, final);
            successor.push_back(curr1);
            successor.push_back(curr2);
            successor.push_back(curr3);
        }
        else if(current->i==1 && current->j==1)
        {   /* 1  2  3
               4  0  5 ==> then we can move 0 to one place left, right, up or down to its current place.
               6  7  8
           */
            Node *curr1 = move_up(current, final);
            Node *curr2 =  move_down(current, final);
            Node *curr3 =  move_right(current, final);
            Node *curr4 =  move_left(current, final);
            successor.push_back(curr1);
            successor.push_back(curr2);
            successor.push_back(curr3);
            successor.push_back(curr4);
        }
        else if(current->i==1 && current->j==2)
        {   /* 1  2  3
               4  5  0 ==> then we can move 0 to one place right, up or down to its current place.
               6  7  8
           */
            Node *curr1 = move_up(current, final);
            Node *curr2 =  move_down(current, final);
            Node *curr3 =  move_left(current, final);
            successor.push_back(curr1);
            successor.push_back(curr2);
            successor.push_back(curr3);
        }
        else if(current->i==2 && current->j==0)
        {   /* 1  2  3
               4  5  6 ==> then we can move 0 to one place left or up to its current place.
               0  7  8
           */
            Node *curr1 = move_up(current, final);
            Node *curr2 =  move_right(current, final);
            successor.push_back(curr1);
            successor.push_back(curr2);
        }
        else if(current->i==2 && current->j==1)
        {   /* 1  2  3
               4  5  6 ==> then we can move 0 to one place left, right, up or down to its current place.
               7  0  8
           */
            Node *curr1 = move_up(current, final);
            Node *curr2 =  move_right(current, final);
            Node *curr3 =  move_left(current, final);
            successor.push_back(curr1);
            successor.push_back(curr2);
            successor.push_back(curr3);
        }
        else if(current->i==2 && current->j==2)
        {   /* 1  2  3
               4  5  6 ==> then we can move 0 to one place left, or up to its current place.
               7  8  0
           */
            Node *curr1 = move_up(current, final);
            Node *curr2 =  move_left(current, final);
            successor.push_back(curr1);
            successor.push_back(curr2);
        }
        /* Iterate over all successor of current node and
           1. check if a succesor is same as final node then 
              push it to close list and return from function
            2. if a successor is neither present in closed list
               nor in open list then push it to the open list
            3. if a successor if present either in close or 
               open list then neglect it. (no action performed).
        */
        for(int i=0; i<successor.size(); i++)    
        {   
            if(successor[i]->h==0)   // checking if a successor is same as final state node.
            {   
              close.push_back(successor[i]);  // pushing successor to close list 
               return;                        // return from function
            }
            else if(! isPresentInClose(successor[i]) && ! isPresentInOpen(successor[i], open))
            {   /* checking wether successor is present in close or open list
                   if no then push successor to open list
               */
                  open.push(successor[i]);
            }
            
        }

  }
  return;
}

void take_input(Node *current)
{   /*
     Function to read input of 
     initial state given by the user.
  */
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            cin>>current->arr[i][j];
            if(current->arr[i][j]==0)
            {
            current->i = i;
            current->j = j;
            }
        }
    }
}



int main()
{   Node *final =  new Node();  // creating final state

    int count=0;
    for(int i=0; i<3; i++)
    {   for(int j=0; j<3; j++)
        {
            final->arr[i][j] = count;   // initializing final state
            count++;
        }
     
    }
    print(final);

    Node *initial = new Node();    // creating initial state

    cout<<"Enter initial State: "<<endl;

    take_input(initial);  // taking input of initial state from user 

    initial-> ans = map_alphabates[initial->i * 3 + initial->j];   // mapping initial state 0 position to a character of [A - I]

    print(initial); 
    
    solve(initial, final);   // function call to find the path from initial to final state

    cout<<endl<<"******** SOLUTION ***********"<<endl;

    Node *curr = close[close.size()-1];  // getting last element of close list (final state)

    vector<char> ans;
    while(curr->parent)  // iterating until the parent of current state exists 
    {                    // ie. untial root / initial state is not reached
        ans.push_back(curr->ans);   // pushing character of that node to ans array
        curr = curr->parent;        // updating current node to its parent node
    }
    cout<<"Final Answer: ";    // printing path from initial to final state
                               // here characters represents position of 0 in each state.
    for(int i=ans.size()-1; i>=0; i--)
    {
        cout<<ans[i]<<" ";
    }cout<<endl;

    return 0;
}