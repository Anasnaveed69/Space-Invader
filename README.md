# Space Invaders

## Table of Contents
1. [Game Overview](#game-overview)
2. [Features](#features)
3. [Gameplay Mechanics](#gameplay-mechanics)
4. [Installation & Setup](#installation--setup)
5. [Controls](#controls)
6. [Contributing](#contributing)
7. [License](#license)

---

## Game Overview

**Space Invaders** is a classic arcade-style game recreated using C++. The player controls a spaceship at the bottom of the screen and must defend Earth from waves of alien invaders. The objective is to eliminate all the aliens before they reach the player's ship.

---

## Features

- **Classic Gameplay**: Faithful recreation of the original Space Invaders mechanics with enhancements.
- **Player Movement**: Move the spaceship left or right using arrow keys.
- **Shooting Mechanism**: Fire lasers to destroy alien invaders.
- **Alien Waves**: Enemies move side-to-side and gradually descend, increasing difficulty.
- **Scoring System**: Earn points for destroying aliens and surviving longer.
- **Game Over Conditions**:
  - Player’s ship is hit by an alien.
  - Aliens reach a certain threshold on the screen.
- **Customizable Graphics**: Simple yet visually appealing 2D graphics.
- **Sound Effects**: Retro-inspired sounds for shooting, explosions, and background music.
- **Difficulty Scaling**: Aliens move faster and become more aggressive as the game progresses.
- **Cross-Platform Support**: Compatible with multiple operating systems.
- **Open Source**: Fully documented codebase for learning game development concepts.

---

## Gameplay Mechanics

1. **Start the Game**:
   - The player controls a spaceship positioned at the bottom of the screen.
   
2. **Defend Against Alien Invaders**:
   - Aliens move in a grid pattern, gradually descending toward the player.
   - The player must shoot and destroy all aliens before they reach the bottom.

3. **Winning & Losing Conditions**:
   - The player wins by eliminating all aliens.
   - The game ends if the aliens reach the player's position or the player's ship is destroyed.

---

## Installation & Setup

### Prerequisites
- A C++ compiler (GCC, Clang, or MSVC)
- **SFML Library** (if using graphics)
- `make` (optional for build automation)

### Steps to Install & Run
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/Space-Invaders.git
   cd Space-Invaders
   ```

2. **Install Dependencies** (if using SFML):
   - On Ubuntu:
     ```bash
     sudo apt-get install libsfml-dev
     ```
   - On Windows:
     - Download SFML from the official website and set up environment variables.

3. **Compile the Code**:
   ```bash
   g++ -o space_invaders main.cpp Game.cpp Player.cpp Alien.cpp -lsfml-graphics -lsfml-window -lsfml-system
   ```

4. **Run the Game**:
   ```bash
   ./space_invaders
   ```

---

## Controls

| Action        | Key |
|--------------|-----|
| Move Left    | Left Arrow (`←`) |
| Move Right   | Right Arrow (`→`) |
| Shoot        | Spacebar (`Space`) |
| Quit Game    | Escape (`Esc`) |

---

## Contributing

We welcome contributions! To contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeatureName`).
3. Commit your changes (`git commit -m "Add YourCommitMessage"`).
4. Push to the branch (`git push origin feature/YourFeatureName`).
5. Open a pull request.

Please ensure your code adheres to the project's coding standards and includes documentation.

---

## License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---

For any issues or suggestions, feel free to open an issue or reach out to the maintainers. Happy coding! 🚀
