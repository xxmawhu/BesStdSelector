/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Electron.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-09-06 Fri 16:12:54 CST
 * <<=====================================>>
 * Last Updated: 2019-12-08 Sun 19:48:42 CST
 *           By: Hao-Kai SUN
 *     Update #: 53
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
#ifndef OMEGAXIK_SELECTOR_ELECTRON_HPP
#define OMEGAXIK_SELECTOR_ELECTRON_HPP

#include "OmegaXiKAlg/Namespace.hpp"
// #include "BesDChain/CDElectron.h"
// #include "DecayChain/Function/DCSelectionFunction.h"
#include "OmegaXiKAlg/selector/DCSFBase.hpp"

class OmegaXiKSLT::Electron : public DCSFElectron
{
  public:
    Electron();

    inline void setCharge(int chr) { m_charge = chr; }

    bool operator()(CDElectron& aElectron);

  private:
    Electron(const Electron&);
    const Electron& operator=(const Electron&);

    int m_charge;

    bool m_useVCut;
    double m_VrCut;
    double m_VzCut;
    double m_CosThetaCut;

    bool m_useEvPCut;
    double m_minEvP;

    bool m_usePID;
    double m_majorProb;
};

extern OmegaXiKSLT::Electron omegaXiKSelectorElectron;

#endif /* OMEGAXIK_SELECTOR_ELECTRON_HPP */
/* ===================================================================<<< */
/* ============= Electron.hpp ends here ============== */
