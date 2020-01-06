/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorKsSelector.h
#   Created Time  : 2019-10-23 15:48
#   Last Modified : 2019-10-23 15:48
#   Describe      :
#
# ====================================================*/

#ifndef BeSelector_KS_SELECTOR_H
#define BeSelector_KS_SELECTOR_H

#include "BesDChain/CDKs.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class BeSelectorKsSelector : public DCSelectionFunction<CDKs> {
   public:
    BeSelectorKsSelector();

    bool operator()(CDKs& aKs);

   private:
    BeSelectorKsSelector(const BeSelectorKsSelector&);
    const BeSelectorKsSelector& operator=(const BeSelectorKsSelector&);

    double m_minMass;
    double m_maxMass;
    double m_maxChisq;

    bool m_doSecondaryVFit;
    double m_maxVFitChisq;
    double m_minFlightSig;
};

extern BeSelectorKsSelector beSelectorKsSelector;

#endif
