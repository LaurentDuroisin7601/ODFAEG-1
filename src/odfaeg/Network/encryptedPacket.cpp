#include "../../../include/odfaeg/Network/encryptedPacket.h"
#include "../../../include/odfaeg/Network/network.h"
namespace odfaeg {
    namespace network {
        using namespace std;
        using namespace sf;
        Rsa& EncryptedPacket::rsa = EncryptedPacket::getRsa();
        bool EncryptedPacket::encryptWithPrKey = true;
        bool EncryptedPacket::decryptWithPrKey = true;
        Rsa& EncryptedPacket::getRsa() {
            if (&rsa == nullptr) {
                static Rsa rsa;
                return rsa;
            }
            return rsa;
        }
        int EncryptedPacket::getCertificate(unsigned char** out) {
            return rsa.ossl_getCertificate(out);
        }
        void EncryptedPacket::setCertificate(const unsigned char* in, int length) {
            rsa.ossl_setCertificate(in, length);
        }
        void EncryptedPacket::setEncryptWithPrKey(bool b) {
            encryptWithPrKey = b;
        }
        void EncryptedPacket::setDecryptWithPrKey(bool b) {
            decryptWithPrKey = b;
        }
        const void* EncryptedPacket::onSend (size_t& dataSize) {
            unsigned char* buffer = nullptr;
            if (Network::getSrvInstance().isRunning())
                buffer = rsa.ossl_encryptWithPrKey(static_cast<const unsigned char*> (getData()), getDataSize(), reinterpret_cast<int&>(dataSize));
            else
                buffer = rsa.ossl_encryptWithPbKey(static_cast<const unsigned char*> (getData()), getDataSize(), reinterpret_cast<int&>(dataSize));
            return &buffer[0];
        }
        void EncryptedPacket::onReceive (const void* data, size_t dataSize) {
            unsigned char* buffer = nullptr;
            std::size_t dstSize = 0;
            if (Network::getSrvInstance().isRunning())
                buffer = rsa.ossl_decryptWithPrKey(static_cast<const unsigned char*> (data), dataSize, reinterpret_cast<int&>(dstSize));
            else
                buffer = rsa.ossl_decryptWithPbKey(static_cast<const unsigned char*> (data), dataSize, reinterpret_cast<int&>(dstSize));
            append(&buffer[0], dstSize);
        }
    }
}