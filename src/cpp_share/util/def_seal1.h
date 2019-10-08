#ifndef _E3_DEF_SEAL1_H_
#define _E3_DEF_SEAL1_H_

// this header def_seal1.h should not be included in any code except *seal1.cpp

#include "def_seal.h"

#include "seal/seal.h"

struct SealCiphertext
{
    seal::Ciphertext b;
    SealCiphertext() {}
};

namespace e3seal
{

struct SealPrivKey
{
    seal::SecretKey secretkey;
    seal::PublicKey publickey;
    seal::IntegerEncoder * encoder;
    seal::Decryptor * decryptor;
    seal::Encryptor * encryptor;
};

struct SealEvalKey
{
    seal::RelinKeys relinkeys;
    seal::EncryptionParameters * params;
    std::shared_ptr<seal::SEALContext> context;
    seal::Evaluator * evaluator;
};

using sk = SealPrivKey;
inline  sk * tosk(e3::SealNativePrivKey a) { return static_cast<sk *>(a); }

using ek = SealEvalKey;
inline  ek * toek(e3::SealNativeEvalKey a) { return static_cast<ek *>(a); }
inline  const ek * toek(e3::cSealNativeEvalKey a) { return static_cast<const ek *>(a); }

} // e3seal
#endif // _E3_DEF_SEAL1_H_
