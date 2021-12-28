#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

struct Coord
{
    uint x;
    uint y;
};

struct Shape;

struct Cell
{
    friend ostream &operator<<(ostream &, const Cell &);
    uint i;
    uint j;
    Shape *parent;
    Cell(uint i, uint j, Shape *shape) : i(i), j(j), parent(shape){};

    Cell *translate(uint i, uint j);
    bool eq(Cell *const cell);
};

ostream &operator<<(ostream &os, const Cell &cell)
{
    os << "Cell{ " << cell.i << ", " << cell.j << " }";
    return os;
}

Cell *Cell::translate(uint i, uint j)
{
    Cell *cell = new Cell{this->i + i, this->j + j, this->parent};
    return cell;
}

bool Cell::eq(Cell *const cell)
{
    return this->i == cell->i && this->j == cell->j;
}

struct Shape
{
    friend ostream &operator<<(ostream &, const Shape &);
    Cell *top;
    Cell *left;
    Cell *right;
    Cell *bottom;
    vector<Cell *> cells;
    Shape(Cell *cell)
    {
        cell->parent = this;

        top = left = right = bottom = cell;
        cells.push_back(cell);
    }
    ~Shape()
    {
        for (auto cell : cells)
        {
            delete cell;
        }
    }

    void addCell(Cell *cell);
    bool isCross() const;
    void merge(Shape *shape);
};

ostream &operator<<(ostream &os, const Shape &shape)
{
    os << "Shape{" << endl;
    for (auto cell : shape.cells)
    {
        os << "   ";
        os << *cell << endl;
    }
    os << "}";
    return os;
}

void Shape::addCell(Cell *cell)
{
    cell->parent = this;
    this->cells.push_back(cell);

    if (cell->j < this->top->j)
        this->top = cell;
    if (cell->i < this->left->i)
        this->left = cell;
    if (cell->i > this->right->i)
        this->right = cell;
    if (cell->j > this->bottom->j)
        this->bottom = cell;
}

void Shape::merge(Shape *shape)
{
    for (auto cell : shape->cells)
    {
        this->addCell(cell);
    }
    shape->cells.clear();
}

bool Shape::isCross() const
{
    if (this->cells.size() == 1)
        return true;
    if (!(this->cells.size() & 1))
        return false;

    auto beam = (this->cells.size() - 1) / 4;

    auto right = this->top->translate(beam, beam);
    if (!this->right->eq(right))
        return false;

    auto bottom = this->top->translate(0, 2 * beam);
    if (!this->bottom->eq(bottom))
        return false;

    auto left = this->top->translate(-beam, beam);
    if (!this->left->eq(left))
        return false;

    return true;
};

const char GOOD{'G'};
const char BAD{'B'};

/*
 * Given matrix with `Good` and `Bad` cells find count of nonoverlapping crosses composed from `Good` cells
 * non-overlapping crosses consisting from `Good` cells
 *
 * Idea:
 *  - find all isolated `Good` shapes
 *  - determine which of shapes are crosses
 */
int crosses(vector<string> grid)
{
    auto n = grid.size();
    auto m = grid[0].size();

    vector<vector<Cell *>> cells;
    for (uint i = 0; i < n; ++i)
    {
        cells.push_back(vector<Cell *>(m));
        for (uint j = 0; j < m; ++j)
        {
            cells[i][j] = new Cell{i, j, nullptr};
        }
    }

    vector<Shape *> shapes;
    for (uint i = 0; i < grid.size(); ++i)
    {
        auto raw = grid[i];
        for (uint j = 0; j < raw.size(); ++j)
        {
            auto mark = raw[j];
            if (mark == BAD)
            {
                continue;
            }
            if (i > 0 && grid[i - 1][j] == GOOD && j > 0 && grid[i][j - 1] == GOOD)
            {
                cells[i - 1][j]->parent->addCell(cells[i][j]);

                if (cells[i - 1][j]->parent != cells[i][j - 1]->parent)
                {

                    cells[i - 1][j]->parent->merge(cells[i][j - 1]->parent);
                }
            }
            else if (i > 0 && grid[i - 1][j] == GOOD)
            {
                cells[i - 1][j]->parent->addCell(cells[i][j]);
            }
            else if (j > 0 && grid[i][j - 1] == GOOD)
            {
                cells[i][j - 1]->parent->addCell(cells[i][j]);
            }
            else
            {
                auto shape = new Shape{cells[i][j]};
                shapes.push_back(shape);
            }
        }
    }

    vector<Shape *> crosses;

    std::copy_if(
        shapes.begin(),
        shapes.end(),
        std::back_inserter(crosses), [](Shape *s)
        { return s->isCross(); });
    return crosses.size();
}

int main(int argv, char *argc[])
{
    string bin_path{argc[0]};
    string bin_dir = bin_path.substr(0, bin_path.find_last_of('/'));
    string data_path = bin_dir + "/data";
    ifstream fin(data_path);

    string first_multiple_input_temp;
    getline(fin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<string> grid(n);

    for (int i = 0; i < n; i++)
    {
        string grid_item;
        getline(fin, grid_item);

        grid[i] = grid_item;
    }

    int result = crosses(grid);

    cout << result << "\n";

    return 0;
}

string ltrim(const string &str)
{
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

    return s;
}

string rtrim(const string &str)
{
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end());

    return s;
}

vector<string> split(const string &str)
{
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos)
    {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
