/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorSigma0Selector.h
#   Created Time  : 2019-10-23 15:46
#   Last Modified : 2019-10-25 19:34
#   Describe      :
#
# ====================================================*/

#ifndef LOCAL_SIGMA0_SELECTOR_H
#define LOCAL_SIGMA0_SELECTOR_H

#include "BesDChain/CDDecay.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class BeSelectorSigma0Selector : public DCSelectionFunction<CDDecay> {
   public:
    BeSelectorSigma0Selector();

    bool operator()(CDDecay& aSigma);

   private:
    BeSelectorSigma0Selector(const BeSelectorSigma0Selector&);
    const BeSelectorSigma0Selector& operator=(const BeSelectorSigma0Selector&);

    double m_minMass;
    double m_maxMass;

    double m_minMass_tight;
    double m_maxMass_tight;
};

extern BeSelectorSigma0Selector sigma0Selector;

#endif
