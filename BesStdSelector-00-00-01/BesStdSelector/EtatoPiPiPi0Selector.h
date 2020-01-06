/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorEtatoPiPiPi0Selector.h
#   Created Time  : 2019-10-23 15:48
#   Last Modified : 2019-10-23 15:48
#   Describe      :
#
# ====================================================*/

#ifndef BeSelector_ETATOPIPIPI0_SELECTOR_H
#define BeSelector_ETATOPIPIPI0_SELECTOR_H

#include "BesDChain/CDDecay.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class BeSelectorEtatoPiPiPi0Selector : public DCSelectionFunction<CDDecay> {
   public:
    BeSelectorEtatoPiPiPi0Selector();

    bool operator()(CDDecay& aEp);

   private:
    BeSelectorEtatoPiPiPi0Selector(const BeSelectorEtatoPiPiPi0Selector&);
    const BeSelectorEtatoPiPiPi0Selector& operator=(
        const BeSelectorEtatoPiPiPi0Selector&);

    double m_minMass;
    double m_maxMass;
};

extern BeSelectorEtatoPiPiPi0Selector beSelectorEtatoPiPiPi0Selector;

#endif
