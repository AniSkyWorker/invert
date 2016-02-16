#include "stdafx.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/assignment.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <fstream>
#include <iomanip>

 
template<class T>
bool InvertMatrix(const  boost::numeric::ublas::matrix<T>& input, boost::numeric::ublas::matrix<T>& inverse)
{
	typedef  boost::numeric::ublas::permutation_matrix<std::size_t> pmatrix;

	boost::numeric::ublas::matrix<T> A(input);
	pmatrix pm(A.size1());

	auto res = boost::numeric::ublas::lu_factorize(A, pm);
	if (res != 0)
		return false;
	inverse.assign(boost::numeric::ublas::identity_matrix<T>(A.size1()));
	boost::numeric::ublas::lu_substitute(A, pm, inverse);

	return true;
}

#include "storage_adapters.h"

int main(int argc,char * argv[])
{
	float inputArray[3][3];
	std::ifstream inputFile(argv[1]);

	if (inputFile.is_open())
	{
		for (std::size_t i = 0; i < 3; i++)
			for (std::size_t j = 0; j < 3; j++)
				inputFile >> inputArray[i][j];
		if (inputFile.fail())
		{
			std::cout << "Incorrect matrix in file!";
			return 1;
		}
	}
	else
	{
		std::cout << "Incorrect name of file!";
		return 1;
	}

	boost::numeric::ublas::matrix<float> inputMat(3, 3), inverseMat(3, 3);

	inputMat = boost::numeric::ublas::make_matrix_from_pointer(inputArray);
	if (InvertMatrix(inputMat, inverseMat))
		std::cout << std::setprecision(3) << "Inverted matrix =" << inverseMat << std::endl;
	else
	{
		std::cout << "Inputted matrix cannot be inverted";
		return 1;
	}
    return 0;
}

