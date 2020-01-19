/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    TypicalTag.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-09-07 Sat 12:51:35 CST
 * <<=====================================>>
 * Last Updated: 2019-11-21 Thu 21:11:31 CST
 *           By: Hao-Kai SUN
 *     Update #: 11
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
#ifndef BesStdSelector_TypicalTag_HPP
#define BesStdSelector_TypicalTag_HPP

#include "BesDChain/CDDecay.h"
#include "DecayChain/Function/DCSelectionFunction.h"
#include "BesStdSelector/BesStdSelector.h"
#include <string>

class BesStdSelector::TypicalTag : public DCSelectionFunction<CDDecay> {
   public:
    TypicalTag(const std::string&);

    bool operator()(CDDecay& aTypicalTag);
    void setEcm(const double& Ecm) { m_Ecm = Ecm; }

   private:
    TypicalTag(const TypicalTag&);
    const TypicalTag& operator=(const TypicalTag&);

    bool m_cutMass;
    double m_minMass;
    double m_maxMass;

    double m_Ecm;
    bool m_cutMbc;
    double m_minMbc, m_maxMbc;

    bool m_cutRecMass;
    double m_minRecMass, m_maxRecMass;

    bool m_cutDeltaE;
    double m_minDeltaE, m_maxDeltaE;
};

#endif /* BesStdSelector_TypicalTag_HPP */
/* ===================================================================<<< */
/* ========================== TypicalTag.hpp ends here
 * ========================== */
