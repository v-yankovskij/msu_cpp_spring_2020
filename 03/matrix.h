#ifndef matrix_h
#define matrix_h

#include <vector>

class Row
{
public:
    size_t cols;
    std::vector<double> data_;
    
    Row (size_t a)
    {
        cols = a;
        for (size_t i = 0; i < a; i++)
        {
            data_.push_back(0);
        }
    }
    
    const double& operator[](size_t j) const
    {
        if (j < cols)
        {
            return data_[j];
        }
        else
        {
            throw std::out_of_range("");
        }
    }
    
    double& operator[](size_t j)
    {
        if (j < cols)
        {
            return data_[j];
        }
        else
        {
            throw std::out_of_range("");
        }
    }
};

class Matrix
{
public:
    size_t rows;
    size_t cols;
    std::vector<Row> data;
    
    Matrix(size_t a, size_t b)
    {
        rows = a;
        cols = b;
        for (size_t i = 0; i < a; i++)
        {
            data.push_back(Row(cols));
        }
    }
    
    const Row& operator[](size_t i) const
    {
        if (i >= rows)
        {
            throw std::out_of_range("");
        }
        return data[i];
    }
    
    Row& operator[](size_t i)
    {
        if (i >= rows)
        {
            throw std::out_of_range("");
        }
        return data[i];
    }
    
    void operator*= (double a)
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                (*this)[i][j] *= a;
            }
        }
    }
    
    bool operator== (const Matrix& M)
    {
        if (cols != M.cols)
        {
            return false;
        }
        if (rows != M.rows)
        {
            return false;
        }
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                if ((*this)[i][j] != M[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!= (const Matrix& M)
    {
        return !(*(this) == M);
    }
};


#endif
