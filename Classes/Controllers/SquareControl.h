//
//  SquareControl.h
//  MagicWars
//
//  Created by nordsoft on 22.10.14.
//
//

#ifndef MagicWars_SquareControl_h
#define MagicWars_SquareControl_h

#include <Engine/TileMap.h>
#include <Engine/GameObj.h>
#include <Common/WavePathFinder.h>
#include <Common/Consts.h>
#include <SDK/Uncopyble.h>
#include <memory>

namespace MagicWars_NS {
    const std::string cstrSprSquares = RES("interface","Squares.png");
    
    struct SquareShape
    {
    
    };
    
    class SquareControl: public Uncopyble
    {
        SquareControl();
        ~SquareControl();
        
    public:
        using Point = std::pair<size_t, size_t>;
        using Points = std::vector<Point>;
        
        static SquareControl& instance();
        
        Points getBorder(size_t x, size_t y, size_t i_radius);
        Points getPoint(size_t x, size_t y);
        Points getSquare(size_t x, size_t y, size_t i_radius, bool i_center = false);
        Points getCross(size_t x, size_t y, size_t i_minradius, size_t i_radius, bool i_center = false);
        Points getStar(size_t x, size_t y, size_t i_minradius, size_t i_radius, bool i_center = false);
        Points getLine(size_t xs, size_t ys, size_t xd, size_t yd, size_t i_radius);
        Points getSquare(size_t x, size_t y, WavePathFinder& i_finder);
        
        void createSquares(const Points& i_points, const std::string i_color);
        
        /*void createBorder(size_t x, size_t y, size_t i_radius, const std::string i_color);
        void createPoint(size_t x, size_t y, const std::string i_color);
        void createSquare(size_t x, size_t y, size_t i_radius, const std::string i_color, bool i_center = false);
        void createCross(size_t x, size_t y, size_t i_minradius, size_t i_radius, const std::string i_color, bool i_center = false);
        void createStar(size_t x, size_t y, size_t i_minradius, size_t i_radius, const std::string i_color, bool i_center = false);
        void createLine(size_t xs, size_t ys, size_t xd, size_t yd, size_t i_radius, const std::string i_color);
        
        void createSquare(size_t x, size_t y, WavePathFinder& i_finder, const std::string i_color);*/
        
        bool isSquared(size_t x, size_t y, const std::string i_color);
        Points getSquared(const std::string i_color);
        
        void deleteSquares(const std::string i_color);
        void deleteSquares();
        void toScene(cocos2d::Node* i_scene);
        
    private:
        TileMap* d_pSquares;
        Tileset* d_pSqTileset;
    };
}

#endif
