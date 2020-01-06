/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorGoodChrTrkSelector.h
#   Created Time  : 2019-10-23 15:48
#   Last Modified : 2019-10-23 15:48
#   Describe      :
#
# ====================================================*/

#ifndef BeSelector_GoodChrTrk_SELECTOR_H
#define BeSelector_GoodChrTrk_SELECTOR_H

#include "BesDChain/CDElectron.h"
#include "DecayChain/Function/DCSelectionFunction.h"

class BeSelectorGoodChrTrkSelector : public DCSelectionFunction<CDElectron> {

   public:
    BeSelectorGoodChrTrkSelector();

    bool operator()(CDElectron &aEle);
    inline void setcharge(int chr) { m_charge = chr; }

   private:
    BeSelectorGoodChrTrkSelector(const BeSelectorGoodChrTrkSelector &);
    const BeSelectorGoodChrTrkSelector &operator=(
        const BeSelectorGoodChrTrkSelector &);

    int m_charge;
    int m_pidtype;

    double m_VrCut;
    double m_VzCut;
    double m_CosThetaCut;

    double m_minEvP;

    bool m_PID;
    bool m_VCut;
    bool m_CutEvP;
};

extern BeSelectorGoodChrTrkSelector beSelectorGoodChrTrkSelector;

#endif
