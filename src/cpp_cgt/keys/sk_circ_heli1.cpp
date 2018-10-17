#include <fstream>
#include <iostream>

#include "sk_circ_heli.h"
#include "def_heli1.h"
#include "ol.h"

using std::cout;

string CircuitPrivKey_heli::filename() { return PrivKey::filename(); }

CircuitPrivKey_heli::CircuitPrivKey_heli
(std::string name, bool forceGen, bool forceLoad, std::string seed, int lam)
    : CircuitPrivKey(name, seed, lam, &ek), ek(name)
{
    init_final(forceGen, forceLoad);
}

void CircuitPrivKey_heli::gen()
{
	init_properties();
        key = new FHESecKey(*properties->pcontext);
		FHESecKey & skey = *e3heli::tosk(key);
        skey.GenSecKey(64);      // A Hamming-weight-64 secret key
        addSome1DMatrices(skey); // compute key-switching matrices that we need
        addFrbMatrices(skey);
        cout << "computing key-dependent tables..." << std::flush;
        skey.genRecryptData();
        cout << " done\n";

		ek.key = key;
}

void CircuitPrivKey_heli::save()
{
	FHESecKey & k = *e3heli::tosk(key);
    cout << "Saving private key .. " << std::flush;
    {
        std::ofstream of(filename(), std::ios::binary);
	    of << k;
    }
    cout << "ok\n";

    ek.save();
}

bool CircuitPrivKey_heli::load()
{
	init_properties();
	key = new FHESecKey(*properties->pcontext);

	FHESecKey & k = *e3heli::tosk(key);
    std::ifstream in(filename(), std::ios::binary);
    if ( !in ) return false;
    in >> k;
    return ek.load();
}

std::string CircuitPrivKey_heli::encbitstr(bool b) const
{
    //TfheNativeBit nb(ek.key);
    //bootsSymEncrypt(&*nb.p, b, e3tfhe::tosk(key));
    //return nb.str(ek.key);
    //Fhe::Bit r;
    //ek->key->Encrypt(r.nb.ctxt, to_ZZX(m));
    //return r;
    HeliNativeBit nb(ek.key);
    e3heli::toek(ek.key)->Encrypt(nb.ctxt->b, to_ZZX(b));
 	return nb.str(ek.key);
}

bool CircuitPrivKey_heli::decbitstr(const std::string & s, bool * ok) const
{
    never("FIXME");
}

// ----------------------------------
//const int IDX = 11;
const int IDX = 0;
//  0:  -104.65     1:  -98.66      2:  -93.83      3:  -88.53
//  4:  -74.04      5:  2.15        6:  28.62       7:  43.54
//  8:  56.?        9:  65.?        10: 87.?        11: 102.?
//  12: 113.975
// using 0 or 11

long mValues(int i, int j)
{
static long smValues[][14] =
{
//{ p, phi(m),  m,    d, m1,  m2, m3,   g1,    g2,    g3,ord1,ord2,ord3, c_m}
    {  2,   600,  1023, 10, 11,  93,  0,   838,   584,    0, 10,  6,   0, 100}, // m=(3)*11*{31} m/phim(m)=1.7    C=24  D=2 E=1
    {  2,  1200,  1705, 20, 11, 155,  0,   156,   936,    0, 10,  6,   0, 100}, // m=(5)*11*{31} m/phim(m)=1.42   C=34  D=2 E=2
    {  2,  1728,  4095, 12,  7,  5, 117,  2341,  3277, 3641,  6,  4,   6, 100}, // m=(3^2)*5*7*{13} m/phim(m)=2.36 C=26 D=3 E=2
    {  2,  2304,  4641, 24,  7,  3, 221,  3979,  3095, 3760,  6,  2,  -8, 100}, // m=3*7*(13)*{17} :-( m/phim(m)=2.01 C=45 D=4 E=3
    {  2,  4096,  4369, 16, 17, 257,  0,   258,  4115,    0, 16, -16,   0, 100}, // m=17*(257) :-( m/phim(m)=1.06 C=61 D=3 E=4
    {  2, 12800, 17425, 40, 41, 425,  0,  5951,  8078,    0, 40, -8,   0, 100}, // m=(5^2)*{17}*41 m/phim(m)=1.36 C=93  D=3 E=3
    {  2, 15004, 15709, 22, 23, 683,  0,  4099, 13663,    0, 22, 31,   0, 100}, // m=23*(683) m/phim(m)=1.04      C=73  D=2 E=1
    {  2, 16384, 21845, 16, 17,   5, 257,  8996, 17477, 21591, 16, 4, -16, 1600}, // m=5*17*(257) :-( m/phim(m)=1.33 C=65 D=4 E=4
    {  2, 18000, 18631, 25, 31, 601,  0, 15627,  1334,    0, 30, 24,   0,  50}, // m=31*(601) m/phim(m)=1.03      C=77  D=2 E=0
    {  2, 18816, 24295, 28, 43, 565,  0, 16386, 16427,    0, 42, 16,   0, 100}, // m=(5)*43*{113} m/phim(m)=1.29  C=84  D=2 E=2
    {  2, 21168, 27305, 28, 43, 635,  0, 10796, 26059,    0, 42, 18,   0, 100}, // m=(5)*43*{127} m/phim(m)=1.28  C=86  D=2 E=2
    {  2, 23040, 28679, 24, 17,  7, 241, 15184,  4098, 28204, 16,  6, -10, 1000}, // m=7*17*(241) m/phim(m)=1.24    C=63  D=4 E=3
    {  2, 24000, 31775, 20, 41, 775,  0,  6976, 24806,    0, 40, 30,   0, 100}, // m=(5^2)*{31}*41 m/phim(m)=1.32 C=88  D=2 E=2
    {  2, 26400, 27311, 55, 31, 881,  0, 21145,  1830,    0, 30, 16,   0, 100}, // m=31*(881) m/phim(m)=1.03      C=99  D=2 E=0
    {  2, 31104, 35113, 36, 37, 949,  0, 16134,  8548,    0, 36, 24,   0, 400}, // m=(13)*37*{73} m/phim(m)=1.12  C=94  D=2 E=2
    {  2, 34848, 45655, 44, 23, 1985, 0, 33746, 27831,    0, 22, 36,   0, 100}, // m=(5)*23*{397} m/phim(m)=1.31  C=100 D=2 E=2
    {  2, 42336, 42799, 21, 127, 337, 0, 25276, 40133,    0, 126, 16,   0,  20}, // m=127*(337) m/phim(m)=1.01     C=161 D=2 E=0
    {  2, 45360, 46063, 45, 73, 631,  0, 35337, 20222,    0, 72, 14,   0, 100}, // m=73*(631) m/phim(m)=1.01      C=129 D=2 E=0
    {  2, 46080, 53261, 24, 17, 13, 241, 43863, 28680, 15913, 16, 12, -10, 100}, // m=13*17*(241) m/phim(m)=1.15   C=69  D=4 E=3
    {  2, 49500, 49981, 30, 151, 331, 0,  6952, 28540,    0, 150, 11,   0, 100}, // m=151*(331) m/phim(m)=1        C=189 D=2 E=1
    {  2, 54000, 55831, 25, 31, 1801, 0, 19812, 50593,    0, 30, 72,   0, 100}, // m=31*(1801) m/phim(m)=1.03     C=125 D=2 E=0
    {  2, 60016, 60787, 22, 89, 683,  0,  2050, 58741,    0, 88, 31,   0, 200}, // m=89*(683) m/phim(m)=1.01      C=139 D=2 E=1
};
const int num_smValues = (sizeof(smValues) / (sizeof(smValues[0])));
if( i>=num_smValues )
{
	std::cerr<<"Bad index in mValues\n";
	i=0;
}
	return smValues[i][j];
}



void CircuitPrivKey_heli::init_properties()
{
    name += std::to_string(IDX);

    cout << "Initializing HELIB .. " << std::flush;

    int idx = IDX;
    cout << "IDX=" << idx << '\n';

    bool cons = false;
    long p = 2;
    long r = 1;
    long c = 3;
    long L = 25;
    long B = 23;
    if (B > NTL_SP_NBITS / 2) B = NTL_SP_NBITS / 2;

    Vec<long> mvec;
    vector<long> gens;
    vector<long> ords;

    long m = mValues(idx,2);
    assert(GCD(p, m) == 1);

    append(mvec, mValues(idx,4));
    if (mValues(idx,5) > 1) append(mvec, mValues(idx,5));
    if (mValues(idx,6) > 1) append(mvec, mValues(idx,6));
    gens.push_back(mValues(idx,7));
    if (mValues(idx,8) > 1) gens.push_back(mValues(idx,8));
    if (mValues(idx,9) > 1) gens.push_back(mValues(idx,9));
    ords.push_back(mValues(idx,10));
    if (abs(mValues(idx,11)) > 1) ords.push_back(mValues(idx,11));
    if (abs(mValues(idx,12)) > 1) ords.push_back(mValues(idx,12));

	static NativeProperties props;
	properties = &props;

    cout << "[ Computing tables " << std::flush;
    props.pcontext = new FHEcontext(m, p, r, gens, ords);
    FHEcontext & context = *props.pcontext;
    context.bitsPerLevel = B;
    buildModChain(context, L, c);
    context.makeBootstrappable(mvec, /*t=*/0, cons);
    cout << "] " << std::flush;;

    //context.zMStar.printout();

    long nPrimes = context.numPrimes();
    IndexSet allPrimes(0, nPrimes - 1);

    if (0)
    {
        double bitsize = context.logOfProduct(allPrimes) / log(2.0);
        long phim = mValues(idx,1);
        cout << "  " << nPrimes << " primes in chain, total bitsize="
             << ceil(bitsize) << ", secparam="
             << (7.2 * phim / bitsize - 110) << std::flush;
    }

    cout << " level=" << context.securityLevel() << std::flush;

    //long p2r = context.alMod.getPPowR();
    context.zMStar.set_cM(mValues(idx,13) / 100.0);

    cout << " ok\n";
}

