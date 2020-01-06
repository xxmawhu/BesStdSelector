/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorElectronSelector.cxx
#   Created Time  : 2019-10-23 15:35
#   Last Modified : 2019-10-23 15:35
#   Describe      :
#
# ====================================================*/

#include "BeSelector/Selector/BeSelectorElectronSelector.h"

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"
#include "BesDChain/CDElectron.h"

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
BeSelectorElectronSelector::BeSelectorElectronSelector() {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    // Declare the properties
    m_propMgr.declareProperty("RxyCut", m_VrCut = 1.0);
    m_propMgr.declareProperty("Vz0Cut", m_VzCut = 10.0);
    m_propMgr.declareProperty("VCut", m_VCut = false);
    m_propMgr.declareProperty("CosThetaCut", m_CosThetaCut = 0.93);

    m_propMgr.declareProperty("doPid", m_PID = true);
    m_propMgr.declareProperty("CutEvP", m_CutEvP = false);
    m_propMgr.declareProperty("minEvP", m_minEvP = 0.800);

    jobSvc->setMyProperties("BeSelectorElectronSelector", &m_propMgr);
}

bool BeSelectorElectronSelector::operator()(CDElectron& aElectron) {
    aElectron.setUserTag(1);
    // cout<<" begin eletronSlector"<<endl;
    int charge = aElectron.charge();
    // if(charge != m_charge) return false;
    EvtRecTrack* recTrk = const_cast<EvtRecTrack*>(aElectron.track());
    // MDC track selection
    if (!recTrk->isMdcKalTrackValid()) {
        cout << __func__ << "mdcnotvalid" << endl;
        return false;
    }
    RecMdcKalTrack* mdcKalTrk = recTrk->mdcKalTrack();
    RecMdcKalTrack::setPidType(RecMdcKalTrack::electron);

    if (mdcKalTrk->charge() == 0) return false;
    HepLorentzVector p4Ele = mdcKalTrk->p4(0.0005109989);
    // cout<<"get p4 of eletron"<<endl;

    // cut energy over momentum
    if (m_CutEvP) {
        double Ee;
        double Pe = p4Ele.rho();
        if (!recTrk->isEmcShowerValid()) {
            Ee = 0;
        } else {
            // cout<<"cut on e v p"<<endl;
            RecEmcShower* emcSwr = recTrk->emcShower();
            Ee = emcSwr->energy();
        }
        if (Ee < Pe * m_minEvP) {
            aElectron.setUserTag(2 * aElectron.userTag());
        }
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
    if (dr >= m_VrCut) return false;
    if (dz >= m_VzCut) return false;
    if (fabs(costheta) >= m_CosThetaCut) return false;

    //----do pid-----

    if (m_PID) {
        ParticleID* pid = ParticleID::instance();
        pid->init();
        pid->setMethod(pid->methodProbability());
        pid->setChiMinCut(4);
        pid->setRecTrack(recTrk);
        pid->usePidSys(pid->useDedx() | pid->useTof1() | pid->useTof2());
        pid->identify(pid->onlyElectron() | pid->onlyKaon() | pid->onlyPion());
        pid->calculate();

        double probE = pid->probElectron();
        double probPi = pid->probKaon();
        double probK = pid->probPion();
        double Q = probE / (probE + probPi + probK);
        if (probE < probPi || probE < probK || Q < 0.8) {
            return false;
        }
    }
    return true;
}

BeSelectorElectronSelector beSelectorElectronSelector;
