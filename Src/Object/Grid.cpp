#include "Grid.h"
#include <DxLib.h>

Grid::Grid(void)
{
}

Grid::~Grid(void)
{
}

void Grid::Init(void)
{
}

void Grid::Update(void)
{
}

void Grid::Draw(void)
{
    const int COLOR_RED = 0xff0000;
    const int COLOR_GREEN = 0x00ff00;
    const int COLOR_BLUE = 0x0000ff;
    const float SPHERE_RADIUS = 20.0f;
    const int SPHERE_DIVISIONS = 10;
    const float Y_AXIS_POSITION = 0.0f;

    for (int zIndex = -LINE_COUNT; zIndex <= LINE_COUNT; zIndex++)
    {
        float offsetZ = zIndex * INTERVAL;

        VECTOR startPosition = { -LENGTH, Y_AXIS_POSITION, offsetZ };
        VECTOR endPosition = { LENGTH, Y_AXIS_POSITION, offsetZ };

        DrawLine3D(startPosition, endPosition, COLOR_RED);

        DrawSphere3D(
            endPosition,
            SPHERE_RADIUS,
            SPHERE_DIVISIONS,
            COLOR_RED,
            COLOR_RED,
            true
        );
    }

    for (int xIndex = -LINE_COUNT; xIndex <= LINE_COUNT; xIndex++)
    {
        float offsetX = xIndex * INTERVAL;

        VECTOR startPosition = { offsetX, Y_AXIS_POSITION, -LENGTH };
        VECTOR endPosition = { offsetX, Y_AXIS_POSITION, LENGTH };

        DrawLine3D(startPosition, endPosition, COLOR_BLUE);

        DrawSphere3D(
            endPosition,
            SPHERE_RADIUS,
            SPHERE_DIVISIONS,
            COLOR_BLUE,
            COLOR_BLUE,
            true
        );
    }

    VECTOR yStartPosition = { 0.0f, -LENGTH, 0.0f };
    VECTOR yEndPosition = { 0.0f, LENGTH, 0.0f };

    DrawLine3D(yStartPosition, yEndPosition, COLOR_GREEN);
}

void Grid::Release(void)
{
}