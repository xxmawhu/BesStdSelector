/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorLambdaSelector.h
#   Created Time  : 2019-10-23 15:48
#   Last Modified : 2019-10-23 15:48
#   Describe      :
#
# ====================================================*/

#ifndef BeSelector_Lamda_SELECTOR_H
#define BeSelector_Lamda_SELECTOR_H

#include "BesDChain/CDDecay.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class BeSelectorLambdaSelector : public DCSelectionFunction<CDDecay> {
   public:
    BeSelectorLambdaSelector();

    bool operator()(CDDecay& aLambda);

   private:
    BeSelectorLambdaSelector(const BeSelectorLambdaSelector&);
    const BeSelectorLambdaSelector& operator=(const BeSelectorLambdaSelector&);

    double m_minMass;
    double m_maxMass;
    double m_maxChisq;

    bool m_CutFlightSig;
    double m_maxVFitChisq;
    double m_minFlightSig;
};

extern BeSelectorLambdaSelector lambdaSelector;

#endif
