#pragma once
#include <iostream>

class Color {
  public:
    Color();
    Color(double red, double green, double blue);
    Color(int r, int g, int b);
    double red() const;
    double green() const;
    double blue() const;

  private:
    double r{};
    double g{};
    double b{};
    bool validateColor(int colorParam);

  private:
    friend std::istream& operator>> (std::istream& stream, Color& color);
    friend std::ostream& operator<< (std::ostream& stream, const Color& color);//почему если убрать эту строку, оператор << выдает ошибку no
    //operator matches these operands???????????????????????????????????
};
