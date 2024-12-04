#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 基类：Person
class Person {
protected:
    int id;
    string name;
    int level;
    double salary;
    static int count; // 静态数据成员，记录员工总数以生成编号

public:
    Person(string n, int l = 1) : name(n), level(l) {
        id = 2001 + count++; // 员工编号从2001开始
        salary = 0;
    }

    virtual ~Person() {}

    // 虚函数，计算并返回工资
    virtual void pay() = 0;
    virtual double getSalary() const {
        return salary;
    }

    virtual void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Level: " << level << ", Salary: " << salary << endl;
    }
};

int Person::count = 0; // 初始化静态成员变量

// Manager类
class Manager : public Person {
public:
    Manager(string n) : Person(n, 4) {}

    void pay() override {
        salary = 18000; // 固定月薪
    }
};

// Technician类
class Technician : public Person {
private:
    int workHours; // 月工作时间

public:
    Technician(string n, int hours) : Person(n, 3), workHours(hours) {}

    void pay() override {
        salary = workHours * 100; // 每小时100元
    }
};

// Salesman类
class Salesman : public Person {
private:
    double sales; // 当月销售额

public:
    Salesman(string n, double s) : Person(n, 1), sales(s) {}

    void pay() override {
        salary = sales * 0.04; // 4% 提成
    }
};

// Salesmanager类（多重继承自Manager和Salesman）
class Salesmanager : public Manager, public Salesman {
private:
    double totalSales; // 所管辖部门销售总额

public:
    Salesmanager(string n, double s) : Person(n, 2), Manager(n), Salesman(n, s), totalSales(s) {}

    void pay() override {
        salary = 5000 + totalSales * 0.02; // 固定月薪5000元 + 2% 部门提成
    }
};

// 系统操作类
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

// 主函数
int main() {
    SalarySystem system;
    int choice;

    while (true) {
        cout << "****** 公司职工薪酬管理系统 ******\n";
        cout << "1. 输入职工资料\n";
        cout << "2. 增加职工\n";
        cout << "3. 删除职工\n";
        cout << "4. 月薪发放\n";
        cout << "5. 显示工资表\n";
        cout << "0. 退出系统\n";
        cout << "请选择: ";
        cin >> choice;

        if (choice == 0) break;

        string name;
        int hours;
        double sales;

        switch (choice) {
            case 1: {
                cout << "输入职工姓名: ";
                cin >> name;
                cout << "输入职工类型 (1. 经理 2. 技术人员 3. 推销员 4. 销售经理): ";
                int type;
                cin >> type;
                Person* p = nullptr;

                if (type == 1) {
                    p = new Manager(name);
                } else if (type == 2) {
                    cout << "输入工作小时数: ";
                    cin >> hours;
                    p = new Technician(name, hours);
                } else if (type == 3) {
                    cout << "输入当月销售额: ";
                    cin >> sales;
                    p = new Salesman(name, sales);
                } else if (type == 4) {
                    cout << "输入部门总销售额: ";
                    cin >> sales;
                    p = new Salesmanager(name, sales);
                } else {
                    cout << "无效输入!\n";
                }

                if (p) {
                    system.addEmployee(p);
                    cout << "职工资料已录入。\n";
                }
                break;
            }
            case 2: {
                // 这里只是展示功能，可以调用case 1的代码
                cout << "增加新职工，请按类型输入信息。\n";
                break;
            }
            case 3: {
                int id;
                cout << "输入要删除的职工编号: ";
                cin >> id;
                system.removeEmployee(id);
                break;
            }
            case 4: {
                cout << "发放所有职工月薪：\n";
                system.payAll();
                break;
            }
            case 5: {
                cout << "显示所有职工的工资表：\n";
                system.displayAll();
                break;
            }
            default:
                cout << "无效选项！\n";
        }
    }

    return 0;
}

