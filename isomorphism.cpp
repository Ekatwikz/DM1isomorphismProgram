#include "graph.h"

using std::swap;
using std::cout;

// We'll say that Graph equality should also be true if an isomorphism exists between the two
[[nodiscard]] bool operator==(const Graph& lhs, const Graph& rhs) {
	if (lhs.size != rhs.size) {
		return false; // Can't have an isomorphism between differently sized graphs
	}
	
	// Check for trivial equality:
	bool foundPermutation = true;
	for (size_t j = 1; foundPermutation && j < lhs.size; ++j) {
		// We only need to check left of the diagonal because our matrices should have symmetry along it,
		// and the diagonal is also assumed to strictly contain 0s, so we can do j=1 and check onl k<j
		for (size_t k = 0; k < j; ++k) {

			if (lhs[j][k] != rhs[j][k]) {
				foundPermutation = false;
				break;
			}
		}
	}
	
	// pseudoStack is an encoding of the stack state. pseudoStack[i] encodes the loop counter for when generate(k-1, perm) is called
	size_t* pseudoStack = new size_t[lhs.size];
	int* perm = new int[lhs.size];

	for (size_t i = 0; i < lhs.size; ++i) {
		pseudoStack[i] = 0;
		perm[i] = i;
	}

	// And then check if a permutation is necessary,
	// I use a version of Heap's algorithm (https://en.wikipedia.org/wiki/Heap%27s_algorithm) to go through all n! permutations
	// i acts similarly to a stack pointer for pseudoStack here
	for (size_t i = 1; !foundPermutation && i < lhs.size;) {
		if (pseudoStack[i] < i) {
			if (i % 2) {
				swap(perm[pseudoStack[i]], perm[i]);
			} else {
				swap(perm[0], perm[i]);
			}

			foundPermutation = true;
			for (size_t j = 1; foundPermutation && j < lhs.size; ++j) {
				// We only need to check left of the diagonal because our matrices should have symmetry along it,
				// and the diagonal is also assumed to strictly contain 0s, so we can do j=1 and check only k<j
				for (size_t k = 0; k < j; ++k) {
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
	
	// print the permuation if we found it
	if (foundPermutation) {
		for (size_t i = 0; i < lhs.size; ++i) {
			cout << i << "->" << perm[i] << ", ";
		}

		cout << "\n";
	}

	return foundPermutation;
}
