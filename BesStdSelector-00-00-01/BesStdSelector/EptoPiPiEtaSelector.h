/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorEptoPiPiEtaSelector.h
#   Created Time  : 2019-10-23 15:47
#   Last Modified : 2019-10-23 15:47
#   Describe      :
#
# ====================================================*/

#ifndef BeSelector_EPTOPIPIETA_SELECTOR_H
#define BeSelector_EPTOPIPIETA_SELECTOR_H

#include "BesDChain/CDDecay.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class BeSelectorEptoPiPiEtaSelector : public DCSelectionFunction<CDDecay> {
   public:
    BeSelectorEptoPiPiEtaSelector();

    bool operator()(CDDecay& aEp);

   private:
    BeSelectorEptoPiPiEtaSelector(const BeSelectorEptoPiPiEtaSelector&);
    const BeSelectorEptoPiPiEtaSelector& operator=(
        const BeSelectorEptoPiPiEtaSelector&);

    double m_minMass;
    double m_maxMass;
};

extern BeSelectorEptoPiPiEtaSelector beSelectorEptoPiPiEtaSelector;

#endif
