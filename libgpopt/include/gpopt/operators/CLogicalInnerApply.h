//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright 2011 EMC Corp.
//
//	@filename:
//		CLogicalInnerApply.h
//
//	@doc:
//		Logical Inner Apply operator
//---------------------------------------------------------------------------
#ifndef GPOPT_CLogicalInnerApply_H
#define GPOPT_CLogicalInnerApply_H

#include "gpos/base.h"
#include "gpopt/operators/CLogicalApply.h"
#include "gpopt/operators/CExpressionHandle.h"

namespace gpopt
{


	//---------------------------------------------------------------------------
	//	@class:
	//		CLogicalInnerApply
	//
	//	@doc:
	//		Logical Apply operator used in scalar subquery transformations
	//
	//---------------------------------------------------------------------------
	class CLogicalInnerApply : public CLogicalApply
	{

		private:
			// private copy ctor
			CLogicalInnerApply(const CLogicalInnerApply &);

		public:

			// ctor for patterns
			explicit
			CLogicalInnerApply(IMemoryPool *mp);

			// ctor
			CLogicalInnerApply(IMemoryPool *mp, CColRefArray *pdrgpcrInner, EOperatorId eopidOriginSubq);

			// dtor
			virtual
			~CLogicalInnerApply();

			// ident accessors
			virtual
			EOperatorId Eopid() const
			{
				return EopLogicalInnerApply;
			}

			// return a string for operator name
			virtual
			const CHAR *SzId() const
			{
				return "CLogicalInnerApply";
			}

			// return a copy of the operator with remapped columns
			virtual
			COperator *PopCopyWithRemappedColumns(IMemoryPool *mp, UlongToColRefMap *colref_mapping, BOOL must_exist);

			//-------------------------------------------------------------------------------------
			// Derived Relational Properties
			//-------------------------------------------------------------------------------------

			// derive output columns
			virtual
			CColRefSet *PcrsDeriveOutput
				(
				IMemoryPool *mp,
				CExpressionHandle &exprhdl
				)
			{
				GPOS_ASSERT(3 == exprhdl.Arity());

				return PcrsDeriveOutputCombineLogical(mp, exprhdl);
			}

			// derive not nullable columns
			virtual
			CColRefSet *PcrsDeriveNotNull
				(
				IMemoryPool *mp,
				CExpressionHandle &exprhdl
				)
				const
			{
				return PcrsDeriveNotNullCombineLogical(mp, exprhdl);
			}

			// derive max card
			virtual
			CMaxCard Maxcard(IMemoryPool *mp, CExpressionHandle &exprhdl) const;

			// derive constraint property
			virtual
			CPropConstraint *PpcDeriveConstraint
				(
				IMemoryPool *mp,
				CExpressionHandle &exprhdl
				)
				const
			{
				return PpcDeriveConstraintFromPredicates(mp, exprhdl);
			}

			//-------------------------------------------------------------------------------------
			// Transformations
			//-------------------------------------------------------------------------------------

			// candidate set of xforms
			virtual
			CXformSet *PxfsCandidates(IMemoryPool *) const;

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------

			// conversion function
			static
			CLogicalInnerApply *PopConvert
				(
				COperator *pop
				)
			{
				GPOS_ASSERT(NULL != pop);
				GPOS_ASSERT(EopLogicalInnerApply == pop->Eopid());

				return dynamic_cast<CLogicalInnerApply*>(pop);
			}

	}; // class CLogicalInnerApply

}


#endif // !GPOPT_CLogicalInnerApply_H

// EOF
