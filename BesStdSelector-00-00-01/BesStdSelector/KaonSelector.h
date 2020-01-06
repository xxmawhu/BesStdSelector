/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorKaonSelector.h
#   Created Time  : 2019-10-23 15:48
#   Last Modified : 2019-10-23 15:48
#   Describe      :
#
# ====================================================*/

#ifndef BeSelector_Kaon_SELECTOR_H
#define BeSelector_Kaon_SELECTOR_H

#include "BesDChain/CDChargedKaon.h"
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

class BeSelectorKaonSelector : public DCSelectionFunction<CDChargedKaon> {
   public:
    BeSelectorKaonSelector();

    bool operator()(CDChargedKaon& aKaon);

    void setpidtype(int type) { m_pidtype = type; }  // 1:  do PID 0: not do pid

   private:
    BeSelectorKaonSelector(const BeSelectorKaonSelector&);
    const BeSelectorKaonSelector& operator=(const BeSelectorKaonSelector&);

    int m_pidtype;

    double m_VrCut;
    double m_VzCut;
    double m_CosThetaCut;

    bool m_useSimplePID;
    bool m_useDedx;
    bool m_useTof1;
    bool m_useTof2;
    bool m_useTofE;
    bool m_useTofQ;
    bool m_useEmc;
    bool m_useMuc;

    bool m_probability;
    double m_PidProbCut;
    bool m_DoPID;
    bool m_rejectPion;
    bool m_rejectProton;

    bool m_likelihood;
    bool m_neuronNetwork;
    std::vector<double> m_neuronValCut;
};

extern BeSelectorKaonSelector beSelectorKaonSelector;

#endif
