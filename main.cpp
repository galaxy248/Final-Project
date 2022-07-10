#include <iostream>

using namespace std;

class Matrix
{
private:
	double* myMatrix;
	int matrixRow, matrixCol;

public:
	Matrix(int row = 1, int col = 1)
	{
		if (row <= 0 || col <= 0) {
			throw 0;
		}
		else {
			matrixRow = row;
			matrixCol = col;
			double k = 0;
			myMatrix = new double[row * col];
			for (int count = 0; count < row; count++) {
				double* tempRow = &myMatrix[count * col];
				for (int inner_count = 0; inner_count < col; inner_count++) {
					double* element = &tempRow[inner_count];
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

	Matrix* operator=(Matrix m)
	{
		if (m.matrixCol != this->matrixCol || m.matrixRow != this->matrixRow)
			throw 1;

		for (int count = 0; count < m.matrixRow; count++) {
			double* tempRow = &this->myMatrix[count * m.matrixCol];
			for (int inner_count = 0; inner_count < m.matrixCol; inner_count++) {
				double* element = &tempRow[inner_count];
				*element = m[count][inner_count];
			}
		}
	}

	bool operator==(Matrix m)
	{
		if (m.matrixCol != this->matrixCol || m.matrixRow != this->matrixRow)
			return false;

		for (int count = 0; count < m.matrixRow; count++) {
			double* tempRow = &this->myMatrix[count * m.matrixCol];
			for (int inner_count = 0; inner_count < m.matrixCol; inner_count++) {
				double* element = &tempRow[inner_count];
				if (*element != m[count][inner_count]) {
					return false;
				}
			}
		}
		return true;
	}

	bool operator!=(Matrix m) 
		// can not use """return !(this == m)""" ->
		// Error : Matrix* == Matrix "==" no operator match
	{

		if (m.matrixCol != this->matrixCol || m.matrixRow != this->matrixRow)
			return !false;

		for (int count = 0; count < m.matrixRow; count++) {
			double* tempRow = &this->myMatrix[count * m.matrixCol];
			for (int inner_count = 0; inner_count < m.matrixCol; inner_count++) {
				double* element = &tempRow[inner_count];
				if (*element != m[count][inner_count]) {
					return !false;
				}
			}
		}
		return !true;
	}

	Matrix* operator*(Matrix* m)
	{
		if (m->matrixCol != this->matrixRow || m->matrixRow != this->matrixCol)
			throw 1;

		static Matrix temp(this->matrixRow, this->matrixCol);
		temp = *this;
		Matrix mTemp = *m;
		for (int i = 0; i < temp.matrixRow; i++) {
			double* tempRow = &(temp.myMatrix[i * temp.matrixCol]);
			double ans = 0;
			static int jTemp = 0;
			for (int z = 0; z < m->matrixCol; z++) {
				ans = 0;
				for (int j = 0; j < temp.matrixCol; j++) {
					double* element = &tempRow[j];
					ans += (*element) * (mTemp[j][z]);
				}
				temp[i][jTemp] = double(ans);
				jTemp++;
			}
			jTemp = 0;
		}
		return &temp;
	}

	Matrix* operator+(Matrix* m)
	{
		if (m->matrixRow != this->matrixRow || m->matrixCol != this->matrixCol)
			throw 2;

		static Matrix temp(this->matrixRow, this->matrixCol);
		temp = *this;
		Matrix mTemp = *m;
		for (int i = 0; i < temp.matrixRow; i++) {
			double* tempRow = &(temp.myMatrix[i * temp.matrixCol]);
			for (int j = 0; j < temp.matrixCol; j++) {
				double* element = &tempRow[j];
				(*element) += (mTemp[i][j]);
			}
		}
		return &temp;
	}

	Matrix* operator*(float p)
	{
		static Matrix temp(this->matrixRow, this->matrixCol);
		temp = *this;
		for (int i = 0; i < temp.matrixRow; i++) {
			double* tempRow = &(temp.myMatrix[i * temp.matrixCol]);
			for (int j = 0; j < temp.matrixCol; j++) {
				double* element = &tempRow[j];
				(*element) *= p;
			}
		}
		return &temp;
	}

	Matrix* operator*=(float p)
	{
		for (int i = 0; i < this->matrixRow; i++) {
			double* tempRow = &(this->myMatrix[i * this->matrixCol]);
			for (int j = 0; j < this->matrixCol; j++) {
				double* element = &tempRow[j];
				(*element) *= p;
			}
		}
		return this;
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
		Matrix b = a;
		/*
		*       /1/      /2/      /3/
		* /1/ [0][0]=0 [0][1]=1 [0][2]=2
		* /2/ [1][0]=3 [1][1]=4 [1][2]=5
		*
		*/
		b[0][0] = 20.81;
		b[1][2] = 15.78;
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
		Matrix e(3, 2);
		/*
		*       /1/      /2/     
		* /1/ [0][0]=0 [0][1]=1 
		* /2/ [1][0]=2 [1][1]=3 
		* /3/ [2][0]=4 [2][1]=5  
		*
		*/
		Matrix f(3, 2);
		/*
		*       /1/      /2/
		* /1/ [0][0]=0 [0][1]=1
		* /2/ [1][0]=2 [1][1]=3
		* /3/ [2][0]=4 [2][1]=5
		*
		*/

		if (a != b)
			cout << "Matrix a != Matrix b\n\n";
		else
			cout << "Matrix a == Matrix b\n\n";
		if (e == f)
			cout << "Matrix e == Matrix f\n\n";
		else
			cout << "Matrix e != Matrix f\n\n";

		Matrix* g{};
		g = f + &e;
		Matrix* h;
		h = a * &e;

		cout << "Matrix a :\n";
		a.print();
		cout << "\n";

		Matrix* i = a * 2;
		cout << "Matrix a*2 :\n";
		i->print();
		cout << "\n";

		a *= 2;
		a *= 2;
		cout << "Matrix a*2*2 :\n";
		a.print();
		cout << "\n";

		cout << "Matrix (a*2*2) * (e)\n";
		(a * &e)->print();
		cout << "\n";

		cout << "Matrix e :\n";
		e.print();
		cout << "\n";

		cout << "Matrix a*e :\n";
		h->print();
		cout << "\n";

		cout << "Matrix f+e :\n";
		g->print();
		cout << "\n";

		cout << "Matrix b :\n";
		b.print();
		cout << "\n";

		cout << "Matrix c :\n";
		c.print();
		cout << "\n";

		cout << "Matrix d :\n";
		d.print();
		cout << "\n";

		if (a[1][1] == 4)
			cout << "a[1][1] == 4 -> YES\n";
		else
			cout << "a[1][1] == 4 -> NO\n";
		if (b[0][0] == 20.81)
			cout << "b[0][0] == 20.81 -> YES\n";
		else
			cout << "b[0][0] == 20.81 -> NO\n";
		if (b[0][0] == 1)
			cout << "b[0][0] == 1 -> YES\n";
		else
			cout << "b[0][0] == 1 -> NO\n";
		if (c[0][0] == 0)
			cout << "c[0][0] == 0 -> YES\n";
		else
			cout << "c[0][0] == 0 -> NO\n";
		if (d[3][0] == 10)
			cout << "d[3][0] == 10 -> YES\n";
		else
			cout << "d[3][0] == 10 -> NO\n";
	}
	catch (const int n)
	{
		if (n == 0) {
			cout << "ROW or COL of your matrix is greather than zero";
		}
		else if (n == 1) {
			cout << "Size of matrix in \"*\", not true !";
		}
		else if (n == 2) {
			cout << "Size of matrix in \"+\" , not true !";
		}
	}
	return 0;
}
