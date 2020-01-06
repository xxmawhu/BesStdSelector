/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin Ma
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorSignalSelector.h
#   Last Modified : 2019-10-23 10:02
#   Describe      :
#
# ====================================================*/

#ifndef BeSelector_Ds_SELECTOR_H
#define BeSelector_Ds_SELECTOR_H

#include "BesDChain/CDDecay.h"
#include "DecayChain/Function/DCSelectionFunction.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/ThreeVector.h"
using CLHEP::HepLorentzVector;

class BeSelectorSignalSelector : public DCSelectionFunction<CDDecay> {
   public:
    BeSelectorSignalSelector();

    inline void setebeam(double ebeam) { m_beamE = ebeam; }

    bool operator()(CDDecay& aOmega);

   private:
    BeSelectorSignalSelector(const BeSelectorSignalSelector&);
    const BeSelectorSignalSelector& operator=(const BeSelectorSignalSelector&);

    double m_beamE;

    bool m_useMbcCuts;
    bool m_useDeltaECut;
    bool m_useRecCuts;
    double m_maxRecMass;
    double m_minRecMass;

    double m_minMass;
    double m_maxMass;

    double m_MinDeltaE;
    double m_MaxDeltaE;
};

extern BeSelectorSignalSelector beSelectorSignalSelector;

#endif
