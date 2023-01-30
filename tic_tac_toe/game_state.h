#pragma once

#include <vector>

#include "state.h"
#include "cell.h"
#include "config.h"

class GameState :
    public State {
private:
    std::vector<std::vector<Cell>> _cells;
    sf::RectangleShape _background;
    sf::Sprite _playerVisualizer;
    sf::Sprite _replayButton;
    Cell::CellStatus _currentPlayer;
    bool _endGame;

    const std::vector<std::pair<sf::Vector2i, sf::Vector2i>> _possibilities{
        std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(-2, 0), sf::Vector2i(-1, 0)),
        std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(-1, 0), sf::Vector2i(1, 0)),
        std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(1, 0), sf::Vector2i(2, 0)),
        std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, -2), sf::Vector2i(0, -1)),
        std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, -1), sf::Vector2i(0, 1)),
        std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(0, 1), sf::Vector2i(0, 2)),
        std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(-2, -2), sf::Vector2i(-1, -1)),
        std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(-1, -1), sf::Vector2i(1, 1)),
        std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(1, 1), sf::Vector2i(2, 2)),
        std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(2, -2), sf::Vector2i(1, -1)),
        std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(1, -1), sf::Vector2i(-1, 1)),
        std::pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(-1, 1), sf::Vector2i(-2, 2)),
    };

    void checkCollision();
    void changePlayer();
    void updatePlayerVisualizer();
    void checkIfWin(sf::Vector2i position);
    bool isInBoard(sf::Vector2i position);
    void resetGame();

public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states);

    void initCells();

    virtual void start() override;
    virtual void updateEvent(sf::Event event) override;
    virtual void update() override;
    virtual void render() override;
    virtual void end() override;
    virtual void switchState() override;
};

