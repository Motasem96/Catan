#include "../../components/GameFigure/GameFigure.hpp"


namespace Catan {
    
    GameFigure::GameFigure(FigureType type, Color color) {
        this->type = type;
        this->color = color;
    }
    GameFigure::~GameFigure() {
        
    }
    void GameFigure::setFigureType(FigureType type) {
        this->type = type;
    }

    FigureType GameFigure::getFigureType() {
        return this->type;
    }

    Color GameFigure::getFigureColor() {
        return this->color;
    }
    void GameFigure::setFigureColor(Color color) {
        this->color = color;
    }

}