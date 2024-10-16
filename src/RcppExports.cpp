// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// MT_CPP
Rcpp::NumericVector MT_CPP(unsigned int seed, unsigned int n);
RcppExport SEXP _Random_MT_CPP(SEXP seedSEXP, SEXP nSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< unsigned int >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type n(nSEXP);
    rcpp_result_gen = Rcpp::wrap(MT_CPP(seed, n));
    return rcpp_result_gen;
END_RCPP
}
// MT
Rcpp::NumericVector MT(unsigned int seed, unsigned int n);
RcppExport SEXP _Random_MT(SEXP seedSEXP, SEXP nSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< unsigned int >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type n(nSEXP);
    rcpp_result_gen = Rcpp::wrap(MT(seed, n));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_Random_MT_CPP", (DL_FUNC) &_Random_MT_CPP, 2},
    {"_Random_MT", (DL_FUNC) &_Random_MT, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_Random(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
