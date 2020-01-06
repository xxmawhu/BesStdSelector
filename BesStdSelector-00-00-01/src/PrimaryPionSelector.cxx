/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorPrimaryPionSelector.cxx
#   Created Time  : 2019-10-23 15:36
#   Last Modified : 2019-10-23 15:36
#   Describe      :
#
# ====================================================*/

#include "BeSelector/Selector/BeSelectorPrimaryPionSelector.h"

BeSelectorPrimaryPionSelector::BeSelectorPrimaryPionSelector() {
    m_pidtype = 0;

    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("MinPCut", m_minP = .0);

    m_propMgr.declareProperty("RxyCut", m_VrCut = 1.0);
    m_propMgr.declareProperty("Vz0Cut", m_VzCut = 10.0);
    m_propMgr.declareProperty("CosThetaCut", m_CosThetaCut = 0.93);
    m_propMgr.declareProperty("DoPID", m_DoPID = true);

    m_propMgr.declareProperty("useSimplePID", m_useSimplePID = false);

    m_propMgr.declareProperty("PidUseDedx", m_useDedx = true);
    m_propMgr.declareProperty("PidUseTof1", m_useTof1 = true);
    m_propMgr.declareProperty("PidUseTof2", m_useTof2 = true);
    m_propMgr.declareProperty("PidUseTofE", m_useTofE = false);
    m_propMgr.declareProperty("PidUseTofQ", m_useTofQ = false);
    m_propMgr.declareProperty("PidUseEmc", m_useEmc = false);
    m_propMgr.declareProperty("PidUseMuc", m_useMuc = false);

    m_propMgr.declareProperty("PidwithProbability", m_probability = true);
    m_propMgr.declareProperty("PidProbCut", m_PidProbCut = 0.001);
    m_propMgr.declareProperty("RejectKaon", m_rejectKaon = true);
    m_propMgr.declareProperty("RejectProton", m_rejectProton = false);

    m_propMgr.declareProperty("PidwithLikelihood", m_likelihood = false);
    m_propMgr.declareProperty("PidwithNeuronNetwork", m_neuronNetwork = false);
    m_neuronValCut.clear();
    m_neuronValCut.push_back(1.5);
    m_neuronValCut.push_back(2.5);
    m_propMgr.declareProperty("NeuronValue", m_neuronValCut);

    jobSvc->setMyProperties("BeSelectorPrimaryPionSelector", &m_propMgr);
}

bool BeSelectorPrimaryPionSelector::operator()(CDChargedPion& aPrimaryPion) {
    aPrimaryPion.setUserTag(1);
    // We can not access to any member function of a const EvtRecTrack*,
    // so we must cast the "const" before get any information of the track
    EvtRecTrack* recTrk = const_cast<EvtRecTrack*>(aPrimaryPion.track());

    // The helix parameters dependent on the particle type
    // So, when you try to get Vxy and Vz, please set the PID type.
    RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
    if (!recTrk->isMdcKalTrackValid()) return false;
    RecMdcKalTrack* mdcKalTrk = recTrk->mdcKalTrack();
    if (mdcKalTrk->charge() == 0) return false;

    HepLorentzVector p4pi = aPrimaryPion.p4();
    if (p4pi.rho() < m_minP) return false;

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

    // particleID pacakge
    if (!m_DoPID) return true;
    ParticleID* pid = ParticleID::instance();
    pid->init();
    pid->setMethod(pid->methodProbability());
    pid->setChiMinCut(4);
    pid->setRecTrack(recTrk);
    pid->usePidSys(pid->useDedx() | pid->useTof1() | pid->useTof2() |
                   pid->useTof());
    pid->identify(pid->onlyPion() | pid->onlyKaon() | pid->onlyProton());
    pid->calculate();

    if (!(pid->probPion() > 0 && pid->probPion() > pid->probProton() &&
          pid->probPion() > pid->probKaon()))
        aPrimaryPion.setUserTag(2);

    if (aPrimaryPion.userTag() == 1)
        return true;
    else
        return false;
}
void BeSelectorPrimaryPionSelector::setpidtype(bool dopid) { m_DoPID = dopid; }

BeSelectorPrimaryPionSelector beSelectorPrimaryPionSelector;
