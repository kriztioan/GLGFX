/**
 *  @file   PhaseData.h
 *  @brief  Phase Data Class Implementation
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "PhaseData.h"

PhaseData::PhaseData() : Phase(), data(0) {}

PhaseData::PhaseData(int x, int y, int dx, int dyy, int dy, void *data)
    : Phase(x, y, dx, dyy, dy), data(data) {}
