#include <iostream>
#include <limits>
#include <string>

#define PRINT_MENU_HEADER std::cout << "\n\n ======= Matrix Operations =======\n";

struct Matrix
{
    int rows;
    int columns;
    double **data = nullptr;
};

const int MIN_LIMIT = 2;
const int MAX_LIMIT = 10;
const int BUFFER_SIZE = 256;


enum MenuOptions
{
    ENTER_MATRIX_A = 1,
    ENTER_MATRIX_B,
    DISPLAY_MATRICES,
    ADD_MATRICES,
    MULTIPLY_MATRICES,
    EXIT
};

// input functions
void readUserInput(const char *message, int &userInput, int minOption, int maxOption)
{
    while (true)
    {
        std::cout << message;

        if (!(std::cin >> userInput))
        {
            std::cout << "Please enter a valid integer\n";
            std::cin.clear();
        }
        else if (userInput < minOption || userInput > maxOption)
        {
            std::cout << "Please enter between " << minOption << "-" << maxOption << ".\n";
        }
        else
        {
            return;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double readUserInput(const char *message)
{
    double input = 0;

    while (true)
    {
        std::cout << message << ": ";
        std::cin >> input;

        if (std::cin.fail())
        {
            std::cout << "Invalid input. Please enter a valid number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
    }
    return input;
}


//display functions
void printMatrix(const Matrix &matrix)
{
    for (int row = 0; row < matrix.rows; row++)
    {
        for (int col = 0; col < matrix.columns; col++)
        {
            std::cout << matrix.data[row][col] << " ";
        }
        std::cout << "\n";
    }
}

void displayMatrices(const Matrix& matrixA, const Matrix& matrixB)
{
    if (matrixA.data != nullptr)
    {
        std::cout << "Matrix-A:\n";
        printMatrix(matrixA);
        std::cout << "\n";
    }
    else
    {
        std::cout << "Matrix-A not yet initialized.\n";
    }

    if (matrixB.data != nullptr)
    {
        std::cout << "Matrix-B:\n";
        printMatrix(matrixB);
        std::cout << "\n";
    }
    else
    {
        std::cout << "Matrix-B not yet initialized.\n";
    }
}
void deleteMatrix(Matrix& matrix){
    for(int row = 0; row < matrix.rows;row++){
        delete[] matrix.data[row];
    }
    delete[] matrix.data;
    
    matrix.rows = -1;
    matrix.columns = -1;
    matrix.data = nullptr;
}

void allocateMatrix(Matrix& matrix)
{
    if(matrix.data != nullptr){
        deleteMatrix(matrix);
    }
    matrix.data = new double* [matrix.rows];

    for (int row = 0; row < matrix.rows; row++)
    {
        matrix.data[row] = new double[matrix.columns];
    }
}


void inputMatrix(Matrix& matrix)
{
    PRINT_MENU_HEADER
    char numRowsMessage[] = "Enter the number of rows: ";
    char numColumnsMessage[] = "Enter the number of columns: ";

    readUserInput(numRowsMessage, matrix.rows, MIN_LIMIT, MAX_LIMIT);
    readUserInput(numColumnsMessage, matrix.columns, MIN_LIMIT, MAX_LIMIT);

    std::cout << "\n Enter Matrix Data: \n";
    
    allocateMatrix(matrix);

    if (matrix.data != nullptr)
    {
        for (int row = 0; row < matrix.rows; row++)
        {
            for (int col = 0; col < matrix.columns; col++)
            {
                char inputMessage[BUFFER_SIZE];
                std::snprintf(inputMessage, sizeof(inputMessage), "Enter data (%d, %d):", row + 1, col + 1);
                matrix.data[row][col] = readUserInput(inputMessage);
            }
        }
    }
}


//operations
void addMatrices(Matrix& matrixA, Matrix& matrixB)
{
    PRINT_MENU_HEADER
    if (matrixA.data == nullptr || matrixB.data == nullptr)
    {
        std::cout << "Please Enter data for Matrices!!\n";
        return;
    }
    else if (!(matrixA.rows == matrixB.rows && matrixA.columns == matrixB.columns))
    {
        std::cout << "Dimensions of both matrices should be same for addition.\n";
        return;
    }

    displayMatrices(matrixA, matrixB);

    std::cout << "Addition Result: \n";
    for (int row = 0; row < matrixA.rows; row++)
    {
        for (int col = 0; col < matrixA.columns; col++)
        {
            std::cout << (matrixA.data[row][col] + matrixB.data[row][col]) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void multiplyMatrices(Matrix& matrixA, Matrix& matrixB)
{
    PRINT_MENU_HEADER
    if (matrixA.data == nullptr || matrixB.data == nullptr)
    {
        std::cout << "Please Enter data for Matrices!!\n";
        return;
    }
    else if (!(matrixA.columns == matrixB.rows))
    {
        std::cout << "Dimensions of both matrices are not compatible for multiplication.\n";
        return;
    }

    displayMatrices(matrixA, matrixB);
    
    std::cout << "Multiplication Result:\n";

    Matrix result{matrixA.rows, matrixB.columns};
    allocateMatrix(result);

    for (int row = 0; row < matrixA.rows; row++)
    {
        for (int col = 0; col < matrixB.columns; col++)
        {
            result.data[row][col] = 0; // initialize before accumulation
            for (int ptr = 0; ptr < matrixA.columns; ptr++)
            {
                result.data[row][col] += matrixA.data[row][ptr] * matrixB.data[ptr][col];
            }
        }
    }

    printMatrix(result);
    deleteMatrix(result);
}

void runProgramLoop()
{
    int selectedOption;
    Matrix matrixA;
    Matrix matrixB;

    char userChoiceMessage[] = "Enter your choice: ";

    do
    {
        PRINT_MENU_HEADER
        std::cout << " 1. Enter(or Update) Matrix A\n";
        std::cout << " 2. Enter(or Update) Matrix B\n";
        std::cout << " 3. Display Matrices\n";
        std::cout << " 4. Add Matrices (A + B)\n";
        std::cout << " 5. Multiply Matrices (A * B)\n";
        std::cout << " 6. Exit\n";

        readUserInput(userChoiceMessage, selectedOption, MenuOptions::ENTER_MATRIX_A, MenuOptions::EXIT);

        switch (selectedOption)
        {
        case MenuOptions::ENTER_MATRIX_A:
            inputMatrix(matrixA);
            break;

        case MenuOptions::ENTER_MATRIX_B:
            inputMatrix(matrixB);
            break;
        case MenuOptions::DISPLAY_MATRICES:
        {
            PRINT_MENU_HEADER
            displayMatrices(matrixA, matrixB);
        }
            break;
        case MenuOptions::ADD_MATRICES:
            addMatrices(matrixA, matrixB);
            break;
        case MenuOptions::MULTIPLY_MATRICES:
            multiplyMatrices(matrixA, matrixB);
            break;
        case MenuOptions::EXIT:
        {
            deleteMatrix(matrixA);
            deleteMatrix(matrixB); 
            std::cout << "\n BYE!!\n";
        }
            break;
        default:
            break;
        }

    } while (selectedOption != MenuOptions::EXIT);
}

int main()
{
    runProgramLoop();

    return 0;
}