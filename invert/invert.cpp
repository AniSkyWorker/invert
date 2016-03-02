#include "stdafx.h"
#include "storage_adapters.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/assignment.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <iomanip>
#include <fstream>

const int C_MATRIX_SIZE = 3;
namespace ublas = boost::numeric::ublas;
typedef boost::numeric::ublas::matrix<float> floatMatrix;

bool InvertMatrix(const floatMatrix& inputMatrix, floatMatrix& inverseMatrix)
{
	typedef ublas::permutation_matrix<std::size_t> permutation_matrix_t;

	ublas::matrix<float> matrix(inputMatrix);
	permutation_matrix_t permutationMatrix(matrix.size1());

	auto det = ublas::lu_factorize(matrix, permutationMatrix);
	if (det != 0)
	{
		return false;
	}

	inverseMatrix.assign(ublas::identity_matrix<float>(matrix.size1()));
	ublas::lu_substitute(matrix, permutationMatrix, inverseMatrix);

	return true;
}

bool ReadMatrixFromFile(const std::string& fileName, float inputArray[C_MATRIX_SIZE][C_MATRIX_SIZE])
{
	std::ifstream inputFile(fileName);

	if (inputFile.is_open())
	{
		for (std::size_t i = 0; i < C_MATRIX_SIZE; i++)
		{
			for (std::size_t j = 0; j < C_MATRIX_SIZE; j++)
			{
				inputFile >> inputArray[i][j];
			}
		}

		if (inputFile.fail())
		{
			std::cout << "Incorrect matrix in file!" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "Incorrect name of file!" << std::endl;
		return false;
	}

	return true;
}

int main(int argc,char * argv[])
{
	if (argc != 2)
	{
		std::cout << "Incorrect inputted arguments!" << std::endl
			<< "Usage: invert.exe <inputFile>" << std::endl;
		return 1;
	}

	float inputArray[C_MATRIX_SIZE][C_MATRIX_SIZE];

	if (!ReadMatrixFromFile(argv[1], inputArray))
	{
		return 1;
	}

	floatMatrix inputMat(C_MATRIX_SIZE, C_MATRIX_SIZE), inverseMat(C_MATRIX_SIZE, C_MATRIX_SIZE);
	inputMat = ublas::make_matrix_from_pointer(inputArray);

	if (InvertMatrix(inputMat, inverseMat))
	{
		std::cout << std::setprecision(3) << "Inverted matrix =" << inverseMat << std::endl;
	}
	else
	{
		std::cout << "Inputted matrix cannot be inverted" << std::endl;
		return 1;
	}

    return 0;
}

