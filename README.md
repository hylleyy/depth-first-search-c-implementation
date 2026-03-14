🕸️ Edges, Vertices, and Other Traumas (v0.1)
---
> “Trying not to leak memory while searching for a path Euler found in 1736 without using a single byte.” — Me, at 3 AM.

This project is the result of an epic battle against pointers and graphs. The idea is to implement an algorithm that determines if a graph is Eulerian, Semi-Eulerian, or just a meaningless tangle of lines.

## What does the program do?

Basically, it takes a list of connections (edges) that you input  and resolves the following:
- **Connectivity**: It uses a Depth-First Search (DFS) to ensure the graph isn't "broken" into isolated pieces.
- **Degree Counting**: It calculates how many connections each vertex has.
- **Euler's Verdict**:
	- 0 odd vertices means it's Eulerian (a closed cycle that visits every edge exactly once).
	- 2 odd vertices means it's Semi-Eulerian (it has a path, but doesn't return to the start).
	- More than 2 means it has no Eulerian path.

## Implementation

`llist.c`: My own Linked List implementation. It even includes python-style negative indexing because counting backwards is a basic human right.

`dfs.c`: The search engine traverses the graph to make sure everything is connected.

`main.c`: The terminal interface that uses RegEx (via the SLRE library).

### Estrutura do projeto
```
src/
 ├── main.c        # Where the chaos begins
 ├── dfs.c         # Where I got lost
 └── utils/
      └── llist.c  # Segfaults and Memory Leaks
include/           # Header files
```

### How to run
If you have gcc and make installed, it's pure joy:
```
make
./graph
```
Then just type the edges in the `1, 2` format and hit Enter.

## Academic Sincerity (Post-Mortem)
Notes for refactoring: If I were to do it all over again, I change would change a couple of things.

- **Less spaghetti**: The code turned into a pasta dish faster than I planned (I didn't plan).
- **Clean Code**: I need to re-read the sections on commenting best practices. A lot of what I wrote yesterday already looks like Greek to me today.
- **Functional Programming**: I need to stop modifying things outside of scope before undefined behavior catches up with me.
