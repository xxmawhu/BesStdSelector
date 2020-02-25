/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Photon.cpp
 * Author:       Xin-Xin MA, Hao-Kai SUN <- Modified from Psi2StoHHHAlg
 * Created:      2019-10-21 Mon 14:51:21 CST
 * <<=====================================>>
 * Last Updated: 2019-12-11 Wed 13:55:47 CST
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
#include "CLHEP/Geometry/Point3D.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "EventModel/EventModel.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "BesStdSelector/Photon.h"

BesStdSelector::Photon::Photon() {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("InBarrelOrEndcap", m_useBarrelEndcap = true);
    m_propMgr.declareProperty("MaxCosThetaBarrel", m_maxCosThetaBarrel = 0.80);
    m_propMgr.declareProperty("MinBarrelEnergy", m_minBarrelEnergy = 0.025);
    m_propMgr.declareProperty("MinCosThetaEndcap", m_minCosThetaEndcap = 0.86);
    m_propMgr.declareProperty("MaxCosThetaEndcap", m_maxCosThetaEndcap = 0.92);
    m_propMgr.declareProperty("MinEndcapEnergy", m_minEndcapEnergy = 0.050);

    /*
     * use the TDC ( time-to-digital converter) cut to suppress the noise
     * background. This is the BESIII standard requirement for photon
     * reconstruction the unit is 50ns
     * https://docbes3.ihep.ac.cn/DocDB/0000/000065/001/hc_bianjm_memo_v4.pdf
     * You can find more detail in the thesis of Bian Jianming:
     * http://ir.ihep.ac.cn/handle/311005/209726
     */
    m_propMgr.declareProperty("UseTDC", m_useTDC = true);
    m_propMgr.declareProperty("MinTime", m_minTime = 0.0);
    m_propMgr.declareProperty("MaxTime", m_maxTime = 14.0);  // unit: 50 ns
    m_propMgr.declareProperty("PhotonDeltaTime", m_deltaTime = 10);

    /*
     * The dang angle is the angle between the position of EMC hited by the
     * charged tracks with gamma direction Charged tracks generate by chance
     * spilt-offs in the MEC which might be assigned to neutral. See:
     * https://indico.ihep.ac.cn/event/9126/contribution/0/material/slides/0.pdf
     * author: Mathilde Himmelreich
     * The cut is recommended at 10, i.e dang < 10, the optimum value is 12
     * the unit is degree, rather than radian
     */
    m_propMgr.declareProperty("UseDangCut", m_useDang = false);
    m_propMgr.declareProperty("MinDang", m_minDang = 10);

    /*
     * loop all photons, once the photon can form a pi0 candidate with another
     * photon, this photon candidate will be drooped.
     * This cut is very important when we search for one solo photon.
     * For example, in the analysis of radiative decay of J/psi or hyperon,
     *   J/psi -> gamma eta_c, Lambda -> gamma n
     */
    m_propMgr.declareProperty("VetoPi0", m_vetoPi0 = false);
    m_propMgr.declareProperty("MinPi0Mass", m_minPi0Mass = 0.115);
    m_propMgr.declareProperty("MaxPi0Mass", m_maxPi0Mass = 0.150);
    m_propMgr.declareProperty("MaxPi0Chisq", m_maxPi0Chisq = 200);

    jobSvc->setMyProperties("SoloPhotonSelector", &m_propMgr);
}

bool BesStdSelector::Photon::operator()(CDPhoton& aPhoton) {
    aPhoton.setUserTag(1);

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
    if (shP4.e() <= m_minBarrelEnergy) return false;

    /// Barrel/Endcap
    if (m_useBarrelEndcap) {
        if (fabs(cosThetaSh) < m_maxCosThetaBarrel) {
            aPhoton.setUserTag(2);
        } else if ((fabs(cosThetaSh) > m_minCosThetaEndcap) &&
                   (fabs(cosThetaSh) < m_maxCosThetaEndcap) &&
                   (shP4.e() > m_minEndcapEnergy)) {
            aPhoton.setUserTag(4);
        } else {
            return false;
        }
    }

    if (m_useTDC || m_useDang) {
        SmartDataPtr<EvtRecEvent> recEvt(eventSvc(),
                                         EventModel::EvtRec::EvtRecEvent);
        SmartDataPtr<EvtRecTrackCol> recTrkCol(
            eventSvc(), EventModel::EvtRec::EvtRecTrackCol);

        // Time, only apply timing cuts if "recEvt->totalCharged() > 0"
        // the delta Time is |T - T0|,
        // the T0 the is first time of charged track hit the EMC
        // while the T is the time of this gamma candidate
        // require on |T-T0| to supress the background from noise
        if (m_useTDC) {
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
        // The dang angle is the angle between the position of EMC hited by the
        // charged tracks with gamma direction
        // Charged tracks generate by chance spilt-offs in the MEC which might
        // be assigned to neutral. See:
        // https://indico.ihep.ac.cn/event/9126/contribution/0/material/slides/0.pdf
        // author: Mathilde Himmelreich
        // The cut is recommended at 10, i.e dang < 10, the optimum value is 12
        if (m_useDang && recEvt->totalCharged() > 0) {
            // Hep3Vector emcpos2(emcTrk->position());
            Hep3Vector emcpos(emcTrk->x(), emcTrk->y(), emcTrk->z());

            double dang = 200.;  // in unit of rad
            // find minimum Dangle
            {
                EvtRecTrackIterator jtTrk;
                RecExtTrack* extTrk;
                Hep3Vector extpos;
                double angd1;
                for (int j = 0; j < recEvt->totalCharged(); ++j) {
                    jtTrk = recTrkCol->begin() + j;
                    if (!(*jtTrk)->isExtTrackValid()) continue;

                    extTrk = (*jtTrk)->extTrack();
                    if (extTrk->emcVolumeNumber() == -1) continue;
                    extpos = extTrk->emcPosition();
                    angd1 = extpos.angle(emcpos);
                    if (angd1 < dang) {
                        dang = angd1;
                    }
                }
            }

            if (dang < 200) {
                dang = dang * 180 / (CLHEP::pi);
                if (dang <= m_minDang) return false;
            }
        }
    }

    if (m_vetoPi0) {
        int ID = recTrk->trackId();
        if (FromPi0(ID, m_goodPi0List)) {
            return false;
        }
    }

    return true;
}

bool BesStdSelector::Photon::FromPi0(
    int ID, const std::vector<const EvtRecPi0*>& _pi0s) {
    const EvtRecPi0* aPi0;
    double mass, chisq;
    int tmp_id;
    for (unsigned i = 0; i < _pi0s.size(); ++i) {
        aPi0 = _pi0s[i];
        mass = aPi0->unconMass();
        if (mass < m_minPi0Mass || mass > m_maxPi0Mass) continue;

        chisq = aPi0->chisq();
        if (chisq > m_maxPi0Chisq) continue;

        // const EvtRecTrack* hiEnGamma = aPi0->hiEnGamma();
        // const EvtRecTrack* loEnGamma = aPi0->loEnGamma();
        tmp_id = const_cast<EvtRecTrack*>(aPi0->hiEnGamma())->trackId();
        if (ID == tmp_id) return true;

        tmp_id = const_cast<EvtRecTrack*>(aPi0->loEnGamma())->trackId();
        if (ID == tmp_id) return true;
    }

    return false;
}

BesStdSelector::Photon BesStdSelector::soloPhotonSelector;
/* ===================================================================<<< */
/* ======================== Photon.cpp ends here ======================== */
