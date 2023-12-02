#include"Product.h"
#include"Order.h"
#include"Payment.h"
#include"Entity.h"
class Supplier : public Entity 
{
private:
    int supplierID ;
    Vector<Product> productsSupplied  ; 
    Vector<Order> Orders ; 
public:
    Supplier();
    Supplier(int Id, char* name,  char* address, char* phoneNumber,  char* email)
    ~Supplier();
    int getSupplierID() ; 
    void setSupplierID(int) ; 
    char* getName() const;
    char* getAndress() const;
    char* getPhoneNumber() const;
    char* getEmail() const;
    void addProduct(const Product) ; 
    void Display() ; 
    friend std::ostream& operator<<(ostream& o,const Supplier&supplier );
    void TypeInformation();
    void WriteDataToFile(std::ostream& file) const ; 
    void ReadDataFromFile(std::istream& file)  ; 
}; 
