/******************************************************************************
 * SIENA: Simulation Investigation for Empirical Network Analysis
 *
 * Web: http://www.stats.ox.ac.uk/~snijders/siena/
 *
 * File: siena07models.h
 *
 * Description: This file contains prototypes for the siena simulation
 * modelling functions called from R
 *****************************************************************************/

#ifndef SIENA07MODELS_H_
#define SIENA07MODELS_H_

/**
 *  Does one forward simulation for all the data by period within group
 */
SEXP model(SEXP DERIV, SEXP DATAPTR, SEXP SEEDS,
	SEXP FROMFINITEDIFF, SEXP MODELPTR, SEXP EFFECTSLIST,
	SEXP THETA, SEXP RANDOMSEED2, SEXP RETURNDEPS, SEXP NEEDSEEDS,
	SEXP USESTREAMS, SEXP ADDCHAINTOSTORE, SEXP NEEDCHANGECONTRIBUTIONS);

/** Does some MH steps for a specified group and period.
 *  For multiple periods, the loop is always constructed in R.
 */
SEXP mlPeriod(SEXP DERIV, SEXP DATAPTR,
	SEXP MODELPTR, SEXP EFFECTSLIST,
	SEXP THETA, SEXP GROUP, SEXP PERIOD,
	SEXP NRUNMH, SEXP ADDCHAINTOSTORE, SEXP NEEDCHANGECONTRIBUTIONS,
	SEXP RETURNDATAFRAME, SEXP RETURNCHAINS, SEXP RETURNLOGLIK);


SEXP clearStoredChains(SEXP MODELPTR);

SEXP getChainProbabilities(SEXP CHAIN, SEXP DATAPTR, SEXP MODELPTR,
	SEXP GROUP, SEXP PERIOD, SEXP EFFECTSLIST, SEXP THETA);

#endif /*SIENA07MODELS_H_*/
