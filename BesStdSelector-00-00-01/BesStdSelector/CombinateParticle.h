/* ====================================================
#   Copyright (C)2020 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : CombinateParticle.h
#   Create Time   : 2020-01-12 19:29
#   Last Modified : 2020-01-12 19:29
#   Describe      :
#
# ====================================================*/
#ifndef CombinateParticle__H
#define CombinateParticle__H
#include "BesDChain/CDDecay.h"
#include "DecayChain/Function/DCSelectionFunction.h"
#include <string>

#include "BesStdSelector/BesStdSelector.h"
using std::string;
class BesStdSelector::CombinateParticle : public DCSelectionFunction<CDDecay> {
   public:
    CombinateParticle(const string& selector_name, const double& minMass = 0.0,
                      const double& maxMass = 5.0);

    bool operator()(CDDecay& aComb);

   private:
    CombinateParticle(const CombinateParticle&);
    const CombinateParticle& operator=(const CombinateParticle&);

    double m_minMass;
    double m_maxMass;
};

#endif  // _COMBINATEPARTICLE_H
