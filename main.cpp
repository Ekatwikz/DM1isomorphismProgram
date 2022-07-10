#include <iostream>
#include "graph.h" // my definitions are here and in the other .cpp files

using std::cout;

int main() {
	// Simple example:
	/*
		0 - 1
		    |
		    |
		2   3
	*/
	Graph graph1 {"0100,1001,0000,0100"};

	/*
		0   1
		|  /
		| /
		2   3
	*/
	Graph graph2 {"0010,0010,1100,0000"};

	cout << graph1 << graph2 << (graph1 == graph2 ? "True" : "False") << "\n\n";
	
	
	// Common pentagon-pentagram example:
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
}
