/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorGoodChrTrkSelector.cxx
#   Created Time  : 2019-10-23 15:36
#   Last Modified : 2019-10-23 15:36
#   Describe      :
#
# ====================================================*/

#include "BeSelector/Selector/BeSelectorGoodChrTrkSelector.h"

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

using std::cout;
using std::endl;
BeSelectorGoodChrTrkSelector::BeSelectorGoodChrTrkSelector() {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    // Declare the properties
    m_propMgr.declareProperty("RxyCut", m_VrCut = 1.0);
    m_propMgr.declareProperty("Vz0Cut", m_VzCut = 10.0);
    m_propMgr.declareProperty("CosThetaCut", m_CosThetaCut = 0.93);

    jobSvc->setMyProperties("BeSelectorGoodChrTrkSelector", &m_propMgr);
}

bool BeSelectorGoodChrTrkSelector::operator()(CDElectron& aGoodChrTrk) {
    EvtRecTrack* recTrk = const_cast<EvtRecTrack*>(aGoodChrTrk.track());
    // MDC track selection
    if (!recTrk->isMdcKalTrackValid()) {
        return false;
    }
    RecMdcKalTrack* mdcKalTrk = recTrk->mdcKalTrack();

    if (mdcKalTrk->charge() == 0) {
        return false;
    }

    Hep3Vector xorigin(0, 0, 0);
    IVertexDbSvc* vtxsvc;
    Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
    if (vtxsvc->isVertexValid()) {
        double* dbv = vtxsvc->PrimaryVertex();
        double* vv = vtxsvc->SigmaPrimaryVertex();
        xorigin.setX(dbv[0]);
        xorigin.setY(dbv[1]);
        xorigin.setZ(dbv[2]);
    }
    HepVector a = mdcKalTrk->getZHelix();
    HepSymMatrix Ea = mdcKalTrk->getZError();
    HepPoint3D point0(0., 0., 0.);
    HepPoint3D IP(xorigin[0], xorigin[1], xorigin[2]);
    VFHelix helixip3(point0, a, Ea);
    helixip3.pivot(IP);
    HepVector vecipa = helixip3.a();

    double dr = fabs(vecipa[0]);
    double dz = fabs(vecipa[3]);
    double costheta = cos(mdcKalTrk->theta());
    if (dr >= m_VrCut) {
        return false;
    }
    if (dz >= m_VzCut) {
        return false;
    }
    if (fabs(costheta) >= m_CosThetaCut) {
        return false;
    }
    return true;
}

BeSelectorGoodChrTrkSelector beSelectorGoodChrTrkSelector;
