<style>
    .figure
    {
        font-size:70%;
        font-weight:bold;
    }
    .source
    {
        font-size:60%;
        font-style:italic;
        /*font-weight:bold;*/
    }
</style>

# Finding the shortest path
### 1. Introduction
Finding the shortest path is useful in many situations, for example: Finding your way home from an unknown location, or making an enemy walk towards a player in a videogame.

These matters can be calculated by the use of algorithms. The algorithms looked at in this study are Dijkstra and A*.



### 2. Dijkstra
Dijkstra's algorithm works with graphs. Graphs are made of vertices and edges. Each edge connects two vertices and each vertex can be connected with multiple other vertices.

Dijkstra's algorithm works with the principle of relaxation. At first the distance of every vertex to the root vertex is overestimated and as the algorithm runs it gets a better and better estimation of what the distance between the root vertex and every other vertex is. Once the algorithm is finished it should have the distance between every vertex and root vertex calculated, and should be able to find a path from every vertex to the root vertex.

#### 2.1 The input file
First a small explanation of the input file is needed.
```
c 9th DIMACS Implementation Challenge: Shortest Paths
c http://www.dis.uniroma1.it/~challenge9
c TIGER/Line graph USA-road-d.NY
c
p sp 264346 733846
c graph contains 264346 nodes and 733846 arcs
c
a 1 2 803
a 2 1 803
a 3 4 158
a 4 3 158
a 5 6 774
a 6 5 774
a 7 8 1531
a 8 7 1531
a 9 10 1673
a 10 9 1673
a 9 11 1400
a 11 9 1400
```
<p class="figure">Figure 1, Small portion of the input file.</p>

An 'a' at the front of a line in the input file indicates that the line stores a path. So, in the program any line that does not begin with 'a' can be ignored. 

If a line is a path it follows a structure: name of the node, the node it is connected to and then the distance between the nodes.

One line also only indicates one way direction. So if two nodes are traversable in two directions, then two lines will be needed, an example can be seen in figure 1, node 1 and 2 are bi directional so they need two lines.


```
// the structure of a path
a node_name node_connection distance
```

#### 2.2 Our implementation
The implementation used for this study is split into 4 parts and 3 cpp files. First it reads the lines of the input file and creates paths from it, second it creates the graph from the paths, third it creates a Dijkstra list and performs the Dijkstra algorithm, and fourth it prints out all the shortests paths from every node to the root node to an output.txt file.

##### Part 1: Creating the path objects

![](https://i.imgur.com/xeiS5o3.png)

<p class="figure">figure 2, the class used to create path objects.</p>

The function called read_destribute creates a dynamically allocated vector of path objects and returns a pointer to this vector, see figure 2.

![](https://i.imgur.com/T66IZCa.png)


<p class="figure">figure 3, read_distribute function.</p>


```cpp=
// called in main.cpp
// vector list of paths is created
std::vector<path> *paths = read_distribute(file);
```

##### Part 2: Creating the graph

There are three classes at work to create the graph.

![](https://i.imgur.com/DOVZVgO.png)

<p class="figure">Figure 4, node class.</p>

The node class, seen on figure 4, holds the name of the node and also a vector of node destinations, see Figure 5.

![](https://i.imgur.com/TieQF3v.png)

<p class="figure">Figure 5, node_destination class. Holds the distance to a node, and points to what node its going.</p>

Lastly the graph class creates the graph by connecting nodes with node_destinations and adds the nodes to a vector for easy access. It does this with the use of the previously made paths vector. It will therefor ask for a vector of paths to construct a graph.

```cpp=
// called in main.cpp
// graph is created
graph g{*paths};
```

![](https://i.imgur.com/y7jGFzx.png)

<p class="figure">Figure 6, Graph constructor.</p>

![](https://i.imgur.com/D2J831G.png)

<p class="figure">Figure 7, Exists function, looks through graph to see if a node object already exists, if it does it returns a pointer to it, else gives back nullpointer.</p>


In the graph constructor, see figure 6, it goes through the list of paths it has been given and create nodes if they dont exists yet, see figure 7, and connect node destinations to their nodes. Then it adds the node to its vector for easy access.

##### Part 3: Creating Dijkstra lists

A Dijkstra list in the context of this study refers to a vector list of Dijkstra objects. Dijkstra objects refer to a node and also holds more information. The information it holds is: the distance from the node to the root node, and if it has been visited before, see figure 8. 

![](https://i.imgur.com/5SoNAic.png)

<p class="figure">Figure 8, The Dijkstra class, points to a node and stores the distance to root node and if it has been visited for relaxation.</p>

When a Dijkstra list object is created it asks for a root node and for a graph.
```cpp=
// called in main.cpp
// dijkstra list object is created, root node given is the first node in the graph and the graph itself is also given.
dijkstra_list d{g.get_graph()->at(0), g};
```

When the Dijkstra list is initialized it creates all the Dijkstra objects, see figure 8, putting their initial distance to the root node to the max number an integer can hold. The only node it doesn't do this for is the root node, whose value is put to 0. See figure 9.

![](https://i.imgur.com/cx7H7Cs.png)

<p class="figure">Figure 9, Initializing the Dijkstra list for relaxation</p>

Once the Dijkstra lijst had been made the Dijkstra routine can be called.

```cpp=
// called in main.cpp
// calls the Dijkstra relaxation routine. Has the correct distance values after the routine.
d.dijkstra_routine();
```

![](https://i.imgur.com/CoyuFJA.png)

<p class="figure">Figure 10, Dijkstra routine, goes through every node and relaxes them.</p>

See figure 10, the Dijkstra routine goes through every node, looks at its neighbours that haven't been visited yet, and relaxes their distance if necessary. If a distance is relaxed then the node from which this is done is also remembered. This is so at the end when the shortest path is asked of any node it can follow the train of previous node pointers until it gets to the root node, see figure 11. 

![](https://i.imgur.com/fJ0WmBI.png)

<p class="figure">Figure 11, Example of how previous node helps create a path.</p>
<p class="source">Source: Youtube | Graph Data Structure 4. Dijkstra’s Shortest Path Algorithm by Computer Science</p>

The lines in this part of the code can get very long as can be seen in figure 10. A more neat implementation could have been made and that is something that we will take into consideration for the next study.

##### Part 4: printing the results

![](https://i.imgur.com/YFU0vOj.png)

<p class="figure">Figure 12, function to print all the distances to output.txt</p>

To print all the distances and paths to a text file the function mentioned in figure 12 will go through all the nodes, print out the path by following the previous nodes until the root node. And also print out the stored distance to root node.

When trying to do this to the big input file we found out that it would take very very long to complete. We stopped printing values to the output.txt file after 2 days of running the program and we expect that to fully print out all values we would have needed to let the program run for 7 more days. We think that there are a few reasons for why this takes so long. Firstly the initial setting up of the graph and Dijkstra list make use of a ton of for loops that go through all entries, Secondly we use vectors for almost all storing of information, thirdly we do not really make any use of const to save processing time, fourthly outputting just takes a lot of time we have noticed. The setting up of the graph, and Dijkstra list took about 8 hours to complete. The rest of the time it was printing out the paths and distances from nodes. 

Getting the direction from any singular node would be really quick, once you had the programming running for 8 hours to set up the graph and do the Dijkstra algorithm, but printing out everything just takes a while. 

Even though we cut off the process of printing, we have a pretty big file of the first 80.000 nodes. This one can be found in the github as a zip file.
```
path to output.zip
shortest_path/shortest path/cmake-build-debug/output.zip
```

### 3. A*

#### 3.1 Introduction

The A* algorithm can be seen as an addition to Dijkstra's Algorithm. It's also created to find the shortest path from one node to another. But with A*, something is added to find the shortest path even faster than Dijkstra.
Thats why we've also decided to look into A*.

#### 3.2 How it works

Like Dijkstra, A* works with graphs based on vertices and edges. By relaxing vertices and holding value's of the distance per vertex, the shortest path is found.

The difference however is that A* uses two more values per vertex to establish the linear distance between the end node and every other node in the graph.

Now every "seen" vertex (vertices that are connected to explored ones) holds 3 values. G, wich stands for the distance from the starting node. This is the same value Dijkstra's algorithm holds. H, wich is the value that holds the linear distance of the selected node to the end node. And F, wich is the sum of G and H.

Now when exploring the graph with A*, the node with the lowest F value will be the first visited. When two or more nodes hold the same F value, the node with the lowest H value will be visited first, since it is the closest to the end node.

With these extra values, some problems where there is a huge graph involved are much easier fixed because the linear value points the pathfinding in the right direction (most of the time).

#### 3.3 Implementation
Because of some complications (see 4. Complications) we weren't able to implement any code for the A* algorithm. Thats why we decided to just research it.


### 4. Complications
Before the study of these algorithms we studied a different subject called Boost your C++. We couldn't figure out the errors we were having while compiling programs using the Boost libraries. One week before due we decided to change our focus on the current subject.

After the switch to 'finding the shortest path' the biggest complication was time. Both in the amount we had to finish the study, and also with how long running the program would take.

### What we have learned
With this study we actually learned quite a lot. Besides learning about the algorithms, we learned how important immedietly optimizing your code can be. And considering that we will most likely do our next study on another algorithm based study 'minimizing losses, maximizing profits' we will take these things we have learned into consideration from the start.