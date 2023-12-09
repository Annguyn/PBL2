#include "include/Supplier.h"
#define MAX_LENGTH 256
#include <iostream>
#include <fstream>
#include <iomanip>
#include<limits>

Supplier::Supplier() : Entity(), supplierID(0) {
}

  

Supplier::Supplier(int supplierID, char* name, char* andress, char* phoneNumber,  char* email)
    : Entity(name, andress, phoneNumber, email)
{
}

Supplier::~Supplier()
{
}

int Supplier::getSupplierID() const
{
    return supplierID;
}

void Supplier::SetSupplierID(int Id)
{
    supplierID = Id;
}
char* Supplier::getName() const {
    return name;
}
char* Supplier::getAndress() const {
    return andress;
}
char* Supplier::getEmail() const {
    return email;
}
void Supplier::addProduct(const Product) {
    Product.push_back(Product); // cái này mình ko biết đúng ko nữa thấy lên mạng người ta kêu push_back là thêm phần tử vào cuối.
}

void Supplier::Display()
{
    std::cout << "Supplier Information : " << std::endl;
    std::cout << "Supplier ID : " << getSupplierID() << std::endl;
    std::cout << "Supplier name : " << getName() << std::endl;
    std::cout << "Address : " << getAddress() << std::endl;
    std::cout << "Phone number : " << getPhoneNumber() << std::endl;
    std::cout << "Email: " << getEmail() << std::endl;
}

ostream &operator<<(ostream &o, const Supplier &obj)
{
    o << obj.getSupplierID() << "," << obj.getName() << ","  << obj.getAddress() << "," << obj.getPhoneNumber() << "," << obj.getEmail()  << endl ; 
    return o;
}

void Supplier::TypeInformation() {
    std::cout << "Supplier Information : " << std::endl;
    std::cout << "Supplier ID : ";
    std::cin >> SupplierID;
    std::cout << "Supplier name : ";
    std::cin >> name ;
    std::cout << "Address : ";
    std::cin >> andress;
    std::cout << "Phone number : ";
    std::cin >>phoneNumber; 
    std::cout << "Email: ";
    std::cin >> email ; 
}

void Supplier::WriteDataToFile(std::ostream &file) const
{
    file << getSupplierID() <<"," << getName()<<","  << getAddress() << "," <<getPhoneNumber() <<"," << getEmail() <<","<<endl ;
}
void Supplier::ReadDataFromFile(std::istream &file) {
        file >> supplierID ;
        file >> address;
        file >> phoneNumber;
        file >> email;
}
