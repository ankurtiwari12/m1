#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
const int MAX_BORROWED_BOOKS = 5;
class Books {
public:
    string book_id;
    string goodreads_book_id;
    string best_book_id;
    string work_id;
    string books_count;
    string isbn;
    string isbn13;
    string authors;
    string original_publication_year;
    string original_title;
    string title;
    string language_code;
    string average_rating;
    string ratings_count;
    string work_ratings_count;
    string work_text_reviews_count;
    string ratings_1;
    string ratings_2;
    string ratings_3;
    string ratings_4;
    string ratings_5;
    string image_url;
    string small_image_url;
    string physical_location;
};

string *splitCSVLine(const string &line)
{
    // Define the number of fields based on your data structure
    const int numFields = 23; // Adjust this based on your data

    string *result = new string[numFields];
    istringstream stream(line);
    string cell;
    bool inQuotes = false;
    int fieldIndex = 0;

    while (getline(stream, cell, ','))
    {
        if (cell.empty())
        {
            result[fieldIndex++] = ""; // Handle empty cells
        }
        else
        {
            // Check if the cell starts with a double quote
            if (cell.front() == '"')
            {
                inQuotes = true;
                cell = cell.substr(1); // Remove the opening double quote
            }

            // Check if the cell ends with a double quote
            if (cell.back() == '"')
            {
                inQuotes = false;
                cell = cell.substr(0, cell.size() - 1); // Remove the closing double quote
            }

            if (inQuotes)
            {
                // If in quotes, combine with the next cell
                cell += ",";
                string nextCell;
                while (inQuotes && getline(stream, nextCell, ','))
                {
                    if (nextCell.back() == '"')
                    {
                        inQuotes = false;
                        nextCell = nextCell.substr(0, nextCell.size() - 1); // Remove the closing double quote
                    }
                    cell += nextCell + ",";
                }
                cell = cell.substr(0, cell.size() - 1); // Remove the trailing comma
            }

            result[fieldIndex++] = cell;
        }
    }

    return result;
}
int main() {
    string csv_file_path = "books.csv";
    ifstream file(csv_file_path);

    if (!file.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return 1;
    }

    string line;
    const int max_books = 100;
    Books booksData[max_books];

    int bookIndex = 0;
    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        string *fields = splitCSVLine(line);

        if (fields != nullptr) {
            Books &book = booksData[bookIndex];
            book.book_id = fields[0];
            book.goodreads_book_id = fields[1];
            book.best_book_id = fields[2];
            book.work_id = fields[3];
            book.books_count = fields[4];
            book.isbn = fields[5];
            book.isbn13 = fields[6];
            book.authors = fields[7];
            book.original_publication_year = fields[8];
            book.original_title = fields[9];
            book.title = fields[10];
            book.language_code = fields[11];
            book.average_rating = fields[12];
            book.ratings_count = fields[13];
            book.work_ratings_count = fields[14];
            book.work_text_reviews_count = fields[15];
            book.ratings_1 = fields[16];
            book.ratings_2 = fields[17];
            book.ratings_3 = fields[18];
            book.ratings_4 = fields[19];
            book.ratings_5 = fields[20];
            book.image_url = fields[21];
            book.small_image_url = fields[22];

            delete[] fields; // Free the memory allocated by splitCSVLine
            ++bookIndex;
        }
    }

    file.close();

    for (int i = 0; i < bookIndex; ++i) { // Use bookIndex to iterate over valid data
        cout << "Book " << i + 1 << " Details:" << endl;
        cout << "book_id: " << booksData[i].book_id << endl;
        cout << "title: " << booksData[i].title << endl;
        cout << "best_book_id: " << booksData[i].best_book_id << endl;

        cout << endl;
    }
    
    return 0;
}
