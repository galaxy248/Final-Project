#include <iostream>

using namespace std;

class Matrix
{
private:
	float* myMatrix{};
	int matrixRow{}, matrixCol{};
	enum { colss = 5 };
public:
	//constructor
	Matrix(int row = 1, int col = 1)
	{
		if (row <= 0 || col <= 0)
		{
			// throw
		}
		else
		{
			matrixRow = row;
			matrixCol = col;
			int k = 0;
			myMatrix = new float[row * col];
			for (int count = 0; count < row; count++)
			{
				float* tempRow = &myMatrix[count * col];

				for (int inner_count = 0; inner_count < col; inner_count++)
				{
					float* element = &tempRow[inner_count];
					if (count == 1 && inner_count == 4)
					{
						*element = 8;
						continue;
					}
					*element = k;
					k++;
				}
			}
		}
	}
	// copy constructor
	Matrix(Matrix& m)
	{
		if (m.matrixCol <= 0 || m.matrixRow <= 0)
		{
			// throw
		}
		else
		{
			matrixRow = m.matrixRow;
			matrixCol = m.matrixCol;
			myMatrix = new float[m.matrixRow * m.matrixCol];
			for (int count = 0; count < m.matrixRow; count++)
			{
				float* tempRow = &myMatrix[count * m.matrixCol];

				for (int inner_count = 0; inner_count < m.matrixCol; inner_count++)
				{
					float* element = &tempRow[inner_count];
					if (count == 1 && inner_count == 4)
					{
						*element = 8;
						continue;
					}
					*element = m[count][inner_count];
				}
			}
		}
	}

	int getCol() 
	{
		return matrixCol;
	}

	int getRow() 
	{
		return matrixRow;
	}
	// operator []
	float* (operator[](int i))
	{
		return &myMatrix[i*matrixCol];
	}
	// operator =
	// work for a[i + 1][j + 1] instead of a[i][j]
	Matrix* (operator=(float i))
	{
		*this = i;
		return this;
	}
	// operator ==
	// Not Working !
	Matrix* (operator==(float m))
	{
		cout << "here";
		if (*this == m)
		{
			cout << "yes";
		}
		else
		{
			cout << "no";
		}
	}

	void print()
	{
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
			float* tempRow = &myMatrix[count * matrixCol];
			cout << count + 1 << " | ";
			for (int inner_count = 0; inner_count < matrixCol; inner_count++)
			{
				float* element = &tempRow[inner_count];
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
	Matrix a(4, 3);
	a[3][2] = 12.56; // change to -> a[4][3] !
	Matrix k = a;
	a[3][2] == 12.56; // not working
	k.print();
	cout << "\n";
	a.print();
	return 0;
}
