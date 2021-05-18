// Virtual function
// -----------------
// Person - base class
// Professor and Student are derived class with different fields
#include<iostream>
class Person
{
    public:
    char name[100];
    int age;
    virtual void getdata()=0;
    virtual void putdata()=0;
};
class Professor:public Person
{
    public:
    int pub;
    static int id;
    void getdata()
    {
        cin>>name;
        cin>>age;
        cin>>pub;
    }
    void putdata()
    {
         cout<<name<<" "<<age<<" "<<pub<<" "<<++id<<endl;   
    }
    
};
int Professor::id=0;
class Student:public Person
{
    public:
    int marks[6];
    static int id;
    void getdata()
    {
        cin>>name;
        cin>>age;
        for(int i=0;i<6;i++)
        {
            cin>>marks[i];     
        }
    }
    void putdata()
    {
        int s=0;
        for(int i=0;i<6;i++)
        {
            s=s+marks[i];    
        }
         cout<<name<<" "<<age<<" "<<s<<" "<<++id<<endl;   
    }
 
};
int Student::id=0;
    
Approach 2.

class Person{
  protected:
  	char name[101];
	int age;
  public:
	virtual void putdata() = 0;
	virtual void getdata() = 0;
};

class Professor: public Person{
  private:
	static int id;
	int cur_id;
	int publications;
  public:
	Professor() {cur_id = ++id;};
	void putdata(){
		cout << name << " " << age << " " << publications << " " << cur_id << "\n";
	}
	void getdata(){
		cin >> name >> age >> publications;
	}
};

int Professor::id = 0;

class Student: public Person{
	static int id;
	int cur_id;
	int marks[6];

	int summarks() {
		int sum = marks[0];
		for (int i = 1; i<6; i++)
			sum += marks[i];
		return sum;
	}

  public:
	Student() {cur_id = ++id;};
	void putdata(){
		cout << name << " " << age << " " << summarks() << " " << cur_id << "\n";
	}
	void getdata(){
		cin >> name >> age;
		for (int i = 0; i<6; i++)
			cin >> marks[i] ;
	}
};

int Student::id = 0;
Approach 3.

static int professorID, studentID;

class Person

{

private:
string name;
int age;

public:
virtual void getdata() {
    cin >> name;
    cin >> age;
}
virtual void putdata() {
    cout << name << " " << age << " ";
}

};

class Professor : public Person

{

private:
int publication;
int id;

public:
Professor() {
    professorID++;
}
void getdata() {
    Person::getdata();
    cin >> publication;
    id = professorID;
}
void putdata() {
    Person::putdata();
    cout << publication << " " << id << endl;
}

};

class Student : public Person
{
  private:
    int marks[6];
    int id;
  public:
    Student() {
        studentID++;
    }
    void getdata() {
        Person::getdata();
        for(int i = 0; i < 6; ++i)
            cin >> marks[i];
        id = studentID;
    }
    void putdata() {
        Person::putdata();
        int sum = 0;
        for(int i = 0; i < 6; ++i)
            sum += marks[i];
        cout << sum << " " << id << endl;
    }
};