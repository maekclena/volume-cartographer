#pragma once

#ifndef _VOLCART_SEGMENTATION_FITTED_CURVE_H_
#define _VOLCART_SEGMENTATION_FITTED_CURVE_H_

#include <vector>
#include <tuple>
#include <cinttypes>
#include <iostream>
#include <Eigen/Dense>

namespace volcart {

namespace segmentation {

// Simple curve fitting using nonlinear least squares
template <typename TPoint=double, int32_t Degree=12>
class FittedCurve {
public:
    using TInputPoints = std::vector<std::tuple<TPoint, TPoint>>;

    FittedCurve() { }

    FittedCurve(const TInputPoints& points)
    {
        fitPoints(points);
    }

    // Fit 'points' and generate coefficients for polynomial curve
    void fitPoints(const TInputPoints& points)
    {
        std::tie(x_, y_) = make_matrices(points);    

        // Seems to use least squares computation. Check Eigen documentation for
        // the Eigen::ComputeThinU/V.
        Eigen::VectorXd a = x_.jacobiSvd(Eigen::ComputeFullU | Eigen::ComputeFullV).solve(y_);
        std::cout << a << std::endl;
        for (uint32_t i = 0; i < a.size(); ++i) {
            coefficients_.push_back(a(i));
        }
    }

    // Evaluate the polynomial at 'x'
    TPoint at(TPoint x) const
    {
        auto y = coefficients_.at(0);
        for (size_t i = 1; i < coefficients_.size(); ++i) {
            y += coefficients_.at(i) * std::pow(x, i);
        }
        return y;
    }

    // Pretty printing
    friend std::ostream& operator<<(std::ostream& s, FittedCurve& f)
    {
        s << std::fixed;
        s << *(f.coefficients_.begin()) << " + ";
        for (size_t i = 1; i < f.coefficients_.size() - 1; ++i) {
            s << f.coefficients_.at(i) << "*x" << i << " + ";
        }
        return s << *(f.coefficients_.end()) << "*x" << f.coefficients_.size() - 1;
    }

private:
    // Create the matrices for use later on in generating poly coefficients
    std::tuple<Eigen::MatrixXd, Eigen::VectorXd> make_matrices(
            const TInputPoints& points) const
    {
        Eigen::MatrixXd x(points.size(), Degree + 1);
        Eigen::VectorXd y(points.size());
        for (size_t i = 0; i < points.size(); ++i) {
            for (int32_t d = 0; d < Degree + 1; ++d) {
                x(i, d) = std::pow(std::get<0>(points.at(i)), d);
            }
            y(i) = std::get<1>(points.at(i));
        }
        std::cout << x << std::endl;
        std::cout << y << std::endl;
        return std::make_tuple(x, y);
    }

    std::vector<TPoint> coefficients_;
    Eigen::MatrixXd x_;
    Eigen::VectorXd y_;
};

}

}

#endif
