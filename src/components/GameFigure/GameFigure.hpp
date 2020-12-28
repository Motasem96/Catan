/**
 * @author: Al Motasem Bellah Arisheh
 * 
 **/
#ifndef GAMEFIGURE_HEADER
#define GAMEFIGURE_HEADER

#include "../../types/FigureType.hpp"
#include "../../types/Color.hpp"

namespace Catan {
  class GameFigure {

  public:
    GameFigure(FigureType type, Color color);
    ~GameFigure();
    FigureType getFigureType();
    void setFigureType(FigureType type);
    Color getFigureColor();
    void setFigureColor(Color color);
    
  protected:
    FigureType type;
    Color color;
  };
}

#endif