/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2004, 2005, 2006, 2007 StatPro Italia srl

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

#include <ql/termstructure.hpp>
#include <ql/math/comparison.hpp>

namespace {
    QuantLib::Real Time2Date = 365.0;
    QuantLib::BigInteger maxSerial = QuantLib::Date::maxDate().serialNumber();
}

namespace QuantLib {

    TermStructure::TermStructure(const Date& referenceDate)
    : moving_(false), updated_(true),
      calendar_(Calendar()), settlementDays_(Null<Natural>()),
      referenceDate_(referenceDate) {}

    TermStructure::TermStructure(Natural settlementDays,
                                 const Calendar& cal)
    : moving_(true), updated_(false),
      calendar_(cal), settlementDays_(settlementDays)
    {
        registerWith(Settings::instance().evaluationDate());
    }

    Time TermStructure::timeFromReference(const Date& d) const {
        return (d-referenceDate())/Time2Date;
    }

    Date TermStructure::dateFromTime(Time t) const {
        BigInteger result = std::min<BigInteger>(maxSerial, 
            referenceDate().serialNumber() + BigInteger(t*Time2Date));
        return Date(result);
    }

    const Date& TermStructure::referenceDate() const {
        if (!updated_) {
            Date today = Settings::instance().evaluationDate();
            referenceDate_ = calendar_.advance(today, settlementDays(), Days);
            updated_ = true;
        }
        return referenceDate_;
    }

    void TermStructure::update() {
        if (moving_)
            updated_ = false;
        notifyObservers();
    }

    void TermStructure::checkRange(const Date& d,
                                   bool extrapolate) const {
        QL_REQUIRE(d >= referenceDate(),
                   "date (" << d << ") before reference date (" <<
                   referenceDate() << ")");
        QL_REQUIRE(extrapolate || allowsExtrapolation() || d <= maxDate(),
                   "date (" << d << ") is past max curve date ("
                            << maxDate() << ")");
    }

    void TermStructure::checkRange(Time t,
                                   bool extrapolate) const {
        QL_REQUIRE(t >= 0.0,
                   "negative time (" << t << ") given");
        QL_REQUIRE(extrapolate || allowsExtrapolation()
                   || t <= maxTime() || close_enough(t, maxTime()),
                   "time (" << t << ") is past max curve time ("
                            << maxTime() << ")");
    }

}
