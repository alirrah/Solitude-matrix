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

int findNumber(string &sentence, int &j)
{
    int i = j;
    for(; j < sentence.size(); j++)
        if(!isdigit(sentence[j]))
            break;
    return stoi(sentence.substr(i, j));
}