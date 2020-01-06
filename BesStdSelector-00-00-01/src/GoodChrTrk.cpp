/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    GoodChrTrk.cpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-10-20 Sun 18:26:13 CST
 * <<=====================================>>
 * Last Updated: 2019-12-11 Wed 13:50:04 CST
 *           By: Hao-Kai SUN
 *     Update #: 21
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

#include "OmegaXiKAlg/selector/GoodChrTrk.hpp"

OmegaXiKSLT::GoodChrTrk::GoodChrTrk()
    : m_VrCut(1.0), m_VzCut(10.0), m_CosThetaCut(0.93)
{
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("RxyCut", m_VrCut);
    m_propMgr.declareProperty("Vz0Cut", m_VzCut);
    m_propMgr.declareProperty("CosThetaCut", m_CosThetaCut);

    jobSvc->setMyProperties("OmegaXiKSelectorGoodChrTrk", &m_propMgr);
}

bool OmegaXiKSLT::GoodChrTrk::operator()(CDElectron& aGoodChrTrk)
{
    EvtRecTrack* recTrk = const_cast<EvtRecTrack*>(aGoodChrTrk.track());
    // MDC track selection
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

    return true;
}

OmegaXiKSLT::GoodChrTrk omegaXiKSelectorGoodChrTrk;
/* ===================================================================<<< */
/* ===================== GoodChrTrk.cpp ends here ======================= */
