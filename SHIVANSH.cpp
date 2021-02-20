#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <cstring>
#include <process.h>
#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;
class emp
{
  int eno;
  char name[30];
  char phone[15];
  char dept[10];
  char desig[10];
  double salary;

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
emp::emp()
{
  eno = 0;
  name[0] = '\0';
  dept[0] = '\0';
  desig[0] = '\0';
  phone[0] = '\0';
  salary = 0;
}
emp::emp(emp &E)
{
  eno = E.eno;
  strcpy(name, E.name);
  strcpy(dept, E.dept);
  strcpy(desig, E.desig);
  strcpy(phone, E.phone);
  salary = E.salary;
}
void emp::getdata()
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
void emp::putdata()
{
  cout << "Employee number: " << eno << endl;
  cout << "Employee name: " << name << endl;
  cout << "Phone name: " << phone << endl;
  cout << "Department: " << dept << endl;
  cout << "Designation: " << desig << endl;
  cout << "Salary: " << salary << endl;
}
int emp::geteno()
{
  return (eno);
}
char *emp::getname()
{
  return (name);
}
char *emp::getdept()
{
  return (dept);
}
float emp::getsal()
{
  return (salary);
}
void write()
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
  } while (toupper(reply) == 'Y');
  f.close();
}
void read()
{
  ifstream f("emp.txt", ios::binary | ios::in);
  emp E;
  if (!f)
  {
    cout << "file does not exit!!! ";
    getche();
    return;
  }
  int ctr = 0;
  while (f.read((char *)&E, sizeof(E)))
  {
    cout << "Record: " << ++ctr << endl;
    E.putdata();
    getche();
  }
  f.close();
}
void search_eno()
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
    if (e.geteno() == empno)
    {
      cout << " Information of the employee: " << endl;
      e.putdata();
      found = 'Y';
      break;
    }
  }
  if (found == 'N')
    cout << " No such record is found";
  f.close();
}
void sort_eno()
{
  fstream f;
  int n;
  f.open("emp.txt", ios::binary | ios::in);
  emp E[100];
  if (!f)
  {
    cout << "\n FILE DOES NOT EXIT!!!";
    getch();
    return;
  }
  n = 0;
  while (f.read((char *)&E[n], sizeof(emp)))
    n++;
  emp temp;
  int i, j;
  for (i = 0; i < n; i++)
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
  f.close();
  f.open("emp.txt", ios::out | ios::binary);
  i = 0;
  while (i < n)
  {
    f.write((char *)&E[i], sizeof(emp));
    i++;
  }
  cout << "\n FILE SORTED\n";
  f.close();
}
void sort_name()
{
  fstream f;
  f.open("emp.txt", ios::binary | ios::in | ios::out);
  emp E[100];
  if (!f)
  {
    cout << "File does not exit!!!";
    getch();
    return;
  }
  int n = 0;
  while (f.read((char *)&E[n], sizeof(E[n])))
    n++;
  emp temp;
  int i, j;
  for (i = 0; i < n; i++)
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
  f.close();
  f.open("emp.txt", ios::binary | ios::out | ios::in);
  i = 0;
  while (i < n)
  {
    f.write((char *)&E[i], sizeof(emp));
    i++;
  }
  f.close();
  cout << " File sorted...\n";
}
void insertion()
{
  ifstream fmain("emp.txt", ios::binary | ios::in);
  ofstream ftemp("temp.txt", ios::binary | ios::out);
  emp E, ENEW;
  cout << "Enter new record information ";
  ENEW.getdata();
  char EOF_FLAG = 'Y';
  while (fmain.read((char *)&E, sizeof(emp)))
  {
    if (E.geteno() <= ENEW.geteno())
      ftemp.write((char *)&E, sizeof(emp));
    else
    {
      ftemp.write((char *)&ENEW, sizeof(emp));
      EOF_FLAG = 'N';
      break;
    }
  }
  if (EOF_FLAG == 'Y')
    ftemp.write((char *)&ENEW, sizeof(emp));
  else
    while (!fmain.eof())
    {
      ftemp.write((char *)&E, sizeof(emp));
      fmain.read((char *)&E, sizeof(emp));
    }
  fmain.close();
  ftemp.close();
  remove("emp.txt");
  rename("temp.txt", "emp.txt");
}
void modify()
{
  fstream f("emp.txt", ios::binary | ios::in | ios::out);
  emp e;
  int empno;
  cout << " Enter Empno whose record to be modified: ";
  cin >> empno;
  int rec_count = 0;
  char found = 'N';
  while (f.read((char *)&e, sizeof(emp)))
  {
    if (e.geteno() == empno)
    {
      cout << "Enter New information";
      e.getdata();
      f.seekg(rec_count * sizeof(emp), ios::beg);
      f.write((char *)&e, sizeof(emp));
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
void deletion()
{
  ifstream fmain("emp.txt", ios::binary | ios::in);
  ofstream ftemp("temp.txt", ios::binary | ios::out);
  emp E;
  int empno;
  cout << "Enter the employee number whose record has to be deleted: ";
  cin >> empno;
  char found = 'N';
  while (fmain.read((char *)&E, sizeof(emp)))
  {
    if (E.geteno() != empno)
      ftemp.write((char *)&E, sizeof(emp));
    else
      found = 'Y';
  }
  if (found == 'N')
    cout << "Record not found";
  fmain.close();
  ftemp.close();
  remove("emp.txt");
  rename("temp.txt", "emp.txt");
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
    switch (ch)
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
