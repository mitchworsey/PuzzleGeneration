NAME: Mitch Worsey

Project 2 README

For Project 2, I was able to implement all puzzle evaluation criteria, which includes: solution length, number of black holes, number of white holes, number of forced forward moves, number of forced backward moves, and if there is a unique shortest solution. I used the scoring function provided in the Project file.

In order to generate the best possible puzzle, I used a form of hill climbing. In my algorithm, it begins with a completely randomly generated puzzle (random values within the range for each state). It then randomly picks any neighbor in the puzzle (excluding the goal state), and assigns it a random value that is different than its previous value. If this temporary puzzle generates a higher score than the previous best puzzle, then it moves to this temporary puzzle and sets it as the new best puzzle. If this temporary puzzle does not generate a higher score than the previous best puzzle, it will assign a new random value (specifically, a value that has not been tried yet) to the same state and compare puzzle scores again. If all possible values were tried with a particular random state and none produced a higher-scoring puzzle, then it will randomly pick a new neighbor in the puzzle, and repeat the same process.

It continues to repeat this process as many times as possible within the 60 seconds provided. Also, after every 15 seconds, my algorithm will automatically generate an entirely new, randomly-formed puzzle; this function serves to create random restarts throughout the hill climbing process, helping my algorithm escape local maximum as well as improving my chances of generating a better puzzle.


