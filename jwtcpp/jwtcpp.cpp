#include <jwt-cpp/jwt.h>
#include <iostream>

int main() 
{
	auto token = jwt::create()
		.set_type("JWS")
		.set_issuer("auth0")
		.set_payload_claim("sample", jwt::claim(std::string("test")))
		.set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{ 1000000 })
		.sign(jwt::algorithm::hs256{ "secret" });
	auto decoded = jwt::decode(token);

	for (auto& e : decoded.get_payload_json())
		std::cout << e.first << " = " << e.second << std::endl;

	auto verifier = jwt::verify()
		.with_issuer("auth0")
		.with_claim("sample", jwt::claim(std::string("test")))
		.allow_algorithm(jwt::algorithm::hs256{ "secret" });

	try
	{
		verifier.verify(decoded);
		for (auto& e : decoded.get_header_json())
			std::cout << e.first << " = " << e.second << std::endl;
		for (auto& e : decoded.get_payload_json())
			std::cout << e.first << " = " << e.second << std::endl;
	}
	catch (const jwt::error::token_verification_exception& e)
	{
		std::cout << "token_verification_error";
	}
}