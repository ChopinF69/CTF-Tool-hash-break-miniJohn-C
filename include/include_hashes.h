//
// Created by lazar on 24.02.2024.
//

#ifndef MINIJOHN_INCLUDE_HASHES_H
#define MINIJOHN_INCLUDE_HASHES_H

#include "MD5.h"
#include "SHA1.h"
#include "SHA256.h"
#include "SHA512.h"

namespace hash
{
    std::string h_md5(const std::string& input)
    {
        MD5 md5 = MD5(input);
        return md5.hexdigest();
    }

    std::string h_sha1(const std::string& input)
    {
        return sha1(input);
    }

    std::string h_sha256(const std::string& input)
    {
        return sha256(input);
    }

    std::string h_sha512(const std::string& input)
    {
        return sha512(input);
    }
}

#endif //MINIJOHN_INCLUDE_HASHES_H
