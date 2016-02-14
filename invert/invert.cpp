#include "stdafx.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/assignment.hpp>
#include <boost/numeric/ublas/io.hpp>


using namespace boost::numeric::ublas;
using namespace std;

template<class T>
bool InvertMatrix(const matrix<T>& input, matrix<T>& inverse)
{
	typedef permutation_matrix<std::size_t> pmatrix;

	matrix<T> A(input);
	pmatrix pm(A.size1());

	int res = lu_factorize(A, pm);
	if (res != 0)
		return false;
	inverse.assign(identity_matrix<T>(A.size1()));
	lu_substitute(A, pm, inverse);

	return true;
}

#include "storage_adapters.h"

int main()
{
	double initialValues[3][3] = {
		0, 0, 0,
		0, 0, 0,
		0, 0, 0
	};

	matrix<double> A(3, 3), Z(3, 3);

	A = make_matrix_from_pointer(initialValues); 
	InvertMatrix(A, Z);

	cout << "A=" << A << endl << "Z=" << Z << endl;
    return 0;
}

