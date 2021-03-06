/******************************************************************************
 * SIENA: Simulation Investigation for Empirical Network Analysis
 *
 * Web: http://www.stats.ox.ac.uk/~snijders/siena/
 *
 * File: XWXClosureEffect.cpp
 *
 * Description: This file contains the implementation of the
 * XWXClosureEffect class.
 *****************************************************************************/

#include "XWXClosureEffect.h"
#include "network/Network.h"
#include "data/NetworkLongitudinalData.h"
#include "network/IncidentTieIterator.h"
#include "data/DyadicCovariateValueIterator.h"
#include "model/variables/NetworkVariable.h"

namespace siena
{

/**
 * Constructor.
 */
XWXClosureEffect::XWXClosureEffect(const EffectInfo * pEffectInfo) :
	DyadicCovariateDependentNetworkEffect(pEffectInfo)
{
	this->ltwoPathSums = 0;
	this->linStarSums = 0;
}


/**
 * Destructor.
 */
XWXClosureEffect::~XWXClosureEffect()
{
	delete[] this->ltwoPathSums;
	delete[] this->linStarSums;
	this->ltwoPathSums = 0;
	this->linStarSums = 0;
}


/**
 * Initializes this effect.
 * @param[in] pData the observed data
 * @param[in] pState the current state of the dependent variables
 * @param[in] period the period of interest
 * @param[in] pCache the cache object to be used to speed up calculations
 */
void XWXClosureEffect::initialize(const Data * pData,
	State * pState,
	int period,
	Cache * pCache)
{
	DyadicCovariateDependentNetworkEffect::initialize(pData,
		pState,
		period,
		pCache);

	delete[] this->ltwoPathSums;
	delete[] this->linStarSums;
	this->ltwoPathSums = new double[this->pNetwork()->n()];
	this->linStarSums = new double[this->pNetwork()->n()];
}


/**
 * Does the necessary preprocessing work for calculating the tie flip
 * contributions for a specific ego. This method must be invoked before
 * calling NetworkEffect::calculateTieFlipContribution(...).
 */
void XWXClosureEffect::preprocessEgo(int ego)
{
	DyadicCovariateDependentNetworkEffect::preprocessEgo(ego);
	this->calculateTwoPathSums(ego, this->pNetwork(), this->ltwoPathSums);
	this->calculateInStarSums(ego, this->pNetwork(), this->linStarSums);
}


/**
 * For each j and the given i, this method calculates the sum
 * sum_h x_{ih} w_{hj}.
 */
void XWXClosureEffect::calculateTwoPathSums(int i,
	const Network * pNetwork,
	double * sums) const
{
	int n = pNetwork->n();

	// Initialize

	for (int j = 0; j < n; j++)
	{
		sums[j] = 0;
	}

	// Iterate over all h with x_{ih} = 1

	for (IncidentTieIterator iterH = pNetwork->outTies(i);
		iterH.valid();
		iterH.next())
	{
		int h = iterH.actor();

		// Iterate over all j with non-zero non-missing w_{hj}

		for (DyadicCovariateValueIterator iterJ = this->rowValues(h);
			iterJ.valid();
			iterJ.next())
		{
			int j = iterJ.actor();

			// Add the term x_{ih} w_{hj} (= w_{hj})
			sums[j] += iterJ.value();
		}
	}
}


/**
 * For each j and the given i, this method calculates the sum
 * sum_h x_{ih} w_{jh}.
 */
void XWXClosureEffect::calculateInStarSums(int i,
	const Network * pNetwork,
	double * sums) const
{
	int n = pNetwork->n();

	// Initialize

	for (int j = 0; j < n; j++)
	{
		sums[j] = 0;
	}

	// Iterate over all h with x_{ih} = 1

	for (IncidentTieIterator iterH = pNetwork->outTies(i);
		iterH.valid();
		iterH.next())
	{
		int h = iterH.actor();

		// Iterate over all j with non-zero non-missing w_{jh}

		for (DyadicCovariateValueIterator iterJ = this->columnValues(h);
			iterJ.valid();
			iterJ.next())
		{
			int j = iterJ.actor();

			// Add the term x_{ih} w_{jh} (= w_{jh})
			sums[j] += iterJ.value();
		}
	}
}


/**
 * Calculates the contribution of a tie flip to the given actor.
 */
double XWXClosureEffect::calculateContribution(int alter) const
{
	return this->ltwoPathSums[alter] + this->linStarSums[alter];
}


/**
 * The contribution of the tie from the implicit ego to the given alter
 * to the statistic. It is assumed that preprocessEgo(ego) has been
 * called before.
 */
double XWXClosureEffect::tieStatistic(int alter)
{
	return this->ltwoPathSums[alter];
}

}
