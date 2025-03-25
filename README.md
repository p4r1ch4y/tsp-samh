## a C++ Program which finds optimal TSP (Travelling Sales Man Problem) tour using Simulated Annealing Meta Heuristics.

## What is TSP and How it works Explain me like i'm 5 ELI5


# How the Traveling Salesman Solver Works for a 5-Year-Old



imagine you have a bunch of cities on a map, and you want to visit all of them without going to the same city twice, and then return home. You want to find the shortest path to save time right?



## Howw it works?



This C++ program is like a smart helper that tries to find the shortest path through all the cities. Here's how it works:



# Step 1

First, we tell the computer where all the cities are by giving it a file with the locations. The computer reads this file and makes a map in its memory.



# Step 2: Starting with a Random Path

The computer starts by picking any random order to visit the cities - like picking cities out of a hat

# Step 3: The Magic Trick - Simulated Annealing


Now comes the clever part! The computer uses something called "Simulated Annealing" which is like playing a game:

1. The computer looks at its current path
2. It swaps two random cities in the path 
(like saying "what if I visit City B before City A instead?")


3. It checks if the new path is shorter
   - If it's shorter: "Yay! I'll use this new path!"
   - If it's longer: "Hmm, maybe I'll still try it..." (especially early in the game)

# Step 4: Getting Pickier Over Time


At the beginning, the computer is willing to try lots of different paths, 
even if they're not great. This is like exploring different routes.

As time goes on, 
the computer gets pickier and mostly sticks with changes 
that make the path shorter. 
This is like focusing on the best route once you've explored a bit.


# Step 5: Finding the Answer

After trying 10,000 different paths, 
the computer shows us the best path it found 
and tells us how long that path is.

# The Special Sauce

The really cool thing about this program is
 that it's like a kid who's willing to try "wrong turns" sometimes. 
 This helps it avoid getting stuck with a "kind of good" path 
 when there might be a much better path if it tries something different first!

It's like if you're looking for treasure - sometimes you need to look in a few wrong places before you find the right spot

## Now the Technical Part

How the program works 

-> Reads city coordinates from the TSP format file

-> Generate a random initial tour

-> Set initial temperature and cooling rate


## How the Algorithm Works



## Distance Calculation


- Euclidean distance between cities is calculated using the formula:
  ```
  distance = sqrt((x2-x1)² + (y2-y1)²)
  ```

Acceptance Probability
- The probability of accepting a worse solution is:
  ```
  P = exp(-deltaLength/temperature)
  ```
- This probability decreases as the temperature decreases, focusing the search on better solutions in later iterations



The implemented Simulated Annealing algorithm for TSP works by this way


 -> Reads city coordinates from the TSPLIB format file
   - Generates a random initial tour
   - Sets initial temperature and cooling rate

 For a fixed number of iterations (10,000) :

     - Generates a neighbor solution by swapping two random cities
     - Calculate the change in tour length (delta)
     - Accept the new solution if it's better (delta < 0)
     - Otherwise, accept with probability exp(-delta/temperature)
     - Update the best solution if the current one is better
     - Decreasses the temperature according to the cooling rate



. **Output**:

   - Prints the best tour found and its length

Program Output looks like this : 

Here's an example of how the output of the program might look:

```
Loaded 131 cities from xqf131.tsp
Running Simulated Annealing with:
Initial Temperature: 10000.0
Cooling Rate: 0.99995
Iterations: 10000
Iteration 0: Best length = 578.0
Iteration 1000: Best length = 566.0
Iteration 2000: Best length = 562.0
Iteration 3000: Best length = 559.0
Iteration 4000: Best length = 557.0
Iteration 5000: Best length = 555.0
Iteration 6000: Best length = 554.0
Iteration 7000: Best length = 553.0
Iteration 8000: Best length = 552.0
Iteration 9000: Best length = 551.0

Final Results:
Best tour length: 551.0
Best tour: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 
Execution time: 2.5 seconds
```





### Explanation of the Code

1. **Includes and Namespace**:
   - `#include <bits/stdc++.h>`: Includes all C++ standard libraries, simplifying the code.

2. **City Structure**:
   - Represents a city with an ID and coordinates (`x`, `y`).

3. **Distance Calculation**:
   - Computes the Euclidean distance between two cities using the Pythagorean theorem.

4. **Tour Length**:
   - Calculates the total distance of a tour by summing up distances between consecutive cities.

5. **Swap Cities**:
   - Randomly swaps two cities in the tour to generate a new candidate solution.

6. **Read Cities**:
   - Reads city data from a file in the TSP format. Handles parsing and converts IDs to 0-based indexing.

7. **Simulated Annealing**:
   - Implements the Simulated Annealing algorithm:
     - Starts with a random tour.
     - Iteratively generates new tours by swapping cities.
     - Accepts new tours based on a probability function or if they improve the solution.
     - Gradually reduces the temperature to decrease the probability of accepting worse solutions.

8. **Main Function**:
   - Reads the input file and initializes parameters for Simulated Annealing.
   - Runs the algorithm and measures execution time.
   - Outputs the best tour and its length.



 
## Usage

Compile the program and run it with the path to a TSP file ( Keep the tsp file and this cpp file in same path ) :



```
g++ -O3 -std=c++11 tsp_program.cpp -o tsp_sa


./tsp_sa xqf131.tsp
```


The program will output the best tour found and its length after running for 10,000 iterations.


Thanks and credit to OpenSource and LLMs for assistance. 
