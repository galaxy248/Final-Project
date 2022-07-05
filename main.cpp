#include <iostream>

using namespace std;

class Matrix
{
private:
	double* myMatrix{};
	int matrixRow{}, matrixCol{};

public:
	Matrix(int row = 1, int col = 1)
	{
		if (row <= 0 || col <= 0) {
			throw 0;
		}
		else {
			matrixRow = row;
			matrixCol = col;
			int k = 0;
			myMatrix = new double[row * col];
			for (int count = 0; count < row; count++) {
				double* tempRow = &myMatrix[count * col];
				for (int inner_count = 0; inner_count < col; inner_count++) {
					double* element = &tempRow[inner_count];
					if (count == 1 && inner_count == 4) {
						*element = 8;
						continue;
					}
					*element = k;
					k++;
				}
			}
		}
	}

	Matrix(Matrix& m)
	{
		if (m.matrixCol <= 0 || m.matrixRow <= 0) {
			throw 0;
		}
		else
		{
			matrixRow = m.matrixRow;
			matrixCol = m.matrixCol;
			myMatrix = new double[m.matrixRow * m.matrixCol];
			for (int count = 0; count < m.matrixRow; count++) {
				double* tempRow = &myMatrix[count * m.matrixCol];
				for (int inner_count = 0; inner_count < m.matrixCol; inner_count++) {
					double* element = &tempRow[inner_count];
					if (count == 1 && inner_count == 4) {
						*element = 8;
						continue;
					}
					*element = m[count][inner_count];
				}
			}
		}
	}

	double* (operator[](int i))
	{
		return &myMatrix[(i)*matrixCol];
	}

	void print() {
		cout << "      \t";
		for (int i = 0; i < matrixCol; i++)
		{
			cout << i + 1 << "\t";
		}
		cout << "\n";
		for (int i = 0; i < matrixCol * 9; i++)
		{
			cout << "-";
		}
		cout << "\n";
		for (int count = 0; count < matrixRow; count++)
		{
			double* tempRow = &myMatrix[count * matrixCol];
			cout << count + 1 << " | ";
			for (int inner_count = 0; inner_count < matrixCol; inner_count++)
			{
				double* element = &tempRow[inner_count];
				cout << "\t" << *element << " ";
			}
			cout << "\n";
		}
	}

	~Matrix()
	{
		delete[] myMatrix;
	}
};

int main()
{
	try
	{
		Matrix a(2, 3);
		/*
		*       /1/      /2/      /3/
		* /1/ [0][0]=0 [0][1]=1 [0][2]=2
		* /2/ [1][0]=3 [1][1]=4 [1][2]=5
		* 
		*/
		a[1][2] = 15.78;
		/*
		*       /1/      /2/      /3/
		* /1/ [0][0]=0 [0][1]=1 [0][2]=2
		* /2/ [1][0]=3 [1][1]=4 [1][2]=15.78
		*
		*/
		Matrix b = a;
		/*
		*       /1/      /2/      /3/
		* /1/ [0][0]=0 [0][1]=1 [0][2]=2
		* /2/ [1][0]=3 [1][1]=4 [1][2]=15.78
		*
		*/
		b[0][0] = 20.81;
		/*
		*       /1/          /2/      /3/
		* /1/ [0][0]=20.81 [0][1]=1 [0][2]=2
		* /2/ [1][0]=3     [1][1]=4 [1][2]=15.78
		*
		*/
		Matrix c;
		/*
		*       /1/    
		* /1/ [0][0]=0 
		*
		*/
		Matrix d(4, 3);
		/*
		*       /1/      /2/       /3/
		* /1/ [0][0]=0 [0][1]=1  [0][2]=2
		* /2/ [1][0]=3 [1][1]=4  [1][2]=5
		* /3/ [2][0]=6 [2][1]=7  [2][2]=8
		* /4/ [3][0]=9 [3][1]=10 [3][2]=11
		*
		*/
		a.print();
		cout << "\n";
		b.print();
		cout << "\n";
		c.print();
		cout << "\n";
		d.print();
		cout << "\n";
		if (a[1][1] == 4)
			cout << "YES\n";
		else
			cout << "NO\n";
		if (b[0][0] == 20.81)
			cout << "YES\n";
		else
			cout << "NO\n";
		if (b[0][0] == 1)
			cout << "YES\n";
		else
			cout << "NO\n";
		if (c[0][0] == 0)
			cout << "YES\n";
		else
			cout << "NO\n";
		if (d[3][0] == 10)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	catch (const int n)
	{
		if (n == 0) {
			cout << "ROW or COL of your matrix is greather than zero";
		}
	}
	return 0;
}
