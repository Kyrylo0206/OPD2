#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

class Figure {
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
    int x;
    int y;
public:
    void draw(std::vector<std::vector<char>> &grid) override {
        int grid_height = grid.size();
        int grid_width = grid[0].size();
        for (int i = 0; i < grid_height; i++) {
            for (int j = 0; j < grid_width; ++j) {
                double dist = sqrt(pow(j - x, 2) + pow(i - y, 2));
                if (abs(dist - radius_circle) < 0.5) {
                    grid[i][j] = 'O';
                }
            }
        }
    }
};

class Rectangle: public Figure  {
protected:
    int width;
    int height;
public:
    void draw_rectangle (int w, int h) {
        
    }

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
     while(true) {
          cin >> command;
          if(command == "draw") {
               board.print();
          }
          else if(command == "add") {
               string shapeType;
               cin >> shapeType;
               if(shapeType == "circle") {
                    int x, y, radius;
                    cin >> x >> y >> radius;
                    if(cin.fail() || radius <= 0) {
                        cout << "Invalid parameters for Circle. Usage: add circle x y radius\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    board.addFigure(make_unique<Circle>(x, y, radius));
               }
               else if(shapeType == "rectangle") {
                    int x, y, width, height;
                    cin >> x >> y >> width >> height;
                    if(cin.fail() || width <= 0 || height <= 0) {
                        cout << "Invalid parameters for Rectangle. Usage: add rectangle x y width height\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    board.addFigure(make_unique<Rectangle>(x, y, width, height));
               }
               else if(shapeType == "line") {
                    int x, y, length;
                    char dir;
                    cin >> x >> y >> length >> dir;
                    if(cin.fail() || length <= 0 || (dir != 'H' && dir != 'V')) {
                        cout << "Invalid parameters for Line. Usage: add line x y length direction(H/V)\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    board.addFigure(make_unique<Line>(x, y, length, dir));
               }
               else if(shapeType == "triangle") {
                    int x, y, height;
                    cin >> x >> y >> height;
                    if(cin.fail() || height <= 0) {
                        cout << "Invalid parameters for Triangle. Usage: add triangle x y height\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    board.addFigure(make_unique<Triangle>(x, y, height));
               }
               else {
                    cout << "Unknown shape type: " << shapeType << ". Type 'shapes' to see available shapes.\n";
               }
          }
          else if(command == "undo") {
               board.removeLastFigure();
          }
          else if(command == "clear") {
               board.clear();
               cout << "Blackboard cleared.\n";
          }
          else if(command == "save") {
               string filePath;
               cin >> filePath;
               board.save(filePath);
          }
          else if(command == "load") {
               string filePath;
               cin >> filePath;
               board.load(filePath);
          }
          else if(command == "shapes") {
               board.listAvailableShapes();
          }
          else if(command == "list") {
               board.listFigures();
          }
          else if(command == "exit") {
               cout << "Exiting the application. Goodbye!\n";
               break;
          }
          else {
               cout << "Unknown command. Type 'help' to see available commands.\n";
          }
     }

     return 0;
}

