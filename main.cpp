#include <iostream>
#include "graph.h" // the rest of my definitions are here and in graph.cpp

using std::cout;
using std::swap;

// We'll say that equality should also be true if an isomorphism exists
[[nodiscard]] bool operator==(const Graph& lhs, const Graph& rhs) {
	if (lhs.size != rhs.size)
		return false; // Can't have an isomorphism between differently sized graphs
	
	// Check for trivial equality:
	bool foundPermutation = true;
	for (int j = 1; foundPermutation && j < lhs.size; ++j) {
		// We only need to check left of the diagonal because our matrices should have symmetry along it,
		// and the diagonal is also assumed to strictly contain 0s, so we can do j=1 and check onl k<j
		for(int k = 0; k < j; ++k) {

			if (lhs[j][k] != rhs[j][k]) {
				foundPermutation = false;
				break;
			}
		}
	}
	
	// pseudoStack is an encoding of the stack state. pseudoStack[i] encodes the loop counter for when generate(k - 1, perm) is called
	int* pseudoStack = new int[lhs.size];
	int* perm = new int[lhs.size];

	for (int i = 0; i < lhs.size; ++i) {
		pseudoStack[i] = 0;
		perm[i] = i;
	}

	// And then check if a permutation is necessary,
	// I use a version of Heap's algorithm (https://en.wikipedia.org/wiki/Heap%27s_algorithm) to go through all n! permutations
	// i acts similarly to a stack pointer for pseudoStack here
	for (int i = 1; !foundPermutation && i < lhs.size;) {
		if (pseudoStack[i] < i) {
			if (i % 2)
				swap(perm[pseudoStack[i]], perm[i]);
			else
				swap(perm[0], perm[i]);

			foundPermutation = true;
			for (int j = 1; foundPermutation && j < lhs.size; ++j) {
				// We only need to check left of the diagonal because our matrices should have symmetry along it,
				// and the diagonal is also assumed to strictly contain 0s, so we can do j=1 and check onl k<j
				for(int k = 0; k < j; ++k) {

					if (lhs[j][k] != rhs[perm[j]][perm[k]]) {
						foundPermutation = false;
						break;
					}
				}
			}
			
			// Swap has occurred ending the loop. Simulate the increment of the loop counter
			++pseudoStack[i];
			// Simulate recursive call reaching the base case by bringing the pointer to the base case analog in the array
			i = 1;
		} else {
			// Calling generate(i+1, perm) has ended as the loop terminated. Reset the state and simulate popping the stack by incrementing the pointer.
			pseudoStack[i] = 0;
			++i;
		}
	}
	
	if (foundPermutation) {
		for (int i = 0; i < lhs.size; ++i)
			cout << i << "->" << perm[i] << ", ";
		cout << "\n";
	}

	return foundPermutation;
}

int main() {
	// Simple example:
	/*
		0 - 1
			|
			|
		2	3
	*/
	Graph graph1 {"0100,1001,0000,0100"};

	/*
		0   1
		|  /
		| /
		2	3
	*/
	Graph graph2 {"0010,0010,1100,0000"};

	cout << graph1 << graph2 << (graph1 == graph2 ? "True" : "False") << "\n\n";
	
	
	// Popular pentagon-pentagram example:
	graph1 = {"01001,10100,01010,00101,10010"}; // Pentagon
	graph2 = {"00110,00011,10001,11000,01100"}; // Pentagram
	cout << graph1 << graph2 << (graph1 == graph2 ? "True" : "False") << "\n\n";
	
	
	// A pair of Visually "similar" but non-isomorphic graphs:
	/*
	0 ------3
	|\      |
	| 1 - 2 |
	| |   | |
	| 5 - 6 |
	|      \|
	4 ----- 7
	*/
	graph1 = {"01011000,10100100,01000010,10000001,10000001,01000010,00100101,00011010"};
	
	/*
	0 ------3
	|\      |
	| 1 - 2 |
	| |   | |
	| 5 - 6 |
	|/      |
	4 ----- 7
	*/
	graph2 = {"01011000,10100100,01000010,10000001,10000101,01001010,00100100,00011000"};
	
	cout << graph1 << graph2 << (graph1 == graph2 ? "True" : "False") << "\n";

	return 0;
}