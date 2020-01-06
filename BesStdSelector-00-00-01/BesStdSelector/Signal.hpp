/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Signal.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-12-06 Fri 14:24:09 CST
 * <<=====================================>>
 * Last Updated: 2019-12-07 Sat 17:46:18 CST
 *           By: Hao-Kai SUN
 *     Update #: 15
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
#ifndef OMEGAXIK_SELECTOR_SIGNAL_HPP
#define OMEGAXIK_SELECTOR_SIGNAL_HPP

#include "OmegaXiKAlg/Namespace.hpp"
#include "OmegaXiKAlg/selector/DCSFBase.hpp"

class OmegaXiKSLT::Signal : public DCSFDecay
{
  public:
    Signal();

    bool operator()(CDDecay& aSignal);
    inline void setEcm(const double& _ecm) { m_Ecm = _ecm; }

  private:
    Signal(const Signal&);
    const Signal& operator=(const Signal&);

    double m_Ecm;

    double m_minRecMass;
    double m_maxRecMass;
};

extern OmegaXiKSLT::Signal omegaXiKSelectorSignal;

#endif /* OMEGAXIK_SELECTOR_SIGNAL_HPP */
/* ===================================================================<<< */
/* ======================== Signal.hpp ends here ======================== */
