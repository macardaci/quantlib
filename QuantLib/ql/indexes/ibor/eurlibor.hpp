/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2007, 2015 Ferdinando Ametrano
 Copyright (C) 2006, 2007 Chiara Fornarola
 Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl
 Copyright (C) 2003, 2004, 2005, 2006 StatPro Italia srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file eurlibor.hpp
    \brief %EUR %LIBOR rate
*/

#ifndef quantlib_eur_libor_hpp
#define quantlib_eur_libor_hpp

#include <ql/indexes/iborindex.hpp>

namespace QuantLib {

    //! base class for all BBA %EUR %LIBOR indexes but the O/N
    /*! Euro LIBOR fixed by BBA.

        See <http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1414>.

        \warning This is the rate fixed in London by BBA. Use Euribor if
                 you're interested in the fixing by the ECB.
    */
    class EURLibor : public IborIndex {
      public:
        EURLibor(const Period& tenor,
                 const Handle<ForwardRateCurve>& h =
                                    Handle<ForwardRateCurve>());
        EURLibor(const Period& tenor,
                 const Handle<YieldTermStructure>& h);
        /*! \name Date calculations

            see http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1412
            @{
        */
        Date valueDate(const Date& fixingDate) const;
        Date maturityDate(const Date& valueDate) const;
        // @}
      private:
        Calendar target_;
    };

    //! base class for the one day deposit BBA %EUR %LIBOR indexes
    /*! Euro O/N LIBOR fixed by BBA. It can be also used for T/N and S/N
        indexes, even if such indexes do not have BBA fixing.

        See <http://www.bba.org.uk/bba/jsp/polopoly.jsp?d=225&a=1414>.

        \warning This is the rate fixed in London by BBA. Use Eonia if
                 you're interested in the fixing by the ECB.
    */
    class DailyTenorEURLibor : public IborIndex {
      public:
        DailyTenorEURLibor(Natural settlementDays,
                           const Handle<ForwardRateCurve>& h =
                                    Handle<ForwardRateCurve>());
        DailyTenorEURLibor(Natural settlementDays,
                           const Handle<YieldTermStructure>& h);
    };

    //! Overnight %EUR %Libor index
    class EURLiborON : public DailyTenorEURLibor {
      public:
        EURLiborON(const Handle<ForwardRateCurve>& h =
                                    Handle<ForwardRateCurve>())
        : DailyTenorEURLibor(0, h) {}
        EURLiborON(const Handle<YieldTermStructure>& h)
        : DailyTenorEURLibor(0, h) {}
    };

    //! 1-week %EUR %Libor index
    class EURLiborSW : public EURLibor {
      public:
        EURLiborSW(const Handle<ForwardRateCurve>& h =
                                    Handle<ForwardRateCurve>())
        : EURLibor(Period(1, Weeks), h) {}
        EURLiborSW(const Handle<YieldTermStructure>& h)
        : EURLibor(Period(1, Weeks), h) {}
    };

    //! 1-month %EUR %Libor index
    class EURLibor1M : public EURLibor {
      public:
        EURLibor1M(const Handle<ForwardRateCurve>& h =
                                    Handle<ForwardRateCurve>())
        : EURLibor(Period(1, Months), h) {}
        EURLibor1M(const Handle<YieldTermStructure>& h)
        : EURLibor(Period(1, Months), h) {}
    };

    //! 2-months %EUR %Libor index
    class EURLibor2M : public EURLibor {
      public:
        EURLibor2M(const Handle<ForwardRateCurve>& h =
                                    Handle<ForwardRateCurve>())
        : EURLibor(Period(2, Months), h) {}
        EURLibor2M(const Handle<YieldTermStructure>& h)
        : EURLibor(Period(2, Months), h) {}
    };

    //! 3-months %EUR %Libor index
    class EURLibor3M : public EURLibor {
      public:
        EURLibor3M(const Handle<ForwardRateCurve>& h =
                                    Handle<ForwardRateCurve>())
        : EURLibor(Period(3, Months), h) {}
        EURLibor3M(const Handle<YieldTermStructure>& h)
        : EURLibor(Period(3, Months), h) {}
    };

    //! 6-months %EUR %Libor index
    class EURLibor6M : public EURLibor {
      public:
        EURLibor6M(const Handle<ForwardRateCurve>& h =
                                    Handle<ForwardRateCurve>())
        : EURLibor(Period(6, Months), h) {}
        EURLibor6M(const Handle<YieldTermStructure>& h)
        : EURLibor(Period(6, Months), h) {}
    };

    //! 1-year %EUR %Libor index
    class EURLibor1Y : public EURLibor {
      public:
        EURLibor1Y(const Handle<ForwardRateCurve>& h =
                                    Handle<ForwardRateCurve>())
        : EURLibor(Period(1, Years), h) {}
        EURLibor1Y(const Handle<YieldTermStructure>& h)
        : EURLibor(Period(1, Years), h) {}
    };


}

#endif
