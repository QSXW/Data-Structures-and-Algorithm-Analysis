#include <iostream>
#include <vector>

template<typename ElemType>
struct TupleNode
{
public:
    TupleNode(size_t r, size_t c, ElemType elem)
    {
        this->row = r;
        this->column = c;
        this->e = elem;
    }

public:
    size_t row;
    size_t column;
    ElemType e;
};

template<typename ElemType>
class TupleSparseMatrix
{
public:
	TupleSparseMatrix()
	{
		this->rows = 0;
		this->columns = 0;
		this->nonZeroCnt = 0;
	}

    TupleSparseMatrix(std::vector<std::vector<ElemType>> a)
    {
        // this->data = new TupleNode<ElemType>[MAXSIZE];
        this->rows = a.size();
        this->columns = a[0].size();
        this->nonZeroCnt = 0;
        
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->columns; j++)
            {
                if (a[i][j] != 0)
                {
                    this->data.push_back(TupleNode<ElemType>(i, j, a[i][j]));
                    this->nonZeroCnt++;
                }
            }
        }
    }

	inline size_t getRows() const
	{
		return this->rows;
	}

	inline size_t getColumns() const
	{
		return this->columns;
	}

	inline int getNonZeroCnt() const
	{
		return this->nonZeroCnt;
	}

    /* When using friend keyword and template, you must apply a different template typename from class */
    template<typename T> friend std::ostream & operator<< (std::ostream &os, TupleSparseMatrix<T> &t);

    bool value(ElemType x, int i, int j)
    {
        int k = 0;
		auto it = this->data.begin();

        if (i >= this->rows || j >= this->columns)
        {
            return false;
        }
        while (k < this->nonZeroCnt && i > this->data[k].row)
        {
            k++;
            it++;
        }
        while (k < this->nonZeroCnt && i == this->data[k].row && j > this->data[k].column)
        {
            k++;
            it++;
        }
        if (this->data[k].row == i && this->data[k].column == j)
        {
            this->data[k].e = x;
        }
        else
        {
            this->data.insert(it, TupleNode<ElemType>(i, j, x));
            this->nonZeroCnt++;
        }
        
        return true;
    }

    bool assign(ElemType &x, int i, int j)
    {
        int k = 0;
        
        if (i >= this->rows || j>= this->columns)
        {
            return false;
        }
        while (k < this->nonZeroCnt && i > this->data[k].row)
        {
            k++;
        }
        while (k < this->nonZeroCnt && i == this->data[k].row && j > this->data[k].column)
        {
            k++;
        }
        if (this->data[k].row == i && this->data[k].column == j)
        {
            x = this->data[k].e;
        }
        else
        {
            x = 0;
        }
        return true;
    }
	
	void displayTS() const
	{
		if (this->nonZeroCnt <= 0)
		{
			return;
		}
		std::cout << this->rows << '\t' << this->columns << '\t' << this->nonZeroCnt << std::endl;
		printf("----------------------------------\n");
		for (int i = 0; i < this->nonZeroCnt; i++)
		{
			std::cout << this->data[i].row << '\t' << this->data[i].column << '\t' << this->data[i].e << std::endl;
		}
	}

	TupleSparseMatrix<ElemType> & transport()
	{
		TupleSparseMatrix<ElemType> *a = new TupleSparseMatrix<ElemType>();
		a->rows = this->columns;
		a->columns = this->rows;
		a->nonZeroCnt = this->nonZeroCnt;

		if (this->nonZeroCnt > 0)
		{
			for (int i = 0; i < this->columns; i++)
			{
				for (int j = 0; j < this->nonZeroCnt; j++)
				{
					if (this->data[j].column == i)
					{
						a->data.push_back(TupleNode<ElemType>(this->data[j].column, this->data[j].row, this->data[j].e));
					}
				}
			}
		}
		return *a;
	}

	TupleSparseMatrix<ElemType> & operator+ (TupleSparseMatrix<ElemType> &b)
	{
		TupleSparseMatrix<ElemType> *a = new TupleSparseMatrix();
		
		if (this->rows == b.rows && this->columns == b.columns)
		{
			for (int i = 0, j = 0; i < this->nonZeroCnt || j < b.nonZeroCnt; /* None */)
			{
				if (j >= b.nonZeroCnt || (i < this->nonZeroCnt && this->data[i].row < b.data[j].row))
				{
					a->data.push_back(TupleNode<ElemType>(this->data[i].row, this->data[i].column, this->data[i].e));
					i++;
					continue;
				}
				else if (i >= this->nonZeroCnt || (j < b.nonZeroCnt && this->data[i].row > b.data[j].row))
				{
					a->data.push_back(TupleNode<ElemType>(b.data[j].row, b.data[j].column, b.data[j].e));
					j++;
					continue;
				}
				else if (i < this->nonZeroCnt && j < b.nonZeroCnt && this->data[i].row == b.data[j].row)
				{
					if (this->data[i].column == b.data[j].column)
					{
						a->data.push_back(TupleNode<ElemType>(this->data[i].row, this->data[i].column, this->data[i].e + b.data[j].e));
						i++;
						j++;
						continue;
					}
					else if (this->data[i].column < b.data[j].column)
					{
						a->data.push_back(TupleNode<ElemType>(this->data[i].row, this->data[i].column, this->data[i].e));
						i++;
						continue;
					}
					else if (this->data[i].column > b.data[j].column)
					{
						a->data.push_back(TupleNode<ElemType>(b.data[j].row, b.data[j].column, b.data[j].e));
						j++;
						continue;
					}
				}
			}
		}
		a->rows = this->rows;
		a->columns = this->columns;
		a->nonZeroCnt = (int)a->data.size();
		return *a;
	}

	TupleSparseMatrix<ElemType> & operator* (int i)
	{
		TupleSparseMatrix<ElemType> *a = new TupleSparseMatrix();

		/* Pending complete. */

		a->nonZeroCnt = (int)a->data.size();
		return *a;
	}


private:
    size_t rows;
    size_t columns;
    int nonZeroCnt;
    std::vector<TupleNode<ElemType>> data;
};

template<typename T>
std::ostream & operator<< (std::ostream &os, TupleSparseMatrix<T> &t)
{
    if (t.nonZeroCnt <= 0)
    {
        return os;
    }

	/* Generally speaking, the vector would initialize the element to be zero.
	   But for safer, below is intended to automatically set all elements to be zero.
	*/
    std::vector<std::vector<T>> mat;
    for (int i = 0; i < t.rows; i++)
    {
		mat.push_back(std::vector<T>(t.columns));
        for (int j = 0; j < t.columns; j++)
        {
            mat[i][j] = (T)0;
        }
    }

    int k = 0;
    while (k < t.nonZeroCnt)
    {
        mat[t.data[k].row][t.data[k].column] = t.data[k].e;
		k++;
    }
    
    for (auto c : mat)
    {
        for (auto r : c)
        {
            os << r << "\t";
        }
        os << std::endl;
    }

    return os;
}

#if 0
int main()
{  
	using namespace ::std;
/*
    TupleSparseMatrix<int> a({
		{ 0, 0, 1, 0, 0, 0, 0 },
		{ 0, 2, 0, 0, 0, 0, 0 },
		{ 3, 0, 4, 0, 0, 0, 0 },
		{ 0, 0, 0, 5, 0, 0, 0 },
		{ 0, 0, 0, 0, 6, 0, 0 },
		{ 0, 2, 0, 0, 0, 7, 4 },
		{ 3, 0, 4, 0, 0, 0, 0 }
	});

	TupleSparseMatrix<int> b({
		{ 2, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 2, 0, 0, 0, 0, 0, 0 },
		{ 3, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 5, 0, 0, 0, 0 },
		{ 0, 0, 7, 0, 6, 0, 0, 0 },
		{ 0, 0, 4, 0, 0, 7, 4, 0 },
		{ 0, 0, 4, 0, 0, 7, 4, 0 }
	});
*/

	TupleSparseMatrix<int> a({
		{ 5, 2, 4 },
		{ 3, 8, 2 },
		{ 6, 0, 4 },
		{ 0, 1, 6 }
	});

	TupleSparseMatrix<int> b({
		{ 2, 4 },
		{ 1, 3 },
		{ 3, 2 }
	});

	TupleSparseMatrix<int> c = a + b;
	cout << a;
	cout << endl;
	cout << b;
	cout << endl;
	cout << c;

    std::cin.get();
    return 0;
}
#endif