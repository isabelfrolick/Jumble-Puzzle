# JumblePuzzle Game

Fun project This project implements JumblePuzzle class in ISO C++.

The game generates a 2D puzzle with a hidden word and random lowercase letters, playable at three difficulty levels, without any GUI.

---

## Overview

The **JumblePuzzle** class allows users to:

- Create a square puzzle array containing a hidden word of 3–10 characters.
- Select difficulty:  
  - `easy` → 2× word length  
  - `medium` → 3× word length  
  - `hard` → 4× word length
- Hide the word in a random row and column, in one of four directions: north, south, east, west.  
- Play the puzzle against the clock (console-based).  

The puzzle is stored dynamically on the heap as a **2D array of characters (`char**`)**, with proper memory management (Big Three: destructor, copy constructor, assignment operator).

---

### Puzzle Generation
- Random placement of the hidden word  
- Random lowercase letters filling remaining positions  
- Word placement validated to ensure it fits in the chosen direction  
- Sizes based on difficulty levels  

### Memory Management
- Puzzle array stored on the heap (`char**`)  
- Destructor deletes all allocated memory  
- Copy constructor prevents aliasing  
- Assignment operator implements deep copy  

### Public Interface
- Constructor to initialize puzzle with word and difficulty  
- Destructor  
- Copy constructor  
- Assignment operator  
- Accessor methods:  
  - `getSize()` → puzzle size  
  - `getRowPos()` → starting row of the word  
  - `getColPos()` → starting column of the word  
  - `getDirection()` → direction of the hidden word  
  - `getPuzzle()` → returns the puzzle array  
- Display function to print the puzzle  
- Unit testing integrated in `testJumble()`  

---

## How to Run

Compile the test program with your implementation:

```bash
g++ -std=c++11 jumble.cpp JumblePuzzle.cpp -o jumble
./jumble
