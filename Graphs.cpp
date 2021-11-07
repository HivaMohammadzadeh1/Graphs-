#include<iostream>
#include<iomanip>
#include<cstring>

using namespace std;


// The class definition for QueType using templates


class FullQueue
{};


class EmptyQueue
{};


template <class ItemType>
struct NodeType;


template <class ItemType>
class QueType
{
public:
    QueType();
    QueType(int max);
    ~QueType();
    void MakeEmpty();
    bool IsEmpty() const;
    bool IsFull() const;
    void Enqueue(ItemType newItem);
    void Dequeue(ItemType& item);

private:
  NodeType<ItemType>* front;
  NodeType<ItemType>* rear;
};


template <class ItemType>
struct NodeType
{
  ItemType info;
  NodeType* next;
};


// The function definitions for class QueType


template <class ItemType>
QueType<ItemType>::QueType()
{
  front = nullptr;
  rear = nullptr;
}


template <class ItemType>
void QueType<ItemType>::MakeEmpty()
{
  NodeType<ItemType>* tempPtr;

  while (front != nullptr)
  {
    tempPtr = front;
    front = front->next;
    delete tempPtr;
  }
  rear = nullptr;
}


template <class ItemType>
QueType<ItemType>::~QueType()
{
  MakeEmpty();
}


template<class ItemType>
bool QueType<ItemType>::IsFull() const
{
  NodeType<ItemType>* location;
  try
  {
    location = new NodeType<ItemType>;
    delete location;
    return false;
  }
  catch(bad_alloc exception)
  {
    return true;
  }
}


template <class ItemType>
bool QueType<ItemType>::IsEmpty() const
{
  return (front == nullptr);
}


template <class ItemType>
void QueType<ItemType>::Enqueue(ItemType newItem)
{
  if (IsFull())
    throw FullQueue();
  else
  {
    NodeType<ItemType>* newNode;

    newNode = new NodeType<ItemType>;
    newNode->info = newItem;
    newNode->next = nullptr;
    if (rear == nullptr)
      front = newNode;
    else
      rear->next = newNode;
    rear = newNode;
  }
}


template <class ItemType>
void QueType<ItemType>::Dequeue(ItemType& item)
{
  if (IsEmpty())
    throw EmptyQueue();
  else
  {
    NodeType<ItemType>* tempPtr;

    tempPtr = front;
    item = front->info;
    front = front->next;
    if (front == nullptr)
      rear = nullptr;
    delete tempPtr;
  }
}


// The class definition for GraphType using templates


template<class VertexType>

class GraphType
{
public:
  GraphType();
  GraphType(int maxV);
  ~GraphType();
  void AddVertex(VertexType);
  void AddEdge(VertexType, VertexType, int);
  int WeightIs(VertexType, VertexType);
  void GetToVertices(VertexType, QueType<VertexType>&);
    
  // Bolean EdgeExists FUnction which determines whether two vertices are connected by an edge
  bool EdgeExists(VertexType , VertexType );

  // DeleteEdge Function which deletes a given edge from two vertex
  void DeleteEdge(VertexType, VertexType );
    
private:
  int numVertices;
  int maxVertices;
  VertexType* vertices;
  int edges[50][50];
  bool* marks;

  // adjacency matrix
  bool** adjMatrix;
    
};


// The function definitions for class GraphType


template<class VertexType>
GraphType<VertexType>::GraphType()
{
  numVertices = 0;
  maxVertices = 50;
  vertices = new VertexType[50];
  marks = new bool[50];
}


template<class VertexType>
GraphType<VertexType>::GraphType(int maxV)
{
  numVertices = 0;
  maxVertices = maxV;
  vertices = new VertexType[maxV];
  marks = new bool[maxV];
}


template<class VertexType>
GraphType<VertexType>::~GraphType()
{
  delete [] vertices;
  delete [] marks;
}


const int NULL_EDGE = 0;
 

template<class VertexType>
void GraphType<VertexType>::AddVertex(VertexType vertex)
{
  vertices[numVertices] = vertex;
  for (int index = 0; index < numVertices; index++)
  {
    edges[numVertices][index] = NULL_EDGE;
    edges[index][numVertices] = NULL_EDGE;
  }
  numVertices++;
}


template<class VertexType>
int IndexIs(VertexType* vertices, VertexType vertex)
{
  int index = 0;

  while (!(vertex == vertices[index]))
    index++;
  return index;
}


template<class VertexType>
void GraphType<VertexType>::AddEdge(VertexType fromVertex,
     VertexType toVertex, int weight)
{
  int row;
  int col;

  row = IndexIs(vertices, fromVertex);
  col = IndexIs(vertices, toVertex);
  edges[row][col] = weight;
}


template<class VertexType>
int GraphType<VertexType>::WeightIs
     (VertexType fromVertex, VertexType toVertex)
{
  int row;
  int col;

  row = IndexIs(vertices, fromVertex);
  col = IndexIs(vertices, toVertex);
  return edges[row][col];
}


template<class VertexType>
void GraphType<VertexType>::GetToVertices(VertexType vertex,
     QueType<VertexType>& adjVertices)
{
  int fromIndex;
  int toIndex;

  fromIndex = IndexIs(vertices, vertex);
  for (toIndex = 0; toIndex < numVertices; toIndex++)
    if (edges[fromIndex][toIndex] != NULL_EDGE)
      adjVertices.Enqueue(vertices[toIndex]);
}


// Bolean EdgeExists FUnction which determines whether two vertices are connected by an edge


template<class VertexType>
bool GraphType<VertexType>::EdgeExists(VertexType fromVertex, VertexType toVertex)
{
    int row;
    int column;

    row = IndexIs(vertices, fromVertex);
    column = IndexIs(vertices, toVertex);
    if (edges[row][column] == 0)
    {
        return false;
    }
    return true;
}


// DeleteEdge Function which deletes a given edge from two vertex


template<class VertexType>
void GraphType<VertexType>::DeleteEdge(VertexType fromVertex, VertexType toVertex)
{
    int row;
    int column;

    row = IndexIs(vertices, fromVertex);
    column = IndexIs(vertices, toVertex);
    edges[row][column] = 0;
}


// The class definition for StackType using templates


class FullStack
{};

class EmptyStack
{};

const int MAX_ITEMS = 5;

template<class ItemType>
class StackType
{
public:

    StackType();
    bool IsFull() const;
    bool IsEmpty() const;
    void Push(ItemType item);
    void Pop();
    ItemType Top();

private:
    int top;
    ItemType  items[MAX_ITEMS];
};


// The function definitions for class StackType.


template<class ItemType>
StackType<ItemType>::StackType()
{
  top = -1;
}


template<class ItemType>
bool StackType<ItemType>::IsEmpty() const
{
  return (top == -1);
}


template<class ItemType>
bool StackType<ItemType>::IsFull() const
{
  return (top == MAX_ITEMS-1);
}


template<class ItemType>
void StackType<ItemType>::Push(ItemType newItem)
{
    if (IsFull())
        throw FullStack();
            top++;
    items[top] = newItem;
}


template<class ItemType>
void StackType<ItemType>::Pop()
{
  if( IsEmpty() )
    throw EmptyStack();
  top--;
}


template<class ItemType>
ItemType StackType<ItemType>::Top()
{
  if (IsEmpty())
    throw EmptyStack();
  return items[top];
}


//BF Search

template<class VertexType>
void BreadthFirstSearch(GraphType<VertexType> graph,
     VertexType startVertex, VertexType endVertex)
{
  using namespace std;
  QueType<VertexType> queue;
  QueType<VertexType> vertexQ;

  bool found = false;
  VertexType vertex;
  VertexType item;

  graph.ClearMarks();
  queue.Enqueue(startVertex);

  do
  {
    queue.Dequeue(vertex);

    if (vertex == endVertex)
    {
      cout  << vertex;
      found = true;
    }
    else
    {
      if (!graph.IsMarked(vertex))
      {
        graph.MarkVertex(vertex);
        cout  << vertex;
        graph.GetToVertices(vertex, vertexQ);

        while (!vertexQ.IsEmpty())
        {
          vertexQ.Dequeue(item);
          if (!graph.IsMarked(item))
            queue.Enqueue(item);
        }
      }
    }
  } while (!queue.IsEmpty() && !found);
  if (!found)
  cout << "Path not found." << endl;
}


// DF Search


template<class VertexType>
void DepthFirstSearch(GraphType<VertexType> graph,
     VertexType startVertex, VertexType endVertex)
{
  using namespace std;
  StackType<VertexType> stack;
  QueType<VertexType> vertexQ;

  bool found = false;
  VertexType vertex;
  VertexType item;

  graph.ClearMarks();
  stack.Push(startVertex);
  do
  {
    stack.Pop(vertex);
    if (vertex == endVertex)
    {
      cout << vertex;
      found = true;
    }
    else
    {
      if (!graph.IsMarked(vertex))
      {
        graph.MarkVertex(vertex);
        cout << vertex;
        graph.GetToVertices(vertex, vertexQ);

        while (!vertexQ.IsEmpty())
        {
          vertexQ.Dequeue(item);
          if (!graph.IsMarked(item))
            stack.Push(item);
        }
      }
    }
  } while (!stack.IsEmpty() && !found);
  if (!found)
    cout << "Path not found." << endl;
}


// Shortest Path


template<class VertexType>
struct ItemType
{
  bool operator<(ItemType otherItem);
  // “<“ means greater distance
  bool operator==(ItemType otherItem);
  bool operator<=(ItemType otherItem);
  VertexType fromVertex;
  VertexType toVertex;
  int distance;
};


template<class VertexType>
void ShortestPath(GraphType<VertexType> graph,
     VertexType startVertex)
{
  using namespace std;
  ItemType<VertexType> item;
  int minDistance;
  QueType<VertexType> pq(10);
  QueType<VertexType> vertexQ;
  VertexType vertex;

  graph.ClearMarks();
  item.fromVertex = startVertex;
  item.toVertex = startVertex;
  item.distance = 0;
  pq.Enqueue(item);
  cout  << "Last Vertex  Destination   Distance" << endl;
  cout  << "-------------------------------------" << endl;

  do
  {
    pq.Dequeue(item);
    if (!graph.IsMarked(item.toVertex))
    {
      graph.MarkVertex(item.toVertex);
      cout << item.fromVertex;
      cout << "  ";
      cout << item.toVertex;
      cout << "  " << item.distance << endl;
      item.fromVertex = item.toVertex;
      minDistance = item.distance;
      graph.GetToVertices(item.fromVertex, vertexQ);

      while (!vertexQ.IsEmpty())
      {
        vertexQ.Dequeue(vertex);
        if (!graph.IsMarked(vertex))
        {
          item.toVertex = vertex;
          item.distance = minDistance +
              graph.WeightIs(item.fromVertex, vertex);
          pq.Enqueue(item);
        }
      }
    }
  } while (!pq.IsEmpty());
}


// Main


int main()
{
    int maxValue = 5;

    //creating graph
    GraphType<char> graph(maxValue);
    string vertexName;

    //vertices from 'A' to 'E'
    for (int i = 0; i < maxValue; i++)
    {
        char ch = i+'A';
        graph.AddVertex(ch);
    }

    //add edges
    graph.AddEdge('A','B', 2);
    graph.AddEdge('A','D', 2);
    graph.AddEdge('B','E', 1);
    graph.AddEdge('B','C', 4);
    graph.AddEdge('C','E', 3);
    graph.AddEdge('D', 'E', 3);
  
    //checking for edge from 'A' to 'D'

    cout << "Checking edge A-D : ";

    if (graph.EdgeExists('A', 'D'))
    {
        cout << "Edge from 'A' to 'D' exists\n" << endl;
    }
    else
    {
        cout << "Edge from 'A' to 'D' does not exist\n" << endl;
    }

    //Deleting edge A->D
    cout << "Deleting edge A->D\n" << endl;
    graph.DeleteEdge('A', 'D');

    //Checking edge A->D
    cout << "Checking edge A->D : ";

    if (graph.EdgeExists('A', 'D'))
    {
        cout << "Edge from 'A' to 'D' exists" << endl;
    }
    else
    {
        cout << "Edge from 'A' to 'D' does not exist\n" << endl;
    }

    
    cout << "Checking edge B->C : ";

       if (graph.EdgeExists('B', 'C'))
       {
           cout << "Edge from 'B' to 'C' exists\n" << endl;
       }
       else
       {
           cout << "Edge from 'B' to 'C' does not exist\n" << endl;
       }

       //Deleting edge B->C
       cout << "Deleting edge B->C\n" << endl;
       graph.DeleteEdge('B', 'C');

       //Checking edge B->C
       cout << "Checking edge B->C : ";

       if (graph.EdgeExists('B', 'C'))
       {
           cout << "Edge from 'B' to 'C' exists" << endl;
       }
       else
       {
           cout << "Edge from 'B' to 'C' does not exist\n" << endl;
       }
    system("pause");
    return 0;
}

/*
 Checking edge A-D : Edge from 'A' to 'D' exists

 Deleting edge A->D

 Checking edge A->D : Edge from 'A' to 'D' does not exist

 Checking edge B->C : Edge from 'B' to 'C' exists

 Deleting edge B->C

 Checking edge B->C : Edge from 'B' to 'C' does not exist

 sh: pause: command not found
 Program ended with exit code: 0
 */
