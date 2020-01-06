/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorPhotonSelector.cxx
#   Created Time  : 2019-10-23 15:36
#   Last Modified : 2019-10-23 15:36
#   Describe      :
#
# ====================================================*/

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"
#include "GaudiKernel/SmartDataPtr.h"

#include "EventModel/EventModel.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "BeSelector/Selector/BeSelectorPhotonSelector.h"
#include <iostream>
using std::vector;
BeSelectorPhotonSelector::BeSelectorPhotonSelector() {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    // Declare the properties
    m_propMgr.declareProperty("MinEnergy", m_minEnergy = 0.025);
    m_propMgr.declareProperty("VetoPi0", m_vetoPi0 = false);

    m_propMgr.declareProperty("InBarrelOrEndcap", m_useBarrelEndcap = true);
    m_propMgr.declareProperty("MaxCosThetaBarrel", m_maxCosThetaBarrel = 0.8);
    m_propMgr.declareProperty("MinCosThetaEndcap", m_minCosThetaEndcap = 0.86);
    m_propMgr.declareProperty("MaxCosThetaEndcap", m_maxCosThetaEndcap = 0.92);
    m_propMgr.declareProperty("MinEndcapEnergy", m_minEndcapEnergy = 0.050);

    m_propMgr.declareProperty("ApplyTimeCut", m_applyTimeCut = true);
    m_propMgr.declareProperty("MinTime", m_minTime = 0.);
    m_propMgr.declareProperty("MaxTime", m_maxTime = 14.);
    m_propMgr.declareProperty("PhotonDeltaTime", m_deltaTime = 10.);

    m_propMgr.declareProperty("ApplyDangCut", m_applyDangCut = true);
    m_propMgr.declareProperty("MinDang", m_minDang = 10.0);

    jobSvc->setMyProperties("BeSelectorPhotonSelector", &m_propMgr);
}

bool BeSelectorPhotonSelector::operator()(CDPhoton& aPhoton) {

    aPhoton.setUserTag(1);
    SmartDataPtr<EvtRecEvent> recEvt(eventSvc(),
                                     EventModel::EvtRec::EvtRecEvent);
    SmartDataPtr<EvtRecTrackCol> recTrkCol(eventSvc(),
                                           EventModel::EvtRec::EvtRecTrackCol);

    EvtRecTrack* recTrk = const_cast<EvtRecTrack*>(aPhoton.photon());

    if (!recTrk->isEmcShowerValid()) return false;

    RecEmcShower* emcTrk = recTrk->emcShower();
    double eraw = emcTrk->energy();
    double phi = emcTrk->phi();
    double the = emcTrk->theta();
    HepLorentzVector shP4(eraw * sin(the) * cos(phi),
                          eraw * sin(the) * sin(phi), eraw * cos(the), eraw);

    double cosThetaSh = shP4.vect().cosTheta();
    // epLorentzVector newP4( m_energy * sin(the) * cos(phi),
    //		    m_energy * sin(the) * sin(phi),
    //		    m_energy * cos(the),        m_energy );
    // aPhoton.setP4(newP4);

    /// Minimum energy
    if (shP4.e() <= m_minEnergy) return false;

    /// Barrel/Endcap
    if (m_useBarrelEndcap) {
        bool inBarrelEndcap = false;

        if (fabs(cosThetaSh) < m_maxCosThetaBarrel) inBarrelEndcap = true;

        if ((fabs(cosThetaSh) > m_minCosThetaEndcap) &&
            (fabs(cosThetaSh) < m_maxCosThetaEndcap) &&
            (shP4.e() > m_minEndcapEnergy))
            inBarrelEndcap = true;

        if (!inBarrelEndcap) return false;
    }

    // Time, only apply timing cuts if "recEvt->totalCharged() > 0"
    // the delta Time is |T - T0|,
    // the T0 the is first time of charged track hit the EMC
    // while the T is the time of this gamma candidate
    // require on |T-T0| to supress the background from noise
    if (m_applyTimeCut) {
        double time = emcTrk->time();

        if (recEvt->totalCharged() > 0) {
            if (time < m_minTime || time > m_maxTime) {
                return false;
            }
        } else {
            RecEmcShower* firstG = (*(recTrkCol->begin()))->emcShower();
            double deltaTime = fabs(time - firstG->time());
            if (deltaTime > 10) {
                return false;
            }
        }
    }

    // Dang
    // The dang angle is the angle between
    //  the position of EMC hited by the charged tracks
    // with gamma direction
    // the "gamma" may be produced by particle interact with EMC
    if (m_applyDangCut && recEvt->totalCharged() > 0) {
        Hep3Vector emcpos(emcTrk->x(), emcTrk->y(), emcTrk->z());

        double dang = 200.;
        for (int j = 0; j < recEvt->totalCharged(); ++j) {
            EvtRecTrackIterator jtTrk = recTrkCol->begin() + j;
            if (!(*jtTrk)->isExtTrackValid()) continue;

            RecExtTrack* extTrk = (*jtTrk)->extTrack();
            if (extTrk->emcVolumeNumber() == -1) continue;

            Hep3Vector extpos = extTrk->emcPosition();
            double angd1 = extpos.angle(emcpos);
            if (angd1 < dang) {
                dang = angd1;
            }
        }

        if (dang < 200) {
            dang = dang * 180 / (CLHEP::pi);
            if (dang <= m_minDang) {
                return false;
            }
        }
    }
    if (m_vetoPi0) {
        int ID = recTrk->trackId();
        if (FromPi0(ID, m_pi0s)) {
            return false;
        }
    }

    return true;
}
void BeSelectorPhotonSelector::setPi0s(vector<const EvtRecPi0*> pi0s) {
    m_pi0s = pi0s;
    return;
}
bool BeSelectorPhotonSelector::FromPi0(int ID, vector<const EvtRecPi0*> _pi0s) {
    for (int i = 0; i < _pi0s.size(); i++) {
        const EvtRecPi0* aPi0 = _pi0s[i];
        double mass = aPi0->unconMass();
        if (mass < 0.115 || mass > 0.150) continue;
        double chisq = aPi0->chisq();
        if (chisq > 200) continue;
        const EvtRecTrack* hiEnGamma = aPi0->hiEnGamma();
        const EvtRecTrack* loEnGamma = aPi0->loEnGamma();
        int id1 = const_cast<EvtRecTrack*>(hiEnGamma)->trackId();
        int id2 = const_cast<EvtRecTrack*>(loEnGamma)->trackId();
        if (ID == id1 || ID == id2) return true;
    }
    return false;
}

BeSelectorPhotonSelector beSelectorPhotonSelector;
