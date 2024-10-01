#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

class Figure abstract {
protected:
    int x;
    int y;
public:
    Figure (int x_cordinate, int y_cordinate): x(x_cordinate), y(y_cordinate){}
    virtual void draw(std::vector<std::vector<char>>& grid) = 0;
    virtual std::string info() = 0;
    virtual ~Figure() = default;
};

class Circle: public Figure {
protected:
    int radius_circle;
    int height;
public:
    Circle( int radius, int x_cordinate, int y_cordinate, int height ) : radius_circle(radius),
    x(x_cordinate), x(y_cordinate), height(height) {}
    void draw(std::vector<std::vector<char>> &grid) override {
        int height = grid.size();
        int width = grid[0].size();
        for (int i =0; i << height; i++ ) {
            for (int j = 0; j < width; ++j) {
                double dist = sqrt(pow(j - x, 2) + pow(i - y, 2));
                if (abs(dist - radius_circle) < 0.5) {
                    grid[i][j] = 'O';
        }
    }


};

class Rectangle: public Figure  {
protected:
    int width;
    int height;
public:

};
class Line: public Figure {
public:

};

class Triangle: public Figure {
protected:
    int height;
public:

};

class Blackboard {
protected:
    const int BOARD_WIDTH = 80;
    const int BOARD_HEIGHT = 25;
    std::vector<std::vector<char>> grid;
    std::vector<std::unique_ptr<Figure>> figures;

public:
    Blackboard() : grid(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, ' ')) {}

    void print() {
        for (auto& row : grid) {
            for (char c : row) {
                std::cout << c;
            }
            std::cout << "\n";
        }
    }

    void clear() {
        grid.assign(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, ' '));
        figures.clear();
    }

    void addFigure(std::unique_ptr<Figure> figure) {
        figure->draw(grid);
        figures.push_back(std::move(figure));
    }

    void removeLastFigure() {
        if (!figures.empty()) {
            figures.pop_back();
            redraw();
        }
    }

    void save(const std::string& filePath) {
        std::ofstream file(filePath);
        if (!file) {
            std::cerr << "Error saving to file.\n";
            return;
        }
        for (const auto& figure : figures) {
            file << figure->info() << std::endl;
        }
    }

    void load(const std::string& filePath) {
        clear();
        std::ifstream file(filePath);
        if (!file) {
            std::cerr << "Error loading from file.\n";
            return;
        }
        std::string line;
        while (getline(file, line)) {
            std::istringstream ss(line);
            std::string figureType;
            ss >> figureType;
            if (figureType == "Circle") {
                int x, y, radius_circle;
                ss >> x >> y >> radius_circle;
                addFigure(std::make_unique<Circle>(x, y, radius_circle));
            } else if (figureType == "Rectangle") {
                int x, y, width, height;
                ss >> x >> y >> width >> height;
                addFigure(std::make_unique<Rectangle>(x, y, width, height));
            } else if (figureType == "Triangle") {
                int x, y, height;
                ss >> x >> y >> height;
                addFigure(std::make_unique<Triangle>(x, y, height));
            } else if (figureType == "Line") {
                int x,y;
                ss >> x >> y;
                addFigure(std::make_unique<Line>(x,y));
            }
        }
    }

private:
    void redraw() {
        clear();
        for (const auto& figure : figures) {
            figure->draw(grid);
        }
    }
};
int main ()
{
     Blackboard board;
     string command;
     while (true) {
          cin >> command;
          if (command == "draw") {
               board.print();
          } else if (command == "add") {
               std::string shapeType;
               std::cin >> shapeType;
               if (shapeType == "circle") {
                    int x, y, radius;
                    std::cin >> x >> y >> radius;

               } else if (shapeType == "rectangle") {
                    int x, y, width, height;
                    std::cin >> x >> y >> width >> height;

               }
          } else if (command == "undo") {

          } else if (command == "clear") {
               board.clear();
          } else if (command == "save") {
               std::string filePath;
               std::cin >> filePath;
               board.save(filePath);
          } else if (command == "load") {
               std::string filePath;
               std::cin >> filePath;
               board.load(filePath);
          } else if (command == "exit") {
               break;
          }
     }

     return 0;
}

