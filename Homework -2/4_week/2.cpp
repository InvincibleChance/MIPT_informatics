#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>

class Individual {
public:
    virtual void speak() const = 0;

    virtual ~Individual() = default;

    virtual int id() const = 0;
};

class Alice : public Individual {
public:
    void speak() const override {
        std::cout << "Hi, I am Alice\n";
    }

    int id() const override { return 0; }
};

class Bob : public Individual {
public:
    void speak() const override {
        std::cout << "Hi, I am Bob\n";
    }

    int id() const override { return 1; }
};

class Casper : public Individual {
public:
    void speak() const override {
        std::cout << "Hi, I am Casper\n";
    }

    int id() const override { return 2; }
};


std::vector<Individual *> createIndividuals() {
    std::vector<Individual *> v;
    for (int i = 0; i < 3; ++i) v.push_back(new Alice);
    for (int i = 0; i < 2; ++i) v.push_back(new Bob);
    for (int i = 0; i < 4; ++i) v.push_back(new Casper);
    return v;
}


void letThemSpeak(const std::vector<Individual *> &v) {
    for (Individual *p: v) {
        p->speak();
    }
}

void deleteIndividuals(std::vector<Individual *> &v) {
    for (Individual *p: v) {
        delete p;
    }
    v.clear();
}


int identification_dynamic(Individual *p) {
    if (dynamic_cast<Alice *>(p)) return 0;
    if (dynamic_cast<Bob *>(p)) return 1;
    if (dynamic_cast<Casper *>(p)) return 2;
    return -1;
}


int identification_typeid(Individual *p) {
    const std::type_info &ti = typeid(*p);
    if (ti == typeid(Alice)) return 0;
    if (ti == typeid(Bob)) return 1;
    if (ti == typeid(Casper)) return 2;
    return -1;
}


std::vector<std::unique_ptr<Individual> > createIndividualsUP() {
    std::vector<std::unique_ptr<Individual> > v;
    for (int i = 0; i < 3; ++i) v.push_back(std::make_unique<Alice>());
    for (int i = 0; i < 2; ++i) v.push_back(std::make_unique<Bob>());
    for (int i = 0; i < 4; ++i) v.push_back(std::make_unique<Casper>());
    return v;
}

void letThemSpeakUP(const std::vector<std::unique_ptr<Individual> > &v) {
    for (auto &p: v) {
        p->speak();
    }
}


int main() {
    auto v = createIndividuals();
    letThemSpeak(v);
    deleteIndividuals(v);

    std::cout << "—— smart pointers ——\n";

    auto up = createIndividualsUP();
    letThemSpeakUP(up);

    Individual *p = up[0].get();
    std::cout << "via virtual id():      " << p->id() << "\n";
    std::cout << "via dynamic_cast:      " << identification_dynamic(p) << "\n";
    std::cout << "via typeid:            " << identification_typeid(p) << "\n";
}