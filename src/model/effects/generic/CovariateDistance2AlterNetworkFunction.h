/******************************************************************************
 * SIENA: Simulation Investigation for Empirical Network Analysis
 *
 * Web: http://www.stats.ox.ac.uk/~snijders/siena/
 *
 * File: CovariateDistance2AlterNetworkFunction.h
 *
 * Description: This file contains the definition of the
 * CovariateDistance2AlterNetworkFunction class.
 *****************************************************************************/

#ifndef COVARIATEDISTANCE2ALTERNETWORKFUNCTION_H_
#define COVARIATEDISTANCE2ALTERNETWORKFUNCTION_H_

#include "CovariateDistance2NetworkFunction.h"

namespace siena
{


class CovariateDistance2AlterNetworkFunction: public
	CovariateDistance2NetworkFunction
{
public:
	CovariateDistance2AlterNetworkFunction(string networkName,
		string covariateName, double parameter, bool excludeMissing);

	virtual double value(int alter);


private:
	double lparameter;
	bool lexcludeMissing;
};

}

#endif /* COVARIATEDISTANCE2ALTERNETWORKFUNCTION_H_ */
