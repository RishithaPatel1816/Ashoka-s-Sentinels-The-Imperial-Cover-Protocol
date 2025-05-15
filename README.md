# Imperial Surveillance System - Sentinel Deployment for Mauryan Empire

## Description
This project models the deployment strategy of Emperor Ashoka’s sentinels across a tree-structured empire.  
It calculates the minimum number of active sentinels required to monitor all roads (edges), sorts sentinels by military rank,  
and counts how many sentinels outrank a given sentinel, using object-oriented design and efficient tree dynamic programming.

---

## Features
- Abstract base class `Sentinel` with derived classes:
  - `Senapati`
  - `Dandanayaka`
  - `Chaturangini`
- Rank hierarchy enforced in comparisons:  
  **SENAPATI > DANDANAYAKA > CHATURANGINI**
- Tree data structure representing empire outposts connected by roads
- Minimum Vertex Cover algorithm on trees using DP to find minimum sentinels required
- Custom comparator for sorting sentinels by rank and ID
- Query handling for:
  - Minimum active sentinels count
  - Sorted sentinel list by rank
  - Count of higher-ranked sentinels than a given sentinel

---

## Design

### Classes

- **Sentinel** (abstract base class)  
  Fields: `id`, `name`, `rank`  
  Pure virtual method: `countHigherRanked()`  
  Overloaded operators for comparison and sorting

- **Senapati** (inherits Sentinel)  
- **Dandanayaka** (inherits Sentinel)  
- **Chaturangini** (inherits Sentinel)  

- **Kingdom<NodeType>**  
  - Stores adjacency list of the tree  
  - Stores sentinel objects assigned to nodes by id  
  - Implements DP for minimum vertex cover on the tree  
  - Supports adding edges (roads)

### Comparator
- Functor ordering sentinels by rank and id:  
  SENAPATI > DANDANAYAKA > CHATURANGINI  
  If ranks equal, smaller ID is considered higher

### Algorithms
- Minimum Vertex Cover on Tree using DFS and DP:  
  - `dp[node][0]`: minimum sentinels when node is NOT selected  
  - `dp[node][1]`: minimum sentinels when node IS selected

---
- `n`: number of outposts (nodes)  
- Next `n-1` lines: edges connecting outposts  
- Next `n` lines: sentinel details at each node (0-based index)  
- Next line: `q`, number of queries  
- Queries:
  - `1` → print minimum number of active sentinels  
  - `2` → print sorted sentinel IDs by rank  
  - `3 x` → print count of sentinels strictly higher ranked than sentinel with ID `x`

---

## Output Format
- Query 1: single integer → minimum number of active sentinels  
- Query 2: space-separated IDs sorted by rank descending (higher first)  
- Query 3: single integer → count of sentinels strictly higher ranked than given sentinel

---

## Constraints
- 1 ≤ n ≤ 10^5  
- 1 ≤ q ≤ 10^3  
- Sentinel ranks: SENAPATI, DANDANAYAKA, or CHATURANGINI  
- Input graph is guaranteed to be a tree (connected, acyclic)

## Input Format
```
5
0 1
0 2
2 3
2 4
Karna SENAPATI
Vikram DANDANAYAKA
Arjun SENAPATI
Bhima CHATURANGINI
Abhimanyu SENAPATI
3
1
2
3 2
```
## Output format
```
2
0 2 4 1 3
0
```
