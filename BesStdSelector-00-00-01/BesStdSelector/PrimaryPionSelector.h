/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorPrimaryPionSelector.h
#   Created Time  : 2019-10-23 15:47
#   Last Modified : 2019-10-23 15:47
#   Describe      :
#
# ====================================================*/

#ifndef BeSelector_PrimaryPion_SELECTOR_H
#define BeSelector_PrimaryPion_SELECTOR_H

#include "BesDChain/CDChargedPion.h"
#include "DecayChain/Function/DCSelectionFunction.h"

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "EventModel/EventModel.h"
#include "EventModel/EventHeader.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "ParticleID/ParticleID.h"

#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/Helix.h"

class BeSelectorPrimaryPionSelector
    : public DCSelectionFunction<CDChargedPion> {
   public:
    BeSelectorPrimaryPionSelector();

    bool operator()(CDChargedPion& aPrimaryPion);
    void setpidtype(bool type = true);

   private:
    BeSelectorPrimaryPionSelector(const BeSelectorPrimaryPionSelector&);
    const BeSelectorPrimaryPionSelector& operator=(
        const BeSelectorPrimaryPionSelector&);

    int m_pidtype;

    double m_minP;
    double m_VrCut;
    double m_VzCut;
    double m_CosThetaCut;

    bool m_useSimplePID, m_DoPID;
    bool m_useDedx;
    bool m_useTof1;
    bool m_useTof2;
    bool m_useTofE;
    bool m_useTofQ;
    bool m_useEmc;
    bool m_useMuc;

    bool m_probability;
    double m_PidProbCut;
    bool m_rejectKaon;
    bool m_rejectProton;

    bool m_likelihood;
    bool m_neuronNetwork;
    std::vector<double> m_neuronValCut;
};

extern BeSelectorPrimaryPionSelector beSelectorPrimaryPionSelector;

#endif
