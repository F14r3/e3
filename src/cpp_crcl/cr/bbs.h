// FIXME o add e3cr namespace to all exported headers
#pragma once

#include <memory>

#include "olc.h"
#include "olrnd.h"
#include "crutil.h"

using vbool = vector<bool>;
using vvbool = vector<vbool>;

std::ostream & operator<<(std::ostream & os, const vbool & v);
std::ostream & operator<<(std::ostream & os, const vvbool & m);
std::istream & operator>>(std::istream & is, vbool & v);
std::istream & operator>>(std::istream & is, vvbool & m);


void makeBbs(string file);
void bbs2cir(string file);

struct Rcop
{
    int rc, x, y;
    bool operator==(const Rcop & a) const { return rc == a.rc && x == a.x && y == a.y; }
};

class BbsAbs
{
    public:
        virtual void save(std::ostream & os) = 0;
        virtual void generate() = 0;
        virtual void cir(std::ostream & os, bool fwdmx, bool & xy) = 0;
};

class Bbs;

class Lbs : public BbsAbs
{
        ///string file;

        int sz;       // size of the matrix and vector - inputs
        ///ull seed; // seed for random Rcop sequence
        Rnd * rnd;
    public:
        vbool b1, b2;
        vvbool A1, A2;
    private:
        ///string formula;
        vector<Rcop> genRcops();

        // matrix operationis
        static vvbool unit(int sz);
        static void apply(vvbool & a, Rcop z);
        static void mul(vbool & y, const vvbool & a, const vbool c);
        static vvbool mul(const vvbool & a, const vvbool & b);
        static bool equal(const vvbool & a, const vvbool & b);

        ///public:
        ///Lbs(string file, bool load);
        Lbs(int z, bool load, std::istream & is, Rnd * r);

        ///void save() { save(file); }
        ///void save(string file);
        virtual void save(std::ostream & os);
        virtual void generate();

        friend class Bbs;
        virtual void cir(std::ostream & os, bool fwdmx, bool & xy);
};


struct Element
{
    char typ;
    int siz; // size of operations, e.g 2 means a=a^b*c*d
    Element(char t, int s = 1): typ(t), siz(s) {}
};

struct Formula
{

    std::vector<Element> elements;
    friend std::istream & operator>>(std::istream & is, Formula &);
    friend std::ostream & operator<<(std::ostream & is, const Formula &);
};

class Fbs : public BbsAbs
{
        int sz;       // size of the matrix and vector - inputs
        Rnd * rnd;
        Element element;
        std::vector<int> idxs;

    public:
        Fbs(Element e, int z, bool load, std::istream & is, Rnd * r);
        virtual void save(std::ostream & os);
        virtual void cir(std::ostream & os, bool fwdmx, bool & xy);
        virtual void generate();
};


class Bbs
{
        int sz;   // size of the matrix and vector - inputs
        std::string seed; // seed for random Rcop sequence
        Rnd * rnd; // never deletes
    public:
        std::vector<Lbs> lbs;
        std::vector<Fbs> fbs;
        std::vector<BbsAbs *> bbs;

    protected:
        Formula formula;

    public:
        Bbs(): sz(0), rnd(nullptr) {}
        void init(std::istream & in, bool load, Rnd * r);

        void save(std::ostream & of);
        void save(std::ostream && of) { save(of); }
        void generate();
        void cir(std::ostream & of1, std::ostream & of2);
};

// Bbs with file name
class Bbsf : public Bbs
{
        string file;
        void save(string fil);

    public:
        Bbsf(string fil, bool load);
        void save() { save(file); }
        void cir();
};
