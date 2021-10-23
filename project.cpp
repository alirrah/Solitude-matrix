#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define pause system("pause")

int findNumber(string &, int &);

class matrix
{
private:
    class node
    {
    public:
        pair<int, int> location;
        int value;
        node *nextRow, *nextColumn;
    };
    vector<node *> headColumn, headRow;
    int row, column;
public:
    matrix(string &file)
    {
        try
        {
            FILE *fptr;
            char fileSentence;
            int i, j;
            string sent;
            fptr = fopen(file.c_str(), "r");
            if (fptr == NULL)
                throw "Error!!! file could not be opened";
            for(i = 0; i < file.size(); i++)
                if(file[i] == 'M' && file[i + 1] == '(')
                    break;
            i += 2;
            row = findNumber(file, i);
            i++;
            column = findNumber(file, i);
            headRow.resize(row);
            headColumn.resize(column);
            i = 1;
            j = 1;
            while((fileSentence = fgetc(fptr)) != EOF)
            {
                if(isdigit(fileSentence))
                    sent += fileSentence;
                else if(fileSentence == ',' || fileSentence == '\n')
                {
                    insert(i, j, stoi(sent));
                    sent.clear();
                    j++;
                    if(j > column)
                    {
                        j = 1;
                        i++;
                    }
                }

            }
            fclose(fptr);
        }
        catch (char const *message)
        {
            cout << message << endl;
            pause;
            exit(1);
        }

    }
    ~matrix()
    {
        for(int i = 0; i < row; i++)
        {
            node *tmp = headRow[i];
            while (tmp != nullptr)
            {
                node *tp = tmp;
                tmp = tmp->nextRow;
                delete tp;
            }
        }
        column = 0;
        row = 0;
    }
    void insert(int row, int col, int value)
    {
        if (row <= 0 || row > this->row || col <= 0 || col > this->column || value == 0)
            return;
        node *tmp = new node;
        tmp->location.first = row--;
        tmp->location.second = col--;
        tmp->value = value;
        tmp->nextRow = nullptr;
        tmp->nextColumn = nullptr;
        if(headRow[row] == nullptr)
            headRow[row] = tmp;
        else
        {
            bool flag = true;
            node *tmpRow = headRow[row];
            if(headRow[row]->location.second > col + 1)
            {
                tmp->nextRow = headRow[row];
                headRow[row] = tmp;
            }
            else
            {
                while (tmpRow->nextRow != nullptr)
                {
                    if(tmpRow->location.first < row && tmpRow->nextRow->location.first > row)
                    {
                        tmp->nextRow = tmpRow->nextRow;
                        tmpRow->nextRow = tmp;
                        flag = false;
                    }
                    tmpRow = tmpRow->nextRow;
                }
                if(flag)
                    tmpRow->nextRow = tmp;
            }
        }
        if (headColumn[col] == nullptr)
            headColumn[col] = tmp;
        else
        {
            bool flag = true;
            node *tmpColumn = headColumn[col];
            if(headColumn[col]->location.first > row + 1)
            {
                tmp->nextColumn = headColumn[col];
                headColumn[col] = tmp;
            }
            else
            {
                while(tmpColumn->nextColumn != nullptr)
                {
                    if(tmpColumn->location.second < col && tmpColumn->nextColumn->location.second > col)
                    {
                        tmp->nextColumn = tmpColumn->nextColumn;
                        tmpColumn->nextColumn = tmp;
                        flag = false;
                    }
                    tmpColumn = tmpColumn->nextColumn;
                }
                if(flag)
                    tmpColumn->nextColumn = tmp;
            }
        }
    }
    void remove(int row, int col)
    {
        if(this->row < row || row <= 0 || this->column < col || col <= 0)
            return;
        node *tmp = nullptr;
        if(headRow[row - 1]->location.second == col)
        {
            tmp = headRow[row - 1];
            headRow[row - 1] = headRow[row - 1]->nextRow;
        }
        else
        {
            node *tmpRow = headRow[row - 1];
            while(tmpRow->nextRow != nullptr)
            {
                if(tmpRow->nextRow->location.second == col)
                {
                    tmp = tmpRow->nextRow;
                    tmpRow->nextRow = tmpRow->nextRow->nextRow;
                    break;
                }
                tmpRow = tmpRow->nextRow;
            }
        }
        if(headColumn[col - 1]->location.first == row)
            headColumn[col - 1] = headColumn[col - 1]->nextColumn;
        else
        {
            node *tmpColumn = headColumn[col - 1];
            while(tmpColumn->nextColumn != nullptr)
            {
                if(tmpColumn->nextColumn->location.first == row)
                {
                    tmpColumn->nextColumn = tmpColumn->nextColumn->nextColumn;
                    break;
                }
                tmpColumn = tmpColumn->nextColumn;
            }
        }
        delete tmp;
    }
    void search(int value)
    {
        if(!value)
            cout << "The number zero is present in many cells." << endl;
        for(int i = 0; i < row; i++)
        {
            node *tmp = headRow[i];
            while(tmp != nullptr)
            {
                if(tmp->value == value)
                {
                    cout << "The number " << value << " is in cell (" << tmp->location.first << ", " << tmp->location.second << ")." << endl;
                    return;
                }
                tmp = tmp->nextRow;
            }
        }
        cout << "Not cell found with this value." << endl;
    }
    void update(int row, int col, int value)
    {
        if(this->row < row || row <= 0 || this->column < col || col <= 0)
            return;
        if(headRow[--row]->location.second == col)
        {
            headRow[row]->value = value;
            return;
        }
        node *tmp = headRow[row];
        while(tmp != nullptr)
        {
            if(tmp->location.second == col)
            {
                tmp->value = value;
                return;
            }
            tmp = tmp->nextRow;
        }
    }
    void print(bool type)
    {
        if(type)
        {
            for(int i = 0; i < row; i++)
            {
                if(headRow[i] != nullptr)
                {
                    node *tmp = headRow[i];
                    while (tmp != nullptr)
                    {
                        cout << tmp->location.first << ' ' << tmp->location.second << ' ' << tmp->value << endl;
                        tmp = tmp->nextRow;
                    }
                }
            }
            return;
        }
        for(int i = 0 ; i < row; i++)
        {
            node *tmp = headRow[i];
            bool flag = false;
            for(int j = 0; j < column; j++)
            {
                if(headRow[i] == nullptr || !(tmp != nullptr && tmp->location.second == j + 1))
                {
                    if(flag)
                        cout << ',';
                    else
                        flag = true;
                    cout << 0;
                }
                else
                {
                    if(flag)
                        cout << ',';
                    else
                        flag = true;
                    cout << tmp->value;
                    tmp = tmp->nextRow;
                }
            }
            cout << endl;
        }
    }
    void save_file(string &file)
    {
        try
        {
            FILE *fptr;
            fptr = fopen(file.c_str(), "w");
            if (fptr == NULL)
                throw "Error!!! title.ratings.txt could not be opened";
            for(int i = 0 ; i < row; i++)
            {
                node *tmp = headRow[i];
                string sent = "";
                bool flag = false;
                for(int j = 0; j < column; j++)
                {
                    if(headRow[i] == nullptr || !(tmp != nullptr && tmp->location.second == j + 1))
                    {
                        if(flag)
                            sent += ',';
                        else
                            flag= true;
                        sent += '0';
                    }
                    else
                    {
                        if(flag)
                            sent += ',';
                        else
                            flag= true;
                        sent += to_string(tmp->value);
                        tmp = tmp->nextRow;
                    }
                }
                sent += '\n';
                fputs(sent.c_str(), fptr);
            }
            fclose(fptr);
        }
        catch (char const *message)
        {
            cout << message << endl;
            pause;
            exit(1);
        }
    }
};

int main()
{
    return 0;
}

int findNumber(string &sentence, int &j)
{
    int i = j;
    for(; j < sentence.size(); j++)
        if(!isdigit(sentence[j]))
            break;
    return stoi(sentence.substr(i, j));
}