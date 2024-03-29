# Software Entwicklung und Praktikum 2016

## Short Declaration about the Project:
The game to be implemented is a modified version of the maze of Pokemon.
The goal of the game is to reach the goal from the starting field. To achieve the goal,
the player has a limited number of steps available. 
In the maze, there are special fields, that make it easier for the player to reach the goal,
but there are also fields, that make it harder. 
There may also be several ways to get to the goal.

## Field types
* '#'          => Wall
* ' '          => Path
* 'o'          => Start Field
* 'x'          => Goal Field
* '+'          => Ice Field
* 'A-Z'        => Teleport Field
* '>, <, ^, v' => One Way Field 
* 'a-e'        => Bonus Field
* 'f-j'        => Quicksand Field

A maze can look like:


![alt text](https://github.com/heinzi1991/SEP/blob/master/Images/OneMaze.png "Possible Maze")


This maze can find in the folder with the name Mazes


## Commands
* **load [filename]**            => load a new maze from filename
* **save [filename]**            => save the maze with the filename
* **fastmove [series of steps]** => make a series of steps (steps are: u [up], d [down], l [left], r [right])
* **move [direction]**           => make one move in the direction (directions are: up, down, left, right)
* **show**                       => show the maze, with the paramter [more] it shows also the remaining steps and the moved steps
* **reset**                      => reset the maze
* **quit**                       => quit the game

#### Any Questions or Suggestions
martin.zagar@student.tugraz.at



