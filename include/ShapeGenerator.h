#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H
#pragma once
#include "../primitives/ShapeData.h"

class ShapeGenerator
{
    public:
        static ShapeData makeCylinder();
		static ShapeData makeSaw();
		static ShapeData makeBox();
		static ShapeData makeGround();
    protected:
    private:
};

#endif // SHAPEGENERATOR_H
