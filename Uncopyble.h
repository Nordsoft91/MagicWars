//
//  Uncopyble.h
//  MagicWars
//
//  Created by nordsoft on 26.10.15.
//
//

#pragma once

class Uncopyble
{
protected:
    Uncopyble() = default;
    
private:
    Uncopyble( const Uncopyble& ) = delete;
    Uncopyble& operator= ( const Uncopyble& ) = delete;
};