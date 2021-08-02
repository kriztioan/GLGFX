/**
 *  @file   PhaseData.h
 *  @brief  Phase Data Class Definition
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef PARATROOPERS_PHASEDATA_H_
#define PARATROOPERS_PHASEDATA_H_

#include "Phase.h"

class PhaseData : public Phase {

public:
  PhaseData();
  PhaseData(int x, int y, int dx, int dyy, int dy, void *data);

  void *data;
};

#endif