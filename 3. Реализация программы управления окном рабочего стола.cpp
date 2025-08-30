#include <iostream>
#include <string>
#include <vector>

class Window {
private:
    int x, y;
    int width, height;
    static const int SCREEN_WIDTH = 80;
    static const int SCREEN_HEIGHT = 50;

    void adjustWindow() {
        if (width < 0) width = 0;
        if (height < 0) height = 0;

        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x + width > SCREEN_WIDTH) {
            if (width > SCREEN_WIDTH) {
                width = SCREEN_WIDTH;
                x = 0;
            }
            else {
                x = SCREEN_WIDTH - width;
            }
        }
        if (y + height > SCREEN_HEIGHT) {
            if (height > SCREEN_HEIGHT) {
                height = SCREEN_HEIGHT;
                y = 0;
            }
            else {
                y = SCREEN_HEIGHT - height;
            }
        }
    }

public:
    Window(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {
        adjustWindow();
    }

    bool move(int dx, int dy) {
        int newX = x + dx;
        int newY = y + dy;


        if (newX < 0 || newY < 0 ||
            newX + width > SCREEN_WIDTH ||
            newY + height > SCREEN_HEIGHT) {
            return false;
        }

        x = newX;
        y = newY;
        return true;
    }

    bool resize(int newWidth, int newHeight) {
        if (newWidth < 0 || newHeight < 0) {
            return false;
        }

        if (x + newWidth > SCREEN_WIDTH || y + newHeight > SCREEN_HEIGHT) {
            return false;
        }

        width = newWidth;
        height = newHeight;
        return true;
    }

    void display() const {
        for (int row = 0; row < SCREEN_HEIGHT; ++row) {
            for (int col = 0; col < SCREEN_WIDTH; ++col) {
                if (col >= x && col < x + width && row >= y && row < y + height) {
                    std::cout << '1';
                }
                else {
                    std::cout << '0';
                }
            }
            std::cout << '\n';
        }
    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

int main() {
    Window window(10, 10, 20, 10);
    std::string command;

    std::cout << "Enter  command: move, resize, display, close\n";

    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (command == "move") {
            int dx, dy;
            std::cout << "Enter offset (x and y): ";
            std::cin >> dx >> dy;

            if (window.move(dx, dy)) {
                std::cout << "Window moved. New coordinates: ("
                    << window.getX() << ", " << window.getY() << ")\n";
            }
            else {
                std::cout << "Impossible to move. Going beyond the screen.\n";
            }

        }
        else if (command == "resize") {
            int width, height;
            std::cout << "Enter new width and height: ";
            std::cin >> width >> height;

            if (window.resize(width, height)) {
                std::cout << "Window's size've changed. New size: "
                    << window.getWidth() << "x" << window.getHeight() << "\n";
            }
            else {
                std::cout << "Impossible to change. Wrong parametres.\n";
            }

        }
        else if (command == "display") {
            window.display();

        }
        else if (command == "close") {
            std::cout << "Exit the programm.\n";
            break;

        }
        else {
            std::cout << "Unknown command. Enter: move, resize, display, close\n";
        }
    }

    return 0;
}