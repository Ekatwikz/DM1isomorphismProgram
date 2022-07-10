#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>

using std::ostream;
using std::string;
using std::vector;

class Graph {
private:
	size_t size;
	vector<vector<bool>> adjacency; // sizez*size square adjacency matrix

public:
	Graph(string adjacencyString = "");
	
	[[nodiscard]] vector<bool> operator[](int pos) const;
	friend ostream& operator<<(ostream& stream, const Graph& graph);
	[[nodiscard]] friend bool operator==(const Graph& lhs, const Graph& rhs);
};

#endif // GRAPH_H