#include "graph.h"

// This file has my basic Graph representation definitions,
// the more interesting isomorphism algorithm is in the file
// of the same name

Graph::Graph(string adjacencyString) : size{adjacencyString.find(",")}, adjacency{size, vector<bool>()} {
	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size; ++j) {
			adjacency[i].push_back(adjacencyString[i * (size + 1) + j] == '1');
		}
	}
}

[[nodiscard]] vector<bool> Graph::operator[](int pos) const {
	return adjacency[pos];
}

ostream& operator<<(ostream& stream, const Graph& graph) {
	for (size_t i = 0; i < graph.size; ++i) {
		for (size_t j = 0; j < graph.size; ++j) {
			stream << graph[i][j];
		}

		stream << "\n";
	}

	return stream << "\n";
}
