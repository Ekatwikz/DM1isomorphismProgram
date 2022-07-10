#include "graph.h"

Graph::Graph(string adjacencyString) : size{adjacencyString.find(",")}, adjacency{size, vector<bool>()} {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j)
			adjacency[i].push_back(adjacencyString[i*(size + 1) + j] == '1');
	}
}

[[nodiscard]] vector<bool> Graph::operator[](int pos) const {
	return adjacency[pos];
}

ostream& operator<<(ostream& stream, const Graph& graph) {
	for (int i = 0; i < graph.size; ++i) {
		for(int j = 0; j < graph.size; ++j)
			stream << graph[i][j];

		stream << "\n";
	}

	return stream << "\n";
}