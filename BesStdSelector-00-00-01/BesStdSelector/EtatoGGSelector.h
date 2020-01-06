/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorEtatoGGSelector.h
#   Created Time  : 2019-10-23 15:48
#   Last Modified : 2019-10-23 15:48
#   Describe      :
#
# ====================================================*/

#ifndef BeSelector_EtaToGG_SELECTOR_H
#define BeSelector_EtaToGG_SELECTOR_H

#include "BesDChain/CDEta.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class BeSelectorEtatoGGSelector : public DCSelectionFunction<CDEta> {
   public:
    BeSelectorEtatoGGSelector();

    bool operator()(CDEta& aEta);

   private:
    BeSelectorEtatoGGSelector(const BeSelectorEtatoGGSelector&);
    const BeSelectorEtatoGGSelector& operator=(
        const BeSelectorEtatoGGSelector&);

    double m_minMass;
    double m_maxMass;
    double m_maxChisq;
};

extern BeSelectorEtatoGGSelector beSelectorEtatoGGSelector;

#endif
