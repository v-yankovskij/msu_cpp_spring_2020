#ifndef matrix_h
#define matrix_h

#include <vector>

class row_
{
public:
    size_t cols;
    std::vector<double> data_;
    
    row_ (size_t a)
    {
        cols = a;
        for (int i = 0; i < a; i++)
        {
            data_.push_back(0);
        }
    }
    
    const double& operator[](size_t j) const
    {
        if ((j >= 0) && (j < cols))
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
        if ((j >= 0) && (j < cols))
        {
            return data_[j];
        }
        else
        {
            throw std::out_of_range("");
        }
    }
};

class matrix_
{
public:
    size_t rows;
    size_t cols;
    std::vector<row_> data;
    
    matrix_(size_t a, size_t b)
    {
        rows = a;
        cols = b;
        for (int i = 0; i < a; i++)
        {
            data.push_back(Row(cols));
        }
    }
    
    const row_& operator[](size_t i) const
    {
        if ((i < 0) || (i >= rows))
        {
            throw std::out_of_range("");
        }
        return data[i];
    }
    
    row_& operator[](size_t i)
    {
        if ((i < 0) || (i >= rows))
        {
            throw std::out_of_range("");
        }
        return data[i];
    }
    
    size_t get_rows()
    {
        return rows;
    }
    
    size_t get_columns()
    {
        return cols;
    }
    
    void operator*= (double a)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                (*this)[i][j] *= a;
            }
        }
    }
    
    bool operator== (matrix_ M)
    {
        if (cols != M.getColumns())
        {
            return false;
        }
        if (rows != M.getRows())
        {
            return false;
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if ((*this)[i][j] != M[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!= (matrix_ M)
    {
        return !(*(this) == M);
    }
};


#endif
