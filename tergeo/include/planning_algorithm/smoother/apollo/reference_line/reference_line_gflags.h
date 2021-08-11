//wz added for compiling, move to config proto later.
#pragma once

class ConstParameter{
public:
    static int qp_spline_order;
    static bool use_osqp_optimizer_for_reference_line;
    static bool enable_reference_line_stitching;
    static double qp_spline_regularization_weight;
    static double qp_spline_second_derivative_weight;
    static double qp_spline_third_derivative_weight;
    static double qp_spline_max_spline_length;
    static double result_sample_resolution;
};
