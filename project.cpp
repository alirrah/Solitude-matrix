#include <iostream>
#include <string>
#include <vector>
using namespace std;

class matrix
{
private:
    class node
    {
    public:
        pair<int, int> location;
        int value;
        node *nextRow;
        node *nextColumn;
    };
    vector<node *> headColumn;
    vector<node *> headRow;
    int row, column;
public:
    matrix(string &file)
    {
    }
    ~matrix()
    {
    }
    void insert(int row, int col, int value)
    {
    }
    void remove(int row, int col)
    {
    }
    void search(int value)
    {
    }
    void update(int row, int col, int value)
    {
    }
    void print(bool type)
    {
    }
    void save_file(string &file)
    {
    }
};

int main()
{
    return 0;
}