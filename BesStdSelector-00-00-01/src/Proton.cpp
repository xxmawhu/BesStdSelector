/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    ProtonPrimary.cpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-10-21 Mon 19:02:03 CST
 * <<=====================================>>
 * Last Updated: 2019-12-11 Wed 13:59:47 CST
 *           By: Hao-Kai SUN
 *     Update #: 25
 * <<======== COPYRIGHT && LICENSE =======>>
 *
 * Copyright © 2019 SUN Hao-Kai <spin.hk@outlook.com>. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs.  If not, see <https://www.gnu.org/licenses/>.
 *
 * ============================== CODES ==============================>>> */
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "EventModel/EventHeader.h"
#include "EventModel/EventModel.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "ParticleID/ParticleID.h"

#include "VertexFit/Helix.h"
#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/VertexFit.h"

#include "OmegaXiKAlg/selector/Proton.hpp"

OmegaXiKSLT::Proton::Proton(const std::string& JvcName, const double& VrCut,
                            const double& VzCut)
    : m_pidtype(4)
    , m_useMag(false)
    , m_minMag(0.)
    , m_VrCut(VrCut)
    , m_VzCut(VzCut)
    , m_CosThetaCut(0.93)
    , m_usePID(true)
    , m_useDedx(true)
    , m_useTof1(true)
    , m_useTof2(true)
    , m_useTofE(false)
    , m_useTofQ(false)
    , m_useEmc(false)
    , m_useMuc(false)
    , m_useTof(true)
    , m_useTofC(false)
    , m_useTofCorr(false)
    , m_usePIDProb(true)
    , m_minPIDProb(0.001)
    , m_rejectPionKaon(true)
    , m_rejectElectron(false)
    , m_useLikelihood(false)
    , m_useNeuronNetwork(false)
{
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("UseP3MagCut", m_useMag);
    m_propMgr.declareProperty("MinP3Mag", m_minMag);

    m_propMgr.declareProperty("RxyCut", m_VrCut);
    m_propMgr.declareProperty("Vz0Cut", m_VzCut);
    m_propMgr.declareProperty("CosThetaCut", m_CosThetaCut);

    m_propMgr.declareProperty("UsePID", m_usePID);

    m_propMgr.declareProperty("UsePIDDedx", m_useDedx);
    m_propMgr.declareProperty("UsePIDTof1", m_useTof1);
    m_propMgr.declareProperty("UsePIDTof2", m_useTof2);
    m_propMgr.declareProperty("UsePIDTofE", m_useTofE);
    m_propMgr.declareProperty("UsePIDTofQ", m_useTofQ);
    m_propMgr.declareProperty("UsePIDEmc", m_useEmc);
    m_propMgr.declareProperty("UsePIDMuc", m_useMuc);
    m_propMgr.declareProperty("UsePIDTof", m_useTof);
    m_propMgr.declareProperty("UsePIDTofC", m_useTofC);
    m_propMgr.declareProperty("UsePIDTofCorr", m_useTofCorr);

    m_propMgr.declareProperty("UsePIDProbability", m_usePIDProb);
    m_propMgr.declareProperty("MinPIDProb", m_minPIDProb);
    m_propMgr.declareProperty("RejectPionKaon", m_rejectPionKaon);
    m_propMgr.declareProperty("RejectElectron", m_rejectElectron);

    m_propMgr.declareProperty("UsePIDLikelihood", m_useLikelihood);
    m_propMgr.declareProperty("UsePIDNeuronNetwork", m_useNeuronNetwork);

    // C++98 way of initializing a vector.
    m_neuronNetworkValCut.clear();
    m_neuronNetworkValCut.push_back(1.5);
    m_neuronNetworkValCut.push_back(2.5);
    m_propMgr.declareProperty("NeuronNetworkValCut", m_neuronNetworkValCut);

    jobSvc->setMyProperties(JvcName, &m_propMgr);
}

bool OmegaXiKSLT::Proton::operator()(CDProton& aProton)
{
    aProton.setUserTag(1);

    // WRONG: // mag = (P4.E)^2 - (P4.P3)^2, rho() = sign(mag) * sqrt(fabs(mag))
    // WRONG: // m_minMag is 0, then P4.rho() < 0, virtual particles!
    // WRONG: // m_minMag is small, then this is equally a min-mass-cut.
    // P4.rho() return P4.pp.mag(), which is the magnitude of Hep3Vector
    // sqrt(px^2 + py^2 + pz^2)
    if (m_useMag) {
        HepLorentzVector p4proton = aProton.p4();
        if (p4proton.rho() < m_minMag) return false;
    }

    EvtRecTrack* recTrk = const_cast<EvtRecTrack*>(aProton.track());

    // MDC track selection
    RecMdcKalTrack::setPidType(RecMdcKalTrack::proton);
    if (!recTrk->isMdcKalTrackValid()) return false;

    RecMdcKalTrack* mdcKalTrk = recTrk->mdcKalTrack();
    if (mdcKalTrk->charge() == 0) return false;

    Hep3Vector xorigin(0, 0, 0);
    IVertexDbSvc* vtxsvc;
    Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
    if (vtxsvc->isVertexValid()) {
        double* dbv = vtxsvc->PrimaryVertex();

        // double* vv  = vtxsvc->SigmaPrimaryVertex();
        // for (int i = 0; i < 3; ++i) {
        //     if (vv[i] > 0.5 * dbv[i])
        //         std::cout << "WARNING: VertexVal " << i + 1 << " : " <<
        //         dbv[i]
        //                   << ", Sigma : " << vv[i] << std::endl;
        // }

        xorigin.set(dbv[0], dbv[1], dbv[2]);
        // xorigin.setX(dbv[0]);
        // xorigin.setY(dbv[1]);
        // xorigin.setZ(dbv[2]);
    }

    HepVector a     = mdcKalTrk->getZHelix();
    HepSymMatrix Ea = mdcKalTrk->getZError();
    HepPoint3D point0(0., 0., 0.);
    HepPoint3D IP(xorigin[0], xorigin[1], xorigin[2]);
    VFHelix helixip3(point0, a, Ea);
    helixip3.pivot(IP);
    HepVector vecipa = helixip3.a();

    double dr = fabs(vecipa[0]);
    if (dr >= m_VrCut) return false;

    double dz = fabs(vecipa[3]);
    if (dz >= m_VzCut) return false;

    double costheta = cos(mdcKalTrk->theta());
    if (fabs(costheta) >= m_CosThetaCut) return false;

    if (m_usePID) {
        ParticleID* pid = ParticleID::instance();
        pid->init();

        if (m_usePIDProb) {
            pid->setMethod(pid->methodProbability());
        } else if (m_useLikelihood) {
            pid->setMethod(pid->methodLikelihood());
        } else if (m_useNeuronNetwork) {
            pid->setMethod(pid->methodNeuronNetwork());
        } else {
            std::cout << "*** WARNING: None PID Method!! ***" << std::endl;
            return false;
        }
        pid->setChiMinCut(8);
        pid->setRecTrack(recTrk);

        if (m_useDedx) pid->usePidSys(pid->useDedx());
        if (m_useTof1) pid->usePidSys(pid->useTof1());
        if (m_useTof2) pid->usePidSys(pid->useTof2());
        if (m_useTofE) pid->usePidSys(pid->useTofE());
        if (m_useTofQ) pid->usePidSys(pid->useTofQ());
        if (m_useEmc) pid->usePidSys(pid->useEmc());
        if (m_useMuc) pid->usePidSys(pid->useMuc());
        if (m_useTof) pid->usePidSys(pid->useTof());
        if (m_useTofC) pid->usePidSys(pid->useTofC());
        if (m_useTofCorr) pid->usePidSys(pid->useTofCorr());

        double pPion = 0., pKaon = 0.;
        double pProton = 0., pElectron = 0.;
        int charge = aProton.charge();
        if (m_rejectPionKaon && !m_rejectElectron) {
            pid->identify(pid->onlyPionKaonProton());
            pid->calculate();
            pProton = pid->probProton();
            pPion   = pid->probPion();
            pKaon   = pid->probKaon();
            if (!(pProton > m_minPIDProb && pProton > pPion && pProton > pKaon))
                aProton.setUserTag(2 * charge);

        } else if (m_rejectPionKaon && m_rejectElectron) {
            pid->identify(pid->onlyPionKaonProton() | pid->onlyElectron());
            pid->calculate();
            pProton   = pid->probProton();
            pPion     = pid->probPion();
            pKaon     = pid->probKaon();
            pElectron = pid->probElectron();
            if (!(pProton > m_minPIDProb && pProton > pPion &&
                  pProton > pKaon && pProton > pElectron))
                aProton.setUserTag(2 * charge);
        } else {
            std::cout << "*** WARNING: Solo PID! ***" << std::endl;
            pid->identify(pid->onlyProton());
            pid->calculate();
            pProton = pid->probProton();
            if (pProton < m_minPIDProb) aProton.setUserTag(2 * charge);
        }

        if (m_pidtype == 0) { // user switch
            return true;
        } else {
            if (aProton.userTag() != 1) return false;
        }
    }

    return true;
}

OmegaXiKSLT::Proton omegaXiKSelectorProtonPrimary(
    "OmegaXiKSelectorProtonPrimary");
OmegaXiKSLT::Proton omegaXiKSelectorProtonAll("OmegaXiKSelectorProtonAll", 10.0,
                                              20.0);
/* ===================================================================<<< */
/* ======================== Proton.cpp ends here ======================== */
