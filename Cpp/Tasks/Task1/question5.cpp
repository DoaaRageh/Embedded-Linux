struct Name
{
    char *firstName;
    char *middleName;
    char *lastName;
};

struct DateOfBirth
{
    int day;
    int mounth;
    int year;
};

struct Address
{
    char *street;
    char *city;
    char *country;
};

struct Contacts
{
    char *telephoneNumber;
    char *mobileNumber;
    char *emailAddress;
};

struct Salary
{
    double basis;
    double additionals;
    double reductions;
    double taxes;
};

struct Employee
{
    Name name;
    DateOfBirth dateOfBirth;
    Address address;
    Contacts contacts;
    char *job;
    Salary Salary;
};