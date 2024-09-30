#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include "Shape.h"
using namespace std;


class BlackBoard {
private:
     vector<std::unique_ptr<Shape>> shapes;
     vector<std::vector<char>> grid;
     const int BOARD_WIDTH = 80;
     const int BOARD_HEIGHT = 25;
public:
     BlackBoard() : grid(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, ' ')) {}

     void print() {
          for (auto& row : grid) {
               for (char c : row) {
                    std::cout << c;
               }
               std::cout << "\n";
          }
     }

};

class Figure {
     string circle;
     string cube;
private:
     virtual void draw_the_figure();
};

class Circle {
private:
     int radius_circle;
     int area;
public: Figure  {
     void Figure(int r, int area): int radius_circle(r),
     }
};

int main ()
{
     Blackboard bord;
     cout << "Hello in draw studio ";
     cout << "Write a Height of a figure" ;
     cin
}