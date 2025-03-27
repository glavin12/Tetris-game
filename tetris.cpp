#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <conio.h>
#include <windows.h>

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

enum class TetrominoType { I, J, L, O, S, T, Z };

struct Tetromino {
    TetrominoType type;
    int x, y;
    std::vector<std::vector<bool>> shape;
};

std::vector<std::vector<bool>> board(BOARD_HEIGHT, std::vector<bool>(BOARD_WIDTH, false));
Tetromino currentPiece;
int score = 0;

void initializeTetromino(Tetromino& tetromino) {
    tetromino.x = BOARD_WIDTH / 2 - 2;
    tetromino.y = 0;
    switch (tetromino.type) {
        case TetrominoType::I:
            tetromino.shape = {{true, true, true, true}};
            break;
        case TetrominoType::J:
            tetromino.shape = {{true, false, false}, {true, true, true}};
            break;
        case TetrominoType::L:
            tetromino.shape = {{false, false, true}, {true, true, true}};
            break;
        case TetrominoType::O:
            tetromino.shape = {{true, true}, {true, true}};
            break;
        case TetrominoType::S:
            tetromino.shape = {{false, true, true}, {true, true, false}};
            break;
        case TetrominoType::T:
            tetromino.shape = {{false, true, false}, {true, true, true}};
            break;
        case TetrominoType::Z:
            tetromino.shape = {{true, true, false}, {false, true, true}};
            break;
    }
}

TetrominoType getRandomTetrominoType() {
    return static_cast<TetrominoType>(rand() % 7);
}

void spawnNewPiece() {
    currentPiece.type = getRandomTetrominoType();
    initializeTetromino(currentPiece);
}

bool isCollision() {
    for (size_t y = 0; y < currentPiece.shape.size(); ++y) {
        for (size_t x = 0; x < currentPiece.shape[y].size(); ++x) {
            if (currentPiece.shape[y][x]) {
                int boardX = currentPiece.x + x;
                int boardY = currentPiece.y + y;
                if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT || 
                    (boardY >= 0 && board[boardY][boardX])) {
                    return true;
                }
            }
        }
    }
    return false;
}

void mergePieceToBoard() {
    for (size_t y = 0; y < currentPiece.shape.size(); ++y) {
        for (size_t x = 0; x < currentPiece.shape[y].size(); ++x) {
            if (currentPiece.shape[y][x]) {
                board[currentPiece.y + y][currentPiece.x + x] = true;
            }
        }
    }
}

void clearLines() {
    int linesCleared = 0;
    for (int y = BOARD_HEIGHT - 1; y >= 0; --y) {
        bool lineFull = true;
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            if (!board[y][x]) {
                lineFull = false;
                break;
            }
        }
        if (lineFull) {
            ++linesCleared;
            for (int yy = y; yy > 0; --yy) {
                board[yy] = board[yy - 1];  
            }
            board[0] = std::vector<bool>(BOARD_WIDTH, false);  
            ++y; 
        }
    }
    score += linesCleared * 100;
}

void rotatePiece() {
    std::vector<std::vector<bool>> rotated(currentPiece.shape[0].size(), 
    std::vector<bool>(currentPiece.shape.size()));
    for (size_t y = 0; y < currentPiece.shape.size(); ++y) {
        for (size_t x = 0; x < currentPiece.shape[y].size(); ++x) {
            rotated[x][currentPiece.shape.size() - 1 - y] = currentPiece.shape[y][x];
        }
    }
    auto originalShape = currentPiece.shape;
    currentPiece.shape = rotated;
    if (isCollision()) {
        currentPiece.shape = originalShape;
    }
}

void drawBoard() {
    system("cls");
    std::cout << "Score: " << score << "\n";
    // Top border
    std::cout << " " << std::string(BOARD_WIDTH * 2, '_') << " \n";

    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        std::cout << "|"; // Left border
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            bool isCurrent = false;
            for (size_t pieceY = 0; pieceY < currentPiece.shape.size(); ++pieceY) {
                for (size_t pieceX = 0; pieceX < currentPiece.shape[pieceY].size(); ++pieceX) {
                    if (currentPiece.shape[pieceY][pieceX] && 
                        x == currentPiece.x + pieceX && 
                        y == currentPiece.y + pieceY) {
                        isCurrent = true;
                    }
                }
            }
            std::cout << (isCurrent ? "[]" : (board[y][x] ? "##" : "  "));
        }
        std::cout << "|\n"; // Right border
    }
    // Bottom border
    std::cout << "+" << std::string(BOARD_WIDTH * 2, '-') << "+\n";
}

void gameLoop() {
    auto lastFallTime = std::chrono::steady_clock::now();
    while (true) {
        drawBoard();
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
                case 'a': --currentPiece.x; if (isCollision()) ++currentPiece.x; break;
                case 'd': ++currentPiece.x; if (isCollision()) --currentPiece.x; break;
                case 's':
                    ++currentPiece.y;
                    if (isCollision()) {
                        --currentPiece.y;
                        mergePieceToBoard();
                        clearLines();
                        spawnNewPiece();
                        if (isCollision()) {
                            std::cout << "Game Over! Final Score: " << score << "\n";
                            return;
                        }
                    }
                    break;
                case 'w': rotatePiece(); break;
                case 'q': std::cout << "Game Over! Final Score: " << score << "\n"; return;
            }
        }
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFallTime).count() > 500) {
            ++currentPiece.y;
            if (isCollision()) {
                --currentPiece.y;
                mergePieceToBoard();
                clearLines();
                spawnNewPiece();
                if (isCollision()) {
                    std::cout << "Game Over! Final Score: " << score << "\n";
                    return;
                }
            }
            lastFallTime = currentTime;
        }
        Sleep(50);
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    spawnNewPiece();
    gameLoop();
    return 0;
}