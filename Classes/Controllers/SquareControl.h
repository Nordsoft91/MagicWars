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
    const std::string cstrSprSquares = "Squares.png";
    
    struct SquareShape
    {
        
    };
    
    class SquareControl: public Uncopyble
    {
        SquareControl();
        ~SquareControl();
        
    public:
        static SquareControl& instance();
        
        void createBorder(size_t x, size_t y, size_t i_radius, const std::string i_color);
        void createPoint(size_t x, size_t y, const std::string i_color);
        void createSquare(size_t x, size_t y, size_t i_radius, const std::string i_color, bool i_center = false);
        void createCross(size_t x, size_t y, size_t i_radius, const std::string i_color, bool i_center = false);
        void createStar(size_t x, size_t y, size_t i_radius, const std::string i_color, bool i_center = false);
        void createLine(size_t xs, size_t ys, size_t xd, size_t yd, size_t i_radius, const std::string i_color);
        
        void createSquare(size_t x, size_t y, WavePathFinder& i_finder, const std::string i_color);
        
        bool isSquared(size_t x, size_t y, const std::string i_color);
        std::vector<std::pair<size_t, size_t> > getSquared(const std::string i_color);
        
        void deleteSquares(const std::string i_color);
        void deleteSquares();
        void toScene(cocos2d::Node* i_scene);
        
    private:
        TileMap* d_pSquares;
        Tileset* d_pSqTileset;
    };
}

#endif
