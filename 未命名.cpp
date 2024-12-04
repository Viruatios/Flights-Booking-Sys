#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ���ࣺPerson
class Person {
protected:
    int id;
    string name;
    int level;
    double salary;
    static int count; // ��̬���ݳ�Ա����¼Ա�����������ɱ��

public:
    Person(string n, int l = 1) : name(n), level(l) {
        id = 2001 + count++; // Ա����Ŵ�2001��ʼ
        salary = 0;
    }

    virtual ~Person() {}

    // �麯�������㲢���ع���
    virtual void pay() = 0;
    virtual double getSalary() const {
        return salary;
    }

    virtual void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Level: " << level << ", Salary: " << salary << endl;
    }
};

int Person::count = 0; // ��ʼ����̬��Ա����

// Manager��
class Manager : public Person {
public:
    Manager(string n) : Person(n, 4) {}

    void pay() override {
        salary = 18000; // �̶���н
    }
};

// Technician��
class Technician : public Person {
private:
    int workHours; // �¹���ʱ��

public:
    Technician(string n, int hours) : Person(n, 3), workHours(hours) {}

    void pay() override {
        salary = workHours * 100; // ÿСʱ100Ԫ
    }
};

// Salesman��
class Salesman : public Person {
private:
    double sales; // �������۶�

public:
    Salesman(string n, double s) : Person(n, 1), sales(s) {}

    void pay() override {
        salary = sales * 0.04; // 4% ���
    }
};

// Salesmanager�ࣨ���ؼ̳���Manager��Salesman��
class Salesmanager : public Manager, public Salesman {
private:
    double totalSales; // ����Ͻ���������ܶ�

public:
    Salesmanager(string n, double s) : Person(n, 2), Manager(n), Salesman(n, s), totalSales(s) {}

    void pay() override {
        salary = 5000 + totalSales * 0.02; // �̶���н5000Ԫ + 2% �������
    }
};

// ϵͳ������
class SalarySystem {
private:
    vector<Person*> employees;

public:
    ~SalarySystem() {
        for (auto e : employees)
            delete e;
    }

    void addEmployee(Person* p) {
        employees.push_back(p);
    }

    void removeEmployee(int id) {
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if ((*it)->getSalary() == id) {
                delete *it;
                employees.erase(it);
                cout << "Employee removed.\n";
                return;
            }
        }
        cout << "Employee not found.\n";
    }

    void payAll() {
        for (auto e : employees) {
            e->pay();
            e->display();
        }
    }

    void displayAll() const {
        for (const auto e : employees)
            e->display();
    }
};

// ������
int main() {
    SalarySystem system;
    int choice;

    while (true) {
        cout << "****** ��˾ְ��н�����ϵͳ ******\n";
        cout << "1. ����ְ������\n";
        cout << "2. ����ְ��\n";
        cout << "3. ɾ��ְ��\n";
        cout << "4. ��н����\n";
        cout << "5. ��ʾ���ʱ�\n";
        cout << "0. �˳�ϵͳ\n";
        cout << "��ѡ��: ";
        cin >> choice;

        if (choice == 0) break;

        string name;
        int hours;
        double sales;

        switch (choice) {
            case 1: {
                cout << "����ְ������: ";
                cin >> name;
                cout << "����ְ������ (1. ���� 2. ������Ա 3. ����Ա 4. ���۾���): ";
                int type;
                cin >> type;
                Person* p = nullptr;

                if (type == 1) {
                    p = new Manager(name);
                } else if (type == 2) {
                    cout << "���빤��Сʱ��: ";
                    cin >> hours;
                    p = new Technician(name, hours);
                } else if (type == 3) {
                    cout << "���뵱�����۶�: ";
                    cin >> sales;
                    p = new Salesman(name, sales);
                } else if (type == 4) {
                    cout << "���벿�������۶�: ";
                    cin >> sales;
                    p = new Salesmanager(name, sales);
                } else {
                    cout << "��Ч����!\n";
                }

                if (p) {
                    system.addEmployee(p);
                    cout << "ְ��������¼�롣\n";
                }
                break;
            }
            case 2: {
                // ����ֻ��չʾ���ܣ����Ե���case 1�Ĵ���
                cout << "������ְ�����밴����������Ϣ��\n";
                break;
            }
            case 3: {
                int id;
                cout << "����Ҫɾ����ְ�����: ";
                cin >> id;
                system.removeEmployee(id);
                break;
            }
            case 4: {
                cout << "��������ְ����н��\n";
                system.payAll();
                break;
            }
            case 5: {
                cout << "��ʾ����ְ���Ĺ��ʱ�\n";
                system.displayAll();
                break;
            }
            default:
                cout << "��Чѡ�\n";
        }
    }

    return 0;
}

