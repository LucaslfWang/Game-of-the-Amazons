# Game-of-the-Amazons

English | [中文](README-CN.md)

## Introduction
The **Game of the Amazons** was invented by Walter Zamkauskas (Argentina) in 1988.  
It was once chosen as the official competition game for the Computer Olympiad due to its complexity.  

With more than 2,700 possible opening moves, the game is rarely played between humans. Instead, it is widely studied in **AI research and computer game competitions**.

---

## Rules
- **Board**: 10×10 grid of alternating black and white squares, with a white square at each player’s bottom-right corner.  
- **Pieces**: Each player starts with 4 Amazons.  
- **Gameplay**:  
  1. Each Amazon moves like a chess queen, along 8 directions (vertical, horizontal, diagonal) without passing through obstacles.  
  2. On each turn, a player **must** move one Amazon and then **must** shoot an arrow. The arrow travels like the Amazon and occupies its landing square permanently, acting as a new obstacle.  
  3. A player loses when, after the opponent’s move, none of their Amazons can move.  
  4. The player at the bottom (traditionally White) always moves first.  
  5. Neither Amazons nor obstacles can be captured or removed during the game.
![image](https://github.com/LucaslfWang/Game-of-the-Amazons/assets/67529039/b70cc85d-59ec-4cdf-8298-1ce8ff88febe)


---

## Project Structure
- `Searchengine/`: Search functions  
- `evaluationfunction/`: Evaluation functions  
- `movegenerator/`: Piece movement control  

---

## How to Run
1. Clone the repository:
   ```bash
   git clone <repo-url>
2. Compile the source code or run the prebuilt exe to start a game.

## Notes
This repository was developed for the 2018 Beijing University of Technology Computer Game Competition - Amazons Track.
Special thanks to @Liu Wenrui for support and contributions.


