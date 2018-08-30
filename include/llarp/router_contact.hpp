#ifndef LLARP_RC_HPP
#define LLARP_RC_HPP
#include <llarp/address_info.hpp>
#include <llarp/crypto.h>
#include <llarp/bencode.hpp>
#include <llarp/exit_info.hpp>

#include <list>

#define MAX_RC_SIZE (1024)
#define NICKLEN (32)

namespace llarp
{
  struct RouterContact : public IBEncodeMessage
  {
    // advertised addresses
    std::list< AddressInfo > addrs;
    // public encryption public key
    llarp::PubKey enckey;
    // public signing public key
    llarp::PubKey pubkey;
    // advertised exits
    std::list< ExitInfo > exits;
    // signature
    llarp::Signature signature;
    /// node nickname, yw kee
    llarp::AlignedBuffer< NICKLEN > nickname;

    uint64_t last_updated;

    bool
    BEncode(llarp_buffer_t *buf) const;

    bool
    DecodeKey(llarp_buffer_t k, llarp_buffer_t *buf);

    RouterContact &
    operator=(const RouterContact &other);

    bool
    HasNick() const;

    std::string
    Nick() const;

    bool
    IsPublicRouter() const;

    void
    SetNick(const std::string &nick);

    bool
    VerifySignature(llarp_crypto *crypto) const;

    bool
    Sign(llarp_crypto *crypto, const llarp::SecretKey &secret);

    bool
    Read(const char *fname);

    bool
    Write(const char *fname) const;
  };
}  // namespace llarp

#endif
