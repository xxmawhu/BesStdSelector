/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorPi0Selector.h
#   Created Time  : 2019-10-23 15:47
#   Last Modified : 2019-10-23 15:47
#   Describe      :
#
# ====================================================*/

#ifndef BeSelector_Pio_SELECTOR_H
#define BeSelector_Pio_SELECTOR_H

#include "BesDChain/CDPi0.h"
#include "DecayChain/Function/DCSelectionFunction.h"

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "EvtRecEvent/EvtRecPi0.h"

class BeSelectorPi0Selector : public DCSelectionFunction<CDPi0> {
   public:
    BeSelectorPi0Selector();

    bool operator()(CDPi0& aPi0);

   private:
    BeSelectorPi0Selector(const BeSelectorPi0Selector&);
    const BeSelectorPi0Selector& operator=(const BeSelectorPi0Selector&);
    double m_minP;
    double m_minMass;
    double m_maxMass;
    double m_maxChisq;
};

extern BeSelectorPi0Selector beSelectorPi0Selector;

#endif
