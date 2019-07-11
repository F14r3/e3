// === BEGIN phe.pila.h Name=$Name

extern e3::PilaEvalKey * g_pek_$Name;

class $Name
{
    protected:
        e3::PilQuad x;

        static e3::PilaEvalKey * pek;
        static const $Name * zero, * unit;

    public:
        static const char * name() { return "$Ename"; }
        static const char * scheme() { return "$Encryption"; }

        // Constructors
        void init0()
        {
            if ( !pek )
            {
                initEvalKey(name(), pek, g_pek_$Name);
                if ( !unit ) unit = new $Name("$PilUnit");
                if ( !zero ) zero = new $Name("$PilZero");
            }
        }

        template<typename T> T init(const T & s) { init0(); return s; }

        $Name() { init0(); }
        $Name(const std::string & s) : x(init(pek)->decor(init(s), false, "$Name")) {}
        $Name(const char * c) : $Name(std::string(c)) {}
        $Name(e3::PilQuad a) : x(init(a)) {}

        // Operators
        $Name & operator+=(const $Name & a) { return *this = *this + a; }
        $Name & operator-=(const $Name & a) { return *this = *this - a; }
        $Name & operator*=(const $Name & a) { return *this = *this * a; }
        $Name & operator++() { return *this += *unit; }
        $Name & operator--() { return *this -= *unit; }
        $Name operator++(int) { $Name r(*this); ++*this; return r; }
        $Name operator--(int) { $Name r(*this); --*this; return r; }

        $Name operator+(const $Name & a) const;
        $Name operator-(const $Name & a) const;
        $Name operator*(const $Name & a) const;

        $Name operator*(unsigned long long u) const;
        friend $Name operator*(unsigned long long u, const $Name & a) { return a * u; }

        // Functions
        std::string str() const { return pek->decor(x.str(), true, "$Name"); }
};

inline std::ostream & operator<<(std::ostream & os, const $Name & x) { return os << x.str(); }

$PostfixDefines

// === END phe.pila.h Name=$Name

