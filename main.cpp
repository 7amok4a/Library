//Athour : 7amok4a
//Return Dark ^_^ &_&
#include <bits/stdc++.h>
using namespace std;
const int Max_Books = 1e3 ;
const int Max_Users = 1e3 ;
const int Max_Borrowed = 1e3 ;
int Size = 0  , Users = 0 ;
int Searchindex (string &name , int size ,  string arr[] ) {
    for (int i = 0 ; i <  size ; ++i) {
        if (arr[i] == name) {
            return  i ;
        }
    }
    return -1 ;
}
struct  Book {
    int Id ;
    string Name ;
    int Quantity ;
    string UserBorrowed [Max_Borrowed] ;
    int sizeofBorrowed = 0 ;
    int TotalBorrowed = 0 ;
    Book () {
        Id = -1 , Name = "" , Quantity = -1 ;
    }
    Book(int id , string &name , int quantity) : Id(id) , Name(name) , Quantity(quantity) {}
    void Borrowed (string &name) {
        UserBorrowed[sizeofBorrowed++] = name  ;
        ++TotalBorrowed;
    }
    void Return (string &name) {
        int index = Searchindex(name , sizeofBorrowed ,  UserBorrowed) ;
        for (int i =  index + 1 ; i < sizeofBorrowed ; ++i) {
            UserBorrowed[i - 1] = UserBorrowed[i] ;
        }
        --sizeofBorrowed , --TotalBorrowed ;
    }

};
Book ArrayofBooks [Max_Books] ;
int SearchinArrayofBooks (string &book) {
    for (int i = 0 ; i < Size ; ++i) {
        if (ArrayofBooks[i].Name == book) {
            return i ;
        }
    }
    return -1 ;
}
struct  User {
    string Name;
    int Id ;
    string IdBooks [Max_Borrowed] ;
    int sizeofBorrowed = 0 ;
    User() {
        Name = "" , Id = -1 ;
    }
    User (string &name , int id) : Name(name) , Id(id) {}
    void Borrowed(string &name) {
        int index = SearchinArrayofBooks(name) ;
        IdBooks[sizeofBorrowed++] = to_string(ArrayofBooks[index].Id) ;
    }
    void Return (string &name) {
        int index = SearchinArrayofBooks(name) ;
        for (int i =  index + 1 ; i < sizeofBorrowed ; ++i) {
            IdBooks[i - 1] = IdBooks[i] ;
        }
        --sizeofBorrowed ;
    }
};
User ArrayofUsers [Max_Users] ;
bool comp_id (Book &a , Book &b) {
    return a.Id < b.Id ;
}
bool comp_name (Book &a , Book &b) {
    return a.Name < b.Name ;
}
int SearchinArrayofUser (string &name) {
    for (int i = 0 ; i < Users ; ++i) {
        if (ArrayofUsers[i].Name == name) {
            return i ;
        }
    }
    return -1 ;
}

void Add_Book (Book newbook) {
    ArrayofBooks[Size++] = Book(newbook.Id,newbook.Name , newbook.Quantity) ;
}
void Search (string &str) {
    for (int i = 0 ; i < Size ; ++i) {
        string sb = ArrayofBooks[i].Name.substr(0 , (int)str.size()) ;
        if (str == sb) {
            cout << ArrayofBooks[i].Name << "\n" ;
        }
    }
}
void WhoBorrowedBook (string &name) {
    int index = SearchinArrayofBooks(name) ;
    for (int i = 0 ; i < ArrayofBooks[index].sizeofBorrowed;++i) {
        cout << ArrayofBooks[index].UserBorrowed[i] << " " ;
    }
}
void PrintAllId () {
    sort (ArrayofBooks , ArrayofBooks + Size , comp_id) ;
    for (int i = 0 ; i < Size ; ++i) {
        cout << "Id : " << ArrayofBooks[i].Id << "  "
            << "Name : " << ArrayofBooks[i].Name << "  "
            << "Total Quantity : "  << ArrayofBooks[i].Quantity << "  "
            << "Total_Borrowed : " << ArrayofBooks[i].TotalBorrowed << "\n" ;
    }
}
void PrintAllName () {
    sort (ArrayofBooks , ArrayofBooks + Size , comp_name) ;
    for (int i = 0 ; i < Size ; ++i) {
        cout << "Id : " << ArrayofBooks[i].Id << "  "
             << "Name : " << ArrayofBooks[i].Name << "  "
             << "Total Quantity : "  << ArrayofBooks[i].Quantity << "  "
             << "Total_Borrowed : " << ArrayofBooks[i].TotalBorrowed << "\n" ;
    }
}
void AddUser(User newuser) {
    ArrayofUsers[Users++] = User(newuser.Name, newuser.Id)  ;
}
void Borrowed_Book (string &name , string &book) {
    int indexU = SearchinArrayofUser(name) ;
    int indexB = SearchinArrayofBooks(book) ;
    ArrayofBooks[indexB].Borrowed(name) ;
    ArrayofUsers[indexU].Borrowed(book) ;
}
void Return_book(string &name , string &book) {
    int indexU = SearchinArrayofUser(name) ;
    int indexB = SearchinArrayofBooks(book) ;
    ArrayofBooks[indexB].Return(name) ;
    ArrayofUsers[indexU].Return(book) ;
}
void PrintUser() {
    for (int i = 0 ; i < Users ; ++i) {
        cout << "User : " << ArrayofUsers[i].Name
             << " id : " << ArrayofUsers[i].Id
             << " borrowed book ids : " ;
            for (int ii = 0 ; ii < ArrayofUsers[i].sizeofBorrowed ; ++ii) {
                cout << ArrayofUsers[i].IdBooks[ii] << " ";
            }
            cout << "\n" ;
    }
}
void Menu () {
    cout << "Library Menu :\n" ;
    cout << "1)Add Book\n" ;
    cout << "2)Search Books by Prefix\n";
    cout << "3)Print Who Borrowed Book by Name\n" ;
    cout << "4)Print Library by id\n" ;
    cout << "5)Print Library by Name\n" ;
    cout << "6)Add User\n" ;
    cout << "7)User Borrow Book\n" ;
    cout << "8)User Return Book\n" ;
    cout << "9)Print Users \n" ;
    cout << "10)Exit\n" ;
    cout << "\nEnter Menu choice [1-10] : \n" ;
}
void Process () {
    while (true) {
        Menu() ;
        int n;  cin >> n ;
        if (n == 1) {
            cout << "Enter info about book : Id , Name , Quantity : \n ";
            int id ;
            string name ;
            int quantity ;
            cin >> id >> name >> quantity ;
            Add_Book(Book(id , name , quantity));
            cout << "\n" ;
        }
        else if (n == 2) {
            cout << "Enter Prefix : " ;
            string str;     cin >> str ;
            Search(str) ;
            cout << "\n" ;
        }
        else if (n== 3) {
            cout << "Enter Book Name : " ;
            string name ;   cin >> name ;
            WhoBorrowedBook(name) ;
            cout << "\n" ;
        }
        else if (n == 4) {
            PrintAllId();
            cout << "\n" ;
        }
        else if (n == 5) {
            PrintAllName();
            cout << "\n" ;
        }
        else if (n == 6) {
            cout << "Enter Your Name and Id : " ;
            string name ;
            int id ;
            cin >> name >> id ;
            AddUser(User(name , id)) ;
            cout << "\n" ;
        }
        else if (n == 7) {
            cout << "Enter your name and book : " ;
            string name , book ;    cin >> name >> book ;
            Borrowed_Book (name , book) ;
            cout << "\n" ;
        }
        else if (n == 8) {
            cout << "Enter your name and book : " ;
            string name , book ;    cin >> name >> book ;
            Return_book(name , book) ;
        }
        else if (n == 9) {
               PrintUser() ;
               cout << "\n" ;
        }
        else if (n == 10) {
            return;
        }
        else {
            cout << "Wrong Input!! , Please try again\n" ;
        }
    }
}
int main() {
    Process() ;
    return 0;
}