#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <cstring>
#include <process.h>
#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;
class emp // Class of for Empolyee information
{
  int eno; //Employee number/id
  char name[30]; //Name
  char phone[15]; //Phone number
  char dept[10]; //Department
  char desig[10]; //Designation
  double salary; //Salary

public:
  emp();
  emp(emp &E);
  void getdata();
  void putdata();
  int geteno();
  char *getdept();
  float getsal();
  char *getname();
};
emp::emp() //Constructor
{
  eno = 0;
  name[0] = '\0';
  dept[0] = '\0';
  desig[0] = '\0';
  phone[0] = '\0';
  salary = 0;
}
emp::emp(emp &E) //Copy constructor
{
  eno = E.eno;
  strcpy(name, E.name);
  strcpy(dept, E.dept);
  strcpy(desig, E.desig);
  strcpy(phone, E.phone);
  salary = E.salary;
}
void emp::getdata() // To Get the data of the Employee
{
  string tempname;
  cout << "\nEnter Employee number: ";
  cin >> eno;
  cout << "Enter Employee Name:";
  cin >> name;
  cin.ignore();
  cout << "Enter phone number:";
  cin >> phone;
  cout << "Enter Department:";
  cin >> dept;
  cout << "Enter salary:";
  cin >> salary;
}
void emp::putdata() // display data of the employee
{
  cout << "Employee number: " << eno << endl;
  cout << "Employee name: " << name << endl;
  cout << "Phone name: " << phone << endl;
  cout << "Department: " << dept << endl;
  cout << "Designation: " << desig << endl;
  cout << "Salary: " << salary << endl;
}
int emp::geteno() //Method to return Empolyee name/id
{
  return (eno);
}
char *emp::getname() //Method to return Name
{
  return (name);
}
char *emp::getdept() //Method to return Which department
{
  return (dept);
}
float emp::getsal() //Mathod to return salary
{
  return (salary);
}
void write() // Add records to the file
{
  ofstream f("emp.txt", ios::binary | ios::in | ios::out | ios::trunc);
  emp E;
  char reply;
  do
  {
    E.getdata();
    f.write((char *)&E, sizeof(E));
    cout << "Enter Y to put more records: ";
    cin >> reply;
  } while (toupper(reply) == 'Y'); // Add new Records
  f.close();
}
void read() //Read the Employee data from the file
{
  ifstream f("emp.txt", ios::binary | ios::in);
  emp E;
  if (!f)//Check if the file does not exit
  {
    cout << "file does not exit!!! ";
    getche();
    return;
  }
  int ctr = 0;
  while (f.read((char *)&E, sizeof(E))) //Read till the end of the file
  {
    cout << "Record: " << ++ctr << endl;
    E.putdata();
    getche();
  }
  f.close();
}
void search_eno() //Search Empolyee information from the file to find the employee data with matching employee number/id
{
  ifstream f("emp.txt", ios::binary | ios::in);
  char found = 'N';
  if (!f)
  {
    cout << "File reading error";
    getch();
    return;
  }
  emp e;
  int empno;
  cout << "Enter Employee number to be searched: ";
  cin >> empno;
  while (f.read((char *)&e, sizeof(emp))) 
  {
    if (e.geteno() == empno) // Check if Employee Number/id matches
    {
      cout << " Information of the employee: " << endl;
      e.putdata();
      found = 'Y';
      break;
    }
  }
  if (found == 'N')// If the record is not found
    cout << " No such record is found";
  f.close();
}
void sort_eno()// Sorting the Employee Information by employee number/id
{
  fstream f;
  int n;
  f.open("emp.txt", ios::binary | ios::in);// Opening file
  emp E[100]; //Store the Of Each Employee information
  if (!f) //Check if the file exits
  {
    cout << "\n FILE DOES NOT EXIT!!!";
    getch();
    return;
  }
  n = 0;
  while (f.read((char *)&E[n], sizeof(emp))) //Reading the file
    n++;
  emp temp; 
  int i, j;
  for (i = 0; i < n; i++) // Sorting based on Employee id
  {
    for (j = i; j < n - 1; j++)
    {
      if (E[j].geteno() > E[j + 1].geteno())
      {
        temp = E[j];
        E[j] = E[j + 1];
        E[j + 1] = temp;
      }
    }
  }
  f.close(); //Close file
  f.open("emp.txt", ios::out | ios::binary); //Open the file 
  i = 0;
  while (i < n)
  {
    f.write((char *)&E[i], sizeof(emp)); //Writing the sorted Employee Information into the file
    i++;
  }
  cout << "\n FILE SORTED\n";
  f.close();
}
void sort_name() //Sorting the Employee information Alphabetical Order
{
  fstream f;
  f.open("emp.txt", ios::binary | ios::in | ios::out); //Opening the file
  emp E[100]; //Aray to store Employee Information
  if (!f) //Check if the file Exist
  {
    cout << "File does not exit!!!";
    getch();
    return;
  }
  int n = 0;
  while (f.read((char *)&E[n], sizeof(E[n]))) //Read the file 
    n++;
  emp temp;
  int i, j;
  for (i = 0; i < n; i++) //Sorting the Employee Information in Alphabetical Order
  {
    for (j = i; j < n - 1; j++)
    {
      if (strcmp(E[j].getname(), E[j + 1].getname()) > 0)
      {
        temp = E[j];
        E[j] = E[j + 1];
        E[j + 1] = temp;
      }
    }
  }
  f.close(); //Close file
  f.open("emp.txt", ios::binary | ios::out | ios::in);  // opening the file
  i = 0;
  while (i < n) //Writing the sorted Employee Information back into the file 
  {
    f.write((char *)&E[i], sizeof(emp));
    i++;
  }
  f.close();
  cout << " File sorted...\n";
}
/*
* Reading the file and then coping the data in a new file till the Employee object after which the Employee Information needs to be Inserted
* Writing the new employee information the new temp file and the n copying the information the reset of the information from the main file into the new file
* Deleting the min file and thne renaming the temprary file as the main file hence updating the file 
* 
* SHOULD BE DONE IN A SORTED FILE
*/
void insertion() // Inserting a new Employee information based on the Employee number/id
{
  ifstream fmain("emp.txt", ios::binary | ios::in); //Buffer to read Employee information int the main file
  ofstream ftemp("temp.txt", ios::binary | ios::out); //Buffer to Write new Employee information in a temp file
  emp E, ENEW;
  cout << "Enter new record information ";
  ENEW.getdata();
  char EOF_FLAG = 'Y';
  while (fmain.read((char *)&E, sizeof(emp)))// read till the end of the file
  {
    if (E.geteno() <= ENEW.geteno()) // check if it has reached the assigned location where the information should be inserted based on Employee number/id
      ftemp.write((char *)&E, sizeof(emp)); //Inserting values before the New Empolyee Details
    else
    {
      ftemp.write((char *)&ENEW, sizeof(emp)); //Adding the new Empolyee information into the new File
      EOF_FLAG = 'N';
      break;
    }
  }
  if (EOF_FLAG == 'Y') // Inserting the record if it has to be placed at the end of the file
    ftemp.write((char *)&ENEW, sizeof(emp));
  else
    while (!fmain.eof()) //Inputing the rest of the Employee Information if the buffer has not reached the end of the file
    {
      ftemp.write((char *)&E, sizeof(emp));
      fmain.read((char *)&E, sizeof(emp));
    }
  fmain.close();
  ftemp.close();
  remove("emp.txt"); //Deleting the main file
  rename("temp.txt", "emp.txt"); //Renaming the temp file as the main file
}
void modify() //Updating Empolyee Information 
{
  fstream f("emp.txt", ios::binary | ios::in | ios::out);
  emp e;
  int empno;
  cout << " Enter Empno whose record to be modified: ";
  cin >> empno;
  int rec_count = 0; 
  char found = 'N';
  while (f.read((char *)&e, sizeof(emp)))// reading till the end of the file
  {
    if (e.geteno() == empno) // Check if the The current Employee Object has to be updated
    {
      cout << "Enter New information";
      e.getdata();
      f.seekg(rec_count * sizeof(emp), ios::beg);//Move the buffer at the start of the object loaction
      f.write((char *)&e, sizeof(emp));//OverWritting the old infomation with the new information
      found = 'Y';
      break;
    }
    rec_count++;
  }
  if (found == 'Y')
    cout << "Record updated";
  else
    cout << "record not found";
  f.close();
}
/* Method used to read from the main file and then copy all the Employee Information into another file.
   This is done for all Employee objects except the one that wants to be deleted based one Employee number/id 
*/
void deletion()
{
  ifstream fmain("emp.txt", ios::binary | ios::in); //Buffer to read the Employee Information main file
  ofstream ftemp("temp.txt", ios::binary | ios::out);//Buffer to write the Employee Infomation in another file 
  emp E;
  int empno;
  cout << "Enter the employee number whose record has to be deleted: ";
  cin >> empno;
  char found = 'N';
  while (fmain.read((char *)&E, sizeof(emp)))
  {
    if (E.geteno() != empno)  // Writing in new temprary file all the  Employee infomation except the Employee object that needs to be deleted
      ftemp.write((char *)&E, sizeof(emp));
    else
      found = 'Y';
  }
  if (found == 'N')
    cout << "Record not found";
  fmain.close();
  ftemp.close();
  remove("emp.txt"); //Deleting the main file
  rename("temp.txt", "emp.txt");//Renaming the new temprary file into the main file
}
int main()
{
  int ch;
  do 
  {
    system("CLS");
    cout << "FILE OPERATION MENU" << endl;
    cout << "PRESS 9 TO EXIT " << endl;
    cout << "1. CREATE OR CHANGE RECORD" << endl;
    cout << "2. DISPLAY ALL RECORDS" << endl;
    cout << "3. DISPLAY THE RECORD FOR GIVEN EMPLOYEE NO" << endl;
    cout << "4. SORT THE RECORD IN ORDER OF EMPLOYEE NO" << endl;
    cout << "5. SORT THE RECORD IN ALPHABETICAL ORDER OF NAME" << endl;
    cout << "6. INSERTION OF THE NEW RECORD WHEN FILE IS SORTED IN ORDER OF EMP NUMBER" << endl;
    cout << "7. DELETION OF A RECORD FOR THE GIVEN EMPLOYEE NO" << endl;
    cout << "8. MODIFY A RECORD FOR THE GIVEN EMPLOYEE NUMBER" << endl;
    cout << "Enter your choice: ";
    cin >> ch;
    switch (ch)// Options for Empoyee Manipulation
    {
    case 1:
      write();
      break;
    case 2:
      read();
      break;
    case 3:
      search_eno();
      break;
    case 4:
      sort_eno();
      break;
    case 5:
      sort_name();
      break;
    case 6:
      insertion();
      sort_eno();
      break;
    case 7:
      deletion();
      break;
    case 8:
      modify();
      break;
    case 9:
      exit(0);
    }
    getche();
  } while (1);
  return 0;
}
