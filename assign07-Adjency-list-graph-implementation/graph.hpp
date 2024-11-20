#pragma once
#ifndef GRAPH_HPP
#define GRAPH_HPP
/*
 * Name: Vo Nguyen
 * Date: July 9, 2020
 * graph.hpp
 * Adjency-list graph implementation
 */

 #include <climits>				//For INT_MAX, INT_MIN
 #include <list>
 #include <vector>
 #include <queue>

class graph {
	public:
		/* graph(n)
		   Construct a graph with n nodes and no edges, initially
		*/
		graph(int n)
		{
			numVertices = n;
			adjList = new std::list<int>[n];
		}

		// Check if the edge from a to b exists
		bool exists(int a, int b)
		{
			for (int node : adjList[a])
			{
				if (node == b){
					return true;
				}
			}
			
			return false;
			
		}
		
		/* add_edge(a,b)
		   Add an edge from node a to node b. Note that self edges are not allowed,
		   so attempting add_edge(a,a) should be ignored. Similarly, this is not 
		   a multigraph, so if an edge a->b already exists, a seconed one should
		   be ignored.
		   Should run in O(E) time in the worst case.
		*/
		void add_edge(int a, int b)
		{
			if (a != b )
			{
				bool exist = exists(a, b);
				if (exist == false) 
				{
					adjList[a].push_back(b); 
					countEdges++;
				}
			}
		}

		/* has_edge(a,b)
		   Returns true if there is an edge from a to b. Should return false if
		   either a or b is out-of-range (<0 or >= count_nodes()).
		   Should run in O(E) time.
		*/
		bool has_edge(int a, int b)
		{
			if (a < 0 or b < 0 or a >= count_nodes() or b >= count_nodes())
				return false;

			return exists(a,b);
		
		}

		/* count_nodes()
		   Returns the number of nodes in this graph.
		   Should run in O(1) time
		*/
		int count_nodes()
		{
			return numVertices;
		}

		/* count_edges()
		   Returns the total number of edges in this graph.
		   Should run in O(E) time.
		*/
		int count_edges()
		{
			return countEdges;
		}

		/* count_edges(n)
		   Returns the number of outbound edges from node n.
		   Should run in O(E) time
		*/
		int count_edges(int n)
		{
			return adjList[n].size();
		}

		/* bfs(n)
		   Perform a breadth-first search, starting at node n, and returning a
		   vector that gives the distance to every node. (it a node is
		   unreachable from n, then set its distance to INT_MAX)
		   Should run in O(E + N) time.
		*/
		std::vector<int> bfs(int n)
		{
			std::vector<int> distances(count_nodes(), INT_MAX);
			std::queue<int> q;

			q.push(n);
			distances[n] = 0;
			
			while (!q.empty())
			{
				int a = q.front();
				q.pop();

				for (int b : adjList[a])
				{
					if (has_edge(a,b) and distances[b] == INT_MAX)
					{
						q.push(b);
						distances[b] = distances[a]+1;
					}
				}	
			}

			return distances;
		}

		/* is_connected(a,b)
		   Returns true if a path exists from node a to b.
		   Should run in O(E + N) time.
		*/
		bool is_connected(int a, int b)
		{
			return bfs(a)[b] != INT_MAX;
		}
		
	private:
		int numVertices;
		int countEdges = 0;
		std::list<int> *adjList;
};


 #endif