#ifndef _TERGEO_PLANNING_ALGORITHM_CUBIC_SPLINE_H_
#define _TERGEO_PLANNING_ALGORITHM_CUBIC_SPLINE_H_

#include <vector>
#include <cmath>
#include <math.h>
#include <Eigen/Dense>

namespace tergeo {
namespace planning {
namespace algorithm {

//reference:https://meshlogic.github.io/posts/jupyter/curve-fitting/parametric-curve-fitting/
class ParametricSpline{
public:
	ParametricSpline(){}
	~ParametricSpline(){}
	void setKnotPoints(std::vector<Eigen::Vector2d>&knots);
	void runParamFitting(int iter_num);
	std::vector<Eigen::Vector2d> getFittingPts(int interpolate_size,std::vector<double>& knots_u);
	std::vector<double> getFXcoeff(){return _fxcoeff;}
	std::vector<double> getFYcoeff(){return _fycoeff;}
private:
	std::vector<double> getUniformParam(int knots_size);
	std::vector<double> getChordlengthParam();
	std::vector<double> getCentripetalParam();
	std::vector<double> generateParams(double alpha);

	void iterativeParam();
	double loss(double u, const Eigen::Vector2d& knot_pt);
	std::vector<double> polyfit(std::vector<double> xvals,
	                            std::vector<double> yvals,
	                            std::vector<double> weights, int order);
	double polyeval(std::vector<double> coeffs, double x);
private:
	std::vector<Eigen::Vector2d> _knot_pts;
	std::vector<double> _xvals;
	std::vector<double> _yvals;

	std::vector<double> _u;
	std::vector<double> _fxcoeff;
	std::vector<double> _fycoeff;
};


}
}
}

#endif