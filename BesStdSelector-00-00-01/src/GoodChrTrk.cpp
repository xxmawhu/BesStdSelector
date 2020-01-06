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

#include "BesStdSelector/GoodChrTrk.h"

BesStdSelector::GoodChrTrk::GoodChrTrk() {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("RxyCut", m_VrCut=1.0);
    m_propMgr.declareProperty("Vz0Cut", m_VzCut=10.0);
    m_propMgr.declareProperty("CosThetaCut", m_CosThetaCut=0.93);

    jobSvc->setMyProperties("PrimaryGoodChrTrkSelector", &m_propMgr);
}

bool BesStdSelector::GoodChrTrk::operator()(CDElectron& aGoodChrTrk) {
    EvtRecTrack* recTrk = const_cast<EvtRecTrack*>(aGoodChrTrk.track());
    if (!recTrk->isMdcKalTrackValid()) return false;

    RecMdcKalTrack* mdcKalTrk = recTrk->mdcKalTrack();
    if (mdcKalTrk->charge() == 0) return false;

    Hep3Vector xorigin(0, 0, 0);
    IVertexDbSvc* vtxsvc;
    Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
    if (vtxsvc->isVertexValid()) {
        double* dbv = vtxsvc->PrimaryVertex();
        xorigin.set(dbv[0], dbv[1], dbv[2]);
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
    if (dr > m_VrCut || dz > m_VzCut || fabs(costheta) > m_CosThetaCut){
        return false;
    }

    return true;
}

BesStdSelector::GoodChrTrk omegaXiKSelectorGoodChrTrk;
/* ===================================================================<<< */
/* ===================== GoodChrTrk.cpp ends here ======================= */
