#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

class Student {
protected:
    std::string first_name;
    std::string last_name;
    double gpa;
    int grad_year;
    std::string grad_semester;
    int enrolled_year;
    std::string enrolled_semester;
    std::string level;

public:
    Student() : first_name(""), last_name(""), gpa(0.0), grad_year(0), grad_semester(""),
                enrolled_year(0), enrolled_semester(""), level("") {}

    virtual ~Student() {}

    void setName(const std::string &first, const std::string &last) {
        first_name = first;
        last_name = last;
    }
    void setGPA(double g) { gpa = g; }
    void setGradYear(int year) { grad_year = year; }
    void setGradSemester(const std::string &sem) { grad_semester = sem; }
    void setEnrolledYear(int year) { enrolled_year = year; }
    void setEnrolledSemester(const std::string &sem) { enrolled_semester = sem; }
    void setLevel(const std::string &lvl) { level = lvl; }

    virtual void print(std::ostream &os) const {
        os << first_name << " " << last_name << ", gpa: " << gpa
           << ", grad: " << grad_semester << " " << grad_year
           << ", enrolled: " << enrolled_semester << " " << enrolled_year
           << ", level: " << level;
    }
};

class Art_Student : public Student {
private:
    std::string art_emphasis;

public:
    Art_Student() : art_emphasis("") {}

    void setArtEmphasis(const std::string &emphasis) { art_emphasis = emphasis; }

    void print(std::ostream &os) const override {
        Student::print(os);
        os << ", Emphasis: " << art_emphasis << "\n";
    }
};

class Physics_Student : public Student {
private:
    std::string concentration;

public:
    Physics_Student() : concentration("") {}

    void setConcentration(const std::string &conc) { concentration = conc; }

    void print(std::ostream &os) const override {
        Student::print(os);
        os << ", Concentration: " << concentration << "\n";
    }
};

int main() {
    std::vector<Art_Student *> art_students;
    std::vector<Physics_Student *> physics_students;

    for (int i = 0; i < 5; ++i) {
        std::stringstream fn, ln;
        fn << "first name" << i;
        ln << "last name" << i;

        Art_Student *a = new Art_Student();
        a->setName(fn.str(), ln.str());
        a->setGPA(3.5 + i * 0.1);
        a->setGradYear(2026);
        a->setGradSemester("Spring");
        a->setEnrolledYear(2022);
        a->setEnrolledSemester("Fall");
        a->setLevel(i % 2 == 0 ? "undergrad" : "grad");
        a->setArtEmphasis(i % 3 == 0 ? "art" : i % 3 == 1 ? "art history" : "graphic design");
        art_students.push_back(a);
    }

    for (int i = 0; i < 5; ++i) {
        std::stringstream fn, ln;
        fn << "first name" << i;
        ln << "last name" << i;

        Physics_Student *p = new Physics_Student();
        p->setName(fn.str(), ln.str());
        p->setGPA(3.6 + i * 0.1);
        p->setGradYear(2027);
        p->setGradSemester("Fall");
        p->setEnrolledYear(2023);
        p->setEnrolledSemester(i % 2 == 0 ? "Spring" : "Fall");
        p->setLevel("grad");
        p->setConcentration(i % 2 == 0 ? "physics" : "nuclearr physics");
        physics_students.push_back(p);
    }

    std::ofstream outfile("student_info.dat");
    for (size_t i = 0; i < art_students.size(); ++i) {
        art_students[i]->print(outfile);
    }
    for (size_t i = 0; i < physics_students.size(); ++i) {
        physics_students[i]->print(outfile);
    }
    outfile.close();
         
    for (size_t i = 0; i < art_students.size(); ++i) delete art_students[i];
    for (size_t i = 0; i < physics_students.size(); ++i) delete physics_students[i];

    return 0;
}

