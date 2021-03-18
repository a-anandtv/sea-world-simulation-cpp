# A Sea World Simulation in C++

A software world simulation for life at sea without a visualization. The simulation was developed as a skill demonstration for working with C++ and Object Oriented programming. This simulation currently covers 4 elements, namely Salmons, Sharks, Rocks and Sea water. This can further be improved or added upon quite easily. The world was built with following challenges and the end of the simulation returns a statistics for major events during the lifecycle of the simulation and the final state of the world.



## Challenges

* Population:
  * A percentage of the world is filled with each element
    * For eg:
      * 5% filled with Sharks
      * 10% filled with Salmons
      * 7% filled with Rocks
      * And the rest Sea water
* Life cycle:
  * The simulation happens for a number of seconds. 
    * For eg. 1000 or 1000000 seconds.
  * Every fish has an age.
    * For eg:
      * Shark has 100 seconds and Salmon 70 seconds
  * When a specific number of fishes die, a rock is formed.
    * For eg: every 1000 dead Salmon forms a rock.
  * Rocks also have age.
  * When rocks or fishes reach their age, they die or disappear.
* Movement:
  * Every second fishes move in any direction randomly: up, down, left or right, as long as the square is free of a rock.
  * Each fish has a different movement speed, as in squares per second. Also, fishes need not move straight, they can change direction whenever they want.
* Events:
  * If two fishes meet while moving, and event takes place. Fishes meet when they cross the same square in the same moment.
    * If a Shark meet a Salmon, it eats it and the Salmon dies and disappear.
    * If a Shark meet a Shark, they reproduce with a rate, for example 2 or 3. And in the same moment they produce other sharks in random locations.
    * If a Salmon meets a Salmon, they reproduce with a rate, for example 10 or 30. And in the same moment they produce other Salmon in random locations.
* Statistics:
  * Final statistics returned from the simulation:
    * How many sharks left by the end of the simulation?
    * How many Salmons left by the end of the simulation?
    * How many Rocks left by the end of the simulation?
    * How many Salmons died by the end of the simulation?
    * How many Sharks died by the end of the simulation?
    * How many Salmons created newly by the end of the simulation?
    * How many Sharks created newly by the end of the simulation?
    * How many Rocks created newly by the end of the simulation?
    * How many Salmons were eaten?
    * In general, do Salmons and Sharks live with each other in the end or one species vanish?



## Implementation and Problems with current version

Execution starts with the *one.cpp* file.

#### Current architecture:

* Class Simulation - "Encapsulates all other classes and runs the simulation"

* Class Sea - "Abstract class from which all other classes are derived"

  * Class Water - "Derived from Sea"

    ​				"Class holds default cells in sea"

  * Class Rock -  "Derived from Sea"

    ​				"Class for rocks  in sea"

  * Class Fish -  "Derived from Sea"

    ​				"Abstract class from which all other fishes are derived"

    ​				"Holds attributes common to fishes but not water or rocks"

  * Class Salmon -  "Derived from Fish"

    ​				"Holds attributes for Salmons"

  * Class Sharks -  "Derived from Fish"

    ​				"Holds attributes for Sharks"

#### *Note*

* Simulation runs for cycles rather than seconds.
* Reproduction stops if no water cells are available in sea.

#### Bugs:

* Simulation pushes a fish in the direction of execution causing it to be moved again in the same cycle (*scenerio not handled*)
* Simulation assumes that only two fishes can fall on a cell at once causing them to reproduce (*scenerio not handled*)
  * However, more than one fish can randomly move into a single cell
* Simulation does not handle cases where a fish could be surrounded by rocks when the simulation is initialized (*scenerio not handled*)
* Simulation fails for certain generated scenarios where a fish tries to move but reaches out of bounds
  * Issue is found to be in *moveTo* and *getPossibleMoves* functions



## Future Work

* A re-organisation of the OOPs structure; for eg. with a seperate class for Simulation and the main simulation run from *main()*
* A better execution of movements (probably using an additional <execution stack>)
* A design update where in fishes can decide moves and being aware of its surroundings