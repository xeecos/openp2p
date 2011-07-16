#include <iostream>
#include <OpenP2P.hpp>
#include <OpenP2P/Crypt.hpp>

using namespace OpenP2P::Crypt;

int main(){
	std::cout << "Create private key" << std::endl;

	AutoSeededRandomPool rand;
	ECDSA::PrivateKey privateKey(rand, ECDSA::brainpoolP256r1);

	std::cout << "Create sign stream" << std::endl;
	ECDSA::SignStream signStream(rand, privateKey);
	OpenP2P::BinaryOStream binSign(signStream);

	std::cout << "Signing..." << std::endl;
	binSign << uint32_t(42);

	OpenP2P::Buffer signature = signStream.signature();

	std::cout << "Signed: size = " << signature.size() << " bytes" << std::endl;

	std::cout << "Make public key from private key" << std::endl;
	ECDSA::PublicKey publicKey(privateKey);

	std::cout << "Create verify stream" << std::endl;
	ECDSA::VerifyStream verifyStream(publicKey, signature);
	OpenP2P::BinaryOStream binVerify(verifyStream);

	std::cout << "Verifying..." << std::endl;
	binVerify << uint32_t(42);

	std::cout << "Signature is " << (verifyStream.isValid() ? "valid" : "not valid") << std::endl;

	return 0;
}
