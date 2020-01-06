/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Electron.cpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-10-19 Sat 17:10:49 CST
 * <<=====================================>>
 * Last Updated: 2019-12-11 Wed 13:48:20 CST
 *           By: Hao-Kai SUN
 *     Update #: 85
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
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/ThreeVector.h"

#include "EventModel/EventHeader.h"
#include "EventModel/EventModel.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "ParticleID/ParticleID.h"

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "VertexFit/Helix.h"
#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/VertexFit.h"

#include "OmegaXiKAlg/selector/Electron.hpp"

using CLHEP::Hep3Vector;
using CLHEP::HepLorentzVector;

OmegaXiKSLT::Electron::Electron()
    : m_charge(-1)
    , m_useVCut(false)
    , m_VrCut(1.0)
    , m_VzCut(10.0)
    , m_CosThetaCut(0.93)
    , m_useEvPCut(false)
    , m_minEvP(0.800)
    , m_usePID(true)
    , m_majorProb(0.8)
{
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("Charge", m_charge);

    m_propMgr.declareProperty("UseVCut", m_useVCut);
    m_propMgr.declareProperty("RxyCut", m_VrCut);
    m_propMgr.declareProperty("Vz0Cut", m_VzCut);
    m_propMgr.declareProperty("CosThetaCut", m_CosThetaCut);

    m_propMgr.declareProperty("UseEvPCut", m_useEvPCut);
    m_propMgr.declareProperty("MinEvP", m_minEvP);

    m_propMgr.declareProperty("UsePID", m_usePID);
    m_propMgr.declareProperty("MajorProbability", m_majorProb);

    jobSvc->setMyProperties("OmegaXiKSelectorElectron", &m_propMgr);
}

bool OmegaXiKSLT::Electron::operator()(CDElectron& aElectron)
{
    aElectron.setUserTag(1);
    // if(aElectron.charge() != m_charge) return false; // +- check
    EvtRecTrack* recTrk = const_cast<EvtRecTrack*>(aElectron.track());

    // MDC track selection
    if (!recTrk->isMdcKalTrackValid()) {
        std::cout << __func__ << "Mdc NOT Valid!" << std::endl;
        return false;
    }
    RecMdcKalTrack* mdcKalTrk = recTrk->mdcKalTrack();
    RecMdcKalTrack::setPidType(RecMdcKalTrack::electron); // 0
    if (mdcKalTrk->charge() == 0) return false;

    // cut energy over momentum
    if (m_useEvPCut) {
        HepLorentzVector p4Ele = mdcKalTrk->p4(0.0005109989);
        double Pe              = p4Ele.rho();

        double Ee;
        if (!recTrk->isEmcShowerValid()) {
            Ee = 0.;
        } else {
            Ee = recTrk->emcShower()->energy();
        }

        if (Ee < Pe * m_minEvP) {
            aElectron.setUserTag(2 * aElectron.userTag());
        }
    }

    // cut particle track's volume of space
    if (m_useVCut) {
        Hep3Vector xorigin(0, 0, 0);
        IVertexDbSvc* vtxsvc;
        Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);

        if (vtxsvc->isVertexValid()) {
            double* dbv = vtxsvc->PrimaryVertex();
            // double* vv  = vtxsvc->SigmaPrimaryVertex();
            // for (int i = 0; i < 3; ++i) {
            //     if (vv[i] > 0.5 * dbv[i])
            //         std::cout << "WARNING: VertexVal " << i + 1 << " : "
            //                   << dbv[i] << ", Sigma : " << vv[i] <<
            //                   std::endl;
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
    }

    // Particle Identification
    if (m_usePID) {
        ParticleID* pid = ParticleID::instance();
        pid->init();
        pid->setMethod(pid->methodProbability());
        pid->setChiMinCut(4);
        pid->setRecTrack(recTrk);
        pid->usePidSys(pid->useDedx() | pid->useTof1() | pid->useTof2());
        // pid->identify(pid->onlyElectron() | pid->onlyKaon() |
        // pid->onlyPion());
        pid->identify(pid->onlyPionKaonElectron());
        pid->calculate();

        double probE  = pid->probElectron();
        double probPi = pid->probKaon();
        double probK  = pid->probPion();
        double Q      = probE / (probE + probPi + probK);

        if (probE < probPi || probE < probK || Q < m_majorProb) return false;
    }

    return true;
}

OmegaXiKSLT::Electron omegaXiKSelectorElectron;
/* ===================================================================<<< */
/* ====================== Electron.cpp ends here ======================== */
